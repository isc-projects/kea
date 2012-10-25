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

#ifndef CLIENT_H
#define CLIENT_H 1

#include <string>
#include <ostream>

#include <boost/noncopyable.hpp>

#include <acl/ip_check.h>

namespace isc {
namespace asiolink {
class IOMessage;
class IOEndpoint;
}

namespace acl {
struct IPAddress;
}

namespace server_common {

/// A DNS client with a single request context.
///
/// The \c Client class represents a DNS client with information of one
/// DNS request (e.g., a query).  The information includes the source and
/// destination IP addresses of the request, information of the DNS request
/// message such as the query name or (if provided) TSIG key information.
///
/// A \c Client class object is expected to be constructed on receiving a
/// new request with lower level information such as IP addresses and is
/// updated with DNS specific information as the server processes the request.
/// It is also expected to be used as the primary interface for request
/// processing such as query handling or access control.
///
/// Furthermore, to minimize the overhead, this class would be further
/// extended so that it can be reusable with an additional method to reset
/// the internal information.
///
/// In the current initial implementation, however, it only contains the
/// lower level information in the form of \c IOMessage object and cannot
/// be reused (it must be constructed for every new request).  Also, the
/// only actual usage of this class at this moment is for ACL handling.
///
/// A \c Client class object is generally assumed to be valid throughout
/// the processing of a single request, and then be destructed or (when
/// supported) reset.  To avoid it is copied and held accidentally beyond
/// the expected valid period, it is intentionally made non copyable.
///
/// Notes about other possibilities: we may want to abstract it further,
/// so that it can also be used for DHCP.  In that case, we'd subclass a
/// base client class for DNS specific clients and DHCP specific clients.
/// We might also want to separate DNS clients for authoritative servers
/// and clients for the resolver, especially because the former could be
/// simpler with performance optimizations.
class Client : boost::noncopyable {
public:
    ///
    /// \name Constructors and Destructor
    ///
    //@{
    /// The constructor.
    ///
    /// This initial version of constructor takes an \c IOMessage object
    /// that is supposed to represent a DNS request message sent from an
    /// external client (but the constructor does not perform any assumption
    /// check on the given \c IOMessage).
    ///
    /// If and when we extend the behavior and responsibility
    /// of this class, this version of constructor will probably be
    /// deprecated.
    ///
    /// \c request_message must be valid throughout the lifetime of the client.
    ///
    /// \exception None
    /// \param request_message Refers to \c IOMessage corresponding to some
    /// DNS request message.
    explicit Client(const isc::asiolink::IOMessage& request_message);

    /// The destructor
    ~Client();
    //@}

    /// Return the client's endpoint of the request.
    ///
    /// This should be identical to the result of \c getRemoteEndpoint()
    /// called on \c request_message passed to the constructor.
    ///
    /// \exception None
    const isc::asiolink::IOEndpoint& getRequestSourceEndpoint() const;

    /// Return the IP address part of the client request's endpoint.
    ///
    /// The resulting \c IPAddress can be constructed using
    /// \c getRequestSourceEndpoint(), and in that sense this method is
    /// redundant.  But this implementation internally constructs the
    /// \c IPAddress on construction and always returns a reference to it,
    /// and should be more efficient.  It is provided so that it can be
    /// called multiple times in a complicated ACL with minimum cost.
    ///
    /// \exception None
    const isc::acl::IPAddress& getRequestSourceIPAddress() const;

    /// Convert the Client to a string.
    ///
    /// (In the initial implementation) the format of the resulting string
    /// is as follows:
    /// \code <IP address>#<port>
    /// \endcode
    /// The IP address is the textual representation of the client's IP
    /// address, which is the source address of the request the client has
    /// sent.  The port is the UDP or TCP of the client's end of the request.
    ///
    /// \exception std::bad_alloc Internal resource allocation fails
    std::string toText() const;

private:
    struct ClientImpl;
    ClientImpl* impl_;
};

/// \brief Insert the \c Client as a string into stream.
///
/// This method convert \c client into a string and inserts it into the
/// output stream \c os.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param client A reference to a \c Client object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream& operator<<(std::ostream& os, const Client& client);
}
}

#endif  // CLIENT_H

// Local Variables:
// mode: c++
// End:
