// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
#include <config.h>

#include <perfmon_log.h>
#include <perfmon_mgr.h>
#include <stats/stats_mgr.h>
#include <dhcp/dhcp6.h>
#include <util/boost_time_utils.h>

namespace isc {
namespace perfmon {

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::stats;
using namespace isc::util;
using namespace boost::posix_time;

PerfMonMgr::PerfMonMgr(uint16_t family_)
    : PerfMonConfig(family_) {
    init();
}

void
PerfMonMgr::init() {
    // Set convenience values.
    interval_duration_ = seconds(interval_width_secs_);
    alarm_report_interval_ = seconds(alarm_report_secs_);

    // Re-create the duration store.
    duration_store_.reset(new MonitoredDurationStore(family_, interval_duration_));
}

void
PerfMonMgr::configure(const ConstElementPtr& params) {
    if (!params) {
        // User wants passive logging only.
        setEnableMonitoring(false);
        return;
    }

    if (params->getType() != Element::map) {
        isc_throw(dhcp::DhcpConfigError, "params must be an Element::map");
        return;
    }

    // Parse 'parameters' map.
    try {
        parse(params);
    } catch (std::exception& ex) {
        isc_throw(dhcp::DhcpConfigError,
                  "PerfMonMgr::configure failed - " << ex.what());
    }

    init();
}

void
PerfMonMgr::processPktEventStack(isc::dhcp::PktPtr query,
                                 isc::dhcp::PktPtr response,
                                 const isc::dhcp::SubnetID& subnet_id) {
    if (!query) {
        isc_throw(Unexpected, "PerfMonMgr::processPktEventStack - query is empty!");
    }
    uint16_t query_type = query->getType();

    // Response is optional to allow for future support of responseless queries
    // such as declines or releases.
    uint16_t response_type;
    if (!response) {
       response_type = (family_ == AF_INET ? static_cast<uint16_t>(DHCP_NOTYPE)
                                           : static_cast<uint16_t>(DHCPV6_NOTYPE));
    } else {
       response_type = response->getType();
    }

    // Sanity check the message types.
    DurationKey::validateMessagePair(family_, query_type, response_type);

    auto events = query->getPktEvents();
    if (events.size() < 2) {
        isc_throw(Unexpected, "PerfMonMgr::processPtkEventStack - incomplete stack, size: "
                              << events.size());
    }

    // no subnet id?

    boost::posix_time::ptime start_time;
    boost::posix_time::ptime prev_time;
    std::string prev_event_label;
    bool first_pass = true;
    for (auto const& event : events) {
        if (first_pass) {
            prev_event_label = event.label_;
            prev_time = event.timestamp_;
            start_time = prev_time;
            first_pass = false;
        } else {
            Duration sample = event.timestamp_ - prev_time;
            DurationKeyPtr key(new DurationKey(family_, query_type, response_type,
                               prev_event_label, event.label_, subnet_id));
            addDurationSample(key, sample);

            // Update global duration.
            if (subnet_id != SUBNET_ID_GLOBAL) {
                key->setSubnetId(SUBNET_ID_GLOBAL);
                addDurationSample(key, sample);
            }

            prev_event_label = event.label_;
            prev_time = event.timestamp_;
        }
    }

    // Generate composite total.
    Duration sample = prev_time - start_time;
    DurationKeyPtr key(new DurationKey(family_, query_type, response_type,
                       "composite", "total_response", subnet_id));
    addDurationSample(key, sample);
    // Update global duration.
    if (subnet_id != SUBNET_ID_GLOBAL) {
        key->setSubnetId(SUBNET_ID_GLOBAL);
        addDurationSample(key, sample);
    }
}

void
PerfMonMgr::addDurationSample(DurationKeyPtr key, const Duration& sample) {
    // Update duration - duration is only returned if its time to report.
    MonitoredDurationPtr duration = duration_store_->addDurationSample(key, sample);
    if (duration) {
        // Report to stat mgr, returns average duration.
        Duration average = reportToStatsMgr(duration);

        // Check the average against an alarm, if one exists.
        AlarmPtr alarm = alarm_store_->checkDurationSample(duration, average, alarm_report_interval_);

        // If an alarm had a reportable outcome, report it.
        if (alarm) {
            reportAlarm(alarm, average);
        }
    }
}

Duration
PerfMonMgr::reportToStatsMgr(MonitoredDurationPtr duration) {
    if (!duration) {
        isc_throw(BadValue, "reportToStatsMgr - duration is empty");
    }

    auto previous_interval = duration->getPreviousInterval();
    if (!previous_interval) {
        isc_throw(BadValue, "reportToStatsMgr - duration previous interval is empty");
    }

    auto average = previous_interval->getAverageDuration();
    if (getStatsMgrReporting()) {
        StatsMgr::instance().setValue(duration->getStatName("average-ms"),
                                      static_cast<int64_t>(average.total_milliseconds()));
    }

    /// @todo - decide if we want to report min and max values too.

    return(average);
}

void
PerfMonMgr::reportAlarm(AlarmPtr alarm, const Duration& average) {
    std::string label = alarm->getLabel();
    switch(alarm->getState()) {
    case Alarm::CLEAR:
        LOG_INFO(perfmon_logger, PERFMON_ALARM_CLEARED)
                .arg(alarm->getLabel())
                .arg(average)
                .arg(alarm->getLowWater().total_milliseconds());
        break;

    case Alarm::TRIGGERED:
        LOG_WARN(perfmon_logger, PERFMON_ALARM_TRIGGERED)
                .arg(alarm->getLabel())
                .arg(ptimeToText(alarm->getStosTime(), 3))
                .arg(average)
                .arg(alarm->getHighWater().total_milliseconds());
        alarm->setLastHighWaterReport();
        alarm_store_->updateAlarm(alarm);
        break;

    case Alarm::DISABLED:
        // Shouldn't happen. We'll silently ignore for now.
        break;
    }
}

void
PerfMonMgr::reportTimerExpired() {
    isc_throw (NotImplemented, __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__);
}

void
PerfMonMgr::setNextReportExpiration() {
    isc_throw (NotImplemented, __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__);
}

} // end of namespace perfmon
} // end of namespace isc
