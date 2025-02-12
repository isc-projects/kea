// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <cc/data.h>
#include <dhcp/testutils/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <blq_service.h>
#include <bulk_lease_query.h>
#include <bulk_lease_query4.h>
#include <lease_query_test_client.h>
#include <util/multi_threading_mgr.h>
#include <lease_query_listener.h>
#include <blq4_utils.h>

#include <gtest/gtest.h>

using namespace boost::asio::ip;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::tcp;
using namespace isc::util;
using namespace isc::lease_query;
using namespace isc::lease_query::test;

namespace ph = std::placeholders;

namespace {

/// @brief IP address to which service is bound.
const std::string SERVER_ADDRESS = "127.0.0.1";

/// @brief Port number to which service is bound.
const unsigned short SERVER_PORT = 18123;

/// @brief Connection idle timeout used in most of the tests (ms).
const long IDLE_TIMEOUT = 10000;

/// @brief Connection idle timeout used in tests where idle connections
/// are tested (ms).
const long SHORT_IDLE_TIMEOUT = 200;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Simple test fixture for testing XidQueue.
class XidQueue4Test : public ::testing::Test {
public:
    /// @brief Class of test queries..
    class TestQuery {
    public:
        /// @brief Constructor.
        ///
        /// @param xid Xid of the query.
        /// @param xid address ip address used in the query.
        TestQuery(const Xid& xid, const IOAddress& address) :
            xid_(xid), address_(address) {
        }

        /// @brief Destructor.
        virtual ~TestQuery() {
        }

        /// @brief Get xid.
        Xid getXid() const {
            return (xid_);
        }

   private:
        /// The xid.
        Xid xid_;

        /// The address.
        IOAddress address_;
    };

    /// @brief Type of pointers to test queries.
    typedef boost::shared_ptr<TestQuery> TestQueryPtr;
};

// Verifies BulkLeaseQueryList operations.
TEST_F(XidQueue4Test, queue) {
    // Create some queries.
    TestQueryPtr query1(new TestQuery(78, IOAddress("192.0.2.1")));
    TestQueryPtr query2(new TestQuery(79, IOAddress("192.0.2.2")));
    TestQueryPtr query3(new TestQuery(80, IOAddress("192.0.2.3")));

    // Create an empty list.
    XidQueue<TestQuery> queries;
    ASSERT_EQ(0, queries.size());

    // Add a query to the list.
    ASSERT_NO_THROW(queries.add(query1));
    EXPECT_EQ(1, queries.size());
    TestQueryPtr query;

    // Verify we can find the query.
    ASSERT_NO_THROW(query = queries.find(query1->getXid()));
    ASSERT_TRUE(query);
    EXPECT_EQ(query, query1);

    // Add a second one.
    ASSERT_NO_THROW(queries.add(query2));
    EXPECT_EQ(2, queries.size());

    // Verify we can find it.
    ASSERT_NO_THROW(query = queries.find(query2->getXid()));
    ASSERT_TRUE(query);
    EXPECT_EQ(query, query2);

    // Add another one.
    ASSERT_NO_THROW(queries.add(query3));
    EXPECT_EQ(3, queries.size());

    // Verify we can find the last one.
    ASSERT_NO_THROW(query = queries.find(query3->getXid()));
    ASSERT_TRUE(query);
    EXPECT_EQ(query, query3);

    // Remove one.
    ASSERT_NO_THROW(queries.remove(query2->getXid()));
    EXPECT_EQ(2, queries.size());

    // Verify it's gone.
    ASSERT_NO_THROW(query = queries.find(query2->getXid()));
    EXPECT_FALSE(query);

    // Pop the first.
    ASSERT_NO_THROW(query = queries.pop());
    ASSERT_TRUE(query);
    EXPECT_EQ(query, query1);
    EXPECT_EQ(1, queries.size());

    // Clear the list.
    ASSERT_NO_THROW(queries.clear());
    EXPECT_EQ(0, queries.size());
}

/// @brief Test fixture class for @ref LeaseQueryListener.  It exercises
/// connections and responding to clients.
class LeaseQueryListenerTest4 : public BlqPacketTest4{
public:
    /// @brief Constructor.
    ///
    /// Starts test timer which detects timeouts.
    LeaseQueryListenerTest4()
        : io_service_(new IOService()), test_timer_(io_service_),
          run_io_service_timer_(io_service_),
          clients_(), clients_done_(0) {
          test_timer_.setup(std::bind(&LeaseQueryListenerTest4::timeoutHandler,
                                      this, true),
                            TEST_TIMEOUT,
                            IntervalTimer::ONE_SHOT);
        CfgMgr::instance().clear();
    }

