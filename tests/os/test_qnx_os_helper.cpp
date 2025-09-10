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

#include <string>

#include "daal/af/os/details/posix_helper_impl.hpp"
#include "daal/af/os/details/posix_wrapper_impl.hpp"
#include "mocks/local/daal/af/os/details/posix_wrapper_impl.hpp"

/*!
 * \brief manages the fake objects for every test fixtures
 *
 */
class PosixHelper : public ::testing::Test {
 protected:
  void SetUp() override {
    fake = FakeObject<daal::af::os::OSWrapperMock>::GetFakeObject();
  }

  void TearDown() override {
    FakeObject<daal::af::os::OSWrapperMock>::RemoveFakeObject();
  }

  std::shared_ptr<daal::af::os::OSWrapperMock> fake;
  daal::af::os::PosixHelper test_obj;
};

/*!
 * \brief Test the IsNoEnvVarSet with boundary conditions and valid and invalid
 * parameters
 *
 */
TEST_F(PosixHelper, isNoEnvVarsetValidEnv) {
  std::string varName = "ASMR_VALID";
  std::string varValue = "abcd";
  setenv(varName.c_str(), varValue.c_str(), 1);
  EXPECT_TRUE(test_obj.IsNoEnvVarSet("ASMR_", "ASMR_VALID"));
  varName = "ASMR_INVALID";
  varValue = "xyz";
  setenv(varName.c_str(), varValue.c_str(), 1);
  EXPECT_FALSE(test_obj.IsNoEnvVarSet("ASMR_", "ASMR_VALID"));

  varName = "ASMR_INVALID2";
  varValue = "xyz";
  setenv(varName.c_str(), varValue.c_str(), 1);
  EXPECT_FALSE(test_obj.IsNoEnvVarSet("ASMR_", "ASMR_VALID"));
}

/*!
 * \brief Test the IsNoEnvVarSet with boundary conditions and valid and invalid
 * parameters
 *
 */
TEST_F(PosixHelper, isNoEnvVarsetInValidEnv) {
  EXPECT_FALSE(test_obj.IsNoEnvVarSet("", ""));
}

/*!
 * \brief Test the IsFpuWorking with boundary conditions and valid and invalid
 * parameters
 *
 */
TEST_F(PosixHelper, IsFpuWorking) {
  // Invalid precision
  EXPECT_FALSE(test_obj.IsFpuWorking(1e-9f));
  EXPECT_FALSE(test_obj.IsFpuWorking(-1e-9f));
  EXPECT_FALSE(test_obj.IsFpuWorking(-340));
  EXPECT_FALSE(test_obj.IsFpuWorking(340));
  EXPECT_FALSE(test_obj.IsFpuWorking(0.1f));

  // Valid precision to check
  EXPECT_TRUE(test_obj.IsFpuWorking(0.000001f));
  EXPECT_TRUE(test_obj.IsFpuWorking(0.00001f));
}

/*!
 * \brief Normal expected flow for the DropPrivileges where set and get limits
 * are valid
 * TODO: https://issue.swf.i.mercedes-benz.com/browse/ADASDAI-161969 should fix
 * it
 */
TEST_F(PosixHelper, dropPrivilegesValidReturns) {
  daal::af::os::RLimit get_limits{0, 0};

  EXPECT_CALL(*fake, SetRLimit(testing::_, testing::_))
      .Times(3)
      .WillOnce(testing::Return(0))
      .WillOnce(testing::Return(0))
      .WillOnce(testing::Return(0));

  EXPECT_CALL(*fake, GetRLimit(testing::_))
      .Times(3)
      .WillOnce(testing::Return(get_limits))
      .WillOnce(testing::Return(get_limits))
      .WillOnce(testing::Return(get_limits));
  EXPECT_TRUE(test_obj.DropPrivileges());
}

/*!
 * \brief Test for the failure of the setrlimit in system call
 * TODO: https://issue.swf.i.mercedes-benz.com/browse/ADASDAI-161969 should fix
 * it
 */
TEST_F(PosixHelper, dropPrivilegesInValidSet) {
  EXPECT_CALL(*fake, SetRLimit(testing::_, testing::_))
      .Times(3)
      .WillOnce(testing::Return(-1))
      .WillOnce(testing::Return(-1))
      .WillOnce(testing::Return(-1));
  EXPECT_CALL(*fake, GetRLimit(testing::_)).Times(0);
  EXPECT_FALSE(test_obj.DropPrivileges());
}

/*!
 * \brief Test for the failure of the getrlimit in system call
 * TODO: https://issue.swf.i.mercedes-benz.com/browse/ADASDAI-161969 should fix
 * it
 */
TEST_F(PosixHelper, dropPrivilegesInValidGetReturn) {
  daal::af::os::RLimit get_limits{100, 100};

  EXPECT_CALL(*fake, GetRLimit(testing::_))
      .Times(3)
      .WillOnce(testing::Return(get_limits))
      .WillOnce(testing::Return(get_limits))
      .WillOnce(testing::Return(get_limits));
  EXPECT_FALSE(test_obj.DropPrivileges());
}
/*!
 * \brief Test the DropPrivileges function with environment variables set to
 * disable memory privilege drop
 */
TEST_F(PosixHelper, dropPrivilegesMemoryDisabled) {
  setenv("DAAL_DISABLE_MEMORY_PRIVILEGE_DROP", "1", 1);
  EXPECT_CALL(*fake, SetRLimit(testing::_, testing::_)).Times(2);
  EXPECT_TRUE(test_obj.DropPrivileges());
  unsetenv("DAAL_DISABLE_MEMORY_PRIVILEGE_DROP");
}

/*!
 * \brief Test the DropPrivileges function with environment variables set to
 * disable fork privilege drop
 */
TEST_F(PosixHelper, dropPrivilegesForkDisabled) {
  setenv("DAAL_DISABLE_FORK_PRIVILEGE_DROP", "1", 1);
  EXPECT_CALL(*fake, SetRLimit(testing::_, testing::_)).Times(2);
  EXPECT_TRUE(test_obj.DropPrivileges());
  unsetenv("DAAL_DISABLE_FORK_PRIVILEGE_DROP");
}

/*!
 * \brief Test the DropPrivileges function with environment variables set to
 * disable file privilege drop
 */
TEST_F(PosixHelper, dropPrivilegesFileDisabled) {
  setenv("DAAL_DISABLE_FILE_PRIVILEGE_DROP", "1", 1);
  EXPECT_CALL(*fake, SetRLimit(testing::_, testing::_)).Times(2);
  EXPECT_TRUE(test_obj.DropPrivileges());
  unsetenv("DAAL_DISABLE_FILE_PRIVILEGE_DROP");
}

/*!
 * \brief Test the DropPrivileges function with all environment variables set to
 * disable privilege drops
 */
TEST_F(PosixHelper, dropPrivilegesAllDisabled) {
  setenv("DAAL_DISABLE_MEMORY_PRIVILEGE_DROP", "1", 1);
  setenv("DAAL_DISABLE_FORK_PRIVILEGE_DROP", "1", 1);
  setenv("DAAL_DISABLE_FILE_PRIVILEGE_DROP", "1", 1);
  EXPECT_CALL(*fake, SetRLimit(testing::_, testing::_)).Times(0);
  EXPECT_TRUE(test_obj.DropPrivileges());
  unsetenv("DAAL_DISABLE_MEMORY_PRIVILEGE_DROP");
  unsetenv("DAAL_DISABLE_FORK_PRIVILEGE_DROP");
  unsetenv("DAAL_DISABLE_FILE_PRIVILEGE_DROP");
}

/*!
 * \brief Test the DropPrivileges function with no environment variables set
 */
TEST_F(PosixHelper, dropPrivilegesNoEnvVars) {
  daal::af::os::RLimit get_limits{0, 0};

  EXPECT_CALL(*fake, SetRLimit(testing::_, testing::_))
      .Times(3)
      .WillOnce(testing::Return(0))
      .WillOnce(testing::Return(0))
      .WillOnce(testing::Return(0));

  EXPECT_CALL(*fake, GetRLimit(testing::_))
      .Times(3)
      .WillOnce(testing::Return(get_limits))
      .WillOnce(testing::Return(get_limits))
      .WillOnce(testing::Return(get_limits));
  EXPECT_TRUE(test_obj.DropPrivileges());
}

/*!
 * \brief Test the SetupOomHandler function
 *
 */
TEST_F(PosixHelper, SetupOomHandler) {
  // Check that the function does not throw any exceptions
  EXPECT_CALL(*fake, SetupOomHandler()).Times(1);
  test_obj.SetupOomHandler();
}