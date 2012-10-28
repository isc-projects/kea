// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef IO_MESSAGE_H
#define IO_MESSAGE_H 1

// IMPORTANT NOTE: only very few ASIO headers files can be included in
// this file.  In particular, asio.hpp should never be included here.
// See the description of the namespace below.
#include <unistd.h>             // for some network system calls

#include <functional>
#include <string>

#include <exceptions/exceptions.h>

#include <asiolink/io_endpoint.h>
#include <asiolink/io_socket.h>

namespace isc {
namespace asiolink {

/// \brief The \c IOMessage class encapsulates an incoming message received
/// on a socket.
///
/// An \c IOMessage object represents a tuple of a chunk of data
/// (a UDP packet or some segment of TCP stream), the socket over which the
/// data is passed, the information about the other end point of the
/// communication, and perhaps more.
///
/// The current design and interfaces of this class is tentative.
/// It only provides a minimal level of support that is necessary for
/// the current implementation of the authoritative server.
/// A future version of this class will definitely support more.
class IOMessage {
    ///
    /// \name Constructors and Destructor
    ///

    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    IOMessage(const IOMessage& source);
    IOMessage& operator=(const IOMessage& source);
public:
    /// \brief Constructor from message data
    ///
    /// This constructor needs to handle the ASIO \c ip::address class,
    /// and is intended to be used within this wrapper implementation.
    /// Once the \c IOMessage object is created, the application can
    /// get access to the information via the wrapper interface such as
    /// \c getRemoteAddress().
    ///
    /// This constructor never throws an exception.
    ///
    /// \param data A pointer to the message data.
    /// \param data_size The size of the message data in bytes.
    /// \param io_socket The socket over which the data is given.
    /// \param remote_endpoint The other endpoint of the socket, that is,
    /// the sender of the message.
    IOMessage(const void* data, const size_t data_size,
              const IOSocket& io_socket, const IOEndpoint& remote_endpoint) :
        data_(data), data_size_(data_size), io_socket_(io_socket),
        remote_endpoint_(remote_endpoint)
    {}
    //@}

    /// \brief Returns a pointer to the received data.
    const void* getData() const { return (data_); }

    /// \brief Returns the size of the received data in bytes.
    size_t getDataSize() const { return (data_size_); }

    /// \brief Returns the socket on which the message arrives.
    const IOSocket& getSocket() const { return (io_socket_); }

    /// \brief Returns the endpoint that sends the message.
    const IOEndpoint& getRemoteEndpoint() const { return (remote_endpoint_); }

private:
    const void* data_;
    const size_t data_size_;
    const IOSocket& io_socket_;
    const IOEndpoint& remote_endpoint_;
};


} // namespace asiolink
} // namespace isc
#endif // IO_MESSAGE_H
