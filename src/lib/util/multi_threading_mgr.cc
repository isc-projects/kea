// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <util/multi_threading_mgr.h>

namespace isc {
namespace util {

MultiThreadingMgr::MultiThreadingMgr() : enabled_(false) {
}

MultiThreadingMgr::~MultiThreadingMgr() {
}

MultiThreadingMgr&
MultiThreadingMgr::instance() {
    static MultiThreadingMgr manager;
    return (manager);
}

bool
MultiThreadingMgr::getMode() const {
    return (enabled_);
}

void
MultiThreadingMgr::setMode(bool enabled) {
    enabled_ = enabled;
}

ThreadPool<std::function<void()>>&
MultiThreadingMgr::getPktThreadPool() {
    return pkt_thread_pool_;
}

uint32_t
MultiThreadingMgr::getPktThreadPoolSize() const {
    return (pkt_thread_pool_size_);
}

void
MultiThreadingMgr::setPktThreadPoolSize(uint32_t size) {
    pkt_thread_pool_size_ = size;
}

}  // namespace util
}  // namespace isc
