// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <database/database_connection.h>
#include <test_config_backend_dhcp4.h>

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
                                      const std::string& /* subnet_prefix */) const{
    return (Subnet4Ptr());
}

Subnet4Ptr
TestConfigBackendDHCPv4::getSubnet4(const db::ServerSelector& /* server_selector */,
                                      const SubnetID& /* subnet_id */) const {
    return (Subnet4Ptr());
}

Subnet4Collection
TestConfigBackendDHCPv4::getAllSubnets4(const db::ServerSelector& /* server_selector */) const {
    return(subnets_);
}

Subnet4Collection
TestConfigBackendDHCPv4::getModifiedSubnets4(const db::ServerSelector& /* server_selector */,
                                               const boost::posix_time::ptime& /* modification_time */) const {
    return(subnets_);
}

SharedNetwork4Ptr
TestConfigBackendDHCPv4::getSharedNetwork4(const db::ServerSelector& /* server_selector */,
                                             const std::string& /* name */) const {
    return(SharedNetwork4Ptr());
}

SharedNetwork4Collection
TestConfigBackendDHCPv4::getAllSharedNetworks4(const db::ServerSelector& /* server_selector */) const{
    return(shared_networks_);
}

SharedNetwork4Collection
TestConfigBackendDHCPv4::getModifiedSharedNetworks4(const db::ServerSelector& /* server_selector */,
                                                      const boost::posix_time::ptime& /* modification_time */) const {
    return(shared_networks_);
}

OptionDefinitionPtr
TestConfigBackendDHCPv4::getOptionDef4(const db::ServerSelector& /* server_selector */,
                                         const uint16_t /* code */,
                                         const std::string& /* space */) const {
    return (OptionDefinitionPtr());
}

OptionDefContainer
TestConfigBackendDHCPv4::getAllOptionDefs4(const db::ServerSelector& /* server_selector */) const {
    return (option_defs_);
}

OptionDefContainer
TestConfigBackendDHCPv4::getModifiedOptionDefs4(const db::ServerSelector& /* server_selector */,
                                                  const boost::posix_time::ptime& /* modification_time */) const {
    return (option_defs_);
}

OptionDescriptorPtr
TestConfigBackendDHCPv4::getOption4(const db::ServerSelector& /* server_selector */,
                                      const uint16_t /* code */,
                                      const std::string& /* space */) const {
    return (OptionDescriptorPtr());
}

OptionContainer
TestConfigBackendDHCPv4::getAllOptions4(const db::ServerSelector& /* server_selector */) const {
    return (options_);
}

OptionContainer
TestConfigBackendDHCPv4::getModifiedOptions4(const db::ServerSelector& /* server_selector */,
                                               const boost::posix_time::ptime& /* modification_time */) const {
    return (options_);
}

data::StampedValuePtr
TestConfigBackendDHCPv4::getGlobalParameter4(const db::ServerSelector& /* server_selector */,
                                               const std::string& /* name */) const {
    return(data::StampedValuePtr());
}


data::StampedValueCollection
TestConfigBackendDHCPv4::getAllGlobalParameters4(const db::ServerSelector& /* server_selector */) const {
    return (globals_);
}

data::StampedValueCollection
TestConfigBackendDHCPv4::getModifiedGlobalParameters4(const db::ServerSelector& /* server_selector */,
                                                        const boost::posix_time::ptime& /* modification_time */) const {
    return (globals_);
}

void
TestConfigBackendDHCPv4::createUpdateSubnet4(const db::ServerSelector& /* server_selector */,
                                               const Subnet4Ptr& /* subnet */) {
}

void
TestConfigBackendDHCPv4::createUpdateSharedNetwork4(const db::ServerSelector& /* server_selector */,
                                                      const SharedNetwork4Ptr& /* shared_network */) {
}

void
TestConfigBackendDHCPv4::createUpdateOptionDef4(const db::ServerSelector& /* server_selector */,
                                                  const OptionDefinitionPtr& /* option_def */) {
}

