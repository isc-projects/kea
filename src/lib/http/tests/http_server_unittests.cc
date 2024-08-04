// Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/tls_acceptor.h>
#include <cc/data.h>
#include <http/testutils/test_http_client.h>
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
#include <http/tests/http_response_creator_test.h>

using namespace boost::asio::ip;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::http;
using namespace isc::http::test;
using namespace isc::util;
namespace ph = std::placeholders;

#include <http/tests/http_server_test.h>

namespace {

/// @brief Test fixture class for @ref HttpListener.
class HttpListenerTest : public BaseListenerTest {
public:

    /// brief Create a HTTP test client.
    virtual TestClientPtr createClient() override {
        return (TestHttpClientPtr(new TestHttpClient(io_service_)));
    }
};

// This test verifies that HTTP connection can be established and used to
// transmit HTTP request and receive a response.
TEST_F(HttpListenerTest, listen) {
    testListen();
}

// This test verifies that persistent HTTP connection can be established when
// no "Connection: Keep-Alive" header value is specified.
TEST_F(HttpListenerTest, keepAlive) {
    testKeepAlive();
}

// This test verifies that persistent HTTP connection is established by default
// when HTTP/1.1 is in use.
TEST_F(HttpListenerTest, persistentConnection) {
    testPersistentConnection();
}

// This test verifies that "keep-alive" connection is closed by the server after
// an idle time.
TEST_F(HttpListenerTest, keepAliveTimeout) {
    testKeepAliveTimeout();
}

// This test verifies that persistent connection is closed by the server after
// an idle time.
TEST_F(HttpListenerTest, persistentConnectionTimeout) {
    testPersistentConnectionTimeout();
}

// This test verifies that HTTP/1.1 connection remains open even if there is an
// error in the message body.
TEST_F(HttpListenerTest, persistentConnectionBadBody) {
    testPersistentConnectionBadBody();
}

// This test verifies that the HTTP listener can't be started twice.
TEST_F(HttpListenerTest, startTwice) {
    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), factory_,
                          HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                          HttpListener::IdleTimeout(IDLE_TIMEOUT));
    ASSERT_NO_THROW(listener.start());
    EXPECT_THROW(listener.start(), HttpListenerError);
}

// This test verifies that Bad Request status is returned when the request
// is malformed.
TEST_F(HttpListenerTest, badRequest) {
    testBadRequest();
}

// This test verifies that NULL pointer can't be specified for the
// HttpResponseCreatorFactory.
TEST_F(HttpListenerTest, invalidFactory) {
    EXPECT_THROW(HttpListener(io_service_, IOAddress(SERVER_ADDRESS),
                              SERVER_PORT, TlsContextPtr(),
                              HttpResponseCreatorFactoryPtr(),
                              HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                              HttpListener::IdleTimeout(IDLE_TIMEOUT)),
                 HttpListenerError);
}

// This test verifies that the timeout of 0 can't be specified for the
// Request Timeout.
TEST_F(HttpListenerTest, invalidRequestTimeout) {
    EXPECT_THROW(HttpListener(io_service_, IOAddress(SERVER_ADDRESS),
                              SERVER_PORT, TlsContextPtr(), factory_,
                              HttpListener::RequestTimeout(0),
                              HttpListener::IdleTimeout(IDLE_TIMEOUT)),
                 HttpListenerError);
}

// This test verifies that the timeout of 0 can't be specified for the
// idle persistent connection timeout.
TEST_F(HttpListenerTest, invalidIdleTimeout) {
    EXPECT_THROW(HttpListener(io_service_, IOAddress(SERVER_ADDRESS),
                              SERVER_PORT, TlsContextPtr(), factory_,
                              HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                              HttpListener::IdleTimeout(0)),
                 HttpListenerError);
}

// This test verifies that listener can't be bound to the port to which
// other server is bound.
TEST_F(HttpListenerTest, addressInUse) {
    tcp::acceptor acceptor(io_service_->getInternalIOService());
    // Use other port than SERVER_PORT to make sure that this TCP connection
    // doesn't affect subsequent tests.
    tcp::endpoint endpoint(address::from_string(SERVER_ADDRESS),
                           SERVER_PORT + 1);
    acceptor.open(endpoint.protocol());
    acceptor.bind(endpoint);

    // Listener should report an error when we try to start it because another
    // acceptor is bound to that port and address.
    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS),
                          SERVER_PORT + 1, TlsContextPtr(), factory_,
                          HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                          HttpListener::IdleTimeout(IDLE_TIMEOUT));
    EXPECT_THROW(listener.start(), HttpListenerError);
}

// This test verifies that HTTP Request Timeout status is returned as
// expected when the read part of the request contains the HTTP
// version number. The timeout response should contain the same
// HTTP version number as the partial request.
TEST_F(HttpListenerTest, requestTimeoutHttpVersionFound) {
    // The part of the request specified here is correct but it is not
    // a complete request.
    const std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length:";

    testRequestTimeout(request, HttpVersion::HTTP_11());
}

// This test verifies that HTTP Request Timeout status is returned as
// expected when the read part of the request does not contain
// the HTTP version number. The timeout response should by default
// contain HTTP/1.0 version number.
TEST_F(HttpListenerTest, requestTimeoutHttpVersionNotFound) {
    // The part of the request specified here is correct but it is not
    // a complete request.
    const std::string request = "POST /foo/bar HTTP";

    testRequestTimeout(request, HttpVersion::HTTP_10());
}

// This test verifies that injecting length value greater than the
// output buffer length to the socket write callback does not cause
// an exception.
TEST_F(HttpListenerTest, tooLongWriteBuffer) {
    testWriteBufferIssues<HttpConnectionLongWriteBuffer>();
}

// This test verifies that changing the transaction before calling
// the socket write callback does not cause an exception.
TEST_F(HttpListenerTest, transactionChangeDuringWrite) {
    testWriteBufferIssues<HttpConnectionTransactionChange>();
}

}
