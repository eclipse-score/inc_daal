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

#ifndef SRC_DAAL_AF_APP_BASE_IOHANDLER_HPP
#define SRC_DAAL_AF_APP_BASE_IOHANDLER_HPP

#include <functional>
#include <vector>

#include "daal/af/app_base/safe_application_base.hpp"

namespace daal {
namespace af {

namespace app_base {

class IoHandler {
 public:
  enum class ConnectionState { kDisconnected, kOngoing, kConnected };

  virtual ~IoHandler() = default;

  /* will be called after startup in every cycle until it returns
   * ConnectionState::kConnected */
  virtual ConnectionState Start() = 0;
  /* will be called during shutdown */
  virtual void Stop() = 0;

  virtual void PrepareStep() = 0;
  virtual void FinalizeStep() = 0;
  /* returns the connection status of the IoHandler */
  ConnectionState GetConnectionState() const { return connection_state_; }

 protected:
  void SetConnectionState(ConnectionState state) { connection_state_ = state; }

 private:
  ConnectionState connection_state_ = ConnectionState::kDisconnected;
};

using IoHandlerWrapper = std::reference_wrapper<IoHandler>;
using IoHandlers = std::vector<IoHandlerWrapper>;

class IoHandlerContainer {
 public:
  IoHandlerContainer(IoHandlers const &handlers) : handlers_{handlers} {}
  ~IoHandlerContainer() = default;

  IoHandlers const &GetHandlers() { return handlers_; }

 protected:
  IoHandlers handlers_;
};

template <class ContainerType>
class SafeApplicationBaseWithIo : public SafeApplicationBase {
 public:
  using IoContainerType = ContainerType;
  using AppBase = daal::af::app_base::SafeApplicationBaseWithIo<IoContainerType>;
  SafeApplicationBaseWithIo(IoContainerType ioHandlerContainer)
      : SafeApplicationBase(), ioHandlerContainer_{ioHandlerContainer} {}

  MethodState OnStart() override final {
    for (auto &ioItem : ioHandlerContainer_.GetHandlers()) {
      auto &handler = ioItem.get();
      handler.Start();
    }

    auto ret = OnStart(ioHandlerContainer_);

    return ret;
  }

  virtual MethodState OnStart(IoContainerType &ioHandlers) = 0;

  MethodState Step() override final {
    for (auto &ioItem : ioHandlerContainer_.GetHandlers()) {
      auto &handler = ioItem.get();
      /* if the handler is not connected now, try to establish connection */
      if (IoHandler::ConnectionState::kConnected != handler.GetConnectionState()) {
        handler.Start();
      }
      if (IoHandler::ConnectionState::kConnected == handler.GetConnectionState()) {
        handler.PrepareStep();
      }
    }

    auto ret = Step(ioHandlerContainer_);

    for (auto &ioItem : ioHandlerContainer_.GetHandlers()) {
      auto &handler = ioItem.get();
      if (IoHandler::ConnectionState::kConnected == handler.GetConnectionState()) {
        handler.FinalizeStep();
      }
    }
    return ret;
  }

  virtual MethodState Step(IoContainerType &ioHandlers) = 0;

  MethodState OnStop() override final {
    auto ret = OnStop(ioHandlerContainer_);

    for (auto &ioItem : ioHandlerContainer_.GetHandlers()) {
      auto &handler = ioItem.get();
      handler.Stop();
    }

    return ret;
  }

  virtual MethodState OnStop(IoContainerType &ioHandlers) = 0;

 protected:
  IoContainerType ioHandlerContainer_;
};

}  // namespace app_base
}  // namespace af
}  // namespace daal

#endif  // SRC_DAAL_AF_APP_BASE_IOHANDLER_HPP
