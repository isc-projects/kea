// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef WATCH_SOCKET_H
#define WATCH_SOCKET_H

/// @file watch_socket.h Defines the class, WatchSocket.

#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp_ddns {

/// @brief Exception thrown if an error occurs during IO source open.
class WatchSocketError : public isc::Exception {
public:
    WatchSocketError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Provides an IO "ready" semaphore for use with select() or poll()
/// WatchSocket exposes a single open file descriptor, the "select-fd" which
/// can be marked as being ready to read (i.e. !EWOULDBLOCK) and cleared
/// (i.e. EWOULDBLOCK).  The select-fd can be used with select(), poll(), or
/// their variants alongside other file descriptors.
///
/// Internally, WatchSocket uses a pipe.  The select-fd is the "read" end of
/// pipe.  To mark the socket as ready to read, an integer marker is written
/// to the pipe.  To clear the socket, the marker is read from the pipe.  Note
/// that WatchSocket will only write the marker if it is not already marked.
/// This prevents the socket's pipe from filling endlessly.
class WatchSocket {
public:
    /// @brief Value used to signify an invalid descriptor.
    static const int INVALID_SOCKET = -1;
    /// @brief Value written to the source when marking the socket as ready.
    static const uint32_t MARKER = 0xDEADBEEF;

    /// @brief Constructor
    ///
    /// Constructs an instance of the WatchSocket in the cleared (EWOULDBLOCK)
    /// state.
    WatchSocket();

    /// @brief Destructor
    ///
    /// Closes all internal resources, including the select-fd.
    virtual ~WatchSocket();

    /// @brief Marks the select-fd as ready to read.
    ///
    /// Marks the socket as ready to read, if is not already so marked.
    ///
    /// @throw WatchSocketError if an error occurs marking the socket.
    void markReady();

    /// @brief Returns true the if socket is marked as ready.
    bool isReady();

    /// @brief Clears the socket's ready to read marker.
    ///
    /// Clears the socket if it is currently marked as ready to read.
    ///
    /// @throw WatchSocketError if an error occurs clearing the socket
    /// marker.
    void clearReady();

    /// @brief Returns the file descriptor to use to monitor the socket.
    ///
    /// @note Using this file descriptor as anything other than an argument
    /// to select() or similar methods can have unpredictable results.
    ///
    /// @return The file descriptor associated with read end of the socket's
    /// pipe.
    int getSelectFd();

private:
    /// @brief The end of the pipe to which the marker is written
    int source_;

    /// @brief The end of the pipe from which the marker is read.
    /// This is the value returned as the select-fd.
    int sink_;

    /// @brief True the socket is currently marked ready to read.
    bool ready_flag_;
};

/// @brief Defines a smart pointer to an instance of a WatchSocket.
typedef boost::shared_ptr<WatchSocket> WatchSocketPtr;

} // namespace isc::dhcp_ddns
} // namespace isc

#endif
