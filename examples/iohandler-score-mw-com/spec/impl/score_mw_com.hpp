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

#include "score/mw/com/impl/instance_specifier.h"
#include "score/mw/com/types.h"
#include "score/result/result.h"
#include "spec/steering_request.hpp"

namespace daal {
namespace examples {
namespace spec {

template <typename Trait>
class IpcBridgeInterface : public Trait::Base {
 public:
  using Trait::Base::Base;

  typename Trait::template Event<SteeringRequest> SteeringRequest{*this, "steering_request"};
};

}  // namespace spec
}  // namespace examples
}  // namespace daal

using SteeringRequestProxy = score::mw::com::AsProxy<daal::examples::spec::IpcBridgeInterface>;
using SteeringRequestSkeleton = score::mw::com::AsSkeleton<daal::examples::spec::IpcBridgeInterface>;
