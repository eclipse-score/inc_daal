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

#ifndef APPLICATION_COMMON_DAAL_SAFE_RUNNER_OS_POSIX_HELPER_H_
#define APPLICATION_COMMON_DAAL_SAFE_RUNNER_OS_POSIX_HELPER_H_

namespace daal {

namespace af {
namespace os {

class IPosixHelper {
 public:
  /*!
   * \brief Default Constructor
   *
   */
  IPosixHelper() = default;

  /*!
   * \brief Destructor
   *
   */
  virtual ~IPosixHelper() = default;

  /*!
   * \satisfy  @DNG_RM1_6510845 applications shall not change the Environment
   * variable
   * \brief check if the given string exits in environment variable with
   * exception of ignore_string
   *
   * \param search_str string for searching the environment pattern
   * \param ignore_str string for ignoring the found match
   *
   * \return true if no variable match found
   *
   * \return false if a match found aprat from ignore string
   */
  virtual bool IsNoEnvVarSet(char const *search_str, char const *ignore_str) = 0;

  /*!
   * \satisfy  @DNG_RM1_7466955
   * \brief Check Floating Point Unit precision is as expected
   *
   *
   * \return true if the FPU is working
   *
   * \return false if FPU is not working
   */
  virtual bool IsFpuWorking(float f_precision) = 0;

  /*!
   * \satisfy  @DNG_RM1_4276394 if not prevented by  allowedToAllocateMemory
   this ensures no memory is allocated.
   * \satisfy  @DNG_RM1_6510985 prevent further process creation
   * \brief Drops all privileges unless allowedTo Function tells something
   different
   *
   */
  virtual bool DropPrivileges() = 0;

  /** function to setup the out of memory handler
   */
  virtual void SetupOomHandler() = 0;

 protected:
  /*!
   * \brief Copy Constructor
   *
   */
  IPosixHelper(const IPosixHelper &) = default;

  /*!
   * \brief Copy assignment operator
   *
   */
  IPosixHelper &operator=(const IPosixHelper &) & = default;

  /*!
   * \brief Move Constructor
   *
   */
  IPosixHelper(IPosixHelper &&) = default;

  /*!
   * \brief Move assignment operator
   *
   */
  IPosixHelper &operator=(IPosixHelper &&) & = default;
};

}  // namespace os

}  // namespace af

}  // namespace daal

#endif /* APPLICATION_COMMON_DAAL_SAFE_RUNNER_OS_POSIX_HELPER_H_ */
