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

#include <pthread.h>
#include <sched.h>

#include "worker_thread.hpp"

namespace daal {

namespace af {

namespace worker {

void WorkerThread::InitializeThreadAttributes(int priority) {
  // Do nothing for Linux implementation
}

bool WorkerThread::SetThreadAffinity(unsigned int core_id) {
  // Set CPU affinity for the thread
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(core_id, &cpuset);
  auto ret = pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
  return !ret;
}

}  // namespace worker

}  // namespace af

}  // namespace daal
