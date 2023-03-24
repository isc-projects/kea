// Copyright (C) 2021-2023 Internet Systems Consortium, Inc. ("ISC")
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
                               boost::posix_time::microsec_clock::local_time(),
                               log_message,
                               cascade_transaction);
}

PgSqlConfigBackendImpl::ScopedAuditRevision::~ScopedAuditRevision() {
    impl_->clearAuditRevision();
}

PgSqlConfigBackendImpl::PgSqlConfigBackendImpl(const DatabaseConnection::ParameterMap& parameters,
                                               const DbCallback db_reconnect_callback,
                                               size_t last_insert_id_index)
    : conn_(parameters,
            IOServiceAccessorPtr(new IOServiceAccessor(PgSqlConfigBackendImpl::getIOService)),
            db_reconnect_callback), timer_name_(""),
            audit_revision_ref_count_(0), parameters_(parameters),
            last_insert_id_index_(last_insert_id_index) {

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
        isc_throw(DbOpenError, "PostgreSQL schema version mismatch: need version: "
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
    if (++audit_revision_ref_count_ > 1) {
        return;
    }

    /// @todo The audit trail is not really well prepared to handle multiple server
    /// tags or no server tags. Therefore, if the server selector appears to be
    /// pointing to multiple servers, no servers or any server we simply associate the
    /// audit revision with all servers. The only case when we create a dedicated
    /// audit entry is when there is a single server tag, i.e. "all" or explicit
    /// server name. In fact, these are the most common two cases.
    std::string tag = ServerTag::ALL;
    auto const& tags = server_selector.getTags();
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
    if (audit_revision_ref_count_ <= 0) {
        isc_throw(Unexpected, "attempted to clear audit revision that does not exist - coding error");
    }
    --audit_revision_ref_count_;
}

void
PgSqlConfigBackendImpl::getRecentAuditEntries(const int index,
                                              const db::ServerSelector& server_selector,
                                              const boost::posix_time::ptime& modification_time,
                                              const uint64_t& modification_id,
                                              AuditEntryCollection& audit_entries) {
    auto const& tags = server_selector.getTags();
    for (auto const& tag : tags) {
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
PgSqlConfigBackendImpl::getLastInsertId(const std::string& table, const std::string& column) {
    PsqlBindArray in_bindings;
    in_bindings.add(table);
    in_bindings.add(column);
    uint64_t last_id = 0;
    conn_.selectQuery(getStatement(last_insert_id_index_), in_bindings,
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
PgSqlConfigBackendImpl::getOptionDef(const int index,
                                     const ServerSelector& server_selector,
                                     const uint16_t code,
                                     const std::string& space) {

    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "managing configuration for no particular server"
                  " (unassigned) is unsupported at the moment");
    }

    auto tag = getServerTag(server_selector, "fetching option definition");

    OptionDefContainer option_defs;
    PsqlBindArray in_bindings;
    in_bindings.add(tag);
    in_bindings.add(code);
    in_bindings.add(space);

    getOptionDefs(index, in_bindings, option_defs);
    return (option_defs.empty() ? OptionDefinitionPtr() : *option_defs.begin());
}

void
PgSqlConfigBackendImpl::getAllOptionDefs(const int index,
                                         const ServerSelector& server_selector,
                                         OptionDefContainer& option_defs) {
    auto const& tags = server_selector.getTags();
    for (auto const& tag : tags) {
        PsqlBindArray in_bindings;
        in_bindings.addTempString(tag.get());
        getOptionDefs(index, in_bindings, option_defs);
    }
}

void
PgSqlConfigBackendImpl::getModifiedOptionDefs(const int index,
                                              const ServerSelector& server_selector,
                                              const boost::posix_time::ptime& modification_time,
                                              OptionDefContainer& option_defs) {
    auto const& tags = server_selector.getTags();
    for (auto const& tag : tags) {
        PsqlBindArray in_bindings;
        in_bindings.addTempString(tag.get());
        in_bindings.addTimestamp(modification_time);
        getOptionDefs(index, in_bindings, option_defs);
    }
}

void
PgSqlConfigBackendImpl::getOptionDefs(const int index,
                                      const PsqlBindArray& in_bindings,
                                      OptionDefContainer& option_defs) {
    uint64_t last_def_id = 0;

    OptionDefContainer local_option_defs;

    // Run select query.
    selectQuery(index, in_bindings, [this, &local_option_defs, &last_def_id]
                (PgSqlResult& r, int row) {
        // Extract the column values for r[row].
        // Create a worker for the row.
        PgSqlResultRowWorker worker(r, row);

        // Get pointer to last fetched option definition.
        OptionDefinitionPtr last_def;
        if (!local_option_defs.empty()) {
            last_def = *local_option_defs.rbegin();
        }

        // Get option def ID.
        uint64_t id = worker.getBigInt(0);

        // See if the last fetched definition is the one for which we now got
        // the row of data. If not, it means that we need to create new option
        // definition.
        if ((last_def_id == 0) || (last_def_id != id)) {
            last_def_id = id;
            last_def = processOptionDefRow(worker, 0);

            // server_tag
            ServerTag last_def_server_tag(worker.getString(10));
            last_def->setServerTag(last_def_server_tag.get());

            // If we're fetching option definitions for a given server
            // (explicit server tag is provided), it takes precedence over
            // the same option definition specified for all servers.
            // Therefore, we check if the given option already exists and
            // belongs to 'all'.
            auto& index = local_option_defs.get<1>();
            auto existing_it_pair = index.equal_range(last_def->getCode());
            auto existing_it = existing_it_pair.first;
            bool found = false;
            for ( ; existing_it != existing_it_pair.second; ++existing_it) {
                if ((*existing_it)->getOptionSpaceName() == last_def->getOptionSpaceName()) {
                    found = true;
                    // This option definition was already fetched. Let's check
                    // if we should replace it or not.
                    if (!last_def_server_tag.amAll() && (*existing_it)->hasAllServerTag()) {
                        index.replace(existing_it, last_def);
                        return;
                    }
                    break;
                }
            }

            // If there is no such option definition yet or the existing option
            // definition belongs to a different server and the inserted option
            // definition is not for all servers.
            if (!found ||
                (!(*existing_it)->hasServerTag(last_def_server_tag) &&
                 !last_def_server_tag.amAll())) {
                static_cast<void>(local_option_defs.push_back(last_def));
            }
        }
    });

    // Append the option definition fetched by this function into the container
    // supplied by the caller. The container supplied by the caller may already
    // hold some option definitions fetched for other server tags.
    option_defs.insert(option_defs.end(), local_option_defs.begin(),
                       local_option_defs.end());
}

void
PgSqlConfigBackendImpl::createUpdateOptionDef(const db::ServerSelector& server_selector,
                                              const Option::Universe& universe,
                                              const OptionDefinitionPtr& option_def,
                                              const std::string& /* space */,
                                              const int& /*get_option_def_code_space*/,
                                              const int& insert_option_def,
                                              const int& update_option_def,
                                              const int& create_audit_revision,
                                              const int& insert_option_def_server,
                                              const std::string& client_class_name) {

    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "managing configuration for no particular server"
                                  " (unassigned) is unsupported at the moment");
    }

    auto tag = getServerTag(server_selector, "creating or updating option definition");

    // Create input parameter bindings.
    PsqlBindArray in_bindings;
    in_bindings.add(option_def->getCode());
    in_bindings.addTempString(option_def->getName());
    in_bindings.addTempString(option_def->getOptionSpaceName());
    in_bindings.add(option_def->getType());
    in_bindings.addTimestamp(option_def->getModificationTime());
    in_bindings.add(option_def->getArrayType());
    in_bindings.addTempString(option_def->getEncapsulatedSpace());

    ElementPtr record_types = Element::createList();
    for (auto field : option_def->getRecordFields()) {
        record_types->add(Element::create(static_cast<int>(field)));
    }

    if (record_types->empty()) {
        in_bindings.addNull();
    } else {
        in_bindings.addTempString(record_types->str());
    }

    in_bindings.add(option_def->getContext());

    if (client_class_name.empty()) {
        in_bindings.addNull();
    } else {
        in_bindings.add(client_class_name);
    }

    // Remember the size before we added where clause arguments.
    size_t pre_where_size = in_bindings.size();

    // Now the add the update where clause parameters
    in_bindings.add(tag);
    in_bindings.add(option_def->getCode());
    in_bindings.addTempString(option_def->getOptionSpaceName());

    // Start transaction.
    PgSqlTransaction transaction(conn_);

    // Create scoped audit revision. As long as this instance exists
    // no new audit revisions are created in any subsequent calls.
    ScopedAuditRevision audit_revision(this,
                                       create_audit_revision,
                                       server_selector,
                                       "option definition set",
                                       true);

    // Try to update the definition.
    if (updateDeleteQuery(update_option_def, in_bindings) == 0) {
        // It doesn't exist, so we'll try to insert it.
        // Remove the update where clause bindings.
        while (in_bindings.size() > pre_where_size) {
            in_bindings.popBack();
        }

        // Try to insert the definition.
        insertQuery(insert_option_def, in_bindings);

        // Successfully inserted the definition. Now, we have to associate it
        // with the server tag.
        PsqlBindArray attach_bindings;
        uint64_t id = getLastInsertId((universe == Option::V4 ?
                                       "dhcp4_option_def" : "dhcp6_option_def"), "id");
        attach_bindings.add(id);
        attach_bindings.addTimestamp(option_def->getModificationTime());

        // Insert associations of the option definition with servers.
        attachElementToServers(insert_option_def_server, server_selector, attach_bindings);
    }

    // Commit the work.
    transaction.commit();
}

OptionDescriptorPtr
PgSqlConfigBackendImpl::getOption(const int index,
                                  const Option::Universe& universe,
                                  const ServerSelector& server_selector,
                                  const uint16_t code,
                                  const std::string& space) {

    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "managing configuration for no particular server"
                                  " (unassigned) is unsupported at the moment");
    }

    auto tag = getServerTag(server_selector, "fetching global option");

    OptionContainer options;
    PsqlBindArray in_bindings;
    in_bindings.add(tag);
    in_bindings.add(code);
    in_bindings.add(space);

    getOptions(index, in_bindings, universe, options);
    return (options.empty() ? OptionDescriptorPtr() :
            OptionDescriptor::create(*options.begin()));
}

