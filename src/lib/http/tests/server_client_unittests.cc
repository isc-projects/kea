// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/tls_acceptor.h>
#include <cc/data.h>
#include <test_http_client.h>
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

using namespace boost::asio::ip;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::http;
using namespace isc::http::test;
using namespace isc::util;
namespace ph = std::placeholders;

namespace {

/// @brief IP address to which HTTP service is bound.
const std::string SERVER_ADDRESS = "127.0.0.1";

/// @brief IPv6 address to whch HTTP service is bound.
const std::string IPV6_SERVER_ADDRESS = "::1";

/// @brief Port number to which HTTP service is bound.
const unsigned short SERVER_PORT = 18123;

/// @brief Request Timeout used in most of the tests (ms).
const long REQUEST_TIMEOUT = 10000;

/// @brief Persistent connection idle timeout used in most of the tests (ms).
const long IDLE_TIMEOUT = 10000;

/// @brief Persistent connection idle timeout used in tests where idle connections
/// are tested (ms).
const long SHORT_IDLE_TIMEOUT = 200;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Test HTTP response.
typedef TestHttpResponseBase<HttpResponseJson> Response;

/// @brief Pointer to test HTTP response.
typedef boost::shared_ptr<Response> ResponsePtr;

/// @brief Generic test HTTP response.
typedef TestHttpResponseBase<HttpResponse> GenericResponse;

/// @brief Pointer to generic test HTTP response.
typedef boost::shared_ptr<GenericResponse> GenericResponsePtr;

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
    createStockHttpResponse(const HttpRequestPtr& request,
                            const HttpStatusCode& status_code) const {
        // The request hasn't been finalized so the request object
        // doesn't contain any information about the HTTP version number
        // used. But, the context should have this data (assuming the
        // HTTP version is parsed ok).
        HttpVersion http_version(request->context()->http_version_major_,
                                 request->context()->http_version_minor_);
        // This will generate the response holding JSON content.
        ResponsePtr response(new Response(http_version, status_code));
        response->finalize();
        return (response);
    }

    /// @brief Creates HTTP response.
    ///
    /// This method generates 3 types of responses:
    /// - response with a requested content type,
    /// - partial response with incomplete JSON body,
    /// - response with JSON body copied from the request.
    ///
    /// The first one is useful to test situations when received response can't
    /// be parsed because of the content type mismatch. The second one is useful
    /// to test request timeouts. The third type is used by most of the unit tests
    /// to test successful transactions.
    ///
    /// @param request Pointer to the HTTP request.
    /// @return Pointer to the generated HTTP OK response with no content.
    virtual HttpResponsePtr
    createDynamicHttpResponse(HttpRequestPtr request) {
        // Request must always be JSON.
        PostHttpRequestJsonPtr request_json =
            boost::dynamic_pointer_cast<PostHttpRequestJson>(request);
        ConstElementPtr body;
        if (request_json) {
            body = request_json->getBodyAsJson();
            if (body) {
                // Check if the client requested one of the two first response
                // types.
                GenericResponsePtr response;
                ConstElementPtr content_type = body->get("requested-content-type");
                ConstElementPtr partial_response = body->get("partial-response");
                if (content_type || partial_response) {
                    // The first two response types can only be generated using the
                    // generic response as we have to explicitly modify some of the
                    // values.
                    response.reset(new GenericResponse(request->getHttpVersion(),
                                                       HttpStatusCode::OK));
                    HttpResponseContextPtr ctx = response->context();

                    if (content_type) {
                        // Provide requested content type.
                        ctx->headers_.push_back(HttpHeaderContext("Content-Type",
                                                                  content_type->stringValue()));
                        // It doesn't matter what body is there.
                        ctx->body_ = "abcd";
                        response->finalize();

                    } else {
                        // Generate JSON response.
                        ctx->headers_.push_back(HttpHeaderContext("Content-Type",
                                                                  "application/json"));
                        // The body lacks '}' so the client will be waiting for it and
                        // eventually should time out.
                        ctx->body_ = "{";
                        response->finalize();
                        // The auto generated Content-Length header would be based on the
                        // body size (so set to 1 byte). We have to override it to
                        // account for the missing '}' character.
                        response->setContentLength(2);
                    }
                    return (response);
                }
            }
        }

        // Third type of response is requested.
        ResponsePtr response(new Response(request->getHttpVersion(),
                                          HttpStatusCode::OK));
        // If body was included in the request. Let's copy it.
        if (body) {
            response->setBodyAsJson(body);
        }

        response->finalize();
        return (response);
    }
};

/// @brief Implementation of the test @ref HttpResponseCreatorFactory.
///
/// This factory class creates @ref TestHttpResponseCreator instances.
class TestHttpResponseCreatorFactory : public HttpResponseCreatorFactory {
public:

    /// @brief Creates @ref TestHttpResponseCreator instance.
    virtual HttpResponseCreatorPtr create() const {
        HttpResponseCreatorPtr response_creator(new TestHttpResponseCreator());
        return (response_creator);
    }
};

/// @brief Implementation of the HTTP listener used in tests.
///
/// This implementation replaces the @c HttpConnection type with a custom
/// implementation.
///
/// @tparam HttpConnectionType Type of the connection object to be used by
/// the listener implementation.
template<typename HttpConnectionType>
class HttpListenerImplCustom : public HttpListenerImpl {
public:

    HttpListenerImplCustom(IOService& io_service,
                           const IOAddress& server_address,
                           const unsigned short server_port,
                           const TlsContextPtr& tls_context,
                           const HttpResponseCreatorFactoryPtr& creator_factory,
                           const long request_timeout,
                           const long idle_timeout)
        : HttpListenerImpl(io_service, server_address, server_port,
                           tls_context, creator_factory, request_timeout,
                           idle_timeout) {
    }

protected:

    /// @brief Creates an instance of the @c HttpConnection.
    ///
    /// This method is virtual so as it can be overridden when customized
    /// connections are to be used, e.g. in case of unit testing.
    ///
    /// @param response_creator Pointer to the response creator object used to
    /// create HTTP response from the HTTP request received.
    /// @param callback Callback invoked when new connection is accepted.
    ///
    /// @return Pointer to the created connection.
    virtual HttpConnectionPtr createConnection(const HttpResponseCreatorPtr& response_creator,
                                               const HttpAcceptorCallback& callback) {
        HttpConnectionPtr
            conn(new HttpConnectionType(io_service_, acceptor_,
                                        tls_context_, connections_,
                                        response_creator, callback,
                                        request_timeout_, idle_timeout_));
        return (conn);
    }
};

/// @brief Derivation of the @c HttpListener used in tests.
///
/// This class replaces the default implementation instance with the
/// @c HttpListenerImplCustom using the customized connection type.
///
/// @tparam HttpConnectionType Type of the connection object to be used by
/// the listener implementation.
template<typename HttpConnectionType>
class HttpListenerCustom : public HttpListener {
public:

