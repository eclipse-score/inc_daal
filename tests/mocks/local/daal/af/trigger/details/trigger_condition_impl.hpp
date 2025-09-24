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

#ifndef APPLICATION_COMMON_DAAL_SAFE_RUNNER_TEST_MOCKS_LOCAL_TRIGGER_TRIGGER_CONDITION_IMPL_H_
#define APPLICATION_COMMON_DAAL_SAFE_RUNNER_TEST_MOCKS_LOCAL_TRIGGER_TRIGGER_CONDITION_IMPL_H_

#include "mocks/helper/fake_object.h"
#include "daal/af/trigger/trigger_condition.hpp"

namespace daal {

namespace af {

namespace trigger {


/**
 * @class NullTriggerConditionMock
 * @brief Mock class for NullTriggerCondition.
 *        It provides a mock implementation of the IsTriggered() method.
 */
class NullTriggerConditionMock : public FakeObject<NullTriggerConditionMock> {
 public:
  /**
   * @brief Mock implementation of the IsTriggered() method.
   * @return true if the trigger condition is met, false otherwise.
   */
  MOCK_METHOD(bool, IsTriggered, (), ());
};

/**
 * @class NullTriggerCondition
 * @brief Fake implementation of the original NullTriggerCondition class.
 *        It delegates the IsTriggered() method to the NullTriggerConditionMock
 * class.
 */
class NullTriggerCondition : public daal::af::trigger::TriggerCondition {
 public:
  /**
   * @brief Forwards the call to Fake/Mocked object.
   * @return true if the trigger condition is met, false otherwise.
   */
  bool IsTriggered() override {
    return FakeObject<NullTriggerConditionMock>::GetFakeObject()->IsTriggered();
  };
};



} // namespace trigger

} // namespace af

} // namespace daal

#endif /* APPLICATION_COMMON_DAAL_SAFE_RUNNER_TEST_MOCKS_LOCAL_TRIGGER_TRIGGER_CONDITION_IMPL_H_ \
        */