OptionContainer
PgSqlConfigBackendImpl::getAllOptions(const int index,
                                      const Option::Universe& universe,
                                      const ServerSelector& server_selector) {
    OptionContainer options;

    auto const& tags = server_selector.getTags();
    for (auto const& tag : tags) {
        PsqlBindArray in_bindings;
        in_bindings.addTempString(tag.get());
        getOptions(index, in_bindings, universe, options);
    }

    return (options);
}

OptionContainer
PgSqlConfigBackendImpl::getModifiedOptions(const int index,
                                           const Option::Universe& universe,
                                           const ServerSelector& server_selector,
                                           const boost::posix_time::ptime& modification_time) {
    OptionContainer options;

    PsqlBindArray in_bindings;
    auto const& tags = server_selector.getTags();
    for (auto const& tag : tags) {
        in_bindings.addTempString(tag.get());
        in_bindings.addTimestamp(modification_time);
        getOptions(index, in_bindings, universe, options);
    }

    return (options);
}

OptionDescriptorPtr
PgSqlConfigBackendImpl::getOption(const int index,
                                  const Option::Universe& universe,
                                  const ServerSelector& server_selector,
                                  const SubnetID& subnet_id,
                                  const uint16_t code,
                                  const std::string& space) {

    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "managing configuration for no particular server"
                                  " (unassigned) is unsupported at the moment");
    }

    auto tag = getServerTag(server_selector, "fetching subnet level option");

    PsqlBindArray in_bindings;
    in_bindings.add(tag);
    in_bindings.add(subnet_id);
    in_bindings.add(code);   // Postgresql code is same size regardless of universe
    in_bindings.add(space);

    OptionContainer options;
    getOptions(index, in_bindings, universe, options);
    return (options.empty() ? OptionDescriptorPtr() :
            OptionDescriptor::create(*options.begin()));
}

