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

#ifndef SRC_DAAL_LOG_LOGGER_H_
#define SRC_DAAL_LOG_LOGGER_H_

#include <fmt/format.h>

#include <memory>

#include "daal/log/config/logger_config.hpp"
#include "daal/log/logger_types.hpp"

namespace daal {
namespace log {

/* Forward declaration. */
class Sink;

/**
 * @brief Logging facility.
 *
 * This logging facility provides an easy to use interface for logging message to a set of sinks. It provides methods
 * for each logging level that take a format string and arguments conforming to the std::print(). The messages are shown
 * on the registered sinks. There is the method addSinks() to register custom sinks and the method addDefaultSinks() to
 * register a set of predefined sinks.
 * The facility can be enabled(), disabled() and the current state can be checked using isEnabled(). Furthermore it is
 * possible to check if a message of a given log level would be shown. This is useful to do time consuming tasks only if
 * the result of the calculations would be shown at all.
 *
 */
class Logger : public std::enable_shared_from_this<Logger> {
 public:
  Logger() = delete;
  explicit Logger(const std::string &context);
  ~Logger() = default;
  Logger(const Logger &other) = default;
  Logger(Logger &&other) noexcept = default;
  Logger &operator=(const Logger &other) = default;
  Logger &operator=(Logger &&other) noexcept = default;

  /**
   * @brief Add a sink to the list of sinks.
   */
  bool AddSink(const std::shared_ptr<Sink> &sink);

  /**
   * @brief Add default sinks.
   *
   * Currently this adds a sink that prints messages to the console.
   */
  bool AddDefaultSinks();

  /**
   * @brief Request to update minimal severity over all sinks.
   */
  void UpdateSinkLimits();

  /**
   * @brief Enable the logging facility.
   */
  void Enable();

  /**
   * @brief Disable the logging facility.
   */
  void Disable();

  /**
   * @brief Check whether the logging facility is enabled.
   */
  bool IsEnabled() const;

  /**
   * @brief Check whether a message of the given log level would be shown.
   */
  bool WouldShow(LogLevel log_level) const;

  /**
   * @brief Flush all log messages on all registered sinks.
   */
  void Flush();

  /**
   * @brief Show a message of severity 'fatal' to all registered sinks.
   *
   * Calls to this method are removed by the compiler if the compile time constant daal::log::config::kLimitLogLevel is
   * LogLevel::Fatal or if logging is not desired due to sensitivity considerations.
   *
   * \note Sensitive messages must be explicitly marked as such by specifying the template parameter
   *       LogSensitivity::kSensitive!
   */
  template <LogSensitivity LogSensitivity = LogSensitivity::kNonSensitive, typename... T>
  void Fatal(fmt::format_string<T...> fmt, T &&...args) {
    LogInternal<LogLevel::kFatal, LogSensitivity>(fmt, std::forward<T>(args)...);
  }

  /**
   * @brief Show a message of severity 'critical' to all registered sinks.
   *
   * Calls to this method are removed by the compiler if the compile time constant daal::log::config::kLimitLogLevel is
   * LogLevel::Critical or if logging is not desired due to sensitivity considerations.
   *
   * \note Sensitive messages must be explicitly marked as such by specifying the template parameter
   *       LogSensitivity::kSensitive!
   */
  template <LogSensitivity LogSensitivity = LogSensitivity::kNonSensitive, typename... T>
  void Critical(fmt::format_string<T...> fmt, T &&...args) {
    LogInternal<LogLevel::kCritical, LogSensitivity>(fmt, std::forward<T>(args)...);
  }

  /**
   * @brief Show a message of severity 'error' to all registered sinks.
   *
   * Calls to this method are removed by the compiler if the compile time constant daal::log::config::kLimitLogLevel is
   * LogLevel::Errir or if logging is not desired due to sensitivity considerations.
   *
   * \note Sensitive messages must be explicitly marked as such by specifying the template parameter
   *       LogSensitivity::kSensitive!
   */
  template <LogSensitivity LogSensitivity = LogSensitivity::kNonSensitive, typename... T>
  void Error(fmt::format_string<T...> fmt, T &&...args) {
    LogInternal<LogLevel::kError, LogSensitivity>(fmt, std::forward<T>(args)...);
  }

  /**
   * @brief Show a message of severity 'warning' to all registered sinks.
   *
   * Calls to this method are removed by the compiler if the compile time constant daal::log::config::kLimitLogLevel is
   * LogLevel::Warning or higher or if logging is not desired due to sensitivity considerations.
   *
   * \note Sensitive messages must be explicitly marked as such by specifying the template parameter
   *       LogSensitivity::kSensitive!
   */
  template <LogSensitivity LogSensitivity = LogSensitivity::kNonSensitive, typename... T>
  void Warning(fmt::format_string<T...> fmt, T &&...args) {
    LogInternal<LogLevel::kWarning, LogSensitivity>(fmt, std::forward<T>(args)...);
  }

