// Copyright (C) 2017-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_SERVER_TEST_H
#define HTTP_SERVER_TEST_H

namespace isc {
namespace http {
namespace test {

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

    HttpListenerImplCustom(const IOServicePtr& io_service,
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
    HttpListenerCustom(const IOServicePtr& io_service,
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
    HttpConnectionLongWriteBuffer(const IOServicePtr& io_service,
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
    HttpConnectionTransactionChange(const IOServicePtr& io_service,
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

/// @brief Pointer to the TestHttp[s]Client.
typedef boost::shared_ptr<BaseTestHttpClient> TestClientPtr;

/// @brief Test fixture class for @ref HttpListener.
class BaseListenerTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Starts test timer which detects timeouts.
    BaseListenerTest()
        : io_service_(new IOService()), factory_(new TestHttpResponseCreatorFactory()),
          test_timer_(io_service_), run_io_service_timer_(io_service_),
          clients_(), server_context_() {
        test_timer_.setup(std::bind(&BaseListenerTest::timeoutHandler,
                                    this, true),
                          TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
    }

    /// @brief Destructor.
    ///
    /// Removes active HTTP clients.
    virtual ~BaseListenerTest() {
        for (auto const& client : clients_) {
            client->close();
        }
        test_timer_.cancel();
        io_service_->stopAndPoll();
    }

    /// brief Create a HTTP test client.
    virtual TestClientPtr createClient() = 0;

    /// @brief Connect to the endpoint.
    ///
    /// This method creates TestHttpClient instance and retains it in the clients_
    /// list.
    ///
    /// @param request String containing the HTTP request to be sent.
    void startRequest(const std::string& request) {
        auto client = createClient();
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
        io_service_->stop();
    }

    /// @brief Runs IO service with optional timeout.
    ///
    /// @param timeout Optional value specifying for how long the io service
    /// should be ran.
    void runIOService(long timeout = 0) {
        io_service_->stop();
        io_service_->restart();

        if (timeout > 0) {
            run_io_service_timer_.setup(std::bind(&BaseListenerTest::timeoutHandler,
                                                  this, false),
                                        timeout, IntervalTimer::ONE_SHOT);
        }
        io_service_->run();
        io_service_->stopAndPoll(false);
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
                              SERVER_PORT, server_context_,
                              factory_, HttpListener::RequestTimeout(1000),
                              HttpListener::IdleTimeout(IDLE_TIMEOUT));
        ASSERT_NO_THROW(listener.start());
        ASSERT_NO_THROW(startRequest(request));
        ASSERT_NO_THROW(runIOService());
        ASSERT_EQ(1, clients_.size());
        auto client = *clients_.begin();
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
                     server_context_, factory_,
                     HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                     HttpListener::IdleTimeout(IDLE_TIMEOUT));

        ASSERT_NO_THROW(listener.start());

        // Send the request.
        ASSERT_NO_THROW(startRequest(request));

        // Injecting unexpected data should not result in an exception.
        ASSERT_NO_THROW(runIOService());

        ASSERT_EQ(1, clients_.size());
        auto client = *clients_.begin();
        ASSERT_TRUE(client);
        EXPECT_EQ(httpOk(HttpVersion::HTTP_11()), client->getResponse());
    }

    /// @brief Verify that HTTP connection can be established and used to
    /// transmit HTTP request and receive a response.
    void testListen() {
        const std::string request = "POST /foo/bar HTTP/1.1\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: 3\r\n\r\n"
            "{ }";

        HttpListener listener(io_service_,
                              IOAddress(SERVER_ADDRESS),
                              SERVER_PORT,
                              server_context_,
                              factory_,
                              HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                              HttpListener::IdleTimeout(IDLE_TIMEOUT));
        ASSERT_NO_THROW(listener.start());
        ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
        ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
        ASSERT_NO_THROW(startRequest(request));
        ASSERT_NO_THROW(runIOService());
        ASSERT_EQ(1, clients_.size());
        auto client = *clients_.begin();
        ASSERT_TRUE(client);
        EXPECT_EQ(httpOk(HttpVersion::HTTP_11()), client->getResponse());

        listener.stop();
        io_service_->poll();
    }

    /// @brief Verify that persistent HTTP connection can be established when
    /// no "Connection: Keep-Alive" header value is specified.
    void testKeepAlive() {
        // The first request contains the keep-alive header which
        // instructs the server to maintain the TCP connection after
        // sending a response.
        std::string request = "POST /foo/bar HTTP/1.0\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: 3\r\n"
            "Connection: Keep-Alive\r\n\r\n"
            "{ }";

        HttpListener listener(io_service_,
                              IOAddress(SERVER_ADDRESS),
                              SERVER_PORT,
                              server_context_,
                              factory_,
                              HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                              HttpListener::IdleTimeout(IDLE_TIMEOUT));

        ASSERT_NO_THROW(listener.start());

        // Send the request with the keep-alive header.
        ASSERT_NO_THROW(startRequest(request));
        ASSERT_NO_THROW(runIOService());
        ASSERT_EQ(1, clients_.size());
        auto client = *clients_.begin();
        ASSERT_TRUE(client);
        EXPECT_EQ(httpOk(HttpVersion::HTTP_10()), client->getResponse());

        // We have sent keep-alive header so we expect that the connection with
        // the server remains active.
        ASSERT_TRUE(client->isConnectionAlive());

        // Test that we can send another request via the same connection.
        // This time it lacks the keep-alive header, so the server should
        // close the connection after sending the response.
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
        io_service_->poll();
    }

    /// @brief Verify that persistent HTTP connection is established by default
    /// when HTTP/1.1 is in use.
    void testPersistentConnection() {
        // The HTTP/1.1 requests are by default persistent.
        std::string request = "POST /foo/bar HTTP/1.1\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: 3\r\n\r\n"
            "{ }";

        HttpListener listener(io_service_,
                              IOAddress(SERVER_ADDRESS),
                              SERVER_PORT,
                              server_context_,
                              factory_,
                              HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                              HttpListener::IdleTimeout(IDLE_TIMEOUT));

        ASSERT_NO_THROW(listener.start());

        // Send the first request.
        ASSERT_NO_THROW(startRequest(request));
        ASSERT_NO_THROW(runIOService());
        ASSERT_EQ(1, clients_.size());
        auto client = *clients_.begin();
        ASSERT_TRUE(client);
        EXPECT_EQ(httpOk(HttpVersion::HTTP_11()), client->getResponse());

        // HTTP/1.1 connection is persistent by default.
        ASSERT_TRUE(client->isConnectionAlive());

        // Test that we can send another request via the same connection.
        // This time it includes the "Connection: close"  header which
        // instructs the server to close the connection after responding.
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
        io_service_->poll();
    }

    /// @brief Verify that "keep-alive" connection is closed by the server
    /// after an idle time.
    void testKeepAliveTimeout() {

        // The first request contains the keep-alive header which
        // instructs the server to maintain the TCP connection after
        // sending a response.
        std::string request = "POST /foo/bar HTTP/1.0\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: 3\r\n"
            "Connection: Keep-Alive\r\n\r\n"
            "{ }";

        // Specify the idle timeout of 500ms.
        HttpListener listener(io_service_,
                              IOAddress(SERVER_ADDRESS),
                              SERVER_PORT,
                              server_context_,
                              factory_,
                              HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                              HttpListener::IdleTimeout(500));

        ASSERT_NO_THROW(listener.start());

        // Send the request with the keep-alive header.
        ASSERT_NO_THROW(startRequest(request));
        ASSERT_NO_THROW(runIOService());
        ASSERT_EQ(1, clients_.size());
        auto client = *clients_.begin();
        ASSERT_TRUE(client);
        EXPECT_EQ(httpOk(HttpVersion::HTTP_10()), client->getResponse());

        // We have sent keep-alive header so we expect that the connection with
        // the server remains active.
        ASSERT_TRUE(client->isConnectionAlive());

        // Run IO service for 1000ms. The idle time is set to 500ms, so
        // the connection should be closed by the server while we wait here.
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
        io_service_->poll();
    }

    /// @brief Verify that persistent connection is closed by the server after
    /// an idle time.
    void testPersistentConnectionTimeout() {
        // The HTTP/1.1 requests are by default persistent.
        std::string request = "POST /foo/bar HTTP/1.1\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: 3\r\n\r\n"
            "{ }";

        // Specify the idle timeout of 500ms.
        HttpListener listener(io_service_,
                              IOAddress(SERVER_ADDRESS),
                              SERVER_PORT,
                              server_context_,
                              factory_,
                              HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                              HttpListener::IdleTimeout(500));

        ASSERT_NO_THROW(listener.start());

        // Send the request.
        ASSERT_NO_THROW(startRequest(request));
        ASSERT_NO_THROW(runIOService());
        ASSERT_EQ(1, clients_.size());
        auto client = *clients_.begin();
        ASSERT_TRUE(client);
        EXPECT_EQ(httpOk(HttpVersion::HTTP_11()), client->getResponse());

        // The connection should remain active.
        ASSERT_TRUE(client->isConnectionAlive());

        // Run IO service for 1000ms. The idle time is set to 500ms, so
        // the connection should be closed by the server while we wait here.
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
        io_service_->poll();
    }

    /// @brief Verify that HTTP/1.1 connection remains open even if there is an
    /// error in the message body.
    void testPersistentConnectionBadBody() {
        // The HTTP/1.1 requests are by default persistent.
        std::string request = "POST /foo/bar HTTP/1.1\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: 12\r\n\r\n"
            "{ \"a\": abc }";

        HttpListener listener(io_service_,
                              IOAddress(SERVER_ADDRESS),
                              SERVER_PORT,
                              server_context_,
                              factory_,
                              HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                              HttpListener::IdleTimeout(IDLE_TIMEOUT));

        ASSERT_NO_THROW(listener.start());

        // Send the request.
        ASSERT_NO_THROW(startRequest(request));
        ASSERT_NO_THROW(runIOService());
        ASSERT_EQ(1, clients_.size());
        auto client = *clients_.begin();
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
        io_service_->poll();
    }

    /// @brief Verify that Bad Request status is returned when the request
    /// is malformed.
    void testBadRequest() {
        // Content-Type is wrong. This should result in Bad Request status.
        const std::string request = "POST /foo/bar HTTP/1.1\r\n"
            "Content-Type: foo\r\n"
            "Content-Length: 3\r\n\r\n"
            "{ }";

        HttpListener listener(io_service_,
                              IOAddress(SERVER_ADDRESS),
                              SERVER_PORT,
                              server_context_,
                              factory_,
                              HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                              HttpListener::IdleTimeout(IDLE_TIMEOUT));
        ASSERT_NO_THROW(listener.start());
        ASSERT_NO_THROW(startRequest(request));
        ASSERT_NO_THROW(runIOService());
        ASSERT_EQ(1, clients_.size());
        auto client = *clients_.begin();
        ASSERT_TRUE(client);
        EXPECT_EQ("HTTP/1.1 400 Bad Request\r\n"
                  "Content-Length: 40\r\n"
                  "Content-Type: application/json\r\n"
                  "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
                  "\r\n"
                  "{ \"result\": 400, \"text\": \"Bad Request\" }",
                  client->getResponse());
    }

    /// @brief IO service used in the tests.
    IOServicePtr io_service_;

    /// @brief Pointer to the response creator factory.
    HttpResponseCreatorFactoryPtr factory_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Asynchronous timer for running IO service for a specified amount
    /// of time.
    IntervalTimer run_io_service_timer_;

    /// @brief List of client connections.
    std::list<TestClientPtr> clients_;

    /// @brief Server TLS context.
    TlsContextPtr server_context_;
};

}
}
}
#endif // HTTP_SERVER_TEST_H
