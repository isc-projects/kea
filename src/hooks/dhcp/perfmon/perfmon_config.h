// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PERFMON_CONFIG_H
#define PERFMON_CONFIG_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <alarm_store.h>
#include <monitored_duration.h>

namespace isc {
namespace perfmon {

/// @file perfmon_config.h The classes herein parse PerfMon hook library's 'parameters' element
/// depicted below:
///
/// @code
///    {
///        "library": "lib/kea/hooks/libdhcp_perf_mon.so",
///        "parameters": {
///            "enable-monitoring": true,
///            "interval-width-secs": 5,
///            "stats-mgr-reporting": true,
///            "alarm-report-secs": 600,
///            "alarms": [
///            {
///                "duration-key": {
///                    "query-type": "DHCPDISCOVER",
///                    "response-type": "DHCPOFFER",
///                    "start-event": "process-started",
///                    "stop-event": "process-completed",
///                    "subnet-id": 0
///                },
///                "enable-alarm": true,
///                "high-water-ms": 500,
///                "low-water-ms": 25
///            },
///            ..
///            }]
///        }
///    }
/// @endcode

/// @brief Parses configuration parameters for a single DurationKey.
///
/// DurationKey is used to identify both MonitoredDurations and
/// Alarms, thus they could be use to define either in configuration
/// as well as identifiy either in API calls. Given this, it seems
/// prudent to define a "duration-key" element with its own
/// parser.
class DurationKeyParser {
public:
    /// @brief List of valid parameters and expected types.
    static const data::SimpleKeywords CONFIG_KEYWORDS;

    /// @brief Constructor.
    explicit DurationKeyParser() = default;

    /// @brief Destructor.
    ~DurationKeyParser() = default;

    /// @brief Convert a configuration parameter to family-specific message type.
    ///
    /// @param config element map containing the duration key parameters.
    /// @param family protocol family AF_INET or AF_INET6.
    /// @param param_name configuration parameter name.
    /// @param required if true then function will throw if the parameter does
    /// not exist in the configuration. Defaults to true.
    ///
    /// @return numeric message type, returns DHCP_NOTYPE if name is empty.
    /// @throw DhcpConfigError if parameter type or value is not valid, or when
    /// required is true and the parameter is not in the map.
    static uint16_t getMessageType(data::ConstElementPtr config,
                                   uint16_t family,
                                   const std::string& param_name,
                                   bool required = true);

    /// @brief Convert string message name to DHCP message type.
    ///
    /// @param name upper-case message name (e.g "DHCPDISCOVER", "DHCPOFFER").
    ///
    /// @return numeric message type, returns DHCP_NOTYPE if name is empty.
    /// @throw BadValue if the message name is unknown.
    static uint16_t getMessageNameType4(const std::string& name);

    /// @brief Convert string message name to DHCP6 message type.
    ///
    /// @param name upper-case message name (e.g "DHCPV6_SOLICIT", "DHCV6_REPLY").
    ///
    /// @return numeric message type, returns DHCPV6_NOTYPE if name is empty.
    /// @throw BadValue if the message name is unknown.
    static uint16_t getMessageNameType6(const std::string& name);

    /// @brief Convert a map of Elements into a DurationKey.
    ///
    /// @param config element map containing the duration key parameters.
    /// @param family protocol family AF_INET or AF_INET6.
    static DurationKeyPtr parse(data::ConstElementPtr config, uint16_t family);

    /// @brief Convert a DurationKey into a map of Elements.
    ///
    /// @param key DurationKey to convert.
    ///
    /// @return Pointer to a map of elements.
    static data::ElementPtr toElement(DurationKeyPtr key);
};

/// @brief Parses configuration parameters for a single Alarm.
class AlarmParser {
public:
    /// @brief List of valid parameters and expected types.
    static const data::SimpleKeywords CONFIG_KEYWORDS;

    /// @brief Constructor.
    explicit AlarmParser();

    /// @brief Destructor.
    ~AlarmParser() = default;

