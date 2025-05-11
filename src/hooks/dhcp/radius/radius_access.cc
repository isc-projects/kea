// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcpsrv/callout_handle_store.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host_mgr.h>
#include <radius_access.h>
#include <radius_log.h>
#include <radius_utils.h>
#include <util/multi_threading_mgr.h>
#include <stdio.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::util;
namespace ph = std::placeholders;

namespace {

// From Dhcpv6Srv.
HWAddrPtr
getMAC(Pkt6& pkt) {
    CfgMACSources mac_sources = CfgMgr::instance().getCurrentCfg()->
        getMACSources().get();
    HWAddrPtr hwaddr;
    for (auto const& source : mac_sources) {
        hwaddr = pkt.getMAC(source);
        if (hwaddr) {
            return (hwaddr);
        }
    }
    return (hwaddr);
}

} // end of anonymous namespace.

namespace isc {
namespace radius {

RadiusAuthEnv::RadiusAuthEnv(uint32_t subnet_id,
                             const std::vector<uint8_t>& id,
                             AttributesPtr send_attrs)
    : subnet_id_(subnet_id), id_(id), send_attrs_(send_attrs) {
}

RadiusAuthHandler::RadiusAuthHandler(RadiusAuthEnv env,
                                     const CallbackAuth& callback)
    : env_(env), auth_() {
    auth_.reset(new RadiusAsyncAuth(env.subnet_id_, env_.send_attrs_, callback));
    RadiusImpl::instance().registerExchange(auth_->getExchange());
    // set the IO service when async access will be available.
}

void
RadiusAuthHandler::start() {
    auth_->start();
}

RadiusAccess::RadiusAccess() : RadiusService("access") {
}

bool
RadiusAccess::getIdentifier(dhcp::Pkt4& query,
                            std::vector<uint8_t>& id,
                            std::string& text) {
    Host::IdentifierType type = RadiusImpl::instance().id_type4_;
    try {
        HWAddrPtr hwaddr;
        OptionPtr option;
        ClientIdPtr clientid;
        bool extracted = false;
        switch (type) {
        case Host::IDENT_HWADDR:
            hwaddr = query.getHWAddr();
            if (!hwaddr) {
                isc_throw(BadValue, "no hardware address");
            }
            id = hwaddr->hwaddr_;
            if (id.empty()) {
                isc_throw(BadValue, "empty hardware address");
            }
            text = query.getHWAddr()->toText(false);
            if (RadiusImpl::instance().canonical_mac_address_) {
                text = canonize(text);
            }
            break;

        case Host::IDENT_DUID:
            option = query.getOption(DHO_DHCP_CLIENT_IDENTIFIER);
            if (!option) {
                isc_throw(BadValue, "no client-id option");
            }
            clientid.reset(new ClientId(option->getData()));
            id = clientid->getClientId();
            if ((id.size() <= 5) || (id[0] != CLIENT_ID_OPTION_TYPE_DUID)) {
                isc_throw(BadValue, "no DUID in client-id option");
            }
            id = vector<uint8_t>(id.begin() + 5, id.end());
            if (RadiusImpl::instance().clientid_printable_) {
                text = toPrintable(id);
            } else {
                text = toHex(id);
            }
            break;

        case Host::IDENT_CIRCUIT_ID:
            option = query.getOption(DHO_DHCP_AGENT_OPTIONS);
            if (!option) {
                isc_throw(BadValue, "no relay agent options");
            }
            option = option->getOption(RAI_OPTION_AGENT_CIRCUIT_ID);
            if (!option) {
                isc_throw(BadValue, "no circuit-id option");
            }
            id = option->getData();
            if (id.empty()) {
                isc_throw(BadValue, "empty circuit-id option");
            }
            if (RadiusImpl::instance().clientid_printable_) {
                text = toPrintable(id);
            } else {
                text = toHex(id);
            }
            break;

        case Host::IDENT_CLIENT_ID:
            option = query.getOption(DHO_DHCP_CLIENT_IDENTIFIER);
            if (!option) {
                isc_throw(BadValue, "no client-id option");
            }
            clientid.reset(new ClientId(option->getData()));
            id = clientid->getClientId();
            if (id.empty()) {
                isc_throw(BadValue, "empty client-id option");
            }
            if (RadiusImpl::instance().extract_duid_) {
                text = toHex(extractDuid(clientid, extracted));
            }
            if (extracted) {
                break;
            }
            if (RadiusImpl::instance().clientid_pop0_) {
                vector<uint8_t> popped = pop0(clientid);
                if (RadiusImpl::instance().clientid_printable_) {
                    text = toPrintable(popped);
                } else {
                    text = toHex(popped);
                }
            } else if (RadiusImpl::instance().clientid_printable_) {
                text = toPrintable(id);
            } else {
                text = toHex(id);
            }
            break;

        case Host::IDENT_FLEX:
            // Relies on replace-client-id flex-id parameter to be true.
            option = query.getOption(DHO_DHCP_CLIENT_IDENTIFIER);
            if (!option) {
                isc_throw(BadValue, "no client-id option");
            }
            clientid.reset(new ClientId(option->getData()));
            id = clientid->getClientId();
            if ((id.size() <= 1) || (id[0] != 0)) {
                isc_throw(BadValue, "no flex-id in client-id option");
            }
            id = vector<uint8_t>(id.begin() + 1, id.end());
            if (RadiusImpl::instance().clientid_printable_) {
                text = toPrintable(id);
            } else {
                text = toHex(id);
            }
            break;

        default:
            isc_throw(OutOfRange, "unsupported identifier type " << type);
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_ACCESS_GET_IDENTIFIER_FAILED)
            .arg(Host::getIdentifierName(type))
            .arg(query.getLabel())
            .arg(ex.what());
        id.clear();
        text.clear();
        return (false);
    }
    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_ACCESS_GET_IDENTIFIER)
        .arg(toHex(id))
        .arg(Host::getIdentifierName(type))
        .arg(text)
        .arg(query.getLabel());
    return (true);
}

bool
RadiusAccess::getIdentifier(dhcp::Pkt6& query,
                            std::vector<uint8_t>& id,
                            std::string& text) {
    Host::IdentifierType type = RadiusImpl::instance().id_type6_;
    try {
        HWAddrPtr hwaddr;
        OptionPtr option;
        DuidPtr duid;
        switch (type) {
        case Host::IDENT_DUID:
            option = query.getOption(D6O_CLIENTID);
            if (!option) {
                isc_throw(BadValue, "no client-id option");
            }
            duid.reset(new DUID(option->getData()));
            id = duid->getDuid();
            if (id.empty()) {
                isc_throw(BadValue, "empty client-id option");
            }
            if (RadiusImpl::instance().clientid_pop0_) {
                vector<uint8_t> popped = pop0(duid);
                if (RadiusImpl::instance().clientid_printable_) {
                    text = toPrintable(popped);
                } else {
                    text = toHex(popped);
                }
            } else if (RadiusImpl::instance().clientid_printable_) {
                text = toPrintable(id);
            } else {
                text = toHex(id);
            }
            break;

        case Host::IDENT_HWADDR:
            hwaddr = getMAC(query);
            if (!hwaddr) {
                isc_throw(BadValue, "no hardware address");
            }
            id = hwaddr->hwaddr_;
            if (id.empty()) {
                isc_throw(BadValue, "empty hardware address");
            }
            text = hwaddr->toText(false);
            if (RadiusImpl::instance().canonical_mac_address_) {
                text = canonize(text);
            }
            break;

        case Host::IDENT_FLEX:
            option = query.getOption(D6O_CLIENTID);
            if (!option) {
                isc_throw(BadValue, "no client-id option");
            }
            duid.reset(new DUID(option->getData()));
            id = duid->getDuid();
            if ((id.size() <= 2) || (id[0] != 0) || (id[1] != 0)) {
                isc_throw(BadValue, "no flex-id in client-id option");
            }
            id = vector<uint8_t>(id.begin() + 2, id.end());
            if (RadiusImpl::instance().clientid_printable_) {
                text = toPrintable(id);
            } else {
                text = toHex(id);
            }
            break;

        default:
            isc_throw(OutOfRange, "unsupported identifier type " << type);
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_ACCESS_GET_IDENTIFIER_FAILED)
            .arg(Host::getIdentifierName(type))
            .arg(query.getLabel())
            .arg(ex.what());
        id.clear();
        text.clear();
        return (false);
    }
    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_ACCESS_GET_IDENTIFIER)
        .arg(toHex(id))
        .arg(Host::getIdentifierName(type))
        .arg(text)
        .arg(query.getLabel());
    return (true);
}

