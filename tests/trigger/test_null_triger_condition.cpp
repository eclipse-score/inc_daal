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

#include <gtest/gtest.h>

#include "daal/af/trigger/details/trigger_condition_impl.hpp"

TEST(NullTriggerConditionTest, IsTriggeredReturnsTrue) {
  daal::af::trigger::NullTriggerCondition trigger;
  EXPECT_TRUE(trigger.IsTriggered());
}

TEST(NullTriggerConditionTest, IsTriggeredReturnsTrueMultipleTimes) {
  daal::af::trigger::NullTriggerCondition trigger;
  for (int i = 0; i < 10; ++i) {
    EXPECT_TRUE(trigger.IsTriggered());
  }
}
