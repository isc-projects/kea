// Copyright (C) 2019-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_CONFIG_BACKEND_DHCP6_H
#define MYSQL_CONFIG_BACKEND_DHCP6_H

#include <mysql_cb_impl.h>
#include <database/database_connection.h>
#include <dhcpsrv/config_backend_dhcp6.h>
#include <mysql_cb_log.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

class MySqlConfigBackendDHCPv6Impl;

/// @brief Implementation of the MySql Configuration Backend for
/// Kea DHCPv6 server.
///
/// All POSIX times specified in the methods belonging to this
/// class must be local times.
///
/// The server selection mechanisms used by this backend generally adhere
/// to the rules described for @c ConfigBackendDHCPv6, but support for
/// some of the selectors is not implemented. Whenever this is the case,
/// the methods throw @c isc::NotImplemented exception.
class MySqlConfigBackendDHCPv6 : public ConfigBackendDHCPv6 {
public:

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    explicit MySqlConfigBackendDHCPv6(const db::DatabaseConnection::ParameterMap& parameters);

    /// @brief Retrieves a single subnet by subnet_prefix.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be retrieved.
    /// @return Pointer to the retrieved subnet or NULL if not found.
    virtual Subnet6Ptr
    getSubnet6(const db::ServerSelector& server_selector,
               const std::string& subnet_prefix) const;

    /// @brief Retrieves a single subnet by subnet identifier.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of a subnet to be retrieved.
    /// @return Pointer to the retrieved subnet or NULL if not found.
    virtual Subnet6Ptr
    getSubnet6(const db::ServerSelector& server_selector, const SubnetID& subnet_id) const;

    /// @brief Retrieves all subnets.
    ///
    /// @param server_selector Server selector.
    /// @return Collection of subnets or empty collection if no subnet found.
    virtual Subnet6Collection
    getAllSubnets6(const db::ServerSelector& server_selector) const;

