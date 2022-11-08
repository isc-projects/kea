// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file unix_control_socket.h
/// Contains declarations for UNIX control socket communication.

#ifndef UNIX_CONTROL_SOCKET_H
#define UNIX_CONTROL_SOCKET_H

#include <netconf/control_socket.h>

namespace isc {
namespace netconf {

/// @brief Class for control socket communication over UNIX socket.
///
/// This class is the derived class for control socket communication
/// over UNIX sockets.
/// This class implements config-get, config-test and config-set.
class UnixControlSocket : public ControlSocketBase {
public:
    /// @brief Constructor.
    ///
    /// @param ctrl_sock The control socket configuration.
    UnixControlSocket(CfgControlSocketPtr ctrl_sock);

    /// @brief Destructor (does nothing).
    virtual ~UnixControlSocket() = default;

    /// @brief Get configuration.
    ///
    /// Call config-get over the control socket.
    ///
    /// @param service The target service (ignored).
    /// @return The JSON element answer of config-get.
    /// @throw ControlSocketError when a communication error occurs.
    data::ConstElementPtr configGet(const std::string& service) override final;

    /// @brief Test configuration.
    ///
    /// Call config-test over the control socket.
    ///
    /// @param service The target service (ignored).
    /// @param config The configuration to test.
    /// @return The JSON element answer of config-test.
    /// @throw ControlSocketError when a communication error occurs.
    data::ConstElementPtr configTest(data::ElementPtr config,
                                     const std::string& service) override final;

    /// @brief Set configuration.
    ///
    /// Call config-set over the control socket.
    ///
    /// @param config The configuration to set.
    /// @param service The target service (ignored).
    /// @return The JSON element answer of config-set.
    /// @throw ControlSocketError when a communication error occurs.
    data::ConstElementPtr configSet(data::ElementPtr config,
                                    const std::string& service) override final;

private:
    /// @brief Perform the actual communication.
    ///
    /// @note This method is synchronous, i.e. it blocks until it finishes
    /// and returns.
    ///
    /// @param command The command to send.
    /// @return The answer.
    data::ConstElementPtr sendCommand(data::ConstElementPtr command);
};  // UnixControlSocket

/// @brief Type definition for the pointer to the @c UnixControlSocket.
using UnixControlSocketPtr = std::shared_ptr<UnixControlSocket>;

/// @brief Factory template specialization for unix control sockets.
///
/// @param ctrl_sock The control socket configuration.
/// @return A pointer to a unix control socket communication object.
template <> ControlSocketBasePtr
createControlSocket<CfgControlSocket::Type::UNIX>(CfgControlSocketPtr ctrl_sock);

}  // namespace netconf
}  // namespace isc

#endif  // UNIX_CONTROL_SOCKET_H
