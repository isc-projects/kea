// Copyright (C) 2014-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <process/logging_info.h>
#include <process/daemon.h>
#include <log/logger_name.h>

using namespace isc::log;
using namespace isc::data;

namespace isc {
namespace process {

static const std::string STDOUT = "stdout";
static const std::string STDERR = "stderr";
static const std::string SYSLOG = "syslog";
static const std::string SYSLOG_COLON = "syslog:";

bool
LoggingDestination::equals(const LoggingDestination& other) const {
    return (output_ == other.output_ &&
            maxver_ == other.maxver_ &&
            maxsize_ == other.maxsize_ &&
            flush_ == other.flush_ &&
            pattern_ == other.pattern_);
}

ElementPtr
LoggingDestination::toElement() const {
    ElementPtr result = Element::createMap();

    // Set output
    result->set("output", Element::create(output_));

    // Set flush
    result->set("flush", Element::create(flush_));

    // Set pattern
    result->set("pattern", Element::create(pattern_));

    if ((output_ != STDOUT) && (output_ != STDERR) && (output_ != SYSLOG) &&
        (output_.find(SYSLOG_COLON) == std::string::npos)) {
        // Set maxver
        result->set("maxver", Element::create(maxver_));

        // Set maxsize
        result->set("maxsize", Element::create(static_cast<long long>(maxsize_)));
    }

    return (result);
}

LoggingInfo::LoggingInfo()
    : name_("kea"), severity_(isc::log::INFO), debuglevel_(0) {
    // If configuration Manager is in the verbose mode, we need to modify the
    // default settings.
    if (Daemon::getVerbose()) {
        severity_ = isc::log::DEBUG;
        debuglevel_ = 99;
    }

    // If the process has set the non-empty name for the default logger,
    // let's use this name.
    std::string default_logger = Daemon::getDefaultLoggerName();
    if (!default_logger.empty()) {
        name_ = default_logger;
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
    for (auto const& dest : destinations_) {
        bool match = false;
        for (auto const &dest_other : other.destinations_) {
            if (dest.equals(dest_other)) {
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
    LoggerSpecification spec(name_, severity_, debuglevel_);

    // Go over logger destinations and create output options accordingly.
    for (auto const& dest : destinations_) {
        OutputOption option;
        // Set up output option according to destination specification
        if (dest.output_ == STDOUT) {
            option.destination = OutputOption::DEST_CONSOLE;
            option.stream = OutputOption::STR_STDOUT;

        } else if (dest.output_ == STDERR) {
            option.destination = OutputOption::DEST_CONSOLE;
            option.stream = OutputOption::STR_STDERR;

        } else if (dest.output_ == SYSLOG) {
            option.destination = OutputOption::DEST_SYSLOG;
            // Use default specified in OutputOption constructor for the
            // syslog destination

        } else if (dest.output_.find(SYSLOG_COLON) == 0) {
            option.destination = OutputOption::DEST_SYSLOG;
            // Must take account of the string actually being "syslog:"
            if (dest.output_ == SYSLOG_COLON) {
                // The expected syntax is syslog:facility. User skipped
                // the logging name, so we'll just use the default ("kea")
                option.facility = isc::log::getDefaultRootLoggerName();

            } else {
                // Everything else in the string is the facility name
                option.facility = dest.output_.substr(SYSLOG_COLON.size());
            }

        } else {
            // Not a recognized destination, assume a file.
            option.destination = OutputOption::DEST_FILE;
            option.filename = dest.output_;
            option.maxsize = dest.maxsize_;
            option.maxver = dest.maxver_;
        }

        // Copy the immediate flush flag
        option.flush = dest.flush_;

        // Copy the pattern
        option.pattern = dest.pattern_;

        // ... and set the destination
        spec.addOutputOption(option);
    }

    return (spec);
}

ElementPtr
LoggingInfo::toElement() const {
    ElementPtr result = Element::createMap();
    // Set user context
    contextToElement(result);
    // Set name
    result->set("name", Element::create(name_));
    // Set output_options if not empty
    if (!destinations_.empty()) {
        ElementPtr options = Element::createList();
        for (auto const& dest : destinations_) {
            options->add(dest.toElement());
        }
        result->set("output_options", options);
    }
    // Set severity
    std::string severity;
    switch (severity_) {
    case isc::log::DEBUG:
        severity = "DEBUG";
        break;
    case isc::log::INFO:
        severity = "INFO";
        break;
    case isc::log::WARN:
        severity = "WARN";
        break;
    case isc::log::ERROR:
        severity = "ERROR";
        break;
    case isc::log::FATAL:
        severity = "FATAL";
        break;
    case isc::log::NONE:
        severity = "NONE";
        break;
    default:
        isc_throw(ToElementError, "illegal severity: " << severity_);
        break;
    }
    result->set("severity", Element::create(severity));
    // Set debug level
    result->set("debuglevel", Element::create(debuglevel_));

    return (result);
}

} // end of namespace isc::dhcp
} // end of namespace isc
