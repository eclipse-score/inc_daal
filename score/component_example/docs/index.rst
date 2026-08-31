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

.. _component_template:

[Your Component Name]
#####################

.. note:: Document header

.. document:: [Your Component Name]
   :id: doc__mod_temp_component_name
   :status: draft
   :version: 1
   :safety: ASIL_B
   :security: NO
   :realizes: wp__cmpt_request
   :tags: template

.. code-block:: rst

   .. comp:: Component Name
      :id: comp__mod_temp_component_name_template
      :security: YES
      :safety: ASIL_B
      :status: invalid
      :implements: logic_arc_int__feature_name__interface_name1
      :consists_of: comp__component_name_internal_1, comp__component_name_internal_2, comp__component_name_internal_3
      :belongs_to: feat__feature_name

.. attention::
    The above directives must be updated according to your Component.

    - Modify ``document`` to be your Component Name
    - Modify ``id`` to be your Component Name in upper snake case preceded by ``doc__``
    - Adjust ``status`` to be ``valid``
    - Adjust ``safety`` and ``tags`` according to your needs

Abstract
========

[A short (~200 word) description of the component.]


Specification
=============

[Describe the requirements, architecture of any component.] or


How to Teach This
=================

[How to teach users, new and experienced, how to apply the CR to their work.]

.. note::
   For a CR that adds new functionality or changes behaviour, it is helpful to include a section on how to teach users, new and experienced, how to apply the CR to their work.

Footnotes
=========

[A collection of footnotes cited in the CR, and a place to list non-inline hyperlink targets.]


Further Documentation of the component can be found in the following sections:

Component Detail Information
============================

.. toctree::
   :maxdepth: 1

   architecture/index
   detailed_design/index
   requirements/index
   safety_analysis/dfa
   safety_analysis/fmea
   safety_analysis/aou_requirements
   component_classification
