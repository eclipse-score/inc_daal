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

#ifndef SRC_DAAL_AF_CHECKPOINT_DETAILS_DUMMY_CHECKPOINT_HPP
#define SRC_DAAL_AF_CHECKPOINT_DETAILS_DUMMY_CHECKPOINT_HPP

#include <string>
#include <system_error>

#include "daal/af/checkpoint/icheckpoint.hpp"
#include "daal/af/checkpoint/when.hpp"

namespace daal {
namespace af {
namespace monitoring {

/**
 * @class DummyCheckpoint
 * @brief A dummy implementation of the ICheckpoint interface.
 *
 * The DummyCheckpoint class provides a simple implementation of the
 * ICheckpoint interface, primarily for testing and demonstration purposes.
 */
class DummyCheckpoint : public daal::af::checkpoint::ICheckpoint {
 public:
  /**
   * @brief Constructor for DummyCheckpoint.
   * @param name The name of the checkpoint.
   * @param when The condition under which the checkpoint is triggered.
   */
  DummyCheckpoint(std::string name, daal::af::checkpoint::When when);

  /**
   * @brief Destructor for DummyCheckpoint.
   */
  ~DummyCheckpoint() override = default;

  /**
   * @brief Triggers the checkpoint.
   * @return A std::error_code indicating the result of the trigger operation.
   */
  auto Trigger() -> std::error_code override;

  /**
   * @brief Gets the condition under which the checkpoint is triggered.
   * @return The condition under which the checkpoint is triggered.
   */
  auto GetWhen() const noexcept -> daal::af::checkpoint::When override;

  /**
   * @brief Gets the name of the checkpoint.
   * @return The name of the checkpoint.
   */
  auto GetName() const noexcept -> const std::string & override;

 protected:
  /**
   * @brief Default constructor for DummyCheckpoint.
   */
  DummyCheckpoint() = default;

  /**
   * @brief Copy constructor for DummyCheckpoint.
   */
  DummyCheckpoint(const DummyCheckpoint &) = default;

  /**
   * @brief Copy assignment operator for DummyCheckpoint.
   */
  DummyCheckpoint &operator=(const DummyCheckpoint &) & = default;

  /**
   * @brief Move constructor for DummyCheckpoint.
   */
  DummyCheckpoint(DummyCheckpoint &&) noexcept = default;

  /**
   * @brief Move assignment operator for DummyCheckpoint.
   */
  DummyCheckpoint &operator=(DummyCheckpoint &&) &noexcept = default;

 private:
  std::string name_;                 ///< The name of the checkpoint.
  daal::af::checkpoint::When when_;  ///< The condition under which the checkpoint is triggered.
};

}  // namespace monitoring
}  // namespace af
}  // namespace daal

#endif  // SRC_DAAL_AF_CHECKPOINT_DETAILS_DUMMY_CHECKPOINT_HPP
