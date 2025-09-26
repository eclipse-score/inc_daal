# *******************************************************************************
# Copyright (c) 2025 Contributors to the Eclipse Foundation
#
# See the NOTICE file(s) distributed with this work for additional
# information regarding copyright ownership.
#
# This program and the accompanying materials are made available under the
# terms of the Apache License Version 2.0 which is available at
# https://www.apache.org/licenses/LICENSE-2.0
#
# SPDX-License-Identifier: Apache-2.0
# *******************************************************************************

package(default_visibility = ["//visibility:public"])

## Config

cc_library(
    name = "daal_config_production",
    hdrs = [
        "config/production/config.hpp",
    ],
    include_prefix = "daal/af/config",
    strip_include_prefix = "config/production",
)

cc_library(
    name = "daal_config_debug",
    hdrs = [
        "config/debug/config.hpp",
    ],
    include_prefix = "daal/af/config",
    strip_include_prefix = "config/debug",
)

## Logging ##

cc_library(
    name = "daal_logger_config_production",
    hdrs = [
        "daal/log/config/production/logger_config.hpp",
    ],
    include_prefix = "daal/log/config",
    strip_include_prefix = "daal/log/config/production",
    deps = [
        ":daal_config_production",
    ],
)

cc_library(
    name = "daal_logger_config_debug",
    hdrs = [
        "daal/log/config/debug/logger_config.hpp",
    ],
    include_prefix = "daal/log/config",
    strip_include_prefix = "daal/log/config/debug",
    deps = [
        ":daal_config_debug",
    ],
)

cc_library(
    name = "daal_logger_hdrs",
    hdrs = [
        "daal/log/logger.hpp",
        "daal/log/logger_types.hpp",
        "daal/log/sink.hpp",
    ],
    includes = ["."],
    deps = select({
        "//:dev": [
            ":daal_logger_config_debug",
        ],
        "//conditions:default": [
            ":daal_logger_config_production",
        ],
    }) + [
        "@fmt",
    ],
)

cc_library(
    name = "daal_logger",
    srcs = [
        "daal/log/logger.cpp",
        "daal/log/sink.cpp",
    ],
    deps = [
        "daal_logger_default_sinks",
        "daal_logger_hdrs",
    ],
)

cc_library(
    name = "daal_framework_logger",
    hdrs = [
        "daal/log/framework_logger.hpp",
    ],
    deps = [
        "daal_logger",
    ],
)

cc_library(
    name = "daal_logger_console_sink",
    srcs = [
        "daal/log/details/console_sink.cpp",
    ],
    hdrs = [
        "daal/log/details/console_sink.hpp",
    ],
    deps = [
        "daal_logger_hdrs",
    ],
)

cc_library(
    name = "daal_logger_default_sinks",
    srcs = select({
        "@platforms//os:qnx": ["daal/log/details/logger_add_default_sinks_qnx.cpp"],
        "//conditions:default": ["daal/log/details/logger_add_default_sinks.cpp"],
    }),
    deps = [
        "daal_logger_console_sink",
    ],
)

## Application Framework ##

### app_base ###

cc_library(
    name = "daal_safe_application_base_hdrs",
    hdrs = [
        "daal/af/app_base/safe_application_base.hpp",
    ],
    includes = ["."],
)

cc_library(
    name = "daal_safe_application_base",
    linkstatic = 1,
    deps = [
        "daal_override_allocate_exception",
        "daal_safe_application_base_hdrs",
        "daal_std_terminate_override",
    ],
)

# This library is used for QM applications only.
cc_library(
    name = "daal_safe_application_base_qm",
    linkstatic = 1,
    deps = [
        "daal_safe_application_base_hdrs",
    ],
)

cc_library(
    name = "daal_iohandler",
    hdrs = [
        "daal/af/app_base/iohandler.hpp",
    ],
    deps = [
        "daal_safe_application_base_hdrs",
    ],
)

cc_library(
    name = "daal_override_allocate_exception",
    srcs = [
        "daal/af/std/override_allocate_exception.cpp",
    ],
    hdrs = [
        "daal/af/std/override_allocate_exception.h",
    ],
)

cc_library(
    name = "daal_std_terminate_override",
    srcs = [
        "daal/af/std/override_terminate.cpp",
    ],
    hdrs = [
        "daal/af/std/override_terminate.hpp",
    ],
    linkstatic = 1,
)

