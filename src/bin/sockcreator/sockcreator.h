// Copyright (C) 2010  CZ NIC
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

/**
 * \file sockcreator.h
 * \short Socket creator functionality.
 *
 * This module holds the functionality of the socket creator. It is
 * a separate module from main to ease up the tests.
 */

#ifndef __SOCKCREATOR_H
#define __SOCKCREATOR_H 1

#include <sys/types.h>
#include <sys/socket.h>

namespace isc {
namespace socket_creator {

/**
 * \short Create a socket and bind it.
 *
 * This is just a bundle of socket() and bind() calls. The sa_family of
 * bind_addr is used to determine the domain of the socket.
 *
 * \return The file descriptor of the newly created socket, if everything
 *     goes well. A negative number is returned if an error occurs -
 *     -1 if the socket() call fails or -2 if bind() fails. In case of error,
 *     errno is set (or better, left intact from socket() or bind()).
 * \param type The type of socket to create (SOCK_STREAM, SOCK_DGRAM, etc).
 * \param bind_addr The address to bind.
 * \param addr_len The actual length of bind_addr.
 */
int
get_sock(const int type, struct sockaddr *bind_addr, const socklen_t addr_len);

/**
 * Type of the get_sock function, to pass it as parameter.
 */
typedef
int
(*get_sock_t)(const int, struct sockaddr *, const socklen_t);

/**
 * Sends a payload socket file descriptor to destination file descriptor.
 * This is temporary and it will be stolen somewhere in the surrounding code,
 * since it is there already somewhere.
 *
 * TODO Actually steal it.
 */
int
send_fd(const int destination, const int payload);

/**
 * Type of the send_fd() function, so it can be passed as a parameter.
 */
typedef
int
(*send_fd_t)(const int, const int);

/**
 * \short Infinite loop parsing commands and returning the sockets.
 *
 * This reads commands and socket descriptions from the input_fd
 * file descriptor, creates sockets and writes the results (socket or
 * error) to output_fd.
 *
 * Current errors are:
 * - 1: Read error
 * - 2: Write error
 * - 3: Protocol error (unknown command, etc)
 *
 * It terminates either if a command asks it to or when unrecoverable
 * error happens.
 *
 * \return Like a return value of a main - 0 means everything OK, anything
 *     else is error.
 * \param input_fd Here is where it reads the commads.
 * \param output_fd Here is where it writes the results.
 * \param get_sock_fun The function that is used to create the sockets.
 *     This should be left on the default value, the parameter is here
 *     for testing purposes.
 * \param send_fd_fun The function that is used to send the socket over
 *     a file descriptor. This should be left on the default value, it is
 *     here for testing purposes.
 */
int
run(const int input_fd, const int output_fd,
    const get_sock_t get_sock_fun = get_sock,
    const send_fd_t send_fd_fun = send_fd);

/*
 * \short write() that writes everything.
 * Wrapper around write(). The difference is, it never writes less data
 * and looks successfull (eg. it blocks until all data are written).
 * Retries on signals.
 *
 * \return True if sucessfull, false otherwise. The errno variable is left
 *     intact.
 * \param fd Where to write.
 * \param data The buffer to write.
 * \param length How much data is there to write.
 *
 * TODO: Shouldn't this be in some kind of library?
 */
bool
write_data(const int fd, const char *data, const size_t length);

/*
 * \short read() that reads everything.
 * Wrapper around read(). It does not do short reads, if it returns less,
 * it means there was EOF. It retries on signals.
 *
 * \return Number of bytes read or -1 on error.
 * \param fd Where to read data from.
 * \param data Where to put the data.
 * \param length How many of them.
 *
 * TODO: Shouldn't this be in some kind of library?
 */
ssize_t
read_data(const int fd, char *buffer, const size_t length);

} // End of the namespaces
}

#endif // __SOCKCREATOR_H
