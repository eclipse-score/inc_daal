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

/**
 * \file application_handler.hpp
 * \brief Defines the interface class IApplicationHandler for handling
 * application execution.
 *
 * This file contains the declaration of the interface class
 * IApplicationHandler, which is responsible for handling the execution of an
 * application. It provides methods for setting the application, initializing,
 * resetting, executing, preparing for shutdown, and shutting down the
 * application.
 */

#ifndef SRC_DAAL_AF_APP_HANDLER_IAPPLICATION_HANDLER_HPP
#define SRC_DAAL_AF_APP_HANDLER_IAPPLICATION_HANDLER_HPP

namespace daal {

namespace af {

namespace app_handler {

/**
 * \class IApplicationHandler
 * \brief Interface class for handling application execution.
 *
 * The IApplicationHandler class defines an interface for handling the execution
 * of an application. It provides pure virtual methods for setting the
 * application, initializing, resetting, executing, preparing for shutdown, and
 * shutting down the application.
 */
class IApplicationHandler {
 public:
  /**
   * \brief Constructor.
   */
  IApplicationHandler() = default;
  /**
   * \brief Destructor.
   */
  virtual ~IApplicationHandler() = default;

  /**
   * \brief Initializes the application.
   * \return True if the initialization is successful, false otherwise.
   */
  virtual bool Initialize() = 0;

  /**
   * \brief Resets the application.
   * \return True if the reset is successful, false otherwise.
   */
  virtual bool PrepareForExecute() = 0;

  /**
   * \brief Executes the application.
   * \return True if the execution is successful, false otherwise.
   */
  virtual bool Execute() = 0;
  /**
   * \brief Prepares the application for shutdown.
   * \return True if the preparation is successful, false otherwise.
   */
  virtual bool PrepareForShutdown() = 0;

  /**
   * \brief Shuts down the application.
   * \return True if the shutdown is successful, false otherwise.
   */
  virtual bool Shutdown() = 0;

 protected:
  /**
   * \brief Copy constructor.
   */
  IApplicationHandler(const IApplicationHandler &) = default;

  /**
   * \brief Copy assignment operator.
   */
  IApplicationHandler &operator=(const IApplicationHandler &) & = default;

  /**
   * \brief Move constructor.
   */
  IApplicationHandler(IApplicationHandler &&) = default;

  /**
   * \brief Move assignment operator.
   */
  IApplicationHandler &operator=(IApplicationHandler &&) & = default;
};

}  // namespace app_handler

}  // namespace af

}  // namespace daal

#endif  // SRC_DAAL_AF_APP_HANDLER_IAPPLICATION_HANDLER_HPP
