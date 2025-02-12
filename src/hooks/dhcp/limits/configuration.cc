// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/dhcp_config_error.h>
#include <exceptions/exceptions.h>
#include <limits/configuration.h>
#include <limits/limits_logger.h>
#include <log/macros.h>

#include <string>

namespace isc {
namespace limits {

using namespace isc::dhcp;

using namespace std;

using isc::data::ConstElementPtr;
using isc::log::DBGLVL_TRACE_BASIC;

RateLimit::RateLimit(string const& text) {
    // Parse string.
    char const* pkt_per(" packets per ");
    size_t index(text.find(pkt_per));
    if (index == text.npos) {
        pkt_per = " packet per ";
        index = text.find(pkt_per);
        if (index == text.npos) {
            isc_throw(ConfigError,
                      "expected rate limit of format <n> packet[s] per <time-unit>, got: " << text);
        }
    }

    // Determine the number of allowed packets.
    int64_t const allowed_packets(stoll(text.substr(0, index)));
    checkForLimitBoundaries<decltype(allowed_packets_)>(allowed_packets);
    allowed_packets_ = allowed_packets;

    // Determine the time unit and convert it to a chrono::duration type.
    string const time_period(text.substr(index + strlen(pkt_per)));
    if (time_period == "second") {
        time_unit_ = chrono::seconds(1);
    } else if (time_period == "minute") {
        time_unit_ = chrono::minutes(1);
    } else if (time_period == "hour") {
        time_unit_ = chrono::hours(1);
    } else if (time_period == "day") {
        time_unit_ = chrono::hours(24);
    } else if (time_period == "week") {
        time_unit_ = chrono::hours(7 * 24);
    } else if (time_period == "month") {
        time_unit_ = chrono::hours(30 * 24);
    } else if (time_period == "year") {
        time_unit_ = chrono::hours(365 * 24);
    } else {
        isc_throw(ConfigError, "invalid time period " << time_period);
    }

    // Keep the entire text, it's used for logging purposes.
    text_ = text;
}

// -- AddressLimitConfiguration --

const std::string&
AddressLimitConfiguration::key() const {
    static std::string limit_str("address-limit");
    return (limit_str);
}

void
AddressLimitConfiguration::logClientClassLimit(ClientClass const& client_class,
                                                       ConstElementPtr const& limit) {
    if (!limit) {
        return;
    }

    int64_t const limit_candidate(limit->intValue());
    checkForLimitBoundaries<LeaseLimit>(limit_candidate);

    LOG_DEBUG(limits_logger, DBGLVL_TRACE_BASIC, LIMITS_CONFIGURED_ADDRESS_LIMIT_BY_CLIENT_CLASS)
        .arg(limit_candidate)
        .arg(client_class);
}

void
AddressLimitConfiguration::logSubnetLimit(SubnetID const subnet_id,
                                          ConstElementPtr const& limit) {
    if (!limit) {
        return;
    }

    int64_t const limit_candidate(limit->intValue());
    checkForLimitBoundaries<LeaseLimit>(limit_candidate);

    LOG_DEBUG(limits_logger, DBGLVL_TRACE_BASIC, LIMITS_CONFIGURED_ADDRESS_LIMIT_BY_SUBNET)
        .arg(limit_candidate)
        .arg(subnet_id);
}

// -- PrefixLimitConfiguration --

const std::string&
PrefixLimitConfiguration::key() const {
    static std::string limit_str ("prefix-limit");
    return (limit_str);
}

void
PrefixLimitConfiguration::logClientClassLimit(ClientClass const& client_class,
                                                      ConstElementPtr const& limit) {
    if (!limit) {
        return;
    }

    int64_t const limit_candidate(limit->intValue());
    checkForLimitBoundaries<LeaseLimit>(limit_candidate);

    LOG_DEBUG(limits_logger, DBGLVL_TRACE_BASIC, LIMITS_CONFIGURED_PREFIX_LIMIT_BY_CLIENT_CLASS)
        .arg(limit_candidate)
        .arg(client_class);
}

void
PrefixLimitConfiguration::logSubnetLimit(SubnetID const subnet_id,
                                         ConstElementPtr const& limit) {
    if (!limit) {
        return;
    }

    int64_t const limit_candidate(limit->intValue());
    checkForLimitBoundaries<LeaseLimit>(limit_candidate);

    LOG_DEBUG(limits_logger, DBGLVL_TRACE_BASIC, LIMITS_CONFIGURED_PREFIX_LIMIT_BY_SUBNET)
        .arg(limit_candidate)
        .arg(subnet_id);
}

// -- RateLimitConfiguration --

const std::string&
RateLimitConfiguration::key() const {
    static std::string limit_str("rate-limit");
    return (limit_str);
}

void
RateLimitConfiguration::logClientClassLimit(ClientClass const& client_class,
                                            ConstElementPtr const& limit) {
    if (!limit) {
        return;
    }

    string const& limit_candidate = limit->stringValue();
    RateLimit rate_limit(limit_candidate);

    LOG_DEBUG(limits_logger, DBGLVL_TRACE_BASIC, LIMITS_CONFIGURED_RATE_LIMIT_BY_CLIENT_CLASS)
        .arg(limit_candidate)
        .arg(client_class);
}

void
RateLimitConfiguration::logSubnetLimit(SubnetID const subnet_id,
                                               ConstElementPtr const& limit) {
    if (!limit) {
        return;
    }

    string const& limit_candidate = limit->stringValue();
    RateLimit rate_limit(limit_candidate);

    LOG_DEBUG(limits_logger, DBGLVL_TRACE_BASIC, LIMITS_CONFIGURED_RATE_LIMIT_BY_SUBNET)
        .arg(limit_candidate)
        .arg(subnet_id);
}

}  // namespace limits
}  // namespace isc
