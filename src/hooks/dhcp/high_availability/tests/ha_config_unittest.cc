// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ha_impl.h>
#include <ha_service_states.h>
#include <ha_test.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <cc/dhcp_config_error.h>
#include <config/command_mgr.h>
#include <string>

using namespace isc;
using namespace isc::config;
using namespace isc::data;
using namespace isc::ha;
using namespace isc::hooks;
using namespace isc::ha::test;

namespace {

/// @brief Test fixture class for testing HA hooks library
/// configuration.
class HAConfigTest : public HATest {
public:

    /// @brief Constructor.
    HAConfigTest()
        : HATest() {
    }

    /// @brief Verifies if an exception is thrown if provided HA
    /// configuration is invalid.
    ///
    /// @param invalid_config Configuration to be tested.
    /// @param expected_error Expected error message.
    void testInvalidConfig(const std::string& invalid_config,
                           const std::string& expected_error) {
        HAImplPtr impl(new HAImpl());
        try {
            impl->configure(Element::fromJSON(invalid_config));
            ADD_FAILURE() << "expected ConfigError exception, thrown no exception";

        } catch (const ConfigError& ex) {
            EXPECT_EQ(expected_error, std::string(ex.what()));

        } catch (...) {
            ADD_FAILURE() << "expected ConfigError exception, thrown different"
                " exception type";
        }
    }
};

// Verifies that load balancing configuration is parsed correctly.
TEST_F(HAConfigTest, configureLoadBalancing) {
    const std::string ha_config =
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"send-lease-updates\": false,"
        "        \"sync-leases\": false,"
        "        \"sync-timeout\": 20000,"
        "        \"heartbeat-delay\": 8,"
        "        \"max-response-delay\": 11,"
        "        \"max-ack-delay\": 5,"
        "        \"max-unacked-clients\": 20,"
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8081/\","
        "                \"role\": \"secondary\""
        "            },"
        "            {"
        "                \"name\": \"server3\","
        "                \"url\": \"http://127.0.0.1:8082/\","
        "                \"role\": \"backup\","
        "                \"auto-failover\": false"
        "            }"
        "        ],"
        "        \"state-machine\": {"
        "            \"states\": ["
        "                {"
        "                    \"state\": \"waiting\","
        "                    \"pause\": \"once\""
        "                },"
        "                {"
        "                    \"state\": \"ready\","
        "                    \"pause\": \"always\""
        "                },"
        "                {"
        "                    \"state\": \"partner-down\","
        "                    \"pause\": \"never\""
        "                }"
        "            ]"
        "        }"
        "    }"
        "]";

    HAImplPtr impl(new HAImpl());
    ASSERT_NO_THROW(impl->configure(Element::fromJSON(ha_config)));
    EXPECT_EQ("server1", impl->getConfig()->getThisServerName());
    EXPECT_EQ(HAConfig::LOAD_BALANCING, impl->getConfig()->getHAMode());
    EXPECT_FALSE(impl->getConfig()->amSendingLeaseUpdates());
    EXPECT_FALSE(impl->getConfig()->amSyncingLeases());
    EXPECT_EQ(20000, impl->getConfig()->getSyncTimeout());
    EXPECT_EQ(8, impl->getConfig()->getHeartbeatDelay());
    EXPECT_EQ(11, impl->getConfig()->getMaxResponseDelay());
    EXPECT_EQ(5, impl->getConfig()->getMaxAckDelay());
    EXPECT_EQ(20, impl->getConfig()->getMaxUnackedClients());

    HAConfig::PeerConfigPtr cfg = impl->getConfig()->getThisServerConfig();
    ASSERT_TRUE(cfg);
    EXPECT_EQ("server1", cfg->getName());
    EXPECT_EQ("http://127.0.0.1:8080/", cfg->getUrl().toText());
    EXPECT_EQ(cfg->getLogLabel(), "server1 (http://127.0.0.1:8080/)");
    EXPECT_EQ(HAConfig::PeerConfig::PRIMARY, cfg->getRole());
    EXPECT_FALSE(cfg->isAutoFailover());

    cfg = impl->getConfig()->getPeerConfig("server2");
    ASSERT_TRUE(cfg);
    EXPECT_EQ("server2", cfg->getName());
    EXPECT_EQ("http://127.0.0.1:8081/", cfg->getUrl().toText());
    EXPECT_EQ(cfg->getLogLabel(), "server2 (http://127.0.0.1:8081/)");
    EXPECT_EQ(HAConfig::PeerConfig::SECONDARY, cfg->getRole());
    EXPECT_TRUE(cfg->isAutoFailover());

    cfg = impl->getConfig()->getPeerConfig("server3");
    ASSERT_TRUE(cfg);
    EXPECT_EQ("server3", cfg->getName());
    EXPECT_EQ("http://127.0.0.1:8082/", cfg->getUrl().toText());
    EXPECT_EQ(cfg->getLogLabel(), "server3 (http://127.0.0.1:8082/)");
    EXPECT_EQ(HAConfig::PeerConfig::BACKUP, cfg->getRole());
    EXPECT_FALSE(cfg->isAutoFailover());

    // Verify that per-state configuration is correct.x

    HAConfig::StateConfigPtr state_cfg;
    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_BACKUP_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_LOAD_BALANCING_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_PARTNER_DOWN_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_READY_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_ALWAYS, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_SYNCING_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_TERMINATED_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_WAITING_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_ONCE, state_cfg->getPausing());
}

