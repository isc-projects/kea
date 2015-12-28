// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcpsrv/database_connection.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <exceptions/exceptions.h>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <vector>

using namespace std;

namespace isc {
namespace dhcp {

const time_t DatabaseConnection::MAX_DB_TIME = 2147483647;

std::string
DatabaseConnection::getParameter(const std::string& name) const {
    ParameterMap::const_iterator param = parameters_.find(name);
    if (param == parameters_.end()) {
        isc_throw(BadValue, "Parameter " << name << " not found");
    }
    return (param->second);
}

DatabaseConnection::ParameterMap
DatabaseConnection::parse(const std::string& dbaccess) {
    DatabaseConnection::ParameterMap mapped_tokens;

    if (!dbaccess.empty()) {
        vector<string> tokens;

        // We need to pass a string to is_any_of, not just char*. Otherwise
        // there are cryptic warnings on Debian6 running g++ 4.4 in
        // /usr/include/c++/4.4/bits/stl_algo.h:2178 "array subscript is above
        // array bounds"
        boost::split(tokens, dbaccess, boost::is_any_of(string("\t ")));
        BOOST_FOREACH(std::string token, tokens) {
            size_t pos = token.find("=");
            if (pos != string::npos) {
                string name = token.substr(0, pos);
                string value = token.substr(pos + 1);
                mapped_tokens.insert(make_pair(name, value));
            } else {
                LOG_ERROR(dhcpsrv_logger, DHCPSRV_INVALID_ACCESS).arg(dbaccess);
                isc_throw(InvalidParameter, "Cannot parse " << token
                          << ", expected format is name=value");
            }
        }
    }

    return (mapped_tokens);
}

std::string
DatabaseConnection::redactedAccessString(const ParameterMap& parameters) {
    // Reconstruct the access string: start of with an empty string, then
    // work through all the parameters in the original string and add them.
    std::string access;
    for (DatabaseConnection::ParameterMap::const_iterator i = parameters.begin();
         i != parameters.end(); ++i) {

        // Separate second and subsequent tokens are preceded by a space.
        if (!access.empty()) {
            access += " ";
        }

        // Append name of parameter...
        access += i->first;
        access += "=";

        // ... and the value, except in the case of the password, where a
        // redacted value is appended.
        if (i->first == std::string("password")) {
            access += "*****";
        } else {
            access += i->second;
        }
    }

    return (access);
}

};
};
