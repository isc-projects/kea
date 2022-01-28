// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <config_backend/constants.h>
#include <dhcp/option_space.h>
#include <database/db_exceptions.h>
#include <pgsql/pgsql_exchange.h>
#include <util/buffer.h>

#include <pgsql_cb_impl.h>
#include <pgsql_cb_log.h>
#include <cstdint>
#include <utility>

using namespace isc::asiolink;
using namespace isc::cb;
using namespace isc::data;
using namespace isc::db;
using namespace isc::util;

namespace isc {
namespace dhcp {

isc::asiolink::IOServicePtr PgSqlConfigBackendImpl::io_service_ = isc::asiolink::IOServicePtr();

PgSqlTaggedStatement&
PgSqlConfigBackendImpl::getStatement(size_t /* index */) const {
    isc_throw(NotImplemented, "derivations must override this");
}

void
PgSqlConfigBackendImpl::selectQuery(size_t index,
                                    const PsqlBindArray& in_bindings,
                                    PgSqlConnection::ConsumeResultRowFun process_result_row) {
    conn_.selectQuery(getStatement(index), in_bindings, process_result_row);
}

void
PgSqlConfigBackendImpl::insertQuery(size_t index,
                                    const PsqlBindArray& in_bindings) {
    conn_.insertQuery(getStatement(index), in_bindings);
}

uint64_t
PgSqlConfigBackendImpl::updateDeleteQuery(size_t index,
                                          const PsqlBindArray& in_bindings) {
    return(conn_.updateDeleteQuery(getStatement(index), in_bindings));
}

PgSqlConfigBackendImpl::ScopedAuditRevision::ScopedAuditRevision(
    PgSqlConfigBackendImpl* impl,
    const int index,
    const ServerSelector& server_selector,
    const std::string& log_message,
    bool cascade_transaction)
    : impl_(impl) {
    impl_->createAuditRevision(index, server_selector,
                               boost::posix_time::microsec_clock::local_time(), log_message,
                               cascade_transaction);
}

PgSqlConfigBackendImpl::ScopedAuditRevision::~ScopedAuditRevision() {
    impl_->clearAuditRevision();
}

PgSqlConfigBackendImpl::PgSqlConfigBackendImpl(const DatabaseConnection::ParameterMap& parameters,
                                               const DbCallback db_reconnect_callback)
    : conn_(parameters,
            IOServiceAccessorPtr(new IOServiceAccessor(PgSqlConfigBackendImpl::getIOService)),
            db_reconnect_callback),
      timer_name_(""), audit_revision_created_(false), parameters_(parameters) {

    // Check TLS support.
    size_t tls(0);
    tls += parameters.count("trust-anchor");
    tls += parameters.count("cert-file");
    tls += parameters.count("key-file");
    tls += parameters.count("cipher-list");
#ifdef HAVE_PGSQL_SSL
    if ((tls > 0) && !PgSqlConnection::warned_about_tls) {
        PgSqlConnection::warned_about_tls = true;
        LOG_INFO(pgsql_cb_logger, PGSQL_CB_TLS_SUPPORT)
            .arg(DatabaseConnection::redactedAccessString(parameters);
        PQinitSSL(1);
    }
#else
    if (tls > 0) {
        LOG_ERROR(pgsql_cb_logger, PGSQL_CB_NO_TLS_SUPPORT)
            .arg(DatabaseConnection::redactedAccessString(parameters));
        isc_throw(DbOpenError, "Attempt to configure TLS for PostgreSQL "
                  << "backend (built with this feature disabled)");
    }
#endif

    // Test schema version first.
    std::pair<uint32_t, uint32_t> code_version(PGSQL_SCHEMA_VERSION_MAJOR, PGSQL_SCHEMA_VERSION_MINOR);
    std::pair<uint32_t, uint32_t> db_version = PgSqlConnection::getVersion(parameters);
    if (code_version != db_version) {
        isc_throw(DbOpenError, "Postgres schema version mismatch: need version: "
                                   << code_version.first << "." << code_version.second
                                   << " found version: " << db_version.first << "."
                                   << db_version.second);
    }

    // Open the database.
    conn_.openDatabase();
}

PgSqlConfigBackendImpl::~PgSqlConfigBackendImpl() {
    /// nothing to do there. The conn_ connection will be deleted and its dtor
    /// will take care of releasing the compiled statements and similar.
}

void
PgSqlConfigBackendImpl::createAuditRevision(const int index,
                                            const ServerSelector& server_selector,
                                            const boost::posix_time::ptime& audit_ts,
                                            const std::string& log_message,
                                            const bool cascade_transaction) {
    // Do not touch existing audit revision in case of the cascade update.
    if (audit_revision_created_) {
        return;
    }

    /// @todo The audit trail is not really well prepared to handle multiple server
    /// tags or no server tags. Therefore, if the server selector appears to be
    /// pointing to multiple servers, no servers or any server we simply associate the
    /// audit revision with all servers. The only case when we create a dedicated
    /// audit entry is when there is a single server tag, i.e. "all" or explicit
    /// server name. In fact, these are the most common two cases.
    std::string tag = ServerTag::ALL;
    auto tags = server_selector.getTags();
    if (tags.size() == 1) {
        tag = tags.begin()->get();
    }

    PsqlBindArray in_bindings;
    in_bindings.addTimestamp(audit_ts);
    in_bindings.add(tag);
    in_bindings.add(log_message);
    in_bindings.add(cascade_transaction);

    insertQuery(index, in_bindings);
}

void
PgSqlConfigBackendImpl::clearAuditRevision() {
    audit_revision_created_ = false;
}

void
PgSqlConfigBackendImpl::getRecentAuditEntries(const int index,
                                              const db::ServerSelector& server_selector,
                                              const boost::posix_time::ptime& modification_time,
                                              const uint64_t& modification_id,
                                              AuditEntryCollection& audit_entries) {
    auto tags = server_selector.getTags();
    for (auto tag : tags) {
        // Create the input parameters.
        PsqlBindArray in_bindings;
        in_bindings.addTempString(tag.get());
        in_bindings.addTimestamp(modification_time);
        in_bindings.add(modification_id);

        // Execute select.
        selectQuery(index, in_bindings,
                    [&audit_entries] (PgSqlResult& r, int row) {
            // Extract the column values for r[row].
            // Create a worker for the row.
            PgSqlResultRowWorker worker(r, row);

            // Get the object type. Column 0 is the entry ID which
            // we don't need here.
            std::string object_type = worker.getString(1);

            // Get the object ID.
            uint64_t object_id = worker.getBigInt(2);

            // Get the modification type.
            AuditEntry::ModificationType mod_type =
                static_cast<AuditEntry::ModificationType>(worker.getSmallInt(3));

            // Get the modification time.
            boost::posix_time::ptime mod_time = worker.getTimestamp(4);

            // Get the revision ID.
            uint64_t revision_id = worker.getBigInt(5);;

            // Get the revision log message.
            std::string log_message = worker.getString(6);

            // Create new audit entry and add it to the collection of received
            // entries.
            AuditEntryPtr audit_entry =
                AuditEntry::create(object_type, object_id, mod_type, mod_time,
                                   revision_id, log_message);
            audit_entries.insert(audit_entry);
        });
    }
}

uint64_t
PgSqlConfigBackendImpl::deleteFromTable(const int index,
                                        const ServerSelector& server_selector,
                                        const std::string& operation) {
    // When deleting multiple objects we must not use ANY server.
    if (server_selector.amAny()) {
        isc_throw(InvalidOperation, "deleting multiple objects for ANY server is not"
                                    " supported");
    }

    PsqlBindArray in_bindings;
    return (deleteFromTable(index, server_selector, operation, in_bindings));
}

uint64_t
PgSqlConfigBackendImpl::deleteFromTable(const int index,
                                        const db::ServerSelector& server_selector,
                                        const std::string& operation,
                                        db::PsqlBindArray& in_bindings) {
    // For ANY server, we use queries that lack server tag, otherwise
    // we need to insert the server tag as the first input parameter.
    if (!server_selector.amAny() && !server_selector.amUnassigned()) {
        std::string tag = getServerTag(server_selector, operation);
        in_bindings.insert(tag, 0);
    }

    return (updateDeleteQuery(index, in_bindings));
}

uint64_t
PgSqlConfigBackendImpl::getLastInsertId(const int index, const std::string& table,
                                        const std::string& column) {
    PsqlBindArray in_bindings;
    in_bindings.add(table);
    in_bindings.add(column);
    uint64_t last_id = 0;
    conn_.selectQuery(getStatement(index), in_bindings,
                    [&last_id] (PgSqlResult& r, int row) {
            // Get the object type. Column 0 is the entry ID which
            PgSqlExchange::getColumnValue(r, row, 0, last_id);
        });

    return (last_id);
}

void
PgSqlConfigBackendImpl::getGlobalParameters(const int index,
                                            const PsqlBindArray& in_bindings,
                                            StampedValueCollection& parameters) {
    // The following parameters from the dhcp[46]_global_parameter table are
    // returned per row:
    // - id
    // - parameter name
    // - parameter value
    // - parameter type
    // - modification timestamp

    StampedValuePtr last_param;
    StampedValueCollection local_parameters;
    selectQuery(index, in_bindings,
                [&local_parameters, &last_param](PgSqlResult& r, int row) {
        // Extract the column values for r[row].
        // Create a worker for the row.
        PgSqlResultRowWorker worker(r, row);

        // Get parameter ID.
        uint64_t id = worker.getBigInt(0);

        // If we're starting or if this is new parameter being processed...
        if (!last_param || (last_param->getId() != id)) {
            // Create the parameter instance.

            // Get parameter name.
            std::string name = worker.getString(1);
            if (!name.empty()) {
                // Fetch the value.
                std::string value = worker.getString(2);

                // Fetch the type.
                Element::types ptype = static_cast<Element::types>(worker.getSmallInt(3));

                // Create the parameter.
                last_param = StampedValue::create(name, value, ptype);

                // Set the id.
                last_param->setId(id);

                // Get and set the modification time.
                boost::posix_time::ptime mod_time = worker.getTimestamp(4);
                last_param->setModificationTime(mod_time);

                // server_tag
                std::string server_tag_str = worker.getString(5);
                last_param->setServerTag(server_tag_str);

                // If we're fetching parameters for a given server (explicit server
                // tag is provided), it takes precedence over the same parameter
                // specified for all servers. Therefore, we check if the given
                // parameter already exists and belongs to 'all'.
                ServerTag last_param_server_tag(server_tag_str);
                auto& index = local_parameters.get<StampedValueNameIndexTag>();
                auto existing = index.find(name);
                if (existing != index.end()) {
                    // This parameter was already fetched. Let's check if we should
                    // replace it or not.
                    if (!last_param_server_tag.amAll() && (*existing)->hasAllServerTag()) {
                        // Replace parameter specified for 'all' with the one associated
                        // with the particular server tag.
                        local_parameters.replace(existing, last_param);
                        return;
                    }
                }

                // If there is no such parameter yet or the existing parameter
                // belongs to a different server and the inserted parameter is
                // not for all servers.
                if ((existing == index.end()) ||
                    (!(*existing)->hasServerTag(last_param_server_tag) &&
                     !last_param_server_tag.amAll())) {
                    local_parameters.insert(last_param);
                }
            }
        }
    });

    parameters.insert(local_parameters.begin(), local_parameters.end());
}

OptionDefinitionPtr
PgSqlConfigBackendImpl::getOptionDef(const int /* index */,
                                     const ServerSelector& /* server_selector */,
                                     const uint16_t /* code */,
                                     const std::string& /* space */) {
    isc_throw(NotImplemented, NOT_IMPL_STR);
}

void
PgSqlConfigBackendImpl::getAllOptionDefs(const int /* index */,
                                         const ServerSelector& server_selector,
                                         OptionDefContainer& /* option_defs */) {
    auto tags = server_selector.getTags();
    isc_throw(NotImplemented, NOT_IMPL_STR);
}

void
PgSqlConfigBackendImpl::getModifiedOptionDefs(const int /* index */,
                                              const ServerSelector& server_selector,
                                              const boost::posix_time::ptime& /* modification_time */,
                                              OptionDefContainer& /* option_defs */) {
    auto tags = server_selector.getTags();
    isc_throw(NotImplemented, NOT_IMPL_STR);
}

void
PgSqlConfigBackendImpl::getOptionDefs(const int /* index */,
                                      const PsqlBindArray& /* in_bindings */,
                                      OptionDefContainer& /* option_defs*/ ) {
    // Create output bindings. The order must match that in the prepared
    // statement.
    isc_throw(NotImplemented, NOT_IMPL_STR);
}

void
PgSqlConfigBackendImpl::createUpdateOptionDef(const db::ServerSelector& server_selector,
                                              const OptionDefinitionPtr& option_def,
                                              const std::string& /* space */,
                                              const int& /* get_option_def_code_space */,
                                              const int& /* insert_option_def */,
                                              const int& /* update_option_def */,
                                              const int& /* create_audit_revision */,
                                              const int& /* insert_option_def_server */) {

    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "managing configuration for no particular server"
                                  " (unassigned) is unsupported at the moment");
    }