// Verifies that load balancing configuration is parsed correctly.
TEST_F(HAConfigTest, configureHotStandby) {
    const std::string ha_config =
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"hot-standby\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8081/\","
        "                \"role\": \"standby\","
        "                \"auto-failover\": true"
        "            },"
        "            {"
        "                \"name\": \"server3\","
        "                \"url\": \"http://127.0.0.1:8082/\","
        "                \"role\": \"backup\","
        "                \"auto-failover\": false"
        "            }"
        "        ]"
        "    }"
        "]";

    HAImplPtr impl(new HAImpl());
    ASSERT_NO_THROW(impl->configure(Element::fromJSON(ha_config)));
    EXPECT_EQ("server1", impl->getConfig()->getThisServerName());
    EXPECT_EQ(HAConfig::HOT_STANDBY, impl->getConfig()->getHAMode());
    EXPECT_TRUE(impl->getConfig()->amSendingLeaseUpdates());
    EXPECT_TRUE(impl->getConfig()->amSyncingLeases());
    EXPECT_EQ(60000, impl->getConfig()->getSyncTimeout());
    EXPECT_EQ(10000, impl->getConfig()->getHeartbeatDelay());
    EXPECT_EQ(10000, impl->getConfig()->getMaxAckDelay());
    EXPECT_EQ(10, impl->getConfig()->getMaxUnackedClients());

    HAConfig::PeerConfigPtr cfg = impl->getConfig()->getThisServerConfig();
    ASSERT_TRUE(cfg);
    EXPECT_EQ("server1", cfg->getName());
    EXPECT_EQ("http://127.0.0.1:8080/", cfg->getUrl().toText());
    EXPECT_EQ(HAConfig::PeerConfig::PRIMARY, cfg->getRole());
    EXPECT_FALSE(cfg->isAutoFailover());

    cfg = impl->getConfig()->getPeerConfig("server2");
    ASSERT_TRUE(cfg);
    EXPECT_EQ("server2", cfg->getName());
    EXPECT_EQ("http://127.0.0.1:8081/", cfg->getUrl().toText());
    EXPECT_EQ(HAConfig::PeerConfig::STANDBY, cfg->getRole());
    EXPECT_TRUE(cfg->isAutoFailover());

    cfg = impl->getConfig()->getPeerConfig("server3");
    ASSERT_TRUE(cfg);
    EXPECT_EQ("server3", cfg->getName());
    EXPECT_EQ("http://127.0.0.1:8082/", cfg->getUrl().toText());
    EXPECT_EQ(HAConfig::PeerConfig::BACKUP, cfg->getRole());
    EXPECT_FALSE(cfg->isAutoFailover());

    HAConfig::StateConfigPtr state_cfg;
    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_BACKUP_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_HOT_STANDBY_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_PARTNER_DOWN_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_READY_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_SYNCING_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_TERMINATED_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_WAITING_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_NEVER, state_cfg->getPausing());
}

// This server name must not be empty.
TEST_F(HAConfigTest, emptyServerName) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"\","
        "        \"mode\": \"load-balancing\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "'this-server-name' value must not be empty");
}

// There must be a configuration provided for this server.
TEST_F(HAConfigTest, nonMatchingServerName) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"foo\","
        "        \"mode\": \"load-balancing\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "no peer configuration specified for the 'foo'");
}

