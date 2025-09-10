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

#include "fork_join_module_handler.hpp"

#include <cstdlib>
#include <future>

#include "daal/log/framework_logger.hpp"

namespace daal {

namespace af {

namespace app_handler {

ForkJoinModuleHandler::ForkJoinModuleHandler(unsigned int core_id, int priority, ForkMap fork_map)
    : IApplicationHandler(),
      fork_map_(std::move(fork_map)),
      worker_thread_{core_id, priority} {}

bool ForkJoinModuleHandler::Initialize() {
  bool success = true;
  for (auto &pair : fork_map_) {
    for (auto &phases : pair.second) {
      success = phases.second->Initialize() && success;
    }
  }
  return success;
}

bool ForkJoinModuleHandler::PrepareForExecute() {
  bool success = true;
  for (auto &pair : fork_map_) {
    for (auto &phases : pair.second) {
      success = phases.second->PrepareForExecute() && success;
    }
  }
  return success;
}

bool ForkJoinModuleHandler::Execute() {
  bool main_thread_success = true;
  bool worker_thread_success = false;
  // stage loop
  for (auto &pair : fork_map_) {
    auto &phase_configs = pair.second;

    // Prepare the tasks for the main and worker threads
    daal::af::worker::WorkerThread::TaskList main_t_tasks;
    daal::af::worker::WorkerThread::TaskList worker_t_tasks;
    // phase loop, assign the tasks to the main and worker threads
    for (auto &phase_config : phase_configs) {
      auto &thread_affinity = phase_config.first;
      auto &application = phase_config.second;
      auto lambda_func = [application]() -> bool { return application->Execute(); };
      if (thread_affinity == TaskAffinity::MAIN) {
        main_t_tasks.push(lambda_func);
      } else if (thread_affinity == TaskAffinity::WORKER) {
        worker_t_tasks.push(lambda_func);
      } else {
        daal::log::FrameworkLogger::get()->Error("Invalid thread affinity");
        exit(42);
      }
    }

    ///////////////////////// Fork Worker Thread///////////////////////////////
    daal::log::FrameworkLogger::get()->Error("Worker thread load {}", worker_t_tasks.size());
    std::future<bool> worker_future = worker_thread_.Submit(worker_t_tasks);
    /////////////////////////////////////////////////////////////////////

    /////////////////////////Main Thread/////////////////////////////////
    while (!main_t_tasks.empty()) {
      auto &application_execution = main_t_tasks.front();
      main_thread_success = application_execution() && main_thread_success;
      main_t_tasks.pop();
    }
    ////////////////////////////////////////////////////////////////////

    //////// Join Worker Thread ////////////////////////////////////////
    daal::log::FrameworkLogger::get()->Error("Waiting for worker thread");
    if (worker_future.valid()) {
      worker_thread_success = worker_future.get();
    } else {
      // This is a catastrofic failuer as given future is not valid
      daal::log::FrameworkLogger::get()->Error("Invalid future!");
      exit(-1);
    }
    daal::log::FrameworkLogger::get()->Error("Waiting for worker thread done");
    ////////////////////////////////////////////////////////////////////
  }
  bool final_result{worker_thread_success && main_thread_success};
  return final_result;
}

bool ForkJoinModuleHandler::PrepareForShutdown() {
  bool success = true;
  for (auto &pair : fork_map_) {
    for (auto &phases : pair.second) {
      success = phases.second->PrepareForShutdown() && success;
    }
  }
  return success;
}

bool ForkJoinModuleHandler::Shutdown() {
  bool success = true;
  for (auto &pair : fork_map_) {
    for (auto &phases : pair.second) {
      success = phases.second->Shutdown() && success;
    }
  }
  return success;
}

}  // namespace app_handler

}  // namespace af

}  // namespace daal
