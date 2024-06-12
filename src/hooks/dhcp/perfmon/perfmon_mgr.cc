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
#include <cc/simple_parser.h>
#include <config/cmd_response_creator.h>
#include <stats/stats_mgr.h>
#include <dhcp/dhcp6.h>
#include <util/boost_time_utils.h>

namespace isc {
namespace perfmon {

using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::log;
using namespace isc::stats;
using namespace isc::util;
using namespace boost::posix_time;

PerfMonMgr::PerfMonMgr(uint16_t family_)
    : PerfMonConfig(family_), mutex_(new std::mutex) {
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
PerfMonMgr::processPktEventStack(PktPtr query, PktPtr response, SubnetPtr subnet) {
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

    // If we're here without a selected subnet, use global subnet id.
    SubnetID subnet_id = (subnet ? subnet->getID() : SUBNET_ID_GLOBAL);

    LOG_DEBUG(perfmon_logger, DBGLVL_TRACE_DETAIL,
              (family_ == AF_INET ? PERFMON_DHCP4_PKT_EVENTS : PERFMON_DHCP6_PKT_EVENTS))
            .arg(query->getLabel())
            .arg(query->dumpPktEvents());

    // If monitoring is disabled, then punt.
    if (!enable_monitoring_) {
        return;
    }

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
        isc_throw(BadValue, "reportToStatsMgr - duration is empty!");
    }

    auto previous_interval = duration->getPreviousInterval();
    if (!previous_interval) {
        isc_throw(BadValue, "reportToStatsMgr - duration previous interval is empty!");
    }

    auto average = previous_interval->getAverageDuration();
    if (getStatsMgrReporting()) {
        StatsMgr::instance().setValue(duration->getStatName("average-usecs"),
                                       static_cast<int64_t>(average.total_microseconds()));
    }

    /// @todo - decide if we want to report min and max values too.

    return (average);
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

int
PerfMonMgr::perfmonControlHandler(hooks::CalloutHandle& handle) {
    static SimpleKeywords keywords = {
        { "enable-monitoring",   Element::boolean },
        { "stats-mgr-reporting", Element::boolean }
    };

    std::string txt = "(missing parameters)";
    ElementPtr result = Element::createMap();
    ConstElementPtr response;

    // Extract the command and then the parameters
    try {
        extractCommand(handle);
        if (cmd_args_) {
            txt = cmd_args_->str();
        }

        if (cmd_args_) {
            SimpleParser::checkKeywords(keywords, cmd_args_);

            ConstElementPtr elem = cmd_args_->get("enable-monitoring");
            if (elem) {
                enable_monitoring_ = elem->boolValue();
            }

            elem = cmd_args_->get("stats-mgr-reporting");
            if (elem) {
                stats_mgr_reporting_ = elem->boolValue();
            }
        }

        LOG_INFO(perfmon_logger, PERFMON_CMDS_CONTROL_OK)
                .arg(enable_monitoring_ ? "enabled" : "disabled")
                .arg(stats_mgr_reporting_ ? "enabled" : "disabled");

        result->set("enable-monitoring", Element::create(enable_monitoring_));
        result->set("stats-mgr-reporting", Element::create(stats_mgr_reporting_));
        response = createAnswer(CONTROL_RESULT_SUCCESS, "perfmon-control success", result);
    } catch (const std::exception& ex) {
        LOG_ERROR(perfmon_logger, PERFMON_CMDS_CONTROL_ERROR)
                  .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    setResponse(handle, response);
    return (0);
}

int
PerfMonMgr::perfmonGetAllDurationsHandler(hooks::CalloutHandle& handle) {
    static SimpleKeywords keywords = {
        { "result-set-format",   Element::boolean }
    };

    ElementPtr result = Element::createMap();
    ConstElementPtr response;

    try {
        // Extract the command and then the parameters
        bool result_set_format = false;
        extractCommand(handle);
        if (cmd_args_) {
            SimpleParser::checkKeywords(keywords, cmd_args_);

            ConstElementPtr elem = cmd_args_->get("result-set-format");
            if (elem) {
                result_set_format = elem->boolValue();
            }
        }

        // Fetch the durations from the store.
        auto durations = duration_store_->getAll();
        auto rows = durations->size();
        ElementPtr formatted_durations;

        // Format them either as a list of elements or as a result set
        if (!result_set_format) {
            formatted_durations = formatDurationDataAsElements(durations);
        } else {
            formatted_durations = formatDurationDataAsResultSet(durations);
        }

        //  Construct the result
        result->set("interval-width-secs", Element::create(getIntervalWidthSecs()));
        result->set("timestamp", Element::create(isc::util::ptimeToText(PktEvent::now())));
        result->set((result_set_format ? "durations-result-set" : "durations"), formatted_durations);

        std::ostringstream oss;
        oss << "perfmon-get-all-durations: " << rows << " found";

        response = createAnswer(CONTROL_RESULT_SUCCESS, oss.str(), result);
        LOG_INFO(perfmon_logger, PERFMON_CMDS_GET_ALL_DURATIONS_OK)
                 .arg(rows);
    } catch (const std::exception& ex) {
        LOG_ERROR(perfmon_logger, PERFMON_CMDS_GET_ALL_DURATIONS_ERROR)
                  .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    setResponse(handle, response);
    return (0);
}

ElementPtr
PerfMonMgr::formatDurationDataAsElements(MonitoredDurationCollectionPtr durations) const {
    // Create the list.
    ElementPtr duration_list = Element::createList();

    // Add in the duration elements.
    for (auto const& d : *durations) {
        ElementPtr element = d->toElement();
        duration_list->add(element);
    }

    return (duration_list);
}

ElementPtr
PerfMonMgr::formatDurationDataAsResultSet(MonitoredDurationCollectionPtr /*durations */) const{
    isc_throw (NotImplemented, "Not Implemented - " << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__);
#if 0
    // Create the result-set map and add it to the wrapper.
    ElementPtr result_set = Element::createMap();
    result_wrapper->set("result-set", result_set);

    // Create the list of column names and add it to the result set.
    ElementPtr columns = Element::createList();
    for (auto const& label : column_labels) {
        columns->add(Element::create(label));
    }
    result_set->set("columns", columns);

    // Create the empty value_rows list, add it and then return it.
    ElementPtr value_rows = Element::createList();
    result_set->set("rows", value_rows);
    if (durations.empty()) {
        return;
    }

    return (value_rows);
        for (auto const& d : *durations) {
            const auto& reported_interval =  d->getPreviousInterval();
            if (reported_interval) {
                std::string label = d->getLabel();

        }
#endif
}




} // end of namespace perfmon
} // end of namespace isc
