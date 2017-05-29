// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <asiolink/unix_domain_socket.h>
#include <asiolink/testutils/test_server_unix_socket.h>
#include <gtest/gtest.h>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>

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
    UnixDomainSocketTest() :
        io_service_(),
        test_socket_(new test::TestServerUnixSocket(io_service_,
                                                    unixSocketFilePath())) {
        test_socket_->startTimer(TEST_TIMEOUT);
        removeUnixSocketFile();
    }

    /// @brief Destructor.
    ///
    /// Removes unix socket descriptor after the test.
    virtual ~UnixDomainSocketTest() {
        removeUnixSocketFile();
    }

    /// @brief Returns socket file path.
    ///
    /// If the KEA_SOCKET_TEST_DIR environment variable is specified, the
    /// socket file is created in the location pointed to by this variable.
    /// Otherwise, it is created in the build directory.
    static std::string unixSocketFilePath() {
        std::ostringstream s;
        const char* env = getenv("KEA_SOCKET_TEST_DIR");
        if (env) {
            s << std::string(env);
        } else {
            s << TEST_DATA_BUILDDIR;
        }

        s << "/" << TEST_SOCKET;
        return (s.str());
    }

    /// @brief Removes unix socket descriptor.
    void removeUnixSocketFile() {
        static_cast<void>(remove(unixSocketFilePath().c_str()));
    }

    /// @brief IO service used by the tests.
    IOService io_service_;

    /// @brief Server side unix socket used in these tests.
    test::TestServerUnixSocketPtr test_socket_;
};

// This test verifies that the client can send data over the unix
// domain socket and receive a response.
TEST_F(UnixDomainSocketTest, sendReceive) {
    // Start the server.
    test_socket_->bindServerSocket();

    // Setup client side.
    UnixDomainSocket socket(io_service_);
    ASSERT_NO_THROW(socket.connect(unixSocketFilePath()));

    // Send "foo".
    const std::string outbound_data = "foo";
    size_t sent_size = 0;
    ASSERT_NO_THROW(sent_size = socket.write(outbound_data.c_str(),
                                             outbound_data.size()));
    // Make sure all data have been sent.
    ASSERT_EQ(outbound_data.size(), sent_size);

    // Run IO service to generate server's response.
    while ((test_socket_->getResponseNum() < 1) &&
           (!test_socket_->isStopped())) {
        io_service_.run_one();
    }

    // Receive response from the socket.
    std::array<char, 1024> read_buf;
    size_t bytes_read = 0;
    ASSERT_NO_THROW(bytes_read = socket.receive(&read_buf[0], read_buf.size()));
    std::string response(&read_buf[0], bytes_read);

    // The server should prepend "received" to the data we had sent.
    EXPECT_EQ("received foo", response);
}

// This test verifies that the client can send the data over the unix
// domain socket and receive a response asynchronously.
TEST_F(UnixDomainSocketTest, asyncSendReceive) {
    // Start the server.
    test_socket_->bindServerSocket();

    // Setup client side.
    UnixDomainSocket socket(io_service_);

    // We're going to asynchronously connect to the server. The boolean value
    // below will be modified by the connect handler function (lambda) invoked
    // when the connection is established or if an error occurs.
    bool connect_handler_invoked = false;
    ASSERT_NO_THROW(socket.asyncConnect(unixSocketFilePath(),
        [this, &connect_handler_invoked](const boost::system::error_code& ec) {
            // Indicate that the handler has been called so as the loop below gets
            // interrupted.
            connect_handler_invoked = true;
            // Operation aborted indicates that IO service has been stopped. This
            // shouldn't happen here.
            if (ec && (ec.value() != boost::asio::error::operation_aborted)) {
                ADD_FAILURE() << "error occurred while asynchronously connecting"
                    " via unix domain socket: " << ec.message();
            }
        }
    ));
    // Run IO service until connect handler is invoked.
    while (!connect_handler_invoked && (!test_socket_->isStopped())) {
        io_service_.run_one();
    }

    // We are going to asynchronously send the 'foo' over the unix socket.
    const std::string outbound_data = "foo";
    size_t sent_size = 0;
    ASSERT_NO_THROW(socket.asyncSend(outbound_data.c_str(), outbound_data.size(),
        [this, &sent_size](const boost::system::error_code& ec, size_t length) {
        // If we have been successful sending the data, record the number of
        // bytes we have sent.
        if (!ec) {
            sent_size = length;

        } else if (ec.value() != boost::asio::error::operation_aborted) {
            ADD_FAILURE() << "error occurred while asynchronously sending the"
            " data over unix domain socket: " << ec.message();
        }
    }
    ));

    // Run IO service to generate server's response.
    while ((test_socket_->getResponseNum() < 1) &&
           (!test_socket_->isStopped())) {
        io_service_.run_one();
    }

    // There is no guarantee that all data have been sent so we only check that
    // some data have been sent.
    ASSERT_GT(sent_size, 0);

    // Receive response from the socket.
    std::array<char, 1024> read_buf;
    size_t bytes_read = 0;
    bool receive_handler_invoked = false;
    ASSERT_NO_THROW(socket.asyncReceive(&read_buf[0], read_buf.size(),
        [this, &receive_handler_invoked, &bytes_read]
            (const boost::system::error_code& ec, size_t length) mutable {
        // Indicate that the handler has been called to interrupt the
        // loop below.
        receive_handler_invoked = true;

        // If we have been successful receiving the data, record the number of
        // bytes received.
        if (!ec) {
            bytes_read = length;

        } else if (ec.value() != boost::asio::error::operation_aborted) {
            ADD_FAILURE() << "error occurred while asynchronously receiving"
                " data via unix domain socket: " << ec.message();
        }

    }));
    // Run IO service until we get some response from the server.
    while (!receive_handler_invoked && !test_socket_->isStopped()) {
        io_service_.run_one();
    }

    // Make sure we have received something.
    ASSERT_GT(bytes_read, 0);

    std::string response(&read_buf[0], bytes_read);

    // What we have received should be a substring of the sent data prepended
    // with 'received'. For such short chunks of data it is usually 'received foo'
    // that we receive but there is no guarantee.
    EXPECT_EQ(0, std::string("received foo").find(response));
}

// This test verifies that UnixDomainSocketError exception is thrown
// on attempt to connect, write or receive when the server socket
// is not available.
TEST_F(UnixDomainSocketTest, clientErrors) {
    UnixDomainSocket socket(io_service_);
    ASSERT_THROW(socket.connect(unixSocketFilePath()), UnixDomainSocketError);
    const std::string outbound_data = "foo";
    ASSERT_THROW(socket.write(outbound_data.c_str(), outbound_data.size()),
                 UnixDomainSocketError);
    std::array<char, 1024> read_buf;
    ASSERT_THROW(socket.receive(&read_buf[0], read_buf.size()),
                 UnixDomainSocketError);
}

// This test verifies that an error is returned on attempt to asynchronously
// connect, write or receive when the server socket is not available.
TEST_F(UnixDomainSocketTest, asyncClientErrors) {
    UnixDomainSocket socket(io_service_);

    // Connect
    bool connect_handler_invoked = false;
    socket.asyncConnect(unixSocketFilePath(),
        [this, &connect_handler_invoked](const boost::system::error_code& ec) {
        connect_handler_invoked = true;
        EXPECT_TRUE(ec);
    });
    while (!connect_handler_invoked && !test_socket_->isStopped()) {
        io_service_.run_one();
    }

    // Send
    const std::string outbound_data = "foo";
    bool send_handler_invoked = false;
    socket.asyncSend(outbound_data.c_str(), outbound_data.size(),
        [this, &send_handler_invoked]
        (const boost::system::error_code& ec, size_t length) {
        send_handler_invoked = true;
        EXPECT_TRUE(ec);
    });
    while (!send_handler_invoked && !test_socket_->isStopped()) {
        io_service_.run_one();
    }

    // Receive
    bool receive_handler_invoked = false;
    std::array<char, 1024> read_buf;
    socket.asyncReceive(&read_buf[0], read_buf.size(),
        [this, &receive_handler_invoked]
        (const boost::system::error_code& ec, size_t length) {
        receive_handler_invoked = true;
        EXPECT_TRUE(ec);
    });
    while (!receive_handler_invoked && !test_socket_->isStopped()) {
        io_service_.run_one();
    }
}

// Check that native socket descriptor is returned correctly when
// the socket is connected.
TEST_F(UnixDomainSocketTest, getNative) {
    // Start the server.
    test_socket_->bindServerSocket();

    // Setup client side.
    UnixDomainSocket socket(io_service_);
    ASSERT_NO_THROW(socket.connect(unixSocketFilePath()));
    ASSERT_GE(socket.getNative(), 0);
}

// Check that protocol returned is 0.
TEST_F(UnixDomainSocketTest, getProtocol) {
    UnixDomainSocket socket(io_service_);
    EXPECT_EQ(0, socket.getProtocol());
}

}
