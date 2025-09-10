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

#ifndef SRC_DAAL_LOG_CONFIG_DEBUG_LOGGER_CONFIG_H_
#define SRC_DAAL_LOG_CONFIG_DEBUG_LOGGER_CONFIG_H_

#include "daal/af/config/config.hpp"
#include "daal/log/logger_types.hpp"

namespace daal {
namespace log {
namespace config {

/** Compile time lower bound of logging severity level. Calls to logging methods below this level will be removed from
 * the code at compile time. */
constexpr LogLevel kLimitLogLevel{LogLevel::kDebug};

}  // namespace config
}  // namespace log
}  // namespace daal

#endif  // SRC_DAAL_LOG_CONFIG_DEBUGLOGGER_CONFIG_H_
