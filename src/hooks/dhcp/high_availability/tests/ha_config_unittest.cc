// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
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
#include <util/state_model.h>
#include <util/multi_threading_mgr.h>
#include <testutils/gtest_utils.h>
#include <string>

using namespace isc;
using namespace isc::config;
using namespace isc::data;
using namespace isc::ha;
using namespace isc::hooks;
using namespace isc::ha::test;
using namespace isc::util;

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
            // Expect the error to be contained in the exception message.
            std::string const exception(ex.what());
            EXPECT_NE(exception.find(expected_error), std::string::npos);
        } catch (...) {
            ADD_FAILURE() << "expected ConfigError exception, thrown different"
                " exception type";
        }
    }

    /// @brief Replace a pattern in a configuration.
    ///
    /// @param config Configuration to patch.
    /// @param from String to replace.
    /// @param repl String which replaces all occurrences of from.
    /// @result A copy of config where all occurrences of from were replaced
    /// by repl.
    std::string replaceInConfig(const std::string& config,
                                const std::string& from,
                                const std::string& repl) {
        std::string result(config);
        if (from.empty()) {
            return (result);
        }
        for (;;) {
            size_t where = result.find(from);
            if (where == std::string::npos) {
                return (result);
            }
            result.replace(where, from.size(), repl);
        }
        return (result);
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
        "        \"sync-page-limit\": 3,"
        "        \"delayed-updates-limit\": 111,"
        "        \"heartbeat-delay\": 8,"
        "        \"max-response-delay\": 11,"
        "        \"max-ack-delay\": 5,"
        "        \"max-unacked-clients\": 20,"
        "        \"wait-backup-ack\": false,"
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"basic-auth-password\": \"1234\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8081/\","
        "                \"basic-auth-user\": \"\","
        "                \"role\": \"secondary\""
        "            },"
        "            {"
        "                \"name\": \"server3\","
        "                \"url\": \"http://127.0.0.1:8082/\","
        "                \"basic-auth-user\": \"foo\","
        "                \"basic-auth-password\": \"bar\","
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
    EXPECT_EQ(3, impl->getConfig()->getSyncPageLimit());
    EXPECT_EQ(111, impl->getConfig()->getDelayedUpdatesLimit());
    EXPECT_TRUE(impl->getConfig()->amAllowingCommRecovery());
    EXPECT_EQ(8, impl->getConfig()->getHeartbeatDelay());
    EXPECT_EQ(11, impl->getConfig()->getMaxResponseDelay());
    EXPECT_EQ(5, impl->getConfig()->getMaxAckDelay());
    EXPECT_EQ(20, impl->getConfig()->getMaxUnackedClients());
    EXPECT_FALSE(impl->getConfig()->amWaitingBackupAck());

    HAConfig::PeerConfigPtr cfg = impl->getConfig()->getThisServerConfig();
    ASSERT_TRUE(cfg);
    EXPECT_EQ("server1", cfg->getName());
    EXPECT_EQ("http://127.0.0.1:8080/", cfg->getUrl().toText());
    EXPECT_EQ(cfg->getLogLabel(), "server1 (http://127.0.0.1:8080/)");
    EXPECT_EQ(HAConfig::PeerConfig::PRIMARY, cfg->getRole());
    EXPECT_FALSE(cfg->isAutoFailover());
    EXPECT_FALSE(cfg->getBasicAuth());

    cfg = impl->getConfig()->getPeerConfig("server2");
    ASSERT_TRUE(cfg);
    EXPECT_EQ("server2", cfg->getName());
    EXPECT_EQ("http://127.0.0.1:8081/", cfg->getUrl().toText());
    EXPECT_EQ(cfg->getLogLabel(), "server2 (http://127.0.0.1:8081/)");
    EXPECT_EQ(HAConfig::PeerConfig::SECONDARY, cfg->getRole());
    EXPECT_TRUE(cfg->isAutoFailover());
    EXPECT_FALSE(cfg->getBasicAuth());

    cfg = impl->getConfig()->getPeerConfig("server3");
    ASSERT_TRUE(cfg);
    EXPECT_EQ("server3", cfg->getName());
    EXPECT_EQ("http://127.0.0.1:8082/", cfg->getUrl().toText());
    EXPECT_EQ(cfg->getLogLabel(), "server3 (http://127.0.0.1:8082/)");
    EXPECT_EQ(HAConfig::PeerConfig::BACKUP, cfg->getRole());
    EXPECT_FALSE(cfg->isAutoFailover());
    ASSERT_TRUE(cfg->getBasicAuth());
    EXPECT_EQ("foo:bar", cfg->getBasicAuth()->getSecret());

    // Verify that per-state configuration is correct.

    HAConfig::StateConfigPtr state_cfg;
    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_BACKUP_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(STATE_PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_COMMUNICATION_RECOVERY_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(STATE_PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_LOAD_BALANCING_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(STATE_PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_PARTNER_DOWN_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(STATE_PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_READY_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(STATE_PAUSE_ALWAYS, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_SYNCING_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(STATE_PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_TERMINATED_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(STATE_PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_WAITING_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(STATE_PAUSE_ONCE, state_cfg->getPausing());

    // Verify multi-threading default values.
    EXPECT_FALSE(impl->getConfig()->getEnableMultiThreading());
    EXPECT_FALSE(impl->getConfig()->getHttpDedicatedListener());
    EXPECT_EQ(0, impl->getConfig()->getHttpListenerThreads());
    EXPECT_EQ(0, impl->getConfig()->getHttpClientThreads());
}

// Verifies that hot standby configuration is parsed correctly.
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
        "                \"basic-auth-user\": \"admin\","
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
    EXPECT_EQ(10000, impl->getConfig()->getSyncPageLimit());
    EXPECT_EQ(0, impl->getConfig()->getDelayedUpdatesLimit());
    EXPECT_FALSE(impl->getConfig()->amAllowingCommRecovery());
    EXPECT_EQ(10000, impl->getConfig()->getHeartbeatDelay());
    EXPECT_EQ(10000, impl->getConfig()->getMaxAckDelay());
    EXPECT_EQ(10, impl->getConfig()->getMaxUnackedClients());
    EXPECT_FALSE(impl->getConfig()->amWaitingBackupAck());

    HAConfig::PeerConfigPtr cfg = impl->getConfig()->getThisServerConfig();
    ASSERT_TRUE(cfg);
    EXPECT_EQ("server1", cfg->getName());
    EXPECT_EQ("http://127.0.0.1:8080/", cfg->getUrl().toText());
    EXPECT_EQ(HAConfig::PeerConfig::PRIMARY, cfg->getRole());
    EXPECT_FALSE(cfg->isAutoFailover());
    ASSERT_TRUE(cfg->getBasicAuth());
    EXPECT_EQ("admin:", cfg->getBasicAuth()->getSecret());

    cfg = impl->getConfig()->getPeerConfig("server2");
    ASSERT_TRUE(cfg);
    EXPECT_EQ("server2", cfg->getName());
    EXPECT_EQ("http://127.0.0.1:8081/", cfg->getUrl().toText());
    EXPECT_EQ(HAConfig::PeerConfig::STANDBY, cfg->getRole());
    EXPECT_TRUE(cfg->isAutoFailover());
    EXPECT_FALSE(cfg->getBasicAuth());

    cfg = impl->getConfig()->getPeerConfig("server3");
    ASSERT_TRUE(cfg);
    EXPECT_EQ("server3", cfg->getName());
    EXPECT_EQ("http://127.0.0.1:8082/", cfg->getUrl().toText());
    EXPECT_EQ(HAConfig::PeerConfig::BACKUP, cfg->getRole());
    EXPECT_FALSE(cfg->isAutoFailover());
    EXPECT_FALSE(cfg->getBasicAuth());

    HAConfig::StateConfigPtr state_cfg;
    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_BACKUP_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(STATE_PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_HOT_STANDBY_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(STATE_PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_PARTNER_DOWN_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(STATE_PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_READY_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(STATE_PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_SYNCING_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(STATE_PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_TERMINATED_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(STATE_PAUSE_NEVER, state_cfg->getPausing());

    ASSERT_NO_THROW(state_cfg = impl->getConfig()->getStateMachineConfig()->
                    getStateConfig(HA_WAITING_ST));
    ASSERT_TRUE(state_cfg);
    EXPECT_EQ(STATE_PAUSE_NEVER, state_cfg->getPausing());

    // Verify multi-threading default values.
    EXPECT_FALSE(impl->getConfig()->getEnableMultiThreading());
    EXPECT_FALSE(impl->getConfig()->getHttpDedicatedListener());
    EXPECT_EQ(0, impl->getConfig()->getHttpListenerThreads());
    EXPECT_EQ(0, impl->getConfig()->getHttpClientThreads());
}

// Verifies that passive-backup configuration is parsed correctly.
TEST_F(HAConfigTest, configurePassiveBackup) {
    const std::string ha_config =
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"passive-backup\","
        "        \"wait-backup-ack\": true,"
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\""
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8081/\","
        "                \"role\": \"backup\""
        "            },"
        "            {"
        "                \"name\": \"server3\","
        "                \"url\": \"http://127.0.0.1:8082/\","
        "                \"basic-auth-user\": \"keatest\","
        "                \"basic-auth-password-file\": \""
                             TEST_HTTP_DIR "/hiddenp\","
        "                \"role\": \"backup\""
        "            }"
        "        ]"
        "    }"
        "]";

    HAImplPtr impl(new HAImpl());
    ASSERT_NO_THROW(impl->configure(Element::fromJSON(ha_config)));
    EXPECT_EQ("server1", impl->getConfig()->getThisServerName());
    EXPECT_EQ(HAConfig::PASSIVE_BACKUP, impl->getConfig()->getHAMode());
    EXPECT_TRUE(impl->getConfig()->amSendingLeaseUpdates());
    EXPECT_TRUE(impl->getConfig()->amWaitingBackupAck());

    HAConfig::PeerConfigPtr cfg = impl->getConfig()->getThisServerConfig();
    ASSERT_TRUE(cfg);
    EXPECT_EQ("server1", cfg->getName());
    EXPECT_EQ("http://127.0.0.1:8080/", cfg->getUrl().toText());
    EXPECT_EQ(HAConfig::PeerConfig::PRIMARY, cfg->getRole());
    EXPECT_FALSE(cfg->getBasicAuth());

    cfg = impl->getConfig()->getPeerConfig("server2");
    ASSERT_TRUE(cfg);
    EXPECT_EQ("server2", cfg->getName());
    EXPECT_EQ("http://127.0.0.1:8081/", cfg->getUrl().toText());
    EXPECT_EQ(HAConfig::PeerConfig::BACKUP, cfg->getRole());
    EXPECT_FALSE(cfg->getBasicAuth());

    cfg = impl->getConfig()->getPeerConfig("server3");
    ASSERT_TRUE(cfg);
    EXPECT_EQ("server3", cfg->getName());
    EXPECT_EQ("http://127.0.0.1:8082/", cfg->getUrl().toText());
    EXPECT_EQ(HAConfig::PeerConfig::BACKUP, cfg->getRole());
    ASSERT_TRUE(cfg->getBasicAuth());
    EXPECT_EQ("a2VhdGVzdDpLZWFUZXN0", cfg->getBasicAuth()->getCredential());

    // Verify multi-threading default values.
    EXPECT_FALSE(impl->getConfig()->getEnableMultiThreading());
    EXPECT_FALSE(impl->getConfig()->getHttpDedicatedListener());
    EXPECT_EQ(0, impl->getConfig()->getHttpListenerThreads());
    EXPECT_EQ(0, impl->getConfig()->getHttpClientThreads());
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
        "secondary server required in the load balancing configuration");
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

// URL hostname must be an address.
TEST_F(HAConfigTest, badURLName) {
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
        "                \"url\": \"http://localhost:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "bad url 'http://localhost:8080/': "
        "Failed to convert string to address 'localhost': "
        "Invalid argument for server server2");
}

// URL HTTPS scheme is not supported.
TEST_F(HAConfigTest, badURLHttps) {
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
        "                \"url\": \"https://127.0.0.1:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "bad url 'https://127.0.0.1:8080/': "
        "https scheme is not supported for server server2 "
        "where TLS is disabled");
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

// Test that wait-backup-ack must not be enabled in the load-balancing
// configuration.
TEST_F(HAConfigTest, waitBackupAckLoadBalancing) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"wait-backup-ack\": true,"
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
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "'wait-backup-ack' must be set to false in the load balancing configuration");
}

// Test that wait-backup-ack must not be enabled in the hot-standby
// configuration.
TEST_F(HAConfigTest, waitBackupAckHotStandby) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"hot-standby\","
        "        \"wait-backup-ack\": true,"
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
        "        ]"
        "    }"
        "]",
        "'wait-backup-ack' must be set to false in the hot standby configuration");
}

// Test that secondary server is not allowed in the passive-backup mode.
TEST_F(HAConfigTest, passiveBackupSecondaryServer) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"passive-backup\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\""
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8081/\","
        "                \"role\": \"secondary\""
        "            }"
        "        ]"
        "    }"
        "]",
        "secondary servers not allowed in the passive backup configuration");
}

// Test that standby server is not allowed in the passive-backup mode.
TEST_F(HAConfigTest, passiveBackupStandbyServer) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"passive-backup\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\""
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8081/\","
        "                \"role\": \"standby\""
        "            }"
        "        ]"
        "    }"
        "]",
        "standby servers not allowed in the passive backup configuration");
}

// Test that primary server is required in the passive-backup mode.
TEST_F(HAConfigTest, passiveBackupNoPrimary) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"passive-backup\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"backup\""
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8081/\","
        "                \"role\": \"backup\""
        "            }"
        "        ]"
        "    }"
        "]",
        "primary server required in the passive backup configuration");
}

