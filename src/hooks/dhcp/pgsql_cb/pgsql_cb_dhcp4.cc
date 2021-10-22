// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

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
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/network.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/timer_mgr.h>
#include <pgsql/pgsql_connection.h>
#include <util/boost_time_utils.h>
#include <util/buffer.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/scoped_ptr.hpp>

#include <array>
#include <pgsql_cb_dhcp4.h>
#include <pgsql_cb_impl.h>
#include <pgsql_macros.h>
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
class PgSqlConfigBackendDHCPv4Impl : public PgSqlConfigBackendImpl {
public:
    /// @brief Statement tags.
    ///
    /// The contents of the enum are indexes into the list of SQL statements.
    /// It is assumed that the order is such that the indices of statements
    /// reading the database are less than those of statements modifying the
    /// database.
    enum StatementIndex {
        CREATE_AUDIT_REVISION,
        GET_GLOBAL_PARAMETER4,
        GET_ALL_GLOBAL_PARAMETERS4,
        GET_MODIFIED_GLOBAL_PARAMETERS4,
        GET_SUBNET4_ID_NO_TAG,
        GET_SUBNET4_ID_ANY,
        GET_SUBNET4_ID_UNASSIGNED,
        GET_SUBNET4_PREFIX_NO_TAG,
        GET_SUBNET4_PREFIX_ANY,
        GET_SUBNET4_PREFIX_UNASSIGNED,
        GET_ALL_SUBNETS4,
        GET_ALL_SUBNETS4_UNASSIGNED,
        GET_MODIFIED_SUBNETS4,
        GET_MODIFIED_SUBNETS4_UNASSIGNED,
        GET_SHARED_NETWORK_SUBNETS4,
        GET_POOL4_RANGE,
        GET_POOL4_RANGE_ANY,
        GET_SHARED_NETWORK4_NAME_NO_TAG,
        GET_SHARED_NETWORK4_NAME_ANY,
        GET_SHARED_NETWORK4_NAME_UNASSIGNED,
        GET_ALL_SHARED_NETWORKS4,
        GET_ALL_SHARED_NETWORKS4_UNASSIGNED,
        GET_MODIFIED_SHARED_NETWORKS4,
        GET_MODIFIED_SHARED_NETWORKS4_UNASSIGNED,
        GET_OPTION_DEF4_CODE_SPACE,
        GET_ALL_OPTION_DEFS4,
        GET_MODIFIED_OPTION_DEFS4,
        GET_OPTION4_CODE_SPACE,
        GET_ALL_OPTIONS4,
        GET_MODIFIED_OPTIONS4,
        GET_OPTION4_SUBNET_ID_CODE_SPACE,
        GET_OPTION4_POOL_ID_CODE_SPACE,
        GET_OPTION4_SHARED_NETWORK_CODE_SPACE,
        GET_AUDIT_ENTRIES4_TIME,
        GET_SERVER4,
        GET_ALL_SERVERS4,
        INSERT_GLOBAL_PARAMETER4,
        INSERT_GLOBAL_PARAMETER4_SERVER,
        INSERT_SUBNET4,
        INSERT_SUBNET4_SERVER,
        INSERT_POOL4,
        INSERT_SHARED_NETWORK4,
        INSERT_SHARED_NETWORK4_SERVER,
        INSERT_OPTION_DEF4,
        INSERT_OPTION_DEF4_SERVER,
        INSERT_OPTION4,
        INSERT_OPTION4_SERVER,
        INSERT_SERVER4,
        UPDATE_GLOBAL_PARAMETER4,
        UPDATE_SUBNET4,
        UPDATE_SHARED_NETWORK4,
        UPDATE_OPTION_DEF4,
        UPDATE_OPTION4,
        UPDATE_OPTION4_SUBNET_ID,
        UPDATE_OPTION4_POOL_ID,
        UPDATE_OPTION4_SHARED_NETWORK,
        UPDATE_SERVER4,
        DELETE_GLOBAL_PARAMETER4,
        DELETE_ALL_GLOBAL_PARAMETERS4,
        DELETE_ALL_GLOBAL_PARAMETERS4_UNASSIGNED,
        DELETE_SUBNET4_ID_WITH_TAG,
        DELETE_SUBNET4_ID_ANY,
        DELETE_SUBNET4_PREFIX_WITH_TAG,
        DELETE_SUBNET4_PREFIX_ANY,
        DELETE_ALL_SUBNETS4,
        DELETE_ALL_SUBNETS4_UNASSIGNED,
        DELETE_ALL_SUBNETS4_SHARED_NETWORK_NAME,
        DELETE_SUBNET4_SERVER,
        DELETE_POOLS4,
        DELETE_SHARED_NETWORK4_NAME_WITH_TAG,
        DELETE_SHARED_NETWORK4_NAME_ANY,
        DELETE_ALL_SHARED_NETWORKS4,
        DELETE_ALL_SHARED_NETWORKS4_UNASSIGNED,
        DELETE_SHARED_NETWORK4_SERVER,
        DELETE_OPTION_DEF4_CODE_NAME,
        DELETE_ALL_OPTION_DEFS4,
        DELETE_ALL_OPTION_DEFS4_UNASSIGNED,
        DELETE_OPTION4,
        DELETE_ALL_GLOBAL_OPTIONS4_UNASSIGNED,
        DELETE_OPTION4_SUBNET_ID,
        DELETE_OPTION4_POOL_RANGE,
        DELETE_OPTION4_SHARED_NETWORK,
        DELETE_OPTIONS4_SUBNET_ID_PREFIX,
        DELETE_OPTIONS4_SHARED_NETWORK,
        DELETE_SERVER4,
        DELETE_ALL_SERVERS4,
        NUM_STATEMENTS
    };

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    explicit PgSqlConfigBackendDHCPv4Impl(const DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor.
    ~PgSqlConfigBackendDHCPv4Impl();

    /// @brief Sends query to retrieve global parameter.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the parameter to be retrieved.
    ///
    /// @return Pointer to the retrieved value or null if such parameter
    /// doesn't exist.
    StampedValuePtr
    getGlobalParameter4(const ServerSelector& server_selector, const std::string& name) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to insert or update global parameter.
    ///
    /// @param server_selector Server selector.
    /// @param name Name of the global parameter.
    /// @param value Value of the global parameter.
    void createUpdateGlobalParameter4(const db::ServerSelector& server_selector,
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
    Subnet4Ptr getSubnet4(const ServerSelector& server_selector, const SubnetID& subnet_id) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve single subnet by prefix.
    ///
    /// The prefix should be in the following format: "192.0.2.0/24".
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Pointer to the returned subnet or NULL if such subnet
    /// doesn't exist.
    Subnet4Ptr getSubnet4(const ServerSelector& server_selector, const std::string& subnet_prefix) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve all subnets.
    ///
    /// @param server_selector Server selector.
    /// @param [out] subnets Reference to the subnet collection structure where
    /// subnets should be inserted.
    void getAllSubnets4(const ServerSelector& server_selector, Subnet4Collection& subnets) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve modified subnets.
    ///
    /// @param server_selector Server selector.
    /// @param modification_ts Lower bound modification timestamp.
    /// @param [out] subnets Reference to the subnet collection structure where
    /// subnets should be inserted.
    void getModifiedSubnets4(const ServerSelector& server_selector,
                             const boost::posix_time::ptime& modification_ts,
                             Subnet4Collection& subnets) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve all subnets belonging to a shared network.
    ///
    /// @param server_selector Server selector.
    /// @param shared_network_name Name of the shared network for which the
    /// subnets should be retrieved.
    /// @param [out] subnets Reference to the subnet collection structure where
    /// subnets should be inserted.
    void getSharedNetworkSubnets4(const ServerSelector& server_selector,
                                  const std::string& shared_network_name,
                                  Subnet4Collection& subnets) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve single pool by address range.
    ///
    /// @param server_selector Server selector.
    /// @param pool_start_address Lower bound pool address.
    /// @param pool_end_address Upper bound pool address.
    /// @param pool_id Pool identifier for the returned pool.
    /// @return Pointer to the pool or null if no such pool found.
    Pool4Ptr getPool4(const ServerSelector& server_selector,
                      const IOAddress& pool_start_address,
                      const IOAddress& pool_end_address,
                      uint64_t& pool_id) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to insert or update subnet.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Pointer to the subnet to be inserted or updated.
    void createUpdateSubnet4(const ServerSelector& server_selector, const Subnet4Ptr& subnet) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Inserts new IPv4 pool to the database.
    ///
    /// @param server_selector Server selector.
    /// @param pool Pointer to the pool to be inserted.
    /// @param subnet Pointer to the subnet that this pool belongs to.
    void createPool4(const ServerSelector& server_selector,
                     const Pool4Ptr& pool,
                     const Subnet4Ptr& subnet) {
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
    template <typename... Args>
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
    uint64_t deleteSubnet4(const ServerSelector& server_selector, const SubnetID& subnet_id) {
        int index = (server_selector.amAny() ?
                         PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_ID_ANY :
                         PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_ID_WITH_TAG);
        return (deleteTransactional(index, server_selector, "deleting a subnet", "subnet deleted",
                                    true, static_cast<uint32_t>(subnet_id)));
    }

    /// @brief Sends query to delete subnet by id.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_prefix Prefix of the subnet to be deleted.
    /// @return Number of deleted subnets.
    uint64_t
    deleteSubnet4(const ServerSelector& server_selector, const std::string& subnet_prefix) {
        int index = (server_selector.amAny() ?
                         PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_PREFIX_ANY :
                         PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_PREFIX_WITH_TAG);
        return (deleteTransactional(index, server_selector, "deleting a subnet", "subnet deleted",
                                    true, subnet_prefix));
    }

    /// @brief Deletes pools belonging to a subnet from the database.
    ///
    /// The query deletes all pools associated with the subnet's
    /// identifier or prefix.
    /// @param subnet Pointer to the subnet for which pools should be
    /// deleted.
    uint64_t deletePools4(const Subnet4Ptr& subnet) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve single shared network by name.
    ///
    /// @param server_selector Server selector.
    /// @param name Shared network name.
    ///
    /// @return Pointer to the returned shared network or NULL if such shared
    /// network doesn't exist.
    SharedNetwork4Ptr
    getSharedNetwork4(const ServerSelector& server_selector, const std::string& name) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve all shared networks.
    ///
    /// @param server_selector Server selector.
    /// @param [out] shared_networks Reference to the shared networks collection
    /// structure where shared networks should be inserted.
    void getAllSharedNetworks4(const ServerSelector& server_selector,
                               SharedNetwork4Collection& shared_networks) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to retrieve modified shared networks.
    ///
    /// @param server_selector Server selector.
    /// @param modification_ts Lower bound modification timestamp.
    /// @param [out] shared_networks Reference to the shared networks collection
    /// structure where shared networks should be inserted.
    void getModifiedSharedNetworks4(const ServerSelector& server_selector,
                                    const boost::posix_time::ptime& modification_ts,
                                    SharedNetwork4Collection& shared_networks) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to insert or update shared network.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Pointer to the shared network to be inserted or updated.
    void createUpdateSharedNetwork4(const ServerSelector& server_selector,
                                    const SharedNetwork4Ptr& shared_network) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to insert or update global DHCP option.
    ///
    /// @param server_selector Server selector.
    /// @param option Pointer to the option descriptor encapsulating the option.
    void
    createUpdateOption4(const ServerSelector& server_selector, const OptionDescriptorPtr& option) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to insert or update DHCP option in a subnet.
    ///
    /// @param server_selector Server selector.
    /// @param subnet_id Identifier of the subnet the option belongs to.
    /// @param option Pointer to the option descriptor encapsulating the option.
    /// @param cascade_update Boolean value indicating whether the update is
    /// performed as part of the owning element, e.g. subnet.
    void createUpdateOption4(const ServerSelector& server_selector,
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
    void createUpdateOption4(const ServerSelector& server_selector,
                             const IOAddress& pool_start_address,
                             const IOAddress& pool_end_address,
                             const OptionDescriptorPtr& option) {
        uint64_t pool_id = 0;
        Pool4Ptr pool = getPool4(server_selector, pool_start_address, pool_end_address, pool_id);
        if (!pool) {
            isc_throw(BadValue, "no pool found for range of " << pool_start_address << " : "
                                                              << pool_end_address);
        }

        createUpdateOption4(server_selector, pool_id, option, false);
    }

    /// @brief Sends query to insert or update DHCP option in a pool.
    ///
    /// @param selector Server selector.
    /// @param pool_id Identifier of the pool the option belongs to.
    /// @param option Pointer to the option descriptor encapsulating the option.
    /// @param cascade_update Boolean value indicating whether the update is
    /// performed as part of the owning element, e.g. subnet.
    void createUpdateOption4(const ServerSelector& server_selector,
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
    void createUpdateOption4(const ServerSelector& server_selector,
                             const std::string& shared_network_name,
                             const OptionDescriptorPtr& option,
                             const bool cascade_update) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Sends query to insert or update option definition.
    ///
    /// @param server_selector Server selector.
    /// @param option_def Pointer to the option definition to be inserted or updated.
    void createUpdateOptionDef4(const ServerSelector& server_selector,
                                const OptionDefinitionPtr& option_def) {

        createUpdateOptionDef(server_selector, option_def, DHCP4_OPTION_SPACE,
                              PgSqlConfigBackendDHCPv4Impl::GET_OPTION_DEF4_CODE_SPACE,
                              PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION_DEF4,
                              PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION_DEF4,
                              PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                              PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION_DEF4_SERVER);
    }

    /// @brief Sends query to delete option definition by code and
    /// option space name.
    ///
    /// @param server_selector Server selector.
    /// @param code Option code.
    /// @param name Option name.
    /// @return Number of deleted option definitions.
    uint64_t deleteOptionDef4(const ServerSelector& server_selector,
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
    uint64_t deleteOption4(const ServerSelector& server_selector,
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
    uint64_t deleteOption4(const ServerSelector& server_selector,
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
    uint64_t deleteOption4(const db::ServerSelector& server_selector,
                           const IOAddress& pool_start_address,
                           const IOAddress& pool_end_address,
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
    uint64_t deleteOption4(const db::ServerSelector& server_selector,
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
    uint64_t deleteOptions4(const ServerSelector& server_selector, const Subnet4Ptr& subnet) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Deletes options belonging to a shared network from the database.
    ///
    /// @param server_selector Server selector.
    /// @param subnet Pointer to the subnet for which options should be
    /// deleted.
    /// @return Number of deleted options.
    uint64_t
    deleteOptions4(const ServerSelector& server_selector, const SharedNetwork4Ptr& shared_network) {
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
    uint64_t deleteServer4(const data::ServerTag& server_tag) {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Attempts to delete all servers.
    ///
    /// This method deletes all servers added by the user. It does not
    /// delete the logical server 'all'.
    ///
    /// @return Number of deleted servers.
    uint64_t deleteAllServers4() {
        isc_throw(NotImplemented, "Not implemented yet.");
    }

    /// @brief Attempts to reconnect the server to the config DB backend manager.
    ///
    /// This is a self-rescheduling function that attempts to reconnect to the
    /// server's config DB backends after connectivity to one or more have been
    /// lost. Upon entry it will attempt to reconnect via
    /// @ref ConfigBackendDHCPv4Mgr.addBackend.
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
                if (ConfigBackendDHCPv4Mgr::instance().delBackend(parameters["type"], access,
                                                                  true)) {
                    ConfigBackendDHCPv4Mgr::instance().addBackend(db.getAccessString());
                }
            }

            reopened = true;
        } catch (const std::exception& ex) {
            LOG_ERROR(pgsql_cb_logger, PGSQL_CB_RECONNECT_ATTEMPT_FAILED4).arg(ex.what());
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
                LOG_ERROR(pgsql_cb_logger, PGSQL_CB_RECONNECT_FAILED4)
                    .arg(db_reconnect_ctl->maxRetries());

                // Cancel the timer.
                if (TimerMgr::instance()->isTimerRegistered(timer_name)) {
                    TimerMgr::instance()->unregisterTimer(timer_name);
                }

                // Invoke application layer connection failed callback.
                DatabaseConnection::invokeDbFailedCallback(db_reconnect_ctl);

                return (false);
            }

            LOG_INFO(pgsql_cb_logger, PGSQL_CB_RECONNECT_ATTEMPT_SCHEDULE4)
                .arg(db_reconnect_ctl->maxRetries() - db_reconnect_ctl->retriesLeft() + 1)
                .arg(db_reconnect_ctl->maxRetries())
                .arg(db_reconnect_ctl->retryInterval());

            // Start the timer.
            if (!TimerMgr::instance()->isTimerRegistered(timer_name)) {
                TimerMgr::instance()->registerTimer(
                    timer_name,
                    std::bind(&PgSqlConfigBackendDHCPv4Impl::dbReconnect, db_reconnect_ctl),
                    db_reconnect_ctl->retryInterval(), asiolink::IntervalTimer::ONE_SHOT);
            }
            TimerMgr::instance()->setup(timer_name);
        }

        return (true);
    }
};

namespace {

/// @brief Array of tagged statements.
typedef std::array<PgSqlTaggedStatement, PgSqlConfigBackendDHCPv4Impl::NUM_STATEMENTS>
    PgSqlTaggedStatementArray;

/// @brief Prepared Postgres statements used by the backend to insert and
/// retrieve data from the database.
/// @todo: OID types are obviously wrong.
PgSqlTaggedStatementArray tagged_statements = { {
    { 4, { OID_TIMESTAMP, OID_VARCHAR, OID_TEXT, OID_BOOL }, "CREATE_AUDIT_REVISION",
      "CALL createAuditRevisionDHCP4($1, $2, $3, $4)"
    },

    // Select global parameter by name.
    { 1, { OID_VARCHAR }, "GET_GLOBAL_PARAMETER4",
      PGSQL_GET_GLOBAL_PARAMETER(dhcp4, AND g.name = ?)
    },

    // Select all global parameters.
    { 0, { }, "GET_ALL_GLOBAL_PARAMETERS4",
      PGSQL_GET_GLOBAL_PARAMETER(dhcp4)
    },

    // Select modified global parameters.
    { 1, { OID_TIMESTAMP }, "GET_MODIFIED_GLOBAL_PARAMETERS4",
      PGSQL_GET_GLOBAL_PARAMETER(dhcp4, AND g.modification_ts >= ?)
    },

    // Select subnet by id.
    { 1, { OID_INT8 }, "GET_SUBNET4_ID_NO_TAG",
      PGSQL_GET_SUBNET4_NO_TAG(WHERE s.subnet_id = ?)
    },

    // Select subnet by id without specifying server tags.
    { 1, { OID_INT8 }, "GET_SUBNET4_ID_ANY",
      PGSQL_GET_SUBNET4_ANY(WHERE s.subnet_id = ?)
    },

    // Select unassigned subnet by id.
    { 1, { OID_INT8 }, "GET_SUBNET4_ID_UNASSIGNED",
      PGSQL_GET_SUBNET4_UNASSIGNED(AND s.subnet_id = ?)
    },

    // Select subnet by prefix.
    { 1, { OID_VARCHAR }, "GET_SUBNET4_PREFIX_NO_TAG",
      PGSQL_GET_SUBNET4_NO_TAG(WHERE s.subnet_prefix = ?)
    },

    // Select subnet by prefix without specifying server tags.
    { 1, { OID_VARCHAR }, "GET_SUBNET4_PREFIX_ANY",
      PGSQL_GET_SUBNET4_ANY(WHERE s.subnet_prefix = ?)
    }
}};

#if 0
    // Select unassigned subnet by prefix.
    { PgSqlConfigBackendDHCPv4Impl::GET_SUBNET4_PREFIX_UNASSIGNED,
      "TODO" /// @todo: PGSQL_GET_SUBNET4_UNASSIGNED(AND s.subnet_prefix = ?)
    },

    // Select all subnets.
    { PgSqlConfigBackendDHCPv4Impl::GET_ALL_SUBNETS4,
      "TODO" /// @todo: PGSQL_GET_SUBNET4_NO_TAG()
    },

    // Select all unassigned subnets.
    { PgSqlConfigBackendDHCPv4Impl::GET_ALL_SUBNETS4_UNASSIGNED,
      "TODO" /// @todo: PGSQL_GET_SUBNET4_UNASSIGNED()
    },

    // Select subnets having modification time later than X.
    { PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_SUBNETS4,
      "TODO" /// @todo: PGSQL_GET_SUBNET4_NO_TAG(WHERE s.modification_ts >= ?)
    },

    // Select modified and unassigned subnets.
    { PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_SUBNETS4_UNASSIGNED,
      "TODO" /// @todo: PGSQL_GET_SUBNET4_UNASSIGNED(AND s.modification_ts >= ?)
    },

    // Select subnets belonging to a shared network.
    { PgSqlConfigBackendDHCPv4Impl::GET_SHARED_NETWORK_SUBNETS4,
      "TODO" /// @todo: PGSQL_GET_SUBNET4_ANY(WHERE s.shared_network_name = ?)
    },

    // Select pool by address range for a server.
    { PgSqlConfigBackendDHCPv4Impl::GET_POOL4_RANGE,
      "TODO" /// @todo: PGSQL_GET_POOL4_RANGE_WITH_TAG(WHERE (srv.tag = ? OR srv.id = 1) AND p.start_address = ? AND p.end_address = ?)
    },

    // Select pool by address range for any server
    { PgSqlConfigBackendDHCPv4Impl::GET_POOL4_RANGE_ANY,
      "TODO" /// @todo: PGSQL_GET_POOL4_RANGE_NO_TAG(WHERE p.start_address = ? AND p.end_address = ?)
    },

    // Select shared network by name.
    { PgSqlConfigBackendDHCPv4Impl::GET_SHARED_NETWORK4_NAME_NO_TAG,
      "TODO" /// @todo: PGSQL_GET_SHARED_NETWORK4_NO_TAG(WHERE n.name = ?)
    },

    // Select shared network by name without specifying server tags.
    { PgSqlConfigBackendDHCPv4Impl::GET_SHARED_NETWORK4_NAME_ANY,
      "TODO" /// @todo: PGSQL_GET_SHARED_NETWORK4_ANY(WHERE n.name = ?)
    },

    // Select unassigned shared network by name.
    { PgSqlConfigBackendDHCPv4Impl::GET_SHARED_NETWORK4_NAME_UNASSIGNED,
      "TODO" /// @todo: PGSQL_GET_SHARED_NETWORK4_UNASSIGNED(AND n.name = ?)
    },

    // Select all shared networks.
    { PgSqlConfigBackendDHCPv4Impl::GET_ALL_SHARED_NETWORKS4,
      "TODO" /// @todo: PGSQL_GET_SHARED_NETWORK4_NO_TAG()
    },

    // Select all unassigned shared networks.
    { PgSqlConfigBackendDHCPv4Impl::GET_ALL_SHARED_NETWORKS4_UNASSIGNED,
      "TODO" /// @todo: PGSQL_GET_SHARED_NETWORK4_UNASSIGNED()
    },

    // Select modified shared networks.
    { PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_SHARED_NETWORKS4,
      "TODO" /// @todo: PGSQL_GET_SHARED_NETWORK4_NO_TAG(WHERE n.modification_ts >= ?)
    },

    // Select modified and unassigned shared networks.
    { PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_SHARED_NETWORKS4_UNASSIGNED,
      "TODO" /// @todo: PGSQL_GET_SHARED_NETWORK4_UNASSIGNED(AND n.modification_ts >= ?)
    },

    // Retrieves option definition by code and space.
    { PgSqlConfigBackendDHCPv4Impl::GET_OPTION_DEF4_CODE_SPACE,
      "TODO" /// @todo: PGSQL_GET_OPTION_DEF(dhcp4, AND d.code = ? AND d.space = ?)
    },

    // Retrieves all option definitions.
    { PgSqlConfigBackendDHCPv4Impl::GET_ALL_OPTION_DEFS4,
      "TODO" /// @todo: PGSQL_GET_OPTION_DEF(dhcp4)
    },

    // Retrieves modified option definitions.
    { PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_OPTION_DEFS4,
      "TODO" /// @todo: PGSQL_GET_OPTION_DEF(dhcp4, AND d.modification_ts >= ?)
    },

    // Retrieves global option by code and space.
    { PgSqlConfigBackendDHCPv4Impl::GET_OPTION4_CODE_SPACE,
      "TODO" /// @todo: PGSQL_GET_OPTION4(AND o.scope_id = 0 AND o.code = ? AND o.space = ?)
    },

    // Retrieves all global options.
    { PgSqlConfigBackendDHCPv4Impl::GET_ALL_OPTIONS4,
      "TODO" /// @todo: PGSQL_GET_OPTION4(AND o.scope_id = 0)
    },

    // Retrieves modified options.
    { PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_OPTIONS4,
      "TODO" /// @todo: PGSQL_GET_OPTION4(AND o.scope_id = 0 AND o.modification_ts >= ?)
    },

    // Retrieves an option for a given subnet, option code and space.
    { PgSqlConfigBackendDHCPv4Impl::GET_OPTION4_SUBNET_ID_CODE_SPACE,
      "TODO" /// @todo: PGSQL_GET_OPTION4(AND o.scope_id = 1 AND o.dhcp4_subnet_id = ? AND o.code = ? AND o.space = ?)
    },

    // Retrieves an option for a given pool, option code and space.
    { PgSqlConfigBackendDHCPv4Impl::GET_OPTION4_POOL_ID_CODE_SPACE,
      "TODO" /// @todo: PGSQL_GET_OPTION4(AND o.scope_id = 5 AND o.pool_id = ? AND o.code = ? AND o.space = ?)
    },

    // Retrieves an option for a given shared network, option code and space.
    { PgSqlConfigBackendDHCPv4Impl::GET_OPTION4_SHARED_NETWORK_CODE_SPACE,
      "TODO" /// @todo: PGSQL_GET_OPTION4(AND o.scope_id = 4 AND o.shared_network_name = ? AND o.code = ? AND o.space = ?)
    },

    // Retrieves the most recent audit entries.
    { PgSqlConfigBackendDHCPv4Impl::GET_AUDIT_ENTRIES4_TIME,
      "TODO" /// @todo: PGSQL_GET_AUDIT_ENTRIES_TIME(dhcp4)
    },

    // Retrieves a server by tag.
    { PgSqlConfigBackendDHCPv4Impl::GET_SERVER4,
      "TODO" /// @todo: PGSQL_GET_SERVER(dhcp4)
    },

    // Retrieves all servers.
    { PgSqlConfigBackendDHCPv4Impl::GET_ALL_SERVERS4,
      "TODO" /// @todo: PGSQL_GET_ALL_SERVERS(dhcp4)
    },

    // Insert global parameter.
    { PgSqlConfigBackendDHCPv4Impl::INSERT_GLOBAL_PARAMETER4,
      "TODO" /// @todo: PGSQL_INSERT_GLOBAL_PARAMETER(dhcp4)
    },

    // Insert association of the global parameter with a server.
    { PgSqlConfigBackendDHCPv4Impl::INSERT_GLOBAL_PARAMETER4_SERVER,
      "TODO" /// @todo: PGSQL_INSERT_GLOBAL_PARAMETER_SERVER(dhcp4)
    },

    // Insert a subnet.
    { PgSqlConfigBackendDHCPv4Impl::INSERT_SUBNET4,
      "INSERT INTO dhcp4_subnet("
      "  subnet_id,"
      "  subnet_prefix,"
      "  4o6_interface,"
      "  4o6_interface_id,"
      "  4o6_subnet,"
      "  boot_file_name,"
      "  client_class,"
      "  interface,"
      "  match_client_id,"
      "  modification_ts,"
      "  next_server,"
      "  rebind_timer,"
      "  relay,"
      "  renew_timer,"
      "  require_client_classes,"
      "  reservations_global,"
      "  server_hostname,"
      "  shared_network_name,"
      "  user_context,"
      "  valid_lifetime,"
      "  min_valid_lifetime,"
      "  max_valid_lifetime,"
      "  calculate_tee_times,"
      "  t1_percent,"
      "  t2_percent,"
      "  authoritative,"
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
      ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
      " ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)" },

    // Insert association of the subnet with a server.
    { PgSqlConfigBackendDHCPv4Impl::INSERT_SUBNET4_SERVER,
      "TODO" /// @todo: PGSQL_INSERT_SUBNET_SERVER(dhcp4)
    },

    // Insert pool for a subnet.
    { PgSqlConfigBackendDHCPv4Impl::INSERT_POOL4,
      "TODO" /// @todo: PGSQL_INSERT_POOL(dhcp4)
    },

    // Insert a shared network.
    { PgSqlConfigBackendDHCPv4Impl::INSERT_SHARED_NETWORK4,
      "INSERT INTO dhcp4_shared_network("
      "  name,"
      "  client_class,"
      "  interface,"
      "  match_client_id,"
      "  modification_ts,"
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
      "  authoritative,"
      "  boot_file_name,"
      "  next_server,"
      "  server_hostname,"
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
      " ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)" },

    // Insert association of the shared network with a server.
    { PgSqlConfigBackendDHCPv4Impl::INSERT_SHARED_NETWORK4_SERVER,
      "TODO" /// @todo: PGSQL_INSERT_SHARED_NETWORK_SERVER(dhcp4)
    },

    // Insert option definition.
    { PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION_DEF4,
      "TODO" /// @todo: PGSQL_INSERT_OPTION_DEF(dhcp4)
    },

    // Insert association of the option definition with a server.
    { PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION_DEF4_SERVER,
      "TODO" /// @todo: PGSQL_INSERT_OPTION_DEF_SERVER(dhcp4)
    },

    // Insert subnet specific option.
    { PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION4,
      "TODO" /// @todo: PGSQL_INSERT_OPTION4()
    },

    // Insert association of the DHCP option with a server.
    { PgSqlConfigBackendDHCPv4Impl::INSERT_OPTION4_SERVER,
      "TODO" /// @todo: PGSQL_INSERT_OPTION_SERVER(dhcp4)
    },

    // Insert server with server tag and description.
    { PgSqlConfigBackendDHCPv4Impl::INSERT_SERVER4,
      "TODO" /// @todo: PGSQL_INSERT_SERVER(dhcp4)
    },

    // Update existing global parameter.
    { PgSqlConfigBackendDHCPv4Impl::UPDATE_GLOBAL_PARAMETER4,
      "TODO" /// @todo: PGSQL_UPDATE_GLOBAL_PARAMETER(dhcp4)
    },

    // Update existing subnet.
    { PgSqlConfigBackendDHCPv4Impl::UPDATE_SUBNET4,
      "UPDATE dhcp4_subnet SET"
      "  subnet_id = ?,"
      "  subnet_prefix = ?,"
      "  4o6_interface = ?,"
      "  4o6_interface_id = ?,"
      "  4o6_subnet = ?,"
      "  boot_file_name = ?,"
      "  client_class = ?,"
      "  interface = ?,"
      "  match_client_id = ?,"
      "  modification_ts = ?,"
      "  next_server = ?,"
      "  rebind_timer = ?,"
      "  relay = ?,"
      "  renew_timer = ?,"
      "  require_client_classes = ?,"
      "  reservations_global = ?,"
      "  server_hostname = ?,"
      "  shared_network_name = ?,"
      "  user_context = ?,"
      "  valid_lifetime = ?,"
      "  min_valid_lifetime = ?,"
      "  max_valid_lifetime = ?,"
      "  calculate_tee_times = ?,"
      "  t1_percent = ?,"
      "  t2_percent = ?,"
      "  authoritative = ?,"
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
      "WHERE subnet_id = ? OR subnet_prefix = ?"
    },

    // Update existing shared network.
    { PgSqlConfigBackendDHCPv4Impl::UPDATE_SHARED_NETWORK4,
      "UPDATE dhcp4_shared_network SET"
      "  name = ?,"
      "  client_class = ?,"
      "  interface = ?,"
      "  match_client_id = ?,"
      "  modification_ts = ?,"
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
      "  authoritative = ?,"
      "  boot_file_name = ?,"
      "  next_server = ?,"
      "  server_hostname = ?,"
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
      "WHERE name = ?"
    },

    // Update existing option definition.
    { PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION_DEF4,
      "TODO" /// @todo: PGSQL_UPDATE_OPTION_DEF(dhcp4)
    },

    // Update existing global option.
    { PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION4,
      "TODO" /// @todo: PGSQL_UPDATE_OPTION4_WITH_TAG(AND o.scope_id = 0 AND o.code = ? AND o.space = ?)
    },

    // Update existing subnet level option.
    { PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_SUBNET_ID,
      "TODO" /// @todo: PGSQL_UPDATE_OPTION4_NO_TAG(o.scope_id = 1 AND o.dhcp4_subnet_id = ? AND o.code = ? AND o.space = ?)
    },

    // Update existing pool level option.
    { PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_POOL_ID,
      "TODO" /// @todo: PGSQL_UPDATE_OPTION4_NO_TAG(o.scope_id = 5 AND o.pool_id = ? AND o.code = ? AND o.space = ?)
    },

    // Update existing shared network level option.
    { PgSqlConfigBackendDHCPv4Impl::UPDATE_OPTION4_SHARED_NETWORK,
      "TODO" /// @todo: PGSQL_UPDATE_OPTION4_NO_TAG(o.scope_id = 4 AND o.shared_network_name = ? AND o.code = ? AND o.space = ?)
    },

    // Update existing server, e.g. server description.
    { PgSqlConfigBackendDHCPv4Impl::UPDATE_SERVER4,
      "TODO" /// @todo: PGSQL_UPDATE_SERVER(dhcp4)
    },

    // Delete global parameter by name.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_GLOBAL_PARAMETER4,
      "TODO" /// @todo: PGSQL_DELETE_GLOBAL_PARAMETER(dhcp4, AND g.name = ?)
    },

    // Delete all global parameters.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_GLOBAL_PARAMETERS4,
      "TODO" /// @todo: PGSQL_DELETE_GLOBAL_PARAMETER(dhcp4)
    },

    // Delete all global parameters which are unassigned to any servers.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_GLOBAL_PARAMETERS4_UNASSIGNED,
      "TODO" /// @todo: PGSQL_DELETE_GLOBAL_PARAMETER_UNASSIGNED(dhcp4)
    },

    // Delete subnet by id with specifying server tag.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_ID_WITH_TAG,
      "TODO" /// @todo: PGSQL_DELETE_SUBNET_WITH_TAG(dhcp4, AND s.subnet_id = ?)
    },

    // Delete subnet by id without specifying server tag.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_ID_ANY,
      "TODO" /// @todo: PGSQL_DELETE_SUBNET_ANY(dhcp4, WHERE s.subnet_id = ?)
    },

    // Delete subnet by prefix with specifying server tag.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_PREFIX_WITH_TAG,
      "TODO" /// @todo: PGSQL_DELETE_SUBNET_WITH_TAG(dhcp4, AND s.subnet_prefix = ?)
    },

    // Delete subnet by prefix without specifying server tag.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_PREFIX_ANY,
      "TODO" /// @todo: PGSQL_DELETE_SUBNET_ANY(dhcp4, WHERE s.subnet_prefix = ?)
    },

    // Delete all subnets.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4,
      "TODO" /// @todo: PGSQL_DELETE_SUBNET_WITH_TAG(dhcp4)
    },

