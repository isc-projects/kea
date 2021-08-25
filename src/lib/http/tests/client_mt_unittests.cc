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

/// @brief Port number to which HTTP service is bound.
const unsigned short SERVER_PORT = 18123;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Container request/response pair handled by a given thread.
struct ClientRR {
    /// @brief Thread id of the client thread handling the request as a string.
    std::string thread_id_;

    /// @brief HTTP request submitted by the client thread.
    PostHttpRequestJsonPtr request_;

    /// @brief HTTP response received by the client thread.
    HttpResponseJsonPtr response_;
};

/// @brief Pointer to a ClientRR instance.
typedef boost::shared_ptr<ClientRR> ClientRRPtr;

/// @brief Implementation of the @ref HttpResponseCreator.
///
/// Creates a response to a request containing body content
/// as follows:
///
/// ```
///     { "sequence" : nnnn }
/// ```
///
/// The response will include the sequence number of the request
/// as well as the server port passed into the creator's constructor:
///
/// ```
///     { "sequence": nnnn, "server-port": xxxx }
/// ```
class TestHttpResponseCreator : public HttpResponseCreator {
public:
    /// @brief Constructor
    ///
    /// @param server_port integer value the server listens upon, it is
    /// echoed back in responses as "server-port".
    TestHttpResponseCreator(uint16_t server_port)
    : server_port_(server_port) { }

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
    /// @param status_code status code to include in the response.
    ///
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
    /// Generates a response which echoes the requests sequence
    /// number as well as the creator's server port value. Responses
    /// should appear as follows:
    ///
    /// ```
    ///     { "sequence" : nnnn }
    /// ```
    ///
    /// @param request Pointer to the HTTP request.
    /// @return Pointer to the generated HTTP OK response with no content.
    virtual HttpResponsePtr
    createDynamicHttpResponse(HttpRequestPtr request) {
        // Request must always be JSON.
        PostHttpRequestJsonPtr request_json =
            boost::dynamic_pointer_cast<PostHttpRequestJson>(request);
        if (!request_json) {
            return (createStockHttpResponse(request, HttpStatusCode::BAD_REQUEST));
        }

        // Extract the sequence from the request.
        ConstElementPtr sequence = request_json->getJsonElement("sequence");
        if (!sequence) {
            return (createStockHttpResponse(request, HttpStatusCode::BAD_REQUEST));
        }

        // Create the response.
        HttpResponseJsonPtr response(new HttpResponseJson(request->getHttpVersion(),
                                                          HttpStatusCode::OK));
        // Construct the body.
        ElementPtr body = Element::createMap();
        body->set("server-port", Element::create(server_port_));
        body->set("sequence", sequence);

        // Echo request body back in the response.
        response->setBodyAsJson(body);

        response->finalize();
        return (response);
    }

    /// @brief Port upon which this creator's server is listening.
    ///
    /// The intent is to use the value to determine which server generated
    /// a given response.
    uint16_t server_port_;
};

/// @brief Implementation of the test @ref HttpResponseCreatorFactory.
///
/// This factory class creates @ref TestHttpResponseCreator instances.
class TestHttpResponseCreatorFactory : public HttpResponseCreatorFactory {
public:

    /// @brief Constructor
    ///
    /// @param server_port port upon with the server is listening. This
    /// value will be included in responses such that each response
    /// can be attributed to a specific server.
    TestHttpResponseCreatorFactory(uint16_t server_port)
    : server_port_(server_port) {};

    /// @brief Creates @ref TestHttpResponseCreator instance.
    virtual HttpResponseCreatorPtr create() const {
        HttpResponseCreatorPtr response_creator(new TestHttpResponseCreator(server_port_));
        return (response_creator);
    }

    /// @brief Port upon which this factory's server is listening.
    ///
    /// The intent is to use the value to determine which server generated
    /// a given response.
    uint16_t server_port_;
};

