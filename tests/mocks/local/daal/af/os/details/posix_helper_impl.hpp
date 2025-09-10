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

#pragma once

#include "daal/af/os/posix_helper.hpp"
#include <gmock/gmock.h>

struct PosixHelperMock {
  static PosixHelperMock &instance() {
    static PosixHelperMock mock;
    return mock;
  }

  MOCK_METHOD(void, ctor, ());
  MOCK_METHOD(bool, IsNoEnvVarSet,
              (const char *search_str, const char *ignore_str));
  MOCK_METHOD(bool, IsFpuWorking, (float f_precision));
  MOCK_METHOD(bool, DropPrivileges, ());
  MOCK_METHOD(void, SetupOomHandler, ());
};

namespace daal::af::os {

struct PosixHelper : public IPosixHelper {
  PosixHelper() { PosixHelperMock::instance().ctor(); }

  bool IsNoEnvVarSet(const char *search_str, const char *ignore_str) override {
    return PosixHelperMock::instance().IsNoEnvVarSet(search_str, ignore_str);
  }

  bool IsFpuWorking(float f_precision) override {
    return PosixHelperMock::instance().IsFpuWorking(f_precision);
  }

  bool DropPrivileges() override {
    return PosixHelperMock::instance().DropPrivileges();
  }
  void SetupOomHandler() override {
    PosixHelperMock::instance().SetupOomHandler();
  }
};

} // namespace daal::af::os