// Test that empty name id is forbidden for basic HTTP authentication.
TEST_F(HAConfigTest, invalidUser) {
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
        "                \"basic-auth-user\": \"foo:bar\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]",
        "user 'foo:bar' must not contain a ':' in peer 'server2'");
}

// Test that setting delayed-updates-limit is not allowed in hot-standby mode.
TEST_F(HAConfigTest, hotStandbyDelayedUpdatesLimit) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"hot-standby\","
        "        \"delayed-updates-limit\": 1,"
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
        "'delayed-updates-limit' must be set to 0 in the hot standby configuration");
}

// Test that setting delayed-updates-limit is not allowed in passive-backup mode.
TEST_F(HAConfigTest, passiveBackupDelayedUpdatesLimit) {
    testInvalidConfig(
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"passive-backup\","
        "        \"delayed-updates-limit\": 1,"
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"primary\""
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"backup\""
        "            }"
        "        ]"
        "    }"
        "]",
        "'delayed-updates-limit' must be set to 0 in the passive backup configuration");
}

#if (defined(WITH_OPENSSL) || defined(WITH_BOTAN_BOOST))
/// Test that TLS parameters are correctly inherited.
TEST_F(HAConfigTest, tlsParameterInheritance) {
    const std::string ha_config =
        "["
        "    {"
        "        \"this-server-name\": \"my-server\","
        "        \"mode\": \"load-balancing\","
        "        \"trust-anchor\": \"!CA!/kea-ca.crt\","
        "        \"cert-file\": \"!CA!/kea-client.crt\","
        "        \"key-file\": \"!CA!/kea-client.key\","
        "        \"peers\": ["
        "            {"
        "                \"name\": \"my-server\","
        "                \"url\": \"https://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"auto-failover\": false"
        "            },"
        "            {"
        "                \"name\": \"overwrite\","
        "                \"trust-anchor\": \"!CA!\","
        "                \"cert-file\": \"!CA!/kea-server.crt\","
        "                \"key-file\": \"!CA!/kea-server.key\","
        "                \"url\": \"https://127.0.0.1:8080/\","
        "                \"role\": \"secondary\","
        "                \"auto-failover\": true"
        "            },"
        "            {"
        "                \"name\": \"disable\","
        "                \"trust-anchor\": \"\","
        "                \"cert-file\": \"\","
        "                \"key-file\": \"\","
        "                \"url\": \"http://127.0.0.1:8080/\","
        "                \"role\": \"backup\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]";
    const std::string& patched = replaceInConfig(ha_config, "!CA!",
                                                 TEST_CA_DIR);
    HAImplPtr impl(new HAImpl());
    ASSERT_NO_THROW(impl->configure(Element::fromJSON(patched)));

    // Check the global parameters.
    std::string expected;
    EXPECT_FALSE(impl->getConfig()->getTrustAnchor().unspecified());
    expected = TEST_CA_DIR;
    expected += "/kea-ca.crt";
    EXPECT_EQ(expected, impl->getConfig()->getTrustAnchor().get());
    EXPECT_FALSE(impl->getConfig()->getCertFile().unspecified());
    expected = TEST_CA_DIR;
    expected += "/kea-client.crt";
    EXPECT_EQ(expected, impl->getConfig()->getCertFile().get());
    EXPECT_FALSE(impl->getConfig()->getKeyFile().unspecified());
    expected = TEST_CA_DIR;
    expected += "/kea-client.key";
    EXPECT_EQ(expected, impl->getConfig()->getKeyFile().get());

    // Check the first peer parameters: it inherits them from the global level.
    HAConfig::PeerConfigPtr cfg = impl->getConfig()->getThisServerConfig();
    ASSERT_TRUE(cfg);
    EXPECT_TRUE(cfg->getTlsContext());

    // Check the second peer parameters: it overwrites them.
    cfg = impl->getConfig()->getPeerConfig("overwrite");
    ASSERT_TRUE(cfg);
    EXPECT_FALSE(cfg->getTrustAnchor().unspecified());
    expected = TEST_CA_DIR;
    EXPECT_EQ(expected, cfg->getTrustAnchor().get());
    EXPECT_FALSE(cfg->getCertFile().unspecified());
    expected = TEST_CA_DIR;
    expected += "/kea-server.crt";
    EXPECT_EQ(expected, cfg->getCertFile().get());
    EXPECT_FALSE(cfg->getKeyFile().unspecified());
    expected = TEST_CA_DIR;
    expected += "/kea-server.key";
    EXPECT_EQ(expected, cfg->getKeyFile().get());
    EXPECT_TRUE(cfg->getTlsContext());

    // Check the last peer parameters: it disables TLS by setting them to "".
    cfg = impl->getConfig()->getPeerConfig("disable");
    ASSERT_TRUE(cfg);
    EXPECT_FALSE(cfg->getTrustAnchor().unspecified());
    EXPECT_EQ("", cfg->getTrustAnchor().get());
    EXPECT_FALSE(cfg->getCertFile().unspecified());
    EXPECT_EQ("", cfg->getCertFile().get());
    EXPECT_FALSE(cfg->getKeyFile().unspecified());
    EXPECT_EQ("", cfg->getKeyFile().get());
    // The TLS context should be null.
    EXPECT_FALSE(cfg->getTlsContext());
}

