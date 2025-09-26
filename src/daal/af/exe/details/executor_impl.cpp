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

#include "executor_impl.hpp"

#include <memory>
#include <system_error>

#include "src/daal/af/exe/iexecutor.hpp"

namespace {
constexpr float kDefaultFpuPrecision = 0.000001F;
}

#include "daal/af/app_handler/iapplication_handler.hpp"
#include "daal/af/checkpoint/icheckpoint_container.hpp"
#include "daal/af/checkpoint/when.hpp"
#include "daal/af/env/execution_environment.hpp"
#include "daal/af/os/posix_helper.hpp"
#include "daal/af/runtime_statistics/details/file_backend.hpp"
#include "daal/af/runtime_statistics/runtime_statistics.hpp"
#include "daal/af/trigger/trigger.hpp"
#include "daal/log/framework_logger.hpp"

namespace daal {
namespace af {
namespace exe {

/* FIXME (Markus Braun, braun5m, 2025-06-11): hack to get the name of the
 * current executable */
extern "C" {
extern const char *__progname;
#define EXECUTABLE_NAME ((__progname != NULL) && (__progname[0] != '\0')) ? (__progname) : "unknown"
}

Executor::Executor(std::unique_ptr<env::ExecutionEnvironment> exe_env, std::unique_ptr<os::IPosixHelper> os_helper,
                   std::unique_ptr<trigger::Trigger> trigger,
                   std::unique_ptr<checkpoint::ICheckpointContainer> checkpoint_container)
    : IExecutor(),
      exe_env_iface_{std::move(exe_env)},
      os_helper_iface_{std::move(os_helper)},
      trigger_iface_{std::move(trigger)},
      chkpt_container_iface_{std::move(checkpoint_container)},
      is_executor_initialised_{false},
      is_application_set_{false},
      app_iface_{nullptr},
      name_{EXECUTABLE_NAME},
      runtime_statistics_{name_, std::make_shared<runtime_statistics::TimeProvider>(),
                          std::make_shared<runtime_statistics::FileBackend>()} {
  os_helper_iface_->SetupOomHandler();
}

auto Executor::Init() -> bool {
  if (not is_executor_initialised_) {
    bool init_success{false};
    init_success = exe_env_iface_->Init();

    if (init_success) {
      init_success =
          // Expected envs AMSR_IPC_DEFAULT_SHM_SIZE
          // TODO(vmurgan): Add actual envs to check #ADASDAI-239939
          os_helper_iface_->IsNoEnvVarSet("XXXX", "NULL");
    } else {
      daal::log::FrameworkLogger::get()->Error("ExecutionEnvironment initialization failed");
    }

    if (init_success) {
      init_success = os_helper_iface_->IsFpuWorking(kDefaultFpuPrecision);
    } else {
      daal::log::FrameworkLogger::get()->Error("Environment variable check failed");
    }

    if (not init_success) {
      daal::log::FrameworkLogger::get()->Error("FPU check failed");
    }

    is_executor_initialised_ = init_success;
  }

  return is_executor_initialised_;
}

auto Executor::Run() -> bool {
  bool ret{false};

  if (not is_application_set_) {
    daal::log::FrameworkLogger::get()->Error("Exit Run, application handler is not set");
    return false;
  }

  is_executor_initialised_ = Init();
  if (!is_executor_initialised_) {
    daal::log::FrameworkLogger::get()->Error("Exit run, Excutor initialization failed");
    return false;
  }

  const bool is_app_initialised{app_iface_->Initialize()};
  if (!is_app_initialised) {
    daal::log::FrameworkLogger::get()->Error("Application Handler initialization failed");
    // Ignore the return type as application will exit with error
    (void)app_iface_->Shutdown();
    return false;
  }

  exe_env_iface_->SetState(env::ExecutionEnvironment::State::kRunning);

  const bool is_app_ready_to_run{app_iface_->PrepareForExecute()};
  if (!is_app_ready_to_run) {
    daal::log::FrameworkLogger::get()->Error("Application Handler is not ready to run");
    // Ignore the return type as application will exit with error
    (void)app_iface_->PrepareForShutdown();
    (void)app_iface_->Shutdown();
    return false;
  }

  const bool is_privileges_dropped{os_helper_iface_->DropPrivileges()};
  if (!is_privileges_dropped) {
    daal::log::FrameworkLogger::get()->Error("Unable to drop application privileges");
    // Ignore the return type as application will exit with error
    (void)app_iface_->PrepareForShutdown();
    (void)app_iface_->Shutdown();
    return false;
  }

  bool is_step_success{true};
  while (!exe_env_iface_->IsSigTerm() && is_step_success) {
    // Keep the old behaviour
    (void)trigger_iface_->CheckTriggerConditionAndWait();

    const bool is_refresh_success{exe_env_iface_->Refresh()};
    if (!is_refresh_success) {
      daal::log::FrameworkLogger::get()->Error("Environment refresh failed step start");
    }

    runtime_statistics_.StartMeasurement();

    const std::error_code ERR_CODE_OK{std::error_code{}};
    const std::error_code ret_code_before{chkpt_container_iface_->TriggerCheckpoints(checkpoint::When::BEFORE)};
    if (ret_code_before != ERR_CODE_OK) {
      daal::log::FrameworkLogger::get()->Error("In Triggering Checkpoints");
      is_step_success = false;
      break;
    }

    // Run/Execute Application Handler if the
    is_step_success = app_iface_->Execute();

    if (not is_step_success) {
      daal::log::FrameworkLogger::get()->Error("Application Handler Execution Failed");
      break;
    }

    const std::error_code ret_code_after{chkpt_container_iface_->TriggerCheckpoints(checkpoint::When::AFTER)};
    if (ret_code_after != ERR_CODE_OK) {
      daal::log::FrameworkLogger::get()->Error("In Triggering Checkpoints");
      is_step_success = false;
      break;
    }

    runtime_statistics_.StopMeasurement();
  }

  // Update the return with while loop state
  ret = is_step_success;

  bool is_app_prepared_to_terminate = app_iface_->PrepareForShutdown();
  if (!is_app_prepared_to_terminate) {
    daal::log::FrameworkLogger::get()->Error("Application failed to terminate");
    ret = false;
  }

  const bool is_app_terminated{app_iface_->Shutdown()};
  if (!is_app_terminated) {
    daal::log::FrameworkLogger::get()->Error("Failed to terminate the Application");
    ret = false;
  }

  if (ret) {
    exe_env_iface_->SetState(env::ExecutionEnvironment::State::kTerminate);
  }

  return ret;
}

void Executor::SetApplicationHandler(std::unique_ptr<app_handler::IApplicationHandler> app_handler) noexcept {
  if (nullptr != app_handler) {
    app_iface_ = std::move(app_handler);
    is_application_set_ = true;
  }
}

}  // namespace exe

}  // namespace af

}  // namespace daal
