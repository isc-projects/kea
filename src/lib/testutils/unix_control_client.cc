// Copyright (C) 2015-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

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
            sizeof(srv_addr.sun_path) - 1);
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
    if (socket_fd_ < 0) {
        ADD_FAILURE() << "send command with closed socket";
        return (false);
    }
    switch (selectCheck(3, false, true)) {
    case -1: {
        const char* errmsg = strerror(errno);
        ADD_FAILURE() << "sendCommand - select failed: " << errmsg;
        return (false);
    }
    case 0:
        return (false);

    default:
        break;
    }
    // Send command
    int bytes_sent = send(socket_fd_, command.c_str(), command.length(), 0);
    if (bytes_sent < static_cast<int>(command.length())) {
        const char* errmsg = strerror(errno);
        ADD_FAILURE() << "Failed to send " << command.length()
                      << " bytes, send() returned " << bytes_sent
                      << " : " << errmsg;
        return (false);
    }

    return (true);
}

bool UnixControlClient::getResponse(std::string& response,
                                    const unsigned int timeout_sec) {
    // Receive response
    char buf[65536];
    memset(buf, 0, sizeof(buf));
    switch (selectCheck(timeout_sec, true, false)) {
    case -1: {
        const char* errmsg = strerror(errno);
        ADD_FAILURE() << "getResponse - select failed: " << errmsg;
        return (false);
    }
    case 0:
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

    // Convert the response to a string
    response = std::string(buf, bytes_rcvd);
    return (true);
}

int UnixControlClient::selectCheck(const unsigned int timeout_sec,
                                   bool read_check,
                                   bool write_check) {
    if (socket_fd_ < 0) {
        ADD_FAILURE() << "select check with closed socket";
        return -1;
    }
    if (socket_fd_ > 1023) {
        ADD_FAILURE() << "select check with out of bound socket";
        return -1;
    }
    int maxfd = 0;

    fd_set read_fds;
    FD_ZERO(&read_fds);

    fd_set write_fds;
    FD_ZERO(&write_fds);

    maxfd = socket_fd_;

    // Add this socket to read set
    FD_SET(socket_fd_, &read_fds);

    // Add this socket to write set
    FD_SET(socket_fd_, &write_fds);

    struct timeval select_timeout;
    select_timeout.tv_sec = static_cast<time_t>(timeout_sec);
    select_timeout.tv_usec = 0;

    fd_set* read_p = 0;
    fd_set* write_p = 0;

    if (read_check) {
        read_p = &read_fds;
    }

    if (write_check) {
        write_p = &write_fds;
    }

    return (select(maxfd + 1, read_p, write_p, NULL, &select_timeout));
}

}
}
}
