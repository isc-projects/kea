// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PGSQL_CONFIG_BACKEND_IMPL_H
#define PGSQL_CONFIG_BACKEND_IMPL_H

#include <cc/stamped_value.h>
#include <database/audit_entry.h>
#include <database/database_connection.h>
#include <database/server.h>
#include <database/server_collection.h>
#include <database/server_selector.h>
#include <dhcp/option.h>
#include <dhcp/option_definition.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/network.h>
#include <dhcpsrv/subnet_id.h>
#include <exceptions/exceptions.h>
#include <pgsql/pgsql_connection.h>
#include <pgsql/pgsql_exchange.h>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Base class for PostgreSQL Config Backend implementations.
///
/// This class contains common methods for manipulating data in the
/// Postgres database, used by all servers.
///
/// All POSIX times specified in the methods belonging to this
/// class must be local times.
class PgSqlConfigBackendImpl {
protected:

    /// @brief RAII object used to protect against creating multiple
    /// audit revisions during cascade configuration updates.
    ///
    /// Audit revision is created per a single database transaction.
    /// It includes log message associated with the configuration
    /// change. Single command sent over the control API should
    /// result in a single audit revision entry in the database.
    /// A single configuration update often consists of multiple
    /// insertions, updates and/or deletes in the database. For
    /// example, a subnet contains pools and DHCP options which are
    /// inserted to their respective tables. We refer to such update
    /// as a cascade update. Cascade update should result in a single
    /// audit revision and an audit entry for a subnet, rather than
    /// multiple audit revisions and audit entries for the subnet,
    /// pools and child DHCP options.
    ///
    /// Creating an instance of the @c ScopedAuditRevision guards
    /// against creation of multiple audit revisions when child
    /// objects are inserted or updated in the database. When the
    /// instance of this object goes out of scope the new audit
    /// revisions can be created. The caller must ensure that
    /// the instance of this object exists throughout the whole
    /// transaction with the database.
    class ScopedAuditRevision {
    public:

        /// @brief Constructor.
        ///
        /// Creates new audit revision and sets the flag in the
        /// Postgres CB implementation object which prevents new audit
        /// revisions to be created while this instance exists.
        ///
        /// @param impl pointer to the Postgres CB implementation.
        /// @param index index of the query to set session variables
        /// used for creation of the audit revision and the audit
        /// entries.
        /// @param server_selector Server selector.
        /// @param log_message log message associated with the audit
        /// revision to be inserted into the database.
        /// @param cascade_transaction boolean flag indicating if
        /// we're performing cascade transaction. If set to true,
        /// the audit entries for the child objects (e.g. DHCP
        /// options) won't be created.
        ScopedAuditRevision(PgSqlConfigBackendImpl* impl,
                            const int index,
                            const db::ServerSelector& server_selector,
                            const std::string& log_message,
                            bool cascade_transaction);

        /// @brief Destructor.
        ///
        /// Clears the flag which is blocking creation of the new
        /// audit revisions.
        ~ScopedAuditRevision();

    private:

        /// @brief Pointer to the Postgres CB implementation.
        PgSqlConfigBackendImpl* impl_;
    };

public:

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    /// @param db_reconnect_callback The connection recovery callback.
    explicit PgSqlConfigBackendImpl(const db::DatabaseConnection::ParameterMap& parameters,
                                    const db::DbCallback db_reconnect_callback);

    /// @brief Destructor.
    virtual ~PgSqlConfigBackendImpl();

    /// @todo: implement condCreateInteger(const util::Optional<T>& value)
#if 0
    static db::PsqlBindArrayPtr createBinding(const Triplet<uint32_t>& triplet);
    static db::PsqlBindArrayPtr createMaxBinding(const Triplet<uint32_t>& triplet);
    static db::PsqlBindArrayPtr createMinBinding(const Triplet<uint32_t>& triplet);
    static Triplet<uint32_t> createTriplet(const db::PsqlBindArrayPtr& binding);
    static Triplet<uint32_t> createTriplet(const db::PsqlBindArrayPtr& def_binding,
        const db::PsqlBindArrayPtr& min_binding, const db::PsqlBindArrayPtr& max_binding);
#endif
    std::string getServerTag(const db::ServerSelector& server_selector,
                            const std::string& operation );

