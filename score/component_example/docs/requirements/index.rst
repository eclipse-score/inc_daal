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

Requirements
############

.. document:: [Your Component Name] Requirements
   :id: doc__mod_temp_component_name_requirements
   :status: draft
   :safety: ASIL_B
   :security: YES
   :realizes: wp__requirements_comp
   :tags: template

.. attention::
    The above directive must be updated according to your Component.

    - Modify ``Your Component Name`` to be your Component Name
    - Modify ``id`` to be your Component Name in upper snake case preceded by ``doc__`` and followed by ``_requirements``
    - Adjust ``status`` to be ``valid``
    - Adjust ``safety``, ``security`` and ``tags`` according to your needs

<Headlines (for the list of requirements if structuring is needed)>
===================================================================

Component Requirements
----------------------

.. comp_req:: Some Title
   :id: comp_req__mod_temp_component_name__some_title
   :reqtype: Process
   :security: YES
   :safety: ASIL_B
   :satisfies: feat_req__feature_name__some_title
   :status: invalid
   :belongs_to: comp__mod_temp_component_name_template

   The Component shall do xyz to another component to bring it to this condition at this time

   Note: (optional, not to be verified)

.. attention::
    The above directive must be updated according to your component requirements.

    - Replace the example content by the real content for your first requirement
    - Set ``satistifes`` with links to Feature requirements
    - Set ``belongs_to`` with a link to the right Component id
    - Set ``safety`` and ``security`` to the right value
    - Set the status to valid and start the review/merge process
    - Add other needed requirements for your component

Assumption of Use Requirements
------------------------------

.. aou_req:: Next Title
   :id: aou_req__mod_temp_component_name__next_title
   :reqtype: Process
   :security: YES
   :safety: ASIL_B
   :status: invalid

   The Component User shall do xyz to use the component safely/securely

Environmental Requirements
--------------------------

.. aou_req:: Another Title
   :id: aou_req__mod_temp_component_name__another
   :reqtype: Process
   :security: YES
   :safety: ASIL_B
   :status: invalid
   :tags: environment

   The Component shall only be used in a xyz environment to ensure its proper functioning.

Hints
-----

.. attention::
    The above directives must be updated according to your feature requirements.

    - Replace the example content by the real content for your first requirement (according to :need:`gd_guidl__req_engineering`)
    - Set ``safety`` and ``security`` to the right value (ASIL B/QM; YES/NO)
    - Set ``reqtype`` with a link to the right value (<Functional|Interface|Process|Non-Functional>)
    - Add other needed requirements for your feature
    - Set ``status`` to ``valid`` and start the review/merge process

.. needextend:: "component_name" in id
   :+tags: component_name