    auto tag = getServerTag(server_selector, "creating or updating option definition");

    ElementPtr record_types = Element::createList();
    for (auto field : option_def->getRecordFields()) {
        record_types->add(Element::create(static_cast<int>(field)));
    }
    isc_throw(NotImplemented, NOT_IMPL_STR);
}

OptionDescriptorPtr
PgSqlConfigBackendImpl::getOption(const int /* index */,
                                  const Option::Universe& /* universe */,
                                  const ServerSelector& server_selector,
                                  const uint16_t /* code */,
                                  const std::string& /* space */) {

    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "managing configuration for no particular server"
                                  " (unassigned) is unsupported at the moment");
    }

    auto tag = getServerTag(server_selector, "fetching global option");

    OptionContainer options;
    isc_throw(NotImplemented, NOT_IMPL_STR);
    return (options.empty() ? OptionDescriptorPtr() :
            OptionDescriptor::create(*options.begin()));
}

OptionContainer
PgSqlConfigBackendImpl::getAllOptions(const int /* index */,
                                      const Option::Universe& /* universe */,
                                      const ServerSelector& server_selector) {
    OptionContainer options;
    auto tags = server_selector.getTags();

    isc_throw(NotImplemented, NOT_IMPL_STR);

    return (options);
}

OptionContainer
PgSqlConfigBackendImpl::getModifiedOptions(const int index,
                                           const Option::Universe& universe,
                                           const ServerSelector& server_selector,
                                           const boost::posix_time::ptime& /* modification_time */) {
    OptionContainer options;

    auto tags = server_selector.getTags();
    for (auto tag : tags) {
        PsqlBindArray in_bindings;

        /// need to define binding parameters
        isc_throw(NotImplemented, NOT_IMPL_STR);

        getOptions(index, in_bindings, universe, options);
    }

    return (options);
}

