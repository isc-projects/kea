// Copyright (C) 2014-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/option_custom.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/subnet_id.h>
#include <asiolink/io_address.h>
#include <asiolink/addr_utilities.h>
#include <stats/stats_mgr.h>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::data;

namespace isc {
namespace dhcp {

void
CfgSubnets4::add(const Subnet4Ptr& subnet) {
    if (getBySubnetId(subnet->getID())) {
        isc_throw(isc::dhcp::DuplicateSubnetID, "ID of the new IPv4 subnet '"
                  << subnet->getID() << "' is already in use");

    } else if (getByPrefix(subnet->toText())) {
        /// @todo: Check that this new subnet does not cross boundaries of any
        /// other already defined subnet.
        isc_throw(isc::dhcp::DuplicateSubnetID, "subnet with the prefix of '"
                  << subnet->toText() << "' already exists");
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_ADD_SUBNET4)
              .arg(subnet->toText());
    static_cast<void>(subnets_.insert(subnet));
}

Subnet4Ptr
CfgSubnets4::replace(const Subnet4Ptr& subnet) {
    // Get the subnet with the same ID.
    const SubnetID& subnet_id = subnet->getID();
    auto& index = subnets_.template get<SubnetSubnetIdIndexTag>();
    auto subnet_it = index.find(subnet_id);
    if (subnet_it == index.end()) {
        isc_throw(BadValue, "There is no IPv4 subnet with ID " <<subnet_id);
    }
    Subnet4Ptr old = *subnet_it;
    bool ret = index.replace(subnet_it, subnet);

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_UPDATE_SUBNET4)
        .arg(subnet_id).arg(ret);
    if (ret) {
        return (old);
    } else {
        return (Subnet4Ptr());
    }
}

void
CfgSubnets4::del(const ConstSubnet4Ptr& subnet) {
    del(subnet->getID());
}

void
CfgSubnets4::del(const SubnetID& subnet_id) {
    auto& index = subnets_.get<SubnetSubnetIdIndexTag>();
    auto subnet_it = index.find(subnet_id);
    if (subnet_it == index.end()) {
        isc_throw(BadValue, "no subnet with ID of '" << subnet_id
                  << "' found");
    }

    Subnet4Ptr subnet = *subnet_it;

    index.erase(subnet_it);

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_DEL_SUBNET4)
        .arg(subnet->toText());
}

