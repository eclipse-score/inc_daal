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

#include "daal/af/app_base/safe_application_base.hpp"
#include "daal/log/logger.hpp"

namespace daal {
namespace examples {

class HelloWorldApp : public daal::af::app_base::SafeApplicationBase {
 public:
  HelloWorldApp() : logger_(std::make_shared<daal::log::Logger>("APP")) { logger_->AddDefaultSinks(); };
  ~HelloWorldApp() override = default;

  daal::af::app_base::MethodState OnInitialize() override { return daal::af::app_base::MethodState::kSuccessful; }

  daal::af::app_base::MethodState OnStart() override { return daal::af::app_base::MethodState::kSuccessful; }

  daal::af::app_base::MethodState Step() override {
    static unsigned int cycle_counter = 0;

    logger_->Info("step #{}", cycle_counter);
    cycle_counter++;

    return daal::af::app_base::MethodState::kSuccessful;
  }

  daal::af::app_base::MethodState OnStop() override { return daal::af::app_base::MethodState::kSuccessful; }

  daal::af::app_base::MethodState OnTerminate() override { return daal::af::app_base::MethodState::kSuccessful; }

 private:
  std::shared_ptr<daal::log::Logger> logger_;
};

}  // namespace examples
}  // namespace daal
