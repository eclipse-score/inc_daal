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

#include <iostream>
#include <memory>

// DAAL minimal dependencies
#include "daal/af/app_handler/details/single_shot_app_handler.hpp"
#include "daal/af/checkpoint/details/checkpoint_container.hpp"
#include "daal/af/env/details/dummy_exec_env.hpp"
#include "daal/af/exe/builder/executor_builder.hpp"
#include "daal/af/os/details/posix_helper_impl.hpp"
#include "daal/af/trigger/details/trigger_impl.hpp"

// the actual application
#include "vehicle_control_app.hpp"

// actual IO handler fake implementation without SCORE mw::com dependencies
#include "steering_wheel_client_stub.hpp"

using namespace std::chrono_literals;

int main() {
  auto logger = std::make_shared<daal::log::Logger>("ADAS_VEHICLE_CONTROL");
  logger->AddDefaultSinks();

  // IO handlers
  daal::examples::SteeringWheelClientStub score_mw_com_client{};
  daal::examples::VehicleControlIoContainer io_container{score_mw_com_client};

  // application and app handler
  auto my_app = std::make_shared<daal::VehicleControlApp>(io_container, logger);
  std::unique_ptr<daal::af::app_handler::SingleShotAppHandler> app_handler =
      std::make_unique<daal::af::app_handler::SingleShotAppHandler>(my_app);

  auto exe = daal::af::exe::ExecutorBuilder()
                 .SetExecutionEnvironment(std::make_unique<daal::af::env::DummyExecutionEnvironment>())
                 .SetPosixHelper(std::make_unique<daal::af::os::PosixHelper>())
                 .SetTrigger(std::make_unique<daal::af::trigger::PeriodicTrigger>(500ms))
                 .SetCheckpointContainer(std::make_unique<daal::af::checkpoint::CheckpointContainer>())
                 .Start()
                 .End()
                 .Build();

  exe->Init();
  exe->SetApplicationHandler(std::move(app_handler));

  bool ret = exe->Run();
  if (ret) {
    logger->Info("Application finished successfully");
  } else {
    logger->Info("Application finished with an error");
  }

  return ret ? 0 : -1;
}
