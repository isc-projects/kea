// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SELECT_EVENT_HANDLER_H
#define SELECT_EVENT_HANDLER_H

#include <fd_event_handler.h>

#include <sys/select.h>

namespace isc {
namespace dhcp {

/// @brief File descriptor event handler class handles events for registered
/// file descriptors. This class uses the OS select syscall for event handling.
class SelectEventHandler : public FDEventHandler {
public:
    /// @brief Constructor.
    SelectEventHandler();

    /// @brief Destructor.
    virtual ~SelectEventHandler() = default;

    /// @brief Add file descriptor to watch for events.
    ///
    /// @param fd The file descriptor.
    /// @param read The flag indicating if the file descriptor should be
    /// registered for read ready events.
    /// @param write The flag indicating if the file descriptor should be
    /// registered for write ready events.
    void add(int fd, bool read = true, bool write = false);

    /// @brief Wait for events on registered file descriptors.
    ///
    /// @param timeout_sec The wait timeout in seconds.
    /// @param timeout_usec The wait timeout in micro seconds
    /// @return -1 on error, 0 if no data is available (timeout expired),
    /// 1 if data is ready.
    int waitEvent(uint32_t timeout_sec, uint32_t timeout_usec = 0);

    /// @brief Check if file descriptor is ready for read operation.
    ///
    /// @param fd The file descriptor.
    ///
    /// @return True if file descriptor is ready for reading.
    bool readReady(int fd);

    /// @brief Check if file descriptor is ready for write operation.
    ///
    /// @param fd The file descriptor.
    ///
    /// @return True if file descriptor is ready for writing.
    bool writeReady(int fd);

    /// @brief Clear registered file descriptors.
    void clear();

private:
    /// @brief The maximum value of registered file descriptors.
    int max_fd_;

    /// @brief The read event FD set.
    fd_set read_fd_set_;

    /// @brief The write event FD set.
    fd_set write_fd_set_;

    /// @brief The read event FD set.
    fd_set ready_read_fd_set_;

    /// @brief The write event FD set.
    fd_set ready_write_fd_set_;
};

}  // namespace isc::dhcp
}  // namespace isc

#endif  // SELECT_EVENT_HANDLER_H
