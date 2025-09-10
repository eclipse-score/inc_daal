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

#include "console_sink.hpp"

namespace daal {
namespace log {

void ConsoleSink::ShowBuffer(LogLevel log_level, const MessageBuffer &buffer) {
  if (WouldShow(log_level)) {
    fmt::println("[{}][{}] {}", GetContext(), GetLevelName(log_level), buffer.data());
  }
}
void ConsoleSink::Flush() {
  // no need to flush as '\n' in printBuffer already flushes stdout
}

}  // namespace log
}  // namespace daal