    /// @brief Returns server tags associated with the particular selector
    /// as text.
    ///
    /// This method is useful for logging purposes.
    std::string getServerTagsAsText(const db::ServerSelector& server_selector) const {
        std::ostringstream s;
        auto server_tags = server_selector.getTags();
        for (auto tag : server_tags) {
            if (s.tellp() != 0) {
                s << ", ";
            }
            s << tag.get();
        }

        return (s.str());
    }



    /// @brief Invokes the corresponding stored procedure in MySQL.
    ///
    /// The @c createAuditRevision stored procedure creates new audit
    /// revision and initializes several session variables to be used when
    /// the audit entries will be created for the inserted, updated or
    /// deleted configuration elements.
    ///
    /// @param index query index.
    /// @param server_selector Server selector.
    /// @param audit_ts Timestamp to be associated with the audit
    /// revision.
    /// @param log_message log message to be used for the audit revision.
    /// @param cascade_transaction Boolean value indicating whether the
    /// configuration modification is performed as part of the owning
    /// element modification, e.g. subnet is modified resulting in
    /// modification of the DHCP options it owns. In that case only the
    /// audit entry for the owning element should be created.
    void createAuditRevision(const int index,
                             const db::ServerSelector& server_selector,
                             const boost::posix_time::ptime& audit_ts,
                             const std::string& log_message,
                             const bool cascade_transaction);

    /// @brief Clears the flag blocking creation of the new audit revisions.
    ///
    /// This is used by the @c ScopedAuditRevision object.
    void clearAuditRevision();

    /// @brief Sends query to the database to retrieve most recent audit entries.
    ///
    /// @param index Index of the query to be used.
    /// @param server_selector Server selector.
    /// @param modification_time Timestamp being a lower limit for the returned
    /// result set, i.e. entries later than specified time are returned.
    /// @param modification_id Identifier being a lower limit for the returned
    /// result set, used when two (or more) revisions have the same
    /// modification_time.
    /// @param [out] audit_entries Reference to the container where fetched audit
    /// entries will be inserted.
    void getRecentAuditEntries(const int index,
                               const db::ServerSelector& server_selector,
                               const boost::posix_time::ptime& modification_time,
                               const uint64_t& modification_id,
                               db::AuditEntryCollection& audit_entries);

    /// @todo: implement uint64_t deleteFromTable(const int index, ...)

    /// @brief Sends query to delete rows from a table.
    ///
    /// @param index Index of the statement to be executed.
    /// @param server_selector Server selector.
    /// @param operation Operation which results in calling this function. This is
    /// used for error reporting purposes.
    /// @return Number of deleted rows.
    uint64_t deleteFromTable(const int index,
                             const db::ServerSelector& server_selector,
                             const std::string& operation);

    uint64_t deleteFromTable(const int index,
                             const db::ServerSelector& server_selector,
                             const std::string& operation,
                             db::PsqlBindArray& bindings);

    /// @brief Sends query to retrieve multiple global parameters.
    ///
    /// @param index Index of the query to be used.
    /// @param in_bindings Input bindings specifying selection criteria. The
    /// size of the bindings collection must match the number of placeholders
    /// in the prepared statement. The input bindings collection must be empty
    /// if the query contains no WHERE clause.
    /// @param [out] parameters Reference to the container where fetched parameters
    /// will be inserted.
    void getGlobalParameters(const int index,
                             const db::PsqlBindArray& in_bindings,
                             data::StampedValueCollection& parameters);

    /// @brief Sends query to retrieve single option definition by code and
    /// option space.
    ///
    /// @param index Index of the query to be used.
    /// @param server_selector Server selector.
    /// @param code Option code.
    /// @param space Option space name.
    ///
    /// @return Pointer to the returned option definition or NULL if such
    /// option definition doesn't exist.
    OptionDefinitionPtr getOptionDef(const int index,
                                     const db::ServerSelector& server_selector,
                                     const uint16_t code,
                                     const std::string& space);

    /// @brief Sends query to retrieve all option definitions.
    ///
    /// @param index Index of the query to be used.
    /// @param server_selector Server selector.
    /// @param [out] option_defs Reference to the container where option
    /// definitions are to be stored.
    void getAllOptionDefs(const int index,
                          const db::ServerSelector& server_selector,
                          OptionDefContainer& option_defs);