### app_handler ###

cc_library(
    name = "app_handler_interface",
    hdrs = [
        "daal/af/app_handler/iapplication_handler.hpp",
    ],
    linkstatic = 1,
)

cc_library(
    name = "daal_app_handler_sequentiallist",
    srcs = [
        "daal/af/app_handler/details/sequential_list_handler.cpp",
    ],
    hdrs = [
        "daal/af/app_handler/details/sequential_list_handler.hpp",
    ],
    linkstatic = 1,
    deps = [
        "app_handler_interface",
        "daal_safe_application_base_hdrs",
    ],
)

cc_library(
    name = "daal_app_handler_singleshot",
    hdrs = [
        "daal/af/app_handler/details/single_shot_app_handler.hpp",
    ],
    linkstatic = 1,
    deps = [
        "daal_app_handler_sequentiallist",
    ],
)

cc_library(
    name = "app_handler_iterative",
    srcs = [
        "daal/af/app_handler/details/iterative_application_handler.cpp",
    ],
    hdrs = [
        "daal/af/app_handler/details/iterative_application_handler.hpp",
    ],
    #    linkstatic = 1,
    deps = [
        "app_handler_interface",
        "daal_safe_application_base",
        "trigger_interface",
    ],
)

# TODO - Select for QNX
cc_library(
    name = "daal_worker_thread",
    srcs = [
        "daal/af/worker/linux_impl.cpp",
        "daal/af/worker/worker_thread.cpp",
    ],
    #    + select({
    #        "@platforms//os:linux": ["src/daal/af/worker/linux_impl.cpp"],
    #        "//conditions:default": ["src/daal/af/worker/qnx_impl.cpp"],
    #    }),
    hdrs = [
        "daal/af/worker/worker_thread.hpp",
    ],
    linkstatic = 1,
    deps = [
        "daal_framework_logger",
    ],
)

### checkpoint ###

cc_library(
    name = "daal_checkpoint_interface",
    hdrs = [
        "daal/af/checkpoint/icheckpoint.hpp",
        "daal/af/checkpoint/icheckpoint_container.hpp",
        "daal/af/checkpoint/when.hpp",
    ],
    includes = ["."],
    linkstatic = 1,
)

cc_library(
    name = "daal_checkpoint",
    srcs = [
        "daal/af/checkpoint/details/checkpoint_container.cpp",
    ],
    hdrs = [
        "daal/af/checkpoint/details/checkpoint_container.hpp",
    ],
    linkstatic = 1,
    deps = [
        "daal_checkpoint_interface",
    ],
)

cc_library(
    name = "daal_null_checkpoint",
    hdrs = [
        "daal/af/checkpoint/details/null_checkpoint_container.hpp",
    ],
    linkstatic = 1,
    deps = [
        "daal_checkpoint_interface",
    ],
)

### env ###

cc_library(
    name = "execution_environment_interface",
    hdrs = [
        "daal/af/env/execution_environment.hpp",
    ],
    includes = ["."],
    linkstatic = 1,
)

cc_library(
    name = "signal_handler",
    srcs = [
        "daal/af/env/details/simple_signal_handler.cpp",
    ],
    hdrs = [
        "daal/af/env/details/simple_signal_handler.hpp",
    ],
    linkstatic = 1,
    deps = [
        "daal_framework_logger",
    ],
)

cc_library(
    name = "dummy_execution_environment",
    hdrs = [
        "daal/af/env/details/dummy_exec_env.hpp",
    ],
    includes = ["."],
    linkstatic = 1,
    deps = [
        "execution_environment_interface",
        "signal_handler",
    ],
)

cc_library(
    name = "daal_safe_application_environment",
    linkstatic = 1,
    deps = select(
        {
            "@platforms//os:linux": [
                "dummy_execution_environment",
            ],
        },
    ) + [
        "daal_safe_application_base",
    ],
)

### exe ###

cc_library(
    name = "daal_app_executor_builder",
    hdrs = [
        "daal/af/exe/builder/executor_builder.hpp",
    ],
    linkstatic = 1,
    deps = [
        "daal_app_executor",
    ],
)

cc_library(
    name = "daal_app_executor",
    srcs = [
        "daal/af/exe/details/executor_impl.cpp",
    ],
    hdrs = [
        "daal/af/exe/details/executor_impl.hpp",
        "daal/af/exe/iexecutor.hpp",
    ],
    linkstatic = 1,
    deps = [
        "app_handler_interface",
        "daal_checkpoint_interface",
        "daal_framework_logger",
        "execution_environment_interface",
        "os_helper_interface",
        "runtime_statistics",
        "trigger_interface",
    ],
)

