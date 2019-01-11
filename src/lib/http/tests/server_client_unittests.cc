// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <cc/data.h>
#include <http/client.h>
#include <http/http_types.h>
#include <http/listener.h>
#include <http/post_request_json.h>
#include <http/response_creator.h>
#include <http/response_creator_factory.h>
#include <http/response_json.h>
#include <http/tests/response_test.h>
#include <http/url.h>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
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
    createDynamicHttpResponse(const ConstHttpRequestPtr& request) {
        // Request must always be JSON.
        ConstPostHttpRequestJsonPtr request_json =
            boost::dynamic_pointer_cast<const PostHttpRequestJson>(request);
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

/// @brief Entity which can connect to the HTTP server endpoint.
class TestHttpClient : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// This constructor creates new socket instance. It doesn't connect. Call
    /// connect() to connect to the server.
    ///
    /// @param io_service IO service to be stopped on error.
    explicit TestHttpClient(IOService& io_service)
        : io_service_(io_service.get_io_service()), socket_(io_service_),
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
        socket_.async_connect(endpoint,
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
            sendRequest(request);
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
        socket_.async_send(boost::asio::buffer(request.data(), request.size()),
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
        socket_.async_read_some(boost::asio::buffer(buf_.data(), buf_.size()),
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
    ///
    /// @return true if the TCP connection is open.
    bool isConnectionAlive() {
        // Remember the current non blocking setting.
        const bool non_blocking_orig = socket_.non_blocking();
        // Set the socket to non blocking mode. We're going to test if the socket
        // returns would_block status on the attempt to read from it.
        socket_.non_blocking(true);

        // We need to provide a buffer for a call to read.
        char data[2];
        boost::system::error_code ec;
        boost::asio::read(socket_, boost::asio::buffer(data, sizeof(data)), ec);

        // Revert the original non_blocking flag on the socket.
        socket_.non_blocking(non_blocking_orig);

        // If the connection is alive we'd typically get would_block status code.
        // If there are any data that haven't been read we may also get success
        // status. We're guessing that try_again may also be returned by some
        // implementations in some situations. Any other error code indicates a
        // problem with the connection so we assume that the connection has been
        // closed.
        return (!ec || (ec.value() == boost::asio::error::try_again) ||
                (ec.value() == boost::asio::error::would_block));
    }

    /// @brief Close connection.
    void close() {
        socket_.close();
    }

    std::string getResponse() const {
        return (response_);
    }

private:

    /// @brief Holds reference to the IO service.
    boost::asio::io_service& io_service_;

    /// @brief A socket used for the connection.
    boost::asio::ip::tcp::socket socket_;

    /// @brief Buffer into which response is written.
    std::array<char, 8192> buf_;

    /// @brief Response in the textual format.
    std::string response_;
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
        test_timer_.setup(boost::bind(&HttpListenerTest::timeoutHandler, this, true),
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
            run_io_service_timer_.setup(boost::bind(&HttpListenerTest::timeoutHandler,
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
            "Content-Length: 4\r\n"
            "Content-Type: application/json\r\n"
            "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
            "\r\n"
            "{  }";
        return (s.str());
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
                          factory_, HttpListener::RequestTimeout(REQUEST_TIMEOUT),
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
// "Conection: Keep-Alive" header value is specified.
TEST_F(HttpListenerTest, keepAlive) {

    // The first request contains the keep-alive header which instructs the server
    // to maintain the TCP connection after sending a response.
    std::string request = "POST /foo/bar HTTP/1.0\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n"
        "Connection: Keep-Alive\r\n\r\n"
        "{ }";

    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          factory_, HttpListener::RequestTimeout(REQUEST_TIMEOUT),
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
    EXPECT_FALSE(client->isConnectionAlive());

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
                          factory_, HttpListener::RequestTimeout(REQUEST_TIMEOUT),
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
    EXPECT_FALSE(client->isConnectionAlive());

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
                          factory_, HttpListener::RequestTimeout(REQUEST_TIMEOUT),
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
    EXPECT_FALSE(client->isConnectionAlive());

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

    EXPECT_FALSE(client->isConnectionAlive());

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
                          factory_, HttpListener::RequestTimeout(REQUEST_TIMEOUT),
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
    EXPECT_FALSE(client->isConnectionAlive());

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

    EXPECT_FALSE(client->isConnectionAlive());

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
                          factory_, HttpListener::RequestTimeout(REQUEST_TIMEOUT),
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

    EXPECT_FALSE(client->isConnectionAlive());

    listener.stop();
    io_service_.poll();
}

// This test verifies that the HTTP listener can't be started twice.
TEST_F(HttpListenerTest, startTwice) {
    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          factory_, HttpListener::RequestTimeout(REQUEST_TIMEOUT),
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
                          factory_, HttpListener::RequestTimeout(REQUEST_TIMEOUT),
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
                              SERVER_PORT, HttpResponseCreatorFactoryPtr(),
                              HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                              HttpListener::IdleTimeout(IDLE_TIMEOUT)),
                 HttpListenerError);
}

// This test verifies that the timeout of 0 can't be specified for the
// Request Timeout.
TEST_F(HttpListenerTest, invalidRequestTimeout) {
    EXPECT_THROW(HttpListener(io_service_, IOAddress(SERVER_ADDRESS),
                              SERVER_PORT, factory_, HttpListener::RequestTimeout(0),
                              HttpListener::IdleTimeout(IDLE_TIMEOUT)),
                 HttpListenerError);
}

// This test verifies that the timeout of 0 can't be specified for the
// idle persistent connection timeout.
TEST_F(HttpListenerTest, invalidIdleTimeout) {
    EXPECT_THROW(HttpListener(io_service_, IOAddress(SERVER_ADDRESS),
                              SERVER_PORT, factory_,
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
                          SERVER_PORT + 1, factory_,
                          HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                          HttpListener::IdleTimeout(IDLE_TIMEOUT));
    EXPECT_THROW(listener.start(), HttpListenerError);
}

// This test verifies that HTTP Request Timeout status is returned as
// expected.
TEST_F(HttpListenerTest, requestTimeout) {
    // The part of the request specified here is correct but it is not
    // a complete request.
    const std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length:";

    // Open the listener with the Request Timeout of 1 sec and post the
    // partial request.
    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          factory_, HttpListener::RequestTimeout(1000),
                          HttpListener::IdleTimeout(IDLE_TIMEOUT));
    ASSERT_NO_THROW(listener.start());
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    TestHttpClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);

    // The server should wait for the missing part of the request for 1 second.
    // The missing part never arrives so the server should respond with the
    // HTTP Request Timeout status.
    EXPECT_EQ("HTTP/1.1 408 Request Timeout\r\n"
              "Content-Length: 44\r\n"
              "Content-Type: application/json\r\n"
              "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
              "\r\n"
              "{ \"result\": 408, \"text\": \"Request Timeout\" }",
              client->getResponse());
}

/// @brief Test fixture class for testing HTTP client.
class HttpClientTest : public HttpListenerTest {
public:

    /// @brief Constructor.
    HttpClientTest()
        : HttpListenerTest(),
          listener_(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                    factory_, HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                    HttpListener::IdleTimeout(IDLE_TIMEOUT)),
          listener2_(io_service_, IOAddress(IPV6_SERVER_ADDRESS), SERVER_PORT + 1,
                     factory_, HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                     HttpListener::IdleTimeout(IDLE_TIMEOUT)),
          listener3_(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT + 2,
                     factory_, HttpListener::RequestTimeout(REQUEST_TIMEOUT),
                     HttpListener::IdleTimeout(SHORT_IDLE_TIMEOUT)) {
    }

    /// @brief Destructor.
    ~HttpClientTest() {
        listener_.stop();
        listener2_.stop();
        listener3_.stop();
        io_service_.poll();
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

    /// @brief Test that two consecutive requests can be sent over the same connection.
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
        ASSERT_NO_THROW(client.asyncSendRequest(url, request1, response1,
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
        ASSERT_NO_THROW(client.asyncSendRequest(url, request2, response2,
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

    /// @brief Instance of the listener used in the tests.
    HttpListener listener_;

    /// @brief Instance of the second listener used in the tests.
    HttpListener listener2_;

    /// @brief Instance of the third listener used in the tests (with short idle
    /// timeout).
    HttpListener listener3_;
};

// Test that two conscutive requests can be sent over the same (persistent)
// connection.
TEST_F(HttpClientTest, consecutiveRequests) {
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(HttpVersion(1, 1)));
}

// Test that two consecutive requests can be sent over non-persistent connection.
// This is achieved by sending HTTP/1.0 requests, which are non-persistent by
// default. The client should close the connection right after receiving a response
// from the server.
TEST_F(HttpClientTest, closeBetweenRequests) {
    ASSERT_NO_FATAL_FAILURE(testConsecutiveRequests(HttpVersion(1, 0)));
}

// Test that the client can communicate with two different destinations
// simultaneously.
TEST_F(HttpClientTest, multipleDestinations) {
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
    ASSERT_NO_THROW(client.asyncSendRequest(url1, request1, response1,
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
    ASSERT_NO_THROW(client.asyncSendRequest(url2, request2, response2,
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

// Test that idle connection can be resumed for second request.
TEST_F(HttpClientTest, idleConnection) {
    // Start the server that has short idle timeout. It closes the idle connection
    // after 200ms.
    ASSERT_NO_THROW(listener3_.start());

    // Create the client that will communicate with this server.
    HttpClient client(io_service_);

    // Specify the URL of this server.
    Url url("http://127.0.0.1:18125");

    // Create the first request.
    PostHttpRequestJsonPtr request1 = createRequest("sequence", 1);
    HttpResponseJsonPtr response1(new HttpResponseJson());
    ASSERT_NO_THROW(client.asyncSendRequest(url, request1, response1,
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
    ASSERT_NO_THROW(client.asyncSendRequest(url, request2, response2,
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

// This test verifies that the client returns IO error code when the
// server is unreachable.
TEST_F(HttpClientTest, unreachable) {
    // Create the client.
    HttpClient client(io_service_);

    // Specify the URL of the server. This server is down.
    Url url("http://127.0.0.1:18123");

    // Create the request.
    PostHttpRequestJsonPtr request = createRequest("sequence", 1);
    HttpResponseJsonPtr response(new HttpResponseJson());
    ASSERT_NO_THROW(client.asyncSendRequest(url, request, response,
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

// Test that an error is returned by the client if the server response is
// malformed.
TEST_F(HttpClientTest, malformedResponse) {
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
    PostHttpRequestJsonPtr request = createRequest("requested-content-type", "text/html");
    HttpResponseJsonPtr response(new HttpResponseJson());
    ASSERT_NO_THROW(client.asyncSendRequest(url, request, response,
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

// Test that client times out when it doesn't receive the entire response
// from the server within a desired time.
TEST_F(HttpClientTest, clientRequestTimeout) {
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
    ASSERT_NO_THROW(client.asyncSendRequest(url, request1, response1,
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
    }, HttpClient::RequestTimeout(100)));

    // Create another request after the timeout. It should be handled ok.
    PostHttpRequestJsonPtr request2 = createRequest("sequence", 1);
    HttpResponseJsonPtr response2(new HttpResponseJson());
    ASSERT_NO_THROW(client.asyncSendRequest(url, request2, response2,
                    [this, &cb_num](const boost::system::error_code& /*ec*/, const HttpResponsePtr&,
               const std::string&) {
        if (++cb_num > 1) {
            io_service_.stop();
        }
    }));

    // Actually trigger the requests.
    ASSERT_NO_THROW(runIOService());
}

// Test that client times out when connection takes too long.
TEST_F(HttpClientTest, clientConnectTimeout) {
    // Start the server.
    ASSERT_NO_THROW(listener_.start());

    // Create the client.
    HttpClient client(io_service_);

    // Specify the URL of the server.
    Url url("http://127.0.0.1:18123");

    unsigned cb_num = 0;

    PostHttpRequestJsonPtr request = createRequest("sequence", 1);
    HttpResponseJsonPtr response(new HttpResponseJson());
    ASSERT_NO_THROW(client.asyncSendRequest(url, request, response,
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
       [](const boost::system::error_code& /*ec*/) {
           return (false);
    }));

    // Create another request after the timeout. It should be handled ok.
    ASSERT_NO_THROW(client.asyncSendRequest(url, request, response,
                    [this, &cb_num](const boost::system::error_code& /*ec*/, const HttpResponsePtr&,
               const std::string&) {
        if (++cb_num > 1) {
            io_service_.stop();
        }
    }));

    // Actually trigger the requests.
    ASSERT_NO_THROW(runIOService());
}


}
