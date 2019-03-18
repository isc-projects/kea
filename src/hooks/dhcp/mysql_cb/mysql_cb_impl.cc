// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <mysql_cb_impl.h>
#include <asiolink/io_address.h>
#include <config_backend/constants.h>
#include <dhcp/option_space.h>
#include <util/buffer.h>
#include <mysql.h>
#include <mysqld_error.h>
#include <cstdint>
#include <utility>

using namespace isc::cb;
using namespace isc::data;
using namespace isc::db;
using namespace isc::util;

namespace isc {
namespace dhcp {

MySqlConfigBackendImpl::
ScopedAuditRevision::ScopedAuditRevision(MySqlConfigBackendImpl* impl,
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

MySqlConfigBackendImpl::
ScopedAuditRevision::~ScopedAuditRevision() {
    impl_->clearAuditRevision();
}

MySqlConfigBackendImpl::
MySqlConfigBackendImpl(const DatabaseConnection::ParameterMap& parameters)
    : conn_(parameters), audit_revision_created_(false) {
    // Open the database.
    conn_.openDatabase();

    // Test schema version before we try to prepare statements.
    std::pair<uint32_t, uint32_t> code_version(MYSQL_SCHEMA_VERSION_MAJOR,
                                               MYSQL_SCHEMA_VERSION_MINOR);
/*    std::pair<uint32_t, uint32_t> db_version = getVersion();
    if (code_version != db_version) {
        isc_throw(DbOpenError, "MySQL schema version mismatch: need version: "
                  << code_version.first << "." << code_version.second
                  << " found version:  " << db_version.first << "."
                  << db_version.second);
    } */

    // Enable autocommit. In case transaction is explicitly used, this
    // setting will be overwritten for the transaction. However, there are
    // cases when lack of autocommit could cause transactions to hang
    // until commit or rollback is explicitly called. This already
    // caused issues for some unit tests which were unable to cleanup
    // the database after the test because of pending transactions.
    // Use of autocommit will eliminate this problem.
    my_bool result = mysql_autocommit(conn_.mysql_, 1);
    if (result != MLM_FALSE) {
        isc_throw(DbOperationError, mysql_error(conn_.mysql_));
    }
}

MySqlConfigBackendImpl::~MySqlConfigBackendImpl() {
    // Free up the prepared statements, ignoring errors. (What would we do
    // about them? We're destroying this object and are not really concerned
    // with errors on a database connection that is about to go away.)
    for (int i = 0; i < conn_.statements_.size(); ++i) {
        if (conn_.statements_[i] != NULL) {
            (void) mysql_stmt_close(conn_.statements_[i]);
            conn_.statements_[i] = NULL;
        }
    }
}

MySqlBindingPtr
MySqlConfigBackendImpl::createBinding(const Triplet<uint32_t>& triplet) {
    if (triplet.unspecified()) {
        return (MySqlBinding::createNull());
    }
    return (MySqlBinding::createInteger<uint32_t>(triplet.get()));
}

Triplet<uint32_t>
MySqlConfigBackendImpl::createTriplet(const MySqlBindingPtr& binding) {
    if (!binding) {
        isc_throw(Unexpected, "MySQL configuration backend internal error: "
                  "binding pointer is NULL when creating a triplet value");
    }

    if (binding->amNull()) {
        return (Triplet<uint32_t>());
    }

    return (Triplet<uint32_t>(binding->getInteger<uint32_t>()));
}

void
MySqlConfigBackendImpl::createAuditRevision(const int index,
                                            const ServerSelector& server_selector,
                                            const boost::posix_time::ptime& audit_ts,
                                            const std::string& log_message,
                                            const bool cascade_transaction) {
    // Do not touch existing audit revision in case of the cascade update.
    if (audit_revision_created_) {
        return;
    }

    auto tag = getServerTag(server_selector, "creating new configuration "
                            "audit revision");

    MySqlBindingCollection in_bindings = {
        MySqlBinding::createTimestamp(audit_ts),
        MySqlBinding::createString(tag),
        MySqlBinding::createString(log_message),
        MySqlBinding::createInteger<uint8_t>(static_cast<uint8_t>(cascade_transaction))
    };
    conn_.insertQuery(index, in_bindings);
    audit_revision_created_ = true;
}

void
MySqlConfigBackendImpl::clearAuditRevision() {
    audit_revision_created_ = false;
}

void
MySqlConfigBackendImpl::getRecentAuditEntries(const int index,
                                              const db::ServerSelector& server_selector,
                                              const boost::posix_time::ptime& modification_time,
                                              AuditEntryCollection& audit_entries) {
    // Create the output bindings for receiving the data.
    MySqlBindingCollection out_bindings = {
        MySqlBinding::createInteger<uint64_t>(), // id
        MySqlBinding::createString(AUDIT_ENTRY_OBJECT_TYPE_BUF_LENGTH), // object_type
        MySqlBinding::createInteger<uint64_t>(), // object_id
        MySqlBinding::createInteger<uint8_t>(), // modification_type
        MySqlBinding::createTimestamp(), // modification_time
        MySqlBinding::createString(AUDIT_ENTRY_LOG_MESSAGE_BUF_LENGTH) // log_message
    };

    auto tags = getServerTags(server_selector);

    for (auto tag : tags) {

        // There is only one input binding, modification time.
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(tag),
            MySqlBinding::createTimestamp(modification_time)
        };

        // Execute select.
        conn_.selectQuery(index, in_bindings, out_bindings,
                          [&audit_entries] (MySqlBindingCollection& out_bindings) {
             // Convert the numeric modification type into modification type enum.
            AuditEntry::ModificationType mod_type =
                static_cast<AuditEntry::ModificationType>(out_bindings[3]->getInteger<uint8_t>());

            // Create new audit entry and add it to the collection of received
            // entries.
            AuditEntryPtr audit_entry(new AuditEntry(out_bindings[1]->getString(),
                                                     out_bindings[2]->getInteger<uint64_t>(),
                                                     mod_type,
                                                     out_bindings[4]->getTimestamp(),
                                                     out_bindings[5]->getStringOrDefault("")));
            audit_entries.insert(audit_entry);
        });
    }
}

uint64_t
MySqlConfigBackendImpl::deleteFromTable(const int index,
                                        const ServerSelector& server_selector,
                                        const std::string& operation) {
    MySqlBindingCollection in_bindings;
    return (deleteFromTable(index, server_selector, operation, in_bindings));
}

void
MySqlConfigBackendImpl::getGlobalParameters(const int index,
                                            const MySqlBindingCollection& in_bindings,
                                            StampedValueCollection& parameters) {
    // The following parameters from the dhcp[46]_global_parameter table are
    // returned:
    // - id
    // - name - parameter name
    // - value - parameter value
    // - modification_ts - modification timestamp.
    MySqlBindingCollection out_bindings = {
        MySqlBinding::createInteger<uint64_t>(), // id
        MySqlBinding::createString(GLOBAL_PARAMETER_NAME_BUF_LENGTH), // name
        MySqlBinding::createString(GLOBAL_PARAMETER_VALUE_BUF_LENGTH), // value
        MySqlBinding::createInteger<uint8_t>(), // parameter_type
        MySqlBinding::createTimestamp() // modification_ts
    };

    conn_.selectQuery(index, in_bindings, out_bindings,
                      [&parameters] (MySqlBindingCollection& out_bindings) {
        if (!out_bindings[1]->getString().empty()) {

            // Convert value read as string from the database to the actual
            // data type known from the database as binding #3.
            StampedValuePtr stamped_value =
                StampedValue::create(out_bindings[1]->getString(),
                                     out_bindings[2]->getString(),
                                     static_cast<Element::types>
                                     (out_bindings[3]->getInteger<uint8_t>()));

            stamped_value->setModificationTime(out_bindings[4]->getTimestamp());
            parameters.insert(stamped_value);
        }
    });
}

OptionDefinitionPtr
MySqlConfigBackendImpl::getOptionDef(const int index,
                                     const ServerSelector& server_selector,
                                     const uint16_t code,
                                     const std::string& space) {

    if (server_selector.amUnassigned()) {
        isc_throw(NotImplemented, "managing configuration for no particular server"
                  " (unassigned) is unsupported at the moment");
    }

    auto tag = getServerTag(server_selector, "fetching option definition");

    OptionDefContainer option_defs;
    MySqlBindingCollection in_bindings = {
        MySqlBinding::createString(tag),
        MySqlBinding::createInteger<uint16_t>(code),
        MySqlBinding::createString(space)
    };
    getOptionDefs(index, in_bindings, option_defs);
    return (option_defs.empty() ? OptionDefinitionPtr() : *option_defs.begin());
}

void
MySqlConfigBackendImpl::getAllOptionDefs(const int index,
                     const ServerSelector& server_selector,
                     OptionDefContainer& option_defs) {
    auto tags = getServerTags(server_selector);
    for (auto tag : tags) {
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(tag)
        };
        getOptionDefs(index, in_bindings, option_defs);
    }
}

void
MySqlConfigBackendImpl::getModifiedOptionDefs(const int index,
                                              const ServerSelector& server_selector,
                                              const boost::posix_time::ptime& modification_time,
                                              OptionDefContainer& option_defs) {
    auto tags = getServerTags(server_selector);
    for (auto tag : tags) {
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(tag),
            MySqlBinding::createTimestamp(modification_time)
        };
        getOptionDefs(index, in_bindings, option_defs);
    }
}