cc_library(
    name = "daal_app_executor_bundle",
    deps = [
        "daal_app_executor",
        "daal_app_executor_builder",
        "daal_checkpoint",
        "daal_os_helper",
        "daal_safe_application_environment",
        "daal_trigger",
    ],
)

### os ###

cc_library(
    name = "os_helper_interface",
    hdrs = [
        "daal/af/os/posix_helper.hpp",
    ],
)

cc_library(
    name = "os_helper_hdrs",
    hdrs = [
        "daal/af/os/posix_wrapper.hpp",
    ],
    deps = [
        "os_helper_interface",
    ],
)

cc_library(
    name = "daal_os_helper",
    srcs = [
        "daal/af/os/details/posix_helper_impl.cpp",
        "daal/af/os/details/posix_wrapper_impl.cpp",
    ],
    hdrs = [
        "daal/af/os/details/posix_helper_impl.hpp",
        "daal/af/os/details/posix_wrapper_impl.hpp",
    ],
    linkstatic = 1,
    deps = [
        "daal_framework_logger",
        "os_helper_hdrs",
    ],
)

### runtime_statistics ###

cc_library(
    name = "runtime_statistics",
    srcs = [
        "daal/af/runtime_statistics/details/console_backend.cpp",
        "daal/af/runtime_statistics/details/file_backend.cpp",
        "daal/af/runtime_statistics/runtime_statistics.cpp",
    ] + select({
        "@platforms//os:linux": [
            "daal/af/runtime_statistics/details/platform_linux.cpp",
            "daal/af/runtime_statistics/details/time_provider_linux_impl.cpp",
        ],
        "//conditions:default": [
            "daal/af/runtime_statistics/details/platform_qnx.cpp",
            "daal/af/runtime_statistics/details/time_provider_qnx_impl.cpp",
        ],
    }),
    hdrs = [
        "daal/af/runtime_statistics/config/runtime_statistics_config.hpp",
        "daal/af/runtime_statistics/details/console_backend.hpp",
        "daal/af/runtime_statistics/details/file_backend.hpp",
        "daal/af/runtime_statistics/details/platform.hpp",
        "daal/af/runtime_statistics/reporting_backend.hpp",
        "daal/af/runtime_statistics/runtime_statistics.hpp",
        "daal/af/runtime_statistics/time_provider.hpp",
    ],
    features = [
        "libm",
    ],
    includes = ["."],
    linkstatic = 1,
)

### trigger ###

cc_library(
    name = "trigger_interface",
    hdrs = [
        "daal/af/trigger/trigger.hpp",
        "daal/af/trigger/trigger_activation.hpp",
        "daal/af/trigger/trigger_condition.hpp",
    ],
    linkstatic = 1,
)

cc_library(
    name = "trigger_impl_hdrs",
    hdrs = [
        "daal/af/trigger/details/daal_steady_clock.hpp",
        "daal/af/trigger/details/trigger_activation_impl.hpp",
        "daal/af/trigger/details/trigger_condition_impl.hpp",
        "daal/af/trigger/details/trigger_impl.hpp",
    ],
    includes = ["."],
    deps = [
        "daal_framework_logger",
        "trigger_interface",
    ],
)

cc_library(
    name = "trigger_activation_condition_impl_hdrs",
    hdrs = [
        "daal/af/trigger/details/trigger_activation_impl.hpp",
        "daal/af/trigger/details/trigger_condition_impl.hpp",
    ],
    deps = ["trigger_impl_hdrs"],
)

cc_library(
    name = "daal_trigger",
    srcs = [
        "daal/af/trigger/details/trigger_activation_impl.cpp",
        "daal/af/trigger/details/trigger_condition_impl.cpp",
        "daal/af/trigger/details/trigger_impl.cpp",
    ],
    linkstatic = 1,
    deps = [
        "daal_framework_logger",
        "daal_steady_clock",
        "trigger_activation_condition_impl_hdrs",
    ],
)

cc_library(
    name = "daal_steady_clock",
    hdrs = [
        "daal/af/trigger/details/daal_steady_clock.hpp",
    ],
    linkstatic = 1,
)
