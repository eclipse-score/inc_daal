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

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>

#include "src/daal/af/trigger/details/trigger_impl.hpp"
#include "daal/af/trigger/details/trigger_condition_impl.hpp"
#include "daal/af/trigger/details/trigger_activation_impl.hpp"

using namespace std::chrono_literals;

class PeriodicTriggerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    fakeCondition =
        FakeObject<daal::af::trigger::NullTriggerConditionMock>::GetFakeObject();
    fakeActivation =
        FakeObject<daal::af::trigger::PeriodicActivationMock>::GetFakeObject();
  }

  void TearDown() override {
    FakeObject<daal::af::trigger::NullTriggerConditionMock>::RemoveFakeObject();
    FakeObject<daal::af::trigger::PeriodicActivationMock>::RemoveFakeObject();
  }

  std::shared_ptr<daal::af::trigger::NullTriggerConditionMock> fakeCondition;
  std::shared_ptr<daal::af::trigger::PeriodicActivationMock> fakeActivation;
  daal::af::trigger::PeriodicTrigger trigger{100ms};
};

TEST_F(PeriodicTriggerTest, CheckTriggerConditionAndWait_Triggered_Waits) {
  EXPECT_CALL(*fakeCondition, IsTriggered()).WillOnce(testing::Return(true));
  EXPECT_CALL(*fakeActivation, Wait()).Times(1);
  trigger.CheckTriggerConditionAndWait();
}

TEST_F(PeriodicTriggerTest,
       CheckTriggerConditionAndWait_NotTriggered_DoesNotWait) {
  EXPECT_CALL(*fakeCondition, IsTriggered()).WillOnce(testing::Return(false));
  EXPECT_CALL(*fakeActivation, Wait()).Times(0);
  trigger.CheckTriggerConditionAndWait();
}
