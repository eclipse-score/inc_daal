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

#ifndef APPLICATION_COMMON_DAAL_SF_RUNNER_EXECUTOR_EXECUTOR_H_
#define APPLICATION_COMMON_DAAL_SF_RUNNER_EXECUTOR_EXECUTOR_H_

namespace daal {

namespace af {
namespace exe {

/*!
 * \brief Interface for executor
 *
 */
class IExecutor {
 public:
  /*!
   * \brief Default Constructor
   *
   */
  IExecutor() = default;

  /*!
   * \brief Destructor
   *
   */
  virtual ~IExecutor() = default;

 protected:
  /*!
   * \brief Copy Constructor
   *
   */
  IExecutor(const IExecutor &) = default;

  /*!
   * \brief Copy assignment operator
   *
   */
  IExecutor &operator=(const IExecutor &) & = default;

  /*!
   * \brief Move Constructor
   *
   */
  IExecutor(IExecutor &&) = default;

  /*!
   * \brief Move assignment operator
   *
   */
  IExecutor &operator=(IExecutor &&) & = default;

 public:
  /*!
   * \brief This function shall initialize the application dependencies and do
   * the safety check.
   * This function shall be called before instantiating the application if
   * application intend to use the platform functions like log and platform
   * application client in the constructor.
   * \satisfy  @DNG_RM1_6510749 initialisation in order to use the platform
   *
   * \return true if the initialisation safety checks are successful.
   *
   * \return false if something went wrong.
   */
  virtual auto Init() -> bool = 0;

  /*!
   * \brief run the application in loop until terminate signal or application
   * returns false on step execution
   * \satisfy  @DNG_RM1_6510749 the method wile loop is the main loop of
   *
   * \return true if successful run
   *
   * \return false if run exited with error or application step returns false.
   */
  virtual auto Run() -> bool = 0;
};

}  // namespace exe

}  // namespace af

}  // namespace daal

#endif /* APPLICATION_COMMON_DAAL_SF_RUNNER_EXECUTOR_EXECUTOR_H_ */
