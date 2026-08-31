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

.. _component_detailed_design_template:

Detailed Design
###############

.. document:: [Your Component Name] Detailed Design
   :id: doc__mod_temp_component_name_detailed_design
   :status: draft
   :safety: ASIL_B
   :security: NO
   :realizes: wp__sw_implementation
   :tags: template

.. attention::
    The above directive must be updated according to your Component.

    - Modify ``Your Component Name`` to be your Component Name
    - Modify ``id`` to be your Component Name in upper snake case preceded by ``doc__`` and followed by ``_detailed_design``
    - Adjust ``status`` to be ``valid``
    - Adjust ``safety`` and ``tags`` according to your needs

Detailed Design for Component: <Component Name>
===============================================

Description
-----------

| Design Decisions - For the documentation of the decision the :need:`gd_temp__change_decision_record` can be used.
| Design Constraints

Rationale Behind Decomposition into Units
******************************************
| mandatory: a motivation for the decomposition into one or more units.

.. note:: Reason for split into multiple units could be-
	    - Based on design principles like SOLID,DRY etc
	    - Based on design pattern's etc.

Static Diagrams for Unit Interactions
-------------------------------------
.. code-block:: rst

   .. dd_sta:: <Title>
      :id: dd_sta__<Component>__<Title>
      :security: <YES|NO>
      :safety: <QM|ASIL_B>
      :status: <valid|invalid>
      :implements: <link to component requirement id>
      :satisfies: <link to component architecture id>
      :belongs_to: <link to component id>
      :includes: <link to sw_unit id>, <link to sw_unit interface id>

      .. needarch:: or .. image:: <link to drawio image>

Dynamic Diagrams for Unit Interactions
--------------------------------------
.. code-block:: rst

   .. dd_dyn:: <Title>
      :id: dd_dyn__<Component>__<Title>
      :security: <YES|NO>
      :safety: <QM|ASIL_B>
      :status: <valid|invalid>
      :implements: <link to component requirement id>
      :satisfies: <link to component architecture id>
      :belongs_to: <link to component id>
      :includes: <link to sw_unit id>, <link to sw_unit interface id>

      .. needarch:: or .. image:: <link to drawio image>

Units within the Component
--------------------------

In your rst file:

.. code-block:: rst

   .. sw_unit:: cpp unit
      :id: sw_unit__<Component>__<title>
      :belongs_to: <link to component id>

      This implements the ....

In your source file, any programming language, here with C++:

.. code-block:: cpp

   # need-Id: sw_unit__<Component>__<title>
   class <class name> {
      public:

   };

Interface View
--------------

In your rst file:

.. code-block:: rst

   .. sw_unit_int:: <here InterfaceDemo - change it>
      :id: sw_unit_int__<Component>__<title>
      :belongs_to: <link to sw_unit id>
      :implements: <real_arc_int, real_arc_int_op>

      This implements the ....

In your source file, any programming language, here with C++:

.. code-block:: cpp

   # need-Id: sw_unit__<Component>__<title>
   class InterfaceDemo
   {
      public:
         virtual ~InterfaceDemo() {}
         virtual void OverrideMe() = 0;
   };

-  For cpp using doxygen comments

.. code-block:: cpp

   /**
      * @rst
      * .. sw_unit_int:: cpp unit
      *    :id: sw_unit_int__<Component>__<title>
      *    :belongs_to: <link to sw_unit id>
      *    :implements: <real_arc_int, real_arc_int_op>
      *
      *    This implements the ....
      * @endrst
   */

-  For rust

.. code-block:: rust

   //! .. sw_unit_int:: rust unit
   //!     :id: sw_unit_int__<Component>__<title>
   //!     :belongs_to: <link to sw_unit id>
   //!     :implements: <real_arc_int, real_arc_int_op>
   //!
   //!     This implements the ....