    /// @brief Sends query to retrieve option definitions with modification
    /// time later than specified timestamp.
    ///
    /// @param index Index of the query to be used.
    /// @param server_selector Server selector.
    /// @param modification_time Lower bound subnet modification time.
    /// @param [out] option_defs Reference to the container where option
    /// definitions are to be stored.
    void getModifiedOptionDefs(const int index,
                               const db::ServerSelector& server_selector,
                               const boost::posix_time::ptime& modification_time,
                               OptionDefContainer& option_defs);

    /// @brief Sends query to the database to retrieve multiple option
    /// definitions.
    ///
    /// Query should order option definitions by id.
    ///
    /// @param index Index of the query to be used.
    /// @param in_bindings Input bindings specifying selection criteria. The
    /// size of the bindings collection must match the number of placeholders
    /// in the prepared statement. The input bindings collection must be empty
    /// if the query contains no WHERE clause.
    /// @param [out] option_defs Reference to the container where fetched
    /// option definitions will be inserted.
    void
    getOptionDefs(const int index,
                  const db::PsqlBindArray& in_bindings,
                  OptionDefContainer& option_defs);

    /// @brief Creates or updates an option definition.
    ///
    /// @param server_selector Server selector.
    /// @param option_def Option definition to be added or updated.
    /// @param space Default option space
    /// @param get_option_def_code_space Statement getting option
    /// definition by code and space.
    /// @param insert_option_def Statement inserting option definition.
    /// @param update_option_def Statement updating option definition.
    /// @param create_audit_revision Statement creating audit revision.
    /// @param insert_option_def_server Statement associating option
    /// definition with a server.
    /// @throw NotImplemented if server selector is "unassigned".
    void createUpdateOptionDef(const db::ServerSelector& server_selector,
                               const OptionDefinitionPtr& option_def,
                               const std::string& space,
                               const int& get_option_def_code_space,
                               const int& insert_option_def,
                               const int& update_option_def,
                               const int& create_audit_revision,
                               const int& insert_option_def_server);

    /// @brief Sends query to retrieve single global option by code and
    /// option space.
    ///
    /// @param index Index of the query to be used.
    /// @param universe Option universe, i.e. V4 or V6.
    /// @param server_selector Server selector.
    /// @param code Option code.
    /// @param space Option space name.
    ///
    /// @return Pointer to the returned option or NULL if such option
    /// doesn't exist.
    OptionDescriptorPtr
    getOption(const int index, const Option::Universe& universe,
              const db::ServerSelector& server_selector, const uint16_t code,
              const std::string& space);

    /// @brief Sends query to retrieve all global options.
    ///
    /// @param index Index of the query to be used.
    /// @param universe Option universe, i.e. V4 or V6.
    /// @param server_selector Server selector.
    /// @return Container holding returned options.
    OptionContainer
    getAllOptions(const int index, const Option::Universe& universe,
                  const db::ServerSelector& server_selector);

    /// @brief Sends query to retrieve global options with modification
    /// time later than specified timestamp.
    ///
    /// @param index Index of the query to be used.
    /// @param universe Option universe, i.e. V4 or V6.
    /// @param server_selector Server selector.
    /// @return Container holding returned options.
    OptionContainer
    getModifiedOptions(const int index, const Option::Universe& universe,
                       const db::ServerSelector& server_selector,
                       const boost::posix_time::ptime& modification_time);

    /// @brief Sends query to retrieve single option by code and option space
    /// for a given subnet id.
    ///
    /// @param index Index of the query to be used.
    /// @param universe Option universe, i.e. V4 or V6.
    /// @param server_selector Server selector.
    /// @param subnet_id Subnet identifier.
    /// @param code Option code.
    /// @param space Option space name.
    ///
    /// @return Pointer to the returned option descriptor or NULL if such
    /// option doesn't exist.
    OptionDescriptorPtr getOption(const int index,
                                  const Option::Universe& universe,
                                  const db::ServerSelector& server_selector,
                                  const dhcp::SubnetID& subnet_id,
                                  const uint16_t code,
                                  const std::string& space);

