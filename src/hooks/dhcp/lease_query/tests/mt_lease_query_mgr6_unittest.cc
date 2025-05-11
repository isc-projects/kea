// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <mt_lease_query_mgr.h>
#include <lease_query_impl_factory.h>
#include <lease_query_test_client.h>
#include <util/multi_threading_mgr.h>
#include <blq6_utils.h>
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
using namespace isc::lease_query::test;

namespace ph = std::placeholders;

namespace {

/// @brief IP address to which TCP service is bound.
const std::string SERVER_ADDRESS = "::1";

/// @brief Port number to which TCP service is bound.
const unsigned short SERVER_PORT = 18123;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Test fixture class for @ref MtLeaseQueryListenerMgr.
class MtLeaseQueryListenerMgrTest6 : public BlqPacketTest6 {
public:
    /// @brief Path name of server's duid file
    static const string duid_file_;

    /// @brief Constructor.
    ///
    /// Starts test timer which detects timeouts, and enables multi-threading mode.
    MtLeaseQueryListenerMgrTest6()
        : mt_listener_mgr_(), io_service_(new IOService()), test_timer_(io_service_),
          run_io_service_timer_(io_service_), clients_(), num_threads_(),
          num_clients_(), num_in_progress_(0), num_finished_(0),
          chunk_size_(0), pause_cnt_(0) {
        test_timer_.setup(std::bind(&MtLeaseQueryListenerMgrTest6::timeoutHandler,
                                    this, true),
                          TEST_TIMEOUT, IntervalTimer::ONE_SHOT);

        // Enable multi-threading.
        MultiThreadingMgr::instance().setMode(true);
        CfgMgr::instance().clear();
    }

    virtual void SetUp() {
        BlqPacketTest6::SetUp();
        LeaseMgrFactory::destroy();
        LeaseMgrFactory::create("type=memfile persist=false universe=6 "
                                "extended-info-tables=true");
        // Configure a server id
        CfgMgr& cfg_mgr = CfgMgr::instance();
        server_id_ = cfg_mgr.getStagingCfg()->getCfgDUID()->create(duid_file_);

        // Commit the config.
        cfg_mgr.commit();

        // Create an implementation.
        const std::string json = "{ \"requesters\" : [ \"2001:db8:3::1\" ] }";
        ConstElementPtr config;
        ASSERT_NO_THROW_LOG(config = Element::fromJSON(json));
        LeaseQueryImpl::terminated_ = false;
        ASSERT_NO_THROW_LOG(LeaseQueryImplFactory::createImpl(AF_INET6, config));
    }

    /// @brief Convenience method for getting a timeout struct
    ///
    /// @param timeout value in seconds for the timeout
    ///
    /// @return a IdleTimeout struct with the given value.
    static const TcpListener::IdleTimeout makeIdleTimeout(const long timeout
                                                          = TCP_IDLE_CONNECTION_TIMEOUT) {
        return(TcpListener::IdleTimeout(timeout));
    }

