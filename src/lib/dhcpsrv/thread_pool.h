// Copyright (C) 2017-2019 Deutsche Telekom AG.
//
// Authors: Andrei Pavel <andrei.pavel@qualitance.com>
//          Cristian Secareanu <cristian.secareanu@qualitance.com>
//          Razvan Becheriu <razvan.becheriu@qualitance.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <util/threads/lock_guard.h>

#include <boost/function.hpp>

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <list>
#include <mutex>
#include <queue>
#include <thread>

namespace isc {
namespace dhcp {

template <typename WorkItem>
struct ThreadPoolQueue {
    ThreadPoolQueue() : exit_(true) {
    }

    ~ThreadPoolQueue() {
    }

    void add(WorkItem item) {
        isc::util::thread::LockGuard<std::mutex> lock(&mutex_);
        if (exit_) {
            return;
        }
        queue_.push(item);
        // Notify get() so that it can effectively get a work item.
        cv_.notify_all();
    }

    bool get(WorkItem& item) {
        std::unique_lock<std::mutex> lock(mutex_);

        while (!exit_) {
            if (queue_.empty()) {
                // Wait for add() or destroy().
                cv_.wait(lock);
                continue;
            }

            item = queue_.front();
            queue_.pop();
            return true;
        }

        return false;
    }

    size_t count() {
        isc::util::thread::LockGuard<std::mutex> lock(&mutex_);
        return queue_.size();
    }

    void removeAll() {
        isc::util::thread::LockGuard<std::mutex> lock(&mutex_);
        removeAllUnsafe();
    }

    void create() {
        isc::util::thread::LockGuard<std::mutex> lock(&mutex_);
        exit_ = false;
    }

    void destroy() {
        isc::util::thread::LockGuard<std::mutex> lock(&mutex_);
        exit_ = true;
        // Notify get() so that it can exit.
        cv_.notify_all();
        removeAllUnsafe();
    }

private:
    /// @brief Has to be called in a mutex_-locked environment.
    void removeAllUnsafe() {
        while (queue_.size()) {
            queue_.pop();
        }
    }

    std::queue<WorkItem> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::atomic_bool exit_;
};

struct ThreadPool {
    using WorkItemCallBack = std::function<void()>;

    ThreadPool();
    ~ThreadPool();

    void create(uint32_t worker_threads);

    void destroy();

    void add(WorkItemCallBack call_back);

    size_t count();

private:
    void threadRun();

    std::list<std::shared_ptr<std::thread>> worker_threads_;
    ThreadPoolQueue<WorkItemCallBack> queue_;
    std::atomic_bool exit_;
};

}  // namespace dhcp
}  // namespace isc

#endif  // THREAD_POOL_H
