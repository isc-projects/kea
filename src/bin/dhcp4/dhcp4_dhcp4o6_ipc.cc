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
#include <dhcp4/dhcp4_dhcp4o6_ipc.h>

using namespace std;

namespace isc {
namespace dhcp {

Dhcp4to6Ipc::Dhcp4to6Ipc() : Dhcp4o6IpcBase() {
}

Dhcp4to6Ipc& Dhcp4to6Ipc::instance() {
    static Dhcp4to6Ipc dhcp4to6_ipc;
    return (dhcp4to6_ipc);
}

void Dhcp4to6Ipc::open() {
    uint32_t port = CfgMgr::instance().getStagingCfg()->getDhcp4o6Port();
    if (port == 0) {
        Dhcp4o6IpcBase::close();
        return;
    }

    int old_fd = socket_fd_;
    socket_fd_ = Dhcp4o6IpcBase::open(static_cast<uint16_t>(port), ENDPOINT_TYPE_V4);
    if ((old_fd == -1) && (socket_fd_ != old_fd)) {
        IfaceMgr::instance().addExternalSocket(socket_fd_, Dhcp4to6Ipc::handler);
    }
}

void Dhcp4to6Ipc::handler() {
    Dhcp4to6Ipc& ipc = Dhcp4to6Ipc::instance();

    // Reset received message in case we return from this method before the
    // received message pointer is updated.
    ipc.received_.reset();

    // Receive message from the IPC socket.
    Pkt6Ptr pkt = ipc.receive();
    if (!pkt) {
        return;
    }

    // Each message must contain option holding DHCPv4 message.
    OptionCollection msgs = pkt->getOptions(D6O_DHCPV4_MSG);
    if (msgs.empty()) {
        isc_throw(Dhcp4o6IpcError, "DHCPv4 message option not present in the"
                  " DHCPv4o6 message received by the DHCPv4 server");

    } else if (msgs.size() > 1) {
        isc_throw(Dhcp4o6IpcError, "expected exactly one DHCPv4 message within"
                  " DHCPv4 message option received by the DHCPv4 server");
    }

    OptionPtr msg = msgs.begin()->second;
    if (!msg) {
        isc_throw(Dhcp4o6IpcError, "null DHCPv4 message option in the"
                  " DHCPv4o6 message received by the DHCPv4 server");
    }

    // Record this message.
    ipc.received_.reset(new Pkt4o6(msg->getData(), pkt));
}

Pkt4o6Ptr& Dhcp4to6Ipc::getReceived() {
    return (received_);
}

};  // namespace dhcp

};  // namespace isc
