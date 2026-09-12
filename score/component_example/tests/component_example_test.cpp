/********************************************************************************
 * Copyright (c) 2026 Contributors to the Eclipse Foundation
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

#include "score/component_example/src/component_example.hpp"

#include <gtest/gtest.h>
#include <string>

namespace score {
namespace component_example {

// Component Integration Test (CIT) for component_example component.
TEST(ComponentExampleTest, MakeHelloMessageReturnsExpectedGreeting) {
    EXPECT_EQ(make_hello_message("World"), "Hello, World!");
    EXPECT_EQ(make_hello_message("SCORE"), "Hello, SCORE!");
}

}  // namespace component_example
}  // namespace score
