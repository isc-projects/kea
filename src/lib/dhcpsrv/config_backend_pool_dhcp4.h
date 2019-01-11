// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CONFIG_BACKEND_POOL_DHCP4_H
#define CONFIG_BACKEND_POOL_DHCP4_H

#include <cc/stamped_value.h>
#include <config_backend/base_config_backend_pool.h>
#include <database/backend_selector.h>
#include <database/server_selector.h>
#include <dhcp/option.h>
#include <dhcp/option_definition.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/config_backend_dhcp4.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/subnet.h>
#include <boost/date_time/posix_time/ptime.hpp>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Implementation of the Configuration Backend Pool for DHCPv4.
class ConfigBackendPoolDHCPv4 : public cb::BaseConfigBackendPool<ConfigBackendDHCPv4> {
public:

    /// @brief Retrieves a single subnet by subnet_prefix.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be retrieved.
    /// @return Pointer to the retrieved subnet or NULL if not found.
    virtual Subnet4Ptr
    getSubnet4(const db::BackendSelector& backend_selector,
               const db::ServerSelector& server_selector,
               const std::string& subnet_prefix) const;

    /// @brief Retrieves a single subnet by subnet identifier.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of a subnet to be retrieved.
    /// @return Pointer to the retrieved subnet or NULL if not found.
    virtual Subnet4Ptr
    getSubnet4(const db::BackendSelector& backend_selector,
               const db::ServerSelector& server_selector,
               const SubnetID& subnet_id) const;

    /// @brief Retrieves all subnets.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @return Collection of subnets or empty collection if no subnet found.
    virtual Subnet4Collection
    getAllSubnets4(const db::BackendSelector& backend_selector,
                   const db::ServerSelector& server_selector) const;

