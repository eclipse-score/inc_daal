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
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>

class SimpleAppTestWithParam
    : public ::testing::Test,
      public ::testing::WithParamInterface<std::string> {
 protected:
  pid_t launchApp(const std::string& binary) {
    pid_t pid = fork();
    if (pid < 0) {
      throw std::runtime_error("fork failed");

    } else if (pid == 0) {
      execl(binary.c_str(), "", nullptr);
      _exit(EXIT_FAILURE);
    }
    return pid;
  }

  void terminateApp(pid_t pid, int signal) {
    kill(pid, signal);
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
      exit_code = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
      exit_code = WTERMSIG(status);
    }
  }

  int exit_code = -1;
};

TEST_P(SimpleAppTestWithParam, TerminationWithSIGABRT) {
  std::string binary = GetParam();
  pid_t pid = launchApp(binary);

  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  terminateApp(pid, SIGABRT);
  EXPECT_EQ(exit_code, SIGABRT);
}

TEST_P(SimpleAppTestWithParam, TerminationWithSIGBUS) {
  std::string binary = GetParam();
  pid_t pid = launchApp(binary);

  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  terminateApp(pid, SIGBUS);
  EXPECT_EQ(exit_code, SIGBUS);
}

TEST_P(SimpleAppTestWithParam, TerminationWithSIGFPE) {
  std::string binary = GetParam();
  pid_t pid = launchApp(binary);

  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  terminateApp(pid, SIGFPE);
  EXPECT_EQ(exit_code, SIGFPE);
}

TEST_P(SimpleAppTestWithParam, TerminationWithSIGILL) {
  std::string binary = GetParam();
  pid_t pid = launchApp(binary);

  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  terminateApp(pid, SIGILL);
  EXPECT_EQ(exit_code, SIGILL);
}

TEST_P(SimpleAppTestWithParam, TerminationWithSIGSEGV) {
  std::string binary = GetParam();
  pid_t pid = launchApp(binary);

  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  terminateApp(pid, SIGSEGV);
  EXPECT_EQ(exit_code, SIGSEGV);
}

TEST_P(SimpleAppTestWithParam, TerminationWithSIGTERM) {
  std::string binary = GetParam();
  pid_t pid = launchApp(binary);

  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  terminateApp(pid, SIGTERM);
  EXPECT_EQ(exit_code, 0);
}

TEST_P(SimpleAppTestWithParam, TerminationWithSIGINT) {
  std::string binary = GetParam();
  pid_t pid = launchApp(binary);

  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  terminateApp(pid, SIGINT);
  EXPECT_EQ(exit_code, 0);
}

std::vector<std::string> binaries = {"simple_application", "dual_trigger_application"};

INSTANTIATE_TEST_SUITE_P(Binaries, SimpleAppTestWithParam,
                         ::testing::ValuesIn(binaries));