    /// @brief Constructor.
    ///
    /// @param io_service IO service to be used by the listener.
    /// @param server_address Address on which the HTTP service should run.
    /// @param server_port Port number on which the HTTP service should run.
    /// @param tls_context TLS context.
    /// @param creator_factory Pointer to the caller-defined
    /// @ref HttpResponseCreatorFactory derivation which should be used to
    /// create @ref HttpResponseCreator instances.
    /// @param request_timeout Timeout after which the HTTP Request Timeout
    /// is generated.
    /// @param idle_timeout Timeout after which an idle persistent HTTP
    /// connection is closed by the server.
    ///
    /// @throw HttpListenerError when any of the specified parameters is
    /// invalid.
    HttpListenerCustom(IOService& io_service,
                       const IOAddress& server_address,
                       const unsigned short server_port,
                       const TlsContextPtr& tls_context,
                       const HttpResponseCreatorFactoryPtr& creator_factory,
                       const HttpListener::RequestTimeout& request_timeout,
                       const HttpListener::IdleTimeout& idle_timeout)
        : HttpListener(io_service, server_address, server_port,
                       tls_context, creator_factory,
                       request_timeout, idle_timeout) {
        // Replace the default implementation with the customized version
        // using the custom derivation of the HttpConnection.
        impl_.reset(new HttpListenerImplCustom<HttpConnectionType>
                    (io_service, server_address, server_port,
                     tls_context, creator_factory, request_timeout.value_,
                     idle_timeout.value_));
    }
};

/// @brief Implementation of the @c HttpConnection which injects greater
/// length value than the buffer size into the write socket callback.
class HttpConnectionLongWriteBuffer : public HttpConnection {
public:

    /// @brief Constructor.
    ///
    /// @param io_service IO service to be used by the connection.
    /// @param acceptor Pointer to the TCP acceptor object used to listen for
    /// new HTTP connections.
    /// @param tls_context TLS context.
    /// @param connection_pool Connection pool in which this connection is
    /// stored.
    /// @param response_creator Pointer to the response creator object used to
    /// create HTTP response from the HTTP request received.
    /// @param callback Callback invoked when new connection is accepted.
    /// @param request_timeout Configured timeout for a HTTP request.
    /// @param idle_timeout Timeout after which persistent HTTP connection is
    /// closed by the server.
    HttpConnectionLongWriteBuffer(IOService& io_service,
                                  const HttpAcceptorPtr& acceptor,
                                  const TlsContextPtr& tls_context,
                                  HttpConnectionPool& connection_pool,
                                  const HttpResponseCreatorPtr& response_creator,
                                  const HttpAcceptorCallback& callback,
                                  const long request_timeout,
                                  const long idle_timeout)
        : HttpConnection(io_service, acceptor, tls_context, connection_pool,
                         response_creator, callback, request_timeout,
                         idle_timeout) {
    }

    /// @brief Callback invoked when data is sent over the socket.
    ///
    /// @param transaction Pointer to the transaction for which the callback
    /// is invoked.
    /// @param ec Error code.
    /// @param length Length of the data sent.
    virtual void socketWriteCallback(HttpConnection::TransactionPtr transaction,
                                     boost::system::error_code ec,
                                     size_t length) {
        // Pass greater length of the data written. The callback should deal
        // with this and adjust the data length.
        HttpConnection::socketWriteCallback(transaction, ec, length + 1);
    }
};

/// @brief Implementation of the @c HttpConnection which replaces
/// transaction instance prior to calling write socket callback.
class HttpConnectionTransactionChange : public HttpConnection {
public:

    /// @brief Constructor.
    ///
    /// @param io_service IO service to be used by the connection.
    /// @param acceptor Pointer to the TCP acceptor object used to listen for
    /// new HTTP connections.
    /// @param context TLS tls_context.
    /// @param connection_pool Connection pool in which this connection is
    /// stored.
    /// @param response_creator Pointer to the response creator object used to
    /// create HTTP response from the HTTP request received.
    /// @param callback Callback invoked when new connection is accepted.
    /// @param request_timeout Configured timeout for a HTTP request.
    /// @param idle_timeout Timeout after which persistent HTTP connection is
    /// closed by the server.
    HttpConnectionTransactionChange(IOService& io_service,
                                    const HttpAcceptorPtr& acceptor,
                                    const TlsContextPtr& tls_context,
                                    HttpConnectionPool& connection_pool,
                                    const HttpResponseCreatorPtr& response_creator,
                                    const HttpAcceptorCallback& callback,
                                    const long request_timeout,
                                    const long idle_timeout)
        : HttpConnection(io_service, acceptor, tls_context, connection_pool,
                         response_creator, callback, request_timeout,
                         idle_timeout) {
    }

    /// @brief Callback invoked when data is sent over the socket.
    ///
    /// @param transaction Pointer to the transaction for which the callback
    /// is invoked.
    /// @param ec Error code.
    /// @param length Length of the data sent.
    virtual void socketWriteCallback(HttpConnection::TransactionPtr transaction,
                                     boost::system::error_code ec,
                                     size_t length) {
        // Replace the transaction. The socket callback should deal with this
        // gracefully. It should detect that the output buffer is empty. Then
        // try to see if the connection is persistent. This check should fail,
        // because the request hasn't been created/finalized. The exception
        // thrown upon checking the persistence should be caught and the
        // connection closed.
        transaction = HttpConnection::Transaction::create(response_creator_);
        HttpConnection::socketWriteCallback(transaction, ec, length);
    }
};

/// @brief Pointer to the TestHttpClient.
typedef boost::shared_ptr<TestHttpClient> TestHttpClientPtr;

