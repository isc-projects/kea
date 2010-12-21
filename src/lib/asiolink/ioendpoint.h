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

// $Id$

#ifndef __IOENDPOINT_H
#define __IOENDPOINT_H 1

// IMPORTANT NOTE: only very few ASIO headers files can be included in
// this file.  In particular, asio.hpp should never be included here.
// See the description of the namespace below.
#include <unistd.h>             // for some network system calls

#include <functional>
#include <string>

#include <exceptions/exceptions.h>

namespace asiolink {

/// \brief The \c IOEndpoint class is an abstract base class to represent
/// a communication endpoint.
///
/// This class is a wrapper for the ASIO endpoint classes such as
/// \c ip::tcp::endpoint and \c ip::udp::endpoint.
///
/// Derived class implementations are completely hidden within the
/// implementation.  User applications only get access to concrete
/// \c IOEndpoint objects via the abstract interfaces.
class IOEndpoint {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    IOEndpoint(const IOEndpoint& source);
    IOEndpoint& operator=(const IOEndpoint& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class
    /// should never be instantiated (except as part of a derived class).
    IOEndpoint() {}
public:
    /// The destructor.
    virtual ~IOEndpoint() {}
    //@}

    /// \brief Returns the address of the endpoint.
    ///
    /// This method returns an IOAddress object corresponding to \c this
    /// endpoint.
    ///
    /// Note that the return value is a real object, not a reference or
    /// a pointer.
    ///
    /// This is aligned with the interface of the ASIO counterpart:
    /// the \c address() method of \c ip::xxx::endpoint classes returns
    /// an \c ip::address object.
    ///
    /// This also means handling the address of an endpoint using this method
    /// can be expensive.  If the address information is necessary in a
    /// performance sensitive context and there's a more efficient interface
    /// for that purpose, it's probably better to avoid using this method.
    ///
    /// This method never throws an exception.
    ///
    /// \return A copy of \c IOAddress object corresponding to the endpoint.
    virtual IOAddress getAddress() const = 0;

    /// \brief Returns the port of the endpoint.
    virtual uint16_t getPort() const = 0;

    /// \brief Returns the protocol number of the endpoint (TCP, UDP...)
    virtual short getProtocol() const = 0;

    /// \brief Returns the address family of the endpoint.
    virtual short getFamily() const = 0;

    /// \brief A polymorphic factory of endpoint from address and port.
    ///
    /// This method creates a new instance of (a derived class of)
    /// \c IOEndpoint object that identifies the pair of given address
    /// and port.
    /// The appropriate derived class is chosen based on the specified
    /// transport protocol.  If the \c protocol doesn't specify a protocol
    /// supported in this implementation, an exception of class \c IOError
    /// will be thrown.
    ///
    /// Memory for the created object will be dynamically allocated.  It's
    /// the caller's responsibility to \c delete it later.
    /// If resource allocation for the new object fails, a corresponding
    /// standard exception will be thrown.
    ///
    /// \param protocol The transport protocol used for the endpoint.
    /// Currently, only \c IPPROTO_UDP and \c IPPROTO_TCP can be specified.
    /// \param address The (IP) address of the endpoint.
    /// \param port The transport port number of the endpoint
    /// \return A pointer to a newly created \c IOEndpoint object.
    static const IOEndpoint* create(const int protocol,
                                    const IOAddress& address,
                                    const unsigned short port);
};

}      // asiolink
#endif // __IOENDPOINT_H

// Local Variables: 
// mode: c++
// End: 
