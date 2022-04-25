// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
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

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace isc::asiolink;
using namespace isc::asiolink::test;
using namespace isc::data;
using namespace isc::http;
using namespace isc::http::test;
using namespace isc::util;
namespace ph = std::placeholders;

/// @todo: put the common part of client and server tests in its own file(s).

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
        TlsContextPtr tls_context;
        configClient(tls_context);
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
    /// @param tls_context TLS context.
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


/// @brief Entity which can connect to the HTTP server endpoint.
class TestHttpClient : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// This constructor creates new socket instance. It doesn't connect. Call
    /// connect() to connect to the server.
    ///
    /// @param io_service IO service to be stopped on error.
    /// @param tls_context TLS context.
    TestHttpClient(IOService& io_service, TlsContextPtr tls_context)
        : io_service_(io_service.get_io_service()),
          stream_(io_service_, tls_context->getContext()),
          buf_(), response_() {
    }

    /// @brief Destructor.
    ///
    /// Closes the underlying socket if it is open.
    ~TestHttpClient() {
        close();
    }

    /// @brief Send HTTP request specified in textual format.
    ///
    /// @param request HTTP request in the textual format.
    void startRequest(const std::string& request) {
        tcp::endpoint endpoint(address::from_string(SERVER_ADDRESS),
                               SERVER_PORT);
        stream_.lowest_layer().async_connect(endpoint,
        [this, request](const boost::system::error_code& ec) {
            if (ec) {
                // One would expect that async_connect wouldn't return
                // EINPROGRESS error code, but simply wait for the connection
                // to get established before the handler is invoked. It turns out,
                // however, that on some OSes the connect handler may receive this
                // error code which doesn't necessarily indicate a problem.
                // Making an attempt to write and read from this socket will
                // typically succeed. So, we ignore this error.
                if (ec.value() != boost::asio::error::in_progress) {
                    ADD_FAILURE() << "error occurred while connecting: "
                                  << ec.message();
                    io_service_.stop();
                    return;
                }
            }
            stream_.async_handshake(roleToImpl(TlsRole::CLIENT),
            [this, request](const boost::system::error_code& ec) {
                if (ec) {
                    ADD_FAILURE() << "error occurred during handshake: "
                                  << ec.message();
                    io_service_.stop();
                    return;
                }
                sendRequest(request);
            });
        });
    }

    /// @brief Send HTTP request.
    ///
    /// @param request HTTP request in the textual format.
    void sendRequest(const std::string& request) {
        sendPartialRequest(request);
    }

    /// @brief Send part of the HTTP request.
    ///
    /// @param request part of the HTTP request to be sent.
    void sendPartialRequest(std::string request) {
        boost::asio::async_write(stream_,
                boost::asio::buffer(request.data(), request.size()),
                [this, request](const boost::system::error_code& ec,
                                std::size_t bytes_transferred) mutable {
            if (ec) {
                if (ec.value() == boost::asio::error::operation_aborted) {
                    return;

                } else if ((ec.value() == boost::asio::error::try_again) ||
                           (ec.value() == boost::asio::error::would_block)) {
                    // If we should try again make sure there is no garbage in the
                    // bytes_transferred.
                    bytes_transferred = 0;

                } else {
                    ADD_FAILURE() << "error occurred while connecting: "
                                  << ec.message();
                    io_service_.stop();
                    return;
                }
            }

            // Remove the part of the request which has been sent.
            if (bytes_transferred > 0 && (request.size() <= bytes_transferred)) {
                request.erase(0, bytes_transferred);
            }

            // Continue sending request data if there are still some data to be
            // sent.
            if (!request.empty()) {
                sendPartialRequest(request);

            } else {
                // Request has been sent. Start receiving response.
                response_.clear();
                receivePartialResponse();
            }
       });
    }

    /// @brief Receive response from the server.
    void receivePartialResponse() {
        stream_.async_read_some(boost::asio::buffer(buf_.data(), buf_.size()),
                                [this](const boost::system::error_code& ec,
                                       std::size_t bytes_transferred) {
            if (ec) {
                // IO service stopped so simply return.
                if (ec.value() == boost::asio::error::operation_aborted) {
                    return;

                } else if ((ec.value() == boost::asio::error::try_again) ||
                           (ec.value() == boost::asio::error::would_block)) {
                    // If we should try again, make sure that there is no garbage
                    // in the bytes_transferred.
                    bytes_transferred = 0;

                } else {
                    // Error occurred, bail...
                    ADD_FAILURE() << "error occurred while receiving HTTP"
                        " response from the server: " << ec.message();
                    io_service_.stop();
                }
            }

            if (bytes_transferred > 0) {
                response_.insert(response_.end(), buf_.data(),
                                 buf_.data() + bytes_transferred);
            }

            // Two consecutive new lines end the part of the response we're
            // expecting.
            if (response_.find("\r\n\r\n", 0) != std::string::npos) {
                io_service_.stop();

            } else {
                receivePartialResponse();
            }

        });
    }

    /// @brief Checks if the TCP connection is still open.
    ///
    /// Tests the TCP connection by trying to read from the socket.
    /// Unfortunately expected failure depends on a race between the read
    /// and the other side close so to check if the connection is closed
    /// please use @c isConnectionClosed instead.
    ///
    /// @return true if the TCP connection is open.
    bool isConnectionAlive() {
        // Remember the current non blocking setting.
        const bool non_blocking_orig = stream_.lowest_layer().non_blocking();
        // Set the socket to non blocking mode. We're going to test if the socket
        // returns would_block status on the attempt to read from it.
        stream_.lowest_layer().non_blocking(true);

        // We need to provide a buffer for a call to read.
        char data[2];
        boost::system::error_code ec;
        boost::asio::read(stream_, boost::asio::buffer(data, sizeof(data)), ec);

        // Revert the original non_blocking flag on the socket.
        stream_.lowest_layer().non_blocking(non_blocking_orig);

        // If the connection is alive we'd typically get would_block status code.
        // If there are any data that haven't been read we may also get success
        // status. We're guessing that try_again may also be returned by some
        // implementations in some situations. Any other error code indicates a
        // problem with the connection so we assume that the connection has been
        // closed.
        return (!ec || (ec.value() == boost::asio::error::try_again) ||
                (ec.value() == boost::asio::error::would_block));
    }

    /// @brief Checks if the TCP connection is already closed.
    ///
    /// Tests the TCP connection by trying to read from the socket.
    /// The read can block so this must be used to check if a connection
    /// is alive so to check if the connection is alive please always
    /// use @c isConnectionAlive.
    ///
    /// @return true if the TCP connection is closed.
    bool isConnectionClosed() {
        // Remember the current non blocking setting.
        const bool non_blocking_orig = stream_.lowest_layer().non_blocking();
        // Set the socket to blocking mode. We're going to test if the socket
        // returns eof status on the attempt to read from it.
        stream_.lowest_layer().non_blocking(false);

        // We need to provide a buffer for a call to read.
        char data[2];
        boost::system::error_code ec;
        boost::asio::read(stream_, boost::asio::buffer(data, sizeof(data)), ec);

        // Revert the original non_blocking flag on the socket.
        stream_.lowest_layer().non_blocking(non_blocking_orig);

        // If the connection is closed we'd typically get eof or
        // stream_truncated status code.
        return ((ec.value() == boost::asio::error::eof) ||
                (ec.value() == STREAM_TRUNCATED));
    }

    /// @brief Close connection.
    void close() {
        stream_.lowest_layer().close();
    }

    std::string getResponse() const {
        return (response_);
    }

