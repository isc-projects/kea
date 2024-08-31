// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ha_test.h>
#include <ha_config.h>
#include <ha_config_parser.h>
#include <query_filter.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/hwaddr.h>
#include <util/multi_threading_mgr.h>

#include <cstdint>
#include <string>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::ha;
using namespace isc::ha::test;
using namespace util;

namespace  {

/// @brief Test fixture class for @c QueryFilter class.
class QueryFilterTest : public HATest {
public:
    /// @brief Constructor.
    QueryFilterTest() {
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief Destructor.
    ~QueryFilterTest() {
        MultiThreadingMgr::instance().setMode(false);
    }

    /// @brief This test verifies that client identifier is used for load
    /// balancing.
    void loadBalancingClientIdThisPrimary();

    /// @brief This test verifies the case when load balancing is enabled and
    /// this server is primary.
    void loadBalancingThisPrimary();

    /// @brief This test verifies the case when load balancing is enabled and
    /// this server is secondary.
    void loadBalancingThisSecondary();

    /// @brief This test verifies the case when load balancing is enabled and
    /// this server is backup.
    /// @todo Expand these tests once we implement the actual load balancing to
    /// verify which packets are in scope.
    void loadBalancingThisBackup();

    /// @brief This test verifies the case when hot-standby is enabled and this
    /// server is primary.
    void hotStandbyThisPrimary();

    /// @brief This test verifies the case when hot-standby is enabled and this
    /// server is standby.
    void hotStandbyThisSecondary();

    /// @brief This test verifies the case when hot-standby is enabled and this
    /// server is backup.
    void hotStandbyThisBackup();

    /// @brief This test verifies the case when load balancing is enabled and
    /// this server is primary.
    void loadBalancingThisPrimary6();

    /// @brief This test verifies the case when load balancing is enabled and
    /// this server is secondary.
    void loadBalancingThisSecondary6();

    /// @brief This test verifies the case when load balancing is enabled and
    /// this server is backup.
    /// @todo Expand these tests once we implement the actual load balancing to
    /// verify which packets are in scope.
    void loadBalancingThisBackup6();

    /// @brief This test verifies the case when hot-standby is enabled and this
    /// server is primary.
    void hotStandbyThisPrimary6();

    /// @brief This test verifies the case when hot-standby is enabled and this
    /// server is standby.
    void hotStandbyThisSecondary6();

    /// @brief This test verifies the case when hot-standby is enabled and this
    /// server is backup.
    void hotStandbyThisBackup6();

    /// @brief This test verifies that it is possible to explicitly enable and
    /// disable certain scopes.
    void explicitlyServeScopes();

    /// @brief This test verifies that load balancing only affects the scope of
    /// DHCPv4 message types that HA cares about.
    void loadBalancingHaTypes4();

    /// @brief This test verifies that load balancing only affects the scope of
    /// DHCPv6 message types that HA cares about.
    void loadBalancingHaTypes6();
};

void
QueryFilterTest::loadBalancingThisPrimary() {
    HAConfigPtr config = createValidConfiguration();

    QueryFilter filter(config);

    // By default the server1 should serve its own scope only. The
    // server2 should serve its scope.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Count number of in scope packets.
    unsigned in_scope = 0;
    // Set the test size - 65535 queries.
    const unsigned queries_num = 65535;
    std::string scope_class;
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random HW address.
        Pkt4Ptr query4 = createQuery4(randomKey(HWAddr::ETHERNET_HWADDR_LEN));
        // If the query is in scope, increase the counter of packets in scope.
        if (filter.inScope(query4, scope_class)) {
            ASSERT_EQ("HA_server1", scope_class);
            ASSERT_NE(scope_class, "HA_server2");
            ++in_scope;
        }
    }

    // We should have roughly 50/50 split of in scope and out of scope queries.
    // However, we don't know exactly how many. To be safe we simply assume that
    // we got more than 25% of in scope and more than 25% out of scope queries.
    EXPECT_GT(in_scope, static_cast<unsigned>(queries_num / 4));
    EXPECT_GT(queries_num - in_scope, static_cast<unsigned>(queries_num / 4));

    // Simulate failover scenario.
    filter.serveFailoverScopes();

