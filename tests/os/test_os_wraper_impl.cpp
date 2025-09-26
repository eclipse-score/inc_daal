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

#include <sys/resource_fake.hpp>

#include "src/daal/af/os/details/posix_wrapper_impl.hpp"

class OSWrapperTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  void TearDown() override { FakeSysRLimit::RemoveFakeObject(); }

  daal::af::os::PosixWrapper test_object;
  FakeSysRLimit& fake = *FakeSysRLimit::GetFakeObject();
};

/*!
 * \brief Test the function call forwarding done correctly for GetRlimit
 *
 */
TEST_F(OSWrapperTest, TestGetFunctionMap) {
  EXPECT_CALL(fake, GetLimit(::testing::_, ::testing::_)).Times(1);
  test_object.GetRLimit(0);
}

/*!
 * \brief Test the function call forwarding done correctly for SetRlimit
 *
 */
TEST_F(OSWrapperTest, TestSetFunctionMap) {
  EXPECT_CALL(fake, SetLimit(::testing::_, ::testing::_)).Times(1);

  daal::af::os::RLimit set{0, 0};
  EXPECT_TRUE(0 == test_object.SetRLimit(0, set));
}

// Custom handler for testing purposes
void testHandler() {
  std::cout << "Test handler called\n";
  abort();
}
/*!
 * \brief Test the function call forwarding done correctly for SetupOomHandler
 *
 */
TEST(OSWrapper, SetupOomHandler) {
  daal::af::os::PosixWrapper test_obj;
  std::set_new_handler(testHandler);

  // Verify that the current handler is the testHandler
  EXPECT_EQ(std::get_new_handler(), testHandler);
  test_obj.SetupOomHandler();
  // Get the current new handler
  std::new_handler currentHandler = std::get_new_handler();

  // Check if the current handler is the PosixWrapper handler
  EXPECT_EQ(currentHandler, daal::af::os::bad_alloc_handler);
}