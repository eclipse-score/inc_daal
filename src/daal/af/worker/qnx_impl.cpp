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

#include <sys/neutrino.h>

#include <cerrno>
#include <cstring>

#include "daal/log/framework_logger.hpp"
#include "worker_thread.hpp"

namespace daal {

namespace af {

namespace worker {

void WorkerThread::InitializeThreadAttributes(int priority) {
  int ret_init = pthread_attr_init(&thread_attr_);
  if (ret_init != 0) {
    daal::log::FrameworkLogger::get()->Error("Initializing thread attributes: {}", strerror(ret_init));
    std::abort();
  }

  // Get the scheduling policy and parameters of the parent thread
  int parent_policy;
  struct sched_param parent_sched_param;
  int ret_get = pthread_getschedparam(pthread_self(), &parent_policy, &parent_sched_param);
  if (ret_get != 0) {
    daal::log::FrameworkLogger::get()->Error("Getting parent thread scheduling parameters: {}", strerror(errno));
    std::abort();
  }

  // Set the scheduling policy for the new thread
  int ret_policy = pthread_attr_setschedpolicy(&thread_attr_, parent_policy);
  if (ret_policy != 0) {
    daal::log::FrameworkLogger::get()->Error("Setting thread scheduling policy: {}", strerror(errno));
    std::abort();
  }

  struct sched_param sched_param {};
  sched_param.sched_priority = priority;
  int ret_sched = pthread_attr_setschedparam(&thread_attr_, &sched_param);
  if (ret_sched != 0) {
    daal::log::FrameworkLogger::get()->Error("Setting thread scheduling parameters: {}", strerror(ret_sched));
    std::abort();
  }
}

bool WorkerThread::SetThreadAffinity(unsigned int core_id) {
  unsigned int run_mask = 1 << (core_id - 1);
  // this shall be called inside of the thread to be set
  auto ret = ThreadCtl(_NTO_TCTL_RUNMASK, reinterpret_cast<void *>(run_mask));
  return ret != -1;
}

}  // namespace worker

}  // namespace af

}  // namespace daal
