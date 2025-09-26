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

#include "trigger_impl.hpp"

namespace daal {

namespace af {
namespace trigger {

SimpleTrigger::SimpleTrigger(TriggerActivation &trigger_activation, TriggerCondition &trigger_condition) noexcept
    : Trigger(), trigger_activation_{trigger_activation}, trigger_condition_{trigger_condition} {}

bool SimpleTrigger::CheckTriggerConditionAndWait() {
  if (trigger_condition_.IsTriggered()) {
    (void)trigger_activation_.Wait();
    return true;
  }

  return false;
}

PeriodicTrigger::PeriodicTrigger(std::chrono::nanoseconds period)
    : SimpleTrigger(activation_, condition_), activation_{period}, condition_{} {}

}  // namespace trigger

}  // namespace af

}  // namespace daal