private:

    /// @brief Holds reference to the IO service.
    boost::asio::io_service& io_service_;

    /// @brief A socket used for the connection.
    TlsStreamImpl stream_;

    /// @brief Buffer into which response is written.
    std::array<char, 8192> buf_;

    /// @brief Response in the textual format.
    std::string response_;
};

/// @brief Pointer to the TestHttpClient.
typedef boost::shared_ptr<TestHttpClient> TestHttpClientPtr;

/// @brief Test fixture class for @ref HttpListener.
class HttpsListenerTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Starts test timer which detects timeouts.
    HttpsListenerTest()
        : io_service_(), factory_(new TestHttpResponseCreatorFactory()),
          test_timer_(io_service_), run_io_service_timer_(io_service_),
          clients_(), server_context_(), client_context_() {
        configServer(server_context_);
        configClient(client_context_);
        test_timer_.setup(std::bind(&HttpsListenerTest::timeoutHandler, this, true),
                          TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
    }

    /// @brief Destructor.
    ///
    /// Removes active HTTP clients.
    virtual ~HttpsListenerTest() {
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
        TestHttpClientPtr client(new TestHttpClient(io_service_,
                                                    client_context_));
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
            run_io_service_timer_.setup(std::bind(&HttpsListenerTest::timeoutHandler,
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
                              SERVER_PORT, server_context_,
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
                     server_context_, factory_,
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

    /// @brief Server TLS context.
    TlsContextPtr server_context_;

    /// @brief Client TLS context.
    TlsContextPtr client_context_;
};

// This test verifies that HTTP connection can be established and used to
// transmit HTTP request and receive a response.
TEST_F(HttpsListenerTest, listen) {
    const std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          server_context_, factory_,
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
TEST_F(HttpsListenerTest, keepAlive) {

    // The first request contains the keep-alive header which instructs the server
    // to maintain the TCP connection after sending a response.
    std::string request = "POST /foo/bar HTTP/1.0\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n"
        "Connection: Keep-Alive\r\n\r\n"
        "{ }";

    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          server_context_, factory_,
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
TEST_F(HttpsListenerTest, persistentConnection) {

    // The HTTP/1.1 requests are by default persistent.
    std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          server_context_, factory_,
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
TEST_F(HttpsListenerTest, keepAliveTimeout) {

    // The first request contains the keep-alive header which instructs the server
    // to maintain the TCP connection after sending a response.
    std::string request = "POST /foo/bar HTTP/1.0\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n"
        "Connection: Keep-Alive\r\n\r\n"
        "{ }";

    // Specify the idle timeout of 500ms.
    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          server_context_, factory_,
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
TEST_F(HttpsListenerTest, persistentConnectionTimeout) {

    // The HTTP/1.1 requests are by default persistent.
    std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    // Specify the idle timeout of 500ms.
    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          server_context_, factory_,
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
TEST_F(HttpsListenerTest, persistentConnectionBadBody) {

    // The HTTP/1.1 requests are by default persistent.
    std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 12\r\n\r\n"
        "{ \"a\": abc }";

    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          server_context_, factory_,
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
TEST_F(HttpsListenerTest, startTwice) {
    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          server_context_, factory_,
                          HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                          HttpListener::IdleTimeout(IDLE_TIMEOUT));
    ASSERT_NO_THROW(listener.start());
    EXPECT_THROW(listener.start(), HttpListenerError);
}

// This test verifies that Bad Request status is returned when the request
// is malformed.
TEST_F(HttpsListenerTest, badRequest) {
    // Content-Type is wrong. This should result in Bad Request status.
    const std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: foo\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          server_context_, factory_,
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
TEST_F(HttpsListenerTest, invalidFactory) {
    EXPECT_THROW(HttpListener(io_service_, IOAddress(SERVER_ADDRESS),
                              SERVER_PORT, server_context_,
                              HttpResponseCreatorFactoryPtr(),
                              HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                              HttpListener::IdleTimeout(IDLE_TIMEOUT)),
                 HttpListenerError);
}

// This test verifies that the timeout of 0 can't be specified for the
// Request Timeout.
TEST_F(HttpsListenerTest, invalidRequestTimeout) {
    EXPECT_THROW(HttpListener(io_service_, IOAddress(SERVER_ADDRESS),
                              SERVER_PORT, server_context_, factory_,
                              HttpListener::RequestTimeout(0),
                              HttpListener::IdleTimeout(IDLE_TIMEOUT)),
                 HttpListenerError);
}

// This test verifies that the timeout of 0 can't be specified for the
// idle persistent connection timeout.
TEST_F(HttpsListenerTest, invalidIdleTimeout) {
    EXPECT_THROW(HttpListener(io_service_, IOAddress(SERVER_ADDRESS),
                              SERVER_PORT, server_context_, factory_,
                              HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                              HttpListener::IdleTimeout(0)),
                 HttpListenerError);
}

// This test verifies that listener can't be bound to the port to which
// other server is bound.
TEST_F(HttpsListenerTest, addressInUse) {
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
                          SERVER_PORT + 1, server_context_, factory_,
                          HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                          HttpListener::IdleTimeout(IDLE_TIMEOUT));
    EXPECT_THROW(listener.start(), HttpListenerError);
}

// This test verifies that HTTP Request Timeout status is returned as
// expected when the read part of the request contains the HTTP
// version number. The timeout response should contain the same
// HTTP version number as the partial request.
TEST_F(HttpsListenerTest, requestTimeoutHttpVersionFound) {
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
TEST_F(HttpsListenerTest, requestTimeoutHttpVersionNotFound) {
    // The part of the request specified here is correct but it is not
    // a complete request.
    const std::string request = "POST /foo/bar HTTP";

    testRequestTimeout(request, HttpVersion::HTTP_10());
}

// This test verifies that injecting length value greater than the
// output buffer length to the socket write callback does not cause
// an exception.
TEST_F(HttpsListenerTest, tooLongWriteBuffer) {
    testWriteBufferIssues<HttpConnectionLongWriteBuffer>();
}

// This test verifies that changing the transaction before calling
// the socket write callback does not cause an exception.
TEST_F(HttpsListenerTest, transactionChangeDuringWrite) {
    testWriteBufferIssues<HttpConnectionTransactionChange>();
}

}
