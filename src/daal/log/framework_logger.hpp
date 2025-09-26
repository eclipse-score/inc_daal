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

#ifndef SRC_DAAL_LOG_FRAMEWORK_LOGGER_H_
#define SRC_DAAL_LOG_FRAMEWORK_LOGGER_H_

#include "daal/log/logger.hpp"

namespace daal {
namespace log {

/**
 * @brief Global framework logger.
 *
 * This implements a singleton logger instance that is used in the framework
 * code to log messages without the need to create lots of logger instances in
 * various places.
 *
 */
class FrameworkLogger {
 public:
  FrameworkLogger(const FrameworkLogger& other) = delete;
  FrameworkLogger(FrameworkLogger&& other) noexcept = delete;
  FrameworkLogger& operator=(const FrameworkLogger& other) = delete;
  FrameworkLogger& operator=(FrameworkLogger&& other) noexcept = delete;

  static std::shared_ptr<daal::log::Logger> get() {
    static std::shared_ptr<daal::log::Logger> instance = [] {
      auto logger = std::make_shared<daal::log::Logger>("DAAL_");
      logger->AddDefaultSinks();
      return logger;
    }();
    return instance;
  };

 private:
  FrameworkLogger() = default;
  ~FrameworkLogger() = default;
};

}  // namespace log
}  // namespace daal

#endif  // SRC_DAAL_LOG_FRAMEWORK_LOGGER_H_
