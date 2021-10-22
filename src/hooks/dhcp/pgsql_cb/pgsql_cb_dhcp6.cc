// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <pgsql_cb_dhcp6.h>
#include <pgsql_cb_impl.h>
#include <pgsql_macros.h>
#include <asiolink/addr_utilities.h>
#include <cc/data.h>
#include <config_backend/constants.h>
#include <database/database_connection.h>
#include <database/db_exceptions.h>
#include <dhcp/classify.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_data_types.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/config_backend_dhcp6_mgr.h>
#include <dhcpsrv/network.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/timer_mgr.h>
#include <util/buffer.h>
#include <util/boost_time_utils.h>
#include <pgsql/pgsql_connection.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <array>
#include <sstream>
#include <utility>
#include <vector>

using namespace isc::cb;
using namespace isc::db;
using namespace isc::data;
using namespace isc::asiolink;
using namespace isc::log;
using namespace isc::util;

namespace isc {
namespace dhcp {

/// @brief Implementation of the Postgres Configuration Backend.
class PgSqlConfigBackendDHCPv6Impl : public PgSqlConfigBackendImpl {
public:

    /// @brief Statement tags.
    ///
    /// The contents of the enum are indexes into the list of SQL statements.
    /// It is assumed that the order is such that the indices of statements
    /// reading the database are less than those of statements modifying the
    /// database.
    enum StatementIndex {
        CREATE_AUDIT_REVISION,
        GET_GLOBAL_PARAMETER6,
        GET_ALL_GLOBAL_PARAMETERS6,
        GET_MODIFIED_GLOBAL_PARAMETERS6,
        GET_SUBNET6_ID_NO_TAG,
        GET_SUBNET6_ID_ANY,
        GET_SUBNET6_ID_UNASSIGNED,
        GET_SUBNET6_PREFIX_NO_TAG,
        GET_SUBNET6_PREFIX_ANY,
        GET_SUBNET6_PREFIX_UNASSIGNED,
        GET_ALL_SUBNETS6,
        GET_ALL_SUBNETS6_UNASSIGNED,
        GET_MODIFIED_SUBNETS6,
        GET_MODIFIED_SUBNETS6_UNASSIGNED,
        GET_SHARED_NETWORK_SUBNETS6,
        GET_POOL6_RANGE,
        GET_POOL6_RANGE_ANY,
        GET_PD_POOL,
        GET_PD_POOL_ANY,
        GET_SHARED_NETWORK6_NAME_NO_TAG,
        GET_SHARED_NETWORK6_NAME_ANY,
        GET_SHARED_NETWORK6_NAME_UNASSIGNED,
        GET_ALL_SHARED_NETWORKS6,
        GET_ALL_SHARED_NETWORKS6_UNASSIGNED,
        GET_MODIFIED_SHARED_NETWORKS6,
        GET_MODIFIED_SHARED_NETWORKS6_UNASSIGNED,
        GET_OPTION_DEF6_CODE_SPACE,
        GET_ALL_OPTION_DEFS6,
        GET_MODIFIED_OPTION_DEFS6,
        GET_OPTION6_CODE_SPACE,
        GET_ALL_OPTIONS6,
        GET_MODIFIED_OPTIONS6,
        GET_OPTION6_SUBNET_ID_CODE_SPACE,
        GET_OPTION6_POOL_ID_CODE_SPACE,
        GET_OPTION6_PD_POOL_ID_CODE_SPACE,
        GET_OPTION6_SHARED_NETWORK_CODE_SPACE,
        GET_AUDIT_ENTRIES6_TIME,
        GET_SERVER6,
        GET_ALL_SERVERS6,
        INSERT_GLOBAL_PARAMETER6,
        INSERT_GLOBAL_PARAMETER6_SERVER,
        INSERT_SUBNET6,
        INSERT_SUBNET6_SERVER,
        INSERT_POOL6,
        INSERT_PD_POOL,
        INSERT_SHARED_NETWORK6,
        INSERT_SHARED_NETWORK6_SERVER,
        INSERT_OPTION_DEF6,
        INSERT_OPTION_DEF6_SERVER,
        INSERT_OPTION6,
        INSERT_OPTION6_SERVER,
        INSERT_SERVER6,
        UPDATE_GLOBAL_PARAMETER6,
        UPDATE_SUBNET6,
        UPDATE_SHARED_NETWORK6,
        UPDATE_OPTION_DEF6,
        UPDATE_OPTION6,
        UPDATE_OPTION6_SUBNET_ID,
        UPDATE_OPTION6_POOL_ID,
        UPDATE_OPTION6_PD_POOL_ID,
        UPDATE_OPTION6_SHARED_NETWORK,
        UPDATE_SERVER6,
        DELETE_GLOBAL_PARAMETER6,
        DELETE_ALL_GLOBAL_PARAMETERS6,
        DELETE_ALL_GLOBAL_PARAMETERS6_UNASSIGNED,
        DELETE_SUBNET6_ID_WITH_TAG,
        DELETE_SUBNET6_ID_ANY,
        DELETE_SUBNET6_PREFIX_WITH_TAG,
        DELETE_SUBNET6_PREFIX_ANY,
        DELETE_ALL_SUBNETS6,
        DELETE_ALL_SUBNETS6_UNASSIGNED,
        DELETE_ALL_SUBNETS6_SHARED_NETWORK_NAME,
        DELETE_SUBNET6_SERVER,
        DELETE_POOLS6,
        DELETE_PD_POOLS,
        DELETE_SHARED_NETWORK6_NAME_WITH_TAG,
        DELETE_SHARED_NETWORK6_NAME_ANY,
        DELETE_ALL_SHARED_NETWORKS6,
        DELETE_ALL_SHARED_NETWORKS6_UNASSIGNED,
        DELETE_SHARED_NETWORK6_SERVER,
        DELETE_OPTION_DEF6_CODE_NAME,
        DELETE_ALL_OPTION_DEFS6,
        DELETE_ALL_OPTION_DEFS6_UNASSIGNED,
        DELETE_OPTION6,
        DELETE_ALL_GLOBAL_OPTIONS6_UNASSIGNED,
        DELETE_OPTION6_SUBNET_ID,
        DELETE_OPTION6_POOL_RANGE,
        DELETE_OPTION6_PD_POOL,
        DELETE_OPTION6_SHARED_NETWORK,
        DELETE_OPTIONS6_SUBNET_ID_PREFIX,
        DELETE_OPTIONS6_SHARED_NETWORK,
        DELETE_SERVER6,
        DELETE_ALL_SERVERS6,
        NUM_STATEMENTS
    };

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    explicit PgSqlConfigBackendDHCPv6Impl(const DatabaseConnection::ParameterMap&
                                          parameters);

    /// @brief Destructor.
    ~PgSqlConfigBackendDHCPv6Impl();

    /// @brief Sends query to retrieve global parameter.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the parameter to be retrieved.
    ///
    /// @return Pointer to the retrieved value or null if such parameter
    /// doesn't exist.
    StampedValuePtr getGlobalParameter6(const ServerSelector& server_selector,
                                        const std::string& name) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to insert or update global parameter.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the global parameter.
    /// @param value Value of the global parameter.
    void createUpdateGlobalParameter6(const db::ServerSelector& server_selector,
                                      const StampedValuePtr& value) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve single subnet by id.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Pointer to the returned subnet or NULL if such subnet
    /// doesn't exist.
    Subnet6Ptr getSubnet6(const ServerSelector& server_selector,
                          const SubnetID& subnet_id) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve single subnet by prefix.
    ///
    /// The prefix should be in the following format: "2001:db8:1::/64".
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Pointer to the returned subnet or NULL if such subnet
    /// doesn't exist.
    Subnet6Ptr getSubnet6(const ServerSelector& server_selector,
                          const std::string& subnet_prefix) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve all subnets.
    ///
    /// @param server_selector Server selector.
    /// @param [out] subnets Reference to the subnet collection structure where
    /// subnets should be inserted.
    void getAllSubnets6(const ServerSelector& server_selector,
                        Subnet6Collection& subnets) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve modified subnets.
    ///
    /// @param server_selector Server selector.
    /// @param modification_ts Lower bound modification timestamp.
    /// @param [out] subnets Reference to the subnet collection structure where
    /// subnets should be inserted.
    void getModifiedSubnets6(const ServerSelector& server_selector,
                             const boost::posix_time::ptime& modification_ts,
                             Subnet6Collection& subnets) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve all subnets belonging to a shared network.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of the shared network for which the
    /// subnets should be retrieved.
    /// @param [out] subnets Reference to the subnet collection structure where
    /// subnets should be inserted.
    void getSharedNetworkSubnets6(const ServerSelector& server_selector,
                                  const std::string& shared_network_name,
                                  Subnet6Collection& subnets) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve multiple pools.
    ///
    /// Query should order pools by id.
    ///
    /// @param index Index of the query to be used.
    /// @param in_bindings Input bindings specifying selection criteria. The
    /// size of the bindings collection must match the number of placeholders
    /// in the prepared statement. The input bindings collection must be empty
    /// if the query contains no WHERE clause.
    /// @param [out] pools Reference to the container where fetched pools
    /// will be inserted.
    /// @param [out] pool_ids Identifiers of the pools returned in @c pools
    /// argument.
    /// @todo: add void getPools(const StatementIndex& index, const MySqlBindingCollection& in_bindings,
    /// PoolCollection& pools, std::vector<uint64_t>& pool_ids) {

