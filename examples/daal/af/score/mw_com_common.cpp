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

#include "mw_com_common.hpp"

#include <chrono>
#include <score/assert.hpp>
#include <score/hash.hpp>
#include <score/optional.hpp>
#include <thread>

#include "score/concurrency/notification.h"
#include "score/mw/com/impl/generic_proxy.h"
#include "score/mw/com/impl/generic_proxy_event.h"
#include "score/mw/com/impl/handle_type.h"
#include "score/mw/com/impl/proxy_event.h"

using namespace score::mw::com;
using namespace score::mw::log;
using namespace std::chrono_literals;

score::Result<score::mw::com::InstanceSpecifier> create_instance_specifier(const std::string& name) {
  const auto instance_specifier_result = InstanceSpecifier::Create(name.c_str());
  if (!instance_specifier_result.has_value()) {
    score::mw::log::LogError() << "Unable to create instance specifier: " << instance_specifier_result.error()
                               << ", bailing!";
    return instance_specifier_result;
  }

  score::mw::log::LogDebug() << "Instance specifier created: " << instance_specifier_result.value().ToString();
  return instance_specifier_result;
}
