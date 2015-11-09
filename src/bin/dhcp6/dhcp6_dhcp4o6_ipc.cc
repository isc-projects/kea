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

#include <util/buffer.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcp6/dhcp6_dhcp4o6_ipc.h>

using namespace std;

namespace isc {
namespace dhcp {

Dhcp4o6Ipc::Dhcp4o6Ipc() : Dhcp4o6IpcBase() {}

Dhcp4o6Ipc& Dhcp4o6Ipc::instance() {
    static Dhcp4o6Ipc dhcp4o6_ipc;
    return (dhcp4o6_ipc);
}

void Dhcp4o6Ipc::open() {
    uint32_t port = CfgMgr::instance().getStagingCfg()->getDhcp4o6Port();
    if (port == 0) {
        Dhcp4o6IpcBase::close();
        return;
    }

    int old_fd = socket_fd_;
    socket_fd_ = Dhcp4o6IpcBase::open(static_cast<uint16_t>(port), ENDPOINT_TYPE_V6);
    if ((old_fd == -1) && (socket_fd_ != old_fd)) {
        IfaceMgr::instance().addExternalSocket(socket_fd_, Dhcp4o6Ipc::handler);
    }
}

void Dhcp4o6Ipc::handler() {
    Dhcp4o6Ipc& ipc = Dhcp4o6Ipc::instance();
    Pkt6Ptr pkt = ipc.receive();
    if (!pkt) {
        return;
    }

    isc::util::OutputBuffer& buf = pkt->getBuffer();
    buf.clear();
    pkt->pack();

    uint8_t msg_type = buf[0];
    if ((msg_type == DHCPV6_RELAY_FORW) || (msg_type == DHCPV6_RELAY_REPL)) {
        pkt->setRemotePort(DHCP6_SERVER_PORT);
    } else {
        pkt->setRemotePort(DHCP6_CLIENT_PORT);
    }

    IfaceMgr::instance().send(pkt);
    // processStatsSent(pkt);
}

};  // namespace dhcp

};  // namespace isc
