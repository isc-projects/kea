// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
