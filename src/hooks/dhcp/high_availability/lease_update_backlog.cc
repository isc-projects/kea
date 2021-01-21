// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <lease_update_backlog.h>
#include <util/multi_threading_mgr.h>

using namespace isc::dhcp;

namespace isc {
namespace ha {

LeaseUpdateBacklog::LeaseUpdateBacklog(const size_t limit)
    : limit_(limit), overflown_(false), outstanding_updates_() {
}

bool
LeaseUpdateBacklog::push(const LeaseUpdateBacklog::OpType op_type, const LeasePtr& lease) {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(mutex_);
        return (pushInternal(op_type, lease));
    }
    return (pushInternal(op_type, lease));
}

LeasePtr
LeaseUpdateBacklog::pop(LeaseUpdateBacklog::OpType& op_type) {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(mutex_);
        return (popInternal(op_type));
    }
    return (popInternal(op_type));
}

bool
LeaseUpdateBacklog::wasOverflown() {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(mutex_);
        return (overflown_);
    }
    return (overflown_);
}

void
LeaseUpdateBacklog::clear() {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(mutex_);
        outstanding_updates_.clear();
        overflown_ = false;
    }
    outstanding_updates_.clear();
    overflown_ = false;
}

size_t
LeaseUpdateBacklog::size() {
    if (util::MultiThreadingMgr::instance().getMode()) {
        std::lock_guard<std::mutex> lock(mutex_);
        return (outstanding_updates_.size());
    }
    return (outstanding_updates_.size());
}

bool
LeaseUpdateBacklog::pushInternal(const LeaseUpdateBacklog::OpType op_type, const LeasePtr& lease) {
    if (outstanding_updates_.size() >= limit_) {
        overflown_ = true;
        return (false);
    }
    outstanding_updates_.push_back(std::make_pair(op_type, lease));
    return (true);
}

LeasePtr
LeaseUpdateBacklog::popInternal(LeaseUpdateBacklog::OpType& op_type) {
    if (outstanding_updates_.empty()) {
        return (LeasePtr());
    }
    auto item = outstanding_updates_.front();
    outstanding_updates_.pop_front();
    op_type = item.first;
    return (item.second);
}

} // end of namespace isc::ha
} // end of namespace isc
