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
TestConfigBackendDHCPv6::getAllSubnets6(const db::ServerSelector& /* server_selector */) const {
    return (subnets_);
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
TestConfigBackendDHCPv6::getAllSharedNetworks6(const db::ServerSelector& /* server_selector */) const{
    return (shared_networks_);
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
TestConfigBackendDHCPv6::getOptionDef6(const db::ServerSelector& /* server_selector */,
                                       const uint16_t code,
                                       const std::string& space) const {
    const auto& index = option_defs_.get<1>();
    auto option_def_it_pair = index.equal_range(code);

    for (auto option_def_it = option_def_it_pair.first;
         option_def_it != option_def_it_pair.second;
         ++option_def_it) {
        if ((*option_def_it)->getOptionSpaceName() == space) {
            return (*option_def_it);
        }
    }
    return (OptionDefinitionPtr());
}

OptionDefContainer
TestConfigBackendDHCPv6::getAllOptionDefs6(const db::ServerSelector& /* server_selector */) const {
    return (option_defs_);
}

OptionDefContainer
TestConfigBackendDHCPv6::getModifiedOptionDefs6(const db::ServerSelector& /* server_selector */,
                                                const boost::posix_time::ptime& modification_time) const {
    const auto& index = option_defs_.get<3>();
    OptionDefContainer option_defs;
    auto lb = index.lower_bound(modification_time);
    for (auto option_def = lb; option_def != index.end(); ++option_def) {
        option_defs.push_back(*option_def);
    }
    return (option_defs);
}

OptionDescriptorPtr
TestConfigBackendDHCPv6::getOption6(const db::ServerSelector& /* server_selector */,
                                    const uint16_t code,
                                    const std::string& space) const {
    const auto& index = options_.get<1>();
    auto option_it_pair = index.equal_range(code);

    for (auto option_it = option_it_pair.first; option_it != option_it_pair.second;
         ++option_it) {
        if (option_it->space_name_ == space) {
            return (OptionDescriptorPtr(new OptionDescriptor(*option_it)));
        }
    }

    return (OptionDescriptorPtr());
}

OptionContainer
TestConfigBackendDHCPv6::getAllOptions6(const db::ServerSelector& /* server_selector */) const {
    return (options_);
}

OptionContainer
TestConfigBackendDHCPv6::getModifiedOptions6(const db::ServerSelector& /* server_selector */,
                                             const boost::posix_time::ptime& modification_time) const {
    const auto& index = options_.get<3>();
    OptionContainer options;
    auto lb = index.lower_bound(modification_time);
    for (auto option = lb; option != index.end(); ++option) {
        options.push_back(*option);
    }
    return (options);
}

StampedValuePtr
TestConfigBackendDHCPv6::getGlobalParameter6(const db::ServerSelector& /* server_selector */,
                                             const std::string& name) const {
    const auto& index = globals_.get<StampedValueNameIndexTag>();
    auto global_it = index.find(name);
    return ((global_it != index.cend()) ? (*global_it) : StampedValuePtr());
}


StampedValueCollection
TestConfigBackendDHCPv6::getAllGlobalParameters6(const db::ServerSelector& /* server_selector */) const {
    return (globals_);
}

StampedValueCollection
TestConfigBackendDHCPv6::getModifiedGlobalParameters6(const db::ServerSelector& /* server_selector */,
                                                      const boost::posix_time::ptime& modification_time) const {
    const auto& index = globals_.get<StampedValueModificationTimeIndexTag>();
    StampedValueCollection globals;
    auto lb = index.lower_bound(modification_time);
    for (auto global = lb; global != index.end(); ++global) {
        globals.insert(*global);
    }
    return (globals);
}

AuditEntryCollection
TestConfigBackendDHCPv6::getRecentAuditEntries(const db::ServerSelector&,
                                               const boost::posix_time::ptime&) const {
    return (AuditEntryCollection());
}

void
TestConfigBackendDHCPv6::createUpdateSubnet6(const db::ServerSelector& /* server_selector */,
                                             const Subnet6Ptr& subnet) {
    auto& index = subnets_.get<SubnetSubnetIdIndexTag>();
    auto subnet_it = index.find(subnet->getID());

    if (subnet_it != index.cend()) {
        index.replace(subnet_it, subnet);

    } else {
        index.insert(subnet);
    }
}

void
TestConfigBackendDHCPv6::createUpdateSharedNetwork6(const db::ServerSelector& /* server_selector */,
                                                    const SharedNetwork6Ptr& shared_network) {
    auto& index = shared_networks_.get<SharedNetworkNameIndexTag>();
    auto network_it = index.find(shared_network->getName());

    if (network_it != index.cend()) {
        index.replace(network_it, shared_network);

    } else {
        index.insert(shared_network);
    }
}

void
TestConfigBackendDHCPv6::createUpdateOptionDef6(const db::ServerSelector& /* server_selector */,
                                                const OptionDefinitionPtr& option_def) {
    auto& index = option_defs_.get<1>();
    auto option_def_it = index.find(option_def->getCode());

    if (option_def_it != index.cend()) {
        index.replace(option_def_it, option_def);

    } else {
        index.insert(option_def);
    }
}

void
TestConfigBackendDHCPv6::createUpdateOption6(const db::ServerSelector& /* server_selector */,
                                             const OptionDescriptorPtr& option) {
    auto& index = options_.get<1>();
    auto option_it = index.find(option->option_->getType());

    if (option_it != index.end()) {
        index.replace(option_it, *option);

    } else {
        index.insert(*option);
    }
}

void
TestConfigBackendDHCPv6::createUpdateOption6(const db::ServerSelector& /* server_selector */,
                                             const std::string& shared_network_name,
                                             const OptionDescriptorPtr& option) {
    auto& index = shared_networks_.get<SharedNetworkNameIndexTag>();
    auto network_it = index.find(shared_network_name);

    if (network_it != index.end()) {
        auto shared_network = *network_it;
        shared_network->getCfgOption()->del(option->space_name_, option->option_->getType());
        shared_network->getCfgOption()->add(*option, option->space_name_);

    } else {
        isc_throw(BadValue, "attempted to create or update option in a non existing "
                  "shared network " << shared_network_name);
    }
}

void
TestConfigBackendDHCPv6::createUpdateOption6(const db::ServerSelector& /* server_selector */,
                                             const SubnetID& subnet_id,
                                             const OptionDescriptorPtr& option) {
    auto& index = subnets_.get<SubnetSubnetIdIndexTag>();
    auto subnet_it = index.find(subnet_id);

    if (subnet_it != index.cend()) {
        auto subnet = *subnet_it;
        subnet->getCfgOption()->del(option->space_name_, option->option_->getType());
        subnet->getCfgOption()->add(*option, option->space_name_);

    } else {
        isc_throw(BadValue, "attempted to create or update option in a non existing "
                  "subnet ID " << subnet_id);
    }
}

void
TestConfigBackendDHCPv6::createUpdateOption6(const db::ServerSelector& /* server_selector */,
                                             const asiolink::IOAddress& pool_start_address,
                                             const asiolink::IOAddress& pool_end_address,
                                             const OptionDescriptorPtr& option) {
    for (auto subnet = subnets_.begin(); subnet != subnets_.end(); ++subnet) {
        auto pool = (*subnet)->getPool(Lease::TYPE_NA, pool_start_address);
        if (pool) {
            pool->getCfgOption()->del(option->space_name_, option->option_->getType());
            pool->getCfgOption()->add(*option, option->space_name_);

            return;
        }
    }

    isc_throw(BadValue, "attempted to create or update option in a non existing "
              "pool " << pool_start_address << " - " << pool_end_address);
}

void
TestConfigBackendDHCPv6::createUpdateOption6(const db::ServerSelector& /* server_selector */,
                                             const asiolink::IOAddress& pd_pool_prefix,
                                             const uint8_t pd_pool_prefix_length,
                                             const OptionDescriptorPtr& option) {
    for (auto subnet = subnets_.begin(); subnet != subnets_.end(); ++subnet) {
        auto pdpool = (*subnet)->getPool(Lease::TYPE_PD,pd_pool_prefix);
        if (pdpool) {
            pdpool->getCfgOption()->del(option->space_name_, option->option_->getType());
            pdpool->getCfgOption()->add(*option, option->space_name_);

            return;
        }
    }

    isc_throw(BadValue, "attempted to create or update option in a non existing "
              "pd pool " << pd_pool_prefix << "/"
              << static_cast<unsigned>(pd_pool_prefix_length));
}

void
TestConfigBackendDHCPv6::createUpdateGlobalParameter6(const db::ServerSelector& /* server_selector */,
                                                      const data::StampedValuePtr& value) {
    auto& index = globals_.get<StampedValueNameIndexTag>();
    auto global_it = index.find(value->getName());

    if (global_it != index.end()) {
        index.replace(global_it, value);

    } else {
        index.insert(value);
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
    auto& index = shared_networks_.get<SharedNetworkNameIndexTag>();
    auto network_it = index.find(shared_network_name);
    if (network_it == index.end()) {
        return (cnt);
    }
    for (auto subnet : *(*network_it)->getAllSubnets()) {
        const SubnetID& subnet_id = subnet->getID();
        auto& subnet_index = subnets_.get<SubnetSubnetIdIndexTag>();
        cnt += subnet_index.erase(subnet_id);
    }
    (*network_it)->delAll();
    return (cnt);
}

uint64_t
TestConfigBackendDHCPv6::deleteSharedNetwork6(const db::ServerSelector& /* server_selector */,
                                              const std::string& name) {
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
TestConfigBackendDHCPv6::deleteOptionDef6(const db::ServerSelector& /* server_selector */,
                                          const uint16_t code,
                                          const std::string& space) {
    uint64_t erased = 0;
    for (auto option_def_it = option_defs_.begin(); option_def_it != option_defs_.end();
         ++option_def_it) {
        if (((*option_def_it)->getCode() == code) &&
            ((*option_def_it)->getOptionSpaceName() == space)) {
            option_def_it = option_defs_.erase(option_def_it);
            ++erased;
        }
    }
    return (erased);
}

uint64_t
TestConfigBackendDHCPv6::deleteAllOptionDefs6(const db::ServerSelector& /* server_selector */) {
    auto option_defs_size = option_defs_.size();
    option_defs_.clear();
    return (option_defs_size);
}

uint64_t
TestConfigBackendDHCPv6::deleteOption6(const db::ServerSelector& /* server_selector */,
                                       const uint16_t code,
                                       const std::string& space) {
    uint64_t erased = 0;
    for (auto option_it = options_.begin(); option_it != options_.end();
         ++option_it) {
        if ((option_it->option_->getType() == code) &&
            (option_it->space_name_ == space)) {
            option_it = options_.erase(option_it);
            ++erased;
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
TestConfigBackendDHCPv6::deleteGlobalParameter6(const db::ServerSelector& /* server_selector */,
                                                const std::string& name) {
    auto& index = globals_.get<StampedValueNameIndexTag>();
    return (index.erase(name));
}

uint64_t
TestConfigBackendDHCPv6::deleteAllGlobalParameters6(const db::ServerSelector& /* server_selector */) {
    auto globals_size = globals_.size();
    globals_.clear();
    return (globals_size);
}

} // namespace test
} // namespace dhcp
} // namespace isc
