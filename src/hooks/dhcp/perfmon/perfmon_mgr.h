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
#include <config/command_mgr.h>
#include <config/cmds_impl.h>
#include <monitored_duration_store.h>
#include <asiolink/io_service.h>
#include <asiolink/interval_timer.h>
#include <dhcpsrv/subnet.h>

namespace isc {
namespace perfmon {

/// @brief Singleton which provides overall configuration, control, and state of
/// the PerfMon hook library. It owns the MonitoredDurationStore and AlarmStore
/// instances and supplies callout and command API handlers.  It derives from
/// PerfMonConfiga and CmdsImpl.
class PerfMonMgr : public PerfMonConfig, private config::CmdsImpl {
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

    /// @brief Sets convenience values and (re)creates the duration store.
    ///
    /// Called by the constructor and also by configure().
    virtual void init();

    /// @brief Processes the event stack of a query packet.
    ///
    ///  -# Emit a dump of packet stack to perfmon debug log at detail level.
    ///  -# Iterates over the query's event stack creating a DurationKey for each
    ///  adjacent event pair, computing the elapsed time between them and then calls
    ///  addDurationSample().
    ///  -# Generates composite duration updates. Durations that monitor total response
    ///  time for a given query/response pair will be computed using the first and last
    ///  events in the stack, with a begin event label of "composite" and an end label
    ///  of "total_response" for the DurationKey. These duration updates will be passed
    ///  into addDurationSample(). Other composite durations may be added in the future.
    ///
    /// @param query query packet whose stack is to be processed.
    /// @param response response packet generated for the query.
    /// @param subnet selected subnet, if empty use the global
    /// subnet id.
    void processPktEventStack(isc::dhcp::PktPtr query,
                              isc::dhcp::PktPtr response,
                              const isc::dhcp::ConstSubnetPtr subnet);

    /// @brief Adds a duration sample to a MonitoredDuration.
    ///
    /// The MonitoredDuration identified by the given key is fetched from
    /// the store and updated with the sample. If the update returns the
    /// duration this means it is time to report the duration via StatsMgr.
    /// The reported mean is then checked against an alarm, if one exists.
    /// If the check returns the alarm, then the alarm has undergone a
    /// reportable event and is passed to reporting.
    ///
    /// @param key identifies the duration to update.
    /// @param sample amount of time that elapsed between the two events
    /// identified in the key.
    void addDurationSample(DurationKeyPtr key, const Duration& sample);

    /// @brief Emits an entry to StatsMgr for a given duration.
    ///
    /// Calculates the mean duration for the reportable interval and
    /// reports the value to StatsMgr if stat-mgr-reporting is true.
    ///
    /// @param duration duration to report.
    ///
    /// @return Always returns the mean duration for reportable interval.
    Duration reportToStatsMgr(MonitoredDurationPtr duration);

    /// @brief Emits a report for a given alarm.
    ///
    /// Emits a WARN log if the alarm state is TRIGGERED or an
    /// INFO log if it is CLEARED. This may expand in the future to
    /// accommodate additional reporting mechanisms.
    ///
    /// @param alarm Alarm to report.
    /// @param mean Duration mean which caused the state transition.
    void reportAlarm(AlarmPtr alarm, const Duration& mean);

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

    /// @brief perfmon-control command handler
    ///
    /// This command sets enable-monitoring and/or stats-mgr-reporting (affects
    /// in memory value(s) only).
    ///
    /// @code
    /// {
    ///     "command": "perfmon-control",
    ///     "arguments": {
    ///         "enable-monitoring": true,
    ///         "stats-mgr-reporting": true
    ///      }
    /// }
    /// @endcode
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// arguments accordingly. Regardless of which arguments, if any, were
    /// specified the command will always return the new/current values
    /// for both settings.
    ///
    /// @code
    /// "arguments": {
    ///     "enable-monitoring": true,
    ///     "stats-mgr-reporting": true
    ///  },
    ///  "result": 0,
    ///  "text": "perfmon-control success"
    /// }
    /// @endcode
    ///
    /// @param handle Callout context - which is expected to contain the
    /// command JSON text in the "command" argument
    /// @return result of the operation
    int perfmonControlHandler(hooks::CalloutHandle& handle);

