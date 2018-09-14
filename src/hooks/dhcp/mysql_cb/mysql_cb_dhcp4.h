// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_CONFIG_BACKEND_DHCP4_H
#define MYSQL_CONFIG_BACKEND_DHCP4_H

#include <database/database_connection.h>
#include <dhcpsrv/config_backend_dhcp4.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

class MySqlConfigBackendDHCPv4Impl;

/// @brief Implementation of the MySql Configuration Backend for
/// Kea DHCPv4 server.
class MySqlConfigBackendDHCPv4 : public ConfigBackendDHCPv4 {
public:

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    explicit MySqlConfigBackendDHCPv4(const db::DatabaseConnection::ParameterMap& parameters);

    /// @brief Retrieves a single subnet by subnet_prefix.
    ///
    /// @param selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be retrieved.
    /// @return Pointer to the retrieved subnet or NULL if not found.
    virtual Subnet4Ptr
    getSubnet4(const db::ServerSelector& selector,
               const std::string& subnet_prefix) const;

    /// @brief Retrieves a single subnet by subnet identifier.
    ///
    /// @param selector Server selector.
    /// @param subnet_id Identifier of a subnet to be retrieved.
    /// @return Pointer to the retrieved subnet or NULL if not found.
    virtual Subnet4Ptr
    getSubnet4(const db::ServerSelector& selector, const SubnetID& subnet_id) const;

    /// @brief Retrieves all subnets.
    ///
    /// @param selector Server selector.
    /// @return Collection of subnets or empty collection if no subnet found.
    virtual Subnet4Collection
    getAllSubnets4(const db::ServerSelector& selector) const;

