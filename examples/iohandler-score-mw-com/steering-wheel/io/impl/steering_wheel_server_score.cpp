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

#include "steering_wheel_server_score.hpp"

#include <cstring>

#include "score/mw/com/runtime.h"

using namespace score::mw::log;
using namespace score::mw::com;

namespace daal {
namespace examples {

SteeringWheelServerScore::SteeringWheelServerScore() {
  const auto instance_specifier_result = create_instance_specifier("/score/vss/steering/front_request");
  assert(instance_specifier_result.has_value() && "Failed to create instance specifier");
  instance_specifier_ = instance_specifier_result.value();
}

daal::af::app_base::IoHandler::ConnectionState SteeringWheelServerScore::Start() {
  auto handle_result = SearchForService<SteeringRequestProxy>(instance_specifier_.value());
  if (!handle_result.has_value()) {
    score::mw::log::LogError() << "Unable to find service: " << instance_specifier_.value().ToString()
                               << ". Failed with error: " << handle_result.error() << ", bailing!\n";
    SetConnectionState(ConnectionState::kOngoing);
    return ConnectionState::kOngoing;
  }
  auto handle = handle_result.value();

  auto proxy_result = SteeringRequestProxy::Create(std::move(handle));
  if (!proxy_result.has_value()) {
    score::mw::log::LogError() << "Unable to construct proxy: " << proxy_result.error() << ", bailing!\n";
    return ConnectionState::kDisconnected;
  }
  proxy_ = std::move(proxy_result.value());

  // Subscribe to hello messages
  proxy_->SteeringRequest.Subscribe(1);

  SetConnectionState(ConnectionState::kConnected);
  return ConnectionState::kConnected;
}

void SteeringWheelServerScore::Stop() {
  // Unsubscribe and clean up proxy if it exists
  if (proxy_.has_value()) {
    proxy_->SteeringRequest.Unsubscribe();
    proxy_.reset();
  }
}

void SteeringWheelServerScore::PrepareStep() {
  // TODO: check handle for connection state and set it to kDisconnected
  proxy_->SteeringRequest.GetNewSamples(
      [this](auto recv) {
        const daal::examples::spec::SteeringRequest& msg = *recv;
        std::memcpy(&cache_, &msg, sizeof(daal::examples::spec::SteeringRequest));
      },
      10);
}

const daal::examples::spec::SteeringRequest& SteeringWheelServerScore::GetSteeringRequest() const { return cache_; }

}  // namespace examples
}  // namespace daal