/// @brief Test fixture class for @ref HttpListener.
class HttpListenerTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Starts test timer which detects timeouts.
    HttpListenerTest()
        : io_service_(), factory_(new TestHttpResponseCreatorFactory()),
          test_timer_(io_service_), run_io_service_timer_(io_service_), clients_() {
        test_timer_.setup(std::bind(&HttpListenerTest::timeoutHandler, this, true),
                          TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
    }

    /// @brief Destructor.
    ///
    /// Removes active HTTP clients.
    virtual ~HttpListenerTest() {
        for (auto client = clients_.begin(); client != clients_.end();
             ++client) {
            (*client)->close();
        }
    }

    /// @brief Connect to the endpoint.
    ///
    /// This method creates TestHttpClient instance and retains it in the clients_
    /// list.
    ///
    /// @param request String containing the HTTP request to be sent.
    void startRequest(const std::string& request) {
        TestHttpClientPtr client(new TestHttpClient(io_service_));
        clients_.push_back(client);
        clients_.back()->startRequest(request);
    }

    /// @brief Callback function invoke upon test timeout.
    ///
    /// It stops the IO service and reports test timeout.
    ///
    /// @param fail_on_timeout Specifies if test failure should be reported.
    void timeoutHandler(const bool fail_on_timeout) {
        if (fail_on_timeout) {
            ADD_FAILURE() << "Timeout occurred while running the test!";
        }
        io_service_.stop();
    }

    /// @brief Runs IO service with optional timeout.
    ///
    /// @param timeout Optional value specifying for how long the io service
    /// should be ran.
    void runIOService(long timeout = 0) {
        io_service_.get_io_service().reset();

        if (timeout > 0) {
            run_io_service_timer_.setup(std::bind(&HttpListenerTest::timeoutHandler,
                                                  this, false),
                                        timeout, IntervalTimer::ONE_SHOT);
        }
        io_service_.run();
        io_service_.get_io_service().reset();
        io_service_.poll();
    }

    /// @brief Returns HTTP OK response expected by unit tests.
    ///
    /// @param http_version HTTP version.
    ///
    /// @return HTTP OK response expected by unit tests.
    std::string httpOk(const HttpVersion& http_version) {
        std::ostringstream s;
        s << "HTTP/" << http_version.major_ << "." << http_version.minor_ << " 200 OK\r\n"
            "Content-Length: 33\r\n"
            "Content-Type: application/json\r\n"
            "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
            "\r\n"
            "{ \"remote-address\": \"127.0.0.1\" }";
        return (s.str());
    }

    /// @brief Tests that HTTP request timeout status is returned when the
    /// server does not receive the entire request.
    ///
    /// @param request Partial request for which the parser will be waiting for
    /// the next chunks of data.
    /// @param expected_version HTTP version expected in the response.
    void testRequestTimeout(const std::string& request,
                            const HttpVersion& expected_version) {
        // Open the listener with the Request Timeout of 1 sec and post the
        // partial request.
        HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS),
                              SERVER_PORT, TlsContextPtr(),
                              factory_, HttpListener::RequestTimeout(1000),
                              HttpListener::IdleTimeout(IDLE_TIMEOUT));
        ASSERT_NO_THROW(listener.start());
        ASSERT_NO_THROW(startRequest(request));
        ASSERT_NO_THROW(runIOService());
        ASSERT_EQ(1, clients_.size());
        TestHttpClientPtr client = *clients_.begin();
        ASSERT_TRUE(client);

        // Build the reference response.
        std::ostringstream expected_response;
        expected_response
            << "HTTP/" << expected_version.major_ << "." << expected_version.minor_
            << " 408 Request Timeout\r\n"
            "Content-Length: 44\r\n"
            "Content-Type: application/json\r\n"
            "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
            "\r\n"
            "{ \"result\": 408, \"text\": \"Request Timeout\" }";

        // The server should wait for the missing part of the request for 1 second.
        // The missing part never arrives so the server should respond with the
        // HTTP Request Timeout status.
        EXPECT_EQ(expected_response.str(), client->getResponse());
    }

    /// @brief Tests various cases when unexpected data is passed to the
    /// socket write handler.
    ///
    /// This test uses the custom listener and the test specific derivations of
    /// the @c HttpConnection class to enforce injection of the unexpected
    /// data to the socket write callback. The two example applications of
    /// this test are:
    /// - injecting greater length value than the output buffer size,
    /// - replacing the transaction with another transaction.
    ///
    /// It is expected that the socket write callback deals gracefully with
    /// those situations.
    ///
    /// @tparam HttpConnectionType Test specific derivation of the
    /// @c HttpConnection class.
    template<typename HttpConnectionType>
    void testWriteBufferIssues() {
        // The HTTP/1.1 requests are by default persistent.
        std::string request = "POST /foo/bar HTTP/1.1\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: 3\r\n\r\n"
            "{ }";

        // Use custom listener and the specialized connection object.
        HttpListenerCustom<HttpConnectionType>
            listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                     TlsContextPtr(), factory_,
                     HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                     HttpListener::IdleTimeout(IDLE_TIMEOUT));

        ASSERT_NO_THROW(listener.start());

        // Send the request.
        ASSERT_NO_THROW(startRequest(request));

        // Injecting unexpected data should not result in an exception.
        ASSERT_NO_THROW(runIOService());

        ASSERT_EQ(1, clients_.size());
        TestHttpClientPtr client = *clients_.begin();
        ASSERT_TRUE(client);
        EXPECT_EQ(httpOk(HttpVersion::HTTP_11()), client->getResponse());
    }

    /// @brief IO service used in the tests.
    IOService io_service_;

    /// @brief Pointer to the response creator factory.
    HttpResponseCreatorFactoryPtr factory_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Asynchronous timer for running IO service for a specified amount
    /// of time.
    IntervalTimer run_io_service_timer_;

    /// @brief List of client connections.
    std::list<TestHttpClientPtr> clients_;
};

// This test verifies that HTTP connection can be established and used to
// transmit HTTP request and receive a response.
TEST_F(HttpListenerTest, listen) {
    const std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), factory_,
                          HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                          HttpListener::IdleTimeout(IDLE_TIMEOUT));
    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TestHttpClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_EQ(httpOk(HttpVersion::HTTP_11()), client->getResponse());

    listener.stop();
    io_service_.poll();
}


// This test verifies that persistent HTTP connection can be established when
// "Connection: Keep-Alive" header value is specified.
TEST_F(HttpListenerTest, keepAlive) {

    // The first request contains the keep-alive header which instructs the server
    // to maintain the TCP connection after sending a response.
    std::string request = "POST /foo/bar HTTP/1.0\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n"
        "Connection: Keep-Alive\r\n\r\n"
        "{ }";

    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), factory_,
                          HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                          HttpListener::IdleTimeout(IDLE_TIMEOUT));

    ASSERT_NO_THROW(listener.start());

    // Send the request with the keep-alive header.
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TestHttpClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_EQ(httpOk(HttpVersion::HTTP_10()), client->getResponse());

    // We have sent keep-alive header so we expect that the connection with
    // the server remains active.
    ASSERT_TRUE(client->isConnectionAlive());

    // Test that we can send another request via the same connection. This time
    // it lacks the keep-alive header, so the server should close the connection
    // after sending the response.
    request = "POST /foo/bar HTTP/1.0\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    // Send request reusing the existing connection.
    ASSERT_NO_THROW(client->sendRequest(request));
    ASSERT_NO_THROW(runIOService());
    EXPECT_EQ(httpOk(HttpVersion::HTTP_10()), client->getResponse());

    // Connection should have been closed by the server.
    EXPECT_TRUE(client->isConnectionClosed());

    listener.stop();
    io_service_.poll();
}

// This test verifies that persistent HTTP connection is established by default
// when HTTP/1.1 is in use.
TEST_F(HttpListenerTest, persistentConnection) {

    // The HTTP/1.1 requests are by default persistent.
    std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), factory_,
                          HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                          HttpListener::IdleTimeout(IDLE_TIMEOUT));

    ASSERT_NO_THROW(listener.start());

    // Send the first request.
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TestHttpClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_EQ(httpOk(HttpVersion::HTTP_11()), client->getResponse());

    // HTTP/1.1 connection is persistent by default.
    ASSERT_TRUE(client->isConnectionAlive());

    // Test that we can send another request via the same connection. This time
    // it includes the "Connection: close" header which instructs the server to
    // close the connection after responding.
    request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n"
        "Connection: close\r\n\r\n"
        "{ }";

    // Send request reusing the existing connection.
    ASSERT_NO_THROW(client->sendRequest(request));
    ASSERT_NO_THROW(runIOService());
    EXPECT_EQ(httpOk(HttpVersion::HTTP_11()), client->getResponse());

    // Connection should have been closed by the server.
    EXPECT_TRUE(client->isConnectionClosed());

    listener.stop();
    io_service_.poll();
}

// This test verifies that "keep-alive" connection is closed by the server after
// an idle time.
TEST_F(HttpListenerTest, keepAliveTimeout) {

    // The first request contains the keep-alive header which instructs the server
    // to maintain the TCP connection after sending a response.
    std::string request = "POST /foo/bar HTTP/1.0\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n"
        "Connection: Keep-Alive\r\n\r\n"
        "{ }";

    // Specify the idle timeout of 500ms.
    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), factory_,
                          HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                          HttpListener::IdleTimeout(500));

    ASSERT_NO_THROW(listener.start());

    // Send the request with the keep-alive header.
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TestHttpClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_EQ(httpOk(HttpVersion::HTTP_10()), client->getResponse());

    // We have sent keep-alive header so we expect that the connection with
    // the server remains active.
    ASSERT_TRUE(client->isConnectionAlive());

    // Run IO service for 1000ms. The idle time is set to 500ms, so the connection
    // should be closed by the server while we wait here.
    runIOService(1000);

    // Make sure the connection has been closed.
    EXPECT_TRUE(client->isConnectionClosed());

    // Check if we can re-establish the connection and send another request.
    clients_.clear();
    request = "POST /foo/bar HTTP/1.0\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_EQ(httpOk(HttpVersion::HTTP_10()), client->getResponse());

    EXPECT_TRUE(client->isConnectionClosed());

    listener.stop();
    io_service_.poll();
}

// This test verifies that persistent connection is closed by the server after
// an idle time.
TEST_F(HttpListenerTest, persistentConnectionTimeout) {

    // The HTTP/1.1 requests are by default persistent.
    std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    // Specify the idle timeout of 500ms.
    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), factory_,
                          HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                          HttpListener::IdleTimeout(500));

    ASSERT_NO_THROW(listener.start());

    // Send the request.
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TestHttpClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_EQ(httpOk(HttpVersion::HTTP_11()), client->getResponse());

    // The connection should remain active.
    ASSERT_TRUE(client->isConnectionAlive());

    // Run IO service for 1000ms. The idle time is set to 500ms, so the connection
    // should be closed by the server while we wait here.
    runIOService(1000);

    // Make sure the connection has been closed.
    EXPECT_TRUE(client->isConnectionClosed());

    // Check if we can re-establish the connection and send another request.
    clients_.clear();
    request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n"
        "Connection: close\r\n\r\n"
        "{ }";

    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_EQ(httpOk(HttpVersion::HTTP_11()), client->getResponse());

    EXPECT_TRUE(client->isConnectionClosed());

    listener.stop();
    io_service_.poll();
}

// This test verifies that HTTP/1.1 connection remains open even if there is an
// error in the message body.
TEST_F(HttpListenerTest, persistentConnectionBadBody) {

    // The HTTP/1.1 requests are by default persistent.
    std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 12\r\n\r\n"
        "{ \"a\": abc }";

    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), factory_,
                          HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                          HttpListener::IdleTimeout(IDLE_TIMEOUT));

    ASSERT_NO_THROW(listener.start());

    // Send the request.
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TestHttpClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_EQ("HTTP/1.1 400 Bad Request\r\n"
              "Content-Length: 40\r\n"
              "Content-Type: application/json\r\n"
              "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
              "\r\n"
              "{ \"result\": 400, \"text\": \"Bad Request\" }",
              client->getResponse());

    // The connection should remain active.
    ASSERT_TRUE(client->isConnectionAlive());

    // Make sure that we can send another request. This time we specify the
    // "close" connection-token to force the connection to close.
    request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n"
        "Connection: close\r\n\r\n"
        "{ }";

    // Send request reusing the existing connection.
    ASSERT_NO_THROW(client->sendRequest(request));
    ASSERT_NO_THROW(runIOService());
    EXPECT_EQ(httpOk(HttpVersion::HTTP_11()), client->getResponse());

    EXPECT_TRUE(client->isConnectionClosed());

    listener.stop();
    io_service_.poll();
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
    // Content-Type is wrong. This should result in Bad Request status.
    const std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: foo\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          TlsContextPtr(), factory_,
                          HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                          HttpListener::IdleTimeout(IDLE_TIMEOUT));
    ASSERT_NO_THROW(listener.start());
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TestHttpClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_EQ("HTTP/1.1 400 Bad Request\r\n"
              "Content-Length: 40\r\n"
              "Content-Type: application/json\r\n"
              "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
              "\r\n"
              "{ \"result\": 400, \"text\": \"Bad Request\" }",
              client->getResponse());
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
    tcp::acceptor acceptor(io_service_.get_io_service());
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

/// @brief Test fixture class for testing HTTP client.
class HttpClientTest : public HttpListenerTest {
public:

    /// @brief Constructor.
    HttpClientTest()
        : HttpListenerTest(),
          listener_(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                    TlsContextPtr(), factory_,
                    HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                    HttpListener::IdleTimeout(IDLE_TIMEOUT)),
          listener2_(io_service_, IOAddress(IPV6_SERVER_ADDRESS), SERVER_PORT + 1,
                     TlsContextPtr(), factory_,
                     HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                     HttpListener::IdleTimeout(IDLE_TIMEOUT)),
          listener3_(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT + 2,
                     TlsContextPtr(), factory_,
                     HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                     HttpListener::IdleTimeout(SHORT_IDLE_TIMEOUT)) {
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Destructor.
    ~HttpClientTest() {
        listener_.stop();
        listener2_.stop();
        listener3_.stop();
        io_service_.poll();
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Creates HTTP request with JSON body.
    ///
    /// It includes a JSON parameter with a specified value.
    ///
    /// @param parameter_name JSON parameter to be included.
    /// @param value JSON parameter value.
    /// @param version HTTP version to be used. Default is HTTP/1.1.
    template<typename ValueType>
    PostHttpRequestJsonPtr createRequest(const std::string& parameter_name,
                                         const ValueType& value,
                                         const HttpVersion& version = HttpVersion(1, 1)) {
        // Create POST request with JSON body.
        PostHttpRequestJsonPtr request(new PostHttpRequestJson(HttpRequest::Method::HTTP_POST,
                                                               "/", version));
        // Body is a map with a specified parameter included.
        ElementPtr body = Element::createMap();
        body->set(parameter_name, Element::create(value));
        request->setBodyAsJson(body);
        try {
            request->finalize();

        } catch (const std::exception& ex) {
            ADD_FAILURE() << "failed to create request: " << ex.what();
        }

        return (request);
    }

    /// @brief Test that two consecutive requests can be sent over the same
    /// connection (if persistent, if not persistent two connections will
    /// be used).
    ///
    /// @param version HTTP version to be used.
    void testConsecutiveRequests(const HttpVersion& version) {
        // Start the server.
        ASSERT_NO_THROW(listener_.start());

        // Create a client and specify the URL on which the server can be reached.
        HttpClient client(io_service_);
        Url url("http://127.0.0.1:18123");

        // Initiate request to the server.
        PostHttpRequestJsonPtr request1 = createRequest("sequence", 1, version);
        HttpResponseJsonPtr response1(new HttpResponseJson());
        unsigned resp_num = 0;
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request1, response1,
            [this, &resp_num](const boost::system::error_code& ec,
                              const HttpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }
            EXPECT_FALSE(ec);
        }));

