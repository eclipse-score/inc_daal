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

#include <cstdint>

/**
 * @file trigger_activation.hpp
 * @brief Defines the TriggerActivation class.
 *
 * This file contains the definition of the TriggerActivation class, which is an
 * abstract base class for trigger activation in the application.
 */

#ifndef APPLICATION_COMMON_DAAL_SAFE_RUNNER_TRIGGER_TRIGGER_ACTIVATION_H_
#define APPLICATION_COMMON_DAAL_SAFE_RUNNER_TRIGGER_TRIGGER_ACTIVATION_H_

namespace daal {

namespace af {
namespace trigger {

/**
 * @class TriggerActivation
 * @brief Abstract base class for trigger activation in the application.
 *
 * The TriggerActivation class provides an interface for trigger activation,
 * which is used to wait for a trigger event in the application.
 */
class TriggerActivation {
 public:
  /**
   * @brief Default constructor.
   */
  TriggerActivation() = default;

  /**
   * @brief Destructor.
   */
  virtual ~TriggerActivation() = default;

 protected:
  /**
   * @brief Copy constructor.
   */
  TriggerActivation(const TriggerActivation &) = default;

  /**
   * @brief Copy assignment operator.
   */
  TriggerActivation &operator=(const TriggerActivation &) & = default;

  /**
   * @brief Move constructor.
   */
  TriggerActivation(TriggerActivation &&) = default;

  /**
   * @brief Move assignment operator.
   */
  TriggerActivation &operator=(TriggerActivation &&) & = default;

 public:
  /**
   * @brief Wait for the remaining time.
   * @return missed calls.
   */
  virtual auto Wait() -> uint64_t = 0;
};

}  // namespace trigger

}  // namespace af

}  // namespace daal

#endif /* APPLICATION_COMMON_DAAL_SAFE_RUNNER_TRIGGER_TRIGGER_ACTIVATION_H_ */
