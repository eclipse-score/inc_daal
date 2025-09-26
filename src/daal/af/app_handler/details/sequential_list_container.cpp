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

#include "sequential_list_container.hpp"

namespace daal {
namespace af {
namespace app_handler {

SequentialAppHandlerContainer::SequentialAppHandlerContainer(AppHandlerList app_handler_list)
    : app_handlers_{app_handler_list} {}

bool SequentialAppHandlerContainer::Initialize() {
  bool state = true;
  for (const auto &app_handler : app_handlers_) {
    state = state && app_handler->Initialize();
  }
  return state;
}

bool SequentialAppHandlerContainer::PrepareForExecute() {
  bool state = true;
  for (const auto &app_handler : app_handlers_) {
    state = state && app_handler->PrepareForExecute();
  }
  return state;
}

bool SequentialAppHandlerContainer::Execute() {
  bool state = true;
  for (const auto &app_handler : app_handlers_) {
    state = state && app_handler->Execute();
  }
  return state;
}

bool SequentialAppHandlerContainer::PrepareForShutdown() {
  bool state = true;
  for (const auto &app_handler : app_handlers_) {
    state = state && app_handler->PrepareForShutdown();
  }
  return state;
}

bool SequentialAppHandlerContainer::Shutdown() {
  bool state = true;
  for (const auto &app_handler : app_handlers_) {
    state = state && app_handler->Shutdown();
  }
  return state;
}

}  // namespace app_handler
}  // namespace af
}  // namespace daal
