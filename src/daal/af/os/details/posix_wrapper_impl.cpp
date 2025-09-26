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

#include "posix_wrapper_impl.hpp"

#include <sys/resource.h>

#include <utility>
// needed for abort
//  @DNG_RM1_6510758
#include <cstdlib>
#include <new>

#include "daal/log/framework_logger.hpp"

namespace daal {

namespace af {

namespace os {

int PosixWrapper::SetRLimit(const int resource, const RLimit r_limits) noexcept {
  struct rlimit r_limit;
  r_limit.rlim_cur = r_limits.soft_limit;
  r_limit.rlim_max = r_limits.max_limit;
  return this->setrlimit(resource, &r_limit);
}

RLimit PosixWrapper::GetRLimit(const int resource) {
  struct rlimit r_limit {};
  // Ignore the return as the set value will be checked later
  int ret = this->getrlimit(resource, &r_limit);
  if (ret == -1) {
    daal::log::FrameworkLogger::get()->Error("Get rlimit");
  }
  RLimit local_limit;
  local_limit.soft_limit = r_limit.rlim_cur;
  local_limit.max_limit = r_limit.rlim_max;
  return local_limit;
}

/*
 See https://en.cppreference.com/w/cpp/memory/new/set_new_handler
 Handler function to be executed in case of new fails.

 @DNG_RM1_6510758 handler to be called if allocation fails

*/
void bad_alloc_handler() {
  // note this message may be lost
  daal::log::FrameworkLogger::get()->Error("Out of memory");
  ;
  abort();
}

void PosixWrapper::SetupOomHandler() {
  // Terminate in case of bad allocations
  // @DNG_RM1_6510758
  std::new_handler previous_handler = std::set_new_handler(bad_alloc_handler);
  (void)previous_handler;  // Explicitly discard the return value if not used
}

template <typename... Args>
int PosixWrapper::setrlimit(Args &&...args) noexcept {
  return ::setrlimit(std::forward<Args>(args)...);
}

template <typename... Args>
int PosixWrapper::getrlimit(Args &&...args) noexcept {
  return ::getrlimit(std::forward<Args>(args)...);
}

}  // namespace os

}  // namespace af

}  // namespace daal
