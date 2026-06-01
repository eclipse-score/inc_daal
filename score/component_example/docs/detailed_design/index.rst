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

.. _component_detailed_design_template:

Detailed Design
###############

.. attention::

   The detailed design document is optional and should be created if the design of the component is complex and cannot be easily understood from the architecture documentation and interface documentation alone.


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

A static view provides an overview of the units and their relationships using
UML 2.0 notations (e.g. class diagrams, component diagrams). Use ``.. uml::``
or ``.. image::`` directives to include the diagram.

Dynamic Diagrams for Unit Interactions (optional)
--------------------------------------------------

A dynamic view illustrates how the units within a component interact over their
interfaces to fulfill a specific use case or functionality. It is optional when the
component's behaviour is straightforward and can be understood from the static view
and interface documentation alone.

Use standard UML behavioural diagrams (sequence diagrams, state machine diagrams)
with ``.. uml::`` or ``.. image::`` directives.

Units within the Component
--------------------------

The relationship between a unit and its parent component is established implicitly
through the file path. Each component has its own directory, and units residing
within that directory belong to it. The unit's attributes and behaviour are documented
in the source code itself. A separate static diagram per unit is not required.

Interface documentation of a software unit is part of the source code (e.g. public
API headers, trait definitions, or documented function signatures).

Inspection Checklist
--------------------

The checklist for verification of the detailed design inspection can be found here:

.. toctree::

   chklst_impl_inspection


Detail design example
---------------------

An example of documenting detailed design can be found in:

   .. toctree::

      detailed_design_example