    virtual void SetUp() {
        BlqPacketTest4::SetUp();
        LeaseMgrFactory::destroy();
        LeaseMgrFactory::create("type=memfile persist=false universe=4");

        // Enable multi-threading.
        MultiThreadingMgr::instance().setMode(true);
        ElementPtr mt_config = Element::createMap();
        mt_config->set("enable-multi-threading", Element::create(true));
        mt_config->set("thread-pool-size", Element::create(4));
        mt_config->set("queue-size", Element::create(16));
        CfgMgr::instance().getStagingCfg()->setDHCPMultiThreading(mt_config);
        CfgMgr::instance().commit();

        // Enable bulk service.
        ElementPtr cfg = Element::createMap();
        cfg->set("requesters", Element::fromJSON("[ \"127.0.0.1\" ]"));
        ElementPtr advanced = Element::createMap();
        cfg->set("advanced", advanced);
        LeaseQueryImplPtr impl_;
        ASSERT_NO_THROW(impl_.reset(new LeaseQueryImpl4(cfg)));
        EXPECT_TRUE(BulkLeaseQueryService::instance());
    }

    /// @brief Destructor.
    ///
    /// Removes active clients.
    virtual ~LeaseQueryListenerTest4() {
        for (auto const& client : clients_) {
            client->close();
        }

        BulkLeaseQueryService::reset();
        LeaseMgrFactory::destroy();
        CfgMgr::instance().clear();
        test_timer_.cancel();
        io_service_->stopAndPoll();
    }

    /// @brief Create a new listener.
    virtual LeaseQueryListenerPtr
    makeListener(const TlsContextPtr& tls_context,
                 const TcpListener::IdleTimeout& idle_timeout,
                 const TcpConnectionFilterCallback& filter_callback = 0) {
        LeaseQueryListenerPtr listener(
            new LeaseQueryListener(io_service_,
                                   IOAddress(SERVER_ADDRESS),
                                   SERVER_PORT,
                                   tls_context,
                                   idle_timeout,
                                   filter_callback,
                                   AF_INET));
        return (listener);
    }

    /// @brief Create client.
    ///
    /// This method creates LeaseQueryTestClient instance and retains it
    /// in the clients_ list.
    LeaseQueryTestClientPtr createClient() {
        LeaseQueryTestClientPtr client(new LeaseQueryTestClient(io_service_,
                                       std::bind(&LeaseQueryListenerTest4::clientDone, this),
                                       AF_INET));
        clients_.push_back(client);
        return (client);
    }

    /// @brief Connect to the endpoint.
    ///
    /// This method creates LeaseQueryTestClient instance and retains it
    /// in the clients_ list.
    void connectClient() {
        LeaseQueryTestClientPtr client = createClient();
        if (!client) {
            isc_throw(isc::Unexpected, "failed to create a client");
        }
        client->connect();
    }

    /// @brief Connect to the endpoint and send a request.
    ///
    /// This method creates a LeaseQueryTestClient instance and initiates a
    /// request.
    ///
    /// @param request String containing the request to be sent.
    void startRequest(BlqQueryPtr query) {
        LeaseQueryTestClientPtr client = createClient();
        client->startRequest(query);
    }

