
# Welome to the Deterministic Application Abstration Layer Framework

DAAL Framework provides an application abstraction layer and APIs for testing.
Implements common code and several safety requirements.

## Goal

* Testing possibility of applications without any framework dependencies (e.g. Autosar, FEO..)

* Independence on Runtime Environment e.g. Linux, QNX

## Design

* Triggers: abstraction of how an application is executed. I.e. cyclic, event-based, conditional fork-join, …

* AppHandler: Abstraction to handle one or multiple applications, configuration of core

* Supports Error Handling and Health Monitoring

* Environment: Abstraction of the Runtime environment, Autosar, Linux.

* Executor: Manages the lifecycle

* IoHandler: Abstraction for handling the communication

## 🚀 Getting Started

### 1️⃣ Clone the Repository

```sh
git clone https://github.com/eclipse-score/inc_daal.git
cd inc_daal
```

### 2️⃣ Build the Examples of module

To build all targets of the module the following command can be used:

```sh
bazel build //src/...
```

This command will instruct Bazel to build all targets that are under Bazel
package `src/`. The ideal solution is to provide single target that builds
artifacts, for example:

```sh
bazel build //src/<module_name>:release_artifacts
```

where `:release_artifacts` is filegroup target that collects all release
artifacts of the module.

### 3️⃣ Run Tests

```sh
bazel test //tests/...
```

### 4️⃣ Scan for leaked secrets

To run a local default scan (same mode as CI):

```sh
docker run --rm -v "$(pwd):/repo" ghcr.io/gitleaks/gitleaks:latest \
	dir --verbose --redact --config=/repo/.gitleaks.toml /repo
```

A default GitHub Actions workflow also runs the same scan on pull requests,
merge queues, and pushes to `main`.

Optional full-history scan (for maintainers with history-rewrite permission):

```sh
docker run --rm -v "$(pwd):/repo" ghcr.io/gitleaks/gitleaks:latest \
	git --verbose --redact --config=/repo/.gitleaks.toml --log-opts="--all" /repo
```

## 📖 Documentation

- A **centralized docs structure** is planned.
