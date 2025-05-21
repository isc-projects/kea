// Copyright (C) 2014-2025 Internet Systems Consortium, Inc. ("ISC")
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
///     "output-options": [
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

    /// @brief Fetches the supported log file path.
    ///
    /// The first call to this function with no arguments will set the default
    /// hooks path to either the value of LOGFILE_DIR or the environment
    /// variable KEA_LOG_FILE_DIR if it is defined. Subsequent calls with no
    /// arguments will simply return this value.
    ///
    /// @param reset recalculate when true, defaults to false.
    /// @param explicit_path set default log path to this value. This is
    /// for testing purposes only.
    ///
    /// @return String containing the default log file path.
    static std::string getLogPath(bool reset = false, const std::string explicit_path = "");

    /// @brief Validates a library path against the supported path for log files.
    ///
    /// @param logpath path to validate.
    /// @param enforce_path enables validation against the supported path.
    /// If false verifies only that the path contains a file name.
    ///
    /// @return validated path
    static std::string validatePath(const std::string logpath, bool enforce_path = true);

private:

    /// @brief Parses one JSON structure in Server/loggers" array
    ///
    /// @param entry JSON structure to be parsed
    /// @brief parses one structure in Server/loggers.
    void parseConfigEntry(isc::data::ConstElementPtr entry);

    /// @brief Parses output-options structure
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
