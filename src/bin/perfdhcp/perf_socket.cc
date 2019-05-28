// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include <perfdhcp/perf_socket.h>
#include <perfdhcp/command_options.h>

#include <dhcp/iface_mgr.h>
#include <asiolink/io_address.h>

#include <boost/foreach.hpp>


using namespace isc::dhcp;
using namespace isc::asiolink;

namespace isc {
namespace perfdhcp {

PerfSocket::PerfSocket(CommandOptions& options) {
    sockfd_ = openSocket(options);
    initSocketData();
}


int
PerfSocket::openSocket(CommandOptions& options) const {
    std::string localname = options.getLocalName();
    std::string servername = options.getServerName();
    uint16_t port = options.getLocalPort();
    int sock = 0;

    uint8_t family = (options.getIpVersion() == 6) ? AF_INET6 : AF_INET;
    IOAddress remoteaddr(servername);

    // Check for mismatch between IP option and server address
    if (family != remoteaddr.getFamily()) {
        isc_throw(InvalidParameter,
                  "Values for IP version: " <<
                  static_cast<unsigned int>(options.getIpVersion()) <<
                  " and server address: " << servername << " are mismatched.");
    }

    if (port == 0) {
        if (family == AF_INET6) {
            // need server port (547) because the server is acting as a relay agent
            port = DHCP6_CLIENT_PORT;
            // if acting as a relay agent change port.
            if (options.isUseRelayedV6()) {
              port = DHCP6_SERVER_PORT;
            }
        } else if (options.getIpVersion() == 4) {
            port = 67; /// @todo: find out why port 68 is wrong here.
        }
    }

    // Local name is specified along with '-l' option.
    // It may point to interface name or local address.
    if (!localname.empty()) {
        // CommandOptions should be already aware whether local name
        // is interface name or address because it uses IfaceMgr to
        // scan interfaces and get's their names.
        if (options.isInterface()) {
            sock = IfaceMgr::instance().openSocketFromIface(localname,
                                                            port,
                                                            family);
        } else {
            IOAddress localaddr(localname);
            sock = IfaceMgr::instance().openSocketFromAddress(localaddr,
                                                              port);
        }
    } else if (!servername.empty()) {
        // If only server name is given we will need to try to resolve
        // the local address to bind socket to based on remote address.
        sock = IfaceMgr::instance().openSocketFromRemoteAddress(remoteaddr,
                                                                port);
    }
    if (sock <= 0) {
        isc_throw(BadValue, "unable to open socket to communicate with "
                  "DHCP server");
    }

    // IfaceMgr does not set broadcast option on the socket. We rely
    // on CommandOptions object to find out if socket has to have
    // broadcast enabled.
    if ((options.getIpVersion() == 4) && options.isBroadcast()) {
        int broadcast_enable = 1;
        int ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST,
                             &broadcast_enable, sizeof(broadcast_enable));
        if (ret < 0) {
            isc_throw(InvalidOperation,
                      "unable to set broadcast option on the socket");
        }
    } else if (options.getIpVersion() == 6) {
        // If remote address is multicast we need to enable it on
        // the socket that has been created.
        if (remoteaddr.isV6Multicast()) {
            int hops = 1;
            int ret = setsockopt(sock, IPPROTO_IPV6, IPV6_MULTICAST_HOPS,
                                 &hops, sizeof(hops));
            // If user specified interface name with '-l' the
            // IPV6_MULTICAST_IF has to be set.
            if ((ret >= 0)  && options.isInterface()) {
                IfacePtr iface =
                    IfaceMgr::instance().getIface(options.getLocalName());
                if (iface == NULL) {
                    isc_throw(Unexpected, "unknown interface "
                              << options.getLocalName());
                }
                int idx = iface->getIndex();
                ret = setsockopt(sock, IPPROTO_IPV6, IPV6_MULTICAST_IF,
                                     &idx, sizeof(idx));
            }
            if (ret < 0) {
                isc_throw(InvalidOperation,
                          "unable to enable multicast on socket " <<  sock
                          << ". errno = " << errno);
            }
        }
    }

    return (sock);
}

PerfSocket::~PerfSocket() {
    IfacePtr iface = IfaceMgr::instance().getIface(ifindex_);
    if (iface) {
        iface->delSocket(sockfd_);
    }
}

void
PerfSocket::initSocketData() {
    BOOST_FOREACH(IfacePtr iface, IfaceMgr::instance().getIfaces()) {
        BOOST_FOREACH(SocketInfo s, iface->getSockets()) {
            if (s.sockfd_ == sockfd_) {
                ifindex_ = iface->getIndex();
                addr_ = s.addr_;
                return;
            }
        }
    }
    isc_throw(BadValue, "interface for specified socket descriptor not found");
}

Pkt4Ptr
PerfSocket::receive4(uint32_t timeout_sec, uint32_t timeout_usec) {
    Pkt4Ptr pkt = IfaceMgr::instance().receive4(timeout_sec, timeout_usec);
    if (pkt) {
        /// @todo: Add packet exception handling here. Right now any
        /// malformed packet will cause perfdhcp to abort.
        pkt->unpack();
    }
    return (pkt);
}

Pkt6Ptr
PerfSocket::receive6(uint32_t timeout_sec, uint32_t timeout_usec) {
    Pkt6Ptr pkt = IfaceMgr::instance().receive6(timeout_sec, timeout_usec);
    if (pkt) {
        /// @todo: Add packet exception handling here. Right now any
        /// malformed packet will cause perfdhcp to abort.
        pkt->unpack();
    }
    return (pkt);
}

bool
PerfSocket::send(const Pkt4Ptr& pkt) {
    return IfaceMgr::instance().send(pkt);
}

bool
PerfSocket::send(const Pkt6Ptr& pkt) {
    return IfaceMgr::instance().send(pkt);
}

IfacePtr
PerfSocket::getIface() {
    return (IfaceMgr::instance().getIface(ifindex_));
}

}
}
