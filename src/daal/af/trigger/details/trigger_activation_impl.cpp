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

#include "daal/af/trigger/details/trigger_activation_impl.hpp"

#include <chrono>
#include <cmath>
#include <cstdint>

#include "daal/af/trigger/details/daal_steady_clock.hpp"
#include "daal/log/framework_logger.hpp"

namespace daal {
namespace af {
namespace trigger {

PeriodicActivation::PeriodicActivation(std::chrono::nanoseconds period, std::chrono::nanoseconds offset)
    : period_{period}, offset_{offset}, missed_cycles_{0}, initialized_{false} {
  if (period_.count() <= 0 || offset_.count() < 0) {
    daal::log::FrameworkLogger::get()->Error("Period cannot be negative or zero / offset can not be negative");
    exit(42);
  }
}

auto PeriodicActivation::Wait() -> uint64_t {
  if (!initialized_) {
    auto time_now = DAALSteadyClock::now();
    // For the first cycle, pick the global time slot
    auto global_start = time_now + (period_ - (time_now.time_since_epoch() % period_));
    // introduce the offset for picking precise start point relative to global
    // time slot
    next_execution_time_ = global_start + offset_;
    initialized_ = true;
  }

  // Wait for until it is time for execute
  DAALSteadyClock::sleep_until(next_execution_time_);

  // Get actual wakeup time
  auto time_now = DAALSteadyClock::now();

  // Check if we have missed calls
  missed_cycles_ = 0;
  if (time_now > next_execution_time_) {
    missed_cycles_ = static_cast<uint64_t>((time_now - next_execution_time_).count() / period_.count());
  }

  // Forecast to next time point
  next_execution_time_ = next_execution_time_ + ((missed_cycles_ + 1) * period_);

  return missed_cycles_;
}

}  // namespace trigger

}  // namespace af

}  // namespace daal
