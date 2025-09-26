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

#include <unistd.h>

#include <ctime>

#include "daal/af/runtime_statistics/config/runtime_statistics_config.hpp"
#include "daal/af/runtime_statistics/time_provider.hpp"

namespace daal {
namespace af {
namespace runtime_statistics {

std::uint64_t TimeProvider::GetRealTime() noexcept {
  if (!kEnableCPUTimeMeasurement) {
    return 0;
  }

  timespec time{};
  clock_gettime(CLOCK_MONOTONIC, &time);
  return time.tv_sec * kMicrosecondsPerSecond + time.tv_nsec / kNanoSecondsPerMicrosecond;
}

std::uint64_t TimeProvider::GetCPUTime() noexcept {
  if (!kEnableRealTimeMeasurement) {
    return 0;
  }

  timespec time{};
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time);
  return time.tv_sec * kMicrosecondsPerSecond + time.tv_nsec / kNanoSecondsPerMicrosecond;
}

}  // namespace runtime_statistics
}  // namespace af
}  // namespace daal
