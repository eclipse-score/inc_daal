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

#ifndef APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_MOCKS_OS_WRAPPER_IMPL_H_
#define APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_MOCKS_OS_WRAPPER_IMPL_H_

#include <gmock/gmock.h>

#include "daal/af/os/posix_wrapper.hpp"
#include "mocks/helper/fake_object.h"

namespace daal {

namespace af {

namespace os {

class OSWrapperMock : public FakeObject<OSWrapperMock> {
 public:
  MOCK_METHOD(int, SetRLimit, (const int resource, const RLimit r_limit), ());
  MOCK_METHOD(RLimit, GetRLimit, (const int resource), ());
  MOCK_METHOD(void, SetupOomHandler, (), ());
};
class PosixWrapper : public IPosixWrapper {
 public:
  int SetRLimit(const int resource, const RLimit r_limit) override {
    return FakeObject<OSWrapperMock>::GetFakeObject()->SetRLimit(resource,
                                                                 r_limit);
  }

  RLimit GetRLimit(const int resource) override {
    return FakeObject<OSWrapperMock>::GetFakeObject()->GetRLimit(resource);
  }

  void SetupOomHandler() override {
    FakeObject<OSWrapperMock>::GetFakeObject()->SetupOomHandler();
  }
};

}  // namespace os

}  // namespace af

}  // namespace daal

#endif /* APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_MOCKS_OS_WRAPPER_IMPL_H_ */