RadiusAuthHandlerPtr
RadiusAccess::buildAuth(dhcp::Pkt4& query,
                        uint32_t subnet_id,
                        const std::vector<uint8_t>& id,
                        const std::string& text) {
    AttributesPtr send(new Attributes());

    try {
        if (subnet_id == SUBNET_ID_UNUSED) {
            isc_throw(BadValue, "subnet ID is reserved");
        }

        send->add(Attribute::fromString(PW_USER_NAME, text));

        // Add hardware address.
        HWAddrPtr hwaddr = query.getHWAddr();
        if (RadiusImpl::instance().id_type4_ != Host::IDENT_HWADDR &&
            hwaddr && !hwaddr->hwaddr_.empty()) {
            string hw = hwaddr->toText(false);
            if (RadiusImpl::instance().canonical_mac_address_) {
                hw = canonize(hw);
            }
            send->add(Attribute::fromString(PW_CALLING_STATION_ID, hw));
        }

        // Add attributes from configuration.
        send->append(RadiusImpl::instance().auth_->
                     attributes_.getEvalAll(query));

    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_ACCESS_BUILD_FAILED)
            .arg(ex.what())
            .arg(query.getLabel());
        return (RadiusAuthHandlerPtr());
    }

    // Return the handler.
    RadiusAuthEnv env(subnet_id, id, send);
    RadiusAuthHandlerPtr handler;
    handler.reset(new RadiusAuthHandler(env,
                                        std::bind(&RadiusAccess::terminate4,
                                                  env, ph::_1, ph::_2)));
    return (handler);
}

