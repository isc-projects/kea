// Copyright (C) 2014-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_custom.h>
#include <asiolink/addr_utilities.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet_id.h>
#include <stats/stats_mgr.h>
#include <boost/foreach.hpp>
#include <string.h>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::data;

namespace isc {
namespace dhcp {

void
CfgSubnets6::add(const Subnet6Ptr& subnet) {
    if (getBySubnetId(subnet->getID())) {
        isc_throw(isc::dhcp::DuplicateSubnetID, "ID of the new IPv6 subnet '"
                  << subnet->getID() << "' is already in use");

    } else if (getByPrefix(subnet->toText())) {
        /// @todo: Check that this new subnet does not cross boundaries of any
        /// other already defined subnet.
        isc_throw(isc::dhcp::DuplicateSubnetID, "subnet with the prefix of '"
                  << subnet->toText() << "' already exists");
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_ADD_SUBNET6)
              .arg(subnet->toText());
    subnets_.push_back(subnet);
}

void
CfgSubnets6::del(const ConstSubnet6Ptr& subnet) {
    auto& index = subnets_.get<SubnetSubnetIdIndexTag>();
    auto subnet_it = index.find(subnet->getID());
    if (subnet_it == index.end()) {
        isc_throw(BadValue, "no subnet with ID of '" << subnet->getID()
                  << "' found");
    }
    index.erase(subnet_it);

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_DEL_SUBNET6)
        .arg(subnet->toText());
}

ConstSubnet6Ptr
CfgSubnets6::getBySubnetId(const SubnetID& subnet_id) const {
    const auto& index = subnets_.get<SubnetSubnetIdIndexTag>();
    auto subnet_it = index.find(subnet_id);
    return ((subnet_it != index.cend()) ? (*subnet_it) : ConstSubnet6Ptr());
}

ConstSubnet6Ptr
CfgSubnets6::getByPrefix(const std::string& subnet_text) const {
    const auto& index = subnets_.get<SubnetPrefixIndexTag>();
    auto subnet_it = index.find(subnet_text);
    return ((subnet_it != index.cend()) ? (*subnet_it) : ConstSubnet6Ptr());
}

SubnetSelector
CfgSubnets6::initSelector(const Pkt6Ptr& query) {
    // Initialize subnet selector with the values used to select the subnet.
    SubnetSelector selector;
    selector.iface_name_ = query->getIface();
    selector.remote_address_ = query->getRemoteAddr();
    selector.first_relay_linkaddr_ = IOAddress("::");
    selector.client_classes_ = query->classes_;

    // Initialize fields specific to relayed messages.
    if (!query->relay_info_.empty()) {
        BOOST_REVERSE_FOREACH(Pkt6::RelayInfo relay, query->relay_info_) {
            if (!relay.linkaddr_.isV6Zero() &&
                !relay.linkaddr_.isV6LinkLocal()) {
                selector.first_relay_linkaddr_ = relay.linkaddr_;
                break;
            }
        }
        selector.interface_id_ =
            query->getAnyRelayOption(D6O_INTERFACE_ID,
                                     Pkt6::RELAY_GET_FIRST);
    }

    return (selector);
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

            // If the specified address matches a relay address, return this
            // subnet.
            if (is_relay_address &&
                ((*subnet)->hasRelayAddress(address)) &&
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

Subnet6Ptr
CfgSubnets6::getSubnet(const SubnetID id) const {

    /// @todo: Once this code is migrated to multi-index container, use
    /// an index rather than full scan.
    for (auto subnet = subnets_.begin(); subnet != subnets_.end(); ++subnet) {
        if ((*subnet)->getID() == id) {
            return (*subnet);
        }
    }
    return (Subnet6Ptr());
}

void
CfgSubnets6::removeStatistics() {
    using namespace isc::stats;

    StatsMgr& stats_mgr = StatsMgr::instance();
    // For each v6 subnet currently configured, remove the statistics.
    for (Subnet6Collection::const_iterator subnet6 = subnets_.begin();
         subnet6 != subnets_.end(); ++subnet6) {
        SubnetID subnet_id = (*subnet6)->getID();
        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id, "total-nas"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "assigned-nas"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id, "total-pds"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "assigned-pds"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "declined-addresses"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "declined-reclaimed-addresses"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "reclaimed-leases"));
    }
}

void
CfgSubnets6::updateStatistics() {
    using namespace isc::stats;

    StatsMgr& stats_mgr = StatsMgr::instance();
    // For each v6 subnet currently configured, calculate totals
    for (Subnet6Collection::const_iterator subnet6 = subnets_.begin();
         subnet6 != subnets_.end(); ++subnet6) {
        SubnetID subnet_id = (*subnet6)->getID();

        stats_mgr.setValue(StatsMgr::generateName("subnet", subnet_id,
                                                  "total-nas"),
                           static_cast<int64_t>
                           ((*subnet6)->getPoolCapacity(Lease::TYPE_NA)));

        stats_mgr.setValue(StatsMgr::generateName("subnet", subnet_id,
                                                  "total-pds"),
                            static_cast<int64_t>
                            ((*subnet6)->getPoolCapacity(Lease::TYPE_PD)));
    }

    // Only recount the stats if we have subnets.
    if (subnets_.begin() != subnets_.end()) {
            LeaseMgrFactory::instance().recountLeaseStats6();
    }
}

ElementPtr
CfgSubnets6::toElement() const {
    ElementPtr result = Element::createList();
    // Iterate subnets
    for (Subnet6Collection::const_iterator subnet = subnets_.cbegin();
         subnet != subnets_.cend(); ++subnet) {
        result->add((*subnet)->toElement());
    }
    return (result);
}

} // end of namespace isc::dhcp
} // end of namespace isc