    /// @brief Destructor.
    ///
    /// Removes TCP clients and disables MT.
    virtual ~MtLeaseQueryListenerMgrTest6() {
        // Wipe out the listener manager.
        mt_listener_mgr_.reset();

        // Destroy all remaining clients.
        for (auto const& client : clients_) {
            client->close();
        }

        LeaseQueryImplFactory::destroyImpl();
        LeaseMgrFactory::destroy();
        CfgMgr::instance().clear();
        static_cast<void>(remove(duid_file_.c_str()));

        test_timer_.cancel();
        io_service_->stopAndPoll();

        // Disable multi-threading.
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Replaces the test's listener with a new listener.
    ///
    /// @param num_threads Number of threads the  listener should use.
    void createMtLeaseQueryListenerMgr(size_t num_threads) {
        // Create a listener with prescribed number of threads.
        ASSERT_NO_THROW_LOG(mt_listener_mgr_.reset(new MtLeaseQueryListenerMgr(
            IOAddress(SERVER_ADDRESS), SERVER_PORT, AF_INET6,
            makeIdleTimeout(), num_threads)));

        ASSERT_TRUE(mt_listener_mgr_);
    }

    /// @brief Callback function each client invokes when done.
    ///
    /// It stops the IO service.
    ///
    /// @param fail_on_timeout Specifies if test failure should be reported.
    void clientDone() {
        // They're all done or dead. Stop the service.
       io_service_->stop();
    }

    /// @brief Initiates a command via a new TCP client.
    ///
    /// This method creates a TcpTestClient instance, adds the
    /// client to the list of clients, and starts a request.
    /// The client will run on the main thread and be driven by
    /// the test's IOService instance.
    ///
    /// @param request_str String containing the request to be sent.
    void startRequest(BlqQueryPtr request) {
        // Instantiate the client.
        LeaseQueryTestClientPtr client(
            new LeaseQueryTestClient(io_service_,
                                     std::bind(&MtLeaseQueryListenerMgrTest6::clientDone, this),
                                     AF_INET6, SERVER_ADDRESS, SERVER_PORT));

        // Add it to the list of clients.
        clients_.push_back(client);

        // Start the request.  Note, nothing happens until the IOService runs.
        client->startRequest(request);
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
    /// We iterate over calls to asio::io_context.run(), until
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
            io_service_->stop();
            io_service_->restart();

            // Run until a client stops the service.
            io_service_->run();

            // If all the clients are done receiving, the test is done.
            num_done = 0;
            for (auto const& client : clients_) {
                if (client->receiveDone() || client->expectedEof()) {
                    ++num_done;
                }
            }
        }
    }

    /// Verifies the construction, starting, stopping, pausing, resuming,
    /// and destruction of MtLeaseQueryListener.
    void testBasicOperation() {
        // Make sure multi-threading is off.
        MultiThreadingMgr::instance().setMode(false);
        IOAddress address(SERVER_ADDRESS);
        uint16_t port = SERVER_PORT;

        // Make sure we can create one.
        ASSERT_NO_THROW_LOG(mt_listener_mgr_.reset(
            new MtLeaseQueryListenerMgr(address, port, AF_INET6,
                                        makeIdleTimeout(789))));

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

        // TcpListener should exist and timeout should be set.
        ASSERT_TRUE(mt_listener_mgr_->getTcpListener());
        EXPECT_EQ(789, mt_listener_mgr_->getTcpListener()->getIdleTimeout());

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
            new MtLeaseQueryListenerMgr(address, port, AF_INET6,
                                        makeIdleTimeout(), 4)));

