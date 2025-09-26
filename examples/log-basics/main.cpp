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

#include <daal/log/logger.hpp>

int main() {
  auto logger = std::make_shared<daal::log::Logger>("MAIN");
  logger->AddDefaultSinks();

  logger->Info("Starting the DAAL log-basics application...");

  const int magic = 40 + 2;
  logger->Debug("We performed some crazy magicians tricks, the magic number is {}", magic);

  logger->Error("Nothing works, let's terminate with an error");

  return 1;
}
