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

Component Architecture Template
===============================

This page contains the component architecture template snippets that belong to the
module template repository.

Overview
--------

Use these snippets as the starting point for documenting component architecture in
the module template.

Static Architecture
-------------------

.. code-block:: rst

   .. comp:: Component Name
      :id: comp__mod_temp_component_name_template
      :security: YES
      :safety: ASIL_B
      :status: invalid
      :implements: logic_arc_int__feature_name__interface_name1
      :consists_of: comp__component_name_internal_1, comp__component_name_internal_2, comp__component_name_internal_3
      :belongs_to: feat__feature_name

   .. comp_arc_sta:: Component Name (Static View)
      :id: comp_arc_sta__mod_temp_component_name__sv
      :security: YES
      :safety: ASIL_B
      :status: invalid
      :belongs_to: comp__mod_temp_component_name_template
      :uses: logic_arc_int__feature_name__interface_name1
      :fulfils: comp_req__mod_temp_component_name__some_title

      .. needarch::
         :scale: 50
         :align: center

         {{ draw_component(need(), needs) }}

Dynamic Architecture
--------------------

.. code-block:: rst

   .. comp_arc_dyn:: Dynamic View
      :id: comp_arc_dyn__mod_temp_component_name__dv
      :security: YES
      :safety: ASIL_B
      :status: invalid
      :belongs_to: comp__mod_temp_component_name_template
      :fulfils: comp_req__mod_temp_component_name__some_title

      Put here a sequence diagram

Component Interface
-------------------

The rendered component-interface example is maintained here so the module template
repository owns the live ``real_arc_int`` example.

.. real_arc_int:: Component Interface 1
   :id: real_arc_int__mod_temp_component_name__if_1
   :status: valid
   :safety: ASIL_B
   :security: NO
   :language: cpp

   .. needarch::
      :scale: 50
      :align: center

      {{ draw_interface(need(), needs)}}

Internal Components
-------------------

.. code-block:: rst

   .. comp_arc_sta:: Component Name Static View
      :id: comp_arc_sta__mod_temp_component_name__2
      :status: invalid
      :safety: ASIL_B
      :security: YES
      :fulfils: comp_req__mod_temp_component_name__some_title
      :belongs_to: comp__mod_temp_component_name_template

      No architecture but detailed design

   .. comp:: Internal Component 1
      :id: comp__component_name_internal_1
      :status: invalid
      :safety: ASIL_B
      :security: YES
      :belongs_to: feat__feature_name

   .. comp:: Internal Component 2
      :id: comp__component_name_internal_2
      :status: invalid
      :safety: ASIL_B
      :security: YES
      :belongs_to: feat__feature_name

   .. comp:: Internal Component 3
      :id: comp__component_name_internal_3
      :status: invalid
      :safety: ASIL_B
      :security: YES
      :belongs_to: feat__feature_name
