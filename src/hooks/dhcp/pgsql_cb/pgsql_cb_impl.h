// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
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
/// PostgreSQL database, used by all servers.
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
        /// PostgreSQL CB implementation object which prevents new audit
        /// revisions to be created while this instance exists.
        ///
        /// @param impl pointer to the PostgreSQL CB implementation.
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

        /// @brief Pointer to the PostgreSQL CB implementation.
        PgSqlConfigBackendImpl* impl_;
    };

public:

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    /// @param db_reconnect_callback The connection recovery callback.
    /// @param last_insert_id_index statement index of the SQL statement to
    /// use when fetching the last insert id for a given table.
    explicit PgSqlConfigBackendImpl(const db::DatabaseConnection::ParameterMap& parameters,
                                    const db::DbCallback db_reconnect_callback,
                                    const size_t last_insert_id_index);

    /// @brief Destructor.
    virtual ~PgSqlConfigBackendImpl();

    /// @brief Returns server tag associated with the particular selector.
    ///
    /// This method expects that there is exactly one server tag associated with
    /// the server selector.
    ///
    /// @param server_selector Server selector.
    /// @param operation Operation which results in calling this function. This is
    /// used for error reporting purposes.
    /// @return Server tag.
    /// @throw InvalidOperation if the server selector is unassigned or if there
    /// is more than one server tag associated with the selector.
    std::string getServerTag(const db::ServerSelector& server_selector,
                             const std::string& operation) const {
        auto const& tags = server_selector.getTags();
        if (tags.size() != 1) {
            isc_throw(InvalidOperation, "expected exactly one server tag to be specified"
                      " while " << operation << ". Got: "
                      << getServerTagsAsText(server_selector));
        }

        return (tags.begin()->get());
    }

    /// @brief Returns server tags associated with the particular selector
    /// as text.
    ///
    /// This method is useful for logging purposes.
    std::string getServerTagsAsText(const db::ServerSelector& server_selector) const {
        std::ostringstream s;
        auto const& server_tags = server_selector.getTags();
        for (auto const& tag : server_tags) {
            if (s.tellp() != 0) {
                s << ", ";
            }
            s << tag.get();
        }

        return (s.str());
    }

    /// @brief Invokes the corresponding stored procedure in PgSQL.
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

    /// @brief Sends query to delete rows from a table.
    ///
    /// @param index Index of the statement to be executed.
    /// @param server_selector Server selector.
    /// @param operation Operation which results in calling this function. This is
    /// used for logging purposes.
    /// @param in_bindings Reference to the PgSQL input bindings. They are modified
    /// as a result of this function - server tag is inserted into the beginning
    /// of the bindings collection.
    /// @return Number of deleted rows.
    uint64_t deleteFromTable(const int index,
                             const db::ServerSelector& server_selector,
                             const std::string& operation,
                             db::PsqlBindArray& bindings);

    /// @brief Sends query to delete rows from a table.
    ///
    /// @tparam KeyType Type of the key used as the second binding. The
    /// server tag is used as first binding.
    ///
    /// @param index Index of the statement to be executed.
    /// @param server_selector Server selector.
    /// @param operation Operation which results in calling this function. This is
    /// used for error reporting purposes.
    /// @param key Value to be used as input binding to the delete
    /// statement. The default value is empty which indicates that the
    /// key should not be used in the query.
    /// @return Number of deleted rows.
    /// @throw InvalidOperation if the server selector is unassigned or
    /// if there are more than one server tags associated with the
    /// server selector.
    template<typename KeyType>
    uint64_t deleteFromTable(const int index,
                             const db::ServerSelector& server_selector,
                             const std::string& operation,
                             KeyType key) {
        // When deleting by some key, we must use ANY.
        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "deleting an unassigned object requires "
                      "an explicit server tag or using ANY server. The UNASSIGNED "
                      "server selector is currently not supported");
        }

        db::PsqlBindArray in_bindings;
        in_bindings.add(key);
        return (deleteFromTable(index, server_selector, operation, in_bindings));
    }

    /// @brief Returns the last sequence value for the given table and
    /// column name.
    ///
    /// This relies on PostgreSQL's currval() function which will return
    /// the last value generated for the sequence within the current session.
    ///
    /// @param table name of the table
    /// @param column name of the sequence column
    /// @return returns the most recently modified value for the given
    /// sequence
    uint64_t getLastInsertId(const std::string& table, const std::string& column);

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
    void getOptionDefs(const int index,
                       const db::PsqlBindArray& in_bindings,
                       OptionDefContainer& option_defs);

    /// @brief Creates or updates an option definition.
    ///
    /// @param server_selector Server selector.
    /// @param universe Option universe, i.e. V4 or V6.
    /// @param option_def Option definition to be added or updated.
    /// @param space Default option space
    /// @param get_option_def_code_space Statement getting option
    /// definition by code and space.
    /// @param insert_option_def Statement inserting option definition.
    /// @param update_option_def Statement updating option definition.
    /// @param create_audit_revision Statement creating audit revision.
    /// @param insert_option_def_server Statement associating option
    /// definition with a server.
    /// @param client_class_name Optional client class name to which
    /// the option definition belongs. If this value is not specified,
    /// it is a global option definition.
    /// @throw NotImplemented if server selector is "unassigned".
    void createUpdateOptionDef(const db::ServerSelector& server_selector,
                               const Option::Universe& universe,
                               const OptionDefinitionPtr& option_def,
                               const std::string& space,
                               const int& get_option_def_code_space,
                               const int& insert_option_def,
                               const int& update_option_def,
                               const int& create_audit_revision,
                               const int& insert_option_def_server,
                               const std::string& client_class_name = "");

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
    OptionDescriptorPtr getOption(const int index,
                                  const Option::Universe& universe,
                                  const db::ServerSelector& server_selector,
                                  const uint16_t code,
                                  const std::string& space);

    /// @brief Sends query to retrieve all global options.
    ///
    /// @param index Index of the query to be used.
    /// @param universe Option universe, i.e. V4 or V6.
    /// @param server_selector Server selector.
    /// @return Container holding returned options.
    OptionContainer getAllOptions(const int index,
                                  const Option::Universe& universe,
                                  const db::ServerSelector& server_selector);

    /// @brief Sends query to retrieve global options with modification
    /// time later than specified timestamp.
    ///
    /// @param index Index of the query to be used.
    /// @param universe Option universe, i.e. V4 or V6.
    /// @param server_selector Server selector.
    /// @return Container holding returned options.
    OptionContainer getModifiedOptions(const int index,
                                       const Option::Universe& universe,
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

    /// @brief Returns DHCP option instance from a set of columns within a
    /// result set row.
    ///
    /// The following is the expected order of columns specified in the SELECT
    /// query:
    /// - option_id,
    /// - code,
    /// - value,
    /// - formatted_value,
    /// - space,
    /// - persistent,
    /// - dhcp4_subnet_id/dhcp6_subnet_id,
    /// - scope_id,
    /// - user_context,
    /// - shared_network_name,
    /// - pool_id,
    /// - [pd_pool_id,]
    /// - modification_ts
    ///
    /// @note The universe is reused to switch between DHCPv4 and DHCPv6
    /// option layouts.
    /// @param universe V4 or V6.
    /// @param worker result set row worker containing the row data
    /// @param first_col column index of the first column (i.e. option_id)
    /// in the row.
    OptionDescriptorPtr processOptionRow(const Option::Universe& universe,
                                         db::PgSqlResultRowWorker& worker,
                                         const size_t first_col);

    /// @brief Returns DHCP option definition instance from output bindings.
    ///
    /// The following is the expected order of columns specified in the SELECT
    /// query:
    /// - id,
    /// - code,
    /// - name,
    /// - space,
    /// - type,
    /// - modification_ts,
    /// - is_array,
    /// - encapsulate,
    /// - record_types,
    /// - user_context
    ///
    /// @param worker result set row worker containing the row data
    /// @param first_col column index of the first column (i.e. definition id)
    /// in the row.
    /// @return Pointer to the option definition.
    OptionDefinitionPtr processOptionDefRow(db::PgSqlResultRowWorker& worker,
                                            const size_t first_col);

    /// @brief Associates a configuration element with multiple servers.
    ///
    /// @param index Query index.
    /// @param server_selector Server selector, perhaps with multiple server tags.
    /// @param in_bindings Parameter pack holding bindings for the query. The first
    /// entry must be the primary key of the element to attach. Note that
    /// the server tag (or server id) must be the last binding in the prepared
    /// statement. The caller must not include this binding in the parameter pack.
    void attachElementToServers(const int index,
                                const db::ServerSelector& server_selector,
                                const db::PsqlBindArray& in_bindings);

    /// @brief Adds network ddns-replace-client-name mode to a bind array.
    ///
    /// If network's value of ddns-replace-client-name mode has been specified
    /// it is added to the binding, otherwise a null is added to the binding.
    ///
    /// @param bindings PsqlBindArray to which the mode should be added.
    /// @param network Pointer to shared network or subnet for which mode binding
    /// should be created.
    void addDdnsReplaceClientNameBinding(db::PsqlBindArray& bindings,
                                         const NetworkPtr& network);

    /// @brief Adds network relays addresses to a bind array.
    ///
    /// Creates an Element tree of relay addresses add adds that to the end
    /// of the given bind array.
    ///
    /// @param bindings PsqlBindArray to which the relay addresses should be added.
    /// @param network Pointer to a shared network or subnet for which binding
    /// should be created.
    void addRelayBinding(db::PsqlBindArray& bindings, const NetworkPtr& network);

    /// @brief Iterates over the relay addresses in a JSON list element at a
    /// given column, adding each to the given Network's relay list.
    ///
    /// Has no effect if the column is null or is an empty list.
    ///
    /// @param worker result set row worker containing the row data
    /// @param col column index of JSON element column
    /// @param network network to update.
    ///
    /// @throw BadValue if the Element is not a list or if any of the
    /// list's elements are not valid IP addresses in string form.
    void setRelays(db::PgSqlResultRowWorker& r, size_t col, Network& network);

    /// @brief Adds 'require_client_classes' parameter to a bind array.
    ///
    /// Creates an Element tree of required class names and adds that to the end
    /// of the given bind array.
    ///
    /// @tparam T of pointer to objects with getRequiredClasses
    /// method, e.g. shared network, subnet, pool or prefix delegation pool.
    /// @param bindings PsqlBindArray to which the classes should be added.
    /// @param object Pointer to an object with getRequiredClasses method
    /// @return Pointer to the binding (possibly null binding if there are no
    /// required classes specified).
    template<typename T>
    void addRequiredClassesBinding(db::PsqlBindArray& bindings, const T& object) {
        // Create JSON list of required classes.
        data::ElementPtr required_classes_element = data::Element::createList();
        const auto& required_classes = object->getRequiredClasses();
        for (auto required_class = required_classes.cbegin();
             required_class != required_classes.cend();
             ++required_class) {
            required_classes_element->add(data::Element::create(*required_class));
        }

        bindings.add(required_classes_element);
    }

    /// @brief Iterates over the class names in a JSON list element at a
    /// given column, invoking a setter function for each one.
    ///
    /// Has no effect if the column is null or is an empty list.
    ///
    /// @param worker result set row worker containing the row data
    /// @param col column index of JSON element column
    /// @param setter function to invoke for each class name in the list
    ///
    /// @throw BadValue if the Element is not a list or if any of the
    /// list's elements are not strings.
    void setRequiredClasses(db::PgSqlResultRowWorker& worker, size_t col,
                            std::function<void(const std::string&)> setter);

    /// @brief Adds an option value to a bind array.
    ///
    /// @param bindings PsqlBindArray to which the option value should be added.
    /// @param option Option descriptor holding the option who's value should
    /// added.
    void addOptionValueBinding(db::PsqlBindArray& bindings,
                               const OptionDescriptorPtr& option);

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

    /// @brief Sends query to retrieve servers.
    ///
    /// @param index Index of the query to be used.
    /// @param bindings Reference to the PgSQL input bindings.
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

    /// @brief Executes multiple update and/or delete queries with no input
    /// bindings.
    ///
    /// This is a convenience function which takes multiple query indexes as
    /// arguments and for each index executes an update or delete query.
    /// One of the applications of this function is to remove dangling
    /// configuration elements after the server associated with these elements
    /// have been deleted.
    ///
    /// @tparam T type of the indexes, e.g. @c PgSqlConfigBackendDHCPv4Impl::StatementIndex.
    /// @tparam R parameter pack holding indexes of type @c T.
    /// @param first_index first index.
    /// @param other_indexes remaining indexes.
    template<typename T, typename... R>
    void multipleUpdateDeleteQueries(T first_index, R... other_indexes) {
        std::vector<T> indexes({ first_index, other_indexes... });
        db::PsqlBindArray in_bindings;
        for (auto index : indexes) {
            updateDeleteQuery(index, in_bindings);
        }
    }

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
        for (auto elem = index.begin(); elem != index.end();) {

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
                auto const& tags = server_selector.getTags();
                bool tag_found = false;
                for (auto const& tag : tags) {
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
    /// @return "postgresql".
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

    /// @brief Sets IO service to be used by the PostgreSQL config backend.
    ///
    /// @param IOService object, used for all ASIO operations.
    static void setIOService(const isc::asiolink::IOServicePtr& io_service) {
        io_service_ = io_service;
    }

    /// @brief Returns pointer to the IO service.
    static isc::asiolink::IOServicePtr& getIOService() {
        return (io_service_);
    }

    /// @brief Fetches the SQL statement for a given statement index.
    ///
    /// Derivations must override the implementation. The reference
    /// returned should be non-volatile over the entire lifetime
    /// of the derivation instance.
    ///
    /// @param index index of the desired statement.
    /// @throw NotImplemented, always
    virtual db::PgSqlTaggedStatement& getStatement(size_t index) const;

    /// @brief Executes SELECT using the prepared statement specified
    /// by the given index.
    ///
    /// The @c index must refer to an existing prepared statement
    /// associated with the connection. The @c in_bindings size must match
    /// the number of placeholders in the prepared statement.
    ///
    /// This method executes prepared statement using provided input bindings and
    /// calls @c process_result_row function for each returned row. The
    /// @c process_result function is implemented by the caller and should
    /// gather and store each returned row in an external data structure prior.
    ///
    /// @param statement reference to the precompiled tagged statement to execute
    /// @param in_bindings input bindings holding values to substitue placeholders
    /// in the query.
    /// @param process_result_row Pointer to the function to be invoked for each
    /// retrieved row. This function consumes the retrieved data from the
    /// result set.
    void selectQuery(size_t index, const db::PsqlBindArray& in_bindings,
                     db::PgSqlConnection::ConsumeResultRowFun process_result_row);

    /// @brief Executes INSERT using the prepared statement specified
    /// by the given index.
    ///
    /// The @c index must refer to an existing prepared statement
    /// associated with the connection. The @c in_bindings size must match
    /// the number of placeholders in the prepared statement.
    ///
    /// This method executes prepared statement using provided bindings to
    /// insert data into the database.
    ///
    /// @param statement reference to the precompiled tagged statement to execute
    /// @param in_bindings input bindings holding values to substitue placeholders
    /// in the query.
    void insertQuery(size_t index, const db::PsqlBindArray& in_bindings);

    /// @brief Executes UPDATE or DELETE using the prepared statement
    /// specified by the given index, and returns the number of affected rows.
    ///
    /// The @c index must refer to an existing prepared statement
    /// associated with the connection. The @c in_bindings size must match
    /// the number of placeholders in the prepared statement.
    ///
    /// @param statement reference to the precompiled tagged statement to execute
    /// @param in_bindings Input bindings holding values to substitute placeholders
    /// in the query.
    ///
    /// @return Number of affected rows.
    uint64_t updateDeleteQuery(size_t index, const db::PsqlBindArray& in_bindings);

    /// @brief Represents connection to the PostgreSQL database.
    db::PgSqlConnection conn_;

protected:

    /// @brief Timer name used to register database reconnect timer.
    std::string timer_name_;

private:

    /// @brief Reference counter for @ScopedAuditRevision instances.
    int audit_revision_ref_count_;

    /// @brief Connection parameters
    isc::db::DatabaseConnection::ParameterMap parameters_;

    /// @brief The IOService object, used for all ASIO operations.
    static isc::asiolink::IOServicePtr io_service_;

    /// @brief Statement index of the SQL statement to use for fetching
    /// last inserted id in a given table.
    size_t last_insert_id_index_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif
