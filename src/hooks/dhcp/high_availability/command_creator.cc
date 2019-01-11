// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <command_creator.h>
#include <cc/command_interpreter.h>
#include <exceptions/exceptions.h>
#include <boost/pointer_cast.hpp>

using namespace isc::data;
using namespace isc::dhcp;

namespace isc {
namespace ha {

ConstElementPtr
CommandCreator::createDHCPDisable(const unsigned int max_period,
                                  const HAServerType& server_type) {
    ElementPtr args;
    // max-period is optional. A value of 0 means that it is not specified.
    if (max_period > 0) {
        args = Element::createMap();
        args->set("max-period", Element::create(static_cast<long int>(max_period)));
    }
    ConstElementPtr command = config::createCommand("dhcp-disable", args);
    insertService(command, server_type);
    return (command);
}

ConstElementPtr
CommandCreator::createDHCPEnable(const HAServerType& server_type) {
    ConstElementPtr command = config::createCommand("dhcp-enable");
    insertService(command, server_type);
    return (command);
}

ConstElementPtr
CommandCreator::createHeartbeat(const HAServerType& server_type) {
    ConstElementPtr command = config::createCommand("ha-heartbeat");
    insertService(command, server_type);
    return (command);
}

ConstElementPtr
CommandCreator::createLease4Update(const Lease4& lease4) {
    ElementPtr lease_as_json = lease4.toElement();
    insertLeaseExpireTime(lease_as_json);
    lease_as_json->set("force-create", Element::create(true));
    ConstElementPtr command = config::createCommand("lease4-update", lease_as_json);
    insertService(command, HAServerType::DHCPv4);
    return (command);
}

ConstElementPtr
CommandCreator::createLease4Delete(const Lease4& lease4) {
    ElementPtr lease_as_json = lease4.toElement();
    insertLeaseExpireTime(lease_as_json);
    ConstElementPtr command = config::createCommand("lease4-del", lease_as_json);
    insertService(command, HAServerType::DHCPv4);
    return (command);
}

ConstElementPtr
CommandCreator::createLease4GetAll() {
    ConstElementPtr command = config::createCommand("lease4-get-all");
    insertService(command, HAServerType::DHCPv4);
    return (command);
}

ConstElementPtr
CommandCreator::createLease4GetPage(const Lease4Ptr& last_lease4,
                                    const uint32_t limit) {
    // Zero value is not allowed.
    if (limit == 0) {
        isc_throw(BadValue, "limit value for lease4-get-page command must not be 0");
    }

    // Get the last lease returned on the previous page. A null pointer means that
    // we're fetching first page. In that case a keyword "start" is used to indicate
    // that first page should be returned.
    ElementPtr from_element = Element::create(last_lease4 ? last_lease4->addr_.toText() : "start");
    // Set the maximum size of the page.
    ElementPtr limit_element = Element::create(static_cast<long long int>(limit));
    // Put both parameters into arguments map.
    ElementPtr args = Element::createMap();
    args->set("from", from_element);
    args->set("limit", limit_element);

    // Create the command.
    ConstElementPtr command = config::createCommand("lease4-get-page", args);
    insertService(command, HAServerType::DHCPv4);
    return (command);
}

ConstElementPtr
CommandCreator::createLease6Update(const Lease6& lease6) {
    ElementPtr lease_as_json = lease6.toElement();
    insertLeaseExpireTime(lease_as_json);
    lease_as_json->set("force-create", Element::create(true));
    ConstElementPtr command = config::createCommand("lease6-update", lease_as_json);
    insertService(command, HAServerType::DHCPv6);
    return (command);
}

ConstElementPtr
CommandCreator::createLease6Delete(const Lease6& lease6) {
    ElementPtr lease_as_json = lease6.toElement();
    insertLeaseExpireTime(lease_as_json);
    ConstElementPtr command = config::createCommand("lease6-del", lease_as_json);
    insertService(command, HAServerType::DHCPv6);
    return (command);
}

ConstElementPtr
CommandCreator::createLease6GetAll() {
    ConstElementPtr command = config::createCommand("lease6-get-all");
    insertService(command, HAServerType::DHCPv6);
    return (command);
}

ConstElementPtr
CommandCreator::createLease6GetPage(const Lease6Ptr& last_lease6,
                                    const uint32_t limit) {
    // Zero value is not allowed.
    if (limit == 0) {
        isc_throw(BadValue, "limit value for lease6-get-page command must not be 0");
    }

    // Get the last lease returned on the previous page. A null pointer means that
    // we're fetching first page. In that case a keyword "start" is used to indicate
    // that first page should be returned.
    ElementPtr from_element = Element::create(last_lease6 ? last_lease6->addr_.toText() : "start");
    // Set the maximum size of the page.
    ElementPtr limit_element = Element::create(static_cast<long long int>(limit));
    // Put both parameters into arguments map.
    ElementPtr args = Element::createMap();
    args->set("from", from_element);
    args->set("limit", limit_element);

    // Create the command.
    ConstElementPtr command = config::createCommand("lease6-get-page", args);
    insertService(command, HAServerType::DHCPv6);
    return (command);
}

void
CommandCreator::insertLeaseExpireTime(ElementPtr& lease) {
    if ((lease->getType() != Element::map) ||
        (!lease->contains("cltt") || (lease->get("cltt")->getType() != Element::integer) ||
         (!lease->contains("valid-lft") ||
          (lease->get("valid-lft")->getType() != Element::integer)))) {
        isc_throw(Unexpected, "invalid lease format");
    }

    int64_t cltt = lease->get("cltt")->intValue();
    int64_t valid_lifetime = lease->get("valid-lft")->intValue();
    int64_t expire = cltt + valid_lifetime;
    lease->set("expire", Element::create(expire));
    lease->remove("cltt");
}

void
CommandCreator::insertService(ConstElementPtr& command,
                              const HAServerType& server_type) {
    ElementPtr service = Element::createList();
    const std::string service_name = (server_type == HAServerType::DHCPv4 ? "dhcp4" : "dhcp6");
    service->add(Element::create(service_name));

    // We have no better way of setting a new element here than
    // doing const pointer cast. That's another reason why this
    // functionality could be moved to the core code. We don't
    // do it however, because we want to minimize concurrent
    // code changes in the premium and core Kea repos.
    (boost::const_pointer_cast<Element>(command))->set("service", service);
}

} // end of namespace ha
} // end of namespace isc
