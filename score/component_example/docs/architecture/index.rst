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

.. _component_architecture_template:

Component Architecture
======================

.. document:: [Your Component Name] Architecture
   :id: doc__mod_temp_component_name_architecture
   :status: draft
   :safety: ASIL_B
   :security: NO
   :realizes: wp__component_arch
   :tags: template

.. attention::
    The above directive must be updated according to your needs.

    - Modify ``Your Component Name`` to be your Component Name
    - Modify ``id`` to be your Component Name in upper snake case preceded by ``doc__`` and followed by ``_architecture``
    - Adjust ``status`` to be ``valid``
    - Adjust ``safety`` and ``tags`` according to your needs

Overview
--------
<Brief summary>

Requirements Linked to Component Architecture
---------------------------------------------

.. code-block:: none

   .. needtable:: Overview of Component Requirements
      :style: table
      :columns: title;id
      :filter: search("comp_arch_sta__archdes$", "fulfils_back")
      :colwidths: 70,30

Description
-----------

<General Description>

<Design Decisions - For the documentation of the decision the :need:`gd_temp__change_decision_record` can be used.>

<Design Constraints>

Rationale Behind Architecture Decomposition
*******************************************

Mandatory: A motivation for the decomposition or reason for not further splitting it into internal components.

.. note:: Common decisions across components / cross cutting concepts is at the higher level.

Static Architecture
-------------------

The components are designed to cover the expectations from the feature architecture
(i.e. if already exists a definition it should be taken over and enriched).

A component can optional also consist of subcomponents to further structure the architecture. The component and its static views can also optionally use interfaces provided by other components.

.. comp:: Component Name
   :id: comp__mod_temp_component_name_template
   :security: YES
   :safety: ASIL_B
   :status: invalid
   :consists_of: comp__mod_temp_archex_sub_component_1, comp__mod_temp_archex_sub_component_2, comp__mod_temp_archex_sub_component_3
   :belongs_to: feat__feature_name

.. comp_arc_sta:: Component Name (Static View)
   :id: comp_arc_sta__mod_temp_component_name__sv
   :security: YES
   :safety: ASIL_B
   :status: invalid
   :belongs_to: comp__mod_temp_component_name_template
   :fulfils: comp_req__mod_temp_component_name__some_title

   .. needarch::
      :scale: 50
      :align: center

      {{ draw_component(need(), needs) }}

Dynamic Architecture
--------------------

.. comp_arc_dyn:: Dynamic View
   :id: comp_arc_dyn__mod_temp_component_name__dv
   :security: YES
   :safety: ASIL_B
   :status: invalid
   :belongs_to: comp__mod_temp_component_name_template
   :fulfils: comp_req__mod_temp_component_name__some_title

   Put here a sequence diagram


Interfaces
----------

.. code-block:: rst

   .. real_arc_int:: <Title>
      :id: real_arc_int__<component>__<Title>
      :security: <YES|NO>
      :safety: <QM|ASIL_B>
      :fulfils: <link to component requirement id>
      :language: cpp

Internal Components
-------------------

.. comp_arc_sta:: Component Name Static View
   :id: comp_arc_sta__mod_temp_component_name__2
   :status: invalid
   :safety: ASIL_B
   :security: YES
   :fulfils: comp_req__mod_temp_component_name__some_title
   :belongs_to: comp__mod_temp_component_example_2

   No architecture but detailed design

.. note::
   Architecture can be split into multiple files. At component level the public interfaces to be used by the user and tester to be shown.

.. attention::
    The above directives must be updated according to your component architecture.

    - Replace the example content by the real content (according to :need:`gd_guidl__arch_design`)
    - Set the status to valid and start the review/merge process
