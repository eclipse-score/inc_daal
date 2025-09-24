/********************************************************************************
* Copyright (c) 2025 Contributors to the Eclipse Foundation
*
* See the NOTICE file(s) distributed with this work for additional
* information regarding copyright ownership.
*
* This program and the accompanying materials are made available under the
* terms of the Apache License Version 2.0 which is available at
* https://www.apache.org/licenses/LICENSE-2.0
*
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/

#include "worker_thread.hpp"

#include <sched.h>

#include <atomic>
#include <cerrno>
#include <condition_variable>
#include <cstdlib>
#include <cstring>
#include <future>

#include "daal/log/framework_logger.hpp"

namespace daal {

namespace af {

namespace worker {

WorkerThread::WorkerThread(unsigned int core_id, int priority)
    : worker_thread_(),
      tasks_{},
      mutex_{},
      condition_{},
      submit_condition_{},
      worker_promise_{nullptr},
      stop_flag_{false},
      thread_attr_{},
      core_id_{core_id} {
  // Initialize thread attributes
  InitializeThreadAttributes(priority);
  int ret_pth = pthread_create(&worker_thread_, &thread_attr_, &WorkerThread::ThreadEntryFunction, this);
  switch (ret_pth) {
    case 0:
      break;
    case EAGAIN:
      daal::log::FrameworkLogger::get()->Error(
          "EAGAIN: Insufficient resources to create another thread, or a "
          "system-imposed limit on the number of threads was encountered.");
      break;
    case EINVAL:
      daal::log::FrameworkLogger::get()->Error("EINVAL: Invalid settings in attr.");
      break;
    case EPERM:
      daal::log::FrameworkLogger::get()->Error(
          "EPERM: No permission to set the scheduling policy and "
          "parameters specified in attr.");
      break;
    default:
      daal::log::FrameworkLogger::get()->Error("Unknown error: {}", ret_pth);
      break;
  }

  if (ret_pth != 0) {
    daal::log::FrameworkLogger::get()->Error("Error in creating thread");
    std::abort();
  }

  // wait for the thread to be ready
  std::unique_lock<std::mutex> lock(mutex_);
  submit_condition_.wait(lock, [this] { return tasks_.empty(); });
}

WorkerThread::~WorkerThread() {
  {
    std::lock_guard<std::mutex> lock(mutex_);
    stop_flag_.store(true);
    condition_.notify_all();
    FulFillPromise(false);
  }
  int ret_join = pthread_join(worker_thread_, nullptr);
  if (ret_join != 0) {
    daal::log::FrameworkLogger::get()->Error("Joining thread: {}", strerror(ret_join));
  }
  int ret_destroy = pthread_attr_destroy(&thread_attr_);
  if (ret_destroy != 0) {
    daal::log::FrameworkLogger::get()->Error("Destroying thread attributes");
  }
}

void *WorkerThread::ThreadEntryFunction(void *arg) {
  auto *self = static_cast<WorkerThread *>(arg);
  bool ret = self->SetThreadAffinity(self->core_id_);
  if (!ret) {
    daal::log::FrameworkLogger::get()->Error("Failed to set thread affinity for core: {}", self->core_id_);
    std::abort();
  }
  self->Run();
  return nullptr;
}

std::future<bool> WorkerThread::Submit(std::function<bool()> task) {
  TaskList tasks;
  tasks.push(task);
  return Submit(tasks);
}

std::future<bool> WorkerThread::Submit(TaskList new_tasks) {
  if (new_tasks.empty()) {
    auto worker_promise = std::make_unique<std::promise<bool>>();
    std::future<bool> worker_future = worker_promise->get_future();
    worker_promise->set_value(false);
    return worker_future;
  }
  std::unique_lock<std::mutex> lock(mutex_);
  submit_condition_.wait(lock, [this] { return tasks_.empty(); });
  auto worker_promise = std::make_unique<std::promise<bool>>();
  std::future<bool> worker_future = worker_promise->get_future();
  while (!new_tasks.empty()) {
    tasks_.push(std::move(new_tasks.front()));
    new_tasks.pop();
  }
  worker_promise_ = std::move(worker_promise);
  condition_.notify_all();
  return worker_future;
}

std::future<bool> WorkerThread::TrySubmit(TaskList new_tasks) {
  std::unique_lock<std::mutex> lock(mutex_, std::try_to_lock);
  if (!lock.owns_lock() || tasks_.size() != 0) {
    auto worker_promise = std::make_unique<std::promise<bool>>();
    std::future<bool> worker_future = worker_promise->get_future();
    worker_promise->set_value(false);
    worker_promise = nullptr;
    return worker_future;
  } else {
    lock.unlock();
    return Submit(std::move(new_tasks));
  }
}

void WorkerThread::FulFillPromise(bool value) {
  if (nullptr != worker_promise_) {
    worker_promise_->set_value(value);
    worker_promise_ = nullptr;
  }
}

void WorkerThread::Run() {
  while (!stop_flag_.load()) {
    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(lock, [this] { return !tasks_.empty() || stop_flag_.load(); });

    if (stop_flag_.load()) {
      FulFillPromise(false);
      lock.unlock();
      return;
    }

    bool apps_success_ = true;
    while (!tasks_.empty()) {
      auto application_execution = tasks_.front();
      apps_success_ = application_execution() && apps_success_;
      tasks_.pop();
    }
    FulFillPromise(apps_success_);
    lock.unlock();
    submit_condition_.notify_all();
  }
}

}  // namespace worker

}  // namespace af

}  // namespace daal
