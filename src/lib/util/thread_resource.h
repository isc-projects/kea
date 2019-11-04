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
class ThreadResource {
    typedef std::shared_ptr<Resource> ResourcePtr;
public:
    /// @brief function to retrieve the specific resource of calling thread
    /// This function returns the resource of the calling thread from the map
    /// container or, in case it is not found, it creates a resource and adds it
    /// to the map container
    ///
    /// @return the specific resource of the calling thread
    ResourcePtr resource() {
        std::lock_guard<std::mutex> lock(mutex_);
        auto id = std::this_thread::get_id();
        if (map_.find(id) != map_.end()) {
            return map_[id];
        }
        ResourcePtr result(std::make_shared<Resource>());
        map_[id] = result;
        return result;
    }
private:
    /// @brief mutex used to keep the internal state consistent
    std::mutex mutex_;

    /// @brief map container which holds the resources for each thread
    std::unordered_map<std::thread::id, ResourcePtr> map_;
};

}  // namespace dhcp
}  // namespace isc

#endif  // THREAD_RESOURCE_MGR_H