    /// @brief Sends query to retrieve multiple pd pools.
    ///
    /// Query should order pd pools by id.
    ///
    /// @param index Index of the query to be used.
    /// @param in_bindings Input bindings specifying selection criteria. The
    /// size of the bindings collection must match the number of placeholders
    /// in the prepared statement. The input bindings collection must be empty
    /// if the query contains no WHERE clause.
    /// @param [out] pd_pools Reference to the container where fetched pools
    /// will be inserted.
    /// @param [out] pd_pool_ids Identifiers of the pd pools returned in
    /// @c pd_pools argument.
    /// @todo add: void getPdPools(const StatementIndex& index, const MySqlBindingCollection& in_bindings,
    ///       PoolCollection& pd_pools, std::vector<uint64_t>& pd_pool_ids) {

    /// @brief Sends query to retrieve single pool by address range.
    ///
    /// @param server_selector Server selector.
    /// @param pool_start_address Lower bound pool address.
    /// @param pool_end_address Upper bound pool address.
    /// @param pool_id Pool identifier for the returned pool.
    /// @return Pointer to the pool or null if no such pool found.
    Pool6Ptr getPool6(const ServerSelector& server_selector,
                      const IOAddress& pool_start_address,
                      const IOAddress& pool_end_address,
                      uint64_t& pool_id) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve single pd pool.
    ///
    /// @param server_selector Server selector.
    /// @param pd_pool_prefix Address part of the pd pool prefix.
    /// @param pd_pool_prefix_length Length of the pd pool prefix.
    /// @param pd_pool_id Pool identifier for the returned pool.
    /// @return Pointer to the pool or null if no such pool found.
    Pool6Ptr getPdPool6(const ServerSelector& server_selector,
                        const asiolink::IOAddress& pd_pool_prefix,
                        const uint8_t pd_pool_prefix_length,
                        uint64_t& pd_pool_id) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to insert or update subnet.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Pointer to the subnet to be inserted or updated.
    void createUpdateSubnet6(const ServerSelector& server_selector,
                             const Subnet6Ptr& subnet) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Inserts new IPv6 pool to the database.
    ///
    /// @param server_selector Server selector.
    /// @param pool Pointer to the pool to be inserted.
    /// @param subnet Pointer to the subnet that this pool belongs to.
    void createPool6(const ServerSelector& server_selector, const Pool6Ptr& pool,
                     const Subnet6Ptr& subnet) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Inserts new IPv6 pd pool to the database.
    ///
    /// @param server_selector Server selector.
    /// @param pd_pool Pointer to the pd pool to be inserted.
    /// @param subnet Pointer to the subnet that this pd pool belongs to.
    void createPdPool6(const ServerSelector& server_selector,
                       const Pool6Ptr& pd_pool,
                       const Subnet6Ptr& subnet) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends a query to delete data from a table.
    ///
    /// If creates a new audit revision for this change if such audit
    /// revision doesn't exist yet (using ScopedAuditRevision mechanism).
    ///
    /// @tparam Args type of the arguments to be passed to one of the existing
    /// @c deleteFromTable methods.
    /// @param server_selector server selector.
    /// @param operation operation which results in calling this function. This is
    /// used for logging purposes.
    /// @param log_message log message to be associated with the audit revision.
    /// @param cascade_delete boolean flag indicating if we're performing
    /// cascade delete. If set to true, the audit entries for the child
    /// objects (e.g. DHCPoptions) won't be created.
    /// @param keys arguments to be passed to one of the existing
    /// @c deleteFromTable methods.
    ///
    /// @return Number of deleted entries.
    template<typename... Args>
    uint64_t deleteTransactional(const int index,
                                 const db::ServerSelector& server_selector,
                                 const std::string& operation,
                                 const std::string& log_message,
                                 const bool cascade_delete,
                                 Args&&... keys) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to delete subnet by id.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of the subnet to be deleted.
    /// @return Number of deleted subnets.
    uint64_t deleteSubnet6(const ServerSelector& server_selector,
                           const SubnetID& subnet_id) {
        int index = (server_selector.amAny() ?
                     PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_ID_ANY :
                     PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_ID_WITH_TAG);
        return (deleteTransactional(index, server_selector,
                                    "deleting a subnet", "subnet deleted",
                                    true, static_cast<uint32_t>(subnet_id)));
    }

    /// @brief Sends query to delete subnet by id.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be deleted.
    /// @return Number of deleted subnets.
    uint64_t deleteSubnet6(const ServerSelector& server_selector,
                           const std::string& subnet_prefix) {
        int index = (server_selector.amAny() ?
                     PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_PREFIX_ANY :
                     PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_PREFIX_WITH_TAG);
        return (deleteTransactional(index, server_selector,
                                    "deleting a subnet", "subnet deleted",
                                    true, subnet_prefix));
    }

    /// @brief Deletes pools belonging to a subnet from the database.
    ///
    /// The query deletes all pools associated with the subnet's
    /// identifier or prefix.
    /// @param subnet Pointer to the subnet for which pools should be
    /// deleted.
    uint64_t deletePools6(const Subnet6Ptr& subnet) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Deletes prefix delegation pools belonging to a subnet from
    /// the database.
    ///
    /// The query deletes all pd pools associated with the subnet's
    /// identifier or prefix.
    /// @param subnet Pointer to the subnet for which pd pools should be
    /// deleted.
    uint64_t deletePdPools6(const Subnet6Ptr& subnet) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to the database to retrieve multiple shared
    /// networks.
    ///
    /// Query should order shared networks by id.
    ///
    /// @param index Index of the query to be used.
    /// @param server_selector Server selector.
    /// @param in_bindings Input bindings specifying selection criteria. The
    /// size of the bindings collection must match the number of placeholders
    /// in the prepared statement. The input bindings collection must be empty
    /// if the query contains no WHERE clause.
    /// @param [out] shared_networks Reference to the container where fetched
    /// shared networks will be inserted.
    /// @todo: implement void getSharedNetworks6(const StatementIndex& index,
///                            const ServerSelector& server_selector,
///                            const MySqlBindingCollection& in_bindings,
                            ///SharedNetwork6Collection& shared_networks) {

    /// @brief Sends query to retrieve single shared network by name.
    ///
    /// @param server_selector Server selector.
    /// @param name Shared network name.
    ///
    /// @return Pointer to the returned shared network or NULL if such shared
    /// network doesn't exist.
    SharedNetwork6Ptr getSharedNetwork6(const ServerSelector& server_selector,
                                        const std::string& name) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve all shared networks.
    ///
    /// @param server_selector Server selector.
    /// @param [out] shared_networks Reference to the shared networks collection
    /// structure where shared networks should be inserted.
    void getAllSharedNetworks6(const ServerSelector& server_selector,
                               SharedNetwork6Collection& shared_networks) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve modified shared networks.
    ///
    /// @param server_selector Server selector.
    /// @param modification_ts Lower bound modification timestamp.
    /// @param [out] shared_networks Reference to the shared networks collection
    /// structure where shared networks should be inserted.
    void getModifiedSharedNetworks6(const ServerSelector& server_selector,
                                    const boost::posix_time::ptime& modification_ts,
                                    SharedNetwork6Collection& shared_networks) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to insert or update shared network.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Pointer to the shared network to be inserted or updated.
    void createUpdateSharedNetwork6(const ServerSelector& server_selector,
                                    const SharedNetwork6Ptr& shared_network) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }


    /// @brief Sends query to insert DHCP option.
    ///
    /// This method expects that the server selector contains exactly one
    /// server tag.
    ///
    /// @param server_selector Server selector.
    /// @param in_bindings Collection of bindings representing an option.
    /// @todo: implement void insertOption6(const ServerSelector& server_selector,
    ///                       const MySqlBindingCollection& in_bindings) {

    /// @brief Sends query to insert or update global DHCP option.
    ///
    /// @param server_selector Server selector.
    /// @param option Pointer to the option descriptor encapsulating the option.
    void createUpdateOption6(const ServerSelector& server_selector,
                             const OptionDescriptorPtr& option) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to insert or update DHCP option in a subnet.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of the subnet the option belongs to.
    /// @param option Pointer to the option descriptor encapsulating the option.
    /// @param cascade_update Boolean value indicating whether the update is
    /// performed as part of the owning element, e.g. subnet.
    void createUpdateOption6(const ServerSelector& server_selector,
                             const SubnetID& subnet_id,
                             const OptionDescriptorPtr& option,
                             const bool cascade_update) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to insert or update DHCP option in a pool.
    ///
    /// @param server_selector Server selector.
    /// @param pool_start_address Lower bound address of the pool.
    /// @param pool_end_address Upper bound address of the pool.
    /// @param option Pointer to the option descriptor encapsulating the option.
    void createUpdateOption6(const ServerSelector& server_selector,
                             const IOAddress& pool_start_address,
                             const IOAddress& pool_end_address,
                             const OptionDescriptorPtr& option) {
        uint64_t pool_id = 0;
        Pool6Ptr pool = getPool6(server_selector, pool_start_address, pool_end_address,
                                 pool_id);
        if (!pool) {
            isc_throw(BadValue, "no pool found for range of "
                      << pool_start_address << " : "
                      << pool_end_address);
        }

        createUpdateOption6(server_selector, Lease::TYPE_NA,
                            pool_id, option, false);
    }