// Test that a missing trust-anchor in the HTTPS parameter set raise an error.
TEST_F(HAConfigTest, missingTrustAnchor) {
    const std::string ha_config =
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"trust-anchor\": \"!CA!/kea-ca.crt\","
        "        \"cert-file\": \"!CA!/kea-client.crt\","
        "        \"key-file\": \"!CA!/kea-client.key\","
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
        "                \"trust-anchor\": \"\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]";
    const std::string& patched = replaceInConfig(ha_config, "!CA!",
                                                 TEST_CA_DIR);
    std::string expected = "bad TLS config for server server2: ";
    expected += "trust-anchor parameter is missing or empty: ";
    expected += "all or none of TLS parameters must be set";
    testInvalidConfig(patched, expected);
}

// Test that a missing cert-file in the HTTPS parameter set raise an error.
TEST_F(HAConfigTest, missingCertFile) {
    const std::string ha_config =
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"trust-anchor\": \"!CA!/kea-ca.crt\","
        "        \"cert-file\": \"!CA!/kea-client.crt\","
        "        \"key-file\": \"!CA!/kea-client.key\","
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
        "                \"cert-file\": \"\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]";
    const std::string& patched = replaceInConfig(ha_config, "!CA!",
                                                 TEST_CA_DIR);
    std::string expected = "bad TLS config for server server2: ";
    expected += "cert-file parameter is missing or empty: ";
    expected += "all or none of TLS parameters must be set";
    testInvalidConfig(patched, expected);
}

