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

#ifndef EXAMPLES_DAAL_AF_SCORE_SCORE_ENVIRONMENT_HPP
#define EXAMPLES_DAAL_AF_SCORE_SCORE_ENVIRONMENT_HPP

#include <atomic>
#include <thread>

// DAAL dependencies
#include "daal/af/env/details/simple_signal_handler.hpp"
#include "daal/af/env/execution_environment.hpp"
#include "daal/log/framework_logger.hpp"

// SCORE dependencies
#include "mw_com_common.hpp"
#include "mw_log_common.hpp"
#include "score/mw/com/runtime.h"
#include "score/mw/com/types.h"
#include "score/mw/log/logging.h"

namespace daal {
namespace af {
namespace score {

class ScoreExecutionEnvironment : public daal::af::env::ExecutionEnvironment {
 public:
  ScoreExecutionEnvironment(const std::string service_instance_manifest_path)
      : recorder_(configure_console_logging(::score::mw::log::LogLevel::kVerbose)),
        service_instance_manifest_path_{service_instance_manifest_path} {
    // init the SCORE mw::log recorder
    if (!recorder_) {
      std::cerr << "Failed to create log recorder." << std::endl;
      return false;
    }
    ::score::mw::log::SetLogRecorder(recorder_.get());
  }
  ~ScoreExecutionEnvironment() override {
    bool ret = Deinit();
    if (!ret) {
      daal::log::FrameworkLogger::get()->Error("Failed to de-initialize the Execution environment");
    }
  }

  bool Init() override {
    // init the SCORE mw::com runtime
    ::score::StringLiteral runtime_args[2u] = {"-service_instance_manifest", service_instance_manifest_path_.c_str()};
    ::score::mw::com::runtime::InitializeRuntime(2, runtime_args);

    // init signal handler
    signal_handler_thread_ = std::thread(daal::af::env::SimpleSignalHandler{exit_requested_, terminated_by_signal_});
    return signal_handler_thread_.joinable();
  }
  bool Deinit() override {
    if (signal_handler_thread_.joinable()) {
      signal_handler_thread_.join();
    }

    return true;
  }

  void SetState(const State state) noexcept override {
    // do nothing
  }

  bool IsSigTerm() const noexcept override { return exit_requested_.load(); }

  bool Refresh() const noexcept override { return true; }

 private:
  std::atomic_bool exit_requested_;
  std::atomic_bool terminated_by_signal_;
  std::thread signal_handler_thread_;
  std::unique_ptr<::score::mw::log::Recorder> recorder_;
  std::string service_instance_manifest_path_;
};

}  // namespace score
}  // namespace af
}  // namespace daal

#endif  // EXAMPLES_DAAL_AF_SCORE_SCORE_ENVIRONMENT_HPP
