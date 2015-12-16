// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/pkt_filter6.h>

namespace isc {
namespace dhcp {

bool
PktFilter6::joinMulticast(int sock, const std::string& ifname,
                          const std::string & mcast) {

    struct ipv6_mreq mreq;
    memset(&mreq, 0, sizeof(ipv6_mreq));

    // Convert the multicast address to a binary form.
    if (inet_pton(AF_INET6, mcast.c_str(), &mreq.ipv6mr_multiaddr) <= 0) {
        return (false);
    }
    // Set the interface being used.
    mreq.ipv6mr_interface = if_nametoindex(ifname.c_str());
    // Join the multicast group.
    if (setsockopt(sock, IPPROTO_IPV6, IPV6_JOIN_GROUP,
                   &mreq, sizeof(mreq)) < 0) {
        return (false);
    }

    return (true);
}


} // end of isc::dhcp namespace
} // end of isc namespace
