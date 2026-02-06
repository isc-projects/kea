// Copyright (C) 2020-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_STATUS_H
#define RADIUS_STATUS_H

#include <client_exchange.h>
#include <radius.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/timer_mgr.h>

#include <functional>
#include <sstream>

namespace isc {
namespace radius {

/// @brief Type of callback for status termination.
///
/// The argument is the result code.
typedef std::function<void(int)> CallbackStatus;

/// @brief Base class for communication with servers.
class RadiusStatus {
public:

    /// @brief Constructor.
    RadiusStatus() : exchange_() {
    }

    /// @brief Destructor.
    virtual ~RadiusStatus() = default;

    /// @brief Start communication.
    ///
    /// Initiates the (first) exchange.
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
    /// @brief Exchange.
    ExchangePtr exchange_;
};

/// @brief Class for communication with access servers.
///
/// Only the asynchronous variant is defined.
class RadiusAuthStatus : public RadiusStatus {
public:

    /// @brief Constructor.
    ///
    /// @param send_attrs Attributes to send.
    /// @param handler Termination handler.
    RadiusAuthStatus(const AttributesPtr& send_attrs,
                     const CallbackStatus& handler);

    /// @brief Destructor.
    virtual ~RadiusAuthStatus() = default;

    /// @brief Start communication.
    virtual void start() override;

    /// @brief Invoke access status callback.
    ///
    /// @param callback Termination callback.
    /// @param exchange the exchange.
    static void invokeCallback(const CallbackStatus& callback,
                               const ExchangePtr exchange);
};

/// @brief Pointer to access status.
typedef boost::shared_ptr<RadiusAuthStatus> RadiusAuthStatusPtr;

/// @brief Class for communication with accounting servers.
///
/// Only the asynchronous variant is defined.
class RadiusAcctStatus : public RadiusStatus {
public:

    /// @brief Constructor.
    ///
    /// @param send_attrs Attributes to send.
    /// @param handler Termination handler.
    RadiusAcctStatus(const AttributesPtr& send_attrs,
                     const CallbackStatus& handler);

    /// @brief Destructor.
    virtual ~RadiusAcctStatus() = default;

    /// @brief Start communication.
    virtual void start() override;

    /// @brief Invoke accounting status callback.
    ///
    /// @param callback Termination callback.
    /// @param exchange the exchange.
    static void invokeCallback(const CallbackStatus& callback,
                               const ExchangePtr exchange);
};

/// @brief Pointer to accounting status.
typedef boost::shared_ptr<RadiusAcctStatus> RadiusAcctStatusPtr;

/// @brief Class for communication with common TLS servers.
///
/// Only the asynchronous variant is defined.
class RadiusTlsStatus : public RadiusStatus {
public:

    /// @brief Constructor.
    ///
    /// @param send_attrs Attributes to send.
    /// @param handler Termination handler.
    RadiusTlsStatus(const AttributesPtr& send_attrs,
                    const CallbackStatus& handler);

    /// @brief Destructor.
    virtual ~RadiusTlsStatus() = default;

    /// @brief Start communication.
    virtual void start() override;

    /// @brief Invoke access status callback.
    ///
    /// @param callback Termination callback.
    /// @param exchange the exchange.
    static void invokeCallback(const CallbackStatus& callback,
                               const ExchangePtr exchange);
};

/// @brief Pointer to access status.
typedef boost::shared_ptr<RadiusTlsStatus> RadiusTlsStatusPtr;

} // end of namespace radius
} // end of namespace isc
#endif // RADIUS_STATUS_H
