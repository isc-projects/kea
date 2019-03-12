// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <database/database_connection.h>
#include <test_config_backend_dhcp4.h>
#include <list>

using namespace isc::data;
using namespace isc::db;

namespace isc {
namespace dhcp {
namespace test {

bool
TestConfigBackendDHCPv4::registerBackendType(ConfigBackendDHCPv4Mgr& mgr,
                                             const std::string& db_type) {
    return(mgr.registerBackendFactory(db_type,
                [](const db::DatabaseConnection::ParameterMap& params)
                -> dhcp::ConfigBackendDHCPv4Ptr {
                return (TestConfigBackendDHCPv4Ptr(new TestConfigBackendDHCPv4(params)));
            })
    );
}

void
TestConfigBackendDHCPv4::unregisterBackendType(ConfigBackendDHCPv4Mgr& mgr,
                                               const std::string& db_type) {
    mgr.unregisterBackendFactory(db_type);
}

Subnet4Ptr
TestConfigBackendDHCPv4::getSubnet4(const db::ServerSelector& /* server_selector */,
                                    const std::string& subnet_prefix) const{
    const auto& index = subnets_.get<SubnetPrefixIndexTag>();
    auto subnet_it = index.find(subnet_prefix);
    return ((subnet_it != index.cend()) ? (*subnet_it) : Subnet4Ptr());
}

Subnet4Ptr
TestConfigBackendDHCPv4::getSubnet4(const db::ServerSelector& /* server_selector */,
                                    const SubnetID& subnet_id) const {
    const auto& index = subnets_.get<SubnetSubnetIdIndexTag>();
    auto subnet_it = index.find(subnet_id);
    return ((subnet_it != index.cend()) ? (*subnet_it) : Subnet4Ptr());
}

Subnet4Collection
TestConfigBackendDHCPv4::getAllSubnets4(const db::ServerSelector& /* server_selector */) const {
    return (subnets_);
}

Subnet4Collection
TestConfigBackendDHCPv4::getModifiedSubnets4(const db::ServerSelector& /* server_selector */,
                                             const boost::posix_time::ptime& modification_time) const {
    const auto& index = subnets_.get<SubnetModificationTimeIndexTag>();
    Subnet4Collection subnets;
    auto lb = index.lower_bound(modification_time);
    for (auto subnet = lb; subnet != index.end(); ++subnet) {
        subnets.push_back(*subnet);
    }
    return (subnets);
}

Subnet4Collection
TestConfigBackendDHCPv4::getSharedNetworkSubnets4(const db::ServerSelector& /* server_selector */,
                                                  const std::string& shared_network_name) const {
    Subnet4Collection subnets;

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
        SharedNetwork4Ptr network;
        (*subnet)->getSharedNetwork(network);
        if (((network && (network->getName() == shared_network_name)) ||
             ((*subnet)->getSharedNetworkName() == shared_network_name))) {
            subnets.push_back(*subnet);
        }
    }
    return (subnets);
}

SharedNetwork4Ptr
TestConfigBackendDHCPv4::getSharedNetwork4(const db::ServerSelector& /* server_selector */,
                                           const std::string& name) const {
    const auto& index = shared_networks_.get<SharedNetworkNameIndexTag>();
    auto network_it = index.find(name);
    return ((network_it != index.cend()) ? (*network_it) : SharedNetwork4Ptr());
}

SharedNetwork4Collection
TestConfigBackendDHCPv4::getAllSharedNetworks4(const db::ServerSelector& /* server_selector */) const{
    return (shared_networks_);
}

SharedNetwork4Collection
TestConfigBackendDHCPv4::getModifiedSharedNetworks4(const db::ServerSelector& /* server_selector */,
                                                    const boost::posix_time::ptime& modification_time) const {
    const auto& index = shared_networks_.get<SharedNetworkModificationTimeIndexTag>();
    SharedNetwork4Collection shared_networks;
    auto lb = index.lower_bound(modification_time);
    for (auto shared_network = lb; shared_network != index.end(); ++shared_network) {
        shared_networks.push_back(*shared_network);
    }
    return (shared_networks);
}

OptionDefinitionPtr
TestConfigBackendDHCPv4::getOptionDef4(const db::ServerSelector& /* server_selector */,
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
TestConfigBackendDHCPv4::getAllOptionDefs4(const db::ServerSelector& /* server_selector */) const {
    return (option_defs_);
}

OptionDefContainer
TestConfigBackendDHCPv4::getModifiedOptionDefs4(const db::ServerSelector& /* server_selector */,
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
TestConfigBackendDHCPv4::getOption4(const db::ServerSelector& /* server_selector */,
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
TestConfigBackendDHCPv4::getAllOptions4(const db::ServerSelector& /* server_selector */) const {
    return (options_);
}

OptionContainer
TestConfigBackendDHCPv4::getModifiedOptions4(const db::ServerSelector& /* server_selector */,
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
TestConfigBackendDHCPv4::getGlobalParameter4(const db::ServerSelector& /* server_selector */,
                                             const std::string& name) const {
    const auto& index = globals_.get<StampedValueNameIndexTag>();
    auto global_it = index.find(name);
    return ((global_it != index.cend()) ? (*global_it) : StampedValuePtr());
}


StampedValueCollection
TestConfigBackendDHCPv4::getAllGlobalParameters4(const db::ServerSelector& /* server_selector */) const {
    return (globals_);
}

StampedValueCollection
TestConfigBackendDHCPv4::getModifiedGlobalParameters4(const db::ServerSelector& /* server_selector */,
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
TestConfigBackendDHCPv4::getRecentAuditEntries4(const db::ServerSelector&,
                                                const boost::posix_time::ptime&) const {
    return (AuditEntryCollection());
}

void
TestConfigBackendDHCPv4::createUpdateSubnet4(const db::ServerSelector& /* server_selector */,
                                             const Subnet4Ptr& subnet) {
    auto& index = subnets_.get<SubnetSubnetIdIndexTag>();
    auto subnet_it = index.find(subnet->getID());

    if (subnet_it != index.cend()) {
        index.replace(subnet_it, subnet);

    } else {
        index.insert(subnet);
    }
}

void
TestConfigBackendDHCPv4::createUpdateSharedNetwork4(const db::ServerSelector& /* server_selector */,
                                                    const SharedNetwork4Ptr& shared_network) {
    auto& index = shared_networks_.get<SharedNetworkNameIndexTag>();
    auto network_it = index.find(shared_network->getName());

    if (network_it != index.cend()) {
        index.replace(network_it, shared_network);

    } else {
        index.insert(shared_network);
    }
}

void
TestConfigBackendDHCPv4::createUpdateOptionDef4(const db::ServerSelector& /* server_selector */,
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
TestConfigBackendDHCPv4::createUpdateOption4(const db::ServerSelector& /* server_selector */,
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
TestConfigBackendDHCPv4::createUpdateOption4(const db::ServerSelector& /* server_selector */,
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
TestConfigBackendDHCPv4::createUpdateOption4(const db::ServerSelector& /* server_selector */,
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
TestConfigBackendDHCPv4::createUpdateOption4(const db::ServerSelector& /* server_selector */,
                                             const asiolink::IOAddress& pool_start_address,
                                             const asiolink::IOAddress& pool_end_address,
                                             const OptionDescriptorPtr& option) {
    for (auto subnet = subnets_.begin(); subnet != subnets_.end(); ++subnet) {
        auto pool = (*subnet)->getPool(Lease::TYPE_V4, pool_start_address);
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
TestConfigBackendDHCPv4::createUpdateGlobalParameter4(const db::ServerSelector& /* server_selector */,
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
TestConfigBackendDHCPv4::deleteSubnet4(const db::ServerSelector& /* server_selector */,
                                       const std::string& subnet_prefix) {
    auto& index = subnets_.get<SubnetPrefixIndexTag>();
    return (index.erase(subnet_prefix));
}

uint64_t
TestConfigBackendDHCPv4::deleteSubnet4(const db::ServerSelector& /* server_selector */,
                                       const SubnetID& subnet_id) {
    auto& index = subnets_.get<SubnetSubnetIdIndexTag>();
    return (index.erase(subnet_id));
}

uint64_t
TestConfigBackendDHCPv4::deleteAllSubnets4(const db::ServerSelector& /* server_selector */) {
    auto subnets_size = subnets_.size();
    subnets_.clear();
    return (subnets_size);
}

uint64_t
TestConfigBackendDHCPv4::deleteSharedNetworkSubnets4(const db::ServerSelector& /* server_selector */,
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
TestConfigBackendDHCPv4::deleteSharedNetwork4(const db::ServerSelector& /* server_selector */,
                                              const std::string& name) {
    auto& index = shared_networks_.get<SharedNetworkNameIndexTag>();
    auto network_it = index.find(name);
    if (network_it != index.end()) {
        (*network_it)->delAll();
    }
    return (index.erase(name));
}

uint64_t
TestConfigBackendDHCPv4::deleteAllSharedNetworks4(const db::ServerSelector& /* server_selector */) {
    auto shared_networks_size = shared_networks_.size();
    shared_networks_.clear();
    return (shared_networks_size);
}

uint64_t
TestConfigBackendDHCPv4::deleteOptionDef4(const db::ServerSelector& /* server_selector */,
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
TestConfigBackendDHCPv4::deleteAllOptionDefs4(const db::ServerSelector& /* server_selector */) {
    auto option_defs_size = option_defs_.size();
    option_defs_.clear();
    return (option_defs_size);
}

uint64_t
TestConfigBackendDHCPv4::deleteOption4(const db::ServerSelector& /* server_selector */,
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
TestConfigBackendDHCPv4::deleteOption4(const db::ServerSelector& /* server_selector */,
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
TestConfigBackendDHCPv4::deleteOption4(const db::ServerSelector& /* server_selector */,
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
TestConfigBackendDHCPv4::deleteOption4(const db::ServerSelector& /* server_selector */,
                                       const asiolink::IOAddress& pool_start_address,
                                       const asiolink::IOAddress& pool_end_address,
                                       const uint16_t code,
                                       const std::string& space) {
    for (auto subnet = subnets_.begin(); subnet != subnets_.end(); ++subnet) {
        auto pool = (*subnet)->getPool(Lease::TYPE_V4, pool_start_address);
        if (pool) {
            return (pool->getCfgOption()->del(space, code));
        }
    }

    isc_throw(BadValue, "attempted to delete an option in a non existing "
              "pool " << pool_start_address << " - " << pool_end_address);
}

uint64_t
TestConfigBackendDHCPv4::deleteGlobalParameter4(const db::ServerSelector& /* server_selector */,
                                                const std::string& name) {
    auto& index = globals_.get<StampedValueNameIndexTag>();
    return (index.erase(name));
}

uint64_t
TestConfigBackendDHCPv4::deleteAllGlobalParameters4(const db::ServerSelector& /* server_selector */) {
    auto globals_size = globals_.size();
    globals_.clear();
    return (globals_size);
}

} // namespace test
} // namespace dhcp
} // namespace isc
