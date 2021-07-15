// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file http_control_socket.h
/// Contains declarations for HTTP control socket communication.

#ifndef HTTP_CONTROL_SOCKET_H
#define HTTP_CONTROL_SOCKET_H

#include <netconf/control_socket.h>

namespace isc {
namespace netconf {

/// @brief Class for control socket communication over HTTP socket.
///
/// This class is the derived class for control socket communication
/// over HTTP sockets.
/// This class implements config-get, config-test and config-set.
class HttpControlSocket : public ControlSocketBase {
public:

    /// @brief Constructor.
    ///
    /// @param ctrl_sock The control socket configuration.
    HttpControlSocket(CfgControlSocketPtr ctrl_sock);

    /// @brief Destructor (does nothing).
    virtual ~HttpControlSocket() = default;

    /// @brief Get configuration.
    ///
    /// Call config-get over the control socket.
    ///
    /// @param service The target service.
    /// @return The JSON element answer of config-get.
    /// @throw ControlSocketError when a communication error occurs.
    virtual data::ConstElementPtr configGet(const std::string& service);

    /// @brief Test configuration.
    ///
    /// Call config-test over the control socket.
    ///
    /// @param config The configuration to test.
    /// @param service The target service.
    /// @return The JSON element answer of config-test.
    /// @throw ControlSocketError when a communication error occurs.
    virtual data::ConstElementPtr configTest(data::ConstElementPtr config,
                                             const std::string& service);

    /// @brief Set configuration.
    ///
    /// Call config-set over the control socket.
    ///
    /// @param config The configuration to set.
    /// @param service The target service.
    /// @return The JSON element answer of config-set.
    /// @throw ControlSocketError when a communication error occurs.
    virtual data::ConstElementPtr configSet(data::ConstElementPtr config,
                                            const std::string& service);

private:
    /// @brief Perform the actual communication.
    ///
    /// @todo Use persistent connections (vs. a new connection per call)
    /// as the HTTP library supports them.
    ///
    /// @param command The command to send.
    /// @return The answer.
    data::ConstElementPtr sendCommand(data::ConstElementPtr command);
};

/// @brief Type definition for the pointer to the @c HttpControlSocket.
typedef boost::shared_ptr<HttpControlSocket> HttpControlSocketPtr;

/// @brief Factory template specialization for http control sockets.
///
/// @param ctrl_sock The control socket configuration.
/// @return A pointer to a http control socket communication object.
template <> ControlSocketBasePtr
createControlSocket<CfgControlSocket::Type::HTTP>(CfgControlSocketPtr ctrl_sock);

} // namespace netconf
} // namespace isc

#endif // HTTP_CONTROL_SOCKET_H
