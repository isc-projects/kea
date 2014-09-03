// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <cc/data.h>
#include <dhcpsrv/logging.h>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <log/logger_specification.h>
#include <log/logger_manager.h>
#include <log/logger_name.h>

using namespace isc::data;
using namespace isc::log;

namespace isc {
namespace dhcp {

LogConfigParser::LogConfigParser(const ConfigurationPtr& storage)
    :config_(storage), verbose_(false) {
    if (!storage) {
        isc_throw(BadValue, "LogConfigParser needs a pointer to the "
                  "configuration, so parsed data can be stored there");
    }
}

void LogConfigParser::parseConfiguration(const isc::data::ConstElementPtr& loggers,
                                         bool verbose) {
    verbose_ = verbose;

    // Iterate over all entries in "Logging/loggers" list
    BOOST_FOREACH(ConstElementPtr logger, loggers->listValue()) {
        parseConfigEntry(logger);
    }
}

void LogConfigParser::parseConfigEntry(isc::data::ConstElementPtr entry) {
    if (!entry) {
        // This should not happen, but let's be on the safe side and check
        return;
    }

    if (!config_) {
        isc_throw(BadValue, "configuration storage not set, can't parse logger config.");
    }

    LoggingInfo info;
    // Remove default destinations as we are going to replace them.
    info.clearDestinations();

    // Get a name
    isc::data::ConstElementPtr name_ptr = entry->get("name");
    if (!name_ptr) {
        isc_throw(BadValue, "loggers entry does not have a mandatory 'name' "
                  "element (" << entry->getPosition() << ")");
    }
    info.name_ = name_ptr->stringValue();

    // Get severity
    isc::data::ConstElementPtr severity_ptr = entry->get("severity");
    if (!name_ptr) {
        isc_throw(BadValue, "loggers entry does not have a mandatory "
                  "'severity' element (" << entry->getPosition() << ")");
    }
    try {
        info.severity_ = isc::log::getSeverity(severity_ptr->stringValue().c_str());
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "Unsupported severity value '"
                  << severity_ptr->stringValue() << "' ("
                  << severity_ptr->getPosition() << ")");
    }

    // Get debug logging level
    info.debuglevel_ = 0;
    isc::data::ConstElementPtr debuglevel_ptr = entry->get("debuglevel");

    // It's ok to not have debuglevel, we'll just assume its least verbose
    // (0) level.
    if (debuglevel_ptr) {
        try {
            info.debuglevel_ = boost::lexical_cast<int>(debuglevel_ptr->str());
            if ( (info.debuglevel_ < 0) || (info.debuglevel_ > 99) ) {
                // Comment doesn't matter, it is caught several lines below
                isc_throw(BadValue, "");
            }
        } catch (...) {
            isc_throw(BadValue, "Unsupported debuglevel value '"
                      << debuglevel_ptr->stringValue()
                      << "', expected 0-99 ("
                      << debuglevel_ptr->getPosition() << ")");
        }
    }

    // We want to follow the normal path, so it could catch parsing errors even
    // when verbose mode is enabled. If it is, just override whatever was parsed
    // in the config file.
    if (verbose_) {
        info.severity_ = isc::log::DEBUG;
        info.debuglevel_ = 99;
    }

    isc::data::ConstElementPtr output_options = entry->get("output_options");

    if (output_options) {
        parseOutputOptions(info.destinations_, output_options);
    }
    
    config_->addLoggingInfo(info);
}

void LogConfigParser::parseOutputOptions(std::vector<LoggingDestination>& destination,
                                         isc::data::ConstElementPtr output_options) {
    if (!output_options) {
        isc_throw(BadValue, "Missing 'output_options' structure in 'loggers'");
    }

    BOOST_FOREACH(ConstElementPtr output_option, output_options->listValue()) {

        LoggingDestination dest;

        isc::data::ConstElementPtr output = output_option->get("output");
        if (!output) {
            isc_throw(BadValue, "output_options entry does not have a mandatory 'output' "
                      "element (" << output_option->getPosition() << ")");
        }
        dest.output_ = output->stringValue();

        isc::data::ConstElementPtr maxver_ptr = output_option->get("maxver");
        if (maxver_ptr) {
            dest.maxver_ = boost::lexical_cast<int>(maxver_ptr->str());
        }

        isc::data::ConstElementPtr maxsize_ptr = output_option->get("maxsize");
        if (maxsize_ptr) {
            dest.maxsize_ = boost::lexical_cast<uint64_t>(maxsize_ptr->str());
        }

        destination.push_back(dest);
    }
}

void LogConfigParser::applyConfiguration() {

    static const std::string STDOUT = "stdout";
    static const std::string STDERR = "stderr";
    static const std::string SYSLOG = "syslog";
    static const std::string SYSLOG_COLON = "syslog:";

    // Set locking directory to /tmp
    setenv("B10_LOCKFILE_DIR_FROM_BUILD", "/tmp", 1);

    std::vector<LoggerSpecification> specs;

    // Now iterate through all specified loggers
    const LoggingInfoStorage& logging_info = config_->getLoggingInfo();
    for (LoggingInfoStorage::const_iterator it = logging_info.begin();
         it != logging_info.end(); ++it) {

        // Prepare the objects to define the logging specification
        LoggerSpecification spec(it->name_,
                                 it->severity_,
                                 it->debuglevel_);
        OutputOption option;

        for (std::vector<LoggingDestination>::const_iterator dest = it->destinations_.begin();
             dest != it->destinations_.end(); ++dest) {
            
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
                // Not a recognised destination, assume a file.
                option.destination = OutputOption::DEST_FILE;
                option.filename = dest->output_;
            }

            // ... and set the destination
            spec.addOutputOption(option);
        }

        specs.push_back(spec);
    }

    LoggerManager manager;
    manager.process(specs.begin(), specs.end());
}

void LogConfigParser::applyDefaultConfiguration(bool verbose) {
    LoggerSpecification spec("kea", (verbose?isc::log::DEBUG : isc::log::INFO),
                             (verbose?99:0));

    OutputOption option;
    option.destination = OutputOption::DEST_CONSOLE;
    option.stream = OutputOption::STR_STDOUT;

    spec.addOutputOption(option);

    LoggerManager manager;
    manager.process(spec);
}

} // namespace isc::dhcp
} // namespace isc
