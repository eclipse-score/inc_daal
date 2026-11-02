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

.. document:: [Component Name] Implementation Inspection Checklist
  :id: doc__mod_temp_component_name_impl_inspection
  :status: draft
  :version: 2
  :safety: ASIL_B
  :security: YES
  :realizes: wp__sw_implementation_inspection
  :tags: template

.. attention::
    The above directive must be updated according to your Component.

    - Modify ``Component Name`` to be your Component Name
    - Modify ``id`` to be your Component Name in lower snake case preceded by ``doc__`` and followed by ``_impl_inspection``
    - Adjust ``status`` to be ``valid``
    - Adjust ``safety``, ``security`` and ``tags`` according to your needs

[Component Name] Implementation Inspection Checklist
====================================================

Purpose
-------

The purpose of this checklist is to define the topics to be reviewed during implementation,
including the detailed design and unit source code. Unit testing and structural coverage are
addressed separately through the verification activities and report.

The checklist is intended to be language-agnostic. Language-specific guidance should be referenced
where applicable, for example, in the C++ or Rust documentation.

Conduct
-------

As described in the concept :need:`doc_concept__wp_inspections`, the following inspection roles are expected to be assigned:

- content responsible (author): <contributor/committer explicitly named here who is the main author, as shown in configuration management tooling>
- reviewer: <contributor/committer explicitly named here who is the main content reviewer; this person must differ from the content responsible>
- moderator: <committer explicitly named here who initiates the inspection as the safety, security, or quality manager>

Checklist
---------

Enter "yes" or "no" in the "Passed" column for each checklist item, and explain the result in the "Remarks" column.
If "no" is entered, add a link to the corresponding issue in the "Issue link" column unless the finding is already tracked in the issue conducting the inspection.
See also :need:`doc_concept__wp_inspections` for further information about reviews in general and inspection in particular.

.. list-table:: Implementation Checklist
   :header-rows: 1
   :widths: 10,30,50,6,6,8

   * - Review ID
     - Acceptance criteria
     - Guidance
     - Passed
     - Remarks
     - Issue link
   * - IMPL_01_01
     - Does the detailed design follow the applicable project guidelines?
     - See :need:`gd_temp__detailed_design` and :need:`doc_concept__imp_concept`.
       For example, check whether design views use the notations recommended by the project.
     -
     -
     -
   * - IMPL_01_02
     - Does the implementation conform to the allocated requirements, architecture, and detailed design?
     - Check whether the linked component requirements are fulfilled and whether the detailed design is consistent with the architecture description.
     -
     -
     -
   * - IMPL_01_03
     - Are the design decisions, assumptions, and constraints documented and justified?
     - Check whether the rationale is clear and consistent with the requirements and architecture.
     -
     -
     -
   * - IMPL_01_04
     - Are all external libraries and other third-party dependencies used by the component identified and assessed for the intended use?
     - Check the automated dependency analysis and confirm that relevant safety evidence, assumptions, constraints, and usage conditions are documented. Where a dependency is used in a safety-related context, justify its suitability for the required safety integrity level; do not assume that an "ASIL-rated" label alone demonstrates suitability.
     -
     -
     -
   * - IMPL_02_01
     - Have the static and dynamic code-analysis results been reviewed, and have the findings been resolved or justified?
     - Review findings against the applicable coding guidelines. Resolve findings or document and approve the rationale for accepted deviations, especially in safety-related code.
     -
     -
     -
   * - IMPL_02_02
     - Have the manual checks required by the applicable coding guidelines been performed, with findings resolved or justified?
     - Use the checks applicable to the programming language (e.g., C++ <link_to_checks_list>, Rust <link_to_checks_list>).
     -
     -
     -
   * - IMPL_03_01
     - Are the interface UIDs in the component documentation traceable to the corresponding implemented public interfaces?
     - Compare the interface UIDs in the component architecture and detailed design documentation with the corresponding public interfaces in the source code (e.g., API headers, traits, public types, or functions). The identifiers need not match source-level names exactly, but their correspondence should be clear.
     -
     -
     -
   * - IMPL_03_02
     - Are the detailed design and source code consistent, and is traceability between them established?
     - Check whether available static and dynamic design diagrams and textual descriptions match the code (e.g., the names of interfaces, units, functions, operations, messages, and data types).
       Where required by project conventions, check whether unit folder and file names reflect their intended functionality. For example, a unit named "communication" should not contain unrelated data-processing code.
     -
     -
     -
