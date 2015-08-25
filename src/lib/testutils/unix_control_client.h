// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef UNIX_CONTROL_CLIENT_H
#define UNIX_CONTROL_CLIENT_H

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
class UnixControlClient {
public:

    /// @brief Default constructor
    UnixControlClient();

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
    /// @return true if data was successfully read from the socket,
    /// false otherwise
    bool getResponse(std::string& response);

    /// @brief Uses select to poll the Control Channel for data waiting
    /// @return -1 on error, 0 if no data is available,  1 if data is ready
    int selectCheck();

    /// @brief Retains the fd of the open socket
    int socket_fd_;
};

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // UNIX_CONTROL_CLIENT_H
