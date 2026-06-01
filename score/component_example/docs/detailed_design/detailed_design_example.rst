..
   # *******************************************************************************
   # Copyright (c) 2026 Contributors to the Eclipse Foundation
   #
   # See the NOTICE file(s) distributed with this work for additional
   # information regarding copyright ownership.
   #
   # This program and the accompanying materials are made available under the
   # terms of the Apache License Version 2.0 which is available at
   # https://www.apache.org/licenses/LICENSE-2.0
   #
   # SPDX-License-Identifier: Apache-2.0
   # *******************************************************************************

Example: Detailed Design
========================

Description
-----------

 - component is split into two units unit1 and unit2 based on single responsibility principle.
 - unit2 is injected to unit1 one via dependency injection for testability.


Static Diagrams for Unit Interactions
-------------------------------------

.. uml:: dd_example_ex_sta.puml

Dynamic Diagrams for Unit Interactions (optional)
--------------------------------------------------

.. uml:: dd_example_ex_dyn.puml

Units within the Component
--------------------------

The units are defined in the source code. The relationship between a unit and the
component is established implicitly through the file path.

- unit1: implements the main logic (see source code for details)
- unit2: injected into unit1 via dependency injection for testability
