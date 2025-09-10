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

#ifndef SRC_DAAL_AF_APP_BASE_SAFE_APPLICATION_BASE_HPP
#define SRC_DAAL_AF_APP_BASE_SAFE_APPLICATION_BASE_HPP

namespace daal {

namespace af {
namespace app_base {

/*!
 * \brief Enum class for the state of the called function
 *
 */
enum class MethodState {
  kSuccessful = 0,
  kFailed = 1,
  kOnGoing = 2,  // NOTE: kOnGoing is not supported by every IApplicationHandler
};

/*!
 * \brief This is the interface for the application to implement.
 *
 */
class SafeApplicationBase {
 public:
  SafeApplicationBase() = default;
  SafeApplicationBase(const SafeApplicationBase &) = default;
  SafeApplicationBase(SafeApplicationBase &&) = default;
  SafeApplicationBase &operator=(const SafeApplicationBase &) & = default;
  SafeApplicationBase &operator=(SafeApplicationBase &&) & = default;
  virtual ~SafeApplicationBase() = default;

  /*!
   * \satisfy  @DNG_RM2_6510757 initialize Functions
   * \satisfy  @DNG_RM1_4276394
   * \brief Here the Application has to initialize.
   * After initialization privileges are dropped
   * All relevant init functions have to be called here
   * User is responsible to call all Init functions
   * of DriveOS/Libraries of AVOS and/or Adaptive here
   *
   * This function has to return and setup all interfaces.
   * In an event driven Application this function has to setup all the
   * events needed.
   *
   *
   * \return kSuccessful on successful initialization
   * \return kFailed on failed initialization
   * \return kOnGoing Application needs re-attempt
   */
  virtual MethodState OnInitialize() = 0;

  /*!
   * \brief The application should step normally, but use this state change to
   * undo other states and step normally again
   *
   *
   * \return kSuccessful Application is set to run normally
   * \return kOnGoing Application needs re-attempt
   * \return kFailed otherwise
   */
  virtual MethodState OnStart() = 0;

  /*!
   * \brief Periodically executed function - not executed in event driven
   * applications
   * \return kSuccessful if application should continue
   * \return kOnGoing shall not be used for step as it called periodically.
   * \return kFailed if the application is to shutdown
   */
  virtual MethodState Step() = 0;

  /*!
   * \brief The application shall prepare for the Termination state. Application
   * shall behave as if it received SIGTERM
   *
   *
   * \return kSuccessful if the preparation for Termination is successful
   * \return kOnGoing Application needs re-attempt
   * \return kFailed otherwise
   */
  virtual MethodState OnStop() = 0;

  /*!
   * \brief  Function called during shutdown
   * Application shall cleanup
   * deregister here the interfaces
   *
   * \return kSuccessful if de-initialisation done without error
   * \return kOnGoing Application needs re-attempt
   * \return kFailed if de-initialisation done with error
   */
  virtual MethodState OnTerminate() = 0;
};

}  // namespace app_base

}  // namespace af

}  // namespace daal

#endif  // SRC_DAAL_AF_APP_BASE_SAFE_APPLICATION_BASE_HPP
