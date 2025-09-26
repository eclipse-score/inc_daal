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
    deps = [
        "//src:execution_environment_interface",
        "@communication//score/mw/com",
        "@score-baselibs//score/mw/log",
        "@score-baselibs//score/result",
    ],
)

package(default_visibility = ["//visibility:public"])

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
        "af-hello-world/main.cpp",
        "af-hello-world/hello_world_app.hpp",
    ],
    deps = [
        "//src:daal_logger",
        "//src:daal_app_handler_singleshot",
        "//src:daal_checkpoint",
        "//src:dummy_execution_environment",
        "//src:daal_app_executor_builder",
        "//src:daal_os_helper",
        "//src:daal_trigger",
    ],
)

cc_library(
    name = "daal_score_mw_com",
    hdrs = [
        "daal/af/score/mw_com_common.hpp",
        "daal/af/score/mw_log_common.hpp",
        "daal/af/score/score_exec_env.hpp"
    ],
    srcs = [
        "daal/af/score/mw_com_common.cpp",
        "daal/af/score/mw_log_common.cpp",
    ],
    includes = ["."],
    deps = [
        "@communication//score/mw/com",
        "@score-baselibs//score/mw/log",
        "@score-baselibs//score/result",
        "//src:execution_environment_interface",
    ]
)
