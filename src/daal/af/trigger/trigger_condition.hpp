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
 * @file trigger_condition.hpp
 * @brief Defines the TriggerCondition class.
 *
 * The TriggerCondition class is an abstract base class that represents a
 * condition for triggering an action. Subclasses of TriggerCondition can
 * implement their own logic for determining whether the trigger condition is
 * met.
 */

#ifndef APPLICATION_COMMON_DAAL_SAFE_RUNNER_TRIGGER_TRIGGER_CONDITION_H_
#define APPLICATION_COMMON_DAAL_SAFE_RUNNER_TRIGGER_TRIGGER_CONDITION_H_

namespace daal {

namespace af {
namespace trigger {

/**
 * @class TriggerCondition
 * @brief Abstract base class for trigger conditions.
 *
 * The TriggerCondition class provides an interface for defining trigger
 * conditions. Subclasses of TriggerCondition must implement the IsTriggered()
 * method to determine whether the trigger condition is met.
 */
class TriggerCondition {
 public:
  /**
   * @brief Default constructor.
   */
  TriggerCondition() = default;

  /**
   * @brief Destructor.
   */
  virtual ~TriggerCondition() = default;

 protected:
  /**
   * @brief Deleted copy constructor.
   */
  TriggerCondition(const TriggerCondition &) = default;

  /**
   * @brief Deleted copy assignment operator.
   */
  TriggerCondition &operator=(const TriggerCondition &) & = default;

  /**
   * @brief Deleted move constructor.
   */
  TriggerCondition(TriggerCondition &&) = default;

  /**
   * @brief Deleted move assignment operator.
   */
  TriggerCondition &operator=(TriggerCondition &&) & = default;

 public:
  /**
   * @brief Checks whether the trigger condition is met.
   * @return true if the trigger condition is met, false otherwise.
   */
  virtual auto IsTriggered() -> bool = 0;
};

}  // namespace trigger

}  // namespace af

}  // namespace daal

#endif /* APPLICATION_COMMON_DAAL_SAFE_RUNNER_TRIGGER_TRIGGER_CONDITION_H_ */
