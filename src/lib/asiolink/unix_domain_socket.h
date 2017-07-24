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
#include <functional>
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

    /// @brief Callback type used in call to @ref UnixDomainSocket::asyncConnect.
    typedef std::function<void(const boost::system::error_code&)> ConnectHandler;

    /// @brief Callback type used in calls to @ref UnixDomainSocket::asyncSend
    /// and @ref UnixDomainSocket::asyncReceive.
    typedef std::function<void(const boost::system::error_code&, size_t)> Handler;

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

    /// @brief Asynchronously connects the socket to the specified endpoint.
    ///
    /// Always returns immediately.
    ///
    /// @param path Path to the unix socket to which we should connect.
    /// @param handler Callback to be invoked when connection is established or
    /// a connection error is signalled.
    void asyncConnect(const std::string& path, const ConnectHandler& handler);

    /// @brief Writes specified amount of data to a socket.
    ///
    /// @param data Pointer to data to be written.
    /// @param length Number of bytes to be written.
    ///
    /// @return Number of bytes written.
    /// @throw UnixDomainSocketError if error occurs.
    size_t write(const void* data, size_t length);

    /// @brief Asynchronously sends data over the socket.
    ///
    /// Always returns immediately.
    ///
    /// @param data Pointer to data to be sent.
    /// @param length Number of bytes to be sent.
    /// @param handler Callback to be invoked when data have been sent or
    /// sending error is signalled.
    void asyncSend(const void* data, const size_t length, const Handler& handler);

    /// @brief Receives data from a socket.
    ///
    /// @param [out] data Pointer to a location into which the read data should
    /// be stored.
    /// @param length Length of the buffer.
    ///
    /// @return Number of bytes read.
    /// @throw UnixDomainSocketError if error occurs.
    size_t receive(void* data, size_t length);

    /// @brief Asynchronously receives data over the socket.
    ///
    /// Always returns immediately.
    /// @param [out] data Pointer to a location into which the read data should
    /// be stored.
    /// @param length Length of the buffer.
    /// @param handler Callback to be invoked when data have been received or an
    /// error is signalled.
    void asyncReceive(void* data, const size_t length, const Handler& handler);

    /// @brief Disables read and write operations on the socket.
    ///
    /// @throw UnixDomainSocketError if an error occurs during shutdown.
    void shutdown();

    /// @brief Cancels scheduled asynchronous operations on the socket.
    ///
    /// @throw UnixDomainSocketError if an error occurs during cancel operation.
    void cancel();

    /// @brief Closes the socket.
    ///
    /// @throw UnixDomainSocketError if an error occurs during closure.
    void close();

    /// @brief Returns reference to the underlying ASIO socket.
    ///
    /// @return Reference to underlying ASIO socket.
    virtual boost::asio::local::stream_protocol::socket& getASIOSocket() const;

private:

    /// @brief Pointer to the implementation of this class.
    boost::shared_ptr<UnixDomainSocketImpl> impl_;

};

} // end of namespace isc::asiolink
} // end of namespace isc

#endif // UNIX_DOMAIN_SOCKET_H