// Test that a missing key-file in the HTTPS parameter set raise an error.
TEST_F(HAConfigTest, missingKeyFile) {
    const std::string ha_config =
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"trust-anchor\": \"!CA!/kea-ca.crt\","
        "        \"cert-file\": \"!CA!/kea-client.crt\","
        "        \"key-file\": \"!CA!/kea-client.key\","
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
        "                \"key-file\": \"\","
        "                \"auto-failover\": true"
        "            }"
        "        ]"
        "    }"
        "]";
    const std::string& patched = replaceInConfig(ha_config, "!CA!",
                                                 TEST_CA_DIR);
    std::string expected = "bad TLS config for server server2: ";
    expected += "key-file parameter is missing or empty: ";
    expected += "all or none of TLS parameters must be set";
    testInvalidConfig(patched, expected);
}

// Test that a bad trust-anchor in the HTTPS parameter set raise an error.
TEST_F(HAConfigTest, badTrustAnchor) {
    const std::string ha_config =
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"trust-anchor\": \"/this-file-does-not-exist\","
        "        \"cert-file\": \"!CA!/kea-client.crt\","
        "        \"key-file\": \"!CA!/kea-client.key\","
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
        "]";
    const std::string& patched = replaceInConfig(ha_config, "!CA!",
                                                 TEST_CA_DIR);
    std::string expected = "bad TLS config for server server1: ";
    expected += "load of CA file '/this-file-does-not-exist' failed: ";
    // Backend dependent.
#ifdef WITH_OPENSSL
    expected += "No such file or directory";
#else
    expected += "I/O error: DataSource: Failure opening file /this-file-does-not-exist";
#endif
    testInvalidConfig(patched, expected);
}