    /// @brief Sends query to insert or update DHCP option in a pd pool.
    ///
    /// @param server_selector Server selector.
    /// @param pd_pool_prefix Address part of the pd pool prefix.
    /// @param pd_pool_prefix_length Length of the pd pool prefix.
    /// @param option Pointer to the option descriptor encapsulating the option.
    void createUpdateOption6(const ServerSelector& server_selector,
                             const asiolink::IOAddress& pd_pool_prefix,
                             const uint8_t pd_pool_prefix_length,
                             const OptionDescriptorPtr& option) {
        uint64_t pd_pool_id = 0;
        Pool6Ptr pd_pool = getPdPool6(server_selector,
                                      pd_pool_prefix,
                                      pd_pool_prefix_length,
                                      pd_pool_id);
        if (!pd_pool) {
            isc_throw(BadValue, "no prefix delegation pool found for prefix "
                      << "of " << pd_pool_prefix << "/"
                      << static_cast<unsigned>(pd_pool_prefix_length));
        }

        createUpdateOption6(server_selector, Lease::TYPE_PD,
                            pd_pool_id, option, false);
    }


    /// @brief Sends query to insert or update DHCP option in an address
    /// or prefix delegation pool.
    ///
    /// @param selector Server selector.
    /// @param pool_type Pool type (Lease::TYPE_NA or Lease::TYPE_PD).
    /// @param pool_id Identifier of the address or prefix delegation pool
    /// the option belongs to.
    /// @param option Pointer to the option descriptor encapsulating the option.
    /// @param cascade_update Boolean value indicating whether the update is
    /// performed as part of the owning element, e.g. subnet.
    void createUpdateOption6(const ServerSelector& server_selector,
                             const Lease::Type& pool_type,
                             const uint64_t pool_id,
                             const OptionDescriptorPtr& option,
                             const bool cascade_update) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to insert or update DHCP option in a shared network.
    ///
    /// @param selector Server selector.
    /// @param shared_network_name Name of the shared network the option
    /// belongs to.
    /// @param option Pointer to the option descriptor encapsulating the option.
    /// @param cascade_update Boolean value indicating whether the update is
    /// performed as part of the owning element, e.g. shared network.
    void createUpdateOption6(const ServerSelector& server_selector,
                             const std::string& shared_network_name,
                             const OptionDescriptorPtr& option,
                             const bool cascade_update) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to insert or update option definition.
    ///
    /// @param server_selector Server selector.
    /// @param option_def Pointer to the option definition to be inserted or updated.
    void createUpdateOptionDef6(const ServerSelector& server_selector,
                                const OptionDefinitionPtr& option_def) {

        createUpdateOptionDef(server_selector, option_def, DHCP6_OPTION_SPACE,
                              PgSqlConfigBackendDHCPv6Impl::GET_OPTION_DEF6_CODE_SPACE,
                              PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6,
                              PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION_DEF6,
                              PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                              PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6_SERVER);
    }

