// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file control_socket.h
/// Contains declarations for control socket communication.

#ifndef CONTROL_SOCKET_H
#define CONTROL_SOCKET_H

#include <exceptions/exceptions.h>
#include <netconf/netconf_config.h>

namespace isc {
namespace netconf {

/// @brief Exception thrown when the error during communication.
class ControlSocketError : public isc::Exception {
public:
    ControlSocketError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { }
};  // ControlSocketError

/// @brief Base class for control socket communication.
///
/// This class is the base class for control socket communication.
/// Derived classes implement config-get, config-test and config-set
/// using control sockets of different types. Those classes are used to
/// communicate with other Kea daemons.
class ControlSocketBase {
public:
    /// @brief Constructor.
    ///
    /// @param ctrl_sock The control socket configuration.
    /// @throw ControlSocketError if ctrl_sock is null.
    ControlSocketBase(CfgControlSocketPtr ctrl_sock) : socket_cfg_(ctrl_sock) {
        if (!ctrl_sock) {
            isc_throw(ControlSocketError, "ControlSocket constructor called "
                      "with a null configuration");
        }
    }

    /// @brief Destructor (does nothing).
    virtual ~ControlSocketBase() = default;

    /// @brief Getter which returns the socket type.
    ///
    /// @return returns the socket type as a CfgControlSocket::Type.
    CfgControlSocket::Type getType() const {
        return (socket_cfg_->getType());
    }

    /// @brief Returns the Unix socket name.
    ///
    /// @return returns the Unix socket name as a std::string.
    const std::string getName() const {
        return (socket_cfg_->getName());
    }

    /// @brief Returns the HTTP server URL.
    ///
    /// @return returns the HTTP server URL as an isc::http::Url.
    const isc::http::Url getUrl() const {
        return (socket_cfg_->getUrl());
    }

    /// @brief Get configuration.
    ///
    /// Call config-get over the control socket.
    ///
    /// @param service The target service (used by http).
    /// @return The JSON element answer of config-get.
    /// @throw ControlSocketError when a communication error occurs.
    virtual data::ConstElementPtr configGet(const std::string& service) = 0;

    /// @brief Test configuration.
    ///
    /// Call config-test over the control socket.
    ///
    /// @param config The configuration to test.
    /// @param service The target service (used by http).
    /// @return The JSON element answer of config-test.
    /// @throw ControlSocketError when a communication error occurs.
    virtual data::ConstElementPtr configTest(data::ElementPtr config,
                                             const std::string& service) = 0;

    /// @brief Set configuration.
    ///
    /// Call config-set over the control socket.
    ///
    /// @param config The configuration to set.
    /// @param service The target service (used by http).
    /// @return The JSON element answer of config-set.
    /// @throw ControlSocketError when a communication error occurs.
    virtual data::ConstElementPtr configSet(data::ElementPtr config,
                                            const std::string& service) = 0;

    /// @brief The control socket configuration.
    CfgControlSocketPtr socket_cfg_;
};  // ControlSocketBase

/// @brief Type definition for the pointer to the @c ControlSocketBase.
using ControlSocketBasePtr = std::shared_ptr<ControlSocketBase>;

/// @brief Factory template for control sockets.
///
/// @tparam TYPE The control socket type.
/// @param ctrl_sock The control socket configuration.
/// @return A pointer to a control socket communication object.
/// @throw NotImplemented if no specialization was called.
template <CfgControlSocket::Type TYPE> ControlSocketBasePtr
createControlSocket(CfgControlSocketPtr ctrl_sock) {
    isc_throw(NotImplemented, "not specialized createControlSocket");
}

/// @brief Factory function for control sockets.
///
/// @param ctrl_sock The control socket configuration.
/// @return A pointer to a control socket communication object.
/// @throw BadValue if called with null or an unknown type.
ControlSocketBasePtr
controlSocketFactory(CfgControlSocketPtr ctrl_sock);

}  // namespace netconf
}  // namespace isc

#endif  // CONTROL_SOCKET_H
