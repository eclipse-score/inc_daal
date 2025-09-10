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

#ifndef DAAL__SRC_ENVIRONMENT_DETAILS_DUMMY_EXEC_ENV_HPP
#define DAAL__SRC_ENVIRONMENT_DETAILS_DUMMY_EXEC_ENV_HPP

#include <atomic>
#include <thread>

#include "daal/af/env/details/simple_signal_handler.hpp"
#include "daal/af/env/execution_environment.hpp"
#include "daal/log/framework_logger.hpp"

/*!
 * \class DummyExecutionEnvironment
 * \brief A dummy implementation of the ExecutionEnvironment interface.
 *
 * This class provides a basic implementation of the ExecutionEnvironment
 * interface, primarily for testing or placeholder purposes. It includes
 * methods for initialization, deinitialization, state setting, and signal
 * handling.
 *
 * \details
 * The DummyExecutionEnvironment class is designed to handle signals and manage
 * the state of the execution environment. It blocks all signals except for
 * SIGABRT, SIGBUS, SIGFPE, SIGILL, and SIGSEGV, as blocking these signals can
 * lead to undefined behavior. The signal mask is inherited by subsequent
 * threads.
 *
 * \note
 * This class is not intended for production use and should be replaced with a
 * more robust implementation for actual deployment.
 */
namespace daal {

namespace af {

namespace env {

/*!
 * \brief
 *
 */
class DummyExecutionEnvironment : public ExecutionEnvironment {
 public:
  DummyExecutionEnvironment() {}
  ~DummyExecutionEnvironment() override {
    bool ret = Deinit();
    if (!ret) {
      daal::log::FrameworkLogger::get()->Error("Failed to de-initialize the Execution environment");
    }
  }

  bool Init() override {
    signal_handler_thread_ = std::thread(SimpleSignalHandler{exit_requested_, terminated_by_signal_});
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
};

}  // namespace env

}  // namespace af

}  // namespace daal

#endif  // DAAL__SRC_ENVIRONMENT_DETAILS_DUMMY_EXEC_ENV_HPP
