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

#include "logger.hpp"

#include <utility>

#include "sink.hpp"

namespace daal {
namespace log {

Logger::Logger(const std::string &context) : context_{std::move(context)} {}

bool Logger::AddSink(const std::shared_ptr<Sink> &sink) {
  bool ret{true};

  if (sink && sinks_insert_idx_ != sinks_.size()) {
    limit_of_all_sinks_ = std::min(limit_of_all_sinks_, sink->GetLogLevel());
    sink->RegisterLogger(shared_from_this(), context_);
    sinks_[sinks_insert_idx_] = sink;
    sinks_insert_idx_++;
  } else {
    ret = false;
  }

  return ret;
}

void Logger::UpdateSinkLimits() {
  limit_of_all_sinks_ = LogLevel::kMax;
  for (size_t idx = 0; idx != sinks_insert_idx_; idx++) {
    const auto kSink = sinks_[idx];
    if (kSink) {
      limit_of_all_sinks_ = std::min(limit_of_all_sinks_, kSink->GetLogLevel());
    }
  }
}

void Logger::Enable() { is_enabled_ = true; }

void Logger::Disable() { is_enabled_ = false; }

bool Logger::IsEnabled() const { return is_enabled_; }

bool Logger::WouldShow(LogLevel log_level) const {
  return IsEnabled() &&                          //
         log_level >= config::kLimitLogLevel &&  //
         log_level >= limit_of_all_sinks_;
}

void Logger::Flush() {
  for (size_t idx = 0; idx != sinks_insert_idx_; idx++) {
    const auto kSink = sinks_[idx];
    if (kSink) {
      kSink->Flush();
    }
  }
}

void Logger::ShowBuffer(LogLevel log_level, const MessageBuffer &buffer) {
  for (size_t idx = 0; idx != sinks_insert_idx_; idx++) {
    const auto kSink = sinks_[idx];
    if (kSink) {
      kSink->ShowBuffer(log_level, buffer_);
    }
  }
}

}  // namespace log
}  // namespace daal
