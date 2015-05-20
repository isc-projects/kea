// Copyright (C) 2011-2012, 2015  Internet Systems Consortium, Inc. ("ISC")
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

/// \file sockcreator.h
/// \short Socket creator functionality.
///
/// This module holds the functionality of the socket creator. It is a separate
/// module from main to make testing easier.

#ifndef SOCKCREATOR_H
#define SOCKCREATOR_H 1

#include <util/io/fd_share.h>
#include <exceptions/exceptions.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

namespace isc {
namespace socket_creator {

// Exception classes - the base class exception SocketCreatorError is caught
// by main() and holds an exit code returned to the environment.  The code
// depends on the exact exception raised.
class SocketCreatorError : public isc::Exception {
public:
    SocketCreatorError(const char* file, size_t line, const char* what,
                       int exit_code) :
        isc::Exception(file, line, what), exit_code_(exit_code) {}

    int getExitCode() const {
        return (exit_code_);
    }

private:
    const int exit_code_;   // Code returned to exit()
};

class ReadError : public SocketCreatorError {
public:
    ReadError(const char* file, size_t line, const char* what) :
        SocketCreatorError(file, line, what, 1) {}
};

class WriteError : public SocketCreatorError {
public:
    WriteError(const char* file, size_t line, const char* what) :
        SocketCreatorError(file, line, what, 2) {}
};

class ProtocolError : public SocketCreatorError {
public:
    ProtocolError(const char* file, size_t line, const char* what) :
        SocketCreatorError(file, line, what, 3) {}
};

class InternalError : public SocketCreatorError {
public:
    InternalError(const char* file, size_t line, const char* what) :
        SocketCreatorError(file, line, what, 4) {}
};


// Type of the close() function, so it can be passed as a parameter.
// Argument is the same as that for close(2).
typedef int (*close_t)(int);

/// \short Create a socket and bind it.
///
/// This is just a bundle of socket() and bind() calls. The sa_family of
/// bind_addr is used to determine the domain of the socket.
///
/// \param type The type of socket to create (SOCK_STREAM, SOCK_DGRAM, etc).
/// \param bind_addr The address to bind.
/// \param addr_len The actual length of bind_addr.
/// \param close_fun The function used to close a socket if there's an error
///     after the creation.
///
/// \return The file descriptor of the newly created socket, if everything
///         goes well. A negative number is returned if an error occurs -
///         -1 if the socket() call fails or -2 if bind() fails. In case of
///         error, errno is set (or left intact from socket() or bind()).
int
getSock(const int type, struct sockaddr* bind_addr, const socklen_t addr_len,
        const close_t close_fun);

// Define some types for functions used to perform socket-related operations.
// These are typedefed so that alternatives can be passed through to the
// main functions for testing purposes.

// Type of the function to get a socket and to pass it as parameter.
// Arguments are those described above for getSock().
typedef int (*get_sock_t)(const int, struct sockaddr *, const socklen_t,
                          const close_t close_fun);

// Type of the send_fd() function, so it can be passed as a parameter.
// Arguments are the same as those of the send_fd() function.
typedef int (*send_fd_t)(const int, const int);


/// \brief Infinite loop parsing commands and returning the sockets.
///
/// This reads commands and socket descriptions from the input_fd file
/// descriptor, creates sockets and writes the results (socket or error) to
/// output_fd.
///
/// It terminates either if a command asks it to or when unrecoverable error
/// happens.
///
/// \param input_fd File number of the stream from which the input commands
///        are read.
/// \param output_fd File number of the stream to which the response is
///        written.  The socket is sent as part of a control message associated
///        with that stream.
/// \param get_sock_fun The function that is used to create the sockets.
///        This should be left on the default value, the parameter is here
///        for testing purposes.
/// \param send_fd_fun The function that is used to send the socket over
///        a file descriptor. This should be left on the default value, it is
///        here for testing purposes.
/// \param close_fun The close function used to close sockets, coming from
///        unistd.h. It can be overriden in tests.
///
/// \exception isc::socket_creator::ReadError Error reading from input
/// \exception isc::socket_creator::WriteError Error writing to output
/// \exception isc::socket_creator::ProtocolError Unrecognised command received
/// \exception isc::socket_creator::InternalError Other error
void
run(const int input_fd, const int output_fd, get_sock_t get_sock_fun,
    send_fd_t send_fd_fun, close_t close_fun);

}   // namespace socket_creator
}   // NAMESPACE ISC

#endif // SOCKCREATOR_H
