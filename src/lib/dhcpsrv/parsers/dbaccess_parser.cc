// Copyright (C) 2012-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/option.h>
#include <dhcpsrv/cfg_db_access.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/parsers/dbaccess_parser.h>

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
DbAccessParser::DbAccessParser(const std::string&, DBType db_type)
    : values_(), type_(db_type) {
}

// Parse the configuration and check that the various keywords are consistent.
void
DbAccessParser::build(isc::data::ConstElementPtr config_value) {

    // To cope with incremental updates, the strategy is:
    // 1. Take a copy of the stored keyword/value pairs.
    // 2. Update the copy with the passed keywords.
    // 3. Perform validation checks on the updated keyword/value pairs.
    // 4. If all is OK, update the stored keyword/value pairs.
    // 5. Save resulting database access string in the Configuration
    // Manager.

    // 1. Take a copy of the stored keyword/value pairs.
    std::map<string, string> values_copy = values_;

    int64_t lfc_interval = 0;
    // 2. Update the copy with the passed keywords.
    BOOST_FOREACH(ConfigPair param, config_value->mapValue()) {
        try {
            if (param.first == "persist") {
                values_copy[param.first] = (param.second->boolValue() ?
                                            "true" : "false");

            } else if (param.first == "lfc-interval") {
                lfc_interval = param.second->intValue();
                values_copy[param.first] =
                    boost::lexical_cast<std::string>(lfc_interval);

            } else {
                values_copy[param.first] = param.second->stringValue();
            }
        } catch (const isc::data::TypeError& ex) {
            // Append position of the element.
            isc_throw(isc::data::TypeError, ex.what() << " ("
                      << param.second->getPosition() << ")");
        }
    }

    // 3. Perform validation checks on the updated set of keyword/values.
    //
    // a. Check if the "type" keyword exists and thrown an exception if not.
    StringPairMap::const_iterator type_ptr = values_copy.find("type");
    if (type_ptr == values_copy.end()) {
        isc_throw(TypeKeywordMissing, "lease database access parameters must "
                  "include the keyword 'type' to determine type of database "
                  "to be accessed (" << config_value->getPosition() << ")");
    }

    // b. Check if the 'type' keyword known and throw an exception if not.
    string dbtype = type_ptr->second;
    if ((dbtype != "memfile") && (dbtype != "mysql") && (dbtype != "postgresql")) {
        isc_throw(BadValue, "unknown backend database type: " << dbtype
                  << " (" << config_value->getPosition() << ")");
    }

    // c. Check that the lfc-interval is a number and it is within a resonable
    // range.
    if ((lfc_interval < 0) || (lfc_interval > std::numeric_limits<uint32_t>::max())) {
        isc_throw(BadValue, "lfc-interval value: " << lfc_interval
                  << " is out of range, expected value: 0.."
                  << std::numeric_limits<uint32_t>::max());
    }

    // 4. If all is OK, update the stored keyword/value pairs.  We do this by
    // swapping contents - values_copy is destroyed immediately after the
    // operation (when the method exits), so we are not interested in its new
    // value.
    values_.swap(values_copy);

    // 5. Save the database access string in the Configuration Manager.
    CfgDbAccessPtr cfg_db = CfgMgr::instance().getStagingCfg()->getCfgDbAccess();
    if (type_ == LEASE_DB) {
        cfg_db->setLeaseDbAccessString(getDbAccessString());

    } else {
        cfg_db->setHostDbAccessString(getDbAccessString());
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

// Commit the changes - reopen the database with the new parameters
void
DbAccessParser::commit() {
}

};  // namespace dhcp
};  // namespace isc

