// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MYSQL_CONFIG_BACKEND_IMPL_H
#define MYSQL_CONFIG_BACKEND_IMPL_H

#include <database/audit_entry.h>
#include <database/database_connection.h>
#include <database/server_selector.h>
#include <dhcp/option.h>
#include <dhcp/option_definition.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/network.h>
#include <exceptions/exceptions.h>
#include <mysql/mysql_binding.h>
#include <mysql/mysql_connection.h>
#include <set>
#include <sstream>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Base class for MySQL Config Backend implementations.
///
/// This class contains common methods for manipulating data in the
/// MySQL database, used by all servers.
class MySqlConfigBackendImpl {
public:

    class ScopedAuditRevision {
    public:

        ScopedAuditRevision(MySqlConfigBackendImpl* impl,
                            const int index,
                            const std::string& log_message,
                            bool cascade_transaction);

        ~ScopedAuditRevision();

    private:
        MySqlConfigBackendImpl* impl_;

    };

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    explicit MySqlConfigBackendImpl(const db::DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor.
    ~MySqlConfigBackendImpl();

    /// @brief Returns server tags associated with the particular selector.
    ///
    /// @param server_selector Server selector.
    /// @return Set of server tags.
    std::set<std::string> getServerTags(const db::ServerSelector& server_selector) const {
        std::set<std::string> tags;
        switch (server_selector.getType()) {
        case db::ServerSelector::Type::ALL:
            tags.insert("all");
            return (tags);

        default:
            return (server_selector.getTags());
        }

        // Unassigned server case.
        return (tags);
    }

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
        auto tags = getServerTags(server_selector);
        if (tags.size() != 1) {
            isc_throw(InvalidOperation, "expected exactly one server tag to be specified"
                      " while " << operation << ". Got: "
                      << getServerTagsAsText(server_selector));
        }

        return (*tags.begin());
    }

    /// @brief Returns server tags associated with the particular selector
    /// as text.
    ///
    /// This method is useful for logging purposes.
    std::string getServerTagsAsText(const db::ServerSelector& server_selector) const {
        std::ostringstream s;
        auto server_tags = getServerTags(server_selector);
        for (auto tag : server_tags) {
            if (s.tellp() != 0) {
                s << ", ";
            }
            s << tag;
        }

        return (s.str());
    }

    /// @brief Invokes the corresponding stored procedure in MySQL.
    ///
    /// The @c initAuditRevision stored procedure initializes several
    /// session variables used when creating new audit revision in the
    /// database. That includes setting a log message for the revision,
    /// setting the boolean value indicating if the audit entries should
    /// be created for DHCP options (that should only be the case when
    /// the options are not added as part of the subnet, shared network
    /// etc.). Finally, it resets the session variables used internally
    /// by the database to corrdinate between the triggers.
    ///
    /// @param index query index.
    /// @param log_message log message to be used for the audit revision.
    /// @param cascade_transaction Boolean value indicating whether the
    /// configuration modification is performed as part of the ownining
    /// element modification, e.g. subnet is modified resulting in
    /// modification of the DHCP options it owns. In that case only the
    /// audit entry for the owning element should be created.
    void initAuditRevision(const int index,
                           const std::string& log_message,
                           const bool cascade_transaction);

    void clearAuditRevision();

    /// @brief Sends query to the database to retrieve most recent audit entries.
    ///
    /// @param index Index of the query to be used.
    /// @param modification_time Timestamp being a lower limit for the returned
    /// result set, i.e. entries later than specified time are returned.
    /// @param [out] audit_entries Reference to the container where fetched audit
    /// entries will be inserted.
    void getRecentAuditEntries(const int index,
                               const boost::posix_time::ptime& modification_time,
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

        if (server_selector.amUnassigned()) {
            isc_throw(NotImplemented, "managing configuration for no particular server"
                      " (unassigned) is unsupported at the moment");
        }

        auto tag = getServerTag(server_selector, operation);

        in_bindings.insert(in_bindings.begin(), db::MySqlBinding::createString(tag));

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
        db::MySqlBindingCollection in_bindings;

        if (db::MySqlBindingTraits<KeyType>::column_type == MYSQL_TYPE_STRING) {
            in_bindings.push_back(db::MySqlBinding::createString(key));

        } else {
            in_bindings.push_back(db::MySqlBinding::createInteger<KeyType>(key));
        }

        return (deleteFromTable(index, server_selector, operation, in_bindings));
    }

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

    /// @brief Sends query to the database to retrieve multiple options.
    ///
    /// Query should order by option_id.
    ///
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
    /// - dhcp4_subnet_id,
    /// - scope_id,
    /// - user_context,
    /// - shared_network_name,
    /// - pool_id,
    /// - modification_ts
    ///
    /// @param universe V4 or V6.
    /// @param first_binding Iterator of the output binding containing
    /// option_id.
    OptionDescriptorPtr
    processOptionRow(const Option::Universe& universe,
                     db::MySqlBindingCollection::iterator first_binding);

    /// @brief Creates input binding for relay addresses.
    ///
    /// @param network Pointer to a shared network or subnet for which binding
    /// should be created.
    /// @return Pointer to the binding (possibly null binding if there are no
    /// relay addresses specified).
    db::MySqlBindingPtr createInputRelayBinding(const NetworkPtr& network);

    /// @brief Creates input binding for 'require_client_classes' parameter.
    ///
    /// @param network Pointer to a shared network or subnet for which binding
    /// should be created.
    /// @return Pointer to the binding (possibly null binding if there are no
    /// required classes specified).
    db::MySqlBindingPtr createInputRequiredClassesBinding(const NetworkPtr& network);

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

    /// @brief Creates input binding for option value parameter.
    ///
    /// @param option Option descriptor holding option for which binding is to
    /// be created.
    /// @return Pointer to the binding (possibly null binding if formatted
    /// value is non-empty.
    db::MySqlBindingPtr createOptionValueBinding(const OptionDescriptorPtr& option);

    /// @brief Represents connection to the MySQL database.
    db::MySqlConnection conn_;

    /// @brief Boolean flag indicating if audit revision has been created
    /// using @c ScopedAuditRevision object.
    bool audit_revision_created_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif
