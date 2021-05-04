// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_THREAD_POOL_H
#define HTTP_THREAD_POOL_H

#include <asiolink/io_service.h>
#include <util/unlock_guard.h>

#include <boost/shared_ptr.hpp>

#include <condition_variable>
#include <list>
#include <mutex>
#include <thread>

namespace isc {
namespace http {

/// @brief Implements a pausable pool of IOService driven threads.
class HttpThreadPool {
public:
    /// @brief Describes the possible operational state of the pool.
    enum class RunState {
        STOPPED,    /// Pool is not operational.
        RUN,        /// Pool is populated with running threads.
        PAUSED,     /// Pool is populated with threads which are paused.
        SHUTDOWN,   /// Pool is transitioning from RUN or PAUSED to STOPPED.
    };

    /// @brief Constructor
    ///
    /// @param io_service IOService that will drive the pool's IO. If empty, it
    /// create it's own instance.
    /// @param pool_size Maximum number of threads in the pool.  Currently the number
    /// of threads is fixed at this value.
    /// @param defer_start If true, creation of the threads is deferred until a subsequent
    /// call to @ref start().  In this case the pool's operational state post construction
    /// is STOPPED.  If false, the construtor will invoke start() which will create the
    /// threads, placing the pool in RUN state.
    HttpThreadPool(asiolink::IOServicePtr io_service, size_t pool_size, bool defer_start = false);

    /// @brief Destructor
    ///
    /// Ensures the pool is stopped prior to destruction.
    ~HttpThreadPool();

    /// @brief Transitions the pool from STOPPED to RUN run state.
    ///
    /// It starts the pool by doing the following:
    /// -# Sets state to RUN
    /// -# Restarts the IOService preparing it thread invocations of
    ///    IOService::run()
    /// -# Creates thread_pool_size_ threads, adding each to the pool.
    ///
    /// @throw InvalidOperation if called with the pool in any state other
    /// than STOPPED.
    void start();

    /// @brief Tranisitions the pool to STOPPED state.
    ///
    /// It stops the pool by doing the following:
    /// -# Sets the state to SHUTDOWN.
    /// =# Stops the IOService.
    /// =# Joins the pool threads.
    /// -# Empties the pool.
    /// -# Sets the state to STOPPED.
    void stop();

    /// @brief Transitions the pool from RUN to PAUSED state.
    ///
    /// If the state is any state other than RUN it simply returns,
    /// otherwise it does the following:
    ///
    /// -# Sets the state to PAUSED.
    /// -# Stops the IOService.
    void pause();

    /// @brief Transitions the pool from PAUSED to RUN state.
    ///
    /// If the state is any state other than PAUSED it simply returns,
    /// otherwise it does the following:
    ///
    /// -# Restarts the IOService preparing it for thread invocations
    ///    of IOService::run()
    /// -# Sets the state to RUN.
    void resume();

    /// @brief Thread-safe fetch of the pool's operational state.
    ///
    /// @return Pool run state.
    RunState getRunState();

private:
    /// @brief Thread-safe set of the pool's operational state.
    ///
    /// @note This method does not validate the state change.
    ///
    /// @param state new state for the pool.
    void setRunState(RunState state);

public:
    /// @brief Fetches the IOService that drives the pool.
    ///
    /// @return A pointer to the IOService.
    asiolink::IOServicePtr getIOService() const;

    /// @brief Fetches the maximum size of the thread pool.
    ///
    /// @return the maximum size of the thread pool.
    uint16_t getPoolSize() const;

    /// @brief Fetches the number of threads in the pool.
    ///
    /// @return the number of running threads.
    uint16_t getThreadCount() const;

private:
    /// @brief Maxim number of threads in the thread pool.
    size_t pool_size_;

    /// @brief Pointer to private IOService used in multi-threaded mode.
    asiolink::IOServicePtr io_service_;

    /// @brief Tracks the operational state of the pool.
    RunState run_state_;

    /// @brief Mutex to protect the internal state.
    std::mutex mutex_;

    /// @brief Condition variable for synchronization.
    std::condition_variable cv_;

    /// @brief Pool of threads used to service connections in multi-threaded
    /// mode.
    std::list<boost::shared_ptr<std::thread> > threads_;
};

/// @brief Defines a pointer to a thread pool.
typedef boost::shared_ptr<HttpThreadPool> HttpThreadPoolPtr;

} // end of namespace isc::http
} // end of namespace isc

#endif

