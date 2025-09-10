# Checkpoint Package Usage

This package provides functionality to manage and trigger checkpoints in your application. The main components are:

1. `ICheckpoint`: Interface for individual checkpoints.
2. `ICheckpointContainer`: Interface for a container that manages checkpoints.
3. `CheckpointContainer`: Concrete implementation of `ICheckpointContainer`.
4. `When`: Enum to specify when checkpoints should be triggered (`BEFORE` or `AFTER`).

## Usage

### Step 1: Define Your Checkpoint

Implement the `ICheckpoint` interface to define your custom checkpoint.

```cpp
#include "daal/af/checkpoint/icheckpoint.hpp"

class MyCheckpoint : public daal::af::checkpoint::ICheckpoint {
 public:
    std::error_code Trigger() override {
        // Your checkpoint logic here
        return {};
    }

    daal::af::checkpoint::When GetWhen() const override {
        return daal::af::checkpoint::When::BEFORE;
    }

    const std::string& GetName() const override {
        static const std::string name = "MyCheckpoint";
        return name;
    }
};
```

### Step 2: Add Checkpoints to the Container

Create an instance of `CheckpointContainer` and add your checkpoints.

```cpp
#include "daal/af/checkpoint/details/checkpoint_container.hpp"

int main() {
    auto container = std::make_shared<daal::af::checkpoint::CheckpointContainer>();
    auto checkpoint = std::make_shared<MyCheckpoint>();

    std::error_code ec = container->AddCheckpoint(checkpoint);
    if (ec) {
        // Handle error
    }

    return 0;
}
```

### Step 3: Trigger Checkpoints

Trigger the checkpoints at the appropriate time in your application.

```cpp
std::error_code ec = container->TriggerCheckpoints(daal::af::checkpoint::When::BEFORE);
if (ec) {
    // Handle error
}
```
---

## Important Note

The order of execution is crucial. Ensure that checkpoints are added to the container before triggering them. The `When` enum helps in organizing checkpoints to be triggered `BEFORE` or `AFTER` specific events. and called in the order they were added in their category

---
