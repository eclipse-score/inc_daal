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

#include "console_backend.hpp"

#include <iomanip>
#include <iostream>

namespace daal {
namespace af {
namespace runtime_statistics {

void ConsoleBackend::Show(const RuntimeStatistics::Statistics& statistics) noexcept {
  std::cout << std::fixed << std::setprecision(0)  //
            << "{ "                                //
            << "\"NAME\""
            << " : "
            << "\"" << statistics.name.data() << "\""
            << ", "  //
            << "\"CYCLES\""
            << " : " << statistics.cycle_count << ", "  //
            << "\"DT_MIN\""
            << " : " << statistics.delta_time.minimum << ", "  //
            << "\"DT_MAX\""
            << " : " << statistics.delta_time.maximum << ", "  //
            << "\"DT_MEAN\""
            << " : " << statistics.delta_time.mean << ", "  //
            << "\"DT_STDDEV\""
            << " : " << statistics.delta_time.std_dev << ", "  //
            << "\"CET_MIN\""
            << " : " << statistics.core_execution_time.minimum << ", "  //
            << "\"CET_MAX\""
            << " : " << statistics.core_execution_time.maximum << ", "  //
            << "\"CET_MEAN\""
            << " : " << statistics.core_execution_time.mean << ", "  //
            << "\"CET_STDDEV\""
            << " : " << statistics.core_execution_time.std_dev << ", "  //
            << "\"GET_MIN\""
            << " : " << statistics.gross_execution_time.minimum << ", "  //
            << "\"GET_MAX\""
            << " : " << statistics.gross_execution_time.maximum << ", "  //
            << "\"GET_MEAN\""
            << " : " << statistics.gross_execution_time.mean << ", "  //
            << "\"GET_STDDEV\""
            << " : " << statistics.gross_execution_time.std_dev << " }\n";  //
}

}  // namespace runtime_statistics
}  // namespace af
}  // namespace daal
