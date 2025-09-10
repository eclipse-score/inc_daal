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

#ifndef APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_MOCKS_SYS_RESOURCE_H_
#define APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_MOCKS_SYS_RESOURCE_H_

using rlim_t = unsigned long int;

struct rlimit {
  rlim_t rlim_cur; /* Soft limit */
  rlim_t rlim_max; /* Hard limit (ceiling for rlim_cur) */
};

// fake functions
int getrlimit(int resource, struct rlimit *rlim);
int setrlimit(int resource, const struct rlimit *rlim);

#endif /* APPLICATION_COMMON_DAAL_SF_RUNNER_TEST_MOCKS_SYS_RESOURCE_H_ */
