// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <testutils/sandbox.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <asiolink/testutils/test_server_unix_socket.h>
#include <cc/json_feed.h>
#include <config/client_connection.h>
#include <gtest/gtest.h>
#include <cstdlib>
#include <sstream>
#include <string>

using namespace isc::asiolink;
using namespace isc::config;

namespace {

/// @brief Test timeout in ms.
const long TEST_TIMEOUT = 10000;

/// Test fixture class for @ref ClientConnection.
class ClientConnectionTest : public ::testing::Test {
public:
    isc::test::Sandbox sandbox;

    /// @brief Constructor.
    ///
    /// Removes unix socket descriptor before the test.
    ClientConnectionTest() :
        io_service_(),
        test_socket_(new test::TestServerUnixSocket(io_service_,
                                                    unixSocketFilePath())) {
        removeUnixSocketFile();
    }

    /// @brief Destructor.
    ///
    /// Removes unix socket descriptor after the test.
    virtual ~ClientConnectionTest() {
        removeUnixSocketFile();
    }

    /// @brief Returns socket file path.
    ///
    /// If the KEA_SOCKET_TEST_DIR environment variable is specified, the
    /// socket file is created in the location pointed to by this variable.
    /// Otherwise, it is created in the build directory.
    ///
    /// The KEA_SOCKET_TEST_DIR is typically used to overcome the problem of
    /// a system limit on the unix socket file path (usually 102 or 103 characters).
    /// When Kea build is located in the nested directories with absolute path
    /// exceeding this limit, the test system should be configured to set
    /// the KEA_SOCKET_TEST_DIR environmental variable to point to an alternative
    /// location, e.g. /tmp, with an absolute path length being within the
    /// allowed range.
    std::string unixSocketFilePath() {
        std::string socket_path;
        const char* env = getenv("KEA_SOCKET_TEST_DIR");
        if (env) {
            socket_path = std::string(env) + "/test-socket";
        } else {
            socket_path = sandbox.join("test-socket");
        }
        return (socket_path);
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

// Tests successful transaction: connect, send command and receive a
// response.
TEST_F(ClientConnectionTest, success) {
    // Start timer protecting against test timeouts.
    test_socket_->startTimer(TEST_TIMEOUT);

    // Start the server.
    test_socket_->bindServerSocket();
    test_socket_->generateCustomResponse(2048);

    // Create some valid command.
    std::string command = "{ \"command\": \"list-commands\" }";

    ClientConnection conn(io_service_);

    // This boolean value will indicate when the callback function is invoked
    // at the end of the transaction (whether it is successful or unsuccessful).
    bool handler_invoked = false;
    conn.start(ClientConnection::SocketPath(unixSocketFilePath()),
               ClientConnection::ControlCommand(command),
        [&handler_invoked](const boost::system::error_code& ec,
                           const ConstJSONFeedPtr& feed) {
        // Indicate that the handler has been called to break from the
        // while loop below.
        handler_invoked = true;
        // The ec should contain no error.
        ASSERT_FALSE(ec);
        // The JSONFeed should be present and it should contain a valid
        // response.
        ASSERT_TRUE(feed);
        EXPECT_TRUE(feed->feedOk()) << feed->getErrorMessage();
    });
    // Run the connection.
    while (!handler_invoked && !test_socket_->isStopped()) {
        io_service_.run_one();
    }
}

// This test checks that a timeout is signalled when the communication
// takes too long.
TEST_F(ClientConnectionTest, timeout) {
    // The server will return only partial JSON response (lacking closing
    // brace). The client will wait for closing brace and eventually the
    // connection should time out.
    test_socket_.reset(new test::TestServerUnixSocket(io_service_,
                                                      unixSocketFilePath(),
                                                      "{ \"command\": \"foo\""));
    test_socket_->startTimer(TEST_TIMEOUT);

    // Start the server.
    test_socket_->bindServerSocket();

    // Command to be sent to the server.
    std::string command = "{ \"command\": \"list-commands\" }";

    ClientConnection conn(io_service_);

    // This boolean value will be set to true when the callback is invoked.
    bool handler_invoked = false;
    conn.start(ClientConnection::SocketPath(unixSocketFilePath()),
              ClientConnection::ControlCommand(command),
    [&handler_invoked](const boost::system::error_code& ec,
                       const ConstJSONFeedPtr& /*feed*/) {
        // Indicate that the callback has been invoked to break the loop
        // below.
        handler_invoked = true;
        ASSERT_TRUE(ec);
        EXPECT_TRUE(ec.value() == boost::asio::error::timed_out);
    }, ClientConnection::Timeout(1000));

    while (!handler_invoked && !test_socket_->isStopped()) {
        io_service_.run_one();
    }
}

// This test checks that an error is returned when the client is unable
// to connect to the server.
TEST_F(ClientConnectionTest, connectionError) {
    // Create the new connection but do not bind the server socket.
    // The connection should be refused and an error returned.
    ClientConnection conn(io_service_);

    std::string command = "{ \"command\": \"list-commands\" }";

    bool handler_invoked = false;
    conn.start(ClientConnection::SocketPath(unixSocketFilePath()),
               ClientConnection::ControlCommand(command),
    [&handler_invoked](const boost::system::error_code& ec,
                       const ConstJSONFeedPtr& /*feed*/) {
        handler_invoked = true;
        ASSERT_TRUE(ec);
    });

    while (!handler_invoked && !test_socket_->isStopped()) {
        io_service_.run_one();
    }
}

} // end of anonymous namespace
