// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/tls_acceptor.h>
#include <asiolink/testutils/test_tls.h>
#include <tcp/tcp_client.h>
#include <tcp/tcp_listener.h>
#include <tcp/tcp_stream_msg.h>
#include <cc/data.h>
#include <util/multi_threading_mgr.h>

#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>

#include <functional>
#include <list>
#include <sstream>
#include <string>

#ifdef WITH_BOTAN
// All tests work with last Botan versions so commenting this.
// #define DISABLE_SOME_TESTS
#endif
#ifdef WITH_OPENSSL
#if !defined(LIBRESSL_VERSION_NUMBER) && (OPENSSL_VERSION_NUMBER < 0x10100000L)
#define DISABLE_SOME_TESTS
#endif
#endif

#include <tcp/tests/common_client_test.h>
#include <tcp/tests/common_client_unittests.h>

using namespace isc::asiolink::test;
using namespace isc::tcp::test;

namespace {

/// @brief Test fixture class for testing TCPS client.
class TlsClientTest : public BaseTcpClientTest {
public:

    /// @brief Constructor.
    TlsClientTest() {
        configServer(server_context_);
        configClient(client_context_);
        configClient(client_context2_);
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
    virtual ~TlsClientTest() = default;
};

/// @brief Test a single request.
TEST_F(TlsClientTest, singleRequest) {
    ASSERT_NO_FATAL_FAILURE(testSingleRequest());
}

/// @brief Test a single request.
TEST_F(TlsClientTest, singleRequestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testSingleRequest());
}

/// @brief Test a large request.
TEST_F(TlsClientTest, largeRequest) {
    ASSERT_NO_FATAL_FAILURE(testLargeRequest());
}

/// @brief Test a large request.
TEST_F(TlsClientTest, largeRequestMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testLargeRequest());
}

/// @brief Test a large response.
TEST_F(TlsClientTest, largeResponse) {
    ASSERT_NO_FATAL_FAILURE(testLargeResponse());
}

/// @brief Test a large response.
TEST_F(TlsClientTest, largeResponseMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testLargeResponse());
}

#ifndef DISABLE_SOME_TESTS
// Test that two consecutive requests can be sent over the same (persistent)
// connection.
TEST_F(TlsClientTest, consecutiveRequests) {

    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(true));
}

// Test that two consecutive requests can be sent over the same (persistent)
// connection.
TEST_F(TlsClientTest, consecutiveRequestsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);

    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(true));
}
#endif

// Test that two consecutive requests can be sent over non-persistent connection.
TEST_F(TlsClientTest, closeBetweenRequests) {
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(false));
}

// Test that two consecutive requests can be sent over non-persistent connection.
TEST_F(TlsClientTest, closeBetweenRequestsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(false));
}

// Test that the client can communicate with two different destinations
// simultaneously.
TEST_F(TlsClientTest, multipleDestinations) {
    ASSERT_NO_FATAL_FAILURE(testMultipleDestinations());
}

// Test that the client can communicate with two different destinations
// simultaneously.
TEST_F(TlsClientTest, multipleDestinationsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testMultipleDestinations());
}

// Test that the client can use two different TLS contexts to the same
// destination address and port simultaneously.
TEST_F(TlsClientTest, multipleTlsContexts) {
    ASSERT_NO_FATAL_FAILURE(testMultipleTlsContexts());
}

// Test that the client can use two different TLS contexts to the same
// destination address and port simultaneously.
TEST_F(TlsClientTest, multipleTlsContextsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testMultipleTlsContexts());
}

// Test that idle connection can be resumed for second request.
TEST_F(TlsClientTest, idleConnection) {
    ASSERT_NO_FATAL_FAILURE(testIdleConnection());
}

// Test that idle connection can be resumed for second request.
TEST_F(TlsClientTest, idleConnectionMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testIdleConnection());
}

// This test verifies that the client returns IO error code when the
// server is unreachable.
TEST_F(TlsClientTest, unreachable) {
    ASSERT_NO_FATAL_FAILURE(testUnreachable());
}

// This test verifies that the client returns IO error code when the
// server is unreachable.
TEST_F(TlsClientTest, unreachableMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testUnreachable());
}

// Test that an error is returned by the client if the server response is
// malformed.
TEST_F(TlsClientTest, malformedResponse) {
    ASSERT_NO_FATAL_FAILURE(testMalformedResponse());
}

// Test that an error is returned by the client if the server response is
// malformed.
TEST_F(TlsClientTest, malformedResponseMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testMalformedResponse());
}

// Test that client times out when it doesn't receive the entire response
// from the server within a desired time.
TEST_F(TlsClientTest, clientRequestTimeout) {
    ASSERT_NO_FATAL_FAILURE(testClientRequestTimeout());
}

// Test that client times out when it doesn't receive the entire response
// from the server within a desired time.
TEST_F(TlsClientTest, clientRequestTimeoutMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testClientRequestTimeout());
}

// This test verifies the behavior of the TCP client when the premature
// (and unexpected) timeout occurs. The premature timeout may be caused
// by the system clock move.
TEST_F(TlsClientTest, DISABLED_clientRequestLateStartNoQueue) {
    testClientRequestLateStart(false);
}

// This test verifies the behavior of the TCP client when the premature
// (and unexpected) timeout occurs. The premature timeout may be caused
// by the system clock move.
TEST_F(TlsClientTest, DISABLED_clientRequestLateStartNoQueueMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testClientRequestLateStart(false);
}

#ifndef DISABLE_SOME_TESTS
// This test verifies the behavior of the TCP client when the premature
// timeout occurs and there are requests queued after the request which
// times out.
TEST_F(TlsClientTest, clientRequestLateStartQueue) {

    testClientRequestLateStart(true);
}

// This test verifies the behavior of the TCP client when the premature
// timeout occurs and there are requests queued after the request which
// times out.
TEST_F(TlsClientTest, clientRequestLateStartQueueMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testClientRequestLateStart(true);
}
#endif

// Test that client times out when connection takes too long.
TEST_F(TlsClientTest, clientConnectTimeout) {
    ASSERT_NO_FATAL_FAILURE(testClientConnectTimeout());
}

// Test that client times out when connection takes too long.
TEST_F(TlsClientTest, clientConnectTimeoutMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testClientConnectTimeout());
}

#ifndef DISABLE_SOME_TESTS
/// Tests that connect and close callbacks work correctly.
TEST_F(TlsClientTest, connectCloseCallbacks) {
    ASSERT_NO_FATAL_FAILURE(testConnectCloseCallbacks(true));
}

/// Tests that connect and close callbacks work correctly.
TEST_F(TlsClientTest, connectCloseCallbacksMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testConnectCloseCallbacks(true));
}
#endif

/// Tests that TcpClient::closeIfOutOfBand works correctly.
TEST_F(TlsClientTest, closeIfOutOfBand) {
    ASSERT_NO_FATAL_FAILURE(testCloseIfOutOfBand(true));
}

/// Tests that TcpClient::closeIfOutOfBand works correctly.
TEST_F(TlsClientTest, closeIfOutOfBandMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testCloseIfOutOfBand(true));
}

}
