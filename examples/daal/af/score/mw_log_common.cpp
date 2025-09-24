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

#include "mw_com_common.hpp"

std::unique_ptr<score::mw::log::Recorder> configure_console_logging(score::mw::log::LogLevel log_level) {
  score::mw::log::detail::Configuration config{};
  config.SetLogMode({score::mw::LogMode::kConsole});
  config.SetDefaultConsoleLogLevel(log_level);

  return score::mw::log::detail::RecorderFactory().CreateRecorderFromLogMode(score::mw::LogMode::kConsole, config);
}
