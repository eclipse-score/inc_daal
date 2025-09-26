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

#include "checkpoint_container.hpp"

#include <algorithm>
#include <iterator>
#include <string>
#include <system_error>

namespace daal {

namespace af {

namespace checkpoint {

CheckpointContainer::CheckpointContainer() : ICheckpointContainer() {}

std::error_code CheckpointContainer::AddCheckpoint(std::shared_ptr<ICheckpoint> checkpoint) {
  std::error_code error_code{};

  if (nullptr == checkpoint) {
    error_code = std::make_error_code(std::errc::invalid_argument);
  } else {
    auto when = checkpoint->GetWhen();
    auto check_item = [checkpoint](const std::shared_ptr<ICheckpoint> &item) {
      bool ret = item == checkpoint;
      ret = ret || item->GetName() == checkpoint->GetName();
      return ret;
    };
    switch (when) {
      case When::BEFORE:

        if (std::find_if(before_checkpoints.begin(), before_checkpoints.end(), check_item) ==
            before_checkpoints.end()) {
          before_checkpoints.push_back(checkpoint);
        } else {
          error_code = std::make_error_code(std::errc::invalid_argument);
        }
        break;
      case When::AFTER:
        if (std::find_if(after_checkpoints.begin(), after_checkpoints.end(), check_item) == after_checkpoints.end()) {
          after_checkpoints.push_back(checkpoint);
        } else {
          error_code = std::make_error_code(std::errc::invalid_argument);
        }
        break;
      default:
        error_code = std::make_error_code(std::errc::invalid_argument);
    }
  }

  return error_code;
}

std::error_code CheckpointContainer::TriggerCheckpoints(When when) const {
  std::error_code ec{};
  const auto &checkpoints = (when == When::BEFORE) ? before_checkpoints : after_checkpoints;
  for (const auto &checkpoint : checkpoints) {
    auto rec = checkpoint->Trigger();
    if (rec != std::error_code{}) {
      ec = rec;
    }
  }

  return ec;
}

}  // namespace checkpoint
}  // namespace af
}  // namespace daal
