// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#ifndef PERFMON_MGR_H
#define PERFMON_MGR_H

#include <perfmon_config.h>
#include <monitored_duration_store.h>
#include <asiolink/io_service.h>
#include <asiolink/interval_timer.h>

namespace isc {
namespace perfmon {

/// @brief Singleton which provides overall configuration, control, and state of
/// the PerfMon hook library. It owns the MonitoredDurationStore and AlarmStore
/// instances and supplies callout and command API handlers.  It derives from
/// PerfMonConfig.
class PerfMonMgr : public PerfMonConfig {
public:
    /// @brief Constructor.
    ///
    /// @param family Protocol family AF_INET or AF_INET6.
    explicit PerfMonMgr(uint16_t family);

    /// @brief Destructor.
    virtual ~PerfMonMgr() = default;

    /// @brief Parses the hook library 'parameters' element.
    ///
    /// @param params map of configuration parameters to parse.
    void configure(const isc::data::ConstElementPtr& params);

    /// @brief Processes the event stack of a query packet.
    ///
    /// @todo DETAILS TO FOLLOW
    ///
    /// @param query query packet whose stack is to be processed.
    /// @param response response packet generated for the query.
    /// @param subnet_id id of the selected subnet.
    void processPktEventStack(isc::dhcp::PktPtr query,
                              isc::dhcp::PktPtr response,
                              const isc::dhcp::SubnetID& subnet_id);

    /// @brief Adds a duration sample to a MonitoredDuration.
    ///
    /// The MonitoredDuration identified by the given key is fetched from
    /// the store and updated with the sample. If the update returns the
    /// duration this means it is time to report the duration via StatsMgr.
    /// The reported average is then checked against an alarm, if one exists.
    /// If the check returns the alarm, then the alarm has undergone a
    /// reportable event and is passed to reporting.
    ///
    /// @param key identifies the duration to update.
    /// @param sample amount of time that elapsed between the two events
    /// identified in the key.
    void addDurationSample(DurationKeyPtr key, const Duration& sample);

    /// @brief Emits an entry to StatsMgr for a given duration.
    ///
    /// Calculates the average duration for the reportable interval and
    /// reports the value to StatsMgr if stat-mgr-reporting is true.
    ///
    /// @param duration duration to report.
    ///
    /// @return Always returns the average duration for reportable interval.
    Duration reportToStatsMgr(MonitoredDurationPtr duration);

    /// @brief Emits a report for a given alarm.
    ///
    /// Emits a WARN log if the alarm state is TRIGGERED or an
    /// INFO log if it is CLEARED. This may expand in the future to
    /// accommodate additional reporting mechanisms.
    ///
    /// @param alarm Alarm to report.
    /// @param average Duration average which caused the state transition.
    void reportAlarm(AlarmPtr alarm, const Duration& average);

    /// @brief Handler invoked when the report timer expires.
    ///
    /// Fetches a list of the durations which are overdue to report and submits
    /// them for reporting.
    void reportTimerExpired();

    /// @brief Updates the report timer.
    ///
    ///  MonitoredDurationPtr next = durations->getReportsNext()
    ///  if next
    ///      reschedule report timer for (next->getIntervalStart() + interval_duration_);
    ///  else
    ///      cancel report timer
    void setNextReportExpiration();

    /// @brief Get the interval duration.
    ///
    /// @return interval-width-secs as a Duration.
    Duration getIntervalDuration() {
        return (interval_duration_);
    }

    /// @brief Get the alarm report interval.
    ///
    /// @return alarm-report-secs as a Duration.
    Duration getAlarmReportInterval() {
        return (alarm_report_interval_);
    }

    /// @brief Get the duration store.
    ///
    /// @return pointer to the duration store.
    MonitoredDurationStorePtr getDurationStore() {
        return (duration_store_);
    }

private:
    /// @brief Length of time a MonitoredDuration accumulates samples until reporting.
    Duration interval_duration_;

    /// @brief Length of time between raised Alarm reports.
    /// It's a conversion of alarm-report-secs to a Duration set during configuration
    /// parsing.
    Duration alarm_report_interval_;

    /// @brief In-memory store of MonitoredDurations.
    MonitoredDurationStorePtr duration_store_;

    /// @todo Not sure if we really care.  When not in service, traffic will
    /// effectively stop. Any active durations will eventually report once via
    /// timer but nothing more until traffic resumes.
    ///
    /// @brief Tracks whether or not the server is processing DHCP packets.
    // dhcp::NetworkStatePtr network_state_;

    /// @brief IOService instance used by the timer.
    asiolink::IOServicePtr io_service_;

    /// @brief Timer which tracks the next duration due to report.
    asiolink::IntervalTimerPtr report_timer_;

    /// @brief The mutex used to protect internal state.
    const boost::scoped_ptr<std::mutex> mutex_;
};

/// @brief Defines a shared pointer to a PerfMonMgr.
typedef boost::shared_ptr<PerfMonMgr> PerfMonMgrPtr;

} // end of namespace perfmon
} // end of namespace isc

#endif
