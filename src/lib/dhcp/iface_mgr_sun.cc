// Copyright (C) 2011-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#if defined(OS_SUN)

#include <dhcp/iface_mgr.h>
#include <dhcp/iface_mgr_error_handler.h>
#include <dhcp/pkt_filter_inet.h>
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

namespace {

static const uint8_t default_ib_bcast_addr[20] = {
       0x00, 0xff, 0xff, 0xff,
       0xff, 0x12, 0x40, 0x1b,
       0x00, 0x00, 0x00, 0x00,
       0x00, 0x00, 0x00, 0x00,
       0xff, 0xff, 0xff, 0xff
};

static const uint8_t default_ether_bcast_addr[6] = {
       0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

}

namespace isc {
namespace dhcp {

/// This is a Solaris specific interface detection code. It works on Solaris 11
/// only, as earlier versions did not support getifaddrs() API.
void
IfaceMgr::detectIfaces(bool update_only) {
    if (detect_callback_) {
        if (!detect_callback_(update_only)) {
            return;
        }
    }

    struct ifaddrs* iflist = 0;// The whole interface list
    struct ifaddrs* ifptr = 0; // The interface we're processing now

    // Gets list of ifaddrs struct
    if (getifaddrs(&iflist) != 0) {
        isc_throw(Unexpected, "Network interfaces detection failed.");
    }

    typedef map<string, IfacePtr> IfaceLst;
    IfaceLst::iterator iface_iter;
    IfaceLst ifaces;

    // First lookup for getting interfaces ...
    for (ifptr = iflist; ifptr != 0; ifptr = ifptr->ifa_next) {
        const char * ifname = ifptr->ifa_name;
        uint ifindex = 0;

        if (!(ifindex = if_nametoindex(ifname))) {
            // Interface name does not have corresponding index ...
            freeifaddrs(iflist);
            isc_throw(Unexpected, "Interface " << ifname << " has no index");
        }

        iface_iter = ifaces.find(ifname);
        if (iface_iter != ifaces.end()) {
            continue;
        }

        IfacePtr iface;
        if (update_only) {
            iface = getIface(ifname);
        }
        if (!iface) {
            iface.reset(new Iface(ifname, ifindex));
        }
        iface->setFlags(ifptr->ifa_flags);
        ifaces.insert(pair<string, IfacePtr>(ifname, iface));
    }

    // Second lookup to get MAC and IP addresses
    for (ifptr = iflist; ifptr != 0; ifptr = ifptr->ifa_next) {
        iface_iter = ifaces.find(ifptr->ifa_name);
        if (iface_iter == ifaces.end()) {
            continue;
        }
        // Common byte pointer for following data
        const uint8_t * ptr = 0;
        if (ifptr->ifa_addr->sa_family == AF_LINK) {
            // HWAddr
            struct sockaddr_dl * ldata =
                reinterpret_cast<struct sockaddr_dl *>(ifptr->ifa_addr);
            ptr = reinterpret_cast<uint8_t *>(LLADDR(ldata));

            iface_iter->second->setHWType(ldata->sdl_type);
            iface_iter->second->setMac(ptr, ldata->sdl_alen);

            //TODO: I don't have SUN, this needs tested
            if (ifptr->ifa_flags & IFF_BROADCAST) {
                ldata = reinterpret_cast<struct sockaddr_dl *>(ifptr->ifa_broadaddr);
                ptr = reinterpret_cast<uint8_t *>(LLADDR(ldata));

                iface_iter->second->setBcastMac(ptr, ldata->sdl_alen);
            } else if (ldata->sdl_type == HTYPE_INFINIBAND) {
                iface_iter->second->setBcastMac(default_ib_bcast_addr, sizeof(default_ib_bcast_addr));
            } else if (ldata->sdl_type == HTYPE_ETHER) {
                iface_iter->second->setBcastMac(default_ether_bcast_addr, sizeof(default_ether_bcast_addr));
            }
        } else if (ifptr->ifa_addr->sa_family == AF_INET6) {
            // IPv6 Addr
            struct sockaddr_in6 * adata =
                reinterpret_cast<struct sockaddr_in6 *>(ifptr->ifa_addr);
            ptr = reinterpret_cast<uint8_t *>(&adata->sin6_addr);

            IOAddress a = IOAddress::fromBytes(AF_INET6, ptr);
            iface_iter->second->addAddress(a);
        } else {
            // IPv4 Addr
            struct sockaddr_in * adata =
                reinterpret_cast<struct sockaddr_in *>(ifptr->ifa_addr);
            ptr = reinterpret_cast<uint8_t *>(&adata->sin_addr);

            IOAddress a = IOAddress::fromBytes(AF_INET, ptr);
            iface_iter->second->addAddress(a);
        }
    }

    freeifaddrs(iflist);

    // Interfaces registering
    for (auto const& iface_it : ifaces) {
        IfacePtr iface;
        if (update_only) {
            iface = getIface(iface_it.first);
        }
        if (!iface) {
            addInterface(iface_it.second);
        }
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

void
IfaceMgr::setMatchingPacketFilter(const bool /* direct_response_desired */) {
    // @todo Currently we ignore the preference to use direct traffic
    // because it hasn't been implemented for Solaris.
    setPacketFilter(PktFilterPtr(new PktFilterInet()));
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
        IFACEMGR_ERROR(SocketConfigError, error_handler, IfacePtr(),
                       "Failed to open link-local socket on "
                       "interface " << iface.getName() << ": "
                       << ex.what());
        return (false);

    }
    return (true);
}

int
IfaceMgr::openSocket6(Iface& iface, const IOAddress& addr, uint16_t port,
                      const bool join_multicast) {
    // On Solaris, we bind the socket to in6addr_any and join multicast group
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