// Test that a bad cert-file in the HTTPS parameter set raise an error.
TEST_F(HAConfigTest, badCertFile) {
    const std::string ha_config =
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"trust-anchor\": \"!CA!/kea-ca.crt\","
        "        \"cert-file\": \"/this-file-does-not-exist\","
        "        \"key-file\": \"!CA!/kea-client.key\","
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
        "]";
    const std::string& patched = replaceInConfig(ha_config, "!CA!",
                                                 TEST_CA_DIR);
    std::string expected = "bad TLS config for server server1: ";
    expected += "load of cert file '/this-file-does-not-exist' failed: ";
    // Backend dependent.
#ifdef WITH_OPENSSL
    expected += "No such file or directory";
#else
    expected += "I/O error: DataSource: Failure opening file /this-file-does-not-exist";
#endif
    testInvalidConfig(patched, expected);
}

// Test that a bad key-file in the HTTPS parameter set raise an error.
TEST_F(HAConfigTest, badKeyFile) {
    const std::string ha_config =
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"load-balancing\","
        "        \"trust-anchor\": \"!CA!/kea-ca.crt\","
        "        \"cert-file\": \"!CA!/kea-client.crt\","
        "        \"key-file\": \"/this-file-does-not-exist\","
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
        "]";
    const std::string& patched = replaceInConfig(ha_config, "!CA!",
                                                 TEST_CA_DIR);
    std::string expected = "bad TLS config for server server1: ";
    expected += "load of private key file '/this-file-does-not-exist' failed: ";
    // Backend dependent.
#ifdef WITH_OPENSSL
    expected += "No such file or directory";
#else
    expected += "I/O error: DataSource: Failure opening file /this-file-does-not-exist";
#endif
    testInvalidConfig(patched, expected);
}
#endif // WITH_OPENSSL || WITH_BOTAN_BOOST

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
    EXPECT_EQ(HAConfig::PASSIVE_BACKUP, HAConfig::stringToHAMode("passive-backup"));
}