/// @brief Test fixture class for testing threading modes of HTTP client.
class MultiThreadingHttpClientTest : public ::testing::Test {
public:

    /// @brief Constructor.
    MultiThreadingHttpClientTest()
        : io_service_(), client_(), listener_(), factory_(), listeners_(), factories_(),
          test_timer_(io_service_), num_threads_(0), num_batches_(0), num_listeners_(0),
          expected_requests_(0), num_in_progress_(0), num_finished_(0), paused_(false),
          pause_cnt_(0) {
        test_timer_.setup(std::bind(&MultiThreadingHttpClientTest::timeoutHandler, this, true),
                          TEST_TIMEOUT, IntervalTimer::ONE_SHOT);
        MultiThreadingMgr::instance().setMode(true);
    }

    /// @brief Destructor.
    ~MultiThreadingHttpClientTest() {
        // Stop the client.
        if (client_) {
            client_->stop();
        }

        // Stop all listeners.
        for (const auto& listener : listeners_) {
            listener->stop();
        }

        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Callback function to invoke upon test timeout.
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

    /// @brief Runs the test's IOService until the desired number of requests
    /// have been carried out or the test fails.
    void runIOService(size_t request_limit) {
        while (getRRCount() < request_limit) {
            // Always call reset() before we call run();
            io_service_.restart();

            // Run until a client stops the service.
            io_service_.run();
        }
    }

    /// @brief Creates an HTTP request with JSON body.
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
                                                               "/boo", version));
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

    /// @brief Test that worker threads are not permitted to change thread pool
    /// state.
    void testIllegalThreadPoolActions() {
        ASSERT_THROW(client_->start(), MultiThreadingInvalidOperation);
        ASSERT_THROW(client_->pause(), MultiThreadingInvalidOperation);
        ASSERT_THROW(client_->resume(), MultiThreadingInvalidOperation);
    }

    /// @brief Initiates a single HTTP request.
    ///
    /// Constructs an HTTP post whose body is a JSON map containing a
    /// single integer element, "sequence".
    ///
    /// The request completion handler will block each requesting thread
    /// until the number of in-progress threads reaches the number of
    /// threads in the pool. At that point, the handler will unblock
    /// until all threads have finished preparing their response and are
    /// ready to return. The handler will then notify all pending threads
    /// and invoke stop() on the test's main IO service thread.
    ///
    /// @param sequence value for the integer element, "sequence",
    /// to send in the request.
    void startRequest(int sequence, int port_offset = 0) {
        // Create the URL on which the server can be reached.
        std::stringstream ss;
        ss << "http://" << SERVER_ADDRESS << ":" << (SERVER_PORT + port_offset);
        Url url(ss.str());

        // Initiate request to the server.
        PostHttpRequestJsonPtr request_json = createRequest("sequence", sequence);
        HttpResponseJsonPtr response_json = boost::make_shared<HttpResponseJson>();
        ASSERT_NO_THROW(client_->asyncSendRequest(url, TlsContextPtr(),
                                                  request_json, response_json,
            [this, request_json, response_json](const boost::system::error_code& ec,
                                                const HttpResponsePtr&,
                                                const std::string&) {
            // Bail on an error.
            ASSERT_FALSE(ec) << "asyncSendRequest failed, ec: " << ec;

            // Wait here until we have as many in progress as we have threads.
            {
                std::unique_lock<std::mutex> lck(test_mutex_);
                ++num_in_progress_;
                if (num_threads_ == 0 || num_in_progress_ == num_threads_) {
                    // Everybody has one, let's go.
                    num_finished_ = 0;
                    test_cv_.notify_all();
                } else {
                    // I'm ready but others aren't wait here.
                    bool ret = test_cv_.wait_for(lck, std::chrono::seconds(10),
                                                 [&]() { return (num_in_progress_ == num_threads_); });
                    if (!ret) {
                        ADD_FAILURE() << "clients failed to start work";
                    }
                }
            }

            // If running on multiple threads, threads should be prohibited from
            // changing the thread pool state.
            if (num_threads_) {
                testIllegalThreadPoolActions();
            }

            // Get stringified thread-id.
            std::stringstream ss;
            ss << std::this_thread::get_id();

            // Create the ClientRR.
            ClientRRPtr clientRR(new ClientRR());
            clientRR->thread_id_ = ss.str();
            clientRR->request_ = request_json;
            clientRR->response_ = response_json;

            // Wait here until we have as many ready to finish as we have threads.
            {
                std::unique_lock<std::mutex> lck(test_mutex_);
                ++num_finished_;
                clientRRs_.push_back(clientRR);
                if (num_threads_ == 0 || num_finished_ == num_threads_) {
                    // We're all done, notify the others and finish.
                    num_in_progress_ = 0;
                    test_cv_.notify_all();
                    // Stop the test's IOService.
                    io_service_.stop();
                } else {
                    // I'm done but others aren't wait here.
                    bool ret = test_cv_.wait_for(lck, std::chrono::seconds(10),
                                                 [&]() { return (num_finished_ == num_threads_); });
                    if (!ret) {
                        ADD_FAILURE() << "clients failed to finish work";
                    }
                }
            }
        }));
    }

    /// @brief Initiates a single HTTP request.
    ///
    /// Constructs an HTTP post whose body is a JSON map containing a
    /// single integer element, "sequence".
    ///
    /// The request completion handler simply constructs the response,
    /// and adds it the list of completed request/responses. If the
    /// number of completed requests has reached the expected number
    /// it stops the test IOService.
    ///
    /// @param sequence value for the integer element, "sequence",
    /// to send in the request.
    void startRequestSimple(int sequence, int port_offset = 0) {
        // Create the URL on which the server can be reached.
        std::stringstream ss;
        ss << "http://" << SERVER_ADDRESS << ":" << (SERVER_PORT + port_offset);
        Url url(ss.str());

        // Initiate request to the server.
        PostHttpRequestJsonPtr request_json = createRequest("sequence", sequence);
        HttpResponseJsonPtr response_json = boost::make_shared<HttpResponseJson>();
        ASSERT_NO_THROW(client_->asyncSendRequest(url, TlsContextPtr(),
                                                  request_json, response_json,
            [this, request_json, response_json](const boost::system::error_code& ec,
                                                const HttpResponsePtr&,
                                                const std::string&) {
            // Bail on an error.
            ASSERT_FALSE(ec) << "asyncSendRequest failed, ec: " << ec;

            // Get stringified thread-id.
            std::stringstream ss;
            ss << std::this_thread::get_id();

            // Create the ClientRR.
            ClientRRPtr clientRR(new ClientRR());
            clientRR->thread_id_ = ss.str();
            clientRR->request_ = request_json;
            clientRR->response_ = response_json;

            {
                std::unique_lock<std::mutex> lck(test_mutex_);
                clientRRs_.push_back(clientRR);
                ++num_finished_;
                if ((num_finished_ >= expected_requests_) && !io_service_.stopped()) {
                    io_service_.stop();
                }
            }

        }));
    }

    /// @brief Carries out HTTP requests via HttpClient to HTTP listener(s).
    ///
    /// This function creates one HttpClient with the given number
    /// of threads and then the given number of HttpListeners. It then
    /// initiates the given number of request batches where each batch
    /// contains one request per thread per listener.
    ///
    /// Then it iteratively runs the test's IOService until all
    /// the requests have been responded to, an error occurs, or the
    /// test times out.
    ///
    /// Each request carries a single integer element, "sequence", which
    /// uniquely identifies the request. Each response is expected to
    /// contain this value echoed back along with the listener's server
    /// port number. Thus each response can be matched to it's request
    /// and to the listener that handled the request.
    ///
    /// After all requests have been conducted, the function verifies
    /// that:
    ///
    /// 1. The number of requests conducted is correct
    /// 2. The sequence numbers in request-response pairs match
    /// 3. Each client thread handled the same number of requests
    /// 4. Each listener handled the same number of requests
    ///
    /// @param num_threads number of threads the HttpClient should use.
    /// A value of 0 puts the HttpClient in single-threaded mode.
    /// @param num_batches number of batches of requests that should be
    /// conducted.
    /// @param num_listeners number of HttpListeners to create. Defaults
    /// to 1.
    void threadRequestAndReceive(size_t num_threads, size_t num_batches,
                                 size_t num_listeners = 1) {
        ASSERT_TRUE(num_batches);
        ASSERT_TRUE(num_listeners);
        num_threads_ = num_threads;
        num_batches_ = num_batches;
        num_listeners_ = num_listeners;

        // Client in ST is, in effect, 1 thread.
        size_t effective_threads = (num_threads_ == 0 ? 1 : num_threads_);

        // Calculate the expected number of requests.
        expected_requests_ = (num_batches_ * num_listeners_ * effective_threads);

        for (auto i = 0; i < num_listeners_; ++i) {
            // Make a factory
            HttpResponseCreatorFactoryPtr factory(new TestHttpResponseCreatorFactory(SERVER_PORT + i));
            factories_.push_back(factory);

            // Need to create a Listener on
            HttpListenerPtr listener(new HttpListener(io_service_,
                                                      IOAddress(SERVER_ADDRESS), (SERVER_PORT + i),
                                                      TlsContextPtr(), factory,
                                                      HttpListener::RequestTimeout(10000),
                                                      HttpListener::IdleTimeout(10000)));
            listeners_.push_back(listener);

            // Start the server.
            ASSERT_NO_THROW(listener->start());
        }

        // Create an MT client with num_threads
        ASSERT_NO_THROW_LOG(client_.reset(new HttpClient(io_service_, num_threads)));
        ASSERT_TRUE(client_);

        if (num_threads_ == 0) {
            // If we single-threaded client should not have it's own IOService.
            ASSERT_FALSE(client_->getThreadIOService());
        } else {
            // If we multi-threaded client should have it's own IOService.
            ASSERT_TRUE(client_->getThreadIOService());
        }

        // Verify the pool size and number of threads are as expected.
        ASSERT_EQ(client_->getThreadPoolSize(), num_threads);
        ASSERT_EQ(client_->getThreadCount(), num_threads);

        // Start the requisite number of requests:
        //   batch * listeners * threads.
        int sequence = 0;
        for (auto b = 0; b < num_batches; ++b) {
            for (auto l = 0; l < num_listeners_; ++l) {
                for (auto t = 0; t < effective_threads; ++t) {
                    startRequest(++sequence, l);
                }
            }
        }

        // Loop until the clients are done, an error occurs, or the time runs out.
        runIOService(expected_requests_);

        // Client should stop without issue.
        ASSERT_NO_THROW(client_->stop());

        // Listeners should stop without issue.
        for (const auto& listener : listeners_) {
            ASSERT_NO_THROW(listener->stop());
        }

        // We should have a response for each request.
        ASSERT_EQ(getRRCount(), expected_requests_);

        // Create a map to track number of responses for each client thread.
        std::map<std::string, int> responses_per_thread;

        // Create a map to track number of responses for each listener port.
        std::map<uint16_t, int> responses_per_listener;

        // Get the stringified thread-id of the test's main thread.
        std::stringstream ss;
        ss << std::this_thread::get_id();
        std::string main_thread_id = ss.str();

        // Iterate over the client request/response pairs.
        for (auto const& clientRR : clientRRs_) {
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

            ConstElementPtr server_port_elem = clientRR->response_->getJsonElement("server-port");
            ASSERT_TRUE(server_port_elem);
            uint16_t server_port = server_port_elem->intValue();

            if (num_threads_ == 0) {
                // For ST mode thread id should always be the main thread.
                ASSERT_EQ(clientRR->thread_id_, main_thread_id);
            } else {
                // For MT mode the thread id should never be the main thread.
                ASSERT_NE(clientRR->thread_id_, main_thread_id);
            }

            // Bump the response count for the given client thread-id.
            auto rit = responses_per_thread.find(clientRR->thread_id_);
            if (rit != responses_per_thread.end()) {
                responses_per_thread[clientRR->thread_id_] = rit->second + 1;
            } else {
                responses_per_thread[clientRR->thread_id_] = 1;
            }

            // Bump the response count for the given server port.
            auto lit = responses_per_listener.find(server_port);
            if (lit != responses_per_listener.end()) {
                responses_per_listener[server_port] = lit->second + 1;
            } else {
                responses_per_listener[server_port] = 1;
            }
        }

        // Make sure that all client threads received responses.
        ASSERT_EQ(responses_per_thread.size(), effective_threads);

        // Make sure that each client thread received the same number of responses.
        for (auto const& it : responses_per_thread) {
            EXPECT_EQ(it.second, (num_batches_ * num_listeners_))
                      << "thread-id: " << it.first
                      << ", responses: " << it.second << std::endl;
        }

        // Make sure that all listeners generated responses.
        ASSERT_EQ(responses_per_listener.size(), num_listeners_);

        // Make sure Each listener generated the same number of responses.
        for (auto const& it : responses_per_listener) {
            EXPECT_EQ(it.second, (num_batches_ * effective_threads))
                      << "server-port: " << it.first
                      << ", responses: " << it.second << std::endl;
        }
    }

    /// @brief Verifies the client can be paused and resumed repeatedly
    /// while doing multi-threaded work.
    ///
    /// @param num_threads number of threads the HttpClient should use.
    /// Must be greater than zero, this test does not make sense for a
    /// single threaded client.
    /// @param num_batches number of batches of requests that should be
    /// conducted.
    /// @param num_listeners number of HttpListeners to create.
    /// @param num_pauses number of pauses to conduct.
    void workPauseResumeShutdown(size_t num_threads, size_t num_batches,
                                 size_t num_listeners, size_t num_pauses) {
        ASSERT_TRUE(num_threads);
        ASSERT_TRUE(num_batches);
        ASSERT_TRUE(num_listeners);
        num_threads_ = num_threads;
        num_batches_ = num_batches;
        num_listeners_ = num_listeners;

        // Calculate the total expected number of requests.
        size_t total_requests = (num_batches_ * num_listeners_ * num_threads_);

        // Create the listeners.
        for (auto i = 0; i < num_listeners_; ++i) {
            // Make a factory
            HttpResponseCreatorFactoryPtr factory(new TestHttpResponseCreatorFactory(SERVER_PORT + i));
            factories_.push_back(factory);

            // Need to create a Listener on
            HttpListenerPtr listener(new HttpListener(io_service_,
                                                      IOAddress(SERVER_ADDRESS), (SERVER_PORT + i),
                                                      TlsContextPtr(), factory,
                                                      HttpListener::RequestTimeout(10000),
                                                      HttpListener::IdleTimeout(10000)));
            listeners_.push_back(listener);

            // Start the server.
            ASSERT_NO_THROW(listener->start());
        }

        // Create an instant start, MT client with num_threads
        ASSERT_NO_THROW_LOG(client_.reset(new HttpClient(io_service_, num_threads)));
        ASSERT_TRUE(client_);

        // Client should be running. Check convenience functions.
        ASSERT_TRUE(client_->isRunning());
        ASSERT_FALSE(client_->isPaused());
        ASSERT_FALSE(client_->isStopped());

        // Verify the pool size and number of threads are as expected.
        ASSERT_EQ(client_->getThreadPoolSize(), num_threads);
        ASSERT_EQ(client_->getThreadCount(), num_threads);

        // Start the requisite number of requests:
        //   batch * listeners * threads.
        int sequence = 0;
        for (auto b = 0; b < num_batches; ++b) {
            for (auto l = 0; l < num_listeners_; ++l) {
                for (auto t = 0; t < num_threads_; ++t) {
                    startRequestSimple(++sequence, l);
                }
            }
        }

        size_t rr_count = 0;
        while (rr_count < total_requests) {
            size_t request_limit = (pause_cnt_ < num_pauses ?
                                    (rr_count + ((total_requests - rr_count) / num_pauses))
                                    : total_requests);

            // Run test IOService until we hit the limit.
            runIOService(request_limit);

            // If we've done all our pauses we should be through.
            if (pause_cnt_ == num_pauses) {
                break;
            }

            // Pause the client.
            ASSERT_NO_THROW(client_->pause());
            ASSERT_TRUE(client_->isPaused());
            ++pause_cnt_;

            // Check our progress.
            rr_count = getRRCount();
            ASSERT_GE(rr_count, request_limit);

            // Resume the client.
            ASSERT_NO_THROW(client_->resume());
            ASSERT_TRUE(client_->isRunning());
        }

        // Client should stop without issue.
        ASSERT_NO_THROW(client_->stop());
        ASSERT_TRUE(client_->isStopped());

        // We should have finished all our requests.
        ASSERT_EQ(getRRCount(), total_requests);

        // Stopping again should be harmless.
        ASSERT_NO_THROW(client_->stop());

        // Listeners should stop without issue.
        for (const auto& listener : listeners_) {
            ASSERT_NO_THROW(listener->stop());
        }

        // Get the stringified thread-id of the test's main thread.
        std::stringstream ss;
        ss << std::this_thread::get_id();
        std::string main_thread_id = ss.str();

        // Tracks the number for requests fulfilled by main thread.
        size_t worked_by_main = 0;

        // Iterate over the client request/response pairs.
        for (auto const& clientRR : clientRRs_) {
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

            ConstElementPtr server_port_elem = clientRR->response_->getJsonElement("server-port");
            ASSERT_TRUE(server_port_elem);

            // Track how many requests were completed by the main thread.
            // These can occur when pausing calls IOService::poll.
            if (clientRR->thread_id_ == main_thread_id) {
                ++worked_by_main;
            }
        }

        // Make sure the majority of the requests were worked by
        // worker threads.  In theory, the number of calls to poll
        // times the number of threads is the limit for responses
        // built by the main thread.
        ASSERT_LE(worked_by_main, num_pauses * num_threads);
    }

    /// @brief Fetch the number of completed requests.
    ///
    /// @return number of completed requests.
    size_t getRRCount() {
        std::lock_guard<std::mutex> lck(test_mutex_);
        return (clientRRs_.size());
    }

    /// @brief IO service used in the tests.
    IOService io_service_;

    /// @brief Instance of the client used in the tests.
    HttpClientPtr client_;

    /// @brief Instance of the listener used in the tests.
    HttpListenerPtr listener_;

    /// @brief Pointer to the response creator factory.
    HttpResponseCreatorFactoryPtr factory_;

    /// @brief List of listeners.
    std::vector<HttpListenerPtr> listeners_;

    /// @brief List of response factories.
    std::vector<HttpResponseCreatorFactoryPtr> factories_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Number of threads HttpClient should use.
    size_t num_threads_;

    /// @brief Number of request batches to conduct.
    size_t num_batches_;

    /// @brief Number of listeners to start.
    size_t num_listeners_;

    /// @brief Number of expected requests to carry out.
    size_t expected_requests_;

    /// @brief Number of requests that are in progress.
    size_t num_in_progress_;

    /// @brief Number of requests that have been completed.
    size_t num_finished_;

    /// @brief a List of client request-response pairs.
    std::vector<ClientRRPtr> clientRRs_;

    /// @brief Mutex for locking.
    std::mutex test_mutex_;

    /// @brief Condition variable used to make client threads wait
    /// until number of in-progress requests reaches the number
    /// of client requests.
    std::condition_variable test_cv_;

    /// @brief Indicates if client threads are currently "paused".
    bool paused_;

    /// @brief Number of times client has been paused during the test.
    size_t pause_cnt_;
};

// Verifies we can construct and destruct, in both single
// and multi-threaded modes.
TEST_F(MultiThreadingHttpClientTest, basics) {
    MultiThreadingMgr::instance().setMode(false);
    HttpClientPtr client;

    // Value of 0 for thread_pool_size means single-threaded.
    ASSERT_NO_THROW_LOG(client.reset(new HttpClient(io_service_, 0)));
    ASSERT_TRUE(client);

    ASSERT_FALSE(client->getThreadIOService());
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
    ASSERT_TRUE(client->getThreadIOService());
    EXPECT_FALSE(client->getThreadIOService()->stopped());
    ASSERT_EQ(client->getThreadPoolSize(), 3);
    ASSERT_EQ(client->getThreadCount(), 3);

    // Check convenience functions.
    ASSERT_TRUE(client->isRunning());
    ASSERT_FALSE(client->isPaused());
    ASSERT_FALSE(client->isStopped());

    // Verify stop doesn't throw.
    ASSERT_NO_THROW_LOG(client->stop());

    // Verify we're stopped.
    ASSERT_TRUE(client->getThreadIOService());
    EXPECT_TRUE(client->getThreadIOService()->stopped());
    ASSERT_EQ(client->getThreadPoolSize(), 3);
    ASSERT_EQ(client->getThreadCount(), 0);

    // Check convenience functions.
    ASSERT_FALSE(client->isRunning());
    ASSERT_FALSE(client->isPaused());
    ASSERT_TRUE(client->isStopped());

    // Verify a second call to stop() doesn't throw.
    ASSERT_NO_THROW_LOG(client->stop());

    // Make sure destruction doesn't throw.
    ASSERT_NO_THROW_LOG(client.reset());

    // Create another multi-threaded instance.
    ASSERT_NO_THROW_LOG(client.reset(new HttpClient(io_service_, 3)));

    // Make sure destruction doesn't throw.
    ASSERT_NO_THROW_LOG(client.reset());
}

// Verifies we can construct with deferred start.
TEST_F(MultiThreadingHttpClientTest, deferredStart) {
    MultiThreadingMgr::instance().setMode(true);
    HttpClientPtr client;
    size_t thread_pool_size = 3;

    // Create MT client with deferred start.
    ASSERT_NO_THROW_LOG(client.reset(new HttpClient(io_service_, thread_pool_size, true)));
    ASSERT_TRUE(client);

    // Client should be STOPPED, with no threads.
    ASSERT_TRUE(client->getThreadIOService());
    ASSERT_EQ(client->getThreadPoolSize(), thread_pool_size);
    ASSERT_EQ(client->getThreadCount(), 0);

    // Check convenience functions.
    ASSERT_FALSE(client->isRunning());
    ASSERT_FALSE(client->isPaused());
    ASSERT_TRUE(client->isStopped());

    // We should be able to start it.
    ASSERT_NO_THROW(client->start());

    // Verify we have threads and run state is RUNNING.
    ASSERT_EQ(client->getThreadCount(), 3);
    ASSERT_TRUE(client->getThreadIOService());
    ASSERT_FALSE(client->getThreadIOService()->stopped());

    // Check convenience functions.
    ASSERT_TRUE(client->isRunning());
    ASSERT_FALSE(client->isPaused());
    ASSERT_FALSE(client->isStopped());

    // Second call to start should be harmless.
    ASSERT_NO_THROW_LOG(client->start());

    // Verify we didn't break it.
    ASSERT_EQ(client->getThreadCount(), 3);
    ASSERT_TRUE(client->isRunning());

    // Make sure destruction doesn't throw.
    ASSERT_NO_THROW_LOG(client.reset());
}