void
MySqlConfigBackendImpl::getOptionDefs(const int index,
                                      const MySqlBindingCollection& in_bindings,
                                      OptionDefContainer& option_defs) {
    // Create output bindings. The order must match that in the prepared
    // statement.
    MySqlBindingCollection out_bindings = {
        MySqlBinding::createInteger<uint64_t>(), // id
        MySqlBinding::createInteger<uint16_t>(), // code
        MySqlBinding::createString(OPTION_NAME_BUF_LENGTH), // name
        MySqlBinding::createString(OPTION_SPACE_BUF_LENGTH), // space
        MySqlBinding::createInteger<uint8_t>(), // type
        MySqlBinding::createTimestamp(), // modification_ts
        MySqlBinding::createInteger<uint8_t>(), // array
        MySqlBinding::createString(OPTION_ENCAPSULATE_BUF_LENGTH), // encapsulate
        MySqlBinding::createString(OPTION_RECORD_TYPES_BUF_LENGTH), // record_types
        MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH) // user_context
    };

    uint64_t last_def_id = 0;

    // Run select query.
    conn_.selectQuery(index, in_bindings, out_bindings,
                      [&option_defs, &last_def_id]
                      (MySqlBindingCollection& out_bindings) {
        // Get pointer to last fetched option definition.
        OptionDefinitionPtr last_def;
        if (!option_defs.empty()) {
            last_def = *option_defs.rbegin();
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
                last_def.reset(new OptionDefinition(out_bindings[2]->getString(),
                                                    out_bindings[1]->getInteger<uint16_t>(),
                                                    static_cast<OptionDataType>
                                                    (out_bindings[4]->getInteger<uint8_t>()),
                                                    array_type));
            } else {
                // Create non-array option.
                last_def.reset(new OptionDefinition(out_bindings[2]->getString(),
                                                    out_bindings[1]->getInteger<uint16_t>(),
                                                    static_cast<OptionDataType>
                                                    (out_bindings[4]->getInteger<uint8_t>()),
                                                    out_bindings[7]->getStringOrDefault("").c_str()));
            }

            // space
            last_def->setOptionSpaceName(out_bindings[3]->getStringOrDefault(""));

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

            // Store created option definition.
            option_defs.push_back(last_def);
        }
    });
}

