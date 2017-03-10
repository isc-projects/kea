// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <asiolink/unix_domain_socket.h>
#include <boost/bind.hpp>
#include <gtest/gtest.h>
#include <array>
#include <cstdio>
#include <sstream>
#include <string>

using namespace boost::asio;
using namespace boost::asio::local;
using namespace isc::asiolink;

namespace  {

/// @brief Test unix socket file name.
const std::string TEST_SOCKET = "test-socket";

/// @brief Test timeout in ms.
const long TEST_TIMEOUT = 10000;

/// @brief Test fixture class for @ref UnixDomainSocket class.
class UnixDomainSocketTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Removes unix socket descriptor before the test.
    UnixDomainSocketTest() : io_service_(),
                             server_endpoint_(unixSocketFilePath()),
                             server_acceptor_(io_service_.get_io_service()),
                             server_socket_(io_service_.get_io_service()),
                             test_timer_(io_service_) {
        removeUnixSocketFile();
        test_timer_.setup(boost::bind(&UnixDomainSocketTest::timeoutHandler, this),
                                      TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
    }

    /// @brief Destructor.
    ///
    /// Removes unix socket descriptor after the test.
    virtual ~UnixDomainSocketTest() {
        removeUnixSocketFile();
    }

    /// @brief Returns socket file path.
    static std::string unixSocketFilePath() {
        std::ostringstream s;
        s << TEST_DATA_BUILDDIR << "/" << TEST_SOCKET;
        return (s.str());
    }

    /// @brief Removes unix socket descriptor.
    void removeUnixSocketFile() {
        static_cast<void>(remove(unixSocketFilePath().c_str()));
    }

    /// @brief Creates and binds server socket.
    void bindServerSocket() {
        server_acceptor_.open();
        server_acceptor_.bind(server_endpoint_);
        server_acceptor_.listen();
        server_acceptor_.async_accept(server_socket_,
                                      boost::bind(&UnixDomainSocketTest::
                                                  acceptHandler, this, _1));
    }

    /// @brief Server acceptor handler.
    ///
    /// @param ec Error code.
    void acceptHandler(const boost::system::error_code& ec) {
        if (ec) {
            ADD_FAILURE() << ec.message();
        }
        server_socket_.async_read_some(boost::asio::buffer(&raw_buf_[0],
                                                           raw_buf_.size()),
                                       boost::bind(&UnixDomainSocketTest::
                                                   readHandler, this, _1, _2));
    }

    /// @brief Server read handler.
    ///
    /// @param ec Error code.
    /// @param bytes_transferred Number of bytes read.
    void readHandler(const boost::system::error_code& ec,
                     size_t bytes_transferred) {
        std::string received(&raw_buf_[0], bytes_transferred);
        std::string response("received " + received);
        boost::asio::write(server_socket_, boost::asio::buffer(response.c_str(),
                                                               response.size()));
        io_service_.stop();
    }

    /// @brief Callback function invoke upon test timeout.
    ///
    /// It stops the IO service and reports test timeout.
    void timeoutHandler() {
        ADD_FAILURE() << "Timeout occurred while running the test!";
        io_service_.stop();
    }

    /// @brief IO service used by the tests.
    IOService io_service_;

    /// @brief Server endpoint.
    local::stream_protocol::endpoint server_endpoint_;

    /// @brief Server acceptor.
    local::stream_protocol::acceptor server_acceptor_;

    /// @brief Server side unix domain socket.
    stream_protocol::socket server_socket_;

    /// @brief Receive buffer.
    std::array<char, 1024> raw_buf_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;
};

// This test verifies that the client can send data over the unix
// domain socket and receive a response.
TEST_F(UnixDomainSocketTest, sendReceive) {
    // Start the server.
    bindServerSocket();

    // Setup client side.
    UnixDomainSocket socket(io_service_);
    ASSERT_NO_THROW(socket.connect(TEST_SOCKET));

    // Send "foo".
    const std::string outbound_data = "foo";
    size_t sent_size = 0;
    ASSERT_NO_THROW(sent_size = socket.write(outbound_data.c_str(),
                                             outbound_data.size()));
    // Make sure all data have been sent.
    ASSERT_EQ(outbound_data.size(), sent_size);

    // Run IO service to generate server's response.
    io_service_.run();

    // Receive response from the socket.
    std::array<char, 1024> read_buf;
    size_t bytes_read = 0;
    ASSERT_NO_THROW(bytes_read = socket.receive(&read_buf[0], read_buf.size()));
    std::string response(&read_buf[0], bytes_read);

    // The server should prepend "received" to the data we had sent.
    EXPECT_EQ("received foo", response);
}

// This test verifies that UnixDomainSocketError exception is thrown
// on attempt to connect, write or receive when the server socket
// is not available.
TEST_F(UnixDomainSocketTest, clientErrors) {
    UnixDomainSocket socket(io_service_);
    ASSERT_THROW(socket.connect(TEST_SOCKET), UnixDomainSocketError);
    const std::string outbound_data = "foo";
    ASSERT_THROW(socket.write(outbound_data.c_str(), outbound_data.size()),
                 UnixDomainSocketError);
    std::array<char, 1024> read_buf;
    ASSERT_THROW(socket.receive(&read_buf[0], read_buf.size()),
                 UnixDomainSocketError);
}

// Check that native socket descriptor is returned correctly when
// the socket is connected.
TEST_F(UnixDomainSocketTest, getNative) {
    // Start the server.
    bindServerSocket();

    // Setup client side.
    UnixDomainSocket socket(io_service_);
    ASSERT_NO_THROW(socket.connect(TEST_SOCKET));
    ASSERT_GE(socket.getNative(), 0);
}

// Check that protocol returned is 0.
TEST_F(UnixDomainSocketTest, getProtocol) {
    UnixDomainSocket socket(io_service_);
    EXPECT_EQ(0, socket.getProtocol());
}

}