        // Initiate another request to the destination.
        PostHttpRequestJsonPtr request2 = createRequest("sequence", 2, version);
        HttpResponseJsonPtr response2(new HttpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request2, response2,
            [this, &resp_num](const boost::system::error_code& ec,
                              const HttpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }
            EXPECT_FALSE(ec);
        }));

        // Actually trigger the requests. The requests should be handlded by the
        // server one after another. While the first request is being processed
        // the server should queue another one.
        ASSERT_NO_THROW(runIOService());

        // Make sure that the received responses are different. We check that by
        // comparing value of the sequence parameters.
        ASSERT_TRUE(response1);
        ConstElementPtr sequence1 = response1->getJsonElement("sequence");
        ASSERT_TRUE(sequence1);

        ASSERT_TRUE(response2);
        ConstElementPtr sequence2 = response2->getJsonElement("sequence");
        ASSERT_TRUE(sequence2);

        EXPECT_NE(sequence1->intValue(), sequence2->intValue());
    }

    /// @brief Test that the client can communicate with two different
    /// destinations simultaneously.
    void testMultipleDestinations() {
        // Start two servers running on different ports.
        ASSERT_NO_THROW(listener_.start());
        ASSERT_NO_THROW(listener2_.start());

        // Create the client. It will be communicating with the two servers.
        HttpClient client(io_service_);

        // Specify the URLs on which the servers are available.
        Url url1("http://127.0.0.1:18123");
        Url url2("http://[::1]:18124");

        // Create a request to the first server.
        PostHttpRequestJsonPtr request1 = createRequest("sequence", 1);
        HttpResponseJsonPtr response1(new HttpResponseJson());
        unsigned resp_num = 0;
        ASSERT_NO_THROW(client.asyncSendRequest(url1, TlsContextPtr(),
                                                request1, response1,
            [this, &resp_num](const boost::system::error_code& ec,
                              const HttpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }
            EXPECT_FALSE(ec);
        }));

        // Create a request to the second server.
        PostHttpRequestJsonPtr request2 = createRequest("sequence", 2);
        HttpResponseJsonPtr response2(new HttpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url2, TlsContextPtr(),
                                                request2, response2,
            [this, &resp_num](const boost::system::error_code& ec,
                              const HttpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }
            EXPECT_FALSE(ec);
        }));

        // Actually trigger the requests.
        ASSERT_NO_THROW(runIOService());

        // Make sure we have received two different responses.
        ASSERT_TRUE(response1);
        ConstElementPtr sequence1 = response1->getJsonElement("sequence");
        ASSERT_TRUE(sequence1);

        ASSERT_TRUE(response2);
        ConstElementPtr sequence2 = response2->getJsonElement("sequence");
        ASSERT_TRUE(sequence2);

        EXPECT_NE(sequence1->intValue(), sequence2->intValue());
    }

    /// @brief Test that the client can communicate with the same destination
    /// address and port but with different TLS contexts so
    void testMultipleTlsContexts() {
        // Start only one server.
        ASSERT_NO_THROW(listener_.start());

        // Create the client.
        HttpClient client(io_service_);

        // Specify the URL on which the server is available.
        Url url("http://127.0.0.1:18123");

        // Create a request to the first server.
        PostHttpRequestJsonPtr request1 = createRequest("sequence", 1);
        HttpResponseJsonPtr response1(new HttpResponseJson());
        unsigned resp_num = 0;
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request1, response1,
            [this, &resp_num](const boost::system::error_code& ec,
                              const HttpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }
            if (ec) {
                ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
            }
        }));

        // Create a request with the second TLS context.
        PostHttpRequestJsonPtr request2 = createRequest("sequence", 2);
        HttpResponseJsonPtr response2(new HttpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request2, response2,
            [this, &resp_num](const boost::system::error_code& ec,
                              const HttpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }
            if (ec) {
                ADD_FAILURE() << "asyncSendRequest failed: " << ec.message();
            }
        }));

        // Actually trigger the requests.
        ASSERT_NO_THROW(runIOService());

        // Make sure we have received two different responses.
        ASSERT_TRUE(response1);
        ConstElementPtr sequence1 = response1->getJsonElement("sequence");
        ASSERT_TRUE(sequence1);

        ASSERT_TRUE(response2);
        ConstElementPtr sequence2 = response2->getJsonElement("sequence");
        ASSERT_TRUE(sequence2);

        EXPECT_NE(sequence1->intValue(), sequence2->intValue());
    }

    /// @brief Test that idle connection can be resumed for second request.
    void testIdleConnection() {
        // Start the server that has short idle timeout. It closes the idle
        // connection after 200ms.
        ASSERT_NO_THROW(listener3_.start());

        // Create the client that will communicate with this server.
        HttpClient client(io_service_);

        // Specify the URL of this server.
        Url url("http://127.0.0.1:18125");

        // Create the first request.
        PostHttpRequestJsonPtr request1 = createRequest("sequence", 1);
        HttpResponseJsonPtr response1(new HttpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request1, response1,
            [this](const boost::system::error_code& ec, const HttpResponsePtr&,
                   const std::string&) {
            io_service_.stop();
            EXPECT_FALSE(ec);
        }));

        // Run the IO service until the response is received.
        ASSERT_NO_THROW(runIOService());

        // Make sure the response has been received.
        ASSERT_TRUE(response1);
        ConstElementPtr sequence1 = response1->getJsonElement("sequence");
        ASSERT_TRUE(sequence1);

        // Delay the generation of the second request by 2x server idle timeout.
        // This should be enough to cause the server to close the connection.
        ASSERT_NO_THROW(runIOService(SHORT_IDLE_TIMEOUT * 2));

        // Create another request.
        PostHttpRequestJsonPtr request2 = createRequest("sequence", 2);
        HttpResponseJsonPtr response2(new HttpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request2, response2,
            [this](const boost::system::error_code& ec, const HttpResponsePtr&,
                   const std::string&) {
            io_service_.stop();
            EXPECT_FALSE(ec);
        }));

        // Actually trigger the second request.
        ASSERT_NO_THROW(runIOService());

        // Make sire that the server has responded.
        ASSERT_TRUE(response2);
        ConstElementPtr sequence2 = response2->getJsonElement("sequence");
        ASSERT_TRUE(sequence2);

        // Make sure that two different responses have been received.
        EXPECT_NE(sequence1->intValue(), sequence2->intValue());
    }

    /// @brief This test verifies that the client returns IO error code when the
    /// server is unreachable.
    void testUnreachable () {
        // Create the client.
        HttpClient client(io_service_);

        // Specify the URL of the server. This server is down.
        Url url("http://127.0.0.1:18123");

        // Create the request.
        PostHttpRequestJsonPtr request = createRequest("sequence", 1);
        HttpResponseJsonPtr response(new HttpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request, response,
            [this](const boost::system::error_code& ec,
                   const HttpResponsePtr&,
                   const std::string&) {
            io_service_.stop();
            // The server should have returned an IO error.
            EXPECT_TRUE(ec);
        }));

        // Actually trigger the request.
        ASSERT_NO_THROW(runIOService());
    }

    /// @brief Test that an error is returned by the client if the server
    /// response is malformed.
    void testMalformedResponse () {
        // Start the server.
        ASSERT_NO_THROW(listener_.start());

        // Create the client.
        HttpClient client(io_service_);

        // Specify the URL of the server.
        Url url("http://127.0.0.1:18123");

        // The response is going to be malformed in such a way that it holds
        // an invalid content type. We affect the content type by creating
        // a request that holds a JSON parameter requesting a specific
        // content type.
        PostHttpRequestJsonPtr request = createRequest("requested-content-type",
                                                       "text/html");
        HttpResponseJsonPtr response(new HttpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request, response,
            [this](const boost::system::error_code& ec,
                   const HttpResponsePtr& response,
                   const std::string& parsing_error) {
            io_service_.stop();
            // There should be no IO error (answer from the server is received).
            EXPECT_FALSE(ec);
            // The response object is NULL because it couldn't be finalized.
            EXPECT_FALSE(response);
            // The message parsing error should be returned.
            EXPECT_FALSE(parsing_error.empty());
        }));

        // Actually trigger the request.
        ASSERT_NO_THROW(runIOService());
    }

    /// @brief Test that client times out when it doesn't receive the entire
    /// response from the server within a desired time.
    void testClientRequestTimeout() {
        // Start the server.
        ASSERT_NO_THROW(listener_.start());

        // Create the client.
        HttpClient client(io_service_);

        // Specify the URL of the server.
        Url url("http://127.0.0.1:18123");

        unsigned cb_num = 0;

        // Create the request which asks the server to generate a partial
        // (although well formed) response. The client will be waiting for the
        // rest of the response to be provided and will eventually time out.
        PostHttpRequestJsonPtr request1 = createRequest("partial-response", true);
        HttpResponseJsonPtr response1(new HttpResponseJson());
        // This value will be set to true if the connection close callback is
        // invoked upon time out.
        auto connection_closed = false;
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request1, response1,
            [this, &cb_num](const boost::system::error_code& ec,
                            const HttpResponsePtr& response,
                            const std::string&) {
                if (++cb_num > 1) {
                    io_service_.stop();
                }
                // In this particular case we know exactly the type of the
                // IO error returned, because the client explicitly sets this
                // error code.
                EXPECT_TRUE(ec.value() == boost::asio::error::timed_out);
                // There should be no response returned.
                EXPECT_FALSE(response);
            },
            HttpClient::RequestTimeout(100),
            HttpClient::ConnectHandler(),
            HttpClient::HandshakeHandler(),
            [&connection_closed](const int) {
                // This callback is called when the connection gets closed
                // by the client.
                connection_closed = true;
            })
        );

        // Create another request after the timeout. It should be handled ok.
        PostHttpRequestJsonPtr request2 = createRequest("sequence", 1);
        HttpResponseJsonPtr response2(new HttpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request2, response2,
            [this, &cb_num](const boost::system::error_code& /*ec*/,
                            const HttpResponsePtr&,
                            const std::string&) {
                if (++cb_num > 1) {
                    io_service_.stop();
                }
            }));

        // Actually trigger the requests.
        ASSERT_NO_THROW(runIOService());
        // Make sure that the client has closed the connection upon timeout.
        EXPECT_TRUE(connection_closed);
    }

    /// @brief Test that client times out when connection takes too long.
    void testClientConnectTimeout() {
        // Start the server.
        ASSERT_NO_THROW(listener_.start());

        // Create the client.
        HttpClient client(io_service_);

        // Specify the URL of the server.
        Url url("http://127.0.0.1:18123");

        unsigned cb_num = 0;

        PostHttpRequestJsonPtr request = createRequest("sequence", 1);
        HttpResponseJsonPtr response(new HttpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request, response,
            [this, &cb_num](const boost::system::error_code& ec,
                            const HttpResponsePtr& response,
                            const std::string&) {
            if (++cb_num > 1) {
                io_service_.stop();
            }
            // In this particular case we know exactly the type of the
            // IO error returned, because the client explicitly sets this
            // error code.
            EXPECT_TRUE(ec.value() == boost::asio::error::timed_out);
            // There should be no response returned.
            EXPECT_FALSE(response);

        }, HttpClient::RequestTimeout(100),

           // This callback is invoked upon an attempt to connect to the
           // server. The false value indicates to the HttpClient to not
           // try to send a request to the server. This simulates the
           // case of connect() taking very long and should eventually
           // cause the transaction to time out.
           [](const boost::system::error_code& /*ec*/, int) {
               return (false);
        }));

        // Create another request after the timeout. It should be handled ok.
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request, response,
            [this, &cb_num](const boost::system::error_code& /*ec*/,
                            const HttpResponsePtr&,
                            const std::string&) {
                if (++cb_num > 1) {
                    io_service_.stop();
                }
            }));

        // Actually trigger the requests.
        ASSERT_NO_THROW(runIOService());
    }

    /// @brief Tests the behavior of the HTTP client when the premature
    /// timeout occurs.
    ///
    /// The premature timeout may occur when the system clock is moved
    /// during the transaction. This test simulates this behavior by
    /// starting new transaction and waiting for the timeout to occur
    /// before the IO service is ran. The timeout handler is invoked
    /// first and it resets the transaction state. This test verifies
    /// that the started transaction tears down gracefully after the
    /// transaction state is reset.
    ///
    /// There are two variants of this test. The first variant schedules
    /// one transaction before running the IO service. The second variant
    /// schedules two transactions prior to running the IO service. The
    /// second transaction is queued, so it is expected that it doesn't
    /// time out and it runs successfully.
    ///
    /// @param queue_two_requests Boolean value indicating if a single
    /// transaction should be queued (false), or two (true).
    void testClientRequestLateStart(const bool queue_two_requests) {
        // Start the server.
        ASSERT_NO_THROW(listener_.start());

        // Create the client.
        HttpClient client(io_service_);

        // Specify the URL of the server.
        Url url("http://127.0.0.1:18123");

        // Specify the TLS context of the server.
        TlsContextPtr tls_context;

        // Generate first request.
        PostHttpRequestJsonPtr request1 = createRequest("sequence", 1);
        HttpResponseJsonPtr response1(new HttpResponseJson());

        // Use very short timeout to make sure that it occurs before we actually
        // run the transaction.
        ASSERT_NO_THROW(client.asyncSendRequest(url, tls_context,
                                                request1, response1,
            [](const boost::system::error_code& ec,
               const HttpResponsePtr& response,
               const std::string&) {

            // In this particular case we know exactly the type of the
            // IO error returned, because the client explicitly sets this
            // error code.
            EXPECT_TRUE(ec.value() == boost::asio::error::timed_out);
            // There should be no response returned.
            EXPECT_FALSE(response);
        }, HttpClient::RequestTimeout(1)));

        if (queue_two_requests) {
            PostHttpRequestJsonPtr request2 = createRequest("sequence", 2);
            HttpResponseJsonPtr response2(new HttpResponseJson());
            ASSERT_NO_THROW(client.asyncSendRequest(url, tls_context,
                                                    request2, response2,
                [](const boost::system::error_code& ec,
                   const HttpResponsePtr& response,
                   const std::string&) {

                // This second request should be successful.
                EXPECT_TRUE(ec.value() == 0);
                EXPECT_TRUE(response);
            }));
        }

        // This waits for 3ms to make sure that the timeout occurs before we
        // run the transaction. This leads to an unusual situation that the
        // transaction state is reset as a result of the timeout but the
        // transaction is alive. We want to make sure that the client can
        // gracefully deal with this situation.
        usleep(3000);

        // Run the transaction and hope it will gracefully tear down.
        ASSERT_NO_THROW(runIOService(100));

        // Now try to send another request to make sure that the client
        // is healthy.
        PostHttpRequestJsonPtr request3 = createRequest("sequence", 3);
        HttpResponseJsonPtr response3(new HttpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request3, response3,
                         [this](const boost::system::error_code& ec,
                                const HttpResponsePtr&,
                                const std::string&) {
            io_service_.stop();

            // Everything should be ok.
            EXPECT_TRUE(ec.value() == 0);
        }));

        // Actually trigger the requests.
        ASSERT_NO_THROW(runIOService());
    }

    /// @brief Tests that underlying TCP socket can be registered and
    /// unregistered via connection and close callbacks.
    ///
    /// It conducts to consecutive requests over the same client.
    ///
    /// @param version HTTP version to be used.
    void testConnectCloseCallbacks(const HttpVersion& version) {
        // Start the server.
        ASSERT_NO_THROW(listener_.start());

        // Create a client and specify the URL on which the server can be reached.
        HttpClient client(io_service_);
        Url url("http://127.0.0.1:18123");

        // Initiate request to the server.
        PostHttpRequestJsonPtr request1 = createRequest("sequence", 1, version);
        HttpResponseJsonPtr response1(new HttpResponseJson());
        unsigned resp_num = 0;
        ExternalMonitor monitor;

        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request1, response1,
            [this, &resp_num](const boost::system::error_code& ec,
                              const HttpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }

            EXPECT_FALSE(ec);
        },
            HttpClient::RequestTimeout(10000),
            std::bind(&ExternalMonitor::connectHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::handshakeHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::closeHandler, &monitor, ph::_1)
        ));

        // Initiate another request to the destination.
        PostHttpRequestJsonPtr request2 = createRequest("sequence", 2, version);
        HttpResponseJsonPtr response2(new HttpResponseJson());
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request2, response2,
            [this, &resp_num](const boost::system::error_code& ec,
                              const HttpResponsePtr&,
                              const std::string&) {
            if (++resp_num > 1) {
                io_service_.stop();
            }
            EXPECT_FALSE(ec);
        },
            HttpClient::RequestTimeout(10000),
            std::bind(&ExternalMonitor::connectHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::handshakeHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::closeHandler, &monitor, ph::_1)
        ));

        // Actually trigger the requests. The requests should be handlded by the
        // server one after another. While the first request is being processed
        // the server should queue another one.
        ASSERT_NO_THROW(runIOService());

        // We should have had 2 connect invocations, no closes
        // and a valid registered fd
        EXPECT_EQ(2, monitor.connect_cnt_);
        EXPECT_EQ(0, monitor.close_cnt_);
        EXPECT_GT(monitor.registered_fd_, -1);

        // Make sure that the received responses are different. We check that by
        // comparing value of the sequence parameters.
        ASSERT_TRUE(response1);
        ConstElementPtr sequence1 = response1->getJsonElement("sequence");
        ASSERT_TRUE(sequence1);

        ASSERT_TRUE(response2);
        ConstElementPtr sequence2 = response2->getJsonElement("sequence");
        ASSERT_TRUE(sequence2);
        EXPECT_NE(sequence1->intValue(), sequence2->intValue());

        // Stopping the client the close the connection.
        client.stop();

        // We should have had 2 connect invocations, 1 closes
        // and an invalid registered fd
        EXPECT_EQ(2, monitor.connect_cnt_);
        EXPECT_EQ(1, monitor.close_cnt_);
        EXPECT_EQ(-1, monitor.registered_fd_);
    }

    /// @brief Tests detection and handling out-of-band socket events
    ///
    /// It initiates a transaction and verifies that a mid-transaction call
    /// to HttpClient::closeIfOutOfBand() has no affect on the connection.
    /// After successful completion of the transaction, a second call to
    /// HttpClient::closeIfOutOfBand() is made. This should result in the
    /// connection being closed.
    /// This step is repeated to verify that after an OOB closure, transactions
    /// to the same destination can be processed.
    ///
    /// Lastly, we verify that HttpClient::stop() closes the connection correctly.
    ///
    /// @param version HTTP version to be used.
    void testCloseIfOutOfBand(const HttpVersion& version) {
        // Start the server.
        ASSERT_NO_THROW(listener_.start());

        // Create a client and specify the URL on which the server can be reached.
        HttpClient client(io_service_);
        Url url("http://127.0.0.1:18123");

        // Initiate request to the server.
        PostHttpRequestJsonPtr request1 = createRequest("sequence", 1, version);
        HttpResponseJsonPtr response1(new HttpResponseJson());
        unsigned resp_num = 0;
        ExternalMonitor monitor;

        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request1, response1,
            [this, &client, &resp_num, &monitor](const boost::system::error_code& ec,
                              const HttpResponsePtr&,
                              const std::string&) {
            if (++resp_num == 1) {
                io_service_.stop();
            }

            EXPECT_EQ(1, monitor.connect_cnt_);      // We should have 1 connect.
            EXPECT_EQ(0, monitor.close_cnt_);        // We should have 0 closes
            ASSERT_GT(monitor.registered_fd_, -1);   // We should have a valid fd.
            int orig_fd = monitor.registered_fd_;

            // Test our socket for OOBness.
            client.closeIfOutOfBand(monitor.registered_fd_);

            // Since we're in a transaction, we should have no closes and
            // the same valid fd.
            EXPECT_EQ(0, monitor.close_cnt_);
            ASSERT_EQ(monitor.registered_fd_, orig_fd);

            EXPECT_FALSE(ec);
        },
            HttpClient::RequestTimeout(10000),
            std::bind(&ExternalMonitor::connectHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::handshakeHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::closeHandler, &monitor, ph::_1)
        ));

        // Actually trigger the requests. The requests should be handlded by the
        // server one after another. While the first request is being processed
        // the server should queue another one.
        ASSERT_NO_THROW(runIOService());

        // Make sure that we received a response.
        ASSERT_TRUE(response1);
        ConstElementPtr sequence1 = response1->getJsonElement("sequence");
        ASSERT_TRUE(sequence1);
        EXPECT_EQ(1, sequence1->intValue());

        // We should have had 1 connect invocations, no closes
        // and a valid registered fd
        EXPECT_EQ(1, monitor.connect_cnt_);
        EXPECT_EQ(0, monitor.close_cnt_);
        EXPECT_GT(monitor.registered_fd_, -1);

        // Test our socket for OOBness.
        client.closeIfOutOfBand(monitor.registered_fd_);

        // Since we're in a transaction, we should have no closes and
        // the same valid fd.
        EXPECT_EQ(1, monitor.close_cnt_);
        EXPECT_EQ(-1, monitor.registered_fd_);

        // Now let's do another request to the destination to verify that
        // we'll reopen the connection without issue.
        PostHttpRequestJsonPtr request2 = createRequest("sequence", 2, version);
        HttpResponseJsonPtr response2(new HttpResponseJson());
        resp_num = 0;
        ASSERT_NO_THROW(client.asyncSendRequest(url, TlsContextPtr(),
                                                request2, response2,
            [this, &client, &resp_num, &monitor](const boost::system::error_code& ec,
                              const HttpResponsePtr&,
                              const std::string&) {
            if (++resp_num == 1) {
                io_service_.stop();
            }

            EXPECT_EQ(2, monitor.connect_cnt_);      // We should have 1 connect.
            EXPECT_EQ(1, monitor.close_cnt_);        // We should have 0 closes
            ASSERT_GT(monitor.registered_fd_, -1);   // We should have a valid fd.
            int orig_fd = monitor.registered_fd_;

            // Test our socket for OOBness.
            client.closeIfOutOfBand(monitor.registered_fd_);

            // Since we're in a transaction, we should have no closes and
            // the same valid fd.
            EXPECT_EQ(1, monitor.close_cnt_);
            ASSERT_EQ(monitor.registered_fd_, orig_fd);

            EXPECT_FALSE(ec);
        },
            HttpClient::RequestTimeout(10000),
            std::bind(&ExternalMonitor::connectHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::handshakeHandler, &monitor, ph::_1, ph::_2),
            std::bind(&ExternalMonitor::closeHandler, &monitor, ph::_1)
        ));

        // Actually trigger the requests. The requests should be handlded by the
        // server one after another. While the first request is being processed
        // the server should queue another one.
        ASSERT_NO_THROW(runIOService());

        // Make sure that we received the second response.
        ASSERT_TRUE(response2);
        ConstElementPtr sequence2 = response2->getJsonElement("sequence");
        ASSERT_TRUE(sequence2);
        EXPECT_EQ(2, sequence2->intValue());

        // Stopping the client the close the connection.
        client.stop();

        // We should have had 2 connect invocations, 2 closes
        // and an invalid registered fd
        EXPECT_EQ(2, monitor.connect_cnt_);
        EXPECT_EQ(2, monitor.close_cnt_);
        EXPECT_EQ(-1, monitor.registered_fd_);
    }

    /// @brief Simulates external registery of Connection TCP sockets
    ///
    /// Provides methods compatible with Connection callbacks for connect
    /// and close operations.
    class ExternalMonitor {
    public:
        /// @brief Constructor
        ExternalMonitor()
            : registered_fd_(-1), connect_cnt_(0), close_cnt_(0) {
        }

        /// @brief Connect callback handler
        /// @param ec Error status of the ASIO connect
        /// @param tcp_native_fd socket descriptor to register
        bool connectHandler(const boost::system::error_code& ec, int tcp_native_fd) {
            ++connect_cnt_;
            if ((!ec || (ec.value() == boost::asio::error::in_progress))
                && (tcp_native_fd >= 0)) {
                registered_fd_ = tcp_native_fd;
                return (true);
            } else if ((ec.value() == boost::asio::error::already_connected)
                       && (registered_fd_ != tcp_native_fd)) {
                return (false);
            }

            // ec indicates an error, return true, so that error can be handled
            // by Connection logic.
            return (true);
        }

        /// @brief Handshake callback handler
        /// @param ec Error status of the ASIO connect
        bool handshakeHandler(const boost::system::error_code&, int) {
            ADD_FAILURE() << "handshake callback handler is called";
            // ec indicates an error, return true, so that error can be handled
            // by Connection logic.
            return (true);
        }

        /// @brief Close callback handler
        ///
        /// @param tcp_native_fd socket descriptor to register
        void closeHandler(int tcp_native_fd) {
            ++close_cnt_;
            EXPECT_EQ(tcp_native_fd, registered_fd_) << "closeHandler fd mismatch";
            if (tcp_native_fd >= 0) {
                registered_fd_ = -1;
            }
        }

        /// @brief Keeps track of socket currently "registered" for external monitoring.
        int registered_fd_;

        /// @brief Tracks how many times the connect callback is invoked.
        int connect_cnt_;

        /// @brief Tracks how many times the close callback is invoked.
        int close_cnt_;
    };

    /// @brief Instance of the listener used in the tests.
    HttpListener listener_;

    /// @brief Instance of the second listener used in the tests.
    HttpListener listener2_;

    /// @brief Instance of the third listener used in the tests (with short idle
    /// timeout).
    HttpListener listener3_;

};

