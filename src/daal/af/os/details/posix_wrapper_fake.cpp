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

#include <stdlib.h>
#include <sys/resource.h>

#include <cstdlib>

#include "daal/af/os/posix_wrapper.hpp"
#include "daal/log/framework_logger.hpp"
#include "posix_wrapper_impl.hpp"

// needed for abort
//  @DNG_RM1_6510758
#include <stdlib.h>

namespace daal {

namespace af {

namespace os {

int PosixWrapper::SetRLimit(const int resource, const RLimit r_limits) {
  struct rlimit r_limit {};
  r_limit.rlim_cur = r_limits.soft_limit;
  r_limit.rlim_max = r_limits.max_limit;
  return this->setrlimit(resource, &r_limit);
}

RLimit PosixWrapper::GetRLimit(const int resource) {
  struct rlimit r_limit {};
  // Ignore the return as the set value will be checked later
  this->getrlimit(resource, &r_limit);
  RLimit local_limit;
  local_limit.soft_limit = r_limit.rlim_cur;
  local_limit.max_limit = r_limit.rlim_max;
  return local_limit;
}

template <typename... Args>
int PosixWrapper::setrlimit(Args &&...args) noexcept {
  return EXIT_SUCCESS;
}

template <typename... Args>
int PosixWrapper::getrlimit(Args &&...args) noexcept {
  return EXIT_SUCCESS;
}

/*
 See https://en.cppreference.com/w/cpp/memory/new/set_new_handler
 Handler function to be executed in case of new fails.

 @DNG_RM1_6510758 handler to be called if allocation fails

*/
void handler() { abort(); }

void PosixWrapper::SetupOomHandler() {
  // Terminate in case of bad allocations
  // this is also added here as the unit test is using the fake by default
  // @DNG_RM1_6510758
  daal::log::FrameworkLogger::get()->info("OOm Handler installed - fake");
  std::set_new_handler(handler);
}

}  // namespace os

}  // namespace af

}  // namespace daal
