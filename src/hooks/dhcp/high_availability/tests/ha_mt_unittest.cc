// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <config/cmd_response_creator.h>
#include <ha_test.h>
#include <ha_config.h>
#include <ha_service.h>
#include <http/http_thread_pool.h>

#include <util/multi_threading_mgr.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;

using namespace isc::ha;
using namespace isc::ha::test;
using namespace isc::http;
using namespace isc::util;

namespace {

/// @brief Derivation of the @c HAService which provides access to
/// protected methods and members.
class TestHAService : public HAService {
public:

    /// @brief Constructor.
    ///
    /// @param io_service Pointer to the IO service used by the DHCP server.
    /// @param network_state Object holding state of the DHCP service
    /// (enabled/disabled).
    /// @param config Parsed HA hook library configuration.
    /// @param server_type Server type, i.e. DHCPv4 or DHCPv6 server.
    TestHAService(const IOServicePtr& io_service,
                  const NetworkStatePtr& network_state,
                  const HAConfigPtr& config,
                  const HAServerType& server_type = HAServerType::DHCPv4)
        : HAService(io_service, network_state, config, server_type) {
    }

    /// @brief Test version of the @c HAService::runModel.
    ///
    /// The original implementation of this method returns control when
    /// @c NOP_EVT is found. This implementation runs a
    /// single handler to allow the tests to verify if the state machine
    /// transitions to an expected state before it is run again.
    virtual void runModel(unsigned int event) {
        try {
            postNextEvent(event);
            getState(getCurrState())->run();

        } catch (const std::exception& ex) {
            abortModel(ex.what());
        }
    }

    /// @brief Schedules asynchronous "dhcp-disable" command to the specified
    /// server.
    ///
    /// This variant of the method uses default HTTP client for communication.
    ///
    /// @param server_name name of the server to which the command should be
    /// sent.
    /// @param max_period maximum number of seconds for which the DHCP service
    /// should be disabled.
    /// @param post_request_action pointer to the function to be executed when
    /// the request is completed.
    void asyncDisableDHCPService(const std::string& server_name,
                                 const unsigned int max_period,
                                 const PostRequestCallback& post_request_action) {
        HAService::asyncDisableDHCPService(*client_, server_name, max_period,
                                           post_request_action);
    }

    /// @brief Schedules asynchronous "dhcp-enable" command to the specified
    /// server.
    ///
    /// This variant of the method uses default HTTP client for communication.
    ///
    /// @param server_name name of the server to which the command should be
    /// sent.
    /// @param post_request_action pointer to the function to be executed when
    /// the request is completed.
    void asyncEnableDHCPService(const std::string& server_name,
                                const PostRequestCallback& post_request_action) {
        HAService::asyncEnableDHCPService(*client_, server_name, post_request_action);
    }

    using HAService::asyncSendHeartbeat;
    using HAService::asyncSyncLeases;
    using HAService::postNextEvent;
    using HAService::transition;
    using HAService::verboseTransition;
    using HAService::shouldSendLeaseUpdates;
    using HAService::shouldQueueLeaseUpdates;
    using HAService::pendingRequestSize;
    using HAService::getPendingRequest;
    using HAService::network_state_;
    using HAService::config_;
    using HAService::communication_state_;
    using HAService::query_filter_;
    using HAService::lease_update_backlog_;
    using HAService::client_;
    using HAService::listener_;
};

/// @brief Pointer to the @c TestHAService.
typedef boost::shared_ptr<TestHAService> TestHAServicePtr;

/// @brief Test fixture class for @c HAService multi-threading.
class HAMtServiceTest : public HATest {
public:

    /// @brief Constructor.
    HAMtServiceTest()
        : HATest() {
        MultiThreadingMgr::instance().setMode(true);
        CmdResponseCreator::command_accept_list_.clear();
    }

