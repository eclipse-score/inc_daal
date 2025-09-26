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

#include "override_terminate.hpp"

namespace daal {
namespace af {
namespace std_override {

TerminateHandlerInitializer::TerminateHandlerInitializer() noexcept { std::set_terminate(CustomTerminate); }

void TerminateHandlerInitializer::CustomTerminate() noexcept {
  // abort the program, for safety reasons
  // This is a safety requirement, as unwind is not expected to be used
  std::abort();
}

// Static instance to ensure initialization before main()
static const TerminateHandlerInitializer terminateHandlerInitializer;

}  // namespace std_override
}  // namespace af
}  // namespace daal