OptionDescriptorPtr
MySqlConfigBackendImpl::getOption(const int index,
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
    MySqlBindingCollection in_bindings;
    in_bindings.push_back(MySqlBinding::createString(tag));
    if (universe == Option::V4) {
        in_bindings.push_back(MySqlBinding::createInteger<uint8_t>(static_cast<uint8_t>(code)));
    } else {
        in_bindings.push_back(MySqlBinding::createInteger<uint16_t>(code));
    }
    in_bindings.push_back(MySqlBinding::createString(space));
    getOptions(index, in_bindings, universe, options);
    return (options.empty() ? OptionDescriptorPtr() :
            OptionDescriptorPtr(new OptionDescriptor(*options.begin())));
}

OptionContainer
MySqlConfigBackendImpl::getAllOptions(const int index,
                                      const Option::Universe& universe,
                                      const ServerSelector& server_selector) {
    OptionContainer options;

    auto tags = getServerTags(server_selector);
    for (auto tag : tags) {
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(tag)
        };
        getOptions(index, in_bindings, universe, options);
    }

    return (options);
}

OptionContainer
MySqlConfigBackendImpl::getModifiedOptions(const int index,
                                           const Option::Universe& universe,
                                           const ServerSelector& server_selector,
                                           const boost::posix_time::ptime& modification_time) {
    OptionContainer options;

    auto tags = getServerTags(server_selector);
    for (auto tag : tags) {
        MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(tag),
            MySqlBinding::createTimestamp(modification_time)
        };
        getOptions(index, in_bindings, universe, options);
    }

    return (options);
}