    // Delete all unassigned subnets.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4_UNASSIGNED,
      "TODO" /// @todo: PGSQL_DELETE_SUBNET_UNASSIGNED(dhcp4)
    },

    // Delete all subnets for a shared network.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4_SHARED_NETWORK_NAME,
      "TODO" /// @todo: PGSQL_DELETE_SUBNET_ANY(dhcp4, WHERE s.shared_network_name = ?)
    },

    // Delete associations of a subnet with server.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_SUBNET4_SERVER,
      "TODO" /// @todo: PGSQL_DELETE_SUBNET_SERVER(dhcp4),
    },

    // Delete pools for a subnet.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_POOLS4,
      "TODO" /// @todo: PGSQL_DELETE_POOLS(dhcp4)
    },

    // Delete shared network by name with specifying server tag.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_SHARED_NETWORK4_NAME_WITH_TAG,
      "TODO" /// @todo: PGSQL_DELETE_SHARED_NETWORK_WITH_TAG(dhcp4, AND n.name = ?)
    },

    // Delete shared network by name without specifying server tag.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_SHARED_NETWORK4_NAME_ANY,
      "TODO" /// @todo: PGSQL_DELETE_SHARED_NETWORK_ANY(dhcp4, WHERE n.name = ?)
    },

    // Delete all shared networks.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SHARED_NETWORKS4,
      "TODO" /// @todo: PGSQL_DELETE_SHARED_NETWORK_WITH_TAG(dhcp4)
    },

    // Delete all unassigned shared networks.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SHARED_NETWORKS4_UNASSIGNED,
      "TODO" /// @todo: PGSQL_DELETE_SHARED_NETWORK_UNASSIGNED(dhcp4)
    },

    // Delete associations of a shared network with server.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_SHARED_NETWORK4_SERVER,
      "TODO" /// @todo: PGSQL_DELETE_SHARED_NETWORK_SERVER(dhcp4)
    },

    // Delete option definition.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION_DEF4_CODE_NAME,
      "TODO" /// @todo: PGSQL_DELETE_OPTION_DEF(dhcp4, AND code = ? AND space = ?)
    },

    // Delete all option definitions.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_OPTION_DEFS4,
      "TODO" /// @todo: PGSQL_DELETE_OPTION_DEF(dhcp4)
    },

    // Delete all option definitions which are assigned to no servers.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_OPTION_DEFS4_UNASSIGNED,
      "TODO" /// @todo: PGSQL_DELETE_OPTION_DEF_UNASSIGNED(dhcp4)
    },

    // Delete single global option.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION4,
      "TODO" /// @todo: PGSQL_DELETE_OPTION_WITH_TAG(dhcp4, AND o.scope_id = 0  AND o.code = ? AND o.space = ?)
    },

    // Delete all global options which are unassigned to any servers.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_GLOBAL_OPTIONS4_UNASSIGNED,
      "TODO" /// @todo: PGSQL_DELETE_OPTION_UNASSIGNED(dhcp4, AND o.scope_id = 0)
    },

    // Delete single option from a subnet.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION4_SUBNET_ID,
      "TODO" /// @todo: PGSQL_DELETE_OPTION_NO_TAG(dhcp4, WHERE o.scope_id = 1 AND o.dhcp4_subnet_id = ? AND o.code = ? AND o.space = ?)
    },

    // Delete single option from a pool.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION4_POOL_RANGE,
      "TODO" /// @todo: PGSQL_DELETE_OPTION_POOL_RANGE(dhcp4, o.scope_id = 5 AND o.code = ? AND o.space = ?)
    },

    // Delete single option from a shared network.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_OPTION4_SHARED_NETWORK,
      "TODO" /// @todo: PGSQL_DELETE_OPTION_NO_TAG(dhcp4, WHERE o.scope_id = 4 AND o.shared_network_name = ? AND o.code = ? AND o.space = ?)
    },

    // Delete options belonging to a subnet.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_OPTIONS4_SUBNET_ID_PREFIX,
      "TODO" /// @todo: PGSQL_DELETE_OPTION_SUBNET_ID_PREFIX(dhcp4)
    },

    // Delete options belonging to a shared_network.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_OPTIONS4_SHARED_NETWORK,
      "TODO" /// @todo: PGSQL_DELETE_OPTION_NO_TAG(dhcp4, WHERE o.scope_id = 4 AND o.shared_network_name = ?)
    },

    // Delete a server by tag.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_SERVER4,
      "TODO" /// @todo: PGSQL_DELETE_SERVER(dhcp4)
    },

    // Deletes all servers except logical server 'all'.
    { PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SERVERS4,
      "TODO" /// @todo: PGSQL_DELETE_ALL_SERVERS(dhcp4)
    }
}
};
#endif

};  // end anonymous namespace