    /// @brief Connect to the endpoint and send a list of requests.
    ///
    /// This method creates a LeaseQueryTestClient instance and initiates a
    /// series of requests.
    ///
    /// @param request String containing the request to be sent.
    void startRequests(const std::list<BlqQueryPtr>& requests) {
        LeaseQueryTestClientPtr client = createClient();
        client->startRequests(requests);
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

    /// @brief Callback function each client invokes when done.
    ///
    /// It stops the IO service when all clients are done.
    ///
    /// @param fail_on_timeout Specifies if test failure should be reported.
    void clientDone() {
        ++clients_done_;
        if (clients_done_ >= clients_.size()) {
            // They're all done or dead. Stop the service.
            io_service_->stop();
        }
    }

    /// @brief Runs IO service with optional timeout.
    ///
    /// @param timeout Optional value specifying for how long the io service
    /// should be ran.
    void runIOService(long timeout = 0) {
        io_service_->stop();
        io_service_->restart();

        if (timeout > 0) {
            run_io_service_timer_.setup(std::bind(&LeaseQueryListenerTest4::timeoutHandler,
                                                  this, false),
                                        timeout,
                                        IntervalTimer::ONE_SHOT);
        }
        io_service_->run();
        io_service_->stopAndPoll();
    }

    /// @brief Filter that denies every other connection.
    ///
    /// @param remote_endpoint_address ip address of the remote end of
    /// a connection.
    bool connectionFilter(const boost::asio::ip::tcp::endpoint& remote_endpoint) {
        static size_t count = 0;
        // If the address doesn't match, something hinky is going on, so
        // we'll reject them all.  If it does match, then cool, it works
        // as expected.
        if ((count++ % 2) ||
            (remote_endpoint.address().to_string() != SERVER_ADDRESS)) {
            // Reject every other connection.
            return (false);
        }

        return (true);
    }

    /// @brief Constructs a DHCPv4 bulk query by client id.
    ///
    /// @param qry_client_id Client id to query for.
    /// @return An BlqQuery containing the query packet.
    BlqQueryPtr makeBlqQueryByClientId(const ClientIdPtr& qry_client_id) {
        PktPtr lq = makeQueryByClientId(qry_client_id);
        return (BlqQueryPtr(new BlqQuery(lq)));
    }

    /// @brief IO service used in the tests.
    IOServicePtr io_service_;

    /// @brief Asynchronous timer service to detect timeouts.
    IntervalTimer test_timer_;

    /// @brief Asynchronous timer for running IO service for a specified amount
    /// of time.
    IntervalTimer run_io_service_timer_;

    /// @brief List of client connections.
    std::list<LeaseQueryTestClientPtr> clients_;

    /// @brief Counts the number of clients that have reported as done.
    size_t clients_done_;
};

// This test verifies that A TCP connection can be established and used to
// transmit a V4 LeaseBulkQuery query and receive a LeaseBulkQuery response.
TEST_F(LeaseQueryListenerTest4, listen) {
    LeaseQueryListenerPtr listener =
        makeListener(TlsContextPtr(),
                     TcpListener::IdleTimeout(IDLE_TIMEOUT),
                     TcpConnectionFilterCallback(0));
    ASSERT_TRUE(listener);

    ASSERT_NO_THROW(listener->start());
    ASSERT_EQ(SERVER_ADDRESS, listener->getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener->getLocalPort());

    ClientIdPtr cid(new ClientId(vector<uint8_t>{ 1, 2, 3, 4 }));
    BlqQueryPtr request = makeBlqQueryByClientId(cid);
    ASSERT_NO_THROW(startRequest(request));

    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(1, clients_.size());
    LeaseQueryTestClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_TRUE(client->receiveDone());
    EXPECT_FALSE(client->expectedEof());
    client->checkResponses();

    listener->stop();
    io_service_->poll();
}

// This test verifies that A TCP connection will be timed out and closed if
// it remains idle for longer than the idle timeout.
TEST_F(LeaseQueryListenerTest4, idleTimeoutTest) {
    LeaseQueryListenerPtr listener =
        makeListener(TlsContextPtr(),
                     TcpListener::IdleTimeout(SHORT_IDLE_TIMEOUT),
                     TcpConnectionFilterCallback(0));
    ASSERT_TRUE(listener);

    ASSERT_NO_THROW(listener->start());
    ASSERT_EQ(SERVER_ADDRESS, listener->getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener->getLocalPort());
    ASSERT_NO_THROW(connectClient());
    ASSERT_EQ(1, clients_.size());
    LeaseQueryTestClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);

    // Tell the client expecting reading to fail with an EOF.
    ASSERT_NO_THROW(client->waitForEof());

    // Run until idle timer expires.
    ASSERT_NO_THROW(runIOService());
    EXPECT_FALSE(client->receiveDone());
    EXPECT_TRUE(client->expectedEof());

