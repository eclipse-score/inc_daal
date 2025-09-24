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

#ifndef EXAMPLES_IOHANDLER_SCORE_MW_COM_STEERING_WHEEL_IO_STEERING_WHEEL_CLIENT_HPP_
#define EXAMPLES_IOHANDLER_SCORE_MW_COM_STEERING_WHEEL_IO_STEERING_WHEEL_CLIENT_HPP_

#include <cstdint>

#include "daal/af/app_base/iohandler.hpp"
#include "spec/steering_request.hpp"

namespace daal {
namespace examples {

class SteeringWheelClient : public daal::af::app_base::IoHandler {
 public:
  SteeringWheelClient() = default;
  ~SteeringWheelClient() = default;

  virtual void SetAngleTarget(const std::uint16_t value, const std::uint8_t mode) = 0;
  virtual void SetTorqueOffsetTarget(const std::uint16_t value, const std::uint8_t mode) = 0;
  virtual void SetTorqueTarget(const std::uint16_t value, const std::uint8_t mode) = 0;
};

}  // namespace examples
}  // namespace daal

#endif  // EXAMPLES_IOHANDLER_SCORE_MW_COM_STEERING_WHEEL_IO_STEERING_WHEEL_CLIENT_HPP_
