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

#ifndef SRC_DAAL_AF_OS_DETAILS_POSIX_WRAPPER_IMPL_H_
#define SRC_DAAL_AF_OS_DETAILS_POSIX_WRAPPER_IMPL_H_

#include "daal/af/os/posix_wrapper.hpp"

namespace daal {

namespace af {

namespace os {

void bad_alloc_handler();

class PosixWrapper : public IPosixWrapper {
 public:
  PosixWrapper() = default;
  ~PosixWrapper() override = default;

  auto SetRLimit(const int resource, const RLimit r_limits) noexcept -> int override;
  auto GetRLimit(const int resource) -> RLimit override;

  void SetupOomHandler() override;

 protected:
  PosixWrapper(const PosixWrapper &) = default;
  PosixWrapper &operator=(const PosixWrapper &) & = default;
  PosixWrapper(PosixWrapper &&) noexcept = default;
  PosixWrapper &operator=(PosixWrapper &&) &noexcept = default;

 private:
  template <typename... Args>
  auto setrlimit(Args &&...args) noexcept -> int;

  template <typename... Args>
  auto getrlimit(Args &&...args) noexcept -> int;
};

}  // namespace os

}  // namespace af

}  // namespace daal

#endif /* SRC_DAAL_AF_OS_DETAILS_POSIX_WRAPPER_IMPL_H_ */
