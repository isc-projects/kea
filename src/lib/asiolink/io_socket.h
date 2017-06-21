// Copyright (C) 2010-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IO_SOCKET_H
#define IO_SOCKET_H 1

// IMPORTANT NOTE: only very few ASIO headers files can be included in
// this file.  In particular, asio.hpp should never be included here.
// See the description of the namespace below.
#include <unistd.h>             // for some network system calls

#include <functional>
#include <string>

#include <exceptions/exceptions.h>

namespace isc {
namespace asiolink {

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
public:

    /// @name Types of objects encapsulating socket options.
    //@{

    /// @brief Represents SO_REUSEADDR socket option.
    typedef boost::asio::socket_base::reuse_address ReuseAddress;

    //@}

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

} // namespace asiolink
} // namespace isc

#endif // IO_SOCKET_H
