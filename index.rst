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

Module Template Documentation
=============================

This documentation describes the structure, usage and configuration of the Bazel-based C++/Rust module template according to the `SCORE module folder structure <https://eclipse-score.github.io/score/main/contribute/general/folder.html#module-folder-structure>`_ and the `SCORE building blocks concept <https://eclipse-score.github.io/process_description/main/general_concepts/score_building_blocks_concept.html>`_.

.. contents:: Table of Contents
   :depth: 2
   :local:

Overview
--------

This repository provides a standardized setup for projects using **C++** or **Rust** and **Bazel** as a build system.
It integrates best practices for build, test, CI/CD and documentation.
It also provides an example for the documentation of an module with all necessary artifacts for safety and security management, verification and release management.
It also provides an example of modeling architecture in Sphinx Needs in :doc:`/examples/docs/architecture_modeling_example`.
It also provides the component architecture template snippets in :doc:`/score/component_example/docs/architecture/component_architecture`.
It also provides an example of documenting detailed design in :doc:`/score/component_example/docs/detailed_design/detailed_design_example`.

Module Layout
-------------

The module template includes the following top-level structure:

.. parsed-literal::

    <module_name>/                      # Root folder of the module, subfolder only if more than one module exists in the repository
    ├── .github/
    │   └── workflows/                  # CI/CD pipelines
    ├── docs/                           # Global documentation of the module
    │   ├── features/                   # Feature documentation and architecture
    │   │   └── <feature_name>/         # Feature folder parts for each feature which should be in module documentation
    │   │       ├── architecture/       # Feature architecture [wp__feature_arch] and of architecture review [wp__sw_arch_verification]
    │   │       ├── safety_analysis/    # Feature safety analysis artifacts ([wp__feature_fmea], [wp__feature_dfa], [wp__requirements_feat_aou])
    │   │       ├── safety_planning/    # Feature safety planning artifacts
    │   │       ├── security_analysis/  # Feature security analysis artifacts [wp__feature_security_analysis]
    │   │       └── security_planning/  # Feature security planning artifacts
    │   ├── manuals/                    # Module manual, integration manual, table of assumptions of use
    │   │   |                           #   safety manual [wp__module_safety_manual],
    │   │   |                           #   needs table of [wp__requirements_feat_aou]
    │   │   |                           #   security manual [wp__module_security_manual]
    │   │   │                           # Additional optional user centric documentation (e.g. configuration guide,
    │   │   │                           #   examples user guide, APIs & usage, performance analysis)
    │   │   ├── config/                 # Configuration guide (optional)
    │   │   ├── examples/               # Examples user guide (optional)
    │   │   ├── api_description/        # API detail description (optional)
    │   │   └── performance/            # Performance analysis (optional)
    │   ├── release/                    # Module release note [wp__module_sw_release_note]
    │   ├── safety_mgt/                 # Module safety plan [wp__module_safety_plan],
    │   │                               #   module safety package [wp__module_safety_package],
    │   │                               #   formal document and safety analysis reviews [wp__fdr_reports]
    │   ├── security_mgt/               # Module security plan [wp__module_security_plan],
    │   │                               #   module security package [wp__module_security_package],
    │   │                               #   formal document reviews [wp__fdr_reports_security],
    │   │                               #   module SW bill of material [wp__sw_module_sbom]
    │   └── verification_report/        # Module verification report,
    │                                   #   module verifications [wp__verification_module_ver_report],
    ├── examples/                       # Usage examples for the module / features
    ├── score/                          # Components of the module
    │   ├── tests/                      # Module-level tests (e.g., feature integration tests, system tests) [wp__verification_feat_int_test]
    │   └── <component_name>/           # Component folder for each component of the module
    │       ├── docs/                   # Documentation of the component
    │       │   ├── architecture/       # Component architecture [wp__component_arch]
    │       │   │                       #   (only if lower level components exist)
    |       |   |                       #   architecture review [wp__sw_arch_verification],
    │       │   ├── detailed_design/    # Detailed design [wp__sw_implementation]
    │       │   │                       #   code inspection [wp__sw_implementation_inspection]
    │       │   ├── requirements/       # Component requirements [wp__requirements_comp],[wp__requirements_inspect]
    │       │   ├── safety_analysis/    # Safety analysis [wp__sw_component_fmea], [wp__sw_component_dfa], [wp__requirements_comp_aou]
    |       |   |                       # Component classification [wp__sw_component_class] for pre-existing software
    │       │   │                       #   (only if component architecture exists)
    │       │   ├── security_analysis/  # Security analysis [wp__sw_component_security_analysis]
    │       │   │                       #   (only if component architecture exists)
    │       │   └── manuals/            # User documentation (of a single component, e.g., user manual of a library component, optional)
    │       ├── src/                    # Source files, include files, unit tests [wp__verification_sw_unit_test],
    │       │   └── <lower_level_comp>/ # Lower level component (follows <component_name> structure)
    │       └── tests/                  # Component-level tests (e.g., integration or complex unit tests) [wp__verification_comp_int_test]
    ├── MODULE.bazel                    # Bazel module definition
    ├── BUILD                           # Root build rules
    ├── project_config.bzl              # Project metadata used by Bazel macros
    └── README.md                       # Entry point of the repository

