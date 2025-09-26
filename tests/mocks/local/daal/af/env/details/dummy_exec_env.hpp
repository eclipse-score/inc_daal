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

#include <gmock/gmock.h>

#include "daal/af/env/execution_environment.hpp"

namespace daal {
namespace af {
namespace env {

class DummyExecutionEnvironment : public ExecutionEnvironment {
 public:
  DummyExecutionEnvironment() {}
  ~DummyExecutionEnvironment() = default;

  bool Init() override { return true; }
  bool Deinit() override { return true; }

  void SetState(State state) override {
    // do nothing
    return;
  }

  bool IsSigTerm() override { return false; }

  bool Refresh() override { return true; }
};

}  // namespace env
}  // namespace af
}  // namespace daal
