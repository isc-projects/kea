// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config/command_socket.h>
#include <config/command_mgr.h>
#include <config/config_log.h>
#include <dhcp/iface_mgr.h>
#include <boost/bind.hpp>
#include <unistd.h>

namespace isc {
namespace config {

ConnectionSocket::ConnectionSocket(int sockfd) {
    sockfd_ = sockfd;

    // Install commandReader callback. When there's any data incoming on this
    // socket, commandReader will be called and process it. It may also
    // eventually close this socket.
    isc::dhcp::IfaceMgr::instance().addExternalSocket(sockfd,
        boost::bind(&ConnectionSocket::receiveHandler, this));
    }

void ConnectionSocket::close() {
    LOG_INFO(command_logger, COMMAND_SOCKET_CONNECTION_CLOSED).arg(sockfd_);

    // Unregister this callback
    isc::dhcp::IfaceMgr::instance().deleteExternalSocket(sockfd_);

    // We're closing a connection, not the whole socket. It's ok to just
    // close the connection and don't delete anything.
    ::close(sockfd_);
}

void ConnectionSocket::receiveHandler() {
    CommandMgr::instance().commandReader(sockfd_);
}

};
};
