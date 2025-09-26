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

#ifndef SRC_DAAL_AF_RUNTIME_STATISTICS_RUNTIME_STATISTICS_HPP_
#define SRC_DAAL_AF_RUNTIME_STATISTICS_RUNTIME_STATISTICS_HPP_

#include <cmath>
#include <cstdint>
#include <functional>
#include <limits>
#include <memory>
#include <string>

#include "time_provider.hpp"

namespace daal {
namespace af {
namespace runtime_statistics {

class IReportingBackend;

/** Time statistics class for measuring runtime metrics.
 *
 * This class provides a standard implementation to do time statistic calculations for runtime measurement.
 *
 * The naming of the different time metrics uses Gliwa’s definitions:
 *
 * IPT:: Initial Pending Time is the time between the task becoming due and actually being started.
 *
 * CET:: Core Execution Time is the time required to compute a task on a processor core. It is independent of
 *       scheduling as it does not include time for preemptions.
 *
 * GET:: Gross Execution Time is the real time required to execute a task. It is the CET plus time for preemptions.
 *
 * RT::  Response Time is the real time between an event and the software response demanded by that event. Response
 *       time includes GET plus IPT.
 *
 * DT::  Delta Time is the real time from one start of the task to the next. It is not the same as the period because
 *        of variation in IPT.
 *
 * PER:: PERiod is the regular interval between times the task becomes due. It is normally an input parameter rather
 *       than a measured value but observing the period can be useful, for example when a configuration problem causes
 *       a task to have an unexpected period. Aperiodic tasks, also called sporadic tasks, often have a non-zero
 *       minimum period, which can be a useful property to verify through measurement.
 *
 * ST::  Slack Time is the time between a task finishing and becoming due again.
 *
 * DL::  DeadLine
 *
 * %%%:: Task is ready
 *
 * ###:: Task is running
 *
 * PRIORITY
 *   ^
 *   |
 *   |  Task B    --------------%%%#####--------------%%#####--------------
 *   |                                             |
 *   |  Task A    ----%%%%%########%%%%%#######---------------%%%#######---
 *   |               | IPT |      |     |      |   |         |   |
 *   |               |-----|      |     |      |   |         |   |
 *   |               |     | CET1 |     | CET2 |   |         |   |
 *   |               |     |------|     |------|   |         |   |
 *   |               |     |        GET        |   |         |   |
 *   |               |     |-------------------|   |         |   |
 *   |               |     |    RT             |   |         |   |
 *   |               |-------------------------|   |         |   |
 *   |               |     |    DL             |   |         |   |
 *   |               |---------------------------- |         |   |
 *   |               |     |                   |     ST      |   |
 *   |               |     |            DT     |-------------|   |
 *   |               |     |-------------------------------------|
 *   |               |                  PER                  |
 *   |               |---------------------------------------|
 *   |
 *   |
 *  -+-------------------------------------------------------------------> TIME
 *   |
 *
 * This implementation uses Welford's algorithm to calculate the mean and variance values. This is numerically more
 * stable than the naive algorithm that sums up the time deltas and squared time deltas.
 *
 *   - Calculation of mean value:
 *
 *     \f[
 *       M_1 = x_1
 *     \f]
 *
 *     \f[
 *       M_k = M_{k-1} + \frac{(x_k - M_{k-1})}{k}
 *     \f]
 *
 *   - Calculation of variance:
 *
 *     \f[
 *       S_1 = 0
 *     \f]
 *
 *     \f[
 *       S_k = S_{k-1} + (x_k - M_{k-1}) * (x_k - M_k)
 *     \f]
 *
 *   - Calculation of standard deviation:
 *
 *     \f[
 *        \sigma = \sqrt{\frac{S_n}{n - 1}}
 *     \f]
 *
 */
class RuntimeStatistics {
 public:
  /** Data collection used for storing time statistic data for various time
   * bases. */
  struct Data {
    /** Runtime of current cycle [µs]. */
    float current{0.0F};

    /** Minimum runtime since start or last reset [µs]. */
    float minimum{std::numeric_limits<float>::max()};

    /** Maximum runtime since start or last reset [µs]. */
    float maximum{std::numeric_limits<float>::min()};

    /** Mean runtime since start or last reset [µs]. */
    float mean{0.0F};

