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
#include "company.h"

#include <utility>

Company::Company(std::string name) : name(std::move(name)) {};

std::string Company::GetName()
{
    return this->name;
}

void Company::AddDepartment(int id, std::string dep_name, int employee_nu)
{
    this->departments.push_back(Department(id, std::move(dep_name), employee_nu));
}

std::optional<Department> Company::GetDepartmentByName(const std::string& sname)
{
    std::list<Department>::iterator it;

    for (it = this->departments.begin(); it != this->departments.end(); ++it)
    {
        if (sname.compare((*it).GetName()) == 0)
        {
            return *it;
        }
    }

    return std::nullopt;
}

size_t Company::GetNumberOfDepartments()
{
    return this->departments.size();
}
