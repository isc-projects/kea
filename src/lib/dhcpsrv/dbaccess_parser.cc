// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <dhcpsrv/dbaccess_parser.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/lease_mgr_factory.h>

#include <boost/foreach.hpp>

#include <map>
#include <string>
#include <utility>

using namespace std;
using namespace isc::data;

namespace isc {
namespace dhcp {


// Factory function to build the parser
DbAccessParser::DbAccessParser(const std::string& param_name) : values_()
{
    if (param_name != "lease-database") {
        LOG_WARN(dhcpsrv_logger, DHCPSRV_UNEXPECTED_NAME).arg(param_name);
    }
}

// Parse the configuration and check that the various keywords are consistent.
void
DbAccessParser::build(isc::data::ConstElementPtr config_value) {

    // To cope with incremental updates, the strategy is:
    // 1. Take a copy of the stored keyword/value pairs.
    // 2. Update the copy with the passed keywords.
    // 3. Perform validation checks on the updated keyword/value pairs.
    // 4. If all is OK, update the stored keyword/value pairs.
    // 5. Construct the updated database access string.

    // 1. Take a copy of the stored keyword/value pairs.
    map<string, string> values_copy = values_;

    // 2. Update the copy with the passed keywords.
    BOOST_FOREACH(DbAccessParser::ConfigPair param, config_value->mapValue()) {
        values_copy[param.first] = param.second->stringValue();
    }

    // 3. Perform validation checks on the updated set of keyword/values.
    //
    // a. Check if the "type" keyword exists and thrown an exception if not.
    StringPairMap::const_iterator type_ptr = values_copy.find("type");
    if (type_ptr == values_copy.end()) {
        isc_throw(TypeKeywordMissing, "lease database access parameters must "
                  "include the keyword 'type' to determine type of database "
                  "to be accessed");
    }

    // b. Check if the 'type; keyword known and throw an exception if not.
    string dbtype = type_ptr->second;
    if ((dbtype != "memfile") && (dbtype != "mysql")) {
        isc_throw(BadValue, "unknown backend database type: " << dbtype);
    }

    /// @todo Log a warning if the type is memfile and there are other keywords.
    ///       This will be done when the module is moved to libdhcpsrv

    // 4. If all is OK, update the stored keyword/value pairs.
    values_ = values_copy;
}

// Commit the changes - reopen the database with the new parameters
void
DbAccessParser::commit() {
    // Close current lease manager.
    LeaseMgrFactory::destroy();

    // Construct the database access string from all keywords and values in the
    // parameter map where the value is not null.
    string dbaccess;
    BOOST_FOREACH(StringPair keyval, values_) {
        if (!keyval.second.empty()) {

            // Separate keyword/value pair from predecessor (if there is one).
            if (! dbaccess.empty()) {
                dbaccess += std::string(" ");
            }

            // Add the keyword/value pair to the access string.
            dbaccess += (keyval.first + std::string("=") + keyval.second);
        }
    }

    // ... and open the database using that access string.
    LeaseMgrFactory::create(dbaccess);
}

};  // namespace dhcp
};  // namespace isc

