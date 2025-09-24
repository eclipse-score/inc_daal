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

#ifndef APPLICATION_COMMON_DAAL_SAFE_RUNNER_TRIGGER_DETAILS_TRIGGER_ACTIVATION_IMPL_H_
#define APPLICATION_COMMON_DAAL_SAFE_RUNNER_TRIGGER_DETAILS_TRIGGER_ACTIVATION_IMPL_H_

#include <chrono>
#include <cstdint>

#include "daal/af/trigger/trigger_activation.hpp"

namespace daal {

namespace af {

namespace trigger {

/**
 * @brief The PeriodicActivation class represents a trigger activation that
 * waits periodically by taking jitter in sleep/wake-up, and time elapsed into
 * the account.
 */
class PeriodicActivation : public TriggerActivation {
 public:
  /**
   * @brief Constructs a PeriodicActivation object with the specified period.
   * @param period The period at which the activation occurs.
   */
  explicit PeriodicActivation(std::chrono::nanoseconds period,
                              std::chrono::nanoseconds offset = std::chrono::nanoseconds(0));

  /**
   * @brief Default constructor.
   */
  PeriodicActivation() = delete;
  /**
   * @brief Default destructor.
   */
  ~PeriodicActivation() override = default;

  /**
   * @brief Copy constructor.
   */
  PeriodicActivation(const PeriodicActivation &) = default;

  /**
   * @brief Copy assignment operator.
   */
  PeriodicActivation &operator=(const PeriodicActivation &) & = default;

  /**
   * @brief Move constructor.
   */
  PeriodicActivation(PeriodicActivation &&) = default;

  /**
   * @brief Move assignment operator.
   */
  PeriodicActivation &operator=(PeriodicActivation &&) & = default;

  /**
   * @brief Waits for the activation to occur.
   * @return An integer representing the result of the wait operation.
   */
  auto Wait() -> uint64_t override;

 private:
  std::chrono::nanoseconds period_;
  std::chrono::nanoseconds offset_;
  std::chrono::steady_clock::time_point next_execution_time_;
  uint64_t missed_cycles_;
  bool initialized_;
};

}  // namespace trigger

}  // namespace af

}  // namespace daal

#endif /* APPLICATION_COMMON_DAAL_SAFE_RUNNER_TRIGGER_DETAILS_TRIGGER_ACTIVATION_IMPL_H_ \
        */
