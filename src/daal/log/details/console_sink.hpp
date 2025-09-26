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

#ifndef SRC_DAAL_LOG_DETAILS_CONSOLESINK_H_
#define SRC_DAAL_LOG_DETAILS_CONSOLESINK_H_

#include "daal/log/sink.hpp"

namespace daal {
namespace log {

/**
 * @brief Sink implementation that prints messages to the console.
 */
class ConsoleSink : public Sink {
 public:
  ConsoleSink() = default;
  ~ConsoleSink() override = default;
  ConsoleSink(const ConsoleSink &other) = default;
  ConsoleSink(ConsoleSink &&other) noexcept = default;
  ConsoleSink &operator=(const ConsoleSink &other) = default;
  ConsoleSink &operator=(ConsoleSink &&other) noexcept = default;

  /**
   * @brief Method called by the logger facility to show the buffer.
   */
  void ShowBuffer(LogLevel log_level, const MessageBuffer &buffer) override;

  /**
   * @brief Method called by the logging facility to ensure that all buffers are
   * flushed to their destination.
   */
  void Flush() override;
};

}  // namespace log
}  // namespace daal

#endif  // SRC_DAAL_LOG_DETAILS_CONSOLESINK_H_
