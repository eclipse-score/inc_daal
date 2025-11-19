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

## Logging

cc_binary(
    name = "log_basics",
    srcs = [
        "log-basics/main.cpp",
    ],
    deps = [
        "//src:daal_logger",
    ],
)

## Application Framework ##

cc_binary(
    name = "af_hello_world",
    srcs = [
        "af-hello-world/hello_world_app.hpp",
        "af-hello-world/main.cpp",
    ],
    deps = [
        "//src:daal_app_executor_builder",
        "//src:daal_app_handler_singleshot",
        "//src:daal_checkpoint",
        "//src:daal_logger",
        "//src:daal_os_helper",
        "//src:daal_trigger",
        "//src:dummy_execution_environment",
    ],
)

cc_library(
    name = "daal_score_mw_com",
    srcs = [
        "daal/af/score/mw_com_common.cpp",
        "daal/af/score/mw_log_common.cpp",
    ],
    hdrs = [
        "daal/af/score/mw_com_common.hpp",
        "daal/af/score/mw_log_common.hpp",
        "daal/af/score/score_exec_env.hpp",
    ],
    includes = ["."],
    visibility = ["//visibility:public"],
    deps = [
        "//src:execution_environment_interface",
        "@score_baselibs//score/mw/log",
        "@score_baselibs//score/result",
        "@score_communication//score/mw/com",
    ],
)
