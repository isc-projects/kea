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

#include <config.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/testutils/dhcp4o6_test_ipc.h>
#include <boost/bind.hpp>

namespace isc {
namespace dhcp {
namespace test {

Dhcp4o6TestIpc::Dhcp4o6TestIpc(const uint16_t port,
                               const EndpointType& endpoint_type)
    : desired_port_(port), endpoint_type_(endpoint_type), pkt_received_() {
}

void
Dhcp4o6TestIpc::open() {
    // Use the base IPC to open the socket.
    socket_fd_ = Dhcp4o6IpcBase::open(desired_port_, endpoint_type_);
    // If the socket has been opened correctly, register it in the @c IfaceMgr.
    if (socket_fd_ != -1) {
        IfaceMgr& iface_mgr = IfaceMgr::instance();
        iface_mgr.addExternalSocket(socket_fd_,
                                    boost::bind(&Dhcp4o6TestIpc::receiveHandler,
                                                this));
    }
}

void
Dhcp4o6TestIpc::receiveHandler() {
    pkt_received_ = receive();
}


} // end of isc::dhcp::test namespace
} // end of isc::dhcp namespace
} // end of isc namespace
