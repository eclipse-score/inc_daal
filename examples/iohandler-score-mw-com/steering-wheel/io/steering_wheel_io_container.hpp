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

#ifndef EXAMPLES_IOHANDLER_SCORE_MW_COM_STEERING_WHEEL_IO_STEERING_WHEEL_CONTAINER_HPP_
#define EXAMPLES_IOHANDLER_SCORE_MW_COM_STEERING_WHEEL_IO_STEERING_WHEEL_CONTAINER_HPP_

#include "steering_wheel_server.hpp"

namespace daal {
namespace examples {

class SteeringWheelIoContainer : public daal::af::app_base::IoHandlerContainer {
 public:
  SteeringWheelIoContainer(daal::examples::SteeringWheelServer &server)
      : daal::af::app_base::IoHandlerContainer({server}) {}
  ~SteeringWheelIoContainer() = default;

  daal::examples::SteeringWheelServer &SteeringWheelServer() const {
    return static_cast<daal::examples::SteeringWheelServer &>(handlers_[0].get());
  }
};

}  // namespace examples
}  // namespace daal

#endif  // EXAMPLES_IOHANDLER_SCORE_MW_COM_STEERING_WHEEL_IO_STEERING_WHEEL_CONTAINER_HPP_
