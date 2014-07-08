// Copyright (C) 2011, 2013-2014 Internet Systems Consortium, Inc. ("ISC")
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

#if defined(OS_BSD)

#include <dhcp/iface_mgr.h>
#include <dhcp/iface_mgr_error_handler.h>
#include <dhcp/pkt_filter_bpf.h>
#include <exceptions/exceptions.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <net/if_dl.h>
#include <net/if.h>
#include <ifaddrs.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace isc {
namespace dhcp {

/// This is a BSD specific interface detection method.
void
IfaceMgr::detectIfaces() {
    struct ifaddrs* iflist = 0;// The whole interface list
    struct ifaddrs* ifptr = 0; // The interface we're processing now

    // Gets list of ifaddrs struct
    if(getifaddrs(&iflist) != 0) {
        isc_throw(Unexpected, "Network interfaces detection failed.");
    }

    typedef map<string, Iface> ifaceLst;
    ifaceLst::iterator iface_iter;
    ifaceLst ifaces;

    // First lookup for getting interfaces ...
    for (ifptr = iflist; ifptr != 0; ifptr = ifptr->ifa_next) {
        const char * ifname = ifptr->ifa_name;
        uint ifindex = 0;

        if (!(ifindex = if_nametoindex(ifname))) {
            // Interface name does not have corresponding index ...
            freeifaddrs(iflist);
            isc_throw(Unexpected, "Interface " << ifname << " has no index");
        }

        if ((iface_iter = ifaces.find(ifname)) != ifaces.end()) {
            continue;
        }

        Iface iface(ifname, ifindex);
        iface.setFlags(ifptr->ifa_flags);
        ifaces.insert(pair<string, Iface>(ifname, iface));
    }

    // Second lookup to get MAC and IP addresses
    for (ifptr = iflist; ifptr != 0; ifptr = ifptr->ifa_next) {
        if ((iface_iter = ifaces.find(ifptr->ifa_name)) == ifaces.end()) {
            continue;
        }
        // Common byte pointer for following data
        const uint8_t * ptr = 0;
        if(ifptr->ifa_addr->sa_family == AF_LINK) {
            // HWAddr
            struct sockaddr_dl * ldata =
                reinterpret_cast<struct sockaddr_dl *>(ifptr->ifa_addr);
            ptr = reinterpret_cast<uint8_t *>(LLADDR(ldata));

            iface_iter->second.setHWType(ldata->sdl_type);
            iface_iter->second.setMac(ptr, ldata->sdl_alen);
        } else if(ifptr->ifa_addr->sa_family == AF_INET6) {
            // IPv6 Addr
            struct sockaddr_in6 * adata =
                reinterpret_cast<struct sockaddr_in6 *>(ifptr->ifa_addr);
            ptr = reinterpret_cast<uint8_t *>(&adata->sin6_addr);

            IOAddress a = IOAddress::fromBytes(AF_INET6, ptr);
            iface_iter->second.addAddress(a);
        } else {
            // IPv4 Addr
            struct sockaddr_in * adata =
                reinterpret_cast<struct sockaddr_in *>(ifptr->ifa_addr);
            ptr = reinterpret_cast<uint8_t *>(&adata->sin_addr);

            IOAddress a = IOAddress::fromBytes(AF_INET, ptr);
            iface_iter->second.addAddress(a);
        }
    }

    freeifaddrs(iflist);

    // Interfaces registering
    for(ifaceLst::const_iterator iface_iter = ifaces.begin();
        iface_iter != ifaces.end(); ++iface_iter) {
        ifaces_.push_back(iface_iter->second);
    }
}

/// @brief sets flag_*_ fields
///
/// Like Linux version, os specific flags
///
/// @params flags
void Iface::setFlags(uint64_t flags) {
    flags_ = flags;

    flag_loopback_ = flags & IFF_LOOPBACK;
    flag_up_ = flags & IFF_UP;
    flag_running_ = flags & IFF_RUNNING;
    flag_multicast_ = flags & IFF_MULTICAST;
    flag_broadcast_ = flags & IFF_BROADCAST;
}

void IfaceMgr::os_send4(struct msghdr& /*m*/,
                        boost::scoped_array<char>& /*control_buf*/,
                        size_t /*control_buf_len*/,
                        const Pkt4Ptr& /*pkt*/) {
  // @todo: Are there any specific actions required before sending IPv4 packet
  // on BSDs? See iface_mgr_linux.cc for working Linux implementation.
}

bool IfaceMgr::os_receive4(struct msghdr& /*m*/, Pkt4Ptr& /*pkt*/) {
  // @todo: Are there any specific actions required before receiving IPv4 packet
  // on BSDs? See iface_mgr_linux.cc for working Linux implementation.

  return (true); // pretend that we have everything set up for reception.
}

void
IfaceMgr::setMatchingPacketFilter(const bool /* direct_response_desired */) {
    // Ignore whether the direct response is desired or not. Even if the
    // direct response is not desired we don't want to use PktFilterInet
    // because the BSD doesn't support binding to the device and listening
    // to broadcast traffic on individual interfaces. So, datagram socket
    // supported by PktFilterInet is not really usable for DHCP.
    setPacketFilter(PktFilterPtr(new PktFilterBPF()));
}

bool
IfaceMgr::openMulticastSocket(Iface& iface,
                              const isc::asiolink::IOAddress& addr,
                              const uint16_t port,
                              IfaceMgrErrorMsgCallback error_handler) {
    try {
        // This should open a socket, bind it to link-local address
        // and join multicast group.
        openSocket(iface.getName(), addr, port, iface.flag_multicast_);

    } catch (const Exception& ex) {
        IFACEMGR_ERROR(SocketConfigError, error_handler,
                       "Failed to open link-local socket on "
                       " interface " << iface.getName() << ": "
                       << ex.what());
        return (false);

    }
    return (true);
}

int
IfaceMgr::openSocket6(Iface& iface, const IOAddress& addr, uint16_t port,
                      const bool join_multicast) {
    // On BSD, we bind the socket to in6addr_any and join multicast group
    // to receive multicast traffic. So, if the multicast is requested,
    // replace the address specified by the caller with the "unspecified"
    // address.
    IOAddress actual_address = join_multicast ? IOAddress("::") : addr;
    SocketInfo info = packet_filter6_->openSocket(iface, actual_address, port,
                                                  join_multicast);
    iface.addSocket(info);
    return (info.sockfd_);
}


} // end of isc::dhcp namespace
} // end of dhcp namespace

#endif
