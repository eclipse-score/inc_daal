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
#ifndef SAMPLE_COMPANY_H
#define SAMPLE_COMPANY_H

#include "department.h"
#include <list>
#include <optional>
#include <vector>

class Company
{

  public:
    explicit Company(std::string name);
    std::string GetName();
    void AddDepartment(int id, std::string dep_name, int employee_nu);
    std::optional<Department> GetDepartmentByName(const std::string& name);
    size_t GetNumberOfDepartments();

  private:
    std::string name;
    std::list<Department> departments;
};

#endif  // SAMPLE_COMPANY_H