OptionDescriptorPtr
PgSqlConfigBackendImpl::getOption(const int index,
                                  const ServerSelector& server_selector,
                                  const Lease::Type& pool_type,
                                  const uint64_t pool_id,
                                  const uint16_t code,
                                  const std::string& space) {

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

    PsqlBindArray in_bindings;
    in_bindings.add(tag);
    in_bindings.add(pool_id);
    in_bindings.add(code);   // Postgresql code is same size regardless of universe
    in_bindings.add(space);
    Option::Universe universe = Option::V4;
    OptionContainer options;
    if (pool_type != Lease::TYPE_V4) {
        universe = Option::V6;
    }
    getOptions(index, in_bindings, universe, options);
    return (options.empty() ? OptionDescriptorPtr() :
            OptionDescriptor::create(*options.begin()));
}

OptionDescriptorPtr
PgSqlConfigBackendImpl::getOption(const int index,
                                  const Option::Universe& universe,
                                  const ServerSelector& server_selector,
                                  const std::string& shared_network_name,
                                  const uint16_t code,
                                  const std::string& space) {

    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "managing configuration for no particular server"
                                  " (unassigned) is unsupported at the moment");
    }

    auto tag = getServerTag(server_selector, "fetching shared network level option");

    PsqlBindArray in_bindings;
    in_bindings.add(tag);
    in_bindings.add(shared_network_name);
    in_bindings.add(code);   // Postgresql code is same size regardless of universe
    in_bindings.add(space);

    OptionContainer options;
    getOptions(index, in_bindings, universe, options);
    return (options.empty() ? OptionDescriptorPtr() :
            OptionDescriptor::create(*options.begin()));
}

