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

#ifndef SRC_DAAL_AF_STD_OVERRIDE_TERMINATE_H_
#define SRC_DAAL_AF_STD_OVERRIDE_TERMINATE_H_

#include <cfenv>
#include <cstdlib>
#include <exception>

namespace daal {
namespace af {
namespace std_override {

// Static initializer to set the custom terminate handler
class TerminateHandlerInitializer {
 public:
  /**
   * @brief Constructor that initializes the custom terminate handler.
   *
   * This constructor sets a custom terminate handler (`CustomTerminate`)
   * to be invoked when the program encounters an unhandled exception or
   * calls `std::terminate`. The custom handler ensures the program
   * aborts immediately for safety reasons, as stack unwinding is not
   * expected to be used in this context.
   *
   * \satisfy @DNG_RM1_4274981
   * @note This is a noexcept constructor to guarantee it does not throw
   *       exceptions during initialization.
   */
  TerminateHandlerInitializer() noexcept;

  /**
   * @brief Custom terminate handler.
   *
   * This function is called when the program encounters an unhandled
   * exception or calls `std::terminate`. It aborts the program immediately
   * for safety reasons, as stack unwinding is not expected to be used in
   * this context.
   *
   * \satisfy @DNG_RM1_4274980
   */
  static void CustomTerminate() noexcept;
};

}  // namespace std_override
}  // namespace af
}  // namespace daal

#endif /* SRC_DAAL_AF_STD_OVERRIDE_TERMINATE_H_ */
