// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_CONFIG_BACKEND_IMPL_H
#define MYSQL_CONFIG_BACKEND_IMPL_H

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
#include <mysql/mysql_binding.h>
#include <mysql/mysql_connection.h>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Base class for MySQL Config Backend implementations.
///
/// This class contains common methods for manipulating data in the
/// MySQL database, used by all servers.
///
/// All POSIX times specified in the methods belonging to this
/// class must be local times.
class MySqlConfigBackendImpl {
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
        /// MySQL CB implementation object which prevents new audit
        /// revisions to be created while this instance exists.
        ///
        /// @param impl pointer to the MySQL CB implementation.
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
        ScopedAuditRevision(MySqlConfigBackendImpl* impl,
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

        /// @brief Pointer to the MySQL CB implementation.
        MySqlConfigBackendImpl* impl_;
    };

public:

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    /// @param db_reconnect_callback The connection recovery callback.
    explicit MySqlConfigBackendImpl(const db::DatabaseConnection::ParameterMap& parameters,
                                    const db::DbCallback db_reconnect_callback);

    /// @brief Destructor.
    virtual ~MySqlConfigBackendImpl();

    /// @brief Creates MySQL binding from an @c Optional of integer type.
    ///
    /// @tparam T Numeric type corresponding to the binding type, e.g.
    /// @c uint8_t, @c uint16_t etc.
    /// @param value Optional integer of type T.
    /// @return Pointer to a null binding if the value is "unspecified" or
    /// a pointer to a binding representing integer value.
    template<typename T>
    static db::MySqlBindingPtr condCreateInteger(const util::Optional<T>& value) {
        if (value.unspecified()) {
            return (db::MySqlBinding::createNull());
        }
        return (db::MySqlBinding::createInteger(value));
    }

    /// @brief Creates MySQL binding from a @c Triplet.
    ///
    /// @param triplet Triplet value from which the binding should be created.
    /// @return Pointer to a null binding if the triplet is "unspecified" or
    /// a pointer to a binding representing 32-bit unsigned integer value
    /// otherwise.
    static db::MySqlBindingPtr createBinding(const Triplet<uint32_t>& triplet);

    /// @brief Creates MySQL binding from a @c Triplet max value.
    ///
    /// @param triplet Triplet value from which the binding should be created.
    /// @return Pointer to a null binding if the triplet is "unspecified" or
    /// the max value is the same as the default value, or a pointer to
    /// a binding representing 32-bit unsigned integer value from the max
    /// value otherwise.
    static db::MySqlBindingPtr createMaxBinding(const Triplet<uint32_t>& triplet);

    /// @brief Creates MySQL binding from a @c Triplet min value.
    ///
    /// @param triplet Triplet value from which the binding should be created.
    /// @return Pointer to a null binding if the triplet is "unspecified" or
    /// the min value is the same as the default value, or a pointer to
    /// a binding representing 32-bit unsigned integer value from the min
    /// value otherwise.
    static db::MySqlBindingPtr createMinBinding(const Triplet<uint32_t>& triplet);

    /// @brief Creates @c Triplet object from MySQL binding.
    ///
    /// @param binding Pointer to the MySQL binding.
    /// @return Triplet value set to "unspecified" if the MySQL binding
    /// represents a NULL value or a Triplet value encapsulating 32-bit
    /// unsigned integer if the MySQL represents an integer.
    /// @throw isc::Unexpected if the provided binding pointer is NULL.
    /// @throw isc::InvalidOperation if the binding does not represent
    /// a 32-bit unsigned integer.
    static Triplet<uint32_t> createTriplet(const db::MySqlBindingPtr& binding);

    /// @brief Creates @c Triplet object from MySQL bindings.
    ///
    /// @param def_binding Pointer to the MySQL binding of the default.
    /// @param min_binding Pointer to the MySQL binding of the min value.
    /// @param max_binding Pointer to the MySQL binding of the max value.
    /// @return Triplet value set to "unspecified" if the MySQL binding
    /// represents a NULL value or a Triplet value encapsulating 32-bit
    /// unsigned integer if the MySQL represents an integer.
    /// When max or max bindings are not NULL their values are used.
    /// @throw isc::Unexpected if the provided binding pointer is NULL.
    /// @throw isc::InvalidOperation if the binding does not represent
    /// a 32-bit unsigned integer.
    static Triplet<uint32_t> createTriplet(const db::MySqlBindingPtr& def_binding,
                                           const db::MySqlBindingPtr& min_binding,
                                           const db::MySqlBindingPtr& max_binding);

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
        auto tags = server_selector.getTags();
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

    /// @brief Sends query to delete rows from a table.
    ///
    /// @param index Index of the statement to be executed.
    /// @param server_selector Server selector.
    /// @param operation Operation which results in calling this function. This is
    /// used for logging purposes.
    /// @param in_bindings Reference to the MySQL input bindings. They are modified
    /// as a result of this function - server tag is inserted into the beginning
    /// of the bindings collection.
    /// @return Number of deleted rows.
    uint64_t deleteFromTable(const int index,
                             const db::ServerSelector& server_selector,
                             const std::string& operation,
                             db::MySqlBindingCollection& in_bindings) {

        // For ANY server, we use queries that lack server tag.
        if (!server_selector.amAny() && !server_selector.amUnassigned()) {
            auto tag = getServerTag(server_selector, operation);
            in_bindings.insert(in_bindings.begin(), db::MySqlBinding::createString(tag));
        }

        return (conn_.updateDeleteQuery(index, in_bindings));
    }

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

        db::MySqlBindingCollection in_bindings;

        if (db::MySqlBindingTraits<KeyType>::column_type == MYSQL_TYPE_STRING) {
            in_bindings.push_back(db::MySqlBinding::createString(key));

        } else {
            in_bindings.push_back(db::MySqlBinding::createInteger<KeyType>(key));
        }

