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
    UnixDomainSocketTest() : io_service_(),
                             test_socket_(io_service_, unixSocketFilePath(),
                                          TEST_TIMEOUT) {
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
    test::TestServerUnixSocket test_socket_;
};

// This test verifies that the client can send data over the unix
// domain socket and receive a response.
TEST_F(UnixDomainSocketTest, sendReceive) {
    // Start the server.
    test_socket_.bindServerSocket();

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
    while (test_socket_.getResponseNum() < 1) {
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

// Check that native socket descriptor is returned correctly when
// the socket is connected.
TEST_F(UnixDomainSocketTest, getNative) {
    // Start the server.
    test_socket_.bindServerSocket();

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
