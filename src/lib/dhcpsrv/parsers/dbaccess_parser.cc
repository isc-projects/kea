// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/option.h>
#include <dhcpsrv/cfg_db_access.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/db_type.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/parsers/dbaccess_parser.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include <map>
#include <string>
#include <utility>

using namespace std;
using namespace isc::data;

namespace isc {
namespace dhcp {


// Factory function to build the parser
DbAccessParser::DbAccessParser(DBType db_type)
    : values_(), type_(db_type) {
}

// Parse the configuration and check that the various keywords are consistent.
void
DbAccessParser::parse(CfgDbAccessPtr& cfg_db,
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
    std::map<string, string> values_copy = values_;

    int64_t lfc_interval = 0;
    int64_t timeout = 0;
    int64_t port = 0;
    int64_t max_reconnect_tries = 0;
    int64_t reconnect_wait_time = 0;
    int64_t request_timeout = 0;
    int64_t tcp_keepalive = 0;
    int64_t max_row_errors = 0;

    // 2. Update the copy with the passed keywords.
    BOOST_FOREACH(ConfigPair param, database_config->mapValue()) {
        try {
            if ((param.first == "persist") || (param.first == "readonly") ||
                (param.first == "tcp-nodelay")) {
                values_copy[param.first] = (param.second->boolValue() ?
                                            "true" : "false");

            } else if (param.first == "lfc-interval") {
                lfc_interval = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(lfc_interval);

            } else if (param.first == "connect-timeout") {
                timeout = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(timeout);

            } else if (param.first == "max-reconnect-tries") {
                max_reconnect_tries = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(max_reconnect_tries);

            } else if (param.first == "reconnect-wait-time") {
                reconnect_wait_time = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(reconnect_wait_time);

            } else if (param.first == "request-timeout") {
                request_timeout = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(request_timeout);

            } else if (param.first == "tcp-keepalive") {
                tcp_keepalive = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(tcp_keepalive);

            } else if (param.first == "port") {
                port = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(port);

            } else if (param.first == "max-row-errors") {
                max_row_errors = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(max_row_errors);

            } else {
                values_copy[param.first] = param.second->stringValue();
            }
        } catch (const isc::data::TypeError& ex) {
            // Append position of the element.
            isc_throw(DhcpConfigError, "invalid value type specified for "
                      "parameter '" << param.first << "' ("
                      << param.second->getPosition() << ")");
        }
    }

    // 3. Perform validation checks on the updated set of keyword/values.
    //
    // a. Check if the "type" keyword exists and thrown an exception if not.
    StringPairMap::const_iterator type_ptr = values_copy.find("type");
    if (type_ptr == values_copy.end()) {
        isc_throw(DhcpConfigError,
                  (type_ == DBType::LEASE_DB ? "lease" : "host")
                  << " database access parameters must "
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
        (dbtype != "postgresql") &&
        (dbtype != "cql")) {
        ConstElementPtr value = database_config->get("type");
        isc_throw(DhcpConfigError, "unknown backend database type: " << dbtype
                  << " (" << value->getPosition() << ")");
    }

    // c. Check that the lfc-interval is within a reasonable range.
    if ((lfc_interval < 0) ||
        (lfc_interval > std::numeric_limits<uint32_t>::max())) {
        ConstElementPtr value = database_config->get("lfc-interval");
        isc_throw(DhcpConfigError, "lfc-interval value: " << lfc_interval
                  << " is out of range, expected value: 0.."
                  << std::numeric_limits<uint32_t>::max()
                  << " (" << value->getPosition() << ")");
    }

    // d. Check that the timeout is within a reasonable range.
    if ((timeout < 0) ||
        (timeout > std::numeric_limits<uint32_t>::max())) {
        ConstElementPtr value = database_config->get("connect-timeout");
        isc_throw(DhcpConfigError, "connect-timeout value: " << timeout
                  << " is out of range, expected value: 0.."
                  << std::numeric_limits<uint32_t>::max()
                  << " (" << value->getPosition() << ")");
    }

    // e. Check that the port is within a reasonable range.
    if ((port < 0) ||
        (port > std::numeric_limits<uint16_t>::max())) {
        ConstElementPtr value = database_config->get("port");
        isc_throw(DhcpConfigError, "port value: " << port
                  << " is out of range, expected value: 0.."
                  << std::numeric_limits<uint16_t>::max()
                  << " (" << value->getPosition() << ")");
    }

    // f. Check that the max-row-errors is within a reasonable range.
    if ((max_row_errors < 0) ||
        (max_row_errors > std::numeric_limits<uint32_t>::max())) {
        ConstElementPtr value = database_config->get("max-row-errors");
        isc_throw(DhcpConfigError, "max-row-errors value: " << max_row_errors
                  << " is out of range, expected value: 0.."
                  << std::numeric_limits<uint32_t>::max()
                  << " (" << value->getPosition() << ")");
    }

    // Check that the max-reconnect-retries reasonable.
    if (max_reconnect_tries < 0) {
        ConstElementPtr value = database_config->get("max-reconnect-tries");
        isc_throw(DhcpConfigError, "max-reconnect-tries cannot be less than zero: "
                  << " (" << value->getPosition() << ")");
    }

    // Check that the reconnect-wait-time reasonable.
    if ((reconnect_wait_time < 0) ||
        (reconnect_wait_time > std::numeric_limits<uint32_t>::max())) {
        ConstElementPtr value = database_config->get("reconnect-wait-time");
        isc_throw(DhcpConfigError, "reconnect-wait-time " << reconnect_wait_time
                  << " must be in range 0...MAX_UINT32 (4294967295) "
                  << " (" << value->getPosition() << ")");
    }

    // Check that request_timeout value makes sense.
    if ((reconnect_wait_time < 0) ||
        (reconnect_wait_time > std::numeric_limits<uint32_t>::max())) {
        ConstElementPtr value = database_config->get("reconnect-wait-time");
        isc_throw(DhcpConfigError, "reconnect-wait-time " << reconnect_wait_time
                  << " must be in range 0...MAX_UINT32 (4294967295) "
                  << " (" << value->getPosition() << ")");
    }
    // Check that tcp_keepalive value makes sense.
    if ((tcp_keepalive < 0) ||
        (tcp_keepalive > std::numeric_limits<uint32_t>::max())) {
        ConstElementPtr value = database_config->get("reconnect-wait-time");
        isc_throw(DhcpConfigError, "tcp-keepalive " << tcp_keepalive
                  << " must be in range 0...MAX_UINT32 (4294967295) "
                  << " (" << value->getPosition() << ")");
    }

    // 4. If all is OK, update the stored keyword/value pairs.  We do this by
    // swapping contents - values_copy is destroyed immediately after the
    // operation (when the method exits), so we are not interested in its new
    // value.
    values_.swap(values_copy);

    // 5. Save the database access string in the Configuration Manager.
    if (type_ == DBType::LEASE_DB) {
        cfg_db->setLeaseDbAccessString(getDbAccessString());
    } else if (type_ == DBType::HOSTS_DB) {
        cfg_db->setHostDbAccessString(getDbAccessString(), false);
    }
}

// Create the database access string
std::string
DbAccessParser::getDbAccessString() const {

    // Construct the database access string from all keywords and values in the
    // parameter map where the value is not null.
    string dbaccess;
    BOOST_FOREACH(StringPair keyval, values_) {
        if (!keyval.second.empty()) {

            // Separate keyword/value pair from predecessor (if there is one).
            if (!dbaccess.empty()) {
                dbaccess += std::string(" ");
            }

            // Add the keyword/value pair to the access string.
            dbaccess += (keyval.first + std::string("=") + keyval.second);
        }
    }

    return (dbaccess);
}

}  // namespace dhcp
}  // namespace isc