void
CfgSubnets4::merge(CfgOptionDefPtr cfg_def, CfgSharedNetworks4Ptr networks,
                   CfgSubnets4& other) {
    auto& index_id = subnets_.get<SubnetSubnetIdIndexTag>();
    auto& index_prefix = subnets_.get<SubnetPrefixIndexTag>();

    // Iterate over the subnets to be merged. They will replace the existing
    // subnets with the same id. All new subnets will be inserted into the
    // configuration into which we're merging.
    auto const& other_subnets = other.getAll();
    for (auto const& other_subnet : (*other_subnets)) {

        // Check if there is a subnet with the same ID.
        auto subnet_id_it = index_id.find(other_subnet->getID());
        if (subnet_id_it != index_id.end()) {

            // Subnet found.
            auto existing_subnet = *subnet_id_it;

            // If the existing subnet and other subnet
            // are the same instance skip it.
            if (existing_subnet == other_subnet) {
                continue;
            }

            // Updating the prefix can lead to problems... e.g. pools
            // and reservations going outside range.
            // @todo: check prefix change.

            // We're going to replace the existing subnet with the other
            // version. If it belongs to a shared network, we need
            // remove it from that network.
            SharedNetwork4Ptr network;
            existing_subnet->getSharedNetwork(network);
            if (network) {
                network->del(existing_subnet->getID());
            }

            // Now we remove the existing subnet.
            index_id.erase(subnet_id_it);
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
            SharedNetwork4Ptr network;
            existing_subnet->getSharedNetwork(network);
            if (network) {
                network->del(existing_subnet->getID());
            }

            // Now we remove the existing subnet.
            index_prefix.erase(subnet_prefix_it);
        }

        // Create the subnet's options based on the given definitions.
        other_subnet->getCfgOption()->createOptions(cfg_def);

        // Encapsulate options, so that the DHCP server can effectively return
        // them to the clients without having to encapsulate them for each request.
        other_subnet->getCfgOption()->encapsulate();

        // Create the options for pool based on the given definitions.
        for (auto const& pool : other_subnet->getPoolsWritable(Lease::TYPE_V4)) {
            pool->getCfgOption()->createOptions(cfg_def);
            pool->getCfgOption()->encapsulate();
        }

        // Add the "other" subnet to the our collection of subnets.
        static_cast<void>(subnets_.insert(other_subnet));

        // If it belongs to a shared network, find the network and
        // add the subnet to it
        std::string network_name = other_subnet->getSharedNetworkName();
        if (!network_name.empty()) {
            SharedNetwork4Ptr network = networks->getByName(network_name);
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
        // Instantiate the configured allocator and its state.
        other_subnet->createAllocators();
    }
}

ConstSubnet4Ptr
CfgSubnets4::getByPrefix(const std::string& subnet_text) const {
    auto const& index = subnets_.get<SubnetPrefixIndexTag>();
    auto subnet_it = index.find(subnet_text);
    return ((subnet_it != index.cend()) ? (*subnet_it) : ConstSubnet4Ptr());
}

bool
CfgSubnets4::hasSubnetWithServerId(const asiolink::IOAddress& server_id) const {
    auto const& index = subnets_.get<SubnetServerIdIndexTag>();
    auto subnet_it = index.find(server_id);
    return (subnet_it != index.cend());
}

SubnetSelector
CfgSubnets4::initSelector(const Pkt4Ptr& query) {
    SubnetSelector selector;
    selector.ciaddr_ = query->getCiaddr();
    selector.giaddr_ = query->getGiaddr();
    selector.local_address_ = query->getLocalAddr();
    selector.remote_address_ = query->getRemoteAddr();
    selector.client_classes_ = query->classes_;
    selector.iface_name_ = query->getIface();

    // If the link-selection sub-option is present, extract its value.
    // "The link-selection sub-option is used by any DHCP relay agent
    // that desires to specify a subnet/link for a DHCP client request
    // that it is relaying but needs the subnet/link specification to
    // be different from the IP address the DHCP server should use
    // when communicating with the relay agent." (RFC 3527)
    //
    // Try first Relay Agent Link Selection sub-option
    OptionPtr rai = query->getOption(DHO_DHCP_AGENT_OPTIONS);
    if (rai) {
        OptionCustomPtr rai_custom =
            boost::dynamic_pointer_cast<OptionCustom>(rai);
        if (rai_custom) {
            // If Relay Agent Information Link Selection is ignored in the
            // configuration, skip returning the related subnet selector here,
            // and move on to normal subnet selection.
            bool ignore_link_sel = CfgMgr::instance().getCurrentCfg()->
                                   getIgnoreRAILinkSelection();
            if (!ignore_link_sel) {
                OptionPtr link_select =
                    rai_custom->getOption(RAI_OPTION_LINK_SELECTION);
                if (link_select) {
                    OptionBuffer link_select_buf = link_select->getData();
                    if (link_select_buf.size() == sizeof(uint32_t)) {
                        selector.option_select_ =
                            IOAddress::fromBytes(AF_INET, &link_select_buf[0]);
                        return (selector);
                    }
                }
            }
        }
    }
    // The query does not include a RAI option or that option does
    // not contain the link-selection sub-option. Try subnet-selection
    // option.
    OptionPtr sbnsel = query->getOption(DHO_SUBNET_SELECTION);
    if (sbnsel) {
        OptionCustomPtr oc =
            boost::dynamic_pointer_cast<OptionCustom>(sbnsel);
        if (oc) {
            selector.option_select_ = oc->readAddress();
        }
    }
    return (selector);
}

ConstSubnet4Ptr
CfgSubnets4::selectSubnet4o6(const SubnetSelector& selector) const {
    for (auto const& subnet : subnets_) {
        Cfg4o6& cfg4o6 = subnet->get4o6();

        // Is this an 4o6 subnet at all?
        if (!cfg4o6.enabled()) {
            continue; // No? Let's try the next one.
        }

        // First match criteria: check if we have a prefix/len defined.
        std::pair<asiolink::IOAddress, uint8_t> pref = cfg4o6.getSubnet4o6();
        if (!pref.first.isV6Zero()) {

            // Let's check if the IPv6 address is in range
            IOAddress first = firstAddrInPrefix(pref.first, pref.second);
            IOAddress last = lastAddrInPrefix(pref.first, pref.second);
            if ((first <= selector.remote_address_) &&
                (selector.remote_address_ <= last)) {
                return (subnet);
            }
        }

        // Second match criteria: check if the interface-id matches
        if (cfg4o6.getInterfaceId() && selector.interface_id_ &&
            cfg4o6.getInterfaceId()->equals(selector.interface_id_)) {
            return (subnet);
        }

        // Third match criteria: check if the interface name matches
        if (!cfg4o6.getIface4o6().empty() && !selector.iface_name_.empty()
            && cfg4o6.getIface4o6() == selector.iface_name_) {
            return (subnet);
        }
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_SUBNET4O6_SELECT_FAILED);

    // Ok, wasn't able to find any matching subnet.
    return (ConstSubnet4Ptr());
}

ConstSubnet4Ptr
CfgSubnets4::selectSubnet(const SubnetSelector& selector) const {
    // First use RAI link select sub-option or subnet select option
    if (!selector.option_select_.isV4Zero()) {
        return (selectSubnet(selector.option_select_,
                             selector.client_classes_));
    } else {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                  DHCPSRV_SUBNET4_SELECT_NO_RAI_OPTIONS);
    }

    // If relayed message has been received, try to match the giaddr with the
    // relay address specified for a subnet and/or shared network. It is also
    // possible that the relay address will not match with any of the relay
    // addresses across all subnets, but we need to verify that for all subnets
    // before we can try to use the giaddr to match with the subnet prefix.
    if (!selector.giaddr_.isV4Zero()) {
        for (auto const& subnet : subnets_) {

            // If relay information is specified for this subnet, it must match.
            // Otherwise, we ignore this subnet.
            if (subnet->hasRelays()) {
                if (!subnet->hasRelayAddress(selector.giaddr_)) {
                    continue;
                }
            } else {
                // Relay information is not specified on the subnet level,
                // so let's try matching on the shared network level.
                SharedNetwork4Ptr network;
                subnet->getSharedNetwork(network);
                if (!network || !(network->hasRelayAddress(selector.giaddr_))) {
                    continue;
                }
            }

            // If a subnet meets the client class criteria return it.
            if (subnet->clientSupported(selector.client_classes_)) {
                LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                          DHCPSRV_CFGMGR_SUBNET4_RELAY)
                    .arg(subnet->toText())
                    .arg(selector.giaddr_.toText());
                return (subnet);
            }
        }
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                  DHCPSRV_SUBNET4_SELECT_BY_RELAY_ADDRESS_NO_MATCH)
            .arg(selector.giaddr_.toText());
    } else {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                  DHCPSRV_SUBNET4_SELECT_NO_RELAY_ADDRESS);
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

        // Attempt to select subnet based on the interface name.
        ConstSubnet4Ptr subnet = selectSubnet(selector.iface_name_,
                                              selector.client_classes_);

        // If it matches - great. If not, we'll try to use a different
        // selection criteria below.
        if (subnet) {
            return (subnet);
        } else {
            // Let's try to get an address from the local interface and
            // try to match it to defined subnet.
            iface->getAddress4(address);
        }
    }

    // Unable to find a suitable address to use for subnet selection.
    if (address.isV4Zero()) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                  DHCPSRV_SUBNET4_SELECT_NO_USABLE_ADDRESS);

        return (ConstSubnet4Ptr());
    }

    // We have identified an address in the client's packet that can be
    // used for subnet selection. Match this packet with the subnets.
    return (selectSubnet(address, selector.client_classes_));
}

