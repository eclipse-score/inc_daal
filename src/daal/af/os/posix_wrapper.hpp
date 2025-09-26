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

#ifndef SRC_DAAL_AF_OS_POSIX_WRAPPER_H_
#define SRC_DAAL_AF_OS_POSIX_WRAPPER_H_

namespace daal {

namespace af {
namespace os {

using u_int_32 = unsigned long int;

class RLimit {
 public:
  u_int_32 soft_limit{};
  u_int_32 max_limit{};
  friend auto operator==(const RLimit &lhs, const RLimit &rhs) noexcept -> bool {
    return lhs.soft_limit == rhs.soft_limit && lhs.max_limit == rhs.max_limit;
  }
};

class IPosixWrapper {
 public:
  IPosixWrapper() = default;
  virtual ~IPosixWrapper() = default;

 protected:
  IPosixWrapper(const IPosixWrapper &) = default;
  auto operator=(const IPosixWrapper &) -> IPosixWrapper & = default;
  IPosixWrapper(IPosixWrapper &&) = default;
  auto operator=(IPosixWrapper &&) -> IPosixWrapper & = default;

 public:
  virtual auto SetRLimit(int resource, RLimit r_limits) -> int = 0;
  virtual auto GetRLimit(int resource) -> RLimit = 0;

  virtual void SetupOomHandler() = 0;
};
}  // namespace os

}  // namespace af

}  // namespace daal

#endif /* SRC_DAAL_AF_OS_POSIX_WRAPPER_H_ */
