/********************************************************************************
* Copyright (c) {year} Contributors to the Eclipse Foundation
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
#ifndef SAMPLE_DEPARTMENT_H
#define SAMPLE_DEPARTMENT_H

#include <string>

class Department
{

  public:
    Department(int id, std::string name, int employee_nu);
    int GetEmployeeNumber();
    int GetID();
    std::string GetName();

  private:
    int id;
    std::string name;
    int employee_nu;
};

#endif  // SAMPLE_DEPARTMENT_H
