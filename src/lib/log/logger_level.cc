// Copyright (C) 2011, 2015 Internet Systems Consortium, Inc. ("ISC")
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
// PERFORMANCE OF THIS SOFTWARE

#define KEA_LOG_EXPORT

#include <log/logger_level.h>
#include <log/macros.h>
#include <log/log_messages.h>

#include <boost/algorithm/string.hpp>


namespace isc {
namespace log {

KEA_LOG_API isc::log::Severity
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
