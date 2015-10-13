// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/subnet_id.h>
#include <stats/stats_mgr.h>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

void
CfgSubnets4::add(const Subnet4Ptr& subnet) {
    /// @todo: Check that this new subnet does not cross boundaries of any
    /// other already defined subnet.
    if (isDuplicate(*subnet)) {
        isc_throw(isc::dhcp::DuplicateSubnetID, "ID of the new IPv4 subnet '"
                  << subnet->getID() << "' is already in use");
    }
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_ADD_SUBNET4)
              .arg(subnet->toText());
    subnets_.push_back(subnet);
}

Subnet4Ptr
CfgSubnets4::selectSubnet(const SubnetSelector& selector) const {
    // First use RAI link select sub-option or subnet select option
    if (!selector.option_select_.isV4Zero()) {
        return (selectSubnet(selector.option_select_,
                             selector.client_classes_));
    }

    // If relayed message has been received, try to match the giaddr with the
    // relay address specified for a subnet. It is also possible that the relay
    // address will not match with any of the relay addresses accross all
    // subnets, but we need to verify that for all subnets before we can try
    // to use the giaddr to match with the subnet prefix.
    if (!selector.giaddr_.isV4Zero()) {
        for (Subnet4Collection::const_iterator subnet = subnets_.begin();
             subnet != subnets_.end(); ++subnet) {

            // Check if the giaddr is equal to the one defined for the subnet.
            if (selector.giaddr_ != (*subnet)->getRelayInfo().addr_) {
                continue;
            }

            // Eliminate those subnets that do not meet client class criteria.
            if ((*subnet)->clientSupported(selector.client_classes_)) {
                return (*subnet);
            }
        }
    }

    // If we got to this point it means that we were not able to match the
    // giaddr with any of the addresses specified for subnets. Let's determine
    // what address from the client's packet to use to match with the
    // subnets' prefixes.

    IOAddress address = IOAddress::IPV4_ZERO_ADDRESS();
    // If there is a giaddr, use it for subnet selection.
    if (!selector.giaddr_.isV4Zero()) {
        address = selector.giaddr_;

    // If it is a Renew or Rebind, use the ciaddr.
    } else if (!selector.ciaddr_.isV4Zero() &&
               !selector.local_address_.isV4Bcast()) {
        address = selector.ciaddr_;

    // If ciaddr is not specified, use the source address.
    } else if (!selector.remote_address_.isV4Zero() &&
               !selector.local_address_.isV4Bcast()) {
        address = selector.remote_address_;

    // If local interface name is known, use the local address on this
    // interface.
    } else if (!selector.iface_name_.empty()) {
        IfacePtr iface = IfaceMgr::instance().getIface(selector.iface_name_);
        // This should never happen in the real life. Hence we throw an
        // exception.
        if (iface == NULL) {
            isc_throw(isc::BadValue, "interface " << selector.iface_name_
                      << " doesn't exist and therefore it is impossible"
                      " to find a suitable subnet for its IPv4 address");
        }
        iface->getAddress4(address);
    }

    // Unable to find a suitable address to use for subnet selection.
    if (address.isV4Zero()) {
        return (Subnet4Ptr());
    }

    // We have identified an address in the client's packet that can be
    // used for subnet selection. Match this packet with the subnets.
    return (selectSubnet(address, selector.client_classes_));
}

Subnet4Ptr
CfgSubnets4::selectSubnet(const IOAddress& address,
                 const ClientClasses& client_classes) const {
    for (Subnet4Collection::const_iterator subnet = subnets_.begin();
         subnet != subnets_.end(); ++subnet) {

        // Address is in range for the subnet prefix, so return it.
        if (!(*subnet)->inRange(address)) {
            continue;
        }

        // Eliminate those subnets that do not meet client class criteria.
        if ((*subnet)->clientSupported(client_classes)) {
            return (*subnet);
        }
    }

    // Failed to find a subnet.
    return (Subnet4Ptr());
}

bool
CfgSubnets4::isDuplicate(const Subnet4& subnet) const {
    for (Subnet4Collection::const_iterator subnet_it = subnets_.begin();
         subnet_it != subnets_.end(); ++subnet_it) {
        if ((*subnet_it)->getID() == subnet.getID()) {
            return (true);
        }
    }
    return (false);
}

void
CfgSubnets4::removeStatistics() {
    using namespace isc::stats;

    // For each v4 subnet currently configured, remove the statistic.
    /// @todo: May move this to CfgSubnets4 class if there will be more
    /// statistics here.
    for (Subnet4Collection::const_iterator subnet4 = subnets_.begin();
         subnet4 != subnets_.end(); ++subnet4) {

        StatsMgr::instance().del(StatsMgr::generateName("subnet",
                                                        (*subnet4)->getID(),
                                                        "total-addresses"));

        StatsMgr::instance().del(StatsMgr::generateName("subnet",
                                                        (*subnet4)->getID(),
                                                        "assigned-addresses"));
    }
}

void
CfgSubnets4::updateStatistics() {
    using namespace isc::stats;

    /// @todo: May move this to CfgSubnets4 class if there will be more
    /// statistics here.
    for (Subnet4Collection::const_iterator subnet = subnets_.begin();
         subnet != subnets_.end(); ++subnet) {

        StatsMgr::instance().setValue(
            StatsMgr::generateName("subnet", (*subnet)->getID(), "total-addresses"),
            static_cast<int64_t>((*subnet)->getPoolCapacity(Lease::TYPE_V4)));
    }
}

} // end of namespace isc::dhcp
} // end of namespace isc
