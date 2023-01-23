// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <database/database_connection.h>
#include <database/db_exceptions.h>
#include <database/dbaccess_parser.h>

#include <boost/lexical_cast.hpp>

#include <map>
#include <string>
#include <utility>

using namespace std;
using namespace isc::data;

namespace isc {
namespace db {


// Factory function to build the parser
DbAccessParser::DbAccessParser()
    : values_() {
}

// Parse the configuration and check that the various keywords are consistent.
void
DbAccessParser::parse(std::string& access_string,
                      ConstElementPtr database_config) {

    // To cope with incremental updates, the strategy is:
    // 1. Take a copy of the stored keyword/value pairs.
    // 2. Update the copy with the passed keywords.
    // 3. Perform validation checks on the updated keyword/value pairs.
    // 4. If all is OK, update the stored keyword/value pairs.
    // 5. Save resulting database access string in the Configuration
    // Manager.

    // Note only range checks can fail with a database_config from
    // a flex/bison parser.

    // 1. Take a copy of the stored keyword/value pairs.
    DatabaseConnection::ParameterMap values_copy = values_;

    int64_t lfc_interval = 0;
    int64_t connect_timeout = 0;
    int64_t read_timeout = 0;
    int64_t write_timeout = 0;
    int64_t tcp_user_timeout = 0;
    int64_t port = 0;
    int64_t max_reconnect_tries = 0;
    int64_t reconnect_wait_time = 0;
    int64_t max_row_errors = 0;

    // 2. Update the copy with the passed keywords.
    for (std::pair<std::string, ConstElementPtr> param : database_config->mapValue()) {
        try {
            if ((param.first == "persist") ||
                (param.first == "readonly")) {
                values_copy[param.first] = (param.second->boolValue() ?
                                            "true" : "false");

            } else if (param.first == "lfc-interval") {
                lfc_interval = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(lfc_interval);

            } else if (param.first == "connect-timeout") {
                connect_timeout = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(connect_timeout);

            } else if (param.first == "read-timeout") {
                read_timeout = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(read_timeout);

            } else if (param.first == "write-timeout") {
                write_timeout = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(write_timeout);

            } else if (param.first == "tcp-user-timeout") {
                tcp_user_timeout = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(tcp_user_timeout);

            } else if (param.first == "max-reconnect-tries") {
                max_reconnect_tries = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(max_reconnect_tries);

            } else if (param.first == "reconnect-wait-time") {
                reconnect_wait_time = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(reconnect_wait_time);

            } else if (param.first == "port") {
                port = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(port);

            } else if (param.first == "max-row-errors") {
                max_row_errors = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(max_row_errors);
            } else {

                // all remaining string parameters
                // type
                // user
                // password
                // host
                // name
                // on-fail
                // trust-anchor
                // cert-file
                // key-file
                // cipher-list
                values_copy[param.first] = param.second->stringValue();
            }
        } catch (const isc::data::TypeError& ex) {
            // Append position of the element.
            isc_throw(DbConfigError, "invalid value type specified for "
                      "parameter '" << param.first << "' ("
                      << param.second->getPosition() << ")");
        }
    }

    // 3. Perform validation checks on the updated set of keyword/values.
    //
    // a. Check if the "type" keyword exists and thrown an exception if not.
    auto type_ptr = values_copy.find("type");
    if (type_ptr == values_copy.end()) {
        isc_throw(DbConfigError,
                  "database access parameters must "
                  "include the keyword 'type' to determine type of database "
                  "to be accessed (" << database_config->getPosition() << ")");
    }

    // b. Check if the 'type' keyword known and throw an exception if not.
    //
    // Please note when you add a new database backend you have to add
    // the new type here and in server grammars.
    string dbtype = type_ptr->second;
    if ((dbtype != "memfile") &&
        (dbtype != "mysql") &&
        (dbtype != "postgresql")) {
        ConstElementPtr value = database_config->get("type");
        isc_throw(DbConfigError, "unknown backend database type: " << dbtype
                  << " (" << value->getPosition() << ")");
    }

    // c. Check that the lfc-interval is within a reasonable range.
    if ((lfc_interval < 0) ||
        (lfc_interval > std::numeric_limits<uint32_t>::max())) {
        ConstElementPtr value = database_config->get("lfc-interval");
        isc_throw(DbConfigError, "lfc-interval value: " << lfc_interval
                  << " is out of range, expected value: 0.."
                  << std::numeric_limits<uint32_t>::max()
                  << " (" << value->getPosition() << ")");
    }

    // d. Check that the timeouts are within a reasonable range.
    if ((connect_timeout < 0) ||
        (connect_timeout > std::numeric_limits<uint32_t>::max())) {
        ConstElementPtr value = database_config->get("connect-timeout");
        isc_throw(DbConfigError, "connect-timeout value: " << connect_timeout
                  << " is out of range, expected value: 0.."
                  << std::numeric_limits<uint32_t>::max()
                  << " (" << value->getPosition() << ")");
    }
    if ((read_timeout < 0) ||
        (read_timeout > std::numeric_limits<uint32_t>::max())) {
        ConstElementPtr value = database_config->get("read-timeout");
        isc_throw(DbConfigError, "read-timeout value: " << read_timeout
                  << " is out of range, expected value: 0.."
                  << std::numeric_limits<uint32_t>::max()
                  << " (" << value->getPosition() << ")");
    }
    if (read_timeout > 0 && (dbtype != "mysql")) {
        ConstElementPtr value = database_config->get("read-timeout");
        isc_throw(DbConfigError, "read-timeout value is only supported by the mysql backend"
                  << " (" << value->getPosition() << ")");
    }
    if ((write_timeout < 0) ||
        (write_timeout > std::numeric_limits<uint32_t>::max())) {
        ConstElementPtr value = database_config->get("write-timeout");
        isc_throw(DbConfigError, "write-timeout value: " << write_timeout
                  << " is out of range, expected value: 0.."
                  << std::numeric_limits<uint32_t>::max()
                  << " (" << value->getPosition() << ")");
    }
    if (write_timeout > 0 && (dbtype != "mysql")) {
        ConstElementPtr value = database_config->get("write-timeout");
        isc_throw(DbConfigError, "write-timeout value is only supported by the mysql backend"
                  << " (" << value->getPosition() << ")");
    }
    if ((tcp_user_timeout < 0) ||
        (tcp_user_timeout > std::numeric_limits<uint32_t>::max())) {
        ConstElementPtr value = database_config->get("tcp-user-timeout");
        isc_throw(DbConfigError, "tcp-user-timeout value: " << tcp_user_timeout
                  << " is out of range, expected value: 0.."
                  << std::numeric_limits<uint32_t>::max()
                  << " (" << value->getPosition() << ")");
    }
    if (tcp_user_timeout > 0 && (dbtype != "postgresql")) {
        ConstElementPtr value = database_config->get("tcp-user-timeout");
        isc_throw(DbConfigError, "tcp-user-timeout value is only supported by the postgresql backend"
                  << " (" << value->getPosition() << ")");
    }

    // e. Check that the port is within a reasonable range.
    if ((port < 0) ||
        (port > std::numeric_limits<uint16_t>::max())) {
        ConstElementPtr value = database_config->get("port");
        isc_throw(DbConfigError, "port value: " << port
                  << " is out of range, expected value: 0.."
                  << std::numeric_limits<uint16_t>::max()
                  << " (" << value->getPosition() << ")");
    }

    // f. Check that the max-row-errors is within a reasonable range.
    if ((max_row_errors < 0) ||
        (max_row_errors > std::numeric_limits<uint32_t>::max())) {
        ConstElementPtr value = database_config->get("max-row-errors");
        isc_throw(DbConfigError, "max-row-errors value: " << max_row_errors
                  << " is out of range, expected value: 0.."
                  << std::numeric_limits<uint32_t>::max()
                  << " (" << value->getPosition() << ")");
    }

    // Check that the max-reconnect-tries is reasonable.
    if (max_reconnect_tries < 0) {
        ConstElementPtr value = database_config->get("max-reconnect-tries");
        isc_throw(DbConfigError,
                  "max-reconnect-tries cannot be less than zero: ("
                      << value->getPosition() << ")");
    }

    // Check that the reconnect-wait-time is reasonable.
    if ((reconnect_wait_time < 0) ||
        (reconnect_wait_time > std::numeric_limits<uint32_t>::max())) {
        ConstElementPtr value = database_config->get("reconnect-wait-time");
        isc_throw(DbConfigError, "reconnect-wait-time " << reconnect_wait_time
                  << " must be in range 0...MAX_UINT32 (4294967295) "
                  << "(" << value->getPosition() << ")");
    }

    // 4. If all is OK, update the stored keyword/value pairs.  We do this by
    // swapping contents - values_copy is destroyed immediately after the
    // operation (when the method exits), so we are not interested in its new
    // value.
    values_.swap(values_copy);

    // 5. Save the database access string in the Configuration Manager.
    access_string = getDbAccessString();
}

// Create the database access string
std::string
DbAccessParser::getDbAccessString() const {

    // Construct the database access string from all keywords and values in the
    // parameter map where the value is not null.
    string dbaccess;
    for (auto keyval : values_) {
        if (!keyval.second.empty()) {

            // Separate keyword/value pair from predecessor (if there is one).
            if (!dbaccess.empty()) {
                dbaccess += std::string(" ");
            }

            // Add the keyword/value pair to the access string.
            auto val = keyval.second;
            if (val.find_first_of("\t ") != string::npos){
                val = "'" + val + "'";
            }
            dbaccess += (keyval.first + std::string("=") + val);
        }
    }

    return (dbaccess);
}

}  // namespace db
}  // namespace isc
