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

#include "daal/af/app_base/safe_application_base.hpp"
#include "daal/af/app_handler/details/iterative_application_handler.hpp"

// Mock class for daal::af::app_base::SafeApplicationBase
class MockSafeApplicationBase : public daal::af::app_base::SafeApplicationBase {
 public:
  MOCK_METHOD(daal::af::app_base::MethodState, OnInitialize, (), (override));
  MOCK_METHOD(daal::af::app_base::MethodState, OnStart, (), (override));
  MOCK_METHOD(daal::af::app_base::MethodState, Step, (), (override));
  MOCK_METHOD(daal::af::app_base::MethodState, OnStop, (), (override));
  MOCK_METHOD(daal::af::app_base::MethodState, OnTerminate, (), (override));
};

class DummyTrigger : public daal::af::trigger::Trigger {
 public:
  MOCK_METHOD(bool, CheckTriggerConditionAndWait, (), (override));
};

// Test fixture for IterativeApplicationHandler tests
class IterativeApplicationHandlerTest : public ::testing::Test {
 protected:
  MockSafeApplicationBase app;
  daal::af::app_handler::PhaseAttempts attempts_{
      daal::af::app_handler::Attempts(3),  // initialize_attempts
      daal::af::app_handler::Attempts(2),  // prepare_for_execute_attempts
      daal::af::app_handler::Attempts(1),  // prepare_for_shutdown_attempts
      daal::af::app_handler::Attempts(0)   // shutdown_attempts
  };

  DummyTrigger trigger_;

  daal::af::app_handler::IterativeApplicationHandler handler{app, trigger_, attempts_};

  void SetUp() override {}

  void TearDown() override {}
};

// Test case for Initialize() method
TEST_F(IterativeApplicationHandlerTest, Initialize_fail) {
  EXPECT_CALL(trigger_, CheckTriggerConditionAndWait())
      .Times(2)
      .WillRepeatedly(testing::Return(true));
  EXPECT_CALL(app, OnInitialize())
      .Times(2)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kOnGoing))
      .WillRepeatedly(testing::Return(daal::af::app_base::MethodState::kFailed));

  EXPECT_FALSE(handler.Initialize());
}

// Test case for Initialize() method with trigger fail
TEST_F(IterativeApplicationHandlerTest, Initialize_fail_trigger) {
  EXPECT_CALL(trigger_, CheckTriggerConditionAndWait())
      .Times(3)
      .WillOnce(testing::Return(false))
      .WillRepeatedly(testing::Return(true));
  EXPECT_CALL(app, OnInitialize())
      .Times(2)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kOnGoing))
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kFailed));

  EXPECT_FALSE(handler.Initialize());
}

// Test case for PrepareForExecute() method
TEST_F(IterativeApplicationHandlerTest, PrepareForExecute_fail) {
  EXPECT_CALL(trigger_, CheckTriggerConditionAndWait())
      .Times(2)
      .WillRepeatedly(testing::Return(true));
  EXPECT_CALL(app, OnStart())
      .Times(2)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kOnGoing))
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kFailed));

  EXPECT_FALSE(handler.PrepareForExecute());
}

// Test case for Execute() method
TEST_F(IterativeApplicationHandlerTest, Execute_fail) {
  EXPECT_CALL(app, Step())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kFailed));

  EXPECT_FALSE(handler.Execute());
}

// Test case for PrepareForShutdown() method
TEST_F(IterativeApplicationHandlerTest, PrepareForShutdown_fail) {
  EXPECT_CALL(trigger_, CheckTriggerConditionAndWait())
      .Times(1)
      .WillRepeatedly(testing::Return(true));
  EXPECT_CALL(app, OnStop())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kFailed));

  EXPECT_FALSE(handler.PrepareForShutdown());
}

// Test case for successful initialization
TEST_F(IterativeApplicationHandlerTest, Initialize_Success) {
  EXPECT_CALL(trigger_, CheckTriggerConditionAndWait())
      .Times(1)
      .WillRepeatedly(testing::Return(true));
  EXPECT_CALL(app, OnInitialize())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));

  EXPECT_TRUE(handler.Initialize());
}

// Test case for successful preparation for execution
TEST_F(IterativeApplicationHandlerTest, PrepareForExecute_Success) {
  EXPECT_CALL(trigger_, CheckTriggerConditionAndWait())
      .Times(2)
      .WillRepeatedly(testing::Return(true));
  EXPECT_CALL(app, OnStart())
      .Times(2)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kOnGoing))
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));

  EXPECT_TRUE(handler.PrepareForExecute());
}

TEST_F(IterativeApplicationHandlerTest, PrepareForExecute_fail_state) {
  EXPECT_CALL(trigger_, CheckTriggerConditionAndWait())
      .Times(1)
      .WillRepeatedly(testing::Return(true));
  EXPECT_CALL(app, OnStart())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kFailed));

  EXPECT_FALSE(handler.PrepareForExecute());
}

// Test case for successful execution
TEST_F(IterativeApplicationHandlerTest, Execute_Success) {
  EXPECT_CALL(app, Step())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));
  EXPECT_TRUE(handler.Execute());
}

// Test case for successful preparation for shutdown
TEST_F(IterativeApplicationHandlerTest, PrepareForShutdown_Success) {
  EXPECT_CALL(trigger_, CheckTriggerConditionAndWait())
      .Times(1)
      .WillRepeatedly(testing::Return(true));
  EXPECT_CALL(app, OnStop())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));

  EXPECT_TRUE(handler.PrepareForShutdown());
}

// Test case for successful shutdown
TEST_F(IterativeApplicationHandlerTest, Shutdown_Success) {
  EXPECT_CALL(trigger_, CheckTriggerConditionAndWait()).Times(0);
  EXPECT_CALL(app, OnTerminate()).Times(0);

  EXPECT_FALSE(handler.Shutdown());
}

// Test case for IsMaxAttemptsReached() method
TEST(AttemptsTest, IsMaxAttemptsReached) {
  daal::af::app_handler::Attempts attempts(3);
  ++attempts;  // current_attempt_ = 1
  ++attempts;  // current_attempt_ = 2
  ++attempts;  // current_attempt_ = 3

  EXPECT_TRUE(attempts.IsMaxAttemptsReached());
}

// Test case for operator++() method
TEST(AttemptsTest, OperatorIncrement) {
  daal::af::app_handler::Attempts attempts(3);
  ++attempts;  // current_attempt_ = 1
  ++attempts;  // current_attempt_ = 2

  EXPECT_FALSE(attempts.IsMaxAttemptsReached());
}
