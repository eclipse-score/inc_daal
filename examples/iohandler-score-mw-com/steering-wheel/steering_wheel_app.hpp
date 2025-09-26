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

#pragma once

// DAAL dependencies
#include <daal/af/app_base/iohandler.hpp>
#include <daal/log/logger.hpp>

// application-specific IO handlers
#include "io/steering_wheel_io_container.hpp"

namespace daal {

class SteeringWheelApp
    : public daal::af::app_base::SafeApplicationBaseWithIo<daal::examples::SteeringWheelIoContainer> {
 public:
  SteeringWheelApp(daal::examples::SteeringWheelIoContainer &io_container, std::shared_ptr<daal::log::Logger> logger)
      : daal::af::app_base::SafeApplicationBaseWithIo<daal::examples::SteeringWheelIoContainer>(io_container),
        logger_{logger} {}
  ~SteeringWheelApp() = default;

  daal::af::app_base::MethodState OnInitialize() override;
  daal::af::app_base::MethodState OnStart(daal::examples::SteeringWheelIoContainer &io) override;
  daal::af::app_base::MethodState Step(daal::examples::SteeringWheelIoContainer &io) override;
  daal::af::app_base::MethodState OnStop(daal::examples::SteeringWheelIoContainer &io) override;
  daal::af::app_base::MethodState OnTerminate() override;

 private:
  unsigned int count_{};
  std::shared_ptr<daal::log::Logger> logger_;
};

}  //  namespace daal
