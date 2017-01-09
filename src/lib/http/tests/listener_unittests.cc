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
#include <boost/bind.hpp>
#include <gtest/gtest.h>
#include <list>
#include <string>

using namespace isc::asiolink;
using namespace isc::http;
using namespace isc::http::test;

namespace {

const std::string SERVER_ADDRESS = "127.0.0.1";
const unsigned short SERVER_PORT = 18123;

/// @brief Test timeout in ms.
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

    /// @brief Creates HTTP 400 response.
    ///
    /// @param request Pointer to the HTTP request.
    /// @return Pointer to the generated HTTP 400 response.
    virtual HttpResponsePtr
    createStockBadRequest(const ConstHttpRequestPtr& request) const {
        // The request hasn't been finalized so the request object
        // doesn't contain any information about the HTTP version number
        // used. But, the context should have this data (assuming the
        // HTTP version is parsed ok).
        HttpVersion http_version(request->context()->http_version_major_,
                                 request->context()->http_version_minor_);
        // This will generate the response holding JSON content.
        ResponsePtr response(new Response(http_version,
                                          HttpStatusCode::BAD_REQUEST));
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

class TestHttpResponseCreatorFactory : public HttpResponseCreatorFactory {
public:

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

    void startRequest() {
        boost::asio::ip::tcp::endpoint
            endpoint(boost::asio::ip::address::from_string(SERVER_ADDRESS),
                     SERVER_PORT);
        socket_.async_connect(endpoint, [this](const boost::system::error_code& ec) {
            if (ec) {
                ADD_FAILURE() << "error occurred while connecting: "
                              << ec.message();
                io_service_.stop();
            }
            sendRequest();
        });
    }

    void sendRequest() {
        const std::string request = "POST /foo/bar HTTP/1.1\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: 3\r\n\r\n"
            "{ }";
        sendPartialRequest(request);
    }

    void sendPartialRequest(std::string request) {
        socket_.async_send(boost::asio::buffer(request.data(), request.size()),
                           [this, request](const boost::system::error_code& ec,
                                           std::size_t bytes_transferred) mutable {
            if (ec) {
                ADD_FAILURE() << "error occurred while connecting: "
                              << ec.message();
                io_service_.stop();
                return;
            }

            if (bytes_transferred > 0 && (request.size() <= bytes_transferred)) {
                request.erase(0, bytes_transferred);
            }

            if (!request.empty()) {
                sendPartialRequest(request);

            } else {
                response_.clear();
                receivePartialResponse();
            }
       });
    }

    void receivePartialResponse() {
        socket_.async_read_some(boost::asio::buffer(buf_),
                                [this](const boost::system::error_code& ec,
                                       std::size_t bytes_transferred) {
            if (ec) {
                ADD_FAILURE() << "error occurred while receiving HTTP"
                    " response from the server: " << ec.message();
                io_service_.stop();
            }

            if (bytes_transferred > 0) {
                response_.insert(response_.end(), buf_.data(),
                                 buf_.data() + bytes_transferred);
            }

            if (response_.find("\r\n\r\n", 0) != std::string::npos) {
                io_service_.stop();
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

class HttpListenerTest : public ::testing::Test {
public:

    HttpListenerTest()
        : io_service_(), factory_(new TestHttpResponseCreatorFactory()),
          test_timer_(io_service_) {
        test_timer_.setup(boost::bind(&HttpListenerTest::timeoutHandler, this),
                          TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
    }

    /// @brief Connect to the endpoint.
    ///
    /// This method creates HttpClient instance and retains it in the clients_
    /// list.
    void startRequest() {
        HttpClientPtr client(new HttpClient(io_service_));
        clients_.push_back(client);
        clients_.back()->startRequest();
    }

    /// @brief Callback function invoke upon test timeout.
    ///
    /// It stops the IO service and reports test timeout.
    void timeoutHandler() {
        ADD_FAILURE() << "Timeout occurred while running the test!";
        io_service_.stop();
    }

    IOService io_service_;

    HttpResponseCreatorFactoryPtr factory_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief List of client connections.
    std::list<HttpClientPtr> clients_;
};

TEST_F(HttpListenerTest, listen) {
    HttpListener listener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                          factory_);
    ASSERT_NO_THROW(listener.start());
    ASSERT_NO_THROW(startRequest());
    ASSERT_NO_THROW(io_service_.run());
    ASSERT_EQ(1, clients_.size());
    HttpClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_EQ("HTTP/1.1 200 OK\r\n"
              "Content-Type: application/json\r\n"
              "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
              "\r\n",
              client->getResponse());
}

}