// Test that HA mode name is generated correctly.
TEST_F(HAConfigTest, HAModeToString) {
    EXPECT_EQ("load-balancing", HAConfig::HAModeToString(HAConfig::LOAD_BALANCING));
    EXPECT_EQ("hot-standby", HAConfig::HAModeToString(HAConfig::HOT_STANDBY));
    EXPECT_EQ("passive-backup", HAConfig::HAModeToString(HAConfig::PASSIVE_BACKUP));
}

// Test that conversion of the 'pause' value works correctly.
TEST_F(HAConfigTest, stringToPausing) {
    EXPECT_EQ(STATE_PAUSE_ALWAYS,
              HAConfig::StateConfig::stringToPausing("always"));
    EXPECT_EQ(STATE_PAUSE_NEVER,
              HAConfig::StateConfig::stringToPausing("never"));
    EXPECT_EQ(STATE_PAUSE_ONCE,
              HAConfig::StateConfig::stringToPausing("once"));
}

// Test that pause parameter value is generated correctly.
TEST_F(HAConfigTest, pausingToString) {
    EXPECT_EQ("always",
              HAConfig::StateConfig::pausingToString(STATE_PAUSE_ALWAYS));
    EXPECT_EQ("never",
              HAConfig::StateConfig::pausingToString(STATE_PAUSE_NEVER));
    EXPECT_EQ("once",
              HAConfig::StateConfig::pausingToString(STATE_PAUSE_ONCE));
}

