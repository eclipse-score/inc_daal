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

#include "vehicle_control_app.hpp"

#include <cstdint>
#include <iostream>
#include <limits>
#include <random>

namespace daal {

// adapted from https://stackoverflow.com/a/20136256
template <typename T>
T generate_random() {
  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_int_distribution<T> distr(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
  return distr(generator);
}

daal::af::app_base::MethodState VehicleControlApp::OnInitialize() {
  logger_->Info("Ready to start.");
  return daal::af::app_base::MethodState::kSuccessful;
}

daal::af::app_base::MethodState VehicleControlApp::OnStart(daal::examples::VehicleControlIoContainer &io) {
  logger_->Debug("app started");
  return daal::af::app_base::MethodState::kSuccessful;
}

daal::af::app_base::MethodState VehicleControlApp::Step(daal::examples::VehicleControlIoContainer &io) {
  logger_->Debug("Step execution {}", count_);
  count_++;

  // sending some random steering request
  if (io.SteeringWheelClient().GetConnectionState() == daal::af::app_base::IoHandler::ConnectionState::kConnected) {
    io.SteeringWheelClient().SetAngleTarget(generate_random<std::int16_t>(), 1);
    io.SteeringWheelClient().SetTorqueOffsetTarget(generate_random<std::int16_t>(), 1);
    io.SteeringWheelClient().SetTorqueTarget(generate_random<std::int16_t>(), 1);
  }

  return daal::af::app_base::MethodState::kSuccessful;
}

daal::af::app_base::MethodState VehicleControlApp::OnStop(daal::examples::VehicleControlIoContainer &io) {
  logger_->Debug("Prepared for Terminating");
  return daal::af::app_base::MethodState::kSuccessful;
}

daal::af::app_base::MethodState VehicleControlApp::OnTerminate() {
  count_ = 0;
  logger_->Debug("Ready to terminate.");
  return daal::af::app_base::MethodState::kSuccessful;
}

//! [class definition]

}  // namespace daal
