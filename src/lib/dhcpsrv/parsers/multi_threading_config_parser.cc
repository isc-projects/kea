// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <dhcpsrv/srv_config.h>
#include <dhcpsrv/parsers/multi_threading_config_parser.h>
#include <util/multi_threading_mgr.h>

using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace dhcp {

void
MultiThreadingConfigParser::parse(SrvConfig& srv_cfg,
                                  const ConstElementPtr& value) {
    if (!value) {
        return;
    }
    if (value->getType() != Element::map) {
        isc_throw(DhcpConfigError, "multi-threading is supposed to be a map");
    }

    // enable-multi-threading is mandatory
    auto enabled = getBoolean(value, "enable-multi-threading");

    // thread-pool-size is not mandatory
    if (value->get("thread-pool-size")) {
        auto thread_pool_size = getInteger(value, "thread-pool-size");
        uint32_t max_size = std::numeric_limits<uint16_t>::max();
        if (thread_pool_size < 0) {
            isc_throw(DhcpConfigError,
                      "thread pool size code must not be negative ("
                      << getPosition("thread-pool-size", value) << ")");
        }
        if (thread_pool_size > max_size) {
            isc_throw(DhcpConfigError, "invalid thread pool size '"
                      << thread_pool_size << "', it must not be greater than '"
                      << max_size << "' ("
                      << getPosition("thread-pool-size", value) << ")");
        }
    }

    // packet-queue-size is not mandatory
    if (value->get("packet-queue-size")) {
        auto packet_queue_size = getInteger(value, "packet-queue-size");
        uint32_t max_size = std::numeric_limits<uint16_t>::max();
        if (packet_queue_size < 0) {
            isc_throw(DhcpConfigError,
                      "packet queue size code must not be negative ("
                      << getPosition("packet-queue-size", value) << ")");
        }
        if (packet_queue_size > max_size) {
            isc_throw(DhcpConfigError, "invalid packet queue size '"
                      << packet_queue_size << "', it must not be greater than '"
                      << max_size << "' ("
                      << getPosition("packet-queue-size", value) << ")");
        }
    }

    srv_cfg.setDHCPMultiThreading(value);
    MultiThreadingMgr::instance().setMode(enabled);
}

}  // namespace dhcp
}  // namespace isc
