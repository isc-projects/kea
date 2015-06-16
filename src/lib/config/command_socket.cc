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

#include <config/command_socket.h>
#include <config/command_mgr.h>
#include <config/config_log.h>
#include <dhcp/iface_mgr.h>
#include <boost/bind.hpp>
#include <unistd.h>

namespace isc {
namespace config {

ConnectionSocket::ConnectionSocket(int sockfd)
    :CommandSocket(isc::data::ConstElementPtr()) {
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
