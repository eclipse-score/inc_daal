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

#include "sequential_list_handler.hpp"

#include "daal/af/app_base/safe_application_base.hpp"

namespace daal {
namespace af {
namespace app_handler {

SequentialListAppHandler::SequentialListAppHandler(std::shared_ptr<daal::af::app_base::SafeApplicationBase> application)
    : apps_{{application}} {}

SequentialListAppHandler::SequentialListAppHandler(AppList app_list) : apps_{app_list} {}

bool SequentialListAppHandler::CheckState(daal::af::app_base::MethodState state) {
  return state == daal::af::app_base::MethodState::kSuccessful;
}

bool SequentialListAppHandler::Initialize() {
  bool state = true;
  for (const auto &app : apps_) {
    state = state && CheckState(app->OnInitialize());
  }
  return state;
}

bool SequentialListAppHandler::PrepareForExecute() {
  bool state = true;
  for (const auto &app : apps_) {
    state = state && CheckState(app->OnStart());
  }
  return state;
}

bool SequentialListAppHandler::Execute() {
  bool state = true;
  for (const auto &app : apps_) {
    state = state && CheckState(app->Step());
  }
  return state;
}

bool SequentialListAppHandler::PrepareForShutdown() {
  bool state = true;
  for (const auto &app : apps_) {
    state = state && CheckState(app->OnStop());
  }
  return state;
}

bool SequentialListAppHandler::Shutdown() {
  bool state = true;
  for (const auto &app : apps_) {
    state = state && CheckState(app->OnTerminate());
  }
  return state;
}

}  // namespace app_handler
}  // namespace af
}  // namespace daal
