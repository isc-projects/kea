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

#include <log/dummylog.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>             // for some IPC/network system calls

#include <iostream>
#include <cstddef>

#include <config.h>

#include <asiolink/io_asio_socket.h>
#include <asiolink/io_endpoint.h>
#include <asiolink/io_service.h>
#include <asiolink/tcp_endpoint.h>

namespace asiolink {

/// \brief The \c TCPSocket class is a concrete derived class of \c IOAsioSocket
/// that represents a TCP socket.
///
/// \param C Callback type
template <typename C>
class TCPSocket : public IOAsioSocket<C> {
private:
    /// \brief Class is non-copyable
    TCPSocket(const TCPSocket&);
    TCPSocket& operator=(const TCPSocket&);

public:
    
    /// \brief Constructor from an ASIO TCP socket.
    ///
    /// \param socket The ASIO representation of the TCP socket.  It
    /// is assumed that the caller will open and close the socket, so
    /// these operations are a no-op for that socket.
    TCPSocket(asio::ip::tcp::socket& socket);

    /// \brief Constructor
    ///
    /// Used when the TCPSocket is being asked to manage its own internal
    /// socket.  It is assumed that open() and close() will not be used.
    ///
    /// \param service I/O Service object used to manage the socket.
    TCPSocket(IOService& service);

    /// \brief Destructor
    virtual ~TCPSocket();

    virtual int getNative() const { return (socket_.native()); }
    virtual int getProtocol() const { return (IPPROTO_TCP); }

    /// \brief Open Socket
    ///
    /// Opens the TCP socket.  In the model for transport-layer agnostic I/O,
    /// an "open" operation includes a connection to the remote end (which
    /// may take time).  This does not happen for TCP, so the method returns
    /// "false" to indicate that the operation completed synchronously.
    ///
    /// \param endpoint Endpoint to which the socket will connect to.
    /// \param callback Unused.
    ///
    /// \return false to indicate that the "operation" completed synchronously.
    virtual bool open(const IOEndpoint* endpoint, C&);

    /// \brief Send Asynchronously
    ///
    /// This corresponds to async_send_to() for TCP sockets and async_send()
    /// for TCP.  In both cases an endpoint argument is supplied indicating the
    /// target of the send - this is ignored for TCP.
    ///
    /// \param data Data to send
    /// \param length Length of data to send
    /// \param endpoint Target of the send
    /// \param callback Callback object.
    virtual void asyncSend(const void* data, size_t length,
        const IOEndpoint* endpoint, C& callback);

    /// \brief Receive Asynchronously
    ///
    /// This correstponds to async_receive_from() for TCP sockets and
    /// async_receive() for TCP.  In both cases, an endpoint argument is
    /// supplied to receive the source of the communication.  For TCP it will
    /// be filled in with details of the connection.
    ///
    /// \param data Buffer to receive incoming message
    /// \param length Length of the data buffer
    /// \param cumulative Amount of data that should already be in the buffer.
    /// (This is ignored - every UPD receive fills the buffer from the start.)
    /// \param endpoint Source of the communication
    /// \param callback Callback object
    virtual void asyncReceive(void* data, size_t length, size_t cumulative,
        IOEndpoint* endpoint, C& callback);

    /// \brief Checks if the data received is complete.
    ///
    /// As all the data is received in one I/O, so this is, this is effectively
    /// a no-op (although it does update the amount of data received).
    ///
    /// \param data Data buffer containing data to date.  (This is ignored
    /// for TCP receives.)
    /// \param length Amount of data received in last asynchronous I/O
    /// \param cumulative On input, amount of data received before the last
    /// I/O.  On output, the total amount of data received to date.
    ///
    /// \return true if the receive is complete, false if another receive is
    /// needed.
    virtual bool receiveComplete(void*, size_t length, size_t& cumulative) {
        cumulative = length;
        return (true);
    }

    /// \brief Cancel I/O On Socket
    virtual void cancel();