    /// @brief Sends query to delete option definition by code and
    /// option space name.
    ///
    /// @param server_selector Server selector.
    /// @param code Option code.
    /// @param name Option name.
    /// @return Number of deleted option definitions.
    uint64_t deleteOptionDef6(const ServerSelector& server_selector,
                              const uint16_t code,
                              const std::string& space) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Deletes global option.
    ///
    /// @param server_selector Server selector.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    uint64_t deleteOption6(const ServerSelector& server_selector,
                           const uint16_t code,
                           const std::string& space) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Deletes subnet level option.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of the subnet to which deleted option
    /// belongs.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    uint64_t deleteOption6(const ServerSelector& server_selector,
                           const SubnetID& subnet_id,
                           const uint16_t code,
                           const std::string& space) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Deletes pool level option.
    ///
    /// @param server_selector Server selector.
    /// @param pool_start_address Lower bound pool address.
    /// @param pool_end_address  Upper bound pool address.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    uint64_t deleteOption6(const db::ServerSelector& server_selector,
                           const IOAddress& pool_start_address,
                           const IOAddress& pool_end_address,
                           const uint16_t code,
                           const std::string& space) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Deletes pd pool level option.
    ///
    /// @param server_selector Server selector.
    /// @param pd_pool_prefix Address part of the pd pool prefix.
    /// @param pd_pool_prefix_length Length of the pd pool prefix.
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    uint64_t deleteOption6(const db::ServerSelector& server_selector,
                           const asiolink::IOAddress& pd_pool_prefix,
                           const uint8_t pd_pool_prefix_length,
                           const uint16_t code,
                           const std::string& space) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Deletes shared network level option.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of the shared network which deleted
    /// option belongs to
    /// @param code Code of the deleted option.
    /// @param space Option space of the deleted option.
    /// @return Number of deleted options.
    uint64_t deleteOption6(const db::ServerSelector& server_selector,
                           const std::string& shared_network_name,
                           const uint16_t code,
                           const std::string& space) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Deletes options belonging to a subnet from the database.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Pointer to the subnet for which options should be
    /// deleted.
    /// @return Number of deleted options.
    uint64_t deleteOptions6(const ServerSelector& server_selector,
                            const Subnet6Ptr& subnet) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Deletes options belonging to a shared network from the database.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Pointer to the subnet for which options should be
    /// deleted.
    /// @return Number of deleted options.
    uint64_t deleteOptions6(const ServerSelector& server_selector,
                            const SharedNetwork6Ptr& shared_network) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Removes unassigned global parameters, global options and
    /// option definitions.
    ///
    /// This function is called when one or more servers are deleted and
    /// it is likely that there are some orphaned configuration elements
    /// left in the database. This method removes those elements.
    void purgeUnassignedConfig() {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Attempts to delete a server having a given tag.
    ///
    /// @param server_tag Tag of the server to be deleted.
    /// @return Number of deleted servers.
    /// @throw isc::InvalidOperation when trying to delete the logical
    /// server 'all'.
    uint64_t deleteServer6(const data::ServerTag& server_tag) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Attempts to delete all servers.
    ///
    /// This method deletes all servers added by the user. It does not
    /// delete the logical server 'all'.
    ///
    /// @return Number of deleted servers.
    uint64_t deleteAllServers6() {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Attempts to reconnect the server to the config DB backend manager.
    ///
    /// This is a self-rescheduling function that attempts to reconnect to the
    /// server's config DB backends after connectivity to one or more have been
    /// lost. Upon entry it will attempt to reconnect via
    /// @ref ConfigBackendDHCPv6Mgr.addBackend.
    /// If this is successful, DHCP servicing is re-enabled and server returns
    /// to normal operation.
    ///
    /// If reconnection fails and the maximum number of retries has not been
    /// exhausted, it will schedule a call to itself to occur at the
    /// configured retry interval. DHCP service remains disabled.
    ///
    /// If the maximum number of retries has been exhausted an error is logged
    /// and the server shuts down.
    ///
    /// @param db_reconnect_ctl pointer to the ReconnectCtl containing the
    /// configured reconnect parameters.
    /// @return true if connection has been recovered, false otherwise.
    static bool dbReconnect(ReconnectCtlPtr db_reconnect_ctl) {
        // Invoke application layer connection lost callback.
        if (!DatabaseConnection::invokeDbLostCallback(db_reconnect_ctl)) {
            return (false);
        }

        bool reopened = false;

        const std::string timer_name = db_reconnect_ctl->timerName();

        // At least one connection was lost.
        try {
            auto srv_cfg = CfgMgr::instance().getCurrentCfg();
            auto config_ctl = srv_cfg->getConfigControlInfo();
            // Iterate over the configured DBs and instantiate them.
            for (auto db : config_ctl->getConfigDatabases()) {
                const std::string& access = db.getAccessString();
                auto parameters = db.getParameters();
                if (ConfigBackendDHCPv6Mgr::instance().delBackend(parameters["type"], access, true)) {
                    ConfigBackendDHCPv6Mgr::instance().addBackend(db.getAccessString());
                }
            }

            reopened = true;
        } catch (const std::exception& ex) {
            LOG_ERROR(pgsql_cb_logger, PGSQL_CB_RECONNECT_ATTEMPT_FAILED6)
                    .arg(ex.what());
        }

        if (reopened) {
            // Cancel the timer.
            if (TimerMgr::instance()->isTimerRegistered(timer_name)) {
                TimerMgr::instance()->unregisterTimer(timer_name);
            }

            // Invoke application layer connection recovered callback.
            if (!DatabaseConnection::invokeDbRecoveredCallback(db_reconnect_ctl)) {
                return (false);
            }
        } else {
            if (!db_reconnect_ctl->checkRetries()) {
                // We're out of retries, log it and initiate shutdown.
                LOG_ERROR(pgsql_cb_logger, PGSQL_CB_RECONNECT_FAILED6)
                        .arg(db_reconnect_ctl->maxRetries());

                // Cancel the timer.
                if (TimerMgr::instance()->isTimerRegistered(timer_name)) {
                    TimerMgr::instance()->unregisterTimer(timer_name);
                }

                // Invoke application layer connection failed callback.
                DatabaseConnection::invokeDbFailedCallback(db_reconnect_ctl);

                return (false);
            }

            LOG_INFO(pgsql_cb_logger, PGSQL_CB_RECONNECT_ATTEMPT_SCHEDULE6)
                    .arg(db_reconnect_ctl->maxRetries() - db_reconnect_ctl->retriesLeft() + 1)
                    .arg(db_reconnect_ctl->maxRetries())
                    .arg(db_reconnect_ctl->retryInterval());

            // Start the timer.
            if (!TimerMgr::instance()->isTimerRegistered(timer_name)) {
                TimerMgr::instance()->registerTimer(timer_name,
                    std::bind(&PgSqlConfigBackendDHCPv6Impl::dbReconnect, db_reconnect_ctl),
                              db_reconnect_ctl->retryInterval(),
                              asiolink::IntervalTimer::ONE_SHOT);
            }
            TimerMgr::instance()->setup(timer_name);
        }

        return (true);
    }

};

namespace {

/// @brief Array of tagged statements.
typedef std::array<PgSqlTaggedStatement, PgSqlConfigBackendDHCPv6Impl::NUM_STATEMENTS>
PgSqlTaggedStatementArray;

/// @brief Prepared Postgres statements used by the backend to insert and
/// retrieve data from the database.
PgSqlTaggedStatementArray tagged_statements = { {
    { 4, { OID_INT8, OID_INT8, OID_INT8, OID_INT8 }, "CREATE_AUDIT_REVISION",
      "CALL createAuditRevisionDHCP6(?, ?, ?, ?)"
    },

    // Select global parameter by name.
    { 1, { OID_VARCHAR }, "GET_GLOBAL_PARAMETER6",
      PGSQL_GET_GLOBAL_PARAMETER(dhcp6, AND g.name = ?)
    }
}};

#if 0
    // Select all global parameters.
    { PgSqlConfigBackendDHCPv6Impl::GET_ALL_GLOBAL_PARAMETERS6,
      PGSQL_GET_GLOBAL_PARAMETER(dhcp6)
    },

    // Select modified global parameters.
    { PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_GLOBAL_PARAMETERS6,
      PGSQL_GET_GLOBAL_PARAMETER(dhcp6, AND g.modification_ts >= ?)
    },

    // Delete all global parameters which are unassigned to any servers.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_GLOBAL_PARAMETERS6_UNASSIGNED,
      PGSQL_DELETE_GLOBAL_PARAMETER_UNASSIGNED(dhcp6)
    },

    // Select subnet by id.
    { PgSqlConfigBackendDHCPv6Impl::GET_SUBNET6_ID_NO_TAG,
      PGSQL_GET_SUBNET6_NO_TAG(WHERE s.subnet_id = ?)
    },

    // Select subnet by id without specifying server tags.
    { PgSqlConfigBackendDHCPv6Impl::GET_SUBNET6_ID_ANY,
      PGSQL_GET_SUBNET6_ANY(WHERE s.subnet_id = ?)
    },

    // Select unassigned subnet by id.
    { PgSqlConfigBackendDHCPv6Impl::GET_SUBNET6_ID_UNASSIGNED,
      PGSQL_GET_SUBNET6_UNASSIGNED(AND s.subnet_id = ?)
    },

    // Select subnet by prefix.
    { PgSqlConfigBackendDHCPv6Impl::GET_SUBNET6_PREFIX_NO_TAG,
      PGSQL_GET_SUBNET6_NO_TAG(WHERE s.subnet_prefix = ?)
    },

    // Select subnet by prefix without specifying server tags.
    { PgSqlConfigBackendDHCPv6Impl::GET_SUBNET6_PREFIX_ANY,
      PGSQL_GET_SUBNET6_ANY(WHERE s.subnet_prefix = ?)
    },

    // Select unassigned subnet by prefix.
    { PgSqlConfigBackendDHCPv6Impl::GET_SUBNET6_PREFIX_UNASSIGNED,
      PGSQL_GET_SUBNET6_UNASSIGNED(AND s.subnet_prefix = ?)
    },

    // Select all subnets.
    { PgSqlConfigBackendDHCPv6Impl::GET_ALL_SUBNETS6,
      PGSQL_GET_SUBNET6_NO_TAG()
    },

    // Select all unassigned subnets.
    { PgSqlConfigBackendDHCPv6Impl::GET_ALL_SUBNETS6_UNASSIGNED,
      PGSQL_GET_SUBNET6_UNASSIGNED()
    },

    // Select subnets having modification time later than X.
    { PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_SUBNETS6,
      PGSQL_GET_SUBNET6_NO_TAG(WHERE s.modification_ts >= ?)
    },

    // Select modified and unassigned subnets.
    { PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_SUBNETS6_UNASSIGNED,
      PGSQL_GET_SUBNET6_UNASSIGNED(AND s.modification_ts >= ?)
    },

    // Select subnets belonging to a shared network.
    { PgSqlConfigBackendDHCPv6Impl::GET_SHARED_NETWORK_SUBNETS6,
      PGSQL_GET_SUBNET6_ANY(WHERE s.shared_network_name = ?)
    },

    // Select pool by address range for a server.
    { PgSqlConfigBackendDHCPv6Impl::GET_POOL6_RANGE,
      PGSQL_GET_POOL6_RANGE_WITH_TAG(WHERE (srv.tag = ? OR srv.id = 1) AND p.start_address = ? \
                                     AND p.end_address = ?)
    },

    // Select pool by address range for any server.
    { PgSqlConfigBackendDHCPv6Impl::GET_POOL6_RANGE_ANY,
      PGSQL_GET_POOL6_RANGE_NO_TAG(WHERE p.start_address = ? AND p.end_address = ?)
    },

    // Select prefix delegation pool for a server.
    { PgSqlConfigBackendDHCPv6Impl::GET_PD_POOL,
      PGSQL_GET_PD_POOL_WITH_TAG(WHERE (srv.tag = ? OR srv.id = 1) \
                                 AND p.prefix = ? AND p.prefix_length = ?)
    },

    // Select prefix delegation pool for any server.
    { PgSqlConfigBackendDHCPv6Impl::GET_PD_POOL_ANY,
      PGSQL_GET_PD_POOL_NO_TAG(WHERE p.prefix = ? AND p.prefix_length = ?)
    },

    // Select shared network by name.
    { PgSqlConfigBackendDHCPv6Impl::GET_SHARED_NETWORK6_NAME_NO_TAG,
      PGSQL_GET_SHARED_NETWORK6_NO_TAG(WHERE n.name = ?)
    },

    // Select shared network by name without specifying server tags.
    { PgSqlConfigBackendDHCPv6Impl::GET_SHARED_NETWORK6_NAME_ANY,
      PGSQL_GET_SHARED_NETWORK6_ANY(WHERE n.name = ?)
    },

    // Select unassigned shared network by name.
    { PgSqlConfigBackendDHCPv6Impl::GET_SHARED_NETWORK6_NAME_UNASSIGNED,
      PGSQL_GET_SHARED_NETWORK6_UNASSIGNED(AND n.name = ?)
    },

    // Select all shared networks.
    { PgSqlConfigBackendDHCPv6Impl::GET_ALL_SHARED_NETWORKS6,
      PGSQL_GET_SHARED_NETWORK6_NO_TAG()
    },

    // Select all unassigned shared networks.
    { PgSqlConfigBackendDHCPv6Impl::GET_ALL_SHARED_NETWORKS6_UNASSIGNED,
      PGSQL_GET_SHARED_NETWORK6_UNASSIGNED()
    },

    // Select modified shared networks.
    { PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_SHARED_NETWORKS6,
      PGSQL_GET_SHARED_NETWORK6_NO_TAG(WHERE n.modification_ts >= ?)
    },

    // Select modified and unassigned shared networks.
    { PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_SHARED_NETWORKS6_UNASSIGNED,
      PGSQL_GET_SHARED_NETWORK6_UNASSIGNED(AND n.modification_ts >= ?)
    },

    // Retrieves option definition by code and space.
    { PgSqlConfigBackendDHCPv6Impl::GET_OPTION_DEF6_CODE_SPACE,
      PGSQL_GET_OPTION_DEF(dhcp6, AND d.code = ? AND d.space = ?)
    },

    // Retrieves all option definitions.
    { PgSqlConfigBackendDHCPv6Impl::GET_ALL_OPTION_DEFS6,
      PGSQL_GET_OPTION_DEF(dhcp6)
    },

    // Retrieves modified option definitions.
    { PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_OPTION_DEFS6,
      PGSQL_GET_OPTION_DEF(dhcp6, AND d.modification_ts >= ?)
    },

    // Retrieves global option by code and space.
    { PgSqlConfigBackendDHCPv6Impl::GET_OPTION6_CODE_SPACE,
      PGSQL_GET_OPTION6(AND o.scope_id = 0 AND o.code = ? AND o.space = ?)
    },

    // Retrieves all global options.
    { PgSqlConfigBackendDHCPv6Impl::GET_ALL_OPTIONS6,
      PGSQL_GET_OPTION6(AND o.scope_id = 0)
    },

    // Retrieves modified options.
    { PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_OPTIONS6,
      PGSQL_GET_OPTION6(AND o.scope_id = 0 AND o.modification_ts >= ?)
    },

    // Retrieves an option for a given subnet, option code and space.
    { PgSqlConfigBackendDHCPv6Impl::GET_OPTION6_SUBNET_ID_CODE_SPACE,
      PGSQL_GET_OPTION6(AND o.scope_id = 1 AND o.dhcp6_subnet_id = ? AND o.code = ? AND o.space = ?)
    },

    // Retrieves an option for a given pool, option code and space.
    { PgSqlConfigBackendDHCPv6Impl::GET_OPTION6_POOL_ID_CODE_SPACE,
      PGSQL_GET_OPTION6(AND o.scope_id = 5 AND o.pool_id = ? AND o.code = ? AND o.space = ?)
    },

    // Retrieves an option for a given pd pool, option code and space.
    { PgSqlConfigBackendDHCPv6Impl::GET_OPTION6_PD_POOL_ID_CODE_SPACE,
      PGSQL_GET_OPTION6(AND o.scope_id = 6 AND o.pd_pool_id = ? AND o.code = ? AND o.space = ?)
    },

    // Retrieves an option for a given shared network, option code and space.
    { PgSqlConfigBackendDHCPv6Impl::GET_OPTION6_SHARED_NETWORK_CODE_SPACE,
      PGSQL_GET_OPTION6(AND o.scope_id = 4 AND o.shared_network_name = ? AND o.code = ? AND o.space = ?)
    },

    // Retrieves the most recent audit entries.
    { PgSqlConfigBackendDHCPv6Impl::GET_AUDIT_ENTRIES6_TIME,
      PGSQL_GET_AUDIT_ENTRIES_TIME(dhcp6)
    },

    // Retrieves a server by tag.
    { PgSqlConfigBackendDHCPv6Impl::GET_SERVER6,
      PGSQL_GET_SERVER(dhcp6)
    },

    // Retrieves all servers.
    { PgSqlConfigBackendDHCPv6Impl::GET_ALL_SERVERS6,
      PGSQL_GET_ALL_SERVERS(dhcp6)
    },

    // Insert global parameter.
    { PgSqlConfigBackendDHCPv6Impl::INSERT_GLOBAL_PARAMETER6,
      PGSQL_INSERT_GLOBAL_PARAMETER(dhcp6)
    },

    // Insert association of the global parameter with a server.
    { PgSqlConfigBackendDHCPv6Impl::INSERT_GLOBAL_PARAMETER6_SERVER,
      PGSQL_INSERT_GLOBAL_PARAMETER_SERVER(dhcp6)
    },

    // Insert a subnet.
    { PgSqlConfigBackendDHCPv6Impl::INSERT_SUBNET6,
      "INSERT INTO dhcp6_subnet("
      "  subnet_id,"
      "  subnet_prefix,"
      "  client_class,"
      "  interface,"
      "  modification_ts,"
      "  preferred_lifetime,"
      "  min_preferred_lifetime,"
      "  max_preferred_lifetime,"
      "  rapid_commit,"
      "  rebind_timer,"
      "  relay,"
      "  renew_timer,"
      "  require_client_classes,"
      "  reservations_global,"
      "  shared_network_name,"
      "  user_context,"
      "  valid_lifetime,"
      "  min_valid_lifetime,"
      "  max_valid_lifetime,"
      "  calculate_tee_times,"
      "  t1_percent,"
      "  t2_percent,"
      "  interface_id,"
      "  ddns_send_updates,"
      "  ddns_override_no_update,"
      "  ddns_override_client_update,"
      "  ddns_replace_client_name,"
      "  ddns_generated_prefix,"
      "  ddns_qualifying_suffix,"
      "  reservations_in_subnet,"
      "  reservations_out_of_pool,"
      "  cache_threshold,"
      "  cache_max_age"
      ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
      " ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)" },

    // Insert association of the subnet with a server.
    { PgSqlConfigBackendDHCPv6Impl::INSERT_SUBNET6_SERVER,
      PGSQL_INSERT_SUBNET_SERVER(dhcp6)
    },

    // Insert pool for a subnet.
    { PgSqlConfigBackendDHCPv6Impl::INSERT_POOL6,
      PGSQL_INSERT_POOL(dhcp6)
    },

    // Insert pd pool for a subnet.
    { PgSqlConfigBackendDHCPv6Impl::INSERT_PD_POOL,
      PGSQL_INSERT_PD_POOL()
    },

    // Insert a shared network.
    { PgSqlConfigBackendDHCPv6Impl::INSERT_SHARED_NETWORK6,
      "INSERT INTO dhcp6_shared_network("
      "  name,"
      "  client_class,"
      "  interface,"
      "  modification_ts,"
      "  preferred_lifetime,"
      "  min_preferred_lifetime,"
      "  max_preferred_lifetime,"
      "  rapid_commit,"
      "  rebind_timer,"
      "  relay,"
      "  renew_timer,"
      "  require_client_classes,"
      "  reservations_global,"
      "  user_context,"
      "  valid_lifetime,"
      "  min_valid_lifetime,"
      "  max_valid_lifetime,"
      "  calculate_tee_times,"
      "  t1_percent,"
      "  t2_percent,"
      "  interface_id,"
      "  ddns_send_updates,"
      "  ddns_override_no_update,"
      "  ddns_override_client_update,"
      "  ddns_replace_client_name,"
      "  ddns_generated_prefix,"
      "  ddns_qualifying_suffix,"
      "  reservations_in_subnet,"
      "  reservations_out_of_pool,"
      "  cache_threshold,"
      "  cache_max_age"
      ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
      " ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)" },

    // Insert association of the shared network with a server.
    { PgSqlConfigBackendDHCPv6Impl::INSERT_SHARED_NETWORK6_SERVER,
      PGSQL_INSERT_SHARED_NETWORK_SERVER(dhcp6)
    },

    // Insert option definition.
    { PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6,
      PGSQL_INSERT_OPTION_DEF(dhcp6)
    },

    // Insert association of the option definition with a server.
    { PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION_DEF6_SERVER,
      PGSQL_INSERT_OPTION_DEF_SERVER(dhcp6)
    },

    // Insert subnet specific option.
    { PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION6,
      PGSQL_INSERT_OPTION6()
    },

    // Insert association of the DHCP option with a server.
    { PgSqlConfigBackendDHCPv6Impl::INSERT_OPTION6_SERVER,
      PGSQL_INSERT_OPTION_SERVER(dhcp6)
    },

    // Insert server with server tag and description.
    { PgSqlConfigBackendDHCPv6Impl::INSERT_SERVER6,
      PGSQL_INSERT_SERVER(dhcp6)
    },

    // Update existing global parameter.
    { PgSqlConfigBackendDHCPv6Impl::UPDATE_GLOBAL_PARAMETER6,
      PGSQL_UPDATE_GLOBAL_PARAMETER(dhcp6)
    },

    // Update existing subnet.
    { PgSqlConfigBackendDHCPv6Impl::UPDATE_SUBNET6,
      "UPDATE dhcp6_subnet SET"
      "  subnet_id = ?,"
      "  subnet_prefix = ?,"
      "  client_class = ?,"
      "  interface = ?,"
      "  modification_ts = ?,"
      "  preferred_lifetime = ?,"
      "  min_preferred_lifetime = ?,"
      "  max_preferred_lifetime = ?,"
      "  rapid_commit = ?,"
      "  rebind_timer = ?,"
      "  relay = ?,"
      "  renew_timer = ?,"
      "  require_client_classes = ?,"
      "  reservations_global = ?,"
      "  shared_network_name = ?,"
      "  user_context = ?,"
      "  valid_lifetime = ?,"
      "  min_valid_lifetime = ?,"
      "  max_valid_lifetime = ?,"
      "  calculate_tee_times = ?,"
      "  t1_percent = ?,"
      "  t2_percent = ?,"
      "  interface_id = ?,"
      "  ddns_send_updates = ?,"
      "  ddns_override_no_update = ?,"
      "  ddns_override_client_update = ?,"
      "  ddns_replace_client_name = ?,"
      "  ddns_generated_prefix = ?,"
      "  ddns_qualifying_suffix = ?,"
      "  reservations_in_subnet = ?,"
      "  reservations_out_of_pool = ?,"
      "  cache_threshold = ?,"
      "  cache_max_age = ? "
      "WHERE subnet_id = ? OR subnet_prefix = ?" },

    // Update existing shared network.
    { PgSqlConfigBackendDHCPv6Impl::UPDATE_SHARED_NETWORK6,
      "UPDATE dhcp6_shared_network SET"
      "  name = ?,"
      "  client_class = ?,"
      "  interface = ?,"
      "  modification_ts = ?,"
      "  preferred_lifetime = ?,"
      "  min_preferred_lifetime = ?,"
      "  max_preferred_lifetime = ?,"
      "  rapid_commit = ?,"
      "  rebind_timer = ?,"
      "  relay = ?,"
      "  renew_timer = ?,"
      "  require_client_classes = ?,"
      "  reservations_global = ?,"
      "  user_context = ?,"
      "  valid_lifetime = ?,"
      "  min_valid_lifetime = ?,"
      "  max_valid_lifetime = ?,"
      "  calculate_tee_times = ?,"
      "  t1_percent = ?,"
      "  t2_percent = ?,"
      "  interface_id = ?,"
      "  ddns_send_updates = ?,"
      "  ddns_override_no_update = ?,"
      "  ddns_override_client_update = ?,"
      "  ddns_replace_client_name = ?,"
      "  ddns_generated_prefix = ?,"
      "  ddns_qualifying_suffix = ?,"
      "  reservations_in_subnet = ?,"
      "  reservations_out_of_pool = ?,"
      "  cache_threshold = ?,"
      "  cache_max_age = ? "
      "WHERE name = ?" },

    // Update existing option definition.
    { PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION_DEF6,
      PGSQL_UPDATE_OPTION_DEF(dhcp6)
    },

    // Update existing global option.
    { PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6,
      PGSQL_UPDATE_OPTION6_WITH_TAG(AND o.scope_id = 0 AND o.code = ? AND o.space = ?)
    },

    // Update existing subnet level option.
    { PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_SUBNET_ID,
      PGSQL_UPDATE_OPTION6_NO_TAG(o.scope_id = 1 AND o.dhcp6_subnet_id = ? AND o.code = ? AND o.space = ?)
    },

    // Update existing pool level option.
    { PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_POOL_ID,
      PGSQL_UPDATE_OPTION6_NO_TAG(o.scope_id = 5 AND o.pool_id = ? AND o.code = ? AND o.space = ?)
    },

    // Update existing pd pool level option.
    { PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_PD_POOL_ID,
      PGSQL_UPDATE_OPTION6_NO_TAG(o.scope_id = 6 AND o.pd_pool_id = ? AND o.code = ? AND o.space = ?)
    },

    // Update existing shared network level option.
    { PgSqlConfigBackendDHCPv6Impl::UPDATE_OPTION6_SHARED_NETWORK,
      PGSQL_UPDATE_OPTION6_NO_TAG(o.scope_id = 4 AND o.shared_network_name = ? AND o.code = ? AND o.space = ?)
    },

    // Update existing server, e.g. server description.
    { PgSqlConfigBackendDHCPv6Impl::UPDATE_SERVER6,
      PGSQL_UPDATE_SERVER(dhcp6)
    },

    // Delete global parameter by name.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_GLOBAL_PARAMETER6,
      PGSQL_DELETE_GLOBAL_PARAMETER(dhcp6, AND g.name = ?)
    },

    // Delete all global parameters.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_GLOBAL_PARAMETERS6,
      PGSQL_DELETE_GLOBAL_PARAMETER(dhcp6)
    },

    // Delete subnet by id with specifying server tag.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_ID_WITH_TAG,
      PGSQL_DELETE_SUBNET_WITH_TAG(dhcp6, AND s.subnet_id = ?)
    },

    // Delete subnet by id without specifying server tag.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_ID_ANY,
      PGSQL_DELETE_SUBNET_ANY(dhcp6, WHERE s.subnet_id = ?)
    },

    // Delete subnet by prefix with specifying server tag.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_PREFIX_WITH_TAG,
      PGSQL_DELETE_SUBNET_WITH_TAG(dhcp6, AND s.subnet_prefix = ?)
    },

    // Delete subnet by prefix without specifying server tag.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_PREFIX_ANY,
      PGSQL_DELETE_SUBNET_ANY(dhcp6, WHERE s.subnet_prefix = ?)
    },

    // Delete all subnets.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6,
      PGSQL_DELETE_SUBNET_WITH_TAG(dhcp6)
    },

    // Delete all unassigned subnets.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6_UNASSIGNED,
      PGSQL_DELETE_SUBNET_UNASSIGNED(dhcp6)
    },

    // Delete all subnets for a shared network.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6_SHARED_NETWORK_NAME,
      PGSQL_DELETE_SUBNET_ANY(dhcp6, WHERE s.shared_network_name = ?)
    },

    // Delete associations of a subnet with server.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_SUBNET6_SERVER,
      PGSQL_DELETE_SUBNET_SERVER(dhcp6),
    },

    // Delete pools for a subnet.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_POOLS6,
      PGSQL_DELETE_POOLS(dhcp6)
    },

    // Delete pd pools for a subnet.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_PD_POOLS,
      PGSQL_DELETE_PD_POOLS()
    },

    // Delete shared network by name with specifying server tag.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_NAME_WITH_TAG,
      PGSQL_DELETE_SHARED_NETWORK_WITH_TAG(dhcp6, AND n.name = ?)
    },

    // Delete shared network by name without specifying server tag.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_NAME_ANY,
      PGSQL_DELETE_SHARED_NETWORK_ANY(dhcp6, WHERE n.name = ?)
    },

    // Delete all shared networks.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SHARED_NETWORKS6,
      PGSQL_DELETE_SHARED_NETWORK_WITH_TAG(dhcp6)
    },

    // Delete all unassigned shared networks.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SHARED_NETWORKS6_UNASSIGNED,
      PGSQL_DELETE_SHARED_NETWORK_UNASSIGNED(dhcp6)
    },

    // Delete associations of a shared network with server.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_SERVER,
      PGSQL_DELETE_SHARED_NETWORK_SERVER(dhcp6)
    },

    // Delete option definition.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION_DEF6_CODE_NAME,
      PGSQL_DELETE_OPTION_DEF(dhcp6, AND code = ? AND space = ?)
    },

    // Delete all option definitions.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_OPTION_DEFS6,
      PGSQL_DELETE_OPTION_DEF(dhcp6)
    },

    // Delete all option definitions which are assigned to no servers.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_OPTION_DEFS6_UNASSIGNED,
      PGSQL_DELETE_OPTION_DEF_UNASSIGNED(dhcp6)
    },

    // Delete single global option.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION6,
      PGSQL_DELETE_OPTION_WITH_TAG(dhcp6, AND o.scope_id = 0  AND o.code = ? AND o.space = ?)
    },

    // Delete all global options which are unassigned to any servers.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_GLOBAL_OPTIONS6_UNASSIGNED,
      PGSQL_DELETE_OPTION_UNASSIGNED(dhcp6, AND o.scope_id = 0)
    },

    // Delete single option from a subnet.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION6_SUBNET_ID,
      PGSQL_DELETE_OPTION_NO_TAG(dhcp6,
                          WHERE o.scope_id = 1 AND o.dhcp6_subnet_id = ? AND o.code = ? AND o.space = ?)
    },

    // Delete single option from a pool.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION6_POOL_RANGE,
      PGSQL_DELETE_OPTION_POOL_RANGE(dhcp6, o.scope_id = 5 AND o.code = ? AND o.space = ?)
    },

    // Delete single option from a pd pool.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION6_PD_POOL,
      PGSQL_DELETE_OPTION_PD_POOL(o.scope_id = 6 AND o.code = ? AND o.space = ?)
    },

    // Delete single option from a shared network.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_OPTION6_SHARED_NETWORK,
      PGSQL_DELETE_OPTION_NO_TAG(dhcp6,
                          WHERE o.scope_id = 4 AND o.shared_network_name = ? AND o.code = ? AND o.space = ?)
    },

    // Delete options belonging to a subnet.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_OPTIONS6_SUBNET_ID_PREFIX,
      PGSQL_DELETE_OPTION_SUBNET_ID_PREFIX(dhcp6)
    },

    // Delete options belonging to a shared_network.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_OPTIONS6_SHARED_NETWORK,
      PGSQL_DELETE_OPTION_NO_TAG(dhcp6, WHERE o.scope_id = 4 AND o.shared_network_name = ?)
    },

    // Delete a server by tag.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_SERVER6,
      PGSQL_DELETE_SERVER(dhcp6)
    },

    // Deletes all servers except logical server 'all'.
    { PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SERVERS6,
      PGSQL_DELETE_ALL_SERVERS(dhcp6)
    }
}
};
#endif

}; // end anonymous namespace

