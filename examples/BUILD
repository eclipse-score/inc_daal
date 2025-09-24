# Needed for Dash tool to check python dependency licenses.
filegroup(
    name = "cargo_lock",
    srcs = [
        "Cargo.lock",
    ],
    visibility = ["//visibility:public"],
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