void
TestConfigBackendDHCPv4::createUpdateOption4(const db::ServerSelector& /* server_selector */,
                                               const OptionDescriptorPtr& /* option */) {
}

void
TestConfigBackendDHCPv4::createUpdateOption4(const db::ServerSelector& /* server_selector */,
                                               const std::string& /* shared_network_name */,
                                               const OptionDescriptorPtr& /* option */) {
}

void
TestConfigBackendDHCPv4::createUpdateOption4(const db::ServerSelector& /* server_selector */,
                                               const SubnetID& /* subnet_id */,
                                               const OptionDescriptorPtr& /* option */) {
}

void
TestConfigBackendDHCPv4::createUpdateOption4(const db::ServerSelector& /* server_selector */,
                                               const asiolink::IOAddress& /* pool_start_address */,
                                               const asiolink::IOAddress& /* pool_end_address */,
                                               const OptionDescriptorPtr& /* option */) {
}

void
TestConfigBackendDHCPv4::createUpdateGlobalParameter4(const db::ServerSelector& /* server_selector */,
                                                        const data::StampedValuePtr& /* value */) {
}

uint64_t
TestConfigBackendDHCPv4::deleteSubnet4(const db::ServerSelector& /* server_selector */,
                                         const std::string& /* subnet_prefix */) {
    return (0);
}

uint64_t
TestConfigBackendDHCPv4::deleteSubnet4(const db::ServerSelector& /* server_selector */,
                                         const SubnetID& /* subnet_id */) {
    return (0);
}

uint64_t
TestConfigBackendDHCPv4::deleteAllSubnets4(const db::ServerSelector& /* server_selector */) {
    return (0);
}

uint64_t
TestConfigBackendDHCPv4::deleteSharedNetwork4(const db::ServerSelector& /* server_selector */,
                                                const std::string& /* name */) {
    return (0);
}

uint64_t
TestConfigBackendDHCPv4::deleteAllSharedNetworks4(const db::ServerSelector& /* server_selector */) {
    return (0);
}

uint64_t
TestConfigBackendDHCPv4::deleteOptionDef4(const db::ServerSelector& /* server_selector */,
                                            const uint16_t /* code */,
                                            const std::string& /* space */) {
    return (0);
}

uint64_t
TestConfigBackendDHCPv4::deleteAllOptionDefs4(const db::ServerSelector& /* server_selector */) {
    return (0);
}

uint64_t
TestConfigBackendDHCPv4::deleteOption4(const db::ServerSelector& /* server_selector */,
                                         const uint16_t /* code */,
                                         const std::string& /* space */) {
    return (0);
}

uint64_t
TestConfigBackendDHCPv4::deleteOption4(const db::ServerSelector& /* server_selector */,
                                         const std::string& /* shared_network_name */,
                                         const uint16_t /* code */,
                                         const std::string& /* space */) {
    return (0);
}

uint64_t
TestConfigBackendDHCPv4::deleteOption4(const db::ServerSelector& /* server_selector */,
                                         const SubnetID& /* subnet_id */,
                                         const uint16_t /* code */,
                                         const std::string& /* space */) {
    return (0);
}

uint64_t
TestConfigBackendDHCPv4::deleteOption4(const db::ServerSelector& /* server_selector */,
                                         const asiolink::IOAddress& /* pool_start_address */,
                                         const asiolink::IOAddress& /* pool_end_address */,
                                         const uint16_t /* code */,
                                         const std::string& /* space */) {
    return (0);
}

uint64_t
TestConfigBackendDHCPv4::deleteGlobalParameter4(const db::ServerSelector& /* server_selector */,
                                                  const std::string& /* name */) {
    return (0);
}

uint64_t
TestConfigBackendDHCPv4::deleteAllGlobalParameters4(const db::ServerSelector& /* server_selector */) {
    return (0);
}

} // namespace test
} // namespace dhcp
} // namespace isc
