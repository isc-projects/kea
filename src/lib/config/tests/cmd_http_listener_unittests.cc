// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/testutils/test_tls.h>
#include <cc/command_interpreter.h>
#include <config/cmd_http_listener.h>
#include <config/command_mgr.h>
#include <http/response.h>
#include <http/response_parser.h>
#include <http/tests/test_http_client.h>
#include <util/multi_threading_mgr.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>

#include <thread>
#include <list>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::asiolink::test;
using namespace isc::config;
using namespace isc::data;
using namespace boost::asio::ip;
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

/// @brief Test fixture class for @ref CmdHttpListener.
class CmdHttpListenerTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Starts test timer which detects timeouts, deregisters all commands
    /// from CommandMgr, and enables multi-threading mode.
    CmdHttpListenerTest()
        : listener_(), io_service_(), test_timer_(io_service_),
          run_io_service_timer_(io_service_), clients_(), num_threads_(),
          num_clients_(), num_in_progress_(0), num_finished_(0), chunk_size_(0),
          pause_cnt_(0) {
        test_timer_.setup(std::bind(&CmdHttpListenerTest::timeoutHandler, this, true),
                          TEST_TIMEOUT, IntervalTimer::ONE_SHOT);

        // Deregisters commands.
        CommandMgr::instance().deregisterAll();

        // Enable multi-threading.
        MultiThreadingMgr::instance().setMode(true);
    }

    /// @brief Destructor.
    ///
    /// Removes HTTP clients, unregisters commands, disables MT.
    virtual ~CmdHttpListenerTest() {
        // Wipe out the listener.
        listener_.reset();

        // Destroy all remaining clients.
        for (auto const& client : clients_) {
            client->close();
        }

        // Deregisters commands.
        config::CommandMgr::instance().deregisterAll();

        // Disable multi-threading.
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Constructs a complete HTTP POST given a request body.
    ///
    /// @param request_body string containing the desired request body.
    ///
    /// @return string containing the constructed POST.
    std::string buildPostStr(const std::string& request_body) {
        // Create the command string.
        std::stringstream ss;
        ss << "POST /foo/bar HTTP/1.1\r\n"
              "Content-Type: application/json\r\n"
              "Content-Length: "
              << request_body.size() << "\r\n\r\n"
              << request_body;
        return (ss.str());
    }

    /// @brief Initiates a command via a new HTTP client.
    ///
    /// This method creates a TestHttpClient instance, adds the
    /// client to the list of clients, and starts a request based
    /// on the given command. The client will run on the main
    /// thread and be driven by the test's IOService instance.
    ///
    /// @param request_body JSON String containing the API command
    /// to be sent.
    void startRequest(const std::string& request_body = "{ }") {
        std::string request_str = buildPostStr(request_body);

        // Instantiate the client.
        TestHttpClientPtr client(new TestHttpClient(io_service_, SERVER_ADDRESS,
                                                    SERVER_PORT));
        // Add it to the list of clients.
        clients_.push_back(client);

        // Start the request.  Note, nothing happens until the IOService runs.
        client->startRequest(request_str);
    }

    /// @brief Initiates a "thread" command via a new HTTP client.
    ///
    /// This method creates a TestHttpClient instance, adds the
    /// client to the list of clients, and starts a request based
    /// on the given command. The client will run on the main
    /// thread and be driven by the test's IOService instance.
    ///
    /// The command has a single argument, "client-ptr". The function creates
    /// the value for this argument from the pointer address of client instance
    /// it creates.  This argument should be echoed back in the response, along
    /// with the thread-id of the CmdHttpListener thread which handled the
    /// command. The response body should look this:
    ///
    /// ```
    /// [ { "arguments": { "client-ptr": "xxxxx", "thread-id": "zzzzz" }, "result": 0} ]
    /// ```
    void startThreadCommand() {
        // Create a new client.
        TestHttpClientPtr client(new TestHttpClient(io_service_, SERVER_ADDRESS,
                                                    SERVER_PORT));

        // Construct the "thread" command post including the argument,
        // "client-ptr", whose value is the stringified pointer to the
        // newly created client.
        std::stringstream request_body;
        request_body << "{\"command\": \"thread\", \"arguments\": { \"client-ptr\": \""
                     << client << "\" } }";

        std::string command = buildPostStr(request_body.str());

        // Add it to the list of clients.
        clients_.push_back(client);

        // Start the request.  Note, nothing happens until the IOService runs.
        ASSERT_NO_THROW_LOG(client->startRequest(command));
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
    /// We iterate over calls to asio::io_service.run(), until
    /// all the clients have completed their requests.  We do it this way
    /// because the test clients stop the io_service when they're
    /// through with a request.
    ///
    /// @param request_limit Desired number of requests the function should wait
    /// to be processed before returning.
    void runIOService(size_t request_limit = 0) {
        if (!request_limit) {
            request_limit = clients_.size();
        }

        // Loop until the clients are done, an error occurs, or the time runs out.
        size_t num_done = 0;
        while (num_done != request_limit) {
            // Always call restart() before we call run();
            io_service_.restart();

            // Run until a client stops the service.
            io_service_.run();

            // If all the clients are done receiving, the test is done.
            num_done = 0;
            for (auto const& client : clients_) {
                if (client->receiveDone()) {
                    ++num_done;
                }
            }
        }
    }

    /// @brief Create an HttpResponse from a response string.
    ///
    /// @param response_str a string containing the whole HTTP
    /// response received.
    ///
    /// @return An HttpResponse constructed from by parsing the
    /// response string.
    HttpResponsePtr parseResponse(const std::string response_str) {
        HttpResponsePtr hr(new HttpResponse());
        HttpResponseParser parser(*hr);
        parser.initModel();
        parser.postBuffer(&response_str[0], response_str.size());
        parser.poll();
        if (!parser.httpParseOk()) {
            isc_throw(Unexpected, "response_str: '" << response_str
                      << "' failed to parse: " << parser.getErrorMessage());
        }

        return (hr);
    }

    /// @brief Handler for the 'foo' command.
    ///
    /// The command needs no arguments and returns a response
    /// with a body containing:
    ///
    /// "[ { \"arguments\": [ \"bar\" ], \"result\": 0 } ]")
    ///
    /// @param command_name Command name, i.e. 'foo'.
    /// @param command_arguments Command arguments (empty).
    ///
    /// @return Returns response with a single string "bar".
    ConstElementPtr fooCommandHandler(const std::string& /*command_name*/,
                                      const ConstElementPtr& /*command_arguments*/) {
        ElementPtr arguments = Element::createList();
        arguments->add(Element::create("bar"));
        return (createAnswer(CONTROL_RESULT_SUCCESS, arguments));
    }

    /// @brief Handler for the 'thread' command.
    ///
    /// @param command_name Command name, i.e. 'thread'.
    /// @param command_arguments Command arguments should contain
    /// one string element, "client-ptr", whose value is the stringified
    /// pointer to the client that issued the command.
    ///
    /// @return Returns response with map of arguments containing
    /// a string value 'thread-id': <thread id>
    ConstElementPtr synchronizedCommandHandler(const std::string& /*command_name*/,
                                               const ConstElementPtr& command_arguments) {
        // If the number of in progress commands is less than the number
        // of threads, then wait here until we're notified.  Otherwise,
        // notify everyone and finish.  The idea is to force each thread
        // to handle the same number of requests over the course of the
        // test, making verification reliable.
        {
            std::unique_lock<std::mutex> lck(mutex_);
            ++num_in_progress_;
            if (num_in_progress_ == chunk_size_) {
                num_finished_ = 0;
                cv_.notify_all();
            } else {
                bool ret = cv_.wait_for(lck, std::chrono::seconds(10),
                                        [&]() { return (num_in_progress_ == chunk_size_); });
                if (!ret) {
                    ADD_FAILURE() << "clients failed to start work";
                }
            }
        }

        // Create the map of response arguments.
        ElementPtr arguments = Element::createMap();
        // First we echo the client-ptr command argument.
        ConstElementPtr client_ptr = command_arguments->get("client-ptr");
        if (!client_ptr) {
            return (createAnswer(CONTROL_RESULT_ERROR, "missing client-ptr"));
        }

        arguments->set("client-ptr", client_ptr);

        // Now we add the thread-id.
        std::stringstream ss;
        ss << std::this_thread::get_id();
        arguments->set("thread-id", Element::create(ss.str()));

        {
            std::unique_lock<std::mutex> lck(mutex_);
            num_finished_++;
            if (num_finished_ == chunk_size_) {
                // We're all done, notify the others and finish.
                num_in_progress_ = 0;
                cv_.notify_all();
            } else {
                // I'm done but others aren't wait here.
                bool ret = cv_.wait_for(lck, std::chrono::seconds(10),
                                        [&]() { return (num_finished_ == chunk_size_); });
                if (!ret) {
                    ADD_FAILURE() << "clients failed to finish work";
                }
            }
        }

        EXPECT_THROW(listener_->start(), InvalidOperation);
        EXPECT_THROW(listener_->pause(), MultiThreadingInvalidOperation);
        EXPECT_THROW(listener_->resume(), MultiThreadingInvalidOperation);
        EXPECT_THROW(listener_->stop(), MultiThreadingInvalidOperation);

        // We're done, ship it!
        return (createAnswer(CONTROL_RESULT_SUCCESS, arguments));
    }

    /// @brief Handler for the 'thread' command.
    ///
    /// @param command_name Command name, i.e. 'thread'.
    /// @param command_arguments Command arguments should contain
    /// one string element, "client-ptr", whose value is the stringified
    /// pointer to the client that issued the command.
    ///
    /// @return Returns response with map of arguments containing
    /// a string value 'thread-id': <thread id>
    ConstElementPtr simpleCommandHandler(const std::string& /*command_name*/,
                                         const ConstElementPtr& command_arguments) {
        // Create the map of response arguments.
        ElementPtr arguments = Element::createMap();
        // First we echo the client-ptr command argument.
        ConstElementPtr client_ptr = command_arguments->get("client-ptr");
        if (!client_ptr) {
            return (createAnswer(CONTROL_RESULT_ERROR, "missing client-ptr"));
        }

        arguments->set("client-ptr", client_ptr);

        // Now we add the thread-id.
        std::stringstream ss;
        ss << std::this_thread::get_id();
        arguments->set("thread-id", Element::create(ss.str()));

        // We're done, ship it!
        return (createAnswer(CONTROL_RESULT_SUCCESS, arguments));
    }

    /// @brief Submits one or more thread commands to a CmdHttpListener.
    ///
    /// This function command will create a CmdHttpListener
    /// with the given number of threads, initiates the given
    /// number of clients, each requesting the "thread" command,
    /// and then iteratively runs the test's IOService until all
    /// the clients have received their responses or an error occurs.
    ///
    /// It requires that the number of clients, when greater than the
    /// number of threads, be a multiple of the number of threads.  The
    /// thread command handler is structured in such a way as to ensure
    /// (we hope) that each thread handles the same number of commands.
    ///
    /// @param num_threads - the number of threads the CmdHttpListener
    /// should use. Must be greater than 0.
    /// @param num_clients - the number of clients that should issue the
    /// thread command.  Each client is used to carry out a single thread
    /// command request.  Must be greater than 0 and a multiple of num_threads
    /// if it is greater than num_threads.
    void threadListenAndRespond(size_t num_threads, size_t num_clients) {
        // First we makes sure the parameter rules apply.
        ASSERT_TRUE(num_threads);
        ASSERT_TRUE(num_clients);
        ASSERT_TRUE((num_clients < num_threads) || (num_clients % num_threads == 0));

        num_threads_ = num_threads;
        num_clients_ = num_clients;
        chunk_size_ = num_threads_;
        if (num_clients_ < chunk_size_) {
            chunk_size_ = num_clients_;
        }

        // Register the thread command handler.
        CommandMgr::instance().registerCommand("thread",
                                               std::bind(&CmdHttpListenerTest
                                                         ::synchronizedCommandHandler,
                                                         this, ph::_1, ph::_2));

        // Create a listener with prescribed number of threads.
        ASSERT_NO_THROW_LOG(listener_.reset(new CmdHttpListener(IOAddress(SERVER_ADDRESS),
                                                                SERVER_PORT, num_threads)));
        ASSERT_TRUE(listener_);

        // Start it and verify it is running.
        ASSERT_NO_THROW_LOG(listener_->start());
        ASSERT_TRUE(listener_->isRunning());
        EXPECT_EQ(listener_->getThreadCount(), num_threads);

        // Maps the number of clients served by a given thread-id.
        std::map<std::string, int> clients_per_thread;

        // Initiate the prescribed number of command requests.
        num_in_progress_ = 0;
        while (clients_.size() < num_clients) {
            ASSERT_NO_THROW_LOG(startThreadCommand());
        }

        // Now we run the client-side IOService until all requests are done,
        // errors occur or the test times out.
        ASSERT_NO_FATAL_FAILURE(runIOService());

        // Stop the listener and then verify it has stopped.
        ASSERT_NO_THROW_LOG(listener_->stop());
        ASSERT_TRUE(listener_->isStopped());
        EXPECT_EQ(listener_->getThreadCount(), 0);

        // Iterate over the clients, checking their outcomes.
        size_t total_responses = 0;
        for (auto const& client : clients_) {
            // Client should have completed its receive successfully.
            ASSERT_TRUE(client->receiveDone());

            // Client response should not be empty.
            HttpResponsePtr hr;
            std::string response_str = client->getResponse();
            ASSERT_FALSE(response_str.empty());

            // Parse the response into an HttpResponse.
            ASSERT_NO_THROW_LOG(hr = parseResponse(client->getResponse()));

            // Now we walk the element tree to get the response data.  It should look
            // this:
            //
            //  [ {
            //       "arguments": { "client-ptr": "xxxxx",
            //                      "thread-id": "zzzzz" },
            //       "result": 0
            //  } ]
            //
            // First we turn it into an Element tree.
            std::string body_str = hr->getBody();
            ConstElementPtr body;
            ASSERT_NO_THROW_LOG(body = Element::fromJSON(hr->getBody()));

            // Outermost is a list, since we're emulating agent responses.
            ASSERT_EQ(body->getType(), Element::list);
            ASSERT_EQ(body->size(), 1);

            // Answer should be a map containing "arguments" and "results".
            ConstElementPtr answer = body->get(0);
            ASSERT_EQ(answer->getType(), Element::map);

            // "result" should be 0.
            ConstElementPtr result = answer->get("result");
            ASSERT_TRUE(result);
            ASSERT_EQ(result->getType(), Element::integer);
            ASSERT_EQ(result->intValue(), 0);

            // "arguments" is a map containing "client-ptr" and "thread-id".
            ConstElementPtr arguments = answer->get("arguments");
            ASSERT_TRUE(arguments);
            ASSERT_EQ(arguments->getType(), Element::map);

            // "client-ptr" is a string.
            ConstElementPtr client_ptr = arguments->get("client-ptr");
            ASSERT_TRUE(client_ptr);
            ASSERT_EQ(client_ptr->getType(), Element::string);

            // "thread-id" is a string.
            ConstElementPtr thread_id = arguments->get("thread-id");
            ASSERT_TRUE(thread_id);
            ASSERT_EQ(thread_id->getType(), Element::string);
            std::string thread_id_str = thread_id->stringValue();

            // Make sure the response received was for this client.
            std::stringstream ss;
            ss << client;
            ASSERT_EQ(client_ptr->stringValue(), ss.str());

            // Bump the client count for the given thread-id.
            auto it = clients_per_thread.find(thread_id_str);
            if (it != clients_per_thread.end()) {
                clients_per_thread[thread_id_str] = it->second + 1;
            } else {
                clients_per_thread[thread_id_str] = 1;
            }

            ++total_responses;
        }

        // We should have responses for all our clients.
        EXPECT_EQ(total_responses, num_clients);

        // Verify we have the expected number of entries in our map.
        size_t expected_thread_count = (num_clients < num_threads ?
                                        num_clients : num_threads);

        ASSERT_EQ(clients_per_thread.size(), expected_thread_count);

        // Each thread-id ought to have handled the same number of clients.
        for (auto const& it : clients_per_thread) {
            EXPECT_EQ(it.second, num_clients / clients_per_thread.size())
                      << "thread-id: " << it.first
                      << ", clients: " << it.second << std::endl;
        }
    }

    /// @brief Pauses and resumes a CmdHttpListener while it processes command
    /// requests.
    ///
    /// This function command will create a CmdHttpListener
    /// with the given number of threads, initiates the given
    /// number of clients, each requesting the "thread" command,
    /// and then iteratively runs the test's IOService until all
    /// the clients have received their responses or an error occurs.
    /// It will pause and resume the listener at intervals governed
    /// by the given number of pauses.
    ///
    /// @param num_threads - the number of threads the CmdHttpListener
    /// should use. Must be greater than 0.
    /// @param num_clients - the number of clients that should issue the
    /// thread command.  Each client is used to carry out a single thread
    /// command request.  Must be greater than 0.
    /// @param num_pauses Desired number of times the listener should be
    /// paused during the test. Must be greater than 0.
    void workPauseAndResume(size_t num_threads, size_t num_clients,
                            size_t num_pauses) {
        // First we makes sure the parameter rules apply.
        ASSERT_TRUE(num_threads);
        ASSERT_TRUE(num_clients);
        ASSERT_TRUE(num_pauses);
        num_threads_ = num_threads;
        num_clients_ = num_clients;

        // Register the thread command handler.
        CommandMgr::instance().registerCommand("thread",
                                               std::bind(&CmdHttpListenerTest
                                                         ::simpleCommandHandler,
                                                         this, ph::_1, ph::_2));

        // Create a listener with prescribed number of threads.
        ASSERT_NO_THROW_LOG(listener_.reset(new CmdHttpListener(IOAddress(SERVER_ADDRESS),
                                                                SERVER_PORT, num_threads)));
        ASSERT_TRUE(listener_);

        // Start it and verify it is running.
        ASSERT_NO_THROW_LOG(listener_->start());
        ASSERT_TRUE(listener_->isRunning());
        EXPECT_EQ(listener_->getThreadCount(), num_threads);

        // Initiate the prescribed number of command requests.
        num_in_progress_ = 0;
        while (clients_.size() < num_clients) {
            ASSERT_NO_THROW_LOG(startThreadCommand());
        }

        // Now we run the client-side IOService until all requests are done,
        // errors occur or the test times out.  We'll pause and resume the
        // number of times given by num_pauses.
        size_t num_done = 0;
        size_t total_requests = clients_.size();
        while (num_done < total_requests) {
            // Calculate how many more requests to process before we pause again.
            // We divide the number of outstanding requests by the number of pauses
            // and stop after we've done at least that many more requests.
            size_t request_limit = (pause_cnt_ < num_pauses ?
                                    (num_done + ((total_requests - num_done) / num_pauses))
                                     : total_requests);

            // Run test IOService until we hit the limit.
            runIOService(request_limit);

            // If we've done all our pauses we should be through.
            if (pause_cnt_ == num_pauses) {
                break;
            }

            // Pause the client.
            ASSERT_NO_THROW(listener_->pause());
            ASSERT_TRUE(listener_->isPaused());
            ++pause_cnt_;

            // Check our progress.
            num_done = 0;
            for (auto const& client : clients_) {
                if (client->receiveDone()) {
                    ++num_done;
                }
            }

            // We should completed at least as many as our
            // target limit.
            ASSERT_GE(num_done, request_limit);

            // Resume the listener.
            ASSERT_NO_THROW(listener_->resume());
            ASSERT_TRUE(listener_->isRunning());
        }

        // Stop the listener and then verify it has stopped.
        ASSERT_NO_THROW_LOG(listener_->stop());
        ASSERT_TRUE(listener_->isStopped());
        EXPECT_EQ(listener_->getThreadCount(), 0);

        // Iterate over the clients, checking their outcomes.
        size_t total_responses = 0;
        for (auto const& client : clients_) {
            // Client should have completed its receive successfully.
            ASSERT_TRUE(client->receiveDone());

            // Client response should not be empty.
            HttpResponsePtr hr;
            std::string response_str = client->getResponse();
            ASSERT_FALSE(response_str.empty());

            // Parse the response into an HttpResponse.
            ASSERT_NO_THROW_LOG(hr = parseResponse(client->getResponse()));

            // Now we walk the element tree to get the response data.  It should look
            // this:
            //
            //  [ {
            //       "arguments": { "client-ptr": "xxxxx",
            //                      "thread-id": "zzzzz" },
            //       "result": 0
            //  } ]
            //
            // First we turn it into an Element tree.
            std::string body_str = hr->getBody();
            ConstElementPtr body;
            ASSERT_NO_THROW_LOG(body = Element::fromJSON(hr->getBody()));

            // Outermost is a list, since we're emulating agent responses.
            ASSERT_EQ(body->getType(), Element::list);
            ASSERT_EQ(body->size(), 1);

            // Answer should be a map containing "arguments" and "results".
            ConstElementPtr answer = body->get(0);
            ASSERT_EQ(answer->getType(), Element::map);

            // "result" should be 0.
            ConstElementPtr result = answer->get("result");
            ASSERT_TRUE(result);
            ASSERT_EQ(result->getType(), Element::integer);
            ASSERT_EQ(result->intValue(), 0);

            // "arguments" is a map containing "client-ptr" and "thread-id".
            ConstElementPtr arguments = answer->get("arguments");
            ASSERT_TRUE(arguments);
            ASSERT_EQ(arguments->getType(), Element::map);

            // "client-ptr" is a string.
            ConstElementPtr client_ptr = arguments->get("client-ptr");
            ASSERT_TRUE(client_ptr);
            ASSERT_EQ(client_ptr->getType(), Element::string);

            // "thread-id" is a string.
            ConstElementPtr thread_id = arguments->get("thread-id");
            ASSERT_TRUE(thread_id);
            ASSERT_EQ(thread_id->getType(), Element::string);
            std::string thread_id_str = thread_id->stringValue();

            // Make sure the response received was for this client.
            std::stringstream ss;
            ss << client;
            ASSERT_EQ(client_ptr->stringValue(), ss.str());

            ++total_responses;
        }

        // We should have responses for all our clients.
        EXPECT_EQ(total_responses, num_clients);

        // We should have had the expected number of pauses.
        if (!num_pauses) {
            ASSERT_EQ(pause_cnt_, 0);
        } else {
            // We allow a range on pauses of +-1.
            ASSERT_TRUE((num_pauses - 1) <= pause_cnt_ &&
                        (pause_cnt_ <= (num_pauses + 1)))
                        << " num_pauses: " << num_pauses
                        << ", pause_cnt_" << pause_cnt_;
        }
    }

    /// @brief CmdHttpListener instance under test.
    CmdHttpListenerPtr listener_;

    /// @brief IO service used in drive the test and test clients.
    IOService io_service_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Asynchronous timer for running IO service for a specified amount
    /// of time.
    IntervalTimer run_io_service_timer_;

    /// @brief List of client connections.
    std::list<TestHttpClientPtr> clients_;

    /// @brief Number of threads the listener should use for the test.
    size_t num_threads_;

    /// @brief Number of client requests to make during the test.
    size_t num_clients_;

    /// @brief Number of requests currently in progress.
    size_t num_in_progress_;

    /// @brief Number of requests that have finished.
    size_t num_finished_;

    /// @brief Chunk size of requests that need to be processed in parallel.
    ///
    /// This can either be the number of threads (if the number of requests is
    /// greater than the number of threads) or the number of requests (if the
    /// number of threads is greater than the number of requests).
    size_t chunk_size_;

    /// @brief Mutex used to lock during thread coordination.
    std::mutex mutex_;

    /// @brief Condition variable used to coordinate threads.
    std::condition_variable cv_;

    /// @brief Number of times client has been paused during the test.
    size_t pause_cnt_;
};

/// Verifies the construction, starting, stopping, pausing, resuming,
/// and destruction of CmdHttpListener.
TEST_F(CmdHttpListenerTest, basics) {
    // Make sure multi-threading is off.
    MultiThreadingMgr::instance().setMode(false);
    IOAddress address(SERVER_ADDRESS);
    uint16_t port = SERVER_PORT;

    // Make sure we can create one.
    ASSERT_NO_THROW_LOG(listener_.reset(new CmdHttpListener(address, port)));
    ASSERT_TRUE(listener_);

    // Verify the getters do what we expect.
    EXPECT_EQ(listener_->getAddress(), address);
    EXPECT_EQ(listener_->getPort(), port);
    EXPECT_EQ(listener_->getThreadPoolSize(), 1);
    EXPECT_FALSE(listener_->getTlsContext());

    // It should not have an IOService, should not be listening and
    // should have no threads.
    ASSERT_FALSE(listener_->getThreadIOService());
    EXPECT_TRUE(listener_->isStopped());
    EXPECT_EQ(listener_->getThreadCount(), 0);

    // Verify that we cannot start it when multi-threading is disabled.
    ASSERT_FALSE(MultiThreadingMgr::instance().getMode());
    ASSERT_THROW_MSG(listener_->start(), InvalidOperation,
                     "CmdHttpListener cannot be started"
                     " when multi-threading is disabled");

    // It should still not be listening and have no threads.
    EXPECT_TRUE(listener_->isStopped());
    EXPECT_EQ(listener_->getThreadCount(), 0);

    // Enable multi-threading.
    MultiThreadingMgr::instance().setMode(true);

    // Make sure we can start it and it's listening with 1 thread.
    ASSERT_NO_THROW_LOG(listener_->start());
    ASSERT_TRUE(listener_->isRunning());
    EXPECT_EQ(listener_->getThreadCount(), 1);
    ASSERT_TRUE(listener_->getThreadIOService());
    EXPECT_FALSE(listener_->getThreadIOService()->stopped());

    // Trying to start it again should fail.
    ASSERT_THROW_MSG(listener_->start(), InvalidOperation,
                     "CmdHttpListener already started!");

    // Stop it and verify we're no longer listening.
    ASSERT_NO_THROW_LOG(listener_->stop());
    ASSERT_TRUE(listener_->isStopped());
    EXPECT_EQ(listener_->getThreadCount(), 0);
    ASSERT_FALSE(listener_->getThreadIOService());

    // Make sure we can call stop again without problems.
    ASSERT_NO_THROW_LOG(listener_->stop());

    // We should be able to restart it.
    ASSERT_NO_THROW_LOG(listener_->start());
    ASSERT_TRUE(listener_->isRunning());
    EXPECT_EQ(listener_->getThreadCount(), 1);
    ASSERT_TRUE(listener_->getThreadIOService());
    EXPECT_FALSE(listener_->getThreadIOService()->stopped());

    // Destroying it should also stop it.
    // If the test timeouts we know it didn't!
    ASSERT_NO_THROW_LOG(listener_.reset());

    // Verify we can construct with more than one thread.
    ASSERT_NO_THROW_LOG(listener_.reset(new CmdHttpListener(address, port, 4)));
    ASSERT_NO_THROW_LOG(listener_->start());
    EXPECT_EQ(listener_->getAddress(), address);
    EXPECT_EQ(listener_->getPort(), port);
    EXPECT_EQ(listener_->getThreadCount(), 4);
    EXPECT_EQ(listener_->getThreadPoolSize(), 4);
    ASSERT_TRUE(listener_->isRunning());
    ASSERT_TRUE(listener_->getThreadIOService());
    EXPECT_FALSE(listener_->getThreadIOService()->stopped());

    // Verify we can pause it.  We should still be listening, threads intact,
    // IOService stopped, state set to PAUSED.
    ASSERT_NO_THROW_LOG(listener_->pause());
    ASSERT_TRUE(listener_->isPaused());
    EXPECT_EQ(listener_->getThreadCount(), 4);
    EXPECT_EQ(listener_->getThreadPoolSize(), 4);
    ASSERT_TRUE(listener_->getThreadIOService());
    EXPECT_TRUE(listener_->getThreadIOService()->stopped());

    // Verify we can resume it.
    ASSERT_NO_THROW_LOG(listener_->resume());
    ASSERT_TRUE(listener_->isRunning());
    EXPECT_EQ(listener_->getThreadCount(), 4);
    EXPECT_EQ(listener_->getThreadPoolSize(), 4);
    ASSERT_TRUE(listener_->getThreadIOService());
    EXPECT_FALSE(listener_->getThreadIOService()->stopped());

    // Stop it and verify we're no longer listening.
    ASSERT_NO_THROW_LOG(listener_->stop());
    ASSERT_TRUE(listener_->isStopped());
    EXPECT_EQ(listener_->getThreadCount(), 0);
    EXPECT_EQ(listener_->getThreadPoolSize(), 4);
    ASSERT_FALSE(listener_->getThreadIOService());
    EXPECT_TRUE(listener_->isStopped());
}

// This test verifies that an HTTP connection can be established and used to
// transmit an HTTP request and receive the response.
TEST_F(CmdHttpListenerTest, basicListenAndRespond) {

    // Create a listener with 1 thread.
    ASSERT_NO_THROW_LOG(listener_.reset(new CmdHttpListener(IOAddress(SERVER_ADDRESS),
                                                           SERVER_PORT)));
    ASSERT_TRUE(listener_);

    // Start the listener and verify it's listening with 1 thread.
    ASSERT_NO_THROW_LOG(listener_->start());
    ASSERT_TRUE(listener_->isRunning());
    EXPECT_EQ(listener_->getThreadCount(), 1);

    // Now let's send a "foo" command.  This should create a client, connect
    // to our listener, post our request and retrieve our reply.
    ASSERT_NO_THROW(startRequest("{\"command\": \"foo\"}"));
    ++num_clients_;
    ASSERT_EQ(num_clients_, clients_.size());
    ASSERT_NO_THROW(runIOService());
    TestHttpClientPtr client = clients_.front();
    ASSERT_TRUE(client);

    // Parse the response into an HttpResponse.
    HttpResponsePtr hr;
    ASSERT_NO_THROW_LOG(hr = parseResponse(client->getResponse()));

    // Without a command handler loaded, we should get an unsupported command response.
    EXPECT_EQ(hr->getBody(), "[ { \"result\": 2, \"text\": \"'foo' command not supported.\" } ]");

    // Now let's register the foo command handler.
    CommandMgr::instance().registerCommand("foo",
                                            std::bind(&CmdHttpListenerTest::fooCommandHandler,
                                                      this, ph::_1, ph::_2));
    // Try posting the foo command again.
    ASSERT_NO_THROW(startRequest("{\"command\": \"foo\"}"));
    ++num_clients_;
    ASSERT_EQ(num_clients_, clients_.size());
    ASSERT_NO_THROW(runIOService());
    client = clients_.back();
    ASSERT_TRUE(client);

    // Parse the response.
    ASSERT_NO_THROW_LOG(hr = parseResponse(client->getResponse()));

    // We should have a response from our command handler.
    EXPECT_EQ(hr->getBody(), "[ { \"arguments\": [ \"bar\" ], \"result\": 0 } ]");

    // Make sure the listener is still listening.
    ASSERT_TRUE(listener_->isRunning());
    EXPECT_EQ(listener_->getThreadCount(), 1);

    // Stop the listener then verify it has stopped.
    ASSERT_NO_THROW_LOG(listener_->stop());
    ASSERT_TRUE(listener_->isStopped());
    EXPECT_EQ(listener_->getThreadCount(), 0);
}

// Now we'll run some permutations of the number of listener threads
// and the number of client requests.

// One thread, one client.
TEST_F(CmdHttpListenerTest, oneByOne) {
    size_t num_threads = 1;
    size_t num_clients = 1;
    threadListenAndRespond(num_threads, num_clients);
}

// One thread, four clients.
TEST_F(CmdHttpListenerTest, oneByFour) {
    size_t num_threads = 1;
    size_t num_clients = 4;
    threadListenAndRespond(num_threads, num_clients);
}

// Four threads, one clients.
TEST_F(CmdHttpListenerTest, fourByOne) {
    size_t num_threads = 4;
    size_t num_clients = 1;
    threadListenAndRespond(num_threads, num_clients);
}

// Four threads, four clients.
TEST_F(CmdHttpListenerTest, fourByFour) {
    size_t num_threads = 4;
    size_t num_clients = 4;
    threadListenAndRespond(num_threads, num_clients);
}

// Four threads, eight clients.
TEST_F(CmdHttpListenerTest, fourByEight) {
    size_t num_threads = 4;
    size_t num_clients = 8;
    threadListenAndRespond(num_threads, num_clients);
}

// Six threads, eighteen clients.
TEST_F(CmdHttpListenerTest, sixByEighteen) {
    size_t num_threads = 6;
    size_t num_clients = 18;
    threadListenAndRespond(num_threads, num_clients);
}

// Pauses and resumes the listener while it is processing
// requests.
TEST_F(CmdHttpListenerTest, pauseAndResume) {
    size_t num_threads = 6;
    size_t num_clients = 18;
    size_t num_pauses = 3;
    workPauseAndResume(num_threads, num_clients, num_pauses);
}

// Check if a TLS listener can be created.
TEST_F(CmdHttpListenerTest, tls) {
    IOAddress address(SERVER_ADDRESS);
    uint16_t port = SERVER_PORT;
    TlsContextPtr context;
    configServer(context);

    // Make sure we can create the listener.
    ASSERT_NO_THROW_LOG(listener_.reset(new CmdHttpListener(address, port, 1, context)));
    EXPECT_EQ(listener_->getAddress(), address);
    EXPECT_EQ(listener_->getPort(), port);
    EXPECT_EQ(listener_->getThreadPoolSize(), 1);
    EXPECT_EQ(listener_->getTlsContext(), context);
    EXPECT_TRUE(listener_->isStopped());
    EXPECT_EQ(listener_->getThreadCount(), 0);

    // Make sure we can start it and it's listening with 1 thread.
    ASSERT_NO_THROW_LOG(listener_->start());
    ASSERT_TRUE(listener_->isRunning());
    EXPECT_EQ(listener_->getThreadCount(), 1);
    ASSERT_TRUE(listener_->getThreadIOService());
    EXPECT_FALSE(listener_->getThreadIOService()->stopped());

    // Stop it.
    ASSERT_NO_THROW_LOG(listener_->stop());
    ASSERT_TRUE(listener_->isStopped());
    EXPECT_EQ(listener_->getThreadCount(), 0);
    EXPECT_EQ(listener_->getThreadPoolSize(), 1);
    ASSERT_FALSE(listener_->getThreadIOService());
    EXPECT_TRUE(listener_->isStopped());
}

} // end of anonymous namespace
