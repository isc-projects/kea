// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file stdout_control_socket.h
/// Contains declarations for stdout control socket communication.

#ifndef STDOUT_CONTROL_SOCKET_H
#define STDOUT_CONTROL_SOCKET_H

#include <netconf/control_socket.h>
#include <iostream>

namespace isc {
namespace netconf {

/// @brief Class for control socket communication over stdout.
///
/// This class is the derived class for control socket communication
/// over stdout.
/// This class implements config-test (always OK) and config-set.
class StdoutControlSocket : public ControlSocketBase {
public:
    /// @brief Constructor.
    ///
    /// Use std::cout.
    ///
    /// @param ctrl_sock The control socket configuration.
    StdoutControlSocket(CfgControlSocketPtr ctrl_sock);

    /// @brief Destructor (does nothing).
    virtual ~StdoutControlSocket() = default;

    /// @brief Get configuration.
    ///
    /// Call config-get over the control socket.
    ///
    /// @param service The target service (ignored).
    /// @return The JSON element answer of config-get.
    /// @throw NotImplemented
    data::ConstElementPtr configGet(const std::string& service) override final;

    /// @brief Test configuration.
    ///
    /// Call config-test over the control socket.
    ///
    /// @param config The configuration to test (ignored).
    /// @param service The target service (ignored).
    /// @return The JSON element answer of config-test (fixed answer).
    data::ConstElementPtr configTest(data::ElementPtr config,
                                     const std::string& service) override final;

    /// @brief Set configuration.
    ///
    /// Call config-set over the control socket.
    ///
    /// @param config The configuration to set.
    /// @param service The target service.
    /// @return The JSON element answer of config-set (fixed answer).
    data::ConstElementPtr configSet(data::ElementPtr config,
                                    const std::string& service) override final;

protected:
    /// @brief Alternative constructor for tests.
    ///
    /// @param ctrl_sock The control socket configuration.
    /// @param output The output stream.
    StdoutControlSocket(CfgControlSocketPtr ctrl_sock, std::ostream& output);

    /// @brief The output stream (std::cout outside tests).
    std::ostream& output_;
};  // StdoutControlSocket

/// @brief Type definition for the pointer to the @c StdoutControlSocket.
using StdoutControlSocketPtr = std::shared_ptr<StdoutControlSocket>;

/// @brief Factory template specialization for stdout control sockets.
///
/// @param ctrl_sock The control socket configuration.
/// @return A pointer to a stdout control socket communication object.
template <> ControlSocketBasePtr
createControlSocket<CfgControlSocket::Type::STDOUT>(CfgControlSocketPtr ctrl_sock);

}  // namespace netconf
}  // namespace isc

#endif  // STDOUT_CONTROL_SOCKET_H
