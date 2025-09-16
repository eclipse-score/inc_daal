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
#include <iostream>

#include "company.h"

int main(int /* argc */, char** /* argv */)
{

    Company awesome_company("SuperAwesome Inc.");
    std::cout << "Company name: " << awesome_company.GetName() << '\n';

    awesome_company.AddDepartment(13, "QX-57", 26262);  // NOLINT(cppcoreguidelines-avoid-magic-numbers)

    auto department = awesome_company.GetDepartmentByName("QX-57");
    if (department)
    {
        std::cout << "Department ID: " << department->GetID() << '\n';
    }

    return 0;
}
