// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/testutils/test_tls.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <tcp/mt_tcp_listener_mgr.h>
#include <tcp_test_listener.h>
#include <tcp_test_client.h>
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
using namespace isc::tcp;
using namespace isc::util;
namespace ph = std::placeholders;

namespace {

/// @brief IP address to which TCP service is bound.
const std::string SERVER_ADDRESS = "127.0.0.1";

/// @brief Port number to which TCP service is bound.
const unsigned short SERVER_PORT = 18123;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Test fixture class for @ref MtTcpListenerMgr.
class MtTcpListenerMgrTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Starts test timer which detects timeouts, and enables multi-threading mode.
    MtTcpListenerMgrTest()
        : mt_listener_mgr_(), io_service_(), test_timer_(io_service_),
          run_io_service_timer_(io_service_), clients_(), num_threads_(),
          num_clients_(), num_in_progress_(0), num_finished_(0), chunk_size_(0),
          pause_cnt_(0), response_handler_(0) {
        test_timer_.setup(std::bind(&MtTcpListenerMgrTest::timeoutHandler, this, true),
                          TEST_TIMEOUT, IntervalTimer::ONE_SHOT);

        // Enable multi-threading.
        MultiThreadingMgr::instance().setMode(true);
    }

    /// @brief Destructor.
    ///
    /// Removes TCP clients and disables MT.
    virtual ~MtTcpListenerMgrTest() {
        // Wipe out the listener.
        mt_listener_mgr_.reset();

        // Destroy all remaining clients.
        for (auto const& client : clients_) {
            client->close();
        }

        // Disable multi-threading.
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Replaces the test's listener with a new listener
    ///
    /// @param num_threads Number of threads the listener should use.
    /// @param response_handler Response handler connections should use
    void createMtTcpListenerMgr(size_t num_threads,
                                TcpTestConnection::ResponseHandler response_handler = 0) {
        // Create a listener with prescribed number of threads.
        ASSERT_NO_THROW_LOG(mt_listener_mgr_.reset(new MtTcpListenerMgr(
            std::bind(&MtTcpListenerMgrTest::listenerFactory, this,
                      ph::_1, ph::_2, ph::_3, ph::_4, ph::_5, ph::_6),
            IOAddress(SERVER_ADDRESS),
            SERVER_PORT, num_threads)));

        ASSERT_TRUE(mt_listener_mgr_);
        setResponseHandler(response_handler);
    }

    /// @brief Return the inner TcpTestListener's audit trail
    AuditTrailPtr getAuditTrail() {
        TcpListenerPtr l = mt_listener_mgr_->getTcpListener();
        if (!l) {
            isc_throw(Unexpected, "Test is broken? Listener is null?");
        }

        TcpTestListenerPtr listener = boost::dynamic_pointer_cast<TcpTestListener>(
                                        mt_listener_mgr_->getTcpListener());
        if (!listener) {
            isc_throw(Unexpected, "Test is broken? Listener is not a TcpTestListener");
        }

        return (listener->audit_trail_);
    }

    /// @brief TcpListener factory for MtTcpListener to instantiate new listeners.
    TcpListenerPtr listenerFactory(asiolink::IOService& io_service,
                                   const asiolink::IOAddress& server_address,
                                   const unsigned short server_port,
                                   const asiolink::TlsContextPtr& tls_context,
                                   const TcpListener::IdleTimeout& idle_timeout,
                                   const TcpConnectionFilterCallback& connection_filter) {
        TcpTestListenerPtr listener(new TcpTestListener(io_service,
                                                        server_address,
                                                        server_port,
                                                        tls_context,
                                                        idle_timeout,
                                                        connection_filter));
        // Set the response handler the listener will pass into each connection.
        listener->setResponseHandler(response_handler_);
        return (listener);
    }

    /// @brief Callback function each client invokes when done.
    ///
    /// It stops the IO service
    ///
    /// @param fail_on_timeout Specifies if test failure should be reported.
    void clientDone() {
        io_service_.stop();
    }

    /// @brief Initiates a command via a new TCP client.
    ///
    /// This method creates a TcpTestClient instance, adds the
    /// client to the list of clients, and starts a request.
    /// The client will run on the main thread and be driven by
    /// the test's IOService instance.
    ///
    /// @param request_str String containing the request
    /// to be sent.
    void startRequest(const std::string& request_str) {
        // Instantiate the client.
        TcpTestClientPtr client(new TcpTestClient(io_service_,
                                                  std::bind(&MtTcpListenerMgrTest::clientDone, this),
                                                  TlsContextPtr(),
                                                  SERVER_ADDRESS, SERVER_PORT));
        // Add it to the list of clients.
        clients_.push_back(client);

        // Start the request.  Note, nothing happens until the IOService runs.
        client->startRequest(request_str);
    }

    /// @brief Initiates a "thread" command via a new TCP client.
    ///
    /// This method creates a TcpTestClient instance, adds the
    /// client to the list of clients, and starts a request based
    /// on the given command. The client will run on the main
    /// thread and be driven by the test's IOService instance.
    ///
    /// The command has a single argument, "client-ptr". The function creates
    /// the value for this argument from the pointer address of client instance
    /// it creates.  This argument should be echoed back in the response, along
    /// with the thread-id of the MtTcpListener thread which handled the
    /// command. The response body should look this:
    ///
    /// ```
    /// [ { "arguments": { "client-ptr": "xxxxx", "thread-id": "zzzzz" }, "result": 0} ]
    /// ```
    void startThreadCommand(std::string request_str) {
        // Create a new client.
        TcpTestClientPtr client(new TcpTestClient(io_service_,
                                                  std::bind(&MtTcpListenerMgrTest::clientDone, this),
                                                  TlsContextPtr(),
                                                  SERVER_ADDRESS, SERVER_PORT));

        // Construct the "thread" command post including the argument,
        // "client-ptr", whose value is the stringified pointer to the
        // newly created client.
        std::stringstream request_body;
        request_body << "{\"command\": \"thread\", \"arguments\": { \"client-ptr\": \""
                     << client << "\", \"request\": \"" << request_str << "\" } }";

        // Add it to the list of clients.
        clients_.push_back(client);

        // Start the request.  Note, nothing happens until the IOService runs.
        ASSERT_NO_THROW_LOG(client->startRequest(request_body.str()));
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

    /// @brief Set the response handler use by each connection.
    ///
    /// Sets the response handler invoked by requestReceived.
    ///
    /// @param response_handler Handler function to invoke
    void setResponseHandler(TcpTestConnection::ResponseHandler response_handler) {
        response_handler_ = response_handler;
    };

    /// @brief Response handler for the 'thread' command.
    ///
    /// @param request JSON text containing thread command and arguments
    /// which should contain one string element, "client-ptr", whose value is
    /// the stringified pointer to the client that issued the command.
    ///
    /// @return Returns JSON text containing the response which should include
    /// a string value 'thread-id': <thread id>
    std::string synchronizedCommandHandler(const std::string& request) {
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

        // Parse the command.
        ConstElementPtr command = Element::fromJSON(request);
        ConstElementPtr command_arguments;
        std::string command_str = parseCommand(command_arguments, command);

        // First we echo the client-ptr command argument.
        ConstElementPtr client_ptr = command_arguments->get("client-ptr");
        if (!client_ptr) {
            return (createAnswerString(CONTROL_RESULT_ERROR, "missing client-ptr"));
        }

        arguments->set("client-ptr", client_ptr);

        // Now we add the thread-id.
        std::stringstream ss;
        ss << std::this_thread::get_id();
        arguments->set("thread-id", Element::create(ss.str()));
        arguments->set("sign-off", Element::create("good bye"));

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

        EXPECT_THROW(mt_listener_mgr_->start(), InvalidOperation);
        EXPECT_THROW(mt_listener_mgr_->pause(), MultiThreadingInvalidOperation);
        EXPECT_THROW(mt_listener_mgr_->resume(), MultiThreadingInvalidOperation);
        EXPECT_THROW(mt_listener_mgr_->stop(), MultiThreadingInvalidOperation);

        // We're done, ship it!
        std::string str = createAnswerString(CONTROL_RESULT_SUCCESS, arguments);
        return (str);
    }

    /// @brief Create a response string of JSON
    ///
    /// @param status_code Indicates outcome of the command
    /// @param arguments Element tree of response arguments
    ///
    /// @return JSON text containing the response
    std::string createAnswerString(const int status_code, std::string text) {
        ConstElementPtr answer = createAnswer(status_code, text);
        std::stringstream os;
        answer->toJSON(os);
        return(os.str());
    }

    /// @brief Create a response string of JSON
    ///
    /// @param status_code Indicates outcome of the command
    /// @param arguments Element tree of response arguments
    ///
    /// @return JSON text containing the response
    std::string createAnswerString(const int status_code,
                                   ConstElementPtr arguments) {
        ConstElementPtr answer = createAnswer(status_code, arguments);
        std::stringstream os;
        answer->toJSON(os);
        return(os.str());
    }

    /// @brief Simple response handler for the 'thread' command.
    ///
    /// @param command_name Command name, i.e. 'thread'.
    /// @param command_arguments Command arguments should contain
    /// one string element, "client-ptr", whose value is the stringified
    /// pointer to the client that issued the command.
    ///
    /// @return Returns response with map of arguments containing
    /// a string value 'thread-id': <thread id>
    std::string simpleCommandHandler(const std::string& request) {
        // Create the map of response arguments.
        ElementPtr arguments = Element::createMap();

        // Parse the command.
        ConstElementPtr command = Element::fromJSON(request);
        ConstElementPtr command_arguments;
        std::string command_str = parseCommand(command_arguments, command);

        // First we echo the client-ptr command argument.
        ConstElementPtr client_ptr = command_arguments->get("client-ptr");
        if (!client_ptr) {
            return (createAnswerString(CONTROL_RESULT_ERROR, "missing client-ptr"));
        }

        arguments->set("client-ptr", client_ptr);

        // Now we add the thread-id.
        std::stringstream ss;
        ss << std::this_thread::get_id();
        arguments->set("thread-id", Element::create(ss.str()));
        arguments->set("sign-off", Element::create("good bye"));

        // We're done, ship it!
        std::string str = createAnswerString(CONTROL_RESULT_SUCCESS, arguments);
        return (str);
    }

    /// @brief Submits one or more thread commands to a MtTcpListener.
    ///
    /// This function command will create a MtTcpListener
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
    /// @param num_threads - the number of threads the MtTcpListener
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

        // Create an MtTcpListenerMgr with prescribed number of threads.
        createMtTcpListenerMgr(num_threads,
                               std::bind(&MtTcpListenerMgrTest::synchronizedCommandHandler,
                                          this, ph::_1));

        // Start it and verify it is running.
        ASSERT_NO_THROW_LOG(mt_listener_mgr_->start());
        ASSERT_TRUE(mt_listener_mgr_->isRunning());
        EXPECT_EQ(mt_listener_mgr_->getThreadCount(), num_threads);

        // Maps the number of clients served by a given thread-id.
        std::map<std::string, int> clients_per_thread;

        // Initiate the prescribed number of command requests.
        num_in_progress_ = 0;
        while (clients_.size() < num_clients) {
            ASSERT_NO_THROW_LOG(startThreadCommand("I am done"));
        }

        // Now we run the client-side IOService until all requests are done,
        // errors occur or the test times out.
        ASSERT_NO_FATAL_FAILURE(runIOService());

        // Stop the listener and then verify it has stopped.
        ASSERT_NO_THROW_LOG(mt_listener_mgr_->stop());
        ASSERT_TRUE(mt_listener_mgr_->isStopped());
        EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 0);

        // Iterate over the clients, checking their outcomes.
        size_t total_responses = 0;
        for (auto const& client : clients_) {
            // Client should have completed its receive successfully.
            ASSERT_TRUE(client->receiveDone());

            // Now we walk the element tree to get the response data.  It should look
            // this:
            //
            //  {
            //      "arguments": { "client-ptr": "xxxxx",
            //                      "thread-id": "zzzzz" },
            //       "result": 0
            //  ]
            //
            // We expect 1 response.
            auto responses = client->getResponses();
            ASSERT_EQ(responses.size(), 1);

            // First we turn it into an Element tree.
            ConstElementPtr answer;
            ASSERT_NO_THROW_LOG(answer = Element::fromJSON(responses.front()));

            // Answer should be a map containing "arguments" and "results".
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

    /// @brief Pauses and resumes a MtTcpListener while it processes command
    /// requests.
    ///
    /// This function command will create a MtTcpListenerMgr
    /// with the given number of threads, initiates the given
    /// number of clients, each requesting the "thread" command,
    /// and then iteratively runs the test's IOService until all
    /// the clients have received their responses or an error occurs.
    /// It will pause and resume the listener at intervals governed
    /// by the given number of pauses.
    ///
    /// @param num_threads - the number of threads the MtTcpListener
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

        // Create an MtTcpListenerMgr with prescribed number of threads and the
        // simple handler.
        createMtTcpListenerMgr(num_threads,
                               std::bind(&MtTcpListenerMgrTest::simpleCommandHandler,
                                          this, ph::_1));

        ASSERT_TRUE(mt_listener_mgr_);

        // Start it and verify it is running.
        ASSERT_NO_THROW_LOG(mt_listener_mgr_->start());
        ASSERT_TRUE(mt_listener_mgr_->isRunning());
        EXPECT_EQ(mt_listener_mgr_->getThreadCount(), num_threads);

        // Initiate the prescribed number of command requests.
        num_in_progress_ = 0;
        while (clients_.size() < num_clients) {
            ASSERT_NO_THROW_LOG(startThreadCommand("I am done"));
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
            ASSERT_NO_THROW(mt_listener_mgr_->pause());
            ASSERT_TRUE(mt_listener_mgr_->isPaused());
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
            ASSERT_NO_THROW(mt_listener_mgr_->resume());
            ASSERT_TRUE(mt_listener_mgr_->isRunning());
        }

        // Stop the listener and then verify it has stopped.
        ASSERT_NO_THROW_LOG(mt_listener_mgr_->stop());
        ASSERT_TRUE(mt_listener_mgr_->isStopped());
        EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 0);

        // Iterate over the clients, checking their outcomes.
        size_t total_responses = 0;
        for (auto const& client : clients_) {
            // Client should have completed its receive successfully.
            ASSERT_TRUE(client->receiveDone());

            // Now we walk the element tree to get the response data.  It should look
            // this:
            //
            //  {
            //       "arguments": { "client-ptr": "xxxxx",
            //                      "sign-off": "good bye",
            //                      "thread-id": "zzzzz" },
            //       "result": 0
            //  }
            //
            // We expect one response.
            auto responses = client->getResponses();
            ASSERT_EQ(responses.size(), 1);

            // First we turn it into an Element tree.
            ConstElementPtr answer;
            ASSERT_NO_THROW_LOG(answer = Element::fromJSON(responses.front()));

            // Answer should be a map containing "arguments" and "results".
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

    /// @brief MtTcpListenerMgr instance under test.
    MtTcpListenerMgrPtr mt_listener_mgr_;

    /// @brief IO service used in drive the test and test clients.
    IOService io_service_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Asynchronous timer for running IO service for a specified amount
    /// of time.
    IntervalTimer run_io_service_timer_;

    /// @brief List of client connections.
    std::list<TcpTestClientPtr> clients_;

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

    /// @brief Number of clients that have completed their assignment or
    /// failed
    size_t clients_done_;

    /// @brief Response Handler passed down to each connection.
    TcpTestConnection::ResponseHandler response_handler_;
};

/// Verifies the construction, starting, stopping, pausing, resuming,
/// and destruction of MtTcpListener.
TEST_F(MtTcpListenerMgrTest, basics) {
    // Make sure multi-threading is off.
    MultiThreadingMgr::instance().setMode(false);
    IOAddress address(SERVER_ADDRESS);
    uint16_t port = SERVER_PORT;

    // Make sure we can create one.
    ASSERT_NO_THROW_LOG(mt_listener_mgr_.reset(
        new MtTcpListenerMgr(
            std::bind(&MtTcpListenerMgrTest::listenerFactory, this,
                      ph::_1, ph::_2, ph::_3, ph::_4, ph::_5, ph::_6),
            address, port)));

    ASSERT_TRUE(mt_listener_mgr_);

    // Verify the getters do what we expect.
    EXPECT_EQ(mt_listener_mgr_->getAddress(), address);
    EXPECT_EQ(mt_listener_mgr_->getPort(), port);
    EXPECT_EQ(mt_listener_mgr_->getThreadPoolSize(), 1);
    EXPECT_FALSE(mt_listener_mgr_->getTlsContext());

    // It should not have an IOService, should not be listening and
    // should have no threads.
    ASSERT_FALSE(mt_listener_mgr_->getThreadIOService());
    EXPECT_TRUE(mt_listener_mgr_->isStopped());
    EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 0);

    // Verify that we cannot start it when multi-threading is disabled.
    ASSERT_FALSE(MultiThreadingMgr::instance().getMode());
    ASSERT_THROW_MSG(mt_listener_mgr_->start(), InvalidOperation,
                     "MtTcpListenerMgr cannot be started"
                     " when multi-threading is disabled");

    // It should still not be listening and have no threads.
    EXPECT_TRUE(mt_listener_mgr_->isStopped());
    EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 0);

