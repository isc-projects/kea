// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <legal_log_log.h>
#include <backend_store.h>

#include <rotating_file.h>
#ifdef HAVE_MYSQL
#include <mysql_legal_log.h>
#endif
#ifdef HAVE_PGSQL
#include <pgsql_legal_log.h>
#endif

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
namespace legal_log {

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::eval;
using namespace isc::hooks;
using namespace isc::util;


void
BackendStore::parseFile(const ConstElementPtr& parameters) {
    // Defaults
    std::string path(LEGAL_LOG_DIR);
    std::string base("kea-legal");
    RotatingFile::TimeUnit unit(RotatingFile::TimeUnit::Day);
    int64_t count(1);
    std::string prerotate;
    std::string postrotate;

    // Prioritize parameters.
    if (parameters) {
        if (parameters->get("path")) {
            path = parameters->get("path")->stringValue();
        }
        if (parameters->get("base-name")) {
            base = parameters->get("base-name")->stringValue();
        }
        if (parameters->get("time-unit")) {
            std::string time_unit(parameters->get("time-unit")->stringValue());
            if (time_unit == "second") {
                unit = RotatingFile::TimeUnit::Second;
            } else if (time_unit == "day") {
                unit = RotatingFile::TimeUnit::Day;
            } else if (time_unit == "month") {
                unit = RotatingFile::TimeUnit::Month;
            } else if (time_unit == "year") {
                unit = RotatingFile::TimeUnit::Year;
            } else {
                isc_throw(BadValue, "unknown time unit type: " << time_unit
                            << ", expected one of: second, day, month, year");
            }
        }
        if (parameters->get("count")) {
            count = parameters->get("count")->intValue();
            if ((count < 0) ||
                (count > std::numeric_limits<uint32_t>::max())) {
                isc_throw(OutOfRange, "count value: " << count
                        << " is out of range, expected value: 0.."
                        << std::numeric_limits<uint32_t>::max());
            }
        }
        if (parameters->get("prerotate")) {
            prerotate = parameters->get("prerotate")->stringValue();
        }
        if (parameters->get("postrotate")) {
            postrotate = parameters->get("postrotate")->stringValue();
        }
    }

    BackendStore::instance() = boost::make_shared<RotatingFile>(
        path, base, unit, count, prerotate, postrotate);

    DatabaseConnection::ParameterMap db_parameters;
    db_parameters.emplace("path", path);
    db_parameters.emplace("base-name", base);
    BackendStore::setParameters(db_parameters);
}

void
BackendStore::parseDatabase(const ConstElementPtr& parameters) {
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
            auto const max(std::numeric_limits<uint32_t>::max());
            if (integer_value < 0 || max < integer_value) {
                isc_throw(OutOfRange,
                          key << " value: " << integer_value
                              << " is out of range, expected value: 0.."
                              << max);
            }
            db_parameters[key] =
                boost::lexical_cast<std::string>(integer_value);
        }
    }

    std::string param_name = "tcp-nodelay";
    ConstElementPtr param = parameters->get(param_name);
    if (param) {
        db_parameters.emplace(param_name,
                              param->boolValue() ? "true" : "false");
    }

    // Always set "on-fail" to "serve-retry-continue" if not explicitly
    // configured.
    std::string on_fail_action = ReconnectCtl::onFailActionToText(OnFailAction::SERVE_RETRY_CONTINUE);
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
        if ((port < 0) || (port > std::numeric_limits<uint16_t>::max())) {
            isc_throw(OutOfRange, param_name << " value: " << port
                      << " is out of range, expected value: 0.."
                      << std::numeric_limits<uint16_t>::max());
        }
        db_parameters.emplace(param_name,
                              boost::lexical_cast<std::string>(port));
    }

    std::string redacted =
        DatabaseConnection::redactedAccessString(db_parameters);

    std::string const dbtype(db_parameters["type"]);
#ifdef HAVE_MYSQL
    if (dbtype == "mysql") {
        LOG_INFO(legal_log_logger, LEGAL_LOG_MYSQL_DB).arg(redacted);
        BackendStore::instance().reset(new MySqlStore(db_parameters));
        return;
    }