    // In the failover case, the server1 should also take responsibility for
    // the server2's queries.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_TRUE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Repeat the test, but this time all should be in scope.
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random HW address.
        Pkt4Ptr query4 = createQuery4(randomKey(HWAddr::ETHERNET_HWADDR_LEN));
        // Every single query mist be in scope.
        ASSERT_TRUE(filter.inScope(query4, scope_class));
    }

    // However, the one that lacks HW address and client id should be out of
    // scope.
    Pkt4Ptr query4(new Pkt4(DHCPDISCOVER, 1234));
    EXPECT_FALSE(filter.inScope(query4, scope_class));
}

void
QueryFilterTest::loadBalancingClientIdThisPrimary() {
    HAConfigPtr config = createValidConfiguration();

    QueryFilter filter(config);

    // By default the server1 should serve its own scope only. The
    // server2 should serve its scope.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Fixed HW address used in tests.
    std::vector<uint8_t> hw_address(HWAddr::ETHERNET_HWADDR_LEN);

    // Count number of in scope packets.
    unsigned in_scope = 0;
    // Set the test size - 65535 queries.
    const unsigned queries_num = 65535;
    std::string scope_class;
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random client identifier.
        Pkt4Ptr query4 = createQuery4(hw_address, randomKey(8));
        // If the query is in scope, increase the counter of packets in scope.
        if (filter.inScope(query4, scope_class)) {
            ASSERT_EQ("HA_server1", scope_class);
            ASSERT_NE(scope_class, "HA_server2");
            ++in_scope;
        }
    }

    // We should have roughly 50/50 split of in scope and out of scope queries.
    // However, we don't know exactly how many. To be safe we simply assume that
    // we got more than 25% of in scope and more than 25% out of scope queries.
    EXPECT_GT(in_scope, static_cast<unsigned>(queries_num / 4));
    EXPECT_GT(queries_num - in_scope, static_cast<unsigned>(queries_num / 4));

    // Simulate failover scenario.
    filter.serveFailoverScopes();

    // In the failover case, the server1 should also take responsibility for
    // the server2's queries.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_TRUE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Repeat the test, but this time all should be in scope.
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random client identifier.
        Pkt4Ptr query4 = createQuery4(hw_address, randomKey(8));
        // Every single query mist be in scope.
        ASSERT_TRUE(filter.inScope(query4, scope_class));
    }
}

void
QueryFilterTest::loadBalancingThisSecondary() {
    HAConfigPtr config = createValidConfiguration();

    // We're now a secondary server.
    config->setThisServerName("server2");

    QueryFilter filter(config);

    // By default the server2 should serve its own scope only. The
    // server1 should serve its scope.
    EXPECT_FALSE(filter.amServingScope("server1"));
    EXPECT_TRUE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Count number of in scope packets.
    unsigned in_scope = 0;
    // Set the test size - 65535 queries.
    const unsigned queries_num = 65535;
    std::string scope_class;
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random HW address.
        Pkt4Ptr query4 = createQuery4(randomKey(HWAddr::ETHERNET_HWADDR_LEN));
        // If the query is in scope, increase the counter of packets in scope.
        if (filter.inScope(query4, scope_class)) {
            ASSERT_EQ("HA_server2", scope_class);
            ASSERT_NE(scope_class, "HA_server1");
            ++in_scope;
        }
    }

    // We should have roughly 50/50 split of in scope and out of scope queries.
    // However, we don't know exactly how many. To be safe we simply assume that
    // we got more than 25% of in scope and more than 25% out of scope queries.
    EXPECT_GT(in_scope, static_cast<unsigned>(queries_num / 4));
    EXPECT_GT(queries_num - in_scope, static_cast<unsigned>(queries_num / 4));

    // Simulate failover scenario.
    filter.serveFailoverScopes();

    // In this scenario, the server1 died, so the server2 should now serve
    // both scopes.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_TRUE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Repeat the test, but this time all should be in scope.
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random HW address.
        Pkt4Ptr query4 = createQuery4(randomKey(HWAddr::ETHERNET_HWADDR_LEN));
        // Every single query must be in scope.
        ASSERT_TRUE(filter.inScope(query4, scope_class));
    }
}

