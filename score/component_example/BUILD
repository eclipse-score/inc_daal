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

load("@score_docs_as_code//:docs.bzl", "docs_bundle")

cc_library(
    name = "component_example",
    srcs = ["src/component_example.cpp"],
    hdrs = ["src/component_example.hpp"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "component_example_unit_tests",
    size = "small",
    srcs = ["src/component_example_test.cpp"],
    deps = [
        ":component_example",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "component_example_component_integration_tests",
    size = "small",
    srcs = ["tests/component_example_test.cpp"],
    deps = [
        ":component_example",
        "@googletest//:gtest_main",
    ],
)

docs_bundle(
    name = "docs",
    code_targets = [
        ":component_example",
    ],
    source_dir = "docs",
    visibility = ["//visibility:public"],
)
