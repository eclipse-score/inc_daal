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

#include "runtime_statistics.hpp"

#include "reporting_backend.hpp"

namespace daal {
namespace af {
namespace runtime_statistics {

void RuntimeStatistics::Data::Update(const std::uint64_t delta, const std::uint64_t cycle_count) noexcept {
  current = static_cast<float>(delta);
  minimum = current < minimum ? current : minimum;
  maximum = current > maximum ? current : maximum;

  /* The cycle_count must be converted to double, since float only results in
   * about 700 minutes of measurement time at a cycle time of 5 ms before the 23
   * bits of the mantissa are filled. */
  const float kMeanPrev = mean;
  mean = kMeanPrev + static_cast<float>(static_cast<double>(current - kMeanPrev) / static_cast<double>(cycle_count));
  variance = variance + (current - kMeanPrev) * (current - mean);
}

void RuntimeStatistics::Data::Finalize(const std::uint64_t cycle_count) noexcept {
  if (cycle_count > 1) {
    /* The cycle_count must be converted to double, since float only results in
     * about 700 minutes of measurement time at a cycle time of 5 ms before the
     * 23 bits of the mantissa are filled. */
    std_dev = sqrt(static_cast<double>(variance) / (static_cast<double>(cycle_count) - 1.0F));
  } else {
    std_dev = 0.0F;
  }
}

void RuntimeStatistics::Statistics::Finalize() noexcept {
  gross_execution_time.Finalize(cycle_count);
  core_execution_time.Finalize(cycle_count);
  delta_time.Finalize(cycle_count);
}

RuntimeStatistics::ScopeGuard::~ScopeGuard() { runtime_statistics_.get().StopMeasurement(); };

RuntimeStatistics::RuntimeStatistics(std::string name, std::shared_ptr<TimeProvider> time_provider,
                                     std::shared_ptr<IReportingBackend> backend, float startup_wait_time) noexcept
    : time_provider_(std::move(time_provider)), backend_(std::move(backend)), startup_wait_time_(startup_wait_time) {
  statistics_ = {};
  statistics_.name = std::move(name);
}

RuntimeStatistics::~RuntimeStatistics() noexcept { Show(); }

void RuntimeStatistics::Enable() noexcept { is_enabled_ = true; }

void RuntimeStatistics::Disable() noexcept { is_enabled_ = false; }

[[nodiscard]] RuntimeStatistics::ScopeGuard RuntimeStatistics::ScopeMeasurement() noexcept {
  StartMeasurement();
  return ScopeGuard(*this);
}

void RuntimeStatistics::StartMeasurement() noexcept {
  if (is_enabled_) {
    start_real_last_ = start_real_;
    start_real_ = time_provider_->GetRealTime();
    start_cpu_ = time_provider_->GetCPUTime();
  }
}

void RuntimeStatistics::StopMeasurement() noexcept {
  if (is_enabled_) {
    if (start_real_last_ != 0) {
      end_cpu_ = time_provider_->GetCPUTime();
      end_real_ = time_provider_->GetRealTime();

      const auto kDeltaGET = end_real_ - start_real_;
      const auto kDeltaCET = end_cpu_ - start_cpu_;
      const auto kDeltaDT = start_real_ - start_real_last_;

      if (startup_wait_time_ >= kDeltaDT) {
        startup_wait_time_ -= kDeltaDT;
      } else {
        startup_wait_time_ = 0;
        statistics_.cycle_count++;
        statistics_.gross_execution_time.Update(kDeltaGET, statistics_.cycle_count);
        statistics_.core_execution_time.Update(kDeltaCET, statistics_.cycle_count);
        statistics_.delta_time.Update(kDeltaDT, statistics_.cycle_count);
      }
    }
  }
}

void RuntimeStatistics::Reset() noexcept {
  statistics_.gross_execution_time = {};
  statistics_.core_execution_time = {};
  statistics_.delta_time = {};
  statistics_.cycle_count = 0;
  start_real_ = 0;
  end_real_ = 0;
  start_cpu_ = 0;
  end_cpu_ = 0;
  start_real_last_ = 0;
}

const RuntimeStatistics::Statistics& RuntimeStatistics::Get() noexcept {
  if (is_enabled_) {
    statistics_.Finalize();
  }
  return statistics_;
}

void RuntimeStatistics::Show() noexcept { backend_->Show(Get()); }

}  // namespace runtime_statistics
}  // namespace af
}  // namespace daal
