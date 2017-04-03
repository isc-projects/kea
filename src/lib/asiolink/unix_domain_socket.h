// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UNIX_DOMAIN_SOCKET_H
#define UNIX_DOMAIN_SOCKET_H

#include <asiolink/io_service.h>
#include <asiolink/io_socket.h>
#include <boost/shared_ptr.hpp>
#include <string>

namespace isc {
namespace asiolink {

/// @brief Exception thrown upon socket error.
class UnixDomainSocketError : public Exception {
public:
    UnixDomainSocketError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

class UnixDomainSocketImpl;

/// @brief Represents unix domain socket implemented in terms
/// of boost asio.
class UnixDomainSocket : public IOSocket {
public:

    /// @brief Constructor.
    ///
    /// @param io_service Reference to IOService to be used by this
    /// class.
    explicit UnixDomainSocket(IOService& io_service);

    /// @brief Returns native socket representation.
    virtual int getNative() const;

    /// @brief Always returns 0.
    virtual int getProtocol() const;

    /// @brief Connects the socket to the specified endpoint.
    ///
    /// @param path Path to the unix socket to which we should connect.
    ///
    /// @throw UnixDomainSocketError if error occurs.
    void connect(const std::string& path);

    /// @brief Writes specified amount of data to a socket.
    ///
    /// @param data Pointer to data to be written.
    /// @param length Number of bytes to be written.
    ///
    /// @return Number of bytes written.
    /// @throw UnixDomainSocketError if error occurs.
    size_t write(const void* data, size_t length);

    /// @brief Receives data from a socket.
    ///
    /// @param [out] data Pointer to a location into which the read data should
    /// be stored.
    /// @param length Length of the buffer.
    ///
    /// @return Number of bytes read.
    /// @throw UnixDomainSocketError if error occurs.
    size_t receive(void* data, size_t length);

    /// @brief Closes the socket.
    void close();

private:

    /// @brief Pointer to the implementation of this class.
    boost::shared_ptr<UnixDomainSocketImpl> impl_;

};

} // end of namespace isc::asiolink
} // end of namespace isc

#endif // UNIX_DOMAIN_SOCKET_H
