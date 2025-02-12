// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ICMP_ENDPOINT_H
#define ICMP_ENDPOINT_H 1

#include <asiolink/io_endpoint.h>

namespace isc {
namespace ping_check {

/// @brief The @c ICMPEndpoint class is a concrete derived class of
/// @c IOEndpoint that represents an endpoint of a ICMP packet.
///
/// Other notes about @c TCPEndpoint applies to this class, too.
class ICMPEndpoint : public asiolink::IOEndpoint {
public:
    ///
    /// @name Constructors and Destructor.
    ///
    //@{

    /// @brief Default Constructor
    ///
    /// Creates an internal endpoint.  This is expected to be set by some
    /// external call.
    ICMPEndpoint() :
        asio_endpoint_placeholder_(new boost::asio::ip::icmp::endpoint()),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}

    /// @brief Constructor from an address.
    ///
    /// @param address The IP address of the endpoint.
    explicit ICMPEndpoint(const asiolink::IOAddress& address) :
        asio_endpoint_placeholder_(
            new boost::asio::ip::icmp::endpoint(boost::asio::ip::make_address(address.toText()), 0)),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}

    /// @brief Copy Constructor from an ASIO ICMP endpoint.
    ///
    /// This constructor is designed to be an efficient wrapper for the
    /// corresponding ASIO class, @c icmp::endpoint.
    ///
    /// @param asio_endpoint The ASIO representation of the ICMP endpoint.
    explicit ICMPEndpoint(boost::asio::ip::icmp::endpoint& asio_endpoint) :
        asio_endpoint_placeholder_(0), asio_endpoint_(asio_endpoint)
    {}

    /// @brief Constructor from a const ASIO ICMP endpoint.
    ///
    /// This constructor is designed to be an efficient wrapper for the
    /// corresponding ASIO class, @c icmp::endpoint.
    ///
    /// @param asio_endpoint The ASIO representation of the TCP endpoint.
    explicit ICMPEndpoint(const boost::asio::ip::icmp::endpoint& asio_endpoint) :
        asio_endpoint_placeholder_(new boost::asio::ip::icmp::endpoint(asio_endpoint)),
        asio_endpoint_(*asio_endpoint_placeholder_)
    {}

    /// @brief The destructor.
    virtual ~ICMPEndpoint() { delete asio_endpoint_placeholder_; }
    //@}

    /// @brief Fetches the IP address of the endpoint.
    ///
    /// @return the endpoint's IP address as an IOAddress.
    virtual asiolink::IOAddress getAddress() const {
        return (asio_endpoint_.address());
    }

    /// @brief Fetches the IP address of the endpoint in native form.
    ///
    /// @return the endpoint's IP address as a struct sockaddr.
    virtual const struct sockaddr& getSockAddr() const {
        return (*asio_endpoint_.data());
    }

    /// @brief Fetches the IP port number of the endpoint.
    ///
    /// @return the endpoint's port number as a unit16_t.
    virtual uint16_t getPort() const {
        return (asio_endpoint_.port());
    }

    /// @brief Fetches the network protocol of the endpoint.
    ///
    /// @return the endpoint's protocol as a short
    virtual short getProtocol() const {
        return (asio_endpoint_.protocol().protocol());
    }

    /// @brief Fetches the network protocol family of the endpoint.
    ///
    /// @return the endpoint's protocol as a short
    virtual short getFamily() const {
        return (asio_endpoint_.protocol().family());
    }

    /// @brief Fetches the underlying ASIO endpoint implementation
    ///
    /// This is not part of the exposed IOEndpoint API but allows
    /// direct access to the ASIO implementation of the endpoint
    ///
    /// @return the wrapped ASIO endpoint instance as a const
    inline const boost::asio::ip::icmp::endpoint& getASIOEndpoint() const {
        return (asio_endpoint_);
    }

    /// @brief Fetches the underlying ASIO endpoint implementation
    ///
    /// This is not part of the exposed IOEndpoint API but allows
    /// direct access to the ASIO implementation of the endpoint
    ///
    /// @return the wrapped ASIO endpoint instance as a non-const
    inline boost::asio::ip::icmp::endpoint& getASIOEndpoint() {
        return (asio_endpoint_);
    }

private:
    /// @brief Pointer to the ASIO endpoint placeholder.
    boost::asio::ip::icmp::endpoint* asio_endpoint_placeholder_;

    /// @brief Reference to the underlying ASIO endpoint instance.
    boost::asio::ip::icmp::endpoint& asio_endpoint_;
};

} // namespace ping_check
} // namespace isc
#endif // ICMP_ENDPOINT_H
