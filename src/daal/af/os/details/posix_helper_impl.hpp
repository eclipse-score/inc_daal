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

#ifndef SRC_DAAL_AF_OS_DETAILS_POSIX_HELPER_IMPL_H_
#define SRC_DAAL_AF_OS_DETAILS_POSIX_HELPER_IMPL_H_

#include <unistd.h>

#include "daal/af/os/details/posix_wrapper_impl.hpp"
#include "daal/af/os/posix_helper.hpp"
#include "daal/af/os/posix_wrapper.hpp"

namespace daal {

namespace af {

namespace os {

class PosixHelper : public IPosixHelper {
 public:
  // Default constructor
  PosixHelper() = default;

  // Destructor
  ~PosixHelper() override = default;

  auto DropPrivileges() -> bool override;
  auto IsNoEnvVarSet(char const *search_str, char const *ignore_str) -> bool override;

  auto IsFpuWorking(float f_precision) -> bool override;

  /** function to setup the out of memory handler
   */
  void SetupOomHandler() override;

 protected:
  // Copy constructor
  PosixHelper(const PosixHelper &) = default;

  // Copy assignment operator
  PosixHelper &operator=(const PosixHelper &) & = default;

  // Move constructor
  PosixHelper(PosixHelper &&) noexcept = default;

  // Move assignment operator
  PosixHelper &operator=(PosixHelper &&) &noexcept = default;

 private:
  PosixWrapper os_wrapper_;

  auto SetAndVerifyRLimit(int resource, u_int_32 soft_limit, u_int_32 max_limit) -> bool;
};

}  // namespace os

}  // namespace af

}  // namespace daal

#endif /* SRC_DAAL_AF_OS_DETAILS_POSIX_HELPER_IMPL_H_ */
