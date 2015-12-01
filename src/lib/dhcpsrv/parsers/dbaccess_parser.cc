// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <dhcp/option.h>
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
DbAccessParser::DbAccessParser(const std::string&, DBType db_type,
                               const ParserContext& ctx)
    : values_(), type_(db_type), ctx_(ctx)
{
}

// Parse the configuration and check that the various keywords are consistent.
void
DbAccessParser::build(isc::data::ConstElementPtr config_value) {

    // To cope with incremental updates, the strategy is:
    // 1. Take a copy of the stored keyword/value pairs.
    // 2. Inject the universe parameter.
    // 3. Update the copy with the passed keywords.
    // 4. Perform validation checks on the updated keyword/value pairs.
    // 5. If all is OK, update the stored keyword/value pairs.

    // 1. Take a copy of the stored keyword/value pairs.
    std::map<string, string> values_copy = values_;

    // 2. Inject the parameter which defines whether we are configuring
    // DHCPv4 or DHCPv6. Some database backends (e.g. Memfile make
    // use of it).
    values_copy["universe"] = ctx_.universe_ == Option::V4 ? "4" : "6";

    int64_t lfc_interval = 0;
    // 3. Update the copy with the passed keywords.
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

    // 4. Perform validation checks on the updated set of keyword/values.
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

    // 5. If all is OK, update the stored keyword/value pairs.  We do this by
    // swapping contents - values_copy is destroyed immediately after the
    // operation (when the method exits), so we are not interested in its new
    // value.
    values_.swap(values_copy);
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

    switch (type_) {
    case LEASE_DB:
    {
        // Close current lease manager database.
        LeaseMgrFactory::destroy();

        // ... and open the new database using the access string.
        LeaseMgrFactory::create(getDbAccessString());
        break;
    }
    case HOSTS_DB:
    {
        // Let's instantiate HostMgr with new parameters. Note that HostMgr's
        // create method will call HostDataSourceFactory::create() with
        // appropriate parameters. It will also destroy a pre-existing
        // instance, if it existed.
        HostMgr::create(getDbAccessString());
        break;
    }
    default:
        isc_throw(BadValue, "Incorrect type specified in DbAccessParser: "
                  << type_);
    };
}

};  // namespace dhcp
};  // namespace isc