// Test that two consecutive requests can be sent over the same (persistent)
// connection.
TEST_F(HttpClientTest, consecutiveRequests) {
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(HttpVersion(1, 1)));
}

// Test that two consecutive requests can be sent over the same (persistent)
// connection.
TEST_F(HttpClientTest, consecutiveRequestsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(HttpVersion(1, 1)));
}

// Test that two consecutive requests can be sent over non-persistent connection.
// This is achieved by sending HTTP/1.0 requests, which are non-persistent by
// default. The client should close the connection right after receiving a response
// from the server.
TEST_F(HttpClientTest, closeBetweenRequests) {
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(HttpVersion(1, 0)));
}

// Test that two consecutive requests can be sent over non-persistent connection.
// This is achieved by sending HTTP/1.0 requests, which are non-persistent by
// default. The client should close the connection right after receiving a response
// from the server.
TEST_F(HttpClientTest, closeBetweenRequestsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(HttpVersion(1, 0)));
}

// Test that the client can communicate with two different destinations
// simultaneously.
TEST_F(HttpClientTest, multipleDestinations) {
    ASSERT_NO_FATAL_FAILURE(testMultipleDestinations());
}

// Test that the client can communicate with two different destinations
// simultaneously.
TEST_F(HttpClientTest, multipleDestinationsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testMultipleDestinations());
}

