// Copyright (C) 2014-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCPSRV_LOGGING_H
#define DHCPSRV_LOGGING_H

#include <cc/data.h>
#include <process/logging_info.h>
#include <process/config_base.h>
#include <vector>

namespace isc {
namespace process {

/// @brief Configures log4cplus by translating Kea configuration structures
///
/// This parser iterates over provided data elements and translates them
/// into values applicable to log4cplus.
///
/// The data structures converted to JSON format have the following syntax:
/// {
///     "name": "kea",
///     "output_options": [
///         {
///             "output": "/home/thomson/kea-inst/kea-warn.log",
///             "maxver": 8,
///             "maxsize": 204800,
///             "flush": true
///         }
///     ],
///     "severity": "WARN"
/// }
///
/// This is only an example and actual values may be different.
///
/// The data structures don't have to originate from JSON. JSON is just a
/// convenient presentation syntax.
///
/// This class uses @c ConfigBase object to store logging configuration.
class LogConfigParser {
public:

    /// @brief Constructor
    ///
    /// @param storage parsed logging configuration will be stored here
    LogConfigParser(const ConfigPtr& storage);

    /// @brief Parses specified configuration
    ///
    /// Walks over specified logging configuration JSON structures and store
    /// parsed information in config_->logging_info_.
    ///
    /// @param log_config JSON structures to be parsed (loggers list)
    /// @param verbose specifies verbose mode (true forces DEBUG, debuglevel = 99)
    void parseConfiguration(const isc::data::ConstElementPtr& log_config,
                            bool verbose = false);

private:

    /// @brief Parses one JSON structure in Server/loggers" array
    ///
    /// @param entry JSON structure to be parsed
    /// @brief parses one structure in Server/loggers.
    void parseConfigEntry(isc::data::ConstElementPtr entry);

    /// @brief Parses output_options structure
    ///
    /// @ref @c LogConfigParser for an example in JSON format.
    ///
    /// @param destination parsed parameters will be stored here
    /// @param output_options element to be parsed
    void parseOutputOptions(std::vector<LoggingDestination>& destination,
                            isc::data::ConstElementPtr output_options);

    /// @brief Configuration is stored here
    ///
    /// LogConfigParser class uses only config_->logging_info_ field.
    ConfigPtr config_;

    /// @brief Verbose mode
    ///
    /// When verbose mode is enabled, logging severity is overridden to DEBUG,
    /// and debuglevel is always 99.
    bool verbose_;
};

} // namespace isc::dhcp
} // namespace isc

#endif // DHCPSRV_LOGGING_H
