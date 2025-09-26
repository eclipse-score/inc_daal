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

#include <chrono>

#include "daal/af/app_handler/details/single_shot_app_handler.hpp"
#include "daal/af/checkpoint/details/checkpoint_container.hpp"
#include "daal/af/env/details/dummy_exec_env.hpp"
#include "daal/af/exe/builder/executor_builder.hpp"
#include "daal/af/os/details/posix_helper_impl.hpp"
#include "daal/af/trigger/details/trigger_impl.hpp"
#include "daal/log/logger.hpp"
#include "hello_world_app.hpp"
using namespace std::chrono_literals;

int main() {
  auto logger = std::make_shared<daal::log::Logger>("MAIN");
  logger->AddDefaultSinks();

  logger->Info("Starting DAAL hello-world application");

  // (1) create the application
  // (2) create the application handler (SingleShotAppHandler => we can run only one application)
  auto my_app = std::make_shared<daal::examples::HelloWorldApp>();
  std::unique_ptr<daal::af::app_handler::SingleShotAppHandler> app_handler =
      std::make_unique<daal::af::app_handler::SingleShotAppHandler>(my_app);

  // (3) create the executor with environment, scheduling/trigger and optional checkpoints
  //     here: a dummy environment, the AppHandler is called every 100ms and no checkpoints
  auto exe = daal::af::exe::ExecutorBuilder()
                 .SetExecutionEnvironment(std::make_unique<daal::af::env::DummyExecutionEnvironment>())
                 .SetPosixHelper(std::make_unique<daal::af::os::PosixHelper>())
                 .SetTrigger(std::make_unique<daal::af::trigger::PeriodicTrigger>(500ms))
                 .SetCheckpointContainer(std::make_unique<daal::af::checkpoint::CheckpointContainer>())
                 .Start()
                 .End()
                 .Build();

  // (4) finalize the initialization of the exectuor
  exe->Init();
  exe->SetApplicationHandler(std::move(app_handler));

  // (5) run the executor (= application) until it's terminated
  bool ret = exe->Run();
  if (ret) {
    logger->Info("Application finished successfully");
  } else {
    logger->Error("Application finished with an error");
  }

  return ret ? 0 : -1;
}
