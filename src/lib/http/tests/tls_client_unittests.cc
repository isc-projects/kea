// Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/tls_acceptor.h>
#include <asiolink/testutils/test_tls.h>
#include <cc/data.h>
#include <http/client.h>
#include <http/http_types.h>
#include <http/listener.h>
#include <http/listener_impl.h>
#include <http/post_request_json.h>
#include <http/response_creator.h>
#include <http/response_creator_factory.h>
#include <http/response_json.h>
#include <http/tests/response_test.h>
#include <http/url.h>
#include <util/multi_threading_mgr.h>

#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>

#include <functional>
#include <list>
#include <sstream>
#include <string>

// Keep order of these headers.
#include <http/tests/http_tests.h>
#include <http/tests/tls_response_creator_test.h>

#ifdef WITH_BOTAN
#define DISABLE_SOME_TESTS
#endif
#ifdef WITH_OPENSSL
#if !defined(LIBRESSL_VERSION_NUMBER) && (OPENSSL_VERSION_NUMBER < 0x10100000L)
#define DISABLE_SOME_TESTS
#endif
#endif

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace isc::asiolink;
using namespace isc::asiolink::test;
using namespace isc::data;
using namespace isc::http;
using namespace isc::http::test;
using namespace isc::util;
namespace ph = std::placeholders;

#include <http/tests/http_client_test.h>

namespace {

/// @brief Test fixture class for testing HTTPS client.
class HttpsClientTest : public BaseHttpClientTest {
public:

    /// @brief Constructor.
    HttpsClientTest() {
        configServer(server_context_);
        configClient(client_context_);
        configClient(client_context2_);
        listener_.reset(new HttpListener(io_service_,
                                         IOAddress(SERVER_ADDRESS),
                                         SERVER_PORT,
                                         server_context_,
                                         factory_,
                                         HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                                         HttpListener::IdleTimeout(IDLE_TIMEOUT)));
        listener2_.reset(new HttpListener(io_service_,
                                          IOAddress(IPV6_SERVER_ADDRESS),
                                          SERVER_PORT + 1,
                                          server_context_,
                                          factory_,
                                          HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                                          HttpListener::IdleTimeout(IDLE_TIMEOUT)));
        listener3_.reset(new HttpListener(io_service_,
                                          IOAddress(SERVER_ADDRESS),
                                          SERVER_PORT + 2,
                                          server_context_,
                                          factory_,
                                          HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                                          HttpListener::IdleTimeout(SHORT_IDLE_TIMEOUT)));
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Destructor.
    virtual ~HttpsClientTest() = default;
};

#ifndef DISABLE_SOME_TESTS
// Test that two consecutive requests can be sent over the same (persistent)
// connection.
TEST_F(HttpsClientTest, consecutiveRequests) {

    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(HttpVersion(1, 1)));
}

// Test that two consecutive requests can be sent over the same (persistent)
// connection.
TEST_F(HttpsClientTest, consecutiveRequestsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);

    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(HttpVersion(1, 1)));
}
#endif

// Test that two consecutive requests can be sent over non-persistent connection.
// This is achieved by sending HTTP/1.0 requests, which are non-persistent by
// default. The client should close the connection right after receiving a response
// from the server.
TEST_F(HttpsClientTest, closeBetweenRequests) {
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(HttpVersion(1, 0)));
}

// Test that two consecutive requests can be sent over non-persistent connection.
// This is achieved by sending HTTP/1.0 requests, which are non-persistent by
// default. The client should close the connection right after receiving a response
// from the server.
TEST_F(HttpsClientTest, closeBetweenRequestsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(HttpVersion(1, 0)));
}

// Test that the client can communicate with two different destinations
// simultaneously.
TEST_F(HttpsClientTest, multipleDestinations) {
    ASSERT_NO_FATAL_FAILURE(testMultipleDestinations());
}

// Test that the client can communicate with two different destinations
// simultaneously.
TEST_F(HttpsClientTest, multipleDestinationsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testMultipleDestinations());
}

// Test that the client can use two different TLS contexts to the same
// destination address and port simultaneously.
TEST_F(HttpsClientTest, multipleTlsContexts) {
    ASSERT_NO_FATAL_FAILURE(testMultipleTlsContexts());
}

// Test that the client can use two different TLS contexts to the same
// destination address and port simultaneously.
TEST_F(HttpsClientTest, multipleTlsContextsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testMultipleTlsContexts());
}

// Test that idle connection can be resumed for second request.
TEST_F(HttpsClientTest, idleConnection) {
    ASSERT_NO_FATAL_FAILURE(testIdleConnection());
}

// Test that idle connection can be resumed for second request.
TEST_F(HttpsClientTest, idleConnectionMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testIdleConnection());
}

// This test verifies that the client returns IO error code when the
// server is unreachable.
TEST_F(HttpsClientTest, unreachable) {
    ASSERT_NO_FATAL_FAILURE(testUnreachable());
}

// This test verifies that the client returns IO error code when the
// server is unreachable.
TEST_F(HttpsClientTest, unreachableMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testUnreachable());
}

// Test that an error is returned by the client if the server response is
// malformed.
TEST_F(HttpsClientTest, malformedResponse) {
    ASSERT_NO_FATAL_FAILURE(testMalformedResponse());
}

// Test that an error is returned by the client if the server response is
// malformed.
TEST_F(HttpsClientTest, malformedResponseMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testMalformedResponse());
}

// Test that client times out when it doesn't receive the entire response
// from the server within a desired time.
TEST_F(HttpsClientTest, clientRequestTimeout) {
    ASSERT_NO_FATAL_FAILURE(testClientRequestTimeout());
}

// Test that client times out when it doesn't receive the entire response
// from the server within a desired time.
TEST_F(HttpsClientTest, clientRequestTimeoutMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testClientRequestTimeout());
}

// This test verifies the behavior of the HTTP client when the premature
// (and unexpected) timeout occurs. The premature timeout may be caused
// by the system clock move.
TEST_F(HttpsClientTest, DISABLED_clientRequestLateStartNoQueue) {
    testClientRequestLateStart(false);
}

// This test verifies the behavior of the HTTP client when the premature
// (and unexpected) timeout occurs. The premature timeout may be caused
// by the system clock move.
TEST_F(HttpsClientTest, DISABLED_clientRequestLateStartNoQueueMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testClientRequestLateStart(false);
}

#ifndef DISABLE_SOME_TESTS
// This test verifies the behavior of the HTTP client when the premature
// timeout occurs and there are requests queued after the request which
// times out.
TEST_F(HttpsClientTest, clientRequestLateStartQueue) {

    testClientRequestLateStart(true);
}

// This test verifies the behavior of the HTTP client when the premature
// timeout occurs and there are requests queued after the request which
// times out.
TEST_F(HttpsClientTest, clientRequestLateStartQueueMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testClientRequestLateStart(true);
}
#endif

// Test that client times out when connection takes too long.
TEST_F(HttpsClientTest, clientConnectTimeout) {
    ASSERT_NO_FATAL_FAILURE(testClientConnectTimeout());
}

// Test that client times out when connection takes too long.
TEST_F(HttpsClientTest, clientConnectTimeoutMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testClientConnectTimeout());
}

#ifndef DISABLE_SOME_TESTS
/// Tests that connect and close callbacks work correctly.
TEST_F(HttpsClientTest, connectCloseCallbacks) {
    ASSERT_NO_FATAL_FAILURE(testConnectCloseCallbacks(HttpVersion(1, 1)));
}

/// Tests that connect and close callbacks work correctly.
TEST_F(HttpsClientTest, connectCloseCallbacksMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testConnectCloseCallbacks(HttpVersion(1, 1)));
}
#endif

/// Tests that HttpClient::closeIfOutOfBand works correctly.
TEST_F(HttpsClientTest, closeIfOutOfBand) {
    ASSERT_NO_FATAL_FAILURE(testCloseIfOutOfBand(HttpVersion(1, 1)));
}

/// Tests that HttpClient::closeIfOutOfBand works correctly.
TEST_F(HttpsClientTest, closeIfOutOfBandMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testCloseIfOutOfBand(HttpVersion(1, 1)));
}

}
