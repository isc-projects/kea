// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/srv_config.h>
#include <vector>

namespace isc {
namespace dhcp {

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
/// This class uses @c SrvConfig object to store logging configuration.
class LogConfigParser {
public:

    /// @brief Constructor
    ///
    /// @param storage parsed logging configuration will be stored here
    explicit LogConfigParser(const SrvConfigPtr& storage);

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

    /// @brief Parses one JSON structure in Logging/loggers" array
    ///
    /// @param entry JSON structure to be parsed
    /// @brief parses one structure in Logging/loggers.
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
    SrvConfigPtr config_;

    /// @brief Verbose mode
    ///
    /// When verbose mode is enabled, logging severity is overridden to DEBUG,
    /// and debuglevel is always 99.
    bool verbose_;
};

} // namespace isc::dhcp
} // namespace isc

#endif // DHCPSRV_LOGGING_H
