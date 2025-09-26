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

#ifndef EXAMPLES_IOHANDLER_SCORE_MW_COM_STEERING_WHEEL_IO_IMPL_STEERING_WHEEL_SERVER_SCORE_HPP_
#define EXAMPLES_IOHANDLER_SCORE_MW_COM_STEERING_WHEEL_IO_IMPL_STEERING_WHEEL_SERVER_SCORE_HPP_

#include "daal/af/score/mw_com_common.hpp"
#include "io/steering_wheel_server.hpp"
#include "spec/impl/score_mw_com.hpp"

namespace daal {
namespace examples {

class SteeringWheelServerScore : public SteeringWheelServer {
 public:
  SteeringWheelServerScore();
  ~SteeringWheelServerScore() = default;

  ConnectionState Start() override;
  void Stop() override;

  void PrepareStep() override;
  void FinalizeStep() override {}

  const daal::examples::spec::SteeringRequest& GetSteeringRequest() const override;

 private:
  score::cpp::optional<score::mw::com::InstanceSpecifier> instance_specifier_;
  score::cpp::optional<SteeringRequestProxy> proxy_;
  spec::SteeringRequest cache_;  // TODO: really use zero-copy here, return reference to data
};

}  // namespace examples
}  // namespace daal

#endif  // EXAMPLES_IOHANDLER_SCORE_MW_COM_STEERING_WHEEL_IO_IMPL_STEERING_WHEEL_SERVER_SCORE_HPP_
