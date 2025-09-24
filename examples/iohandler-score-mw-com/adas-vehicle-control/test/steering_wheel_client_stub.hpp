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

#ifndef EXAMPLES_IOHANDLER_SCORE_MW_COM_ADAS_VEHICLE_CONTROL_TEST_STEERING_WHEEL_CLIENT_FAKE_HPP_
#define EXAMPLES_IOHANDLER_SCORE_MW_COM_ADAS_VEHICLE_CONTROL_TEST_STEERING_WHEEL_CLIENT_FAKE_HPP_

#include "io/steering_wheel_client.hpp"

namespace daal {
namespace examples {

class SteeringWheelClientStub : public SteeringWheelClient {
 public:
  SteeringWheelClientStub() = default;
  ~SteeringWheelClientStub() = default;

  ConnectionState Start() override {
    SetConnectionState(ConnectionState::kConnected);
    return GetConnectionState();
  }
  void Stop() override {}

  void PrepareStep() override {}
  void FinalizeStep() override {}

  void SetAngleTarget(const std::uint16_t value, const std::uint8_t mode) override {}
  void SetTorqueOffsetTarget(const std::uint16_t value, const std::uint8_t mode) override {}
  void SetTorqueTarget(const std::uint16_t value, const std::uint8_t mode) override {}
};

}  // namespace examples
}  // namespace daal

#endif  // EXAMPLES_IOHANDLER_SCORE_MW_COM_ADAS_VEHICLE_CONTROL_TEST_STEERING_WHEEL_CLIENT_FAKE_HPP_
