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
#include <cstdlib>

#include <memory>

#include "ara_exec_env_mock.hpp"
#include "checkpoint_mock.hpp"
#include "daal/af/app_base/safe_application_base.hpp"
#include "daal/af/app_handler/details/single_shot_app_handler.hpp"
#include "daal/af/checkpoint/details/checkpoint_container.hpp"
#include "daal/af/exe/details/executor_impl.hpp"
#include "qnx_os_mock.hpp"
#include "trigger_mock.hpp"

/*!
 * \brief Mocked test Application to feed the Executor
 *
 */
class TestDAALApp : public daal::af::app_base::SafeApplicationBase {
 public:
  MOCK_METHOD(daal::af::app_base::MethodState, OnInitialize, (), (override));
  MOCK_METHOD(daal::af::app_base::MethodState, OnStart, (), (override));
  MOCK_METHOD(daal::af::app_base::MethodState, Step, (), (override));
  MOCK_METHOD(daal::af::app_base::MethodState, OnStop, (), (override));
  MOCK_METHOD(daal::af::app_base::MethodState, OnTerminate, (), (override));
};

/*!
 * \brief Base Test class for below tests, which gives basic instances for test
 *
 */
class ExecutorTest : public ::testing::Test {
 protected:
  std::unique_ptr<daal::af::trigger::MockTrigger> trigger_ptr =
      std::make_unique<daal::af::trigger::MockTrigger>();
  daal::af::trigger::MockTrigger& trigger = *trigger_ptr.get();
  std::unique_ptr<daal::af::env::AraExeEnvMock> aae_ptr =
      std::make_unique<daal::af::env::AraExeEnvMock>();
  daal::af::env::AraExeEnvMock& aae = *aae_ptr.get();
  std::unique_ptr<daal::af::os::QNXOSMOCK> os_help_ptr =
      std::make_unique<daal::af::os::QNXOSMOCK>();
  daal::af::os::QNXOSMOCK& os_help = *os_help_ptr.get();
  std::unique_ptr<daal::af::checkpoint::MockCheckpointContainer> cc_ptr =
      std::make_unique<daal::af::checkpoint::MockCheckpointContainer>();
  daal::af::checkpoint::MockCheckpointContainer& cc = *cc_ptr.get();
  daal::af::exe::Executor exe{std::move(aae_ptr), std::move(os_help_ptr),
                            std::move(trigger_ptr), std::move(cc_ptr)};

  void SetUp() override {}

  void TearDown() override {}
};

TEST(ExecutorCtor, callsInCtor) {
  std::unique_ptr<daal::af::trigger::MockTrigger> trigger_ptr =
      std::make_unique<daal::af::trigger::MockTrigger>();
  daal::af::trigger::MockTrigger& trigger = *trigger_ptr.get();
  std::unique_ptr<daal::af::env::AraExeEnvMock> aae_ptr =
      std::make_unique<daal::af::env::AraExeEnvMock>();
  daal::af::env::AraExeEnvMock& aae = *aae_ptr.get();
  std::unique_ptr<daal::af::os::QNXOSMOCK> os_help_ptr =
      std::make_unique<daal::af::os::QNXOSMOCK>();
  daal::af::os::QNXOSMOCK& os_help = *os_help_ptr.get();
  std::unique_ptr<daal::af::checkpoint::MockCheckpointContainer> cc_ptr =
      std::make_unique<daal::af::checkpoint::MockCheckpointContainer>();
  daal::af::checkpoint::MockCheckpointContainer& cc = *cc_ptr.get();

  EXPECT_CALL(os_help, SetupOomHandler()).Times(1);

  daal::af::exe::Executor exe{std::move(aae_ptr), std::move(os_help_ptr),
                            std::move(trigger_ptr), std::move(cc_ptr)};
}

/*!
 * \brief Test for normal flow of the Executor expected call sequences of its
 * public methods.
 *
 */
