// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

template <typename WorkItem>
struct ThreadPoolQueue;

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
    void add(WorkItemCallBack& call_back);

    /// @brief count number of work items in the queue
    ///
    /// @return the number of work items in the queue
    size_t count();

    /// @brief size number of thread pool threads
    ///
    /// @return the number of threads
    size_t size();

private:
    /// @brief run function of each thread
    void run();

    /// @brief list of worker threads
    std::list<std::shared_ptr<std::thread>> threads_;

    /// @brief underlying work items queue
    std::shared_ptr<ThreadPoolQueue<WorkItemCallBack>> queue_;

    /// @brief state of the thread pool
    /// The 'run' state corresponds to false value
    /// The 'stop' state corresponds to true value
    std::atomic_bool exit_;
};

}  // namespace dhcp
}  // namespace isc

#endif  // THREAD_POOL_H