        ASSERT_NO_THROW_LOG(mt_listener_mgr_->start());
        EXPECT_EQ(mt_listener_mgr_->getAddress(), address);
        EXPECT_EQ(mt_listener_mgr_->getPort(), port);
        EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 4);
        EXPECT_EQ(mt_listener_mgr_->getThreadPoolSize(), 4);
        ASSERT_TRUE(mt_listener_mgr_->isRunning());
        ASSERT_TRUE(mt_listener_mgr_->getThreadIOService());
        EXPECT_FALSE(mt_listener_mgr_->getThreadIOService()->stopped());

        // Verify we can pause it.  We should still be listening,
        // threads intact, IOService stopped, state set to PAUSED.
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

    // Verifies listener can be created with a TLS context.
    void testTlsContext() {
        IOAddress address(SERVER_ADDRESS);
        uint16_t port = SERVER_PORT;
        TlsContextPtr context;
        configServer(context);

        // Make sure we can create the listener with a context.
        ASSERT_NO_THROW_LOG(mt_listener_mgr_.reset(
            new MtLeaseQueryListenerMgr(address, port, AF_INET6,
                                        makeIdleTimeout(), 1, context));
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

    // Verifies idle timeout can be set.
    void testIdleTimeout() {
        // Create an  MtLeaseQueryListenerMgr.
        createMtLeaseQueryListenerMgr(1);

        // Verify the default timeout value.
        EXPECT_EQ(TCP_IDLE_CONNECTION_TIMEOUT,
                  mt_listener_mgr_->getIdleTimeout());

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

    /// @brief Constructs a DHCPv6 bulk query by IP address.
    ///
    /// @param qr_iaaddr Address to query for.
    /// @return An BlqQuery containing the query packet.
    BlqQueryPtr makeBlqQueryByIpAddress(const IOAddress& qry_iaaddr) {
        PktPtr lq = makeQueryByIpAddress6(qry_iaaddr);
        return (BlqQueryPtr(new BlqQuery(lq)));
    }

    /// @brief Submits one or more thread commands to a MtLeaseQueryListener.
    ///
    /// This function command will create a MtLeaseQueryListener
    /// with the given number of threads, initiates the given
    /// number of clients, each requesting a query, and then iteratively
    /// runs the test's IOService until all the clients have received their
    /// responses or an error occurs.
    ///
    /// It requires that the number of clients, when greater than the
    /// number of threads, be a multiple of the number of threads.  The
    /// thread command handler is structured in such a way as to ensure
    /// (we hope) that each thread handles the same number of commands.
    ///
    /// @param num_threads - the number of threads the MtLeaseQueryListener
    /// should use. Must be greater than 0.
    /// @param num_clients - the number of clients that should issue the
    /// thread command.  Each client is used to carry out a single thread
    /// command request.  Must be greater than 0 and a multiple of num_threads
    /// if it is greater than num_threads.
    void threadListenAndRespond(size_t num_threads, size_t num_clients) {
        // First we makes sure the parameter rules apply.
        ASSERT_TRUE(num_threads);
        ASSERT_TRUE(num_clients);

        num_threads_ = num_threads;
        num_clients_ = num_clients;

        // Create an  MtLeaseQueryListenerMgr with prescribed number of threads.
        createMtLeaseQueryListenerMgr(num_threads);

        // Start it and verify it is running.
        ASSERT_NO_THROW_LOG(mt_listener_mgr_->start());
        ASSERT_TRUE(mt_listener_mgr_->isRunning());
        EXPECT_EQ(mt_listener_mgr_->getThreadCount(), num_threads);

        // Maps the number of clients served by a given thread-id.
        std::map<std::string, int> clients_per_thread;

        // Initiate the prescribed number of command requests.
        num_in_progress_ = 0;
        while (clients_.size() < num_clients) {
            BlqQueryPtr request = makeBlqQueryByIpAddress(IOAddress("2001:db8::1"));
            ASSERT_NO_THROW_LOG(startRequest(request));
        }

        // Now we run the client-side IOService until all requests are done,
        // errors occur or the test times out.
        ASSERT_NO_FATAL_FAILURE(runIOService());

        // Stop the listener and then verify it has stopped.
        ASSERT_NO_THROW_LOG(mt_listener_mgr_->stop());
        ASSERT_TRUE(mt_listener_mgr_->isStopped());
        EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 0);

        // Iterate over the clients, checking their outcomes.
        for (auto const& client : clients_) {
            ASSERT_TRUE(client->receiveDone());
            ASSERT_FALSE(client->expectedEof());

            // Client should have completed its receive successfully.
            client->checkResponses();
        }
    }

    /// @brief Pauses and resumes a MtLeaseQueryListener while it
    /// processes command requests.
    ///
    /// This function command will create a MtLeaseQueryListenerMgr
    /// with the given number of threads, initiates the given
    /// number of clients, each requesting the "thread" command,
    /// and then iteratively runs the test's IOService until all
    /// the clients have received their responses or an error occurs.
    /// It will pause and resume the listener at intervals governed
    /// by the given number of pauses.
    ///
    /// @param num_threads - the number of threads the MtLeaseQueryListener
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

        // Create an MtLeaseQueryListenerMgr with prescribed number of
        // threads and the simple handler.
        createMtLeaseQueryListenerMgr(num_threads);

        ASSERT_TRUE(mt_listener_mgr_);

        // Start it and verify it is running.
        ASSERT_NO_THROW_LOG(mt_listener_mgr_->start());
        ASSERT_TRUE(mt_listener_mgr_->isRunning());
        EXPECT_EQ(mt_listener_mgr_->getThreadCount(), num_threads);

        // Initiate the prescribed number of command requests.
        num_in_progress_ = 0;
        while (clients_.size() < num_clients) {
            BlqQueryPtr request =
                makeBlqQueryByIpAddress(IOAddress("2001:db8::1"));
            ASSERT_NO_THROW_LOG(startRequest(request));
        }

        // Now we run the client-side IOService until all requests are done,
        // errors occur or the test times out.  We'll pause and resume the
        // number of times given by num_pauses.
        size_t num_done = 0;
        size_t total_requests = clients_.size();
        while (num_done < total_requests) {
            // Calculate how many more requests to process before we
            // pause again.  We divide the number of outstanding
            // requests by the number of pauses and stop after we've
            // done at least that many more requests.
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

            // We should completed at least as many as our target limit.
            ASSERT_GE(num_done, request_limit);

            // Resume the listener.
            ASSERT_NO_THROW(mt_listener_mgr_->resume());
            ASSERT_TRUE(mt_listener_mgr_->isRunning());
        }

        // Stop the listener and then verify it has stopped.
        ASSERT_NO_THROW_LOG(mt_listener_mgr_->stop());
        ASSERT_TRUE(mt_listener_mgr_->isStopped());
        EXPECT_EQ(mt_listener_mgr_->getThreadCount(), 0);

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

        // Iterate over the clients, checking their outcomes.
        for (auto const& client : clients_) {
            ASSERT_TRUE(client->receiveDone());
            ASSERT_FALSE(client->expectedEof());

            // Client should have completed its receive successfully.
            client->checkResponses();
        }
    }

    /// @brief MtLeaseQueryListenerMgr instance under test.
    MtLeaseQueryListenerMgrPtr mt_listener_mgr_;

    /// @brief IO service used in drive the test and test clients.
    IOServicePtr io_service_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Asynchronous timer for running IO service for a specified amount
    /// of time.
    IntervalTimer run_io_service_timer_;

    /// @brief List of client connections.
    std::list<LeaseQueryTestClientPtr> clients_;

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

    /// @brief Convenience values.</font>
    DuidPtr server_id_;
};