    listener->stop();
    io_service_->poll();
}

// This test verifies that a client connection can submit and receive
// responses to multiple queries.
TEST_F(LeaseQueryListenerTest4, multipleQueries) {
    LeaseQueryListenerPtr listener =
        makeListener(TlsContextPtr(),
                     TcpListener::IdleTimeout(IDLE_TIMEOUT),
                     TcpConnectionFilterCallback(0));
    ASSERT_TRUE(listener);


    ASSERT_NO_THROW(listener->start());
    ASSERT_EQ(SERVER_ADDRESS, listener->getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener->getLocalPort());
    ClientIdPtr cid(new ClientId(vector<uint8_t>{ 1, 2, 3, 4 }));
    size_t num_requests = 4;
    std::list<BlqQueryPtr> requests;
    for (auto i = 0; i < num_requests; ++i) {
        BlqQueryPtr request = makeBlqQueryByClientId(cid);
        requests.push_back(request);
    }

    ASSERT_NO_THROW(startRequests(requests));
    ASSERT_NO_THROW(runIOService());

    ASSERT_EQ(1, clients_.size());
    LeaseQueryTestClientPtr client = *clients_.begin();
    ASSERT_TRUE(client);
    EXPECT_TRUE(client->receiveDone());
    EXPECT_FALSE(client->expectedEof());
    client->checkResponses();

    listener->stop();
    io_service_->poll();
}

// This test verifies that the listener can support multiple, concurrent client
// connections.
TEST_F(LeaseQueryListenerTest4, multipleClientsListen) {
    LeaseQueryListenerPtr listener =
        makeListener(TlsContextPtr(),
                     TcpListener::IdleTimeout(IDLE_TIMEOUT),
                     TcpConnectionFilterCallback(0));
    ASSERT_TRUE(listener);

    ASSERT_NO_THROW(listener->start());
    ASSERT_EQ(SERVER_ADDRESS, listener->getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener->getLocalPort());
    ClientIdPtr cid(new ClientId(vector<uint8_t>{ 1, 2, 3, 4 }));
    size_t num_clients = 5;
    std::list<BlqQueryPtr> requests;
    for (auto i = 0; i < num_clients; ++i) {
        BlqQueryPtr request = makeBlqQueryByClientId(cid);
        ASSERT_NO_THROW(startRequest(request));
        requests.push_back(request);
    }

    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(num_clients, clients_.size());

    for (auto const& client : clients_) {
        EXPECT_TRUE(client->receiveDone());
        EXPECT_FALSE(client->expectedEof());
        client->checkResponses();
    }

    listener->stop();
    io_service_->poll();
}

// This test verifies that the listener handles multiple requests from multiple
// clients.
TEST_F(LeaseQueryListenerTest4, multipleRequetsPerClients) {
    LeaseQueryListenerPtr listener =
        makeListener(TlsContextPtr(),
                     TcpListener::IdleTimeout(IDLE_TIMEOUT),
                     TcpConnectionFilterCallback(0));
    ASSERT_TRUE(listener);

    ASSERT_NO_THROW(listener->start());
    ASSERT_EQ(SERVER_ADDRESS, listener->getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener->getLocalPort());
    ClientIdPtr cid(new ClientId(vector<uint8_t>{ 1, 2, 3, 4 }));
    size_t num_clients = 5;
    size_t num_requests = 4;
    for (auto i = 0; i < num_clients; ++i) {
        std::list<BlqQueryPtr> requests;
        for (auto j = 0; j < num_requests; ++j) {
            BlqQueryPtr request = makeBlqQueryByClientId(cid);
            requests.push_back(request);
        }

        ASSERT_NO_THROW(startRequests(requests));
    }

    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(num_clients, clients_.size());

    for (auto const& client : clients_) {
        EXPECT_TRUE(client->receiveDone());
        EXPECT_FALSE(client->expectedEof());
        EXPECT_EQ(num_requests, client->getResponses().size());
        client->checkResponses();
    }

    listener->stop();
    io_service_->poll();
}

// This test verifies that connection filtering can eliminate specific connections.
TEST_F(LeaseQueryListenerTest4, filterClientsTest) {
    LeaseQueryListenerPtr listener
        = makeListener(TlsContextPtr(),
                       TcpListener::IdleTimeout(IDLE_TIMEOUT),
                       std::bind(&LeaseQueryListenerTest4::connectionFilter, this, ph::_1));

    ASSERT_NO_THROW(listener->start());
    ASSERT_EQ(SERVER_ADDRESS, listener->getLocalAddress().toText());
    ASSERT_EQ(SERVER_PORT, listener->getLocalPort());
    ClientIdPtr cid(new ClientId(vector<uint8_t>{ 1, 2, 3, 4 }));
    size_t num_clients = 5;
    std::list<BlqQueryPtr> requests;
    for (auto i = 0; i < num_clients; ++i) {
        // Every other client sends nothing (i.e. waits for EOF) as
        // we expect the filter to reject them.
        if (i % 2 == 0) {
            BlqQueryPtr request = makeBlqQueryByClientId(cid);
            requests.push_back(request);
            ASSERT_NO_THROW(startRequest(request));
        } else {
            ASSERT_NO_THROW(startRequest(BlqQueryPtr()));
        }
    }

    ASSERT_NO_THROW(runIOService());
    ASSERT_EQ(num_clients, clients_.size());

    size_t i = 0;
    for (auto const& client : clients_) {
        if (i % 2 == 0) {
            // These clients should have been accepted and received responses.
            EXPECT_TRUE(client->receiveDone());
            EXPECT_FALSE(client->expectedEof());
            EXPECT_EQ(1, client->getResponses().size());
            client->checkResponses();
        } else {
            // These clients should have been rejected and gotten EOF'd.
            EXPECT_FALSE(client->receiveDone());
            EXPECT_TRUE(client->expectedEof());
            EXPECT_EQ(0, client->getResponses().size());
        }

        ++i;
    }

    listener->stop();
    io_service_->poll();
}

}
