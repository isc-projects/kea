// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
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
    static_cast<void>(subnets_.insert(subnet));
}

Subnet6Ptr
CfgSubnets6::replace(const Subnet6Ptr& subnet) {
    // Get the subnet with the same ID.
    const SubnetID& subnet_id = subnet->getID();
    auto& index = subnets_.template get<SubnetSubnetIdIndexTag>();
    auto subnet_it = index.find(subnet_id);
    if (subnet_it == index.end()) {
        isc_throw(BadValue, "There is no IPv6 subnet with ID " << subnet_id);
    }
    Subnet6Ptr old = *subnet_it;
    bool ret = index.replace(subnet_it, subnet);

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_UPDATE_SUBNET6)
        .arg(subnet_id).arg(ret);
    if (ret) {
        return (old);
    } else {
        return (Subnet6Ptr());
    }
}

void
CfgSubnets6::del(const ConstSubnet6Ptr& subnet) {
    del(subnet->getID());
}

void
CfgSubnets6::del(const SubnetID& subnet_id) {
    auto& index = subnets_.get<SubnetSubnetIdIndexTag>();
    auto subnet_it = index.find(subnet_id);
    if (subnet_it == index.end()) {
        isc_throw(BadValue, "no subnet with ID of '" << subnet_id
                  << "' found");
    }

    Subnet6Ptr subnet = *subnet_it;

    index.erase(subnet_it);

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_DEL_SUBNET6)
        .arg(subnet->toText());
}

void
CfgSubnets6::merge(CfgOptionDefPtr cfg_def, CfgSharedNetworks6Ptr networks,
                   CfgSubnets6& other) {
    auto& index_id = subnets_.get<SubnetSubnetIdIndexTag>();
    auto& index_prefix = subnets_.get<SubnetPrefixIndexTag>();

    // Iterate over the subnets to be merged. They will replace the existing
    // subnets with the same id. All new subnets will be inserted into the
    // configuration into which we're merging.
    auto const& other_subnets = other.getAll();
    for (auto const& other_subnet : *other_subnets) {

        // Check if there is a subnet with the same ID.
        auto subnet_it = index_id.find(other_subnet->getID());
        if (subnet_it != index_id.end()) {

            // Subnet found.
            auto existing_subnet = *subnet_it;

            // If the existing subnet and other subnet
            // are the same instance skip it.
            if (existing_subnet == other_subnet) {
                continue;
            }

            // We're going to replace the existing subnet with the other
            // version. If it belongs to a shared network, we need
            // remove it from that network.
            SharedNetwork6Ptr network;
            existing_subnet->getSharedNetwork(network);
            if (network) {
                network->del(existing_subnet->getID());
            }

            // Now we remove the existing subnet.
            index_id.erase(subnet_it);
        }

        // Check if there is a subnet with the same prefix.
        auto subnet_prefix_it = index_prefix.find(other_subnet->toText());
        if (subnet_prefix_it != index_prefix.end()) {

            // Subnet found.
            auto existing_subnet = *subnet_prefix_it;

            // Updating the id can lead to problems... e.g. reservation
            // for the previous subnet ID.
            // @todo: check reservations

            // We're going to replace the existing subnet with the other
            // version. If it belongs to a shared network, we need
            // remove it from that network.
            SharedNetwork6Ptr network;
            existing_subnet->getSharedNetwork(network);
            if (network) {
                network->del(existing_subnet->getID());
            }

            // Now we remove the existing subnet.
            index_prefix.erase(subnet_prefix_it);
        }

        // Create the subnet's options based on the given definitions.
        other_subnet->getCfgOption()->createOptions(cfg_def);

        // Create the options for pool based on the given definitions.
        for (auto const& pool : other_subnet->getPoolsWritable(Lease::TYPE_NA)) {
            pool->getCfgOption()->createOptions(cfg_def);
        }

        // Create the options for pd pool based on the given definitions.
        for (auto const& pool : other_subnet->getPoolsWritable(Lease::TYPE_PD)) {
            pool->getCfgOption()->createOptions(cfg_def);
        }

        // Add the "other" subnet to the our collection of subnets.
        static_cast<void>(subnets_.insert(other_subnet));

        // If it belongs to a shared network, find the network and
        // add the subnet to it
        std::string network_name = other_subnet->getSharedNetworkName();
        if (!network_name.empty()) {
            SharedNetwork6Ptr network = networks->getByName(network_name);
            if (network) {
                network->add(other_subnet);
            } else {
                // This implies the shared-network collection we were given
                // is out of sync with the subnets we were given.
                isc_throw(InvalidOperation, "Cannot assign subnet ID of "
                          << other_subnet->getID()
                          << " to shared network: " << network_name
                          << ", network does not exist");
            }
        }
    }
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
        for (auto const& subnet : subnets_) {

            // If the specified address matches a relay address, return this
            // subnet.
            if (subnet->hasRelays()) {
                if (!subnet->hasRelayAddress(address)) {
                    continue;
                }

            } else {
                SharedNetwork6Ptr network;
                subnet->getSharedNetwork(network);
                if (!network || !network->hasRelayAddress(address)) {
                    continue;
                }
            }

            if (subnet->clientSupported(client_classes)) {
                // The relay address is matching the one specified for a subnet
                // or its shared network.
                LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                          DHCPSRV_CFGMGR_SUBNET6_RELAY)
                    .arg(subnet->toText()).arg(address.toText());
                return (subnet);
            }
        }
    }

    // No success so far. Check if the specified address is in range
    // with any subnet.
    for (auto const& subnet : subnets_) {
        if (subnet->inRange(address) && subnet->clientSupported(client_classes)) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_SUBNET6)
                      .arg(subnet->toText()).arg(address.toText());
            return (subnet);
        }
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
              DHCPSRV_SUBNET6_SELECT_BY_ADDRESS_NO_MATCH)
        .arg(address.toText());

    // Nothing found.
    return (Subnet6Ptr());
}

