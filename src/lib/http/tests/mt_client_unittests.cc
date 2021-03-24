// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
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
#include <http/listener_impl.h>
#include <http/post_request_json.h>
#include <http/response_creator.h>
#include <http/response_creator_factory.h>
#include <http/response_json.h>
#include <http/tests/response_test.h>
#include <http/url.h>
#include <util/multi_threading_mgr.h>
#include <testutils/gtest_utils.h>

#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>

#include <functional>
#include <list>
#include <sstream>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::http;
using namespace isc::http::test;
using namespace isc::util;
namespace ph = std::placeholders;

namespace isc {
data::ConstElementPtr 
http::HttpResponse::getJsonElement(const std::string& element_name) const {
    try {
        ConstElementPtr body = Element::fromJSON(getBody());
        if (body) {
            const std::map<std::string, ConstElementPtr>& map_value = body->mapValue();
            auto map_element = map_value.find(element_name);
            if (map_element != map_value.end()) {
                return (map_element->second);
            }
        }

    } catch (const std::exception& ex) {
        isc_throw(HttpResponseError, "unable to get JSON element "
                  << element_name << ": " << ex.what());
    }

    return (ConstElementPtr());
}
}


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

struct ClientRR {
    std::string thread_id_;
    HttpRequestPtr request_;
    HttpResponsePtr response_;
};

typedef boost::shared_ptr<ClientRR> ClientRRPtr;

/// @todo  Creator and Factory are currently with server_client_unittests.cc
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

/// @brief Test fixture class for testing HTTP client.
class MtHttpClientTest : public ::testing::Test {
public:

    /// @brief Constructor.
    MtHttpClientTest()
        : io_service_(), client_(), listener_(), factory_(), test_timer_(io_service_),
        num_threads_(0), num_requests_(0), num_in_progress_(0), num_finished_(0) {
        test_timer_.setup(std::bind(&MtHttpClientTest::timeoutHandler, this, true),
                          TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
        MultiThreadingMgr::instance().setMode(true);
    }

    /// @brief Destructor.
    ~MtHttpClientTest() {
        if (listener_) {
            listener_->stop();
        }

        MultiThreadingMgr::instance().setMode(false);
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

   void runIOService() {
        // Loop until the clients are done, an error occurs, or the time runs out.
        while (clientRRs_.size() < num_requests_) {
            // Always call restart() before we call run();
            io_service_.get_io_service().reset();

            // Run until a client stops the service.
            io_service_.run();
        }
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

    void startRequest() {
        // Create the URL on which the server can be reached.
        std::stringstream ss;
        ss << "http://" << SERVER_ADDRESS << ":" << SERVER_PORT;
        Url url(ss.str());

        // Initiate request to the server.
        PostHttpRequestJsonPtr request = createRequest("sequence", 1);

        HttpResponseJsonPtr response_json = boost::make_shared<HttpResponseJson>();

        ASSERT_NO_THROW(client_->asyncSendRequest(url, request, response_json,
            [this, request](const boost::system::error_code& ec,
                   const HttpResponsePtr& response,
                   const std::string&) {
            // Bail on an error.
            ASSERT_FALSE(ec) << "asyncSendRequest failed, ec: " << ec;

            {
                std::unique_lock<std::mutex> lck(mutex_);
                ++num_in_progress_;
                if (num_threads_ == 0 || num_in_progress_ == num_threads_) {
                    num_finished_ = 0;
                    cv_.notify_all();
                } else {
                    bool ret = cv_.wait_for(lck, std::chrono::seconds(10),
                                            [&]() { return (num_in_progress_ == num_threads_); });
                    if (!ret) {
                        ADD_FAILURE() << "clients failed to start work";
                    }
                }
            }

            // Get stringified thread-id.
            std::stringstream ss;
            ss << std::this_thread::get_id();

            // Create the ClientRR.
            ClientRRPtr clientRR(new ClientRR());
            clientRR->thread_id_ =  ss.str();
            clientRR->request_ = request;
            clientRR->response_ = response;

            {
                std::unique_lock<std::mutex> lck(mutex_);
                num_finished_++;
                clientRRs_.push_back(clientRR);
                if (num_threads_ == 0 || num_finished_ == num_threads_) {
                    // We're all done, notify the others and finish.
                    num_in_progress_ = 0;
                    cv_.notify_all();
                    // Stop the test's IOservice.
                    io_service_.stop();
                } else {
                    // I'm done but others aren't wait here.
                    bool ret = cv_.wait_for(lck, std::chrono::seconds(10),
                                            [&]() { return (num_finished_ == num_threads_); });
                    if (!ret) {
                        ADD_FAILURE() << "clients failed to finish work";
                    }
                }
            }
        }));
    }

    void threadRequestAndReceive(size_t num_threads, size_t num_requests) {
        // First we makes sure the parameter rules apply.
        ASSERT_TRUE((num_threads == 0) || (num_requests < num_threads) 
                    || (num_requests % num_threads == 0));

        // Make a factory
        factory_.reset(new TestHttpResponseCreatorFactory());
    
        // Need to create a Listener on
        listener_.reset(new HttpListener(io_service_, IOAddress(SERVER_ADDRESS), SERVER_PORT,
                                         factory_, HttpListener::RequestTimeout(10000),
                                         HttpListener::IdleTimeout(10000)));
        // Start the server.
        ASSERT_NO_THROW(listener_->start());

        num_threads_ = num_threads;
        num_requests_ = num_requests;

        // Create an MT client with num_threads
        ASSERT_NO_THROW_LOG(client_.reset(new HttpClient(io_service_, num_threads)));
        ASSERT_TRUE(client_);

        if (num_threads_ == 0) {
            ASSERT_FALSE(client_->getMyIOService());
        } else {
            ASSERT_TRUE(client_->getMyIOService());
        }
        ASSERT_EQ(client_->getThreadPoolSize(), num_threads);
        ASSERT_EQ(client_->getThreadCount(), num_threads);

        // Start the requisite number of requests.
        for (auto i = 0; i < num_requests_; ++i) {
            startRequest();
        }

        // Run test thread IOService.  This drives the listener's IO.
        ASSERT_NO_THROW(runIOService());

        ASSERT_EQ(clientRRs_.size(), num_requests_);
        for (auto const& clientRR : clientRRs_ ) {
            HttpResponsePtr response = clientRR->response_;
            ASSERT_TRUE(response);
            ConstElementPtr sequence = response->getJsonElement("sequence");
            ASSERT_TRUE(sequence);
        }

        ASSERT_NO_THROW(listener_->stop());
    }

    /// @brief IO service used in the tests.
    IOService io_service_;

    /// @brief Instance of the client used in the tests.
    HttpClientPtr client_;

    /// @brief Instance of the listener used in the tests.
    HttpListenerPtr listener_;

    /// @brief Pointer to the response creator factory.
    HttpResponseCreatorFactoryPtr factory_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Number of threads HttpClient should use.
    size_t num_threads_;

    /// @brief Number of client requests to conduct.
    size_t num_requests_;

    /// @brief Number of requests that are in progress.
    size_t num_in_progress_;

    /// @brief Number of requests that have been completed.
    size_t num_finished_;

    /// @brief a List of client request-response pairs.
    std::vector<ClientRRPtr> clientRRs_;

    /// @brief Mutex for locking.
    std::mutex mutex_;

    /// @brief Condition variable used make client threads wait
    /// until number of in-progress requests reaches the number
    /// of client requests. 
    std::condition_variable cv_;
};

// Verifies we can construct and destruct, in both single
// and multi-threaded modes.
TEST_F(MtHttpClientTest, basics) {
    MultiThreadingMgr::instance().setMode(false);
    HttpClientPtr client;

    // Value of 0 for thread_pool_size means single-threaded.
    ASSERT_NO_THROW_LOG(client.reset(new HttpClient(io_service_, 0)));
    ASSERT_TRUE(client);

    ASSERT_FALSE(client->getMyIOService());
    ASSERT_EQ(client->getThreadPoolSize(), 0);
    ASSERT_EQ(client->getThreadCount(), 0);

    // Make sure destruction doesn't throw.
    ASSERT_NO_THROW_LOG(client.reset());

    // Non-zero thread-pool-size means multi-threaded mode, should throw.
    ASSERT_THROW_MSG(client.reset(new HttpClient(io_service_, 1)), InvalidOperation,
                                  "HttpClient thread_pool_size must be zero"
                                  "when Kea core multi-threading is disabled");
    ASSERT_FALSE(client);

    // Enable Kea core multi-threading.
    MultiThreadingMgr::instance().setMode(true);

    // Multi-threaded construction should work now.
    ASSERT_NO_THROW_LOG(client.reset(new HttpClient(io_service_, 3)));
    ASSERT_TRUE(client);

    // Verify that it has an internal IOService and that thread pool size
    // and thread count match.
    ASSERT_TRUE(client->getMyIOService());
    ASSERT_EQ(client->getThreadPoolSize(), 3);
    ASSERT_EQ(client->getThreadCount(), 3);

    // Verify stop doesn't throw.
    ASSERT_NO_THROW_LOG(client->stop());

    // Verify we're stopped.
    ASSERT_FALSE(client->getMyIOService());
    ASSERT_EQ(client->getThreadPoolSize(), 3);
    ASSERT_EQ(client->getThreadCount(), 0);

    // Verify a second call to stop() doesn't throw.
    ASSERT_NO_THROW_LOG(client->stop());

    // Make sure destruction doesn't throw.
    ASSERT_NO_THROW_LOG(client.reset());

    // Create another multi-threaded instance.
    ASSERT_NO_THROW_LOG(client.reset(new HttpClient(io_service_, 3)));

    // Make sure destruction doesn't throw. Note, if destuctor
    // doesn't stop the threads correctly the test will crash upon exit.
    ASSERT_NO_THROW_LOG(client.reset());
}

TEST_F(MtHttpClientTest, zeroByThree) {
    // Zero threads = ST mode.
    size_t num_threads = 0; 
    size_t num_requests = 3;
    threadRequestAndReceive(num_threads, num_requests);
}


TEST_F(MtHttpClientTest, oneByThree) {
    size_t num_threads = 1;
    size_t num_requests = 3;
    threadRequestAndReceive(num_threads, num_requests);
}

TEST_F(MtHttpClientTest, threeByThree) {
    size_t num_threads = 3;
    size_t num_requests = 3;
    threadRequestAndReceive(num_threads, num_requests);
}

TEST_F(MtHttpClientTest, threeByNine) {
    size_t num_threads = 3;
    size_t num_requests = 9;
    threadRequestAndReceive(num_threads, num_requests);
}

}