ConstSubnet4Ptr
CfgSubnets4::selectSubnet(const std::string& iface,
                          const ClientClasses& client_classes) const {
    for (auto const& subnet : subnets_) {
        ConstSubnet4Ptr subnet_selected;

        // First, try subnet specific interface name.
        if (!subnet->getIface(Network4::Inheritance::NONE).empty()) {
            if (subnet->getIface(Network4::Inheritance::NONE) == iface) {
                subnet_selected = subnet;
            }

        } else {
            // Interface not specified for a subnet, so let's try if
            // we can match with shared network specific setting of
            // the interface.
            SharedNetwork4Ptr network;
            subnet->getSharedNetwork(network);
            if (network &&
                (network->getIface(Network4::Inheritance::NONE) == iface)) {
                subnet_selected = subnet;
            }
        }

        if (subnet_selected) {
            // If a subnet meets the client class criteria return it.
            if (subnet_selected->clientSupported(client_classes)) {
                LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                          DHCPSRV_CFGMGR_SUBNET4_IFACE)
                    .arg(subnet->toText())
                    .arg(iface);
                return (subnet_selected);
            }
        }
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
              DHCPSRV_SUBNET4_SELECT_BY_INTERFACE_NO_MATCH)
        .arg(iface);

    // Failed to find a subnet.
    return (ConstSubnet4Ptr());
}

Subnet4Ptr
CfgSubnets4::getSubnet(const SubnetID subnet_id) const {
    auto const& index = subnets_.get<SubnetSubnetIdIndexTag>();
    auto subnet_it = index.find(subnet_id);
    return ((subnet_it != index.cend()) ? (*subnet_it) : Subnet4Ptr());
}

ConstSubnet4Ptr
CfgSubnets4::selectSubnet(const IOAddress& address,
                          const ClientClasses& client_classes) const {
    for (auto const& subnet : subnets_) {

        // Address is in range for the subnet prefix, so return it.
        if (!subnet->inRange(address)) {
            continue;
        }

        // If a subnet meets the client class criteria return it.
        if (subnet->clientSupported(client_classes)) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_SUBNET4_ADDR)
                .arg(subnet->toText())
                .arg(address.toText());
            return (subnet);
        }
    }

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
              DHCPSRV_SUBNET4_SELECT_BY_ADDRESS_NO_MATCH)
        .arg(address.toText());

    // Failed to find a subnet.
    return (ConstSubnet4Ptr());
}

