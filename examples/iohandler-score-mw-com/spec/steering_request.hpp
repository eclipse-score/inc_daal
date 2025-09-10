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

#include <cstdint>

// see
// https://github.com/COVESA/vehicle_signal_specification/blob/master/spec/Vehicle/MotionManagement/Steering/SteeringWheel.vspec

namespace daal {
namespace examples {
namespace spec {

struct SteeringRequest {
  std::uint32_t id;  // TODO: remove

  std::int16_t AngleTarget;
  std::uint8_t AngleTargetMode;

  std::int16_t TorqueOffsetTarget;
  std::uint8_t TorqueOffsetTargetMode;

  std::int16_t TorqueTarget;
  std::uint8_t TorqueTargetMode;
};

}  // namespace spec
}  // namespace examples
}  // namespace daal
