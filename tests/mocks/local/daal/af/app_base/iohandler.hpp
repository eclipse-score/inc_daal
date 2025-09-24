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

#pragma once

#include <gmock/gmock.h>

#include <vector>

#include "daal/af/app_base/safe_application_base.hpp"

namespace mock {
enum class ConnectionState { kDisconnected, kOngoing, kConnected };
}

namespace daal {
namespace af {
namespace app_base {

class IoHandler;

using IoHandlerWrapper = std::reference_wrapper<IoHandler>;
using IoHandlers = std::vector<IoHandlerWrapper>;

struct IoHandlerMock {
  static testing::StrictMock<IoHandlerMock>& instance() {
    static testing::StrictMock<IoHandlerMock> mock;
    return mock;
  }

  MOCK_METHOD(mock::ConnectionState, Start, ());
  MOCK_METHOD(void, Stop, ());
  MOCK_METHOD(void, PrepareStep, ());
  MOCK_METHOD(void, FinalizeStep, ());
  MOCK_METHOD(mock::ConnectionState, GetConnectionState, ());
  MOCK_METHOD(void, ctorIoHandler, ());
};

struct IoHandlerContainerMock {
  static testing::StrictMock<IoHandlerContainerMock>& instance() {
    static testing::StrictMock<IoHandlerContainerMock> mock;
    return mock;
  }

  MOCK_METHOD(IoHandlers const&, GetHandlers, ());
  MOCK_METHOD(void, ctorIoHandlerContainer, (IoHandlers const& handlers));
};

template <class IoContainerType>
struct SafeApplicationBaseWithIoMock {
  static testing::StrictMock<SafeApplicationBaseWithIoMock<IoContainerType>>&
  instance() {
    static testing::StrictMock<SafeApplicationBaseWithIoMock<IoContainerType>>
        mock;
    return mock;
  }

  MOCK_METHOD(MethodState, OnInitialize, ());
  MOCK_METHOD(MethodState, OnStart, ());
  MOCK_METHOD(MethodState, Step, (IoContainerType & io_container));
  MOCK_METHOD(MethodState, OnStop, ());
  MOCK_METHOD(MethodState, OnTerminate, ());
  MOCK_METHOD(void, ctorSafeApplicationBaseWithIo, (IoContainerType ioHandlerContainer));
};

struct IoHandler {
  using ConnectionState = mock::ConnectionState;
  IoHandler() { IoHandlerMock::instance().ctorIoHandler(); }
  virtual ~IoHandler(){};
  virtual ConnectionState Start() { return IoHandlerMock::instance().Start(); };
  virtual void Stop() { return IoHandlerMock::instance().Stop(); };
  virtual void PrepareStep() {
    return IoHandlerMock::instance().PrepareStep();
  };
  virtual void FinalizeStep() {
    return IoHandlerMock::instance().FinalizeStep();
  };
  virtual ConnectionState GetConnectionState() const {
    return IoHandlerMock::instance().GetConnectionState();
  }
};

struct IoHandlerContainer {
  IoHandlerContainer(IoHandlers const& handlers) : handlers_{handlers} {
    IoHandlerContainerMock::instance().ctorIoHandlerContainer(handlers);
  }
  virtual ~IoHandlerContainer(){};
  virtual IoHandlers const& GetHandlers() { return handlers_; }
  IoHandlers handlers_;
};

template <class IoContainerType>
struct SafeApplicationBaseWithIo {
  SafeApplicationBaseWithIo(IoContainerType ioHandlerContainer) {
    SafeApplicationBaseWithIoMock<IoContainerType>::instance()
        .ctorSafeApplicationBaseWithIo(ioHandlerContainer);
  }

  virtual ~SafeApplicationBaseWithIo() {}

  virtual MethodState OnInitialize() {
    return SafeApplicationBaseWithIoMock<IoContainerType>::instance().OnInitialize();
  }
  virtual MethodState OnStart() {
    return SafeApplicationBaseWithIoMock<IoContainerType>::instance().OnStart();
  }
  virtual MethodState Step(IoContainerType& io_container) {
    return SafeApplicationBaseWithIoMock<IoContainerType>::instance().Step(
        io_container);
  }
  virtual MethodState OnStop() {
    return SafeApplicationBaseWithIoMock<IoContainerType>::instance().OnStop();
  }
  virtual MethodState OnTerminate() {
    return SafeApplicationBaseWithIoMock<IoContainerType>::instance()
        .OnTerminate();
  }
};

}  // namespace app_base
}  // namespace af
}  // namespace daal
