// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef WATCHED_THREAD_H
#define WATCHED_THREAD_H

#include <util/watch_socket.h>

#include <boost/shared_ptr.hpp>

#include <functional>
#include <mutex>
#include <thread>

namespace isc {
namespace util {

/// @brief Thread pointer type.
typedef boost::shared_ptr<std::thread> ThreadPtr;

/// @brief Provides a thread and controls for monitoring its activities
///
/// Given a "worker function", this class creates a thread which
/// runs the function and provides the means to monitor the thread
/// for "error" and "ready" conditions, and finally to stop the thread.
/// It uses three WatchSockets: one to indicate an error, one to indicate
/// data is ready, and a third to monitor as a shut-down command.
class WatchedThread {
public:
    /// @brief Enumerates the list of watch sockets used to mark events
    /// These are used as arguments to watch socket accessor methods.
    enum WatchType {
        ERROR = 0,
        READY = 1,
        TERMINATE = 2
    };

    /// @brief Constructor
    WatchedThread(){};

    /// @brief Virtual destructor
    virtual ~WatchedThread(){}

    /// @brief Fetches the fd of a watch socket
    ///
    /// @param watch_type indicates which watch socket
    /// @return the watch socket's file descriptor
    int getWatchFd(WatchType watch_type);

    /// @brief Sets a watch socket state to ready
    ///
    /// @param watch_type indicates which watch socket to mark
    void markReady(WatchType watch_type);

    /// @brief Indicates if a watch socket state is ready
    ///
    /// @param watch_type indicates which watch socket to mark
    /// @return true if the watch socket is ready, false otherwise
    bool isReady(WatchType watch_type);

    /// @brief Sets a watch socket state to not ready
    ///
    /// @param watch_type indicates which watch socket to clear
    void clearReady(WatchType watch_type);

    /// @brief Checks if the thread should terminate
    ///
    /// Performs a "one-shot" check of the terminate watch socket.
    /// If it is ready, return true and then clear it, otherwise
    /// return false.
    ///
    /// @return true if the terminate watch socket is ready
    bool shouldTerminate();

    /// @brief Creates and runs the thread.
    ///
    /// Creates the thread, passing into it the given function to run.
    ///
    /// @param thread_main function the thread should run
    void start(const std::function<void()>& thread_main);

    /// @brief Returns true if the thread is running
    bool isRunning() {
        return (thread_ != 0);
    }

    /// @brief Terminates the thread
    ///
    /// It marks the terminate watch socket ready, and then waits for the
    /// thread to stop.  At this point, the thread is defunct.  This is
    /// not done in the destructor to avoid race conditions.
    void stop();

    /// @brief Sets the error state
    ///
    /// This records the given error message and sets the error watch
    /// socket to ready.
    ///
    /// @param error_msg to be set as last error
    void setError(const std::string& error_msg);

    /// @brief Fetches the error message text for the most recent error
    ///
    /// @return string containing the error message
    std::string getLastError();

private:

    /// @brief Sets the error state thread safe
    ///
    /// This records the given error message
    ///
    /// @param error_msg to be set as last error
    void setErrorInternal(const std::string& error_msg);

    /// @brief Error message of the last error encountered
    std::string last_error_;

    /// @brief Mutex to protect internal state
    std::mutex mutex_;

    /// @brief WatchSockets that are used to communicate with the owning thread
    /// There are three:
    /// -# ERROR - Marked as ready by the thread when it experiences an error.
    /// -# READY - Marked as ready by the thread when it needs attention for a normal event
    /// (e.g. a thread used to receive data would mark READY when it has data available)
    /// -# TERMINATE - Marked as ready by WatchedThread owner to instruct the thread to
    /// terminate.  Worker functions must monitor TERMINATE by periodically calling
    /// @c shouldTerminate
    WatchSocket sockets_[TERMINATE + 1];

    /// @brief Current thread instance
    ThreadPtr thread_ ;
};

/// @brief Defines a pointer to a WatchedThread
typedef boost::shared_ptr<WatchedThread> WatchedThreadPtr;

}  // namespace util
}  // namespace isc

#endif // WATCHED_THREAD_H