    // Enable multi-threading.
    MultiThreadingMgr::instance().setMode(true);

    // Make sure we can start it and it's listening with 1 thread.
    ASSERT_NO_THROW_LOG(mt_listener_mgr_->start());
    ASSERT_TRUE(mt_listener_mgr_->isRunning());
    EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 1);
    ASSERT_TRUE(mt_listener_mgr_->getThreadIOService());
    EXPECT_FALSE(mt_listener_mgr_->getThreadIOService()->stopped());

    // Trying to start it again should fail.
    ASSERT_THROW_MSG(mt_listener_mgr_->start(), InvalidOperation,
                     "MtTcpListenerMgr already started!");

    // Stop it and verify we're no longer listening.
    ASSERT_NO_THROW_LOG(mt_listener_mgr_->stop());
    ASSERT_TRUE(mt_listener_mgr_->isStopped());
    EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 0);
    ASSERT_FALSE(mt_listener_mgr_->getThreadIOService());

    // Make sure we can call stop again without problems.
    ASSERT_NO_THROW_LOG(mt_listener_mgr_->stop());

    // We should be able to restart it.
    ASSERT_NO_THROW_LOG(mt_listener_mgr_->start());
    ASSERT_TRUE(mt_listener_mgr_->isRunning());
    EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 1);
    ASSERT_TRUE(mt_listener_mgr_->getThreadIOService());
    EXPECT_FALSE(mt_listener_mgr_->getThreadIOService()->stopped());

    // Destroying it should also stop it.
    // If the test timeouts we know it didn't!
    ASSERT_NO_THROW_LOG(mt_listener_mgr_.reset());

    // Verify we can construct with more than one thread.
    ASSERT_NO_THROW_LOG(mt_listener_mgr_.reset(
            new MtTcpListenerMgr(
                std::bind(&MtTcpListenerMgrTest::listenerFactory, this,
                          ph::_1, ph::_2, ph::_3, ph::_4, ph::_5, ph::_6),
                address, port, 4)));

    ASSERT_NO_THROW_LOG(mt_listener_mgr_->start());
    EXPECT_EQ(mt_listener_mgr_->getAddress(), address);
    EXPECT_EQ(mt_listener_mgr_->getPort(), port);
    EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 4);
    EXPECT_EQ(mt_listener_mgr_->getThreadPoolSize(), 4);
    ASSERT_TRUE(mt_listener_mgr_->isRunning());
    ASSERT_TRUE(mt_listener_mgr_->getThreadIOService());
    EXPECT_FALSE(mt_listener_mgr_->getThreadIOService()->stopped());

    // Verify we can pause it.  We should still be listening, threads intact,
    // IOService stopped, state set to PAUSED.
    ASSERT_NO_THROW_LOG(mt_listener_mgr_->pause());
    ASSERT_TRUE(mt_listener_mgr_->isPaused());
    EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 4);
    EXPECT_EQ(mt_listener_mgr_->getThreadPoolSize(), 4);
    ASSERT_TRUE(mt_listener_mgr_->getThreadIOService());
    EXPECT_TRUE(mt_listener_mgr_->getThreadIOService()->stopped());

    // Verify we can resume it.
    ASSERT_NO_THROW_LOG(mt_listener_mgr_->resume());
    ASSERT_TRUE(mt_listener_mgr_->isRunning());
    EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 4);
    EXPECT_EQ(mt_listener_mgr_->getThreadPoolSize(), 4);
    ASSERT_TRUE(mt_listener_mgr_->getThreadIOService());
    EXPECT_FALSE(mt_listener_mgr_->getThreadIOService()->stopped());

    // Stop it and verify we're no longer listening.
    ASSERT_NO_THROW_LOG(mt_listener_mgr_->stop());
    ASSERT_TRUE(mt_listener_mgr_->isStopped());
    EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 0);
    EXPECT_EQ(mt_listener_mgr_->getThreadPoolSize(), 4);
    ASSERT_FALSE(mt_listener_mgr_->getThreadIOService());
    EXPECT_TRUE(mt_listener_mgr_->isStopped());
}

