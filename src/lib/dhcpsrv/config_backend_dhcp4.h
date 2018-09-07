// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CONFIG_BACKEND_DHCP4_H
#define CONFIG_BACKEND_DHCP4_H

#include <config_backend/base_config_backend.h>
#include <database/server_selector.h>
#include <dhcp/option.h>
#include <dhcp/option_definition.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/subnet.h>
#include <util/optional_value.h>
#include <boost/date_time/posix_time/ptime.hpp>
#include <map>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Interface implemented by DHCPv4 configuration backends.
class ConfigBackendDHCPv4 : public cb::BaseConfigBackend {
public:

    /// @brief Virtual destructor.
    virtual ~ConfigBackendDHCPv4() { }

    /// @brief Retrieves a single subnet by subnet_prefix.
    ///
    /// @param selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be retrieved.
    /// @return Pointer to the retrieved subnet or NULL if not found.
    virtual Subnet4Ptr
    getSubnet4(const db::ServerSelector& selector,
               const std::string& subnet_prefix) const = 0;

    /// @brief Retrieves a single subnet by subnet identifier.
    ///
    /// @param selector Server selector.
    /// @param subnet_id Identifier of a subnet to be retrieved.
    /// @return Pointer to the retrieved subnet or NULL if not found.
    virtual Subnet4Ptr
    getSubnet4(const db::ServerSelector& selector, const SubnetID& subnet_id) const = 0;

    /// @brief Retrieves all subnets.
    ///
    /// @param selector Server selector.
    /// @return Collection of subnets or empty collection if no subnet found.
    virtual Subnet4Collection
    getAllSubnets4(const db::ServerSelector& selector) const = 0;

    /// @brief Retrieves subnets modified after specified time.
    ///
    /// @param selector Server selector.
    /// @param modification_time Lower bound subnet modification time.
    /// @return Collection of subnets or empty collection if no subnet found.
    virtual Subnet4Collection
    getModifiedSubnets4(const db::ServerSelector& selector,
                        const boost::posix_time::ptime& modification_time) const = 0;

    /// @brief Retrieves shared network by name.
    ///
    /// @param selector Server selector.
    /// @param name Name of the shared network to be retrieved.
    /// @return Pointer to the shared network or NULL if not found.
    virtual SharedNetwork4Ptr
    getSharedNetwork4(const db::ServerSelector& selector,
                      const std::string& name) const = 0;

    /// @brief Retrieves all shared networks.
    ///
    /// @param selector Server selector.
    /// @return Collection of shared network or empty collection if
    /// no shared network found.
    virtual SharedNetwork4Collection
    getAllSharedNetworks4(const db::ServerSelector& selector) const = 0;

    /// @brief Retrieves shared networks modified after specified time.
    ///
    /// @param selector Server selector.
    /// @param Lower bound shared network modification time.
    /// @return Collection of shared network or empty collection if
    /// no shared network found.
    virtual SharedNetwork4Collection
    getModifiedSharedNetworks4(const db::ServerSelector& selector,
                               const boost::posix_time::ptime& modification_time) const = 0;

    /// @brief Retrieves single option definition by code and space.
    ///
    /// @param selector Server selector.
    /// @param code Code of the option to be retrieved.
    /// @param space Option space of the option to be retrieved.
    /// @return Pointer to the option definition or NULL if not found.
    virtual OptionDefinitionPtr
    getOptionDef4(const db::ServerSelector& selector, const uint16_t code,
                  const std::string& space) const = 0;

    /// @brief Retrieves all option definitions.
    ///
    /// @param selector Server selector.
    /// @return Collection of option definitions or empty collection if
    /// no option definition found.
    virtual OptionDefContainer
    getAllOptionDefs4(const db::ServerSelector& selector) const = 0;

    /// @brief Retrieves option definitions modified after specified time.
    ///
    /// @param selector Server selector.
    /// @param modification_time Lower bound option definition modification
    /// time.
    /// @return Collection of option definitions or empty collection if
    /// no option definition found.
    virtual OptionDefContainer
    getModifiedOptionDefs4(const db::ServerSelector& selector,
                           const boost::posix_time::ptime& modification_time) const = 0;

    /// @brief Retrieves global string parameter value.
    ///
    /// @param selector Server selector.
    /// @param name Name of the global parameter to be retrieved.
    /// @return Value of the global string parameter.
    virtual util::OptionalValue<std::string>
    getGlobalStringParameter4(const db::ServerSelector& selector,
                              const std::string& name) const = 0;

    /// @brief Retrieves global number parameter.
    ///
    /// @param selector Server selector.
    /// @param name Name of the parameter to be retrieved.
    virtual util::OptionalValue<int64_t>
    getGlobalNumberParameter4(const db::ServerSelector& selector,
                              const std::string& name) const = 0;

    /// @brief Retrieves all global parameters as strings.
    ///
    /// @param selector Server selector.
    virtual std::map<std::string, std::string>
    getAllGlobalParameters4(const db::ServerSelector& selector) const = 0;

    /// @brief Creates or updates a subnet.
    ///
    /// @param selector Server selector.
    /// @param subnet Subnet to be added or updated.
    virtual void
    createUpdateSubnet4(const db::ServerSelector& selector,
                        const Subnet4Ptr& subnet) = 0;

