// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/testutils/dhcp4o6_test_ipc.h>
#include <functional>

namespace isc {
namespace dhcp {
namespace test {

Dhcp4o6TestIpc::Dhcp4o6TestIpc(uint16_t port, EndpointType endpoint_type)
    : desired_port_(port), endpoint_type_(endpoint_type), pkt_received_() {
}

void
Dhcp4o6TestIpc::open() {
    // Use the base IPC to open the socket.
    socket_fd_ = Dhcp4o6IpcBase::open(desired_port_, endpoint_type_);
    // If the socket has been opened correctly, register it in the @c IfaceMgr.
    // BTW if it has not an exception has been thrown so it is only
    // a sanity / recommended check.
    if (socket_fd_ != -1) {
        IfaceMgr& iface_mgr = IfaceMgr::instance();
        iface_mgr.addExternalSocket(socket_fd_,
                std::bind(&Dhcp4o6TestIpc::receiveHandler, this));
    }
}

void
Dhcp4o6TestIpc::receiveHandler() {
    pkt_received_ = receive();
}

} // end of isc::dhcp::test namespace
} // end of isc::dhcp namespace
} // end of isc namespace
