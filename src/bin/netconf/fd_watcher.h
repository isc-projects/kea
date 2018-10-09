// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file netconf_log.h
/// Contains declarations for loggers used by the Kea netconf agent.

#ifndef NETCONF_FD_WATCHER_H
#define NETCONF_FD_WATCHER_H

#include <util/watch_socket.h>
#include <util/threads/thread.h>
#include <asiolink/io_service.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <set>

namespace isc {
namespace netconf {

/// @brief Forward declaration to the @c FdWatcher.
class FdWatcher;

/// @brief Type definition for the pointer to the @c FdWatcher.
typedef boost::shared_ptr<FdWatcher> FdWatcherPtr;

/// @brief Type definition for the pointer to the @c isc::util::thread::Thread.
typedef boost::shared_ptr<isc::util::thread::Thread> ThreadPtr;

/// @brief FdWatcher utility.
///
/// This class implements a sysrepo file descriptor watcher.
/// The alternative is to leave sysrepo to create its own thread to
/// handle suscriptions with an independent and likely incompatible
/// event loop and of course locking issues.
/// Reference:
///     http://www.sysrepo.org/static/doc/html/subscribtions.html#callbacks
///
/// To simplify callbacks this class is implemented as a singleton.
class FdWatcher : public boost::noncopyable {
public:

    /// @brief Static singleton instance method.
    ///
    /// This method returns the class singleton instance member.
    /// It instantiates the singleton upon first invocation.
    ///
    /// @return the pointer reference to the singleton instance.
    static FdWatcherPtr& instance();

    /// @brief Destructor (final cleanup).
    virtual ~FdWatcher();

    /// @brief Initialize the fd watcher.
    ///
    /// @param io_service The IO service aka the Kea event loop.
    /// @return SR_ERR_OK (0) on success, SR_ERR_XXX (>0) on error.
    int init(const asiolink::IOServicePtr& io_service);

    /// @brief Clear the fd watcher.
    ///
    /// Uses the terminate watch socket to wake up and terminate the thread
    /// if it exists.
    void clear();

    /// @brief Add a file descriptor to watch.
    ///
    /// The file descriptor is given by sysrepo for reading and/or writing.
    ///
    /// @param fd The file descriptor to add.
    /// @param reading Boolean flag: true to watch for reading.
    /// @param writing Boolean flag: true to watch for writing.
    void addFd(int fd, bool reading, bool writing);

    /// @brief Delete a file descriptor to watch.
    ///
    /// The file descriptor is given by sysrepo for reading and/or writing.
    ///
    /// @param fd The file descriptor to delete.
    /// @param reading Boolean flag: true to watch for reading.
    /// @param writing Boolean flag: true to watch for writing.
    void delFd(int fd, bool reading, bool writing);

    /// @brief Post handler.
    ///
    /// The thread posts this handler on the IO service when there
    /// should be a file descriptor available for IO. This handler
    /// will be called by the process run loop in the main thread.
    static void postHandler();

    /// @brief Thread body.
    ///
    /// The thread body: select() on file descriptors, when one is
    /// available posts fdAvailable and returns. As the file descriptors
    /// include the terminate watch socket the thread can be triggered
    /// from Kea too (vs only by sysrepo).
    static void threadBody();

    /// @brief Shared pointer to the IOService object where to post callbacks.
    asiolink::IOServicePtr io_service_;

    /// @brief Terminate watch socket.
    ///
    /// Used to wake up and terminate the thread from Kea.
    isc::util::WatchSocket watch_terminate_;

    /// @brief Polling thread.
    ThreadPtr thread_;

    /// @brief Reading file descriptors.
    std::set<int> readFds;

    /// @brief Write file descriptors.
    std::set<int> writeFds;

private:
    /// @brief Constructor (private to protect the singleton instance).
    FdWatcher();

    /// @brief Singleton instance value.
    static FdWatcherPtr fd_watcher_;
};

} // namespace netconf
} // namespace isc

#endif // NETCONF_FD_WATCHER_H
