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

#ifndef EXAMPLES_DAAL_AF_SCORE_MW_COM_COMMON_HPP_
#define EXAMPLES_DAAL_AF_SCORE_MW_COM_COMMON_HPP_

#include <atomic>
#include <chrono>
#include <mutex>
#include <random>
#include <string_view>
#include <vector>

#include "score/mw/com/impl/instance_specifier.h"
#include "score/mw/com/types.h"
#include "score/mw/log/detail/recorder_factory.h"
#include "score/mw/log/recorder.h"
#include "score/result/result.h"

using namespace std::chrono_literals;

enum class ErrorCode : score::result::ErrorCode {
  kServiceNotFound = 0,
};

class CommunicationErrorDomain final : public score::result::ErrorDomain {
 public:
  std::string_view MessageFor(const score::result::ErrorCode& code) const noexcept override final {
    switch (code) {
      case static_cast<score::result::ErrorCode>(ErrorCode::kServiceNotFound):
        return "No service has been found";
      default:
        return "unknown Communication error";
    }
  }
};

score::Result<score::mw::com::InstanceSpecifier> create_instance_specifier(const std::string& name);

template <typename ProxyType>
score::Result<score::mw::com::impl::HandleType> SearchForService(
    const score::mw::com::InstanceSpecifier& instance_specifier) {
  score::mw::log::LogInfo() << instance_specifier.ToString() << ": Running as proxy, looking for services\n";
  score::mw::com::ServiceHandleContainer<score::mw::com::impl::HandleType> handles{};

  auto handles_result = ProxyType::FindService(instance_specifier);
  if (!handles_result.has_value()) {
    return score::MakeUnexpected<score::mw::com::impl::HandleType>(std::move(handles_result.error()));
  }

  if (handles_result.value().size() == 0) {
    static CommunicationErrorDomain errorDomain{};
    return score::MakeUnexpected<score::mw::com::impl::HandleType>(score::result::Error(
        static_cast<score::result::ErrorCode>(ErrorCode::kServiceNotFound), errorDomain, "Service not found"));
  }

  return handles_result.value().front();
}

#endif  // EXAMPLES_DAAL_AF_SCORE_MW_LOG_COMMON_HPP_