PgSqlConfigBackendDHCPv6Impl::PgSqlConfigBackendDHCPv6Impl(const DatabaseConnection::ParameterMap& parameters)
    : PgSqlConfigBackendImpl(parameters, &PgSqlConfigBackendDHCPv6Impl::dbReconnect) {
    // Prepare query statements. Those are will be only used to retrieve
    // information from the database, so they can be used even if the
    // database is read only for the current user.
    conn_.prepareStatements(tagged_statements.begin(),
                            tagged_statements.end());
//                            tagged_statements.begin() + WRITE_STMTS_BEGIN);

    // Create unique timer name per instance.
    timer_name_ = "PgSqlConfigBackend6[";
    timer_name_ += boost::lexical_cast<std::string>(reinterpret_cast<uint64_t>(this));
    timer_name_ += "]DbReconnectTimer";

    // Create ReconnectCtl for this connection.
    conn_.makeReconnectCtl(timer_name_);
}

PgSqlConfigBackendDHCPv6Impl::~PgSqlConfigBackendDHCPv6Impl() {
}

PgSqlConfigBackendDHCPv6::PgSqlConfigBackendDHCPv6(const DatabaseConnection::ParameterMap& parameters)
    : impl_(new PgSqlConfigBackendDHCPv6Impl(parameters)), base_impl_(impl_) {
}

