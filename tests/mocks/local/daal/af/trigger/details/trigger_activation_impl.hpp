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

#ifndef APPLICATION_COMMON_DAAL_SAFE_RUNNER_TEST_MOCKS_LOCAL_TRIGGER_TRIGGER_ACTIVATION_IMPL_H_
#define APPLICATION_COMMON_DAAL_SAFE_RUNNER_TEST_MOCKS_LOCAL_TRIGGER_TRIGGER_ACTIVATION_IMPL_H_

#include <gmock/gmock.h>

#include <chrono>

#include "daal/af/trigger/trigger_activation.hpp"
#include "mocks/helper/fake_object.h"


namespace daal {

namespace af {

namespace trigger {


/**
 * @class PeriodicActivationMock
 * @brief Mock class for faking PeriodicActivation.
 */
class PeriodicActivationMock : public FakeObject<PeriodicActivationMock> {
 public:
  /**
   * @brief Mock method for simulating the wait operation.
   * @return The result of the wait operation.
   */
  MOCK_METHOD(uint64_t, Wait, (), ());
};

/**
 * @class PeriodicActivation
 * @brief Fakes the original PeriodicActivation
 */
class PeriodicActivation : public daal::af::trigger::TriggerActivation {
 public:
  /**
   * @brief Constructs a PeriodicActivation object with the specified period.
   * @param period The period between activations.
   */
  PeriodicActivation(std::chrono::nanoseconds period) : period_{period} {}

  /**
   * @brief Maps the original Wait call to fake object.
   * @return The result of the wait operation of the Fake object.
   */
  uint64_t Wait() override {
    return FakeObject<PeriodicActivationMock>::GetFakeObject()->Wait();
  };

 private:
  std::chrono::nanoseconds period_; /**< The period between activations. */
};



} // namespace trigger

} // namespace af

} // namespace daal

#endif /* APPLICATION_COMMON_DAAL_SAFE_RUNNER_TEST_MOCKS_LOCAL_TRIGGER_TRIGGER_ACTIVATION_IMPL_H_ \
        */
