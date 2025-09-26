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

#ifndef SRC_DAAL_AF_CHECKPOINT_DETAILS_NULL_CHECKPOINT_CONTAINER_H_
#define SRC_DAAL_AF_CHECKPOINT_DETAILS_NULL_CHECKPOINT_CONTAINER_H_

#include "daal/af/checkpoint/icheckpoint_container.hpp"

namespace daal {

namespace af {

namespace checkpoint {

class NullCheckpointContainer : public ICheckpointContainer {
 public:
  std::error_code TriggerCheckpoints(When when) const override { return {}; }
  std::error_code AddCheckpoint(std::shared_ptr<ICheckpoint> checkpoint) override { return {}; };
};

}  // namespace checkpoint
}  // namespace af
}  // namespace daal

#endif /* SRC_DAAL_AF_CHECKPOINT_DETAILS_NULL_CHECKPOINT_CONTAINER_H_ */
