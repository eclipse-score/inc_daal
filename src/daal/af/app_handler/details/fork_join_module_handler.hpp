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

#ifndef SRC_DAAL_AF_APP_HANDLER_DETAILS_FORK_JOIN_MODULE_HANDLER_HPP
#define SRC_DAAL_AF_APP_HANDLER_DETAILS_FORK_JOIN_MODULE_HANDLER_HPP

#include <memory>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

#include "daal/af/app_handler/iapplication_handler.hpp"
#include "daal/af/worker/worker_thread.hpp"
#include "utility"

namespace daal {

namespace af {

namespace app_handler {

/**
 * \brief The ForkJoinModuleHandler class is responsible for joint-fork module,
 * where it registers the modules to a stage and executes the stages
 */
class ForkJoinModuleHandler : public IApplicationHandler {
 public:
  enum class TaskAffinity { MAIN, WORKER };
  enum class Stage { STAGE1, STAGE2, STAGE3 };

  using PhaseConfig = std::pair<TaskAffinity, std::shared_ptr<IApplicationHandler>>;
  using PhaseConfigList = std::vector<PhaseConfig>;
  using ForkMap = std::unordered_map<Stage, PhaseConfigList>;

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

 protected:
  /**
   * \brief Deleted default constructor.
   */
  ForkJoinModuleHandler(const ForkJoinModuleHandler &) = delete;

  /**
   * \brief Deleted copy assignment operator.
   */
  ForkJoinModuleHandler &operator=(const ForkJoinModuleHandler &) & = delete;

  /**
   * \brief Deleted move constructor.
   */
  ForkJoinModuleHandler(ForkJoinModuleHandler &&) = delete;

  /**
   * \brief Deleted move assignment operator.
   */
  ForkJoinModuleHandler &operator=(ForkJoinModuleHandler &&) & = delete;

  /**
   * \brief Construct a new Simple Application Handler object
   * \param application reference to the application to be handled
   */
  ForkJoinModuleHandler(unsigned int, int, ForkMap);

  /**
   * \brief Default destructor.
   */
  ~ForkJoinModuleHandler() override = default;

 private:
  ForkMap fork_map_;
  daal::af::worker::WorkerThread worker_thread_;
};

}  // namespace app_handler

}  // namespace af

}  // namespace daal

#endif  // SRC_DAAL_AF_APP_HANDLER_DETAILS_FORK_JOIN_MODULE_HANDLER_HPP