// Error should be returned when mode is invalid.
TEST_F(HAConfigTest, unsupportedMode) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"unsupported-mode\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "unsupported value 'unsupported-mode' for mode parameter");
}

// Error should be returned when heartbeat-delay is negative.
TEST_F(HAConfigTest, negativeHeartbeatDelay) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"heartbeat-delay\": -1,"
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "'heartbeat-delay' must not be negative");
}

// Error should be returned when heartbeat-delay is too large.
TEST_F(HAConfigTest, largeHeartbeatDelay) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"heartbeat-delay\": 65536,"
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "'heartbeat-delay' must not be greater than 65535");
}

// There must be at least two servers provided.
TEST_F(HAConfigTest, singlePeer) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            }"
        "        ]"
        "    }"
        "]",
        "peers configuration requires at least two peers to be specified");
}

// Server name must not be empty.
TEST_F(HAConfigTest, emptyPeerName) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "peer name must not be empty");
}

// Can't have two servers with the same name.
TEST_F(HAConfigTest, duplicatePeerName) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "peer with name 'server1' already specified");
}

// URL must be valid.
TEST_F(HAConfigTest, invalidURL) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"://127.0.0.1:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "invalid URL: url ://127.0.0.1:8080/ lacks http or"
        " https scheme for server server2");
}

// Only certain roles are allowed.
TEST_F(HAConfigTest, unsupportedRole) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"unsupported\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "unsupported value 'unsupported' for role parameter");
}

// There must be exactly one primary server.
TEST_F(HAConfigTest, twoPrimary) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "multiple primary servers specified");
}

// There must be exactly one secondary server.
TEST_F(HAConfigTest, twoSecondary) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "multiple secondary servers specified");
}

// Only one standby server is allowed.
TEST_F(HAConfigTest, twoStandby) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"hot-standby\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"standby\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"standby\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "multiple standby servers specified");
}

// Primary server is required for load balancing.
TEST_F(HAConfigTest, loadBalancingNoPrimary) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"backup\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "primary server required in the load balancing configuration");
}

// Secondary server is required for load balancing.
TEST_F(HAConfigTest, loadBalancingNoSecondary) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"backup\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "secondary server required in the load balancing configuration");
}

// Primary server is required for hot standby mode.
TEST_F(HAConfigTest, hotStandbyNoPrimary) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"hot-standby\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"backup\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"standby\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "primary server required in the hot standby configuration");
}

// Standby server is required for hot standby mode.
TEST_F(HAConfigTest, hotStandbyNoStandby) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"hot-standby\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"backup\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "standby server required in the hot standby configuration");
}

// Standby server must not be specified in the load balancing mode.
TEST_F(HAConfigTest, loadBalancingStandby) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"standby\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "standby servers not allowed in the load balancing configuration");
}

// Secondary server must not be specified in the hot standby mode.
TEST_F(HAConfigTest, hotStandbySecondary) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"hot-standby\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "secondary servers not allowed in the hot standby configuration");
}

// state-machine parameter must be a map.
TEST_F(HAConfigTest, invalidStateMachine) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"hot-standby\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8081/\","
        "                \"role\": \"standby\","
        "                \"auto-failover\": true"
        "            }"
        "        ],"
        "        \"state-machine\": ["
        "            {"
        "                \"state\": \"foo\","
        "                \"pause\": \"always\""
        "            }"
        "        ]"
        "    }"
        "]",
        "'state-machine' parameter must be a map");
}

// states within state-machine must be a list.
TEST_F(HAConfigTest, invalidStatesList) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"hot-standby\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8081/\","
        "                \"role\": \"standby\","
        "                \"auto-failover\": true"
        "            }"
        "        ],"
        "        \"state-machine\": {"
        "            \"states\": {"
        "            }"
        "        }"
        "    }"
        "]",
        "'states' parameter must be a list");
}

// State name must be recognized.
TEST_F(HAConfigTest, invalidStateName) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"hot-standby\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8081/\","
        "                \"role\": \"standby\","
        "                \"auto-failover\": true"
        "            }"
        "        ],"
        "        \"state-machine\": {"
        "            \"states\": ["
        "                {"
        "                    \"state\": \"foo\","
        "                    \"pause\": \"always\""
        "                }"
        "            ]"
        "        }"
        "    }"
        "]",
        "unknown state foo");
}

