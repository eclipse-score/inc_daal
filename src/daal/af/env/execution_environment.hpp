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

#ifndef APPLICATION_COMMON_DAAL_SF_RUNNER_ENVIRONMENT_EXECUTION_ENVIRONMENT_H_
#define APPLICATION_COMMON_DAAL_SF_RUNNER_ENVIRONMENT_EXECUTION_ENVIRONMENT_H_

namespace daal {

namespace af {
namespace env {

/*!
 * \brief Inteface is for execution environment
 * Concrete implementation Executor will use this interface to interact with
 * concrete ExecutionEnvironment
 */
class ExecutionEnvironment {
 public:
  /*!
   * \brief this state is for reporting to the run time environment
   *
   */
  enum class State : int { kRunning, kTerminate };
  /*!
   * \brief Configuration for Process polling
   *
   */
  enum class ProcessingModes : int { kThreadDriven, kPolling };
  /*!
   * \brief Destructor
   *
   */
  virtual ~ExecutionEnvironment() = default;

  /*!
   * \brief Default Constructor
   *
   */
  ExecutionEnvironment() = default;

 protected:
  /*!
   * \brief Copy Constructor
   *
   */
  ExecutionEnvironment(const ExecutionEnvironment &) = default;

  /*!
   * \brief Move Constructor
   *
   */
  ExecutionEnvironment(ExecutionEnvironment &&) = default;

  /*!
   * \brief Copy Assignment
   *
   */
  ExecutionEnvironment &operator=(const ExecutionEnvironment &) & = default;

  /*!
   * \brief Move Assignment
   *
   */
  ExecutionEnvironment &operator=(ExecutionEnvironment &&) & = default;

 public:
  /*!
   * \satisfy  @DNG_RM1_6510757 initialize Functions
   * \brief initialize the run time environment
   *
   *
   * \return true if initialisation is successful
   *
   * \return false if initialisation is not successful
   */
  virtual bool Init() = 0;

  /*!
   * \brief Drop the active resources and maintain the valid state of objects
   *
   *
   * \return true if de-initialisation is successful
   *
   * \return false if de-initialisation is not successful
   */
  virtual bool Deinit() = 0;

  /*!
   * \brief Set the state object and report it to the runtime environment
   *
   */
  virtual void SetState(const State) noexcept = 0;

  /*!
   * \brief check if the kill/terminate signals are received
   *
   *
   * \return true if kill/terminate signals are received
   *
   * \return false if no kill/terminate signals are received
   */
  virtual bool IsSigTerm() const noexcept = 0;

  /*!
   * \brief Refresh the state of the execution environment
   * This is to be called periodically to update the state of the execution
   * Implementor shall read and send the state to the runtime environment
   *
   * \return true
   *
   * \return false
   */
  virtual bool Refresh() const noexcept = 0;
};

}  // namespace env

}  // namespace af

}  // namespace daal

#endif /* APPLICATION_COMMON_DAAL_SF_RUNNER_ENVIRONMENT_EXECUTION_ENVIRONMENT_H_ \
        */
