/********************************************************************************
* Copyright (c) 2025 Contributors to the Eclipse Foundation
*
* See the NOTICE file(s) distributed with this work for additional
* information regarding copyright ownership.
*
* This program and the accompanying materials are made available under the
* terms of the Apache License Version 2.0 which is available at
* https://www.apache.org/licenses/LICENSE-2.0
*
* SPDX-License-Identifier: Apache-2.0
********************************************************************************/

#include "daal/af/trigger/details/trigger_condition_impl.hpp"

namespace daal {

namespace af {
namespace trigger {

bool NullTriggerCondition::IsTriggered() noexcept { return true; }

}  // namespace trigger

}  // namespace af

}  // namespace daal
