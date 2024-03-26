// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
#include <config.h>

#include <perfmon_mgr.h>

namespace isc {
namespace perfmon {

using namespace isc::data;
using namespace boost::posix_time;

PerfMonMgr::PerfMonMgr(uint16_t family_)
    : PerfMonConfig(family_) {
    // Set defaults.
    interval_duration_ = seconds(interval_width_secs_);
    alarm_report_interval_ = seconds(alarm_report_secs_);
    duration_store_.reset(new MonitoredDurationStore(family_, interval_duration_));
}

void PerfMonMgr::configure(const ConstElementPtr& params) {
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

    // Set convenience values.
    interval_duration_ = seconds(interval_width_secs_);
    alarm_report_interval_ = seconds(alarm_report_secs_);

    // Re-create the duration store.
    duration_store_.reset(new MonitoredDurationStore(family_, interval_duration_));
}

void PerfMonMgr::processPktEventStack(isc::dhcp::PktPtr /* query */,
                                      isc::dhcp::PktPtr  /* response */,
                                      const isc::dhcp::SubnetID&  /* subnet_id */) {
    isc_throw (NotImplemented, __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__);
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
PerfMonMgr::reportToStatsMgr(MonitoredDurationPtr /* duration */) {
    isc_throw (NotImplemented, __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__);
}

void
PerfMonMgr::reportAlarm(AlarmPtr /* alarm */, const Duration& /* average */) {
    isc_throw (NotImplemented, __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__);
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