SubnetIDSet
CfgSubnets4::getLinks(const IOAddress& link_addr) const {
    SubnetIDSet links;
    for (auto const& subnet : subnets_) {
        if (!subnet->inRange(link_addr)) {
            continue;
        }
        links.insert(subnet->getID());
    }
    return (links);
}

void
CfgSubnets4::removeStatistics() {
    using namespace isc::stats;

    // For each v4 subnet currently configured, remove the statistic.
    StatsMgr& stats_mgr = StatsMgr::instance();
    for (auto const& subnet4 : subnets_) {
        SubnetID subnet_id = subnet4->getID();
        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "total-addresses"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "assigned-addresses"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "cumulative-assigned-addresses"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "declined-addresses"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "reclaimed-declined-addresses"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "reclaimed-leases"));

        for (auto const& pool : subnet4->getPools(Lease::TYPE_V4)) {
            stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                                 StatsMgr::generateName("pool", pool->getID(),
                                                                        "total-addresses")));

            stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                                 StatsMgr::generateName("pool", pool->getID(),
                                                                        "assigned-addresses")));

            stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                                 StatsMgr::generateName("pool", pool->getID(),
                                                                        "cumulative-assigned-addresses")));

            stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                                 StatsMgr::generateName("pool", pool->getID(),
                                                                        "declined-addresses")));

            stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                                 StatsMgr::generateName("pool", pool->getID(),
                                                                        "reclaimed-declined-addresses")));

            stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                                 StatsMgr::generateName("pool", pool->getID(),
                                                                        "reclaimed-leases")));
        }
    }
}

void
CfgSubnets4::updateStatistics() {
    using namespace isc::stats;

    StatsMgr& stats_mgr = StatsMgr::instance();
    for (auto const& subnet4 : subnets_) {
        SubnetID subnet_id = subnet4->getID();

        stats_mgr.setValue(StatsMgr::
                           generateName("subnet", subnet_id, "total-addresses"),
                                        int64_t(subnet4->getPoolCapacity(Lease::TYPE_V4)));
        const std::string& name(StatsMgr::generateName("subnet", subnet_id,
                                                       "cumulative-assigned-addresses"));
        if (!stats_mgr.getObservation(name)) {
            stats_mgr.setValue(name, static_cast<int64_t>(0));
        }

        const std::string& name_reuses(StatsMgr::generateName("subnet", subnet_id,
                                                              "v4-lease-reuses"));
        if (!stats_mgr.getObservation(name_reuses)) {
            stats_mgr.setValue(name_reuses, int64_t(0));
        }

        const std::string& name_conflicts(StatsMgr::generateName("subnet", subnet_id,
                                                                 "v4-reservation-conflicts"));
        if (!stats_mgr.getObservation(name_conflicts)) {
            stats_mgr.setValue(name_conflicts, static_cast<int64_t>(0));
        }

        for (auto const& pool : subnet4->getPools(Lease::TYPE_V4)) {
            const std::string& name_total(StatsMgr::generateName("subnet", subnet_id,
                                                                 StatsMgr::generateName("pool", pool->getID(),
                                                                                        "total-addresses")));
            if (!stats_mgr.getObservation(name_total)) {
                stats_mgr.setValue(name_total, static_cast<int64_t>(pool->getCapacity()));
            } else {
                stats_mgr.addValue(name_total, static_cast<int64_t>(pool->getCapacity()));
            }

            const std::string& name_ca(StatsMgr::generateName("subnet", subnet_id,
                                                              StatsMgr::generateName("pool", pool->getID(),
                                                                                     "cumulative-assigned-addresses")));
            if (!stats_mgr.getObservation(name_ca)) {
                stats_mgr.setValue(name_ca, static_cast<int64_t>(0));
            }
        }
    }

    // Only recount the stats if we have subnets.
    if (subnets_.begin() != subnets_.end()) {
        LeaseMgrFactory::instance().recountLeaseStats4();
    }
}

void
CfgSubnets4::initAllocatorsAfterConfigure() {
    for (auto const& subnet : subnets_) {
        subnet->initAllocatorsAfterConfigure();
    }
}

void
CfgSubnets4::clear() {
    subnets_.clear();
}

ElementPtr
CfgSubnets4::toElement() const {
    ElementPtr result = Element::createList();
    // Iterate subnets
    for (auto const& subnet : subnets_) {
        result->add(subnet->toElement());
    }
    return (result);
}

} // end of namespace isc::dhcp
} // end of namespace isc
