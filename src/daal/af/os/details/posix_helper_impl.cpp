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

#include "posix_helper_impl.hpp"

#include <cstdlib>
#include <cstring>
// TODO RLIMIT_AS.. are only dependency
#include <sys/resource.h>

#include <cmath>

#include "daal/log/framework_logger.hpp"

extern char **environ;

namespace daal {

namespace af {

namespace os {

auto PosixHelper::IsNoEnvVarSet(char const *search_str, char const *ignore_str) -> bool {
  bool ret{true};
  if (search_str != nullptr && strlen(search_str) > 0 && ignore_str != nullptr && strlen(ignore_str) > 0) {
    char **env = environ;

    while (*env) {
      // check if given env token contains the search string
      if (strstr(*env, search_str) != nullptr) {
        // check if it is ignore string, if so ignore
        if (strstr(*env, ignore_str) != nullptr) {
          // Ignore ignore string
        } else {
          // env var found a match without the ignore
          daal::log::FrameworkLogger::get()->Error("Found a match in env var {}", *env);
          ret = false;
          break;
        }
      }
      env++;
    }
  } else {
    daal::log::FrameworkLogger::get()->Error("Search string or ignore string cannot be NULL or empty");
    ret = false;
  }
  return ret;
}

constexpr float kFpuPrecisionThreshold = 0.001F;
constexpr float kFpuTestValue = 2.0F;

auto PosixHelper::IsFpuWorking(float f_precision) -> bool {
  bool ret{false};
  if (kFpuPrecisionThreshold > f_precision) {
    float f_2{kFpuTestValue};
    float sqr_2 = (f_2 >= 0.0F) ? std::sqrt(f_2) : 0.0F;
    float mul_2 = sqr_2 * sqr_2;
    float f_abs_diff = std::fabs(mul_2 - f_2);
    ret = (f_abs_diff < f_precision);
  }

  return ret;
}

auto PosixHelper::DropPrivileges() -> bool { return true; }

auto PosixHelper::SetAndVerifyRLimit(const int resource, const u_int_32 soft_limit, const u_int_32 max_limit) -> bool {
  RLimit r_limits{soft_limit, max_limit};
  int ret = os_wrapper_.SetRLimit(resource, r_limits);
  if (EXIT_SUCCESS != ret) {
    return false;
  }

  RLimit g_limits = os_wrapper_.GetRLimit(resource);

  return (r_limits == g_limits);
}
void PosixHelper::SetupOomHandler() { os_wrapper_.SetupOomHandler(); }

}  // namespace os

}  // namespace af

}  // namespace daal
