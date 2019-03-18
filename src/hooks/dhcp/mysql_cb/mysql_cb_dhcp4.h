// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
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
///
/// All POSIX times specified in the methods belonging to this
/// class must be local times.
class MySqlConfigBackendDHCPv4 : public ConfigBackendDHCPv4 {
public:

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    explicit MySqlConfigBackendDHCPv4(const db::DatabaseConnection::ParameterMap& parameters);

    /// @brief Retrieves a single subnet by subnet_prefix.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be retrieved.
    /// @return Pointer to the retrieved subnet or NULL if not found.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual Subnet4Ptr
    getSubnet4(const db::ServerSelector& server_selector,
               const std::string& subnet_prefix) const;

    /// @brief Retrieves a single subnet by subnet identifier.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of a subnet to be retrieved.
    /// @return Pointer to the retrieved subnet or NULL if not found.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual Subnet4Ptr
    getSubnet4(const db::ServerSelector& server_selector, const SubnetID& subnet_id) const;

    /// @brief Retrieves all subnets.
    ///
    /// @param server_selector Server selector.
    /// @return Collection of subnets or empty collection if no subnet found.
    virtual Subnet4Collection
    getAllSubnets4(const db::ServerSelector& server_selector) const;

    /// @brief Retrieves subnets modified after specified time.
    ///
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound subnet modification time.
    /// @return Collection of subnets or empty collection if no subnet found.
    virtual Subnet4Collection
    getModifiedSubnets4(const db::ServerSelector& server_selector,
                        const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves all subnets belonging to a specified shared network.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of the shared network for which the
    /// subnets should be retrieved.
    /// @return Collection of subnets or empty collection if no subnet found.
    virtual Subnet4Collection
    getSharedNetworkSubnets4(const db::ServerSelector& server_selector,
                             const std::string& shared_network_name) const;

    /// @brief Retrieves shared network by name.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the shared network to be retrieved.
    /// @return Pointer to the shared network or NULL if not found.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual SharedNetwork4Ptr
    getSharedNetwork4(const db::ServerSelector& server_selector,
                      const std::string& name) const;

    /// @brief Retrieves all shared networks.
    ///
    /// @param server_selector Server selector.
    /// @return Collection of shared network or empty collection if
    /// no shared network found.
    virtual SharedNetwork4Collection
    getAllSharedNetworks4(const db::ServerSelector& server_selector) const;

    /// @brief Retrieves shared networks modified after specified time.
    ///
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound shared network modification time.
    /// @return Collection of shared network or empty collection if
    /// no shared network found.
    virtual SharedNetwork4Collection
    getModifiedSharedNetworks4(const db::ServerSelector& server_selector,
                               const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves single option definition by code and space.
    ///
    /// @param server_selector Server selector.
    /// @param code Code of the option to be retrieved.
    /// @param space Option space of the option to be retrieved.
    /// @return Pointer to the option definition or NULL if not found.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual OptionDefinitionPtr
    getOptionDef4(const db::ServerSelector& server_selector, const uint16_t code,
                  const std::string& space) const;

    /// @brief Retrieves all option definitions.
    ///
    /// @param server_selector Server selector.
    /// @return Collection of option definitions or empty collection if
    /// no option definition found.
    virtual OptionDefContainer
    getAllOptionDefs4(const db::ServerSelector& server_selector) const;

    /// @brief Retrieves option definitions modified after specified time.
    ///
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound option definition modification
    /// time.
    /// @return Collection of option definitions or empty collection if
    /// no option definition found.
    virtual OptionDefContainer
    getModifiedOptionDefs4(const db::ServerSelector& server_selector,
                           const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves single option by code and space.
    ///
    /// @param server_selector Server selector.
    /// @return Pointer to the retrieved option descriptor or null if
    /// no option was found.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual OptionDescriptorPtr
    getOption4(const db::ServerSelector& server_selector, const uint16_t code,
               const std::string& space) const;

    /// @brief Retrieves all global options.
    ///
    /// @param server_selector Server selector.
    /// @return Collection of global options or empty collection if no
    /// option found.
    virtual OptionContainer
    getAllOptions4(const db::ServerSelector& server_selector) const;

    /// @brief Retrieves option modified after specified time.
    ///
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound option modification time.
    /// @return Collection of global options or empty collection if no
    /// option found.
    virtual OptionContainer
    getModifiedOptions4(const db::ServerSelector& server_selector,
                        const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves global parameter value.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the global parameter to be retrieved.
    /// @return Value of the global parameter.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual data::StampedValuePtr
    getGlobalParameter4(const db::ServerSelector& server_selector,
                        const std::string& name) const;

    /// @brief Retrieves all global parameters.
    ///
    /// @param server_selector Server selector.
    virtual data::StampedValueCollection
    getAllGlobalParameters4(const db::ServerSelector& server_selector) const;

    /// @brief Retrieves global parameters modified after specified time.
    ///
    /// @param modification_time Lower bound modification time.
    /// @return Collection of modified global parameters.
    virtual data::StampedValueCollection
    getModifiedGlobalParameters4(const db::ServerSelector& server_selector,
                                 const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves the most recent audit entries.
    ///
    /// @param selector Server selector.
    /// @param modification_time Timestamp being a lower limit for the returned
    /// result set, i.e. entries later than specified time are returned.
    /// @return Collection of audit entries.
    virtual db::AuditEntryCollection
    getRecentAuditEntries(const db::ServerSelector& server_selector,
                          const boost::posix_time::ptime& modification_time) const;

    /// @brief Creates or updates a subnet.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Subnet to be added or updated.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateSubnet4(const db::ServerSelector& server_selector,
                        const Subnet4Ptr& subnet);

    /// @brief Creates or updates a shared network.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network Shared network to be added or updated.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateSharedNetwork4(const db::ServerSelector& server_selector,
                               const SharedNetwork4Ptr& shared_network);

    /// @brief Creates or updates an option definition.
    ///
    /// @param server_selector Server selector.
    /// @param option_def Option definition to be added or updated.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateOptionDef4(const db::ServerSelector& server_selector,
                           const OptionDefinitionPtr& option_def);

    /// @brief Creates or updates global option.
    ///
    /// @param server_selector Server selector.
    /// @param option Option to be added or updated.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateOption4(const db::ServerSelector& server_selector,
                        const OptionDescriptorPtr& option);

    /// @brief Creates or updates shared network level option.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of a shared network to which option
    /// belongs.
    /// @param option Option to be added or updated.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateOption4(const db::ServerSelector& server_selector,
                        const std::string& shared_network_name,
                        const OptionDescriptorPtr& option);

