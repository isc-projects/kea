// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <asiolink/testutils/test_server_unix_socket.h>
#include <cc/json_feed.h>
#include <config/client_connection.h>
#include <config/testutils/socket_path.h>
#include <testutils/gtest_utils.h>

#include <cstdlib>
#include <sstream>
#include <string>

#include <gtest/gtest.h>

using namespace isc::asiolink;
using namespace isc::asiolink::test;
using namespace isc::config;
using namespace isc::config::test;

namespace {

/// @brief Test timeout in ms.
const long TEST_TIMEOUT = 10000;

/// Test fixture class for @ref ClientConnection.
class ClientConnectionTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ///
    /// Removes unix socket descriptor before the test.
    ClientConnectionTest()
        : io_service_(new IOService()), handler_invoked_(false) {
        SocketPath::removeUnixSocketFile();
        setSocketTestPath();
        socket_name_too_long_ = SocketPath::isTooLong(SocketPath::unixSocketFilePath());
        if (!socket_name_too_long_) {
            test_socket_.reset(
                new TestServerUnixSocket(io_service_, SocketPath::unixSocketFilePath()));
        }
    }

    /// @brief Destructor.
    ///
    /// Removes unix socket descriptor after the test.
    virtual ~ClientConnectionTest() {
        SocketPath::removeUnixSocketFile();
        conn_.reset();
        test_socket_.reset();
        io_service_->stopAndPoll();
        resetSocketPath();
    }

    /// @brief Sets the path in which the socket can be created.
    ///
    /// @param explicit_path path to use as the socket path.
    void setSocketTestPath(const std::string explicit_path = std::string()) {
        std::string const path(UnixCommandConfig::getSocketPath(
            true, (!explicit_path.empty() ? explicit_path : TEST_DATA_BUILDDIR)));
        UnixCommandConfig::setSocketPathPerms(isc::util::file::getPermissions(path));
    }

    /// @brief Resets the socket path to the default.
    void resetSocketPath() {
        UnixCommandConfig::getSocketPath(true);
        UnixCommandConfig::setSocketPathPerms();
    }

    /// @brief IO service used by the tests.
    IOServicePtr io_service_;

    /// @brief Flag which indicates if the callback has been called.
    bool handler_invoked_;

    /// @brief Server side unix socket used in these tests.
    TestServerUnixSocketPtr test_socket_;

    /// @brief Client connection.
    ClientConnectionPtr conn_;

    /// @brief Whether socket name is too long which is determined at test startup.
    bool socket_name_too_long_;
};

// Tests successful transaction: connect, send command and receive a
// response.
TEST_F(ClientConnectionTest, success) {
    SKIP_IF(socket_name_too_long_);

    // Start timer protecting against test timeouts.
    test_socket_->startTimer(TEST_TIMEOUT);

    // Start the server.
    test_socket_->bindServerSocket();
    test_socket_->generateCustomResponse(2048);

    // Create some valid command.
    std::string command = "{ \"command\": \"list-commands\" }";

    conn_.reset(new ClientConnection(io_service_));

    conn_->start(ClientConnection::SocketPath(SocketPath::unixSocketFilePath()),
                 ClientConnection::ControlCommand(command),
        [&](const boost::system::error_code& ec,
            const ConstJSONFeedPtr& feed) {
        if (handler_invoked_) {
            return;
        }
        // Indicate that the handler has been called to break from the
        // while loop below.
        handler_invoked_ = true;
        // The ec should contain no error.
        ASSERT_FALSE(ec);
        // The JSONFeed should be present and it should contain a valid
        // response.
        ASSERT_TRUE(feed);
        EXPECT_TRUE(feed->feedOk()) << feed->getErrorMessage();
    });
    // Run the connection.
    while (!handler_invoked_ && !test_socket_->isStopped()) {
        io_service_->runOne();
    }
}

// This test checks that a timeout is signalled when the communication
// takes too long.
TEST_F(ClientConnectionTest, timeout) {
    SKIP_IF(socket_name_too_long_);

    // The server will return only partial JSON response (lacking closing
    // brace). The client will wait for closing brace and eventually the
    // connection should time out.
    test_socket_.reset(new TestServerUnixSocket(io_service_, SocketPath::unixSocketFilePath(),
                                                "{ \"command\": \"foo\""));
    test_socket_->startTimer(TEST_TIMEOUT);

    // Start the server.
    test_socket_->bindServerSocket();

    // Command to be sent to the server.
    std::string command = "{ \"command\": \"list-commands\" }";

    conn_.reset(new ClientConnection(io_service_));

    conn_->start(ClientConnection::SocketPath(SocketPath::unixSocketFilePath()),
                 ClientConnection::ControlCommand(command),
    [&](const boost::system::error_code& ec,
        const ConstJSONFeedPtr& /*feed*/) {
        if (handler_invoked_) {
            return;
        }
        // Indicate that the callback has been invoked to break the loop
        // below.
        handler_invoked_ = true;
        ASSERT_TRUE(ec);
        EXPECT_TRUE(ec.value() == boost::asio::error::timed_out);
    }, ClientConnection::Timeout(1000));

    while (!handler_invoked_ && !test_socket_->isStopped()) {
        io_service_->runOne();
    }

    test_socket_->stopServer();
}

// This test checks that an error is returned when the client is unable
// to connect to the server.
TEST_F(ClientConnectionTest, connectionError) {
    SKIP_IF(socket_name_too_long_);

    // Create the new connection but do not bind the server socket.
    // The connection should be refused and an error returned.
    conn_.reset(new ClientConnection(io_service_));

    std::string command = "{ \"command\": \"list-commands\" }";

    conn_->start(ClientConnection::SocketPath(SocketPath::unixSocketFilePath()),
                 ClientConnection::ControlCommand(command),
    [&](const boost::system::error_code& ec,
        const ConstJSONFeedPtr& /*feed*/) {
        if (handler_invoked_) {
            return;
        }
        handler_invoked_ = true;
        ASSERT_TRUE(ec);
    });

    while (!handler_invoked_ && !test_socket_->isStopped()) {
        io_service_->runOne();
    }
}

} // end of anonymous namespace
