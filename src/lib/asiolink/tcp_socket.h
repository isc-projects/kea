// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __TCP_SOCKET_H
#define __TCP_SOCKET_H 1

#ifndef ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include <asiolink/io_socket.h>

namespace asiolink {

/// \brief The \c TCPSocket class is a concrete derived class of
/// \c IOSocket that represents a TCP socket.
///
/// In the current implementation, an object of this class is always
/// instantiated within the wrapper routines.  Applications are expected to
/// get access to the object via the abstract base class, \c IOSocket.
/// This design may be changed when we generalize the wrapper interface.
class TCPSocket : public IOSocket {
private:
    TCPSocket(const TCPSocket& source);
    TCPSocket& operator=(const TCPSocket& source);
public:
    /// \brief Constructor from an ASIO TCP socket.
    ///
    /// \param socket The ASIO representation of the TCP socket.
    TCPSocket(asio::ip::tcp::socket& socket) : socket_(socket) {}

    int getNative() const { return (socket_.native()); }
    int getProtocol() const { return (IPPROTO_TCP); }

    /// \brief Open Socket
    ///
    /// A call that is a no-op on UDP sockets, this opens a connection to the
    /// system identified by the given endpoint.
    ///
    /// \param endpoint Pointer to the endpoint object.  This is ignored for
    /// a UDP socket (the target is specified in the send call), but should
    /// be of type TCPEndpoint for a TCP connection.
    /// \param callback I/O Completion callback, called when the connect has
    /// completed.  In the stackless coroutines model, this will be the
    /// method containing the call to this function, allowing the operation to
    /// resume after the socket open has completed.
    ///
    /// \return true if an asynchronous operation was started and the caller
    /// should yield and wait for completion, false if not. (i.e. The UDP
    /// derived class will return false, the TCP class will return true).  This
    /// optimisation avoids the overhead required to post a callback to the
    /// I/O Service queue where nothing is done.
    virtual bool open(const IOEndpoint*, IOCompletionCallback&) {
        return false;
    }

    /// \brief Send Asynchronously
    ///
    /// This corresponds to async_send_to() for UDP sockets and async_send()
    /// for TCP.  In both cases an endpoint argument is supplied indicating the
    /// target of the send - this is ignored for TCP.
    ///
    /// \param data Data to send
    /// \param length Length of data to send
    /// \param endpoint Target of the send
    /// \param callback Callback object.
    virtual void async_send(const void*, size_t,
        const IOEndpoint*, IOCompletionCallback&) {
    }

    /// \brief Receive Asynchronously
    ///
    /// This correstponds to async_receive_from() for UDP sockets and
    /// async_receive() for TCP.  In both cases, an endpoint argument is
    /// supplied to receive the source of the communication.  For TCP it will
    /// be filled in with details of the connection.
    ///
    /// \param data Buffer to receive incoming message
    /// \param length Length of the data buffer
    /// \param endpoint Source of the communication
    /// \param callback Callback object
    virtual void async_receive(void* data, size_t, IOEndpoint*,
        IOCompletionCallback&) {
    }

    /// \brief Cancel I/O On Socket
    virtual void cancel() {
    }

    /// \brief Close socket
    virtual void close() {
    }

private:
    asio::ip::tcp::socket& socket_;
};


}      // namespace asiolink
#endif // __TCP_SOCKET_H
