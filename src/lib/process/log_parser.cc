// Copyright (C) 2014-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <process/d_log.h>
#include <process/log_parser.h>
#include <boost/lexical_cast.hpp>
#include <log/logger_specification.h>
#include <log/logger_support.h>
#include <log/logger_manager.h>
#include <log/logger_name.h>
#include <util/filesystem.h>

using namespace isc::data;
using namespace isc::log;
using namespace isc::util::file;

namespace isc {
namespace process {

namespace {
    // Singleton PathChecker to set and hold valid log file path.
    PathCheckerPtr log_path_checker_;
};

LogConfigParser::LogConfigParser(const ConfigPtr& storage)
    :config_(storage), verbose_(false) {
    if (!storage) {
        isc_throw(BadValue, "LogConfigParser needs a pointer to the "
                  "configuration, so parsed data can be stored there");
    }
}

void LogConfigParser::parseConfiguration(const isc::data::ConstElementPtr& loggers,
                                         bool verbose) {
    verbose_ = verbose;

    // Iterate over all entries in "Server/loggers" list
    for (auto const& logger : loggers->listValue()) {
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

    // Get user context
    isc::data::ConstElementPtr user_context = entry->get("user-context");
    if (user_context) {
        info.setContext(user_context);
    }

    // Get a name
    isc::data::ConstElementPtr name_ptr = entry->get("name");
    if (!name_ptr) {
        isc_throw(BadValue, "loggers entry does not have a mandatory 'name' "
                  "element (" << entry->getPosition() << ")");
    }
    info.name_ = name_ptr->stringValue();

    // Get the severity.
    // If not configured, set it to DEFAULT to inherit it from the root logger later.
    isc::data::ConstElementPtr severity_ptr = entry->get("severity");
    if (severity_ptr) {
        info.severity_ = getSeverity(severity_ptr->stringValue());
    } else {
        info.severity_ = DEFAULT;
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
            isc_throw(BadValue, "Unsupported debuglevel value "
                      << debuglevel_ptr->intValue()
                      << ", expected 0-99 ("
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

    isc::data::ConstElementPtr output_options = entry->get("output-options");
    isc::data::ConstElementPtr deprecated_output_options = entry->get("output_options");

    if (output_options && deprecated_output_options) {
        isc_throw(BadValue, "Only one of 'output-options' and 'output_options' may be specified.");
    }

    if (deprecated_output_options) {
        LOG_WARN(dctl_logger, DCTL_DEPRECATED_OUTPUT_OPTIONS);
        output_options = deprecated_output_options;
        ElementPtr mutable_element = boost::const_pointer_cast<Element>(entry);
        mutable_element->remove("output_options");
        mutable_element->set("output-options", output_options);
    }

    if (output_options) {
        parseOutputOptions(info.destinations_, output_options);
    }

    config_->addLoggingInfo(info);
}

std::string
LogConfigParser::getLogPath(bool reset /* = false */, const std::string explicit_path /* = "" */) {
    if (!log_path_checker_ || reset) {
        log_path_checker_.reset(new PathChecker(LOGFILE_DIR, "KEA_LOG_FILE_DIR"));
        if (!explicit_path.empty()) {
            log_path_checker_->getPath(true, explicit_path);
        }
    }

    return (log_path_checker_->getPath());
}

std::string
LogConfigParser::validatePath(const std::string logpath,
                                   bool enforce_path /* = true */) {
    if (!log_path_checker_) {
        getLogPath();
    }

    return (log_path_checker_->validatePath(logpath, enforce_path));
}

void LogConfigParser::parseOutputOptions(std::vector<LoggingDestination>& destination,
                                         isc::data::ConstElementPtr output_options) {
    if (!output_options) {
        isc_throw(BadValue, "Missing 'output-options' structure in 'loggers'");
    }

    for (auto const& output_option : output_options->listValue()) {

        LoggingDestination dest;

        isc::data::ConstElementPtr output = output_option->get("output");
        if (!output) {
            isc_throw(BadValue, "output-options entry does not have a mandatory 'output' "
                      "element (" << output_option->getPosition() << ")");
        }

        auto output_str = output->stringValue();
        if ((output_str == "stdout") ||
            (output_str == "stderr") ||
            (output_str == "syslog") ||
            (output_str.find("syslog:") == 0)) {
            dest.output_ = output_str;
        } else {
            try {
                dest.output_ = validatePath(output_str);
            } catch (const std::exception& ex) {
                isc_throw(BadValue, "invalid path in `output`: " << ex.what()
                          << " (" << output_option->getPosition() << ")");
            }
        }

        isc::data::ConstElementPtr maxver_ptr = output_option->get("maxver");
        if (maxver_ptr) {
            dest.maxver_ = boost::lexical_cast<int>(maxver_ptr->str());
        }

        isc::data::ConstElementPtr maxsize_ptr = output_option->get("maxsize");
        if (maxsize_ptr) {
            dest.maxsize_ = boost::lexical_cast<uint64_t>(maxsize_ptr->str());
        }

        isc::data::ConstElementPtr flush_ptr = output_option->get("flush");
        if (flush_ptr) {
            dest.flush_ = flush_ptr->boolValue();
        }

        isc::data::ConstElementPtr pattern = output_option->get("pattern");
        if (pattern) {
            dest.pattern_ = pattern->stringValue();
        }

        destination.push_back(dest);
    }
}

} // namespace isc::dhcp
} // namespace isc
