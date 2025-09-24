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

#ifndef APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_EXECUTOR_QNX_OS_MOCK_H_
#define APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_EXECUTOR_QNX_OS_MOCK_H_

#include <gmock/gmock.h>

#include "src/daal/af/os/posix_helper.hpp"

namespace daal {

namespace af {

namespace os {

/*!
 * \brief Mock for the some concrete type of IPosixHelper for Executor
 *
 */
class QNXOSMOCK : public IPosixHelper {
public:
  MOCK_METHOD(bool, IsNoEnvVarSet,
              (const char *search_str, const char *ignore_str), (override));
  MOCK_METHOD(bool, IsFpuWorking, (float f_precision), (override));
  MOCK_METHOD(bool, DropPrivileges, (), (override));
  MOCK_METHOD(void, SetupOomHandler, (), (override));
};

} // namespace os

} // namespace af

} // namespace daal

#endif /* APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_EXECUTOR_QNX_OS_MOCK_H_ */