OptionDescriptorPtr
PgSqlConfigBackendImpl::getOption(const int index,
                                  const Option::Universe& universe,
                                  const ServerSelector& server_selector,
                                  const SubnetID& /* subnet_id */,
                                  const uint16_t /* code */,
                                  const std::string& /* space */) {

    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "managing configuration for no particular server"
                                  " (unassigned) is unsupported at the moment");
    }

    auto tag = getServerTag(server_selector, "fetching subnet level option");

    OptionContainer options;
    PsqlBindArray in_bindings;
    isc_throw(NotImplemented, NOT_IMPL_STR);

    getOptions(index, in_bindings, universe, options);
    return (options.empty() ? OptionDescriptorPtr() : OptionDescriptor::create(*options.begin()));
}

OptionDescriptorPtr
PgSqlConfigBackendImpl::getOption(const int index,
                                  const ServerSelector& server_selector,
                                  const Lease::Type& pool_type,
                                  const uint64_t /* pool_id */,
                                  const uint16_t /* code */,
                                  const std::string& /* space */) {

    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "managing configuration for no particular server"
                                  " (unassigned) is unsupported at the moment");
    }

    std::string msg = "fetching ";
    if (pool_type == Lease::TYPE_PD) {
        msg += "prefix delegation";
    } else {
        msg += "address";
    }
    msg += " pool level option";
    auto tag = getServerTag(server_selector, msg);

    Option::Universe universe = Option::V4;
    OptionContainer options;
    PsqlBindArray in_bindings;
    isc_throw(NotImplemented, NOT_IMPL_STR);

    getOptions(index, in_bindings, universe, options);
    return (options.empty() ? OptionDescriptorPtr() : OptionDescriptor::create(*options.begin()));
}

