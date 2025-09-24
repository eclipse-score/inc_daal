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

/**
 * @file trigger_impl.hpp
 * @brief Contains the implementation of the PeriodicTrigger class.
 *
 * This file defines the PeriodicTrigger class, which is a concrete
 * implementation of the Trigger interface. The PeriodicTrigger class represents
 * a trigger that checks a trigger condition periodically and waits if the
 * condition is met. It is used in the MB Safe Runner application.
 */

#ifndef APPLICATION_COMMON_DAAL_SAFE_RUNNER_TRIGGER_DETAILS_TRIGGER_IMPL_H_
#define APPLICATION_COMMON_DAAL_SAFE_RUNNER_TRIGGER_DETAILS_TRIGGER_IMPL_H_

#include <chrono>

#include "daal/af/trigger/details/trigger_activation_impl.hpp"
#include "daal/af/trigger/details/trigger_condition_impl.hpp"
#include "daal/af/trigger/trigger.hpp"
#include "daal/af/trigger/trigger_activation.hpp"
#include "daal/af/trigger/trigger_condition.hpp"

namespace daal {

namespace af {
namespace trigger {

/**
 * @class SimpleTrigger
 * @brief Represents a simple trigger that checks a trigger condition and waits
 * if the condition is met.
 *
 * The SimpleTrigger class provides the functionality to check a trigger
 * condition and wait if the condition is met. It is a base class for other
 * trigger types and is used as a building block for more complex triggers. The
 * trigger condition and activation are implemented using the TriggerCondition
 * and TriggerActivation classes, respectively.
 */
class SimpleTrigger : public Trigger {
 public:
  /**
   * @brief Constructs a SimpleTrigger object with the specified trigger
   * activation and trigger condition.
   * @param trigger_activation The trigger activation object.
   * @param trigger_condition The trigger condition object.
   */
  SimpleTrigger(TriggerActivation &trigger_activation, TriggerCondition &trigger_condition) noexcept;

  ~SimpleTrigger() override = default;

 protected:
  SimpleTrigger(const SimpleTrigger &) = default;
  SimpleTrigger &operator=(const SimpleTrigger &) & = default;

  SimpleTrigger(SimpleTrigger &&) = default;
  SimpleTrigger &operator=(SimpleTrigger &&) & = default;

 public:
  /**
   * @brief Checks the trigger condition and waits if the condition is met.
   *
   * This function checks the trigger condition and waits if the condition is
   * met before returning.
   */
  auto CheckTriggerConditionAndWait() -> bool override;

 private:
  TriggerActivation &trigger_activation_; /**< The trigger activation object. */
  TriggerCondition &trigger_condition_;   /**< The trigger condition object. */
};

/**
 * @class PeriodicTrigger
 * @brief Represents a periodic trigger that checks a trigger condition and
 * waits if the condition is met.
 *
 * The PeriodicTrigger class is an extension of SimpleTrigger for periodic
 * triggers. The concreate trigger condition and activation are the
 * PeriodicActivation and NullTriggerCondition classes, respectively.
 */
class PeriodicTrigger : public SimpleTrigger {
 public:
  /**
   * @brief Constructs a PeriodicTrigger object with the specified period.
   * @param period The period at which the trigger condition should be checked.
   */
  explicit PeriodicTrigger(std::chrono::nanoseconds period);

  ~PeriodicTrigger() override = default;

 protected:
  PeriodicTrigger(const PeriodicTrigger &) = default;
  PeriodicTrigger &operator=(const PeriodicTrigger &) & = default;
  PeriodicTrigger(PeriodicTrigger &&) = delete;
  PeriodicTrigger &operator=(PeriodicTrigger &&) & = default;

 private:
  PeriodicActivation activation_;  /**< The periodic activation object. */
  NullTriggerCondition condition_; /**< The null trigger condition object. */
};

}  // namespace trigger

}  // namespace af

}  // namespace daal

#endif /* APPLICATION_COMMON_DAAL_SAFE_RUNNER_TRIGGER_DETAILS_TRIGGER_IMPL_H_ */