PgSqlConfigBackendDHCPv4Impl::PgSqlConfigBackendDHCPv4Impl(
    const DatabaseConnection::ParameterMap& parameters)
    : PgSqlConfigBackendImpl(parameters, &PgSqlConfigBackendDHCPv4Impl::dbReconnect) {
    // Prepare query statements. Those are will be only used to retrieve
    // information from the database, so they can be used even if the
    // database is read only for the current user.
    conn_.prepareStatements(tagged_statements.begin(), tagged_statements.end());

    // Create unique timer name per instance.
    timer_name_ = "PgSqlConfigBackend4[";
    timer_name_ += boost::lexical_cast<std::string>(reinterpret_cast<uint64_t>(this));
    timer_name_ += "]DbReconnectTimer";

    // Create ReconnectCtl for this connection.
    conn_.makeReconnectCtl(timer_name_);
}

PgSqlConfigBackendDHCPv4Impl::~PgSqlConfigBackendDHCPv4Impl() {
}

PgSqlConfigBackendDHCPv4::PgSqlConfigBackendDHCPv4(
    const DatabaseConnection::ParameterMap& parameters)
    : impl_(new PgSqlConfigBackendDHCPv4Impl(parameters)), base_impl_(impl_) {
}

bool
PgSqlConfigBackendDHCPv4::isUnusable() {
    return (impl_->conn_.isUnusable());
}

