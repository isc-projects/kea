// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_SERVER_UNIX_SOCKET_H
#define TEST_SERVER_UNIX_SOCKET_H

#include <config.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <list>
#include <string>

namespace isc {
namespace asiolink {
namespace test {

class ConnectionPool;

/// @brief Provides unix domain socket functionality for unit tests.
///
/// This class represents a server side socket. It can be used to
/// test client's transmission over the unix domain socket. By default,
/// the server side socket echoes the client's message so the client's
/// message (prefixed with the word "received").
///
/// It is also possible to specify a custom response from the server
/// instead of eachoing back the request.
///
/// It is possible to make multiple connections to the server side
/// socket simultaneously.
///
/// The test should perform IOService::run_one until it finds that
/// the number of responses sent by the server is greater than
/// expected. The number of responses sent so far can be retrieved
/// using @ref TestServerUnixSocket::getResponseNum.
class TestServerUnixSocket {
public:

    /// @brief Constructor.
    ///
    /// @param io_service IO service.
    /// @param socket_file_path Socket file path.
    /// @param test_timeout Test timeout in milliseconds.
    /// @param custom_response Custom response to be sent to the client.
    TestServerUnixSocket(IOService& io_service,
                         const std::string& socket_file_path,
                         const long test_timeout,
                         const std::string& custom_response = "");

    /// @brief Destructor.
    ///
    /// Closes active connections.
    ~TestServerUnixSocket();

    /// @brief Creates and binds server socket.
    void bindServerSocket();

    /// @brief Server acceptor handler.
    ///
    /// @param ec Error code.
    void acceptHandler(const boost::system::error_code& ec);

    /// @brief Callback function invoke upon test timeout.
    ///
    /// It stops the IO service and reports test timeout.
    void timeoutHandler();

    /// @brief Return number of responses sent so far to the clients.
    size_t getResponseNum() const;

private:

    /// @brief Asynchronously accept new connections.
    void accept();

    /// @brief IO service used by the tests.
    IOService& io_service_;

    /// @brief Server endpoint.
    boost::asio::local::stream_protocol::endpoint server_endpoint_;
    /// @brief Server acceptor.
    boost::asio::local::stream_protocol::acceptor server_acceptor_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Holds custom response to be sent to the client.
    std::string custom_response_;

    /// @brief Pool of connections.
    boost::shared_ptr<ConnectionPool> connection_pool_;
};

/// @brief Pointer to the @ref TestServerUnixSocket.
typedef boost::shared_ptr<TestServerUnixSocket> TestServerUnixSocketPtr;

} // end of namespace isc::asiolink::test
} // end of namespace isc::asiolink
} // end of namespace isc

#endif // TEST_SERVER_UNIX_SOCKET_H
