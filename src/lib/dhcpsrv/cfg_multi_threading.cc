// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <cfg_multi_threading.h>
#include <util/multi_threading_mgr.h>

using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace dhcp {

void
CfgMultiThreading::apply(ConstElementPtr value) {
    // Note the default values are set by extract, not here!
    bool enabled = false;
    uint32_t thread_count = 0;
    uint32_t queue_size = 0;
    CfgMultiThreading::extract(value, enabled, thread_count, queue_size);
    MultiThreadingMgr::instance().apply(enabled, thread_count, queue_size);
}

void
CfgMultiThreading::extract(ConstElementPtr value, bool& enabled,
                           uint32_t& thread_count, uint32_t& queue_size) {
    enabled = true;
    thread_count = 0;
    queue_size = 0;
    if (value) {
        if (value->get("enable-multi-threading")) {
            enabled = SimpleParser::getBoolean(value, "enable-multi-threading");
        }

        if (value->get("thread-pool-size")) {
            thread_count = SimpleParser::getInteger(value, "thread-pool-size");
        }

        if (value->get("packet-queue-size")) {
            queue_size = SimpleParser::getInteger(value, "packet-queue-size");
        }
    }
}

}  // namespace dhcp
}  // namespace isc
