// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CONFIG_BACKEND_DHCP4_H
#define CONFIG_BACKEND_DHCP4_H

#include <cc/stamped_value.h>
#include <config_backend/base_config_backend.h>
#include <database/audit_entry.h>
#include <database/server.h>
#include <database/server_collection.h>
#include <database/server_selector.h>
#include <dhcp/option.h>
#include <dhcp/option_definition.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/subnet.h>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Interface implemented by DHCPv4 configuration backends.
///
/// All POSIX times specified in the methods belonging to this
/// class must be local times.
///
/// Below, we describe the general rules of using the server selectors
/// when creating, updating, fetching and deleting the configuration
/// elements from the backends. The detailed information can be found
/// in the descriptions of the individual methods. The backend
/// implementations must not be in conflict with the rules described
/// here but may sometimes lack some functionality and not support
/// some of the server selectors for some API calls. In such cases
/// the backend's documentation should be clear about these cases
/// and document the exceptions thrown when unsupported selector is
/// used for a given method.
///
/// The @c ServerSelector class defines 5 types of selectors:
/// - ANY: server tag/id is not a part of the database query, i.e. the
///   object in the database is identified by some unique property,
///   e.g. subnet identifier, shared network name etc.
///
/// - UNASSIGNED: query pertains to the objects in the database which
///   are associated with no particular server (including the logical
///   server "all"). Objects associated with any server are never
///   selected.
///
/// - ALL: query pertains only to the objects in the database which are
///   associated with the logical server "all". Those objects are shared
///   between all servers using the database. This server selector never
///   returns objects explicitly associated with the particular servers
///   defined by the user.
///
/// - ONE: query pertains to the objects used by one particular server.
///   The server uses both the objects explicitly associated with it and
///   and the objects associated with the logical server "all". Therefore
///   the result returned for this server selector combines configuration
///   elements associated with this server and with "all" servers. In case
///   if there are two instances of the configuration information, one
///   associated with "all" servers and one associated with the server,
///   the information associated with the server takes precedence.
///   When using this selector to delete objects from the database, the
///   deletion pertains only to the objects associated with the given
///   server tag. It doesn't delete the objects associated with "all"
///   servers.
///
/// - MULTIPLE: query pertains to the objects used by multiple servers
///   listed in the selector. It allows for querying for a list of
///   objects associated with multiple servers and/or logical server
///   "all".
///
/// There are limitations imposed on the API calls what server selectors
/// are allowed for them. Configuration Backend implementations must not
/// be in conflict with those limitations. In particular, the implementation
/// must not permit for server selectors which are not allowed here.
/// However, the backend implementation may be more restrictive and not
/// allow some of the server selectors for some API calls. This should,
/// however, be properly documented.
class ConfigBackendDHCPv4 : public cb::BaseConfigBackend {
public:

    /// @brief Virtual destructor.
    virtual ~ConfigBackendDHCPv4() { }

    /// @brief Retrieves a single subnet by subnet_prefix.
    ///
    /// Allowed server selectors: ANY, UNASSIGNED, ALL, ONE.
    /// Not allowed server selector: MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be retrieved.
    /// @return Pointer to the retrieved subnet or NULL if not found.
    virtual Subnet4Ptr
    getSubnet4(const db::ServerSelector& server_selector,
               const std::string& subnet_prefix) const = 0;

    /// @brief Retrieves a single subnet by subnet identifier.
    ///
    /// Allowed server selectors: ANY, UNASSIGNED, ALL, ONE.
    /// Not allowed server selector: MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of a subnet to be retrieved.
    /// @return Pointer to the retrieved subnet or NULL if not found.
    virtual Subnet4Ptr
    getSubnet4(const db::ServerSelector& server_selector, const SubnetID& subnet_id) const = 0;

    /// @brief Retrieves all subnets.
    ///
    /// Allowed server selectors: UNASSIGNED, ALL, ONE, MULTIPLE.
    /// Not allowed server selector: ANY.
    ///
    /// @param server_selector Server selector.
    /// @return Collection of subnets or empty collection if no subnet found.
    virtual Subnet4Collection
    getAllSubnets4(const db::ServerSelector& server_selector) const = 0;

