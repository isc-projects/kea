// Copyright (C) 2014-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCPSRV_LOGGING_INFO_H
#define DHCPSRV_LOGGING_INFO_H

#include <log/logger_level.h>
#include <log/logger_specification.h>
#include <cc/cfg_to_element.h>
#include <cc/user_context.h>
#include <stdint.h>
#include <vector>

namespace isc {
namespace process {

/// @brief Defines single logging destination
///
/// This structure is used to keep log4cplus configuration parameters.
struct LoggingDestination : public isc::data::CfgToElement {
public:

    /// @brief defines logging destination output
    ///
    /// Values accepted are: stdout, stderr, syslog, syslog:name.
    /// Any other destination will be considered a file name.
    std::string output_;

    /// @brief Maximum number of log files in rotation
    int maxver_;

    /// @brief Maximum log file size
    uint64_t maxsize_;

    /// @brief Immediate flush
    bool flush_;

    /// @brief defines the log format pattern
    /// It dictates what additional elements are output
    std::string pattern_;

    /// @brief Compares two objects for equality.
    ///
    /// @param other Object to be compared with this object.
    ///
    /// @return true if objects are equal, false otherwise.
    bool equals(const LoggingDestination& other) const;

    /// @brief Default constructor.
    LoggingDestination()
        : output_("stdout"), maxver_(1), maxsize_(10240000), flush_(true), pattern_("") {
    }

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;
};

/// @brief structure that describes one logging entry
///
/// This is a structure that conveys one logger entry configuration.
/// The structure in JSON form has the following syntax:
///        {
///            "name": "*",
///            "output_options": [
///                {
///                    "output": "/path/to/the/logfile.log",
///                    "maxver": 8,
///                    "maxsize": 204800,
///                    "flush": true
///                    "pattern": "%-5p [%c] %m\n"
///                }
///            ],
///            "severity": "WARN",
///            "debuglevel": 99
///        },
class LoggingInfo : public isc::data::UserContext, public isc::data::CfgToElement {
public:

    /// @brief logging name
    std::string name_;

    /// @brief describes logging severity
    isc::log::Severity severity_;

    /// @brief debuglevel (used when severity_ == DEBUG)
    ///
    /// We use range 0(least verbose)..99(most verbose)
    int debuglevel_;

    /// @brief specific logging destinations
    std::vector<LoggingDestination> destinations_;

    /// @brief Default constructor.
    LoggingInfo();

    /// @brief Removes logging destinations.
    void clearDestinations() {
        destinations_.clear();
    }

    /// @brief Compares two objects for equality.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if objects are equal, false otherwise.
    bool equals(const LoggingInfo& other) const;

    /// @brief Compares two objects for equality.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if objects are equal, false otherwise.
    bool operator==(const LoggingInfo& other) const {
        return (equals(other));
    }

    /// @brief Compares two objects for inequality.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if objects are not equal, false otherwise.
    bool operator!=(const LoggingInfo& other) const {
        return (!equals(other));
    }

    /// @brief Converts logger configuration to a spec.
    isc::log::LoggerSpecification toSpec() const;

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;
};

/// @brief storage for logging information in log4cplus format
typedef std::vector<isc::process::LoggingInfo> LoggingInfoStorage;

}
}

#endif // DHCPSRV_LOGGING_INFO_H