    /// @brief Retrieves subnets modified after specified time.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound subnet modification time.
    /// @return Collection of subnets or empty collection if no subnet found.
    virtual Subnet4Collection
    getModifiedSubnets4(const db::BackendSelector& backend_selector,
                        const db::ServerSelector& server_selector,
                        const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves shared network by name.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param name Name of the shared network to be retrieved.
    /// @return Pointer to the shared network or NULL if not found.
    virtual SharedNetwork4Ptr
    getSharedNetwork4(const db::BackendSelector& backend_selector,
                      const db::ServerSelector& server_selector,
                      const std::string& name) const;

    /// @brief Retrieves all shared networks.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @return Collection of shared network or empty collection if
    /// no shared network found.
    virtual SharedNetwork4Collection
    getAllSharedNetworks4(const db::BackendSelector& backend_selector,
                          const db::ServerSelector& server_selector) const;

    /// @brief Retrieves shared networks modified after specified time.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound shared network modification time.
    /// @return Collection of shared network or empty collection if
    /// no shared network found.
    virtual SharedNetwork4Collection
    getModifiedSharedNetworks4(const db::BackendSelector& backend_selector,
                               const db::ServerSelector& server_selector,
                               const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves single option definition by code and space.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param code Code of the option to be retrieved.
    /// @param space Option space of the option to be retrieved.
    /// @return Pointer to the option definition or NULL if not found.
    virtual OptionDefinitionPtr
    getOptionDef4(const db::BackendSelector& backend_selector,
                  const db::ServerSelector& server_selector,
                  const uint16_t code,
                  const std::string& space) const;

    /// @brief Retrieves all option definitions.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @return Collection of option definitions or empty collection if
    /// no option definition found.
    virtual OptionDefContainer
    getAllOptionDefs4(const db::BackendSelector& backend_selector,
                      const db::ServerSelector& server_selector) const;

    /// @brief Retrieves option definitions modified after specified time.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound option definition modification
    /// time.
    /// @return Collection of option definitions or empty collection if
    /// no option definition found.
    virtual OptionDefContainer
    getModifiedOptionDefs4(const db::BackendSelector& backend_selector,
                           const db::ServerSelector& server_selector,
                           const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves single option by code and space.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param code Option code.
    /// @param space Option space.
    /// @return Pointer to the retrieved option descriptor or null if
    /// no option was found.
    virtual OptionDescriptorPtr
    getOption4(const db::BackendSelector& backend_selector,
               const db::ServerSelector& server_selector,
               const uint16_t code,
               const std::string& space) const;

    /// @brief Retrieves all global options.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @return Collection of global options or empty collection if no
    /// option found.
    virtual OptionContainer
    getAllOptions4(const db::BackendSelector& backend_selector,
                   const db::ServerSelector& server_selector) const;

    /// @brief Retrieves option modified after specified time.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound option modification time.
    /// @return Collection of global options or empty collection if no
    /// option found.
    virtual OptionContainer
    getModifiedOptions4(const db::BackendSelector& backend_selector,
                        const db::ServerSelector& server_selector,
                        const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves global parameter value.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param name Name of the global parameter to be retrieved.
    /// @return Value of the global parameter.
    virtual data::StampedValuePtr
    getGlobalParameter4(const db::BackendSelector& backend_selector,
                        const db::ServerSelector& server_selector,
                        const std::string& name) const;

    /// @brief Retrieves all global parameters.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    virtual data::StampedValueCollection
    getAllGlobalParameters4(const db::BackendSelector& backend_selector,
                            const db::ServerSelector& server_selector) const;

    /// @brief Retrieves global parameters modified after specified time.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound subnet modification time.
    /// @return Collection of modified global parameters.
   virtual data::StampedValueCollection
   getModifiedGlobalParameters4(const db::BackendSelector& backend_selector,
                                const db::ServerSelector& server_selector,
                                const boost::posix_time::ptime& modification_time) const;

    /// @brief Creates or updates a subnet.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param subnet Subnet to be added or updated.
    virtual void
    createUpdateSubnet4(const db::BackendSelector& backend_selector,
                        const db::ServerSelector& server_selector,
                        const Subnet4Ptr& subnet);

    /// @brief Creates or updates a shared network.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param shared_network Shared network to be added or updated.
    virtual void
    createUpdateSharedNetwork4(const db::BackendSelector& backend_selector,
                               const db::ServerSelector& server_selector,
                               const SharedNetwork4Ptr& shared_network);

    /// @brief Creates or updates an option definition.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param option_def Option definition to be added or updated.
    virtual void
    createUpdateOptionDef4(const db::BackendSelector& backend_selector,
                           const db::ServerSelector& server_selector,
                           const OptionDefinitionPtr& option_def);

    /// @brief Creates or updates global option.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param option Option to be added or updated.
    virtual void
    createUpdateOption4(const db::BackendSelector& backend_selector,
                        const db::ServerSelector& server_selector,
                        const OptionDescriptorPtr& option);

    /// @brief Creates or updates shared network level option.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of a shared network to which option
    /// belongs.
    /// @param option Option to be added or updated.
    virtual void
    createUpdateOption4(const db::BackendSelector& backend_selector,
                        const db::ServerSelector& server_selector,
                        const std::string& shared_network_name,
                        const OptionDescriptorPtr& option);

    /// @brief Creates or updates subnet level option.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of a subnet to which option belongs.
    /// @param option Option to be added or updated.
    virtual void
    createUpdateOption4(const db::BackendSelector& backend_selector,
                        const db::ServerSelector& server_selector,
                        const SubnetID& subnet_id,
                        const OptionDescriptorPtr& option);

    /// @brief Creates or updates pool level option.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param pool_start_address Lower bound address of the pool to which
    /// the option belongs.
    /// @param pool_end_address Upper bound address of the pool to which the
    /// option belongs.
    /// @param option Option to be added or updated.
    virtual void
    createUpdateOption4(const db::BackendSelector& backend_selector,
                        const db::ServerSelector& server_selector,
                        const asiolink::IOAddress& pool_start_address,
                        const asiolink::IOAddress& pool_end_address,
                        const OptionDescriptorPtr& option);

    /// @brief Creates or updates global string parameter.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param value Value of the global parameter.
    virtual void
    createUpdateGlobalParameter4(const db::BackendSelector& backend_selector,
                                 const db::ServerSelector& server_selector,
                                 const data::StampedValuePtr& value);

    /// @brief Deletes subnet by prefix.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be deleted.
    /// @return Number of deleted subnets.
    virtual uint64_t
    deleteSubnet4(const db::BackendSelector& backend_selector,
                  const db::ServerSelector& server_selector,
                  const std::string& subnet_prefix);

    /// @brief Deletes subnet by identifier.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of the subnet to be deleted.
    /// @return Number of deleted subnets.
    virtual uint64_t
    deleteSubnet4(const db::BackendSelector& backend_selector,
                  const db::ServerSelector& server_selector,
                  const SubnetID& subnet_id);

    /// @brief Deletes all subnets.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @return Number of deleted subnets.
    virtual uint64_t
    deleteAllSubnets4(const db::BackendSelector& backend_selector,
                      const db::ServerSelector& server_selector);

    /// @brief Deletes shared network by name.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param name Name of the shared network to be deleted.
    /// @return Number of deleted shared networks.
    virtual uint64_t
    deleteSharedNetwork4(const db::BackendSelector& backend_selector,
                         const db::ServerSelector& server_selector,
                         const std::string& name);

    /// @brief Deletes all shared networks.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @return Number of deleted shared networks.
    virtual uint64_t
    deleteAllSharedNetworks4(const db::BackendSelector& backend_selector,
                             const db::ServerSelector& server_selector);

    /// @brief Deletes option definition.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param code Code of the option to be deleted.
    /// @param space Option space of the option to be deleted.
    /// @return Number of deleted option definitions.
    virtual uint64_t
    deleteOptionDef4(const db::BackendSelector& backend_selector,
                     const db::ServerSelector& server_selector,
                     const uint16_t code,
                     const std::string& space);

    /// @brief Deletes all option definitions.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @return Number of deleted option definitions.
    virtual uint64_t
    deleteAllOptionDefs4(const db::BackendSelector& backend_selector,
                         const db::ServerSelector& server_selector);

    /// @brief Deletes global option.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param code Code of the option to be deleted.
    /// @param space Option space of the option to be deleted.
    /// @return Number of deleted options.
    virtual uint64_t
    deleteOption4(const db::BackendSelector& backend_selector,
                  const db::ServerSelector& server_selector,
                  const uint16_t code,
                  const std::string& space);

    /// @brief Deletes shared network level option.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of the shared network which option
    /// belongs to.
    /// @param code Code of the option to be deleted.
    /// @param space Option space of the option to be deleted.
    virtual uint64_t
    deleteOption4(const db::BackendSelector& backend_selector,
                  const db::ServerSelector& server_selector,
                  const std::string& shared_network_name,
                  const uint16_t code,
                  const std::string& space);

    /// @brief Deletes subnet level option.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of the subnet to which deleted option
    /// belongs.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    virtual uint64_t
    deleteOption4(const db::BackendSelector& backend_selector,
                  const db::ServerSelector& server_selector,
                  const SubnetID& subnet_id,
                  const uint16_t code, const std::string& space);

    /// @brief Deletes pool level option.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param pool_start_address Lower bound address of the pool to which
    /// deleted option belongs.
    /// @param pool_end_address Upper bound address of the pool to which the
    /// deleted option belongs.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    virtual uint64_t
    deleteOption4(const db::BackendSelector& backend_selector,
                  const db::ServerSelector& server_selector,
                  const asiolink::IOAddress& pool_start_address,
                  const asiolink::IOAddress& pool_end_address,
                  const uint16_t code,
                  const std::string& space);

    /// @brief Deletes global parameter.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @param name Name of the global parameter to be deleted.
    /// @return Number of deleted global parameters.
    virtual uint64_t
    deleteGlobalParameter4(const db::BackendSelector& backend_selector,
                           const db::ServerSelector& server_selector,
                           const std::string& name);

    /// @brief Deletes all global parameters.
    ///
    /// @param backend_selector Backend selector.
    /// @param server_selector Server selector.
    /// @return Number of deleted global parameters.
    virtual uint64_t
    deleteAllGlobalParameters4(const db::BackendSelector& backend_selector,
                               const db::ServerSelector& server_selector);
};


} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CONFIG_BACKEND_POOL_DHCP4_H
