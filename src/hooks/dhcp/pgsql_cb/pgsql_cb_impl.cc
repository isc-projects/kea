// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <config_backend/constants.h>
#include <dhcp/option_space.h>
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
    std::pair<uint32_t, uint32_t> code_version(PG_SCHEMA_VERSION_MAJOR, PG_SCHEMA_VERSION_MINOR);
    std::pair<uint32_t, uint32_t> db_version = PgSqlConnection::getVersion(parameters);
    if (code_version != db_version) {
        isc_throw(DbOpenError, "Postgres schema version mismatch: need version: "
                                   << code_version.first << "." << code_version.second
                                   << " found version:  " << db_version.first << "."
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
PgSqlConfigBackendImpl::createAuditRevision(const int /* index */,
                                            const ServerSelector& server_selector,
                                            const boost::posix_time::ptime& /* audit_ts */,
                                            const std::string& /* log_message */,
                                            const bool /* cascade_transaction */) {
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

    isc_throw(NotImplemented, "todo");
}

void
PgSqlConfigBackendImpl::clearAuditRevision() {
    audit_revision_created_ = false;
}

void
PgSqlConfigBackendImpl::getRecentAuditEntries(const int /* index */,
                                              const db::ServerSelector& /* server_selector */,
                                              const boost::posix_time::ptime& /* modification_time */,
                                              const uint64_t& /* modification_id */,
                                              AuditEntryCollection& /* audit_entries */) {
    isc_throw(NotImplemented, "todo");
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
PgSqlConfigBackendImpl::deleteFromTable(const int /* index */,
                                        const db::ServerSelector& /* server_selector */,
                                        const std::string& /* operation */,
                                        db::PsqlBindArray& /* bindings */) {
    isc_throw(NotImplemented, "todo");
}

void
PgSqlConfigBackendImpl::getGlobalParameters(const int /* index */,
                                            const PsqlBindArray& /* in_bindings */,
                                            StampedValueCollection& /* parameters */) {

    isc_throw(NotImplemented, "todo");
}

OptionDefinitionPtr
PgSqlConfigBackendImpl::getOptionDef(const int /* index */,
                                     const ServerSelector& server_selector,
                                     const uint16_t /* code */,
                                     const std::string& /* space */) {

    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "managing configuration for no particular server"
                                  " (unassigned) is unsupported at the moment");
    }

    auto tag = getServerTag(server_selector, "fetching option definition");

    OptionDefContainer option_defs;
    isc_throw(NotImplemented, "todo");
    return (option_defs.empty() ? OptionDefinitionPtr() : *option_defs.begin());
}

void
PgSqlConfigBackendImpl::getAllOptionDefs(const int /* index */,
                                         const ServerSelector& server_selector,
                                         OptionDefContainer& /* option_defs */) {
    auto tags = server_selector.getTags();
    isc_throw(NotImplemented, "todo");
}

void
PgSqlConfigBackendImpl::getModifiedOptionDefs(const int /* index */,
                                              const ServerSelector& server_selector,
                                              const boost::posix_time::ptime& /* modification_time */,
                                              OptionDefContainer& /* option_defs */) {
    auto tags = server_selector.getTags();
    isc_throw(NotImplemented, "todo");
}

void
PgSqlConfigBackendImpl::getOptionDefs(const int /* index */,
                                      const PsqlBindArray& /* in_bindings */,
                                      OptionDefContainer& /* option_defs*/ ) {
    // Create output bindings. The order must match that in the prepared
    // statement.
    isc_throw(NotImplemented, "todo");
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
    isc_throw(NotImplemented, "todo");
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
    isc_throw(NotImplemented, "todo");
    return (options.empty() ? OptionDescriptorPtr() :
            OptionDescriptor::create(*options.begin()));
}

OptionContainer
PgSqlConfigBackendImpl::getAllOptions(const int /* index */,
                                      const Option::Universe& /* universe */,
                                      const ServerSelector& server_selector) {
    OptionContainer options;
    auto tags = server_selector.getTags();

    isc_throw(NotImplemented, "todo");

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
        isc_throw(NotImplemented, "todo");

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
    isc_throw(NotImplemented, "todo");

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
    isc_throw(NotImplemented, "todo");

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
    isc_throw(NotImplemented, "todo");
    getOptions(index, in_bindings, universe, options);
    return (options.empty() ? OptionDescriptorPtr() : OptionDescriptor::create(*options.begin()));
}

void
PgSqlConfigBackendImpl::getOptions(const int /* index */,
                                   const db::PsqlBindArray& /* in_bindings */,
                                   const Option::Universe& /* universe */,
                                   OptionContainer& /* options */) {
    isc_throw(NotImplemented, "todo");
}

PsqlBindArrayPtr
PgSqlConfigBackendImpl::createInputRelayBinding(const NetworkPtr& network) {
    ElementPtr relay_element = Element::createList();
    const auto& addresses = network->getRelayAddresses();
    if (!addresses.empty()) {
        for (const auto& address : addresses) {
            relay_element->add(Element::create(address.toText()));
        }
    }
    isc_throw(NotImplemented, "todo");
}

PsqlBindArrayPtr
PgSqlConfigBackendImpl::createOptionValueBinding(const OptionDescriptorPtr& option) {

    PsqlBindArrayPtr p(new PsqlBindArray());
    OptionPtr opt = option->option_;
    if (option->formatted_value_.empty() && (opt->len() > opt->getHeaderLen())) {
        OutputBuffer buf(opt->len());
        opt->pack(buf);
        const char* buf_ptr = static_cast<const char*>(buf.getData());
        std::vector<uint8_t> blob(buf_ptr + opt->getHeaderLen(), buf_ptr + buf.getLength());

        // return (PsqlBindArray::createBlob(blob.begin(), blob.end()));
    }

    // return (PsqlBindArray::createNull());
    return (p);
}

ServerPtr
PgSqlConfigBackendImpl::getServer(const int index, const ServerTag& /* server_tag */) {
    ServerCollection servers;
    PsqlBindArray in_bindings; /* = {
        PsqlBindArray::createString(server_tag.get())
    }; */
    isc_throw(NotImplemented, "todo");

    getServers(index, in_bindings, servers);

    return (servers.empty() ? ServerPtr() : *servers.begin());
}

void
PgSqlConfigBackendImpl::getAllServers(const int index, db::ServerCollection& servers) {
    PsqlBindArray in_bindings;
    getServers(index, in_bindings, servers);
}

void
PgSqlConfigBackendImpl::getServers(const int /* index */,
                                   const PsqlBindArray& /* in_bindings */,
                                   ServerCollection& /* servers */) {
    isc_throw(NotImplemented, "todo");
}

void
PgSqlConfigBackendImpl::createUpdateServer(const int& create_audit_revision,
                                           const int& /* create_index */,
                                           const int& /* update_index */,
                                           const ServerPtr& server) {
    // The server tag 'all' is reserved.
    if (server->getServerTag().amAll()) {
        isc_throw(InvalidOperation,
                  "'all' is a name reserved for the server tag which"
                  " associates the configuration elements with all servers connecting"
                  " to the database and a server with this name may not be created");
    }

    // Create scoped audit revision. As long as this instance exists
    // no new audit revisions are created in any subsequent calls.
    ScopedAuditRevision audit_revision(this, create_audit_revision, ServerSelector::ALL(),
                                       "server set", true);

    PgSqlTransaction transaction(conn_);

    PsqlBindArray in_bindings;
    isc_throw(NotImplemented, "todo");

     /* = {
        PsqlBindArray::createString(server->getServerTagAsText()),
        PsqlBindArray::createString(server->getDescription()),
        PsqlBindArray::createTimestamp(server->getModificationTime())
    };

    try {
        conn_.insertQuery(create_index, in_bindings);

    } catch (const DuplicateEntry&) {
        in_bindings.push_back(PsqlBindArray::createString(server->getServerTagAsText()));
        conn_.updateDeleteQuery(update_index, in_bindings);
    }*/

    transaction.commit();
}

std::string
PgSqlConfigBackendImpl::getType() const {
    return ("pgsql");
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

}  // namespace dhcp
}  // end of namespace isc