    /// \brief Close socket
    virtual void close();


private:
    // Two variables to hold the socket - a socket and a pointer to it.  This
    // handles the case where a socket is passed to the TCPSocket on
    // construction, or where it is asked to manage its own socket.
    asio::ip::tcp::socket*      socket_ptr_;    ///< Pointer to own socket
    asio::ip::tcp::socket&      socket_;        ///< Socket
    bool                        isopen_;        ///< true when socket is open
};

// Constructor - caller manages socket

template <typename C>
TCPSocket<C>::TCPSocket(asio::ip::tcp::socket& socket) :
    socket_ptr_(NULL), socket_(socket), isopen_(true)
{
}

// Constructor - create socket on the fly

template <typename C>
TCPSocket<C>::TCPSocket(IOService& service) :
    socket_ptr_(new asio::ip::tcp::socket(service.get_io_service())),
    socket_(*socket_ptr_), isopen_(false)
{
}

// Destructor.  Only delete the socket if we are managing it.

template <typename C>
TCPSocket<C>::~TCPSocket()
{
    delete socket_ptr_;
}

// Open the socket.  Throws an error on failure
// TODO: Make the open more resilient

template <typename C> bool
TCPSocket<C>::open(const IOEndpoint* endpoint, C&) {

    // Ignore opens on already-open socket.  Don't throw a failure because
    // of uncertainties as to what precedes whan when using asynchronous I/O.
    // At also allows us a treat a passed-in socket as a self-managed socket.

    if (!isopen_) {
        if (endpoint->getFamily() == AF_INET) {
            socket_.open(asio::ip::tcp::v4());
        }
        else {
            socket_.open(asio::ip::tcp::v6());
        }
        isopen_ = true;

        // TODO: Complete TCPSocket::open()

    }
    return (false);
}

// Send a message.  Should never do this if the socket is not open, so throw
// an exception if this is the case.

template <typename C> void
TCPSocket<C>::asyncSend(const void*, size_t,
    const IOEndpoint* endpoint, C&)
{
    if (isopen_) {

        // Upconvert to a TCPEndpoint.  We need to do this because although
        // IOEndpoint is the base class of TCPEndpoint and TCPEndpoint, it
        // doing cont contain a method for getting at the underlying endpoint
        // type - those are in the derived class and the two classes differ on
        // return type.

        assert(endpoint->getProtocol() == IPPROTO_TCP);
        const TCPEndpoint* tcp_endpoint =
            static_cast<const TCPEndpoint*>(endpoint);
        std::cerr << "TCPSocket::asyncSend(): sending to " <<
            tcp_endpoint->getAddress().toText() <<
            ", port " << tcp_endpoint->getPort() << "\n";

        // TODO: Complete TCPSocket::asyncSend()

    } else {
        isc_throw(SocketNotOpen,
            "attempt to send on a TCP socket that is not open");
    }
}

// Receive a message. Note that the "cumulative" argument is ignored - every TCP
// receive is put into the buffer beginning at the start - there is no concept
// receiving a subsequent part of a message.  Same critera as before concerning
// the need for the socket to be open.

template <typename C> void
TCPSocket<C>::asyncReceive(void*, size_t, size_t,
    IOEndpoint* endpoint, C&)
{
    if (isopen_) {

        // Upconvert the endpoint again.
        assert(endpoint->getProtocol() == IPPROTO_TCP);
        const TCPEndpoint* tcp_endpoint =
            static_cast<const TCPEndpoint*>(endpoint);
        std::cerr << "TCPSocket::asyncReceive(): receiving from " <<
            tcp_endpoint->getAddress().toText() <<
            ", port " << tcp_endpoint->getPort() << "\n";

        // TODO: Complete TCPSocket::asyncReceive()

    } else {
        isc_throw(SocketNotOpen,
            "attempt to receive from a TCP socket that is not open");
    }
}

// Cancel I/O on the socket.  No-op if the socket is not open.
template <typename C> void
TCPSocket<C>::cancel() {
    if (isopen_) {
        socket_.cancel();
    }
}

// Close the socket down.  Can only do this if the socket is open and we are
// managing it ourself.

template <typename C> void
TCPSocket<C>::close() {
    if (isopen_ && socket_ptr_) {
        socket_.close();
        isopen_ = false;
    }
}

} // namespace asiolink

#endif // __TCP_SOCKET_H