    /// @brief Retrieves all subnets belonging to a specified shared network.
    ///
    /// Allowed server selector: ANY.
    /// Not allowed server selectors: UNASSIGNED, ALL, ONE, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of the shared network for which the
    /// retrieved subnets should belongs to.
    /// @return Collection of subnets or empty collection if no subnet found.
    virtual Subnet4Collection
    getSharedNetworkSubnets4(const db::ServerSelector& server_selector,
                             const std::string& shared_network_name) const = 0;

    /// @brief Retrieves subnets modified after specified time.
    ///
    /// Allowed server selectors: UNASSIGNED, ALL, ONE, MULTIPLE.
    /// Not allowed server selector: ANY.
    ///
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound subnet modification time.
    /// @return Collection of subnets or empty collection if no subnet found.
    virtual Subnet4Collection
    getModifiedSubnets4(const db::ServerSelector& server_selector,
                        const boost::posix_time::ptime& modification_time) const = 0;

    /// @brief Retrieves shared network by name.
    ///
    /// Allowed server selectors: ANY, UNASSIGNED, ALL, ONE.
    /// Not allowed server selector: MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the shared network to be retrieved.
    /// @return Pointer to the shared network or NULL if not found.
    virtual SharedNetwork4Ptr
    getSharedNetwork4(const db::ServerSelector& server_selector,
                      const std::string& name) const = 0;

    /// @brief Retrieves all shared networks.
    ///
    /// Allowed server selectors: UNASSIGNED, ALL, ONE, MULTIPLE.
    /// Not allowed server selector: ANY.
    ///
    /// @param server_selector Server selector.
    /// @return Collection of shared network or empty collection if
    /// no shared network found.
    virtual SharedNetwork4Collection
    getAllSharedNetworks4(const db::ServerSelector& server_selector) const = 0;

    /// @brief Retrieves shared networks modified after specified time.
    ///
    /// Allowed server selectors: UNASSIGNED, ALL, ONE, MULTIPLE.
    /// Not allowed server selector: ANY.
    ///
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound shared network modification time.
    /// @return Collection of shared network or empty collection if
    /// no shared network found.
    virtual SharedNetwork4Collection
    getModifiedSharedNetworks4(const db::ServerSelector& server_selector,
                               const boost::posix_time::ptime& modification_time) const = 0;

    /// @brief Retrieves single option definition by code and space.
    ///
    /// Allowed server selectors: ALL, ONE.
    /// Not allowed server selectors: ANY, UNASSIGNED, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param code Code of the option to be retrieved.
    /// @param space Option space of the option to be retrieved.
    /// @return Pointer to the option definition or NULL if not found.
    virtual OptionDefinitionPtr
    getOptionDef4(const db::ServerSelector& server_selector, const uint16_t code,
                  const std::string& space) const = 0;

    /// @brief Retrieves all option definitions.
    ///
    /// Allowed server selectors: ALL, ONE, MULTIPLE.
    /// Not allowed server selectors: ANY, UNASSIGNED.
    ///
    /// @param server_selector Server selector.
    /// @return Collection of option definitions or empty collection if
    /// no option definition found.
    virtual OptionDefContainer
    getAllOptionDefs4(const db::ServerSelector& server_selector) const = 0;

    /// @brief Retrieves option definitions modified after specified time.
    ///
    /// Allowed server selectors: ALL, ONE, MULTIPLE.
    /// Not allowed server selectors: ANY, UNASSIGNED.
    ///
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound option definition modification
    /// time.
    /// @return Collection of option definitions or empty collection if
    /// no option definition found.
    virtual OptionDefContainer
    getModifiedOptionDefs4(const db::ServerSelector& server_selector,
                           const boost::posix_time::ptime& modification_time) const = 0;

