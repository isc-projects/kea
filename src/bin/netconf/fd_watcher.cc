// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file fd_watcher.cc
/// Contains the file descriptor watcher.

#include <config.h>

#include <netconf/fd_watcher.h>
#include <netconf/netconf_log.h>

#include <boost/function.hpp>
#include <sys/select.h>
#include <fcntl.h>

#include <sysrepo.h>

using namespace std;
using namespace isc::util::thread;

namespace isc {
namespace netconf {

FdWatcherPtr FdWatcher::fd_watcher_;

FdWatcher::FdWatcher() {
}

FdWatcherPtr&
FdWatcher::instance() {
    if (!fd_watcher_) {
        fd_watcher_.reset(new FdWatcher());
    }
    return (fd_watcher_);
}

FdWatcher::~FdWatcher() {
    this->clear();
}

int
FdWatcher::init(const asiolink::IOServicePtr& io_service) {
    // Remember the IO service.
    io_service_ = io_service;

    // If it was already called the initial watcher is in the receiving set.
    if (!readFds.empty()) {
        return (SR_ERR_OK);
    }

    // sr_fd_watcher_init is C code.
    int watcher_fd = 0;
    // Set a termination handler so closed file descriptors can be flushed.
    int ret = sr_fd_watcher_init(&watcher_fd, []() { return; });
    if (ret != SR_ERR_OK) {
        return (ret);
    }

    // Add the watcher file descriptor to the receiving set.
    addFd(watcher_fd, true, false);

    // Create the first polling thread.
    thread_.reset(new Thread(threadBody));

    return (ret);
}

void
FdWatcher::clear() {
    // Clear sets.
    writeFds.clear();
    readFds.clear();

    // Wake up the thread.
    if (thread_) {
        watch_terminate_.markReady();
        thread_->wait();
        thread_.reset();
    }

    // Clear the terminate watch socket.
    watch_terminate_.clearReady();

    // Clean up sysrepo.
    sr_fd_watcher_cleanup();
}

void
FdWatcher::addFd(int fd, bool reading, bool writing) {
    // Ignore return values.
    if (reading) {
        readFds.insert(fd);
    }
    if (writing) {
        writeFds.insert(fd);
    }
}

void
FdWatcher::delFd(int fd, bool reading, bool writing) {
    if (reading) {
        auto it = readFds.find(fd);
        if (it != readFds.end()) {
            readFds.erase(it);
        }
    }
    if (writing) {
        auto it = writeFds.find(fd);
        if (it != writeFds.end()) {
            writeFds.erase(it);
        }
    }
}

void
FdWatcher::postHandler() {
    // Get the singleton.
    FdWatcherPtr watcher = FdWatcher::instance();

    // Collect the thread.
    if (watcher->thread_) {
        watcher->thread_->wait();
        watcher->thread_.reset();
    }

    // Nothing to do if not initialized.
    if (watcher->readFds.empty()) {
        return;
    }

    // Get reading file descriptors.
    int maxfd = 0;
    fd_set rd_set;
    FD_ZERO(&rd_set);
    set<int> readFds = watcher->readFds;
    for (int fd : readFds) {
        FD_SET(fd, &rd_set);
        if (fd > maxfd) {
            maxfd = fd;
        }
    }

    // Get writing file descriptors.
    fd_set wr_set;
    FD_ZERO(&wr_set);
    set<int> writeFds = watcher->writeFds;
    for (int fd : writeFds) {
        FD_SET(fd, &wr_set);
        if (fd > maxfd) {
            maxfd = fd;
        }
    }

    // No wait,
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    // zero out the errno to be safe.
    errno = 0;

    int ret = select(maxfd + 1, &rd_set, &wr_set, 0, &tv);
    if (ret < 0) {
        if (errno == EINTR) {
            // Not lucky... Just retry.
            watcher->io_service_->post(postHandler);
            return;
        } else if (errno == EBADF) {
            // A file descriptor was closed before being removed.
            for (int fd : readFds) {
                if (fcntl(fd, F_GETFD) == -1) {
                    watcher->delFd(fd, true, true);
                }
            }
            for (int fd : writeFds) {
                if (fcntl(fd, F_GETFD) == -1) {
                    watcher->delFd(fd, true, true);
                }
            }
            // Retry.
            watcher->io_service_->post(postHandler);
            return;
        } else {
            isc_throw(Unexpected, "select failed with " << strerror(errno));
        }
    } else if (ret != 0) {
        // Scan reading file descriptors.
        // Work on the copy as the watcher sets can be modified.
        bool processed = false;
        for (int fd : readFds) {
            if (!FD_ISSET(fd, &rd_set)) {
                continue;
            }

            // sr_fd_event_process is C code.
            sr_fd_change_t* change_set = 0;
            size_t cnt = 0;
            int ret = sr_fd_event_process(fd, SR_FD_INPUT_READY,
                                          &change_set, &cnt);
            if (ret != SR_ERR_OK) {
                // We don't know what to do on error...
                // which BTW should never happen.
                LOG_WARN(netconf_logger, NETCONF_FD_WATCHER_ERROR)
                    .arg(string(sr_strerror(ret)));
            }
            for (size_t i = 0; i < cnt; ++i) {
                if (change_set[i].action == SR_FD_START_WATCHING) {
                    watcher->addFd(change_set[i].fd,
                        (change_set[i].events & SR_FD_INPUT_READY) != 0,
                        (change_set[i].events & SR_FD_OUTPUT_READY) != 0);
                } else if (change_set[i].action == SR_FD_STOP_WATCHING) {
                    watcher->delFd(change_set[i].fd,
                        (change_set[i].events & SR_FD_INPUT_READY) != 0,
                        (change_set[i].events & SR_FD_OUTPUT_READY) != 0);
                }
            }
            free(change_set);
            processed = true;
            break;
        }

        // Restart if something was done.
        if (processed) {
            watcher->io_service_->post(postHandler);
            return;
        }

        // Scan writing file descriptors.
        // Work on the copy as the watcher sets can be modified.
        for (int fd : writeFds) {
            if (!FD_ISSET(fd, &rd_set)) {
                continue;
            }

            // sr_fd_event_process is C code.
            sr_fd_change_t* change_set = 0;
            size_t cnt = 0;
            // ignore return because we don't know what to do on error.
            sr_fd_event_process(fd, SR_FD_OUTPUT_READY, &change_set, &cnt);
            for (size_t i = 0; i < cnt; ++i) {
                if (change_set[i].action == SR_FD_START_WATCHING) {
                    watcher->addFd(change_set[i].fd,
                        (change_set[i].events & SR_FD_INPUT_READY) != 0,
                        (change_set[i].events & SR_FD_OUTPUT_READY) != 0);
                } else if (change_set[i].action == SR_FD_STOP_WATCHING) {
                    watcher->delFd(change_set[i].fd,
                        (change_set[i].events & SR_FD_INPUT_READY) != 0,
                        (change_set[i].events & SR_FD_OUTPUT_READY) != 0);
                }
            }
            free(change_set);
            processed = true;
            break;
        }

        // Restart if something was done.
        if (processed) {
            watcher->io_service_->post(postHandler);
            return;
        }
    }

    // Either select() returns 0 or nothing was done.
    // Create a new polling thread.
    watcher->thread_.reset(new Thread(threadBody));
}

void
FdWatcher::threadBody() {
    // Get the singleton.
    FdWatcherPtr watcher = FdWatcher::instance();

    // Get reading file descriptors.
    int maxfd = 0;
    fd_set rd_set;
    FD_ZERO(&rd_set);
    for (int fd : watcher->readFds) {
        FD_SET(fd, &rd_set);
        if (fd > maxfd) {
            maxfd = fd;
        }
    }
    // Add the terminate watch socket.
    int wt_fd = watcher->watch_terminate_.getSelectFd();
    FD_SET(wt_fd, &rd_set);
    if (wt_fd > maxfd) {
        maxfd = wt_fd;
    }

    // Get writing file descriptors.
    fd_set wr_set;
    FD_ZERO(&wr_set);
    for (int fd : watcher->writeFds) {
        FD_SET(fd, &wr_set);
        if (fd > maxfd) {
            maxfd = fd;
        }
    }

    // Wait until something happens.
    select(maxfd + 1, &rd_set, &wr_set, 0, 0);

    // Deal with events in the Kea event loop.
    watcher->io_service_->post(postHandler);

    return;
}

} // namespace netconf
} // namespace isc
