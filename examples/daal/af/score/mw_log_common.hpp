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

#ifndef EXAMPLES_DAAL_AF_SCORE_MW_LOG_COMMON_HPP_
#define EXAMPLES_DAAL_AF_SCORE_MW_LOG_COMMON_HPP_

#include "score/mw/log/detail/recorder_factory.h"
#include "score/mw/log/recorder.h"

std::unique_ptr<score::mw::log::Recorder> configure_console_logging(
    score::mw::log::LogLevel log_level = score::mw::log::LogLevel::kError);

#endif  // EXAMPLES_DAAL_AF_SCORE_MW_LOG_COMMON_HPP_
