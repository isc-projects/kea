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

#ifndef DHCPSRV_CONFIGURATION_H
#define DHCPSRV_CONFIGURATION_H

#include <dhcpsrv/cfg_iface.h>
#include <log/logger_level.h>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <stdint.h>

namespace isc {
namespace dhcp {

class CfgMgr;

/// @brief Defines single logging destination
///
/// This structure is used to keep log4cplus configuration parameters.
struct LoggingDestination {

    /// @brief defines logging destination output
    ///
    /// Values accepted are: stdout, stderr, syslog, syslog:name.
    /// Any other destination will be considered a file name.
    std::string output_;

    /// @brief Maximum number of log files in rotation
    int maxver_;

    /// @brief Maximum log file size
    uint64_t maxsize_;
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
///                    "maxsize": 204800
///                }
///            ],
///            "severity": "WARN",
///            "debuglevel": 99
///        },
struct LoggingInfo {

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
};

/// @brief storage for logging information in log4cplus format
typedef std::vector<isc::dhcp::LoggingInfo> LoggingInfoStorage;

/// @brief Specifies current DHCP configuration
///
/// @todo Migrate all other configuration parameters from cfgmgr.h here
struct Configuration {

    /// @name Constants for selection of parameters returned by @c getConfigSummary
    ///
    //@{
    /// Nothing selected
    static const uint32_t CFGSEL_NONE    = 0x00000000;
    /// Number of IPv4 subnets
    static const uint32_t CFGSEL_SUBNET4 = 0x00000001;
    /// Number of IPv6 subnets
    static const uint32_t CFGSEL_SUBNET6 = 0x00000002;
    /// Number of enabled ifaces
    static const uint32_t CFGSEL_IFACE4  = 0x00000004;
    /// Number of v6 ifaces
    static const uint32_t CFGSEL_IFACE6  = 0x00000008;
    /// DDNS enabled/disabled
    static const uint32_t CFGSEL_DDNS    = 0x00000010;
    /// Number of all subnets
    static const uint32_t CFGSEL_SUBNET  = 0x00000003;
    /// IPv4 related config
    static const uint32_t CFGSEL_ALL4    = 0x00000015;
    /// IPv6 related config
    static const uint32_t CFGSEL_ALL6    = 0x0000001A;
    /// Whole config
    static const uint32_t CFGSEL_ALL     = 0xFFFFFFFF;
    //@}

    /// @brief logging specific information
    LoggingInfoStorage logging_info_;

    /// @brief Interface configuration.
    ///
    /// Used to select interfaces on which the DHCP server will listen to
    /// queries.
    CfgIface cfg_iface_;

    /// @brief Returns summary of the configuration in the textual format.
    ///
    /// This method returns the brief text describing the current configuration.
    /// It may be used for logging purposes, e.g. when the new configuration is
    /// committed to notify a user about the changes in configuration.
    ///
    /// @todo Currently this method uses @c CfgMgr accessors to get the
    /// configuration parameters. Once these parameters are migrated from the
    /// @c CfgMgr this method will have to be modified accordingly.
    ///
    /// @todo Implement reporting a summary of interfaces being used for
    /// receiving and sending DHCP messages. This will be implemented with
    /// ticket #3512.
    ///
    /// @param selection Is a bitfield which describes the parts of the
    /// configuration to be returned.
    ///
    /// @return Summary of the configuration in the textual format.
    std::string getConfigSummary(const uint32_t selection) const;
};

/// @brief pointer to the configuration
typedef boost::shared_ptr<Configuration> ConfigurationPtr;

} // namespace isc::dhcp
} // namespace isc

#endif // DHCPSRV_CONFIGURATION_H
