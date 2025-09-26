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

#ifndef SRC_DAAL_AF_APP_HANDLER_SEQUENTIAL_LIST_CONTAINER_H_
#define SRC_DAAL_AF_APP_HANDLER_SEQUENTIAL_LIST_CONTAINER_H_

#include <memory>
#include <vector>

#include "daal/af/app_handler/iapplication_handler.hpp"

namespace daal {
namespace af {
namespace app_handler {

class SequentialAppHandlerContainer : public IApplicationHandler {
 public:
  using AppHandlerList = std::vector<std::shared_ptr<IApplicationHandler>>;

  SequentialAppHandlerContainer(const SequentialAppHandlerContainer &) = delete;
  SequentialAppHandlerContainer &operator=(const SequentialAppHandlerContainer &) = delete;
  SequentialAppHandlerContainer(SequentialAppHandlerContainer &&) = delete;
  SequentialAppHandlerContainer &operator=(SequentialAppHandlerContainer &&) = delete;
  ~SequentialAppHandlerContainer() override = default;

  SequentialAppHandlerContainer(AppHandlerList app_handler_list);

  bool Initialize() override;
  bool PrepareForExecute() override;
  bool Execute() override;
  bool PrepareForShutdown() override;
  bool Shutdown() override;

 private:
  AppHandlerList app_handlers_;
};

}  // namespace app_handler
}  // namespace af
}  // namespace daal

#endif  // SRC_DAAL_AF_APP_HANDLER_SEQUENTIAL_LIST_CONTAINER_H_
