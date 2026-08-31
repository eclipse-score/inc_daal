..
   # *******************************************************************************
   # Copyright (c) 2024 Contributors to the Eclipse Foundation
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
It also provides an example of modeling architecture in Sphinx Needs in :doc:`/examples/docs/architecture_modeling_example`.
It also provides the component architecture template snippets in :doc:`/score/component_example/docs/architecture/component_architecture_template`.
It also provides an example of documenting detailed design in :doc:`/score/component_example/docs/detailed_design/detailed_design_example`.

Module Layout
-------------

The module template includes the following top-level structure:

.. code-block:: text

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
    │   ├── manuals/                    # Module manual, integration manual, table of assumptions of use,
    │   │                               #   safety manual [wp__module_safety_manual],
    │   │                               #   needs table of [wp__requirements_feat_aou]
    │   │                               #   security manual [wp__module_security_manual]
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
    │   ├── tests/                      # Module-level tests (e.g., feature integration tests, system tests) [wp__verification_comp_int_test]
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
    │       └── src/                    # Source files, include files, unit tests [wp__verification_sw_unit_test],
    │           ├── <lower_level_comp>/ # Lower level component (follows <component_name> structure)
    │           └── tests/              # Component-level tests (e.g., unit tests) [wp__verification_sw_unit_test]
    ├── MODULE.bazel                    # Bazel module definition
    ├── BUILD                           # Root build rules
    ├── project_config.bzl              # Project metadata used by Bazel macros
    └── README.md                       # Entry point of the repository


Module / Feature Documentation
------------------------------

.. toctree::
   :maxdepth: 1

   docs/features/index
   docs/manual/index
   docs/release/release_note
   docs/safety_mgt/index
   docs/security_mgt/index
   docs/verification/module_verification_report

Component documentation
-------------------------------

.. toctree::
   :maxdepth: 1

   score/component_example/docs/index
   score/component_example/docs/architecture/component_architecture_template
   score/component_example/docs/detailed_design/detailed_design_example

Examples
--------

.. toctree::
   :maxdepth: 1

   /examples/docs/architecture_modeling_example



Quick Start
-----------

To build the module:

.. code-block:: bash

   bazel build //src/...

To run all tests:

.. code-block:: bash

   bazel test //...

To run Unit Tests:

.. code-block:: bash

   bazel test //src/...

To run Component / Feature Integration Tests:

.. code-block:: bash

   bazel test //tests/...

Module Configuration
--------------------

The `project_config.bzl` file defines metadata used by Bazel macros.

Example:

.. code-block:: python

   PROJECT_CONFIG = {
       "asil_level": "QM",
       "source_code": ["cpp", "rust"]
   }

This enables conditional behavior (e.g., choosing `clang-tidy` for C++ or `clippy` for Rust).
