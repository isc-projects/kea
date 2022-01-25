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

            // Get the object type. Column 0 is the entry ID which
            // we don't need here.
            std::string object_type;
            PgSqlExchange::getColumnValue(r, row, 1, object_type);

            // Get the object ID.
            uint64_t object_id;
            PgSqlExchange::getColumnValue(r, row, 2, object_id);

            // Get the modification type.
            uint8_t mod_typ_int;
            PgSqlExchange::getColumnValue(r, row, 3, mod_typ_int);
            AuditEntry::ModificationType mod_type =
                static_cast<AuditEntry::ModificationType>(mod_typ_int);

            // Get the modification time.
            boost::posix_time::ptime mod_time;
            PgSqlExchange::getColumnValue(r, row, 4, mod_time);

            // Get the revision ID.
            uint64_t revision_id;
            PgSqlExchange::getColumnValue(r, row, 5, revision_id);

            // Get the revision log message.
            std::string log_message;
            PgSqlExchange::getColumnValue(r, row, 6, log_message);

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
PgSqlConfigBackendImpl::getGlobalParameters(const int /* index */,
                                            const PsqlBindArray& /* in_bindings */,
                                            StampedValueCollection& /* parameters */) {
    isc_throw(NotImplemented, NOT_IMPL_STR);
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

        // Get the server ID.
        uint64_t id;
        PgSqlExchange::getColumnValue(r, row, 0, id);

        // Get the server tag.
        std::string tag;
        PgSqlExchange::getColumnValue(r, row, 1, tag);

        // Get the description.
        std::string description;
        PgSqlExchange::getColumnValue(r, row, 2, description);

        // Get the modification time.
        boost::posix_time::ptime mod_time;
        PgSqlExchange::getColumnValue(r, row, 3, mod_time);

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
        bindings.add(blob);
    } else {
        bindings.addNull();
    }
}


}  // namespace dhcp
}  // end of namespace isc
