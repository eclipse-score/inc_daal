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

#ifndef DAAL__SRC_ENVIRONMENT_DETAILS_SIMPLE_SIGNAL_HANDLER_HPP
#define DAAL__SRC_ENVIRONMENT_DETAILS_SIMPLE_SIGNAL_HANDLER_HPP

#include <atomic>

namespace daal {

namespace af {

namespace env {

class SimpleSignalHandler {
 public:
  SimpleSignalHandler(std::atomic_bool &requested_exit, std::atomic_bool &signal_to_terminate);

  void operator()();

 private:
  std::atomic_bool &exit_requested_;
  std::atomic_bool &terminated_by_signal_;
};

}  // namespace env

}  // namespace af

}  // namespace daal

#endif  // DAAL__SRC_ENVIRONMENT_DETAILS_SIMPLE_SIGNAL_HANDLER_HPP