bool
PgSqlConfigBackendDHCPv6::isUnusable() {
    return (impl_->conn_.isUnusable());
}

Subnet6Ptr
PgSqlConfigBackendDHCPv6::getSubnet6(const ServerSelector& server_selector,
                                     const std::string& subnet_prefix) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SUBNET6_BY_PREFIX)
        .arg(subnet_prefix);
    return (impl_->getSubnet6(server_selector, subnet_prefix));
}

Subnet6Ptr
PgSqlConfigBackendDHCPv6::getSubnet6(const ServerSelector& server_selector,
                                     const SubnetID& subnet_id) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SUBNET6_BY_SUBNET_ID)
        .arg(subnet_id);
    return (impl_->getSubnet6(server_selector, subnet_id));
}

Subnet6Collection
PgSqlConfigBackendDHCPv6::getAllSubnets6(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SUBNETS6);
    Subnet6Collection subnets;
    impl_->getAllSubnets6(server_selector, subnets);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SUBNETS6_RESULT)
        .arg(subnets.size());
    return (subnets);
}

Subnet6Collection
PgSqlConfigBackendDHCPv6::getModifiedSubnets6(const ServerSelector& server_selector,
                                              const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SUBNETS6)
        .arg(util::ptimeToText(modification_time));
    Subnet6Collection subnets;
    impl_->getModifiedSubnets6(server_selector, modification_time, subnets);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SUBNETS6_RESULT)
        .arg(subnets.size());
    return (subnets);
}