    /// @brief Retrieves single option by code and space.
    ///
    /// Allowed server selectors: ALL, ONE.
    /// Not allowed server selectors: ANY, UNASSIGNED, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param code Option code.
    /// @param space Option space.
    /// @return Pointer to the retrieved option descriptor or null if
    /// no option was found.
    virtual OptionDescriptorPtr
    getOption4(const db::ServerSelector& server_selector, const uint16_t code,
               const std::string& space) const = 0;

    /// @brief Retrieves all global options.
    ///
    /// Allowed server selectors: ALL, ONE, MULTIPLE.
    /// Not allowed server selectors: ANY, UNASSIGNED.
    ///
    /// @param server_selector Server selector.
    /// @return Collection of global options or empty collection if no
    /// option found.
    virtual OptionContainer
    getAllOptions4(const db::ServerSelector& server_selector) const = 0;

    /// @brief Retrieves options modified after specified time.
    ///
    /// Allowed server selectors: ALL, ONE, MULTIPLE.
    /// Not allowed server selectors: ANY, UNASSIGNED.
    ///
    /// @param selector Server selector.
    /// @param modification_time Lower bound option modification time.
    /// @return Collection of global options or empty collection if no
    /// option found.
    virtual OptionContainer
    getModifiedOptions4(const db::ServerSelector& selector,
                        const boost::posix_time::ptime& modification_time) const = 0;

    /// @brief Retrieves global parameter value.
    ///
    /// Allowed server selectors: ALL, ONE.
    /// Not allowed server selectors: ANY, UNASSIGNED, MULTIPLE.
    ///
    /// @param selector Server selector.
    /// @param name Name of the global parameter to be retrieved.
    /// @return Value of the global parameter or null if parameter doesn't
    /// exist.
    virtual data::StampedValuePtr
    getGlobalParameter4(const db::ServerSelector& selector,
                        const std::string& name) const = 0;

    /// @brief Retrieves all global parameters.
    ///
    /// Allowed server selectors: ALL, ONE, MULTIPLE.
    /// Not allowed server selectors: ANY, UNASSIGNED.
    ///
    /// @param selector Server selector.
    /// @return Collection of global parameters.
    virtual data::StampedValueCollection
    getAllGlobalParameters4(const db::ServerSelector& selector) const = 0;

    /// @brief Retrieves global parameters modified after specified time.
    ///
    /// Allowed server selectors: ALL, ONE, MULTIPLE.
    /// Not allowed server selectors: ANY, UNASSIGNED.
    ///
    /// @param selector Server selector.
    /// @param modification_time Modification time.
    /// @return Collection of modified global parameters.
    virtual data::StampedValueCollection
    getModifiedGlobalParameters4(const db::ServerSelector& selector,
                                 const boost::posix_time::ptime& modification_time) const = 0;

    /// @brief Retrieves a client class by name.
    ///
    /// @param selector Server selector.
    /// @param name Client class name.
    /// @return Pointer to the retrieved client class.
    virtual ClientClassDefPtr
    getClientClass4(const db::ServerSelector& selector, const std::string& name) const = 0;

    /// @brief Retrieves all client classes.
    ///
    /// @param selector Server selector.
    /// @return Collection of client classes.
    virtual ClientClassDictionary
    getAllClientClasses4(const db::ServerSelector& selector) const = 0;

    /// @brief Retrieves client classes modified after specified time.
    ///
    /// @param selector Server selector.
    /// @param modification_time Modification time.
    /// @return Collection of client classes.
    virtual ClientClassDictionary
    getModifiedClientClasses4(const db::ServerSelector& selector,
                              const boost::posix_time::ptime& modification_time) const = 0;

