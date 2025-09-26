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

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sys/resource.h>

#include <iostream>
#include <stdexcept>

#include "daal/af/app_handler/details/single_shot_app_handler.hpp"
#include "daal/af/checkpoint/details/null_checkpoint_container.hpp"
#include "daal/af/env/details/dummy_exec_env.hpp"
#include "daal/af/exe/builder/executor_builder.hpp"
#include "daal/af/exe/details/executor_impl.hpp"
#include "daal/af/os/details/posix_helper_impl.hpp"
#include "daal/af/trigger/details/trigger_impl.hpp"

using namespace std::chrono_literals;

void set_memory_limit(size_t limit_in_mb) {
  struct rlimit rl;
  rl.rlim_cur = limit_in_mb * 1024 * 1024;  // Convert MB to bytes
  rl.rlim_max = limit_in_mb * 1024 * 1024;  // Convert MB to bytes

  if (setrlimit(RLIMIT_AS, &rl) != 0) {
    perror("setrlimit failed");
    exit(EXIT_FAILURE);
  }
}

// Basic application class for testing
class MyApplicationAllocTest : public daal::af::app_base::SafeApplicationBase {
 public:
  MyApplicationAllocTest() = default;
  ~MyApplicationAllocTest() override = default;

  auto OnInitialize() -> daal::af::app_base::MethodState override {
    return daal::af::app_base::MethodState::kSuccessful;
  }

  auto OnStart() -> daal::af::app_base::MethodState override {
    return daal::af::app_base::MethodState::kSuccessful;
  }

  auto Step() -> daal::af::app_base::MethodState override {
    std::cerr << "Allocating memory..." << std::endl;
    // Allocate a large amount of memory
    size_t size = 60 * 1024 * 1024;  // 60 MB
    char* buffer = new char[size];
    //delete buffer;
    std::destroy_at(buffer);
    // Return a valid MethodState value
    return daal::af::app_base::MethodState::kSuccessful;
  }

  auto OnStop() -> daal::af::app_base::MethodState override {
    return daal::af::app_base::MethodState::kSuccessful;
  }

  auto OnTerminate() -> daal::af::app_base::MethodState override {
    return daal::af::app_base::MethodState::kSuccessful;
  }
};

/*!
 * \brief Simple test for checking the exception memory allocation fails with
 * abort
 */
TEST(STDLibOverride, MemAllocCrash) {
  // expect abort to be called
  EXPECT_DEATH(
      {
        set_memory_limit(50);

        auto exe =
            daal::af::exe::ExecutorBuilder()
                .SetExecutionEnvironment(
                    std::make_unique<daal::af::env::DummyExecutionEnvironment>())
                .SetPosixHelper(std::make_unique<daal::af::os::PosixHelper>())
                .SetTrigger(
                    std::make_unique<daal::af::trigger::PeriodicTrigger>(100ms))
                .SetCheckpointContainer(
                    std::make_unique<
                        daal::af::checkpoint::NullCheckpointContainer>())
                .End()
                .Build();

        auto my_app = std::make_shared<MyApplicationAllocTest>();

        std::unique_ptr<daal::af::app_handler::SingleShotAppHandler> app_handler =
            std::make_unique<daal::af::app_handler::SingleShotAppHandler>(my_app);

        // set the application to executor.
        exe->SetApplicationHandler(std::move(app_handler));

        // Run the executor
        exe->Run();
      },
      "");
}