Subnet6Collection
PgSqlConfigBackendDHCPv6::getSharedNetworkSubnets6(const ServerSelector& /* server_selector */,
                                                   const std::string& shared_network_name) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SHARED_NETWORK_SUBNETS6)
        .arg(shared_network_name);
    Subnet6Collection subnets;
    impl_->getSharedNetworkSubnets6(ServerSelector::ANY(), shared_network_name, subnets);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SHARED_NETWORK_SUBNETS6_RESULT)
        .arg(subnets.size());
    return (subnets);
}

SharedNetwork6Ptr
PgSqlConfigBackendDHCPv6::getSharedNetwork6(const ServerSelector& server_selector,
                                            const std::string& name) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SHARED_NETWORK6)
        .arg(name);
    return (impl_->getSharedNetwork6(server_selector, name));
}

SharedNetwork6Collection
PgSqlConfigBackendDHCPv6::getAllSharedNetworks6(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SHARED_NETWORKS6);
    SharedNetwork6Collection shared_networks;
    impl_->getAllSharedNetworks6(server_selector, shared_networks);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SHARED_NETWORKS6_RESULT)
        .arg(shared_networks.size());
    return (shared_networks);
}

SharedNetwork6Collection
PgSqlConfigBackendDHCPv6::getModifiedSharedNetworks6(const ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS6)
        .arg(util::ptimeToText(modification_time));
    SharedNetwork6Collection shared_networks;
    impl_->getModifiedSharedNetworks6(server_selector, modification_time, shared_networks);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS6_RESULT)
        .arg(shared_networks.size());
    return (shared_networks);
}

OptionDefinitionPtr
PgSqlConfigBackendDHCPv6::getOptionDef6(const ServerSelector& server_selector,
                                        const uint16_t code,
                                        const std::string& space) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_OPTION_DEF6)
        .arg(code).arg(space);
    return (impl_->getOptionDef(PgSqlConfigBackendDHCPv6Impl::GET_OPTION_DEF6_CODE_SPACE,
                                server_selector, code, space));
}

OptionDefContainer
PgSqlConfigBackendDHCPv6::getAllOptionDefs6(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTION_DEFS6);
    OptionDefContainer option_defs;
    impl_->getAllOptionDefs(PgSqlConfigBackendDHCPv6Impl::GET_ALL_OPTION_DEFS6,
                            server_selector, option_defs);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTION_DEFS6_RESULT)
        .arg(option_defs.size());
    return (option_defs);
}

OptionDefContainer
PgSqlConfigBackendDHCPv6::getModifiedOptionDefs6(const ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTION_DEFS6)
        .arg(util::ptimeToText(modification_time));
    OptionDefContainer option_defs;
    impl_->getModifiedOptionDefs(PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_OPTION_DEFS6,
                                 server_selector, modification_time, option_defs);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTION_DEFS6_RESULT)
        .arg(option_defs.size());
    return (option_defs);
}

OptionDescriptorPtr
PgSqlConfigBackendDHCPv6::getOption6(const ServerSelector& server_selector,
                                     const uint16_t code,
                                     const std::string& space) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_OPTION6)
        .arg(code).arg(space);
    return (impl_->getOption(PgSqlConfigBackendDHCPv6Impl::GET_OPTION6_CODE_SPACE,
                             Option::V6, server_selector, code, space));
}

OptionContainer
PgSqlConfigBackendDHCPv6::getAllOptions6(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTIONS6);
    OptionContainer options = impl_->getAllOptions(PgSqlConfigBackendDHCPv6Impl::GET_ALL_OPTIONS6,
            Option::V6, server_selector);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTIONS6_RESULT)
        .arg(options.size());
    return (options);
}

OptionContainer
PgSqlConfigBackendDHCPv6::getModifiedOptions6(const ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTIONS6)
        .arg(util::ptimeToText(modification_time));
    OptionContainer options = impl_->getModifiedOptions(PgSqlConfigBackendDHCPv6Impl::GET_MODIFIED_OPTIONS6,
            Option::V6, server_selector, modification_time);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTIONS6_RESULT)
        .arg(options.size());
    return (options);
}

StampedValuePtr
PgSqlConfigBackendDHCPv6::getGlobalParameter6(const ServerSelector& server_selector,
                                              const std::string& name) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_GLOBAL_PARAMETER6)
        .arg(name);
    return (impl_->getGlobalParameter6(server_selector, name));
}

StampedValueCollection
PgSqlConfigBackendDHCPv6::getAllGlobalParameters6(const ServerSelector& server_selector) const {
    isc_throw(NotImplemented, "Not implemented yet.");
}

StampedValueCollection
PgSqlConfigBackendDHCPv6::getModifiedGlobalParameters6(const db::ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time) const {
    isc_throw(NotImplemented, "Not implemented yet.");
}

AuditEntryCollection
PgSqlConfigBackendDHCPv6::getRecentAuditEntries(const db::ServerSelector& server_selector,
        const boost::posix_time::ptime& modification_time,
        const uint64_t& modification_id) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_RECENT_AUDIT_ENTRIES6)
      .arg(util::ptimeToText(modification_time))
      .arg(modification_id);
    AuditEntryCollection audit_entries;
    impl_->getRecentAuditEntries(PgSqlConfigBackendDHCPv6Impl::GET_AUDIT_ENTRIES6_TIME,
                                 server_selector, modification_time,
                                 modification_id, audit_entries);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_RECENT_AUDIT_ENTRIES6_RESULT)
        .arg(audit_entries.size());
    return (audit_entries);
}

ServerCollection
PgSqlConfigBackendDHCPv6::getAllServers6() const {
    ServerCollection servers;

    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SERVERS6);
    impl_->getAllServers(PgSqlConfigBackendDHCPv6Impl::GET_ALL_SERVERS6,
                         servers);

    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SERVERS6_RESULT)
        .arg(servers.size());
    return (servers);
}

ServerPtr
PgSqlConfigBackendDHCPv6::getServer6(const data::ServerTag& server_tag) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SERVER6)
        .arg(server_tag.get());
    return (impl_->getServer(PgSqlConfigBackendDHCPv6Impl::GET_SERVER6, server_tag));
}

void
PgSqlConfigBackendDHCPv6::createUpdateSubnet6(const ServerSelector& server_selector,
                                              const Subnet6Ptr& subnet) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SUBNET6)
        .arg(subnet);
    impl_->createUpdateSubnet6(server_selector, subnet);
}

void
PgSqlConfigBackendDHCPv6::createUpdateSharedNetwork6(const ServerSelector& server_selector,
                                                     const SharedNetwork6Ptr& shared_network) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK6)
        .arg(shared_network->getName());
    impl_->createUpdateSharedNetwork6(server_selector, shared_network);
}

void
PgSqlConfigBackendDHCPv6::createUpdateOptionDef6(const ServerSelector& server_selector,
                                                 const OptionDefinitionPtr& option_def) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_OPTION_DEF6)
        .arg(option_def->getName()).arg(option_def->getCode());
    impl_->createUpdateOptionDef6(server_selector, option_def);
}

void
PgSqlConfigBackendDHCPv6::createUpdateOption6(const ServerSelector& server_selector,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_OPTION6);
    impl_->createUpdateOption6(server_selector, option);
}

void
PgSqlConfigBackendDHCPv6::createUpdateOption6(const db::ServerSelector& server_selector,
                                              const std::string& shared_network_name,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION6)
        .arg(shared_network_name);
    impl_->createUpdateOption6(server_selector, shared_network_name, option, false);
}

void
PgSqlConfigBackendDHCPv6::createUpdateOption6(const ServerSelector& server_selector,
                                              const SubnetID& subnet_id,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION6)
        .arg(subnet_id);
    impl_->createUpdateOption6(server_selector, subnet_id, option, false);
}

void
PgSqlConfigBackendDHCPv6::createUpdateOption6(const ServerSelector& server_selector,
                                              const asiolink::IOAddress& pool_start_address,
                                              const asiolink::IOAddress& pool_end_address,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_BY_POOL_OPTION6)
        .arg(pool_start_address.toText()).arg(pool_end_address.toText());
    impl_->createUpdateOption6(server_selector, pool_start_address, pool_end_address,
                               option);
}

void
PgSqlConfigBackendDHCPv6::createUpdateOption6(const ServerSelector& server_selector,
                                              const asiolink::IOAddress& pd_pool_prefix,
                                              const uint8_t pd_pool_prefix_length,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_BY_PREFIX_OPTION6)
        .arg(pd_pool_prefix.toText()).arg(pd_pool_prefix_length);
    impl_->createUpdateOption6(server_selector, pd_pool_prefix,
                               pd_pool_prefix_length, option);
}

void
PgSqlConfigBackendDHCPv6::createUpdateGlobalParameter6(const ServerSelector& server_selector,
                                                       const StampedValuePtr& value) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER6)
        .arg(value->getName());
    impl_->createUpdateGlobalParameter6(server_selector, value);
}

