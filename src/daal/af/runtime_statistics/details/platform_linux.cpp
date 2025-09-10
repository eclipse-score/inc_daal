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

#include <sys/stat.h>
#include <sys/types.h>

#include "platform.hpp"

namespace daal {
namespace af {
namespace runtime_statistics {

bool Platform::isFileBackendEnabled() {
  struct stat info;
  return stat(getFilePath().c_str(), &info) == 0;
}

std::string Platform::getFilePath() { return "/tmp/"; }

}  // namespace runtime_statistics
}  // namespace af
}  // namespace daal