    /// @brief Retrieves the most recent audit entries.
    ///
    /// Allowed server selectors: ALL, ONE.
    /// Not allowed server selectors: ANY, UNASSIGNED, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param modification_time Timestamp being a lower limit for the returned
    /// result set, i.e. entries later than specified time are returned.
    /// @param modification_id Identifier being a lower limit for the returned
    /// result set, used when two (or more) entries have the same
    /// modification_time.
    /// @return Collection of audit entries.
    virtual db::AuditEntryCollection
    getRecentAuditEntries(const db::ServerSelector& server_selector,
                          const boost::posix_time::ptime& modification_time,
                          const uint64_t& modification_id) const = 0;

    /// @brief Retrieves all servers.
    ///
    /// This method returns the list of servers excluding the logical server
    /// 'all'.
    ///
    /// @return Collection of servers from the backend.
    virtual db::ServerCollection
    getAllServers4() const = 0;

    /// @brief Retrieves a server.
    ///
    /// @param server_tag Tag of the server to be retrieved.
    /// @return Pointer to the server instance or null pointer if no server
    /// with the particular tag was found.
    virtual db::ServerPtr
    getServer4(const data::ServerTag& server_tag) const = 0;

    /// @brief Creates or updates a subnet.
    ///
    /// Allowed server selectors: UNASSIGNED, ALL, ONE, MULTIPLE.
    /// Not allowed server selector: ANY.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Subnet to be added or updated.
    virtual void
    createUpdateSubnet4(const db::ServerSelector& server_selector,
                        const Subnet4Ptr& subnet) = 0;

    /// @brief Creates or updates a shared network.
    ///
    /// Allowed server selectors: UNASSIGNED, ALL, ONE, MULTIPLE.
    /// Not allowed server selector: ANY.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network Shared network to be added or updated.
    virtual void
    createUpdateSharedNetwork4(const db::ServerSelector& server_selector,
                               const SharedNetwork4Ptr& shared_network) = 0;

    /// @brief Creates or updates an option definition.
    ///
    /// Allowed server selectors: ALL, ONE.
    /// Not allowed server selectors: ANY, UNASSIGNED, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param option_def Option definition to be added or updated.
    virtual void
    createUpdateOptionDef4(const db::ServerSelector& server_selector,
                           const OptionDefinitionPtr& option_def) = 0;

    /// @brief Creates or updates global option.
    ///
    /// Allowed server selectors: ALL, ONE.
    /// Not allowed server selectors: ANY, UNASSIGNED, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param option Option to be added or updated.
    virtual void
    createUpdateOption4(const db::ServerSelector& server_selector,
                        const OptionDescriptorPtr& option) = 0;

    /// @brief Creates or updates shared network level option.
    ///
    /// Allowed server selector: ANY.
    /// Not allowed server selectors: UNASSIGNED, ALL, ONE, MULTIPLE.
    ///
    /// @param selector Server selector.
    /// @param shared_network_name Name of a shared network to which option
    /// belongs.
    /// @param option Option to be added or updated.
    virtual void
    createUpdateOption4(const db::ServerSelector& selector,
                        const std::string& shared_network_name,
                        const OptionDescriptorPtr& option) = 0;

    /// @brief Creates or updates subnet level option.
    ///
    /// Allowed server selector: ANY.
    /// Not allowed server selectors: UNASSIGNED, ALL, ONE, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of a subnet to which option belongs.
    /// @param option Option to be added or updated.
    virtual void
    createUpdateOption4(const db::ServerSelector& server_selector,
                        const SubnetID& subnet_id,
                        const OptionDescriptorPtr& option) = 0;

    /// @brief Creates or updates pool level option.
    ///
    /// Allowed server selector: ANY.
    /// Not allowed server selectors: UNASSIGNED, ALL, ONE, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param pool_start_address Lower bound address of the pool to which
    /// the option belongs.
    /// @param pool_end_address Upper bound address of the pool to which the
    /// option belongs.
    /// @param option Option to be added or updated.
    virtual void
    createUpdateOption4(const db::ServerSelector& server_selector,
                        const asiolink::IOAddress& pool_start_address,
                        const asiolink::IOAddress& pool_end_address,
                        const OptionDescriptorPtr& option) = 0;

