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

#include "file_backend.hpp"

#include <unistd.h>

#include <fstream>
#include <iomanip>

#include "platform.hpp"

namespace daal {
namespace af {
namespace runtime_statistics {

void FileBackend::Show(const RuntimeStatistics::Statistics& statistics) noexcept {
  if (Platform::isFileBackendEnabled()) {
    static const pid_t kPid{getpid()};
    static const pid_t kTid{gettid()};
    std::ofstream out{};
    std::string path;

    path += Platform::getFilePath();
    path += "rt_stats_pid_";
    path += std::to_string(kPid);
    path += "_tid_";
    path += std::to_string(kTid);
    if (!statistics.name.empty()) {
      path += "_" + statistics.name;
    }
    path += ".json";

    out.open(path, std::ofstream::trunc);

    if (out.good()) {
      out << std::fixed << std::setprecision(0)  //
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
      out.close();
    }
  }
}

}  // namespace runtime_statistics
}  // namespace af
}  // namespace daal
