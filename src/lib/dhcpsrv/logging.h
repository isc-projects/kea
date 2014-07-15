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

#ifndef DHCPSRV_LOGGING_H
#define DHCPSRV_LOGGING_H

#include <cc/data.h>
#include <dhcpsrv/configuration.h>
#include <dhcpsrv/cfgmgr.h>
#include <stdint.h>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Interprets JSON structures and translates them to log4cplus
///
/// This parser iterates over provided JSON structures and translates them
/// into values applicable to log4cplus.
///
/// This class uses Configuration structure to store logging configuration.
class LogConfigParser {
public:

    /// @brief Constructor
    ///
    /// @param storage parsed logging configuration will be stored here
    LogConfigParser(const ConfigurationPtr& storage);

    /// @brief Parses specified configuration
    ///
    /// Walks over specified logging configuration JSON structures and store
    /// parsed information in config_->logging_info_.
    ///
    /// @param log_config JSON structures to be parsed
    void parseConfiguration(isc::data::ConstElementPtr log_config);

    /// @brief Applies stored configuration
    void applyConfiguration();

    /// @brief Configures default logging
    static void defaultLogging();

protected:

    /// @brief Parses one JSON structure in Logging/loggers" array
    ///
    /// The structure has the following syntax:
    /// {
    ///     "name": "*",
    ///     "output_options": [
    ///         {
    ///             "output": "/home/thomson/kea-inst/kea-warn.log",
    ///             "maxver": 8,
    ///             "maxsize": 204800
    ///         }
    ///     ],
    ///     "severity": "WARN"
    /// }
    ///
    /// @param entry JSON structure to be parsed
    /// @brief parses one structure in Logging/loggers.
    void parseConfigEntry(isc::data::ConstElementPtr entry);

    /// @brief Parses output_options structure
    ///
    /// @param destination parsed parameters will be stored here
    /// @param output_options element to be parsed
    void parseOutputOptions(std::vector<LoggingDestination>& destination,
                            isc::data::ConstElementPtr output_options);

    /// @brief Configuration is stored here
    ///
    /// LogConfigParser class uses only config_->logging_info_ field.
    ConfigurationPtr config_;
};

} // namespace isc::dhcp
} // namespace isc

#endif // CFGMGR_H