// Pause value must be recognized.
TEST_F(HAConfigTest, invalidPauseValue) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"hot-standby\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8081/\","
        "                \"role\": \"standby\","
        "                \"auto-failover\": true"
        "            }"
        "        ],"
        "        \"state-machine\": {"
        "            \"states\": ["
        "                {"
        "                    \"state\": \"waiting\","
        "                    \"pause\": \"foo\""
        "                }"
        "            ]"
        "        }"
        "    }"
        "]",
        "unsupported value foo of 'pause' parameter");
}

// Must not specify configuration for the same state twice.
TEST_F(HAConfigTest, duplicatedStates) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"hot-standby\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8081/\","
        "                \"role\": \"standby\","
        "                \"auto-failover\": true"
        "            }"
        "        ],"
        "        \"state-machine\": {"
        "            \"states\": ["
        "                {"
        "                    \"state\": \"waiting\","
        "                    \"pause\": \"always\""
        "                },"
        "                {"
        "                    \"state\": \"ready\","
        "                    \"pause\": \"always\""
        "                },"
        "                {"
        "                    \"state\": \"waiting\","
        "                    \"pause\": \"always\""
        "                }"
        "            ]"
        "        }"
        "    }"
        "]",
        "duplicated configuration for the 'waiting' state");
}

// Test that conversion of the role names works correctly.
TEST_F(HAConfigTest, stringToRole) {
    EXPECT_EQ(HAConfig::PeerConfig::PRIMARY,
              HAConfig::PeerConfig::stringToRole("primary"));
    EXPECT_EQ(HAConfig::PeerConfig::SECONDARY,
              HAConfig::PeerConfig::stringToRole("secondary"));
    EXPECT_EQ(HAConfig::PeerConfig::STANDBY,
              HAConfig::PeerConfig::stringToRole("standby"));
    EXPECT_EQ(HAConfig::PeerConfig::BACKUP,
              HAConfig::PeerConfig::stringToRole("backup"));
    EXPECT_THROW(HAConfig::PeerConfig::stringToRole("unsupported"),
                 BadValue);
}

// Test that role name is generated correctly.
TEST_F(HAConfigTest, roleToString) {
    EXPECT_EQ("primary",
              HAConfig::PeerConfig::roleToString(HAConfig::PeerConfig::PRIMARY));
    EXPECT_EQ("secondary",
              HAConfig::PeerConfig::roleToString(HAConfig::PeerConfig::SECONDARY));
    EXPECT_EQ("standby",
              HAConfig::PeerConfig::roleToString(HAConfig::PeerConfig::STANDBY));
    EXPECT_EQ("backup",
              HAConfig::PeerConfig::roleToString(HAConfig::PeerConfig::BACKUP));
}

// Test that conversion of the HA mode names works correctly.
TEST_F(HAConfigTest, stringToHAMode) {
    EXPECT_EQ(HAConfig::LOAD_BALANCING, HAConfig::stringToHAMode("load-balancing"));
    EXPECT_EQ(HAConfig::HOT_STANDBY, HAConfig::stringToHAMode("hot-standby"));
}

// Test that HA mode name is generated correctly.
TEST_F(HAConfigTest, HAModeToString) {
    EXPECT_EQ("load-balancing", HAConfig::HAModeToString(HAConfig::LOAD_BALANCING));
    EXPECT_EQ("hot-standby", HAConfig::HAModeToString(HAConfig::HOT_STANDBY));
}

// Test that conversion of the 'pause' value works correctly.
TEST_F(HAConfigTest, stringToPausing) {
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_ALWAYS,
              HAConfig::StateConfig::stringToPausing("always"));
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_NEVER,
              HAConfig::StateConfig::stringToPausing("never"));
    EXPECT_EQ(HAConfig::StateConfig::PAUSE_ONCE,
              HAConfig::StateConfig::stringToPausing("once"));
}

// Test that pause parameter value is generated correctly.
TEST_F(HAConfigTest, pausingToString) {
    EXPECT_EQ("always",
              HAConfig::StateConfig::pausingToString(HAConfig::StateConfig::PAUSE_ALWAYS));
    EXPECT_EQ("never",
              HAConfig::StateConfig::pausingToString(HAConfig::StateConfig::PAUSE_NEVER));
    EXPECT_EQ("once",
              HAConfig::StateConfig::pausingToString(HAConfig::StateConfig::PAUSE_ONCE));

}

} // end of anonymous namespace