    /// @brief Creates or updates a shared network.
    ///
    /// @param selector Server selector.
    /// @param shared_network Shared network to be added or updated.
    virtual void
    createUpdateSharedNetwork4(const db::ServerSelector& selector,
                               const SharedNetwork4Ptr& shared_network) = 0;

    /// @brief Creates or updates an option definition.
    ///
    /// @param selector Server selector.
    /// @param option_def Option definition to be added or updated.
    virtual void
    createUpdateOptionDef4(const db::ServerSelector& selector,
                           const OptionDefinitionPtr& option_def) = 0;

    /// @brief Creates or updates global option.
    ///
    /// @param selector Server selector.
    /// @param option Option to be added or updated.
    virtual void
    createUpdateOption4(const db::ServerSelector& selector,
                        const OptionPtr& option) = 0;

    /// @brief Creates or updates subnet level option.
    ///
    /// @param selector Server selector.
    /// @param subnet_id Identifier of a subnet to which option belongs.
    virtual void
    createUpdateOption4(const db::ServerSelector& selector,
                        const SubnetID& subnet_id, const OptionPtr& option) = 0;

    /// @brief Creates or updates pool level option.
    ///
    /// @param selector Server selector.
    /// @param pool_start_address Lower bound address of the pool to which
    /// the option belongs.
    /// @param pool_end_address Upper bound address of the pool to which the
    /// option belongs.
    virtual void
    createUpdateOption4(const db::ServerSelector& selector,
                        const asiolink::IOAddress& pool_start_address,
                        const asiolink::IOAddress& pool_end_address,
                        const OptionPtr& option) = 0;

    /// @brief Creates or updates global string parameter.
    ///
    /// @param selector Server selector.
    /// @param name Name of the global parameter.
    /// @param value Value of the global parameter.
    virtual void
    createUpdateGlobalParameter4(const db::ServerSelector& selector,
                                 const std::string& name,
                                 const std::string& value) = 0;

    /// @brief Creates or updates global number parameter.
    ///
    /// @param selector Server selector.
    /// @param name Name of the global parameter.
    /// @param value Value of the global parameter.
    virtual void
    createUpdateGlobalParameter4(const db::ServerSelector& selector,
                                 const std::string& name,
                                 const int64_t value) = 0;
    
    /// @brief Deletes subnet by prefix.
    ///
    /// @param selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be deleted.
    virtual void
    deleteSubnet4(const db::ServerSelector& selector,
                  const std::string& subnet_prefix) = 0;

    /// @brief Deletes subnet by identifier.
    ///
    /// @param selector Server selector.
    /// @param subnet_id Identifier of the subnet to be deleted.
    virtual void
    deleteSubnet4(const db::ServerSelector& selector, const SubnetID& subnet_id) = 0;

    /// @brief Deletes all subnets.
    ///
    /// @param selector Server selector.
    virtual void
    deleteAllSubnets4(const db::ServerSelector& selector) = 0;

    /// @brief Deletes shared network by name.
    ///
    /// @param selector Server selector.
    /// @param name Name of the shared network to be deleted.
    virtual void
    deleteSharedNetwork4(const db::ServerSelector& selector,
                         const std::string& name) = 0;

    /// @brief Deletes all shared networks.
    ///
    /// @param selector Server selector.
    virtual void
    deleteAllSharedNetworks4(const db::ServerSelector& selector) = 0;

    /// @brief Deletes option definition.
    ///
    /// @param selector Server selector.
    /// @param code Code of the option to be deleted.
    /// @param space Option space of the option to be deleted.
    virtual void
    deleteOptionDef4(const db::ServerSelector& selector, const uint16_t code,
                     const std::string& space) = 0;

    /// @brief Deletes all option definitions.
    ///
    /// @param selector Server selector.
    virtual void
    deleteAllOptionDefs4(const db::ServerSelector& selector) = 0;

    /// @brief Deletes global option.
    ///
    /// @param selector Server selector.
    /// @param code Code of the option to be deleted.
    /// @param space Option space of the option to be deleted.
    virtual void
    deleteOption4(const db::ServerSelector& selector, const uint16_t code,
                  const std::string& space) = 0;

    /// @brief Deletes subnet level option.
    ///
    /// @param selector Server selector.
    /// @param subnet_id Identifier of the subnet to which deleted option
    /// belongs.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    virtual void
    deleteOption4(const db::ServerSelector& selector, const SubnetID& subnet_id,
                  const uint16_t code, const std::string& space) = 0;

    /// @brief Deletes pool level option.
    ///
    /// @param selector Server selector.
    /// @param pool_start_address Lower bound address of the pool to which
    /// deleted option belongs.
    /// @param pool_end_start Upper bound address of the pool to which the
    /// deleted option belongs.
    virtual void
    deleteOption4(const db::ServerSelector& selector,
                  const asiolink::IOAddress& pool_start_address,
                  const asiolink::IOAddress& pool_end_address,
                  const uint16_t code,
                  const std::string& space) = 0;

    /// @brief Deletes global parameter.
    ///
    /// @param selector Server selector.
    /// @param name Name of the global parameter to be deleted.
    virtual void
    deleteGlobalParameter4(const db::ServerSelector& selector,
                           const std::string& name) = 0;

    /// @brief Deletes all global parameters.
    ///
    /// @param selector Server selector.
    virtual void
    deleteAllGlobalParameters4(const db::ServerSelector& selector) = 0;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CONFIG_BACKEND_DHCP4_H