// Verifies we can restart after stop.
TEST_F(MultiThreadingHttpClientTest, restartAfterStop) {
    MultiThreadingMgr::instance().setMode(true);
    HttpClientPtr client;
    size_t thread_pool_size = 3;

    // Create MT client with instant start.
    ASSERT_NO_THROW_LOG(client.reset(new HttpClient(io_service_, thread_pool_size)));
    ASSERT_TRUE(client);

    // Verify we're started.
    ASSERT_EQ(client->getThreadCount(), 3);
    ASSERT_TRUE(client->getThreadIOService());
    ASSERT_FALSE(client->getThreadIOService()->stopped());
    ASSERT_TRUE(client->isRunning());

    // Stop should succeed.
    ASSERT_NO_THROW_LOG(client->stop());

    // Verify we're stopped.
    ASSERT_EQ(client->getThreadCount(), 0);
    ASSERT_TRUE(client->getThreadIOService());
    ASSERT_TRUE(client->getThreadIOService()->stopped());
    ASSERT_TRUE(client->isStopped());

    // Starting again should succeed.
    ASSERT_NO_THROW_LOG(client->start());

    // Verify we didn't break it.
    ASSERT_EQ(client->getThreadCount(), 3);
    ASSERT_TRUE(client->getThreadIOService());
    ASSERT_FALSE(client->getThreadIOService()->stopped());
    ASSERT_TRUE(client->isRunning());

    // Make sure destruction doesn't throw.
    ASSERT_NO_THROW_LOG(client.reset());
}

// Now we'll run some permutations of the number of client threads,
// requests, and listeners.

// Single-threaded, three batches, one listener.
TEST_F(MultiThreadingHttpClientTest, zeroByThreeByOne) {
    size_t num_threads = 0; // Zero threads = ST mode.
    size_t num_batches = 3;
    threadRequestAndReceive(num_threads, num_batches);
}

// Single-threaded, three batches, three listeners.
TEST_F(MultiThreadingHttpClientTest, zeroByThreeByThree) {
    size_t num_threads = 0; // Zero threads = ST mode.
    size_t num_batches = 3;
    size_t num_listeners = 3;
    threadRequestAndReceive(num_threads, num_batches, num_listeners);
}

// Multi-threaded with one thread, three batches, one listener
TEST_F(MultiThreadingHttpClientTest, oneByThreeByOne) {
    size_t num_threads = 1;
    size_t num_batches = 3;
    threadRequestAndReceive(num_threads, num_batches);
}

// Multi-threaded with three threads, three batches, one listener
TEST_F(MultiThreadingHttpClientTest, threeByThreeByOne) {
    size_t num_threads = 3;
    size_t num_batches = 3;
    threadRequestAndReceive(num_threads, num_batches);
}

// Multi-threaded with three threads, nine batches, one listener
TEST_F(MultiThreadingHttpClientTest, threeByNineByOne) {
    size_t num_threads = 3;
    size_t num_batches = 9;
    threadRequestAndReceive(num_threads, num_batches);
}

// Multi-threaded with two threads, four batches, two listeners
TEST_F(MultiThreadingHttpClientTest, twoByFourByTwo) {
    size_t num_threads = 2;
    size_t num_batches = 4;
    size_t num_listeners = 2;
    threadRequestAndReceive(num_threads, num_batches, num_listeners);
}

// Multi-threaded with four threads, four batches, two listeners
TEST_F(MultiThreadingHttpClientTest, fourByFourByTwo) {
    size_t num_threads = 4;
    size_t num_batches = 4;
    size_t num_listeners = 2;
    threadRequestAndReceive(num_threads, num_batches, num_listeners);
}

// Verifies that we can cleanly pause, resume, and shutdown while doing
// multi-threaded work.
TEST_F(MultiThreadingHttpClientTest, workPauseResumeShutdown) {
    size_t num_threads = 4;
    size_t num_batches = 4;
    size_t num_listeners = 4;
    size_t num_pauses = 3;
    workPauseResumeShutdown(num_threads, num_batches, num_listeners, num_pauses);
}

} // end of anonymous namespace
