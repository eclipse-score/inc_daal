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

#include "steering_wheel_client_score.hpp"

#include <cstring>

#include "daal/af/score/mw_com_common.hpp"
#include "score/mw/com/runtime.h"

using namespace score::mw::log;
using namespace score::mw::com;

namespace daal {
namespace examples {

SteeringWheelClientScore::SteeringWheelClientScore() {}

daal::af::app_base::IoHandler::ConnectionState SteeringWheelClientScore::Start() {
  // Active initialization here
  score::mw::log::LogDebug() << "Application data initialize";
  const auto instance_specifier_result = create_instance_specifier("/score/vss/steering/front_request");
  if (!instance_specifier_result.has_value()) {
    return ConnectionState::kDisconnected;
  }
  const auto &instance_specifier = instance_specifier_result.value();
  auto create_result = SteeringRequestSkeleton::Create(instance_specifier);
  if (!create_result.has_value()) {
    score::mw::log::LogError() << "Unable to construct skeleton: " << create_result.error() << ", bailing!\n";
    return ConnectionState::kDisconnected;
  } else {
    score::mw::log::LogDebug() << "SteeringRequestSkeleton created successfully created skeleton.";
  }
  skeleton_ = std::move(create_result.value());

  const auto offer_result = skeleton_->OfferService();
  if (!offer_result.has_value()) {
    score::mw::log::LogError() << "Unable to offer service: " << offer_result.error() << ", bailing!\n";
    return ConnectionState::kDisconnected;
  } else {
    score::mw::log::LogDebug() << "SteeringRequestSkeleton offered service successfully.";
  }

  SetConnectionState(ConnectionState::kConnected);
  return ConnectionState::kConnected;
}

void SteeringWheelClientScore::Stop() {
  // Stop the service offering if it was started
  if (skeleton_.has_value()) {
    skeleton_->StopOfferService();
    skeleton_.reset();
  }
}

void SteeringWheelClientScore::PrepareStep() {
  // nothing to do here, we don't need to read something
}

void SteeringWheelClientScore::FinalizeStep() {
  if (skeleton_.has_value()) {
    daal::examples::spec::SteeringRequest msg{.AngleTarget = cache_.AngleTarget,
                                              .AngleTargetMode = cache_.AngleTargetMode,
                                              .TorqueOffsetTarget = cache_.TorqueOffsetTarget,
                                              .TorqueOffsetTargetMode = cache_.TorqueOffsetTargetMode,
                                              .TorqueTarget = cache_.TorqueTarget,
                                              .TorqueTargetMode = cache_.TorqueTargetMode};
    skeleton_->SteeringRequest.Send(msg);
  } else {
    LogError() << "Skeleton is not available, cannot send hello message.";
  }
}

}  // namespace examples
}  // namespace daal
