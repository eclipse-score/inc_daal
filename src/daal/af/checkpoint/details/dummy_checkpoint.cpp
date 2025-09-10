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

#include "dummy_checkpoint.hpp"

#include "daal/log/framework_logger.hpp"

namespace daal {
namespace af {
namespace monitoring {

DummyCheckpoint::DummyCheckpoint(std::string name, daal::af::checkpoint::When when)
    : daal::af::checkpoint::ICheckpoint(), name_{name}, when_{when} {
  auto when_str = when_ == daal::af::checkpoint::When::BEFORE ? "BEFORE" : "AFTER";
  daal::log::FrameworkLogger::get()->Info("DummyCheckpoint::DummyCheckpoint() {} {}", name_, when_str);
}

auto DummyCheckpoint::GetName() const noexcept -> const std::string& { return name_; }

auto DummyCheckpoint::GetWhen() const noexcept -> daal::af::checkpoint::When { return when_; }

auto DummyCheckpoint::Trigger() -> std::error_code {
  daal::log::FrameworkLogger::get()->Info("DummyCheckpoint::Trigger()");
  return {};
}

}  // namespace monitoring
}  // namespace af
}  // namespace daal
