// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify accept filter for
/// Bulk Lease Query new connections.

#include <config.h>

#include <cc/data.h>
#include <dhcpsrv/cfg_multi_threading.h>
#include <dhcpsrv/cfgmgr.h>
#include <testutils/gtest_utils.h>
#include <util/multi_threading_mgr.h>
#include <blq_service.h>
#include <lease_query_connection.h>
#include <lease_query_impl4.h>
#include <lease_query_log.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::lease_query;
using namespace isc::tcp;
using namespace isc::util;
using namespace boost::asio;

namespace {

const char* CONFIGS[] = {
    // Configuration 0 (one requester).
    "{\n"
    "  \"requesters\": [ \"127.0.0.1\" ],\n"
    "  \"advanced\": {\n"
    "    \"bulk-query-enabled\": true,\n"
    "    \"lease-query-ip\": \"127.0.0.1\",\n"
    "    \"lease-query-tcp-port\": 18123,\n"
    "    \"max-requester-connections\": 2\n"
    "  }\n"
    "}",

    // Configuration 1 (two requesters).
    "{\n"
    "  \"requesters\": [ \"127.0.0.1\", \"192.0.2.1\" ],\n"
    "  \"advanced\": {\n"
    "    \"bulk-query-enabled\": true,\n"
    "    \"lease-query-ip\": \"127.0.0.1\",\n"
    "    \"lease-query-tcp-port\": 18123,\n"
    "    \"max-requester-connections\": 3\n"
    "  }\n"
    "}",

    // Configuration 2 (one connection).
    "{\n"
    "  \"requesters\": [ \"127.0.0.1\", \"192.0.2.1\" ],\n"
    "  \"advanced\": {\n"
    "    \"bulk-query-enabled\": true,\n"
    "    \"lease-query-ip\": \"127.0.0.1\",\n"
    "    \"lease-query-tcp-port\": 18123,\n"
    "    \"max-requester-connections\": 1\n"
    "  }\n"
    "}"
};

/// @brief Test client (from lease_query_test_client.h but doing only connect).
class AcceptFilter4TestClient {
public:

    /// @brief Constructor.
    ///
    /// This constructor creates and connect new socket instance.
    ///
    /// @param io_service IO service.
    /// @param server_address string containing the IP address of the server.
    /// @param port port number of the server.
    AcceptFilter4TestClient(IOServicePtr& io_service,
                            const std::string& server_address = "127.0.0.1",
                            uint16_t port = 18123)
        : io_service_(io_service),
          socket_(io_service_->getInternalIOService()),
          server_address_(server_address),
          server_port_(port) {
        connect();
    }

    /// @brief Destructor.
    virtual ~AcceptFilter4TestClient() {
        close();
    }

    /// @brief Connect to the listener.
    void connect() {
        ip::tcp::endpoint endpoint(ip::make_address(server_address_),
                                   server_port_);
        boost::system::error_code ec;
        socket_.connect(endpoint, ec);
        if (ec) {
            ADD_FAILURE() << "error occurred while connecting: "
                          << ec.message();
        }
    }

    /// @brief Close connection.
    void close() {
        socket_.close();
    }

    /// @brief Checks if the connection is usable.
    /// (from asiolink/tcp_socket.h)
    bool isUsable() {
        if (!socket_.is_open()) {
            return (false);
        }
        socket_.non_blocking(true);
        boost::system::error_code ec;
        char data[2];
        socket_.receive(buffer(data, sizeof(data)),
                        socket_base::message_peek,
                        ec);
        return (!ec || (ec.value() == error::try_again) ||
                (ec.value() == error::would_block));
    }

    /// @brief The IO service used to handle events.
    IOServicePtr io_service_;

    /// @brief A socket used for the connection.
    ip::tcp::socket socket_;

    /// @brief IP address of the server.
    std::string server_address_;

    /// @brief IP port of the server.
    uint16_t server_port_;
};

/// @brief Type of pointers to AcceptFilter4TestClient objects.
typedef boost::shared_ptr<AcceptFilter4TestClient> AcceptFilter4TestClientPtr;

/// @brief Test fixture class for testing BulkLeaseQueryService::acceptFilter.
class AcceptFilter4Test : public ::testing::Test {
public:

    /// @brief Constructor.
    AcceptFilter4Test()
        : blq_srv_(), impl_(), clients_(), io_service_(new IOService()),
          started_counter0_(TcpConnectionPool::started_counter_),
          stopped_counter0_(TcpConnectionPool::stopped_counter_),
          rejected_counter0_(TcpConnectionPool::rejected_counter_) {
        // Set multi-threading mode.
        MultiThreadingMgr::instance().setMode(true);
        // Reset bulk lease query service.
        BulkLeaseQueryService::reset();
    }