  /**
   * @brief Show a message of severity 'info' to all registered sinks.
   *
   * Calls to this method are removed by the compiler if the compile time constant daal::log::config::kLimitLogLevel is
   * LogLevel::Info or higher or if logging is not desired due to sensitivity considerations.
   *
   * \note Sensitive messages must be explicitly marked as such by specifying the template parameter
   *       LogSensitivity::kSensitive!
   */
  template <LogSensitivity LogSensitivity = LogSensitivity::kNonSensitive, typename... T>
  void Info(fmt::format_string<T...> fmt, T &&...args) {
    LogInternal<LogLevel::kInfo, LogSensitivity>(fmt, std::forward<T>(args)...);
  }

  /**
   * @brief Show a message of severity 'debug' to all registered sinks.
   *
   * Calls to this method are removed by the compiler if the compile time constant daal::log::config::kLimitLogLevel is
   * LogLevel::Debug or higher or if logging is not desired due to sensitivity considerations.
   *
   * \note Sensitive messages must be explicitly marked as such by specifying the template parameter
   *       LogSensitivity::kSensitive!
   */
  template <LogSensitivity LogSensitivity = LogSensitivity::kNonSensitive, typename... T>
  void Debug(fmt::format_string<T...> fmt, T &&...args) {
    LogInternal<LogLevel::kDebug, LogSensitivity>(fmt, std::forward<T>(args)...);
  }

  /**
   * @brief Show a message of severity 'verbose' to all registered sinks.
   *
   * Calls to this method are removed by the compiler if the compile time constant daal::log::config::kLimitLogLevel is
   * LogLevel::Verbose or higher or if logging is not desired due to sensitivity considerations.
   *
   * \note Sensitive messages must be explicitly marked as such by specifying the template parameter
   *       LogSensitivity::kSensitive!
   */
  template <LogSensitivity LogSensitivity = LogSensitivity::kNonSensitive, typename... T>
  void Verbose(fmt::format_string<T...> fmt, T &&...args) {
    LogInternal<LogLevel::kVerbose, LogSensitivity>(fmt, std::forward<T>(args)...);
  }

 private:
  /** Static message buffer that is used by libfmt to generate the formatted log message. */
  MessageBuffer buffer_{};

  /** List of registered sinks. */
  Sinks sinks_;

  /** Index where the next registered sink would be added to the list of sinks. */
  std::size_t sinks_insert_idx_{0};

  /** Minimal severity over all sinks. */
  LogLevel limit_of_all_sinks_{LogLevel::kMax};

  /** Flag whether the logging facility is enabled. */
  bool is_enabled_{true};

  /** Context of this logger. */
  std::string context_;

  /**
   * @brief Show the given buffer on all registered sinks.
   */
  void ShowBuffer(LogLevel log_level, const MessageBuffer &buffer);

  /**
   * @brief Determine if logging of the given severity and sensitivity is desired.
   */
  static inline constexpr bool IsLoggingDesired(const LogLevel log_level, const LogSensitivity type) {
    return ((log_level >= config::kLimitLogLevel) &&
            ((type == LogSensitivity::kNonSensitive) || !daal::af::config::kIsProductionBuild));
  }

  /**
   * @brief Method formatting the log message and showing it to on the registered sinks.
   */
  template <LogLevel LogLevel, LogSensitivity LogSensitivity, typename... T>
  inline typename std::enable_if<IsLoggingDesired(LogLevel, LogSensitivity), void>::type LogInternal(
      fmt::format_string<T...> fmt, T &&...args) {
    if (WouldShow(LogLevel)) {
      auto result = fmt::format_to_n(buffer_.begin(), buffer_.size(), fmt, std::forward<T>(args)...);

      const std::size_t kIdx = std::min(result.size, buffer_.size() - 1);
      buffer_[kIdx] = '\0';
      ShowBuffer(LogLevel, buffer_);
    }
  }

  /**
   * @brief Dummy method that removes the logging calls from code if the log level is disabled.
   */
  template <LogLevel LogLevel, LogSensitivity LogSensitivity, typename... T>
  inline typename std::enable_if<!IsLoggingDesired(LogLevel, LogSensitivity), void>::type LogInternal(
      fmt::format_string<T...> fmt, T &&.../*args*/) {}
};

}  // namespace log
}  // namespace daal

#endif  // SRC_DAAL_LOG_LOGGER_H_