    /// @brief Creates or updates global parameter.
    ///
    /// Allowed server selectors: ALL, ONE.
    /// Not allowed server selectors: ANY, UNASSIGNED, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param value Value of the global parameter.
    virtual void
    createUpdateGlobalParameter4(const db::ServerSelector& server_selector,
                                 const data::StampedValuePtr& value) = 0;

    /// @brief Creates or updates DHCPv4 client class.
    ///
    /// @param server_selector Server selector.
    /// @param client_class Client class to be added or updated.
    /// @param follow_class_name name of the class after which the
    /// new or updated class should be positioned. An empty value
    /// causes the class to be appended at the end of the class
    /// hierarchy.
    virtual void
    createUpdateClientClass4(const db::ServerSelector& server_selector,
                             const ClientClassDefPtr& client_class,
                             const std::string& follow_class_name) = 0;

    /// @brief Creates or updates a server.
    ///
    /// @param server Instance of the server to be stored.
    virtual void
    createUpdateServer4(const db::ServerPtr& server) = 0;

    /// @brief Deletes subnet by prefix.
    ///
    /// Allowed server selectors: ANY, UNASSIGNED, ALL, ONE.
    /// Not allowed server selector: MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be deleted.
    /// @return Number of deleted subnets.
    virtual uint64_t
    deleteSubnet4(const db::ServerSelector& server_selector,
                  const std::string& subnet_prefix) = 0;

    /// @brief Deletes subnet by identifier.
    ///
    /// Allowed server selectors: ANY, UNASSIGNED, ALL, ONE.
    /// Not allowed server selector: MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of the subnet to be deleted.
    /// @return Number of deleted subnets.
    virtual uint64_t
    deleteSubnet4(const db::ServerSelector& server_selector, const SubnetID& subnet_id) = 0;

    /// @brief Deletes all subnets.
    ///
    /// Allowed server selectors: UNASSIGNED, ALL, ONE.
    /// Not allowed server selectors: ANY, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @return Number of deleted subnets.
    virtual uint64_t
    deleteAllSubnets4(const db::ServerSelector& server_selector) = 0;

    /// @brief Deletes all subnets belonging to a specified shared network.
    ///
    /// Allowed server selector: ANY.
    /// Not allowed server selectors: UNASSIGNED, ALL, ONE, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of the shared network for which the
    /// deleted subnets should belongs to.
    /// @return Number of deleted subnets.
    virtual uint64_t
    deleteSharedNetworkSubnets4(const db::ServerSelector& server_selector,
                                const std::string& shared_network_name) = 0;

    /// @brief Deletes shared network by name.
    ///
    /// Allowed server selectors: ANY, UNASSIGNED, ALL, ONE.
    /// Not allowed server selector: MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the shared network to be deleted.
    /// @return Number of deleted shared networks.
    virtual uint64_t
    deleteSharedNetwork4(const db::ServerSelector& server_selector,
                         const std::string& name) = 0;

    /// @brief Deletes all shared networks.
    ///
    /// Allowed server selectors: UNASSIGNED, ALL, ONE.
    /// Not allowed server selectors: ANY, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @return Number of deleted shared networks.
    virtual uint64_t
    deleteAllSharedNetworks4(const db::ServerSelector& server_selector) = 0;

    /// @brief Deletes option definition.
    ///
    /// Allowed server selectors: ALL, ONE.
    /// Not allowed server selectors: ANY, UNASSIGNED, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param code Code of the option to be deleted.
    /// @param space Option space of the option to be deleted.
    /// @return Number of deleted option definitions.
    virtual uint64_t
    deleteOptionDef4(const db::ServerSelector& server_selector,
                     const uint16_t code,
                     const std::string& space) = 0;

    /// @brief Deletes all option definitions.
    ///
    /// Allowed server selectors: ALL, ONE.
    /// Not allowed server selectors: ANY, UNASSIGNED, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @return Number of deleted option definitions.
    virtual uint64_t
    deleteAllOptionDefs4(const db::ServerSelector& server_selector) = 0;

