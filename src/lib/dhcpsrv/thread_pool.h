// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
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

#include <boost/function.hpp>

#include <atomic>
#include <condition_variable>
#include <list>
#include <mutex>
#include <queue>
#include <thread>

namespace isc {
namespace dhcp {

/// @brief Defines a generic thread pool queue.
///
/// The main purpose is to safely manage thread pool tasks.
/// The thread pool queue can be 'disabled', which means that no items can be
/// added or removed from the queue, or 'enabled', which guarantees that
/// inserting or removing items are thread safe.
/// In 'disabled' state, all threads waiting on the queue are unlocked and all
/// operations are non blocking.
template <typename WorkItem>
struct ThreadPoolQueue {
    /// @brief Constructor
    ///
    /// Creates the thread pool queue in 'disabled' state
    ThreadPoolQueue() : exit_(true) {
    }

    /// @brief Destructor
    ///
    /// Destroys the thread pool queue
    ~ThreadPoolQueue() {
        stop(true);
    }

    /// @brief push work item to the queue
    ///
    /// Used to add work items in the queue.
    /// If the queue is 'disabled', this function returns immediately.
    /// If the queue is 'enabled', this function adds an item to the queue and
    /// wakes up at least one thread waiting on the queue.
    ///
    /// @param item the new iten to be added to the queue
    void push(WorkItem item) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (exit_) {
            return;
        }
        queue_.push(item);
        // Notify pop function so that it can effectively remove a work item.
        cv_.notify_all();
    }

    /// @brief pop work item from the queue or block waiting
    ///
    /// Used to retrieve and remove a work item from the queue
    /// If the queue is 'disabled', this function returns immediately
    /// (no element).
    /// If the queue is 'enabled', this function returns the first element in
    /// the queue or blocks the calling thread if there are no work items
    /// available.
    ///
    /// @param item the reference of the item removed from the queue, if any
    ///
    /// @return true if there was a work item removed from the queue, false
    /// otherwise
    bool pop(WorkItem& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        while (!exit_) {
            if (queue_.empty()) {
                // Wait for push or stop functions.
                cv_.wait(lock);
                continue;
            }

            item = queue_.front();
            queue_.pop();
            return true;
        }

        return false;
    }

    /// @brief count number of work items in the queue
    ///
    /// Returns the number of work items in the queue
    ///
    /// @return the number of work items
    size_t count() {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    /// @brief clear remove all work items
    ///
    /// Removes all queued work items
    void clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        reset();
    }

    /// @brief start and enable the queue
    ///
    /// Sets the queue state to 'enabled'
    void start() {
        std::lock_guard<std::mutex> lock(mutex_);
        exit_ = false;
    }

    /// brief stop and disable the queue
    ///
    /// Sets the queue state to 'disabled' and optionally removes all work items
    ///
    /// @param clear used to specify if the function should also clear the queue
    void stop(bool clear = false) {
        std::lock_guard<std::mutex> lock(mutex_);
        exit_ = true;
        // Notify get() so that it can exit.
        cv_.notify_all();
        if (clear) {
            reset();
        }
    }

private:
    /// @brief reset clears the queue removing all work items
    ///
    /// Must be called in a critical section (mutex locked scope).
    void reset() {
        queue_ = std::queue<WorkItem>();
    }

    /// @brief underlying queue container
    std::queue<WorkItem> queue_;

    /// @brief mutex used for critical sections
    std::mutex mutex_;

    /// @brief condition variable used to signal waiting threads
    std::condition_variable cv_;

    /// @brief the sate of the queue
    ///
    /// The 'enabled' state corresponds to false value
    /// The 'disabled' state corresponds to true value
    std::atomic_bool exit_;
};

/// @brief Defines a thread pool which uses a thread pool queue for managing
/// work items. Each work item is a 'function' object.
struct ThreadPool {
    using WorkItemCallBack = std::function<void()>;

    /// @brief Constructor
    ThreadPool();

    /// @brief Destructor
    ~ThreadPool();

    /// @brief initialize the thread pool with specified number of treads and
    /// optionally starts all threads.
    ///
    /// @param worker_threads specifies the number of threads to be created
    /// @param run to indicate if the threads should be started immediately
    void create(uint32_t thread_count, bool run = true);

    /// @brief de-initialize the thread pool stopping threads and clearing the
    /// internal queue
    void destroy();

    /// @brief start all the threads
    ///
    /// @param worker_threads specifies the number of threads to be created
    void start(uint32_t thread_count);

    /// @brief stop all the threads
    ///
    /// @param clear used to specify if the function should also clear the queue
    void stop(bool clear = false);

    /// @brief add a working item to the thread pool
    ///
    /// @param call_back the 'function' object to be added to the queue
    void add(WorkItemCallBack call_back);

    /// @brief count number of work items in the queue
    ///
    /// @return the number of work items in the queue
    size_t count();

private:
    /// @brief run function of each thread
    void run();

    /// @brief list of worker threads
    std::list<std::shared_ptr<std::thread>> worker_threads_;

    /// @brief underlying work items queue
    ThreadPoolQueue<WorkItemCallBack> queue_;

    /// @brief state of the thread pool
    /// The 'run' state corresponds to false value
    /// The 'stop' state corresponds to true value
    std::atomic_bool exit_;
};

}  // namespace dhcp
}  // namespace isc

#endif  // THREAD_POOL_H
