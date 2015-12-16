// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IO_ENDPOINT_H
#define IO_ENDPOINT_H 1

// IMPORTANT NOTE: only very few ASIO headers files can be included in
// this file.  In particular, asio.hpp should never be included here.
// See the description of the namespace below.

#include <functional>
#include <string>

#include <exceptions/exceptions.h>
#include <asiolink/io_address.h>

# include <ostream>

#include <unistd.h>             // for some network system calls

#include <sys/socket.h>         // for sockaddr

namespace isc {
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

    /// \brief Returns the address of the endpoint in the form of sockaddr
    /// structure.
    ///
    /// The actual instance referenced by the returned value of this method
    /// is of per address family structure: For IPv4 (AF_INET), it's
    /// \c sockaddr_in; for IPv6 (AF_INET6), it's \c sockaddr_in6.
    /// The corresponding port and address members of the underlying structure
    /// will be set in the network byte order.
    ///
    /// This method is "redundant" in that all information to construct the
    /// \c sockaddr is available via the other "get" methods.
    /// It is still defined for performance sensitive applications that need
    /// to get the address information, such as for address based access
    /// control at a high throughput.  Internally it is implemented with
    /// minimum overhead such as data copy (this is another reason why this
    /// method returns a reference).
    ///
    /// As a tradeoff, this method is more fragile; it assumes that the
    /// underlying ASIO implementation stores the address information in
    /// the form of \c sockaddr and it can be accessed in an efficient way.
    /// This is the case as of this writing, but if the underlying
    /// implementation changes this method may become much slower or its
    /// interface may have to be changed, too.
    ///
    /// It is therefore discouraged for normal applications to use this
    /// method.  Unless the application is very performance sensitive, it
    /// should use the other "get" method to retrieve specific information
    /// of the endpoint.
    ///
    /// The returned reference is only valid while the corresponding
    /// \c IOEndpoint is valid.  Once it's destructed the reference will
    /// become invalid.
    ///
    /// \exception None
    /// \return Reference to a \c sockaddr structure corresponding to the
    /// endpoint.
    virtual const struct sockaddr& getSockAddr() const = 0;

    bool operator==(const IOEndpoint& other) const;
    bool operator!=(const IOEndpoint& other) const;

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

/// \brief Insert the \c IOEndpoint as a string into stream.
///
/// This method converts \c endpoint into a string and inserts it into the
/// output stream \c os.
///
/// This method converts the address and port of the endpoint in the textual
/// format that other Kea modules would use in logging, i.e.,
/// - For IPv6 address: [&lt;address&gt;]:port (e.g., [2001:db8::5300]:53)
/// - For IPv4 address: &lt;address&gt;:port (e.g., 192.0.2.53:5300)
///
/// If it's neither IPv6 nor IPv4, it converts the endpoint into text in the
/// same format as that for IPv4, although in practice such a case is not
/// really expected.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param endpoint A reference to an \c IOEndpoint object output by the
/// operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream& operator<<(std::ostream& os, const IOEndpoint& endpoint);
} // namespace asiolink
} // namespace isc
#endif // IO_ENDPOINT_H

// Local Variables:
// mode: c++
// End:
