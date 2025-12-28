// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/tls_acceptor.h>
#include <cc/data.h>
#include <tcp/tcp_client.h>
#include <tcp/tcp_listener.h>
#include <tcp/tcp_stream_msg.h>
#include <util/multi_threading_mgr.h>

#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>

#include <functional>
#include <list>
#include <sstream>
#include <string>

using namespace isc::asiolink;
using namespace isc::util;
namespace ph = std::placeholders;
#include <tcp/tests/common_client_test.h>

using namespace boost::asio::ip;
using namespace isc::data;
using namespace isc::tcp;
using namespace isc::tcp::test;

namespace {

/// @brief Test fixture class for testing TCP client.
class TcpClientTest : public BaseTcpClientTest {
public:

    /// @brief Constructor.
    TcpClientTest() {
        listener_.reset(new TcpTestListener(io_service_,
                                            IOAddress(SERVER_ADDRESS),
                                            SERVER_PORT,
                                            server_context_,
                                            TcpListener::IdleTimeout(IDLE_TIMEOUT)));
        listener2_.reset(new TcpTestListener(io_service_,
                                             IOAddress(IPV6_SERVER_ADDRESS),
                                             SERVER_PORT + 1,
                                             server_context_,
                                             TcpListener::IdleTimeout(IDLE_TIMEOUT)));
        listener3_.reset(new TcpTestListener(io_service_,
                                             IOAddress(SERVER_ADDRESS),
                                             SERVER_PORT + 2,
                                             server_context_,
                                             TcpListener::IdleTimeout(SHORT_IDLE_TIMEOUT)));
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Destructor.
    virtual ~TcpClientTest() = default;
};

// Test that two consecutive requests can be sent over the same (persistent)
// connection.
TEST_F(TcpClientTest, consecutiveRequests) {
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(true));
}

// Test that two consecutive requests can be sent over the same (persistent)
// connection.
TEST_F(TcpClientTest, consecutiveRequestsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(true));
}

// Test that two consecutive requests can be sent over non-persistent connection.

TEST_F(TcpClientTest, closeBetweenRequests) {
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(false));
}

// Test that two consecutive requests can be sent over non-persistent connection.
TEST_F(TcpClientTest, closeBetweenRequestsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(false));
}

// Test that the client can communicate with two different destinations
// simultaneously.
TEST_F(TcpClientTest, multipleDestinations) {
    ASSERT_NO_FATAL_FAILURE(testMultipleDestinations());
}

// Test that the client can communicate with two different destinations
// simultaneously.
TEST_F(TcpClientTest, multipleDestinationsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testMultipleDestinations());
}

// Test that the client can use two different TLS contexts to the same
// destination address and port simultaneously.
TEST_F(TcpClientTest, multipleTlsContexts) {
    ASSERT_NO_FATAL_FAILURE(testMultipleTlsContexts());
}

// Test that the client can use two different TLS contexts to the same
// destination address and port simultaneously.
TEST_F(TcpClientTest, multipleTlsContextsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testMultipleTlsContexts());
}

// Test that idle connection can be resumed for second request.
TEST_F(TcpClientTest, idleConnection) {
    ASSERT_NO_FATAL_FAILURE(testIdleConnection());
}

// Test that idle connection can be resumed for second request.
TEST_F(TcpClientTest, idleConnectionMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testIdleConnection());
}

// This test verifies that the client returns IO error code when the
// server is unreachable.
TEST_F(TcpClientTest, unreachable) {
    ASSERT_NO_FATAL_FAILURE(testUnreachable());
}

// This test verifies that the client returns IO error code when the
// server is unreachable.
TEST_F(TcpClientTest, unreachableMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testUnreachable());
}

// Test that an error is returned by the client if the server response is
// malformed.
TEST_F(TcpClientTest, malformedResponse) {
    ASSERT_NO_FATAL_FAILURE(testMalformedResponse());
}

// Test that an error is returned by the client if the server response is
// malformed.
TEST_F(TcpClientTest, malformedResponseMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testMalformedResponse());
}

// Test that client times out when it doesn't receive the entire response
// from the server within a desired time.
TEST_F(TcpClientTest, clientRequestTimeout) {
    ASSERT_NO_FATAL_FAILURE(testClientRequestTimeout());
}

// Test that client times out when it doesn't receive the entire response
// from the server within a desired time.
TEST_F(TcpClientTest, clientRequestTimeoutMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testClientRequestTimeout());
}

// This test verifies the behavior of the TCP client when the premature
// (and unexpected) timeout occurs. The premature timeout may be caused
// by the system clock move.
TEST_F(TcpClientTest, clientRequestLateStartNoQueue) {
    testClientRequestLateStart(false);
}

// This test verifies the behavior of the TCP client when the premature
// (and unexpected) timeout occurs. The premature timeout may be caused
// by the system clock move.
TEST_F(TcpClientTest, clientRequestLateStartNoQueueMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testClientRequestLateStart(false);
}

// This test verifies the behavior of the TCP client when the premature
// timeout occurs and there are requests queued after the request which
// times out.
TEST_F(TcpClientTest, clientRequestLateStartQueue) {
    testClientRequestLateStart(true);
}

// This test verifies the behavior of the TCP client when the premature
// timeout occurs and there are requests queued after the request which
// times out.
TEST_F(TcpClientTest, clientRequestLateStartQueueMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testClientRequestLateStart(true);
}

// Test that client times out when connection takes too long.
TEST_F(TcpClientTest, clientConnectTimeout) {
    ASSERT_NO_FATAL_FAILURE(testClientConnectTimeout());
}

// Test that client times out when connection takes too long.
TEST_F(TcpClientTest, clientConnectTimeoutMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testClientConnectTimeout());
}

/// Tests that connect and close callbacks work correctly.
TEST_F(TcpClientTest, connectCloseCallbacks) {
    ASSERT_NO_FATAL_FAILURE(testConnectCloseCallbacks(true));
}

/// Tests that connect and close callbacks work correctly.
TEST_F(TcpClientTest, connectCloseCallbacksMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testConnectCloseCallbacks(true));
}

/// Tests that TcpClient::closeIfOutOfBand works correctly.
TEST_F(TcpClientTest, closeIfOutOfBand) {
    ASSERT_NO_FATAL_FAILURE(testCloseIfOutOfBand(true));
}

/// Tests that TcpClient::closeIfOutOfBand works correctly.
TEST_F(TcpClientTest, closeIfOutOfBandMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testCloseIfOutOfBand(true));
}

}
