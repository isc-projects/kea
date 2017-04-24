// Copyright (C) 2014-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/addr_utilities.h>
#include <stats/stats_mgr.h>
#include <string.h>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::data;

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
        // Prepare the map
        ElementPtr map = Element::createMap();
        // Set subnet id
        SubnetID id = (*subnet)->getID();
        map->set("id", Element::create(static_cast<long long>(id)));
        // Set relay info
        const Subnet::RelayInfo& relay_info = (*subnet)->getRelayInfo();
        ElementPtr relay = Element::createMap();
        relay->set("ip-address", Element::create(relay_info.addr_.toText()));
        map->set("relay", relay);
        // Set subnet
        map->set("subnet", Element::create((*subnet)->toText()));
        // Set interface
        const std::string& iface = (*subnet)->getIface();
        map->set("interface", Element::create(iface));
        // Set interface-id
        const OptionPtr& ifaceid = (*subnet)->getInterfaceId();
        if (ifaceid) {
            std::vector<uint8_t> bin = ifaceid->getData();
            std::string ifid;
            ifid.resize(bin.size());
            if (!bin.empty()) {
                std::memcpy(&ifid[0], &bin[0], bin.size());
            }
            map->set("interface-id", Element::create(ifid));
        } else {
            map->set("interface-id", Element::create(std::string()));
        }
        // Set renew-timer
        map->set("renew-timer",
                 Element::create(static_cast<long long>
                                 ((*subnet)->getT1().get())));
        // Set rebind-timer
        map->set("rebind-timer",
                 Element::create(static_cast<long long>
                                 ((*subnet)->getT2().get())));
        // Set preferred-lifetime
        map->set("preferred-lifetime",
                 Element::create(static_cast<long long>
                                 ((*subnet)->getPreferred().get())));
        // Set valid-lifetime
        map->set("valid-lifetime",
                 Element::create(static_cast<long long>
                                 ((*subnet)->getValid().get())));
        // Set rapid-commit
        bool rapid_commit = (*subnet)->getRapidCommit();
        map->set("rapid-commit", Element::create(rapid_commit));
        // Set pools
        const PoolCollection& pools = (*subnet)->getPools(Lease::TYPE_NA);
        ElementPtr pool_list = Element::createList();
        for (PoolCollection::const_iterator pool = pools.cbegin();
             pool != pools.cend(); ++pool) {
            // Prepare the map for a pool (@todo move this code to pool.cc)
            ElementPtr pool_map = Element::createMap();
            // Set pool
            const IOAddress& first = (*pool)->getFirstAddress();
            const IOAddress& last = (*pool)->getLastAddress();
            std::string range = first.toText() + "-" + last.toText();
            // Try to output a prefix (vs a range)
            int prefix_len = prefixLengthFromRange(first, last);
            if (prefix_len >= 0) {
                std::ostringstream oss;
                oss << first.toText() << "/" << prefix_len;
                range = oss.str();
            }
            pool_map->set("pool", Element::create(range));
            // Set user-context
            ConstElementPtr context = (*pool)->getContext();
            if (!isNull(context)) {
                pool_map->set("user-context", context);
            }
            // Set pool options
            ConstCfgOptionPtr opts = (*pool)->getCfgOption();
            pool_map->set("option-data", opts->toElement());
            // Push on the pool list
            pool_list->add(pool_map);
        }
        map->set("pools", pool_list);
        // Set pd-pools
        const PoolCollection& pdpools = (*subnet)->getPools(Lease::TYPE_PD);
        ElementPtr pdpool_list = Element::createList();
        for (PoolCollection::const_iterator pool = pdpools.cbegin();
             pool != pdpools.cend(); ++pool) {
            // Get it as a Pool6 (@todo move this code to pool.cc)
            const Pool6* pdpool = dynamic_cast<Pool6*>(pool->get());
            if (!pdpool) {
                isc_throw(ToElementError, "invalid pd-pool pointer");
            }
            // Prepare the map for a pd-pool
            ElementPtr pool_map = Element::createMap();
            // Set prefix
            const IOAddress& prefix = pdpool->getFirstAddress();
            pool_map->set("prefix", Element::create(prefix.toText()));
            // Set prefix-len (get it from min - max)
            const IOAddress& last = pdpool->getLastAddress();
            int prefix_len = prefixLengthFromRange(prefix, last);
            if (prefix_len < 0) {
                // The pool is bad: give up
                isc_throw(ToElementError, "invalid prefix range "
                          << prefix.toText() << "-" << last.toText());
            }
            pool_map->set("prefix-len", Element::create(prefix_len));
            // Set delegated-len
            uint8_t len = pdpool->getLength();
            pool_map->set("delegated-len",
                          Element::create(static_cast<int>(len)));
            // Set excluded prefix
            const Option6PDExcludePtr& xopt =
                pdpool->getPrefixExcludeOption();
            if (xopt) {
                const IOAddress& xprefix =
                    xopt->getExcludedPrefix(prefix, len);
                pool_map->set("excluded-prefix",
                              Element::create(xprefix.toText()));
                uint8_t xlen = xopt->getExcludedPrefixLength();
                pool_map->set("excluded-prefix-len",
                              Element::create(static_cast<int>(xlen)));
            } else {
                pool_map->set("excluded-prefix",
                              Element::create(std::string("::")));
                pool_map->set("excluded-prefix-len", Element::create(0));
            }
            // Set user-context
            ConstElementPtr context = pdpool->getContext();
            if (!isNull(context)) {
                pool_map->set("user-context", context);
            }
            // Set pool options
            ConstCfgOptionPtr opts = pdpool->getCfgOption();
            pool_map->set("option-data", opts->toElement());
            // Push on the pool list
            pdpool_list->add(pool_map);
        }
        map->set("pd-pools", pdpool_list);
        // Set host reservation-mode
        Subnet::HRMode hrmode = (*subnet)->getHostReservationMode();
        std::string mode;
        switch (hrmode) {
        case Subnet::HR_DISABLED:
            mode = "disabled";
            break;
        case Subnet::HR_OUT_OF_POOL:
            mode = "out-of-pool";
            break;
        case Subnet::HR_ALL:
            mode = "all";
            break;
        default:
            isc_throw(ToElementError,
                      "invalid host reservation mode: " << hrmode);
        }
        map->set("reservation-mode", Element::create(mode));
        // Set client-class
        const ClientClasses& cclasses = (*subnet)->getClientClasses();
        if (cclasses.size() > 1) {
            isc_throw(ToElementError, "client-class has too many items: "
                      << cclasses.size());
        } else if (!cclasses.empty()) {
            map->set("client-class", Element::create(*cclasses.cbegin()));
        }
        // Set options
        ConstCfgOptionPtr opts = (*subnet)->getCfgOption();
        map->set("option-data", opts->toElement());
        // Push on the list
        result->add(map);
    }
    return (result);
}

} // end of namespace isc::dhcp
} // end of namespace isc
