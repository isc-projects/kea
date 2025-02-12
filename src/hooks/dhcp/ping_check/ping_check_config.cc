// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ping_check_config.h>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;

namespace isc {
namespace ping_check {

const data::SimpleKeywords
PingCheckConfig::CONFIG_KEYWORDS =
{
    { "enable-ping-check",      Element::boolean },
    { "min-ping-requests",      Element::integer },
    { "reply-timeout",          Element::integer },
    { "ping-cltt-secs",         Element::integer},
    { "ping-channel-threads",   Element::integer}
};

PingCheckConfig::PingCheckConfig() :
    enable_ping_check_(true),
    min_ping_requests_(1),
    reply_timeout_(100),
    ping_cltt_secs_(60),
    ping_channel_threads_(0) {
}

void
PingCheckConfig::parse(data::ConstElementPtr config) {
    // Use a local instance to collect values.  This way we
    // avoid corrupting current values if there are any errors.
    PingCheckConfig local;

    // Note checkKeywords() will throw DhcpConfigError if there is a problem.
    SimpleParser::checkKeywords(CONFIG_KEYWORDS, config);
    ConstElementPtr value = config->get("enable-ping-check");
    if (value) {
        local.setEnablePingCheck(value->boolValue());
    }

    value = config->get("min-ping-requests");
    if (value) {
        int64_t val = value->intValue();
        if (val <= 0) {
            isc_throw(DhcpConfigError, "invalid min-ping-requests: '"
                      << val << "', must be greater than 0");
        }

        local.setMinPingRequests(static_cast<size_t>(val));
    }

    value = config->get("reply-timeout");
    if (value) {
        int64_t val = value->intValue();
        if (val <= 0) {
            isc_throw(DhcpConfigError, "invalid reply-timeout: '"
                      << val << "', must be greater than 0");
        }

        local.setReplyTimeout(static_cast<size_t>(val));
    }

    value = config->get("ping-cltt-secs");
    if (value) {
        int64_t val = value->intValue();
        if (val < 0) {
            isc_throw(DhcpConfigError, "invalid ping-cltt-secs: '"
                      << val << "', cannot be less than 0");
        }

        local.setPingClttSecs(static_cast<size_t>(val));
    }

    value = config->get("ping-channel-threads");
    if (value) {
        int64_t val = value->intValue();
        if (val < 0) {
            isc_throw(DhcpConfigError, "invalid ping-channel-threads: '"
                      << val << "', cannot be less than 0");
        }

        local.setPingChannelThreads(static_cast<size_t>(val));
    }

    // All values good, copy from local instance.
    *this = local;
}

} // end of namespace ping_check
} // end of namespace isc
