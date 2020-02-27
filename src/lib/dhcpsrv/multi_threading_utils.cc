// Copyright (C) 2019-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/multi_threading_utils.h>
#include <exceptions/exceptions.h>
#include <util/multi_threading_mgr.h>


using namespace isc::util;

namespace isc {
namespace dhcp {

void
MultiThreadingCriticalSection::stopPktProcessing() {
    auto& thread_pool = MultiThreadingMgr::instance().getPktThreadPool();
    bool override = MultiThreadingMgr::instance().getOverride();
    auto size = MultiThreadingMgr::instance().getPktThreadPoolSize();
    if (size && !override) {
        thread_pool.stop();
    }
}

void
MultiThreadingCriticalSection::startPktProcessing() {
    auto& thread_pool = MultiThreadingMgr::instance().getPktThreadPool();
    bool override = MultiThreadingMgr::instance().getOverride();
    auto size = MultiThreadingMgr::instance().getPktThreadPoolSize();
    if (size && !override) {
        thread_pool.start(size);
    }
}

MultiThreadingCriticalSection::MultiThreadingCriticalSection() {
    if (MultiThreadingMgr::instance().getMode()) {
        stopPktProcessing();
    }
    MultiThreadingMgr::instance().incrementOverride();
}

MultiThreadingCriticalSection::~MultiThreadingCriticalSection() {
    MultiThreadingMgr::instance().decrementOverride();
    if (MultiThreadingMgr::instance().getMode()) {
        startPktProcessing();
    }
}

}  // namespace dhcp
}  // namespace isc
