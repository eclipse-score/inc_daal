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

#ifndef SRC_DAAL_AF_CHECKPOINT_DETAILS_CHECKPOINT_CONTAINER_HPP
#define SRC_DAAL_AF_CHECKPOINT_DETAILS_CHECKPOINT_CONTAINER_HPP

#include <memory>
#include <system_error>
#include <vector>

#include "daal/af/checkpoint/icheckpoint.hpp"
#include "daal/af/checkpoint/icheckpoint_container.hpp"
#include "daal/af/checkpoint/when.hpp"

namespace daal {

namespace af {

namespace checkpoint {

/**
 * @class CheckpointContainer
 * @brief A container class for managing checkpoints.
 *
 * The CheckpointContainer class provides functionality to add and trigger
 * checkpoints. It maintains separate lists for checkpoints that should be
 * triggered before and after certain events.
 */
class CheckpointContainer : public ICheckpointContainer {
 public:
  /**
   * @brief Default constructor for CheckpointContainer.
   */
  CheckpointContainer();

  /**
   * @brief Default destructor for CheckpointContainer.
   */
  ~CheckpointContainer() override = default;

  /**
   * @brief Adds a checkpoint to the container, in given order to its respective
   * type (When::BEFORE or When::AFTER).
   *
   * @param checkpoint A shared pointer to the checkpoint to be added.
   * @return std::error_code indicating success or failure of the operation.
   */
  std::error_code AddCheckpoint(std::shared_ptr<ICheckpoint> checkpoint) override;

  /**
   * @brief Triggers all checkpoints for a given event.
   *
   * @param when The event for which checkpoints should be triggered.
   * @return std::error_code indicating success or failure of the operation.
   */
  std::error_code TriggerCheckpoints(When when) const override;

 protected:
  /**
   * @brief Deleted copy constructor for CheckpointContainer.
   */
  CheckpointContainer(const CheckpointContainer &) = default;
  /**
   * @brief Deleted copy assignment operator for CheckpointContainer.
   */
  CheckpointContainer &operator=(const CheckpointContainer &) & = default;
  /**
   * @brief Deleted move constructor for CheckpointContainer.
   */
  CheckpointContainer(CheckpointContainer &&) = default;
  /**
   * @brief Deleted move assignment operator for CheckpointContainer.
   */
  CheckpointContainer &operator=(CheckpointContainer &&) & = default;

 private:
  std::vector<std::shared_ptr<ICheckpoint>> before_checkpoints{};  ///< Checkpoints to be triggered before events.
  std::vector<std::shared_ptr<ICheckpoint>> after_checkpoints{};   ///< Checkpoints to be triggered after events.
};

}  // namespace checkpoint
}  // namespace af
}  // namespace daal

#endif  // SRC_DAAL_AF_CHECKPOINT_DETAILS_CHECKPOINT_CONTAINER_HPP
