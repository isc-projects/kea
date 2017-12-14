// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <http/http_acceptor.h>
#include <http/connection.h>
#include <http/connection_pool.h>
#include <http/post_request_json.h>
#include <http/response_creator.h>
#include <http/response_json.h>
#include <http/tests/response_test.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <algorithm>

using namespace isc::asiolink;
using namespace isc::http;
using namespace isc::http::test;

namespace {

/// @brief Test HTTP response.
typedef TestHttpResponseBase<HttpResponseJson> Response;

/// @brief Pointer to test HTTP response.
typedef boost::shared_ptr<Response> ResponsePtr;

/// @brief Request timeout used in tests.
const long CONN_REQUEST_TIMEOUT = 1000;

/// @brief Idle connecion timeout used in tests.
const long CONN_IDLE_TIMEOUT = 1000;

/// @brief Implementation of the @ref HttpResponseCreator.
class TestHttpResponseCreator : public HttpResponseCreator {
public:

    /// @brief Create a new request.
    ///
    /// @return Pointer to the new instance of the @ref HttpRequest.
    virtual HttpRequestPtr
    createNewHttpRequest() const {
        return (HttpRequestPtr(new PostHttpRequestJson()));
    }

private:

    /// @brief Creates HTTP response.
    ///
    /// @param request Pointer to the HTTP request.
    /// @return Pointer to the generated HTTP response.
    virtual HttpResponsePtr
    createStockHttpResponse(const ConstHttpRequestPtr& request,
                            const HttpStatusCode& status_code) const {
        // The request hasn't been finalized so the request object
        // doesn't contain any information about the HTTP version number
        // used. But, the context should have this data (assuming the
        // HTTP version is parsed ok).
        HttpVersion http_version(request->context()->http_version_major_,
                                 request->context()->http_version_minor_);
        // This will generate the response holding JSON content.
        ResponsePtr response(new Response(http_version, status_code));
        return (response);
    }

    /// @brief Creates HTTP response.
    ///
    /// @param request Pointer to the HTTP request.
    /// @return Pointer to the generated HTTP OK response with no content.
    virtual HttpResponsePtr
    createDynamicHttpResponse(const ConstHttpRequestPtr& request) {
        // The simplest thing is to create a response with no content.
        // We don't need content to test our class.
        ResponsePtr response(new Response(request->getHttpVersion(),
                                          HttpStatusCode::OK));
        return (response);
    }
};

/// @brief Derivation of @ref HttpConnectionPool exposing protected member.
class TestHttpConnectionPool : public HttpConnectionPool {
public:

    using HttpConnectionPool::connections_;

    /// @brief Checks if specified connection belongs to the pool.
    bool hasConnection(const HttpConnectionPtr& conn) const {
        return (std::find(connections_.begin(), connections_.end(), conn)
                != connections_.end());
    }

};

/// @brief Test fixture class for @ref HttpConnectionPool.
class HttpConnectionPoolTest : public ::testing::Test {
public:

    /// @brief Constructor.
    HttpConnectionPoolTest()
        : io_service_(), acceptor_(io_service_), connection_pool_(),
          response_creator_(new TestHttpResponseCreator()) {
    }

    IOService io_service_;                      ///< IO service.
    HttpAcceptor acceptor_;                     ///< Test acceptor.
    HttpConnectionPool connection_pool_;        ///< Test connection pool.
    HttpResponseCreatorPtr response_creator_;   ///< Test response creator.

};

// This test verifies that connections can be added to the pool and removed.
TEST_F(HttpConnectionPoolTest, startStop) {
    // Create two distinct connections.
    HttpConnectionPtr conn1(new HttpConnection(io_service_, acceptor_,
                                               connection_pool_,
                                               response_creator_,
                                               HttpAcceptorCallback(),
                                               CONN_REQUEST_TIMEOUT,
                                               CONN_IDLE_TIMEOUT));
    HttpConnectionPtr conn2(new HttpConnection(io_service_, acceptor_,
                                               connection_pool_,
                                               response_creator_,
                                               HttpAcceptorCallback(),
                                               CONN_REQUEST_TIMEOUT,
                                               CONN_IDLE_TIMEOUT));
    // The pool should be initially empty.
    TestHttpConnectionPool pool;
    ASSERT_TRUE(pool.connections_.empty());

    // Start first connection and check that it has been added to the pool.
    ASSERT_NO_THROW(pool.start(conn1));
    ASSERT_EQ(1, pool.connections_.size());
    ASSERT_EQ(1, pool.hasConnection(conn1));

    // Start second connection and check that it also has been added.
    ASSERT_NO_THROW(pool.start(conn2));
    ASSERT_EQ(2, pool.connections_.size());
    ASSERT_EQ(1, pool.hasConnection(conn2));

    // Stop first connection.
    ASSERT_NO_THROW(pool.stop(conn1));
    ASSERT_EQ(1, pool.connections_.size());
    // Check that it has been removed but the second connection is still there.
    ASSERT_EQ(0, pool.hasConnection(conn1));
    ASSERT_EQ(1, pool.hasConnection(conn2));

    // Remove second connection and verify.
    ASSERT_NO_THROW(pool.stop(conn2));
    EXPECT_TRUE(pool.connections_.empty());
}

// Check that all connections can be remove with a single call.
TEST_F(HttpConnectionPoolTest, stopAll) {
    HttpConnectionPtr conn1(new HttpConnection(io_service_, acceptor_,
                                               connection_pool_,
                                               response_creator_,
                                               HttpAcceptorCallback(),
                                               CONN_REQUEST_TIMEOUT,
                                               CONN_IDLE_TIMEOUT));
    HttpConnectionPtr conn2(new HttpConnection(io_service_, acceptor_,
                                               connection_pool_,
                                               response_creator_,
                                               HttpAcceptorCallback(),
                                               CONN_REQUEST_TIMEOUT,
                                               CONN_IDLE_TIMEOUT));
    TestHttpConnectionPool pool;
    ASSERT_NO_THROW(pool.start(conn1));
    ASSERT_NO_THROW(pool.start(conn2));

    // There are two distinct connections in the pool.
    ASSERT_EQ(2, pool.connections_.size());

    // This should remove all connections.
    ASSERT_NO_THROW(pool.stopAll());
    EXPECT_TRUE(pool.connections_.empty());
}

// Check that stopping non-existing connection is no-op.
TEST_F(HttpConnectionPoolTest, stopInvalid) {
    HttpConnectionPtr conn1(new HttpConnection(io_service_, acceptor_,
                                               connection_pool_,
                                               response_creator_,
                                               HttpAcceptorCallback(),
                                               CONN_REQUEST_TIMEOUT,
                                               CONN_IDLE_TIMEOUT));
    HttpConnectionPtr conn2(new HttpConnection(io_service_, acceptor_,
                                               connection_pool_,
                                               response_creator_,
                                               HttpAcceptorCallback(),
                                               CONN_REQUEST_TIMEOUT,
                                               CONN_IDLE_TIMEOUT));
    TestHttpConnectionPool pool;
    ASSERT_NO_THROW(pool.start(conn1));
    ASSERT_NO_THROW(pool.stop(conn2));
    ASSERT_EQ(1, pool.connections_.size());
    ASSERT_EQ(1, pool.hasConnection(conn1));
}

}
