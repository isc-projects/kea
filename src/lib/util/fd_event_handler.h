// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FD_EVENT_HANDLER_H
#define FD_EVENT_HANDLER_H

#include <boost/shared_ptr.hpp>
#include <stdint.h>

namespace isc {
namespace util {

/// @brief File descriptor event handler class handles events for registered
/// file descriptors.
class FDEventHandler {
public:
    enum HandlerType : uint16_t {
        TYPE_UNKNOWN = 0,
        TYPE_SELECT = 1,
        TYPE_EPOLL = 2, // Linux OS (Linux like OS) only
        TYPE_KQUEUE = 3, // BSD OS (BSD like OS) only
        TYPE_POLL = 4,
    };

    /// @brief Constructor.
    ///
    /// @param type The file descriptor event handler type.
    FDEventHandler(HandlerType type = TYPE_UNKNOWN);

    /// @brief Destructor.
    virtual ~FDEventHandler() = default;

    /// @brief Add file descriptor to watch for events.
    ///
    /// @param fd The file descriptor.
    virtual void add(int fd) = 0;

    /// @brief Wait for events on registered file descriptors.
    ///
    /// @param timeout_sec The wait timeout in seconds.
    /// @param timeout_usec The wait timeout in micro seconds.
    /// @param use_timeout Flag which indicates if function should wait
    /// with no timeout (wait forever).
    /// @return -1 on error, 0 if no data is available (timeout expired),
    /// 1 if data is ready.
    virtual int waitEvent(uint32_t timeout_sec, uint32_t timeout_usec = 0,
                          bool use_timeout = true) = 0;

    /// @brief Check if file descriptor is ready for read operation.
    ///
    /// @param fd The file descriptor.
    ///
    /// @return True if file descriptor is ready for reading.
    virtual bool readReady(int fd) = 0;

    /// @brief Clear registered file descriptors.
    virtual void clear() = 0;

    /// @brief Return the event handler type.
    HandlerType type();

private:
    /// @brief The event handler type.
    HandlerType type_;
};

/// @brief Shared pointer to an FD event handler.
typedef boost::shared_ptr<FDEventHandler> FDEventHandlerPtr;

}  // namespace isc::util
}  // namespace isc

#endif  // FD_EVENT_HANDLER_H