TEST_F(ExecutorTest, HandelNormalFlow) {
  EXPECT_CALL(aae, Init()).Times(1).WillOnce(testing::Return(true));
  EXPECT_CALL(os_help, IsNoEnvVarSet(testing::_, testing::_))
      .Times(1)
      .WillOnce(testing::Return(true));
  EXPECT_CALL(os_help, IsFpuWorking(testing::_))
      .Times(1)
      .WillOnce(testing::Return(true));

  EXPECT_CALL(aae, SetState(daal::af::env::ExecutionEnvironment::State::kRunning))
      .Times(1);

  EXPECT_TRUE(exe.Init());

  auto app = std::make_shared<TestDAALApp>();

  std::unique_ptr<daal::af::app_handler::SingleShotAppHandler> app_handler =
      std::make_unique<daal::af::app_handler::SingleShotAppHandler>(app);

  exe.SetApplicationHandler(std::move(app_handler));
  EXPECT_CALL(os_help, DropPrivileges())
      .Times(1)
      .WillOnce(testing::Return(true));

  EXPECT_CALL(*app, OnInitialize())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));
  EXPECT_CALL(*app, OnStart())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));
  EXPECT_CALL(aae, Refresh()).Times(1).WillOnce(testing::Return(true));
  EXPECT_CALL(*app, Step())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));
  EXPECT_CALL(cc, TriggerCheckpoints(daal::af::checkpoint::When::BEFORE))
      .Times(1);
  EXPECT_CALL(cc, TriggerCheckpoints(daal::af::checkpoint::When::AFTER)).Times(1);
  EXPECT_CALL(*app, OnStop())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));
  EXPECT_CALL(*app, OnTerminate())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));
  EXPECT_CALL(aae,
              SetState(daal::af::env::ExecutionEnvironment::State::kTerminate))
      .Times(1);

  // TODO fix the this test for trigger ADASDAI-159871
  EXPECT_CALL(trigger, CheckTriggerConditionAndWait()).Times(1);
  EXPECT_CALL(aae, IsSigTerm())
      .Times(2)
      .WillOnce(testing::Return(false))
      .WillOnce(testing::Return(true));

  EXPECT_TRUE(exe.Run());
}

/*!
 * \brief Fail the Executor init function with mocked objects.
 *
 */
TEST_F(ExecutorTest, CheckInitFail) {
  EXPECT_CALL(aae, Init())
      .Times(4)
      .WillOnce(testing::Return(false))
      .WillOnce(testing::Return(true))
      .WillOnce(testing::Return(true))
      .WillOnce(testing::Return(true));
  EXPECT_CALL(os_help, IsNoEnvVarSet(testing::_, testing::_))
      .Times(3)
      .WillOnce(testing::Return(false))
      .WillOnce(testing::Return(true))
      .WillOnce(testing::Return(true));
  EXPECT_CALL(os_help, IsFpuWorking(testing::_))
      .Times(2)
      .WillOnce(testing::Return(false))
      .WillOnce(testing::Return(true));

  EXPECT_FALSE(exe.Init());
  EXPECT_FALSE(exe.Init());
  EXPECT_FALSE(exe.Init());
  EXPECT_TRUE(exe.Init());
}

/*!
 * \brief Test run function of Executor without the initialisation called and
 * check after initialization
 *
 */
TEST_F(ExecutorTest, runWithoutPreconfig) {
  EXPECT_CALL(aae, Init()).Times(1).WillOnce(testing::Return(true));

  EXPECT_CALL(os_help, IsNoEnvVarSet(testing::_, testing::_))
      .Times(1)
      .WillOnce(testing::Return(true));
  EXPECT_CALL(os_help, IsFpuWorking(testing::_))
      .Times(1)
      .WillOnce(testing::Return(true));

  // Shall set running if initialisation is not done
  EXPECT_CALL(aae, SetState(daal::af::env::ExecutionEnvironment::State::kRunning))
      .Times(0);
  // Invalid Run call without Init.
  EXPECT_FALSE(exe.Run());

  EXPECT_TRUE(exe.Init());
  // Invalid Run call without setting application.
  EXPECT_FALSE(exe.Run());
}

/*!
 * \brief Test for Application failures in OnInitialize() function for Executor
 * Run method
 *
 */