Subnet4Ptr
PgSqlConfigBackendDHCPv4::getSubnet4(const ServerSelector& server_selector,
                                     const std::string& subnet_prefix) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SUBNET4_BY_PREFIX)
        .arg(subnet_prefix);
    return (impl_->getSubnet4(server_selector, subnet_prefix));
}

Subnet4Ptr
PgSqlConfigBackendDHCPv4::getSubnet4(const ServerSelector& server_selector,
                                     const SubnetID& subnet_id) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SUBNET4_BY_SUBNET_ID).arg(subnet_id);
    return (impl_->getSubnet4(server_selector, subnet_id));
}

Subnet4Collection
PgSqlConfigBackendDHCPv4::getAllSubnets4(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SUBNETS4);
    Subnet4Collection subnets;
    impl_->getAllSubnets4(server_selector, subnets);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SUBNETS4_RESULT)
        .arg(subnets.size());
    return (subnets);
}

Subnet4Collection
PgSqlConfigBackendDHCPv4::getModifiedSubnets4(
    const ServerSelector& server_selector,
    const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SUBNETS4)
        .arg(util::ptimeToText(modification_time));
    Subnet4Collection subnets;
    impl_->getModifiedSubnets4(server_selector, modification_time, subnets);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SUBNETS4_RESULT)
        .arg(subnets.size());
    return (subnets);
}