    /// @brief Destructor.
    ~AcceptFilter4Test() {
        for (auto const& client : clients_) {
            client->close();
        }
        clients_.clear();
        io_service_->poll();
        if (blq_srv_) {
            blq_srv_->stopListener();
        }
        blq_srv_.reset();
        BulkLeaseQueryService::reset();
        if (impl_) {
            impl_.reset();
        }
        MultiThreadingMgr::instance().setMode(false);
        CfgMgr::instance().clear();
    }

    /// @brief Configure multi-threading.
    ///
    /// @param mode The mode to use in the body. Defaults to true / enabled.
    /// @param thread_count The number of threads. Defaults to 4.
    void configMultiThreading(bool mode = true, uint32_t thread_count = 4) {
        ElementPtr mcfg = Element::createMap();
        mcfg->set("enable-multi-threading", Element::create(mode));
        mcfg->set("thread-pool-size", Element::create(thread_count));
        CfgMgr::instance().getStagingCfg()->setDHCPMultiThreading(mcfg);
    }

    /// @brief Configure Bulk lease query service.
    ///
    /// @param config The configuration (e.g. CONFIGS[0]).
    void configBulkLeaseQuery(string config) {
        // Apply config.
        ElementPtr cfg;
        ASSERT_NO_THROW_LOG(cfg = Element::fromJSON(config));
        ASSERT_NO_THROW_LOG(impl_.reset(new LeaseQueryImpl4(cfg)));

        // Get the lease query service.
        blq_srv_ = BulkLeaseQueryService::instance();
        ASSERT_TRUE(blq_srv_);
        ASSERT_TRUE(blq_srv_->getBulkQueryEnabled());

        // Start listener.
        blq_srv_->startListener();
    }

    /// @brief Create and connect a new client.
    ///
    /// @param address string containing the IP address of the server.
    /// @param port port number of the server.
    void createClient(const std::string& address = "127.0.0.1",
                      uint16_t port = 18123) {
        AcceptFilter4TestClientPtr client;
        ASSERT_NO_THROW(client.reset(new AcceptFilter4TestClient(io_service_,
                                                                 address,
                                                                 port)));
        clients_.push_back(client);
    }

    /// @brief Return the number of usable clients.
    size_t countUsable() {
        size_t usable = 0;
        for (auto const& client : clients_) {
            if (client->isUsable()) {
                ++usable;
            }
        }
        return (usable);
    }

    /// @brief Wait for expected counter values.
    ///
    /// @param expected_started Expected started connection counter value.
    /// @param expected_dropped Expected dropped connection counter value.
    /// @param expected_rejected Expected rejected connection counter value.
    void waitFor(uint64_t expected_started, uint64_t expected_dropped,
                 uint64_t expected_rejected) {
        io_service_->poll();
        // Limit to 50 iterations so 5 seconds.
        uint64_t started_counter;
        uint64_t stopped_counter;
        uint64_t rejected_counter;
        for (unsigned i = 0; i < 50; ++i) {
            // Sleep 100ms.
            usleep(100000);
            io_service_->poll();
            started_counter = TcpConnectionPool::started_counter_;
            stopped_counter = TcpConnectionPool::stopped_counter_;
            rejected_counter = TcpConnectionPool::rejected_counter_;
            if ((started_counter >= expected_started) &&
                (stopped_counter >= expected_dropped) &&
                (rejected_counter >= expected_rejected)) {
                return;
            }
        }
        ASSERT_GE(started_counter, expected_started);
        ASSERT_GE(stopped_counter, expected_dropped);
        ASSERT_GE(rejected_counter, expected_rejected);
    }

    /// @brief Bulk lease query service.
    BulkLeaseQueryServicePtr blq_srv_;

    /// @brief DHCPv4 lease query implementation.
    LeaseQueryImplPtr impl_;

    /// @brief List of test clients.
    list<AcceptFilter4TestClientPtr> clients_;

    /// @brief The IO service used to handle events.
    IOServicePtr io_service_;

    /// @brief Initial started connection counter.
    const uint64_t started_counter0_;

    /// @brief Initial stopped connection counter.
    const uint64_t stopped_counter0_;

