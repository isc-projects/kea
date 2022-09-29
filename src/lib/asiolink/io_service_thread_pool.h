// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IOSERVICE_THREAD_POOL_H
#define IOSERVICE_THREAD_POOL_H

#include <asiolink/io_service.h>
#include <util/unlock_guard.h>

#include <boost/shared_ptr.hpp>

#include <condition_variable>
#include <list>
#include <mutex>
#include <thread>

namespace isc {
namespace asiolink {

/// @brief Implements a pausable pool of IOService driven threads.
class IoServiceThreadPool {
public:
    /// @brief Describes the possible operational state of the thread pool.
    enum class State {
        STOPPED,    /// Pool is not operational.
        RUNNING,    /// Pool is populated with running threads.
        PAUSED,     /// Pool is populated with threads that are paused.
    };

    /// @brief Constructor
    ///
    /// @param io_service IOService that will drive the pool's IO. If empty, it
    /// create its own instance.
    /// @param pool_size Maximum number of threads in the pool.  Currently the
    /// number of threads is fixed at this value.
    /// @param defer_start If true, creation of the threads is deferred until
    /// a subsequent call to @ref run().  In this case the pool's operational
    /// state post construction is STOPPED.  If false, the constructor will
    /// invoke run() to transition the pool into the RUNNING state.
    IoServiceThreadPool(asiolink::IOServicePtr io_service, size_t pool_size,
                   bool defer_start = false);

    /// @brief Destructor
    ///
    /// Ensures the thread pool is stopped prior to destruction.
    ~IoServiceThreadPool();

    /// @brief Transitions the pool from STOPPED or PAUSED to RUNNING.
    ///
    /// When called from the STOPPED state, the pool threads are created and
    /// begin processing events.
    /// When called from the PAUSED state, the pool threads are released
    /// from PAUSED and resume processing events.
    /// Has no effect if the pool is already in the RUNNING state.
    void run();

    /// @brief Transitions the pool from RUNNING to PAUSED.
    ///
    /// Pool threads suspend event processing and pause until they
    /// are released to either resume running or stop.
    /// Has no effect if the pool is already in the PAUSED or STOPPED
    /// state.
    void pause();

    /// @brief Transitions the pool from RUNNING or PAUSED to STOPPED.
    ///
    /// Stops thread event processing and then destroys the pool's threads
    /// Has no effect if the pool is already in the STOPPED state.
    void stop();

    /// @brief Check if the thread pool is running.
    ///
    /// @return True if the thread pool is running, false otherwise.
    bool isRunning() {
        return (getState() == State::RUNNING);
    }

    /// @brief Check if the thread pool is paused.
    ///
    /// @return True if the thread pool is paused, false otherwise.
    bool isPaused() {
        return (getState() == State::PAUSED);
    }

    /// @brief Check if the thread pool is stopped.
    ///
    /// @return True if the thread pool is stopped, false otherwise.
    bool isStopped() {
        return (getState() == State::STOPPED);
    }

    /// @brief Check current thread permissions to transition to the new PAUSED
    /// state.
    ///
    /// This function throws @ref MultiThreadingInvalidOperation if the calling
    /// thread is one of the worker threads. This would prevent a dead-lock if
    /// the calling thread would try to perform a thread pool state transition
    /// to PAUSED state.
    ///
    /// @throw MultiThreadingInvalidOperation if the state transition is done on
    /// any of the worker threads.
    void checkPausePermissions();

private:
    /// @brief Check current thread permissions to transition to the new state.
    ///
    /// This function throws @ref MultiThreadingInvalidOperation if the calling
    /// thread is one of the worker threads. This would prevent a dead-lock if
    /// the calling thread would try to perform a thread pool state transition.
    ///
    /// @param state The new transition state for the pool.
    /// @throw MultiThreadingInvalidOperation if the state transition is done on
    /// any of the worker threads.
    void checkPermissions(State state);

    /// @brief Check specified thread id against own threads.
    ///
    /// @return true if thread is owned, false otherwise.
    bool checkThreadId(std::thread::id id);