// Test that the client can use two different TLS contexts to the same
// destination address and port simultaneously.
TEST_F(HttpClientTest, multipleTlsContexts) {
    ASSERT_NO_FATAL_FAILURE(testMultipleTlsContexts());
}

// Test that the client can use two different TLS contexts to the same
// destination address and port simultaneously.
TEST_F(HttpClientTest, multipleTlsContextsMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testMultipleTlsContexts());
}

// Test that idle connection can be resumed for second request.
TEST_F(HttpClientTest, idleConnection) {
    ASSERT_NO_FATAL_FAILURE(testIdleConnection());
}

// Test that idle connection can be resumed for second request.
TEST_F(HttpClientTest, idleConnectionMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testIdleConnection());
}

// This test verifies that the client returns IO error code when the
// server is unreachable.
TEST_F(HttpClientTest, unreachable) {
    ASSERT_NO_FATAL_FAILURE(testUnreachable());
}

// This test verifies that the client returns IO error code when the
// server is unreachable.
TEST_F(HttpClientTest, unreachableMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testUnreachable());
}

// Test that an error is returned by the client if the server response is
// malformed.
TEST_F(HttpClientTest, malformedResponse) {
    ASSERT_NO_FATAL_FAILURE(testMalformedResponse());
}

// Test that an error is returned by the client if the server response is
// malformed.
TEST_F(HttpClientTest, malformedResponseMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testMalformedResponse());
}

