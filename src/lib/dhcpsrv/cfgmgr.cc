// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_address.h>
#include <dhcpsrv/cfgmgr.h>

using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace dhcp {

CfgMgr&
CfgMgr::instance() {
    static CfgMgr cfg_mgr;
    return (cfg_mgr);
}

void
CfgMgr::addOptionSpace4(const OptionSpacePtr& space) {
    if (!space) {
        isc_throw(InvalidOptionSpace,
                  "provided option space object is NULL.");
    }
    OptionSpaceCollection::iterator it = spaces4_.find(space->getName());
    if (it != spaces4_.end()) {
        isc_throw(InvalidOptionSpace, "option space " << space->getName()
                  << " already added.");
    }
    spaces4_.insert(std::pair<std::string,
                              OptionSpacePtr>(space->getName(), space));
}

void
CfgMgr::addOptionSpace6(const OptionSpacePtr& space) {
    if (!space) {
        isc_throw(InvalidOptionSpace,
                  "provided option space object is NULL.");
    }
    OptionSpaceCollection::iterator it = spaces6_.find(space->getName());
    if (it != spaces6_.end()) {
        isc_throw(InvalidOptionSpace, "option space " << space->getName()
                  << " already added.");
    }
    spaces6_.insert(std::pair<std::string,
                              OptionSpacePtr>(space->getName(), space));
}

Subnet6Ptr
CfgMgr::getSubnet6(const isc::asiolink::IOAddress& hint) {

    // If there's only one subnet configured, let's just use it
    // The idea is to keep small deployments easy. In a small network - one
    // router that also runs DHCPv6 server. Users specifies a single pool and
    // expects it to just work. Without this, the server would complain that it
    // doesn't have IP address on its interfaces that matches that
    // configuration. Such requirement makes sense in IPv4, but not in IPv6.
    // The server does not need to have a global address (using just link-local
    // is ok for DHCPv6 server) from the pool it serves.
    if ((subnets6_.size() == 1) && hint.getAddress().to_v6().is_link_local()) {
        return (subnets6_[0]);
    }

    // If there is more than one, we need to choose the proper one
    for (Subnet6Collection::iterator subnet = subnets6_.begin();
         subnet != subnets6_.end(); ++subnet) {
        if ((*subnet)->inRange(hint)) {
            return (*subnet);
        }
    }

    // sorry, we don't support that subnet
    return (Subnet6Ptr());
}

Subnet6Ptr CfgMgr::getSubnet6(OptionPtr /*interfaceId*/) {
    /// @todo: Implement get subnet6 by interface-id (for relayed traffic)
    isc_throw(NotImplemented, "Relayed DHCPv6 traffic is not supported yet.");
}

void CfgMgr::addSubnet6(const Subnet6Ptr& subnet) {
    /// @todo: Check that this new subnet does not cross boundaries of any
    /// other already defined subnet.
    subnets6_.push_back(subnet);
}

Subnet4Ptr
CfgMgr::getSubnet4(const isc::asiolink::IOAddress& hint) {

    // If there's only one subnet configured, let's just use it
    // The idea is to keep small deployments easy. In a small network - one
    // router that also runs DHCPv6 server. Users specifies a single pool and
    // expects it to just work. Without this, the server would complain that it
    // doesn't have IP address on its interfaces that matches that
    // configuration. Such requirement makes sense in IPv4, but not in IPv6.
    // The server does not need to have a global address (using just link-local
    // is ok for DHCPv6 server) from the pool it serves.
    if (subnets4_.size() == 1) {
        return (subnets4_[0]);
    }

    // If there is more than one, we need to choose the proper one
    for (Subnet4Collection::iterator subnet = subnets4_.begin();
         subnet != subnets4_.end(); ++subnet) {
        if ((*subnet)->inRange(hint)) {
            return (*subnet);
        }
    }

    // sorry, we don't support that subnet
    return (Subnet4Ptr());
}

void CfgMgr::addSubnet4(const Subnet4Ptr& subnet) {
    /// @todo: Check that this new subnet does not cross boundaries of any
    /// other already defined subnet.
    subnets4_.push_back(subnet);
}

void CfgMgr::deleteSubnets4() {
    subnets4_.clear();
}

void CfgMgr::deleteSubnets6() {
    subnets6_.clear();
}

CfgMgr::CfgMgr() {
}

CfgMgr::~CfgMgr() {
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
