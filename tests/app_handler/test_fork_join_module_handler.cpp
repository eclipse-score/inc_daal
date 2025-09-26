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

#include "app_handler/details/fork_join_module_handler.hpp"

using namespace daal::af::app_handler;
using ::testing::NiceMock;
using ::testing::Return;

class MockApplicationModule : public IApplicationHandler {
 public:
  MOCK_METHOD(bool, Initialize, (), (override));
  MOCK_METHOD(bool, PrepareForExecute, (), (override));
  MOCK_METHOD(bool, Execute, (), (override));
  MOCK_METHOD(bool, PrepareForShutdown, (), (override));
  MOCK_METHOD(bool, Shutdown, (), (override));
};

class ForkJoinModuleHandlerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_module_main = std::make_shared<NiceMock<MockApplicationModule>>();
    mock_module_worker = std::make_shared<NiceMock<MockApplicationModule>>();

    fork_map = {
        {ForkJoinModuleHandler::Stage::STAGE1,
         {{ForkJoinModuleHandler::TaskAffinity::MAIN, mock_module_main}}},
        {ForkJoinModuleHandler::Stage::STAGE2,
         {{ForkJoinModuleHandler::TaskAffinity::WORKER, mock_module_worker}}}};

    handler = std::make_unique<ForkJoinModuleHandler>(0, 0, fork_map);
  }

  std::shared_ptr<NiceMock<MockApplicationModule>> mock_module_main;
  std::shared_ptr<NiceMock<MockApplicationModule>> mock_module_worker;
  ForkJoinModuleHandler::ForkMap fork_map;
  std::unique_ptr<ForkJoinModuleHandler> handler;
};

TEST_F(ForkJoinModuleHandlerTest, InitializeSuccess) {
  EXPECT_CALL(*mock_module_main, Initialize()).WillOnce(Return(true));
  EXPECT_CALL(*mock_module_worker, Initialize()).WillOnce(Return(true));

  EXPECT_TRUE(handler->Initialize());
}

TEST_F(ForkJoinModuleHandlerTest, InitializeFailure) {
  EXPECT_CALL(*mock_module_main, Initialize()).WillOnce(Return(false));
  EXPECT_CALL(*mock_module_worker, Initialize()).WillOnce(Return(true));

  EXPECT_FALSE(handler->Initialize());
}

TEST_F(ForkJoinModuleHandlerTest, PrepareForExecuteSuccess) {
  EXPECT_CALL(*mock_module_main, PrepareForExecute()).WillOnce(Return(true));
  EXPECT_CALL(*mock_module_worker, PrepareForExecute()).WillOnce(Return(true));

  EXPECT_TRUE(handler->PrepareForExecute());
}

TEST_F(ForkJoinModuleHandlerTest, PrepareForExecuteFailure) {
  EXPECT_CALL(*mock_module_main, PrepareForExecute()).WillOnce(Return(false));
  EXPECT_CALL(*mock_module_worker, PrepareForExecute()).WillOnce(Return(true));

  EXPECT_FALSE(handler->PrepareForExecute());
}

TEST_F(ForkJoinModuleHandlerTest, ExecuteSuccess) {
  EXPECT_CALL(*mock_module_main, Execute()).WillOnce(Return(true));
  EXPECT_CALL(*mock_module_worker, Execute()).WillOnce(Return(true));

  EXPECT_TRUE(handler->Execute());
}

TEST_F(ForkJoinModuleHandlerTest, ExecuteFailure) {
  EXPECT_CALL(*mock_module_main, Execute()).WillOnce(Return(false));
  EXPECT_CALL(*mock_module_worker, Execute()).WillOnce(Return(true));

  EXPECT_FALSE(handler->Execute());
}

TEST_F(ForkJoinModuleHandlerTest, PrepareForShutdownSuccess) {
  EXPECT_CALL(*mock_module_main, PrepareForShutdown()).WillOnce(Return(true));
  EXPECT_CALL(*mock_module_worker, PrepareForShutdown()).WillOnce(Return(true));

  EXPECT_TRUE(handler->PrepareForShutdown());
}

TEST_F(ForkJoinModuleHandlerTest, PrepareForShutdownFailure) {
  EXPECT_CALL(*mock_module_main, PrepareForShutdown()).WillOnce(Return(false));
  EXPECT_CALL(*mock_module_worker, PrepareForShutdown()).WillOnce(Return(true));

  EXPECT_FALSE(handler->PrepareForShutdown());
}

TEST_F(ForkJoinModuleHandlerTest, ShutdownSuccess) {
  EXPECT_CALL(*mock_module_main, Shutdown()).WillOnce(Return(true));
  EXPECT_CALL(*mock_module_worker, Shutdown()).WillOnce(Return(true));

  EXPECT_TRUE(handler->Shutdown());
}

TEST_F(ForkJoinModuleHandlerTest, ShutdownFailure) {
  EXPECT_CALL(*mock_module_main, Shutdown()).WillOnce(Return(false));
  EXPECT_CALL(*mock_module_worker, Shutdown()).WillOnce(Return(true));

  EXPECT_FALSE(handler->Shutdown());
}
