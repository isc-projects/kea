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

#ifndef __IOSOCKET_H
#define __IOSOCKET_H 1

// IMPORTANT NOTE: only very few ASIO headers files can be included in
// this file.  In particular, asio.hpp should never be included here.
// See the description of the namespace below.
#include <unistd.h>             // for some network system calls

#include <functional>
#include <string>

#include <exceptions/exceptions.h>
#include <coroutine.h>

#include <asiolink/io_completion_cb.h>

namespace asiolink {

/// Forward declaration of an IOEndpoint
class IOEndpoint;


/// \brief The \c IOSocket class is an abstract base class to represent
/// various types of network sockets.
///
/// This class is a wrapper for the ASIO socket classes such as
/// \c ip::tcp::socket and \c ip::udp::socket.
///
/// Derived class implementations are completely hidden within the
/// implementation.  User applications only get access to concrete
/// \c IOSocket objects via the abstract interfaces.
///
/// We may revisit this decision when we generalize the wrapper and more
/// modules use it.  Also, at that point we may define a separate (visible)
/// derived class for testing purposes rather than providing factory methods
/// (i.e., getDummy variants below).
class IOSocket {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    IOSocket(const IOSocket& source);
    IOSocket& operator=(const IOSocket& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class
    /// should never be instantiated (except as part of a derived class).
    IOSocket() {}
public:
    /// The destructor.
    virtual ~IOSocket() {}
    //@}

    /// \brief Return the "native" representation of the socket.
    ///
    /// In practice, this is the file descriptor of the socket for
    /// UNIX-like systems so the current implementation simply uses
    /// \c int as the type of the return value.
    /// We may have to need revisit this decision later.
    ///
    /// In general, the application should avoid using this method;
    /// it essentially discloses an implementation specific "handle" that
    /// can change the internal state of the socket (consider the
    /// application closes it, for example).
    /// But we sometimes need to perform very low-level operations that
    /// requires the native representation.  Passing the file descriptor
    /// to a different process is one example.
    /// This method is provided as a necessary evil for such limited purposes.
    ///
    /// This method never throws an exception.
    ///
    /// \return The native representation of the socket.  This is the socket
    /// file descriptor for UNIX-like systems.
    virtual int getNative() const = 0;

    /// \brief Return the transport protocol of the socket.
    ///
    /// Currently, it returns \c IPPROTO_UDP for UDP sockets, and
    /// \c IPPROTO_TCP for TCP sockets.
    ///
    /// This method never throws an exception.
    ///
    /// \return IPPROTO_UDP for UDP sockets
    /// \return IPPROTO_TCP for TCP sockets
    virtual int getProtocol() const = 0;

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
    virtual bool open(const IOEndpoint* endpoint,
        IOCompletionCallback& callback) = 0;

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
        const IOEndpoint* endpoint, IOCompletionCallback& callback) = 0;

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
        IOCompletionCallback& callback) = 0;

    /// \brief Cancel I/O On Socket
    virtual void cancel() = 0;

    /// \brief Close socket
    virtual void close() = 0;

    /// \brief Return a non-usable "dummy" UDP socket for testing.
    ///
    /// This is a class method that returns a "mock" of UDP socket.
    /// This is not associated with any actual socket, and its only
    /// responsibility is to return \c IPPROTO_UDP from \c getProtocol().
    /// The only feasible usage of this socket is for testing so that
    /// the test code can prepare some "UDP data" even without opening any
    /// actual socket.
    ///
    /// This method never throws an exception.
    ///
    /// \return A reference to an \c IOSocket object whose \c getProtocol()
    /// returns \c IPPROTO_UDP.
    static IOSocket& getDummyUDPSocket();

    /// \brief Return a non-usable "dummy" TCP socket for testing.
    ///
    /// See \c getDummyUDPSocket().  This method is its TCP version.
    ///
    /// \return A reference to an \c IOSocket object whose \c getProtocol()
    /// returns \c IPPROTO_TCP.
    static IOSocket& getDummyTCPSocket();
};

}      // asiolink
#endif // __IOSOCKET_H

// Local Variables: 
// mode: c++
// End: 
