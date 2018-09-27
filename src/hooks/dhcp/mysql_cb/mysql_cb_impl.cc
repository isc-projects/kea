// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <mysql_cb_impl.h>
#include <asiolink/io_address.h>
#include <mysql.h>
#include <mysqld_error.h>
#include <cstdint>
#include <utility>

using namespace isc::data;
using namespace isc::db;

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

void
MySqlConfigBackendImpl::deleteFromTable(const int index) {
    MySqlBindingCollection in_bindings;
    conn_.updateDeleteQuery(index, in_bindings);
}

void
MySqlConfigBackendImpl::deleteFromTable(const int index, const std::string& key) {
    MySqlBindingCollection in_bindings = {
            MySqlBinding::createString(key)
    };
    conn_.updateDeleteQuery(index, in_bindings);
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
        MySqlBinding::createString(128), // name
        MySqlBinding::createString(128), // space
        MySqlBinding::createInteger<uint8_t>(), // type
        MySqlBinding::createTimestamp(), // modification_ts
        MySqlBinding::createInteger<uint8_t>(), // array
        MySqlBinding::createString(128), // encapsulate
        MySqlBinding::createString(512), // record_types
        MySqlBinding::createString(65536) // user_context
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

} // end of namespace isc::dhcp
} // end of namespace isc
