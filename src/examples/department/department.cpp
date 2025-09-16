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
#include "department.h"

#include <utility>

Department::Department(int id, std::string name, int employee_nu)
    : id(id), name(std::move(name)), employee_nu(employee_nu) {};

int Department::GetEmployeeNumber()
{
    return this->employee_nu;
}

std::string Department::GetName()
{
    return this->name;
}

int Department::GetID()
{
    return this->id;
}
