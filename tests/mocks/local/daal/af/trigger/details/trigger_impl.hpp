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

#pragma once

#include <gmock/gmock.h>

#include <chrono>

#include "daal/af/trigger/trigger.hpp"

struct PeriodicTriggerMock {
  static PeriodicTriggerMock& instance() {
    static PeriodicTriggerMock mock;
    return mock;
  }
  MOCK_METHOD(void, ctor, (std::chrono::nanoseconds));
  MOCK_METHOD(bool, CheckTriggerConditionAndWait, ());
};

namespace daal {
namespace af {
namespace trigger {

struct PeriodicTrigger : public Trigger {
  PeriodicTrigger(std::chrono::nanoseconds period) {
    PeriodicTriggerMock::instance().ctor(period);
  }

  ~PeriodicTrigger() override = default;

  bool CheckTriggerConditionAndWait() override { return  PeriodicTriggerMock::instance().CheckTriggerConditionAndWait(); }


};

}  // namespace daal
}  // namespace af
}  // namespace trigger
