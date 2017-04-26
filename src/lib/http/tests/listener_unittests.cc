// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <http/listener.h>
#include <http/post_request_json.h>
#include <http/response_creator.h>
#include <http/response_creator_factory.h>
#include <http/response_json.h>
#include <http/tests/response_test.h>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <gtest/gtest.h>
#include <list>
#include <string>

using namespace boost::asio::ip;
using namespace isc::asiolink;
using namespace isc::http;
using namespace isc::http::test;

namespace {

/// @brief IP address to which HTTP service is bound.
const std::string SERVER_ADDRESS = "127.0.0.1";

/// @brief Port number to which HTTP service is bound.
const unsigned short SERVER_PORT = 18123;

/// @brief Request Timeout used in most of the tests (ms).
const long REQUEST_TIMEOUT = 10000;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Test HTTP response.
typedef TestHttpResponseBase<HttpResponseJson> Response;

/// @brief Pointer to test HTTP response.
typedef boost::shared_ptr<Response> ResponsePtr;

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
class HttpClient : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// This constructor creates new socket instance. It doesn't connect. Call
    /// connect() to connect to the server.
    ///
    /// @param io_service IO service to be stopped on error.
    explicit HttpClient(IOService& io_service)
        : io_service_(io_service.get_io_service()), socket_(io_service_),
          buf_(), response_() {
    }

    /// @brief Destructor.
    ///
    /// Closes the underlying socket if it is open.
    ~HttpClient() {
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
                // error code which doesn't neccessarily indicate a problem.
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

/// @brief Pointer to the HttpClient.
typedef boost::shared_ptr<HttpClient> HttpClientPtr;

/// @brief Test fixture class for @ref HttpListener.
class HttpListenerTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Starts test timer which detects timeouts.
    HttpListenerTest()
        : io_service_(), factory_(new TestHttpResponseCreatorFactory()),
          test_timer_(io_service_), clients_() {
        test_timer_.setup(boost::bind(&HttpListenerTest::timeoutHandler, this),
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
    /// This method creates HttpClient instance and retains it in the clients_
    /// list.
    void startRequest(const std::string& request) {
        HttpClientPtr client(new HttpClient(io_service_));
        clients_.push_back(client);
        clients_.back()->startRequest(request);
    }

    /// @brief Callback function invoke upon test timeout.
    ///
    /// It stops the IO service and reports test timeout.
    void timeoutHandler() {
        ADD_FAILURE() << "Timeout occurred while running the test!";
        io_service_.stop();
    }

    /// @brief IO service used in the tests.
    IOService io_service_;

    /// @brief Pointer to the response creator factory.
    HttpResponseCreatorFactoryPtr factory_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief List of client connections.
    std::list<HttpClientPtr> clients_;
};

// This test verifies that HTTP connection can be established and used to
// transmit HTTP request and receive a response.
TEST_F(HttpListenerTest, listen) {
    const std::string request = "POST /foo/bar HTTP/1.1\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 3\r\n\r\n"
        "{ }";

    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          factory_, REQUEST_TIMEOUT);
    ASSERT_NO_THROW(listener.start());
    ASSERT_EQ(SERVER_ADDRESS, listener.getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener.getLocalPort());
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(io_service_.run());
    ASSERT_EQ(1, clients_.size());
    HttpClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_EQ("HTTP/1.1 200 OK\r\n"
              "Content-Length: 0\r\n"
              "Content-Type: application/json\r\n"
              "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
              "\r\n",
              client->getResponse());
    listener.stop();
    io_service_.poll();
}

// This test verifies that the HTTP listener can't be started twice.
TEST_F(HttpListenerTest, startTwice) {
    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          factory_, REQUEST_TIMEOUT);
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
                          factory_, REQUEST_TIMEOUT);
    ASSERT_NO_THROW(listener.start());
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(io_service_.run());
    ASSERT_EQ(1, clients_.size());
    HttpClientPtr client = *clients_.begin();
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
                              REQUEST_TIMEOUT),
                 HttpListenerError);
}

// This test verifies that the timeout of 0 can't be specified for the
// Request Timeout.
TEST_F(HttpListenerTest, invalidRequestTimeout) {
    EXPECT_THROW(HttpListener(io_service_, IOAddress(SERVER_ADDRESS),
                              SERVER_PORT, factory_, 0),
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
                          SERVER_PORT + 1, factory_, REQUEST_TIMEOUT);
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
                          factory_, 1000);
    ASSERT_NO_THROW(listener.start());
    ASSERT_NO_THROW(startRequest(request));
    ASSERT_NO_THROW(io_service_.run());
    ASSERT_EQ(1, clients_.size());
    HttpClientPtr client = *clients_.begin();
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

}