    /** Variance of runtime since start or last reset [µs]. */
    float variance{0.0F};

    /** Standard deviation of runtime since start or last reset [µs]. */
    float std_dev{0.0F};

    /** Update the data using the given delta.
     * \attention This does not update the standard deviation. These are updated
     * on finalize() call */
    void Update(std::uint64_t delta, std::uint64_t cycle_count) noexcept;

    /** Finalize the statistic data by calculating the average and standard
     * deviation values. */
    void Finalize(std::uint64_t cycle_count) noexcept;
  };

  /** Collection of several runtime statistics. */
  struct Statistics {
    /** Gross execution time according to Gliwas definition. */
    Data gross_execution_time{};

    /** Core execution time according to Gliwas definition. */
    Data core_execution_time{};

    /** Period time according to Gliwas definition. */
    Data delta_time{};

    /* TODO (Markus Braun, braun5m, 2025-08-05): add IPT */
    /** Number of cycles since start or last reset. */
    std::uint64_t cycle_count{0};

    /** Name of the measured component. */
    std::string name;

    /** Finalize the statistic data by calculating the average and standard
     * deviation values. */
    void Finalize() noexcept;
  };

  class ScopeGuard {
   public:
    explicit ScopeGuard(RuntimeStatistics& runtime_statistics) : runtime_statistics_(runtime_statistics){};
    virtual ~ScopeGuard();
    ScopeGuard(const ScopeGuard& other) = default;
    ScopeGuard(ScopeGuard&& other) noexcept = default;
    ScopeGuard& operator=(const ScopeGuard& other) = default;
    ScopeGuard& operator=(ScopeGuard&& other) = default;

   private:
    std::reference_wrapper<RuntimeStatistics> runtime_statistics_;
  };

  RuntimeStatistics(std::string name, std::shared_ptr<TimeProvider> time_provider,
                    std::shared_ptr<IReportingBackend> backend,
                    float startup_wait_time = kStartupWaitTimeDefault) noexcept;

  ~RuntimeStatistics() noexcept;

  /** Start measuring inside scope and end automatically if scope is left.
   * \note The return value of this method mus be stored in a variable local to
   * the scope.
   * \attention This method must not be used in conjunction with
   * StartMeasurement() and StopMeasurement() */
  [[nodiscard]] ScopeGuard ScopeMeasurement() noexcept;

  /** Start measurement for the current cycle.
   * \attention This method must not be used in conjunction with
   * ScopeMeasurement() */
  void StartMeasurement() noexcept;

  /** Stop measurement for the current cycle.
   * \attention This method must not be used in conjunction with
   * ScopeMeasurement() */
  void StopMeasurement() noexcept;

  /** Reset all statistic data. */
  void Reset() noexcept;

  /** Enable gathering statistic data. */
  void Enable() noexcept;

  /** Disable gathering statistic data. */
  void Disable() noexcept;

  /** Retrieve the statistic data. */
  const Statistics& Get() noexcept;

  /** Print statistic data to console. */
  void Show() noexcept;

 private:
  /** Runtime statistics are enabled */
  bool is_enabled_{true};

  /** Time provider to get platform specific time information. */
  std::shared_ptr<TimeProvider> time_provider_;

  /** Backend for outputting the runtime statistics. */
  std::shared_ptr<IReportingBackend> backend_;

  /** Real time to wait skip before starting to collect runtime statistics [µs]. */
  constexpr static float kStartupWaitTimeDefault{1000000};

  /** Remaining real time until collection of runtime statistics starts. */
  float startup_wait_time_{kStartupWaitTimeDefault};

  /** Actual runtime statistic data. */
  Statistics statistics_{};

  /** Start time of monotonic real time wall clock [µs]. */
  std::uint64_t start_real_{0};

  /** End time of monotonic real time wall clock [µs]. */
  std::uint64_t end_real_{0};

  /** Start time of CPU clock [µs]. */
  std::uint64_t start_cpu_{0};

  /** End time of CPU clock [µs]. */
  std::uint64_t end_cpu_{0};

  /** Previous start time of monotonic real time wall clock [µs]. */
  std::uint64_t start_real_last_{0};
};

}  // namespace runtime_statistics
}  // namespace af
}  // namespace daal

#endif  // SRC_DAAL_AF_RUNTIME_STATISTICS_RUNTIME_STATISTICS_HPP_
