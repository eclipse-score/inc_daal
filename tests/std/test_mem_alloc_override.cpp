/********************************************************************************
* Copyright (c) 2025 Contributors to the Eclipse Foundation
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

#include <gtest/gtest.h>

#include <stdexcept>

#ifdef DAAL_SAFETY_ENABLED
#include "daal/af/std/override_allocate_exception.h"
#endif


int foo() { throw std::runtime_error("error"); }


/*!
 * \brief Simple test for checking the exception memory allocation fails with
 * abort
 */
TEST(STD_lib_override, MemAllocOverride) {
  #ifdef DAAL_SAFETY_ENABLED
  EXPECT_DEATH(
      {
        try {
          foo();
        } catch (...) {
        }
      },
      "");
  #endif
}