    /// @brief Sends query to retrieve single option by code and option space
    /// for a given address or prefix delegation (v6) pool id.
    ///
    /// @param index Index of the query to be used.
    /// @param server_selector Server selector.
    /// @param pool_type Pool type (Lease::TYPE_V4, TYPE_NA or TYPE_PD).
    /// @param pool_id Pool identifier in the database.
    /// @param code Option code.
    /// @param space Option space name.
    ///
    /// @return Pointer to the returned option descriptor or NULL if such
    /// option doesn't exist.
    OptionDescriptorPtr getOption(const int index,
                                  const db::ServerSelector& server_selector,
                                  const dhcp::Lease::Type& pool_type,
                                  const uint64_t pool_id,
                                  const uint16_t code,
                                  const std::string& space);

    /// @brief Sends query to retrieve single option by code and option space
    /// for a given shared network.
    ///
    /// @param index Index of the query to be used.
    /// @param universe Option universe, i.e. V4 or V6.
    /// @param server_selector Server selector.
    /// @param shared_network_name Shared network name.
    /// @param code Option code.
    /// @param space Option space name.
    ///
    /// @return Pointer to the returned option descriptor or NULL if such
    /// option doesn't exist.
    OptionDescriptorPtr getOption(const int index,
                                  const Option::Universe& universe,
                                  const db::ServerSelector& server_selector,
                                  const std::string& shared_network_name,
                                  const uint16_t code,
                                  const std::string& space);

    /// @brief Sends query to the database to retrieve multiple options.
    ///
    /// Query should order by option_id.
    ///
    /// @note The universe is reused to switch between DHCPv4 and DHCPv6
    /// option layouts.
    /// @param family Address family (either AF_INET or AF_INET6).
    /// @param index Index of the query to be used.
    /// @param in_bindings Input bindings specifying selection criteria. The
    /// size of the bindings collection must match the number of placeholders
    /// in the prepared statement. The input bindings collection must be empty
    /// if the query contains no WHERE clause.
    /// @param universe Option universe, i.e. V4 or V6.
    /// @param [out] options Reference to the container where fetched options
    /// will be inserted.
    void getOptions(const int index,
                    const db::PsqlBindArray& in_bindings,
                    const Option::Universe& universe,
                    OptionContainer& options);

    /// @todo implement OptionDescriptorPtr processOptionRow(const Option::Universe& universe, ...)

    /// @todo implement void attachElementToServers(const int index, ...)

    /// @todo implement
    db::PsqlBindArrayPtr createInputRelayBinding(const NetworkPtr& network);

    /// @todo implement template<typename T> db::MySqlBindingPtr createInputRequiredClassesBinding(const T& object)

    /// @todo implement db::MySqlBindingPtr createInputContextBinding(const T& config_element) {

    /// @todo implement
    db::PsqlBindArrayPtr createOptionValueBinding(const OptionDescriptorPtr& option);

    /// @brief Retrieves a server.
    ///
    /// @param index Index of the query to be used.
    /// @param server_tag Server tag of the server to be retrieved.
    /// @return Pointer to the @c Server object representing the server or
    /// null if such server doesn't exist.
    db::ServerPtr getServer(const int index, const data::ServerTag& server_tag);

    /// @brief Retrieves all servers.
    ///
    /// @param index Index of the query to be used.
    /// @param [out] servers Reference to the container where fetched servers
    /// will be inserted.
    void getAllServers(const int index, db::ServerCollection& servers);

    /// @todo implement
    /// @brief Sends query to retrieve servers.
    ///
    /// @param index Index of the query to be used.
    /// @param bindings Reference to the MySQL input bindings.
    /// @param [out] servers Reference to the container where fetched servers
    /// will be inserted.
    void getServers(const int index,
                    const db::PsqlBindArray& bindings,
                    db::ServerCollection& servers);

    /// @brief Creates or updates a server.
    ///
    /// This method attempts to insert a new server into the database using
    /// the query identified by @c create_index. If the insertion fails because
    /// the server with the given tag already exists in the database, the
    /// existing server is updated using the query identified by the
    /// @c update_index.
    ///
    /// @param create_audit_revision Index of the query inserting audit
    /// revision.
    /// @param create_index Index of the INSERT query to be used.
    /// @param update_index Index of the UPDATE query to be used.
    /// @param server Pointer to the server to be inserted or updated.
    /// @throw InvalidOperation when trying to create a duplicate or
    /// update the logical server 'all'.
    void createUpdateServer(const int& create_audit_revision,
                            const int& create_index,
                            const int& update_index,
                            const db::ServerPtr& server);

