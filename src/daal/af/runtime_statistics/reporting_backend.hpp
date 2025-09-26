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

#ifndef SRC_DAAL_AF_RUNTIME_STATISTICS_REPORTING_BACKEND_HPP_
#define SRC_DAAL_AF_RUNTIME_STATISTICS_REPORTING_BACKEND_HPP_

#include "runtime_statistics.hpp"

namespace daal {
namespace af {
namespace runtime_statistics {

/** Reporting backend interface. */
class IReportingBackend {
 public:
  IReportingBackend() = default;
  virtual ~IReportingBackend() = default;

  /** Report the given statistics to the backend. */
  virtual void Show(const RuntimeStatistics::Statistics& statistics) noexcept = 0;
};

}  // namespace runtime_statistics
}  // namespace af
}  // namespace daal

#endif  // SRC_DAAL_AF_RUNTIME_STATISTICS_REPORTING_BACKEND_HPP_