    /// @brief Retrieves subnets modified after specified time.
    ///
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound subnet modification time.
    /// @return Collection of subnets or empty collection if no subnet found.
    virtual Subnet6Collection
    getModifiedSubnets6(const db::ServerSelector& server_selector,
                        const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves all subnets belonging to a specified shared network.
    ///
    /// The server selector is currently ignored by this method. All subnets
    /// for the given shared network are returned regardless of their
    /// associations with the servers.
    ///
    /// @param server_selector Server selector (currently ignored).
    /// @param shared_network_name Name of the shared network for which the
    /// subnets should be retrieved.
    /// @return Collection of subnets or empty collection if no subnet found.
    virtual Subnet6Collection
    getSharedNetworkSubnets6(const db::ServerSelector& server_selector,
                             const std::string& shared_network_name) const;

    /// @brief Retrieves shared network by name.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the shared network to be retrieved.
    /// @return Pointer to the shared network or NULL if not found.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual SharedNetwork6Ptr
    getSharedNetwork6(const db::ServerSelector& server_selector,
                      const std::string& name) const;

    /// @brief Retrieves all shared networks.
    ///
    /// @param server_selector Server selector.
    /// @return Collection of shared network or empty collection if
    /// no shared network found.
    virtual SharedNetwork6Collection
    getAllSharedNetworks6(const db::ServerSelector& server_selector) const;

    /// @brief Retrieves shared networks modified after specified time.
    ///
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound shared network modification time.
    /// @return Collection of shared network or empty collection if
    /// no shared network found.
    virtual SharedNetwork6Collection
    getModifiedSharedNetworks6(const db::ServerSelector& server_selector,
                               const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves single option definition by code and space.
    ///
    /// @param server_selector Server selector.
    /// @param code Code of the option to be retrieved.
    /// @param space Option space of the option to be retrieved.
    /// @return Pointer to the option definition or NULL if not found.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual OptionDefinitionPtr
    getOptionDef6(const db::ServerSelector& server_selector, const uint16_t code,
                  const std::string& space) const;

    /// @brief Retrieves all option definitions.
    ///
    /// @param server_selector Server selector.
    /// @return Collection of option definitions or empty collection if
    /// no option definition found.
    virtual OptionDefContainer
    getAllOptionDefs6(const db::ServerSelector& server_selector) const;

    /// @brief Retrieves option definitions modified after specified time.
    ///
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound option definition modification
    /// time.
    /// @return Collection of option definitions or empty collection if
    /// no option definition found.
    virtual OptionDefContainer
    getModifiedOptionDefs6(const db::ServerSelector& server_selector,
                           const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves single option by code and space.
    ///
    /// @param server_selector Server selector.
    /// @return Pointer to the retrieved option descriptor or null if
    /// no option was found.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual OptionDescriptorPtr
    getOption6(const db::ServerSelector& server_selector, const uint16_t code,
               const std::string& space) const;

    /// @brief Retrieves all global options.
    ///
    /// @param server_selector Server selector.
    /// @return Collection of global options or empty collection if no
    /// option found.
    virtual OptionContainer
    getAllOptions6(const db::ServerSelector& server_selector) const;

    /// @brief Retrieves option modified after specified time.
    ///
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound option modification time.
    /// @return Collection of global options or empty collection if no
    /// option found.
    virtual OptionContainer
    getModifiedOptions6(const db::ServerSelector& server_selector,
                        const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves global parameter value.
    ///
    /// Typically, the server selector used for this query should be set to
    /// ONE. It is possible to use the MULTIPLE server selector but in that
    /// case only the first found parameter is returned.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the global parameter to be retrieved.
    /// @return Value of the global parameter.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual data::StampedValuePtr
    getGlobalParameter6(const db::ServerSelector& server_selector,
                        const std::string& name) const;

    /// @brief Retrieves all global parameters.
    ///
    /// Using the server selector it is possible to fetch the parameters for
    /// one or more servers. The following list describes what parameters are
    /// returned depending on the server selector specified:
    /// - ALL: only common parameters are returned which are associated with
    ///   the logical server 'all'. No parameters associated with the explicit
    ///   server tags are returned.
    ///
    /// - ONE: parameters used by the particular sever are returned. This includes
    ///   parameters associated with the particular server (identified by tag)
    ///   and parameters associated with the logical server 'all' when server
    ///   specific parameters are not given. For example, if there is a
    ///   renew-timer specified for 'server1' tag, different value of the
    ///   renew-timer specified for 'all' servers and a rebind-timer specified
    ///   for 'all' servers, the caller will receive renew-timer value associated
    ///   with the server1 and the rebind-timer value associated with all servers,
    ///   because there is no explicit rebind-timer specified for server1.
    ///
    /// - MULTIPLE: parameters used by multiple servers, but those associated
    ///   with specific server tags take precedence over the values specified for
    ///   'all' servers. This is similar to the case of ONE server described
    ///   above. The effect of querying for parameters belonging to multiple
    ///   servers is the same as issuing multiple queries with ONE server
    ///   being selected multiple times.
    ///
    /// - UNASSIGNED: parameters not associated with any servers.
    ///
    ///
    /// @param server_selector Server selector.
    virtual data::StampedValueCollection
    getAllGlobalParameters6(const db::ServerSelector& server_selector) const;

    /// @brief Retrieves global parameters modified after specified time.
    ///
    /// @param modification_time Lower bound modification time.
    /// @return Collection of modified global parameters.
    virtual data::StampedValueCollection
    getModifiedGlobalParameters6(const db::ServerSelector& server_selector,
                                 const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves a client class by name.
    ///
    /// @param server_selector Server selector.
    /// @param name Client class name.
    /// @return Pointer to the retrieved client class.
    virtual ClientClassDefPtr
    getClientClass6(const db::ServerSelector& selector, const std::string& name) const;

    /// @brief Retrieves all client classes.
    ///
    /// @param selector Server selector.
    /// @return Collection of client classes.
    virtual ClientClassDictionary
    getAllClientClasses6(const db::ServerSelector& selector) const;

    /// @brief Retrieves client classes modified after specified time.
    ///
    /// @param selector Server selector.
    /// @param modification_time Modification time.
    /// @return Collection of client classes.
    virtual ClientClassDictionary
    getModifiedClientClasses6(const db::ServerSelector& selector,
                              const boost::posix_time::ptime& modification_time) const;

    /// @brief Retrieves the most recent audit entries.
    ///
    /// @param selector Server selector.
    /// @param modification_time Timestamp being a lower limit for the returned
    /// result set, i.e. entries later than specified time are returned.
    /// @param modification_id Identifier being a lower limit for the returned
    /// result set, used when two (or more) entries have the same
    /// modification_time.
    /// @return Collection of audit entries.
    virtual db::AuditEntryCollection
    getRecentAuditEntries(const db::ServerSelector& server_selector,
                          const boost::posix_time::ptime& modification_time,
                          const uint64_t& modification_id) const;

    /// @brief Retrieves all servers.
    ///
    /// This method returns the list of servers excluding the logical server
    /// 'all'.
    ///
    /// @return Collection of servers from the backend.
    virtual db::ServerCollection
    getAllServers6() const;

    /// @brief Retrieves a server.
    ///
    /// @param server_tag Tag of the server to be retrieved.
    /// @return Pointer to the server instance or null pointer if no server
    /// with the particular tag was found.
    virtual db::ServerPtr
    getServer6(const data::ServerTag& server_tag) const;

    /// @brief Creates or updates a subnet.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Subnet to be added or updated.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateSubnet6(const db::ServerSelector& server_selector,
                        const Subnet6Ptr& subnet);

    /// @brief Creates or updates a shared network.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network Shared network to be added or updated.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateSharedNetwork6(const db::ServerSelector& server_selector,
                               const SharedNetwork6Ptr& shared_network);

    /// @brief Creates or updates an option definition.
    ///
    /// @param server_selector Server selector.
    /// @param option_def Option definition to be added or updated.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateOptionDef6(const db::ServerSelector& server_selector,
                           const OptionDefinitionPtr& option_def);

    /// @brief Creates or updates global option.
    ///
    /// @param server_selector Server selector.
    /// @param option Option to be added or updated.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateOption6(const db::ServerSelector& server_selector,
                        const OptionDescriptorPtr& option);

    /// @brief Creates or updates shared network level option.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of a shared network to which option
    /// belongs.
    /// @param option Option to be added or updated.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateOption6(const db::ServerSelector& server_selector,
                        const std::string& shared_network_name,
                        const OptionDescriptorPtr& option);