void
QueryFilterTest::loadBalancingThisBackup() {
    HAConfigPtr config = createValidConfiguration();

    config->setThisServerName("server3");

    QueryFilter filter(config);

    // The backup server doesn't handle any DHCP traffic by default.
    EXPECT_FALSE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Set the test size - 65535 queries.
    const unsigned queries_num = 65535;
    std::string scope_class;
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random HW address.
        Pkt4Ptr query4 = createQuery4(randomKey(HWAddr::ETHERNET_HWADDR_LEN));
        // None of the packets should be handlded by the backup server.
        ASSERT_FALSE(filter.inScope(query4, scope_class));
    }

    // Simulate failover. Although, backup server never starts handling
    // other server's traffic automatically, it can be manually instructed
    // to do so. This simulates such scenario.
    filter.serveFailoverScopes();

    // The backup server now handles traffic of server 1 and server 2.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_TRUE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Repeat the test, but this time all should be in scope.
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random HW address.
        Pkt4Ptr query4 = createQuery4(randomKey(HWAddr::ETHERNET_HWADDR_LEN));
        // Every single query must be in scope.
        ASSERT_TRUE(filter.inScope(query4, scope_class));
    }
}

void
QueryFilterTest::hotStandbyThisPrimary() {
    HAConfigPtr config = createValidConfiguration(HAConfig::HOT_STANDBY);
    config->getPeerConfig("server2")->setRole("standby");

    QueryFilter filter(config);

    Pkt4Ptr query4 = createQuery4("11:22:33:44:55:66");

    // By default, only the primary server is active.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    std::string scope_class;

    // It should process its queries.
    EXPECT_TRUE(filter.inScope(query4, scope_class));

    // Simulate failover scenario, in which the active server detects a
    // failure of the standby server. This doesn't change anything in how
    // the traffic is distributed.
    filter.serveFailoverScopes();

    // The server1 continues to process its own traffic.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    EXPECT_TRUE(filter.inScope(query4, scope_class));
    EXPECT_EQ("HA_server1", scope_class);
    EXPECT_NE(scope_class, "HA_server2");
}

void
QueryFilterTest::hotStandbyThisSecondary() {
    HAConfigPtr config = createValidConfiguration(HAConfig::HOT_STANDBY);
    config->getPeerConfig("server2")->setRole("standby");
    config->setThisServerName("server2");

    QueryFilter filter(config);

    Pkt4Ptr query4 = createQuery4("11:22:33:44:55:66");

    // The server2 doesn't process any queries by default. The whole
    // traffic is processed by the server1.
    EXPECT_FALSE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    std::string scope_class;

    EXPECT_FALSE(filter.inScope(query4, scope_class));
    EXPECT_EQ("HA_server1", scope_class);
    EXPECT_NE(scope_class, "HA_server2");

    // Simulate failover case whereby the standby server detects a
    // failure of the active server.
    filter.serveFailoverScopes();

    // The server2 now handles the traffic normally handled by the
    // server1.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    EXPECT_TRUE(filter.inScope(query4, scope_class));
    EXPECT_EQ("HA_server1", scope_class);
    EXPECT_NE(scope_class, "HA_server2");
}

void
QueryFilterTest::hotStandbyThisBackup() {
    HAConfigPtr config = createValidConfiguration(HAConfig::HOT_STANDBY);
    config->getPeerConfig("server2")->setRole("standby");
    config->setThisServerName("server3");

    QueryFilter filter(config);

    Pkt4Ptr query4 = createQuery4("11:22:33:44:55:66");

    // By default the backup server doesn't process any traffic.
    EXPECT_FALSE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    std::string scope_class;

    EXPECT_FALSE(filter.inScope(query4, scope_class));

    // Simulate failover. Although, backup server never starts handling
    // other server's traffic automatically, it can be manually instructed
    // to do so. This simulates such scenario.
    filter.serveFailoverScopes();

    // The backup server now handles the entire traffic, i.e. the traffic
    // that the primary server handles.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    EXPECT_TRUE(filter.inScope(query4, scope_class));
}

