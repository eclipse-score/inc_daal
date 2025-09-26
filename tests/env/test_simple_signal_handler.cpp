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

#include <gtest/gtest.h>

#include <atomic>
#include <csignal>
#include <thread>

#include "daal/af/env/details/single_shot_app_handler.hpp"

namespace daal {

namespace af {

namespace env {

class SimpleSignalHandlerTest : public ::testing::Test {
 protected:
  std::atomic_bool exit_requested_{false};
  std::atomic_bool terminated_by_signal_{false};
  SimpleSignalHandler* signal_handler_;

  void SetUp() override {
    signal_handler_ =
        new SimpleSignalHandler(exit_requested_, terminated_by_signal_);
  }

  void TearDown() override { delete signal_handler_; }
};

TEST_F(SimpleSignalHandlerTest, SignalHandlerInitialization) {
  EXPECT_FALSE(exit_requested_.load());
  EXPECT_FALSE(terminated_by_signal_.load());
}

TEST_F(SimpleSignalHandlerTest, HandleSIGTERM) {
  std::thread signal_thread([this]() { (*signal_handler_)(); });

  // Send SIGTERM signal
  pthread_kill(pthread_t(signal_thread.native_handle()), SIGTERM);

  // Wait for the signal handler to process the signal
  signal_thread.join();

  EXPECT_TRUE(exit_requested_.load());
  EXPECT_TRUE(terminated_by_signal_.load());
}

TEST_F(SimpleSignalHandlerTest, HandleSIGINT) {
  std::thread signal_thread([this]() { (*signal_handler_)(); });

  // Send SIGINT signal
  pthread_kill(pthread_t(signal_thread.native_handle()), SIGINT);

  // Wait for the signal handler to process the signal
  signal_thread.join();

  EXPECT_TRUE(exit_requested_.load());
  EXPECT_TRUE(terminated_by_signal_.load());
}

TEST_F(SimpleSignalHandlerTest, IgnoreOtherSignals) {
  std::thread signal_thread([this]() { (*signal_handler_)(); });

  // Send a signal that should be ignored
  pthread_kill(pthread_t(signal_thread.native_handle()), SIGUSR1);

  // Give some time for the signal to be processed
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  EXPECT_FALSE(exit_requested_.load());
  EXPECT_FALSE(terminated_by_signal_.load());

  // Send SIGTERM to exit the loop
  pthread_kill(pthread_t(signal_thread.native_handle()), SIGTERM);
  signal_thread.join();
}

} // namespace env

} // namespace af

} // namespace daal