// Now we'll run some permutations of the number of listener threads
// and the number of client requests.

// One thread, one client.
TEST_F(MtTcpListenerMgrTest, oneByOne) {
    size_t num_threads = 1;
    size_t num_clients = 1;
    threadListenAndRespond(num_threads, num_clients);
}

// One thread, four clients.
TEST_F(MtTcpListenerMgrTest, oneByFour) {
    size_t num_threads = 1;
    size_t num_clients = 4;
    threadListenAndRespond(num_threads, num_clients);
}

// Four threads, one clients.
TEST_F(MtTcpListenerMgrTest, fourByOne) {
    size_t num_threads = 4;
    size_t num_clients = 1;
    threadListenAndRespond(num_threads, num_clients);
}

// Four threads, four clients.
TEST_F(MtTcpListenerMgrTest, fourByFour) {
    size_t num_threads = 4;
    size_t num_clients = 4;
    threadListenAndRespond(num_threads, num_clients);
}

// Four threads, eight clients.
TEST_F(MtTcpListenerMgrTest, fourByEight) {
    size_t num_threads = 4;
    size_t num_clients = 8;
    threadListenAndRespond(num_threads, num_clients);
}

// Six threads, eighteen clients.
TEST_F(MtTcpListenerMgrTest, sixByEighteen) {
    size_t num_threads = 6;
    size_t num_clients = 18;
    threadListenAndRespond(num_threads, num_clients);
}

