// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/config_backend_pool_dhcp6.h>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;

namespace isc {
namespace dhcp {

Subnet6Ptr
ConfigBackendPoolDHCPv6::getSubnet6(const BackendSelector& backend_selector,
                                    const ServerSelector& server_selector,
                                    const std::string& subnet_prefix) const {
    Subnet6Ptr subnet;
    getPropertyPtrConst<Subnet6Ptr, const std::string&>
        (&ConfigBackendDHCPv6::getSubnet6, backend_selector, server_selector,
         subnet, subnet_prefix);
    return (subnet);
}

Subnet6Ptr
ConfigBackendPoolDHCPv6::getSubnet6(const BackendSelector& backend_selector,
                                    const ServerSelector& server_selector,
                                    const SubnetID& subnet_id) const {
    Subnet6Ptr subnet;
    getPropertyPtrConst<Subnet6Ptr, const SubnetID&>
        (&ConfigBackendDHCPv6::getSubnet6, backend_selector, server_selector,
         subnet, subnet_id);
    return (subnet);
}

Subnet6Collection
ConfigBackendPoolDHCPv6::getAllSubnets6(const BackendSelector& backend_selector,
                                        const ServerSelector& server_selector) const {
    Subnet6Collection subnets;
    getAllPropertiesConst<Subnet6Collection>
        (&ConfigBackendDHCPv6::getAllSubnets6, backend_selector, server_selector,
         subnets);
    return (subnets);
}

Subnet6Collection
ConfigBackendPoolDHCPv6::getModifiedSubnets6(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const boost::posix_time::ptime& modification_time) const {
    Subnet6Collection subnets;
    getMultiplePropertiesConst<Subnet6Collection, const boost::posix_time::ptime&>
        (&ConfigBackendDHCPv6::getModifiedSubnets6, backend_selector, server_selector,
         subnets, modification_time);
    return (subnets);
}

Subnet6Collection
ConfigBackendPoolDHCPv6::getSharedNetworkSubnets6(const db::BackendSelector& backend_selector,
                                                  const db::ServerSelector& server_selector,
                                                  const std::string& shared_network_name) const {
    Subnet6Collection subnets;
    getMultiplePropertiesConst<Subnet6Collection, const std::string&>
        (&ConfigBackendDHCPv6::getSharedNetworkSubnets6, backend_selector, server_selector,
         subnets, shared_network_name);
    return (subnets);
}

SharedNetwork6Ptr
ConfigBackendPoolDHCPv6::getSharedNetwork6(const BackendSelector& backend_selector,
                                           const ServerSelector& server_selector,
                                           const std::string& name) const {
    SharedNetwork6Ptr shared_network;
    getPropertyPtrConst<SharedNetwork6Ptr, const std::string&>
        (&ConfigBackendDHCPv6::getSharedNetwork6, backend_selector, server_selector,
         shared_network, name);
    return (shared_network);
}

SharedNetwork6Collection
ConfigBackendPoolDHCPv6::getAllSharedNetworks6(const BackendSelector& backend_selector,
                                               const ServerSelector& server_selector) const {
    SharedNetwork6Collection shared_networks;
    getAllPropertiesConst<SharedNetwork6Collection>
        (&ConfigBackendDHCPv6::getAllSharedNetworks6, backend_selector, server_selector,
         shared_networks);
    return (shared_networks);
}

SharedNetwork6Collection
ConfigBackendPoolDHCPv6::
getModifiedSharedNetworks6(const BackendSelector& backend_selector,
                           const ServerSelector& server_selector,
                           const boost::posix_time::ptime& modification_time) const {
    SharedNetwork6Collection shared_networks;
    getMultiplePropertiesConst<SharedNetwork6Collection, const boost::posix_time::ptime&>
        (&ConfigBackendDHCPv6::getModifiedSharedNetworks6, backend_selector, server_selector,
         shared_networks, modification_time);
    return (shared_networks);
}

OptionDefinitionPtr
ConfigBackendPoolDHCPv6::getOptionDef6(const BackendSelector& backend_selector,
                                       const ServerSelector& server_selector,
                                       const uint16_t code,
                                       const std::string& space) const {
    OptionDefinitionPtr option_def;
    getPropertyPtrConst<OptionDefinitionPtr, uint16_t, const std::string&>
        (&ConfigBackendDHCPv6::getOptionDef6, backend_selector, server_selector,
         option_def, code, space);
    return (option_def);
}

OptionDefContainer
ConfigBackendPoolDHCPv6::getAllOptionDefs6(const BackendSelector& backend_selector,
                                           const ServerSelector& server_selector) const {
    OptionDefContainer option_defs;
    getAllPropertiesConst<OptionDefContainer>
        (&ConfigBackendDHCPv6::getAllOptionDefs6, backend_selector, server_selector,
         option_defs);
    return (option_defs);
}

OptionDefContainer
ConfigBackendPoolDHCPv6::getModifiedOptionDefs6(const BackendSelector& backend_selector,
                                                const ServerSelector& server_selector,
                                                const boost::posix_time::ptime& modification_time) const {
    OptionDefContainer option_defs;
    getMultiplePropertiesConst<OptionDefContainer, const boost::posix_time::ptime&>
        (&ConfigBackendDHCPv6::getModifiedOptionDefs6, backend_selector, server_selector,
         option_defs, modification_time);
    return (option_defs);
}

OptionDescriptorPtr
ConfigBackendPoolDHCPv6::getOption6(const BackendSelector& backend_selector,
                                    const ServerSelector& server_selector,
                                    const uint16_t code,
                                    const std::string& space) const {
    OptionDescriptorPtr option;
    getPropertyPtrConst<OptionDescriptorPtr, uint16_t, const std::string&>
        (&ConfigBackendDHCPv6::getOption6, backend_selector, server_selector,
         option, code, space);
    return (option);
}

OptionContainer
ConfigBackendPoolDHCPv6::getAllOptions6(const BackendSelector& backend_selector,
                                        const ServerSelector& server_selector) const {
    OptionContainer options;
    getAllPropertiesConst<OptionContainer>
        (&ConfigBackendDHCPv6::getAllOptions6, backend_selector, server_selector,
         options);
    return (options);
}

OptionContainer
ConfigBackendPoolDHCPv6::getModifiedOptions6(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const boost::posix_time::ptime& modification_time) const {
    OptionContainer options;
    getMultiplePropertiesConst<OptionContainer, const boost::posix_time::ptime&>
        (&ConfigBackendDHCPv6::getModifiedOptions6, backend_selector, server_selector,
         options, modification_time);
    return (options);
}

StampedValuePtr
ConfigBackendPoolDHCPv6::getGlobalParameter6(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const std::string& name) const {
    StampedValuePtr parameter;
    getPropertyPtrConst<StampedValuePtr, const std::string&>
        (&ConfigBackendDHCPv6::getGlobalParameter6, backend_selector,
          server_selector, parameter, name);
     return (parameter);
}

StampedValueCollection
ConfigBackendPoolDHCPv6::getAllGlobalParameters6(const BackendSelector& backend_selector,
                                                 const ServerSelector& server_selector) const {
    StampedValueCollection parameters;
    getAllPropertiesConst<StampedValueCollection>
        (&ConfigBackendDHCPv6::getAllGlobalParameters6, backend_selector,
         server_selector, parameters);
    return (parameters);
}

StampedValueCollection
ConfigBackendPoolDHCPv6::
getModifiedGlobalParameters6(const db::BackendSelector& backend_selector,
                             const db::ServerSelector& server_selector,
                             const boost::posix_time::ptime& modification_time) const {
    StampedValueCollection parameters;
    getMultiplePropertiesConst<StampedValueCollection, const boost::posix_time::ptime&>
        (&ConfigBackendDHCPv6::getModifiedGlobalParameters6, backend_selector,
         server_selector, parameters, modification_time);
    return (parameters);
}

AuditEntryCollection
ConfigBackendPoolDHCPv6::
getRecentAuditEntries(const db::BackendSelector& backend_selector,
                      const db::ServerSelector& server_selector,
                      const boost::posix_time::ptime& modification_time) const {
    AuditEntryCollection audit_entries;
    getMultiplePropertiesConst<AuditEntryCollection, const boost::posix_time::ptime&>
        (&ConfigBackendDHCPv6::getRecentAuditEntries, backend_selector,
         server_selector, audit_entries, modification_time);
    return (audit_entries);
}

void
ConfigBackendPoolDHCPv6::createUpdateSubnet6(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const Subnet6Ptr& subnet) {
    createUpdateDeleteProperty<void, const Subnet6Ptr&>
        (&ConfigBackendDHCPv6::createUpdateSubnet6, backend_selector,
         server_selector, subnet);
}

void
ConfigBackendPoolDHCPv6::createUpdateSharedNetwork6(const BackendSelector& backend_selector,
                                                    const ServerSelector& server_selector,
                                                    const SharedNetwork6Ptr& shared_network) {
    createUpdateDeleteProperty<void, const SharedNetwork6Ptr&>
        (&ConfigBackendDHCPv6::createUpdateSharedNetwork6, backend_selector,
         server_selector, shared_network);
}

void
ConfigBackendPoolDHCPv6::createUpdateOptionDef6(const BackendSelector& backend_selector,
                                                const ServerSelector& server_selector,
                                                const OptionDefinitionPtr& option_def) {
    createUpdateDeleteProperty<void, const OptionDefinitionPtr&>
        (&ConfigBackendDHCPv6::createUpdateOptionDef6, backend_selector,
         server_selector, option_def);
}

void
ConfigBackendPoolDHCPv6::createUpdateOption6(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const OptionDescriptorPtr& option) {
    createUpdateDeleteProperty<void, const OptionDescriptorPtr&>
        (&ConfigBackendDHCPv6::createUpdateOption6, backend_selector,
         server_selector, option);
}

void
ConfigBackendPoolDHCPv6::createUpdateOption6(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const std::string& shared_network_name,
                                             const OptionDescriptorPtr& option) {
    createUpdateDeleteProperty<void, const std::string&, const OptionDescriptorPtr&>
        (&ConfigBackendDHCPv6::createUpdateOption6, backend_selector,
         server_selector, shared_network_name, option);
}


void
ConfigBackendPoolDHCPv6::createUpdateOption6(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const SubnetID& subnet_id,
                                             const OptionDescriptorPtr& option) {
    createUpdateDeleteProperty<void, const SubnetID&, const OptionDescriptorPtr&>
        (&ConfigBackendDHCPv6::createUpdateOption6, backend_selector,
         server_selector, subnet_id, option);
}

void
ConfigBackendPoolDHCPv6::createUpdateOption6(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const IOAddress& pool_start_address,
                                             const IOAddress& pool_end_address,
                                             const OptionDescriptorPtr& option) {
    createUpdateDeleteProperty<void, const IOAddress&, const IOAddress&,
                               const OptionDescriptorPtr&>
        (&ConfigBackendDHCPv6::createUpdateOption6, backend_selector,
         server_selector, pool_start_address, pool_end_address, option);
}

void
ConfigBackendPoolDHCPv6::createUpdateOption6(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const asiolink::IOAddress& pd_pool_prefix,
                                             const uint8_t pd_pool_prefix_length,
                                             const OptionDescriptorPtr& option) {
    createUpdateDeleteProperty<void, const IOAddress&, const IOAddress&,
                               const OptionDescriptorPtr&>
        (&ConfigBackendDHCPv6::createUpdateOption6, backend_selector,
         server_selector, pd_pool_prefix, pd_pool_prefix_length, option);
}

void
ConfigBackendPoolDHCPv6::createUpdateGlobalParameter6(const BackendSelector& backend_selector,
                                                      const ServerSelector& server_selector,
                                                      const StampedValuePtr& value) {
    createUpdateDeleteProperty<void, const StampedValuePtr&>
        (&ConfigBackendDHCPv6::createUpdateGlobalParameter6, backend_selector,
         server_selector, value);
}

uint64_t
ConfigBackendPoolDHCPv6::deleteSubnet6(const BackendSelector& backend_selector,
                                       const ServerSelector& server_selector,
                                       const std::string& subnet_prefix) {
    return (createUpdateDeleteProperty<uint64_t, const std::string&>
            (&ConfigBackendDHCPv6::deleteSubnet6, backend_selector, server_selector,
             subnet_prefix));
}

uint64_t
ConfigBackendPoolDHCPv6::deleteSubnet6(const BackendSelector& backend_selector,
                                       const ServerSelector& server_selector,
                                       const SubnetID& subnet_id) {
    return (createUpdateDeleteProperty<uint64_t, const SubnetID&>
            (&ConfigBackendDHCPv6::deleteSubnet6, backend_selector, server_selector,
             subnet_id));
}

uint64_t
ConfigBackendPoolDHCPv6::deleteAllSubnets6(const BackendSelector& backend_selector,
                                          const ServerSelector& server_selector) {
    return (createUpdateDeleteProperty<uint64_t>
            (&ConfigBackendDHCPv6::deleteAllSubnets6, backend_selector, server_selector));
}

uint64_t
ConfigBackendPoolDHCPv6::deleteSharedNetworkSubnets6(const db::BackendSelector& backend_selector,
                                                     const db::ServerSelector& server_selector,
                                                     const std::string& shared_network_name) {
    return (createUpdateDeleteProperty<uint64_t, const std::string&>
            (&ConfigBackendDHCPv6::deleteSharedNetworkSubnets6, backend_selector, server_selector,
             shared_network_name));
}

uint64_t
ConfigBackendPoolDHCPv6::deleteSharedNetwork6(const BackendSelector& backend_selector,
                                              const ServerSelector& server_selector,
                                              const std::string& name) {
    return (createUpdateDeleteProperty<uint64_t, const std::string&>
            (&ConfigBackendDHCPv6::deleteSharedNetwork6, backend_selector,
             server_selector, name));
}

uint64_t
ConfigBackendPoolDHCPv6::deleteAllSharedNetworks6(const BackendSelector& backend_selector,
                                                  const ServerSelector& server_selector) {
    return (createUpdateDeleteProperty<uint64_t>
            (&ConfigBackendDHCPv6::deleteAllSharedNetworks6, backend_selector, server_selector));
}

uint64_t
ConfigBackendPoolDHCPv6::deleteOptionDef6(const BackendSelector& backend_selector,
                                          const ServerSelector& server_selector,
                                          const uint16_t code,
                                          const std::string& space) {
    return (createUpdateDeleteProperty<uint64_t, uint16_t, const std::string&>
            (&ConfigBackendDHCPv6::deleteOptionDef6, backend_selector,
             server_selector, code, space));
}

uint64_t
ConfigBackendPoolDHCPv6::deleteAllOptionDefs6(const BackendSelector& backend_selector,
                                              const ServerSelector& server_selector) {
    return (createUpdateDeleteProperty<uint64_t>
            (&ConfigBackendDHCPv6::deleteAllOptionDefs6, backend_selector, server_selector));
}

uint64_t
ConfigBackendPoolDHCPv6::deleteOption6(const BackendSelector& backend_selector,
                                       const ServerSelector& server_selector,
                                       const uint16_t code,
                                       const std::string& space) {
    return (createUpdateDeleteProperty<uint64_t, uint16_t, const std::string&>
            (&ConfigBackendDHCPv6::deleteOption6, backend_selector, server_selector,
             code, space));
}

uint64_t
ConfigBackendPoolDHCPv6::deleteOption6(const BackendSelector& backend_selector,
                                       const ServerSelector& server_selector,
                                       const std::string& shared_network_name,
                                       const uint16_t code,
                                       const std::string& space) {
    return (createUpdateDeleteProperty<uint64_t, const std::string&, uint16_t,
                                       const std::string&>
            (&ConfigBackendDHCPv6::deleteOption6, backend_selector, server_selector,
             shared_network_name, code, space));
}

uint64_t
ConfigBackendPoolDHCPv6::deleteOption6(const BackendSelector& backend_selector,
                                       const ServerSelector& server_selector,
                                       const SubnetID& subnet_id,
                                       const uint16_t code,
                                       const std::string& space) {
    return (createUpdateDeleteProperty<uint64_t, const SubnetID&, uint16_t, const std::string&>
            (&ConfigBackendDHCPv6::deleteOption6, backend_selector, server_selector,
             subnet_id, code, space));
}

uint64_t
ConfigBackendPoolDHCPv6::deleteOption6(const BackendSelector& backend_selector,
                                       const ServerSelector& server_selector,
                                       const asiolink::IOAddress& pool_start_address,
                                       const asiolink::IOAddress& pool_end_address,
                                       const uint16_t code,
                                       const std::string& space) {
    return (createUpdateDeleteProperty<uint64_t, const IOAddress&, const IOAddress&,
                                       uint16_t, const std::string&>
            (&ConfigBackendDHCPv6::deleteOption6, backend_selector, server_selector,
             pool_start_address, pool_end_address, code, space));
}

uint64_t
ConfigBackendPoolDHCPv6::deleteOption6(const BackendSelector& backend_selector,
                                       const ServerSelector& server_selector,
                                       const asiolink::IOAddress& pd_pool_prefix,
                                       const uint8_t pd_pool_prefix_length,
                                       const uint16_t code,
                                       const std::string& space) {
    return (createUpdateDeleteProperty<uint64_t, const IOAddress&, const IOAddress&,
                                       uint16_t, const std::string&>
            (&ConfigBackendDHCPv6::deleteOption6, backend_selector, server_selector,
             pd_pool_prefix, pd_pool_prefix_length, code, space));
}

uint64_t
ConfigBackendPoolDHCPv6::deleteGlobalParameter6(const BackendSelector& backend_selector,
                                                const ServerSelector& server_selector,
                                                const std::string& name) {
    return (createUpdateDeleteProperty<uint64_t, const std::string&>
            (&ConfigBackendDHCPv6::deleteGlobalParameter6, backend_selector,
             server_selector, name));
}

uint64_t
ConfigBackendPoolDHCPv6::deleteAllGlobalParameters6(const BackendSelector& backend_selector,
                                                    const ServerSelector& server_selector) {
    return (createUpdateDeleteProperty<uint64_t>
            (&ConfigBackendDHCPv6::deleteAllGlobalParameters6, backend_selector,
             server_selector));
}


} // end of namespace isc::dhcp
} // end of namespace isc