Subnet4Collection
PgSqlConfigBackendDHCPv4::getSharedNetworkSubnets4(const ServerSelector& /* server_selector */,
                                                   const std::string& shared_network_name) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SHARED_NETWORK_SUBNETS4)
        .arg(shared_network_name);
    Subnet4Collection subnets;
    impl_->getSharedNetworkSubnets4(ServerSelector::ANY(), shared_network_name, subnets);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SHARED_NETWORK_SUBNETS4_RESULT)
        .arg(subnets.size());
    return (subnets);
}

SharedNetwork4Ptr
PgSqlConfigBackendDHCPv4::getSharedNetwork4(const ServerSelector& server_selector,
                                            const std::string& name) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SHARED_NETWORK4).arg(name);
    return (impl_->getSharedNetwork4(server_selector, name));
}

SharedNetwork4Collection
PgSqlConfigBackendDHCPv4::getAllSharedNetworks4(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SHARED_NETWORKS4);
    SharedNetwork4Collection shared_networks;
    impl_->getAllSharedNetworks4(server_selector, shared_networks);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SHARED_NETWORKS4_RESULT)
        .arg(shared_networks.size());
    return (shared_networks);
}

SharedNetwork4Collection
PgSqlConfigBackendDHCPv4::getModifiedSharedNetworks4(
    const ServerSelector& server_selector,
    const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS4)
        .arg(util::ptimeToText(modification_time));
    SharedNetwork4Collection shared_networks;
    impl_->getModifiedSharedNetworks4(server_selector, modification_time, shared_networks);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_SHARED_NETWORKS4_RESULT)
        .arg(shared_networks.size());
    return (shared_networks);
}

