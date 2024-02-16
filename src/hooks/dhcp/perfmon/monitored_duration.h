// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _MONITORED_DURATION_H
#define _MONITORED_DURATION_H

#include <dhcp/pkt.h>
#include <dhcpsrv/subnet_id.h>

#include <boost/date_time/posix_time/posix_time.hpp>

namespace isc {
namespace perfmon {

typedef boost::posix_time::ptime Timestamp;
typedef boost::posix_time::time_duration Duration;

/// @brief Embodies a span of time (i.e. an interval) over which duration data
/// is accumulated.
class DurationDataInterval {
public:
    /// @brief Get a duration of zero.
    ///
    /// @return Duration of zero microseconds.
    static const Duration& ZERO_DURATION() {
        static Duration duration(boost::posix_time::microseconds(0));
        return (duration);
    }

    /// @brief Constructor
    explicit DurationDataInterval(const Timestamp& start_time = dhcp::PktEvent::now());

    /// @brief Destructor
    ~DurationDataInterval() = default;

    /// @brief Add a duration to the interval.
    ///
    /// Given a duration value:
    /// -# Increment the number of occurrences
    /// -# Add the duration to the total duration
    /// -# Update the minimum and/or maxium duration accordingly
    ///
    /// @param duration Duration to add.
    void addDuration(const Duration& duration);

    /// @brief Get the start time of the interval.
    ///
    /// @return Timestamp containing the start time.
    const Timestamp& getStartTime() const {
        return (start_time_);
    }

    /// @brief Set the interval start time.
    ///
    /// @param start_time new value for the interval start time.
    void setStartTime(const Timestamp& start_time) {
        start_time_ = start_time;
    }

    /// @brief Get the number of occurrences that have contributed to the
    /// interval.
    ///
    /// @return uint64_t containing the number of occurrences.
    uint64_t getOccurrences() const {
        return (occurrences_);
    };

    /// @brief Get the minimum duration that has occurred in the interval.
    ///
    /// @return Duration containing the minimum duration.
    Duration getMinDuration() const {
        return (min_duration_);
    }

    /// @brief Get the maximum duration that has occurred in the interval.
    ///
    /// @return Duration containing the maximum duration.
    Duration getMaxDuration() const {
        return (max_duration_);
    }

    /// @brief Get the total duration in the interval.
    ///
    /// @return Duration containing the total duration.
    Duration getTotalDuration() const {
        return (total_duration_);
    }

    /// @brief Get the average duration for the interval.
    ///
    /// @return Duration containing the average.
    Duration getAverageDuration() const;

private:
    /// @brief Timestamp at which this interval began.
    Timestamp start_time_;

    /// @brief Number of event-pairs that occurred during the interval.
    uint64_t occurrences_;

    /// @brief Minimum duration that occurred during this interval.
    Duration min_duration_;

    /// @brief Maximum duration that occurred during this interval.
    Duration max_duration_;

    /// @brief Total duration of all the occurrences included in this interval.
    Duration total_duration_;
};

/// @brief Defines a pointer to a DurationDataInterval instance.
typedef boost::shared_ptr<DurationDataInterval> DurationDataIntervalPtr;

/// @brief Houses the composite key that uniquely identifies a duration:
/// -# Query Packet Type
/// -# Response Packet Type
/// -# Start Event
/// -# End Event
/// -# Subnet ID  can be GLOBAL_SUBNET_ID for aggregate durations
class DurationKey {
public:
    /// @brief Constructor
    ///
    /// @param family protocol family AF_INET or AF_INET6
    /// @param query_type message type of the query packet
    /// @param response_type_ message type of the response packet
    /// @param start_event_label label of the start event
    /// @param end_event_label label of the end event
    /// @param SubnetID subnet_id id of the selected subnet
    DurationKey(uint16_t family, uint8_t query_type_, uint8_t response_type_,
                const std::string& start_event_label, const std::string& end_event_label,
                dhcp::SubnetID subnet_id_);

    /// @brief Destructor
    virtual ~DurationKey() = default;

    /// @brief Get protocol family
    ///
    /// @return uint16_t containing the family (AF_INET or AF_INET6)
    uint16_t getFamily() {
        return(family_);
    }

    /// @brief Get the query packet type.
    ///
    /// @return uint8_t containing the query packet type.
    uint8_t getQueryType() const {
        return (query_type_);
    }

    /// @brief Get the response packet type.
    ///
    /// @return uint8_t containing the response packet type.
    uint8_t getResponseType() const {
        return (response_type_);
    };

    /// @brief Get the start event label.
    ///
    /// @return String containing the start event label.
    std::string getStartEventLabel() const {
        return (start_event_label_);
    }

    /// @brief Get the end event label.
    ///
    /// @return String containing the end event label.
    std::string getEndEventLabel() const {
        return (end_event_label_);
    }

