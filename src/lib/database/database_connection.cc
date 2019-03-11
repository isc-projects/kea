// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/cfg_to_element.h>
#include <database/database_connection.h>
#include <database/db_exceptions.h>
#include <database/db_log.h>
#include <database/db_messages.h>
#include <exceptions/exceptions.h>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <vector>

using namespace std;

namespace isc {
namespace db {

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
                DB_LOG_ERROR(DB_INVALID_ACCESS).arg(dbaccess);
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

bool
DatabaseConnection::configuredReadOnly() const {
    std::string readonly_value = "false";
    try {
        readonly_value = getParameter("readonly");
        boost::algorithm::to_lower(readonly_value);
    } catch (...) {
        // Parameter "readonly" hasn't been specified so we simply use
        // the default value of "false".
    }

    if ((readonly_value != "false") && (readonly_value != "true")) {
        isc_throw(DbInvalidReadOnly, "invalid value '" << readonly_value
                  << "' specified for boolean parameter 'readonly'");
    }

    return (readonly_value == "true");
}

ReconnectCtlPtr
DatabaseConnection::makeReconnectCtl() const {
    ReconnectCtlPtr retry;
    string type = "unknown";
    unsigned int retries = 0;
    unsigned int interval = 0;

    // Assumes that parsing ensurse only valid values are present
    try {
        type = getParameter("type");
    } catch (...) {
        // Wasn't specified so we'll use default of "unknown".
    }

    std::string parm_str;
    try {
        parm_str = getParameter("max-reconnect-tries");
        retries = boost::lexical_cast<unsigned int>(parm_str);
    } catch (...) {
        // Wasn't specified so we'll use default of 0;
    }

    try {
        parm_str = getParameter("reconnect-wait-time");
        interval = boost::lexical_cast<unsigned int>(parm_str);
    } catch (...) {
        // Wasn't specified so we'll use default of 0;
    }

    retry.reset(new ReconnectCtl(type, retries, interval));
    return (retry);
}

bool
DatabaseConnection::invokeDbLostCallback() const {
    if (DatabaseConnection::db_lost_callback) {
        // Invoke the callback, passing in a new instance of ReconnectCtl
        return (DatabaseConnection::db_lost_callback)(makeReconnectCtl());
    }

    return (false);
}

isc::data::ElementPtr
DatabaseConnection::toElement(const ParameterMap& params) {
    isc::data::ElementPtr result = isc::data::Element::createMap();

    for (auto param: params) {
        std::string keyword = param.first;
        std::string value = param.second;

        if ((keyword == "lfc-interval") ||
            (keyword == "connect-timeout") ||
            (keyword == "reconnect-wait-time") ||
            (keyword == "max-reconnect-tries") ||
            (keyword == "request-timeout") ||
            (keyword == "tcp-keepalive") ||
            (keyword == "port")) {
            // integer parameters
            int64_t int_value;
            try {
                int_value = boost::lexical_cast<int64_t>(value);
                result->set(keyword, isc::data::Element::create(int_value));
            } catch (...) {
                LOG_ERROR(database_logger, DATABASE_TO_JSON_ERROR)
                    .arg("integer").arg(keyword).arg(value);
            }
        } else if ((keyword == "persist") ||
                   (keyword == "tcp-nodelay") ||
                   (keyword == "readonly")) {
            if (value == "true") {
                result->set(keyword, isc::data::Element::create(true));
            } else if (value == "false") {
                result->set(keyword, isc::data::Element::create(false));
            } else {
                LOG_ERROR(database_logger, DATABASE_TO_JSON_ERROR)
                    .arg("boolean").arg(keyword).arg(value);
            }
        } else if ((keyword == "type") ||
                   (keyword == "user") ||
                   (keyword == "password") ||
                   (keyword == "host") ||
                   (keyword == "name") ||
                   (keyword == "contact-points") ||
                   (keyword == "consistency") ||
                   (keyword == "serial-consistency") ||
                   (keyword == "keyspace")) {
            result->set(keyword, isc::data::Element::create(value));
        } else {
            LOG_ERROR(database_logger, DATABASE_TO_JSON_ERROR)
                    .arg("unknown").arg(keyword).arg(value);
        }
    }

    return (result);
}

isc::data::ElementPtr
DatabaseConnection::toElementDbAccessString(const std::string& dbaccess) {
    ParameterMap params = parse(dbaccess);
    return (toElement(params));
}

DatabaseConnection::DbLostCallback
DatabaseConnection::db_lost_callback = 0;

};
};
