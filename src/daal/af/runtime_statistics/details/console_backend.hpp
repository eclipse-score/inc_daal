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

#include "daal/af/runtime_statistics/reporting_backend.hpp"

#ifndef SRC_DAAL_AF_RUNTIME_STATISTICS_DETAILS_CONSOLE_BACKEND_HPP_
#define SRC_DAAL_AF_RUNTIME_STATISTICS_DETAILS_CONSOLE_BACKEND_HPP_

namespace daal {
namespace af {
namespace runtime_statistics {

/** Backend that prints a JSON of the statistics to the console. */
class ConsoleBackend : public IReportingBackend {
 public:
  ConsoleBackend() = default;
  ~ConsoleBackend() override = default;

  /** Report the given statistics to the backend. */
  void Show(const RuntimeStatistics::Statistics& statistics) noexcept override;
};

}  // namespace runtime_statistics
}  // namespace af
}  // namespace daal

#endif  // SRC_DAAL_AF_RUNTIME_STATISTICS_DETAILS_CONSOLE_BACKEND_HPP_
