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
#include <boost/pointer_cast.hpp>
#include <errno.h>
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

int Dhcp4o6IpcBase::open(const uint16_t port, const int side) {
    if (port == port_) {
        // No change: nothing to do
        return (socket_fd_);
    }

    // Open socket
    int sock = socket(PF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        isc_throw(Dhcp4o6IpcError, "Failed to create DHCP4o6 socket.");
    }

    // Set reuse address
    int flag = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, static_cast<const void*>(&flag),
                   sizeof(flag)) < 0) {
        ::close(sock);
        isc_throw(Dhcp4o6IpcError, "Failed to set SO_REUSEADDR on DHCP4o6 socket.");
    }

    // Set no blocking
    if (fcntl(sock, F_SETFL, O_NONBLOCK) < 0) {
        ::close(sock);
        isc_throw(Dhcp4o6IpcError, "Failed to set O_NONBLOCK on DHCP4o6 socket.");
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
        isc_throw(Dhcp4o6IpcError, "Failed to bind DHCP4o6 socket.");
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
    if (connect(sock, reinterpret_cast<const struct sockaddr*>(&remote6),
                sizeof(remote6)) < 0) {
        ::close(sock);
        isc_throw(Dhcp4o6IpcError, "Failed to connect DHCP4o6 socket.");
    }

    if (socket_fd_ != -1) {
        if (dup2(sock, socket_fd_) == -1) {
            ::close(sock);
            isc_throw(Dhcp4o6IpcError, "Failed to duplicate DHCP4o6 socket.");
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
    port_ = 0;
    if (socket_fd_ != -1) {
        IfaceMgr::instance().deleteExternalSocket(socket_fd_);
        ::close(socket_fd_);
        socket_fd_ = -1;
    }
}

Pkt6Ptr Dhcp4o6IpcBase::receive() {
    uint8_t buf[65536];
    ssize_t cc = recv(socket_fd_, buf, sizeof(buf), 0);
    if (cc < 0) {
        isc_throw(Dhcp4o6IpcError, "Failed to receive on DHCP4o6 socket.");
    }
    Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(buf, cc));
    pkt->updateTimestamp();

    // Get interface name and remote address
    pkt->unpack();

    // Vendor option is initially NULL. If we find the instance of the vendor
    // option with the ISC enterprise id this pointer will point to it.
    OptionVendorPtr option_vendor;

    // Get all vendor option and look for the one with the ISC enterprise id.
    OptionCollection vendor_options = pkt->getOptions(D6O_VENDOR_OPTS);
    for (OptionCollection::const_iterator opt = vendor_options.begin();
         opt != vendor_options.end(); ++opt) {
        option_vendor = boost::dynamic_pointer_cast<OptionVendor>(opt->second);
        if (option_vendor) {
            if (option_vendor->getVendorId() == ENTERPRISE_ID_ISC) {
                break;
            }

        } else {
            option_vendor.reset();
        }
    }
         
    // Vendor option must exist.
    if (!option_vendor) {
        isc_throw(Dhcp4o6IpcError, "option " << D6O_VENDOR_OPTS
                  << " with ISC enterprise id is not present in the DHCP4o6"
                  " message sent between the servers");
    }

    // The option carrying interface name is required.
    OptionStringPtr ifname = boost::dynamic_pointer_cast<
        OptionString>(option_vendor->getOption(ISC_V6_4O6_INTERFACE));
    if (!ifname) {
        isc_throw(Dhcp4o6IpcError, "option " << D6O_VENDOR_OPTS
                  << " doesn't contain the " << ISC_V6_4O6_INTERFACE
                  << " option required in the DHCP4o6 message sent"
                  " between Kea servers");
    }

    // Check if this interface is present in the system.
    IfacePtr iface = IfaceMgr::instance().getIface(ifname->getValue());
    if (!iface) {
        isc_throw(Dhcp4o6IpcError, "option " << ISC_V6_4O6_INTERFACE
                  << " sent in the DHCP4o6 message contains non-existing"
                  " interface name '" << ifname->getValue() << "'");
    }

    // Get the option holding source IPv6 address.
    OptionCustomPtr srcs = boost::dynamic_pointer_cast<
        OptionCustom>(option_vendor->getOption(ISC_V6_4O6_SRC_ADDRESS));
    if (!srcs) {
        isc_throw(Dhcp4o6IpcError, "option " << D6O_VENDOR_OPTS
                  << " doesn't contain the " << ISC_V6_4O6_SRC_ADDRESS
                  << " option required in the DHCP4o6 message sent"
                  " between Kea servers");
    }

    // Update the packet.
    pkt->setRemoteAddr(srcs->readAddress());
    pkt->setIface(iface->getName());
    pkt->setIndex(iface->getIndex());

    // Remove options that have been added by the IPC sender.
    static_cast<void>(option_vendor->delOption(ISC_V6_4O6_INTERFACE));
    static_cast<void>(option_vendor->delOption(ISC_V6_4O6_SRC_ADDRESS));

    // If there are no more options, the IPC sender has probably created the
    // vendor option, in which case we should remove it here.
    if (option_vendor->getOptions().empty()) {
        static_cast<void>(pkt->delOption(D6O_VENDOR_OPTS));
    }

    return (pkt);
}

void Dhcp4o6IpcBase::send(const Pkt6Ptr& pkt) {
    // This shouldn't happen, i.e. send() shouldn't be called if there is
    // no message.
    if (!pkt) {
        isc_throw(Dhcp4o6IpcError, "DHCP4o6 message must not be NULL while"
                  " trying to send it over the IPC");
    }

    // Disabled: nowhere to send
    if (socket_fd_ == -1) {
        isc_throw(Dhcp4o6IpcError, "unable to send DHCP4o6 message because"
                  " IPC socket is closed");
    }

    // Check if vendor option exists.
    OptionVendorPtr option_vendor = dynamic_pointer_cast<
        OptionVendor>(pkt->getOption(D6O_VENDOR_OPTS));

    // If vendor option doesn't exist or its enterprise id is not ISC's
    // enterprise id, let's create it.
    if (!option_vendor || (option_vendor->getVendorId() != ENTERPRISE_ID_ISC)) {
        option_vendor.reset(new OptionVendor(Option::V6, ENTERPRISE_ID_ISC));
        pkt->addOption(option_vendor);

    }

    // Push interface name and source address in it
    option_vendor->addOption(OptionStringPtr(new OptionString(Option::V6,
                                                       ISC_V6_4O6_INTERFACE,
                                                       pkt->getIface())));
    option_vendor->addOption(Option6AddrLstPtr(new Option6AddrLst(ISC_V6_4O6_SRC_ADDRESS,
                                                                  pkt->getRemoteAddr())));
    // Get packet content
    OutputBuffer& buf = pkt->getBuffer();
    buf.clear();
    pkt->pack();

    // Try to send the message.
   if (::send(socket_fd_, buf.getData(), buf.getLength(), 0) < 0) {
       isc_throw(Dhcp4o6IpcError, "failed to send DHCP4o6 message over the IPC: "
                 << strerror(errno));
   }

}

};  // namespace dhcp

};  // namespace isc