.. note::

    The feature-specific subfolder under ``docs/features/<feature_name>/`` is only necessary
    if more than one feature is implemented in the module.

Module Folder Structure (Single-Feature Variant)
------------------------------------------------

The following variant keeps the same structure but removes the additional
feature-name nesting under ``docs/features/``. In this case, the ``features/``
subfolder is optional and omitted. This variant is intended for modules that only implement a single feature, to avoid unnecessary nesting.
For identification of the single feature, the repository name or module name should be replicate the feature name.

.. parsed-literal::

    <module_name>/                      # Root folder of the module, subfolder only if more than one module exists in the repository
    ├── .github/
    │   └── workflows/                  # CI/CD pipelines
    ├── docs/                           # Global documentation of the module and the single feature
    │   ├── architecture/               # Feature architecture [wp__feature_arch] and of architecture review [wp__sw_arch_verification]
    │   ├── safety_analysis/            # Feature safety analysis artifacts ([wp__feature_fmea], [wp__feature_dfa], [wp__requirements_feat_aou])
    │   ├── safety_planning/            # Feature safety planning artifacts
    │   ├── security_analysis/          # Feature security analysis artifacts [wp__feature_security_analysis]
    │   ├── security_planning/          # Feature security planning artifacts
    │   ├── manuals/                    # Module manual, integration manual, table of assumptions of use,
    │   │   |                           #   safety manual [wp__module_safety_manual],
    │   │   |                           #   needs table of [wp__requirements_feat_aou]
    │   │   |                           #   security manual [wp__module_security_manual]
    │   │   |                           # Additional optional user centric documentation (e.g. configuration guide,
    │   │   |                           #   examples user guide, APIs & usage, performance analysis)
    │   │   ├── config/                 # Configuration guide (optional)
    │   │   ├── examples/               # Examples user guide (optional)
    │   │   ├── api_description/        # APIs detail description (optional)
    │   │   └── performance/            # Performance analysis (optional)
    │   ├── release/                    # Module release note [wp__module_sw_release_note]
    │   ├── safety_mgt/                 # Module safety plan [wp__module_safety_plan],
    │   │                               #   module safety package [wp__module_safety_package],
    │   │                               #   formal document and safety analysis reviews [wp__fdr_reports]
    │   ├── security_mgt/               # Module security plan [wp__module_security_plan],
    │   │                               #   module security package [wp__module_security_package],
    │   │                               #   formal document reviews [wp__fdr_reports_security],
    │   │                               #   module SW bill of material [wp__sw_module_sbom]
    │   └── verification_report/        # Module verification report,
    │                                   #   module verifications [wp__verification_module_ver_report],
    ├── examples/                       # Usage examples for the module / features
    ├── score/                          # Components of the module
    │   ├── tests/                      # Module-level tests (e.g., feature integration tests, system tests) [wp__verification_feat_int_test]
    │   └── <component_name>/           # Component folder for each component of the module
    │       ├── docs/                   # Documentation of the component
    │       │   ├── architecture/       # Component architecture [wp__component_arch]
    │       │   │                       #   (only if lower level components exist)
    |       |   |                       #   architecture review [wp__sw_arch_verification],
    │       │   ├── detailed_design/    # Detailed design [wp__sw_implementation]
    │       │   │                       #   code inspection [wp__sw_implementation_inspection]
    │       │   ├── requirements/       # Component requirements [wp__requirements_comp],[wp__requirements_inspect]
    │       │   ├── safety_analysis/    # Safety analysis [wp__sw_component_fmea], [wp__sw_component_dfa], [wp__requirements_comp_aou]
    |       |   |                       # Component classification [wp__sw_component_class] for pre-existing software
    │       │   │                       #   (only if component architecture exists)
    │       │   ├── security_analysis/  # Security analysis [wp__sw_component_security_analysis]
    │       │   │                       #   (only if component architecture exists)
    │       │   └── manuals/            # User documentation (of a single component, e.g., user manual of a library component, optional)
    │       ├── src/                    # Source files, include files, unit tests [wp__verification_sw_unit_test],
    │       │   └── <lower_level_comp>/ # Lower level component (follows <component_name> structure)
    │       └── tests/                  # Component-level tests (e.g., integration or complex unit tests) [wp__verification_comp_int_test]
    ├── MODULE.bazel                    # Bazel module definition
    ├── BUILD                           # Root build rules
    ├── project_config.bzl              # Project metadata used by Bazel macros
    └── README.md                       # Entry point of the repository