TEST_F(ExecutorTest, failApplicationInitStarting) {
  EXPECT_CALL(aae, Init()).Times(1).WillOnce(testing::Return(true));
  EXPECT_CALL(aae, SetState(daal::af::env::ExecutionEnvironment::State::kRunning))
      .Times(0);
  EXPECT_CALL(aae,
              SetState(daal::af::env::ExecutionEnvironment::State::kTerminate))
      .Times(0);

  EXPECT_CALL(os_help, IsNoEnvVarSet(testing::_, testing::_))
      .Times(1)
      .WillOnce(testing::Return(true));
  EXPECT_CALL(os_help, IsFpuWorking(testing::_))
      .Times(1)
      .WillOnce(testing::Return(true));

  EXPECT_CALL(os_help, DropPrivileges())
      .Times(0)
      .WillOnce(testing::Return(true));

  EXPECT_TRUE(exe.Init());

  auto app = std::make_shared<TestDAALApp>();

  std::unique_ptr<daal::af::app_handler::SingleShotAppHandler> app_handler =
      std::make_unique<daal::af::app_handler::SingleShotAppHandler>(app);
  exe.SetApplicationHandler(std::move(app_handler));

  // Fail the application Init
  EXPECT_CALL(*app, OnInitialize())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kFailed));
  EXPECT_CALL(*app, OnStart()).Times(0);
  EXPECT_CALL(*app, Step()).Times(0);
  EXPECT_CALL(*app, OnStop()).Times(0);
  EXPECT_CALL(*app, OnTerminate()).Times(0);
  EXPECT_CALL(cc, TriggerCheckpoints(testing::_)).Times(0);

  EXPECT_FALSE(exe.Run());
}

/*!
 * \brief Test for Application failures in OnStart() function for Executor Run
 * method
 *
 */
TEST_F(ExecutorTest, failApplicationInitOnStart) {
  EXPECT_CALL(aae, Init()).Times(1).WillOnce(testing::Return(true));
  EXPECT_CALL(aae, SetState(daal::af::env::ExecutionEnvironment::State::kRunning))
      .Times(0);
  EXPECT_CALL(aae,
              SetState(daal::af::env::ExecutionEnvironment::State::kTerminate))
      .Times(0);

  EXPECT_CALL(os_help, IsNoEnvVarSet(testing::_, testing::_))
      .Times(1)
      .WillOnce(testing::Return(true));
  EXPECT_CALL(os_help, IsFpuWorking(testing::_))
      .Times(1)
      .WillOnce(testing::Return(true));

  EXPECT_CALL(os_help, DropPrivileges())
      .Times(0)
      .WillOnce(testing::Return(true));

  EXPECT_TRUE(exe.Init());

  auto app = std::make_shared<TestDAALApp>();

  std::unique_ptr<daal::af::app_handler::SingleShotAppHandler> app_handler =
      std::make_unique<daal::af::app_handler::SingleShotAppHandler>(app);
  exe.SetApplicationHandler(std::move(app_handler));

  // Fail the application Init
  EXPECT_CALL(*app, OnInitialize())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));
  EXPECT_CALL(*app, OnStart())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kFailed));
  EXPECT_CALL(*app, Step()).Times(0);
  EXPECT_CALL(*app, OnStop()).Times(0);
  EXPECT_CALL(*app, OnTerminate()).Times(0);
  EXPECT_CALL(cc, TriggerCheckpoints(testing::_)).Times(0);

  EXPECT_FALSE(exe.Run());
}

/*!
 * \brief Test for Application failures in OnStop() function for Executor Run
 * method
 *
 */
TEST_F(ExecutorTest, failApplicationOnStop) {
  EXPECT_CALL(aae, Init()).Times(1).WillOnce(testing::Return(true));
  EXPECT_CALL(aae, IsSigTerm())
      .Times(2)
      .WillOnce(testing::Return(false))
      .WillOnce(testing::Return(true));
  EXPECT_CALL(aae, SetState(daal::af::env::ExecutionEnvironment::State::kRunning))
      .Times(1);
  EXPECT_CALL(aae,
              SetState(daal::af::env::ExecutionEnvironment::State::kTerminate))
      .Times(1);
  EXPECT_CALL(os_help, IsNoEnvVarSet(testing::_, testing::_))
      .Times(1)
      .WillOnce(testing::Return(true));
  EXPECT_CALL(os_help, IsFpuWorking(testing::_))
      .Times(1)
      .WillOnce(testing::Return(true));

  EXPECT_CALL(os_help, DropPrivileges())
      .Times(1)
      .WillOnce(testing::Return(true));

  EXPECT_TRUE(exe.Init());

  auto app = std::make_shared<TestDAALApp>();

  std::unique_ptr<daal::af::app_handler::SingleShotAppHandler> app_handler =
      std::make_unique<daal::af::app_handler::SingleShotAppHandler>(app);
  exe.SetApplicationHandler(std::move(app_handler));

  EXPECT_CALL(*app, OnInitialize())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));
  EXPECT_CALL(*app, OnStart())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));

  EXPECT_CALL(*app, Step())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));
  EXPECT_CALL(cc, TriggerCheckpoints(daal::af::checkpoint::When::BEFORE))
      .Times(1);
  EXPECT_CALL(cc, TriggerCheckpoints(daal::af::checkpoint::When::AFTER)).Times(1);
  // Fail to deinitialize
  EXPECT_CALL(*app, OnStop())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kFailed));
  EXPECT_CALL(*app, OnTerminate())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));

  EXPECT_FALSE(exe.Run());
}

