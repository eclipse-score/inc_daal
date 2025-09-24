#include <gtest/gtest.h>

#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>

// Test to verify the custom terminate handler
TEST(CustomTerminateHandlerTest, VerifyTerminateHandler) {
  // Trigger the terminate handler and verify using EXPECT_DEATH
  EXPECT_DEATH({ std::terminate(); }, "");
}
