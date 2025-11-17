// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef POLL_EVENT_HANDLER_H
#define POLL_EVENT_HANDLER_H

#include <util/fd_event_handler.h>

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <sys/poll.h>

namespace isc {
namespace util {

/// @brief File descriptor event handler class handles events for registered
/// file descriptors. This class uses the OS select syscall for event handling.
class PollEventHandler : public FDEventHandler {
public:
    /// @brief Constructor.
    PollEventHandler();

    /// @brief Destructor.
    virtual ~PollEventHandler() = default;

    /// @brief Add file descriptor to watch for events.
    ///
    /// @param fd The file descriptor.
    void add(int fd);

    /// @brief Wait for events on registered file descriptors.
    ///
    /// @param timeout_sec The wait timeout in seconds.
    /// @param timeout_usec The wait timeout in micro seconds.
    /// @param use_timeout Flag which indicates if function should wait
    /// with no timeout (wait forever).
    /// @return -1 on error, 0 if no data is available (timeout expired),
    /// 1 if data is ready.
    int waitEvent(uint32_t timeout_sec, uint32_t timeout_usec = 0,
                  bool use_timeout = true);

    /// @brief Check if file descriptor is ready for read operation.
    ///
    /// @param fd The file descriptor.
    ///
    /// @return True if file descriptor is ready for reading.
    bool readReady(int fd);

    /// @brief Check if file descriptor has error.
    ///
    /// @param fd The file descriptor.
    ///
    /// @return True if file descriptor has error.
    virtual bool hasError(int fd);

    /// @brief Clear registered file descriptors.
    void clear();

private:
    /// @brief The poll file descriptors data.
    std::vector<struct pollfd> data_;

    /// @brief The map with file descriptor to data reference.
    std::unordered_map<int, struct pollfd*> map_;
};

}  // namespace isc::util;
}  // namespace isc

#endif  // POLL_EVENT_HANDLER_H
