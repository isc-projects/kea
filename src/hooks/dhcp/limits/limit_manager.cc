// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <dhcp/classify.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/srv_config.h>
#include <dhcpsrv/subnet_id.h>
#include <limits/configuration.h>
#include <limits/limit_manager.h>
#include <util/dhcp_space.h>

#include <string>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;

using namespace std;

namespace isc {
namespace limits {

LimitManager&
LimitManager::instance() {
    static LimitManager instance;
    return (instance);
}

void
LimitManager::clear() {
    clocked_in_times_by_class_.clear();
    clocked_in_times_by_subnet_id_.clear();
}

void
LimitManager::initialize(SrvConfigPtr const& config) {
    // Reset any packet accounting that had transpired so far.
    clear();

    // Parse the configuration to get the limits of interest.
    parse(config);
}

void
LimitManager::addClientClassesToLeaseContext(ClientClasses const& classes, LeasePtr const& lease) {
    // The ConstElementPtr - ElementPtr division forces the copies below. Changes to the lease's
    // user context are not expected so shallow copy is fine as it would have been to reuse the
    // original user context. Feel free to get rid of the copying. Preferable to not resort to the
    // undefined behavior that is const-cast + writing data to the memory freshly made mutable.

    // Get a mutable user context.
    ConstElementPtr user_context_source(lease->getContext());
    ElementPtr user_context;
    if (user_context_source) {
        user_context = copy(user_context_source, 0);
    } else {
        user_context = Element::createMap();
    }

    // Get a mutable ISC element.
    ConstElementPtr isc_source(user_context->get("ISC"));
    ElementPtr isc;
    if (isc_source) {
        isc = copy(isc_source, 0);
    } else {
        isc = Element::createMap();
    }
    user_context->set("ISC", isc);

    // Set the new client classes. Old ones are discarded.
    isc->set("client-classes", classes.toElement());

    // Set the modified user context in the lease.
    lease->setContext(user_context);
}

void
LimitManager::parse(SrvConfigPtr const& config) {
    // Parse the configuration to get the limits of interest.
    address_limit_configuration_.parse(config);
    prefix_limit_configuration_.parse(config);
    rate_limit_configuration_.parse(config);
}

template <>
ElementPtr
LimitManager::clientClassLimitsToElement<DHCPv4>(SubClassRelationContainer const& classes,
                                                 Lease::Type const& /* lease_type */) {
    ElementPtr result(Element::createList());

    for (auto const& c : classes) {
        auto const& class_def = isc::dhcp::CfgMgr::instance().getCurrentCfg()->getClientClassDictionary()->findClass(c.class_def_);
        if (!class_def) {
            continue;
        }

        auto const& limit_cfg = address_limit_configuration_.parseUserContext(class_def->getContext());
        if (limit_cfg) {
            int64_t const limit_candidate(limit_cfg->intValue());
            checkForLimitBoundaries<LeaseLimit>(limit_candidate);
            // Get the limit.
            LeaseLimit const limit(limit_candidate);

            ElementPtr element(Element::createMap());
            element->set("name", Element::create(c.class_));
            element->set("address-limit", Element::create(limit));
            result->add(element);
        }
    }

    return (result);
}

template <>
ElementPtr
LimitManager::clientClassLimitsToElement<DHCPv6>(SubClassRelationContainer const& classes,
                                                 Lease::Type const& lease_type) {
    ElementPtr result(Element::createList());

    auto get_configuration = [&]() -> Configuration<LeaseLimit>& {
        if (lease_type == Lease::TYPE_PD) {
            return (prefix_limit_configuration_);
        } else {
            return (address_limit_configuration_);
        }
    };

    auto& config = get_configuration();

    for (auto const& c : classes) {
        auto const& class_def = isc::dhcp::CfgMgr::instance().getCurrentCfg()->getClientClassDictionary()->findClass(c.class_def_);
        if (!class_def) {
            continue;
        }

        auto& limit_cfg = config.parseUserContext(class_def->getContext());
        if (limit_cfg) {
            int64_t const limit_candidate(limit_cfg->intValue());
            checkForLimitBoundaries<LeaseLimit>(limit_candidate);
            // Get the limit.
            LeaseLimit const limit(limit_candidate);

            ElementPtr element(Element::createMap());
            element->set("name", Element::create(c.class_));
            element->set(config.key(), Element::create(limit));
            result->add(element);
        }
    }

    return (result);
}

template <>
ElementPtr
LimitManager::subnetLimitToElement<DHCPv4>(SubnetID const subnet_id,
                                           Lease::Type const& /* lease_type */) {
    ElementPtr result(Element::createMap());

    auto const& subnet_cfg = isc::dhcp::CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getBySubnetId(subnet_id);
    if (subnet_cfg) {
        auto const& limit_cfg = address_limit_configuration_.parseUserContext(subnet_cfg->getContext());
        if (limit_cfg) {
            int64_t const limit_candidate(limit_cfg->intValue());
            checkForLimitBoundaries<LeaseLimit>(limit_candidate);
            // Get the limit.
            LeaseLimit const limit(limit_candidate);

            result->set("id", Element::create(subnet_id));
            result->set("address-limit", Element::create(limit));
        }
    }

    return (result);
}

template <>
ElementPtr
LimitManager::subnetLimitToElement<DHCPv6>(SubnetID const subnet_id,
                                           Lease::Type const& lease_type) {
    ElementPtr result(Element::createMap());

    std::string limit_name;
    auto get_configuration = [&]() -> Configuration<LeaseLimit>& {
        if (lease_type == Lease::TYPE_PD) {
            limit_name = std::string("prefix-limit");
            return (prefix_limit_configuration_);
        } else {
            limit_name = std::string("address-limit");
            return (address_limit_configuration_);
        }
    };

    auto& config = get_configuration();

    auto const& subnet_cfg = isc::dhcp::CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getBySubnetId(subnet_id);
    if (subnet_cfg) {
        auto const& limit_cfg = config.parseUserContext(subnet_cfg->getContext());
        if (limit_cfg) {
            int64_t const limit_candidate(limit_cfg->intValue());
            checkForLimitBoundaries<LeaseLimit>(limit_candidate);
            // Get the limit.
            LeaseLimit const limit(limit_candidate);

            result->set("id", Element::create(subnet_id));
            result->set(limit_name, Element::create(limit));
        }
    }

    return (result);
}

template <>
ConstElementPtr
LimitManager::subnetRateLimit<DHCPv4>(SubnetID const subnet_id) {
    ConstElementPtr limit;

    auto const& subnet_cfg = isc::dhcp::CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()->getBySubnetId(subnet_id);
    if (subnet_cfg) {
        limit = rate_limit_configuration_.parseUserContext(subnet_cfg->getContext());
    }

    return (limit);
}

template <>
ConstElementPtr
LimitManager::subnetRateLimit<DHCPv6>(SubnetID const subnet_id) {
    ConstElementPtr limit;

    auto const& subnet_cfg = isc::dhcp::CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()->getBySubnetId(subnet_id);
    if (subnet_cfg) {
        limit = rate_limit_configuration_.parseUserContext(subnet_cfg->getContext());
    }

    return (limit);
}

template <>
string
LimitManager::checkLeaseLimits<DHCPv4>(ConstElementPtr const& context) const {
    return (LeaseMgrFactory::instance().checkLimits4(context));
}

template <>
string
LimitManager::checkLeaseLimits<DHCPv6>(ConstElementPtr const& context) const {
    return (LeaseMgrFactory::instance().checkLimits6(context));
}

template <>
void
LimitManager::recountClassLeases<DHCPv4>() const {
    if (isc::dhcp::LeaseMgrFactory::instance().getType() == "memfile") {
        isc::dhcp::LeaseMgrFactory::instance().recountClassLeases4();
    }
}

template <>
void
LimitManager::recountClassLeases<DHCPv6>() const {
    if (isc::dhcp::LeaseMgrFactory::instance().getType() == "memfile") {
        isc::dhcp::LeaseMgrFactory::instance().recountClassLeases6();
    }
}

}  // namespace limits
}  // namespace isc
