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

#ifndef APPLICATION_COMMON_DAAL_SAFE_RUNNER_TEST_MOCKS_LOCAL_TRIGGER_DAAL_STEADY_CLOCK_H_
#define APPLICATION_COMMON_DAAL_SAFE_RUNNER_TEST_MOCKS_LOCAL_TRIGGER_DAAL_STEADY_CLOCK_H_

#include <gmock/gmock.h>

#include <chrono>

#include "mocks/helper/fake_object.h"

namespace daal {

namespace af {

namespace trigger {

using duration = std::chrono::steady_clock::duration;
using time_point = std::chrono::steady_clock::time_point;

/**
 * @brief Mock class for the DAALSteadyClock.
 *
 * This class is used to mock the behavior of the DAALSteadyClock class for
 * testing purposes.
 */
class DAALSteadyClockMock : public FakeObject<DAALSteadyClockMock> {
 public:
  /**
   * @brief Mock method to get the current time point.
   *
   * @return The current time point.
   */
  MOCK_METHOD(time_point, Now, (), ());
};


/**
 * @brief Wrapper class for the std::chrono::steady_clock.
 *
 * This class provides a static method to get the current time point using the
 * DAALSteadyClock.
 */
class DAALSteadyClock {
 public:
  /**
   * @brief Get the current time point.
   *
   * @return The current time point.
   */
  static time_point now() {
    return FakeObject<DAALSteadyClockMock>::GetFakeObject()->Now();
  }

  static void sleep_until(const std::chrono::steady_clock::time_point &time_point) {
    return;
  }
};

} // namespace trigger

} // namespace af

} // namespace daal

#endif /* APPLICATION_COMMON_DAAL_SAFE_RUNNER_TEST_MOCKS_LOCAL_TRIGGER_DAAL_STEADY_CLOCK_H_ \
        */