        return (deleteFromTable(index, server_selector, operation, in_bindings));
    }

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
                             const db::MySqlBindingCollection& in_bindings,
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
                       const db::MySqlBindingCollection& in_bindings,
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
    /// @param client_class_name Optional client class name to which
    /// the option definition belongs. If this value is not specified,
    /// it is a global option definition.
    /// @throw NotImplemented if server selector is "unassigned".
    void createUpdateOptionDef(const db::ServerSelector& server_selector,
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
                    const db::MySqlBindingCollection& in_bindings,
                    const Option::Universe& universe,
                    OptionContainer& options);

    /// @brief Returns DHCP option instance from output bindings.
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
    /// @param first_binding Iterator of the output binding containing
    /// option_id.
    OptionDescriptorPtr
    processOptionRow(const Option::Universe& universe,
                     db::MySqlBindingCollection::iterator first_binding);

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
    /// @param first_binding Iterator of the output binding containing
    /// option definition id.
    /// @return Pointer to the option definition.
    OptionDefinitionPtr
    processOptionDefRow(db::MySqlBindingCollection::iterator first_binding);

    /// @brief Associates a configuration element with multiple servers.
    ///
    /// @param index Query index.
    /// @param server_selector Server selector, perhaps with multiple server tags.
    /// @param first_binding First binding to be used in the query.
    /// @param in_bindings Parameter pack holding bindings for the query. Note that
    /// the server tag (or server id) must be the last binding in the prepared
    /// statement. The caller must not include this binding in the parameter pack.
    void attachElementToServers(const int index,
                                const db::ServerSelector& server_selector,
                                const db::MySqlBindingPtr& first_binding,
                                const db::MySqlBindingPtr& in_bindings...);

    /// @brief Creates input binding for relay addresses.
    ///
    /// @param network Pointer to a shared network or subnet for which binding
    /// should be created.
    /// @return Pointer to the binding (possibly null binding if there are no
    /// relay addresses specified).
    db::MySqlBindingPtr createInputRelayBinding(const NetworkPtr& network);

    /// @brief Creates input binding for 'require_client_classes' parameter.
    ///
    /// @tparam T of pointer to objects with getRequiredClasses
    /// method, e.g. shared network, subnet, pool or prefix delegation pool.
    /// @param object Pointer to an object with getRequiredClasses method
    /// @return Pointer to the binding (possibly null binding if there are no
    /// required classes specified).
    template<typename T>
    db::MySqlBindingPtr createInputRequiredClassesBinding(const T& object) {
        // Create JSON list of required classes.
        data::ElementPtr required_classes_element = data::Element::createList();
        const auto& required_classes = object->getRequiredClasses();
        for (auto required_class = required_classes.cbegin();
             required_class != required_classes.cend();
             ++required_class) {
            required_classes_element->add(data::Element::create(*required_class));
        }

        return (required_classes_element ?
                db::MySqlBinding::createString(required_classes_element->str()) :
                db::MySqlBinding::createNull());
    }

    /// @brief Creates input binding for user context parameter.
    ///
    /// @param T Type of the configuration element to which context belongs.
    /// @param network Pointer to a shared network, subnet or other configuration
    /// element for which binding should be created.
    /// @return Pointer to the binding (possibly null binding if context is
    /// null).
    template<typename T>
    db::MySqlBindingPtr createInputContextBinding(const T& config_element) {
        // Create user context binding if user context exists.
        auto context_element = config_element->getContext();
        return (context_element ? db::MySqlBinding::createString(context_element->str()) :
                db::MySqlBinding::createNull());
    }

    /// @brief Creates input binding for option value parameter.
    ///
    /// @param option Option descriptor holding option for which binding is to
    /// be created.
    /// @return Pointer to the binding (possibly null binding if formatted
    /// value is non-empty.
    db::MySqlBindingPtr createOptionValueBinding(const OptionDescriptorPtr& option);

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
    /// @param in_bindings Reference to the MySQL input bindings.
    /// @param [out] servers Reference to the container where fetched servers
    /// will be inserted.
    void getServers(const int index,
                    const db::MySqlBindingCollection& in_bindings,
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
    /// @tparam T type of the indexes, e.g. @c MySqlConfigBackendDHCPv4Impl::StatementIndex.
    /// @tparam R parameter pack holding indexes of type @c T.
    /// @param first_index first index.
    /// @param other_indexes remaining indexes.
    template<typename T, typename... R>
    void multipleUpdateDeleteQueries(T first_index, R... other_indexes) {
        std::vector<T> indexes({ first_index, other_indexes... });
        db::MySqlBindingCollection empty_bindings;
        for (auto index : indexes) {
            conn_.updateDeleteQuery(index, empty_bindings);
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
    /// @return "mysql".
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

    /// @brief Sets IO service to be used by the MySql config backend.
    ///
    /// @param IOService object, used for all ASIO operations.
    static void setIOService(const isc::asiolink::IOServicePtr& io_service) {
        io_service_ = io_service;
    }

    /// @brief Returns pointer to the IO service.
    static isc::asiolink::IOServicePtr& getIOService() {
        return (io_service_);
    }

    /// @brief Represents connection to the MySQL database.
    db::MySqlConnection conn_;

protected:

    /// @brief Timer name used to register database reconnect timer.
    std::string timer_name_;

private:

    /// @brief Reference counter for @ScopedAuditRevision instances.
    int audit_revision_ref_count_;

    /// @brief Connection parameters
    isc::db::DatabaseConnection::ParameterMap parameters_;

    /// The IOService object, used for all ASIO operations.
    static isc::asiolink::IOServicePtr io_service_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif
