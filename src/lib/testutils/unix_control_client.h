// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