OptionDefinitionPtr
PgSqlConfigBackendDHCPv4::getOptionDef4(const ServerSelector& server_selector,
                                        const uint16_t code,
                                        const std::string& space) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_OPTION_DEF4).arg(code).arg(space);
    return (impl_->getOptionDef(PgSqlConfigBackendDHCPv4Impl::GET_OPTION_DEF4_CODE_SPACE,
                                server_selector, code, space));
}

OptionDefContainer
PgSqlConfigBackendDHCPv4::getAllOptionDefs4(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTION_DEFS4);
    OptionDefContainer option_defs;
    impl_->getAllOptionDefs(PgSqlConfigBackendDHCPv4Impl::GET_ALL_OPTION_DEFS4, server_selector,
                            option_defs);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTION_DEFS4_RESULT)
        .arg(option_defs.size());
    return (option_defs);
}

OptionDefContainer
PgSqlConfigBackendDHCPv4::getModifiedOptionDefs4(
    const ServerSelector& server_selector,
    const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTION_DEFS4)
        .arg(util::ptimeToText(modification_time));
    OptionDefContainer option_defs;
    impl_->getModifiedOptionDefs(PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_OPTION_DEFS4,
                                 server_selector, modification_time, option_defs);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTION_DEFS4_RESULT)
        .arg(option_defs.size());
    return (option_defs);
}

OptionDescriptorPtr
PgSqlConfigBackendDHCPv4::getOption4(const ServerSelector& server_selector,
                                     const uint16_t code,
                                     const std::string& space) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_OPTION4).arg(code).arg(space);
    return (impl_->getOption(PgSqlConfigBackendDHCPv4Impl::GET_OPTION4_CODE_SPACE, Option::V4,
                             server_selector, code, space));
}

