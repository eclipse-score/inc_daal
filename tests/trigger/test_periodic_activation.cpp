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
#include <thread>

#include "daal/af/trigger/details/daal_steady_clock.hpp"
#include "daal/af/trigger/details/trigger_activation_impl.hpp"

using namespace std::chrono_literals;

class PeriodicActivationTest : public ::testing::Test {
 protected:
  void SetUp() override {
    fake = FakeObject<daal::af::trigger::DAALSteadyClockMock>::GetFakeObject();
  }

  void TearDown() override {
    FakeObject<daal::af::trigger::DAALSteadyClockMock>::RemoveFakeObject();
  }

  std::shared_ptr<daal::af::trigger::DAALSteadyClockMock> fake;
  std::chrono::steady_clock::time_point time_now_ =
      std::chrono::steady_clock::now();
  std::chrono::nanoseconds period_{100};
  std::chrono::nanoseconds execution_time_{50};
  std::chrono::nanoseconds jitter_{10};
  std::chrono::nanoseconds offset_{15};
};

TEST_F(PeriodicActivationTest, CTOR_WithNegativePeriod_ShouldDie) {
  // Fake object is at global scope, so we need to allow it to leak
  testing::Mock::AllowLeak(fake.get());
  // Prepare
  period_ = -100ms;
  // Assert death
  EXPECT_DEATH(
      {
        EXPECT_CALL(*fake, Now()).WillOnce(testing::Return(time_now_));
        daal::af::trigger::PeriodicActivation activation(period_);
      },
      "Period cannot be negative");
}

TEST_F(PeriodicActivationTest, CTOR_WithZeroPeriod_ShouldWork_Offset) {
  testing::Mock::AllowLeak(fake.get());
  daal::af::trigger::PeriodicActivation activation(period_, 100ns);
  auto start = std::chrono::steady_clock::now();
  EXPECT_EQ(activation.Wait(), 0);
  auto end = std::chrono::steady_clock::now();
  auto actual_period =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
  EXPECT_GE(actual_period, 100ns);
  start = std::chrono::steady_clock::now();

  EXPECT_EQ(activation.Wait(), 0);

  end = std::chrono::steady_clock::now();
  actual_period =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

  EXPECT_GE(actual_period, period_);
}

TEST_F(PeriodicActivationTest, Wait_ReturnsZeroMissedWakeupCalls) {
  // Prepare

  EXPECT_CALL(*fake, Now())
      .Times(4)
      .WillOnce(testing::Return(time_now_))  // offset
      .WillOnce(testing::Return(time_now_))  // app start time
      .WillOnce(testing::Return(time_now_ + execution_time_))
      .WillOnce(testing::Return(time_now_ + period_));

  daal::af::trigger::PeriodicActivation activation(period_);

  EXPECT_EQ(activation.Wait(), 0);
  EXPECT_EQ(activation.Wait(), 0);
  EXPECT_EQ(activation.Wait(), 0);
}

TEST_F(PeriodicActivationTest, Wait_SleepsForCorrectPeriod) {
  EXPECT_CALL(*fake, Now())
      .Times(3)
      .WillOnce(testing::Return(time_now_))
      .WillOnce(testing::Return(time_now_ + execution_time_))
      .WillOnce(testing::Return(time_now_ + period_));

  daal::af::trigger::PeriodicActivation activation(period_);
  EXPECT_EQ(activation.Wait(), 0);

  // Act
  auto start = std::chrono::steady_clock::now();

  // Call the Wait function
  EXPECT_EQ(activation.Wait(), 0);

  auto end = std::chrono::steady_clock::now();
  auto actual_period =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

  // Assert
  EXPECT_GE(actual_period, period_);  // Actual period should be greater than or
                                      // equal to the specified period
}

