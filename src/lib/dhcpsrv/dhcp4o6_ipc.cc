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

#include <dhcp/dhcp6.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcpsrv/dhcp4o6_ipc.h>

#include <netinet/in.h>
#include <string>

using namespace isc::asiolink;
using namespace isc::util;
using namespace std;

namespace isc {
namespace dhcp {

Dhcp4o6IpcBase::Dhcp4o6IpcBase() : port_(0), socket_fd_(-1) {}

Dhcp4o6IpcBase::~Dhcp4o6IpcBase() {
    close();
}

int Dhcp4o6IpcBase::open(uint16_t port, int side) {
    if (port == port_) {
        // No change: nothing to do
        return (socket_fd_);
    }

    // Port 0: closing
    if (port == 0) {
        port_ = 0;
        if (socket_fd_ != -1) {
            IfaceMgr::instance().deleteExternalSocket(socket_fd_);
            ::close(socket_fd_);
            socket_fd_ = -1;
        }
        return (socket_fd_);
    }

    // Open socket
    int sock = socket(PF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        isc_throw(Unexpected, "Failed to create DHCP4o6 socket.");
    }

    // Set reuse address
    int flag = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
                   (char *)&flag, sizeof(flag)) < 0) {
        ::close(sock);
        isc_throw(Unexpected, "Failed to set SO_REUSEADDR on DHCP4o6 socket.");
    }

    // Set no blocking
    if (fcntl(sock, F_SETFL, O_NONBLOCK) < 0) {
        ::close(sock);
        isc_throw(Unexpected, "Failed to set O_NONBLOCK on DHCP4o6 socket.");
    }

    // Bind to the local address
    struct sockaddr_in6 local6;
    memset(&local6, 0, sizeof(local6));
    local6.sin6_family = AF_INET6;
#ifdef HAVE_SA_LEN
    local6.sin6_len = sizeof(local6);
#endif
    if (side == 6) {
        local6.sin6_port = htons(port);
    } else {
        local6.sin6_port = htons(port + 1);
    }
    if (bind(sock, (struct sockaddr *)&local6, sizeof(local6)) < 0) {
        ::close(sock);
        isc_throw(Unexpected, "Failed to bind DHCP4o6 socket.");
    }

    // Connect to the remote address
    struct sockaddr_in6 remote6;
    memset(&remote6, 0, sizeof(remote6));
    remote6.sin6_family = AF_INET6;
#ifdef HAVE_SA_LEN
    remote6.sin6_len = sizeof(remote6);
#endif
    if (side == 6) {
        remote6.sin6_port = htons(port + 1);
    } else {
        remote6.sin6_port = htons(port);
    }
    if (connect(sock, (struct sockaddr *)&remote6, sizeof(remote6)) < 0) {
        ::close(sock);
        isc_throw(Unexpected, "Failed to connect DHCP4o6 socket.");
    }

    if (socket_fd_ != -1) {
        if (dup2(sock, socket_fd_) == -1) {
            ::close(sock);
            isc_throw(Unexpected, "Failed to duplicate DHCP4o6 socket.");
        }
        if (sock != socket_fd_) {
            ::close(sock);
            sock = socket_fd_;
        }
    }

    // Success
    port_ = port;
    socket_fd_ = sock;
    return (socket_fd_);
}

void Dhcp4o6IpcBase::close() {
    static_cast<void>(open(0, 0));
}

Pkt6Ptr Dhcp4o6IpcBase::receive() {
    uint8_t buf[65536];
    ssize_t cc = recv(socket_fd_, buf, sizeof(buf), 0);
    if (cc < 0) {
        isc_throw(Unexpected, "Failed to receive on DHCP4o6 socket.");
    }
    Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(buf, cc));
    pkt->updateTimestamp();

    // Get interface name and remote address
    pkt->unpack();

    OptionVendorPtr vendor =
        boost::dynamic_pointer_cast<OptionVendor>(pkt->getOption(D6O_VENDOR_OPTS));
    if (!vendor || vendor->getVendorId() != ENTERPRISE_ID_ISC) {
        return (Pkt6Ptr());
    }
    OptionStringPtr ifname =
        boost::dynamic_pointer_cast<OptionString>(vendor->getOption(ISC_V6_4O6_INTERFACE));
    if (!ifname) {
        return (Pkt6Ptr());
    }
    IfacePtr iface = IfaceMgr::instance().getIface(ifname->getValue());
    if (!iface) {
        return (Pkt6Ptr());
    }
    OptionCustomPtr srcs =
        boost::dynamic_pointer_cast<OptionCustom>(vendor->getOption(ISC_V6_4O6_SRC_ADDRESS));
    if (!srcs) {
        return (Pkt6Ptr());
    }

    // Update the packet and return it
    static_cast<void>(pkt->delOption(D6O_VENDOR_OPTS));
    pkt->setRemoteAddr(srcs->readAddress());
    pkt->setIface(iface->getName());
    pkt->setIndex(iface->getIndex());
    return (pkt);
}

void Dhcp4o6IpcBase::send(Pkt6Ptr pkt) {
    // No packet: nothing to send
    if (!pkt) {
        return;
    }

    // Disabled: nowhere to send
    if (socket_fd_ == -1) {
        return;
    }

    // Get a vendor option
    OptionVendorPtr vendor(new OptionVendor(Option::V6, ENTERPRISE_ID_ISC));

    // Push interface name and source address in it
    vendor->addOption(OptionPtr(new OptionString(Option::V6,
                                                 ISC_V6_4O6_INTERFACE,
                                                 pkt->getIface())));
    vendor->addOption(OptionPtr(new Option6AddrLst(ISC_V6_4O6_SRC_ADDRESS,
                                                   pkt->getRemoteAddr())));
    pkt->addOption(vendor);

    // Get packet content
    OutputBuffer& buf = pkt->getBuffer();
    buf.clear();
    pkt->pack();

    // Send
    static_cast<void>(::send(socket_fd_, buf.getData(), buf.getLength(), 0));
    return;
}

};  // namespace dhcp

};  // namespace isc
