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

#include "steering_wheel_app.hpp"

namespace daal {

daal::af::app_base::MethodState SteeringWheelApp::OnInitialize() {
  logger_->Info("Ready to start.");
  count_ = 0;

  return daal::af::app_base::MethodState::kSuccessful;
}

daal::af::app_base::MethodState SteeringWheelApp::OnStart(daal::examples::SteeringWheelIoContainer &io) {
  logger_->Debug("app started");
  return daal::af::app_base::MethodState::kSuccessful;
}

daal::af::app_base::MethodState SteeringWheelApp::Step(daal::examples::SteeringWheelIoContainer &io) {
  logger_->Debug("Step execution {}", count_);
  count_++;

  if (io.SteeringWheelServer().GetConnectionState() == daal::af::app_base::IoHandler::ConnectionState::kConnected) {
    logger_->Info("SteeringWheelServer not connected, skipping step.");
    auto request = io.SteeringWheelServer().GetSteeringRequest();
    logger_->Info(
        "Received Steering Request - Angle: {}, Angle Mode: {}, Torque Offset: {}, Torque Offset Mode: {}, Torque: {}, "
        "Torque Mode: {}",
        request.AngleTarget, static_cast<int>(request.AngleTargetMode), request.TorqueOffsetTarget,
        static_cast<int>(request.TorqueOffsetTargetMode), request.TorqueTarget,
        static_cast<int>(request.TorqueTargetMode));
  }

  return daal::af::app_base::MethodState::kSuccessful;
}

daal::af::app_base::MethodState SteeringWheelApp::OnStop(daal::examples::SteeringWheelIoContainer &io) {
  logger_->Debug("Prepared for Terminating");
  return daal::af::app_base::MethodState::kSuccessful;
}

daal::af::app_base::MethodState SteeringWheelApp::OnTerminate() {
  count_ = 0;
  logger_->Debug("Ready to terminate.");
  return daal::af::app_base::MethodState::kSuccessful;
}

}  // namespace daal
