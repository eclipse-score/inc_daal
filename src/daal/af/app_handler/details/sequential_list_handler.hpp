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

#ifndef SRC_DAAL_AF_APP_HANDLER_SEQUENTIAL_LIST_HANDLER_H_
#define SRC_DAAL_AF_APP_HANDLER_SEQUENTIAL_LIST_HANDLER_H_

#include <memory>
#include <vector>

#include "daal/af/app_base/safe_application_base.hpp"
#include "daal/af/app_handler/iapplication_handler.hpp"

namespace daal {
namespace af {
namespace app_handler {

/**
 * \brief The SequentialListAppHandler class is responsible for handling a
 * simple application.
 *
 * It implements the IApplicationHandler interface and provides methods for
 * initializing, resetting, executing, preparing for shutdown, and shutting down
 * the application.
 */
class SequentialListAppHandler : public IApplicationHandler {
 public:
  using AppList = std::vector<std::shared_ptr<daal::af::app_base::SafeApplicationBase>>;
  /**
   * \brief Deleted default constructor.
   */
  SequentialListAppHandler(const SequentialListAppHandler &) = delete;

  /**
   * \brief Deleted copy assignment operator.
   */
  SequentialListAppHandler &operator=(const SequentialListAppHandler &) = delete;

  /**
   * \brief Deleted move constructor.
   */
  SequentialListAppHandler(SequentialListAppHandler &&) = delete;

  /**
   * \brief Deleted move assignment operator.
   */
  SequentialListAppHandler &operator=(SequentialListAppHandler &&) = delete;

  /**
   * \brief Construct a new SequentialListAppHandler object
   * \param application reference to the application to be handled
   */
  SequentialListAppHandler(std::shared_ptr<daal::af::app_base::SafeApplicationBase>);

  /**
   * \brief Construct a new SequentialListAppHandler object
   * \param app_list list of applications to execute
   */
  SequentialListAppHandler(AppList app_list);

  /**
   * \brief Default destructor.
   */
  ~SequentialListAppHandler() override = default;

  /**
   * \brief Initializes the application.
   *
   * \return true if the initialization is successful, false otherwise.
   */
  bool Initialize() override;

  /**
   * \brief Resets the application.
   *
   * \return true if the reset is successful, false otherwise.
   */
  bool PrepareForExecute() override;

  /**
   * \brief Executes the application.
   *
   * \return true if the execution is successful, false otherwise.
   */
  bool Execute() override;

  /**
   * \brief Prepares the application for shutdown.
   */
  bool PrepareForShutdown() override;

  /**
   * \brief Shuts down the application.
   */
  bool Shutdown() override;

 private:
  bool CheckState(daal::af::app_base::MethodState);

  AppList apps_;
};

}  // namespace app_handler
}  // namespace af
}  // namespace daal

#endif  // SRC_DAAL_AF_APP_HANDLER_SEQUENTIAL_LIST_HANDLER_H_