    /// @brief perfmon-get-all-durations handler
    ///
    /// This command fetches all of the monitored durations and their previous
    /// intervals (if one).
    ///
    /// @code
    /// {
    ///     "command": "perfmon-get-all-durations",
    ///     "arguments": {
    ///         "result-set-format": true
    ///      }
    /// }
    /// @endcode
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// arguments accordingly.  If result-set-format is false (the default) the
    /// durations are returned as a list of Elements:
    ///
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "perfmon-get-all-durations: n rows found",
    ///     "arguments": {
    ///         "result-set-format": false,
    ///         "interval-width-secs": 5,
    ///         "timestamp": "2024-01-18 10:11:20.594800"
    ///         "durations": [{
    ///                 "duration-key": {
    ///                     "query-type": "discover",
    ///                     "response-type": "offer",
    ///                     "start-event": "socket_received",
    ///                     "stop-event": "buffer_read",
    ///                     "subnet-id": 10
    ///                 },
    ///             "start-time": "2024-01-18 10:11:19.498739",
    ///             "occurrences": 105,
    ///             "min-duration-usecs": 5300,
    ///             "max-duration-usecs": 9000,
    ///             "total-duration-usecs": 786500
    ///             },
    ///         ..
    ///         ]
    ///     },
    /// }
    /// @endcode
    ///
    /// If result-set-format is true, the durations are returned in a more compact format,
    /// patterned after an SQL result set:
    ///
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "perfmon-get-all-durations: n rows found",
    ///     "arguments": {
    ///         "result-set-format": true,
    ///         "interval-width-secs": 5,
    ///         "timestamp": "2024-01-18 10:11:20.594800"
    ///         "durations-result-set": {
    ///             "columns": [
    ///                 "subnet-id", "query-type", "response-type", "start-event", "end-event",
    ///                 "interval start", "occurrences", "min-duration-usecs", "max-duration-usecs",
    ///                 "total-duration-usecs"
    ///             ],
    ///             "rows": [
    ///                 [
    ///                     10, "discover", "offer", "socket_received", "buffer_read",
    ///                     "2024-01-18 10:11:19.498739",  105, 5300, 9000, 786500
    ///                 ],
    ///                 ..
    ///             ]
    ///         }
    ///     }
    /// }
    /// @endcode
    ///
    /// @param handle Callout context - which is expected to contain the
    /// command JSON text in the "command" argument
    /// @return result of the operation
    int perfmonGetAllDurationsHandler(hooks::CalloutHandle& handle);

    /// @brief Renders a list of MonitoredDurations as a map of individual Elements
    ///
    /// @param durations collection of durations to convert
    data::ElementPtr formatDurationDataAsElements(MonitoredDurationCollectionPtr durations) const;

    /// @brief Renders a list of MonitoredDurations as a result set
    ///
    /// The result set Element will be as shown below:
    ///
    /// @code
    ///     "durations-result-set": {
    ///         "columns": [
    ///             "subnet-id", "query-type", "response-type", "start-event", "end-event",
    ///             "interval start", "occurrences", "min-duration-usecs", "max-duration-usecs",
    ///             "total-duration-usecs"
    ///         ],
    ///         "rows": [
    ///             [
    ///                 10, "discover", "offer", "socket_received", "buffer_read",
    ///                 "2024-01-18 10:11:19.498739",  105, 5300, 9000, 786500
    ///             ],
    ///         ..
    ///         ]
    /// @endcode
    ///
    /// @param durations collection of durations to convert
    data::ElementPtr formatDurationDataAsResultSet(MonitoredDurationCollectionPtr durations) const;

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

protected:
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
