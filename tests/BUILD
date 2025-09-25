#*******************************************************************************
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
#*******************************************************************************

cc_test(
    name = "test_application_handler_simple",
    srcs = [
        ":app_handler/test_simple_application_handler.cpp",
    ],
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    deps = [
        "//src:daal_app_handler_singleshot",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "os_wrapper_impl_mock",
    testonly = 1,
    hdrs = [
        "mocks/local/daal/af/os/details/posix_wrapper_impl.hpp",
    ],
    strip_include_prefix = "mocks/local",
    deps = ["mocks_helper"],
)

#
## OS wrapper test
cc_library(
    name = "sys_mocks_hdrs",
    testonly = 1,
    srcs = [
        "mocks/system/sys/resource.h",
        "mocks/system/sys/resource_fake.cpp",
        "mocks/system/sys/resource_fake.hpp",
    ],
    includes = ["mocks/system"],
    deps = [
        "mocks_helper",
        "@googletest//:gtest",
    ],
)

#
cc_test(
    name = "test_checkpoint_container",
    srcs = [
        ":checkpoint/test_checkpoint.cpp",
    ],
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    deps = [
        "//src:daal_checkpoint",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

#
cc_library(
    name = "mocks_helper",
    testonly = 1,
    srcs = [
        "mocks/helper/fake_object.h",
    ],
    includes = ["."],
)

#
cc_library(
    name = "env_ara_sig_wrap_mock",
    testonly = 1,
    srcs = [
        "mocks/local/daal/af/env/details/simple_signal_handler.hpp",
    ],
    includes = ["mocks/local/daal/af/env/details"],
    deps = [],
)

#
cc_test(
    name = "test_daal_sf_exception_throw",
    srcs = [
        ":std/test_mem_alloc_override.cpp",
    ],
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    deps = [
        "//src:daal_safe_application_base_hdrs",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

#
cc_library(
    name = "daal_steady_clock_mock",
    testonly = 1,
    hdrs = [
        "mocks/local/daal/af/trigger/details/daal_steady_clock.hpp",
    ],
    strip_include_prefix = "mocks/local",
    deps = ["mocks_helper"],
)

#
cc_library(
    name = "daal_activation_condition_mock",
    testonly = 1,
    hdrs = [
        "mocks/local/daal/af/trigger/details/trigger_activation_impl.hpp",
        "mocks/local/daal/af/trigger/details/trigger_condition_impl.hpp",
    ],
    strip_include_prefix = "mocks/local",
    deps = ["mocks_helper"],
)

cc_library(
    name = "iohandler_mock",
    testonly = 1,
    hdrs = [
        "mocks/local/daal/af/app_base/iohandler.hpp",
    ],
    strip_include_prefix = "mocks/local/",
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@googletest//:gtest",
    ],
)

cc_library(
    name = "daal_safe_applicaton_environment_mock",
    testonly = 1,
    hdrs = [
        "mocks/local/daal/af/env/details/dummy_exec_env.hpp",
    ],
    linkstatic = 1,
    strip_include_prefix = "mocks/local/",
    visibility = ["//visibility:public"],
    deps = [
        "//src:execution_environment_interface",
    ],
)

cc_library(
    name = "daal_safe_applicaton_os_helper_mock",
    testonly = 1,
    hdrs = [
        "mocks/local/daal/af/os/details/posix_helper_impl.hpp",
    ],
    linkstatic = 1,
    strip_include_prefix = "mocks/local",
    visibility = ["//visibility:public"],
    deps = ["//src:os_helper_interface"],
)

#
cc_library(
    name = "daal_safe_applicaton_trigger_mock",
    testonly = 1,
    hdrs = [
        "mocks/local/daal/af/trigger/details/trigger_impl.hpp",
    ],
    linkstatic = 1,
    strip_include_prefix = "mocks/local/",
    visibility = ["//visibility:public"],
    deps = ["//src:trigger_interface"],
)

cc_library(
    name = "daal_safe_applicaton_executor_mock",
    testonly = 1,
    hdrs = [
        "mocks/local/daal/af/exe/details/executor_impl.hpp",
    ],
    strip_include_prefix = "mocks/local/",
    visibility = ["//visibility:public"],
    deps = [
        "daal_safe_applicaton_environment_mock",
        "daal_safe_applicaton_os_helper_mock",
        "daal_safe_applicaton_trigger_mock",
        "//src:app_handler_interface",
        "//src:daal_checkpoint_interface",
    ],
)

cc_library(
    name = "dummy_exec_env_mock",
    testonly = 1,
    hdrs = [
        "mocks/local/daal/af/env/details/dummy_exec_env.hpp",
    ],
    includes = ["."],
    linkstatic = 1,
    strip_include_prefix = "mocks/local",
    visibility = ["//visibility:public"],
    deps = [],
)

#
cc_test(
    name = "test_application_handler_iterative",
    srcs = [
        ":app_handler/test_iterative_application_handler.cpp",
    ],
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    deps = [
        "//src:app_handler_iterative",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "test_daal_sf_qnx_os",
    srcs = [
        ":os/test_qnx_os_helper.cpp",
        "//src:daal/af/os/details/posix_helper_impl.cpp",
        "//src:daal/af/os/details/posix_wrapper_impl.cpp",
    ],
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    deps = [
        ":os_wrapper_impl_mock",
        "//src:daal_os_helper",
        "//src:os_helper_hdrs",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

#
cc_test(
    name = "test_daal_sf_qnx_os_helper",
    srcs = [
        ":os/test_os_wraper_impl.cpp",
        "//src:daal/af/os/details/posix_wrapper_impl.cpp",
        "//src:daal/af/os/posix_wrapper.hpp",
    ],
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    deps = [
        ":sys_mocks_hdrs",
        "//src:daal_os_helper",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

##
cc_test(
    name = "test_daal_sf_exception_crash",
    testonly = 1,
    srcs = [
        ":std/test_mem_alloc_crash.cpp",
    ],
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    deps = [
        "//src:daal_app_executor_bundle",
        "//src:daal_app_handler_singleshot",
        "//src:daal_null_checkpoint",
        "//src:daal_safe_application_base_hdrs",
        "//src:daal_os_helper",
        #       "//test:dummy_exec_env_mock",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "test_null_and_periodic_condition_activation_trigger",
    srcs = [
        ":trigger/test_null_triger_condition.cpp",
        ":trigger/test_periodic_activation.cpp",
        "//src:daal/af/trigger/details/trigger_activation_impl.cpp",
        "//src:daal/af/trigger/details/trigger_condition_impl.cpp",
    ],
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    deps = [
        "daal_steady_clock_mock",
        "//src:trigger_activation_condition_impl_hdrs",
        "//src:trigger_impl_hdrs",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

#
cc_test(
    name = "test_periodic_trigger",
    srcs = [
        ":trigger/test_periodic_trigger.cpp",
        "//src:daal/af/trigger/details/trigger_impl.cpp",
    ],
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    deps = [
        "daal_activation_condition_mock",
        "//src:trigger_impl_hdrs",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "test_daal_steady_clock",
    srcs = [
        ":trigger/test_daal_steady_clock.cpp",
    ],
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    deps = [
        "//src:daal_steady_clock",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

"""
# REMOVE
cc_test(
    name = "test_example_apps",
    testonly = 1,
    srcs = [
        "example_app/test_simple_app_main.cpp",
    ],
    data = [
        "//:dual_trigger_application",
        "//:simple_application",
    ],
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//src:dual_trigger_application",
        "//src:simple_application",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
"""

cc_test(
    name = "test_worker_thread",
    testonly = 1,
    srcs = [
        "worker/test_worker_thread.cpp",
    ],
    target_compatible_with = [
        "@platforms//os:linux",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//src:daal_worker_thread",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

test_suite(
    name = "daal_unit_test_suite",
    tests = [
        "test_application_handler_iterative",
        "test_application_handler_simple",
        "test_checkpoint_container",
        "test_daal_sf_exception_crash",
        "test_daal_sf_exception_throw",
        "test_daal_sf_qnx_os",
        "test_daal_sf_qnx_os_helper",
        "test_daal_steady_clock",
        "test_null_and_periodic_condition_activation_trigger",
        "test_periodic_trigger",
        "test_worker_thread",
    ],
)
