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

#ifndef SRC_DAAL_AF_EXE_BUILDER_CYCLIC_ARA_QNX_EXECUTOR_BUILDER_H_
#define SRC_DAAL_AF_EXE_BUILDER_CYCLIC_ARA_QNX_EXECUTOR_BUILDER_H_

#include <chrono>
#include <limits>
#include <memory>

#include "daal/af/checkpoint/details/checkpoint_container.hpp"
#include "daal/af/exe/builder/executor_builder.hpp"
#include "daal/af/monitoring/details/araphm_checkpoint.hpp"
#include "daal/af/mt/details/mt_trigger_handler.hpp"
#include "daal/af/os/details/posix_helper_impl.hpp"
#include "daal/af/trigger/details/trigger_impl.hpp"

namespace daal {
namespace af {
namespace exe {

template <std::uint32_t AliveSignalId>
class CyclicAraQNXExecutorBuilder {
 public:
  CyclicAraQNXExecutorBuilder(const std::chrono::milliseconds period,
                              env::ExecutionEnvironment::ProcessingModes process_mode =
                                  env::ExecutionEnvironment::ProcessingModes::kThreadDriven)
      : period_{period}, process_mode_{process_mode} {}

  std::unique_ptr<Executor> Build() {
    auto exe = ExecutorBuilder()
                   .CreateExecutionEnvironment<env::AAExecutionEnvironment>(process_mode_)
                   .CreatePosixHelper<os::PosixHelper>()
                   .CreateTrigger<trigger::PeriodicTrigger>(period_)
                   .CreateCheckpointContainer<checkpoint::CheckpointContainer>()
                   .Start()
                   .CreateCheckpoint<mt::MtTriggerHandler>()
                   .CreateCheckpoint<monitoring::AraPhmCheckpoint<AliveSignalId>>()
                   .End()
                   .Build();
    return exe;
  }

 private:
  std::chrono::milliseconds period_;
  env::ExecutionEnvironment::ProcessingModes process_mode_;
};

}  // namespace exe
}  // namespace af
}  // namespace daal

#endif /* SRC_DAAL_AF_EXE_BUILDER_CYCLIC_ARA_QNX_EXECUTOR_BUILDER_H_ */
