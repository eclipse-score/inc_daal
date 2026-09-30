# *******************************************************************************
# Copyright (c) 2026 Contributors to the Eclipse Foundation
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
load("@rules_cc//cc:defs.bzl", "cc_test")
load("@rules_rust//rust:defs.bzl", "rust_test")

rust_test(
    name = "feature_integration_tests_rust",
    size = "small",
    srcs = ["test_main.rs"],
)

cc_test(
    name = "feature_integration_tests_cpp",
    size = "small",
    srcs = ["test_main.cpp"],
    deps = [
        "//score/component_example",
        "@googletest//:gtest_main",  # GoogleTest dependency via Bazel Modules
    ],
)
