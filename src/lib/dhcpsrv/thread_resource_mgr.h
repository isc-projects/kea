// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef THREAD_RESOURCE_MGR_H
#define THREAD_RESOURCE_MGR_H

#include <boost/shared_ptr.hpp>
#include <mutex>
#include <thread>
#include <unordered_map>

namespace isc {
namespace dhcp {

template <typename Resource>
class ThreadResourceMgr {
    typedef boost::shared_ptr<Resource> ResourcePtr;
public:
    ResourcePtr resource() {
        std::lock_guard<std::mutex> lock(mutex_);
        auto id = std::this_thread::get_id();
        if (map_.find(id) != map_.end()) {
            return map_[id];
        }
        ResourcePtr result(new Resource());
        map_[id] = result;
        return result;
    }
private:
    std::mutex mutex_;
    std::unordered_map<std::thread::id, ResourcePtr> map_;
};

}  // namespace dhcp
}  // namespace isc

#endif  // THREAD_RESOURCE_MGR_H