/// @brief Path name for server-id generation
const string MtLeaseQueryListenerMgrTest6::duid_file_
    = string(TEST_DATA_BUILDDIR) + string("/lq6-duid");

/// Verifies the construction, starting, stopping, pausing, resuming,
/// and destruction of MtLeaseQueryListener.
TEST_F(MtLeaseQueryListenerMgrTest6, basics) {
    testBasicOperation();
}

// Now we'll run some permutations of the number of listener threads
// and the number of client requests.

// One thread, one client.
TEST_F(MtLeaseQueryListenerMgrTest6, oneByOne) {
    size_t num_threads = 1;
    size_t num_clients = 1;
    threadListenAndRespond(num_threads, num_clients);
}

// One thread, four clients.
TEST_F(MtLeaseQueryListenerMgrTest6, oneByFour) {
    size_t num_threads = 1;
    size_t num_clients = 4;
    threadListenAndRespond(num_threads, num_clients);
}

// Four threads, one clients.
TEST_F(MtLeaseQueryListenerMgrTest6, fourByOne) {
    size_t num_threads = 4;
    size_t num_clients = 1;
    threadListenAndRespond(num_threads, num_clients);
}

// Four threads, four clients.
TEST_F(MtLeaseQueryListenerMgrTest6, fourByFour) {
    size_t num_threads = 4;
    size_t num_clients = 4;
    threadListenAndRespond(num_threads, num_clients);
}

// Four threads, eight clients.
TEST_F(MtLeaseQueryListenerMgrTest6, fourByEight) {
    size_t num_threads = 4;
    size_t num_clients = 8;
    threadListenAndRespond(num_threads, num_clients);
}

// Six threads, eighteen clients.
TEST_F(MtLeaseQueryListenerMgrTest6, sixByEighteen) {
    size_t num_threads = 6;
    size_t num_clients = 18;
    threadListenAndRespond(num_threads, num_clients);
}

// Pauses and resumes the listener while it is processing
// requests.
TEST_F(MtLeaseQueryListenerMgrTest6, pauseAndResume) {
    size_t num_threads = 6;
    size_t num_clients = 18;
    size_t num_pauses = 3;
    workPauseAndResume(num_threads, num_clients, num_pauses);
}

// Check if a TLS listener can be created.
TEST_F(MtLeaseQueryListenerMgrTest6, tls) {
    testTlsContext();
}

/// Verifies that idle timeout can be passed down to the internal listener.
TEST_F(MtLeaseQueryListenerMgrTest6, idleTimeout) {
    testIdleTimeout();
}

} // end of anonymous namespace
