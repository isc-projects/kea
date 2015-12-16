// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>

#include <boost/algorithm/string.hpp>

#include <log/log_messages.h>
#include <log/macros.h>
#include <log/output_option.h>

namespace isc {
namespace log {

OutputOption::Destination
getDestination(const std::string& dest_str) {
    if (boost::iequals(dest_str, "console")) {
        return OutputOption::DEST_CONSOLE;
    } else if (boost::iequals(dest_str, "file")) {
        return OutputOption::DEST_FILE;
    } else if (boost::iequals(dest_str, "syslog")) {
        return OutputOption::DEST_SYSLOG;
    } else {
        Logger logger("log");
        LOG_ERROR(logger, LOG_BAD_DESTINATION).arg(dest_str);
        return OutputOption::DEST_CONSOLE;
    }
}

OutputOption::Stream
getStream(const std::string& stream_str) {
    if (boost::iequals(stream_str, "stderr")) {
        return OutputOption::STR_STDERR;
    } else if (boost::iequals(stream_str, "stdout")) {
        return OutputOption::STR_STDOUT;
    } else {
        Logger logger("log");
        LOG_ERROR(logger, LOG_BAD_STREAM).arg(stream_str);
        return OutputOption::STR_STDOUT;
    }
}

} // namespace log
} // namespace isc
