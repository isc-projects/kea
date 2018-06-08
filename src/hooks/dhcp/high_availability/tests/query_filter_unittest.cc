// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <ha_test.h>
#include <ha_config.h>
#include <ha_config_parser.h>
#include <query_filter.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/hwaddr.h>
#include <cstdint>
#include <string>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::ha;
using namespace isc::ha::test;

namespace  {

/// @brief Test fixture class for @c QueryFilter class.
using QueryFilterTest = HATest;

// This test verifies the case when load balancing is enabled and
// this server is primary.
TEST_F(QueryFilterTest, loadBalancingThisPrimary) {
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

// This test verifies that client identifier is used for load balancing.
TEST_F(QueryFilterTest, loadBalancingClientIdThisPrimary) {
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

// This test verifies the case when load balancing is enabled and
// this server is secondary.
TEST_F(QueryFilterTest, loadBalancingThisSecondary) {
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

// This test verifies the case when load balancing is enabled and
// this server is backup.
/// @todo Expand these tests once we implement the actual load balancing to
/// verify which packets are in scope.
TEST_F(QueryFilterTest, loadBalancingThisBackup) {
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

// This test verifies the case when hot-standby is enabled and this
// server is primary.
TEST_F(QueryFilterTest, hotStandbyThisPrimary) {
    HAConfigPtr config = createValidConfiguration();

    config->setHAMode("hot-standby");
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

// This test verifies the case when hot-standby is enabled and this
// server is standby.
TEST_F(QueryFilterTest, hotStandbyThisSecondary) {
    HAConfigPtr config = createValidConfiguration();

    config->setHAMode("hot-standby");
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

// This test verifies the case when hot-standby is enabled and this
// server is backup.
TEST_F(QueryFilterTest, hotStandbyThisBackup) {
    HAConfigPtr config = createValidConfiguration();

    config->setHAMode("hot-standby");
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

// This test verifies the case when load balancing is enabled and
// this DHCPv6 server is primary.
TEST_F(QueryFilterTest, loadBalancingThisPrimary6) {
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

// This test verifies the case when load balancing is enabled and
// this server is secondary.
TEST_F(QueryFilterTest, loadBalancingThisSecondary6) {
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

// This test verifies the case when load balancing is enabled and
// this server is backup.
/// @todo Expand these tests once we implement the actual load balancing to
/// verify which packets are in scope.
TEST_F(QueryFilterTest, loadBalancingThisBackup6) {
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

// This test verifies the case when hot-standby is enabled and this
// server is primary.
TEST_F(QueryFilterTest, hotStandbyThisPrimary6) {
    HAConfigPtr config = createValidConfiguration();

    config->setHAMode("hot-standby");
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

// This test verifies the case when hot-standby is enabled and this
// server is standby.
TEST_F(QueryFilterTest, hotStandbyThisSecondary6) {
    HAConfigPtr config = createValidConfiguration();

    config->setHAMode("hot-standby");
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

// This test verifies that it is possible to explicitly enable and
// disable certain scopes.
TEST_F(QueryFilterTest, explicitlyServeScopes) {
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

}