    /// @brief Get the subnet id.
    ///
    /// @return SubnetID of the selected subnet.
    dhcp::SubnetID getSubnetId() const {
        return (subnet_id_);
    }

    /// @brief Get a composite label of the member values with text message types.
    ///
    /// @param family Protocol family of the key (AF_INET or AF_INET6)
    /// The format of the string:
    ///
    /// @code
    ///     <query type>-<response type>.<start_event>-<end_event>.<subnet id>
    ///
    /// Example:
    ///
    ///     "DHCPDISCOVER-DHCPOFFER.socket_received.buffer_read.12"
    ///
    ///     or
    ///
    ///     "DHCPV6_SOLICIT-DHCPV6_ADVERTISE.socket_received.buffer_read.12"
    ///
    /// @endcode
    ///
    /// @return String containing the composite label.
    std::string getLabel() const;

    /// @brief Validates that a query and response message type pair is sane.
    ///
    /// @param family Protocol family of the key (AF_INET or AF_INET6)
    /// The format of the string:
    /// @param query_type message type of the query packet
    /// @param response_type_ message type of the response packet
    ///
    /// @throw BadValue is the pairing does not make sense.
    static void validateMessagePair(uint16_t family, uint8_t query_type, uint8_t response_type);

protected:
    /// @brief Protocol family AF_INET or AF_INET6
    uint16_t family_;

    /// @brief Query message type (e.g. DHCPDISCOVER, DHCP6_SOLICIT)
    uint8_t query_type_;

    /// @brief Response message type. (e.g. DHCPOFFER, DHCP6_ADVERTISE)
    uint8_t response_type_;

    /// @brief Label of the start event which begins the duration.
    std::string start_event_label_;

    /// @brief Label of the end event which ends the duration.
    std::string end_event_label_;

    /// @brief Subnet ID of the subnet selected during query fulfillment.
    isc::dhcp::SubnetID subnet_id_;
};

/// @brief Defines a pointer to a DurationKey instance.
typedef boost::shared_ptr<DurationKey> DurationKeyPtr;

/// @brief Defines an alarm for a duration.
class Alarm : public DurationKey {
public:
    /// @brief Defines Alarm states
    enum State {
        CLEAR,      // Enabled and not currently triggered
        TRIGGERED,  // High water has been exceeded
        DISABLED    // Disabled
    };

    /// @brief Constructor
    ///
    /// @param family protocol family AF_INET or AF_INET6
    /// @param query_type message type of the query packet
    /// @param response_type_ message type of the response packet
    /// @param start_event_label label of the start event
    /// @param end_event_label label of the end event
    /// @param SubnetID subnet_id id of the selected subnet
    /// @param low_water threshold below which the average duration must fall to clear the alarm
    /// @brief high_water threshold above which the average duration must rise to trigger the alarm.
    /// @brief enabled true sets state to CLEAR, otherwise DISABLED, defaults to true.
    Alarm(uint16_t family, uint8_t query_type_, uint8_t response_type_,
          const std::string& start_event_label, const std::string& end_event_label,
          dhcp::SubnetID subnet_id_,
          const Duration& low_water, const Duration& high_water, bool enabled = true);

    /// @brief Constructor
    ///
    /// param key composite key that identifies the alarm
    /// @param low_water threshold below which the average duration must fall to clear the alarm
    /// @brief high_water threshold above which the average duration must rise to trigger the alarm.
    /// @brief enabled true sets state to CLEAR, otherwise DISABLED, defaults to true.
    Alarm(const DurationKey& key, const Duration& low_water, const Duration& high_water, bool enabled = true);

    /// @brief Destructor
    virtual ~Alarm() = default;

    /// @brief Get the low water threshold.
    ///
    /// @return Duration containing the low water threshold.
    Duration getLowWater() const {
        return (low_water_);
    }

    /// @brief Set the low water threshold.
    ///
    /// @param low_water new value for the low water threshold.
    /// @throw BadValue if new value is greater than the current value
    /// of high water.
    void setLowWater(const Duration& low_water);

    /// @brief Get the high water threshold.
    ///
    /// @return Duration containing the high water threshold.
    Duration getHighWater() const {
        return (high_water_);
    }

    /// @brief Set the high water threshold.
    ///
    /// @param high_water new value for the high water threshold.
    /// @throw BadValue if new value is less than the current value
    /// of low water.
    void setHighWater(const Duration& high_water);

    /// @brief Get the alarm's state.
    State getState() {
        return (state_);
    }

    /// @brief Sets the alarm state.
    ///
    /// Sets the alarm's state to the given value,
    /// sets the start of state time to the current time,
    /// and resets the last high water report.
    ///
    /// @param state new state to which to transition.
    void setState(State state);

