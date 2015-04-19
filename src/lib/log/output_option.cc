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
// PERFORMANCE OF THIS SOFTWARE.

#define KEA_LOG_EXPORT

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