    /// @brief Creates or updates subnet level option.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of a subnet to which option belongs.
    /// @param option Option to be added or updated.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateOption6(const db::ServerSelector& server_selector,
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
    createUpdateOption6(const db::ServerSelector& server_selector,
                        const asiolink::IOAddress& pool_start_address,
                        const asiolink::IOAddress& pool_end_address,
                        const OptionDescriptorPtr& option);

    /// @brief Creates or updates prefix delegation pool level option.
    ///
    /// @param server_selector Server selector.
    /// @param pd_pool_prefix Address part of the prefix of the prefix
    /// delegation pool to which the option belongs.
    /// @param pd_pool_prefix_length Prefix length of the prefix
    /// delegation pool to which the option belongs.
    /// @param option Option to be added or updated.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateOption6(const db::ServerSelector& server_selector,
                        const asiolink::IOAddress& pd_pool_prefix,
                        const uint8_t pd_pool_prefix_length,
                        const OptionDescriptorPtr& option);

    /// @brief Creates or updates global parameter.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the global parameter.
    /// @param value Value of the global parameter.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual void
    createUpdateGlobalParameter6(const db::ServerSelector& server_selector,
                                 const data::StampedValuePtr& value);

    /// @brief Creates or updates DHCPv6 client class.
    ///
    /// @param server_selector Server selector.
    /// @param client_class Client class to be added or updated.
    /// @param follow_class_name name of the class after which the
    /// new or updated class should be positioned. An empty value
    /// causes the class to be appended at the end of the class
    /// hierarchy.
    virtual void
    createUpdateClientClass6(const db::ServerSelector& server_selector,
                             const ClientClassDefPtr& client_class,
                             const std::string& follow_class_name);

    /// @brief Creates or updates a server.
    ///
    /// @param server Instance of the server to be stored.
    /// @throw InvalidOperation when trying to create a duplicate or
    /// update the logical server 'all'.
    virtual void
    createUpdateServer6(const db::ServerPtr& server);

    /// @brief Deletes subnet by prefix.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be deleted.
    /// @return Number of deleted subnets.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteSubnet6(const db::ServerSelector& server_selector,
                  const std::string& subnet_prefix);

    /// @brief Deletes subnet by identifier.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of the subnet to be deleted.
    /// @return Number of deleted subnets.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteSubnet6(const db::ServerSelector& server_selector, const SubnetID& subnet_id);

    /// @brief Deletes all subnets.
    ///
    /// @param server_selector Server selector.
    /// @return Number of deleted subnets.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteAllSubnets6(const db::ServerSelector& server_selector);

    /// @brief Deletes all subnets belonging to a specified shared network.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of the shared network for which the
    /// subnets should be deleted.
    /// @return Number of deleted subnets.
    virtual uint64_t
    deleteSharedNetworkSubnets6(const db::ServerSelector& server_selector,
                                const std::string& shared_network_name);

    /// @brief Deletes shared network by name.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the shared network to be deleted.
    /// @return Number of deleted shared networks.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteSharedNetwork6(const db::ServerSelector& server_selector,
                         const std::string& name);

    /// @brief Deletes all shared networks.
    ///
    /// @param server_selector Server selector.
    /// @return Number of deleted shared networks.
    virtual uint64_t
    deleteAllSharedNetworks6(const db::ServerSelector& server_selector);

    /// @brief Deletes option definition.
    ///
    /// @param server_selector Server selector.
    /// @param code Code of the option to be deleted.
    /// @param space Option space of the option to be deleted.
    /// @return Number of deleted option definitions.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteOptionDef6(const db::ServerSelector& server_selector, const uint16_t code,
                     const std::string& space);

    /// @brief Deletes all option definitions.
    ///
    /// @param server_selector Server selector.
    /// @return Number of deleted option definitions.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteAllOptionDefs6(const db::ServerSelector& server_selector);

    /// @brief Deletes global option.
    ///
    /// @param server_selector Server selector.
    /// @param code Code of the option to be deleted.
    /// @param space Option space of the option to be deleted.
    /// @return Number of deleted options.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteOption6(const db::ServerSelector& server_selector, const uint16_t code,
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
    deleteOption6(const db::ServerSelector& server_selector,
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
    deleteOption6(const db::ServerSelector& server_selector, const SubnetID& subnet_id,
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
    deleteOption6(const db::ServerSelector& server_selector,
                  const asiolink::IOAddress& pool_start_address,
                  const asiolink::IOAddress& pool_end_address,
                  const uint16_t code,
                  const std::string& space);

    /// @brief Deletes prefix delegation pool level option.
    ///
    /// @param server_selector Server selector.
    /// @param pool_start_address Lower bound address of the prefix
    /// delegation pool to which deleted option belongs.
    /// @param pool_end_address Upper bound address of the prefix
    /// delegation pool to which the deleted option belongs.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteOption6(const db::ServerSelector& server_selector,
                  const asiolink::IOAddress& pd_pool_prefix,
                  const uint8_t pd_pool_prefix_length,
                  const uint16_t code,
                  const std::string& space);

    /// @brief Deletes global parameter.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the global parameter to be deleted.
    /// @return Number of deleted global parameters.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteGlobalParameter6(const db::ServerSelector& server_selector,
                           const std::string& name);

    /// @brief Deletes all global parameters.
    ///
    /// @param server_selector Server selector.
    /// @return Number of deleted global parameters.
    /// @throw NotImplemented if server selector is "unassigned".
    virtual uint64_t
    deleteAllGlobalParameters6(const db::ServerSelector& server_selector);

    /// @brief Deletes DHCPv6 client class.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the class to be deleted.
    /// @return Number of deleted client classes.
    virtual uint64_t
    deleteClientClass6(const db::ServerSelector& server_selector,
                       const std::string& name);

    /// @brief Deletes all client classes.
    ///
    /// @param server_selector Server selector.
    /// @return Number of deleted client classes.
    virtual uint64_t
    deleteAllClientClasses6(const db::ServerSelector& server_selector);

    /// @brief Deletes a server from the backend.
    ///
    /// @param server_tag Tag of the server to be deleted.
    /// @return Number of deleted servers.
    /// @throw isc::InvalidOperation when trying to delete the logical
    /// server 'all'.
    virtual uint64_t
    deleteServer6(const data::ServerTag& server_tag);

    /// @brief Deletes all servers from the backend except the logical
    /// server 'all'.
    ///
    /// @return Number of deleted servers.
    virtual uint64_t
    deleteAllServers6();

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

    /// @brief Flag which indicates if the config backend has an unusable
    /// connection.
    ///
    /// @return true if there is at least one unusable connection, false
    /// otherwise
    virtual bool isUnusable();

    /// @brief Return backend parameters
    ///
    /// Returns the backend parameters
    ///
    /// @return Parameters of the backend.
    isc::db::DatabaseConnection::ParameterMap getParameters() const;

protected:

    /// @brief Pointer to the implementation of the @c MySqlConfigBackendDHCPv6
    /// class.
    boost::shared_ptr<MySqlConfigBackendDHCPv6Impl> impl_;

    /// @brief Pointer to the base implementation of the backend shared by
    /// DHCPv4 and DHCPv6 servers.
    boost::shared_ptr<MySqlConfigBackendImpl> base_impl_;
};

/// @brief Pointer to the @c MySqlConfigBackendDHCPv6 class.
typedef boost::shared_ptr<MySqlConfigBackendDHCPv6> MySqlConfigBackendDHCPv6Ptr;

} // end of namespace isc::cb
} // end of namespace isc

#endif // MYSQL_CONFIG_BACKEND_DHCP6_H
