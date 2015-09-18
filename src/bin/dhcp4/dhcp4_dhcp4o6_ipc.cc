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
    if (port > 65534) {
        isc_throw(OutOfRange, "DHCP4o6 port " << port);
    }

    int old_fd = socket_fd_;
    socket_fd_ = Dhcp4o6IpcBase::open(static_cast<uint16_t>(port), 6);
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

    pkt->unpack();
    OptionCollection msgs = pkt->getOptions(D6O_DHCPV4_MSG);
    if (msgs.size() != 1) {
        return;
    }
    OptionPtr msg = pkt->getOption(D6O_DHCPV4_MSG);
    if (!msg) {
        isc_throw(Unexpected, "Can't get DHCPv4 message option");
    }
    instance().received_.reset(new Pkt4o6(msg->getData(), pkt));
}

Pkt4o6Ptr& Dhcp4o6Ipc::getReceived() {
    return (received_);
}

};  // namespace dhcp

};  // namespace isc
