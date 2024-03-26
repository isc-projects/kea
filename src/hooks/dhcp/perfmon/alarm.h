// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ALARM_H
#define _ALARM_H

#include <dhcp/pkt.h>
#include <dhcpsrv/subnet_id.h>
#include <monitored_duration.h>

#include <boost/date_time/posix_time/posix_time.hpp>

namespace isc {
namespace perfmon {

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
    /// @param response_type message type of the response packet
    /// @param start_event_label label of the start event
    /// @param stop_event_label label of the end event
    /// @param subnet_id SubnetID of the selected subnet
    /// @param low_water threshold below which the average duration must fall to clear the alarm
    /// @param high_water threshold above which the average duration must rise to trigger the alarm
    /// @param enabled true sets state to CLEAR, otherwise DISABLED, defaults to true
    Alarm(uint16_t family, uint8_t query_type, uint8_t response_type,
          const std::string& start_event_label, const std::string& stop_event_label,
          dhcp::SubnetID subnet_id,
          const Duration& low_water, const Duration& high_water, bool enabled = true);

    /// @brief Constructor
    ///
    /// @param key composite key that identifies the alarm
    /// @param low_water threshold below which the average duration must fall to clear the alarm
    /// @param high_water threshold above which the average duration must rise to trigger the alarm
    /// @param enabled true sets state to CLEAR, otherwise DISABLED, defaults to true
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

} // end of namespace isc::perfmon
} // end of namespace isc

#endif
