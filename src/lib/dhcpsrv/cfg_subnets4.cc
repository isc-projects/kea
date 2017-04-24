// Copyright (C) 2014-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/iface_mgr.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/addr_utilities.h>
#include <asiolink/io_address.h>
#include <stats/stats_mgr.h>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::data;

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
CfgSubnets4::selectSubnet4o6(const SubnetSelector& selector) const {

    for (Subnet4Collection::const_iterator subnet = subnets_.begin();
         subnet != subnets_.end(); ++subnet) {
        Cfg4o6& cfg4o6 = (*subnet)->get4o6();

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
                return (*subnet);
            }
        }

        // Second match criteria: check if the interface-id matches
        if (cfg4o6.getInterfaceId() && selector.interface_id_ &&
            cfg4o6.getInterfaceId()->equals(selector.interface_id_)) {
            return (*subnet);
        }

        // Third match criteria: check if the interface name matches
        if (!cfg4o6.getIface4o6().empty() && !selector.iface_name_.empty()
            && cfg4o6.getIface4o6() == selector.iface_name_) {
            return (*subnet);
        }
    }

    // Ok, wasn't able to find any matching subnet.
    return (Subnet4Ptr());
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
    // address will not match with any of the relay addresses across all
    // subnets, but we need to verify that for all subnets before we can try
    // to use the giaddr to match with the subnet prefix.
    if (!selector.giaddr_.isV4Zero()) {
        for (Subnet4Collection::const_iterator subnet = subnets_.begin();
             subnet != subnets_.end(); ++subnet) {

            // Check if the giaddr is equal to the one defined for the subnet.
            if (selector.giaddr_ != (*subnet)->getRelayInfo().addr_) {
                continue;
            }

            // If a subnet meets the client class criteria return it.
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

        // Attempt to select subnet based on the interface name.
        Subnet4Ptr subnet = selectSubnet(selector.iface_name_,
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
        return (Subnet4Ptr());
    }

    // We have identified an address in the client's packet that can be
    // used for subnet selection. Match this packet with the subnets.
    return (selectSubnet(address, selector.client_classes_));
}

Subnet4Ptr
CfgSubnets4::selectSubnet(const std::string& iface,
                 const ClientClasses& client_classes) const {
    for (Subnet4Collection::const_iterator subnet = subnets_.begin();
         subnet != subnets_.end(); ++subnet) {

        // If there's no interface specified for this subnet, proceed to
        // the next subnet.
        if ((*subnet)->getIface().empty()) {
            continue;
        }

        // If it's specified, but does not match, proceed to the next
        // subnet.
        if ((*subnet)->getIface() != iface) {
            continue;
        }

        // If a subnet meets the client class criteria return it.
        if ((*subnet)->clientSupported(client_classes)) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE,
                      DHCPSRV_CFGMGR_SUBNET4_IFACE)
                .arg((*subnet)->toText())
                .arg(iface);
            return (*subnet);
        }
    }

    // Failed to find a subnet.
    return (Subnet4Ptr());
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

        // If a subnet meets the client class criteria return it.
        if ((*subnet)->clientSupported(client_classes)) {
            LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_SUBNET4_ADDR)
                .arg((*subnet)->toText())
                .arg(address.toText());
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
    StatsMgr& stats_mgr = StatsMgr::instance();
    for (Subnet4Collection::const_iterator subnet4 = subnets_.begin();
         subnet4 != subnets_.end(); ++subnet4) {
        SubnetID subnet_id = (*subnet4)->getID();
        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "total-addresses"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "assigned-addresses"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "declined-addresses"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "declined-reclaimed-addresses"));

        stats_mgr.del(StatsMgr::generateName("subnet", subnet_id,
                                             "reclaimed-leases"));
    }
}

void
CfgSubnets4::updateStatistics() {
    using namespace isc::stats;

    StatsMgr& stats_mgr = StatsMgr::instance();
    for (Subnet4Collection::const_iterator subnet4 = subnets_.begin();
         subnet4 != subnets_.end(); ++subnet4) {
        SubnetID subnet_id = (*subnet4)->getID();

        stats_mgr.setValue(StatsMgr::
                           generateName("subnet", subnet_id, "total-addresses"),
                                        static_cast<int64_t>
                                        ((*subnet4)->getPoolCapacity(Lease::
                                                                     TYPE_V4)));
    }

    // Only recount the stats if we have subnets.
    if (subnets_.begin() != subnets_.end()) {
            LeaseMgrFactory::instance().recountLeaseStats4();
    }
}

ElementPtr
CfgSubnets4::toElement() const {
    ElementPtr result = Element::createList();
    // Iterate subnets
    for (Subnet4Collection::const_iterator subnet = subnets_.cbegin();
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
        // Set renew-timer
        map->set("renew-timer",
                 Element::create(static_cast<long long>
                                 ((*subnet)->getT1().get())));
        // Set rebind-timer
        map->set("rebind-timer",
                 Element::create(static_cast<long long>
                                 ((*subnet)->getT2().get())));
        // Set valid-lifetime
        map->set("valid-lifetime",
                 Element::create(static_cast<long long>
                                 ((*subnet)->getValid().get())));
        // Set pools
        const PoolCollection& pools = (*subnet)->getPools(Lease::TYPE_V4);
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
            // Set pool options (not yet supported)
            // Push on the pool list
            pool_list->add(pool_map);
        }
        map->set("pools", pool_list);
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
        // Set match-client-id
        map->set("match-client-id",
                 Element::create((*subnet)->getMatchClientId()));
        // Set next-server
        map->set("next-server",
                 Element::create((*subnet)->getSiaddr().toText()));
        // Set DHCP4o6
        const Cfg4o6& d4o6 = (*subnet)->get4o6();
        isc::data::merge(map, d4o6.toElement());
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
        // Not supported: interface-id
        // Not supported: rapid-commit
        // Push on the list
        result->add(map);
    }
    return (result);
}

} // end of namespace isc::dhcp
} // end of namespace isc
