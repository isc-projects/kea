// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_REQUEST_H
#define RADIUS_REQUEST_H

#include <client_exchange.h>
#include <radius.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/timer_mgr.h>

#include <functional>
#include <sstream>

namespace isc {
namespace radius {

/// @brief Type of callback for authentication termination.
/// First argument is the result code, second is the attribute collection
/// from server response.
typedef std::function<void(int, AttributesPtr)> CallbackAuth;

/// @brief Type of callback for accounting termination.
/// The argument is the result code.
typedef std::function<void(int)> CallbackAcct;

/// @brief Remap a subnet ID to a NAS port.
///
/// First the subnet ID is looked for in the remap table.
/// Second if not found the default is tried.
/// Finally the subnet ID is returned as it.
///
/// @param subnet_id The subnet ID to map to a NAS port.
/// @return (eventually) mapped NAS port
uint32_t getNASPort(uint32_t subnet_id);

/// @brief Base class for communication with servers.
/// It represents the common part of authentication/authorization and
/// accounting communication.
class RadiusRequest {
public:

    /// @brief Constructor.
    ///
    /// @param code message code (PW_ACCESS_REQUEST or PW_ACCOUNTING_REQUEST).
    /// @param subnet_id Subnet ID (aka client/NAS port).
    /// @param send_attrs Attributes to send.
    /// @param sync true if synchronous, false if asynchronous.
    /// @param handler Termination handler.
    RadiusRequest(const MsgCode code,
                  uint32_t subnet_id,
                  const AttributesPtr& send_attrs,
                  bool sync,
                  const Exchange::Handler& handler);

    /// @brief Destructor.
    virtual ~RadiusRequest() = default;

    /// @brief Start communication.
    /// In synchronous mode it returns when exchange(s) is(are) finished,
    /// in asynchronous mode it initiates the (first) exchange.
    virtual void start() {
        exchange_->start();
    }

    /// @brief Get the error code.
    int getRC() const {
        return (exchange_->getRC());
    }

    /// @brief Get request attributes.
    ///
    /// @return attributes from the to be sent request message.
    AttributesPtr getReqAttrs() const {
        MessagePtr request = exchange_->getRequest();
        if (request) {
            return (request->getAttributes());
        }
        return (AttributesPtr());
    }

    /// @brief Get response attributes.
    ///
    /// @return attributes from the received response message.
    AttributesPtr getRespAttrs() const {
        MessagePtr response = exchange_->getResponse();
        if (response) {
            return (response->getAttributes());
        }
        return (AttributesPtr());
    }

    /// @brief Get the exchange.
    ///
    /// @return The exchange.
    ExchangePtr getExchange() {
        return (exchange_);
    }

protected:
    /// @brief Client/NAS port (from Subnet Id).
    uint32_t nas_port_;

    /// @brief Exchange.
    ExchangePtr exchange_;
};

/// @brief class for authentication communication with servers.
class RadiusAuth : public RadiusRequest {
public:

    /// @brief Constructor.
    ///
    /// @param subnet_id Subnet ID (aka client/NAS port).
    /// @param send_attrs Attributes to send.
    /// @param sync true if synchronous, false if asynchronous.
    /// @param handler Termination handler.
    RadiusAuth(uint32_t subnet_id,
               const AttributesPtr& send_attrs,
               bool sync,
               const Exchange::Handler& handler)
        : RadiusRequest(PW_ACCESS_REQUEST, subnet_id, send_attrs, sync,
                        handler) {
    }

    /// @brief Destructor.
    virtual ~RadiusAuth() = default;
};

/// @brief class for synchronous authentication communication with servers.
class RadiusSyncAuth : public RadiusAuth {
public:

    /// @brief Constructor.
    ///
    /// @param subnet_id Subnet ID (aka client/NAS port).
    /// @param send_attrs Attributes to send.
    /// @param callback Termination callback.
    RadiusSyncAuth(uint32_t subnet_id,
                   const AttributesPtr& send_attrs,
                   const CallbackAuth& callback)
        : RadiusAuth(subnet_id, send_attrs, true, Exchange::Handler()),
          callback_(callback) {
    }

