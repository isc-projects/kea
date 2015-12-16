// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef WATCH_SOCKET_H
#define WATCH_SOCKET_H

/// @file watch_socket.h Defines the class, WatchSocket.

#include <exceptions/exceptions.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <stdint.h>
#include <string>

namespace isc {
namespace util {

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
///
/// @warning Because the read or "sink" side of the pipe is used as the select_fd,
/// it is possible for that fd to be interfered with, albeit only from within the
/// process space which owns it.  Performing operations that may alter the fd's state
/// such as close, read, or altering behavior flags with fcntl or ioctl can have
/// unpredictable results.  It is intended strictly use with functions such as select()
/// poll() or their variants.
class WatchSocket : public boost::noncopyable {
public:
    /// @brief Value used to signify an invalid descriptor.
    static const int SOCKET_NOT_VALID = -1;
    /// @brief Value written to the source when marking the socket as ready.
    /// The value itself is arbitrarily chosen as one that is unlikely to occur
    /// otherwise and easy to debug.
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
    /// If an error occurs, closeSocket is called. This will force any further
    /// use of the select_fd to fail rather than show the fd as READY.  Such
    /// an error is almost surely a programmatic error which has corrupted the
    /// select_fd.
    ///
    /// @throw WatchSocketError if an error occurs marking the socket.
    void markReady();

    /// @brief Returns true the if socket is marked as ready.
    ///
    /// This method uses a non-blocking call to  select() to test read state of the
    /// select_fd.  Rather than track what the status "should be" it tests the status.
    /// This should eliminate conditions where the select-fd appear to be perpetually
    /// ready.
    /// @return  Returns true if select_fd is not SOCKET_NOT_VALID and select() reports it
    /// as !EWOULDBLOCK, otherwise it returns false.
    /// This method is guaranteed NOT to throw.
    bool isReady();

    /// @brief Clears the socket's ready to read marker.
    ///
    /// Clears the socket if it is currently marked as ready to read.
    /// If an error occurs, closeSocket is called. This will force any further
    /// use of the select_fd to fail rather than show the fd as READY.  Such
    /// an error is almost surely a programmatic error which has corrupted the
    /// select_fd.
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

    /// @brief Closes the descriptors associated with the socket.
    ///
    /// This method is used to close the socket and capture errors that
    /// may occur during this operation.
    ///
    /// @param [out] error_string Holds the error string if closing
    /// the socket failed. It will hold empty string otherwise.
    ///
    /// @return true if the operation was successful, false otherwise.
    bool closeSocket(std::string& error_string);

private:

    /// @brief Closes the descriptors associated with the socket.
    ///
    /// This method is called by the class destructor and it ignores
    /// any errors that may occur while closing the sockets.
    void closeSocket();

    /// @brief The end of the pipe to which the marker is written
    int source_;

    /// @brief The end of the pipe from which the marker is read.
    /// This is the value returned as the select-fd.
    int sink_;
};

/// @brief Defines a smart pointer to an instance of a WatchSocket.
typedef boost::shared_ptr<WatchSocket> WatchSocketPtr;

} // namespace isc::util
} // namespace isc

#endif