RadiusAuthHandlerPtr
RadiusAccess::buildAuth(dhcp::Pkt6& query,
                        uint32_t subnet_id,
                        const std::vector<uint8_t>& id,
                        const std::string& text) {
    AttributesPtr send(new Attributes());

    try {
        if (subnet_id == SUBNET_ID_UNUSED) {
            isc_throw(BadValue, "subnet ID is reserved");
        }

        send->add(Attribute::fromString(PW_USER_NAME, text));

        // Add hardware address.
        HWAddrPtr hwaddr = getMAC(query);
        if (RadiusImpl::instance().id_type6_ != Host::IDENT_HWADDR &&
            hwaddr && !hwaddr->hwaddr_.empty()) {
            string hw = hwaddr->toText(false);
            if (RadiusImpl::instance().canonical_mac_address_) {
                hw = canonize(hw);
            }
            send->add(Attribute::fromString(PW_CALLING_STATION_ID, hw));
        }

        // Add attributes from configuration.
        send->append(RadiusImpl::instance().auth_->
                     attributes_.getEvalAll(query));

    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_ACCESS_BUILD_FAILED)
            .arg(ex.what())
            .arg(query.getLabel());
        return (RadiusAuthHandlerPtr());
    }

    // Return the handler.
    RadiusAuthEnv env(subnet_id, id, send);
    RadiusAuthHandlerPtr handler;
    handler.reset(new RadiusAuthHandler(env,
                                        std::bind(&RadiusAccess::terminate6,
                                                  env, ph::_1, ph::_2)));
    return (handler);
}

