// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>
#include <log/logger_name.h>

namespace isc {
namespace log {

namespace {

// Obtain the root logger name in a way that is safe for statically-initialized
// objects.

std::string&
getRootLoggerNameInternal() {
    static std::string root_name;
    return (root_name);
}

} // Anonymous namespace

void
setRootLoggerName(const std::string& name) {
    getRootLoggerNameInternal() = name;
}

const std::string& getRootLoggerName() {
    return (getRootLoggerNameInternal());
}

const std::string& getDefaultRootLoggerName() {
    static std::string root_name("kea");
    return (root_name);
}

std::string expandLoggerName(const std::string& name) {

    // Are we the root logger, or does the logger name start with
    // the string "<root_logger_name>.".  If so, use a logger
    // whose name is the one given.
    if ((name == getRootLoggerName()) ||
        (name.find(getRootLoggerName() + std::string(".")) == 0)) {
        return (name);

    } 

    // Anything else is assumed to be a sub-logger of the root logger.
    return (getRootLoggerName() + "." + name);
}

} // namespace log
} // namespace isc
