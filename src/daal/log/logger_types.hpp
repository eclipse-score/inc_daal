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

#ifndef SRC_DAAL_LOG_LOGGER_TYPES_H_
#define SRC_DAAL_LOG_LOGGER_TYPES_H_

#include <array>
#include <cstdint>
#include <memory>

namespace daal {
namespace log {

namespace config {
/** Maximum length of a formatted log message including '\0' at the end. */
constexpr std::size_t kMaxLogMessageBufferLength{200};

/** Maximum number of sinks for each logging facility. */
constexpr std::size_t kMaxSinks{4};
}  // namespace config

/** Type for message buffer. */
using MessageBuffer = std::array<char, config::kMaxLogMessageBufferLength>;

class Sink;

/** Type for list of sinks. */
using Sinks = std::array<std::shared_ptr<Sink>, config::kMaxSinks>;

/** Definition of logging severity levels. */
enum class LogLevel : std::uint8_t {
  kUndefined = 0,
  kVerbose,
  kDebug,
  kInfo,
  kWarning,
  kError,
  kCritical,
  kFatal,
  kMax,  // last entry, always!
};

/** @brief Convert logging severity levels to strings. */
const inline char *GetLevelName(const LogLevel level) {
  switch (level) {
    case LogLevel::kUndefined:
      return "UNDEFINED";
    case LogLevel::kVerbose:
      return "VERBOSE";
    case LogLevel::kDebug:
      return "DEBUG";
    case LogLevel::kInfo:
      return "INFO";
    case LogLevel::kWarning:
      return "WARNING";
    case LogLevel::kError:
      return "ERROR";
    case LogLevel::kCritical:
      return "CRITICAL";
    case LogLevel::kFatal:
      return "FATAL";
    case LogLevel::kMax:
      return "DISABLED";
    default:
      return "UNKNOWN";
  }
}

/** Definition of logging sensitivity classification. */
enum class LogSensitivity : uint8_t { kSensitive = 0, kNonSensitive };

}  // namespace log
}  // namespace daal

#endif  // SRC_DAAL_LOG_LOGGER_TYPES_H_