// Test that client times out when it doesn't receive the entire response
// from the server within a desired time.
TEST_F(HttpClientTest, clientRequestTimeout) {
    ASSERT_NO_FATAL_FAILURE(testClientRequestTimeout());
}

// Test that client times out when it doesn't receive the entire response
// from the server within a desired time.
TEST_F(HttpClientTest, clientRequestTimeoutMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testClientRequestTimeout());
}

// This test verifies the behavior of the HTTP client when the premature
// (and unexpected) timeout occurs. The premature timeout may be caused
// by the system clock move.
TEST_F(HttpClientTest, clientRequestLateStartNoQueue) {
    testClientRequestLateStart(false);
}

// This test verifies the behavior of the HTTP client when the premature
// (and unexpected) timeout occurs. The premature timeout may be caused
// by the system clock move.
TEST_F(HttpClientTest, clientRequestLateStartNoQueueMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testClientRequestLateStart(false);
}

// This test verifies the behavior of the HTTP client when the premature
// timeout occurs and there are requests queued after the request which
// times out.
TEST_F(HttpClientTest, clientRequestLateStartQueue) {
    testClientRequestLateStart(true);
}

// This test verifies the behavior of the HTTP client when the premature
// timeout occurs and there are requests queued after the request which
// times out.
TEST_F(HttpClientTest, clientRequestLateStartQueueMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    testClientRequestLateStart(true);
}

// Test that client times out when connection takes too long.
TEST_F(HttpClientTest, clientConnectTimeout) {
    ASSERT_NO_FATAL_FAILURE(testClientConnectTimeout());
}

// Test that client times out when connection takes too long.
TEST_F(HttpClientTest, clientConnectTimeoutMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testClientConnectTimeout());
}

/// Tests that connect and close callbacks work correctly.
TEST_F(HttpClientTest, connectCloseCallbacks) {
    ASSERT_NO_FATAL_FAILURE(testConnectCloseCallbacks(HttpVersion(1, 1)));
}

/// Tests that connect and close callbacks work correctly.
TEST_F(HttpClientTest, connectCloseCallbacksMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testConnectCloseCallbacks(HttpVersion(1, 1)));
}

/// Tests that HttpClient::closeIfOutOfBand works correctly.
TEST_F(HttpClientTest, closeIfOutOfBand) {
    ASSERT_NO_FATAL_FAILURE(testCloseIfOutOfBand(HttpVersion(1, 1)));
}

/// Tests that HttpClient::closeIfOutOfBand works correctly.
TEST_F(HttpClientTest, closeIfOutOfBandMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    ASSERT_NO_FATAL_FAILURE(testCloseIfOutOfBand(HttpVersion(1, 1)));
}

}
