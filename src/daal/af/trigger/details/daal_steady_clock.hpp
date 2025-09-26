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

#ifndef APPLICATION_COMMON_MB_SAFE_RUNNER_TRIGGER_DETAILS_DAAL_STEADY_CLOCK_H_
#define APPLICATION_COMMON_MB_SAFE_RUNNER_TRIGGER_DETAILS_DAAL_STEADY_CLOCK_H_

#include <time.h>

#include <chrono>
#include <iostream>
#include <thread>

namespace daal {

namespace af {
namespace trigger {

/**
 * @brief A class that provides a static function to get the current time using
 * std::chrono::steady_clock.
 * Easy to mock for simulation, testing, and debugging purposes.
 * Common standard for time measurement.
 * TODO: Wirte to chrono TrivialClock concept.
 */
class DAALSteadyClock {
 public:
  /**
   * @brief Returns the current time as a std::chrono::steady_clock::time_point.
   * @return The current time.
   */
  static std::chrono::steady_clock::time_point now() {
    struct timespec time_now_c;
    if (clock_gettime(CLOCK_MONOTONIC, &time_now_c) == -1) {
      std::cerr << "Failed to get time using clock_gettime" << std::endl;
      exit(42);
    }

    // Convert timespec to steady_clock::time_point
    auto time_now = std::chrono::steady_clock::time_point(std::chrono::seconds(time_now_c.tv_sec) +
                                                          std::chrono::nanoseconds(time_now_c.tv_nsec));
    return time_now;
  }

  static void sleep_until(const std::chrono::steady_clock::time_point &time_point) {
    struct timespec desired_wakeup;
    auto duration = time_point.time_since_epoch();

    // get the seconds
    desired_wakeup.tv_sec = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    // get remaining nanoseconds
    desired_wakeup.tv_nsec =
        std::chrono::duration_cast<std::chrono::nanoseconds>(duration % std::chrono::seconds(1)).count();

    int ret;
    do {
      ret = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &desired_wakeup, NULL);
    } while (ret == EINTR);
  }
};

}  // namespace trigger

}  // namespace af

}  // namespace daal

#endif /* APPLICATION_COMMON_MB_SAFE_RUNNER_TRIGGER_DETAILS_DAAL_STEADY_CLOCK_H_ \
        */
