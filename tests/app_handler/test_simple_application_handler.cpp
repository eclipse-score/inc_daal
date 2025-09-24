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

#include "daal/af/app_handler/details/single_shot_app_handler.hpp"

using namespace daal::af::app_handler;
using ::testing::NiceMock;
using ::testing::Return;

class MockSafeApplication : public daal::af::app_base::SafeApplicationBase {
 public:
  MOCK_METHOD(daal::af::app_base::MethodState, OnInitialize, (), (override));
  MOCK_METHOD(daal::af::app_base::MethodState, OnStart, (), (override));
  MOCK_METHOD(daal::af::app_base::MethodState, Step, (), (override));
  MOCK_METHOD(daal::af::app_base::MethodState, OnStop, (), (override));
  MOCK_METHOD(daal::af::app_base::MethodState, OnTerminate, (), (override));
};

TEST(SingleShotAppHandlerTest, Initialize) {
  auto mockApplication = std::make_shared<NiceMock<MockSafeApplication>>();
  SingleShotAppHandler handler(mockApplication);

  EXPECT_CALL(*mockApplication, OnInitialize())
      .WillOnce(Return(daal::af::app_base::MethodState::kSuccessful));

  bool result = handler.Initialize();

  EXPECT_TRUE(result);
}

TEST(SingleShotAppHandlerTest, PrepareForExecute) {
 auto mockApplication = std::make_shared<NiceMock<MockSafeApplication>>();
  SingleShotAppHandler handler(mockApplication);

  EXPECT_CALL(*mockApplication, OnStart)
      .WillOnce(Return(daal::af::app_base::MethodState::kSuccessful));

  bool result = handler.PrepareForExecute();

  EXPECT_TRUE(result);
}

TEST(SingleShotAppHandlerTest, Execute) {
 auto mockApplication = std::make_shared<NiceMock<MockSafeApplication>>();
  SingleShotAppHandler handler(mockApplication);

  EXPECT_CALL(*mockApplication, Step())
      .WillOnce(Return(daal::af::app_base::MethodState::kSuccessful));

  bool result = handler.Execute();

  EXPECT_TRUE(result);
}

TEST(SingleShotAppHandlerTest, PrepareForShutdown) {
 auto mockApplication = std::make_shared<NiceMock<MockSafeApplication>>();
  SingleShotAppHandler handler(mockApplication);

  EXPECT_CALL(*mockApplication, OnStop())
      .WillOnce(Return(daal::af::app_base::MethodState::kSuccessful));

  bool result = handler.PrepareForShutdown();

  EXPECT_TRUE(result);
}

TEST(SingleShotAppHandlerTest, Shutdown) {
 auto mockApplication = std::make_shared<NiceMock<MockSafeApplication>>();
  SingleShotAppHandler handler(mockApplication);

  EXPECT_CALL(*mockApplication, OnTerminate())
      .WillOnce(Return(daal::af::app_base::MethodState::kSuccessful));

  bool result = handler.Shutdown();

  EXPECT_TRUE(result);
}

TEST(SingleShotAppHandlerTest, Initialize_fail) {
 auto mockApplication = std::make_shared<NiceMock<MockSafeApplication>>();
  SingleShotAppHandler handler(mockApplication);

  EXPECT_CALL(*mockApplication, OnInitialize())
      .WillOnce(Return(daal::af::app_base::MethodState::kFailed));

  bool result = handler.Initialize();

  EXPECT_FALSE(result);
}

TEST(SingleShotAppHandlerTest, PrepareForExecute_fail) {
 auto mockApplication = std::make_shared<NiceMock<MockSafeApplication>>();
  SingleShotAppHandler handler(mockApplication);

  EXPECT_CALL(*mockApplication, OnStart)
      .WillOnce(Return(daal::af::app_base::MethodState::kOnGoing));

  bool result = handler.PrepareForExecute();

  EXPECT_FALSE(result);
}

TEST(SingleShotAppHandlerTest, Execute_fail) {
 auto mockApplication = std::make_shared<NiceMock<MockSafeApplication>>();
  SingleShotAppHandler handler(mockApplication);

  EXPECT_CALL(*mockApplication, Step())
      .WillOnce(Return(daal::af::app_base::MethodState::kFailed));

  bool result = handler.Execute();

  EXPECT_FALSE(result);
}

TEST(SingleShotAppHandlerTest, PrepareForShutdown_fail) {
 auto mockApplication = std::make_shared<NiceMock<MockSafeApplication>>();
  SingleShotAppHandler handler(mockApplication);

  EXPECT_CALL(*mockApplication, OnStop())
      .WillOnce(Return(daal::af::app_base::MethodState::kOnGoing));

  bool result = handler.PrepareForShutdown();

  EXPECT_FALSE(result);
}

TEST(SingleShotAppHandlerTest, Shutdown_fail) {
 auto mockApplication = std::make_shared<NiceMock<MockSafeApplication>>();
  SingleShotAppHandler handler(mockApplication);

  EXPECT_CALL(*mockApplication, OnTerminate())
      .WillOnce(Return(daal::af::app_base::MethodState::kFailed));

  bool result = handler.Shutdown();

  EXPECT_FALSE(result);
}
