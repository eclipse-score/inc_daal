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

#ifndef TEST_EXE_CHECKPOINT_MOCK_H_
#define TEST_EXE_CHECKPOINT_MOCK_H_

#include <gmock/gmock.h>

#include "daal/af/checkpoint/icheckpoint_container.hpp"

namespace daal {
namespace af {
namespace checkpoint {

class MockCheckpointContainer : public ICheckpointContainer {
 public:
  MOCK_METHOD(std::error_code, TriggerCheckpoints, (When when),
              (override, const));
  MOCK_METHOD(std::error_code, AddCheckpoint,
              (std::shared_ptr<ICheckpoint> checkpoint), (override));
};

class MockCheckpoint : public ICheckpoint {
 public:
    MOCK_METHOD(std::error_code, Trigger, (), (override));
    MOCK_METHOD(When, GetWhen, (), (const, override));
    MOCK_METHOD(const std::string&, GetName, (), (const, override));
};

}  // namespace checkpoint
}  // namespace af
}  // namespace daal

#endif /* TEST_EXE_CHECKPOINT_MOCK_H_ */