OptionDescriptorPtr
MySqlConfigBackendImpl::getOption(const int index,
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
    MySqlBindingCollection in_bindings;
    in_bindings.push_back(MySqlBinding::createString(tag));
    uint32_t id = static_cast<uint32_t>(subnet_id);
    in_bindings.push_back(MySqlBinding::createInteger<uint32_t>(id));
    if (universe == Option::V4) {
        in_bindings.push_back(MySqlBinding::createInteger<uint8_t>(static_cast<uint8_t>(code)));
    } else {
        in_bindings.push_back(MySqlBinding::createInteger<uint16_t>(code));
    }
    in_bindings.push_back(MySqlBinding::createString(space));
    getOptions(index, in_bindings, universe, options);
    return (options.empty() ? OptionDescriptorPtr() :
            OptionDescriptorPtr(new OptionDescriptor(*options.begin())));
}

OptionDescriptorPtr
MySqlConfigBackendImpl::getOption(const int index,
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
    MySqlBindingCollection in_bindings;
    in_bindings.push_back(MySqlBinding::createString(tag));
    in_bindings.push_back(MySqlBinding::createInteger<uint64_t>(pool_id));
    if (pool_type == Lease::TYPE_V4) {
        in_bindings.push_back(MySqlBinding::createInteger<uint8_t>(static_cast<uint8_t>(code)));
    } else {
        in_bindings.push_back(MySqlBinding::createInteger<uint16_t>(code));
        universe = Option::V6;
    }
    in_bindings.push_back(MySqlBinding::createString(space));
    getOptions(index, in_bindings, universe, options);
    return (options.empty() ? OptionDescriptorPtr() :
            OptionDescriptorPtr(new OptionDescriptor(*options.begin())));
}

OptionDescriptorPtr
MySqlConfigBackendImpl::getOption(const int index,
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
    MySqlBindingCollection in_bindings;
    in_bindings.push_back(MySqlBinding::createString(tag));
    in_bindings.push_back(MySqlBinding::createString(shared_network_name));
    if (universe == Option::V4) {
        in_bindings.push_back(MySqlBinding::createInteger<uint8_t>(static_cast<uint8_t>(code)));
    } else {
        in_bindings.push_back(MySqlBinding::createInteger<uint16_t>(code));
    }
    in_bindings.push_back(MySqlBinding::createString(space));
    getOptions(index, in_bindings, universe, options);
    return (options.empty() ? OptionDescriptorPtr() :
            OptionDescriptorPtr(new OptionDescriptor(*options.begin())));
}

