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

#ifndef SRC_DAAL_AF_CHECKPOINT_ICHECKPOINT_H_
#define SRC_DAAL_AF_CHECKPOINT_ICHECKPOINT_H_

#include <system_error>

#include "daal/af/checkpoint/when.hpp"

namespace daal {

namespace af {

namespace checkpoint {

class ICheckpoint {
 public:
  /*!
   * \brief Interface for checkpoint
   *
   */
  ICheckpoint() = default;

  /*!
   * \brief Destructor
   *
   */
  virtual ~ICheckpoint() = default;

 protected:
  /*!
   * \brief Copy Constructor
   *
   */
  ICheckpoint(const ICheckpoint &) = default;

  /*!
   * \brief Move Constructor
   *
   */
  ICheckpoint(ICheckpoint &&) = default;

  /*!
   * \brief Copy assignment operator
   *
   */
  ICheckpoint &operator=(const ICheckpoint &) & = default;

  /*!
   * \brief Move assignment operator
   *
   */
  ICheckpoint &operator=(ICheckpoint &&) & = default;

 public:
  /*!
   * \brief This function shall trigger the checkpoint
   *
   * \return std::error_code
   *
   */
  virtual std::error_code Trigger() = 0;

  /*!
   * \brief This function shall return the when the checkpoint should be
   * triggered
   *
   * \return When
   *
   */
  virtual When GetWhen() const = 0;

  /*!
   * \brief This function shall return the name of the checkpoint
   *
   * \return std::string
   *
   */
  virtual std::string const &GetName() const = 0;
};

}  // namespace checkpoint
}  // namespace af
}  // namespace daal

#endif /* SRC_DAAL_AF_CHECKPOINT_ICHECKPOINT_H_ */
