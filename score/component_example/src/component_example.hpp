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

#ifndef SCORE_COMPONENT_EXAMPLE_COMPONENT_EXAMPLE_HPP_
#define SCORE_COMPONENT_EXAMPLE_COMPONENT_EXAMPLE_HPP_

#include <string>

namespace score {
namespace component_example {

// Unit
std::string make_hello();

// Component API
std::string make_hello_message(const std::string& name);

}  // namespace component_example
}  // namespace score

#endif  // SCORE_COMPONENT_EXAMPLE_COMPONENT_EXAMPLE_HPP_
