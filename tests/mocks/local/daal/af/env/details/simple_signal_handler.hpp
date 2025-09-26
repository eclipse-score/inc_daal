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

#ifndef APPLICATION_COMMON_DAAL_SAFE_RUNNER_TEST_MOCKS_LOCAL_ENVIRONMENT_DETAILS_SIGNAL_HANDLER_WRAPPER_HPP
#define APPLICATION_COMMON_DAAL_SAFE_RUNNER_TEST_MOCKS_LOCAL_ENVIRONMENT_DETAILS_SIGNAL_HANDLER_WRAPPER_HPP

#ifndef APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_MOCKS_LOCAL_APPLICATION_COMMON_APPLICATION_BASE_SIGNAL_HANDLER_H_
#define APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_MOCKS_LOCAL_APPLICATION_COMMON_APPLICATION_BASE_SIGNAL_HANDLER_H_

#include <atomic>


namespace daal {

namespace af {

namespace env {

class SimpleSignalHandler {
 public:
  SimpleSignalHandler(std::atomic_bool& exit_requested,
                      std::atomic_bool& terminated_by_signal)
      : exit_requested_(exit_requested),
        terminated_by_signal_(terminated_by_signal) {}

  void operator()() { exit_requested_ = true; }

 private:
  std::atomic_bool& exit_requested_;
  std::atomic_bool& terminated_by_signal_;
};



} // namespace env

} // namespace af

} // namespace daal

#endif /* APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_MOCKS_LOCAL_APPLICATION_COMMON_APPLICATION_BASE_SIGNAL_HANDLER_H_ \
        */

#endif  // APPLICATION_COMMON_DAAL_SAFE_RUNNER_TEST_MOCKS_LOCAL_ENVIRONMENT_DETAILS_SIGNAL_HANDLER_WRAPPER_HPP
