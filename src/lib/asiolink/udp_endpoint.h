// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UDP_ENDPOINT_H
#define UDP_ENDPOINT_H 1

#ifndef BOOST_ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include <asiolink/io_endpoint.h>

namespace isc {
namespace asiolink {

/// \brief The \c UDPEndpoint class is a concrete derived class of
/// \c IOEndpoint that represents an endpoint of a UDP packet.
///
/// Other notes about \c TCPEndpoint applies to this class, too.
class UDPEndpoint : public IOEndpoint {
public:
    ///
    /// \name Constructors and Destructor.
    ///
    //@{

    /// \brief Default Constructor
    ///
    /// Creates an internal endpoint.  This is expected to be set by some
    /// external call.
    UDPEndpoint() :
        asio_endpoint_placeholder_(new boost::asio::ip::udp::endpoint()),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}

    /// \brief Constructor from a pair of address and port.
    ///
    /// \param address The IP address of the endpoint.
    /// \param port The UDP port number of the endpoint.
    UDPEndpoint(const IOAddress& address, const unsigned short port) :
        asio_endpoint_placeholder_(
            new boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(address.toText()),
                              port)),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}

    /// \brief Constructor from an ASIO UDP endpoint.
    ///
    /// This constructor is designed to be an efficient wrapper for the
    /// corresponding ASIO class, \c udp::endpoint.
    ///
    /// \param asio_endpoint The ASIO representation of the UDP endpoint.
    UDPEndpoint(boost::asio::ip::udp::endpoint& asio_endpoint) :
        asio_endpoint_placeholder_(NULL), asio_endpoint_(asio_endpoint)
    {}

    /// \brief Constructor from an ASIO UDP endpoint.
    ///
    /// This constructor is designed to be an efficient wrapper for the
    /// corresponding ASIO class, \c udp::endpoint.
    ///
    /// \param asio_endpoint The ASIO representation of the TCP endpoint.
    UDPEndpoint(const boost::asio::ip::udp::endpoint& asio_endpoint) :
        asio_endpoint_placeholder_(new boost::asio::ip::udp::endpoint(asio_endpoint)),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}

    /// \brief The destructor.
    virtual ~UDPEndpoint() { delete asio_endpoint_placeholder_; }
    //@}

    virtual IOAddress getAddress() const {
        return (asio_endpoint_.address());
    }

    virtual const struct sockaddr& getSockAddr() const {
        return (*asio_endpoint_.data());
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

    // This is not part of the exposed IOEndpoint API but allows
    // direct access to the ASIO implementation of the endpoint
    inline const boost::asio::ip::udp::endpoint& getASIOEndpoint() const {
        return (asio_endpoint_);
    }
    inline boost::asio::ip::udp::endpoint& getASIOEndpoint() {
        return (asio_endpoint_);
    }

private:
    boost::asio::ip::udp::endpoint* asio_endpoint_placeholder_;
    boost::asio::ip::udp::endpoint& asio_endpoint_;
};

} // namespace asiolink
} // namespace isc
#endif // UDP_ENDPOINT_H

// Local Variables:
// mode: c++
// End:
