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
#include <http/listener.h>
#include <http/post_request_json.h>
#include <http/response_creator.h>
#include <http/response_creator_factory.h>
#include <http/response_json.h>
#include <http/url.h>
#include <util/multi_threading_mgr.h>
#include <testutils/gtest_utils.h>

#include <boost/asio/ip/tcp.hpp>
#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>

#include <functional>
#include <sstream>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::http;
using namespace isc::util;
namespace ph = std::placeholders;

namespace {

/// @brief IP address to which HTTP service is bound.
const std::string SERVER_ADDRESS = "127.0.0.1";

/// @brief IPv6 address to which HTTP service is bound.
const std::string IPV6_SERVER_ADDRESS = "::1";

/// @brief Port number to which HTTP service is bound.
const unsigned short SERVER_PORT = 18123;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Container request/response pair handled by a given thread.
struct ClientRR {
    std::string thread_id_;
    PostHttpRequestJsonPtr request_;
    HttpResponseJsonPtr response_;
};

/// @brief Pointer to a ClientRR.
typedef boost::shared_ptr<ClientRR> ClientRRPtr;

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
        // HTTP version is parsed OK).
        HttpVersion http_version(request->context()->http_version_major_,
                                 request->context()->http_version_minor_);
        // This will generate the response holding JSON content.
        HttpResponseJsonPtr response(new HttpResponseJson(http_version, status_code));
        response->finalize();
        return (response);
    }

    /// @brief Creates HTTP response.
    ///
    /// This method generates a response with the JSON body copied 
    /// from the request.
    ///
    /// @param request Pointer to the HTTP request.
    /// @return Pointer to the generated HTTP OK response with no content.
    virtual HttpResponsePtr
    createDynamicHttpResponse(HttpRequestPtr request) {
        // Request must always be JSON.
        PostHttpRequestJsonPtr request_json =
            boost::dynamic_pointer_cast<PostHttpRequestJson>(request);

        if (!request_json) {
            return(createStockHttpResponse(request, HttpStatusCode::BAD_REQUEST));
        }

        // Request must always contain a body.
        ConstElementPtr body = request_json->getBodyAsJson();
        if (!body) {
            return(createStockHttpResponse(request, HttpStatusCode::BAD_REQUEST));
        }

        HttpResponseJsonPtr response(new HttpResponseJson(request->getHttpVersion(),
                                                          HttpStatusCode::OK));

        // Echo request body back in the response.
        response->setBodyAsJson(body);

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

/// @brief Test fixture class for testing multi-threaded HTTP client.
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
        if (client_) {
            client_->stop();
        }

        if (listener_) {
            listener_->stop();
        }
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

    /// @brief Runs test's IOService until the desired number of have been carried out.
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

    /// @brief Initiates a single HTTP request.
    ///
    /// Constructs an HTTP post whose body is a JSON map containing a
    /// single integer element, "sequence".
    ///
    /// The request completion handler will block each requesting thread
    /// until the number of in-progress threads reaches the number of
    /// threads in the pool.  At that point, the handler will unblock
    /// until all threads have finished preparing the response and are
    /// ready to return.   The handler will notify all pending threads
    /// and invoke stop() on the test's main IO service thread. 
    ///
    /// @param sequence value for the integer element, "sequence",
    /// to send in the request.
    void startRequest(int sequence) {
        // Create the URL on which the server can be reached.
        std::stringstream ss;
        ss << "http://" << SERVER_ADDRESS << ":" << SERVER_PORT;
        Url url(ss.str());

        // Initiate request to the server.
        PostHttpRequestJsonPtr request_json = createRequest("sequence", sequence);

        HttpResponseJsonPtr response_json = boost::make_shared<HttpResponseJson>();

        ASSERT_NO_THROW(client_->asyncSendRequest(url, TlsContextPtr(),
                                                  request_json, response_json,
            [this, request_json, response_json](const boost::system::error_code& ec,
                   const HttpResponsePtr&/* response*/,
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
            clientRR->request_ = request_json;
            clientRR->response_ = response_json;

            {
                std::unique_lock<std::mutex> lck(mutex_);
                num_finished_++;
                clientRRs_.push_back(clientRR);
                if (num_threads_ == 0 || num_finished_ == num_threads_) {
                    // We're all done, notify the others and finish.
                    num_in_progress_ = 0;
                    cv_.notify_all();
                    // Stop the test's IOService.
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

    /// @brief Starts one or more HTTP requests via HttpClient to a test listener.
    ///
    /// This function command creates a HttpClient with the given number
    /// of threads. It initiates then given number of HTTP requests. Each 
    /// request carries a single integer element, "sequence" in its body.
    /// The response is expected to be this same element echoed back.
    /// Then it iteratively runs the test's IOService until all
    /// the requests have been responded to, an error occurs, or the
    /// test times out.
    ///
    /// It requires that the number of requests, when greater than the
    /// number of threads, be a multiple of the number of threads.  The
    /// requests completion handler is structured in such a way as to ensure
    /// (we hope) that each client thread handles the same number of requests.
    ///
    /// @param num_threads - the number of threads the HttpClient
    /// should use. A value of 0 puts the HttpClient in single-threaded mode.
    /// @param num_requests - the number of requests that should be carried out.
    /// Must be greater than 0. If it is greater than num_threads it must be a
    /// multiple of num_threads.
    ///
    /// @param num_threads
    /// @param num_requests
    void threadRequestAndReceive(size_t num_threads, size_t num_requests) {
        // First we makes sure the parameter rules apply.
        ASSERT_TRUE((num_threads == 0) || (num_requests < num_threads) 
                    || (num_requests % num_threads == 0));
        num_threads_ = num_threads;
        num_requests_ = num_requests;

        // Make a factory
        factory_.reset(new TestHttpResponseCreatorFactory());
    
        // Need to create a Listener on
        listener_.reset(new HttpListener(io_service_, 
                                         IOAddress(SERVER_ADDRESS), SERVER_PORT,
                                         TlsContextPtr(), factory_,
                                         HttpListener::RequestTimeout(10000),
                                         HttpListener::IdleTimeout(10000)));

        // Start the server.
        ASSERT_NO_THROW(listener_->start());

        // Create an MT client with num_threads
        ASSERT_NO_THROW_LOG(client_.reset(new HttpClient(io_service_, num_threads)));
        ASSERT_TRUE(client_);

        if (num_threads_ == 0) {
            // If we single-threaded client should not have it's own IOService.
            ASSERT_FALSE(client_->getMyIOService());
        } else {
            // If we multi-threaded client should have it's own IOService.
            ASSERT_TRUE(client_->getMyIOService());
        }

        // Verify the pool size and number of threads are as expected.
        ASSERT_EQ(client_->getThreadPoolSize(), num_threads);
        ASSERT_EQ(client_->getThreadCount(), num_threads);

        // Start the requisite number of requests.
        for (int i = 0; i < num_requests_; ++i) {
            startRequest(i + 1);
        }

        // Run test thread IOService.  This drives the listener's IO.
        ASSERT_NO_THROW(runIOService());

        // We should have a response for each request.
        ASSERT_EQ(clientRRs_.size(), num_requests_);

        // Create a map to track number of responses for each client thread.
        std::map<std::string, int> responses_per_thread;

        // Get the stringified thread-id of the test's main thread.
        std::stringstream ss;
        ss << std::this_thread::get_id();
        std::string main_thread_id = ss.str();

        // Iterate over the client request/response pairs.
        for (auto const& clientRR : clientRRs_ ) {
            // Make sure it's whole.
            ASSERT_FALSE(clientRR->thread_id_.empty());
            ASSERT_TRUE(clientRR->request_);
            ASSERT_TRUE(clientRR->response_);

            // Request should contain an integer sequence number.
            int request_sequence;
            ConstElementPtr sequence = clientRR->request_->getJsonElement("sequence");
            ASSERT_TRUE(sequence);
            ASSERT_NO_THROW(request_sequence = sequence->intValue());

            // Response should contain an integer sequence number.
            int response_sequence;
            sequence = clientRR->response_->getJsonElement("sequence");
            ASSERT_TRUE(sequence);
            ASSERT_NO_THROW(response_sequence = sequence->intValue());

            // Request and Response sequence numbers should match.
            ASSERT_EQ(request_sequence, response_sequence);

            if (num_threads_ == 0) {
                // For ST mode thread id should always be the main thread.
                ASSERT_EQ(clientRR->thread_id_, main_thread_id);
            } else {
                // For MT mode the thread id should never be the main thread.
                ASSERT_NE(clientRR->thread_id_, main_thread_id);
            }

            // Bump the response count for the given client thread-id.
            auto it = responses_per_thread.find(clientRR->thread_id_);
            if (it != responses_per_thread.end()) {
                responses_per_thread[clientRR->thread_id_] = it->second + 1;
            } else {
                responses_per_thread[clientRR->thread_id_] = 1;
            }
        }

        // Make sure we have the expected number of responding threads.
        if (num_threads_ == 0) {
            ASSERT_EQ(responses_per_thread.size(), 1);
        } else {
            size_t expected_thread_count = (num_requests_ < num_threads_ ?
                                            num_requests_ : num_threads_);
            ASSERT_EQ(responses_per_thread.size(), expected_thread_count);
        }

        // Each thread-id ought to have received the same number of responses.
        for (auto const& it : responses_per_thread) {
            EXPECT_EQ(it.second, num_requests_ / responses_per_thread.size())
                      << "thread-id: " << it.first
                      << ", responses: " << it.second << std::endl;
        }

        ASSERT_NO_THROW(client_->stop());

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

    // Make sure destruction doesn't throw.
    ASSERT_NO_THROW_LOG(client.reset());
}

// Now we'll run some permutations of the number of client threads
// and the number of client requests.

// Single-threaded, three requests.
TEST_F(MtHttpClientTest, zeroByThree) {
    size_t num_threads = 0; // Zero threads = ST mode.
    size_t num_requests = 3;
    threadRequestAndReceive(num_threads, num_requests);
}

// Multi-threaded with one thread, three requests.
TEST_F(MtHttpClientTest, oneByThree) {
    size_t num_threads = 1;
    size_t num_requests = 3;
    threadRequestAndReceive(num_threads, num_requests);
}

// Multi-threaded with threads, three requests.
TEST_F(MtHttpClientTest, threeByThree) {
    size_t num_threads = 3;
    size_t num_requests = 3;
    threadRequestAndReceive(num_threads, num_requests);
}

// Multi-threaded with threads, nine requests.
TEST_F(MtHttpClientTest, threeByNine) {
    size_t num_threads = 3;
    size_t num_requests = 9;
    threadRequestAndReceive(num_threads, num_requests);
}

} // end of anonymous namespace
