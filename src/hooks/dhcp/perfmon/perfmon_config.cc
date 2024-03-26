// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <perfmon_config.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace boost::posix_time;

namespace isc {
namespace perfmon {

const data::SimpleKeywords
DurationKeyParser::CONFIG_KEYWORDS =
{
    {"query-type",        Element::string},
    {"response-type",     Element::string},
    {"start-event",       Element::string},
    {"stop-event",        Element::string},
    {"subnet-id",         Element::integer}
};

uint16_t
DurationKeyParser::getMessageNameType4(const std::string& name) {
    static std::map<std::string, uint16_t> name_type_map = {
        {"",                        DHCP_NOTYPE},
        {"*",                       DHCP_NOTYPE},
        {"DHCPDISCOVER",            DHCPDISCOVER},
        {"DHCPOFFER",               DHCPOFFER},
        {"DHCPREQUEST",             DHCPREQUEST},
        {"DHCPDECLINE",             DHCPDECLINE},
        {"DHCPACK",                 DHCPACK},
        {"DHCPNAK",                 DHCPNAK},
        {"DHCPRELEASE",             DHCPRELEASE},
        {"DHCPINFORM",              DHCPINFORM},
        {"DHCPLEASEQUERY",          DHCPLEASEQUERY},
        {"DHCPLEASEUNASSIGNED",     DHCPLEASEUNASSIGNED},
        {"DHCPLEASEUNKNOWN",        DHCPLEASEUNKNOWN},
        {"DHCPLEASEACTIVE",         DHCPLEASEACTIVE},
        {"DHCPBULKLEASEQUERY",      DHCPBULKLEASEQUERY},
        {"DHCPLEASEQUERYDONE",      DHCPLEASEQUERYDONE},
        {"DHCPLEASEQUERYSTATUS",    DHCPLEASEQUERYSTATUS},
        {"DHCPTLS",                 DHCPTLS}
    };

    try {
        const auto& found = name_type_map.at(name);
        return (found);
    } catch (const std::out_of_range& ex) {
        isc_throw(BadValue, "'" << name << "' is not a valid DHCP message type");
    }
}

uint16_t
DurationKeyParser::getMessageNameType6(const std::string& name) {
    static std::map<std::string, uint16_t> name_type_map = {
        {"",                        DHCPV6_NOTYPE},
        {"*",                       DHCPV6_NOTYPE},
        {"SOLICIT",                 DHCPV6_SOLICIT},
        {"ADVERTISE",               DHCPV6_ADVERTISE},
        {"REQUEST",                 DHCPV6_REQUEST},
        {"CONFIRM",                 DHCPV6_CONFIRM},
        {"RENEW",                   DHCPV6_RENEW},
        {"REBIND",                  DHCPV6_REBIND},
        {"REPLY",                   DHCPV6_REPLY},
        {"RELEASE",                 DHCPV6_RELEASE},
        {"DECLINE",                 DHCPV6_DECLINE},
        {"RECONFIGURE",             DHCPV6_RECONFIGURE},
        {"INFORMATION_REQUEST",     DHCPV6_INFORMATION_REQUEST},
        {"RELAY_FORW",              DHCPV6_RELAY_FORW},
        {"RELAY_REPL",              DHCPV6_RELAY_REPL},
        {"LEASEQUERY",              DHCPV6_LEASEQUERY},
        {"LEASEQUERY_REPLY",        DHCPV6_LEASEQUERY_REPLY},
        {"LEASEQUERY_DONE",         DHCPV6_LEASEQUERY_DONE},
        {"LEASEQUERY_DATA",         DHCPV6_LEASEQUERY_DATA},
        {"RECONFIGURE_REQUEST",     DHCPV6_RECONFIGURE_REQUEST},
        {"RECONFIGURE_REPLY",       DHCPV6_RECONFIGURE_REPLY},
        {"DHCPV4_QUERY",            DHCPV6_DHCPV4_QUERY},
        {"DHCPV4_RESPONSE",         DHCPV6_DHCPV4_RESPONSE},
        {"ACTIVELEASEQUERY",        DHCPV6_ACTIVELEASEQUERY},
        {"STARTTLS",                DHCPV6_STARTTLS},
        {"BNDUPD",                  DHCPV6_BNDUPD},
        {"BNDREPLY",                DHCPV6_BNDREPLY},
        {"POOLREQ",                 DHCPV6_POOLREQ},
        {"POOLRESP",                DHCPV6_POOLRESP},
        {"UPDREQ",                  DHCPV6_UPDREQ},
        {"UPDREQALL",               DHCPV6_UPDREQALL},
        {"UPDDONE",                 DHCPV6_UPDDONE},
        {"CONNECT",                 DHCPV6_CONNECT},
        {"CONNECTREPLY",            DHCPV6_CONNECTREPLY},
        {"DISCONNECT",              DHCPV6_DISCONNECT},
        {"STATE",                   DHCPV6_STATE},
        {"CONTACT",                 DHCPV6_CONTACT}
    };

    try {
        const auto& found = name_type_map.at(name);
        return (found);
    } catch (const std::out_of_range& ex) {
        isc_throw(BadValue, "'" << name << "' is not a valid DHCPV6 message type");
    }
}

uint16_t
DurationKeyParser::getMessageType(data::ConstElementPtr config,
                                  uint16_t family,
                                  const std::string& param_name,
                                  bool required /*= true */) {
    // Parse members.
    uint16_t msg_type = 0;
    ConstElementPtr elem = config->get(param_name);
    if (elem) {
        try {
            msg_type = (family == AF_INET ? getMessageNameType4(elem->stringValue())
                                          : getMessageNameType6(elem->stringValue()));
        } catch (const std::exception& ex) {
            isc_throw(DhcpConfigError, "'" << param_name << "' parameter is invalid, " << ex.what());
        }
    } else {
        if (required) {
            isc_throw(DhcpConfigError, "'" << param_name << "' parameter is required");
        }
    }

    return (msg_type);
}

DurationKeyPtr
DurationKeyParser::parse(data::ConstElementPtr config, uint16_t family) {
    // Note checkKeywords() will throw DhcpConfigError if there is a problem.
    SimpleParser::checkKeywords(CONFIG_KEYWORDS, config);

    // Parse members.
    auto query_type = getMessageType(config, family, "query-type");

    auto response_type = getMessageType(config, family, "response-type");

    std::string start_event;
    ConstElementPtr elem = config->get("start-event");
    if (elem) {
        start_event = elem->stringValue();
    } else {
        isc_throw(DhcpConfigError, "'start-event' parameter is required");
    }

    std::string stop_event;
    elem = config->get("stop-event");
    if (elem) {
        stop_event = elem->stringValue();
    } else {
        isc_throw(DhcpConfigError, "'stop-event' parameter is required");
    }

    SubnetID subnet_id = SUBNET_ID_GLOBAL;
    elem = config->get("subnet-id");
    if (elem) {
        subnet_id = static_cast<SubnetID>(elem->intValue());
    }

    return (DurationKeyPtr(new DurationKey(family, query_type, response_type,
                                           start_event, stop_event, subnet_id)));
}

data::ElementPtr
DurationKeyParser::toElement(DurationKeyPtr key) {
    if (!key) {
        isc_throw(BadValue, "DurationKeyParser::toElement() - key is empty");
    }

    ElementPtr map = Element::createMap();
    if (key->getFamily() == AF_INET) {
        map->set("query-type", Element::create(Pkt4::getName(key->getQueryType())));
        map->set("response-type", Element::create(Pkt4::getName(key->getResponseType())));
    } else {
        map->set("query-type", Element::create(Pkt6::getName(key->getQueryType())));
        map->set("response-type", Element::create(Pkt6::getName(key->getResponseType())));
    }

    map->set("start-event", Element::create(key->getStartEventLabel()));
    map->set("stop-event", Element::create(key->getStopEventLabel()));
    map->set("subnet-id", Element::create(static_cast<long long>(key->getSubnetId())));
    return (map);
}

const data::SimpleKeywords
AlarmParser::CONFIG_KEYWORDS =
{
    {"duration-key",    Element::map},
    {"enable-alarm",    Element::boolean},
    {"high-water-ms",   Element::integer},
    {"low-water-ms",    Element::integer}
};

AlarmPtr
AlarmParser::parse(data::ConstElementPtr config, uint16_t family) {
    // Note checkKeywords() will throw DhcpConfigError if there is a problem.
    SimpleParser::checkKeywords(CONFIG_KEYWORDS, config);

    // First parse the duration-key.
    ConstElementPtr elem = config->get("duration-key");
    if (!elem) {
        isc_throw(DhcpConfigError, "'duration-key'" <<" parameter is required");
    }

    DurationKeyPtr key = DurationKeyParser::parse(elem, family);

    // Parse scalar members.
    elem = config->get("enable-alarm");
    bool enable_alarm = (elem ? elem->boolValue() : true);

    elem = config->get("high-water-ms");
    uint64_t high_water_ms = 0;
    if (elem) {
        int64_t value = elem->intValue();
        if (value <= 0) {
            isc_throw(DhcpConfigError, "high-water-ms: '"
                       << value << "', must be greater than 0");
        }

        high_water_ms = value;
    } else {
        isc_throw(DhcpConfigError, "'high-water-ms'" <<" parameter is required");
    }

    elem = config->get("low-water-ms");
    uint64_t low_water_ms = 0;
    if (elem) {
        int64_t value = elem->intValue();
        if (value <= 0) {
            isc_throw(DhcpConfigError, "low-water-ms: '"
                       << value << "', must be greater than 0");
        }

        low_water_ms = value;
    } else {
        isc_throw(DhcpConfigError, "'low-water-ms'" <<" parameter is required");
    }

    if (low_water_ms >= high_water_ms) {
        isc_throw(DhcpConfigError, "'low-water-ms': " << low_water_ms
                   << ", must be less than 'high-water-ms': " << high_water_ms);
    }

    return (AlarmPtr(new Alarm(*key, milliseconds(low_water_ms),
                               milliseconds(high_water_ms), enable_alarm)));
}

const data::SimpleKeywords
PerfMonConfig::CONFIG_KEYWORDS =
{
    {"enable-monitoring",      Element::boolean},
    {"interval-width-secs",    Element::integer},
    {"stats-mgr-reporting",    Element::boolean},
    {"alarm-report-secs",      Element::integer},
    {"alarms",                 Element::list}
};

PerfMonConfig::PerfMonConfig(uint16_t family)
    : family_(family),
      enable_monitoring_(false),
      interval_width_secs_(60),
      stats_mgr_reporting_(true),
      alarm_report_secs_(300) {
    if (family_ != AF_INET && family_ != AF_INET6) {
        isc_throw (BadValue, "PerfmonConfig: family must be AF_INET or AF_INET6");
    }

    alarm_store_.reset(new AlarmStore(family_));
}

void
PerfMonConfig::parse(data::ConstElementPtr config) {
    // Use a local instance to collect values.  This way we
    // avoid corrupting current values if there are any errors.
    PerfMonConfig local(family_);

    // Note checkKeywords() will throw DhcpConfigError if there is a problem.
    SimpleParser::checkKeywords(CONFIG_KEYWORDS, config);

    // Parse members.
    ConstElementPtr elem = config->get("enable-monitoring");
    if (elem) {
        local.setEnableMonitoring(elem->boolValue());
    }

    elem = config->get("interval-width-secs");
    if (elem) {
        int64_t value = elem->intValue();
        if (value <= 0) {
            isc_throw(DhcpConfigError, "invalid interval-width-secs: '"
                       << value << "', must be greater than 0");
        }

        local.setIntervalWidthSecs(value);
    }

    elem = config->get("stats-mgr-reporting");
    if (elem) {
        local.setStatsMgrReporting(elem->boolValue());
    }

    elem = config->get("alarm-report-secs");
    if (elem) {
        int64_t value = elem->intValue();
        if (value < 0) {
            isc_throw(DhcpConfigError, "invalid alarm-report-secs: '"
                       << value << "', cannot be less than 0");
        }

        local.setAlarmReportSecs(value);
    }

    elem = config->get("alarms");
    if (elem) {
        local.parseAlarms(elem);
    }

    // All values good, shallow copy from local instance.
    *this = local;
}

void
PerfMonConfig::parseAlarms(data::ConstElementPtr config) {
    alarm_store_.reset(new AlarmStore(family_));
    for (auto const& alarm_elem : config->listValue()) {
        try {
            AlarmPtr alarm = AlarmParser::parse(alarm_elem, family_);
            alarm_store_->addAlarm(alarm);
        } catch (const std::exception& ex) {
            isc_throw(DhcpConfigError, "cannot add Alarm to store: " << ex.what());
        }
    }
}

} // end of namespace perfmon
} // end of namespace isc
