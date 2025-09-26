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

#include "iterative_application_handler.hpp"

#include "daal/af/app_base/safe_application_base.hpp"
#include "daal/af/trigger/trigger.hpp"

namespace daal {

namespace af {

namespace app_handler {

bool Attempts::IsMaxAttemptsReached() const noexcept { return current_attempt_ >= max_attempts_; }

Attempts &Attempts::operator++() noexcept {
  ++current_attempt_;
  return *this;
}

bool IterativeApplicationHandler::RunPhase(Attempts &attempt_current,
                                           std::function<daal::af::app_base::MethodState()> &phase) {
  for (Attempts &attempts = attempt_current; !attempts.IsMaxAttemptsReached(); ++attempts) {
    bool result = trigger_.CheckTriggerConditionAndWait();
    if (result) {
      daal::af::app_base::MethodState state = phase();
      switch (state) {
        case daal::af::app_base::MethodState::kSuccessful:
          return true;
          break;
        case daal::af::app_base::MethodState::kFailed:
          return false;
          break;
        case daal::af::app_base::MethodState::kOnGoing:
          continue;
        default:
          return false;
      }
    }
  }
  return false;
}

IterativeApplicationHandler::IterativeApplicationHandler(daal::af::app_base::SafeApplicationBase &application,
                                                         daal::af::trigger::Trigger &trigger,
                                                         PhaseAttempts attempts) noexcept
    : IApplicationHandler(), application_{application}, trigger_{trigger}, phase_attempts_{attempts} {}

bool IterativeApplicationHandler::Initialize() {
  std::function<daal::af::app_base::MethodState()> initialize = [this]() { return application_.OnInitialize(); };
  return RunPhase(phase_attempts_.initialize_attempts, initialize);
}

bool IterativeApplicationHandler::PrepareForExecute() {
  std::function<daal::af::app_base::MethodState()> power_on = [this]() { return application_.OnStart(); };
  return RunPhase(phase_attempts_.prepare_for_execute_attempts, power_on);
}

bool IterativeApplicationHandler::Execute() {
  daal::af::app_base::MethodState state = application_.Step();
  return (state == daal::af::app_base::MethodState::kSuccessful || state == daal::af::app_base::MethodState::kOnGoing);
}

bool IterativeApplicationHandler::PrepareForShutdown() {
  std::function<daal::af::app_base::MethodState()> power_off = [this]() { return application_.OnStop(); };
  return RunPhase(phase_attempts_.prepare_for_shutdown_attempts, power_off);
}

bool IterativeApplicationHandler::Shutdown() {
  std::function<daal::af::app_base::MethodState()> terminate = [this]() { return application_.OnTerminate(); };
  return RunPhase(phase_attempts_.shutdown_attempts, terminate);
}

}  // namespace app_handler

}  // namespace af

}  // namespace daal
