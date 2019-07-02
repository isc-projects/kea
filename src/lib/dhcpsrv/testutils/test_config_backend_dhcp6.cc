// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <database/database_connection.h>
#include <test_config_backend_dhcp6.h>

using namespace isc::data;
using namespace isc::db;

namespace isc {
namespace dhcp {
namespace test {

bool
TestConfigBackendDHCPv6::registerBackendType(ConfigBackendDHCPv6Mgr& mgr,
                                             const std::string& db_type) {
    return(mgr.registerBackendFactory(db_type,
                [](const db::DatabaseConnection::ParameterMap& params)
                -> dhcp::ConfigBackendDHCPv6Ptr {
                return (TestConfigBackendDHCPv6Ptr(new TestConfigBackendDHCPv6(params)));
            })
    );
}

void
TestConfigBackendDHCPv6::unregisterBackendType(ConfigBackendDHCPv6Mgr& mgr,
                                               const std::string& db_type) {
    mgr.unregisterBackendFactory(db_type);
}

Subnet6Ptr
TestConfigBackendDHCPv6::getSubnet6(const db::ServerSelector& /* server_selector */,
                                    const std::string& subnet_prefix) const{
    const auto& index = subnets_.get<SubnetPrefixIndexTag>();
    auto subnet_it = index.find(subnet_prefix);
    return ((subnet_it != index.cend()) ? (*subnet_it) : Subnet6Ptr());
}

Subnet6Ptr
TestConfigBackendDHCPv6::getSubnet6(const db::ServerSelector& /* server_selector */,
                                    const SubnetID& subnet_id) const {
    const auto& index = subnets_.get<SubnetSubnetIdIndexTag>();
    auto subnet_it = index.find(subnet_id);
    return ((subnet_it != index.cend()) ? (*subnet_it) : Subnet6Ptr());
}

Subnet6Collection
TestConfigBackendDHCPv6::getAllSubnets6(const db::ServerSelector& server_selector) const {
    auto tags = server_selector.getTags();
    Subnet6Collection subnets;
    for (auto subnet : subnets_) {
        bool got = false;
        for (auto tag : tags) {
            if (subnet->hasServerTag(ServerTag(tag))) {
                subnets.push_back(subnet);
                got = true;
                break;
            }
        }
        if (got) {
            continue;
        }
        if (subnet->hasAllServerTag()) {
            subnets.push_back(subnet);
        }
    }
    return (subnets);
}

Subnet6Collection
TestConfigBackendDHCPv6::getModifiedSubnets6(const db::ServerSelector& /* server_selector */,
                                             const boost::posix_time::ptime& modification_time) const {
    const auto& index = subnets_.get<SubnetModificationTimeIndexTag>();
    Subnet6Collection subnets;
    auto lb = index.lower_bound(modification_time);
    for (auto subnet = lb; subnet != index.end(); ++subnet) {
        subnets.push_back(*subnet);
    }
    return (subnets);
}

Subnet6Collection
TestConfigBackendDHCPv6::getSharedNetworkSubnets6(const db::ServerSelector& /* server_selector */,
                                                  const std::string& shared_network_name) const {
    Subnet6Collection subnets;

    // Subnet collection does not include the index by shared network name.
    // We need to iterate over the subnets and pick those that are associated
    // with a shared network.
    for (auto subnet = subnets_.begin(); subnet != subnets_.end();
         ++subnet) {
        // The subnet can be associated with a shared network instance or
        // it may just point to the shared network name. The former is
        // the case when the subnet belongs to the server configuration.
        // The latter is the case when the subnet is fetched from the
        // database.
        SharedNetwork6Ptr network;
        (*subnet)->getSharedNetwork(network);
        if (((network && (network->getName() == shared_network_name)) ||
             ((*subnet)->getSharedNetworkName() == shared_network_name))) {
            subnets.push_back(*subnet);
        }
    }
    return (subnets);
}

SharedNetwork6Ptr
TestConfigBackendDHCPv6::getSharedNetwork6(const db::ServerSelector& /* server_selector */,
                                           const std::string& name) const {
    const auto& index = shared_networks_.get<SharedNetworkNameIndexTag>();
    auto network_it = index.find(name);
    return ((network_it != index.cend()) ? (*network_it) : SharedNetwork6Ptr());
}

SharedNetwork6Collection
TestConfigBackendDHCPv6::getAllSharedNetworks6(const db::ServerSelector& server_selector) const{
    auto tags = server_selector.getTags();
    SharedNetwork6Collection shared_networks;
    for (auto shared_network : shared_networks_) {
        bool got = false;
        for (auto tag : tags) {
            if (shared_network->hasServerTag(ServerTag(tag))) {
                shared_networks.push_back(shared_network);
                got = true;
                break;
            }
        }
        if (got) {
            continue;
        }
        if (shared_network->hasAllServerTag()) {
            shared_networks.push_back(shared_network);
        }
    }
    return (shared_networks);
}

SharedNetwork6Collection
TestConfigBackendDHCPv6::getModifiedSharedNetworks6(const db::ServerSelector& /* server_selector */,
                                                    const boost::posix_time::ptime& modification_time) const {
    const auto& index = shared_networks_.get<SharedNetworkModificationTimeIndexTag>();
    SharedNetwork6Collection shared_networks;
    auto lb = index.lower_bound(modification_time);
    for (auto shared_network = lb; shared_network != index.end(); ++shared_network) {
        shared_networks.push_back(*shared_network);
    }
    return (shared_networks);
}

OptionDefinitionPtr
TestConfigBackendDHCPv6::getOptionDef6(const db::ServerSelector& server_selector,
                                       const uint16_t code,
                                       const std::string& space) const {
    auto tags = server_selector.getTags();
    auto candidate = OptionDefinitionPtr();
    const auto& index = option_defs_.get<1>();
    auto option_def_it_pair = index.equal_range(code);

    for (auto option_def_it = option_def_it_pair.first;
         option_def_it != option_def_it_pair.second;
         ++option_def_it) {
        if ((*option_def_it)->getOptionSpaceName() == space) {
            for (auto tag : tags) {
                if ((*option_def_it)->hasServerTag(ServerTag(tag))) {
                    return (*option_def_it);
                }
            }
            if ((*option_def_it)->hasAllServerTag()) {
                candidate = *option_def_it;
            }
        }
    }
    return (candidate);
}

OptionDefContainer
TestConfigBackendDHCPv6::getAllOptionDefs6(const db::ServerSelector& server_selector) const {
    auto tags = server_selector.getTags();
    OptionDefContainer option_defs;
    for (auto option_def : option_defs_) {
        bool got = false;
        for (auto tag : tags) {
            if (option_def->hasServerTag(ServerTag(tag))) {
                option_defs.push_back(option_def);
                got = true;
                break;
            }
        }
        if (got) {
            continue;
        }
        if (option_def->hasAllServerTag()) {
            option_defs.push_back(option_def);
        }
    }
    return (option_defs);
}

OptionDefContainer
TestConfigBackendDHCPv6::getModifiedOptionDefs6(const db::ServerSelector& server_selector,
                                                const boost::posix_time::ptime& modification_time) const {
    auto tags = server_selector.getTags();
    OptionDefContainer option_defs;
    const auto& index = option_defs_.get<3>();
    auto lb = index.lower_bound(modification_time);
    for (auto option_def = lb; option_def != index.end(); ++option_def) {
        bool got = false;
        for (auto tag : tags) {
            if ((*option_def)->hasServerTag(ServerTag(tag))) {
                option_defs.push_back(*option_def);
                got = true;
                break;
            }
        }
        if (got) {
            continue;
        }
        if ((*option_def)->hasAllServerTag()) {
            option_defs.push_back(*option_def);
        }
    }
    return (option_defs);
}

OptionDescriptorPtr
TestConfigBackendDHCPv6::getOption6(const db::ServerSelector& server_selector,
                                    const uint16_t code,
                                    const std::string& space) const {
    auto tags = server_selector.getTags();
    auto candidate = OptionDescriptorPtr();
    const auto& index = options_.get<1>();
    auto option_it_pair = index.equal_range(code);

    for (auto option_it = option_it_pair.first; option_it != option_it_pair.second;
         ++option_it) {
        if (option_it->space_name_ == space) {
            for (auto tag : tags) {
                if (option_it->hasServerTag(ServerTag(tag))) {
                    return (OptionDescriptorPtr(new OptionDescriptor(*option_it)));
                }
            }
            if (option_it->hasAllServerTag()) {
                candidate = OptionDescriptorPtr(new OptionDescriptor(*option_it));
            }
        }
    }

    return (candidate);
}

OptionContainer
TestConfigBackendDHCPv6::getAllOptions6(const db::ServerSelector& server_selector) const {
    auto tags = server_selector.getTags();
    OptionContainer options;
    for (auto option : options_) {
        bool got = false;
        for (auto tag : tags) {
            if (option.hasServerTag(ServerTag(tag))) {
                options.push_back(option);
                got = true;
                break;
            }
        }
        if (got) {
            continue;
        }
        if (option.hasAllServerTag()) {
            options.push_back(option);
        }
    }
    return (options);
}

OptionContainer
TestConfigBackendDHCPv6::getModifiedOptions6(const db::ServerSelector& server_selector,
                                             const boost::posix_time::ptime& modification_time) const {
    auto tags = server_selector.getTags();
    OptionContainer options;
    const auto& index = options_.get<3>();
    auto lb = index.lower_bound(modification_time);
    for (auto option = lb; option != index.end(); ++option) {
        bool got = false;
        for (auto tag : tags) {
            if (option->hasServerTag(ServerTag(tag))) {
                options.push_back(*option);
                got = true;
                break;
            }
        }
        if (got) {
            continue;
        }
        if (option->hasAllServerTag()) {
            options.push_back(*option);
        }
    }
    return (options);
}

StampedValuePtr
TestConfigBackendDHCPv6::getGlobalParameter6(const db::ServerSelector& server_selector,
                                             const std::string& name) const {
    auto tags = server_selector.getTags();
    auto candidate = StampedValuePtr();
    const auto& index = globals_.get<StampedValueNameIndexTag>();
    auto global_range = index.equal_range(name);
    for (auto global_it = global_range.first; global_it != global_range.second;
         ++global_it) {
        for (auto tag : tags) {
            if ((*global_it)->hasServerTag(ServerTag(tag))) {
                return (*global_it);
            }
        }
        if ((*global_it)->hasAllServerTag()) {
            candidate = *global_it;
        }
    }

    return (candidate);
}


StampedValueCollection
TestConfigBackendDHCPv6::getAllGlobalParameters6(const db::ServerSelector& server_selector) const {
    auto tags = server_selector.getTags();
    StampedValueCollection globals;
    for (auto global : globals_) {
        bool got = false;
        for (auto tag : tags) {
            if (global->hasServerTag(ServerTag(tag))) {
                globals.insert(global);
                got = true;
                break;
            }
        }
        if (got) {
            continue;
        }
        if (global->hasAllServerTag()) {
            globals.insert(global);
        }
    }
    return (globals);
}

StampedValueCollection
TestConfigBackendDHCPv6::getModifiedGlobalParameters6(const db::ServerSelector& server_selector,
                                                      const boost::posix_time::ptime& modification_time) const {
    auto tags = server_selector.getTags();
    StampedValueCollection globals;
    const auto& index = globals_.get<StampedValueModificationTimeIndexTag>();
    auto lb = index.lower_bound(modification_time);
    for (auto global = lb; global != index.end(); ++global) {
        bool got = false;
        for (auto tag : tags) {
            if ((*global)->hasServerTag(ServerTag(tag))) {
                globals.insert(*global);
                got = true;
                break;
            }
        }
        if (got) {
            continue;
        }
        if ((*global)->hasAllServerTag()) {
            globals.insert(*global);
        }
    }
    return (globals);
}

AuditEntryCollection
TestConfigBackendDHCPv6::getRecentAuditEntries(const db::ServerSelector&,
                                               const boost::posix_time::ptime&) const {
    return (AuditEntryCollection());
}

ServerCollection
TestConfigBackendDHCPv6::getAllServers6() const {
    return (servers_);
}

ServerPtr
TestConfigBackendDHCPv6::getServer6(const ServerTag& server_tag) const {
    const auto& index = servers_.get<ServerTagIndexTag>();
    auto server_it = index.find(server_tag.get());
    return ((server_it != index.cend()) ? (*server_it) : ServerPtr());
}

void
TestConfigBackendDHCPv6::createUpdateSubnet6(const db::ServerSelector& server_selector,
                                             const Subnet6Ptr& subnet) {
    auto& index = subnets_.get<SubnetSubnetIdIndexTag>();
    auto subnet_it = index.find(subnet->getID());

    if (subnet_it != index.cend()) {
        copyServerTags(*subnet_it, subnet);
        mergeServerTags(subnet, server_selector);
        index.replace(subnet_it, subnet);

    } else {
        mergeServerTags(subnet, server_selector);
        index.insert(subnet);
    }
}

void
TestConfigBackendDHCPv6::createUpdateSharedNetwork6(const db::ServerSelector& server_selector,
                                                    const SharedNetwork6Ptr& shared_network) {
    auto& index = shared_networks_.get<SharedNetworkNameIndexTag>();
    auto network_it = index.find(shared_network->getName());

    if (network_it != index.cend()) {
        copyServerTags(*network_it, shared_network);
        mergeServerTags(shared_network, server_selector);
        index.replace(network_it, shared_network);

    } else {
        mergeServerTags(shared_network, server_selector);
        index.insert(shared_network);
    }
}

void
TestConfigBackendDHCPv6::createUpdateOptionDef6(const db::ServerSelector& server_selector,
                                                const OptionDefinitionPtr& option_def) {
    auto tag = getServerTag(server_selector);
    option_def->setServerTag(tag);

    // Index #1 is by option code.
    auto& index1 = option_defs_.get<1>();
    auto option_def_it_pair1 = index1.equal_range(option_def->getCode());

    for (auto option_def_it = option_def_it_pair1.first;
         option_def_it != option_def_it_pair1.second;
         option_def_it++) {
        auto existing_option_def = *option_def_it;
        if ((existing_option_def->getOptionSpaceName() == option_def->getOptionSpaceName()) &&
            (existing_option_def->hasServerTag(ServerTag(tag)))) {
            index1.replace(option_def_it, option_def);
            return;
        }
    }

    // Index #2 is by option name.
    auto& index2 = option_defs_.get<2>();
    auto option_def_it_pair2 = index2.equal_range(option_def->getName());

    for (auto option_def_it = option_def_it_pair2.first;
         option_def_it != option_def_it_pair2.second;
         option_def_it++) {
        auto existing_option_def = *option_def_it;
        if ((existing_option_def->getOptionSpaceName() == option_def->getOptionSpaceName()) &&
            (existing_option_def->hasServerTag(ServerTag(tag)))) {
            index2.replace(option_def_it, option_def);
            return;
        }
    }

    option_defs_.push_back(option_def);
}

void
TestConfigBackendDHCPv6::createUpdateOption6(const db::ServerSelector& server_selector,
                                             const OptionDescriptorPtr& option) {
    auto tag = getServerTag(server_selector);
    option->setServerTag(tag);

    auto& index = options_.get<1>();
    auto option_it_pair = index.equal_range(option->option_->getType());

    for (auto option_it = option_it_pair.first;
         option_it != option_it_pair.second;
         ++option_it) {
        if ((option_it->space_name_ == option->space_name_) &&
            (option_it->hasServerTag(ServerTag(tag)))) {
            index.replace(option_it, *option);
            return;
        }
    }

    options_.push_back(*option);
}

void
TestConfigBackendDHCPv6::createUpdateOption6(const db::ServerSelector& server_selector,
                                             const std::string& shared_network_name,
                                             const OptionDescriptorPtr& option) {
    auto& index = shared_networks_.get<SharedNetworkNameIndexTag>();
    auto network_it = index.find(shared_network_name);

    if (network_it == index.end()) {
        isc_throw(BadValue, "attempted to create or update option in a non existing "
                  "shared network " << shared_network_name);
    }

    auto shared_network = *network_it;
    if (!shared_network->hasAllServerTag()) {
        bool found = false;
        auto tags = server_selector.getTags();
        for (auto tag : tags) {
            if (shared_network->hasServerTag(ServerTag(tag))) {
                found = true;
                break;
            }
        }
        if (!found) {
            isc_throw(BadValue, "attempted to create or update option in a "
                      "shared network " << shared_network_name
                      << " not present in a selected server");
        }
    }

    shared_network->getCfgOption()->del(option->space_name_, option->option_->getType());
    shared_network->getCfgOption()->add(*option, option->space_name_);
}

void
TestConfigBackendDHCPv6::createUpdateOption6(const db::ServerSelector& server_selector,
                                             const SubnetID& subnet_id,
                                             const OptionDescriptorPtr& option) {
    auto& index = subnets_.get<SubnetSubnetIdIndexTag>();
    auto subnet_it = index.find(subnet_id);

    if (subnet_it == index.cend()) {
        isc_throw(BadValue, "attempted to create or update option in a non existing "
                  "subnet ID " << subnet_id);
    }

    auto subnet = *subnet_it;
    if (!subnet->hasAllServerTag()) {
        bool found = false;
        auto tags = server_selector.getTags();
        for (auto tag : tags) {
            if (subnet->hasServerTag(ServerTag(tag))) {
                found = true;
                break;
            }
        }
        if (!found) {
            isc_throw(BadValue, "attempted to create or update option in a "
                      "subnet ID " << subnet_id
                      << " not present in a selected server");
        }
    }

    subnet->getCfgOption()->del(option->space_name_, option->option_->getType());
    subnet->getCfgOption()->add(*option, option->space_name_);
}

void
TestConfigBackendDHCPv6::createUpdateOption6(const db::ServerSelector& server_selector,
                                             const asiolink::IOAddress& pool_start_address,
                                             const asiolink::IOAddress& pool_end_address,
                                             const OptionDescriptorPtr& option) {
    auto tags = server_selector.getTags();
    auto not_in_tags = false;
    for (auto subnet : subnets_) {
        auto pool = subnet->getPool(Lease::TYPE_NA, pool_start_address);
        if (!pool) {
            continue;
        }
        if (!subnet->hasAllServerTag()) {
            for (auto tag : tags) {
                if (subnet->hasServerTag(ServerTag(tag))) {
                    not_in_tags = true;
                    break;
                }
            }
            if (not_in_tags) {
                continue;
            }
        }

        pool->getCfgOption()->del(option->space_name_, option->option_->getType());
        pool->getCfgOption()->add(*option, option->space_name_);

        return;
    }

    if (!not_in_tags) {
        isc_throw(BadValue, "attempted to create or update option in "
                  "a non existing pool " << pool_start_address
                  << " - " << pool_end_address);
    } else {
        isc_throw(BadValue, "attempted to create or update option in "
                  "a pool " << pool_start_address
                  << " - " << pool_end_address
                  << " not present in a selected server");
    }
}

void
TestConfigBackendDHCPv6::createUpdateOption6(const db::ServerSelector& server_selector,
                                             const asiolink::IOAddress& pd_pool_prefix,
                                             const uint8_t pd_pool_prefix_length,
                                             const OptionDescriptorPtr& option) {
    auto tags = server_selector.getTags();
    auto not_in_tags = false;
    for (auto subnet : subnets_) {
        auto pdpool = subnet->getPool(Lease::TYPE_PD, pd_pool_prefix);
        if (!pdpool) {
            continue;
        }
        if (!subnet->hasAllServerTag()) {
            for (auto tag : tags) {
                if (subnet->hasServerTag(ServerTag(tag))) {
                    not_in_tags = true;
                    break;
                }
            }
            if (not_in_tags) {
                continue;
            }
        }

        pdpool->getCfgOption()->del(option->space_name_, option->option_->getType());
        pdpool->getCfgOption()->add(*option, option->space_name_);

        return;
    }

    if (!not_in_tags) {
        isc_throw(BadValue, "attempted to create or update option in "
                  "a non existing prefix pool " << pd_pool_prefix
                  << "/" << static_cast<unsigned>(pd_pool_prefix_length));
    } else {
        isc_throw(BadValue, "attempted to create or update option in "
                  "a prefix pool " << pd_pool_prefix
                  << "/" << static_cast<unsigned>(pd_pool_prefix_length)
                  << " not present in a selected server");
    }
}

void
TestConfigBackendDHCPv6::createUpdateGlobalParameter6(const db::ServerSelector& server_selector,
                                                      const data::StampedValuePtr& value) {
    auto tag = getServerTag(server_selector);
    value->setServerTag(tag);

    auto& index = globals_.get<StampedValueNameIndexTag>();
    auto global_it_pair = index.equal_range(value->getName());

    for (auto global_it = global_it_pair.first; global_it != global_it_pair.second;
         ++global_it) {
        auto existing_value = *global_it;
        if (existing_value->hasServerTag(ServerTag(tag))) {
            index.replace(global_it, value);
            return;
        }
    }

    index.insert(value);
}

void
TestConfigBackendDHCPv6::createUpdateServer6(const db::ServerPtr& server) {
    auto& index = servers_.get<ServerTagIndexTag>();
    auto server_it = index.find(server->getServerTagAsText());

    if (server_it != index.end()) {
        index.replace(server_it, server);

    } else {
        index.insert(server);
    }
}

uint64_t
TestConfigBackendDHCPv6::deleteSubnet6(const db::ServerSelector& /* server_selector */,
                                       const std::string& subnet_prefix) {
    auto& index = subnets_.get<SubnetPrefixIndexTag>();
    return (index.erase(subnet_prefix));
}

uint64_t
TestConfigBackendDHCPv6::deleteSubnet6(const db::ServerSelector& /* server_selector */,
                                       const SubnetID& subnet_id) {
    auto& index = subnets_.get<SubnetSubnetIdIndexTag>();
    return (index.erase(subnet_id));
}

uint64_t
TestConfigBackendDHCPv6::deleteAllSubnets6(const db::ServerSelector& /* server_selector */) {
    auto subnets_size = subnets_.size();
    subnets_.clear();
    return (subnets_size);
}

uint64_t
TestConfigBackendDHCPv6::deleteSharedNetworkSubnets6(const db::ServerSelector& /* server_selector */,
                                                     const std::string& shared_network_name) {
    uint64_t cnt = 0;
    auto& index = subnets_.get<SubnetRandomAccessIndexTag>();
    for (auto subnet = index.begin(); subnet != index.end(); ) {
        SharedNetwork6Ptr network;
        (*subnet)->getSharedNetwork(network);
        if (network && (network->getName() == shared_network_name)) {
            network->del((*subnet)->getID());
        }

        if ((network && (network->getName() == shared_network_name)) ||
            ((*subnet)->getSharedNetworkName() == shared_network_name)) {
            subnet = index.erase(subnet);
            ++cnt;
        } else {
            ++subnet;
        }
    }
    return (cnt);
}

uint64_t
TestConfigBackendDHCPv6::deleteSharedNetwork6(const db::ServerSelector& /* server_selector */,
                                              const std::string& name) {
    for (auto subnet = subnets_.begin(); subnet != subnets_.end(); ++subnet) {
        if ((*subnet)->getSharedNetworkName() == name) {
            (*subnet)->setSharedNetworkName("");
        }
    }

    auto& index = shared_networks_.get<SharedNetworkNameIndexTag>();
    auto network_it = index.find(name);
    if (network_it != index.end()) {
        (*network_it)->delAll();
    }
    return (index.erase(name));
}

uint64_t
TestConfigBackendDHCPv6::deleteAllSharedNetworks6(const db::ServerSelector& /* server_selector */) {
    auto shared_networks_size = shared_networks_.size();
    shared_networks_.clear();
    return (shared_networks_size);
}

uint64_t
TestConfigBackendDHCPv6::deleteOptionDef6(const db::ServerSelector& server_selector,
                                          const uint16_t code,
                                          const std::string& space) {
    auto tag = getServerTag(server_selector);
    uint64_t erased = 0;
    for (auto option_def_it = option_defs_.begin(); option_def_it != option_defs_.end(); ) {
        if (((*option_def_it)->getCode() == code) &&
            ((*option_def_it)->getOptionSpaceName() == space) &&
            ((*option_def_it)->hasServerTag(ServerTag(tag)))) {
            option_def_it = option_defs_.erase(option_def_it);
            ++erased;
        } else {
            ++option_def_it;
        }
    }
    return (erased);
}

uint64_t
TestConfigBackendDHCPv6::deleteAllOptionDefs6(const db::ServerSelector& server_selector) {
    auto tag = getServerTag(server_selector);
    uint64_t erased = 0;
    for (auto option_def_it = option_defs_.begin(); option_def_it != option_defs_.end(); ) {
        if ((*option_def_it)->hasServerTag(ServerTag(tag))) {
            option_def_it = option_defs_.erase(option_def_it);
            ++erased;
        } else {
            ++option_def_it;
        }
    }
    return (erased);
}

uint64_t
TestConfigBackendDHCPv6::deleteOption6(const db::ServerSelector& server_selector,
                                       const uint16_t code,
                                       const std::string& space) {
    auto tag = getServerTag(server_selector);
    uint64_t erased = 0;
    for (auto option_it = options_.begin(); option_it != options_.end(); ) {
        if ((option_it->option_->getType() == code) &&
            (option_it->space_name_ == space) &&
            (option_it->hasServerTag(ServerTag(tag)))) {
            option_it = options_.erase(option_it);
            ++erased;
        } else {
            ++option_it;
        }
    }
    return (erased);
}

uint64_t
TestConfigBackendDHCPv6::deleteOption6(const db::ServerSelector& /* server_selector */,
                                       const std::string& shared_network_name,
                                       const uint16_t code,
                                       const std::string& space) {
    auto& index = shared_networks_.get<SharedNetworkNameIndexTag>();
    auto network_it = index.find(shared_network_name);

    if (network_it != index.end()) {
        auto shared_network = *network_it;
        return (shared_network->getCfgOption()->del(space, code));

    } else {
        isc_throw(BadValue, "attempted to delete an option in a non existing "
                  "shared network " << shared_network_name);
    }
}

uint64_t
TestConfigBackendDHCPv6::deleteOption6(const db::ServerSelector& /* server_selector */,
                                       const SubnetID& subnet_id,
                                       const uint16_t code,
                                       const std::string& space) {
    auto& index = subnets_.get<SubnetSubnetIdIndexTag>();
    auto subnet_it = index.find(subnet_id);

    if (subnet_it != index.cend()) {
        auto subnet = *subnet_it;
        return (subnet->getCfgOption()->del(space, code));

    } else {
        isc_throw(BadValue, "attempted to delete an option in a non existing "
                  "subnet ID " << subnet_id);
    }
}

uint64_t
TestConfigBackendDHCPv6::deleteOption6(const db::ServerSelector& /* server_selector */,
                                       const asiolink::IOAddress& pool_start_address,
                                       const asiolink::IOAddress& pool_end_address,
                                       const uint16_t code,
                                       const std::string& space) {
    for (auto subnet = subnets_.begin(); subnet != subnets_.end(); ++subnet) {
        auto pool = (*subnet)->getPool(Lease::TYPE_NA, pool_start_address);
        if (pool) {
            return (pool->getCfgOption()->del(space, code));
        }
    }

    isc_throw(BadValue, "attempted to delete an option in a non existing "
              "pool " << pool_start_address << " - " << pool_end_address);
}

uint64_t
TestConfigBackendDHCPv6::deleteOption6(const db::ServerSelector& /* server_selector */,
                                       const asiolink::IOAddress& pd_pool_prefix,
                                       const uint8_t pd_pool_prefix_length,
                                       const uint16_t code,
                                       const std::string& space) {
    for (auto subnet = subnets_.begin(); subnet != subnets_.end(); ++subnet) {
        auto pdpool = (*subnet)->getPool(Lease::TYPE_PD, pd_pool_prefix);
        if (pdpool) {
            return (pdpool->getCfgOption()->del(space, code));
        }
    }

    isc_throw(BadValue, "attempted to delete an option in a non existing "
              "pd pool " << pd_pool_prefix << "/"
              << static_cast<unsigned>(pd_pool_prefix_length));
}

uint64_t
TestConfigBackendDHCPv6::deleteGlobalParameter6(const db::ServerSelector& server_selector,
                                                const std::string& name) {
    auto tag = getServerTag(server_selector);
    auto& index = globals_.get<StampedValueNameIndexTag>();
    auto global_it_pair = index.equal_range(name);

    for (auto global_it = global_it_pair.first; global_it != global_it_pair.second;
         ++global_it) {
        auto value = *global_it;
        if (value->hasServerTag(ServerTag(tag))) {
            index.erase(global_it);
            return (1);
        }
    }
    return (0);
}

uint64_t
TestConfigBackendDHCPv6::deleteAllGlobalParameters6(const db::ServerSelector& server_selector) {
    auto tag = getServerTag(server_selector);
    uint64_t cnt = 0;
    for (auto global_it = globals_.begin(); global_it != globals_.end(); ) {
        auto value = *global_it;
        if (value->hasServerTag(ServerTag(tag))) {
            global_it = globals_.erase(global_it);
            cnt++;
        } else {
            ++global_it;
        }
    }
    return (cnt);
}

uint64_t
TestConfigBackendDHCPv6::deleteServer6(const ServerTag& server_tag) {
    auto& index = servers_.get<ServerTagIndexTag>();
    return (index.erase(server_tag.get()));
}

uint64_t
TestConfigBackendDHCPv6::deleteAllServers6() {
    auto servers_size = servers_.size();
    servers_.clear();
    return (servers_size);
}


} // namespace test
} // namespace dhcp
} // namespace isc