    /// @todo implement template<typename T, typename... R> void multipleUpdateDeleteQueries(T first_index, R... other_indexes)

    /// @brief Removes configuration elements from the index which don't match
    /// the specified server selector.
    ///
    /// This is a generic function which removes configuration elements which
    /// don't match the specified selector. In order to fetch all server tags
    /// for the returned configuration element, the query must not limit the
    /// results to the given server tag. Instead, it must post process the
    /// result to eliminate those configuration elements for which the desired
    /// server tag wasn't found.
    ///
    /// If the server selector is set to ANY, this method is no-op.
    ///
    /// @tparam CollectionIndex Type of the collection to be processed.
    /// @param server_selector Server selector.
    /// @param index Reference to the index holding the returned configuration
    /// elements to be processed.
    template<typename CollectionIndex>
    void tossNonMatchingElements(const db::ServerSelector& server_selector,
                                 CollectionIndex& index) {
        // Don't filter the matching server tags if the server selector is
        // set to ANY.
        if (server_selector.amAny()) {
            return;
        }

        // Go over the collection of elements.
        for (auto elem = index.begin(); elem != index.end(); ) {

            // If we're asking for shared networks matching all servers,
            // we have to make sure that the fetched element has "all"
            // server tag.
            if (server_selector.amAll()) {
                if (!(*elem)->hasAllServerTag()) {
                    // It doesn't so let's remove it.
                    elem = index.erase(elem);
                    continue;
                }

            } else if (server_selector.amUnassigned()) {
                // Returned element has server tags but we expect that the
                // elements are unassigned.
                if (!(*elem)->getServerTags().empty()) {
                    elem = index.erase(elem);
                    continue;
                }

            } else {
                // Server selector contains explicit server tags, so
                // let's see if the returned elements includes any of
                // them.
                auto tags = server_selector.getTags();
                bool tag_found = false;
                for (auto tag : tags) {
                    if ((*elem)->hasServerTag(tag) ||
                        (*elem)->hasAllServerTag()) {
                        tag_found = true;
                        break;
                    }
                }
                if (!tag_found) {
                    // Tag not matching, so toss the element.
                    elem = index.erase(elem);
                    continue;
                }
            }

            // Go to the next element if we didn't toss the current one.
            // Otherwise, the erase() function should have already taken
            // us to the next one.
            ++elem;
        }
    }

    /// @brief Returns backend type in the textual format.
    ///
    /// @return "pgsql".
    std::string getType() const;

    /// @brief Returns backend host.
    ///
    /// This is used by the @c BaseConfigBackendPool to select backend
    /// when @c BackendSelector is specified.
    ///
    /// @return host on which the database is located.
    std::string getHost() const;

    /// @brief Returns backend port number.
    ///
    /// This is used by the @c BaseConfigBackendPool to select backend
    /// when @c BackendSelector is specified.
    ///
    /// @return Port number on which database service is available.
    uint16_t getPort() const;

    /// @brief Return backend parameters
    ///
    /// Returns the backend parameters
    ///
    /// @return Parameters of the backend.
    const isc::db::DatabaseConnection::ParameterMap& getParameters() {
        return (parameters_);
    }

    /// @brief Sets IO service to be used by the Postgres config backend.
    ///
    /// @param IOService object, used for all ASIO operations.
    static void setIOService(const isc::asiolink::IOServicePtr& io_service) {
        io_service_ = io_service;
    }

    /// @brief Returns pointer to the IO service.
    static isc::asiolink::IOServicePtr& getIOService() {
        return (io_service_);
    }

    /// @brief Represents connection to the Postgres database.
    db::PgSqlConnection conn_;

protected:

    /// @brief Timer name used to register database reconnect timer.
    std::string timer_name_;

private:

    /// @brief Boolean flag indicating if audit revision has been created
    /// using @c ScopedAuditRevision object.
    bool audit_revision_created_;

    /// @brief Connection parameters
    isc::db::DatabaseConnection::ParameterMap parameters_;

    /// The IOService object, used for all ASIO operations.
    static isc::asiolink::IOServicePtr io_service_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif
