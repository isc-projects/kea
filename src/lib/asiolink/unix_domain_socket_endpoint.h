// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UNIX_DOMAIN_SOCKET_ENDPOINT_H
#define UNIX_DOMAIN_SOCKET_ENDPOINT_H

#ifndef BOOST_ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include <string>

namespace isc {
namespace asiolink {

/// @brief Endpoint for @ref UnixDomainSocket.
///
/// This is a simple class encapsulating ASIO unix domain socket endpoint.
/// It is used to represent endpoints taking part in communication via
/// unix domain sockets.
class UnixDomainSocketEndpoint {
public:

    /// @brief Constructor.
    ///
    /// @param endpoint_path Path to the socket descriptor.
    explicit UnixDomainSocketEndpoint(const std::string& endpoint_path)
        : endpoint_(endpoint_path) {
    }

    /// @brief Returns underlying ASIO endpoint.
    const boost::asio::local::stream_protocol::endpoint&
    getASIOEndpoint() const {
        return (endpoint_);
    }

private:

    /// @brief Underlying ASIO endpoint.
    boost::asio::local::stream_protocol::endpoint endpoint_;

};

} // end of namespace isc::asiolink
} // end of namespace isc

#endif // UNIX_DOMAIN_SOCKET_ENDPOINT_H