    /// @brief Get the time the current state began.
    ///
    /// @return Timestamp the alarm entered it's current state.
    Timestamp getStosTime() {
        return (stos_time_);
    }

    /// @brief Get the timestamp of the last high water report.
    ///
    /// @return Timestamp containing the last high water report time.
    Timestamp getLastHighWaterReport() {
        return (last_high_water_report_);
    }

    /// @brief Set the timestamp of the last high water report.
    ///
    /// This function is provided for test purposes only.
    ///
    /// @param timestamp new value of the last high water report, defaults to
    /// the current time.
    void setLastHighWaterReport(const Timestamp& timestamp = dhcp::PktEvent::now()) {
        last_high_water_report_ = timestamp;
    }

    /// @brief Sets the alarm back to the CLEAR state.
    void clear();

    /// @brief Disables the alarm by setting the state to DISABLED.
    void disable();

    /// @brief Checks a duration against the high and low water thresholds
    /// and calls the appropriate event handler.
    ///
    /// -# If the sample is less than the low water threshold:
    /// If the state is TRIGGERED, transition to CLEAR and return true otherwise
    /// return false.
    /// -# If the sample is greater than high water threshold:
    /// If the state is not TRIGGERED, transition to TRIGGERED
    /// -# If the state is TRIGGERED and the last report time either not set or
    /// is more than report interval old, update the last report time to current
    /// time and return true.
    /// -# Otherwise return false.
    ///
    /// @param sample duration to test against the thresholds.
    /// @param report_interval amount of time that must elapse between high
    /// water reports.
    ///
    /// @return True if alarm state should be reported.
    ///
    /// @throw InvalidOperation if called when the state is DISABLED.
    bool checkSample(const Duration& sample, const Duration& report_interval);

private:
    /// @brief Threshold below which the average duration must fall to clear the alarm.
    Duration low_water_;

    /// @brief Threshold above which the average duration must rise to trigger the alarm.
    Duration high_water_;

    /// @brief Current alarm state.
    State state_;

    /// @brief Timestamp of the beginning of the current state.
    Timestamp stos_time_;

    /// @brief Last time the high water breach was reported.
    Timestamp last_high_water_report_;
};

/// @brief Defines a pointer to an Alarm instance.
typedef boost::shared_ptr<Alarm> AlarmPtr;

class MonitoredDuration : public DurationKey {
public:
    /// @brief Constructor
    ///
    /// @param family protocol family AF_INET or AF_INET6
    /// @param query_type message type of the query packet
    /// @param response_type_ message type of the response packet
    /// @param start_event_label label of the start event
    /// @param end_event_label label of the end event
    /// @param SubnetID subnet_id id of the selected subnet
    /// @param Duration interval_duration_;
    MonitoredDuration(uint16_t family, uint8_t query_type_, uint8_t response_type_,
                      const std::string& start_event_label, const std::string& end_event_label,
                      dhcp::SubnetID subnet_id_, const Duration& interval_duration_);

    /// @brief Constructor
    ///
    /// param key composite key that identifies the alarm
    /// @param Duration interval_duration_;
    MonitoredDuration(const DurationKey& key, const Duration& interval_duration_);

    /// @brief Destructor
    virtual ~MonitoredDuration() = default;

    /// @brief Get the interval duration
    ///
    /// @return Duration containing the interval duration.
    Duration getIntervalDuration() const {
        return(interval_duration_);
    }

    /// @brief Get the previous interval
    ///
    /// @return Pointer to the previous interval if it exists or an empty pointer.
    DurationDataIntervalPtr getPreviousInterval() const {
        return (previous_interval_);
    }

    /// @brief Get the current interval
    ///
    /// @return Pointer to the current interval if it exists or an empty pointer.
    DurationDataIntervalPtr getCurrentInterval() const {
        return (current_interval_);
    }

    /// @brief Add a sample to the duration's current interval.
    ///
    /// If there is no current interval start a new one otherwise if the current
    /// interval has expired move it to the previous interval, set the return flag
    /// to true, then start a new interval.
    /// Add the sample to the current interval.
    ///
    /// @param sample duration value to add
    ///
    /// @return True if there is a newly completed (i.e. previous) interval to report.
    bool addSample(const Duration& sample);

    /// @brief Deletes the current and previous intervals.
    void clear();

private:
    /// @brief Length of the time of a single data interval.
    Duration interval_duration_;

    /// @brief Data interval into which samples are currently accumulating.
    DurationDataIntervalPtr current_interval_;

    /// @brief Closed data interval immediately prior to the current interval.
    DurationDataIntervalPtr previous_interval_;
};

typedef boost::shared_ptr<MonitoredDuration> MonitoredDurationPtr;

} // end of namespace isc::perfmon
} // end of namespace isc

#endif