void
PgSqlConfigBackendImpl::getOptions(const int index,
                                   const db::PsqlBindArray& in_bindings,
                                   const Option::Universe& universe,
                                   OptionContainer& options) {
    uint64_t last_option_id = 0;
    OptionContainer local_options;
    selectQuery(index, in_bindings, [this, universe, &local_options, &last_option_id]
                (PgSqlResult& r, int row) {
        // Extract the column values for r[row].
        // Create a worker for the row.
        PgSqlResultRowWorker worker(r, row);

        // Get option ID.
        uint64_t id = worker.getBigInt(0);

        // Parse option.
        if ((last_option_id == 0) || (last_option_id < id)) {
            last_option_id = id;

            OptionDescriptorPtr desc = processOptionRow(universe, worker, 0);
            if (desc) {
                // server_tag for the global option
                ServerTag last_option_server_tag(worker.getString(13));
                desc->setServerTag(last_option_server_tag.get());

                // If we're fetching options for a given server (explicit server
                // tag is provided), it takes precedence over the same option
                // specified for all servers. Therefore, we check if the given
                // option already exists and belongs to 'all'.
                auto& index = local_options.get<1>();
                auto existing_it_pair = index.equal_range(desc->option_->getType());
                auto existing_it = existing_it_pair.first;
                bool found = false;
                for ( ; existing_it != existing_it_pair.second; ++existing_it) {
                    if (existing_it->space_name_ == desc->space_name_) {
                        found = true;
                        // This option was already fetched. Let's check if we should
                        // replace it or not.
                        if (!last_option_server_tag.amAll() && existing_it->hasAllServerTag()) {
                            index.replace(existing_it, *desc);
                            return;
                        }
                        break;
                    }
                }

                // If there is no such global option yet or the existing option
                // belongs to a different server and the inserted option is not
                // for all servers.
                if (!found ||
                    (!existing_it->hasServerTag(last_option_server_tag) &&
                     !last_option_server_tag.amAll())) {
                    static_cast<void>(local_options.push_back(*desc));
                }
            }
        }
    });

    // Append the options fetched by this function into the container supplied
    // by the caller. The container supplied by the caller may already hold
    // some options fetched for other server tags.
    options.insert(options.end(), local_options.begin(), local_options.end());
}

OptionDescriptorPtr
PgSqlConfigBackendImpl::processOptionRow(const Option::Universe& universe,
                                         PgSqlResultRowWorker& worker,
                                         size_t first_col) {
    // Some of the options have standard or custom definitions.
    // Depending whether the option has a definition or not a different
    // C++ class may be used to represent the option. Therefore, the
    // first thing to do is to see if there is a definition for our
    // parsed option. The option code and space is needed for it.
    std::string space = worker.getString(first_col + 4);
    uint16_t code = worker.getSmallInt(first_col + 1);

    OptionPtr option = Option::create(universe, code);

    // Get formatted value if available.
    std::string formatted_value;
    if (!worker.isColumnNull(first_col + 3)) {
        formatted_value = worker.getString(first_col + 3);
    }

    // If we don't have a formatted value, check for a blob. Add it to the
    // option if it exists.
    if (formatted_value.empty() && !worker.isColumnNull(first_col + 2)) {
        std::vector<uint8_t> blob;
        worker.getBytes(first_col + 2, blob);
        option->setData(blob.begin(), blob.end());
    }

    // Check if the option is persistent.
    bool persistent = false;
    if (!worker.isColumnNull(first_col + 5)) {
        persistent = worker.getBool(first_col + 5);
    }

    // Check if the option is cancelled.
    bool cancelled = false;
    if (!worker.isColumnNull(first_col + 6)) {
        cancelled = worker.getBool(first_col + 6);
    }

    // Create option descriptor which encapsulates our option and adds
    // additional information, i.e. whether the option is persistent,
    // its option space and timestamp.
    OptionDescriptorPtr desc = OptionDescriptor::create(option,
                                                        persistent,
                                                        cancelled,
                                                        formatted_value);
    desc->space_name_ = space;
    desc->setModificationTime(worker.getTimestamp(first_col + 12));

    // Set database id for the option.
    // @todo Can this actually ever be null and if it is, isn't that an error?
    if (!worker.isColumnNull(first_col)) {
        desc->setId(worker.getBigInt(first_col));
    }

    return (desc);
}