OptionContainer
PgSqlConfigBackendDHCPv4::getAllOptions4(const ServerSelector& server_selector) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTIONS4);
    OptionContainer options = impl_->getAllOptions(PgSqlConfigBackendDHCPv4Impl::GET_ALL_OPTIONS4,
                                                   Option::V4, server_selector);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_OPTIONS4_RESULT)
        .arg(options.size());
    return (options);
}

OptionContainer
PgSqlConfigBackendDHCPv4::getModifiedOptions4(
    const ServerSelector& server_selector,
    const boost::posix_time::ptime& modification_time) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTIONS4)
        .arg(util::ptimeToText(modification_time));
    OptionContainer options =
        impl_->getModifiedOptions(PgSqlConfigBackendDHCPv4Impl::GET_MODIFIED_OPTIONS4, Option::V4,
                                  server_selector, modification_time);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_MODIFIED_OPTIONS4_RESULT)
        .arg(options.size());
    return (options);
}

StampedValuePtr
PgSqlConfigBackendDHCPv4::getGlobalParameter4(const ServerSelector& server_selector,
                                              const std::string& name) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_GLOBAL_PARAMETER4).arg(name);
    return (impl_->getGlobalParameter4(server_selector, name));
}

StampedValueCollection
PgSqlConfigBackendDHCPv4::getAllGlobalParameters4(const ServerSelector& server_selector) const {
    isc_throw(NotImplemented, "Not implemented yet.");
}

StampedValueCollection
PgSqlConfigBackendDHCPv4::getModifiedGlobalParameters4(
    const db::ServerSelector& server_selector,
    const boost::posix_time::ptime& modification_time) const {
    isc_throw(NotImplemented, "Not implemented yet.");
}

AuditEntryCollection
PgSqlConfigBackendDHCPv4::getRecentAuditEntries(const db::ServerSelector& server_selector,
                                                const boost::posix_time::ptime& modification_time,
                                                const uint64_t& modification_id) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_RECENT_AUDIT_ENTRIES4)
        .arg(util::ptimeToText(modification_time))
        .arg(modification_id);
    AuditEntryCollection audit_entries;
    impl_->getRecentAuditEntries(PgSqlConfigBackendDHCPv4Impl::GET_AUDIT_ENTRIES4_TIME,
                                 server_selector, modification_time, modification_id,
                                 audit_entries);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_RECENT_AUDIT_ENTRIES4_RESULT)
        .arg(audit_entries.size());
    return (audit_entries);
}

ServerCollection
PgSqlConfigBackendDHCPv4::getAllServers4() const {
    ServerCollection servers;

    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SERVERS4);
    impl_->getAllServers(PgSqlConfigBackendDHCPv4Impl::GET_ALL_SERVERS4, servers);

    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_ALL_SERVERS4_RESULT)
        .arg(servers.size());
    return (servers);
}

ServerPtr
PgSqlConfigBackendDHCPv4::getServer4(const data::ServerTag& server_tag) const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_SERVER4).arg(server_tag.get());
    return (impl_->getServer(PgSqlConfigBackendDHCPv4Impl::GET_SERVER4, server_tag));
}

void
PgSqlConfigBackendDHCPv4::createUpdateSubnet4(const ServerSelector& server_selector,
                                              const Subnet4Ptr& subnet) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SUBNET4).arg(subnet);
    impl_->createUpdateSubnet4(server_selector, subnet);
}

void
PgSqlConfigBackendDHCPv4::createUpdateSharedNetwork4(const ServerSelector& server_selector,
                                                     const SharedNetwork4Ptr& shared_network) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK4)
        .arg(shared_network->getName());
    impl_->createUpdateSharedNetwork4(server_selector, shared_network);
}

void
PgSqlConfigBackendDHCPv4::createUpdateOptionDef4(const ServerSelector& server_selector,
                                                 const OptionDefinitionPtr& option_def) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_OPTION_DEF4)
        .arg(option_def->getName())
        .arg(option_def->getCode());
    impl_->createUpdateOptionDef4(server_selector, option_def);
}

void
PgSqlConfigBackendDHCPv4::createUpdateOption4(const ServerSelector& server_selector,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_OPTION4);
    impl_->createUpdateOption4(server_selector, option);
}

void
PgSqlConfigBackendDHCPv4::createUpdateOption4(const db::ServerSelector& server_selector,
                                              const std::string& shared_network_name,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SHARED_NETWORK_OPTION4)
        .arg(shared_network_name);
    impl_->createUpdateOption4(server_selector, shared_network_name, option, false);
}

void
PgSqlConfigBackendDHCPv4::createUpdateOption4(const ServerSelector& server_selector,
                                              const SubnetID& subnet_id,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_BY_SUBNET_ID_OPTION4)
        .arg(subnet_id);
    impl_->createUpdateOption4(server_selector, subnet_id, option, false);
}

void
PgSqlConfigBackendDHCPv4::createUpdateOption4(const ServerSelector& server_selector,
                                              const asiolink::IOAddress& pool_start_address,
                                              const asiolink::IOAddress& pool_end_address,
                                              const OptionDescriptorPtr& option) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_BY_POOL_OPTION4)
        .arg(pool_start_address.toText())
        .arg(pool_end_address.toText());
    impl_->createUpdateOption4(server_selector, pool_start_address, pool_end_address, option);
}

void
PgSqlConfigBackendDHCPv4::createUpdateGlobalParameter4(const ServerSelector& server_selector,
                                                       const StampedValuePtr& value) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_GLOBAL_PARAMETER4)
        .arg(value->getName());
    impl_->createUpdateGlobalParameter4(server_selector, value);
}

