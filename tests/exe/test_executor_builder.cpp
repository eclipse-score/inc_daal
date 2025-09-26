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

#ifndef TEST_EXE_TEST_EXECUTOR_BUILDER_H_
#define TEST_EXE_TEST_EXECUTOR_BUILDER_H_

#include <gtest/gtest.h>

#include <memory>

#include "ara_exec_env_mock.hpp"
#include "checkpoint_mock.hpp"
#include "daal/af/exe/details/executor_impl.hpp"
#include "daal/af/exe/builder/executor_builder.hpp"
#include "qnx_os_mock.hpp"
#include "trigger_mock.hpp"

namespace daal {
namespace af {
namespace exe {

class ExecutorBuilderTest : public ::testing::Test {
 protected:
  void SetUp() override { components_ = std::make_shared<Components>(); }

  std::shared_ptr<Components> components_;
};

TEST_F(ExecutorBuilderTest, BuildExecutorSuccessfully) {
  auto exe_env = std::make_unique<env::AraExeEnvMock>();
  auto os_helper = std::make_unique<os::QNXOSMOCK>();
  auto trigger = std::make_unique<trigger::MockTrigger>();
  auto checkpoint_container =
      std::make_unique<checkpoint::MockCheckpointContainer>();

  ExecutorBuilder builder;
  auto executor = builder.SetExecutionEnvironment(std::move(exe_env))
                      .SetPosixHelper(std::move(os_helper))
                      .SetTrigger(std::move(trigger))
                      .SetCheckpointContainer(std::move(checkpoint_container))
                      .End()
                      .Build();

  ASSERT_NE(executor, nullptr);
}

TEST_F(ExecutorBuilderTest, AddCheckpointSuccessfully) {
  auto checkpoint_container =
      std::make_unique<checkpoint::MockCheckpointContainer>();
  auto checkpoint = std::make_shared<checkpoint::MockCheckpoint>();

  ExecutorBuilder builder;
  builder.SetExecutionEnvironment(std::make_unique<env::AraExeEnvMock>())
      .SetPosixHelper(std::make_unique<os::QNXOSMOCK>())
      .SetTrigger(std::make_unique<trigger::MockTrigger>())
      .SetCheckpointContainer(std::move(checkpoint_container))
      .Start()
      .AddCheckpoint(checkpoint)
      .End()
      .Build();
}

TEST_F(ExecutorBuilderTest, CheckpointContainerNotSet) {
  ExecutorBuilder builder;
  builder.SetExecutionEnvironment(std::make_unique<env::AraExeEnvMock>())
      .SetPosixHelper(std::make_unique<os::QNXOSMOCK>())
      .SetTrigger(std::make_unique<trigger::MockTrigger>());
}

TEST_F(ExecutorBuilderTest, CreateCheckpointContainerSuccessfully) {
  ExecutorBuilder builder;
  builder.SetExecutionEnvironment(std::make_unique<env::AraExeEnvMock>())
      .SetPosixHelper(std::make_unique<os::QNXOSMOCK>())
      .SetTrigger(std::make_unique<trigger::MockTrigger>())
      .CreateCheckpointContainer<checkpoint::MockCheckpointContainer>()
      .Start()
      .AddCheckpoint(std::make_shared<checkpoint::MockCheckpoint>())
      .End()
      .Build();
}

TEST_F(ExecutorBuilderTest, CreateTriggerSuccessfully) {
  ExecutorBuilder builder;
  builder.SetExecutionEnvironment(std::make_unique<env::AraExeEnvMock>())
      .SetPosixHelper(std::make_unique<os::QNXOSMOCK>())
      .CreateTrigger<trigger::MockTrigger>()
      .CreateCheckpointContainer<checkpoint::MockCheckpointContainer>()
      .Start()
      .AddCheckpoint(std::make_shared<checkpoint::MockCheckpoint>())
      .End()
      .Build();
}

TEST_F(ExecutorBuilderTest, CreatePosixHelperSuccessfully) {
  ExecutorBuilder builder;
  builder.SetExecutionEnvironment(std::make_unique<env::AraExeEnvMock>())
      .CreatePosixHelper<os::QNXOSMOCK>()
      .CreateTrigger<trigger::MockTrigger>()
      .CreateCheckpointContainer<checkpoint::MockCheckpointContainer>()
      .Start()
      .AddCheckpoint(std::make_shared<checkpoint::MockCheckpoint>())
      .End()
      .Build();
}

}  // namespace exe
}  // namespace af
}  // namespace daal

#endif /* TEST_EXE_TEST_EXECUTOR_BUILDER_H_ */