Subnet6Ptr
CfgSubnets6::selectSubnet(const std::string& iface_name,
                          const ClientClasses& client_classes) const {
    // If empty interface specified, we can't select subnet by interface.
    if (!iface_name.empty()) {
        for (auto const& subnet : subnets_) {

            // If interface name matches with the one specified for the subnet
            // and the client is not rejected based on the classification,
            // return the subnet.
            if ((subnet->getIface() == iface_name) &&
                subnet->clientSupported(client_classes)) {
                LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                          DHCPSRV_CFGMGR_SUBNET6_IFACE)
                    .arg(subnet->toText()).arg(iface_name);
                return (subnet);
            }
        }
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
              DHCPSRV_SUBNET6_SELECT_BY_INTERFACE_NO_MATCH)
        .arg(iface_name);

    // No subnet found for this interface name.
    return (Subnet6Ptr());
}

Subnet6Ptr
CfgSubnets6::selectSubnet(const OptionPtr& interface_id,
                          const ClientClasses& client_classes) const {
    // We can only select subnet using an interface id, if the interface
    // id is known.
    if (interface_id) {
        for (auto const& subnet : subnets_) {

            // If interface id matches for the subnet and the subnet is not
            // rejected based on the classification.
            if (subnet->getInterfaceId() &&
                subnet->getInterfaceId()->equals(interface_id) &&
                subnet->clientSupported(client_classes)) {

                LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                      DHCPSRV_CFGMGR_SUBNET6_IFACE_ID)
                    .arg(subnet->toText());
                return (subnet);
            }
        }

        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                  DHCPSRV_SUBNET6_SELECT_BY_INTERFACE_ID_NO_MATCH)
            .arg(interface_id->toText());
    }

    // No subnet found.
    return (Subnet6Ptr());
}

Subnet6Ptr
CfgSubnets6::getSubnet(const SubnetID id) const {
    /// @todo: Once this code is migrated to multi-index container, use
    /// an index rather than full scan.
    for (auto const& subnet : subnets_) {
        if (subnet->getID() == id) {
            return (subnet);
        }
    }
    return (Subnet6Ptr());
}

SubnetIDSet
CfgSubnets6::getLinks(const IOAddress& link_addr, uint8_t& link_len) const {
    SubnetIDSet links;
    bool link_len_set = false;
    for (auto const& subnet : subnets_) {
        if (!subnet->inRange(link_addr)) {
            continue;
        }
        uint8_t plen = subnet->get().second;
        if (!link_len_set || (plen < link_len)) {
            link_len_set = true;
            link_len = plen;
        }
        links.insert(subnet->getID());
    }
    return (links);
}

void
CfgSubnets6::removeStatistics() {
    using namespace isc::stats;

    StatsMgr& stats_mgr = StatsMgr::instance();
    // For each v6 subnet currently configured, remove the statistics.
    for (auto const& subnet6 : subnets_) {
        SubnetID subnet_id = subnet6->getID();
        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id, "total-nas"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "assigned-nas"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "cumulative-assigned-nas"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id, "total-pds"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "assigned-pds"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "cumulative-assigned-pds"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "declined-addresses"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "reclaimed-declined-addresses"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "reclaimed-leases"));
    }
}

void
CfgSubnets6::updateStatistics() {
    using namespace isc::stats;

    StatsMgr& stats_mgr = StatsMgr::instance();
    // For each v6 subnet currently configured, calculate totals
    for (auto const& subnet6 : subnets_) {
        SubnetID subnet_id = subnet6->getID();

        stats_mgr.setValue(StatsMgr::generateName("subnet", subnet_id,
                                                  "total-nas"),
                           static_cast<int64_t>
                           (subnet6->getPoolCapacity(Lease::TYPE_NA)));

        stats_mgr.setValue(StatsMgr::generateName("subnet", subnet_id,
                                                  "total-pds"),
                            static_cast<int64_t>
                            (subnet6->getPoolCapacity(Lease::TYPE_PD)));

        const std::string& name_nas =
            StatsMgr::generateName("subnet", subnet_id, "cumulative-assigned-nas");
        if (!stats_mgr.getObservation(name_nas)) {
            stats_mgr.setValue(name_nas, static_cast<int64_t>(0));
        }

        const std::string& name_pds =
            StatsMgr::generateName("subnet", subnet_id, "cumulative-assigned-pds");
        if (!stats_mgr.getObservation(name_pds)) {
            stats_mgr.setValue(name_pds, static_cast<int64_t>(0));
        }
    }

    // Only recount the stats if we have subnets.
    if (subnets_.begin() != subnets_.end()) {
        LeaseMgrFactory::instance().recountLeaseStats6();
    }
}

void
CfgSubnets6::initAllocatorsAfterConfigure() {
    for (auto subnet : subnets_) {
        subnet->initAllocatorsAfterConfigure();
    }
}

ElementPtr
CfgSubnets6::toElement() const {
    ElementPtr result = Element::createList();
    // Iterate subnets
    for (auto const& subnet : subnets_) {
        result->add(subnet->toElement());
    }
    return (result);
}

} // end of namespace isc::dhcp
} // end of namespace isc
