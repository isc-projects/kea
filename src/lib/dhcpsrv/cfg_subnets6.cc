// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/subnet_id.h>
#include <stats/stats_mgr.h>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

void
CfgSubnets6::add(const Subnet6Ptr& subnet) {
    /// @todo: Check that this new subnet does not cross boundaries of any
    /// other already defined subnet.
    if (isDuplicate(*subnet)) {
        isc_throw(isc::dhcp::DuplicateSubnetID, "ID of the new IPv6 subnet '"
                  << subnet->getID() << "' is already in use");
    }
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_ADD_SUBNET6)
              .arg(subnet->toText());
    subnets_.push_back(subnet);
}

Subnet6Ptr
CfgSubnets6::selectSubnet(const SubnetSelector& selector) const {
    Subnet6Ptr subnet;

    // If relay agent link address is set to zero it means that we're dealing
    // with a directly connected client.
    if (selector.first_relay_linkaddr_ == IOAddress("::")) {
        // If interface name is known try to match it with interface names
        // specified for configured subnets.
        if (!selector.iface_name_.empty()) {
            subnet = selectSubnet(selector.iface_name_,
                                  selector.client_classes_);
        }

        // If interface name didn't match, try the client's address.
        if (!subnet && selector.remote_address_ != IOAddress("::")) {
            subnet = selectSubnet(selector.remote_address_,
                                  selector.client_classes_);
        }

    // If relay agent link address is set, we're dealing with a relayed message.
    } else {

        // Find the subnet using the Interface Id option, if present.
        subnet = selectSubnet(selector.interface_id_, selector.client_classes_);

        // If Interface ID option could not be matched for any subnet, try
        // the relay agent link address.
        if (!subnet) {
            subnet = selectSubnet(selector.first_relay_linkaddr_,
                                  selector.client_classes_,
                                  true);
        }
    }

    // Return subnet found, or NULL if not found.
    return (subnet);
}

Subnet6Ptr
CfgSubnets6::selectSubnet(const asiolink::IOAddress& address,
                          const ClientClasses& client_classes,
                          const bool is_relay_address) const {

    // If the specified address is a relay address we first need to match
    // it with the relay addresses specified for all subnets.
    if (is_relay_address) {
        for (Subnet6Collection::const_iterator subnet = subnets_.begin();
             subnet != subnets_.end(); ++subnet) {

            // If the specified address matches the relay address, return this
            // subnet.
            if (is_relay_address &&
                ((*subnet)->getRelayInfo().addr_ == address) &&
                (*subnet)->clientSupported(client_classes)) {
                LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                          DHCPSRV_CFGMGR_SUBNET6_RELAY)
                    .arg((*subnet)->toText()).arg(address.toText());
                return (*subnet);
            }
        }
    }

    // No success so far. Check if the specified address is in range
    // with any subnet.
    for (Subnet6Collection::const_iterator subnet = subnets_.begin();
         subnet != subnets_.end(); ++subnet) {
        if ((*subnet)->inRange(address) &&
            (*subnet)->clientSupported(client_classes)) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_SUBNET6)
                      .arg((*subnet)->toText()).arg(address.toText());
            return (*subnet);
        }
    }

    // Nothing found.
    return (Subnet6Ptr());
}


Subnet6Ptr
CfgSubnets6::selectSubnet(const std::string& iface_name,
                          const ClientClasses& client_classes) const {

    // If empty interface specified, we can't select subnet by interface.
    if (!iface_name.empty()) {
        for (Subnet6Collection::const_iterator subnet = subnets_.begin();
             subnet != subnets_.end(); ++subnet) {

            // If interface name matches with the one specified for the subnet
            // and the client is not rejected based on the classification,
            // return the subnet.
            if ((iface_name == (*subnet)->getIface()) &&
                (*subnet)->clientSupported(client_classes)) {

                LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                          DHCPSRV_CFGMGR_SUBNET6_IFACE)
                    .arg((*subnet)->toText()).arg(iface_name);
                return (*subnet);
            }
        }
    }

    // No subnet found for this interface name.
    return (Subnet6Ptr());
}

Subnet6Ptr
CfgSubnets6::selectSubnet(const OptionPtr& interface_id,
                          const ClientClasses& client_classes) const {
    // We can only select subnet using an interface id, if the interface
    // id is known.
    if (interface_id) {
        for (Subnet6Collection::const_iterator subnet = subnets_.begin();
             subnet != subnets_.end(); ++subnet) {

            // If interface id matches for the subnet and the subnet is not
            // rejected based on the classification.
            if ((*subnet)->getInterfaceId() &&
                (*subnet)->getInterfaceId()->equals(interface_id) &&
                (*subnet)->clientSupported(client_classes)) {

                LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                      DHCPSRV_CFGMGR_SUBNET6_IFACE_ID)
                    .arg((*subnet)->toText());
                return (*subnet);
            }
        }
    }
    // No subnet found.
    return (Subnet6Ptr());
}

bool
CfgSubnets6::isDuplicate(const Subnet6& subnet) const {
    for (Subnet6Collection::const_iterator subnet_it = subnets_.begin();
         subnet_it != subnets_.end(); ++subnet_it) {
        if ((*subnet_it)->getID() == subnet.getID()) {
            return (true);
        }
    }
    return (false);
}

void
CfgSubnets6::removeStatistics() {
    using namespace isc::stats;

    // For each v6 subnet currently configured, remove the statistics.
    for (Subnet6Collection::const_iterator subnet6 = subnets_.begin();
         subnet6 != subnets_.end(); ++subnet6) {

        StatsMgr::instance().del(StatsMgr::generateName("subnet",
                                                        (*subnet6)->getID(),
                                                        "total-nas"));

        StatsMgr::instance().del(StatsMgr::generateName("subnet",
                                                        (*subnet6)->getID(),
                                                        "assigned-nas"));

        StatsMgr::instance().del(StatsMgr::generateName("subnet",
                                                        (*subnet6)->getID(),
                                                        "total-pds"));

        StatsMgr::instance().del(StatsMgr::generateName("subnet",
                                                        (*subnet6)->getID(),
                                                        "assigned-pds"));
    }
}

void
CfgSubnets6::updateStatistics() {
    using namespace isc::stats;

    for (Subnet6Collection::const_iterator subnet = subnets_.begin();
         subnet != subnets_.end(); ++subnet) {

        StatsMgr::instance().setValue(
            StatsMgr::generateName("subnet", (*subnet)->getID(), "total-nas"),
            static_cast<int64_t>((*subnet)->getPoolCapacity(Lease::TYPE_NA)));

        StatsMgr::instance().setValue(
            StatsMgr::generateName("subnet", (*subnet)->getID(), "total-pds"),
            static_cast<int64_t>((*subnet)->getPoolCapacity(Lease::TYPE_PD)));
    }
}

} // end of namespace isc::dhcp
} // end of namespace isc
