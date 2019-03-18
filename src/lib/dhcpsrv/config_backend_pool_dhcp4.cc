// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/config_backend_pool_dhcp4.h>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;

namespace isc {
namespace dhcp {

Subnet4Ptr
ConfigBackendPoolDHCPv4::getSubnet4(const BackendSelector& backend_selector,
                                    const ServerSelector& server_selector,
                                    const std::string& subnet_prefix) const {
    Subnet4Ptr subnet;
    getPropertyPtrConst<Subnet4Ptr, const std::string&>
        (&ConfigBackendDHCPv4::getSubnet4, backend_selector, server_selector,
         subnet, subnet_prefix);
    return (subnet);
}

Subnet4Ptr
ConfigBackendPoolDHCPv4::getSubnet4(const BackendSelector& backend_selector,
                                    const ServerSelector& server_selector,
                                    const SubnetID& subnet_id) const {
    Subnet4Ptr subnet;
    getPropertyPtrConst<Subnet4Ptr, const SubnetID&>
        (&ConfigBackendDHCPv4::getSubnet4, backend_selector, server_selector,
         subnet, subnet_id);
    return (subnet);
}

Subnet4Collection
ConfigBackendPoolDHCPv4::getAllSubnets4(const BackendSelector& backend_selector,
                                        const ServerSelector& server_selector) const {
    Subnet4Collection subnets;
    getAllPropertiesConst<Subnet4Collection>
        (&ConfigBackendDHCPv4::getAllSubnets4, backend_selector, server_selector,
         subnets);
    return (subnets);
}

Subnet4Collection
ConfigBackendPoolDHCPv4::getModifiedSubnets4(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const boost::posix_time::ptime& modification_time) const {
    Subnet4Collection subnets;
    getMultiplePropertiesConst<Subnet4Collection, const boost::posix_time::ptime&>
        (&ConfigBackendDHCPv4::getModifiedSubnets4, backend_selector, server_selector,
         subnets, modification_time);
    return (subnets);
}

Subnet4Collection
ConfigBackendPoolDHCPv4::getSharedNetworkSubnets4(const db::BackendSelector& backend_selector,
                                                  const db::ServerSelector& server_selector,
                                                  const std::string& shared_network_name) const {
    Subnet4Collection subnets;
    getMultiplePropertiesConst<Subnet4Collection, const std::string&>
        (&ConfigBackendDHCPv4::getSharedNetworkSubnets4, backend_selector, server_selector,
         subnets, shared_network_name);
    return (subnets);
}

SharedNetwork4Ptr
ConfigBackendPoolDHCPv4::getSharedNetwork4(const BackendSelector& backend_selector,
                                           const ServerSelector& server_selector,
                                           const std::string& name) const {
    SharedNetwork4Ptr shared_network;
    getPropertyPtrConst<SharedNetwork4Ptr, const std::string&>
        (&ConfigBackendDHCPv4::getSharedNetwork4, backend_selector, server_selector,
         shared_network, name);
    return (shared_network);
}

SharedNetwork4Collection
ConfigBackendPoolDHCPv4::getAllSharedNetworks4(const BackendSelector& backend_selector,
                                               const ServerSelector& server_selector) const {
    SharedNetwork4Collection shared_networks;
    getAllPropertiesConst<SharedNetwork4Collection>
        (&ConfigBackendDHCPv4::getAllSharedNetworks4, backend_selector, server_selector,
         shared_networks);
    return (shared_networks);
}

SharedNetwork4Collection
ConfigBackendPoolDHCPv4::
getModifiedSharedNetworks4(const BackendSelector& backend_selector,
                           const ServerSelector& server_selector,
                           const boost::posix_time::ptime& modification_time) const {
    SharedNetwork4Collection shared_networks;
    getMultiplePropertiesConst<SharedNetwork4Collection, const boost::posix_time::ptime&>
        (&ConfigBackendDHCPv4::getModifiedSharedNetworks4, backend_selector, server_selector,
         shared_networks, modification_time);
    return (shared_networks);
}

OptionDefinitionPtr
ConfigBackendPoolDHCPv4::getOptionDef4(const BackendSelector& backend_selector,
                                       const ServerSelector& server_selector,
                                       const uint16_t code,
                                       const std::string& space) const {
    OptionDefinitionPtr option_def;
    getPropertyPtrConst<OptionDefinitionPtr, uint16_t, const std::string&>
        (&ConfigBackendDHCPv4::getOptionDef4, backend_selector, server_selector,
         option_def, code, space);
    return (option_def);
}

OptionDefContainer
ConfigBackendPoolDHCPv4::getAllOptionDefs4(const BackendSelector& backend_selector,
                                           const ServerSelector& server_selector) const {
    OptionDefContainer option_defs;
    getAllPropertiesConst<OptionDefContainer>
        (&ConfigBackendDHCPv4::getAllOptionDefs4, backend_selector, server_selector,
         option_defs);
    return (option_defs);
}

OptionDefContainer
ConfigBackendPoolDHCPv4::getModifiedOptionDefs4(const BackendSelector& backend_selector,
                                                const ServerSelector& server_selector,
                                                const boost::posix_time::ptime& modification_time) const {
    OptionDefContainer option_defs;
    getMultiplePropertiesConst<OptionDefContainer, const boost::posix_time::ptime&>
        (&ConfigBackendDHCPv4::getModifiedOptionDefs4, backend_selector, server_selector,
         option_defs, modification_time);
    return (option_defs);
}

OptionDescriptorPtr
ConfigBackendPoolDHCPv4::getOption4(const BackendSelector& backend_selector,
                                    const ServerSelector& server_selector,
                                    const uint16_t code,
                                    const std::string& space) const {
    OptionDescriptorPtr option;
    getPropertyPtrConst<OptionDescriptorPtr, uint16_t, const std::string&>
        (&ConfigBackendDHCPv4::getOption4, backend_selector, server_selector,
         option, code, space);
    return (option);
}

OptionContainer
ConfigBackendPoolDHCPv4::getAllOptions4(const BackendSelector& backend_selector,
                                        const ServerSelector& server_selector) const {
    OptionContainer options;
    getAllPropertiesConst<OptionContainer>
        (&ConfigBackendDHCPv4::getAllOptions4, backend_selector, server_selector,
         options);
    return (options);
}

OptionContainer
ConfigBackendPoolDHCPv4::getModifiedOptions4(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const boost::posix_time::ptime& modification_time) const {
    OptionContainer options;
    getMultiplePropertiesConst<OptionContainer, const boost::posix_time::ptime&>
        (&ConfigBackendDHCPv4::getModifiedOptions4, backend_selector, server_selector,
         options, modification_time);
    return (options);
}

StampedValuePtr
ConfigBackendPoolDHCPv4::getGlobalParameter4(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const std::string& name) const {
    StampedValuePtr parameter;
    getPropertyPtrConst<StampedValuePtr, const std::string&>
        (&ConfigBackendDHCPv4::getGlobalParameter4, backend_selector,
          server_selector, parameter, name);
     return (parameter);
}

StampedValueCollection
ConfigBackendPoolDHCPv4::getAllGlobalParameters4(const BackendSelector& backend_selector,
                                                 const ServerSelector& server_selector) const {
    StampedValueCollection parameters;
    getAllPropertiesConst<StampedValueCollection>
        (&ConfigBackendDHCPv4::getAllGlobalParameters4, backend_selector,
         server_selector, parameters);
    return (parameters);
}

StampedValueCollection
ConfigBackendPoolDHCPv4::
getModifiedGlobalParameters4(const db::BackendSelector& backend_selector,
                             const db::ServerSelector& server_selector,
                             const boost::posix_time::ptime& modification_time) const {
    StampedValueCollection parameters;
    getMultiplePropertiesConst<StampedValueCollection, const boost::posix_time::ptime&>
        (&ConfigBackendDHCPv4::getModifiedGlobalParameters4, backend_selector,
         server_selector, parameters, modification_time);
    return (parameters);
}

AuditEntryCollection
ConfigBackendPoolDHCPv4::
getRecentAuditEntries(const db::BackendSelector& backend_selector,
                      const db::ServerSelector& server_selector,
                      const boost::posix_time::ptime& modification_time) const {
    AuditEntryCollection audit_entries;
    getMultiplePropertiesConst<AuditEntryCollection, const boost::posix_time::ptime&>
        (&ConfigBackendDHCPv4::getRecentAuditEntries, backend_selector,
         server_selector, audit_entries, modification_time);
    return (audit_entries);
}

void
ConfigBackendPoolDHCPv4::createUpdateSubnet4(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const Subnet4Ptr& subnet) {
    createUpdateDeleteProperty<void, const Subnet4Ptr&>
        (&ConfigBackendDHCPv4::createUpdateSubnet4, backend_selector,
         server_selector, subnet);
}

void
ConfigBackendPoolDHCPv4::createUpdateSharedNetwork4(const BackendSelector& backend_selector,
                                                    const ServerSelector& server_selector,
                                                    const SharedNetwork4Ptr& shared_network) {
    createUpdateDeleteProperty<void, const SharedNetwork4Ptr&>
        (&ConfigBackendDHCPv4::createUpdateSharedNetwork4, backend_selector,
         server_selector, shared_network);
}

void
ConfigBackendPoolDHCPv4::createUpdateOptionDef4(const BackendSelector& backend_selector,
                                                const ServerSelector& server_selector,
                                                const OptionDefinitionPtr& option_def) {
    createUpdateDeleteProperty<void, const OptionDefinitionPtr&>
        (&ConfigBackendDHCPv4::createUpdateOptionDef4, backend_selector,
         server_selector, option_def);
}

void
ConfigBackendPoolDHCPv4::createUpdateOption4(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const OptionDescriptorPtr& option) {
    createUpdateDeleteProperty<void, const OptionDescriptorPtr&>
        (&ConfigBackendDHCPv4::createUpdateOption4, backend_selector,
         server_selector, option);
}

void
ConfigBackendPoolDHCPv4::createUpdateOption4(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const std::string& shared_network_name,
                                             const OptionDescriptorPtr& option) {
    createUpdateDeleteProperty<void, const std::string&, const OptionDescriptorPtr&>
        (&ConfigBackendDHCPv4::createUpdateOption4, backend_selector,
         server_selector, shared_network_name, option);
}


void
ConfigBackendPoolDHCPv4::createUpdateOption4(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const SubnetID& subnet_id,
                                             const OptionDescriptorPtr& option) {
    createUpdateDeleteProperty<void, const SubnetID&, const OptionDescriptorPtr&>
        (&ConfigBackendDHCPv4::createUpdateOption4, backend_selector,
         server_selector, subnet_id, option);
}

void
ConfigBackendPoolDHCPv4::createUpdateOption4(const BackendSelector& backend_selector,
                                             const ServerSelector& server_selector,
                                             const IOAddress& pool_start_address,
                                             const IOAddress& pool_end_address,
                                             const OptionDescriptorPtr& option) {
    createUpdateDeleteProperty<void, const IOAddress&, const IOAddress&,
                               const OptionDescriptorPtr&>
        (&ConfigBackendDHCPv4::createUpdateOption4, backend_selector,
         server_selector, pool_start_address, pool_end_address, option);
}

void
ConfigBackendPoolDHCPv4::createUpdateGlobalParameter4(const BackendSelector& backend_selector,
                                                      const ServerSelector& server_selector,
                                                      const StampedValuePtr& value) {
    createUpdateDeleteProperty<void, const StampedValuePtr&>
        (&ConfigBackendDHCPv4::createUpdateGlobalParameter4, backend_selector,
         server_selector, value);
}

uint64_t
ConfigBackendPoolDHCPv4::deleteSubnet4(const BackendSelector& backend_selector,
                                       const ServerSelector& server_selector,
                                       const std::string& subnet_prefix) {
    return (createUpdateDeleteProperty<uint64_t, const std::string&>
            (&ConfigBackendDHCPv4::deleteSubnet4, backend_selector, server_selector,
             subnet_prefix));
}

uint64_t
ConfigBackendPoolDHCPv4::deleteSubnet4(const BackendSelector& backend_selector,
                                       const ServerSelector& server_selector,
                                       const SubnetID& subnet_id) {
    return (createUpdateDeleteProperty<uint64_t, const SubnetID&>
            (&ConfigBackendDHCPv4::deleteSubnet4, backend_selector, server_selector,
             subnet_id));
}

uint64_t
ConfigBackendPoolDHCPv4::deleteAllSubnets4(const BackendSelector& backend_selector,
                                          const ServerSelector& server_selector) {
    return (createUpdateDeleteProperty<uint64_t>
            (&ConfigBackendDHCPv4::deleteAllSubnets4, backend_selector, server_selector));
}

uint64_t
ConfigBackendPoolDHCPv4::deleteSharedNetworkSubnets4(const db::BackendSelector& backend_selector,
                                                     const db::ServerSelector& server_selector,
                                                     const std::string& shared_network_name) {
    return (createUpdateDeleteProperty<uint64_t, const std::string&>
            (&ConfigBackendDHCPv4::deleteSharedNetworkSubnets4, backend_selector, server_selector,
             shared_network_name));
}

uint64_t
ConfigBackendPoolDHCPv4::deleteSharedNetwork4(const BackendSelector& backend_selector,
                                              const ServerSelector& server_selector,
                                              const std::string& name) {
    return (createUpdateDeleteProperty<uint64_t, const std::string&>
            (&ConfigBackendDHCPv4::deleteSharedNetwork4, backend_selector,
             server_selector, name));
}

uint64_t
ConfigBackendPoolDHCPv4::deleteAllSharedNetworks4(const BackendSelector& backend_selector,
                                                  const ServerSelector& server_selector) {
    return (createUpdateDeleteProperty<uint64_t>
            (&ConfigBackendDHCPv4::deleteAllSharedNetworks4, backend_selector, server_selector));
}

uint64_t
ConfigBackendPoolDHCPv4::deleteOptionDef4(const BackendSelector& backend_selector,
                                          const ServerSelector& server_selector,
                                          const uint16_t code,
                                          const std::string& space) {
    return (createUpdateDeleteProperty<uint64_t, uint16_t, const std::string&>
            (&ConfigBackendDHCPv4::deleteOptionDef4, backend_selector,
             server_selector, code, space));
}

uint64_t
ConfigBackendPoolDHCPv4::deleteAllOptionDefs4(const BackendSelector& backend_selector,
                                              const ServerSelector& server_selector) {
    return (createUpdateDeleteProperty<uint64_t>
            (&ConfigBackendDHCPv4::deleteAllOptionDefs4, backend_selector, server_selector));
}

uint64_t
ConfigBackendPoolDHCPv4::deleteOption4(const BackendSelector& backend_selector,
                                       const ServerSelector& server_selector,
                                       const uint16_t code,
                                       const std::string& space) {
    return (createUpdateDeleteProperty<uint64_t, uint16_t, const std::string&>
            (&ConfigBackendDHCPv4::deleteOption4, backend_selector, server_selector,
             code, space));
}

uint64_t
ConfigBackendPoolDHCPv4::deleteOption4(const BackendSelector& backend_selector,
                                       const ServerSelector& server_selector,
                                       const std::string& shared_network_name,
                                       const uint16_t code,
                                       const std::string& space) {
    return (createUpdateDeleteProperty<uint64_t, const std::string&, uint16_t,
                                       const std::string&>
            (&ConfigBackendDHCPv4::deleteOption4, backend_selector, server_selector,
             shared_network_name, code, space));
}

uint64_t
ConfigBackendPoolDHCPv4::deleteOption4(const BackendSelector& backend_selector,
                                       const ServerSelector& server_selector,
                                       const SubnetID& subnet_id,
                                       const uint16_t code,
                                       const std::string& space) {
    return (createUpdateDeleteProperty<uint64_t, const SubnetID&, uint16_t, const std::string&>
            (&ConfigBackendDHCPv4::deleteOption4, backend_selector, server_selector,
             subnet_id, code, space));
}

uint64_t
ConfigBackendPoolDHCPv4::deleteOption4(const BackendSelector& backend_selector,
                                       const ServerSelector& server_selector,
                                       const asiolink::IOAddress& pool_start_address,
                                       const asiolink::IOAddress& pool_end_address,
                                       const uint16_t code,
                                       const std::string& space) {
    return (createUpdateDeleteProperty<uint64_t, const IOAddress&, const IOAddress&,
                                       uint16_t, const std::string&>
            (&ConfigBackendDHCPv4::deleteOption4, backend_selector, server_selector,
             pool_start_address, pool_end_address, code, space));
}

uint64_t
ConfigBackendPoolDHCPv4::deleteGlobalParameter4(const BackendSelector& backend_selector,
                                                const ServerSelector& server_selector,
                                                const std::string& name) {
    return (createUpdateDeleteProperty<uint64_t, const std::string&>
            (&ConfigBackendDHCPv4::deleteGlobalParameter4, backend_selector,
             server_selector, name));
}

uint64_t
ConfigBackendPoolDHCPv4::deleteAllGlobalParameters4(const BackendSelector& backend_selector,
                                                    const ServerSelector& server_selector) {
    return (createUpdateDeleteProperty<uint64_t>
            (&ConfigBackendDHCPv4::deleteAllGlobalParameters4, backend_selector,
             server_selector));
}


} // end of namespace isc::dhcp
} // end of namespace isc
