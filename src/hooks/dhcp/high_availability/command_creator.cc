// Copyright (C) 2018-2024 Internet Systems Consortium, Inc. ("ISC")
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
using namespace std;

namespace isc {
namespace ha {

unordered_set<string> CommandCreator::ha_commands4_ = {
    "list-commands", "status-get",
    "dhcp-disable", "dhcp-enable",
    "ha-reset", "ha-heartbeat",
    "lease4-update", "lease4-del",
    "lease4-get-all", "lease4-get-page",
    "ha-maintenance-notify", "ha-sync-complete-notify"
};

unordered_set<string> CommandCreator::ha_commands6_ = {
    "list-commands", "status-get",
    "dhcp-disable", "dhcp-enable",
    "ha-reset", "ha-heartbeat",
    "lease6-bulk-apply",
    "lease6-update", "lease6-del",
    "lease6-get-all", "lease6-get-page",
    "ha-maintenance-notify", "ha-sync-complete-notify"
};

ConstElementPtr
CommandCreator::createDHCPDisable(const unsigned int origin_id,
                                  const unsigned int max_period,
                                  const HAServerType& server_type) {
    ElementPtr args;
    args = Element::createMap();
    args->set("origin-id", Element::create(origin_id));
    // Add for backward compatibility with Kea 2.4.0 and earlier.
    args->set("origin", Element::create("ha-partner"));
    // max-period is optional. A value of 0 means that it is not specified.
    if (max_period > 0) {
        args->set("max-period", Element::create(static_cast<long int>(max_period)));
    }
    ConstElementPtr command = config::createCommand("dhcp-disable", args);
    insertService(command, server_type);
    return (command);
}

ConstElementPtr
CommandCreator::createDHCPEnable(const unsigned int origin_id,
                                 const HAServerType& server_type) {
    ElementPtr args;
    args = Element::createMap();
    args->set("origin-id", Element::create(origin_id));
    // Add for backward compatibility with Kea 2.4.0 and earlier.
    args->set("origin", Element::create("ha-partner"));
    ConstElementPtr command = config::createCommand("dhcp-enable", args);
    insertService(command, server_type);
    return (command);
}

ConstElementPtr
CommandCreator::createHAReset(const std::string& server_name,
                              const HAServerType& server_type) {
    auto args = Element::createMap();
    args->set("server-name", Element::create(server_name));
    ConstElementPtr command = config::createCommand("ha-reset", args);
    insertService(command, server_type);
    return (command);
}

ConstElementPtr
CommandCreator::createHeartbeat(const std::string& server_name,
                                const HAServerType& server_type) {
    auto args = Element::createMap();
    args->set("server-name", Element::create(server_name));
    ConstElementPtr command = config::createCommand("ha-heartbeat", args);
    insertService(command, server_type);
    return (command);
}

ConstElementPtr
CommandCreator::createLease4Update(const Lease4& lease4) {
    ElementPtr lease_as_json = lease4.toElement();
    insertLeaseExpireTime(lease_as_json);
    lease_as_json->set("force-create", Element::create(true));
    lease_as_json->set("origin", Element::create("ha-partner"));
    ConstElementPtr command = config::createCommand("lease4-update", lease_as_json);
    insertService(command, HAServerType::DHCPv4);
    return (command);
}

ConstElementPtr
CommandCreator::createLease4Delete(const Lease4& lease4) {
    ElementPtr lease_as_json = lease4.toElement();
    insertLeaseExpireTime(lease_as_json);
    lease_as_json->set("origin", Element::create("ha-partner"));
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
CommandCreator::createLease6BulkApply(const Lease6CollectionPtr& leases,
                                      const Lease6CollectionPtr& deleted_leases) {
    ElementPtr leases_list = Element::createList();
    ElementPtr deleted_leases_list = Element::createList();
    for (auto const& lease : *deleted_leases) {
        ElementPtr lease_as_json = lease->toElement();
        insertLeaseExpireTime(lease_as_json);
        // If the deleted lease is in the released state it means that it
        // should be preserved in the database. It is treated as released
        // but can be re-allocated to the same client later (lease affinity).
        // Such a lease should be updated by the partner rather than deleted.
        if (lease->state_ == Lease6::STATE_RELEASED) {
            leases_list->add(lease_as_json);
        } else {
            deleted_leases_list->add(lease_as_json);
        }
    }

    for (auto const& lease : *leases) {
        ElementPtr lease_as_json = lease->toElement();
        insertLeaseExpireTime(lease_as_json);
        leases_list->add(lease_as_json);
    }

    ElementPtr args = Element::createMap();
    args->set("deleted-leases", deleted_leases_list);
    args->set("leases", leases_list);
    args->set("origin", Element::create("ha-partner"));

    ConstElementPtr command = config::createCommand("lease6-bulk-apply", args);
    insertService(command, HAServerType::DHCPv6);
    return (command);
}

ConstElementPtr
CommandCreator::createLease6BulkApply(LeaseUpdateBacklog& leases) {
    ElementPtr deleted_leases_list = Element::createList();
    ElementPtr leases_list = Element::createList();

    LeaseUpdateBacklog::OpType op_type;
    Lease6Ptr lease;
    while ((lease = boost::dynamic_pointer_cast<Lease6>(leases.pop(op_type)))) {
        ElementPtr lease_as_json = lease->toElement();
        insertLeaseExpireTime(lease_as_json);
        if (op_type == LeaseUpdateBacklog::DELETE) {
            deleted_leases_list->add(lease_as_json);
        } else {
            leases_list->add(lease_as_json);
        }
    }

    ElementPtr args = Element::createMap();
    args->set("deleted-leases", deleted_leases_list);
    args->set("leases", leases_list);
    args->set("origin", Element::create("ha-partner"));

    ConstElementPtr command = config::createCommand("lease6-bulk-apply", args);
    insertService(command, HAServerType::DHCPv6);
    return (command);
}

ConstElementPtr
CommandCreator::createLease6Update(const Lease6& lease6) {
    ElementPtr lease_as_json = lease6.toElement();
    insertLeaseExpireTime(lease_as_json);
    lease_as_json->set("force-create", Element::create(true));
    lease_as_json->set("origin", Element::create("ha-partner"));
    ConstElementPtr command = config::createCommand("lease6-update", lease_as_json);
    insertService(command, HAServerType::DHCPv6);
    return (command);
}

ConstElementPtr
CommandCreator::createLease6Delete(const Lease6& lease6) {
    ElementPtr lease_as_json = lease6.toElement();
    insertLeaseExpireTime(lease_as_json);
    lease_as_json->set("origin", Element::create("ha-partner"));
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

ConstElementPtr
CommandCreator::createMaintenanceNotify(const std::string& server_name,
                                        const bool cancel,
                                        const HAServerType& server_type) {
    auto args = Element::createMap();
    args->set("server-name", Element::create(server_name));
    args->set("cancel", Element::create(cancel));
    auto command = config::createCommand("ha-maintenance-notify", args);
    insertService(command, server_type);
    return (command);
}

ConstElementPtr
CommandCreator::createSyncCompleteNotify(const unsigned int origin_id,
                                         const std::string& server_name,
                                         const HAServerType& server_type) {
    auto args = Element::createMap();
    args->set("server-name", Element::create(server_name));
    args->set("origin-id", Element::create(origin_id));
    // Add for backward compatibility with Kea 2.5.5 to Kea 2.5.7.
    // The origin parameter was introduced for this command in Kea 2.5.5 but
    // renamed to origin-id to be consistent with the origin-id used in
    // dhcp-enable and dhcp-disable commands starting from Kea 2.5.8.
    args->set("origin", Element::create(origin_id));
    auto command = config::createCommand("ha-sync-complete-notify", args);
    insertService(command, server_type);
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
    const string service_name = (server_type == HAServerType::DHCPv4 ? "dhcp4" : "dhcp6");
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
