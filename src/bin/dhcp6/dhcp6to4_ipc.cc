// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/buffer.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcp6/dhcp6to4_ipc.h>

using namespace std;

namespace isc {
namespace dhcp {

Dhcp6to4Ipc::Dhcp6to4Ipc() : Dhcp4o6IpcBase() {}

Dhcp6to4Ipc& Dhcp6to4Ipc::instance() {
    static Dhcp6to4Ipc dhcp6to4_ipc;
    return (dhcp6to4_ipc);
}

void Dhcp6to4Ipc::open() {
    uint32_t port = CfgMgr::instance().getStagingCfg()->getDhcp4o6Port();
    if (port == 0) {
        Dhcp4o6IpcBase::close();
        return;
    }
    if (port > 65534) {
        isc_throw(OutOfRange, "DHCP4o6 port " << port);
    }

    int old_fd = socket_fd_;
    socket_fd_ = Dhcp4o6IpcBase::open(static_cast<uint16_t>(port),
                                      ENDPOINT_TYPE_V6);
    if ((old_fd == -1) && (socket_fd_ != old_fd)) {
        IfaceMgr::instance().addExternalSocket(socket_fd_,
                                               Dhcp6to4Ipc::handler);
    }
}

void Dhcp6to4Ipc::handler() {
    Dhcp6to4Ipc& ipc = Dhcp6to4Ipc::instance();

    // Receive message from IPC.
    Pkt6Ptr pkt = ipc.receive();
    if (!pkt) {
        return;
    }

    // The received message has been unpacked by the receive() function. This
    // method could have modified the message so it's better to pack() it
    // again because we'll be forwarding it to a client.
    isc::util::OutputBuffer& buf = pkt->getBuffer();
    buf.clear();
    pkt->pack();

    uint8_t msg_type = pkt->getType();
    if ((msg_type == DHCPV6_RELAY_FORW) || (msg_type == DHCPV6_RELAY_REPL)) {
        pkt->setRemotePort(DHCP6_SERVER_PORT);
    } else {
        pkt->setRemotePort(DHCP6_CLIENT_PORT);
    }

    // Forward packet to the client.
    IfaceMgr::instance().send(pkt);
    // processStatsSent(pkt);
}

};  // namespace dhcp

};  // namespace isc
