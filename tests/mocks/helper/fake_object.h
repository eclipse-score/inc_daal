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

#ifndef APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_MOCKS_HELPER_FAKE_OBJECT_H_
#define APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_MOCKS_HELPER_FAKE_OBJECT_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <mutex>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

template <typename T>
class FakeObject {
 public:
  static std::unordered_map<std::string, std::shared_ptr<T>> CallsMap;
  static std::mutex Mutex;

  static std::shared_ptr<T> GetFakeObject() {
    // Thread safety for craeting the objects
    std::lock_guard<std::mutex> lock(Mutex);
    std::string test_name =
        ::testing::UnitTest::GetInstance()->current_test_info()->name();
    if (CallsMap.find(test_name) == CallsMap.end()) {
      CallsMap.insert({test_name, std::make_shared<T>()});
    }

    return CallsMap[test_name];
  }

  static void RemoveFakeObject() {
    std::lock_guard<std::mutex> lock(Mutex);
    std::string test_name =
        ::testing::UnitTest::GetInstance()->current_test_info()->name();
    auto it = CallsMap.find(test_name);
    if (it != CallsMap.end()) {
      CallsMap.erase(it);
    }
  }
};

template <typename T>
std::unordered_map<std::string, std::shared_ptr<T>> FakeObject<T>::CallsMap =
    {};

template <typename T>
std::mutex FakeObject<T>::Mutex = {};

#endif /* APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_MOCKS_HELPER_FAKE_OBJECT_H_ */