    /// @brief Initial rejected connection counter.
    const uint64_t rejected_counter0_;
};


/// @brief Verify that acceptFilter works as expected with no clients.
TEST_F(AcceptFilter4Test, basic) {
    // Multi-threading is required.
    configMultiThreading(true, 4);

    // Configure.
    configBulkLeaseQuery(CONFIGS[0]);

    // NO_ENDPOINT is forbidden.
    auto endpoint = TcpConnection::NO_ENDPOINT();
    EXPECT_FALSE(BulkLeaseQueryService::acceptFilter(endpoint));

    // Verify that ::1 is accepted.
    endpoint.address(ip::make_address("127.0.0.1"));
    EXPECT_TRUE(BulkLeaseQueryService::acceptFilter(endpoint));

    // Verify that terminated_ makes everything to be rejected.
    ASSERT_FALSE(LeaseQueryImpl::terminated_);
    LeaseQueryImpl::terminated_ = true;
    EXPECT_FALSE(BulkLeaseQueryService::acceptFilter(endpoint));
    LeaseQueryImpl::terminated_ = false;

    // Verify that unknown addresses are rejected.
    endpoint.address(ip::make_address("192.0.2.2"));
    EXPECT_FALSE(BulkLeaseQueryService::acceptFilter(endpoint));
}

/// @brief Verify that acceptFilter with one configured requester works
/// as expected, i.e. the requester can eat all connections.
TEST_F(AcceptFilter4Test, oneRequester) {
    // Multi-threading is required, limit to 1 to avoid races.
    configMultiThreading(true, 1);

    // Configure.
    configBulkLeaseQuery(CONFIGS[0]);

    // Create and connect 3 clients.
    createClient("127.0.0.1", 18123);
    createClient("127.0.0.1", 18123);
    createClient("127.0.0.1", 18123);

    // Wait for the listener to call the accept filter.
    io_service_->poll();
    waitFor(started_counter0_ + 3,
            stopped_counter0_ + 1,
            rejected_counter0_ + 1);

    // Only 2 should be usable.
    EXPECT_EQ(2, countUsable());
}

/// @brief Verify that acceptFilter with more than one configured requesters
/// works as expected, i.e. the requester can't eat all connections.
TEST_F(AcceptFilter4Test, twoRequesters) {
    // Multi-threading is required, limit to 1 to avoid races.
    configMultiThreading(true, 1);

    // Configure.
    configBulkLeaseQuery(CONFIGS[1]);

    // Create and connect 3 clients.
    createClient("127.0.0.1", 18123);
    createClient("127.0.0.1", 18123);
    createClient("127.0.0.1", 18123);

    // Wait for the listener to call the accept filter.
    io_service_->poll();
    waitFor(started_counter0_ + 3,
            stopped_counter0_ + 1,
            rejected_counter0_ + 1);

    // Only 2 should be usable.
    EXPECT_EQ(2, countUsable());
}

/// @brief Verify that acceptFilter with more than one configured requesters
/// works as expected, i.e. the requester can't eat all connections.
TEST_F(AcceptFilter4Test, differentRequesters) {
    // Multi-threading is required, limit to 1 to avoid races.
    configMultiThreading(true, 1);

    // Configure.
    configBulkLeaseQuery(CONFIGS[1]);

    // Create and connect 3 clients.
    createClient("127.0.0.1", 18123);
    createClient("127.0.0.1", 18123);
    createClient("127.0.0.1", 18123);

    // Wait for the listener to call the accept filter.
    io_service_->poll();
    waitFor(started_counter0_ + 3,
            stopped_counter0_ + 1,
            rejected_counter0_ + 1);

    // Clients should be usable.
    EXPECT_EQ(2, countUsable());

    // Reduce the number of allowed connections to 2.
    blq_srv_->setMaxRequesterConnections(2);

    // Direct call to accept filter is off by one because it does not
    // count the new accepted connection.
    ip::tcp::endpoint endpoint(ip::make_address("192.0.2.1"), 18123);
    EXPECT_TRUE(BulkLeaseQueryService::acceptFilter(endpoint));
    // But ::1 still can't eat the last slot.
    endpoint.address(ip::make_address("127.0.0.1"));
    EXPECT_FALSE(BulkLeaseQueryService::acceptFilter(endpoint));
}

/// @brief Verify that acceptFilter with only one connection works
/// as expected, i.e. the last and unique slot is available.
TEST_F(AcceptFilter4Test, oneConnection) {
    // Multi-threading is required, limit to 1 to avoid races.
    configMultiThreading(true, 1);

    // Configure.
    configBulkLeaseQuery(CONFIGS[2]);

    // Create and connect 2 clients.
    createClient("127.0.0.1", 18123);
    createClient("127.0.0.1", 18123);

    // Wait for the listener to call the accept filter.
    io_service_->poll();
    waitFor(started_counter0_ + 2,
            stopped_counter0_ + 1,
            rejected_counter0_ + 1);

    // One client should be usable.
    EXPECT_EQ(1, countUsable());
}

} // end of anonymous namespace
