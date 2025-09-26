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

#include <gtest/gtest.h>
#include <pthread.h>

#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <chrono>

#include "src/daal/af/worker/worker_thread.hpp"

class WorkerThreadTest : public ::testing::Test {
 protected:
  void SetUp() override {
    core_id = 1;
    priority = 10;
    worker_thread = new daal::af::worker::WorkerThread(core_id, priority);
  }

  void TearDown() override { delete worker_thread; }

  unsigned int core_id;
  int priority;
  daal::af::worker::WorkerThread* worker_thread;
};

TEST_F(WorkerThreadTest, DestructorStopsThread) {
  delete worker_thread;
  worker_thread = nullptr;
  // Assuming there's a way to check if the thread has stopped
  // This might need to be adjusted based on the actual implementation
}

TEST_F(WorkerThreadTest, SubmitFailToAcceptsEmptyTaskList) {
  daal::af::worker::WorkerThread::TaskList tasks;
  auto future = worker_thread->Submit(tasks);
  EXPECT_FALSE(future.get());
}

TEST_F(WorkerThreadTest, SubmitAddsTasksToQueue) {
  daal::af::worker::WorkerThread::TaskList tasks;
  tasks.push([]() { return true; });
  auto future = worker_thread->Submit(tasks);
  EXPECT_TRUE(future.get());
}

TEST_F(WorkerThreadTest, SubmitMultipleTasks) {
  daal::af::worker::WorkerThread::TaskList tasks;
  tasks.push([]() { return true; });
  tasks.push([]() { return true; });
  auto future = worker_thread->Submit(tasks);
  EXPECT_TRUE(future.get());
}

TEST_F(WorkerThreadTest, SubmitTasksWithFailure) {
  daal::af::worker::WorkerThread::TaskList tasks;
  tasks.push([]() { return true; });
  tasks.push([]() { return false; });
  auto future = worker_thread->Submit(tasks);
  EXPECT_FALSE(future.get());
}

TEST_F(WorkerThreadTest, SubmitAndRunMultipleTimes) {
  for (int i = 0; i < 5; ++i) {
    daal::af::worker::WorkerThread::TaskList tasks;
    tasks.push([]() { return true; });
    auto future = worker_thread->Submit(tasks);
    EXPECT_TRUE(future.get());
  }
}

TEST_F(WorkerThreadTest, SubmitWithDelayedTask) {
  daal::af::worker::WorkerThread::TaskList tasks;
  tasks.push([]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return true;
  });
  auto future = worker_thread->Submit(tasks);
  auto future2 = worker_thread->Submit(tasks);
  EXPECT_TRUE(future.get());
  EXPECT_TRUE(future2.get());
}

TEST_F(WorkerThreadTest, SubmitWithMultiplePromises) {
  daal::af::worker::WorkerThread::TaskList tasks1;
  tasks1.push([]() { return true; });
  auto future1 = worker_thread->Submit(tasks1);

  daal::af::worker::WorkerThread::TaskList tasks2;
  tasks2.push([]() { return true; });
  auto future2 = worker_thread->Submit(tasks2);

  EXPECT_EQ(future1.get(), true);
  EXPECT_EQ(future2.get(), true);
}

TEST_F(WorkerThreadTest, SubmitSingleTask) {
  auto future = worker_thread->Submit([]() { return true; });
  EXPECT_TRUE(future.get());
}

TEST_F(WorkerThreadTest, SubmitSingleTaskWithFailure) {
  auto future = worker_thread->Submit([]() { return false; });
  EXPECT_FALSE(future.get());
}

TEST_F(WorkerThreadTest, SubmitSingleTaskWithDelay) {
  auto future = worker_thread->Submit([]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return true;
  });
  EXPECT_TRUE(future.get());
}

TEST_F(WorkerThreadTest, TrySubmitAcceptsEmptyTaskList) {
  daal::af::worker::WorkerThread::TaskList tasks;
  auto future = worker_thread->TrySubmit(tasks);
  EXPECT_FALSE(future.get());
}

TEST_F(WorkerThreadTest, TrySubmitAddsTasksToQueueImmediately) {
  daal::af::worker::WorkerThread::TaskList tasks;
  tasks.push([]() { return true; });
  auto future = worker_thread->TrySubmit(tasks);
  EXPECT_TRUE(future.get());
}

TEST_F(WorkerThreadTest, TrySubmitFailsIfTasksAlreadyPresent) {
  daal::af::worker::WorkerThread::TaskList tasks1;
  tasks1.push([]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return true;
  });
  daal::af::worker::WorkerThread::TaskList tasks2;
  tasks2.push([]() { return true; });
  auto future1 = worker_thread->Submit(tasks1);
  auto future2 = worker_thread->TrySubmit(tasks2);
  EXPECT_EQ(future1.get(), true);
  EXPECT_EQ(future2.get(), false);
}

TEST_F(WorkerThreadTest, TrySubmitTasks) {
  daal::af::worker::WorkerThread::TaskList tasks;
  tasks.push([]() { return true; });
  auto future = worker_thread->TrySubmit(tasks);
  EXPECT_TRUE(future.get());
}

TEST_F(WorkerThreadTest, TrySubmitMultipleTasks) {
  daal::af::worker::WorkerThread::TaskList tasks;
  tasks.push([]() { return true; });
  tasks.push([]() { return true; });
  auto future = worker_thread->TrySubmit(tasks);
  EXPECT_TRUE(future.get());
}

TEST_F(WorkerThreadTest, TrySubmitProcessesTasksWithFailure) {
  daal::af::worker::WorkerThread::TaskList tasks;
  tasks.push([]() { return true; });
  tasks.push([]() { return false; });
  auto future = worker_thread->TrySubmit(tasks);
  EXPECT_FALSE(future.get());
}

TEST_F(WorkerThreadTest, TrySubmitAndRunMultipleTimes) {
  daal::af::worker::WorkerThread::TaskList tasks;
  tasks.push([]() { return true; });
  auto future = worker_thread->TrySubmit(tasks);
  // wait for the future to be ready

  EXPECT_TRUE(future.valid());
  EXPECT_TRUE(future.get());
}

TEST_F(WorkerThreadTest, TrySubmitWithDelayedTask) {
  daal::af::worker::WorkerThread::TaskList tasks;
  tasks.push([]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return true;
  });
  auto future = worker_thread->TrySubmit(tasks);
  EXPECT_TRUE(future.get());
}

TEST_F(WorkerThreadTest, TrySubmitWithMultiplePromises) {
  daal::af::worker::WorkerThread::TaskList tasks;
  tasks.push([]() {
    std::cerr << "Task 1" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cerr << "Task 1 done" << std::endl;
    return true;
  });
  auto future1 = worker_thread->TrySubmit(tasks);
  auto future2 = worker_thread->TrySubmit(tasks);

  EXPECT_EQ(future1.get(), true);
  EXPECT_EQ(future2.get(), false);
}