Module Documentation
--------------------

<Brief description of the module and the implemented feature(s).>

<Module sphinx documentation template snippets for the module. The directives and their parameters
should be updated according to the module and it's components. Further documentation of the module
and the implemented feature(s) should be added in the respective sections of the documentation
(e.g., feature architecture, safety analysis, security analysis, manuals, etc.) following the provided
templates and guidelines.>

.. code-block:: rst

   .. mod:: Module Name
      :id: mod__module_name
      :includes: comp__component_name_template


   .. mod_view_sta:: Module Name Static View
      :id: mod_view_sta__feature_name__module_name
      :includes: comp__component_name_template

      .. needarch::
         :scale: 50
         :align: center

         {{ draw_module(need(), needs) }}


.. toctree::
   :maxdepth: 1

   docs/manuals/index
   docs/release/release_note
   docs/features/index
   docs/safety_mgt/index
   docs/security_mgt/index
   docs/verification_report/module_verification_report


Component Documentation
-----------------------

For documentation of individual components within this module:

.. toctree::
   :maxdepth: 1

   score/component_example/docs/index

Architecture Modeling Example
-----------------------------

An example of modeling architecture in Sphinx Needs can be found in

.. toctree::
   :maxdepth: 1

   examples/docs/architecture_modeling_example

Please note, that is not a template for architecture documentation, but an example of how to use Sphinx Needs for architecture modeling. The architecture documentation of the components and features of the module should follow the provided templates and guidelines.


.. _quick-start-building-testing:

Quick Start - Building and Testing
==================================

To build the entire module:

.. code-block:: bash

   bazel build //src/...

To run all tests:

.. code-block:: bash

   bazel test //...

To run only unit tests:

.. code-block:: bash

   bazel test //src/...

To run only component or feature integration tests:

.. code-block:: bash

   bazel test //tests/...


Module Build Configuration
--------------------------

The ``project_config.bzl`` file at the root of the module defines metadata used by Bazel macros.
This file controls build behavior and project-specific settings. It should follow the S-CORE definition.
See `S-CORE user guide for project_config.bzl <https://eclipse-score.github.io/score/main/users_guide/building_simple_application/first_score_module.html#project-config-bzl>`_ for details.

The configuration enables conditional build behavior:

* **Language-specific tools**: For C++ code, tools like ``clang-tidy`` are used; for Rust code, ``clippy`` is used
* **Safety level**: The ASIL level affects safety-related build settings and validation
* **Source code languages**: The build system optimizes for the configured languages
