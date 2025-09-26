package(default_visibility = ["//visibility:public"])

cc_library(
    name = "score_vss_steering_client",
    hdrs = [
        "spec/steering_request.hpp",
    ],
    includes = ["."],
)

cc_library(
    name = "adas_vehicle_control_io",
    hdrs = [
        "adas-vehicle-control/io/steering_wheel_client.hpp",
        "adas-vehicle-control/io/vehicle_control_io_container.hpp",
        "spec/impl/score_mw_com.hpp",
    ],
    includes = ["adas-vehicle-control"],
    deps = [
        "score_vss_steering_client",
        "//examples:daal_score_mw_com",
        "//src:daal_iohandler",
    ],
)

cc_library(
    name = "adas_vehicle_control_io_impl_score",
    srcs = [
        "adas-vehicle-control/io/impl/steering_wheel_client_score.cpp",
    ],
    hdrs = [
        "adas-vehicle-control/io/impl/steering_wheel_client_score.hpp",
    ],
    includes = ["adas-vehicle-control"],
    deps = [
        "adas_vehicle_control_io",
        "score_vss_steering_client",
        "//examples:daal_score_mw_com",
    ],
)

cc_library(
    name = "adas_vehicle_control_app",
    srcs = [
        "adas-vehicle-control/vehicle_control_app.cpp",
    ],
    hdrs = [
        "adas-vehicle-control/vehicle_control_app.hpp",
    ],
    deps = [
        "adas_vehicle_control_io",
        "//src:daal_logger",
    ],
)

cc_binary(
    name = "adas_vehicle_control",
    srcs = [
        "adas-vehicle-control/main_vehicle_control_app.cpp",
    ],
    data = ["etc/mw_com_config.json"],
    deps = [
        "adas_vehicle_control_app",
        "adas_vehicle_control_io_impl_score",
        "score_vss_steering_client",  # TODO: remove
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
    name = "steering_wheel_io",
    hdrs = [
        "steering-wheel/io/steering_wheel_io_container.hpp",
        "steering-wheel/io/steering_wheel_server.hpp",
    ],
    includes = ["steering-wheel"],
    deps = [
        "//src:daal_iohandler",
    ],
)

cc_library(
    name = "steering_wheel_io_impl_score",
    srcs = [
        "steering-wheel/io/impl/steering_wheel_server_score.cpp",
    ],
    hdrs = [
        "spec/impl/score_mw_com.hpp",
        "steering-wheel/io/impl/steering_wheel_server_score.hpp",
    ],
    includes = [
        ".",
        "steering-wheel",
    ],
    deps = [
        "score_vss_steering_client",
        "steering_wheel_io",
        "//examples:daal_score_mw_com",
    ],
)

cc_binary(
    name = "steering_wheel",
    srcs = [
        "steering-wheel/main_steering_wheel_app.cpp",
        "steering-wheel/steering_wheel_app.cpp",
        "steering-wheel/steering_wheel_app.hpp",
    ],
    data = ["etc/mw_com_config.json"],
    visibility = ["//visibility:public"],
    deps = [
        "steering_wheel_io_impl_score",
        "//src:daal_app_executor_builder",
        "//src:daal_app_handler_singleshot",
        "//src:daal_checkpoint",
        "//src:daal_logger",
        "//src:daal_os_helper",
        "//src:daal_trigger",
        "//src:dummy_execution_environment",
    ],
)

## Stub executables ##

cc_binary(
    name = "stub_adas_vehicle_control",
    srcs = [
        "adas-vehicle-control/test/main_vehicle_control_stub.cpp",
        "adas-vehicle-control/test/steering_wheel_client_stub.hpp",
        "adas-vehicle-control/vehicle_control_app.cpp",
        "adas-vehicle-control/vehicle_control_app.hpp",
    ],
    data = ["etc/mw_com_config.json"],
    visibility = ["//visibility:public"],
    deps = [
        "adas_vehicle_control_io",
        "score_vss_steering_client",
        "//src:daal_app_executor_builder",
        "//src:daal_app_handler_singleshot",
        "//src:daal_checkpoint",
        "//src:daal_logger",
        "//src:daal_os_helper",
        "//src:daal_trigger",
        "//src:dummy_execution_environment",
    ],
)
