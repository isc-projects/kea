// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/data.h>
#include <dhcpsrv/logging.h>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <log/logger_specification.h>
#include <log/logger_support.h>
#include <log/logger_manager.h>
#include <log/logger_name.h>

using namespace isc::data;
using namespace isc::log;

namespace isc {
namespace dhcp {

LogConfigParser::LogConfigParser(const SrvConfigPtr& storage)
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
    } catch (const std::exception&) {
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

        isc::data::ConstElementPtr flush_ptr = output_option->get("flush");
        if (flush_ptr) {
            dest.flush_ = flush_ptr->boolValue();
        }

        destination.push_back(dest);
    }
}

} // namespace isc::dhcp
} // namespace isc
