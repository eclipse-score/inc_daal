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

#include "src/daal/af/trigger/details/daal_steady_clock.hpp"

using namespace daal::af::trigger;
using namespace std::chrono;

class DAALSteadyClockTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up any necessary resources before running the test cases
  }

  void TearDown() override {
    // Clean up any resources allocated in SetUp()
  }
};

TEST_F(DAALSteadyClockTest, Now_ReturnsCurrentTime) {
  // Arrange
  auto expectedTime = steady_clock::now();

  // Act
  auto actualTime = DAALSteadyClock::now();

  // Assert
  EXPECT_GE(actualTime.time_since_epoch().count(),
            expectedTime.time_since_epoch().count());
}