    /// @brief Creates or updates subnet level option.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of a subnet to which option belongs.
    /// @param option Option to be added or updated.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateOption4(const db::ServerSelector& server_selector,
                        const SubnetID& subnet_id,
                        const OptionDescriptorPtr& option);

    /// @brief Creates or updates pool level option.
    ///
    /// @param server_selector Server selector.
    /// @param pool_start_address Lower bound address of the pool to which
    /// the option belongs.
    /// @param pool_end_address Upper bound address of the pool to which the
    /// option belongs.
    /// @param option Option to be added or updated.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateOption4(const db::ServerSelector& server_selector,
                        const asiolink::IOAddress& pool_start_address,
                        const asiolink::IOAddress& pool_end_address,
                        const OptionDescriptorPtr& option);

    /// @brief Creates or updates global parameter.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the global parameter.
    /// @param value Value of the global parameter.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateGlobalParameter4(const db::ServerSelector& server_selector,
                                 const data::StampedValuePtr& value);

    /// @brief Deletes subnet by prefix.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be deleted.
    /// @return Number of deleted subnets.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteSubnet4(const db::ServerSelector& server_selector,
                  const std::string& subnet_prefix);

    /// @brief Deletes subnet by identifier.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of the subnet to be deleted.
    /// @return Number of deleted subnets.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteSubnet4(const db::ServerSelector& server_selector, const SubnetID& subnet_id);

    /// @brief Deletes all subnets.
    ///
    /// @param server_selector Server selector.
    /// @return Number of deleted subnets.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteAllSubnets4(const db::ServerSelector& server_selector);

    /// @brief Deletes all subnets belonging to a specified shared network.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of the shared network for which the
    /// subnets should be deleted.
    /// @return Number of deleted subnets.
    virtual uint64_t
    deleteSharedNetworkSubnets4(const db::ServerSelector& server_selector,
                                const std::string& shared_network_name);

    /// @brief Deletes shared network by name.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the shared network to be deleted.
    /// @return Number of deleted shared networks.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteSharedNetwork4(const db::ServerSelector& server_selector,
                         const std::string& name);

    /// @brief Deletes all shared networks.
    ///
    /// @param server_selector Server selector.
    /// @return Number of deleted shared networks.
    virtual uint64_t
    deleteAllSharedNetworks4(const db::ServerSelector& server_selector);

    /// @brief Deletes option definition.
    ///
    /// @param server_selector Server selector.
    /// @param code Code of the option to be deleted.
    /// @param space Option space of the option to be deleted.
    /// @return Number of deleted option definitions.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteOptionDef4(const db::ServerSelector& server_selector, const uint16_t code,
                     const std::string& space);

    /// @brief Deletes all option definitions.
    ///
    /// @param server_selector Server selector.
    /// @return Number of deleted option definitions.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteAllOptionDefs4(const db::ServerSelector& server_selector);

    /// @brief Deletes global option.
    ///
    /// @param server_selector Server selector.
    /// @param code Code of the option to be deleted.
    /// @param space Option space of the option to be deleted.
    /// @return Number of deleted options.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteOption4(const db::ServerSelector& server_selector, const uint16_t code,
                  const std::string& space);

    /// @brief Deletes shared network level option.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of the shared network which deleted
    /// option belongs to
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteOption4(const db::ServerSelector& server_selector,
                  const std::string& shared_network_name,
                  const uint16_t code,
                  const std::string& space);

    /// @brief Deletes subnet level option.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of the subnet to which deleted option
    /// belongs.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteOption4(const db::ServerSelector& server_selector, const SubnetID& subnet_id,
                  const uint16_t code, const std::string& space);

    /// @brief Deletes pool level option.
    ///
    /// @param server_selector Server selector.
    /// @param pool_start_address Lower bound address of the pool to which
    /// deleted option belongs.
    /// @param pool_end_address Upper bound address of the pool to which the
    /// deleted option belongs.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteOption4(const db::ServerSelector& server_selector,
                  const asiolink::IOAddress& pool_start_address,
                  const asiolink::IOAddress& pool_end_address,
                  const uint16_t code,
                  const std::string& space);

    /// @brief Deletes global parameter.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the global parameter to be deleted.
    /// @return Number of deleted global parameters.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteGlobalParameter4(const db::ServerSelector& server_selector,
                           const std::string& name);

    /// @brief Deletes all global parameters.
    ///
    /// @param server_selector Server selector.
    /// @return Number of deleted global parameters.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteAllGlobalParameters4(const db::ServerSelector& server_selector);

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

    /// @brief Registers the MySQL backend factory with backend config manager
    ///
    /// This should be called by the hook lib load() function.
    /// @return True if the factory was registered successfully, false otherwise.
    static bool registerBackendType();

    /// @brief Unregisters the MySQL backend factory and discards MySQL backends
    ///
    /// This should be called by the hook lib unload() function.
    static void unregisterBackendType();

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