    /// @brief Deletes global option.
    ///
    /// Allowed server selectors: ALL, ONE.
    /// Not allowed server selectors: ANY, UNASSIGNED, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param code Code of the option to be deleted.
    /// @param space Option space of the option to be deleted.
    /// @return Number of deleted options.
    virtual uint64_t
    deleteOption4(const db::ServerSelector& server_selector,
                  const uint16_t code,
                  const std::string& space) = 0;

    /// @brief Deletes shared network level option.
    ///
    /// Allowed server selector: ANY.
    /// Not allowed server selectors: UNASSIGNED, ALL, ONE, MULTIPLE.
    ///
    /// @param selector Server selector.
    /// @param shared_network_name Name of the shared network which option
    /// belongs to.
    /// @param code Code of the option to be deleted.
    /// @param space Option space of the option to be deleted.
    virtual uint64_t
    deleteOption4(const db::ServerSelector& selector,
                  const std::string& shared_network_name,
                  const uint16_t code,
                  const std::string& space) = 0;

    /// @brief Deletes subnet level option.
    ///
    /// Allowed server selector: ANY.
    /// Not allowed server selectors: UNASSIGNED, ALL, ONE, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of the subnet to which deleted option
    /// belongs.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    virtual uint64_t
    deleteOption4(const db::ServerSelector& server_selector,
                  const SubnetID& subnet_id,
                  const uint16_t code,
                  const std::string& space) = 0;

    /// @brief Deletes pool level option.
    ///
    /// Allowed server selector: ANY.
    /// Not allowed server selectors: UNASSIGNED, ALL, ONE, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param pool_start_address Lower bound address of the pool to which
    /// deleted option belongs.
    /// @param pool_end_address Upper bound address of the pool to which the
    /// deleted option belongs.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    virtual uint64_t
    deleteOption4(const db::ServerSelector& server_selector,
                  const asiolink::IOAddress& pool_start_address,
                  const asiolink::IOAddress& pool_end_address,
                  const uint16_t code,
                  const std::string& space) = 0;

    /// @brief Deletes global parameter.
    ///
    /// Allowed server selectors: ALL, ONE.
    /// Not allowed server selectors: ANY, UNASSIGNED, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the global parameter to be deleted.
    /// @return Number of deleted global parameters.
    virtual uint64_t
    deleteGlobalParameter4(const db::ServerSelector& server_selector,
                           const std::string& name) = 0;

    /// @brief Deletes all global parameters.
    ///
    /// Allowed server selectors: ALL, ONE.
    /// Not allowed server selectors: ANY, UNASSIGNED, MULTIPLE.
    ///
    /// @param server_selector Server selector.
    /// @return Number of deleted global parameters.
    virtual uint64_t
    deleteAllGlobalParameters4(const db::ServerSelector& server_selector) = 0;

    /// @brief Deletes DHCPv4 client class.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the class to be deleted.
    /// @return Number of deleted client classes.
    virtual uint64_t
    deleteClientClass4(const db::ServerSelector& server_selector,
                       const std::string& name) = 0;

    /// @brief Deletes all client classes.
    ///
    /// @param server_selector Server selector.
    /// @return Number of deleted client classes.
    virtual uint64_t
    deleteAllClientClasses4(const db::ServerSelector& server_selector) = 0;

    /// @brief Deletes a server from the backend.
    ///
    /// @param server_tag Tag of the server to be deleted.
    /// @return Number of deleted servers.
    virtual uint64_t
    deleteServer4(const data::ServerTag& server_tag) = 0;

    /// @brief Deletes all servers from the backend except the logical
    /// server 'all'.
    ///
    /// @return Number of deleted servers.
    virtual uint64_t
    deleteAllServers4() = 0;
};

/// @brief Shared pointer to the @c ConfigBackendDHCPv4 instance.
typedef boost::shared_ptr<ConfigBackendDHCPv4> ConfigBackendDHCPv4Ptr;

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // CONFIG_BACKEND_DHCP4_H