/*!
 * \brief Test for Application failures in OnTerminate() function for Executor
 * Run method
 *
 */
TEST_F(ExecutorTest, failApplicationTerminating) {
  EXPECT_CALL(aae, Init()).Times(1).WillOnce(testing::Return(true));
  EXPECT_CALL(aae, IsSigTerm())
      .Times(2)
      .WillOnce(testing::Return(false))
      .WillOnce(testing::Return(true));
  EXPECT_CALL(aae, SetState(daal::af::env::ExecutionEnvironment::State::kRunning))
      .Times(1);
  EXPECT_CALL(aae,
              SetState(daal::af::env::ExecutionEnvironment::State::kTerminate))
      .Times(1);

  EXPECT_CALL(os_help, IsNoEnvVarSet(testing::_, testing::_))
      .Times(1)
      .WillOnce(testing::Return(true));
  EXPECT_CALL(os_help, IsFpuWorking(testing::_))
      .Times(1)
      .WillOnce(testing::Return(true));

  EXPECT_CALL(os_help, DropPrivileges())
      .Times(1)
      .WillOnce(testing::Return(true));

  EXPECT_TRUE(exe.Init());

  auto app = std::make_shared<TestDAALApp>();

  std::unique_ptr<daal::af::app_handler::SingleShotAppHandler> app_handler =
      std::make_unique<daal::af::app_handler::SingleShotAppHandler>(app);
  exe.SetApplicationHandler(std::move(app_handler));

  EXPECT_CALL(*app, OnInitialize())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));
  EXPECT_CALL(*app, OnStart())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));

  EXPECT_CALL(*app, Step())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));
  EXPECT_CALL(cc, TriggerCheckpoints(daal::af::checkpoint::When::BEFORE))
      .Times(1);
  EXPECT_CALL(cc, TriggerCheckpoints(daal::af::checkpoint::When::AFTER)).Times(1);
  // Fail to deinitialize
  EXPECT_CALL(*app, OnStop())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kFailed));
  EXPECT_CALL(*app, OnTerminate())
      .Times(1)
      .WillOnce(testing::Return(daal::af::app_base::MethodState::kSuccessful));

  EXPECT_FALSE(exe.Run());
}

/*!
 * \brief Test for Executor Run method when application handler is not set
 *
 */
TEST_F(ExecutorTest, RunWithoutApplicationHandler) {
  EXPECT_CALL(aae, Init()).Times(1).WillOnce(testing::Return(true));
  EXPECT_CALL(os_help, IsNoEnvVarSet(testing::_, testing::_))
      .Times(1)
      .WillOnce(testing::Return(true));
  EXPECT_CALL(os_help, IsFpuWorking(testing::_))
      .Times(1)
      .WillOnce(testing::Return(true));

  EXPECT_TRUE(exe.Init());

  EXPECT_FALSE(exe.Run());
}

/*!
 * \brief Test for Executor Init method when ExecutionEnvironment initialization
 * fails
 *
 */
TEST_F(ExecutorTest, InitExecutionEnvironmentFail) {
  EXPECT_CALL(aae, Init()).Times(1).WillOnce(testing::Return(false));

  EXPECT_FALSE(exe.Init());
}

/*!
 * \brief Test for Executor Init method when environment variables are dirty
 *
 */
TEST_F(ExecutorTest, InitDirtyEnvironmentVariables) {
  EXPECT_CALL(aae, Init()).Times(1).WillOnce(testing::Return(true));
  EXPECT_CALL(os_help, IsNoEnvVarSet(testing::_, testing::_))
      .Times(1)
      .WillOnce(testing::Return(false));

  EXPECT_FALSE(exe.Init());
}

/*!
 * \brief Test for Executor Init method when FPU check fails
 *
 */
TEST_F(ExecutorTest, InitFpuCheckFail) {
  EXPECT_CALL(aae, Init()).Times(1).WillOnce(testing::Return(true));
  EXPECT_CALL(os_help, IsNoEnvVarSet(testing::_, testing::_))
      .Times(1)
      .WillOnce(testing::Return(true));
  EXPECT_CALL(os_help, IsFpuWorking(testing::_))
      .Times(1)
      .WillOnce(testing::Return(false));

  EXPECT_FALSE(exe.Init());
}