    /// @brief
    ///
    /// @param config element map containing the alarm parameters.
    /// @param family protocol family AF_INET or AF_INET6.
    static AlarmPtr parse(data::ConstElementPtr config, uint16_t family);
};

/// @brief Houses the PerfMon configuration parameters for a single scope
/// (e.g. global, subnet...);
class PerfMonConfig {
public:
    /// @brief List of valid parameters and expected types.
    static const data::SimpleKeywords CONFIG_KEYWORDS;

    /// @brief List of valid parameter defaults.
    static const data::SimpleDefaults SIMPLE_DEFAULTS;

    /// @brief Constructor.
    explicit PerfMonConfig(uint16_t family);

    /// @brief Destructor.
    virtual ~PerfMonConfig() = default;

    /// @brief Extracts member values from an Element::map.
    ///
    /// @param config map of configuration parameters.
    ///
    /// @throw DhcpConfigError if invalid values are detected.
    void parse(data::ConstElementPtr config);

    /// @brief Re-creates the AlarmStore and populates it by parsing a
    /// list of alarm elements.
    ///
    /// @param config list of alarm configuration elements.
    ///
    /// @throw DhcpConfigError if a parsing error occurs or
    /// there are duplicate alarm keys.
    void parseAlarms(data::ConstElementPtr config);

    /// @brief Fetches the value of enable-monitoring.
    ///
    /// @return boolean value of enable-monitoring.
    bool getEnableMonitoring() const {
        return (enable_monitoring_);
    }

    /// @brief Sets the value of enable-monitoring.
    ///
    /// @param value new value for enable-monitoring.
    void setEnableMonitoring(bool value) {
        enable_monitoring_ = value;
    }

    /// @brief Fetches the value of interval-width-secs.
    ///
    /// @return integer value of interval-width-secs.
    uint32_t getIntervalWidthSecs() const {
        return (interval_width_secs_);
    }

    /// @brief Sets the value of interval-width-secs.
    ///
    /// @param value new value for interval-width-secs.
    void setIntervalWidthSecs(uint32_t value) {
        interval_width_secs_ = value;
    }

    /// @brief Fetches the value of stats-mgr-reporting.
    ///
    /// @return boolean value of stats-mgr-reporting.
    bool getStatsMgrReporting() const {
        return (stats_mgr_reporting_);
    };

    /// @brief Sets the value of stats-mgr-reporting.
    ///
    /// @param value new value for stats-mgr-reporting.
    void setStatsMgrReporting(bool value) {
        stats_mgr_reporting_ = value;
    }

    /// @brief Fetches the value of alarm-report-secs.
    ///
    /// @return integer value of alarm-report-secs.
    uint32_t getAlarmReportSecs() const {
        return (alarm_report_secs_);
    }

    /// @brief Sets the value of alarm-report-secs.
    ///
    /// @param value new value for alarm-report-secs.
    void setAlarmReportSecs(uint32_t value) {
        alarm_report_secs_ = value;
    }

    /// @brief Get protocol family.
    ///
    /// @return uint16_t containing the family (AF_INET or AF_INET6).
    uint16_t getFamily() {
        return (family_);
    }

    /// @brief Get the alarm store.
    ///
    /// @return pointer to the alarm store.
    AlarmStorePtr getAlarmStore() {
        return (alarm_store_);
    }

protected:
    /// @brief Protocol family AF_INET or AF_INET6.
    uint16_t family_;

    /// @brief If true, performance data is processed/reported. Defaults to
    /// true. If false the library loads and configures but does nothing.
    /// Gives users a way to keep the library loaded without it being active.
    /// Should be accessible via explicit API command.
    bool enable_monitoring_;

    /// @brief Number of seconds a duration accumulates samples until reporting.
    /// Defaults to 60.
    uint32_t interval_width_secs_;

    /// @brief If true durations report to StatsMgr at the end of each interval.
    /// Defaults to true.
    bool stats_mgr_reporting_;

    /// @brief Number of seconds between reports of a raised alarm.
    /// Defaults to 300.  A value of zero disables alarms.
    uint32_t alarm_report_secs_;

    /// @brief Stores the configured alarms.
    AlarmStorePtr alarm_store_;
};

/// @brief Defines a shared pointer to a PerfMonConfig.
typedef boost::shared_ptr<PerfMonConfig> PerfMonConfigPtr;

} // end of namespace perfmon
} // end of namespace isc

#endif
