..
   # *******************************************************************************
   # Copyright (c) 2025 Contributors to the Eclipse Foundation
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

.. dd_sta:: dd example static
    :id: dd_sta__example_feature__approver
    :security: NO
    :safety: ASIL_B
    :status: valid
    :implements: comp_req__example_feature__example_req
    :satisfies: comp_arc_sta__example_feature__comp_1
    :includes: sw_unit__example_feature__unit1, sw_unit__example_feature__unit2

.. uml:: dd_example_ex_sta.puml

Dynamic Diagrams for Unit Interactions
--------------------------------------

.. dd_dyn:: dd example dynamic
    :id: dd_dyn__example_feature__dynamic
    :security: NO
    :safety: ASIL_B
    :status: valid
    :implements: comp_req__example_feature__example_req
    :satisfies: comp_arc_sta__example_feature__comp_1

.. uml:: dd_example_ex_dyn.puml

Units within the Component
--------------------------
From here onwards the needs are defined in the source code and will be automatically generated and linked via doxygen.

SW Unit
*******

The unit description is generated from the source code and linked with
the need ID sw_unit__example_feature__unit1.

Interface
*********

The interface description is generated from the source code and linked with
the need ID sw_unit_int__example_feature__u1_i1.

SW Unit
*******

The unit description is generated from the source code and linked with
the need ID sw_unit__example_feature__unit2.

Interface
*********

The interface description is generated from the source code and linked with
the need ID sw_unit_int__example_feature__u2_i2.
