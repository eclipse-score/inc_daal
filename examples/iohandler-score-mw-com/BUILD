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
        "adas-vehicle-control/io/vehicle_control_io_container.hpp",
        "adas-vehicle-control/io/steering_wheel_client.hpp",
        "spec/impl/score_mw_com.hpp",
    ],
    includes = ["adas-vehicle-control"],
    deps = [
        "//examples:daal_score_mw_com",
        "//src:daal_iohandler",
        "score_vss_steering_client",
    ]
)

cc_library(
    name = "adas_vehicle_control_io_impl_score",
    hdrs = [
        "adas-vehicle-control/io/impl/steering_wheel_client_score.hpp",
    ],
    srcs = [
        "adas-vehicle-control/io/impl/steering_wheel_client_score.cpp",
    ],
    includes = ["adas-vehicle-control"],
    deps = [
        "adas_vehicle_control_io",
        "//examples:daal_score_mw_com",
        "score_vss_steering_client",
    ]
)

cc_library(
    name = "adas_vehicle_control_app",
    hdrs = [
        "adas-vehicle-control/vehicle_control_app.hpp",
    ],
    srcs = [
        "adas-vehicle-control/vehicle_control_app.cpp",
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
    deps = [
        "//src:daal_logger",
        "//src:daal_app_handler_singleshot",
        "//src:daal_checkpoint",
        "//src:dummy_execution_environment",
        "//src:daal_app_executor_builder",
        "//src:daal_os_helper",
        "//src:daal_trigger",
        "score_vss_steering_client", # TODO: remove
        "adas_vehicle_control_io_impl_score",
        "adas_vehicle_control_app",
    ],
    data = ["etc/mw_com_config.json"],
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
    ]
)

cc_library(
    name = "steering_wheel_io_impl_score",
    hdrs = [
        "steering-wheel/io/impl/steering_wheel_server_score.hpp",
        "spec/impl/score_mw_com.hpp",
    ],
    srcs = [
        "steering-wheel/io/impl/steering_wheel_server_score.cpp",
    ],
    includes = ["steering-wheel", "."],
    deps = [
        "steering_wheel_io",
        "//examples:daal_score_mw_com",
        "score_vss_steering_client",
    ]
)

cc_binary(
    name = "steering_wheel",
    srcs = [
        "steering-wheel/steering_wheel_app.cpp",
        "steering-wheel/steering_wheel_app.hpp",
        "steering-wheel/main_steering_wheel_app.cpp",
    ],
    deps = [
        "//src:daal_logger",
        "//src:daal_app_handler_singleshot",
        "//src:daal_checkpoint",
        "//src:dummy_execution_environment",
        "//src:daal_app_executor_builder",
        "//src:daal_os_helper",
        "//src:daal_trigger",
        "steering_wheel_io_impl_score"
    ],
    data = ["etc/mw_com_config.json"],
    visibility = ["//visibility:public"],
)

## Stub executables ##

cc_binary(
    name = "stub_adas_vehicle_control",
    srcs = [
        "adas-vehicle-control/vehicle_control_app.cpp",
        "adas-vehicle-control/vehicle_control_app.hpp",
        "adas-vehicle-control/test/main_vehicle_control_stub.cpp",
        "adas-vehicle-control/test/steering_wheel_client_stub.hpp",
    ],
    deps = [
        "//src:daal_logger",
        "//src:daal_app_handler_singleshot",
        "//src:daal_checkpoint",
        "//src:dummy_execution_environment",
        "//src:daal_app_executor_builder",
        "//src:daal_os_helper",
        "//src:daal_trigger",
        "score_vss_steering_client",
        "adas_vehicle_control_io",
    ],
    data = ["etc/mw_com_config.json"],
    visibility = ["//visibility:public"],
)
