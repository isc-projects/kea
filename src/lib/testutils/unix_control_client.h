// Copyright (C) 2015-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UNIX_CONTROL_CLIENT_H
#define UNIX_CONTROL_CLIENT_H

#include <asiolink/io_service.h>
#include <asiolink/unix_domain_socket.h>
#include <string>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Class that acts as a UnixCommandSocket client
///
/// This class is expected to be used unit-tests that attempt to communicate
/// with the servers that use control channel (see src/lib/config/command_mgr.h)
/// It can connect to an open UnixCommandSocket and exchange ControlChannel
/// commands and responses.
///
/// It uses standard socket system calls e.g. send() and recv() by design.
/// @note macOS uses by default small send and receive spaces for Unix/local
/// sockets so for instance a large command can make send() to hang if
/// the server is not reading.
class UnixControlClient {
public:

    /// @brief Default constructor
    ///
    /// @brief io_service The IOService used in test.
    UnixControlClient(asiolink::IOServicePtr io_service);

    /// @brief Destructor
    ~UnixControlClient();

    /// @brief Closes the Control Channel socket
    void disconnectFromServer();

    /// @brief Connects to a Unix socket at the given path
    /// @param socket_path pathname of the socket to open
    /// @return true if the connect was successful, false otherwise
    bool connectToServer(const std::string& socket_path);

    /// @brief Sends the given command across the open Control Channel
    /// @param command the command text to execute in JSON form
    /// @return true if the send succeeds, false otherwise
    bool sendCommand(const std::string& command);

    /// @brief Reads the response text from the open Control Channel
    /// @param response variable into which the received response should be
    /// placed.
    /// @param timeout_sec Timeout for receiving response in seconds.
    /// @return true if data was successfully read from the socket,
    /// false otherwise
    bool getResponse(std::string& response, const unsigned int timeout_sec = 0);

private:

    /// @brief The IOSerice used for async operations.
    asiolink::IOServicePtr io_service_;

    /// @brief Unix domain socket used for communication with a server.
    asiolink::UnixDomainSocket socket_;
};

} // end of isc::dhcp::test namespace
} // end of isc::dhcp namespace
} // end of isc namespace

#endif // UNIX_CONTROL_CLIENT_H
