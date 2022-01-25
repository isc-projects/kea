// Copyright (C) 2015-2022 Internet Systems Consortium, Inc. ("ISC")
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
#include <util/strutil.h>

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
    std::string dba = dbaccess;

    if (!dba.empty()) {
        try {
            vector<string> tokens;

            // Handle the special case of a password which is enclosed in apostrophes.
            // Such password may include whitespace.
            std::string password_prefix = "password='";
            auto password_pos = dba.find(password_prefix);
            if (password_pos != string::npos) {
                // Password starts with apostrophe, so let's find ending apostrophe.
                auto password_end_pos = dba.find('\'', password_pos + password_prefix.length());
                if (password_end_pos == string::npos) {
                    // No ending apostrophe. This is wrong.
                    isc_throw(InvalidParameter, "Apostrophe (') expected at the end of password");
                }
                // Extract the password value. It starts after the password=' prefix and ends
                // at the position of ending apostrophe.
                auto password = dba.substr(password_pos + password_prefix.length(),
                                           password_end_pos - password_pos - password_prefix.length());
                mapped_tokens.insert(make_pair("password", password));

                // We need to erase the password from the access string because the generic
                // algorithm parsing other parameters requires that there are no whitespaces
                // within the parameter values.
                dba.erase(password_pos, password_prefix.length() + password.length() + 2);
                // Leading or trailing whitespace may remain after the password removal.
                dba = util::str::trim(dba);
                // If the password was the only parameter in the access string, there is
                // nothing more to do.
                if (dba.empty()) {
                    return (mapped_tokens);
                }
            }

            // We need to pass a string to is_any_of, not just char*. Otherwise
            // there are cryptic warnings on Debian6 running g++ 4.4 in
            // /usr/include/c++/4.4/bits/stl_algo.h:2178 "array subscript is above
            // array bounds"
            boost::split(tokens, dba, boost::is_any_of(string("\t ")));
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
        } catch (const std::exception& ex) {
            // We'd obscure the password if we could parse the access string.
            DB_LOG_ERROR(DB_INVALID_ACCESS).arg(dbaccess);
            throw;
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

void
DatabaseConnection::makeReconnectCtl(const std::string& timer_name) {
    string type = "unknown";
    unsigned int retries = 0;
    unsigned int interval = 0;

    // Assumes that parsing ensures only valid values are present
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

    OnFailAction action = OnFailAction::STOP_RETRY_EXIT;
    try {
        parm_str = getParameter("on-fail");
        action = ReconnectCtl::onFailActionFromText(parm_str);
    } catch (...) {
        // Wasn't specified so we'll use default of "stop-retry-exit";
    }

    reconnect_ctl_ = boost::make_shared<ReconnectCtl>(type, timer_name, retries,
                                                      interval, action);
}

bool
DatabaseConnection::invokeDbLostCallback(const ReconnectCtlPtr& db_reconnect_ctl) {
    if (DatabaseConnection::db_lost_callback_) {
        return (DatabaseConnection::db_lost_callback_(db_reconnect_ctl));
    }

    return (false);
}

bool
DatabaseConnection::invokeDbRecoveredCallback(const ReconnectCtlPtr& db_reconnect_ctl) {
    if (DatabaseConnection::db_recovered_callback_) {
        return (DatabaseConnection::db_recovered_callback_(db_reconnect_ctl));
    }

    return (false);
}

bool
DatabaseConnection::invokeDbFailedCallback(const ReconnectCtlPtr& db_reconnect_ctl) {
    if (DatabaseConnection::db_failed_callback_) {
        return (DatabaseConnection::db_failed_callback_(db_reconnect_ctl));
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
            (keyword == "port") ||
            (keyword == "max-row-errors")) {
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
                   (keyword == "keyspace") ||
                   (keyword == "on-fail") ||
                   (keyword == "trust-anchor") ||
                   (keyword == "cert-file") ||
                   (keyword == "key-file") ||
                   (keyword == "cipher-list")) {
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

std::string
ReconnectCtl::onFailActionToText(OnFailAction action) {
    switch (action) {
    case OnFailAction::STOP_RETRY_EXIT:
        return ("stop-retry-exit");
    case OnFailAction::SERVE_RETRY_EXIT:
        return ("serve-retry-exit");
    case OnFailAction::SERVE_RETRY_CONTINUE:
        return ("serve-retry-continue");
    }
    return ("invalid-action-type");
}

OnFailAction
ReconnectCtl::onFailActionFromText(const std::string& text) {
    if (text == "stop-retry-exit") {
        return (OnFailAction::STOP_RETRY_EXIT);
    } else if (text == "serve-retry-exit") {
        return (OnFailAction::SERVE_RETRY_EXIT);
    } else if (text == "serve-retry-continue") {
        return (OnFailAction::SERVE_RETRY_CONTINUE);
    } else {
        isc_throw(BadValue, "Invalid action on connection loss: " << text);
    }
}

DbCallback DatabaseConnection::db_lost_callback_ = 0;
DbCallback DatabaseConnection::db_recovered_callback_ = 0;
DbCallback DatabaseConnection::db_failed_callback_ = 0;

}  // namespace db
}  // namespace isc