#endif
#ifdef HAVE_PGSQL
    if (dbtype == "postgresql") {
        LOG_INFO(legal_log_logger, LEGAL_LOG_PGSQL_DB).arg(redacted);
        BackendStore::instance().reset(new PgSqlStore(db_parameters));
        return;
    }
#endif

    if ((dbtype == "mysql") || (dbtype == "postgresql")) {
        std::string with = (dbtype == "postgresql" ? "pgsql" : dbtype);
        isc_throw(InvalidType, "The Kea server has not been compiled with "
                  "support for database type: " << dbtype
                  << ". Did you forget to use --with-"
                  << with << " during compilation?");
    }

    isc_throw(InvalidType, "Database access parameter 'type' does "
              "not specify a supported database backend: " << dbtype);
}

void
BackendStore::parseExtraParameters(const ConstElementPtr& parameters) {
    if (!parameters) {
        return;
    }

    ConstElementPtr param = parameters->get("request-parser-format");
    if (param && !param->stringValue().empty()) {
        BackendStore::instance()->setRequestFormatExpression(param->stringValue());
    }

    param = parameters->get("response-parser-format");
    if (param && !param->stringValue().empty()) {
        BackendStore::instance()->setResponseFormatExpression(param->stringValue());
    }

    param = parameters->get("timestamp-format");
    if (param && !param->stringValue().empty()) {
        BackendStore::instance()->setTimestampFormat(param->stringValue());
    }
}

IOServicePtr BackendStore::io_service_;
DatabaseConnection::ParameterMap BackendStore::parameters_;
ConstElementPtr BackendStore::config_;

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

std::string
BackendStore::getNowString() const {
    // Get a text representation of the current time.
    return (getNowString(timestamp_format_));
}

std::string
BackendStore::getNowString(const std::string& format) const {
    // Get a text representation of the current time.
    return (getTimeString(now(), format));
}

std::string
BackendStore::getTimeString(const struct timespec& time, const std::string& format) {
    // Get a text representation of the requested time.

    // First a quick and dirty support for fractional seconds: Replace any "%Q"
    // tokens in the format string with the microsecond count from the timespec,
    // before handing it off to strftime().
    std::string tmp_format = format;
    for (auto it = tmp_format.begin(); it < tmp_format.end(); ++it) {
        if (*it == '%' && ((it + 1) < tmp_format.end())) {
            if (*(it + 1) == 'Q') {
                // Save the current position.
                std::string::size_type pos = it - tmp_format.begin();
                // Render the microsecond count.
                std::ostringstream usec;
                usec << std::setw(6) << std::setfill('0') << (time.tv_nsec / 1000);
                std::string microseconds = usec.str();
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
    return (std::string(buffer));
}

std::string
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

    std::ostringstream os;
    // Only spit out days if we have em.
    if (days) {
        os << days << " days ";
    }

    os << hours << " hrs "
       << minutes << " mins "
       << seconds << " secs";

    return (os.str());
}

std::string
BackendStore::vectorHexDump(const std::vector<uint8_t>& bytes,
                         const std::string& delimiter) {
    std::stringstream tmp;
    tmp << std::hex;
    bool delim = false;
    for (auto const& it : bytes) {
        if (delim) {
            tmp << delimiter;
        }
        tmp << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(it);
        delim = true;
    }
    return (tmp.str());
}

std::string
BackendStore::vectorDump(const std::vector<uint8_t>& bytes) {
    if (bytes.empty()) {
        return (std::string());
    }
    return (std::string(bytes.cbegin(), bytes.cend()));
}

void
BackendStore::setRequestFormatExpression(const std::string& extended_format) {
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
BackendStore::setResponseFormatExpression(const std::string& extended_format) {
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
BackendStore::setTimestampFormat(const std::string& timestamp_format) {
    timestamp_format_ = timestamp_format;
}

const std::string
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

} // namespace legal_log
} // namespace isc
