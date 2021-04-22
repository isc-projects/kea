// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <ha_test.h>
#include <ha_config.h>
#include <ha_service.h>
#include <ha_service_states.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <dhcp/classify.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcp/pkt4.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/network_state.h>
#include <dhcpsrv/subnet_id.h>
#include <hooks/parking_lots.h>
#include <http/basic_auth_config.h>
#include <http/date_time.h>
#include <http/http_types.h>
#include <http/listener.h>
#include <http/post_request_json.h>
#include <http/response_creator.h>
#include <http/response_creator_factory.h>
#include <http/response_json.h>
#include <util/multi_threading_mgr.h>
#include <testutils/gtest_utils.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

#include <functional>
#include <sstream>
#include <set>
#include <string>
#include <vector>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::ha;
using namespace isc::ha::test;
using namespace isc::hooks;
using namespace isc::http;
using namespace isc::util;

namespace {

/// @brief IP address to which HTTP service is bound.
const std::string SERVER_ADDRESS = "127.0.0.1";

/// @brief Port number to which HTTP service is bound.
const unsigned short SERVER_PORT = 18123;

/// @brief Request Timeout used in most of the tests (ms).
const long REQUEST_TIMEOUT = 10000;

/// @brief Persistent connection idle timeout used in most of the tests (ms).
const long IDLE_TIMEOUT = 10000;

/// @brief Test timeout (ms).
const long TEST_TIMEOUT = 10000;

/// @brief Generates IPv4 leases to be used by the tests.
///
/// @param [out] leases reference to the container where leases are stored.
void generateTestLeases(std::vector<Lease4Ptr>& leases) {
    for (uint8_t i = 1; i <= 10; ++i) {
        uint32_t lease_address = 0xC0000201 + 256 * i;
        std::vector<uint8_t> hwaddr(6, i);
        Lease4Ptr lease(new Lease4(IOAddress(lease_address),
                                   HWAddrPtr(new HWAddr(hwaddr, HTYPE_ETHER)),
                                   ClientIdPtr(),
                                   60,
                                   static_cast<time_t>(1000 + i),
                                   SubnetID(i)));
        leases.push_back(lease);
    }
}

/// @brief Generates IPv6 leases to be used by the tests.
///
/// @param [out] leases reference to the container where leases are stored.
void generateTestLeases(std::vector<Lease6Ptr>& leases) {
    std::vector<uint8_t> address_bytes = IOAddress("2001:db8:1::1").toBytes();
    for (uint8_t i = 1; i <= 10; ++i) {
        DuidPtr duid(new DUID(std::vector<uint8_t>(10, i)));
        address_bytes[6] += i;
        Lease6Ptr lease(new Lease6(Lease::TYPE_NA,
                                   IOAddress::fromBytes(AF_INET6, &address_bytes[0]),
                                   duid, 1, 50, 60, SubnetID(i)));
        leases.push_back(lease);
    }
}

/// @brief Returns generated leases in JSON format.
///
/// @tparam LeasesVec vector of IPv4 or IPv6 lease pointers.
/// @param leases reference to the container holding leases to be
/// converted to JSON format.
template<typename LeasesVec>
ConstElementPtr getLeasesAsJson(const LeasesVec& leases) {
    ElementPtr leases_json = Element::createList();
    for (auto l = leases.begin(); l != leases.end(); ++l) {
        leases_json->add((*l)->toElement());
    }
    return (leases_json);
}

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
    }

    /// @brief Destructor.
    ///
    /// Stops all test servers.
    ~HAMtServiceTest() {
        io_service_->get_io_service().reset();
        io_service_->poll();
        MultiThreadingMgr::instance().setMode(false);
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

// Verifies permuations of HA+MT configuration and start-up.
TEST_F(HAMtServiceTest, multiThreadingStartup) {

    // Structure describing a test scenario.
    struct Scenario {
        std::string desc_;              // Description of the scenario.
        std::string mt_json_;           // multi-threading config to use.
        bool dhcp_mt_enabled_;          // True if DHCP multi-threading is enabled.
        uint32_t dhcp_threads_;         // Value of DHCP thread-pool-size.
        bool exp_ha_mt_enabled_;        // If HA+MT should be enabled
        bool exp_listener_;             // if HA+MT should use dedicated listener.
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
            "3 dhcp mt disabled, mt enabled",
            makeHAMtJson(ha_mt, listener, 0, 0),
            !dhcp_mt, 4,
            !ha_mt, !listener, 0, 0
        },
        {
            "4 dhcp mt enabled, mt enabled, listener disabled",
            makeHAMtJson(ha_mt, !listener, 0, 0),
            dhcp_mt, 4,
            ha_mt, !listener, 4, 4
        },
        {
            "5 dhcp mt enabled, mt enabled, listener enabled",
            makeHAMtJson(ha_mt, !listener, 0, 0),
            dhcp_mt, 4,
            ha_mt, !listener, 4, 4
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

        // Instanatiate the service.
        TestHAServicePtr service;
        ASSERT_NO_THROW_LOG(service.reset(new TestHAService(io_service_, network_state_,
                                                            ha_config)));
        ASSERT_NO_THROW(service->startClientAndListener());

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

        // We sould have a listening listener with the expected number of threads.
        ASSERT_TRUE(service->listener_);
        EXPECT_TRUE(service->listener_->isListening());
        EXPECT_EQ(service->listener_->getThreadPoolSize(), scenario.exp_listener_threads_);
        // Currently thread count should be the same as thread pool size.  This might
        // change if we go to so some sort of dynamic thread instance management.
        EXPECT_EQ(service->listener_->getThreadCount(), scenario.exp_listener_threads_);
    }
}

TEST_F(HAMtServiceTest, twoServicesFun) {
}

} // end of anonymous namespace
