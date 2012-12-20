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

#include <dhcp6/dbaccess_parser.h>

#include <boost/foreach.hpp>

#include <map>
#include <string>
#include <utility>

using namespace std;
using namespace isc::data;

namespace isc {
namespace dhcp {

/// @brief an auxiliary type used for storing an element name and its parser
typedef map<string, ConstElementPtr> ConfigPairMap;
typedef pair<string, ConstElementPtr> ConfigPair;

// Parse the configuration and check that the various keywords are consistent.
void
DbAccessParser::build(isc::data::ConstElementPtr config_value) {

    // All OK, build up the access string
    dbaccess_ = "";
    BOOST_FOREACH(ConfigPair param, config_value->mapValue()) {
        if (! dbaccess_.empty()) {
            dbaccess_ += std::string(" ");
        }
        dbaccess_ += (param.first + std::string("=") +
                      param.second->stringValue());
    }
}

// Commit the changes - reopen the database with the new parameters
void
DbAccessParser::commit() {
}

};  // namespace dhcp
};  // namespace isc