void
PgSqlConfigBackendDHCPv4::createUpdateServer4(const ServerPtr& server) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_CREATE_UPDATE_SERVER4)
        .arg(server->getServerTagAsText());
    impl_->createUpdateServer(PgSqlConfigBackendDHCPv4Impl::CREATE_AUDIT_REVISION,
                              PgSqlConfigBackendDHCPv4Impl::INSERT_SERVER4,
                              PgSqlConfigBackendDHCPv4Impl::UPDATE_SERVER4, server);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteSubnet4(const ServerSelector& server_selector,
                                        const std::string& subnet_prefix) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_PREFIX_SUBNET4)
        .arg(subnet_prefix);
    uint64_t result = impl_->deleteSubnet4(server_selector, subnet_prefix);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_PREFIX_SUBNET4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteSubnet4(const ServerSelector& server_selector,
                                        const SubnetID& subnet_id) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET4)
        .arg(subnet_id);
    uint64_t result = impl_->deleteSubnet4(server_selector, subnet_id);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_SUBNET4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteAllSubnets4(const ServerSelector& server_selector) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SUBNETS4);

    int index = (server_selector.amUnassigned() ?
                     PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4_UNASSIGNED :
                     PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4);
    uint64_t result = impl_->deleteTransactional(index, server_selector, "deleting all subnets",
                                                 "deleted all subnets", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SUBNETS4_RESULT).arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteSharedNetworkSubnets4(const db::ServerSelector& server_selector,
                                                      const std::string& shared_network_name) {
    if (!server_selector.amAny()) {
        isc_throw(InvalidOperation, "deleting all subnets from a shared "
                                    "network requires using ANY server selector");
    }
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS4)
        .arg(shared_network_name);
    uint64_t result = impl_->deleteTransactional(
        PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SUBNETS4_SHARED_NETWORK_NAME, server_selector,
        "deleting all subnets for a shared network", "deleted all subnets for a shared network",
        true, shared_network_name);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_SUBNETS4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteSharedNetwork4(const ServerSelector& server_selector,
                                               const std::string& name) {
    /// @todo Using UNASSIGNED selector is allowed by the CB API but we don't have
    /// dedicated query for this at the moment. The user should use ANY to delete
    /// the shared network by name.
    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented,
                  "deleting an unassigned shared network requires "
                  "an explicit server tag or using ANY server. The UNASSIGNED server "
                  "selector is currently not supported");
    }

    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK4).arg(name);

    int index = (server_selector.amAny() ?
                     PgSqlConfigBackendDHCPv4Impl::DELETE_SHARED_NETWORK4_NAME_ANY :
                     PgSqlConfigBackendDHCPv4Impl::DELETE_SHARED_NETWORK4_NAME_WITH_TAG);
    uint64_t result = impl_->deleteTransactional(index, server_selector,
                                                 "deleting a shared network",
                                                 "shared network deleted", true, name);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteAllSharedNetworks4(const ServerSelector& server_selector) {
    if (server_selector.amAny()) {
        isc_throw(InvalidOperation, "deleting all shared networks for ANY server is not"
                                    " supported");
    }

    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SHARED_NETWORKS4);

    int index = (server_selector.amUnassigned() ?
                     PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SHARED_NETWORKS4_UNASSIGNED :
                     PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_SHARED_NETWORKS4);
    uint64_t result = impl_->deleteTransactional(index, server_selector,
                                                 "deleting all shared networks",
                                                 "deleted all shared networks", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SHARED_NETWORKS4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteOptionDef4(const ServerSelector& server_selector,
                                           const uint16_t code,
                                           const std::string& space) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION_DEF4).arg(code).arg(space);
    uint64_t result = impl_->deleteOptionDef4(server_selector, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION_DEF4_RESULT).arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteAllOptionDefs4(const ServerSelector& server_selector) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_OPTION_DEFS4);
    uint64_t result =
        impl_->deleteTransactional(PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_OPTION_DEFS4,
                                   server_selector, "deleting all option definitions",
                                   "deleted all option definitions", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_OPTION_DEFS4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& server_selector,
                                        const uint16_t code,
                                        const std::string& space) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION4).arg(code).arg(space);
    uint64_t result = impl_->deleteOption4(server_selector, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_OPTION4_RESULT).arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& /* server_selector */,
                                        const std::string& shared_network_name,
                                        const uint16_t code,
                                        const std::string& space) {
    /// @todo In the future we might use the server selector to make sure that the
    /// option is only deleted if the pool belongs to a given server. For now, we
    /// just delete it when there is a match with the parent object.
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_OPTION4)
        .arg(shared_network_name)
        .arg(code)
        .arg(space);
    uint64_t result = impl_->deleteOption4(ServerSelector::ANY(), shared_network_name, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SHARED_NETWORK_OPTION4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& /* server_selector */,
                                        const SubnetID& subnet_id,
                                        const uint16_t code,
                                        const std::string& space) {
    /// @todo In the future we might use the server selector to make sure that the
    /// option is only deleted if the pool belongs to a given server. For now, we
    /// just delete it when there is a match with the parent object.
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION4)
        .arg(subnet_id)
        .arg(code)
        .arg(space);
    uint64_t result = impl_->deleteOption4(ServerSelector::ANY(), subnet_id, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_SUBNET_ID_OPTION4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& /* server_selector */,
                                        const asiolink::IOAddress& pool_start_address,
                                        const asiolink::IOAddress& pool_end_address,
                                        const uint16_t code,
                                        const std::string& space) {
    /// @todo In the future we might use the server selector to make sure that the
    /// option is only deleted if the pool belongs to a given server. For now, we
    /// just delete it when there is a match with the parent object.
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_POOL_OPTION4)
        .arg(pool_start_address.toText())
        .arg(pool_end_address.toText())
        .arg(code)
        .arg(space);
    uint64_t result = impl_->deleteOption4(ServerSelector::ANY(), pool_start_address,
                                           pool_end_address, code, space);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_BY_POOL_OPTION4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteGlobalParameter4(const ServerSelector& server_selector,
                                                 const std::string& name) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_GLOBAL_PARAMETER4).arg(name);
    uint64_t result =
        impl_->deleteTransactional(PgSqlConfigBackendDHCPv4Impl::DELETE_GLOBAL_PARAMETER4,
                                   server_selector, "deleting global parameter",
                                   "global parameter deleted", false, name);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_GLOBAL_PARAMETER4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteAllGlobalParameters4(const ServerSelector& server_selector) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS4);
    uint64_t result =
        impl_->deleteTransactional(PgSqlConfigBackendDHCPv4Impl::DELETE_ALL_GLOBAL_PARAMETERS4,
                                   server_selector, "deleting all global parameters",
                                   "all global parameters deleted", true);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_GLOBAL_PARAMETERS4_RESULT)
        .arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteServer4(const ServerTag& server_tag) {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SERVER4).arg(server_tag.get());
    uint64_t result = impl_->deleteServer4(server_tag);
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_SERVER4_RESULT).arg(result);
    return (result);
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteAllServers4() {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SERVERS4);
    uint64_t result = impl_->deleteAllServers4();
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_DELETE_ALL_SERVERS4_RESULT).arg(result);
    return (result);
}

std::string
PgSqlConfigBackendDHCPv4::getType() const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_TYPE4);
    return (impl_->getType());
}

std::string
PgSqlConfigBackendDHCPv4::getHost() const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_HOST4);
    return (impl_->getHost());
}

uint16_t
PgSqlConfigBackendDHCPv4::getPort() const {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_GET_PORT4);
    return (impl_->getPort());
}

bool
PgSqlConfigBackendDHCPv4::registerBackendType() {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_REGISTER_BACKEND_TYPE4);
    return (dhcp::ConfigBackendDHCPv4Mgr::instance().registerBackendFactory(
        "pgsql",
        [](const db::DatabaseConnection::ParameterMap& params) -> dhcp::ConfigBackendDHCPv4Ptr {
            // Many virtual function still missing
            return (dhcp::PgSqlConfigBackendDHCPv4Ptr(new dhcp::PgSqlConfigBackendDHCPv4(params)));
        }));
}

void
PgSqlConfigBackendDHCPv4::unregisterBackendType() {
    LOG_DEBUG(pgsql_cb_logger, DBGLVL_TRACE_BASIC, PGSQL_CB_UNREGISTER_BACKEND_TYPE4);
    dhcp::ConfigBackendDHCPv4Mgr::instance().unregisterBackendFactory("pgsql");
}

void
PgSqlConfigBackendDHCPv4::createUpdateClientClass4(const db::ServerSelector& server_selector,
                                                   const ClientClassDefPtr& client_class,
                                                   const std::string& follow_class_name) {
    isc_throw(NotImplemented, "Not implemented yet.");
}

ClientClassDefPtr
PgSqlConfigBackendDHCPv4::getClientClass4(const db::ServerSelector& selector,
                                          const std::string& name) const {
    isc_throw(NotImplemented, "Not implemented yet.");
}

ClientClassDictionary
PgSqlConfigBackendDHCPv4::getAllClientClasses4(const db::ServerSelector& selector) const {
    isc_throw(NotImplemented, "Not implemented yet.");
}

ClientClassDictionary
PgSqlConfigBackendDHCPv4::getModifiedClientClasses4(
    const db::ServerSelector& selector, const boost::posix_time::ptime& modification_time) const {
    isc_throw(NotImplemented, "Not implemented yet.");
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteClientClass4(const db::ServerSelector& server_selector,
                                             const std::string& name) {
    isc_throw(NotImplemented, "Not implemented yet.");
}

uint64_t
PgSqlConfigBackendDHCPv4::deleteAllClientClasses4(const db::ServerSelector& server_selector) {
    isc_throw(NotImplemented, "Not implemented yet.");
}

}  // namespace dhcp
}  // end of namespace isc
