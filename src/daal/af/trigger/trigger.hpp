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
 * @file trigger.hpp
 * @brief This file contains the declaration of the Trigger class.
 *
 * The Trigger class is an abstract base class that defines the interface for
 * trigger objects. Trigger objects are responsible for checking trigger
 * conditions and waiting until the conditions are met. Derived classes must
 * implement the CheckTriggerConditionAndWait() function.
 */

#ifndef APPLICATION_COMMON_DAAL_SAFE_RUNNER_TRIGGER_TRIGGER_H_
#define APPLICATION_COMMON_DAAL_SAFE_RUNNER_TRIGGER_TRIGGER_H_

namespace daal {

namespace af {
namespace trigger {

class Trigger {
 public:
  /**
   * @brief Default constructor for the Trigger class.
   */
  Trigger() = default;
  /**
   * @brief Virtual destructor for the Trigger class.
   */
  virtual ~Trigger() = default;

 protected:
  /**
   * @brief Copy constructor for the Trigger class.
   */
  Trigger(const Trigger &) = default;

  /**
   * @brief Copy assignment operator for the Trigger class.
   */
  Trigger &operator=(const Trigger &) & = default;

  /**
   * @brief Move constructor for the Trigger class.
   */
  Trigger(Trigger &&) = default;

  /**
   * @brief Move assignment operator for the Trigger class.
   */
  Trigger &operator=(Trigger &&) & = default;

 public:
  /**
   * @brief Checks the trigger condition and waits until the condition is met.
   *
   * This function is pure virtual and must be implemented by derived classes.
   */
  virtual bool CheckTriggerConditionAndWait() = 0;
};

}  // namespace trigger

}  // namespace af

}  // namespace daal

#endif /* APPLICATION_COMMON_DAAL_SAFE_RUNNER_TRIGGER_TRIGGER_H_ */