OptionDescriptorPtr
PgSqlConfigBackendImpl::getOption(const int index,
                                  const Option::Universe& universe,
                                  const ServerSelector& server_selector,
                                  const std::string& /* shared_network_name */,
                                  const uint16_t /* code */,
                                  const std::string& /* space */) {

    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "managing configuration for no particular server"
                                  " (unassigned) is unsupported at the moment");
    }

    auto tag = getServerTag(server_selector, "fetching shared network level option");

    OptionContainer options;
    PsqlBindArray in_bindings;
    isc_throw(NotImplemented, NOT_IMPL_STR);
    getOptions(index, in_bindings, universe, options);
    return (options.empty() ? OptionDescriptorPtr() : OptionDescriptor::create(*options.begin()));
}

void
PgSqlConfigBackendImpl::getOptions(const int /* index */,
                                   const db::PsqlBindArray& /* in_bindings */,
                                   const Option::Universe& /* universe */,
                                   OptionContainer& /* options */) {
    isc_throw(NotImplemented, NOT_IMPL_STR);
}

ServerPtr
PgSqlConfigBackendImpl::getServer(const int index, const ServerTag& server_tag) {
    ServerCollection servers;

    // Create input parameter bindings.
    PsqlBindArray in_bindings;
    in_bindings.addTempString(server_tag.get());

    getServers(index, in_bindings, servers);

    return (servers.empty() ? ServerPtr() : *servers.begin());
}