bool
RadiusAccess::reselectSubnet(const dhcp::Pkt4Ptr& query, uint32_t& subnet_id,
                             bool& both_global, const std::string& cclass) {
    both_global = false;
    ConstCfgSubnets4Ptr subnets4 =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();

    // Check selected subnet.
    ConstSubnet4Ptr subnet = subnets4->getBySubnetId(subnet_id);
    if (!subnet) {
        return (false);
    }
    // If one of the pools accepts the client-class we're done.
    if (subnet->clientSupported(query->classes_)) {
        const PoolCollection& pools = subnet->getPools(Lease::TYPE_V4);
        for (auto const& pool : pools) {
            if (pool->clientSupported(cclass)) {
                return (false);
            }
        }
    }
    // Check if this subnet uses global reservations.
    bool use_global = subnet->getReservationsGlobal();

    // Try other selectable subnets.
    const Subnet4Collection* subnets = subnets4->getAll();
    CfgSubnets4Ptr selectable(new CfgSubnets4());

    for (auto const& iter : *subnets) {
        // Check pools.
        const PoolCollection& pools = iter->getPools(Lease::TYPE_V4);
        for (auto const& pool : pools) {
            if (pool->clientSupported(cclass)) {
                selectable->add(iter);
                break;
            }
        }
    }

    const SubnetSelector& selector = CfgSubnets4::initSelector(query);
    subnet = selectable->selectSubnet(selector);

    if (!subnet) {
        subnet_id = SUBNET_ID_UNUSED;
    } else {
        subnet_id = subnet->getID();
        if (use_global && subnet->getReservationsGlobal()) {
            both_global = true;
        }
    }
    return (true);
}

bool
RadiusAccess::reselectSubnet(const dhcp::Pkt6Ptr& query, uint32_t& subnet_id,
                             bool& both_global, const std::string& cclass) {
    both_global = false;
    ConstCfgSubnets6Ptr subnets6 =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();

    // Check selected subnet.
    ConstSubnet6Ptr subnet = subnets6->getBySubnetId(subnet_id);
    if (!subnet) {
        return (false);
    }
    // If one of the pools accepts the client-class we're done.
    if (subnet->clientSupported(query->classes_)) {
        const PoolCollection& pools = subnet->getPools(Lease::TYPE_NA);
        for (auto const& pool : pools) {
            if (pool->clientSupported(cclass)) {
                return (false);
            }
        }
    }
    // Check if this subnet uses global reservations.
    bool use_global = subnet->getReservationsGlobal();

    // Try other selectable subnets.
    const Subnet6Collection* subnets = subnets6->getAll();
    CfgSubnets6Ptr selectable(new CfgSubnets6());

    for (auto const& iter : *subnets) {
        // Check pools.
        const PoolCollection& pools = iter->getPools(Lease::TYPE_NA);
        for (auto const& pool : pools) {
            if (pool->clientSupported(cclass)) {
                selectable->add(iter);
                break;
            }
        }
    }

    const SubnetSelector& selector = CfgSubnets6::initSelector(query);
    subnet = selectable->selectSubnet(selector);

    if (!subnet) {
        subnet_id = SUBNET_ID_UNUSED;
    } else {
        subnet_id = subnet->getID();
        if (use_global && subnet->getReservationsGlobal()) {
            both_global = true;
        }
    }
    return (true);
}

bool
RadiusAccess::reselectSubnet(const isc::dhcp::Pkt4Ptr& query,
                             uint32_t& subnet_id,
                             bool& both_global,
                             const asiolink::IOAddress& address) {
    both_global = false;
    ConstCfgSubnets4Ptr subnets4 =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();

    // Check selected subnet.
    ConstSubnet4Ptr subnet = subnets4->getBySubnetId(subnet_id);
    if (!subnet) {
        return (false);
    }
    // If the reserved address is in range we're done.
    if (subnet->clientSupported(query->classes_) && subnet->inRange(address)) {
        return (false);
    }
    // Check if this subnet uses global reservations.
    bool use_global = subnet->getReservationsGlobal();

    // Select subnet by reserved address only.
    subnet = subnets4->selectSubnet(address, query->classes_);
    if (!subnet) {
        subnet_id = SUBNET_ID_UNUSED;
    } else {
        subnet_id = subnet->getID();
        if (use_global && subnet->getReservationsGlobal()) {
            both_global = true;
        }
    }
    return (true);
}

bool
RadiusAccess::reselectSubnet(const isc::dhcp::Pkt6Ptr& query,
                             uint32_t& subnet_id,
                             bool& both_global,
                             const asiolink::IOAddress& address) {
    both_global = false;
    ConstCfgSubnets6Ptr subnets6 =
        CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();

    // Check selected subnet.
    ConstSubnet6Ptr subnet = subnets6->getBySubnetId(subnet_id);
    if (!subnet) {
        return (false);
    }
    // If the reserved address is in range we're done.
    if (subnet->clientSupported(query->classes_) && subnet->inRange(address)) {
        return (false);
    }
    // Check if this subnet uses global reservations.
    bool use_global = subnet->getReservationsGlobal();

    // Select subnet by reserved address only.
    subnet = subnets6->selectSubnet(address, query->classes_);
    if (!subnet) {
        subnet_id = SUBNET_ID_UNUSED;
    } else {
        subnet_id = subnet->getID();
        if (use_global && subnet->getReservationsGlobal()) {
            both_global = true;
        }
    }
    return (true);
}

void
RadiusAccess::terminate4Internal(RadiusAuthEnv& env, int result,
                                 AttributesPtr recv_attrs,
                                 Pkt4Ptr& query, bool& drop) {
    RadiusImpl& impl = RadiusImpl::instance();
    MultiThreadingLock lock(impl.auth_->requests4_.mutex_);

    // Get the pending request.
    RadiusAuthPendingRequestPtr<Pkt4Ptr> pending_request =
        impl.auth_->requests4_.get(env.id_);
    if (!pending_request) {
        LOG_ERROR(radius_logger, RADIUS_ACCESS_ORPHAN)
            .arg(toHex(env.id_));
        drop = true;
        return;
    }
    // Outside some unit tests the query is never null.
    query = pending_request->query_;
    impl.auth_->requests4_.remove(env.id_);

    // Process response.
    ConstAttributePtr ip_address;
    ConstAttributePtr framed_pool;
    ConstAttributePtr class_;
    bool reselected = false;
    bool both_global = false;
    uint32_t original_subnet_id = env.subnet_id_;

    if (result == REJECT_RC) {
        // Create the host with no attributes.
        // Should we saved them for the Class?
        recv_attrs.reset();
        // Reset subnet
        env.subnet_id_ = SUBNET_ID_UNUSED;
        reselected = true;
    } else if (result != OK_RC) {
        // Error case
        LOG_ERROR(radius_logger, RADIUS_ACCESS_ERROR)
            .arg(result)
            .arg(exchangeRCtoText(result));
        // what to do? For now nothing!?
        // drop = true;
        return;
    } else if (recv_attrs) {
        // Pickup interesting things in received attributes.
        ip_address = recv_attrs->get(PW_FRAMED_IP_ADDRESS);
        framed_pool = recv_attrs->get(PW_FRAMED_POOL);
        class_ = recv_attrs->get(PW_CLASS);
        // etc
    }

    // Set pool.
    string cclass;
    if (framed_pool && (framed_pool->getValueType() == PW_TYPE_STRING)) {
        cclass = framed_pool->toString();
        if (query) {
            query->addClass(cclass);
        }
    }

    // Get IPv4 address.
    IOAddress addr4 = IOAddress::IPV4_ZERO_ADDRESS();
    if (ip_address && (ip_address->getValueType() == PW_TYPE_IPADDR)) {
        addr4 = ip_address->toIpAddr();
    }

    // Check reselection using pool and client-class.
    if (query && !reselected && !cclass.empty() &&
        impl.reselect_subnet_pool_) {
        reselected = reselectSubnet(query, env.subnet_id_, both_global, cclass);
    }

    // Check reselection using reserved address and range.
    if (query && !reselected &&  !addr4.isV4Zero() &&
        impl.reselect_subnet_address_) {
        reselected = reselectSubnet(query, env.subnet_id_, both_global, addr4);
    }

    // Get host identifier.
    Host::IdentifierType type = impl.id_type4_;
    CacheHostDataSourcePtr cache = impl.cache_;
    ElementPtr map = Element::createMap();
    if (reselected) {
        // Add subnet-id in user context.
        map->set("subnet-id",
                 Element::create(static_cast<int>(env.subnet_id_)));
    }

    // Create and insert a reselecting entry.
    uint32_t host_subnet_id = SUBNET_ID_UNUSED;
    if (reselected && !both_global) {
        ConstSubnet4Ptr subnet = CfgMgr::instance().getCurrentCfg()->
            getCfgSubnets4()->getBySubnetId(original_subnet_id);
        if (!subnet) {
            isc_throw(Unexpected, "no original subnet " << original_subnet_id);
        }
        host_subnet_id =
            ((subnet && subnet->getReservationsGlobal()) ?
             SUBNET_ID_GLOBAL : original_subnet_id);

        // Create.
        HostPtr host(new Host(&env.id_[0], env.id_.size(), type,
                              host_subnet_id, SUBNET_ID_UNUSED,
                              IOAddress::IPV4_ZERO_ADDRESS()));

        // Add reselect in the user-context and reset it.
        host->setContext(map);
        map = Element::createMap();

        // Negative entry.
        host->setNegative(true);

        // Insert it.
        if (!cache) {
            return;
        }
        static_cast<void>(cache->insert(host, true));

        ostringstream msg;
        msg << "subnet-id := " << env.subnet_id_;
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_ACCESS_CACHE_INSERT)
            .arg(host->toText())
            .arg(msg.str());
    }

    // Return if the subnet is null. Note in this case both_global
    // is always false.
    if (env.subnet_id_ == SUBNET_ID_UNUSED) {
        return;
    }

    // Build a host entry to cache radius attributes from OK_RC answer.
    ConstSubnet4Ptr subnet = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets4()->getBySubnetId(env.subnet_id_);
    if (!subnet) {
        isc_throw(Unexpected, "no subnet " << env.subnet_id_);
    }
    host_subnet_id =
        ((subnet && subnet->getReservationsGlobal()) ?
         SUBNET_ID_GLOBAL : env.subnet_id_);
    HostPtr host(new Host(&env.id_[0], env.id_.size(), type,
                          host_subnet_id, SUBNET_ID_UNUSED, addr4));

    // Save received attributes.
    if (recv_attrs) {
        map->set("radius", recv_attrs->toElement());
    }
    host->setContext(map);

    if (addr4.isV4Zero()) {
        // The entry has no reservation nor hostname so mark it as negative.
        host->setNegative(true);
    }

    // Insert entry.
    if (!cache) {
        return;
    }
    cache->insert(host, true);

    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_ACCESS_CACHE_INSERT)
        .arg(host->toText())
        .arg(recv_attrs ? recv_attrs->toText() : "");

    // Pass the subnet to the server code.
    if (query) {
        CalloutHandlePtr callout_handle = getCalloutHandle(query);
        callout_handle->setContext("subnet4", subnet);
    }
}

void
RadiusAccess::terminate4(RadiusAuthEnv env, int result,
                         AttributesPtr recv_attrs) {
    Pkt4Ptr query;
    bool drop = false;
    try {
        terminate4Internal(env, result, recv_attrs, query, drop);
    } catch (const std::exception& ex) {
        // Unexpected error.
        LOG_ERROR(radius_logger, RADIUS_ACCESS_TERMINATE_ERROR)
            .arg(ex.what());
        drop = true;
    } catch (...) {
        // Unexpected unknown error.
        LOG_ERROR(radius_logger, RADIUS_ACCESS_TERMINATE_ERROR)
            .arg("unknown error");
        drop = true;
    }
    if (!query) {
        return;
    }
    if (drop) {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_ACCESS_DROP_PARKED_QUERY)
            .arg(query->getLabel());
        HooksManager::drop("subnet4_select", query);
    } else {
        ostringstream msg;
        if (env.subnet_id_ == SUBNET_ID_UNUSED) {
            msg << "no subnet";
        } else {
            msg << "subnet " << env.subnet_id_;
        }
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_ACCESS_RESUME_PARKED_QUERY)
            .arg(query->getLabel())
            .arg(msg.str());
        HooksManager::unpark("subnet4_select", query);
    }
}

void
RadiusAccess::terminate6Internal(RadiusAuthEnv& env, int result,
                                 AttributesPtr recv_attrs,
                                 Pkt6Ptr& query, bool& drop) {
    RadiusImpl& impl = RadiusImpl::instance();
    MultiThreadingLock lock(impl.auth_->requests6_.mutex_);

    // Get the pending request.
    RadiusAuthPendingRequestPtr<Pkt6Ptr> pending_request =
        impl.auth_->requests6_.get(env.id_);
    if (!pending_request) {
        LOG_ERROR(radius_logger, RADIUS_ACCESS_ORPHAN)
            .arg(toHex(env.id_));
        drop = true;
        return;
    }
    // Outside some unit tests the query is never null.
    query = pending_request->query_;
    impl.auth_->requests6_.remove(env.id_);

    // Process response.
    ConstAttributePtr ip6_address;
    ConstAttributePtr prefix;
    ConstAttributePtr framed_pool;
    ConstAttributePtr class_;
    bool reselected = false;
    bool both_global = false;
    uint32_t original_subnet_id = env.subnet_id_;

    if (result == REJECT_RC) {
        // Create the host with no attributes.
        // Should we saved them for the Class?
        recv_attrs.reset();
        // Reset subnet
        env.subnet_id_ = SUBNET_ID_UNUSED;
        reselected = true;
    } else if (result != OK_RC) {
        // Error case
        LOG_ERROR(radius_logger, RADIUS_ACCESS_ERROR)
            .arg(result)
            .arg(exchangeRCtoText(result));
        // what to do? For now nothing!?
        // drop = true;
        return;
    } else if (recv_attrs) {
        // Pickup interesting things in received attributes.
        ip6_address = recv_attrs->get(PW_FRAMED_IPV6_ADDRESS);
        prefix = recv_attrs->get(PW_DELEGATED_IPV6_PREFIX);
        framed_pool = recv_attrs->get(PW_FRAMED_POOL);
        class_ = recv_attrs->get(PW_CLASS);
        // etc
    }

    // Set pool.
    string cclass;
    if (framed_pool && (framed_pool->getValueType() == PW_TYPE_STRING)) {
        cclass = framed_pool->toString();
        if (query) {
            query->addClass(cclass);
        }
    }

    // Get IPv6 address.
    IOAddress addr6 = IOAddress::IPV6_ZERO_ADDRESS();
    if (ip6_address && (ip6_address->getValueType() == PW_TYPE_IPV6ADDR)) {
        addr6 = ip6_address->toIpv6Addr();
    }

    // Get prefix.
    uint8_t pref_len = 0;
    IOAddress pref_addr = IOAddress::IPV6_ZERO_ADDRESS();
    if (prefix && (prefix->getValueType() == PW_TYPE_IPV6PREFIX)) {
        pref_len = prefix->toIpv6PrefixLen();
        pref_addr = prefix->toIpv6Prefix();
    }

    // Check reselection using pool and client-class.
    if (query && !reselected && !cclass.empty() &&
        impl.reselect_subnet_pool_) {
        reselected = reselectSubnet(query, env.subnet_id_, both_global, cclass);
    }

    // Check reselection using reserved address and range.
    if (query && !reselected && !addr6.isV6Zero() &&
        impl.reselect_subnet_address_) {
        reselected = reselectSubnet(query, env.subnet_id_, both_global, addr6);
    }

    // No reselection using prefix.

    // Get host identifier.
    Host::IdentifierType type = impl.id_type6_;
    CacheHostDataSourcePtr cache = impl.cache_;
    ElementPtr map = Element::createMap();
    if (reselected) {
        // Add subnet-id in user context.
        map->set("subnet-id",
                 Element::create(static_cast<int>(env.subnet_id_)));
    }

    // Create and insert a reselecting entry.
    uint32_t host_subnet_id = SUBNET_ID_UNUSED;
    if (reselected && !both_global) {
        ConstSubnet6Ptr subnet = CfgMgr::instance().getCurrentCfg()->
            getCfgSubnets6()->getBySubnetId(original_subnet_id);
        if (!subnet) {
            isc_throw(Unexpected, "no original subnet " << original_subnet_id);
        }
        host_subnet_id =
            ((subnet && subnet->getReservationsGlobal()) ?
             SUBNET_ID_GLOBAL : original_subnet_id);

        // Create.
        HostPtr host(new Host(&env.id_[0], env.id_.size(), type,
                              SUBNET_ID_UNUSED, host_subnet_id,
                              IOAddress::IPV4_ZERO_ADDRESS()));

        // Add reselect in the user-context and reset it.
        host->setContext(map);
        map = Element::createMap();

        // Negative entry.
        host->setNegative(true);

        // Insert it.
        if (!cache) {
            return;
        }
        static_cast<void>(cache->insert(host, true));

        ostringstream msg;
        msg << "subnet-id := " << env.subnet_id_;
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_ACCESS_CACHE_INSERT)
            .arg(host->toText())
            .arg(msg.str());
    }

    // Return if the subnet is null. Note in this case both_global
    // is always false.
    if (env.subnet_id_ == SUBNET_ID_UNUSED) {
        return;
    }

    // Build a host entry to cache radius attributes from OK_RC answer.
    ConstSubnet6Ptr subnet = CfgMgr::instance().getCurrentCfg()->
        getCfgSubnets6()->getBySubnetId(env.subnet_id_);
    if (!subnet) {
        isc_throw(Unexpected, "no subnet " << env.subnet_id_);
    }
    host_subnet_id =
        ((subnet && subnet->getReservationsGlobal()) ?
         SUBNET_ID_GLOBAL : env.subnet_id_);
    HostPtr host(new Host(&env.id_[0], env.id_.size(), type,
                          SUBNET_ID_UNUSED, host_subnet_id,
                          IOAddress::IPV4_ZERO_ADDRESS()));

    // Save received attributes.
    if (recv_attrs) {
        map->set("radius", recv_attrs->toElement());
    }
    host->setContext(map);

    // Add IPv6 address.
    bool has_reservation = false;
    if (!addr6.isV6Zero()) {
        try {
            host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, addr6));
            has_reservation = true;
        } catch (...) {
        }
    }

    // Add delegated prefix.
    if (pref_len && !pref_addr.isV6Zero()) {
        try {
            host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_PD, pref_addr,
                                           pref_len));
            has_reservation = true;
        } catch (...) {
        }
    }

    if (!has_reservation) {
        // The entry has no reservation nor hostname so mark it as negative.
        host->setNegative(true);
    }

    // Insert entry.
    if (!cache) {
        return;
    }
    cache->insert(host, true);

    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_ACCESS_CACHE_INSERT)
        .arg(host->toText())
      .arg(recv_attrs ? recv_attrs->toText() : "");

    // Pass the subnet to the server code.
    if (query) {
        CalloutHandlePtr callout_handle = getCalloutHandle(query);
        callout_handle->setContext("subnet6", subnet);
    }
}

void
RadiusAccess::terminate6(RadiusAuthEnv env, int result,
                         AttributesPtr recv_attrs) {
    Pkt6Ptr query;
    bool drop = false;
    try {
        terminate6Internal(env, result, recv_attrs, query, drop);
    } catch (const std::exception& ex) {
        // Unexpected error.
        LOG_ERROR(radius_logger, RADIUS_ACCESS_TERMINATE_ERROR)
            .arg(ex.what());
        drop = true;
    } catch (...) {
        // Unexpected unknown error.
        LOG_ERROR(radius_logger, RADIUS_ACCESS_TERMINATE_ERROR)
            .arg("unknown error");
        drop = true;
    }
    if (!query) {
        return;
    }
    if (drop) {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_ACCESS_DROP_PARKED_QUERY)
            .arg(query->getLabel());
        HooksManager::drop("subnet6_select", query);
    } else {
        ostringstream msg;
        if (env.subnet_id_ == SUBNET_ID_UNUSED) {
            msg << "no subnet";
        } else {
            msg << "subnet " << env.subnet_id_;
        }
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_ACCESS_RESUME_PARKED_QUERY)
            .arg(query->getLabel())
            .arg(msg.str());
        HooksManager::unpark("subnet6_select", query);
    }
}

} // end of namespace isc::radius
} // end of namespace isc
