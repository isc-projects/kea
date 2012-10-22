// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include "config.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <utility>

#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <exceptions/exceptions.h>
#include <dhcp/lease_mgr_factory.h>

#ifdef HAVE_MYSQL
#include <dhcp/mysql_lease_mgr.h>
#endif

using namespace std;

namespace isc {
namespace dhcp {

LeaseMgr::ParameterMap
LeaseMgrFactory::parse(const std::string& dbconfig) {
    LeaseMgr::ParameterMap mapped_tokens;

    if (! dbconfig.empty()) {
        vector<string> tokens;

        // We need to pass a string to is_any_of, not just char*. Otherwise
        // there are cryptic warnings on Debian6 running g++ 4.4 in
        // /usr/include/c++/4.4/bits/stl_algo.h:2178 "array subscript is above
        // array bounds"
        boost::split(tokens, dbconfig, boost::is_any_of( string("\t ") ));
        BOOST_FOREACH(std::string token, tokens) {
            size_t pos = token.find("=");
            if (pos != string::npos) {
                string name = token.substr(0, pos);
                string value = token.substr(pos + 1);
                mapped_tokens.insert(make_pair(name, value));
            } else {
                isc_throw(InvalidParameter, "Cannot parse " << token
                          << ", expected format is name=value");
            }
        }
    }

    return (mapped_tokens);
}

LeaseMgrPtr
LeaseMgrFactory::create(const std::string& dbconfig) {
    const std::string type = "type";

    // Is "type" present?
    LeaseMgr::ParameterMap parameters = parse(dbconfig);
    if (parameters.find(type) == parameters.end()) {
        isc_throw(InvalidParameter, "Database configuration parameters do not "
                  "contain the 'type' keyword");
    }

    // Yes, check what it is.
#ifdef HAVE_MYSQL
    if (parameters[type] == string("mysql")) {
        return LeaseMgrPtr(new MySqlLeaseMgr(parameters));
    }
#endif

    // Get here on no match
    isc_throw(InvalidParameter, "Database configuration parameter 'type' does "
              "not specify a supported database backend");
}

}; // namespace dhcp
}; // namespace isc
