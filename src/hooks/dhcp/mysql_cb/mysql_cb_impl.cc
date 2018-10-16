// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <mysql_cb_impl.h>
#include <asiolink/io_address.h>
#include <config_backend/constants.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_space.h>
#include <util/buffer.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
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
MySqlConfigBackendImpl(const DatabaseConnection::ParameterMap& parameters)
    : conn_(parameters) {
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
    if (result != 0) {
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

uint64_t
MySqlConfigBackendImpl::deleteFromTable(const int index) {
    MySqlBindingCollection in_bindings;
    return (conn_.updateDeleteQuery(index, in_bindings));
}

uint64_t
MySqlConfigBackendImpl::deleteFromTable(const int index, const std::string& key) {
    MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(key)
    };
    return (conn_.updateDeleteQuery(index, in_bindings));
}

uint64_t
MySqlConfigBackendImpl::deleteFromTable(const int index,
                                        const ServerSelector& server_selector,
                                        const std::string& operation) {
    auto tag = getServerTag(server_selector, operation);

    MySqlBindingCollection in_bindings = {
        MySqlBinding::createString(tag)
    };

    return (conn_.updateDeleteQuery(index, in_bindings));
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

void
MySqlConfigBackendImpl::getOptions(const int index,
                                   const db::MySqlBindingCollection& in_bindings,
                                   const Option::Universe& universe,
                                   OptionContainer& options) {
    // Create output bindings. The order must match that in the prepared
    // statement.
    MySqlBindingCollection out_bindings = {
        MySqlBinding::createInteger<uint64_t>(), // option_id
        MySqlBinding::createInteger<uint8_t>(), // code
        MySqlBinding::createBlob(OPTION_VALUE_BUF_LENGTH), // value
        MySqlBinding::createString(FORMATTED_OPTION_VALUE_BUF_LENGTH), // formatted_value
        MySqlBinding::createString(OPTION_SPACE_BUF_LENGTH), // space
        MySqlBinding::createInteger<uint8_t>(), // persistent
        MySqlBinding::createInteger<uint32_t>(), // dhcp4_subnet_id
        MySqlBinding::createInteger<uint8_t>(), // scope_id
        MySqlBinding::createString(USER_CONTEXT_BUF_LENGTH), // user_context
        MySqlBinding::createString(SHARED_NETWORK_NAME_BUF_LENGTH), // shared_network_name
        MySqlBinding::createInteger<uint64_t>(), // pool_id
        MySqlBinding::createTimestamp() //modification_ts
    };

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
    uint16_t code = (*(first_binding + 1))->getInteger<uint8_t>();

    // See if the option has standard definition.
    OptionDefinitionPtr def = LibDHCP::getOptionDef(space, code);
    // If there is no definition but the option is vendor specific,
    // we should search the definition within the vendor option space.
    if (!def && (space != DHCP4_OPTION_SPACE) && (space != DHCP6_OPTION_SPACE)) {
        uint32_t vendor_id = LibDHCP::optionSpaceToVendorId(space);
        if (vendor_id > 0) {
            def = LibDHCP::getVendorOptionDef(universe, vendor_id, code);
        }
    }

    // Still haven't found the definition. Check if user has specified
    // option definition in the server configuration.
    if (!def) {
        def = LibDHCP::getRuntimeOptionDef(space, code);
    }

    // Option can be stored as a blob or formatted value in the configuration.
    std::vector<uint8_t> blob;
    if (!(*(first_binding + 2))->amNull()) {
        blob = (*(first_binding + 2))->getBlob();
    }
    OptionBuffer buf(blob.begin(), blob.end());

    // Get formatted value if available.
    std::string formatted_value = (*(first_binding + 3))->getStringOrDefault("");

    OptionPtr option;
    if (!def) {
        // No option definition. Create generic option instance.
        option.reset(new Option(universe, code, buf.begin(), buf.end()));

    } else {
        // Option definition found. Use formatted value if available or
        // a blob.
        if (formatted_value.empty()) {
            option = def->optionFactory(universe, code, buf.begin(),
                                        buf.end());
        } else {
            // Spit the value specified in comma separated values
            // format.
            std::vector<std::string> split_vec;
            boost::split(split_vec, formatted_value, boost::is_any_of(","));
            option = def->optionFactory(universe, code, split_vec);
        }
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


} // end of namespace isc::dhcp
} // end of namespace isc
