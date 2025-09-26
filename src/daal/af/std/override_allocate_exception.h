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

#ifndef APPLICATION_COMMON_DAAL_SF_RUNNER_STD_OVERRIDE_ALLOCATE_EXCEPTION_H_
#define APPLICATION_COMMON_DAAL_SF_RUNNER_STD_OVERRIDE_ALLOCATE_EXCEPTION_H_

#include <cstdlib>

/*!
 * \satisfy  @DNG_RM1_6510761
 * \brief This function will overwrite the memory allocation function for on
 * exceptions.
 *
 */
extern "C" void* __cxa_allocate_exception(size_t);

#endif /* APPLICATION_COMMON_DAAL_SF_RUNNER_STD_OVERRIDE_ALLOCATE_EXCEPTION_H_ \
        */