    /// @brief Destructor.
    virtual ~RadiusSyncAuth() = default;

    /// @brief Start communication.
    virtual void start() override;

protected:
    /// @brief Authentication termination callback.
    CallbackAuth callback_;
};

/// @brief Pointer to synchronous authentication.
typedef boost::shared_ptr<RadiusSyncAuth> RadiusSyncAuthPtr;

/// @brief class for asynchronous authentication communication with servers.
class RadiusAsyncAuth : public RadiusAuth {
public:

    /// @brief Constructor.
    ///
    /// @param subnet_id Subnet ID (aka client/NAS port).
    /// @param send_attrs Attributes to send.
    /// @param callback Termination callback.
    RadiusAsyncAuth(uint32_t subnet_id,
                    const AttributesPtr& send_attrs,
                    const CallbackAuth& callback);

    /// @brief Destructor.
    virtual ~RadiusAsyncAuth() = default;

    /// @brief Start communication.
    virtual void start() override;

    /// @brief Invoke authentication communication callback
    ///
    /// @param callback Termination callback
    /// @param exchange the exchange.
    static void invokeCallback(const CallbackAuth& callback,
                               const ExchangePtr exchange);
};

/// @brief Pointer to asynchronous authentication.
typedef boost::shared_ptr<RadiusAsyncAuth> RadiusAsyncAuthPtr;

/// @brief class for accounting communication with servers.
class RadiusAcct : public RadiusRequest {
public:

    /// @brief Constructor.
    ///
    /// @param subnet_id Subnet ID (aka client/NAS port).
    /// @param send_attrs Attributes to send.
    /// @param sync true if synchronous, false if asynchronous.
    /// @param handler Termination handler.
    RadiusAcct(uint32_t subnet_id,
               const AttributesPtr& send_attrs,
               bool sync,
               const Exchange::Handler& handler)
        : RadiusRequest(PW_ACCOUNTING_REQUEST, subnet_id, send_attrs, sync,
                        handler) {
    }

    /// @brief Destructor.
    virtual ~RadiusAcct() = default;
};

/// @brief class for synchronous accounting communication with servers.
class RadiusSyncAcct : public RadiusAcct {
public:

    /// @brief Constructor.
    ///
    /// @param subnet_id Subnet ID (aka client/NAS port).
    /// @param send_attrs Attributes to send.
    /// @param callback Termination callback.
    RadiusSyncAcct(uint32_t subnet_id,
                   const AttributesPtr& send_attrs,
                   const CallbackAcct& callback)
        : RadiusAcct(subnet_id, send_attrs, true, Exchange::Handler()), callback_(callback) {
    }

    /// @brief Destructor.
    virtual ~RadiusSyncAcct() = default;

    /// @brief Start communication.
    virtual void start() override;

protected:
    /// @brief Accounting termination callback.
    CallbackAcct callback_;
};

/// @brief Pointer to synchronous accounting.
typedef boost::shared_ptr<RadiusSyncAcct> RadiusSyncAcctPtr;

/// @brief class for asynchronous accounting communication with servers.
class RadiusAsyncAcct : public RadiusAcct {
public:

    /// @brief Constructor.
    ///
    /// @param subnet_id Subnet ID (aka client/NAS port).
    /// @param send_attrs Attributes to send.
    /// @param callback Termination callback.
    RadiusAsyncAcct(uint32_t subnet_id,
                    const AttributesPtr& send_attrs,
                    const CallbackAcct& callback);

    /// @brief Destructor.
    virtual ~RadiusAsyncAcct() = default;

    /// @brief Start communication.
    virtual void start() override;

    /// @brief Invoke accounting communication callback
    ///
    /// @param callback Termination callback.
    /// @param exchange the exchange.
    static void invokeCallback(const CallbackAcct& callback,
                               const ExchangePtr exchange);
};

/// @brief Pointer to asynchronous accounting.
typedef boost::shared_ptr<RadiusAsyncAcct> RadiusAsyncAcctPtr;

} // end of namespace radius
} // end of namespace isc
#endif // RADIUS_REQUEST_H