    /// @brief Destructor.
    ///
    /// Stops all test servers.
    ~HAMtServiceTest() {
        io_service_->get_io_service().reset();
        io_service_->poll();
        MultiThreadingMgr::instance().setMode(false);
        CmdResponseCreator::command_accept_list_.clear();
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
};

// Verifies HA+MT start, pause, resume, and stop. Note
// that pause and resume are tested indirectly through
// entry and exit of a critical section.
TEST_F(HAMtServiceTest, multiThreadingBasics) {

    // Build the HA JSON configuration.
    std::stringstream ss;
    ss <<
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"passive-backup\","
        "        \"wait-backup-ack\": true,"
        "        \"restrict-commands\": true,"
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

    // Enable MT, listener, and 3 threads for both client and listener.
    ss << "," << makeHAMtJson(true, true, 3, 3) << "}]";
    ConstElementPtr config_json;
    ASSERT_NO_THROW_LOG(config_json = Element::fromJSON(ss.str()));

    // Enable DHCP multi-threading configuration in CfgMgr with 3 threads.
    setDHCPMultiThreadingConfig(true, 3);

    // Create the HA configuration
    HAConfigPtr ha_config(new HAConfig());
    HAConfigParser parser;
    ASSERT_NO_THROW_LOG(parser.parse(ha_config, config_json));

    // Instantiate the service.
    TestHAServicePtr service;
    ASSERT_NO_THROW_LOG(service.reset(new TestHAService(io_service_, network_state_,
                                                        ha_config)));
    // Multi-threading should be enabled.
    ASSERT_TRUE(ha_config->getEnableMultiThreading());

    // Command filtering is enabled.
    EXPECT_FALSE(CmdResponseCreator::command_accept_list_.empty());

    // Now we'll start, pause, resume and stop a few times.
    for (int i = 0; i < 3; ++i) {
        // Verify we're stopped.
        // Client should exist but be stopped.
        ASSERT_TRUE(service->client_);
        ASSERT_TRUE(service->client_->isStopped());
        if (i == 0) {
            EXPECT_FALSE(service->client_->getThreadIOService()->stopped());
        } else {
            EXPECT_TRUE(service->client_->getThreadIOService()->stopped());
        }

        // Listener should exist but be stopped.
        ASSERT_TRUE(service->listener_);
        ASSERT_TRUE(service->listener_->isStopped());
        EXPECT_FALSE(service->listener_->getThreadIOService());

        // Start client and listener.
        ASSERT_NO_THROW_LOG(service->startClientAndListener());

        // Verify we've started.
        // Client should be running.
        ASSERT_TRUE(service->client_->isRunning());
        ASSERT_TRUE(service->client_->getThreadIOService());
        EXPECT_FALSE(service->client_->getThreadIOService()->stopped());
        EXPECT_EQ(service->client_->getThreadPoolSize(), 3);
        EXPECT_EQ(service->client_->getThreadCount(), 3);

        // Listener should be running.
        ASSERT_TRUE(service->listener_->isRunning());
        ASSERT_TRUE(service->listener_->getThreadIOService());
        EXPECT_FALSE(service->listener_->getThreadIOService()->stopped());
        EXPECT_EQ(service->listener_->getThreadPoolSize(), 3);
        EXPECT_EQ(service->listener_->getThreadCount(), 3);

        {
            // Entering a critical section should pause both client
            // and listener.
            MultiThreadingCriticalSection cs;

            // Client should be paused.
            ASSERT_TRUE(service->client_->isPaused());
            EXPECT_TRUE(service->client_->getThreadIOService()->stopped());

            // Listener should be paused.
            ASSERT_TRUE(service->listener_->isPaused());
            EXPECT_TRUE(service->listener_->getThreadIOService()->stopped());
        }

        // Exiting critical section should resume both client
        // and listener.

        // Client should be running.
        ASSERT_TRUE(service->client_->isRunning());
        EXPECT_FALSE(service->client_->getThreadIOService()->stopped());

        // Listener should be running.
        ASSERT_TRUE(service->listener_->isRunning());
        EXPECT_FALSE(service->listener_->getThreadIOService()->stopped());

        // Stop should succeed.
        ASSERT_NO_THROW_LOG(service->stopClientAndListener());
    }
}

// Verifies multiThreadingBasics can be extended to use HTTPS/TLS>
TEST_F(HAMtServiceTest, multiThreadingTls) {

    // Build the HA JSON configuration.
    std::stringstream ss;
    ss <<
        "["
        "    {"
        "        \"this-server-name\": \"server1\","
        "        \"mode\": \"passive-backup\","
        "        \"wait-backup-ack\": true,"
        "        \"require-client-certs\": false,"
        "        \"peers\": ["
        "            {"
        "                \"name\": \"server1\","
        "                \"url\": \"https://127.0.0.1:8080/\","
        "                \"role\": \"primary\","
        "                \"trust-anchor\": \"!CA!/kea-ca.crt\","
        "                \"cert-file\": \"!CA!/kea-server.crt\","
        "                \"key-file\": \"!CA!/kea-server.key\""
        "            },"
        "            {"
        "                \"name\": \"server2\","
        "                \"url\": \"https://127.0.0.1:8081/\","
        "                \"role\": \"backup\","
        "                \"trust-anchor\": \"!CA!/kea-ca.crt\","
        "                \"cert-file\": \"!CA!/kea-client.crt\","
        "                \"key-file\": \"!CA!/kea-client.key\""
        "            }"
        "        ]";

    // Enable MT, listener, and 3 threads for both client and listener.
    ss << "," << makeHAMtJson(true, true, 3, 3) << "}]";
    ConstElementPtr config_json;
    const std::string& patched = replaceInConfig(ss.str(), "!CA!",
                                                 TEST_CA_DIR);
    ASSERT_NO_THROW_LOG(config_json = Element::fromJSON(patched));

    // Enable DHCP multi-threading configuration in CfgMgr with 3 threads.
    setDHCPMultiThreadingConfig(true, 3);

    // Create the HA configuration
    HAConfigPtr ha_config(new HAConfig());
    HAConfigParser parser;
    ASSERT_NO_THROW_LOG(parser.parse(ha_config, config_json));

    // Instantiate the service.
    TestHAServicePtr service;
    ASSERT_NO_THROW_LOG(service.reset(new TestHAService(io_service_, network_state_,
                                                        ha_config)));
    // Multi-threading should be enabled.
    ASSERT_TRUE(ha_config->getEnableMultiThreading());

    // Now we'll start, pause, resume and stop a few times.
    for (int i = 0; i < 3; ++i) {
        // Verify we're stopped.
        // Client should exist but be stopped.
        ASSERT_TRUE(service->client_);
        ASSERT_TRUE(service->client_->isStopped());
        if (i == 0) {
            EXPECT_FALSE(service->client_->getThreadIOService()->stopped());
        } else {
            EXPECT_TRUE(service->client_->getThreadIOService()->stopped());
        }

        // Listener should exist but be stopped.
        ASSERT_TRUE(service->listener_);
        ASSERT_TRUE(service->listener_->isStopped());
        EXPECT_FALSE(service->listener_->getThreadIOService());

        // Start client and listener.
        ASSERT_NO_THROW_LOG(service->startClientAndListener());

        // Verify we've started.
        // Client should be running.
        ASSERT_TRUE(service->client_->isRunning());
        ASSERT_TRUE(service->client_->getThreadIOService());
        EXPECT_FALSE(service->client_->getThreadIOService()->stopped());
        EXPECT_EQ(service->client_->getThreadPoolSize(), 3);
        EXPECT_EQ(service->client_->getThreadCount(), 3);

        // Listener should be running.
        ASSERT_TRUE(service->listener_->isRunning());
        ASSERT_TRUE(service->listener_->getThreadIOService());
        EXPECT_FALSE(service->listener_->getThreadIOService()->stopped());
        EXPECT_EQ(service->listener_->getThreadPoolSize(), 3);
        EXPECT_EQ(service->listener_->getThreadCount(), 3);

        {
            // Entering a critical section should pause both client
            // and listener.
            MultiThreadingCriticalSection cs;

            // Client should be paused.
            ASSERT_TRUE(service->client_->isPaused());
            EXPECT_TRUE(service->client_->getThreadIOService()->stopped());

            // Listener should be paused.
            ASSERT_TRUE(service->listener_->isPaused());
            EXPECT_TRUE(service->listener_->getThreadIOService()->stopped());
        }

        // Exiting critical section should resume both client
        // and listener.

        // Client should be running.
        ASSERT_TRUE(service->client_->isRunning());
        EXPECT_FALSE(service->client_->getThreadIOService()->stopped());

        // Listener should be running.
        ASSERT_TRUE(service->listener_->isRunning());
        EXPECT_FALSE(service->listener_->getThreadIOService()->stopped());

        // Stop should succeed.
        ASSERT_NO_THROW_LOG(service->stopClientAndListener());
    }
}

// Verifies permutations of HA+MT configuration and start-up.
TEST_F(HAMtServiceTest, multiThreadingConfigStartup) {

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
        /// @todo this is a hack... we have chicken-egg...  CmdHttpListener won't
        /// start if MT is not enabled BUT that happens after config hook point
        MultiThreadingMgr::instance().setMode(scenario.dhcp_mt_enabled_);

        // Create the HA configuration
        HAConfigPtr ha_config(new HAConfig());
        HAConfigParser parser;
        ASSERT_NO_THROW_LOG(parser.parse(ha_config, config_json));

        // Instantiate the service.
        TestHAServicePtr service;
        ASSERT_NO_THROW_LOG(service.reset(new TestHAService(io_service_, network_state_,
                                                            ha_config)));
        ASSERT_NO_THROW_LOG(service->startClientAndListener());

        // Verify the configuration is as expected.
        if (!scenario.exp_ha_mt_enabled_) {
            // When HA+MT is disabled, client should be single-threaded.
            ASSERT_TRUE(service->client_);
            EXPECT_FALSE(service->client_->getThreadIOService());
            EXPECT_EQ(service->client_->getThreadPoolSize(), 0);
            EXPECT_EQ(service->client_->getThreadCount(), 0);

            // Listener should not exist.
            ASSERT_FALSE(service->listener_);
            continue;
        }

        // Multi-threading should be enabled.
        ASSERT_TRUE(ha_config->getEnableMultiThreading());

        // When HA+MT is enabled, client should be multi-threaded.
        ASSERT_TRUE(service->client_);
        EXPECT_TRUE(service->client_->isRunning());
        EXPECT_TRUE(service->client_->getThreadIOService());
        EXPECT_EQ(service->client_->getThreadPoolSize(), scenario.exp_client_threads_);

        // Currently thread count should be the same as thread pool size.  This might
        // change if we go to so some sort of dynamic thread instance management.
        EXPECT_EQ(service->client_->getThreadCount(), scenario.exp_client_threads_);

        if (!scenario.exp_listener_) {
            // We should not have a listener.
            ASSERT_FALSE(service->listener_);
            continue;
        }

        // We should have a running listener with the expected number of threads.
        ASSERT_TRUE(service->listener_);
        EXPECT_TRUE(service->listener_->isRunning());
        ASSERT_TRUE(service->listener_->getThreadIOService());
        EXPECT_EQ(service->listener_->getThreadPoolSize(), scenario.exp_listener_threads_);

        // Currently thread count should be the same as thread pool size.  This might
        // change if we go to so some sort of dynamic thread instance management.
        EXPECT_EQ(service->listener_->getThreadCount(), scenario.exp_listener_threads_);

        ASSERT_NO_THROW_LOG(service->stopClientAndListener());
    }
}

} // end of anonymous namespace