    /// @brief Thread-safe change of the pool's run state.
    ///
    /// Transitions a pool from one run state to another:
    ///
    /// When moving from STOPPED or PAUSED to RUNNING:
    /// -# Sets state to RUNNING.
    /// -# Notifies threads of state change.
    /// -# Restarts the IOService.
    /// -# Creates the threads if they do not yet exist (true only
    ///    when transitioning from STOPPED).
    /// -# Waits until all threads are running.
    /// -# Sets the count of exited threads to 0.
    /// -# Returns to caller.
    ///
    /// When moving from RUNNING or PAUSED to STOPPED:
    /// -# Sets state to STOPPED
    /// -# Notifies threads of state change.
    /// -# Polls the IOService to flush handlers.
    /// -# Stops the IOService.
    /// -# Waits until all threads have exited the work function.
    /// -# Joins and destroys the threads.
    /// -# Returns to caller.
    ///
    /// When moving from RUNNING to PAUSED:
    /// -# Sets state to PAUSED
    /// -# Notifies threads of state change.
    /// -# Polls the IOService to flush handlers.
    /// -# Stops the IOService.
    /// -# Waits until all threads have paused.
    /// -# Returns to caller.
    ///
    /// @param state The new transition state for the pool.
    /// @throw MultiThreadingInvalidOperation if the state transition is done on
    /// any of the worker threads.
    void setState(State state);

    /// @brief Thread-safe fetch of the pool's operational state.
    ///
    /// @return Thread pool state.
    State getState();

    /// @brief Validates whether the pool can change to a given state.
    ///
    /// @param state new state for the pool.
    /// @return true if the change is valid, false otherwise.
    /// @note Must be called from a thread-safe context.
    bool validateStateChange(State state) const;

    /// @brief Text representation of a given state.
    ///
    /// @param state The state for the pool.
    /// @return The text representation of a given state.
    static std::string stateToText(State state);

    /// @brief Work function executed by each thread in the pool.
    ///
    /// Implements the run state responsibilities for a given thread.
    /// It executes a run loop until the pool is stopped. At the top
    /// of each iteration of the loop the pool's run state is checked
    /// and when it is:
    ///
    /// RUNNING:
    /// -# The count of threads running is incremented.
    /// -# If the count has reached the number of threads in pool the
    ///    main thread is notified.
    /// -# IOService::run() is invoked.
    /// -# When IOService::run() returns, the count of threads running
    ///    is decremented.
    ///
    /// PAUSED:
    /// -# The count of threads paused is incremented.
    /// -# If the count has reached the number of threads in pool the
    ///    main thread is notified.
    /// -# Thread blocks until notified the pool's run state is no
    ///    longer PAUSED.
    /// -# The count of threads paused is decremented.
    ///
    /// STOPPED:
    /// -# The run loop is exited.
    /// -# The count of threads exited is incremented.
    /// -# If the count has reached the number of threads in pool the
    ///    main thread is notified.
    /// -# The function exits.
    void threadWork();

public:
    /// @brief Fetches the IOService that drives the pool.
    ///
    /// @return the pointer to the IOService.
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
    /// @brief Maximum number of threads in the thread pool.
    size_t pool_size_;

    /// @brief Pointer to private IOService used in multi-threaded mode.
    asiolink::IOServicePtr io_service_;

    /// @brief Tracks the operational state of the pool.
    State run_state_;

    /// @brief Mutex to protect the internal state.
    std::mutex mutex_;

    /// @brief Condition variable used by threads for synchronization.
    std::condition_variable thread_cv_;

    /// @brief Condition variable used by main thread to wait on threads
    /// state transitions.
    std::condition_variable main_cv_;

    /// @brief Number of threads currently paused.
    size_t paused_;

    /// @brief Number of threads currently running.
    size_t running_;

    /// @brief Number of threads that have exited the work function.
    size_t exited_;

    /// @brief Pool of threads used to service connections in multi-threaded
    /// mode.
    std::list<boost::shared_ptr<std::thread> > threads_;
};

/// @brief Defines a pointer to a thread pool.
typedef boost::shared_ptr<IoServiceThreadPool> IoServiceThreadPoolPtr;

} // end of namespace isc::asiolink
} // end of namespace isc

#endif