void
PgSqlConfigBackendImpl::getAllServers(const int index, db::ServerCollection& servers) {
    PsqlBindArray in_bindings;
    getServers(index, in_bindings, servers);
}

void
PgSqlConfigBackendImpl::getServers(const int index,
                                   const PsqlBindArray& in_bindings,
                                   ServerCollection& servers) {
    // Track the last server added to avoid duplicates. This
    // assumes the rows are ordered by server ID.
    ServerPtr last_server;
    selectQuery(index, in_bindings,
                [&servers, &last_server](PgSqlResult& r, int row) {
        // Extract the column values for r[row].
        // Create a worker for the row.
        PgSqlResultRowWorker worker(r, row);

        // Get the server ID.
        uint64_t id = worker.getBigInt(0);

        // Get the server tag.
        std::string tag = worker.getString(1);

        // Get the description.
        std::string description = worker.getString(2);

        // Get the modification time.
        boost::posix_time::ptime mod_time = worker.getTimestamp(3);

        if (!last_server || (last_server->getId() != id)) {
            // Create the server instance.
            last_server = Server::create(ServerTag(tag), description);

            // id
            last_server->setId(id);

            // modification_ts
            last_server->setModificationTime(mod_time);

            // New server fetched. Let's store it.
            servers.insert(last_server);
        }
    });
}