void
QueryFilterTest::loadBalancingThisPrimary6() {
    HAConfigPtr config = createValidConfiguration();

    QueryFilter filter(config);

    // By default the server1 should serve its own scope only. The
    // server2 should serve its scope.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Count number of in scope packets.
    unsigned in_scope = 0;
    // Set the test size - 65535 queries.
    const unsigned queries_num = 65535;
    std::string scope_class;
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random DUID.
        Pkt6Ptr query6 = createQuery6(randomKey(10));
        // If the query is in scope, increase the counter of packets in scope.
        if (filter.inScope(query6, scope_class)) {
            ASSERT_EQ("HA_server1", scope_class);
            ASSERT_NE(scope_class, "HA_server2");
            ++in_scope;
        }
    }

    // We should have roughly 50/50 split of in scope and out of scope queries.
    // However, we don't know exactly how many. To be safe we simply assume that
    // we got more than 25% of in scope and more than 25% out of scope queries.
    EXPECT_GT(in_scope, static_cast<unsigned>(queries_num / 4));
    EXPECT_GT(queries_num - in_scope, static_cast<unsigned>(queries_num / 4));

    // Simulate failover scenario.
    filter.serveFailoverScopes();

    // In the failover case, the server1 should also take responsibility for
    // the server2's queries.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_TRUE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Repeat the test, but this time all should be in scope.
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random HW address.
        Pkt6Ptr query6 = createQuery6(randomKey(10));
        // Every single query mist be in scope.
        ASSERT_TRUE(filter.inScope(query6, scope_class));
    }

    // However, the one that lacks DUID should be out of scope.
    Pkt6Ptr query6(new Pkt6(DHCPV6_SOLICIT, 1234));
    EXPECT_FALSE(filter.inScope(query6, scope_class));
}

void
QueryFilterTest::loadBalancingThisSecondary6() {
    HAConfigPtr config = createValidConfiguration();

    // We're now a secondary server.
    config->setThisServerName("server2");

    QueryFilter filter(config);

    // By default the server2 should serve its own scope only. The
    // server1 should serve its scope.
    EXPECT_FALSE(filter.amServingScope("server1"));
    EXPECT_TRUE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Count number of in scope packets.
    unsigned in_scope = 0;
    // Set the test size - 65535 queries.
    const unsigned queries_num = 65535;
    std::string scope_class;
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random HW address.
        Pkt6Ptr query6 = createQuery6(randomKey(10));
        // If the query is in scope, increase the counter of packets in scope.
        if (filter.inScope(query6, scope_class)) {
            ASSERT_EQ("HA_server2", scope_class);
            ASSERT_NE(scope_class, "HA_server1");
            ++in_scope;
        }
    }

    // We should have roughly 50/50 split of in scope and out of scope queries.
    // However, we don't know exactly how many. To be safe we simply assume that
    // we got more than 25% of in scope and more than 25% out of scope queries.
    EXPECT_GT(in_scope, static_cast<unsigned>(queries_num / 4));
    EXPECT_GT(queries_num - in_scope, static_cast<unsigned>(queries_num / 4));

    // Simulate failover scenario.
    filter.serveFailoverScopes();

    // In this scenario, the server1 died, so the server2 should now serve
    // both scopes.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_TRUE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Repeat the test, but this time all should be in scope.
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random HW address.
        Pkt6Ptr query6 = createQuery6(randomKey(HWAddr::ETHERNET_HWADDR_LEN));
        // Every single query must be in scope.
        ASSERT_TRUE(filter.inScope(query6, scope_class));
    }
}

void
QueryFilterTest::loadBalancingThisBackup6() {
    HAConfigPtr config = createValidConfiguration();

    config->setThisServerName("server3");

    QueryFilter filter(config);

    // The backup server doesn't handle any DHCP traffic by default.
    EXPECT_FALSE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Set the test size - 65535 queries.
    const unsigned queries_num = 65535;
    std::string scope_class;
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random HW address.
        Pkt6Ptr query6 = createQuery6(randomKey(10));
        // None of the packets should be handlded by the backup server.
        ASSERT_FALSE(filter.inScope(query6, scope_class));
    }

    // Simulate failover. Although, backup server never starts handling
    // other server's traffic automatically, it can be manually instructed
    // to do so. This simulates such scenario.
    filter.serveFailoverScopes();

    // The backup server now handles traffic of server 1 and server 2.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_TRUE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Repeat the test, but this time all should be in scope.
    for (unsigned i = 0; i < queries_num; ++i) {
        // Create query with random HW address.
        Pkt6Ptr query6 = createQuery6(randomKey(10));
        // Every single query must be in scope.
        ASSERT_TRUE(filter.inScope(query6, scope_class));
    }
}