void
PgSqlConfigBackendDHCPv6::createUpdateServer6(const ServerPtr& server) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SERVER6)
        .arg(server->getServerTagAsText());
    impl_->createUpdateServer(PgSqlConfigBackendDHCPv6Impl::CREATE_AUDIT_REVISION,
                              PgSqlConfigBackendDHCPv6Impl::INSERT_SERVER6,
                              PgSqlConfigBackendDHCPv6Impl::UPDATE_SERVER6,
                              server);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteSubnet6(const ServerSelector& server_selector,
                                        const std::string& subnet_prefix) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_PREFIX_SUBNET6)
        .arg(subnet_prefix);
    uint64_t result = impl_->deleteSubnet6(server_selector, subnet_prefix);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_PREFIX_SUBNET6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteSubnet6(const ServerSelector& server_selector,
                                        const SubnetID& subnet_id) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET6)
        .arg(subnet_id);
    uint64_t result = impl_->deleteSubnet6(server_selector, subnet_id);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteAllSubnets6(const ServerSelector& server_selector) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SUBNETS6);

    int index = (server_selector.amUnassigned() ?
                 PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6_UNASSIGNED :
                 PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6);
    uint64_t result = impl_->deleteTransactional(index, server_selector, "deleting all subnets",
                                                 "deleted all subnets", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SUBNETS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteSharedNetworkSubnets6(const db::ServerSelector& server_selector,
                                                      const std::string& shared_network_name) {
    if (!server_selector.amAny()) {
        isc_throw(InvalidOperation, "deleting all subnets from a shared "
                  "network requires using ANY server selector");
    }
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS6)
        .arg(shared_network_name);
    uint64_t result = impl_->deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SUBNETS6_SHARED_NETWORK_NAME,
                                                 server_selector,
                                                 "deleting all subnets for a shared network",
                                                 "deleted all subnets for a shared network",
                                                 true, shared_network_name);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteSharedNetwork6(const ServerSelector& server_selector,
                                               const std::string& name) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK6)
        .arg(name);
    int index = (server_selector.amAny() ?
                 PgSqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_NAME_ANY :
                 PgSqlConfigBackendDHCPv6Impl::DELETE_SHARED_NETWORK6_NAME_WITH_TAG);
    uint64_t result = impl_->deleteTransactional(index, server_selector,
                                                 "deleting a shared network",
                                                 "shared network deleted", true, name);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteAllSharedNetworks6(const ServerSelector& server_selector) {
    if (server_selector.amAny()) {
        isc_throw(InvalidOperation, "deleting all shared networks for ANY server is not"
                  " supported");
    }

    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SHARED_NETWORKS6);

    int index = (server_selector.amUnassigned() ?
                 PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SHARED_NETWORKS6_UNASSIGNED :
                 PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_SHARED_NETWORKS6);
    uint64_t result = impl_->deleteTransactional(index,
                                                 server_selector, "deleting all shared networks",
                                                 "deleted all shared networks", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SHARED_NETWORKS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteOptionDef6(const ServerSelector& server_selector,
                                           const uint16_t code,
                                           const std::string& space) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION_DEF6)
        .arg(code).arg(space);
    uint64_t result = impl_->deleteOptionDef6(server_selector, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION_DEF6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteAllOptionDefs6(const ServerSelector& server_selector) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_OPTION_DEFS6);
    uint64_t result = impl_->deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_OPTION_DEFS6,
                                                 server_selector, "deleting all option definitions",
                                                 "deleted all option definitions", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_OPTION_DEFS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteOption6(const ServerSelector& server_selector,
                                        const uint16_t code,
                                        const std::string& space) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION6)
        .arg(code).arg(space);
    uint64_t result = impl_->deleteOption6(server_selector, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteOption6(const ServerSelector& /* server_selector */,
                                        const std::string& shared_network_name,
                                        const uint16_t code,
                                        const std::string& space) {
    /// @todo In the future we might use the server selector to make sure that the
    /// option is only deleted if the pool belongs to a given server. For now, we
    /// just delete it when there is a match with the parent object.
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_OPTION6)
        .arg(shared_network_name).arg(code).arg(space);
    uint64_t result = impl_->deleteOption6(ServerSelector::ANY(), shared_network_name,
                                           code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_OPTION6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteOption6(const ServerSelector& /* server_selector */,
                                        const SubnetID& subnet_id,
                                        const uint16_t code,
                                        const std::string& space) {
    /// @todo In the future we might use the server selector to make sure that the
    /// option is only deleted if the pool belongs to a given server. For now, we
    /// just delete it when there is a match with the parent object.
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION6)
        .arg(subnet_id).arg(code).arg(space);
    uint64_t result = impl_->deleteOption6(ServerSelector::ANY(), subnet_id, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteOption6(const ServerSelector& /* server_selector */,
                                        const asiolink::IOAddress& pool_start_address,
                                        const asiolink::IOAddress& pool_end_address,
                                        const uint16_t code,
                                        const std::string& space) {
    /// @todo In the future we might use the server selector to make sure that the
    /// option is only deleted if the pool belongs to a given server. For now, we
    /// just delete it when there is a match with the parent object.
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_POOL_OPTION6)
        .arg(pool_start_address.toText()).arg(pool_end_address.toText()).arg(code).arg(space);
    uint64_t result = impl_->deleteOption6(ServerSelector::ANY(), pool_start_address, pool_end_address,
                                           code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_POOL_OPTION6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteOption6(const ServerSelector& /* server_selector */,
                                        const asiolink::IOAddress& pd_pool_prefix,
                                        const uint8_t pd_pool_prefix_length,
                                        const uint16_t code,
                                        const std::string& space) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_POOL_PREFIX_OPTION6)
        .arg(pd_pool_prefix.toText()).arg(pd_pool_prefix_length).arg(code).arg(space);
    uint64_t result = impl_->deleteOption6(ServerSelector::ANY(), pd_pool_prefix,
                                           pd_pool_prefix_length, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_POOL_PREFIX_OPTION6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteGlobalParameter6(const ServerSelector& server_selector,
                                                 const std::string& name) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_GLOBAL_PARAMETER6)
        .arg(name);
    uint64_t result = impl_->deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_GLOBAL_PARAMETER6,
                                                 server_selector, "deleting global parameter",
                                                 "global parameter deleted", false, name);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_GLOBAL_PARAMETER6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteAllGlobalParameters6(const ServerSelector& server_selector) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS6);
    uint64_t result = impl_->deleteTransactional(PgSqlConfigBackendDHCPv6Impl::DELETE_ALL_GLOBAL_PARAMETERS6,
                                                 server_selector, "deleting all global parameters",
                                                 "all global parameters deleted", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteServer6(const ServerTag& server_tag) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SERVER6)
        .arg(server_tag.get());
    uint64_t result = impl_->deleteServer6(server_tag);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SERVER6_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteAllServers6() {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SERVERS6);
    uint64_t result = impl_->deleteAllServers6();
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SERVERS6_RESULT)
        .arg(result);
    return (result);
}

std::string
PgSqlConfigBackendDHCPv6::getType() const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_TYPE6);
    return (impl_->getType());
}

std::string
PgSqlConfigBackendDHCPv6::getHost() const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_HOST6);
    return (impl_->getHost());
}

uint16_t
PgSqlConfigBackendDHCPv6::getPort() const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_PORT6);
    return (impl_->getPort());
}

bool
PgSqlConfigBackendDHCPv6::registerBackendType() {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_REGISTER_BACKEND_TYPE6);
    return (
        dhcp::ConfigBackendDHCPv6Mgr::instance().registerBackendFactory("pgsql",
            [](const db::DatabaseConnection::ParameterMap& params) -> dhcp::ConfigBackendDHCPv6Ptr {
            return (dhcp::PgSqlConfigBackendDHCPv6Ptr(new dhcp::PgSqlConfigBackendDHCPv6(params)));
        })
    );
}

void
PgSqlConfigBackendDHCPv6::unregisterBackendType() {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_UNREGISTER_BACKEND_TYPE6);
    dhcp::ConfigBackendDHCPv6Mgr::instance().unregisterBackendFactory("pgsql");
}

void
PgSqlConfigBackendDHCPv6::createUpdateClientClass6(const db::ServerSelector& server_selector,
                          const ClientClassDefPtr& client_class,
                          const std::string& follow_class_name) {
    isc_throw(NotImplemented, "Not implemented yet.");
}

ClientClassDefPtr
PgSqlConfigBackendDHCPv6::getClientClass6(const db::ServerSelector& selector,
                                          const std::string& name) const {
    isc_throw(NotImplemented, "Not implemented yet.");
}

ClientClassDictionary
PgSqlConfigBackendDHCPv6::getAllClientClasses6(const db::ServerSelector& selector) const {
    isc_throw(NotImplemented, "Not implemented yet.");
}

ClientClassDictionary
PgSqlConfigBackendDHCPv6::getModifiedClientClasses6(const db::ServerSelector& selector,
                          const boost::posix_time::ptime& modification_time) const {
    isc_throw(NotImplemented, "Not implemented yet.");
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteClientClass6(const db::ServerSelector& server_selector,
                    const std::string& name) {
    isc_throw(NotImplemented, "Not implemented yet.");
}

uint64_t
PgSqlConfigBackendDHCPv6::deleteAllClientClasses6(const db::ServerSelector& server_selector) {
    isc_throw(NotImplemented, "Not implemented yet.");
}


} // end of namespace isc::dhcp
} // end of namespace isc
