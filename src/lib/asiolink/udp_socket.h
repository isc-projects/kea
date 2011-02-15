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

#ifndef __UDP_SOCKET_H
#define __UDP_SOCKET_H 1

#ifndef ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include <cstddef>
#include <asiolink/io_socket.h>
#include <asiolink/io_service.h>

namespace asiolink {

/// \brief The \c UDPSocket class is a concrete derived class of
/// \c IOSocket that represents a UDP socket.
///
/// Other notes about \c TCPSocket applies to this class, too.
class UDPSocket : public IOSocket {
private:
    /// \brief Class is non-copyable
    UDPSocket(const UDPSocket&);
    UDPSocket& operator=(const UDPSocket&);

public:
    enum {
        MAX_SIZE = 4096         // Send and receive size
    };
    
    /// \brief Constructor from an ASIO UDP socket.
    ///
    /// \param socket The ASIO representation of the UDP socket.
    UDPSocket(asio::ip::udp::socket& socket) :
        socket_ptr_(NULL), socket_(socket)
    {}

    /// \brief Constructor
    ///
    /// Used when the UDPSocket is being asked to manage its own internal
    /// socket.
    UDPSocket(IOService& service);

    /// \brief Destructor
    virtual ~UDPSocket();

    virtual int getNative() const { return (socket_.native()); }
    virtual int getProtocol() const { return (IPPROTO_UDP); }

    /// \brief Open Socket
    ///
    /// Opens the UDP socket.  In the model for transport-layer agnostic I/O,
    /// an "open" operation includes a connection to the remote end (which
    /// may take time).  This does not happen for UDP, so the method returns
    /// "false" to indicate that the operation completed synchronously.
    ///
    /// \param endpoint Endpoint to which the socket will connect to.
    /// \param callback Unused.
    ///
    /// \return false to indicate that the "operation" completed synchronously.
    virtual bool open(const IOEndpoint* endpoint, IOCompletionCallback&);

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
    virtual void async_send(const void* data, size_t length,
        const IOEndpoint* endpoint, IOCompletionCallback& callback);

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
    virtual void async_receive(void* data, size_t length, IOEndpoint* endpoint,
        IOCompletionCallback& callback);

    /// \brief Cancel I/O On Socket
    virtual void cancel();

    /// \brief Close socket
    virtual void close();


private:
    // Two variables to hold the socket - a socket and a pointer to it.  This
    // handles the case where a socket is passed to the UDPSocket on
    // construction, or where it is asked to manage its own socket.
    asio::ip::udp::socket*      socket_ptr_;    ///< Pointer to the socket
    asio::ip::udp::socket&      socket_;        ///< Socket
};

}      // namespace asiolink
#endif // __UDP_SOCKET_H
