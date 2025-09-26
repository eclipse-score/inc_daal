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

#ifndef EXAMPLES_IOHANDLER_SCORE_MW_COM_STEERING_WHEEL_IO_IMPL_STEERING_WHEEL_CLIENT_SCORE_HPP_
#define EXAMPLES_IOHANDLER_SCORE_MW_COM_STEERING_WHEEL_IO_IMPL_STEERING_WHEEL_CLIENT_SCORE_HPP_

#include "daal/af/score/mw_com_common.hpp"
#include "io/steering_wheel_client.hpp"
#include "spec/impl/score_mw_com.hpp"

namespace daal {
namespace examples {

class SteeringWheelClientScore : public SteeringWheelClient {
 public:
  SteeringWheelClientScore();
  ~SteeringWheelClientScore() = default;

  ConnectionState Start() override;
  void Stop() override;

  void PrepareStep() override;
  void FinalizeStep() override;

  void SetAngleTarget(const std::uint16_t value, const std::uint8_t mode) override {
    cache_.AngleTarget = value;
    cache_.AngleTargetMode = mode;
  }
  void SetTorqueOffsetTarget(const std::uint16_t value, const std::uint8_t mode) override {
    cache_.TorqueOffsetTarget = value;
    cache_.TorqueOffsetTargetMode = mode;
  }
  void SetTorqueTarget(const std::uint16_t value, const std::uint8_t mode) override {
    cache_.TorqueTarget = value;
    cache_.TorqueTargetMode = mode;
  }

 private:
  score::cpp::optional<score::mw::com::InstanceSpecifier> instance_specifier_;
  std::optional<SteeringRequestSkeleton> skeleton_;
  spec::SteeringRequest cache_;  // TODO: really use zero-copy here, return reference to data
};

}  // namespace examples
}  // namespace daal

#endif  // EXAMPLES_IOHANDLER_SCORE_MW_COM_STEERING_WHEEL_IO_IMPL_STEERING_WHEEL_CLIENT_SCORE_HPP_
