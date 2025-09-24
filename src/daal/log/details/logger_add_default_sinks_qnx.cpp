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
#include "daal/log/logger.hpp"

namespace daal {
namespace log {

bool Logger::AddDefaultSinks() {
  bool ret{true};

  ret &= AddSink(std::make_shared<ConsoleSink>(ConsoleSink()));

  return ret;
}
}  // namespace log
}  // namespace daal