void
MySqlConfigBackendImpl::getOptions(const int index,
                                   const db::MySqlBindingCollection& in_bindings,
                                   const Option::Universe& universe,
                                   OptionContainer& options) {
    // Create output bindings. The order must match that in the prepared
    // statement.
    MySqlBindingCollection out_bindings;
    // option_id
    out_bindings.push_back(MySqlBinding::createInteger<uint64_t>());
    // code
    if (universe == Option::V4) {
        out_bindings.push_back(MySqlBinding::createInteger<uint8_t>());
    } else {
        out_bindings.push_back(MySqlBinding::createInteger<uint16_t>());
    }
    // value
    out_bindings.push_back(MySqlBinding::createBlob(OPTION_VALUE_BUF_LENGTH));
    // forma\tted_value
    out_bindings.push_back(MySqlBinding::createString(FORMATTED_OPTION_VALUE_BUF_LENGTH));
    // space
    out_bindings.push_back(MySqlBinding::createString(OPTION_SPACE_BUF_LENGTH));
    // persistent
    out_bindings.push_back(MySqlBinding::createInteger<uint8_t>());
    // dhcp[46]_subnet_id
    out_bindings.push_back(MySqlBinding::createInteger<uint32_t>());
    // scope_id
    out_bindings.push_back(MySqlBinding::createInteger<uint8_t>());
    // user_context
    out_bindings.push_back(MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH));
    // shared_network_name
    out_bindings.push_back(MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH));
    // pool_id
    out_bindings.push_back(MySqlBinding::createInteger<uint64_t>());
    // modification_ts
    out_bindings.push_back(MySqlBinding::createTimestamp());
    // pd_pool_id
    if (universe == Option::V6) {
        out_bindings.push_back(MySqlBinding::createInteger<uint64_t>());
    }

    uint64_t last_option_id = 0;

    conn_.selectQuery(index, in_bindings, out_bindings,
                      [this, universe, &options, &last_option_id]
                      (MySqlBindingCollection& out_bindings) {
        // Parse option.
        if (!out_bindings[0]->amNull() &&
            ((last_option_id == 0) ||
             (last_option_id < out_bindings[0]->getInteger<uint64_t>()))) {
            last_option_id = out_bindings[0]->getInteger<uint64_t>();

            OptionDescriptorPtr desc = processOptionRow(universe, out_bindings.begin());
            if (desc) {
                options.push_back(*desc);
            }
        }
    });
}

OptionDescriptorPtr
MySqlConfigBackendImpl::processOptionRow(const Option::Universe& universe,
                                         MySqlBindingCollection::iterator first_binding) {
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

    OptionPtr option(new Option(universe, code));

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
    OptionDescriptorPtr desc(new OptionDescriptor(option, persistent, formatted_value));
    desc->space_name_ = space;
    desc->setModificationTime((*(first_binding + 11))->getTimestamp());

    return (desc);
}

MySqlBindingPtr
MySqlConfigBackendImpl::createInputRelayBinding(const NetworkPtr& network) {
    ElementPtr relay_element = Element::createList();
    const auto& addresses = network->getRelayAddresses();
    if (!addresses.empty()) {
        for (const auto& address : addresses) {
            relay_element->add(Element::create(address.toText()));
        }
    }

    return (relay_element->empty() ? MySqlBinding::createNull() :
            MySqlBinding::condCreateString(relay_element->str()));
}

MySqlBindingPtr
MySqlConfigBackendImpl::createInputRequiredClassesBinding(const NetworkPtr& network) {
    // Create JSON list of required classes.
    ElementPtr required_classes_element = Element::createList();
    const auto& required_classes = network->getRequiredClasses();
    for (auto required_class = required_classes.cbegin();
         required_class != required_classes.cend();
         ++required_class) {
        required_classes_element->add(Element::create(*required_class));
    }

    return (required_classes_element ?
            MySqlBinding::createString(required_classes_element->str()) :
            MySqlBinding::createNull());
}

MySqlBindingPtr
MySqlConfigBackendImpl::createOptionValueBinding(const OptionDescriptorPtr& option) {
    OptionPtr opt = option->option_;
    if (option->formatted_value_.empty() && (opt->len() > opt->getHeaderLen())) {
        OutputBuffer buf(opt->len());
        opt->pack(buf);
        const char* buf_ptr = static_cast<const char*>(buf.getData());
        std::vector<uint8_t> blob(buf_ptr + opt->getHeaderLen(),
                                  buf_ptr + buf.getLength());
        return (MySqlBinding::createBlob(blob.begin(), blob.end()));

    }

    return (MySqlBinding::createNull());
}

std::string
MySqlConfigBackendImpl::getType() const {
    return ("mysql");
}

std::string
MySqlConfigBackendImpl::getHost() const {
    std::string host = "localhost";
    try {
        host = conn_.getParameter("host");
    } catch (...) {
        // No host parameter. Return localhost as a default.
    }
    return (host);
}

uint16_t
MySqlConfigBackendImpl::getPort() const {
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
