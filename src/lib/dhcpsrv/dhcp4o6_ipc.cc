// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp6.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcpsrv/dhcp4o6_ipc.h>
#include <dhcpsrv/dhcpsrv_log.h>

#include <boost/pointer_cast.hpp>

#include <errno.h>
#include <netinet/in.h>
#include <fcntl.h>
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

int Dhcp4o6IpcBase::open(uint16_t port, EndpointType endpoint_type) {
    // Don't check if the value is greater than 65534 as it is done
    // by callers before they cast the value to 16 bits.

    if (port == port_) {
        // No change: nothing to do
        return (socket_fd_);
    }

    // Open socket
    int sock = socket(PF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        isc_throw(Dhcp4o6IpcError, "Failed to create DHCP4o6 socket.");
    }

    // Set no blocking
    if (fcntl(sock, F_SETFL, O_NONBLOCK) < 0) {
        ::close(sock);
        isc_throw(Dhcp4o6IpcError,
                  "Failed to set O_NONBLOCK on DHCP4o6 socket.");
    }

    // Bind to the local address
    struct sockaddr_in6 local6;
    memset(&local6, 0, sizeof(local6));
    local6.sin6_family = AF_INET6;
#ifdef HAVE_SA_LEN
    local6.sin6_len = sizeof(local6);
#endif
    if (endpoint_type == ENDPOINT_TYPE_V6) {
        local6.sin6_port = htons(port);
    } else {
        local6.sin6_port = htons(port + 1);
    }
    // We'll connect to the loopback address so bind to it too.
    local6.sin6_addr.s6_addr[15] = 1;
    if (::bind(sock, (struct sockaddr *)&local6, sizeof(local6)) < 0) {
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
    if (endpoint_type == ENDPOINT_TYPE_V6) {
        remote6.sin6_port = htons(port + 1);
    } else {
        remote6.sin6_port = htons(port);
    }
    // At least OpenBSD requires the remote address to not be left
    // unspecified, so we set it to the loopback address.
    remote6.sin6_addr.s6_addr[15] = 1;
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
            option_vendor.reset();
        }
    }

    // Vendor option must exist.
    if (!option_vendor) {
        LOG_WARN(dhcpsrv_logger, DHCPSRV_DHCP4O6_RECEIVED_BAD_PACKET)
            .arg("no ISC vendor option");
        isc_throw(Dhcp4o6IpcError, "malformed packet (no ISC vendor option)");
    }

    // The option carrying interface name is required.
    OptionStringPtr ifname = boost::dynamic_pointer_cast<
        OptionString>(option_vendor->getOption(ISC_V6_4O6_INTERFACE));
    if (!ifname) {
        LOG_WARN(dhcpsrv_logger, DHCPSRV_DHCP4O6_RECEIVED_BAD_PACKET)
            .arg("no interface suboption");
        isc_throw(Dhcp4o6IpcError,
                  "malformed packet (interface suboption missing "
                  "or has incorrect type)");
    }

    // Check if this interface is present in the system.
    IfacePtr iface = IfaceMgr::instance().getIface(ifname->getValue());
    if (!iface) {
        LOG_WARN(dhcpsrv_logger, DHCPSRV_DHCP4O6_RECEIVED_BAD_PACKET)
            .arg("can't get interface " + ifname->getValue());
        isc_throw(Dhcp4o6IpcError,
                  "malformed packet (unknown interface "
                  + ifname->getValue() + ")");
    }

    // Get the option holding source IPv6 address.
    OptionCustomPtr srcs = boost::dynamic_pointer_cast<
        OptionCustom>(option_vendor->getOption(ISC_V6_4O6_SRC_ADDRESS));
    if (!srcs) {
        LOG_WARN(dhcpsrv_logger, DHCPSRV_DHCP4O6_RECEIVED_BAD_PACKET)
            .arg("no source address suboption");
        isc_throw(Dhcp4o6IpcError,
                  "malformed packet (source address suboption missing "
                  "or has incorrect type)");
    }

    // Get the option holding source port.
    OptionUint16Ptr sport = boost::dynamic_pointer_cast<
        OptionUint16>(option_vendor->getOption(ISC_V6_4O6_SRC_PORT));
    if (!sport) {
        LOG_WARN(dhcpsrv_logger, DHCPSRV_DHCP4O6_RECEIVED_BAD_PACKET)
            .arg("no source port suboption");
        isc_throw(Dhcp4o6IpcError,
                  "malformed packet (source port suboption missing "
                  "or has incorrect type)");
    }

    // Update the packet.
    pkt->setRemoteAddr(srcs->readAddress());
    pkt->setRemotePort(sport->getValue());
    pkt->setIface(iface->getName());
    pkt->setIndex(iface->getIndex());

    // Remove options that have been added by the IPC sender.
    static_cast<void>(option_vendor->delOption(ISC_V6_4O6_INTERFACE));
    static_cast<void>(option_vendor->delOption(ISC_V6_4O6_SRC_ADDRESS));
    static_cast<void>(option_vendor->delOption(ISC_V6_4O6_SRC_PORT));

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
            option_vendor.reset();
        }
    }

    // If vendor option doesn't exist or its enterprise id is not ISC's
    // enterprise id, let's create it.
    if (!option_vendor) {
        option_vendor.reset(new OptionVendor(Option::V6, ENTERPRISE_ID_ISC));
        pkt->addOption(option_vendor);
    }

    // Push interface name and source address in it
    option_vendor->addOption(OptionStringPtr(new OptionString(Option::V6,
                                                              ISC_V6_4O6_INTERFACE,
                                                              pkt->getIface())));
    option_vendor->addOption(Option6AddrLstPtr(new Option6AddrLst(ISC_V6_4O6_SRC_ADDRESS,
                                                                  pkt->getRemoteAddr())));
    option_vendor->addOption(OptionUint16Ptr(new OptionUint16(Option::V6,
                                                              ISC_V6_4O6_SRC_PORT,
                                                              pkt->getRemotePort())));
    // Get packet content
    OutputBuffer& buf = pkt->getBuffer();
    buf.clear();
    pkt->pack();

    // Try to send the message.
   if (::send(socket_fd_, buf.getData(), buf.getLength(), 0) < 0) {
       isc_throw(Dhcp4o6IpcError,
                 "failed to send DHCP4o6 message over the IPC: "
                 << strerror(errno));
   }
}

}  // namespace dhcp
}  // namespace isc
