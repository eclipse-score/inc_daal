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

#ifndef SRC_DAAL_AF_CHECKPOINT_ICHECKPOINT_CONTAINER_H_
#define SRC_DAAL_AF_CHECKPOINT_ICHECKPOINT_CONTAINER_H_

#include <system_error>

#include "daal/af/checkpoint/icheckpoint.hpp"
#include "daal/af/checkpoint/when.hpp"

namespace daal {

namespace af {

namespace checkpoint {

/**
 * @class ICheckpointContainer
 * @brief Interface for a container that manages checkpoints.
 *
 * This interface defines the methods required for a container that handles
 * checkpoints. Implementations of this interface should provide mechanisms
 * to trigger and add checkpoints.
 */
class ICheckpointContainer {
 public:
  /**
   * @brief Default constructor for the ICheckpointContainer interface.
   */
  ICheckpointContainer() = default;
  /**
   * @brief Virtual destructor for the ICheckpointContainer interface.
   */
  virtual ~ICheckpointContainer() = default;

 protected:
  /**
   * @brief Copy constructor for the ICheckpointContainer interface.
   */
  ICheckpointContainer(const ICheckpointContainer &) = default;

  /**
   * @brief Copy assignment operator for the ICheckpointContainer interface.
   */
  ICheckpointContainer &operator=(const ICheckpointContainer &) & = default;

  /**
   * @brief Move constructor for the ICheckpointContainer interface.
   */
  ICheckpointContainer(ICheckpointContainer &&) = default;

  /**
   * @brief Move assignment operator for the ICheckpointContainer interface.
   */
  ICheckpointContainer &operator=(ICheckpointContainer &&) & = default;

 public:
  /**
   * @brief Triggers checkpoints based on the specified condition.
   *
   * @param when The condition under which checkpoints should be triggered.
   * @return std::error_code indicating the success or failure of the operation.
   */
  virtual std::error_code TriggerCheckpoints(When) const = 0;

  /**
   * @brief Adds a checkpoint to the container.
   *
   * @param checkpoint A shared pointer to the checkpoint to be added.
   * @return std::error_code indicating the success or failure of the operation.
   */
  virtual std::error_code AddCheckpoint(std::shared_ptr<ICheckpoint> checkpoint) = 0;
};

}  // namespace checkpoint
}  // namespace af
}  // namespace daal

#endif /* SRC_DAAL_AF_CHECKPOINT_ICHECKPOINT_CONTAINER_H_ */
