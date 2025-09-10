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

#ifndef APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_MOCKS_SYSTEM_SYS_RESOURCE_FAKE_H_
#define APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_MOCKS_SYSTEM_SYS_RESOURCE_FAKE_H_

#include <gmock/gmock.h>

#include "mocks/helper/fake_object.h"

class FakeSysRLimit : public FakeObject<FakeSysRLimit> {
 public:
  MOCK_METHOD(int, GetLimit, (int resource, struct rlimit *rlim), ());
  MOCK_METHOD(int, SetLimit, (int resource, const struct rlimit *rlim), ());
};

#endif /* APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_MOCKS_SYSTEM_SYS_RESOURCE_FAKE_H_ \
        */
