// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include "pgsql_cb_impl.h"
#include <asiolink/io_address.h>
#include <config_backend/constants.h>
#include <pgsql/pgsql_exchange.h>
#include <dhcp/option_space.h>
#include <util/buffer.h>
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

PgSqlConfigBackendImpl::
ScopedAuditRevision::ScopedAuditRevision(PgSqlConfigBackendImpl* impl,
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

PgSqlConfigBackendImpl::
ScopedAuditRevision::~ScopedAuditRevision() {
    impl_->clearAuditRevision();
}

PgSqlConfigBackendImpl::
PgSqlConfigBackendImpl(const DatabaseConnection::ParameterMap& parameters,
                       const DbCallback db_reconnect_callback)
    : conn_(parameters,
            IOServiceAccessorPtr(new IOServiceAccessor(PgSqlConfigBackendImpl::getIOService)),
            db_reconnect_callback), timer_name_(""),
      audit_revision_created_(false), parameters_(parameters) {
    // Test schema version first.
    std::pair<uint32_t, uint32_t> code_version(PG_SCHEMA_VERSION_MAJOR,
                                               PG_SCHEMA_VERSION_MINOR);
    std::pair<uint32_t, uint32_t> db_version =
        PgSqlConnection::getVersion(parameters);
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

#if 0
PsqlBindArrayPtr
PgSqlConfigBackendImpl::createBinding(const Triplet<uint32_t>& triplet) {
    PsqlBindArrayPtr bind(new PsqlBindArray());

    if (triplet.unspecified()) {
        bind->addNull();
    } else {
        bind->add<uint32_t>(triplet.get());
    }
    return (bind);
}

PsqlBindArrayPtr
PgSqlConfigBackendImpl::createMinBinding(const Triplet<uint32_t>& triplet) {
    PsqlBindArrayPtr bind(new PsqlBindArray());
    if (triplet.unspecified() || (triplet.getMin() == triplet.get())) {
        bind->addNull();
    } else {
        bind->add<uint32_t>(triplet.getMin());
    }
    return (bind);
}

PsqlBindArrayPtr
PgSqlConfigBackendImpl::createMaxBinding(const Triplet<uint32_t>& triplet) {
    PsqlBindArrayPtr bind(new PsqlBindArray());
    if (triplet.unspecified() || (triplet.getMax() == triplet.get())) {
        bind->addNull();
    } else {
        bind->add<uint32_t>(triplet.getMax());
    }
    return (bind);
}
#endif

/* Triplet<uint32_t>
PgSqlConfigBackendImpl::createTriplet(const PsqlBindArrayPtr& binding) {
    if (!binding) {
        isc_throw(Unexpected, "Postgres configuration backend internal error: "
                  "binding pointer is NULL when creating a triplet value");
    }

    if (binding->empty()) {
        return (Triplet<uint32_t>());
    }

    return (Triplet<uint32_t>(binding->getInteger<uint32_t>()));
} */

/* Triplet<uint32_t>
PgSqlConfigBackendImpl::createTriplet(const PsqlBindArrayPtr& def_binding,
                                      const PsqlBindArrayPtr& min_binding,
                                      const PsqlBindArrayPtr& max_binding) {
    if (!def_binding || !min_binding || !max_binding) {
        isc_throw(Unexpected, "Postgres configuration backend internal error: "
                  "binding pointer is NULL when creating a triplet value");
    }

    // This code assumes the database was filled using the API, e.g. it
    // is not possible (so not handled) to have only the min_binding not NULL.
    if (def_binding->empty()) {
        return (Triplet<uint32_t>());
    }

    uint32_t value = def_binding->getInteger<uint32_t>();
    uint32_t min_value = value;
    if (!min_binding->empty()) {
        min_value = min_binding->getInteger<uint32_t>();
    }
    uint32_t max_value = value;
    if (!max_binding->empty()) {
        max_value = max_binding->getInteger<uint32_t>();
    }

    return (Triplet<uint32_t>(min_value, value, max_value));
} */

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

#if 0
    PsqlBindArray in_bindings = {
        PsqlBindArray::createTimestamp(audit_ts),
        PsqlBindArray::createString(tag),
        PsqlBindArray::createString(log_message),
        PsqlBindArray::createInteger<uint8_t>(static_cast<uint8_t>(cascade_transaction))
    };
    conn_.insertQuery(index, in_bindings);
    audit_revision_created_ = true;
#endif
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
    isc_throw(NotImplemented, "");
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

void
PgSqlConfigBackendImpl::getGlobalParameters(const int index,
                                            const PsqlBindArray& in_bindings,
                                            StampedValueCollection& parameters) {
#if 0
    // The following parameters from the dhcp[46]_global_parameter table are
    // returned:
    // - id
    // - name - parameter name
    // - value - parameter value
    // - modification_ts - modification timestamp.
    PsqlBindArray out_bindings = {
        PsqlBindArray::createInteger<uint64_t>(), // id
        PsqlBindArray::createString(GLOBAL_PARAMETER_NAME_BUF_LENGTH), // name
        PsqlBindArray::createString(GLOBAL_PARAMETER_VALUE_BUF_LENGTH), // value
        PsqlBindArray::createInteger<uint8_t>(), // parameter_type
        PsqlBindArray::createTimestamp(), // modification_ts
        PsqlBindArray::createString(SERVER_TAG_BUF_LENGTH) // server_tag
    };

    StampedValuePtr last_param;

    StampedValueCollection local_parameters;

    conn_.selectQuery(index, in_bindings, out_bindings,
                      [&last_param, &local_parameters]
                      (PsqlBindArray& out_bindings) {

        uint64_t id = out_bindings[0]->getInteger<uint64_t>();

        // If we're starting or if this is new parameter being processed...
        if (!last_param || (last_param->getId() != id)) {

            // parameter name
            std::string name = out_bindings[1]->getString();

            if (!name.empty()) {
                last_param = StampedValue::create(name,
                                                  out_bindings[2]->getString(),
                                                  static_cast<Element::types>
                                                  (out_bindings[3]->getInteger<uint8_t>()));

                // id
                last_param->setId(id);

                // modification_ts
                last_param->setModificationTime(out_bindings[4]->getTimestamp());

                // server_tag
                ServerTag last_param_server_tag(out_bindings[5]->getString());
                last_param->setServerTag(last_param_server_tag.get());
                // If we're fetching parameters for a given server (explicit server
                // tag is provided), it takes precedence over the same parameter
                // specified for all servers. Therefore, we check if the given
                // parameter already exists and belongs to 'all'.
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
#endif
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
#if 0
    PsqlBindArray in_bindings = {
        PsqlBindArray::createString(tag),
        PsqlBindArray::createInteger<uint16_t>(code),
        PsqlBindArray::createString(space)
    };
    getOptionDefs(index, in_bindings, option_defs);
#endif
    return (option_defs.empty() ? OptionDefinitionPtr() : *option_defs.begin());
}

void
PgSqlConfigBackendImpl::getAllOptionDefs(const int index,
                     const ServerSelector& server_selector,
                     OptionDefContainer& option_defs) {
    auto tags = server_selector.getTags();
#if 0
    for (auto tag : tags) {
        PsqlBindArray in_bindings = {
            PsqlBindArray::createString(tag.get())
        };
        getOptionDefs(index, in_bindings, option_defs);
    }
#endif
}

void
PgSqlConfigBackendImpl::getModifiedOptionDefs(const int index,
                                              const ServerSelector& server_selector,
                                              const boost::posix_time::ptime& modification_time,
                                              OptionDefContainer& option_defs) {
    auto tags = server_selector.getTags();
#if 0
    for (auto tag : tags) {
        PsqlBindArray in_bindings = {
            PsqlBindArray::createString(tag.get()),
            PsqlBindArray::createTimestamp(modification_time)
        };
        getOptionDefs(index, in_bindings, option_defs);
    }
#endif
}

void
PgSqlConfigBackendImpl::getOptionDefs(const int index,
                                      const PsqlBindArray& in_bindings,
                                      OptionDefContainer& option_defs) {
    // Create output bindings. The order must match that in the prepared
    // statement.
#if 0
    PsqlBindArray out_bindings = {
        PsqlBindArray::createInteger<uint64_t>(), // id
        PsqlBindArray::createInteger<uint16_t>(), // code
        PsqlBindArray::createString(OPTION_NAME_BUF_LENGTH), // name
        PsqlBindArray::createString(OPTION_SPACE_BUF_LENGTH), // space
        PsqlBindArray::createInteger<uint8_t>(), // type
        PsqlBindArray::createTimestamp(), // modification_ts
        PsqlBindArray::createInteger<uint8_t>(), // array
        PsqlBindArray::createString(OPTION_ENCAPSULATE_BUF_LENGTH), // encapsulate
        PsqlBindArray::createString(OPTION_RECORD_TYPES_BUF_LENGTH), // record_types
        PsqlBindArray::createString(USER_CONTEXT_BUF_LENGTH), // user_context
        PsqlBindArray::createString(SERVER_TAG_BUF_LENGTH) // server_tag
    };
#endif

    uint64_t last_def_id = 0;

    OptionDefContainer local_option_defs;

#if 0
    // Run select query.
    conn_.selectQuery(index, in_bindings, out_bindings,
                      [&local_option_defs, &last_def_id]
                      (PsqlBindArray& out_bindings) {
        // Get pointer to last fetched option definition.
        OptionDefinitionPtr last_def;
        if (!local_option_defs.empty()) {
            last_def = *local_option_defs.rbegin();
        }

        // See if the last fetched definition is the one for which we now got
        // the row of data. If not, it means that we need to create new option
        // definition.
        if ((last_def_id == 0) ||
            (last_def_id != out_bindings[0]->getInteger<uint64_t>())) {

            last_def_id = out_bindings[0]->getInteger<uint64_t>();

            // Check array type, because depending on this value we have to use
            // different constructor.
            bool array_type = static_cast<bool>(out_bindings[6]->getInteger<uint8_t>());
            if (array_type) {
                // Create array option.
                last_def = OptionDefinition::create(out_bindings[2]->getString(),
                                                    out_bindings[1]->getInteger<uint16_t>(),
                                                    out_bindings[3]->getString(),
                                                    static_cast<OptionDataType>
                                                    (out_bindings[4]->getInteger<uint8_t>()),
                                                    array_type);
            } else {
                // Create non-array option.
                last_def = OptionDefinition::create(out_bindings[2]->getString(),
                                                    out_bindings[1]->getInteger<uint16_t>(),
                                                    out_bindings[3]->getString(),
                                                    static_cast<OptionDataType>
                                                    (out_bindings[4]->getInteger<uint8_t>()),
                                                    out_bindings[7]->getStringOrDefault("").c_str());
            }

            // id
            last_def->setId(last_def_id);

            // record_types
            ElementPtr record_types_element = out_bindings[8]->getJSON();
            if (record_types_element) {
                if (record_types_element->getType() != Element::list) {
                    isc_throw(BadValue, "invalid record_types value "
                              << out_bindings[8]->getString());
                }
                // This element must contain a list of integers specifying
                // types of the record fields.
                for (auto i = 0; i < record_types_element->size(); ++i) {
                    auto type_element = record_types_element->get(i);
                    if (type_element->getType() != Element::integer) {
                        isc_throw(BadValue, "record type values must be integers");
                    }
                    last_def->addRecordField(static_cast<OptionDataType>
                                             (type_element->intValue()));
                }
            }

            // Update modification time.
            last_def->setModificationTime(out_bindings[5]->getTimestamp());

            // server_tag
            ServerTag last_def_server_tag(out_bindings[10]->getString());
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
#endif
}

void
PgSqlConfigBackendImpl::createUpdateOptionDef(const db::ServerSelector& server_selector,
                                              const OptionDefinitionPtr& option_def,
                                              const std::string& /*space*/,
                                              const int& /*get_option_def_code_space*/,
                                              const int& insert_option_def,
                                              const int& update_option_def,
                                              const int& create_audit_revision,
                                              const int& insert_option_def_server) {

    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "managing configuration for no particular server"
                  " (unassigned) is unsupported at the moment");
    }

    auto tag = getServerTag(server_selector, "creating or updating option definition");

    ElementPtr record_types = Element::createList();
    for (auto field : option_def->getRecordFields()) {
        record_types->add(Element::create(static_cast<int>(field)));
    }
#if 0
    PsqlBindArrayPtr record_types_binding = record_types->empty() ?
        PsqlBindArray::createNull() : PsqlBindArray::createString(record_types->str());

    PsqlBindArray in_bindings = {
        PsqlBindArray::createInteger<uint16_t>(option_def->getCode()),
        PsqlBindArray::createString(option_def->getName()),
        PsqlBindArray::createString(option_def->getOptionSpaceName()),
        PsqlBindArray::createInteger<uint8_t>(static_cast<uint8_t>(option_def->getType())),
        PsqlBindArray::createTimestamp(option_def->getModificationTime()),
        PsqlBindArray::createBool(option_def->getArrayType()),
        PsqlBindArray::createString(option_def->getEncapsulatedSpace()),
        record_types_binding,
        createInputContextBinding(option_def),
        PsqlBindArray::createString(tag),
        PsqlBindArray::createInteger<uint16_t>(option_def->getCode()),
        PsqlBindArray::createString(option_def->getOptionSpaceName())
    };

    PgSqlTransaction transaction(conn_);

    // Create scoped audit revision. As long as this instance exists
    // no new audit revisions are created in any subsequent calls.
    ScopedAuditRevision audit_revision(this,
                                       create_audit_revision,
                                       server_selector,
                                       "option definition set",
                                       true);

    if (conn_.updateDeleteQuery(update_option_def, in_bindings) == 0) {
        // Remove the bindings used only during the update.
        in_bindings.resize(in_bindings.size() - 3);
        conn_.insertQuery(insert_option_def, in_bindings);

        // Fetch unique identifier of the inserted option definition and use it
        // as input to the next query.
        uint64_t id = pgsql_insert_id(conn_.pgsql_);

        // Insert associations of the option definition with servers.
        attachElementToServers(insert_option_def_server,
                               server_selector,
                               PsqlBindArray::createInteger<uint64_t>(id),
                               PsqlBindArray::createTimestamp(option_def->getModificationTime()));
    }

    transaction.commit();
#endif
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

#if 0
    OptionContainer options;
    PsqlBindArray in_bindings;
    in_bindings.push_back(PsqlBindArray::createString(tag));
    if (universe == Option::V4) {
        in_bindings.push_back(PsqlBindArray::createInteger<uint8_t>(static_cast<uint8_t>(code)));
    } else {
        in_bindings.push_back(PsqlBindArray::createInteger<uint16_t>(code));
    }
    in_bindings.push_back(PsqlBindArray::createString(space));
    getOptions(index, in_bindings, universe, options);
    return (options.empty() ? OptionDescriptorPtr() :
            OptionDescriptor::create(*options.begin()));
#endif
}

OptionContainer
PgSqlConfigBackendImpl::getAllOptions(const int index,
                                      const Option::Universe& universe,
                                      const ServerSelector& server_selector) {
    OptionContainer options;
#if 0
    auto tags = server_selector.getTags();
    for (auto tag : tags) {
        PsqlBindArray in_bindings = {
            PsqlBindArray::createString(tag.get())
        };
        getOptions(index, in_bindings, universe, options);
    }
#endif

    return (options);
}

OptionContainer
PgSqlConfigBackendImpl::getModifiedOptions(const int index,
                                           const Option::Universe& universe,
                                           const ServerSelector& server_selector,
                                           const boost::posix_time::ptime& modification_time) {
    OptionContainer options;

    auto tags = server_selector.getTags();
    for (auto tag : tags) {
        PsqlBindArray in_bindings;
#if 0
        PsqlBindArray in_bindings = {
            PsqlBindArray::createString(tag.get()),
            PsqlBindArray::createTimestamp(modification_time)
        };
#endif
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

    OptionContainer options;
    PsqlBindArray in_bindings;
#if 0
    in_bindings.push_back(PsqlBindArray::createString(tag));
    uint32_t id = static_cast<uint32_t>(subnet_id);
    in_bindings.push_back(PsqlBindArray::createInteger<uint32_t>(id));
    if (universe == Option::V4) {
        in_bindings.push_back(PsqlBindArray::createInteger<uint8_t>(static_cast<uint8_t>(code)));
    } else {
        in_bindings.push_back(PsqlBindArray::createInteger<uint16_t>(code));
    }
    in_bindings.push_back(PsqlBindArray::createString(space));
#endif
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

    Option::Universe universe = Option::V4;
    OptionContainer options;
    PsqlBindArray in_bindings;
#if 0
    in_bindings.push_back(PsqlBindArray::createString(tag));
    in_bindings.push_back(PsqlBindArray::createInteger<uint64_t>(pool_id));
    if (pool_type == Lease::TYPE_V4) {
        in_bindings.push_back(PsqlBindArray::createInteger<uint8_t>(static_cast<uint8_t>(code)));
    } else {
        in_bindings.push_back(PsqlBindArray::createInteger<uint16_t>(code));
        universe = Option::V6;
    }
    in_bindings.push_back(PsqlBindArray::createString(space));
#endif
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

    OptionContainer options;
    PsqlBindArray in_bindings;
#if 0
    in_bindings.push_back(PsqlBindArray::createString(tag));
    in_bindings.push_back(PsqlBindArray::createString(shared_network_name));
    if (universe == Option::V4) {
        in_bindings.push_back(PsqlBindArray::createInteger<uint8_t>(static_cast<uint8_t>(code)));
    } else {
        in_bindings.push_back(PsqlBindArray::createInteger<uint16_t>(code));
    }
    in_bindings.push_back(PsqlBindArray::createString(space));
#endif
    getOptions(index, in_bindings, universe, options);
    return (options.empty() ? OptionDescriptorPtr() :
            OptionDescriptor::create(*options.begin()));
}

void
PgSqlConfigBackendImpl::getOptions(const int index,
                                   const db::PsqlBindArray& in_bindings,
                                   const Option::Universe& universe,
                                   OptionContainer& options) {
#if 0
    // Create output bindings. The order must match that in the prepared
    // statement.
    PsqlBindArray out_bindings;
    // option_id
    out_bindings.push_back(PsqlBindArray::createInteger<uint64_t>());
    // code
    if (universe == Option::V4) {
        out_bindings.push_back(PsqlBindArray::createInteger<uint8_t>());
    } else {
        out_bindings.push_back(PsqlBindArray::createInteger<uint16_t>());
    }
    // value
    out_bindings.push_back(PsqlBindArray::createBlob(OPTION_VALUE_BUF_LENGTH));
    // forma\tted_value
    out_bindings.push_back(PsqlBindArray::createString(FORMATTED_OPTION_VALUE_BUF_LENGTH));
    // space
    out_bindings.push_back(PsqlBindArray::createString(OPTION_SPACE_BUF_LENGTH));
    // persistent
    out_bindings.push_back(PsqlBindArray::createInteger<uint8_t>());
    // dhcp[46]_subnet_id
    out_bindings.push_back(PsqlBindArray::createInteger<uint32_t>());
    // scope_id
    out_bindings.push_back(PsqlBindArray::createInteger<uint8_t>());
    // user_context
    out_bindings.push_back(PsqlBindArray::createString(USER_CONTEXT_BUF_LENGTH));
    // shared_network_name
    out_bindings.push_back(PsqlBindArray::createString(SHARED_NETWORK_NAME_BUF_LENGTH));
    // pool_id
    out_bindings.push_back(PsqlBindArray::createInteger<uint64_t>());
    // modification_ts
    out_bindings.push_back(PsqlBindArray::createTimestamp());
    // server_tag
    out_bindings.push_back(PsqlBindArray::createString(SERVER_TAG_BUF_LENGTH));
    // pd_pool_id
    if (universe == Option::V6) {
        out_bindings.push_back(PsqlBindArray::createInteger<uint64_t>());
    }

    uint64_t last_option_id = 0;

    OptionContainer local_options;

    conn_.selectQuery(index, in_bindings, out_bindings,
                      [this, universe, &local_options, &last_option_id]
                      (PsqlBindArray& out_bindings) {
        // Parse option.
        if (!out_bindings[0]->amNull() &&
            ((last_option_id == 0) ||
             (last_option_id < out_bindings[0]->getInteger<uint64_t>()))) {
            last_option_id = out_bindings[0]->getInteger<uint64_t>();

            OptionDescriptorPtr desc = processOptionRow(universe, out_bindings.begin());
            if (desc) {
                // server_tag for the global option
                ServerTag last_option_server_tag(out_bindings[12]->getString());
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
#endif
}

#if 0
OptionDescriptorPtr
PgSqlConfigBackendImpl::processOptionRow(const Option::Universe& universe,
                                         PsqlBindArray::iterator first_binding) {
    // Some of the options have standard or custom definitions.
    // Depending whether the option has a definition or not a different
    // C++ class may be used to represent the option. Therefore, the
    // first thing to do is to see if there is a definition for our
    // parsed option. The option code and space is needed for it.
    std::string space = (*(first_binding + 4))->getString();
    uint16_t code;
    if (universe == Option::V4) {
        code = (*(first_binding + 1))->getInteger<uint8_t>();
    } else {
        code = (*(first_binding + 1))->getInteger<uint16_t>();
    }


    // Get formatted value if available.
    std::string formatted_value = (*(first_binding + 3))->getStringOrDefault("");

    OptionPtr option = Option::create(universe, code);

    // If we don't have a formatted value, check for a blob. Add it to the
    // option if it exists.
    if (formatted_value.empty()) {
        std::vector<uint8_t> blob;
        if (!(*(first_binding + 2))->amNull()) {
            blob = (*(first_binding + 2))->getBlob();
        }
        option->setData(blob.begin(), blob.end());
    }

    // Check if the option is persistent.
    bool persistent = static_cast<bool>((*(first_binding + 5))->getIntegerOrDefault<uint8_t>(0));

    // Create option descriptor which encapsulates our option and adds
    // additional information, i.e. whether the option is persistent,
    // its option space and timestamp.
    OptionDescriptorPtr desc = OptionDescriptor::create(option, persistent, formatted_value);
    desc->space_name_ = space;
    desc->setModificationTime((*(first_binding + 11))->getTimestamp());

    // Set database id for the option.
    if (!(*first_binding)->amNull()) {
        desc->setId((*first_binding)->getInteger<uint64_t>());
    }

    return (desc);
}

void
PgSqlConfigBackendImpl::attachElementToServers(const int index,
                                               const ServerSelector& server_selector,
                                               const PsqlBindArrayPtr& first_binding,
                                               const PsqlBindArrayPtr& in_bindings...) {
    // Create the vector from the parameter pack.
    PsqlBindArray in_server_bindings = { first_binding, in_bindings };
    for (auto tag : server_selector.getTags()) {
        in_server_bindings.push_back(PsqlBindArray::createString(tag.get()));
        // Handles the case where the server does not exists.
        try {
            conn_.insertQuery(index, in_server_bindings);
        } catch (const NullKeyError&) {
            // The message should give the tag value.
            isc_throw(NullKeyError,
                      "server '" << tag.get() << "' does not exist");
        }
        in_server_bindings.pop_back();
    }
}
#endif


PsqlBindArrayPtr
PgSqlConfigBackendImpl::createInputRelayBinding(const NetworkPtr& network) {
    ElementPtr relay_element = Element::createList();
    const auto& addresses = network->getRelayAddresses();
    if (!addresses.empty()) {
        for (const auto& address : addresses) {
            relay_element->add(Element::create(address.toText()));
        }
    }

#if 0
    return (relay_element->empty() ? PsqlBindArray::createNull() :
            PsqlBindArray::condCreateString(relay_element->str()));
#endif
}

PsqlBindArrayPtr
PgSqlConfigBackendImpl::createOptionValueBinding(const OptionDescriptorPtr& option) {

    PsqlBindArrayPtr p(new PsqlBindArray());
    OptionPtr opt = option->option_;
    if (option->formatted_value_.empty() && (opt->len() > opt->getHeaderLen())) {
        OutputBuffer buf(opt->len());
        opt->pack(buf);
        const char* buf_ptr = static_cast<const char*>(buf.getData());
        std::vector<uint8_t> blob(buf_ptr + opt->getHeaderLen(),
                                  buf_ptr + buf.getLength());

        // return (PsqlBindArray::createBlob(blob.begin(), blob.end()));
    }

    // return (PsqlBindArray::createNull());
    return (p);
}

ServerPtr
PgSqlConfigBackendImpl::getServer(const int index, const ServerTag& server_tag) {
    ServerCollection servers;
    PsqlBindArray in_bindings; /* = {
        PsqlBindArray::createString(server_tag.get())
    }; */
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
    PsqlBindArray out_bindings; /*= {
        PsqlBindArray::createInteger<uint64_t>(),
        PsqlBindArray::createString(SERVER_TAG_BUF_LENGTH),
        PsqlBindArray::createString(SERVER_DESCRIPTION_BUF_LENGTH),
        PsqlBindArray::createTimestamp()
    }; */
#if 0
    conn_.selectQuery(index, in_bindings, out_bindings,
                      [&servers](PsqlBindArray& out_bindings) {

        ServerPtr last_server;
        uint64_t id = out_bindings[0]->getInteger<uint64_t>();
        if (!last_server || (last_server->getId() != id)) {

            // Set description if it is non-null.
            auto desc = (out_bindings[2]->amNull() ? "" : out_bindings[2]->getString());
            last_server = Server::create(ServerTag(out_bindings[1]->getString()),
                                         desc);

            // id
            last_server->setId(id);

            // modification_ts
            last_server->setModificationTime(out_bindings[3]->getTimestamp());

            // New server fetched. Let's store it.
            servers.insert(last_server);
        }
    });
#endif
}

void
PgSqlConfigBackendImpl::createUpdateServer(const int& create_audit_revision,
                                           const int& create_index,
                                           const int& update_index,
                                           const ServerPtr& server) {
    // The server tag 'all' is reserved.
    if (server->getServerTag().amAll()) {
        isc_throw(InvalidOperation, "'all' is a name reserved for the server tag which"
                  " associates the configuration elements with all servers connecting"
                  " to the database and a server with this name may not be created");
    }

    // Create scoped audit revision. As long as this instance exists
    // no new audit revisions are created in any subsequent calls.
    ScopedAuditRevision audit_revision(this,
                                       create_audit_revision,
                                       ServerSelector::ALL(),
                                       "server set",
                                       true);

    PgSqlTransaction transaction(conn_);

    PsqlBindArray in_bindings; /* = {
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
    return ("mysql");
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

} // end of namespace isc::dhcp
} // end of namespace isc
