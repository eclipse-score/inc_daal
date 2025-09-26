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

#include "sink.hpp"

#include "logger.hpp"

namespace daal {
namespace log {

void Sink::RegisterLogger(const std::shared_ptr<Logger>& logger, std::string& context) {
  logger_ = logger;
  context_ = context;
}

void Sink::SetLogLevel(LogLevel log_level) {
  log_level_ = log_level;
  if (logger_) {
    logger_->UpdateSinkLimits();
  }
}

const std::string& Sink::GetContext() const { return context_; }

LogLevel Sink::GetLogLevel() const { return log_level_; }

void Sink::Enable() { is_enabled_ = true; }

void Sink::Disable() { is_enabled_ = false; }

bool Sink::IsEnabled() const { return is_enabled_; }

bool Sink::WouldShow(LogLevel log_level) const {
  return IsEnabled() &&                          //
         log_level >= config::kLimitLogLevel &&  //
         log_level >= log_level_;
}

}  // namespace log
}  // namespace daal