void
PgSqlConfigBackendImpl::createUpdateServer(const int& create_audit_revision,
                                           const int& create_index,
                                           const int& update_index,
                                           const ServerPtr& server) {
    // The server tag 'all' is reserved.
    if (server->getServerTag().amAll()) {
        isc_throw(InvalidOperation,
                  "'all' is a name reserved for the server tag which"
                  " associates the configuration elements with all servers connecting"
                  " to the database and a server with this name may not be created");
    }

    // Populate the input bindings.
    PsqlBindArray in_bindings;
    std::string tag = server->getServerTagAsText();
    in_bindings.add(tag);
    in_bindings.addTempString(server->getDescription());
    in_bindings.addTimestamp(server->getModificationTime());

    // Start a new transaction.
    PgSqlTransaction transaction(conn_);

    // Create scoped audit revision. As long as this instance exists
    // no new audit revisions are created in any subsequent calls.
    ScopedAuditRevision audit_revision(this, create_audit_revision, ServerSelector::ALL(),
                                       "server set", true);

    // Create a savepoint in case we are called as part of larger
    // transaction.
    conn_.createSavepoint("createUpdateServer");

    try {
        // Attempt to insert the server.
        insertQuery(create_index, in_bindings);
    } catch (const DuplicateEntry&) {
        // Rollback to the savepoint to preserve an outer
        // transaction work.
        conn_.rollbackToSavepoint("createUpdateServer");

        // Add another instance of tag to the bindings to be used
        // as the where clause parameter. PostgreSQL uses
        // numbered placeholders so we could use $1 again, but
        // doing it this way leaves the SQL more generic.
        in_bindings.add(tag);

        // Attempt to update the server.
        if (!updateDeleteQuery(update_index, in_bindings)) {
            // Possible only if someone deleted it since we tried to insert it,
            // the query is broken, or the bindings are nonsense.
            isc_throw(Unexpected, "Update server failed to find server tag: " << tag);
        }
    }

    // Commit the transaction.
    transaction.commit();
}

std::string
PgSqlConfigBackendImpl::getType() const {
    return ("postgresql");
}

std::string
PgSqlConfigBackendImpl::getHost() const {
    std::string host = "localhost";
    try {
        host = conn_.getParameter("host");
    } catch (...) {
        // No host parameter. Return localhost as a default.
    }
    return (host);
}

uint16_t
PgSqlConfigBackendImpl::getPort() const {
    try {
        std::string sport = conn_.getParameter("port");
        return (boost::lexical_cast<uint16_t>(sport));

    } catch (...) {
        // No port parameter or parameter invalid.
    }
    return (0);
}

void
PgSqlConfigBackendImpl::attachElementToServers(const int index,
                                               const ServerSelector& server_selector,
                                               const PsqlBindArray& in_bindings) {
    // Copy the bindings because we're going to modify them.
    PsqlBindArray server_bindings = in_bindings;
    for (auto tag : server_selector.getTags()) {
        // Add the server tag to end of the bindings.
        std::string server_tag = tag.get();
        server_bindings.add(server_tag);

        // Insert the server association.
        insertQuery(index, server_bindings);

        // Remove the prior server tag.
        server_bindings.popBack();
    }
}

void
PgSqlConfigBackendImpl::addRelayBinding(PsqlBindArray& bindings,
                                        const NetworkPtr& network) {
    ElementPtr relay_element = Element::createList();
    const auto& addresses = network->getRelayAddresses();
    if (!addresses.empty()) {
        for (const auto& address : addresses) {
            relay_element->add(Element::create(address.toText()));
        }
    }

    bindings.add(relay_element);
}

void
PgSqlConfigBackendImpl::addOptionValueBinding(PsqlBindArray& bindings,
                                              const OptionDescriptorPtr& option) {
    OptionPtr opt = option->option_;
    if (option->formatted_value_.empty() && (opt->len() > opt->getHeaderLen())) {
        OutputBuffer buf(opt->len());
        opt->pack(buf);
        const char* buf_ptr = static_cast<const char*>(buf.getData());
        std::vector<uint8_t> blob(buf_ptr + opt->getHeaderLen(),
                                  buf_ptr + buf.getLength());
        bindings.addTempBinary(blob);
    } else {
        bindings.addNull();
    }
}


}  // namespace dhcp
}  // end of namespace isc
