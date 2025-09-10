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

#ifndef SRC_DAAL_AF_EXE_DETAILS_EXECUTOR_IMPL_H_
#define SRC_DAAL_AF_EXE_DETAILS_EXECUTOR_IMPL_H_

#include <memory>
#include <utility>
#include <vector>

#include "daal/af/app_handler/iapplication_handler.hpp"
#include "daal/af/checkpoint/icheckpoint_container.hpp"
#include "daal/af/env/execution_environment.hpp"
#include "daal/af/exe/iexecutor.hpp"
#include "daal/af/os/posix_helper.hpp"
#include "daal/af/runtime_statistics/runtime_statistics.hpp"
#include "daal/af/trigger/trigger.hpp"

namespace daal {

namespace af {
namespace exe {

/*!
 * \brief Generic implementation of Executor
 *
 */
class Executor : public IExecutor {
 public:
  Executor() = delete;
  /*!
   * \brief Construct a new Executor object
   * \satisfy  @DNG_RM1_6510671 requires an initialised Environment
   */
  Executor(std::unique_ptr<env::ExecutionEnvironment>, std::unique_ptr<os::IPosixHelper>,
           std::unique_ptr<trigger::Trigger>,
           std::unique_ptr<checkpoint::ICheckpointContainer>);  // TODO(vmurgan):
                                                                // set valid
                                                                // default values
  ~Executor() override = default;
  Executor(const Executor &) = delete;
  auto operator=(const Executor &) & -> Executor & = delete;
  Executor(Executor &&) noexcept = default;
  auto operator=(Executor &&) &noexcept -> Executor & = default;
  auto Run() -> bool override;
  auto Init() -> bool override;
  void SetApplicationHandler(std::unique_ptr<app_handler::IApplicationHandler>) noexcept;

 private:
  std::unique_ptr<env::ExecutionEnvironment> exe_env_iface_;
  std::unique_ptr<os::IPosixHelper> os_helper_iface_;
  std::unique_ptr<trigger::Trigger> trigger_iface_;
  std::unique_ptr<checkpoint::ICheckpointContainer> chkpt_container_iface_;
  bool is_executor_initialised_;
  bool is_application_set_;
  std::unique_ptr<app_handler::IApplicationHandler> app_iface_;

  const std::string name_;
  runtime_statistics::RuntimeStatistics runtime_statistics_;
};

}  // namespace exe

}  // namespace af

}  // namespace daal

#endif /* SRC_DAAL_AF_EXE_DETAILS_EXECUTOR_IMPL_H_ */
