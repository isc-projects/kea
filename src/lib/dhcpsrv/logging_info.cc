// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/logging_info.h>
#include <log/logger_name.h>

using namespace isc::log;

namespace isc {
namespace dhcp {

bool
LoggingDestination::equals(const LoggingDestination& other) const {
    return (output_ == other.output_ &&
            maxver_ == other.maxver_ &&
            maxsize_ == other.maxsize_ &&
            flush_ == other.flush_);
}

LoggingInfo::LoggingInfo()
    : name_("kea"), severity_(isc::log::INFO), debuglevel_(0) {
    // If configuration Manager is in the verbose mode, we need to modify the
    // default settings.
    if (CfgMgr::instance().isVerbose()) {
        severity_ = isc::log::DEBUG;
        debuglevel_ = 99;
    }

    // If the process has set the non-empty name for the default logger,
    // let's use this name.
    std::string logger_name = CfgMgr::instance().getDefaultLoggerName();
    if (!logger_name.empty()) {
        name_ = logger_name;
    }

    // Add a default logging destination in case use hasn't provided a
    // logger specification.
    LoggingDestination dest;
    dest.output_ = "stdout";
    destinations_.push_back(dest);
}

bool
LoggingInfo::equals(const LoggingInfo& other) const {
    // If number of destinations aren't equal, the objects are not equal.
    if (destinations_.size() != other.destinations_.size()) {
        return (false);
    }
    // If there is the same number of logging destinations verify that the
    // destinations are equal. The order doesn't matter to we don't expect
    // that they are at the same index of the vectors.
    for (std::vector<LoggingDestination>::const_iterator
             it_this = destinations_.begin();
         it_this != destinations_.end();
         ++it_this) {
        bool match = false;
        for (std::vector<LoggingDestination>::const_iterator
                 it_other = other.destinations_.begin();
             it_other != other.destinations_.end();
             ++it_other) {
            if (it_this->equals(*it_other)) {
                match = true;
                break;
            }
        }
        if (!match) {
            return (false);
        }
    }

    // Logging destinations are equal. Check the rest of the parameters for
    // equality.
    return (name_ == other.name_ &&
            severity_ == other.severity_ &&
            debuglevel_ == other.debuglevel_);
}

LoggerSpecification
LoggingInfo::toSpec() const {
    static const std::string STDOUT = "stdout";
    static const std::string STDERR = "stderr";
    static const std::string SYSLOG = "syslog";
    static const std::string SYSLOG_COLON = "syslog:";

    LoggerSpecification spec(name_, severity_, debuglevel_);

    // Go over logger destinations and create output options accordinly.
    for (std::vector<LoggingDestination>::const_iterator dest =
             destinations_.begin(); dest != destinations_.end(); ++dest) {

        OutputOption option;
        // Set up output option according to destination specification
        if (dest->output_ == STDOUT) {
            option.destination = OutputOption::DEST_CONSOLE;
            option.stream = OutputOption::STR_STDOUT;

        } else if (dest->output_ == STDERR) {
            option.destination = OutputOption::DEST_CONSOLE;
            option.stream = OutputOption::STR_STDERR;

        } else if (dest->output_ == SYSLOG) {
            option.destination = OutputOption::DEST_SYSLOG;
            // Use default specified in OutputOption constructor for the
            // syslog destination

        } else if (dest->output_.find(SYSLOG_COLON) == 0) {
            option.destination = OutputOption::DEST_SYSLOG;
            // Must take account of the string actually being "syslog:"
            if (dest->output_ == SYSLOG_COLON) {
                // The expected syntax is syslog:facility. User skipped
                // the logging name, so we'll just use the default ("kea")
                option.facility = isc::log::getDefaultRootLoggerName();

            } else {
                // Everything else in the string is the facility name
                option.facility = dest->output_.substr(SYSLOG_COLON.size());
            }

        } else {
            // Not a recognized destination, assume a file.
            option.destination = OutputOption::DEST_FILE;
            option.filename = dest->output_;
        }

        // Copy the immediate flush flag
        option.flush = dest->flush_;

        // ... and set the destination
        spec.addOutputOption(option);
    }

    return (spec);
}

} // end of namespace isc::dhcp
} // end of namespace isc
