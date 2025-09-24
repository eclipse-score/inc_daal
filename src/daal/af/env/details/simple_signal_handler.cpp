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

#include "simple_signal_handler.hpp"

#include <atomic>
#include <csignal>
#include <cstdint>
#include <cstdlib>

#include "daal/log/framework_logger.hpp"

namespace daal {

namespace af {

namespace env {
SimpleSignalHandler::SimpleSignalHandler(std::atomic_bool &requested_exit, std::atomic_bool &signal_to_terminate)
    : exit_requested_(requested_exit), terminated_by_signal_(signal_to_terminate) {
  bool success{false};
  sigset_t signals;

  /* Block all signals except the SIGABRT, SIGBUS, SIGFPE, SIGILL, SIGSEGV
   * signals because blocking them will lead to undefined behavior. Their
   * default handling shall not be changed (dependent on underlying POSIX
   * environment, usually process is killed and a dump file is
   * written). Signal mask will be inherited by subsequent threads. */

  success = (EXIT_SUCCESS == sigfillset(&signals));
  success = success && (EXIT_SUCCESS == sigdelset(&signals, SIGABRT));
  success = success && (EXIT_SUCCESS == sigdelset(&signals, SIGBUS));
  success = success && (EXIT_SUCCESS == sigdelset(&signals, SIGFPE));
  success = success && (EXIT_SUCCESS == sigdelset(&signals, SIGILL));
  success = success && (EXIT_SUCCESS == sigdelset(&signals, SIGSEGV));
  success = success && (EXIT_SUCCESS == pthread_sigmask(SIG_SETMASK, &signals, nullptr));

  if (!success) {
    daal::log::FrameworkLogger::get()->Error("InitializeSignalHandling failed.");
    std::abort();
  }
}

void SimpleSignalHandler::operator()() {
  sigset_t signal_set;

  // initialize the signal set, such that all signals are excluded
  constexpr std::int32_t kSigEmptySetSuccess{0};
  if (kSigEmptySetSuccess != sigemptyset(&signal_set)) {
    daal::log::FrameworkLogger::get()->Error("Could not empty signal set.");
    std::abort();
  }

  // add SIGTERM to signal set
  constexpr std::int32_t kSigAddSetSuccess{0};
  if (kSigAddSetSuccess != sigaddset(&signal_set, SIGTERM)) {
    daal::log::FrameworkLogger::get()->Error("Cannot add signal to signalset: SIGTERM");
    std::abort();
  }

  // add SIGINT to signal set
  if (kSigAddSetSuccess != sigaddset(&signal_set, SIGINT)) {
    daal::log::FrameworkLogger::get()->Error("Cannot add signal to signalset: SIGINT");
    std::abort();
  }

  // loop until SIGTERM or SIGINT signal received
  // used in the sigwait() call
  std::int32_t sig{-1};
  exit_requested_.store(false);

  while (!exit_requested_.load()) {
    constexpr std::int32_t kSigWaitSuccess{0};
    if (kSigWaitSuccess != sigwait(&signal_set, &sig)) {
      daal::log::FrameworkLogger::get()->Error("Called sigwait() with invalid signalset");
      std::abort();
    }

    if ((sig == SIGTERM) || (sig == SIGINT)) {
      exit_requested_.store(true);
      terminated_by_signal_.store(true);
    }
  }
}
}  // namespace env

}  // namespace af

}  // namespace daal
