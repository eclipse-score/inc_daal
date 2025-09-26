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

#ifndef APPLICATION_COMMON_DAAL_SAFE_RUNNER_APPLICATION_HANDLER_DETAILS_ITERATIVE_APPLICATION_HANDLER_H_
#define APPLICATION_COMMON_DAAL_SAFE_RUNNER_APPLICATION_HANDLER_DETAILS_ITERATIVE_APPLICATION_HANDLER_H_

#include <ctime>
#include <functional>

#include "daal/af/app_base/safe_application_base.hpp"
#include "daal/af/app_handler/iapplication_handler.hpp"
#include "daal/af/trigger/trigger.hpp"

/**
 * \file iterative_application_handler.hpp
 * \brief Contains the definition of the IterativeApplicationHandler class.
 */

namespace daal {

namespace af {

namespace app_handler {

/**
 * \class Attempts
 * \brief Represents the number of attempts for a specific operation.
 */
class Attempts {
 public:
  /**
   * \brief Constructs an Attempts object with the specified maximum number of
   * attempts.
   * \param max_attempts The maximum number of attempts.
   */
  Attempts(size_t max_attempts) noexcept : max_attempts_{max_attempts}, current_attempt_{0} {}

  /**
   * \brief Checks if the maximum number of attempts has been reached.
   * \return True if the maximum number of attempts has been reached, false
   * otherwise.
   */
  auto IsMaxAttemptsReached() const noexcept -> bool;

  /**
   * \brief Pre-increment overload.
   * \return A reference to the incremented Attempts object.
   */
  auto operator++() noexcept -> Attempts &;

 private:
  size_t max_attempts_;     ///< The maximum number of attempts.
  size_t current_attempt_;  ///< The current attempt count.
};

class PhaseAttempts {
 public:
  PhaseAttempts(Attempts initialize_attempts_, Attempts prepare_for_execute_attempts_,
                Attempts prepare_for_shutdown_attempts_, Attempts shutdown_attempts_) noexcept
      : initialize_attempts{initialize_attempts_},
        prepare_for_execute_attempts{prepare_for_execute_attempts_},
        prepare_for_shutdown_attempts{prepare_for_shutdown_attempts_},
        shutdown_attempts{shutdown_attempts_} {}
  Attempts initialize_attempts;
  Attempts prepare_for_execute_attempts;
  Attempts prepare_for_shutdown_attempts;
  Attempts shutdown_attempts;
};

/**
 * \class IterativeApplicationHandler
 * \brief Represents an iterative application handler.
 */
class IterativeApplicationHandler : public IApplicationHandler {
 public:
  /**
   * \brief Constructs an IterativeApplicationHandler object with the specified
   * safe application and iteration attempts.
   * \param application The safe application.
   * \param iteration_attempts The iteration attempts.
   */
  IterativeApplicationHandler(daal::af::app_base::SafeApplicationBase &application, daal::af::trigger::Trigger &trigger,
                              PhaseAttempts phase_attempts) noexcept;

  /**
   * \brief Default destructor.
   */
  ~IterativeApplicationHandler() override = default;

  /**
   * \brief Initializes the application.
   * \return True if the initialization was successful, false otherwise.
   */
  bool Initialize() override;

  /**
   * \brief Prepares for the application execution.
   * \return True if the preparation was successful, false otherwise.
   */
  bool PrepareForExecute() override;

  /**
   * \brief Executes the application.
   * \return True if the execution was successful, false otherwise.
   * \note This function is not iterative.
   */
  bool Execute() override;

  /**
   * \brief Prepares for the application shutdown.
   * \return True if the preparation was successful, false otherwise.
   */
  bool PrepareForShutdown() override;

  /**
   * \brief Shuts down the application.
   * \return True if the shutdown was successful, false otherwise.
   */
  bool Shutdown() override;

 protected:
  /**
   * \brief Deleted copy constructor.
   */
  IterativeApplicationHandler(const IterativeApplicationHandler &) = delete;

  /**
   * \brief Deleted copy assignment operator.
   */
  IterativeApplicationHandler &operator=(const IterativeApplicationHandler &) & = delete;

  /**
   * \brief Deleted move constructor.
   */
  IterativeApplicationHandler(IterativeApplicationHandler &&) = delete;

  /**
   * \brief Deleted move assignment operator.
   */
  IterativeApplicationHandler &operator=(IterativeApplicationHandler &&) & = delete;

 private:
  bool RunPhase(Attempts &attempt_current, std::function<daal::af::app_base::MethodState()> &phase);

  daal::af::app_base::SafeApplicationBase &application_;  ///< The safe application.
  daal::af::trigger::Trigger &trigger_;
  PhaseAttempts phase_attempts_;  ///< The iteration attempts.
};

}  // namespace app_handler

}  // namespace af

}  // namespace daal

#endif /* APPLICATION_COMMON_DAAL_SAFE_RUNNER_APPLICATION_HANDLER_DETAILS_ITERATIVE_APPLICATION_HANDLER_H_ \
        */
