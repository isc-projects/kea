// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <testutils/unix_control_client.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <string.h>

namespace isc {
namespace dhcp {
namespace test {

UnixControlClient::UnixControlClient() {
    socket_fd_ = -1;
}

UnixControlClient::~UnixControlClient() {
    disconnectFromServer();
}

    /// @brief Closes the Control Channel socket
void UnixControlClient::disconnectFromServer() {
    if (socket_fd_ >= 0) {
        static_cast<void>(close(socket_fd_));
        socket_fd_ = -1;
    }
}

bool UnixControlClient::connectToServer(const std::string& socket_path) {
    // Create UNIX socket
    socket_fd_ = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd_ < 0) {
        const char* errmsg = strerror(errno);
        ADD_FAILURE() << "Failed to open unix stream socket: " << errmsg;
        return (false);
    }

    struct sockaddr_un srv_addr;
    if (socket_path.size() > sizeof(srv_addr.sun_path) - 1) {
        ADD_FAILURE() << "Socket path specified (" << socket_path
                      << ") is larger than " << (sizeof(srv_addr.sun_path) - 1)
                      << " allowed.";
        disconnectFromServer();
        return (false);
    }

    // Prepare socket address
    memset(&srv_addr, 0, sizeof(srv_addr));
    srv_addr.sun_family = AF_UNIX;
    strncpy(srv_addr.sun_path, socket_path.c_str(),
            sizeof(srv_addr.sun_path));
    socklen_t len = sizeof(srv_addr);

    // Connect to the specified UNIX socket
    int status = connect(socket_fd_, (struct sockaddr*)&srv_addr, len);
    if (status == -1) {
        const char* errmsg = strerror(errno);
        ADD_FAILURE() << "Failed to connect unix socket: fd=" << socket_fd_
                      << ", path=" << socket_path << " : " << errmsg;
        disconnectFromServer();
        return (false);
    }

    return (true);
}

bool UnixControlClient::sendCommand(const std::string& command) {
    // Send command
    int bytes_sent = send(socket_fd_, command.c_str(), command.length(), 0);
    if (bytes_sent < command.length()) {
        const char* errmsg = strerror(errno);
        ADD_FAILURE() << "Failed to send " << command.length()
                      << " bytes, send() returned " << bytes_sent
                      << " : " << errmsg;
        return (false);
    }

    return (true);
}

bool UnixControlClient::getResponse(std::string& response) {
    // Receive response
    char buf[65536];
    memset(buf, 0, sizeof(buf));
    switch (selectCheck()) {
    case -1: {
        const char* errmsg = strerror(errno);
        ADD_FAILURE() << "getResponse - select failed: " << errmsg;
        return (false);
    }
    case 0:
        ADD_FAILURE() << "No response data sent";
        return (false);

    default:
        break;
    }

    int bytes_rcvd = recv(socket_fd_, buf, sizeof(buf), 0);
    if (bytes_rcvd < 0) {
        const char* errmsg = strerror(errno);
        ADD_FAILURE() << "Failed to receive a response. recv() returned "
                      << bytes_rcvd << " : " << errmsg;
        return (false);
    }

    if (bytes_rcvd >= sizeof(buf)) {
        ADD_FAILURE() << "Response size too large: " << bytes_rcvd;
        return (false);
    }

    // Convert the response to a string
    response = std::string(buf, bytes_rcvd);
    return (true);
}

int UnixControlClient::selectCheck() {
    int maxfd = 0;

    fd_set read_fds;
    FD_ZERO(&read_fds);

    // Add this socket to listening set
    FD_SET(socket_fd_,  &read_fds);
    maxfd = socket_fd_;

    struct timeval select_timeout;
    select_timeout.tv_sec = 0;
    select_timeout.tv_usec = 0;

    return (select(maxfd + 1, &read_fds, NULL, NULL, &select_timeout));
}

};
};
};
