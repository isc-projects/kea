// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef WATCHED_THREAD_H
#define WATCHED_THREAD_H

#include <util/watch_socket.h>
#include <util/threads/thread.h>

#include <boost/shared_ptr.hpp>

namespace isc {
namespace util {
namespace thread {

/// @brief Provides a thread and controls for receiving packets.
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
        RCV_ERROR = 0,
        RCV_READY = 1,
        RCV_TERMINATE = 2
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

    /// @brief Checks if the receiver thread should terminate
    ///
    /// Performs a "one-shot" check of the receiver's terminate
    /// watch socket.  If it is ready, return true and then clear
    /// it, otherwise return false.
    ///
    /// @return true if the terminate watch socket is ready
    bool shouldTerminate();

    /// @brief Creates and runs the thread.
    ///
    /// Creates teh receiver's thread, passing into it the given
    /// function to run.
    ///
    /// @param thread_main function the receiver's thread should run
    void start(const boost::function<void()>& thread_main);

    /// @brief Returns true if the receiver thread is running
    /// @todo - this may need additional logic to handle cases where
    /// a thread function exits w/o the caller invoking @c
    /// WatchedThread::stop().
    bool isRunning() {
        return (thread_ != 0);
    }

    /// @brief Terminates the receiver thread
    ///
    /// It marks the terminate watch socket ready, and then waits for the
    /// thread to stop.  At this point, the receiver is defunct.  This is
    /// not done in the destructor to avoid race conditions.
    void stop();

    /// @brief Sets the receiver error state
    ///
    /// This records the given error message and sets the error watch
    /// socket to ready.
    ///
    /// @param error_msg
    void setError(const std::string& error_msg);

    /// @brief Fetches the error message text for the most recent socket error
    ///
    /// @return string containing the error message
    std::string getLastError();

    /// @brief Error message of the last error encountered
    std::string last_error_;

    /// @brief DHCP watch sockets that are used to communicate with the owning thread
    /// There are three:
    /// -# RCV_ERROR - packet receive error watch socket.
    /// Marked as ready when the DHCP packet receiver experiences an I/O error.
    /// -# RCV_READY - Marked as ready when the DHCP packet receiver adds a packet
    /// to the packet queue.
    /// -# RCV_TERMINATE Packet receiver terminate watch socket.
    /// Marked as ready when the DHCP packet receiver thread should terminate.
    WatchSocket sockets_[RCV_TERMINATE + 1];

    /// DHCP packet receiver thread.
    thread::ThreadPtr thread_ ;
};

/// @brief Defines a pointer to a WatchedThread
typedef boost::shared_ptr<WatchedThread> WatchedThreadPtr;

}; // namespace isc::util::thread
}; // namespace isc::util
}; // namespace isc

#endif // WATCHED_THREAD_H