TEST_F(PeriodicActivationTest,
       Wait_WithRemainingTime_ShouldSleepForRemainingTime) {
  EXPECT_CALL(*fake, Now())
      .Times(3)
      .WillOnce(testing::Return(time_now_))
      .WillOnce(testing::Return(time_now_ + execution_time_))
      .WillOnce(testing::Return(time_now_ + period_ - jitter_));

  daal::af::trigger::PeriodicActivation activation{period_};
  EXPECT_EQ(activation.Wait(), 0);

  auto start = std::chrono::steady_clock::now();

  // Call the Wait function
  uint64_t missed_calls = activation.Wait();

  auto end = std::chrono::steady_clock::now();
  auto actual_period =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

  EXPECT_GE(actual_period, period_);

  // Check that the thread slept for the remaining time
  EXPECT_EQ(missed_calls, 0);
}

TEST_F(PeriodicActivationTest, Wait_WithExceededTime_ShouldHandleExceededTime) {
  EXPECT_CALL(*fake, Now())
      .Times(4)
      .WillOnce(testing::Return(time_now_))                      // offset
      .WillOnce(testing::Return(time_now_ + offset_))            // first call
      .WillOnce(testing::Return(time_now_ + offset_ + period_))  // second call
      .WillOnce(testing::Return(time_now_ + offset_ + period_ + period_ +
                                period_ + jitter_));  // third call

  daal::af::trigger::PeriodicActivation activation{period_};
  EXPECT_EQ(activation.Wait(), 0);  // offset first call
  EXPECT_EQ(activation.Wait(), 0);  // second call
  EXPECT_EQ(activation.Wait(), 1);  // third call
}

TEST_F(PeriodicActivationTest,
       Wait_WithExceededTime_ShouldHandleExceededTime_2) {
  EXPECT_CALL(*fake, Now())
      .Times(3)
      .WillOnce(testing::Return(time_now_))  // offset
      .WillOnce(
          testing::Return(time_now_ + offset_))  // app start time + period
      .WillOnce(testing::Return(time_now_ + execution_time_ + period_ +
                                period_ + period_));  // after sleep

  daal::af::trigger::PeriodicActivation activation{period_};
  EXPECT_EQ(activation.Wait(), 0);  // offset first call

  // Call the Wait function
  uint64_t missed_calls = activation.Wait();

  EXPECT_EQ(missed_calls, 2);
}

TEST_F(PeriodicActivationTest, Wait_NextExpectedTimeToWakeUpNoMiss) {
  EXPECT_CALL(*fake, Now())
      .Times(4)
      .WillOnce(testing::Return(time_now_))  // app start time
      .WillOnce(
          testing::Return(time_now_ + offset_))  // calculate execution time
      .WillOnce(testing::Return(time_now_ + period_ +
                                execution_time_))  // after sleep
      .WillOnce(testing::Return(time_now_ + period_ + period_));

  daal::af::trigger::PeriodicActivation activation{period_};
  EXPECT_EQ(activation.Wait(), 0);  // offset first call

  EXPECT_EQ(activation.Wait(), 0);
  EXPECT_EQ(activation.Wait(), 0);
}

TEST_F(PeriodicActivationTest, Wait_NextExpectedTimeToWakeUpMiss) {
  EXPECT_CALL(*fake, Now())
      .Times(5)
      // initial app start time
      .WillOnce(testing::Return(time_now_))
      // end of execution time
      .WillOnce(testing::Return(time_now_ + offset_))
      // start of execution
      .WillOnce(testing::Return(time_now_ + period_))
      // end of execution time
      .WillOnce(testing::Return(time_now_ + period_ + period_))
      // start of execution time
      .WillOnce(testing::Return(time_now_ + period_ + period_ + period_ +
                                period_ + jitter_));

  daal::af::trigger::PeriodicActivation activation{period_};
  EXPECT_EQ(activation.Wait(), 0);  // offset first call
  EXPECT_EQ(activation.Wait(), 0);
  EXPECT_EQ(activation.Wait(), 0);
  EXPECT_EQ(activation.Wait(), 1);
}
