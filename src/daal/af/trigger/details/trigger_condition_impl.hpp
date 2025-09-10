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

#ifndef SRC_DAAL_AF_TRIGGER_DETAILS_TRIGGER_CONDITION_IMPL_H_
#define SRC_DAAL_AF_TRIGGER_DETAILS_TRIGGER_CONDITION_IMPL_H_

#include "daal/af/trigger/trigger_condition.hpp"

/**
 * @file trigger_condition_impl.hpp
 * @brief This file contains the implementation of the NullTriggerCondition
 * class.
 *
 * The NullTriggerCondition class is a concrete implementation of the
 * TriggerCondition interface. It provides a default implementation of the
 * IsTriggered() method.
 */

namespace daal {

namespace af {
namespace trigger {

/**
 * @class NullTriggerCondition
 * @brief A concrete implementation of the TriggerCondition interface.
 *
 * The NullTriggerCondition class provides a no condition wait.
 */
class NullTriggerCondition : public TriggerCondition {
 public:
  /**
   * @brief Default constructor.
   */
  NullTriggerCondition() = default;
  ~NullTriggerCondition() override = default;

  NullTriggerCondition(const NullTriggerCondition &) = default;
  auto operator=(const NullTriggerCondition &) -> NullTriggerCondition & = default;
  NullTriggerCondition(NullTriggerCondition &&) = default;
  auto operator=(NullTriggerCondition &&) -> NullTriggerCondition & = default;
  /**
   * @brief No condition check.
   * @return Always return true
   */
  auto IsTriggered() noexcept -> bool override;
};

}  // namespace trigger

}  // namespace af

}  // namespace daal

#endif /* SRC_DAAL_AF_TRIGGER_DETAILS_TRIGGER_CONDITION_IMPL_H_ */
