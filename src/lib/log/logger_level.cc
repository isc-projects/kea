// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <log/logger_level.h>
#include <log/macros.h>
#include <log/log_messages.h>

#include <boost/algorithm/string.hpp>


namespace isc {
namespace log {

isc::log::Severity
getSeverity(const std::string& sev_str) {
    if (boost::iequals(sev_str, "DEBUG")) {
        return isc::log::DEBUG;
    } else if (boost::iequals(sev_str, "INFO")) {
        return isc::log::INFO;
    } else if (boost::iequals(sev_str, "WARN")) {
        return isc::log::WARN;
    } else if (boost::iequals(sev_str, "ERROR")) {
        return isc::log::ERROR;
    } else if (boost::iequals(sev_str, "FATAL")) {
        return isc::log::FATAL;
    } else if (boost::iequals(sev_str, "NONE")) {
        return isc::log::NONE;
    } else {
        Logger logger("log");
        LOG_ERROR(logger, LOG_BAD_SEVERITY).arg(sev_str);
        return isc::log::INFO;
    }
}


} // namespace log
} // namespace isc
