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

#include <cstdint>

#ifndef SRC_DAAL_AF_RUNTIME_STATISTICS_TIME_PROVIDER_HPP_
#define SRC_DAAL_AF_RUNTIME_STATISTICS_TIME_PROVIDER_HPP_

namespace daal {
namespace af {
namespace runtime_statistics {

/** Platform specific time provider interface. */
class TimeProvider {
 public:
  TimeProvider() = default;
  virtual ~TimeProvider() = default;

  /** Retrieve the current monotonic real time wall clock in microseconds. */
  virtual std::uint64_t GetRealTime() noexcept;

  /** Retrieve the current CPU clock in microseconds. */
  virtual std::uint64_t GetCPUTime() noexcept;

  static const std::uint64_t kMicrosecondsPerSecond{1000000};
  static const std::uint64_t kNanoSecondsPerMicrosecond{1000};
};

}  // namespace runtime_statistics
}  // namespace af
}  // namespace daal

#endif  // SRC_DAAL_AF_RUNTIME_STATISTICS_TIME_PROVIDER_HPP_