// Verifies permutations of HA+MT configuration.
TEST_F(HAConfigTest, multiThreadingPermutations) {

    // Structure describing a test scenario.
    struct Scenario {
        std::string desc_;              // Description of the scenario.
        std::string mt_json_;           // multi-threading config to use.
        bool dhcp_mt_enabled_;          // True if DHCP multi-threading is enabled.
        uint32_t dhcp_threads_;         // Value of DHCP thread-pool-size.
        bool exp_ha_mt_enabled_;        // If HA+MT should be enabled
        bool exp_listener_;             // If HA+MT should use dedicated listener.
        uint32_t exp_listener_threads_; // Expected number of listener threads.
        uint32_t exp_client_threads_;   // Expected number of client threads.
    };

    // Mnemonic constants.
    bool dhcp_mt = true;
    bool ha_mt = true;
    bool listener = true;

    // Number of threads the system reports as supported.
    uint32_t sys_threads = MultiThreadingMgr::detectThreadCount();

    std::vector<Scenario> scenarios {
        {
            "1 no ha+mt/default",
            "",
            dhcp_mt, 4,
            !ha_mt, !listener, 0, 0
        },
        {
            "2 dhcp mt enabled, ha mt disabled",
            makeHAMtJson(!ha_mt, !listener, 0, 0),
            dhcp_mt, 4,
            !ha_mt, !listener, 0, 0
        },
        {
            "3 dhcp mt disabled, ha mt enabled",
            makeHAMtJson(ha_mt, listener, 0, 0),
            !dhcp_mt, 4,
            !ha_mt, !listener, 0, 0
        },
        {
            "4 dhcp mt enabled, ha mt enabled, listener disabled",
            makeHAMtJson(ha_mt, !listener, 0, 0),
            dhcp_mt, 4,
            ha_mt, !listener, 4, 4
        },
        {
            "5 dhcp mt enabled, ha mt enabled, listener enabled",
            makeHAMtJson(ha_mt, listener, 0, 0),
            dhcp_mt, 4,
            ha_mt, listener, 4, 4
        },
        {
            "6 explicit DHCP threads, explicit thread values",
            makeHAMtJson(ha_mt, listener, 5, 6),
            dhcp_mt, 4,
            ha_mt, listener, 5, 6
        },
        {
            "7 explicit DHCP threads, zero thread values",
            makeHAMtJson(ha_mt, listener, 0, 0),
            dhcp_mt, 8,
            ha_mt, listener, 8, 8
        },
        {
            "8 DHCP auto detect threads, zero thread values",
            // Special case: if system reports supported threads as 0
            // then HA+MT should be disabled.  Otherwise it should
            // be enabled with listener and client threads set to the
            // reported value.
            makeHAMtJson(ha_mt, listener, 0, 0),
            dhcp_mt, 0,
            (sys_threads > 0), listener, sys_threads, sys_threads
        }
    };

    // Iterate over the scenarios.
    for (auto const& scenario : scenarios) {
        SCOPED_TRACE(scenario.desc_);

        // Build the HA JSON configuration.
        std::stringstream ss;
        ss <<
            "["
            "    {"
            "        \"this-server-name\": \"server1\","
            "        \"mode\": \"passive-backup\","
            "        \"wait-backup-ack\": true,"
            "        \"peers\": ["
            "            {"
            "                \"name\": \"server1\","
            "                \"url\": \"http://127.0.0.1:8080/\","
            "                \"role\": \"primary\""
            "            },"
            "            {"
            "                \"name\": \"server2\","
            "                \"url\": \"http://127.0.0.1:8081/\","
            "                \"role\": \"backup\""
            "            }"
            "        ]";

        if (!scenario.mt_json_.empty()) {
            ss << "," << scenario.mt_json_;
        }

        ss << "}]";
        ConstElementPtr config_json;
        ASSERT_NO_THROW_LOG(config_json = Element::fromJSON(ss.str()));

        // Set DHCP multi-threading configuration in CfgMgr.
        setDHCPMultiThreadingConfig(scenario.dhcp_mt_enabled_, scenario.dhcp_threads_);

        // Create and configure the implementation.
        HAImplPtr impl(new HAImpl());
        ASSERT_NO_THROW_LOG(impl->configure(config_json));

        // Fetch the updated config.
        HAConfigPtr ha_config = impl->getConfig();

        // Verify the configuration is as expected.
        if (!scenario.exp_ha_mt_enabled_) {
            // When HA+MT is disabled, the other values are moot.
            ASSERT_FALSE(ha_config->getEnableMultiThreading());
        } else {
            ASSERT_TRUE(ha_config->getEnableMultiThreading());
            EXPECT_EQ(ha_config->getHttpDedicatedListener(), scenario.exp_listener_);
            EXPECT_EQ(ha_config->getHttpListenerThreads(), scenario.exp_listener_threads_);
            EXPECT_EQ(ha_config->getHttpClientThreads(), scenario.exp_client_threads_);
       }
    }
}

// Check that an IPv6 address can be used as part of a value for "url".
TEST_F(HAConfigTest, ipv6Url) {
    std::string const ha_config(R"(
        [
            {
                "mode": "load-balancing",
                "peers": [
                    {
                        "name": "server1",
                        "role": "primary",
                        "url": "http://[2001:db8::1]:8080/"
                    },
                    {
                        "name": "server2",
                        "role": "secondary",
                        "url": "http://[2001:db8::2]:8080/"
                    }
                ],
                "this-server-name": "server1"
            }
        ]
    )");

    // Configure HA.
    HAImplPtr impl(new HAImpl());
    ASSERT_NO_THROW_LOG(impl->configure(Element::fromJSON(ha_config)));

    // Check the URL.
    EXPECT_EQ(impl->getConfig()->getThisServerConfig()->getUrl().toText(), "http://[2001:db8::1]:8080/");
}

} // end of anonymous namespace
