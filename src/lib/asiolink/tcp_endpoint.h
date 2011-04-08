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

#ifndef __TCP_ENDPOINT_H
#define __TCP_ENDPOINT_H 1

#ifndef ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include <asiolink/io_endpoint.h>

namespace isc {
namespace asiolink {

/// \brief The \c TCPEndpoint class is a concrete derived class of
/// \c IOEndpoint that represents an endpoint of a TCP packet.
///
/// Other notes about \c TCPEndpoint applies to this class, too.
class TCPEndpoint : public IOEndpoint {
public:
    ///
    /// \name Constructors and Destructor.
    ///
    //@{

    /// \brief Default Constructor
    ///
    /// Creates an internal endpoint.  This is expected to be set by some
    /// external call.
    TCPEndpoint() :
        asio_endpoint_placeholder_(new asio::ip::tcp::endpoint()),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}

    /// \brief Constructor from a pair of address and port.
    ///
    /// \param address The IP address of the endpoint.
    /// \param port The TCP port number of the endpoint.
    TCPEndpoint(const IOAddress& address, const unsigned short port) :
        asio_endpoint_placeholder_(
            new asio::ip::tcp::endpoint(asio::ip::address::from_string(address.toText()),
                              port)),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}

    /// \brief Constructor from an ASIO TCP endpoint.
    ///
    /// This constructor is designed to be an efficient wrapper for the
    /// corresponding ASIO class, \c tcp::endpoint.
    ///
    /// \param asio_endpoint The ASIO representation of the TCP endpoint.
    TCPEndpoint(asio::ip::tcp::endpoint& asio_endpoint) :
        asio_endpoint_placeholder_(NULL), asio_endpoint_(asio_endpoint)
    {}

    /// \brief Constructor from an ASIO TCP endpoint.
    ///
    /// This constructor is designed to be an efficient wrapper for the
    /// corresponding ASIO class, \c tcp::endpoint.
    ///
    /// \param asio_endpoint The ASIO representation of the TCP endpoint.
    TCPEndpoint(const asio::ip::tcp::endpoint& asio_endpoint) :
        asio_endpoint_placeholder_(new asio::ip::tcp::endpoint(asio_endpoint)),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}

    /// \brief The destructor.
    virtual ~TCPEndpoint() { delete asio_endpoint_placeholder_; }
    //@}

    virtual IOAddress getAddress() const {
        return (asio_endpoint_.address());
    }

    virtual uint16_t getPort() const {
        return (asio_endpoint_.port());
    }

    virtual short getProtocol() const {
        return (asio_endpoint_.protocol().protocol());
    }

    virtual short getFamily() const {
        return (asio_endpoint_.protocol().family());
    }

    // This is not part of the exosed IOEndpoint API but allows
    // direct access to the ASIO implementation of the endpoint
    inline const asio::ip::tcp::endpoint& getASIOEndpoint() const {
        return (asio_endpoint_);
    }
    inline asio::ip::tcp::endpoint& getASIOEndpoint() {
        return (asio_endpoint_);
    }

private:
    asio::ip::tcp::endpoint* asio_endpoint_placeholder_;
    asio::ip::tcp::endpoint& asio_endpoint_;
};

} // namespace asiolink
} // namespace isc
#endif // __TCP_ENDPOINT_H
