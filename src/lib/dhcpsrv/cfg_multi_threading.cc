// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
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
        bool enabled = false;
        uint32_t thread_pool_size = 0;
        uint32_t thread_queue_size = 0;
        if (value) {
            if (value->get("enable-multi-threading")) {
                enabled = SimpleParser::getBoolean(value, "enable-multi-threading");
            }
            if (value->get("thread-pool-size")) {
                thread_pool_size = SimpleParser::getInteger(value, "thread-pool-size");
            }
            if (value->get("packet-queue-size")) {
                thread_queue_size = SimpleParser::getInteger(value, "packet-queue-size");
            }
        }
        MultiThreadingMgr::instance().apply(enabled, thread_pool_size,
                                            thread_queue_size);
    }

}  // namespace dhcp
}  // namespace isc