void
QueryFilterTest::hotStandbyThisPrimary6() {
    HAConfigPtr config = createValidConfiguration(HAConfig::HOT_STANDBY);
    config->getPeerConfig("server2")->setRole("standby");

    QueryFilter filter(config);

    Pkt6Ptr query6 = createQuery6("01:02:11:22:33:44:55:66");

    // By default, only the primary server is active.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    std::string scope_class;

    // It should process its queries.
    EXPECT_TRUE(filter.inScope(query6, scope_class));

    // Simulate failover scenario, in which the active server detects a
    // failure of the standby server. This doesn't change anything in how
    // the traffic is distributed.
    filter.serveFailoverScopes();

    // The server1 continues to process its own traffic.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    EXPECT_TRUE(filter.inScope(query6, scope_class));
    EXPECT_EQ("HA_server1", scope_class);
    EXPECT_NE(scope_class, "HA_server2");
}

void
QueryFilterTest::hotStandbyThisSecondary6() {
    HAConfigPtr config = createValidConfiguration(HAConfig::HOT_STANDBY);
    config->getPeerConfig("server2")->setRole("standby");
    config->setThisServerName("server2");

    QueryFilter filter(config);

    Pkt6Ptr query6 = createQuery6("01:02:11:22:33:44:55:66");

    // The server2 doesn't process any queries by default. The whole
    // traffic is processed by the server1.
    EXPECT_FALSE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    std::string scope_class;

    EXPECT_FALSE(filter.inScope(query6, scope_class));
    EXPECT_EQ("HA_server1", scope_class);
    EXPECT_NE(scope_class, "HA_server2");

    // Simulate failover case whereby the standby server detects a
    // failure of the active server.
    filter.serveFailoverScopes();

    // The server2 now handles the traffic normally handled by the
    // server1.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    EXPECT_TRUE(filter.inScope(query6, scope_class));
    EXPECT_EQ("HA_server1", scope_class);
    EXPECT_NE(scope_class, "HA_server2");
}

void
QueryFilterTest::hotStandbyThisBackup6() {
    HAConfigPtr config = createValidConfiguration(HAConfig::HOT_STANDBY);
    config->getPeerConfig("server2")->setRole("standby");
    config->setThisServerName("server3");

    QueryFilter filter(config);

    Pkt6Ptr query6 = createQuery6(randomKey(10));

    // By default the backup server doesn't process any traffic.
    EXPECT_FALSE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    std::string scope_class;

    EXPECT_FALSE(filter.inScope(query6, scope_class));

    // Simulate failover. Although, backup server never starts handling
    // other server's traffic automatically, it can be manually instructed
    // to do so. This simulates such scenario.
    filter.serveFailoverScopes();

    // The backup server now handles the entire traffic, i.e. the traffic
    // that the primary server handles.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    EXPECT_TRUE(filter.inScope(query6, scope_class));
}

void
QueryFilterTest::explicitlyServeScopes() {
    HAConfigPtr config = createValidConfiguration();

    QueryFilter filter(config);

    // Initially, the scopes should be set according to the load
    // balancing configuration.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Enable "server2" scope.
    ASSERT_NO_THROW(filter.serveScope("server2"));
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_TRUE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Enable only "server2" scope.
    ASSERT_NO_THROW(filter.serveScopeOnly("server2"));
    EXPECT_FALSE(filter.amServingScope("server1"));
    EXPECT_TRUE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Explicitly enable selected scopes.
    ASSERT_NO_THROW(filter.serveScopes({ "server1", "server3" }));
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_TRUE(filter.amServingScope("server3"));

    // Revert to defaults.
    ASSERT_NO_THROW(filter.serveDefaultScopes());
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Disable all scopes.
    ASSERT_NO_THROW(filter.serveNoScopes());
    EXPECT_FALSE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Test negative cases.
    EXPECT_THROW(filter.serveScope("unsupported"), BadValue);
    EXPECT_THROW(filter.serveScopeOnly("unsupported"), BadValue);
    EXPECT_THROW(filter.serveScopes({ "server1", "unsupported" }), BadValue);
}

void
QueryFilterTest::loadBalancingHaTypes4() {
    HAConfigPtr config = createValidConfiguration();

    QueryFilter filter(config);

    // By default the server1 should serve its own scope only. The
    // server2 should serve its scope.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Use DHCPDISCOVER to find MAC addresses in scope for server1 and server2.
    Pkt4Ptr server1_pkt;
    Pkt4Ptr server2_pkt;
    const unsigned max_scope_tries = 100;
    for (unsigned i = 0; i < max_scope_tries; ++i) {
        // Create query with random HW address.
        std::string scope_class;
        Pkt4Ptr query4 = createQuery4(randomKey(HWAddr::ETHERNET_HWADDR_LEN));
        // If the query is in scope then we're done.
        if (filter.inScope(query4, scope_class)) {
            ASSERT_EQ("HA_server1", scope_class);
            server1_pkt = query4;
            if (server2_pkt) {
                break;
            }
        } else {
            ASSERT_EQ("HA_server2", scope_class);
            server2_pkt = query4;
            if (server1_pkt) {
                break;
            }
        }
    }

    ASSERT_TRUE(server1_pkt && server2_pkt) << "do not have both scopes in "
                << max_scope_tries << ", load balance broken?";

    // Iterate over message types.  While setting message type to zero is
    // semantically invalid, it is useful for testing here. Similarly we exceed
    // DHCP_TYPES_EOF just to be sure.
    for (uint8_t msg_type = 0; msg_type < DHCP_TYPES_EOF + 2; ++msg_type) {
        // All message types should be in scope for server1.
        server1_pkt->setType(msg_type);

        std::string scope_class;
        bool is_in_scope = filter.inScope(server1_pkt, scope_class);
        ASSERT_EQ("HA_server1", scope_class);
        EXPECT_TRUE(is_in_scope);

        server2_pkt->setType(msg_type);
        scope_class.clear();
        is_in_scope = filter.inScope(server2_pkt, scope_class);
        switch (msg_type) {
            case DHCPDISCOVER:
            case DHCPREQUEST:
            case DHCPDECLINE:
            case DHCPRELEASE:
            case DHCPINFORM:
                // HA message types should be in scope for server2.
                ASSERT_EQ("HA_server2", scope_class);
                EXPECT_FALSE(is_in_scope);
                break;
            default:
                // Non HA message types should be in scope for server1.
                ASSERT_EQ("HA_server1", scope_class);
                EXPECT_TRUE(is_in_scope);
                break;
        }
    }
}

void
QueryFilterTest::loadBalancingHaTypes6() {
    HAConfigPtr config = createValidConfiguration();

    QueryFilter filter(config);

    // By default the server1 should serve its own scope only. The
    // server2 should serve its scope.
    EXPECT_TRUE(filter.amServingScope("server1"));
    EXPECT_FALSE(filter.amServingScope("server2"));
    EXPECT_FALSE(filter.amServingScope("server3"));

    // Use DHCPV6_SOLICIT to find MAC addresses in scope for server1 and server2.
    Pkt6Ptr server1_pkt;
    Pkt6Ptr server2_pkt;
    const unsigned max_scope_tries = 100;
    for (unsigned i = 0; i < max_scope_tries; ++i) {
        // Create query with random HW address.
        std::string scope_class;

        // Create query with random DUID.
        Pkt6Ptr query6 = createQuery6(randomKey(10));
        if (filter.inScope(query6, scope_class)) {
            ASSERT_EQ("HA_server1", scope_class);
            // In scope for server1, save it.
            server1_pkt = query6;
            if (server2_pkt) {
                // Have both, we're done.
                break;
            }
        } else {
            ASSERT_EQ("HA_server2", scope_class);
            // In scope for server2, save it.
            server2_pkt = query6;
            if (server1_pkt) {
                // Have both, we're done.
                break;
            }
        }
    }

    ASSERT_TRUE(server1_pkt && server2_pkt) << "do not have both scopes in "
                << max_scope_tries << ", load balance broken?";

    // Iterate over message types.  While setting message type to zero is
    // semantically invalid, it is useful for testing here. Similarly we exceed
    // DHCPV6_TYPES_EOF just to be sure.
    for (uint8_t msg_type = 0; msg_type < DHCPV6_TYPES_EOF + 2; ++msg_type) {
        // All message types should be in scope for server1.
        server1_pkt->setType(msg_type);

        std::string scope_class;
        bool is_in_scope = filter.inScope(server1_pkt, scope_class);
        ASSERT_EQ("HA_server1", scope_class);
        EXPECT_TRUE(is_in_scope);

        server2_pkt->setType(msg_type);
        scope_class.clear();
        is_in_scope = filter.inScope(server2_pkt, scope_class);
        switch (msg_type) {
            case DHCPV6_SOLICIT:
            case DHCPV6_REQUEST:
            case DHCPV6_CONFIRM:
            case DHCPV6_RENEW:
            case DHCPV6_REBIND:
            case DHCPV6_RELEASE:
            case DHCPV6_DECLINE:
                // HA message types should be in scope for server2.
                ASSERT_EQ("HA_server2", scope_class);
                EXPECT_FALSE(is_in_scope);
                break;
            default:
                // Non HA message types should be in scope for server1.
                ASSERT_EQ("HA_server1", scope_class);
                EXPECT_TRUE(is_in_scope);
                break;
        }
    }
}

TEST_F(QueryFilterTest, loadBalancingClientIdThisPrimary) {
    loadBalancingClientIdThisPrimary();
}

TEST_F(QueryFilterTest, loadBalancingClientIdThisPrimaryMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    loadBalancingClientIdThisPrimary();
}

TEST_F(QueryFilterTest, loadBalancingThisPrimary) {
    loadBalancingThisPrimary();
}

TEST_F(QueryFilterTest, loadBalancingThisPrimaryMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    loadBalancingThisPrimary();
}

TEST_F(QueryFilterTest, loadBalancingThisSecondary) {
    loadBalancingThisSecondary();
}

TEST_F(QueryFilterTest, loadBalancingThisSecondaryMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    loadBalancingThisSecondary();
}

TEST_F(QueryFilterTest, loadBalancingThisBackup) {
    loadBalancingThisBackup();
}

TEST_F(QueryFilterTest, loadBalancingThisBackupMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    loadBalancingThisBackup();
}

TEST_F(QueryFilterTest, hotStandbyThisPrimary) {
    hotStandbyThisPrimary();
}

TEST_F(QueryFilterTest, hotStandbyThisPrimaryMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    hotStandbyThisPrimary();
}

TEST_F(QueryFilterTest, hotStandbyThisSecondary) {
    hotStandbyThisSecondary();
}

TEST_F(QueryFilterTest, hotStandbyThisSecondaryMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    hotStandbyThisSecondary();
}

TEST_F(QueryFilterTest, hotStandbyThisBackup) {
    hotStandbyThisBackup();
}

TEST_F(QueryFilterTest, hotStandbyThisBackupMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    hotStandbyThisBackup();
}

TEST_F(QueryFilterTest, loadBalancingThisPrimary6) {
    loadBalancingThisPrimary6();
}

TEST_F(QueryFilterTest, loadBalancingThisPrimary6MultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    loadBalancingThisPrimary6();
}

TEST_F(QueryFilterTest, loadBalancingThisSecondary6) {
    loadBalancingThisSecondary6();
}

TEST_F(QueryFilterTest, loadBalancingThisSecondary6MultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    loadBalancingThisSecondary6();
}

TEST_F(QueryFilterTest, loadBalancingThisBackup6) {
    loadBalancingThisBackup6();
}

TEST_F(QueryFilterTest, loadBalancingThisBackup6MultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    loadBalancingThisBackup6();
}

TEST_F(QueryFilterTest, hotStandbyThisPrimary6) {
    hotStandbyThisPrimary6();
}

TEST_F(QueryFilterTest, hotStandbyThisPrimary6MultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    hotStandbyThisPrimary6();
}

TEST_F(QueryFilterTest, hotStandbyThisSecondary6) {
    hotStandbyThisSecondary6();
}

TEST_F(QueryFilterTest, hotStandbyThisSecondary6MultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    hotStandbyThisSecondary6();
}

TEST_F(QueryFilterTest, hotStandbyThisBackup6) {
    hotStandbyThisBackup6();
}

TEST_F(QueryFilterTest, hotStandbyThisBackup6MultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    hotStandbyThisBackup6();
}

TEST_F(QueryFilterTest, explicitlyServeScopes) {
    explicitlyServeScopes();
}

TEST_F(QueryFilterTest, explicitlyServeScopesMultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    explicitlyServeScopes();
}

TEST_F(QueryFilterTest, loadBalancingHaTypes4) {
    loadBalancingHaTypes4();
}

TEST_F(QueryFilterTest, loadBalancingHaTypes4MultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    loadBalancingHaTypes4();
}

TEST_F(QueryFilterTest, loadBalancingHaTypes6) {
    loadBalancingHaTypes6();
}

TEST_F(QueryFilterTest, loadBalancingHaTypes6MultiThreading) {
    MultiThreadingMgr::instance().setMode(true);
    loadBalancingHaTypes6();
}

}
