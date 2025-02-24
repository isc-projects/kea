// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <backend_store.h>
#include <backend_store_factory.h>

#include <database/database_connection.h>
#include <dhcpsrv/cfgmgr.h>
#include <eval/eval_context.h>
#include <util/reconnect_ctl.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <errno.h>
#include <iostream>
#include <sstream>
#include <time.h>

namespace isc {
namespace dhcp {

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::eval;
using namespace isc::hooks;
using namespace isc::util;
using namespace std;

void
BackendStore::parseConfig(const ConstElementPtr& parameters, DatabaseConnection::ParameterMap& map) {
    if (!parameters || !parameters->get("type") ||
        parameters->get("type")->stringValue() == "logfile") {
        parseFile(parameters, map);
    } else {
        parseDatabase(parameters, map);
    }
    parseExtraParameters(parameters, map);
}

void
BackendStore::parseDatabase(const ConstElementPtr& parameters, DatabaseConnection::ParameterMap& map) {
    // Should never happen with the code flow at the time of writing, but
    // let's get this check out of the way.
    if (!parameters) {
        isc_throw(BadValue, "no parameters specified for the hook library");
    }

    DatabaseConnection::ParameterMap db_parameters;

    // Strings
    for (char const* const& key : {
         "type", "user", "password", "host", "name", "trust-anchor",
         "cert-file", "key-file", "cipher-list" }) {
        ConstElementPtr const value(parameters->get(key));
        if (value) {
            db_parameters.emplace(key, value->stringValue());
        }
    }

    // uint32_t
    for (char const* const& key : {
         "connect-timeout", "reconnect-wait-time", "max-reconnect-tries"}) {
        ConstElementPtr const value(parameters->get(key));
        if (value) {
            int64_t integer_value(value->intValue());
            auto const max(numeric_limits<uint32_t>::max());
            if (integer_value < 0 || max < integer_value) {
                isc_throw(OutOfRange,
                          key << " value: " << integer_value
                              << " is out of range, expected value: 0.."
                              << max);
            }
            db_parameters[key] =
                boost::lexical_cast<string>(integer_value);
        }
    }

    string param_name = "tcp-nodelay";
    ConstElementPtr param = parameters->get(param_name);
    if (param) {
        db_parameters.emplace(param_name,
                              param->boolValue() ? "true" : "false");
    }

    // Always set "on-fail" to "serve-retry-continue" if not explicitly
    // configured.
    string on_fail_action = ReconnectCtl::onFailActionToText(OnFailAction::SERVE_RETRY_CONTINUE);
    param_name = "on-fail";
    param = parameters->get(param_name);
    if (param) {
        on_fail_action = param->stringValue();
        ReconnectCtl::onFailActionFromText(on_fail_action);
    }
    db_parameters.emplace(param_name, on_fail_action);

    param_name = "retry-on-startup";
    param = parameters->get(param_name);
    if (param) {
        db_parameters.emplace(param_name,
                              param->boolValue() ? "true" : "false");
    }

    int64_t port = 0;
    param_name = "port";
    param = parameters->get(param_name);
    if (param) {
        port = param->intValue();
        if ((port < 0) || (port > numeric_limits<uint16_t>::max())) {
            isc_throw(OutOfRange, param_name << " value: " << port
                      << " is out of range, expected value: 0.."
                      << numeric_limits<uint16_t>::max());
        }
        db_parameters.emplace(param_name,
                              boost::lexical_cast<string>(port));
    }

    string redacted =
        DatabaseConnection::redactedAccessString(db_parameters);

    string const db_type(db_parameters["type"]);
    map = db_parameters;
}

void
BackendStore::parseFile(const ConstElementPtr& parameters, DatabaseConnection::ParameterMap& map) {
    DatabaseConnection::ParameterMap file_parameters;
    file_parameters["type"] = "logfile";

    if (!parameters) {
        map = file_parameters;
        return;
    }

    // Strings
    for (char const* const& key : { "path", "base-name", "time-unit", "prerotate", "postrotate" }) {
        ConstElementPtr const value(parameters->get(key));
        if (value) {
            file_parameters.emplace(key, value->stringValue());
        }
    }

    // uint32_t
    for (char const* const& key : { "count" }) {
        ConstElementPtr const value(parameters->get(key));
        if (value) {
            int64_t integer_value(value->intValue());
            auto const max(numeric_limits<uint32_t>::max());
            if (integer_value < 0 || max < integer_value) {
                isc_throw(OutOfRange,
                          key << " value: " << integer_value
                              << " is out of range, expected value: 0.."
                              << max);
            }
            file_parameters[key] = boost::lexical_cast<string>(integer_value);
        }
    }
    map = file_parameters;
}

void
BackendStore::parseExtraParameters(const ConstElementPtr& parameters, DatabaseConnection::ParameterMap& map) {
    if (!parameters) {
        return;
    }

    // Strings
    for (char const* const& key : { "request-parser-format", "response-parser-format", "timestamp-format" }) {
        ConstElementPtr const value(parameters->get(key));
        if (value && !value->stringValue().empty()) {
            map.emplace(key, value->stringValue());
        }
    }
}

struct tm
BackendStore::currentTimeInfo() const {
    struct tm time_info;
    struct timespec timestamp = now();
    localtime_r(&timestamp.tv_sec, &time_info);
    return (time_info);
}

struct timespec
BackendStore::now() const {
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return (now);
}

string
BackendStore::getNowString() const {
    // Get a text representation of the current time.
    return (getNowString(timestamp_format_));
}

string
BackendStore::getNowString(const string& format) const {
    // Get a text representation of the current time.
    return (getTimeString(now(), format));
}

string
BackendStore::getTimeString(const struct timespec& time, const string& format) {
    // Get a text representation of the requested time.

    // First a quick and dirty support for fractional seconds: Replace any "%Q"
    // tokens in the format string with the microsecond count from the timespec,
    // before handing it off to strftime().
    string tmp_format = format;
    for (auto it = tmp_format.begin(); it < tmp_format.end(); ++it) {
        if (*it == '%' && ((it + 1) < tmp_format.end())) {
            if (*(it + 1) == 'Q') {
                // Save the current position.
                string::size_type pos = it - tmp_format.begin();
                // Render the microsecond count.
                ostringstream usec;
                usec << setw(6) << setfill('0') << (time.tv_nsec / 1000);
                string microseconds = usec.str();
                microseconds.insert(3, 1, '.');
                tmp_format.replace(it, it + 2, microseconds);
                // Reinitialize the iterator after manipulating the string.
                it = tmp_format.begin() + pos + microseconds.length() - 1;
            } else {
                ++it;
            }
        }
    }

    char buffer[128];
    struct tm time_info;
    localtime_r(&time.tv_sec, &time_info);

    if (!strftime(buffer, sizeof(buffer), tmp_format.c_str(), &time_info)) {
        isc_throw(BackendStoreError,
                  "strftime returned 0. Maybe the timestamp format '"
                      << tmp_format
                      << "' result is too long, maximum length allowed: "
                      << sizeof(buffer));
    }
    return (string(buffer));
}

string
BackendStore::genDurationString(const uint32_t secs) {
    // Because Kea handles lease lifetimes as uint32_t and supports
    // a value of 0xFFFFFFFF (infinite lifetime), we don't use things like
    // boost:posix_time::time_duration as they work on longs.  Therefore
    // we'll figure it out ourselves.  Besides, the math ain't that hard.
    if (secs == 0xffffffff) {
        return ("infinite duration");
    }

    uint32_t seconds = secs % 60;
    uint32_t remainder = secs / 60;
    uint32_t minutes = remainder % 60;
    remainder /= 60;
    uint32_t hours = remainder % 24;
    uint32_t days = remainder / 24;

    ostringstream os;
    // Only spit out days if we have em.
    if (days) {
        os << days << " days ";
    }

    os << hours << " hrs "
       << minutes << " mins "
       << seconds << " secs";

    return (os.str());
}

string
BackendStore::vectorHexDump(const vector<uint8_t>& bytes,
                         const string& delimiter) {
    stringstream tmp;
    tmp << hex;
    bool delim = false;
    for (auto const& it : bytes) {
        if (delim) {
            tmp << delimiter;
        }
        tmp << setw(2) << setfill('0') << static_cast<unsigned int>(it);
        delim = true;
    }
    return (tmp.str());
}

string
BackendStore::vectorDump(const vector<uint8_t>& bytes) {
    if (bytes.empty()) {
        return (string());
    }
    return (string(bytes.cbegin(), bytes.cend()));
}

void
BackendStore::setRequestFormatExpression(const string& extended_format) {
    Option::Universe universe;
    if (CfgMgr::instance().getFamily() == AF_INET) {
        universe = Option::V4;
    } else {
        universe = Option::V6;
    }
    EvalContext eval_ctx(universe);
    eval_ctx.parseString(extended_format, EvalContext::PARSER_STRING);
    request_expression_.reset(new Expression(eval_ctx.expression_));
}

void
BackendStore::setResponseFormatExpression(const string& extended_format) {
    Option::Universe universe;
    if (CfgMgr::instance().getFamily() == AF_INET) {
        universe = Option::V4;
    } else {
        universe = Option::V6;
    }
    EvalContext eval_ctx(universe);
    eval_ctx.parseString(extended_format, EvalContext::PARSER_STRING);
    response_expression_.reset(new Expression(eval_ctx.expression_));
}

void
BackendStore::setTimestampFormat(const string& timestamp_format) {
    timestamp_format_ = timestamp_format;
}

const string
actionToVerb(Action action) {
    switch (action) {
    case Action::ASSIGN:
        return ("assigned");
    case Action::RELEASE:
        return ("released");
    default:
        return ("unknown-action");
    }
}

} // namespace dhcp
} // namespace isc
