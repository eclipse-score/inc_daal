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

#ifndef DAAL_TEST_MOCKS_LOCAL_DAAL_AF_EXE_DETAILS_EXECUTOR_IMPL__H_
#define DAAL_TEST_MOCKS_LOCAL_DAAL_AF_EXE_DETAILS_EXECUTOR_IMPL__H_

#include <gmock/gmock.h>

#include <memory>

#include "daal/af/env/execution_environment.hpp"
#include "daal/af/os/posix_helper.hpp"
#include "daal/af/trigger/trigger.hpp"
#include "daal/af/checkpoint/icheckpoint_container.hpp"
#include "daal/af/app_handler/iapplication_handler.hpp"  // Ensure this include is correct

struct ExecutorImplMock {
  static ExecutorImplMock& instance() {
    static ExecutorImplMock mock;
    return mock;
  }

  MOCK_METHOD(void, ctor,
              (std::unique_ptr<daal::af::env::ExecutionEnvironment>,
               std::unique_ptr<daal::af::os::IPosixHelper>,
               std::unique_ptr<daal::af::trigger::Trigger>,
               std::unique_ptr<daal::af::checkpoint::ICheckpointContainer>));
  MOCK_METHOD(void, SetApplicationHandler,
              (std::unique_ptr<daal::af::app_handler::IApplicationHandler>));
  MOCK_METHOD(bool, Run, ());
  MOCK_METHOD(void, Init, ());
};

namespace daal {
namespace af {
namespace exe {

struct Executor {
  Executor(std::unique_ptr<daal::af::env::ExecutionEnvironment> aae,
           std::unique_ptr<daal::af::os::IPosixHelper> helper,
           std::unique_ptr<daal::af::trigger::Trigger> trigger,
           std::unique_ptr<daal::af::checkpoint::ICheckpointContainer> cc) {
    ExecutorImplMock::instance().ctor(std::move(aae), std::move(helper), std::move(trigger), std::move(cc));
  }
  void SetApplicationHandler(std::unique_ptr<daal::af::app_handler::IApplicationHandler> app) {
    ExecutorImplMock::instance().SetApplicationHandler(std::move(app));
  }
  bool Run() { return ExecutorImplMock::instance().Run(); }
  void Init() { ExecutorImplMock::instance().Init(); }
};

}  // namespace exe
}  // namespace af
}  // namespace daal


#endif /* DAAL_TEST_MOCKS_LOCAL_DAAL_AF_EXE_DETAILS_EXECUTOR_IMPL__H_ */