OptionDefinitionPtr
PgSqlConfigBackendImpl::processOptionDefRow(PgSqlResultRowWorker& worker,
                                            const size_t first_col) {
    OptionDefinitionPtr def;

    // Check array type, because depending on this value we have to use
    // different constructor.
    std::string name = worker.getString(first_col + 2);
    uint16_t code = worker.getSmallInt(first_col + 1);
    std::string space = worker.getString(first_col + 3);
    OptionDataType type = static_cast<OptionDataType>(worker.getSmallInt(first_col + 4));

    bool array_type = worker.getBool(first_col + 6);
    if (array_type) {
        // Create array option.
        def = OptionDefinition::create(name, code, space, type, true);
    } else {
        // Create non-array option.
        def = OptionDefinition::create(name, code, space, type,
                                       (worker.isColumnNull(first_col + 7) ? ""
                                        : worker.getString(first_col + 7).c_str()));
    }

    // id
    def->setId(worker.getBigInt(first_col));

    // record_types
    if (!worker.isColumnNull(first_col + 8)) {
        ElementPtr record_types_element = worker.getJSON(first_col + 8);
        if (record_types_element->getType() != Element::list) {
            isc_throw(BadValue, "invalid record_types value "
                      << worker.getString(first_col + 8));
        }

        // This element must contain a list of integers specifying
        // types of the record fields.
        for (auto i = 0; i < record_types_element->size(); ++i) {
            auto type_element = record_types_element->get(i);
            if (type_element->getType() != Element::integer) {
                isc_throw(BadValue, "record type values must be integers");
            }

            def->addRecordField(static_cast<OptionDataType>(type_element->intValue()));
        }
    }

    // Update modification time.
    def->setModificationTime(worker.getTimestamp(first_col + 5));

    return (def);
}

void
PgSqlConfigBackendImpl::attachElementToServers(const int index,
                                               const ServerSelector& server_selector,
                                               const PsqlBindArray& in_bindings) {
    // Copy the bindings because we're going to modify them.
    PsqlBindArray server_bindings = in_bindings;
    for (auto const& tag : server_selector.getTags()) {
        // Add the server tag to end of the bindings.
        std::string server_tag = tag.get();
        server_bindings.add(server_tag);

        // Insert the server association.
        // Handles the case where the server does not exists.
        try {
            insertQuery(index, server_bindings);
        } catch (const NullKeyError&) {
            // The message should give the tag value.
            isc_throw(NullKeyError,
                      "server '" << tag.get() << "' does not exist");
        }
        // Remove the prior server tag.
        server_bindings.popBack();
    }
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

    // Start transaction.
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
PgSqlConfigBackendImpl::addDdnsReplaceClientNameBinding(PsqlBindArray& bindings,
                                                        const NetworkPtr& network) {
    auto ddns_rcn_mode = network->getDdnsReplaceClientNameMode(Network::Inheritance::NONE);
    if (!ddns_rcn_mode.unspecified()) {
        bindings.add(static_cast<uint8_t>(ddns_rcn_mode.get()));
    } else {
        bindings.addNull();
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
PgSqlConfigBackendImpl::setRelays(PgSqlResultRowWorker& worker, size_t col, Network& network) {
    if (worker.isColumnNull(col)) {
        return;
    }

    ElementPtr relay_element = worker.getJSON(col);
    if (relay_element->getType() != Element::list) {
        isc_throw(BadValue, "invalid relay list: " << worker.getString(col));
    }

    for (auto i = 0; i < relay_element->size(); ++i) {
        auto relay_address_element = relay_element->get(i);
        if (relay_address_element->getType() != Element::string) {
            isc_throw(BadValue, "elements of relay_addresses list must"
                                "be valid strings");
        }

        network.addRelayAddress(IOAddress(relay_address_element->stringValue()));
    }
}

void
PgSqlConfigBackendImpl::setRequiredClasses(PgSqlResultRowWorker& worker, size_t col,
                                           std::function<void(const std::string&)> setter) {
    if (worker.isColumnNull(col)) {
        return;
    }

    ElementPtr require_element = worker.getJSON(col);
    if (require_element->getType() != Element::list) {
        std::ostringstream ss;
        require_element->toJSON(ss);
        isc_throw(BadValue, "invalid require_client_classes value " << ss.str());
    }

    for (auto i = 0; i < require_element->size(); ++i) {
        auto require_item = require_element->get(i);
        if (require_item->getType() != Element::string) {
            isc_throw(BadValue, "elements of require_client_classes list must"
                                "be valid strings");
        }

        setter(require_item->stringValue());
    }
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

} // end of namespace isc::dhcp
} // end of namespace isc