    /// @brief Retrieves subnets modified after specified time.
    ///
    /// @param selector Server selector.
    /// @param modification_time Lower bound subnet modification time.
    /// @return Collection of subnets or empty collection if no subnet found.
    virtual Subnet4Collection
    getModifiedSubnets4(const db::ServerSelector& selector,
                        const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves shared network by name.
    ///
    /// @param selector Server selector.
    /// @param name Name of the shared network to be retrieved.
    /// @return Pointer to the shared network or NULL if not found.
    virtual SharedNetwork4Ptr
    getSharedNetwork4(const db::ServerSelector& selector,
                      const std::string& name) const;

    /// @brief Retrieves all shared networks.
    ///
    /// @param selector Server selector.
    /// @return Collection of shared network or empty collection if
    /// no shared network found.
    virtual SharedNetwork4Collection
    getAllSharedNetworks4(const db::ServerSelector& selector) const;

    /// @brief Retrieves shared networks modified after specified time.
    ///
    /// @param selector Server selector.
    /// @param modification_time Lower bound shared network modification time.
    /// @return Collection of shared network or empty collection if
    /// no shared network found.
    virtual SharedNetwork4Collection
    getModifiedSharedNetworks4(const db::ServerSelector& selector,
                               const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves single option definition by code and space.
    ///
    /// @param selector Server selector.
    /// @param code Code of the option to be retrieved.
    /// @param space Option space of the option to be retrieved.
    /// @return Pointer to the option definition or NULL if not found.
    virtual OptionDefinitionPtr
    getOptionDef4(const db::ServerSelector& selector, const uint16_t code,
                  const std::string& space) const;

    /// @brief Retrieves all option definitions.
    ///
    /// @param selector Server selector.
    /// @return Collection of option definitions or empty collection if
    /// no option definition found.
    virtual OptionDefContainer
    getAllOptionDefs4(const db::ServerSelector& selector) const;

    /// @brief Retrieves option definitions modified after specified time.
    ///
    /// @param selector Server selector.
    /// @param modification_time Lower bound option definition modification
    /// time.
    /// @return Collection of option definitions or empty collection if
    /// no option definition found.
    virtual OptionDefContainer
    getModifiedOptionDefs4(const db::ServerSelector& selector,
                           const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves global string parameter value.
    ///
    /// @param selector Server selector.
    /// @param name Name of the global parameter to be retrieved.
    /// @return Value of the global string parameter.
    virtual util::OptionalValue<std::string>
    getGlobalStringParameter4(const db::ServerSelector& selector,
                              const std::string& name) const;

    /// @brief Retrieves global number parameter.
    ///
    /// @param selector Server selector.
    /// @param name Name of the parameter to be retrieved.
    virtual util::OptionalValue<int64_t>
    getGlobalNumberParameter4(const db::ServerSelector& selector,
                              const std::string& name) const;

    /// @brief Retrieves all global parameters as strings.
    ///
    /// @param selector Server selector.
    virtual std::map<std::string, std::string>
    getAllGlobalParameters4(const db::ServerSelector& selector) const;

    /// @brief Creates or updates a subnet.
    ///
    /// @param selector Server selector.
    /// @param subnet Subnet to be added or updated.
    virtual void
    createUpdateSubnet4(const db::ServerSelector& selector,
                        const Subnet4Ptr& subnet);

    /// @brief Creates or updates a shared network.
    ///
    /// @param selector Server selector.
    /// @param shared_network Shared network to be added or updated.
    virtual void
    createUpdateSharedNetwork4(const db::ServerSelector& selector,
                               const SharedNetwork4Ptr& shared_network);

    /// @brief Creates or updates an option definition.
    ///
    /// @param selector Server selector.
    /// @param option_def Option definition to be added or updated.
    virtual void
    createUpdateOptionDef4(const db::ServerSelector& selector,
                           const OptionDefinitionPtr& option_def);

    /// @brief Creates or updates global option.
    ///
    /// @param selector Server selector.
    /// @param option Option to be added or updated.
    virtual void
    createUpdateOption4(const db::ServerSelector& selector,
                        const OptionPtr& option);

    /// @brief Creates or updates subnet level option.
    ///
    /// @param selector Server selector.
    /// @param subnet_id Identifier of a subnet to which option belongs.
    /// @param option Option to be added or updated.
    virtual void
    createUpdateOption4(const db::ServerSelector& selector,
                        const SubnetID& subnet_id,
                        const OptionPtr& option);

    /// @brief Creates or updates pool level option.
    ///
    /// @param selector Server selector.
    /// @param pool_start_address Lower bound address of the pool to which
    /// the option belongs.
    /// @param pool_end_address Upper bound address of the pool to which the
    /// option belongs.
    /// @param option Option to be added or updated.
    virtual void
    createUpdateOption4(const db::ServerSelector& selector,
                        const asiolink::IOAddress& pool_start_address,
                        const asiolink::IOAddress& pool_end_address,
                        const OptionPtr& option);

    /// @brief Creates or updates global string parameter.
    ///
    /// @param selector Server selector.
    /// @param name Name of the global parameter.
    /// @param value Value of the global parameter.
    virtual void
    createUpdateGlobalParameter4(const db::ServerSelector& selector,
                                 const std::string& name,
                                 const std::string& value);

    /// @brief Creates or updates global number parameter.
    ///
    /// @param selector Server selector.
    /// @param name Name of the global parameter.
    /// @param value Value of the global parameter.
    virtual void
    createUpdateGlobalParameter4(const db::ServerSelector& selector,
                                 const std::string& name,
                                 const int64_t value);
    
    /// @brief Deletes subnet by prefix.
    ///
    /// @param selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be deleted.
    virtual void
    deleteSubnet4(const db::ServerSelector& selector,
                  const std::string& subnet_prefix);

    /// @brief Deletes subnet by identifier.
    ///
    /// @param selector Server selector.
    /// @param subnet_id Identifier of the subnet to be deleted.
    virtual void
    deleteSubnet4(const db::ServerSelector& selector, const SubnetID& subnet_id);

    /// @brief Deletes all subnets.
    ///
    /// @param selector Server selector.
    virtual void
    deleteAllSubnets4(const db::ServerSelector& selector);

    /// @brief Deletes shared network by name.
    ///
    /// @param selector Server selector.
    /// @param name Name of the shared network to be deleted.
    virtual void
    deleteSharedNetwork4(const db::ServerSelector& selector,
                         const std::string& name);

    /// @brief Deletes all shared networks.
    ///
    /// @param selector Server selector.
    virtual void
    deleteAllSharedNetworks4(const db::ServerSelector& selector);

    /// @brief Deletes option definition.
    ///
    /// @param selector Server selector.
    /// @param code Code of the option to be deleted.
    /// @param space Option space of the option to be deleted.
    virtual void
    deleteOptionDef4(const db::ServerSelector& selector, const uint16_t code,
                     const std::string& space);

    /// @brief Deletes all option definitions.
    ///
    /// @param selector Server selector.
    virtual void
    deleteAllOptionDefs4(const db::ServerSelector& selector);

    /// @brief Deletes global option.
    ///
    /// @param selector Server selector.
    /// @param code Code of the option to be deleted.
    /// @param space Option space of the option to be deleted.
    virtual void
    deleteOption4(const db::ServerSelector& selector, const uint16_t code,
                  const std::string& space);

    /// @brief Deletes subnet level option.
    ///
    /// @param selector Server selector.
    /// @param subnet_id Identifier of the subnet to which deleted option
    /// belongs.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    virtual void
    deleteOption4(const db::ServerSelector& selector, const SubnetID& subnet_id,
                  const uint16_t code, const std::string& space);

    /// @brief Deletes pool level option.
    ///
    /// @param selector Server selector.
    /// @param pool_start_address Lower bound address of the pool to which
    /// deleted option belongs.
    /// @param pool_end_address Upper bound address of the pool to which the
    /// deleted option belongs.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    virtual void
    deleteOption4(const db::ServerSelector& selector,
                  const asiolink::IOAddress& pool_start_address,
                  const asiolink::IOAddress& pool_end_address,
                  const uint16_t code,
                  const std::string& space);

    /// @brief Deletes global parameter.
    ///
    /// @param selector Server selector.
    /// @param name Name of the global parameter to be deleted.
    virtual void
    deleteGlobalParameter4(const db::ServerSelector& selector,
                           const std::string& name);

    /// @brief Deletes all global parameters.
    ///
    /// @param selector Server selector.
    virtual void
    deleteAllGlobalParameters4(const db::ServerSelector& selector);

    /// @brief Returns backend type in the textual format.
    ///
    /// @return "mysql".
    virtual std::string getType() const;

    /// @brief Returns backend host.
    ///
    /// This is used by the @c BaseConfigBackendPool to select backend
    /// when @c BackendSelector is specified.
    ///
    /// @return host on which the database is located.
    virtual std::string getHost() const;

    /// @brief Returns backend port number.
    ///
    /// This is used by the @c BaseConfigBackendPool to select backend
    /// when @c BackendSelector is specified.
    ///
    /// @return Port number on which database service is available.
    virtual uint16_t getPort() const;

private:

    /// @brief Pointer to the implementation of the @c MySqlConfigBackendDHCPv4
    /// class.
    boost::shared_ptr<MySqlConfigBackendDHCPv4Impl> impl_;

};

/// @brief Pointer to the @c MySqlConfigBackendDHCPv4 class.
typedef boost::shared_ptr<MySqlConfigBackendDHCPv4> MySqlConfigBackendDHCPv4Ptr;

} // end of namespace isc::cb
} // end of namespace isc

#endif // MYSQL_CONFIG_BACKEND_DHCP4_H
