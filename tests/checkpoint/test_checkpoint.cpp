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

#include "daal/af/checkpoint/details/checkpoint_container.hpp"
#include "daal/af/checkpoint/icheckpoint.hpp"

using namespace daal::af::checkpoint;

class MockCheckpoint : public ICheckpoint {
 public:
  MOCK_METHOD(std::error_code, Trigger, (), (override));
  MOCK_METHOD(When, GetWhen, (), (const, override));
  MOCK_METHOD(const std::string&, GetName, (), (const, override));
};

class CheckpointContainerTest : public ::testing::Test {
 protected:
  CheckpointContainer container;
};

TEST_F(CheckpointContainerTest, AddCheckpoint_Nullptr) {
  auto result = container.AddCheckpoint(nullptr);
  EXPECT_EQ(result, std::make_error_code(std::errc::invalid_argument));
}

TEST_F(CheckpointContainerTest, AddCheckpoint_Before) {
  auto checkpoint = std::make_shared<MockCheckpoint>();
  const std::string checkpoint1 = "checkpoint1";
  EXPECT_CALL(*checkpoint, GetWhen()).WillOnce(testing::Return(When::BEFORE));

  auto result = container.AddCheckpoint(checkpoint);
  EXPECT_EQ(result, std::error_code{});
}

TEST_F(CheckpointContainerTest, AddCheckpoint_After) {
  auto checkpoint = std::make_shared<MockCheckpoint>();
  const std::string checkpoint2 = "checkpoint2";
  EXPECT_CALL(*checkpoint, GetWhen()).WillOnce(testing::Return(When::AFTER));

  auto result = container.AddCheckpoint(checkpoint);
  EXPECT_EQ(result, std::error_code{});
}

TEST_F(CheckpointContainerTest, AddCheckpoint_Invalid) {
  auto checkpoint = std::make_shared<MockCheckpoint>();
  EXPECT_CALL(*checkpoint, GetWhen())
      .WillOnce(testing::Return(static_cast<When>(-1)));

  auto result = container.AddCheckpoint(checkpoint);
  EXPECT_EQ(result, std::make_error_code(std::errc::invalid_argument));
}

TEST_F(CheckpointContainerTest, AddCheckpoint_DuplicateBefore) {
  auto checkpoint = std::make_shared<MockCheckpoint>();
  const std::string checkpoint1_name = "checkpoint1";
  EXPECT_CALL(*checkpoint, GetWhen())
      .WillRepeatedly(testing::Return(When::BEFORE));
  EXPECT_CALL(*checkpoint, GetName())
      .WillRepeatedly(testing::ReturnRef(checkpoint1_name));

  container.AddCheckpoint(checkpoint);
  auto result = container.AddCheckpoint(checkpoint);
  EXPECT_EQ(result, std::make_error_code(std::errc::invalid_argument));

  auto checkpoint2 = std::make_shared<MockCheckpoint>();
  const std::string checkpoint2_name = "checkpoint2";
  EXPECT_CALL(*checkpoint2, GetWhen())
      .WillRepeatedly(testing::Return(When::BEFORE));
  EXPECT_CALL(*checkpoint2, GetName())
      .WillRepeatedly(testing::ReturnRef(checkpoint2_name));
  result = container.AddCheckpoint(checkpoint2);
  EXPECT_EQ(result, std::error_code{});

  auto checkpoint3 = std::make_shared<MockCheckpoint>();
  const std::string checkpoint3_name = "checkpoint2";
  EXPECT_CALL(*checkpoint3, GetWhen())
      .WillRepeatedly(testing::Return(When::BEFORE));
  EXPECT_CALL(*checkpoint3, GetName())
      .WillRepeatedly(testing::ReturnRef(checkpoint3_name));
  result = container.AddCheckpoint(checkpoint3);
  EXPECT_EQ(result, std::make_error_code(std::errc::invalid_argument));
}

TEST_F(CheckpointContainerTest, AddCheckpoint_DuplicateAfter) {
  auto checkpoint = std::make_shared<MockCheckpoint>();
  const std::string checkpoint1_name = "checkpoint1";
  EXPECT_CALL(*checkpoint, GetWhen())
      .WillRepeatedly(testing::Return(When::AFTER));
  EXPECT_CALL(*checkpoint, GetName())
      .WillRepeatedly(testing::ReturnRef(checkpoint1_name));

  container.AddCheckpoint(checkpoint);
  auto result = container.AddCheckpoint(checkpoint);
  EXPECT_EQ(result, std::make_error_code(std::errc::invalid_argument));

  auto checkpoint2 = std::make_shared<MockCheckpoint>();
  const std::string checkpoint2_name = "checkpoint2";
  EXPECT_CALL(*checkpoint2, GetWhen())
      .WillRepeatedly(testing::Return(When::AFTER));
  EXPECT_CALL(*checkpoint2, GetName())
      .WillRepeatedly(testing::ReturnRef(checkpoint2_name));
  result = container.AddCheckpoint(checkpoint2);
  EXPECT_EQ(result, std::error_code{});

  auto checkpoint3 = std::make_shared<MockCheckpoint>();
  const std::string checkpoint3_name = "checkpoint2";
  EXPECT_CALL(*checkpoint3, GetWhen())
      .WillRepeatedly(testing::Return(When::AFTER));
  EXPECT_CALL(*checkpoint3, GetName())
      .WillRepeatedly(testing::ReturnRef(checkpoint3_name));
  result = container.AddCheckpoint(checkpoint3);
  EXPECT_EQ(result, std::make_error_code(std::errc::invalid_argument));
}

TEST_F(CheckpointContainerTest, TriggerCheckpoints_Before) {
  auto checkpoint = std::make_shared<MockCheckpoint>();
  EXPECT_CALL(*checkpoint, GetWhen()).WillOnce(testing::Return(When::BEFORE));
  EXPECT_CALL(*checkpoint, Trigger())
      .WillOnce(testing::Return(std::error_code{}));

  container.AddCheckpoint(checkpoint);
  auto result = container.TriggerCheckpoints(When::BEFORE);
  EXPECT_EQ(result, std::error_code{});
}

TEST_F(CheckpointContainerTest, TriggerCheckpoints_After) {
  auto checkpoint = std::make_shared<MockCheckpoint>();
  EXPECT_CALL(*checkpoint, GetWhen()).WillOnce(testing::Return(When::AFTER));
  EXPECT_CALL(*checkpoint, Trigger())
      .WillOnce(testing::Return(std::error_code{}));

  container.AddCheckpoint(checkpoint);
  auto result = container.TriggerCheckpoints(When::AFTER);
  EXPECT_EQ(result, std::error_code{});
}

TEST_F(CheckpointContainerTest, TriggerCheckpoints_Error) {
  auto checkpoint = std::make_shared<MockCheckpoint>();
  EXPECT_CALL(*checkpoint, GetWhen()).WillOnce(testing::Return(When::BEFORE));
  EXPECT_CALL(*checkpoint, Trigger())
      .WillOnce(testing::Return(
          std::make_error_code(std::errc::operation_not_permitted)));

  container.AddCheckpoint(checkpoint);
  auto result = container.TriggerCheckpoints(When::BEFORE);
  EXPECT_EQ(result, std::make_error_code(std::errc::operation_not_permitted));
}