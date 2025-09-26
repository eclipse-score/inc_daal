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

#ifndef SRC_DAAL_AF_EXE_EXECUTOR_COMPONENTS_H_
#define SRC_DAAL_AF_EXE_EXECUTOR_COMPONENTS_H_

#include <memory>
#include <utility>

#include "daal/af/exe/details/executor_impl.hpp"
#include "daal/log/framework_logger.hpp"

namespace daal {
namespace af {
namespace exe {

class Components {
 public:
  std::unique_ptr<env::ExecutionEnvironment> exe_env_;
  std::unique_ptr<os::IPosixHelper> os_helper_;
  std::unique_ptr<trigger::Trigger> trigger_;
  std::unique_ptr<checkpoint::ICheckpointContainer> checkpoint_container_;
};

class Finalize {
 public:
  Finalize(std::shared_ptr<Components> components) : components_(components) {}

  /**
   * @brief Constructs and returns a unique pointer to an Executor instance.
   *
   * This method finalizes the building process by assembling all the components
   * and creating an Executor instance.
   *
   * @return std::unique_ptr<Executor> A unique pointer to the constructed
   * Executor.
   */
  std::unique_ptr<Executor> Build() {
    return std::make_unique<Executor>(std::move(components_->exe_env_), std::move(components_->os_helper_),
                                      std::move(components_->trigger_), std::move(components_->checkpoint_container_));
  }

 private:
  std::shared_ptr<Components> components_;
};

class CheckpointAdder {
 public:
  CheckpointAdder(std::shared_ptr<Components> components) : components_(components) {}

  CheckpointAdder &AddCheckpoint(std::shared_ptr<checkpoint::ICheckpoint> checkpoint) {
    if (components_->checkpoint_container_) {
      components_->checkpoint_container_->AddCheckpoint(checkpoint);
    } else {
      daal::log::FrameworkLogger::get()->Error("Checkpoint container is not set");
      std::terminate();
    }
    return *this;
  }

  template <typename T, typename... Args>
  CheckpointAdder &CreateCheckpoint(Args &&...args) {
    auto checkpoint = std::make_shared<T>(std::forward<Args>(args)...);
    return AddCheckpoint(checkpoint);
  }

  Finalize End() { return Finalize(components_); }

 private:
  std::shared_ptr<Components> components_;
};

class CheckpointContainerBuilder {
 public:
  CheckpointContainerBuilder(std::shared_ptr<Components> components) : components_(components) {}

  CheckpointContainerBuilder &SetCheckpointContainer(
      std::unique_ptr<checkpoint::ICheckpointContainer> checkpoint_container) {
    components_->checkpoint_container_ = std::move(checkpoint_container);
    return *this;
  }

  template <typename T, typename... Args>
  CheckpointContainerBuilder &CreateCheckpointContainer(Args &&...args) {
    auto checkpoint_container = std::make_unique<T>(std::forward<Args>(args)...);
    return SetCheckpointContainer(std::move(checkpoint_container));
  }

  CheckpointAdder Start() { return CheckpointAdder(components_); }

  Finalize End() { return Finalize(components_); }

 private:
  std::shared_ptr<Components> components_;
};

class TriggerBuilder {
 public:
  TriggerBuilder(std::shared_ptr<Components> components) : components_(components) {}

  CheckpointContainerBuilder SetTrigger(std::unique_ptr<trigger::Trigger> trigger) {
    components_->trigger_ = std::move(trigger);
    return CheckpointContainerBuilder(components_);
  }

  template <typename T, typename... Args>
  CheckpointContainerBuilder CreateTrigger(Args &&...args) {
    auto trigger = std::make_unique<T>(std::forward<Args>(args)...);
    return SetTrigger(std::move(trigger));
  }

 private:
  std::shared_ptr<Components> components_;
};

class PosixHelperBuilder {
 public:
  PosixHelperBuilder(std::shared_ptr<Components> components) : components_(components) {}

  TriggerBuilder SetPosixHelper(std::unique_ptr<os::IPosixHelper> os_helper) {
    components_->os_helper_ = std::move(os_helper);
    return TriggerBuilder(components_);
  }

  template <typename T, typename... Args>
  TriggerBuilder CreatePosixHelper(Args &&...args) {
    auto os_helper = std::make_unique<T>(std::forward<Args>(args)...);
    return SetPosixHelper(std::move(os_helper));
  }

 private:
  std::shared_ptr<Components> components_;
};

class ExecutorBuilder {
 public:
  ExecutorBuilder() : components_(std::make_shared<Components>()) {}

  PosixHelperBuilder SetExecutionEnvironment(std::unique_ptr<env::ExecutionEnvironment> exe_env) {
    components_->exe_env_ = std::move(exe_env);
    return PosixHelperBuilder(components_);
  }

  template <typename T, typename... Args>
  PosixHelperBuilder CreateExecutionEnvironment(Args &&...args) {
    auto exec_env = std::make_unique<T>(std::forward<Args>(args)...);
    return SetExecutionEnvironment(std::move(exec_env));
  }

 private:
  std::shared_ptr<Components> components_;
};

}  // namespace exe
}  // namespace af
}  // namespace daal

#endif /* SRC_DAAL_AF_EXE_EXECUTOR_COMPONENTS_H_ */