// Pauses and resumes the listener while it is processing
// requests.
TEST_F(MtTcpListenerMgrTest, pauseAndResume) {
    size_t num_threads = 6;
    size_t num_clients = 18;
    size_t num_pauses = 3;
    workPauseAndResume(num_threads, num_clients, num_pauses);
}

// Check if a TLS listener can be created.
TEST_F(MtTcpListenerMgrTest, tls) {
    IOAddress address(SERVER_ADDRESS);
    uint16_t port = SERVER_PORT;
    TlsContextPtr context;
    configServer(context);

    // Make sure we can create the listener.
    ASSERT_NO_THROW_LOG(
        mt_listener_mgr_.reset(new MtTcpListenerMgr(
            std::bind(&MtTcpListenerMgrTest::listenerFactory,
                      this,
                      ph::_1, ph::_2, ph::_3, ph::_4, ph::_5, ph::_6),
        IOAddress(SERVER_ADDRESS), SERVER_PORT, 1, context))
    );

    EXPECT_EQ(mt_listener_mgr_->getAddress(), address);
    EXPECT_EQ(mt_listener_mgr_->getPort(), port);
    EXPECT_EQ(mt_listener_mgr_->getThreadPoolSize(), 1);
    EXPECT_EQ(mt_listener_mgr_->getTlsContext(), context);
    EXPECT_TRUE(mt_listener_mgr_->isStopped());
    EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 0);

    // Make sure we can start it and it's listening with 1 thread.
    ASSERT_NO_THROW_LOG(mt_listener_mgr_->start());
    ASSERT_TRUE(mt_listener_mgr_->isRunning());
    EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 1);
    ASSERT_TRUE(mt_listener_mgr_->getThreadIOService());
    EXPECT_FALSE(mt_listener_mgr_->getThreadIOService()->stopped());

    // Stop it.
    ASSERT_NO_THROW_LOG(mt_listener_mgr_->stop());
    ASSERT_TRUE(mt_listener_mgr_->isStopped());
    EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 0);
    EXPECT_EQ(mt_listener_mgr_->getThreadPoolSize(), 1);
    ASSERT_FALSE(mt_listener_mgr_->getThreadIOService());
    EXPECT_TRUE(mt_listener_mgr_->isStopped());
}

/// Verifies that idle timeout can be passed down to the internal listener.
TEST_F(MtTcpListenerMgrTest, idleTimeout) {
    // Create an MtTcpListenerMgr.
    createMtTcpListenerMgr(1, std::bind(&MtTcpListenerMgrTest::synchronizedCommandHandler,
                                        this, ph::_1));
    // Verify the default timeout value.
    EXPECT_EQ(TCP_IDLE_CONNECTION_TIMEOUT, mt_listener_mgr_->getIdleTimeout());

    // Set a new timeout value.
    mt_listener_mgr_->setIdleTimeout(200);
    EXPECT_EQ(200, mt_listener_mgr_->getIdleTimeout());

    // Start the listener, which should instantiate the internal listener.
    ASSERT_NO_THROW_LOG(mt_listener_mgr_->start());
    ASSERT_TRUE(mt_listener_mgr_->isRunning());

    // Verify the internal listener's timeout value.
    auto tcp_listener = mt_listener_mgr_->getTcpListener();
    ASSERT_TRUE(tcp_listener);
    EXPECT_EQ(200, tcp_listener->getIdleTimeout());
}

} // end of anonymous namespace
