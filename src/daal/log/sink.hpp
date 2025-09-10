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

#ifndef SRC_DAAL_LOG_SINK_H_
#define SRC_DAAL_LOG_SINK_H_

#include <fmt/format.h>

#include "daal/log/config/logger_config.hpp"
#include "daal/log/logger_types.hpp"

namespace daal {
namespace log {

/* Forward declaration. */
class Logger;

/**
 * @brief Abstract interface for sink implementation.
 */
class Sink {
 public:
  Sink() = default;
  virtual ~Sink() = default;
  Sink(const Sink &other) = default;
  Sink(Sink &&other) noexcept = default;
  Sink &operator=(const Sink &other) = default;
  Sink &operator=(Sink &&other) noexcept = default;

  /**
   * @brief Method called by the logger facility to show the buffer.
   * \attention Concrete implementations must respect log_level_ and is_enabled_
   */
  virtual void ShowBuffer(LogLevel log_level, const MessageBuffer &buffer) = 0;

  /**
   * @brief Method called by the logging facility to ensure that all buffers are
   * flushed to their destination.
   */
  virtual void Flush() = 0;

  /**
   * @brief Register logger for callbacks.
   */
  void RegisterLogger(const std::shared_ptr<Logger> &logger, std::string &context);

  /**
   * @brief Get the context of this sink.
   */
  const std::string &GetContext() const;

  /**
   * @brief Set the log level of this sink.
   */
  void SetLogLevel(LogLevel log_level);

  /**
   * @brief Get the log level of this sink.
   */
  LogLevel GetLogLevel() const;

  /**
   * @brief Enable this sink.
   */
  void Enable();

  /**
   * @brief Disable this sink.
   */
  void Disable();

  /**
   * @brief Check whether this sink is enabled.
   */
  bool IsEnabled() const;

  /**
   * @brief Check whether a message of the given log level would be shown.
   */
  bool WouldShow(LogLevel log_level) const;

 private:
  /** Context of this logger. */
  std::string context_;

  /** Log level of this sink. Messages of this or higher severity will be shown.
   */
  LogLevel log_level_{config::kLimitLogLevel};

  /** Flag whether this sink is enabled. */
  bool is_enabled_{true};

  std::shared_ptr<Logger> logger_;
};

}  // namespace log
}  // namespace daal

#endif  // SRC_DAAL_LOG_SINK_H_
