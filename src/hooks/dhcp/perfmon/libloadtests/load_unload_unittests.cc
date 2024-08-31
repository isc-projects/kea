// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the perfmon hook library. In order to test the load
/// function, one must be able to pass it hook library parameters. The
/// the only way to populate these parameters is by actually loading the
/// library via HooksManager::loadLibraries().

#include <config.h>

#include <dhcpsrv/testutils/lib_load_test_fixture.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>
#include <errno.h>

using namespace std;
using namespace isc;
using namespace isc::hooks;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::process;

namespace {

/// @brief Test fixture for testing loading and unloading the perfmon library
class PerfMonLibLoadTest : public isc::test::LibLoadTest {
public:
    /// @brief Constructor
    PerfMonLibLoadTest() : LibLoadTest(LIBDHCP_PERFMON_SO) {
    }

    /// @brief Destructor
    virtual ~PerfMonLibLoadTest() {
        unloadLibraries();
    }

    /// @brief Registers hooks in the hook manager.
    ///
    /// Normally this is done by the server core code.
    void registerHooks() {
        if (isc::dhcp::CfgMgr::instance().getFamily() == AF_INET) {
            hook_index_dhcpx_srv_configured_ = HooksManager::registerHook("dhcp4_srv_configured");
            hook_index_pktx_send_ = HooksManager::registerHook("pkt4_send");
        } else {
            hook_index_dhcpx_srv_configured_ = HooksManager::registerHook("dhcp6_srv_configured");
            hook_index_pktx_send_ = HooksManager::registerHook("pkt6_send");
        }
    }

    /// @brief  Checks that expected callouts are present.
    void calloutsPresent() {
        bool result;
        ASSERT_NO_THROW_LOG(result = HooksManager::calloutsPresent(hook_index_dhcpx_srv_configured_));
        EXPECT_TRUE(result);
        ASSERT_NO_THROW_LOG(result = HooksManager::calloutsPresent(hook_index_pktx_send_));
        EXPECT_TRUE(result);
    }

    /// @brief Creates a valid set configuration parameters valid for the library.
    virtual isc::data::ElementPtr validConfigParams() {
        std::string valid_config =
            R"({
                    "enable-monitoring": true,
                    "interval-width-secs": 5,
                    "stats-mgr-reporting": true,
                    "alarm-report-secs": 600,
                    "alarms": [{
                            "duration-key": {
                                "query-type": "*",
                                "response-type": "*",
                                "start-event": "socket-received",
                                "stop-event": "buffer-read",
                                "subnet-id": 70
                                },
                            "enable-alarm": true,
                            "high-water-ms": 500,
                            "low-water-ms": 25
                        }]
                })";

        // Convert JSON texts to Element map.
        return (Element::fromJSON(valid_config));
    }

    /// @brief Hook index values.
    int hook_index_pktx_send_;
    int hook_index_dhcpx_srv_configured_;
};

// Simple V4 test that checks the library can be loaded and unloaded several times.
TEST_F(PerfMonLibLoadTest, validLoad4) {
    validDaemonTest("kea-dhcp4", AF_INET, valid_params_);
}

// Simple V6 test that checks the library can be loaded and unloaded several times.
TEST_F(PerfMonLibLoadTest, validLoad6) {
    validDaemonTest("kea-dhcp6", AF_INET6, valid_params_);
}

// Simple test that checks the library cannot by loaded by invalid daemons.
TEST_F(PerfMonLibLoadTest, invalidDaemonLoad) {
    invalidDaemonTest("kea-ctrl-agent");
    invalidDaemonTest("kea-dhcp-ddns");
    invalidDaemonTest("bogus");
}

// Verifies that callout functions exist after loading the library.
TEST_F(PerfMonLibLoadTest, verifyCallouts4) {
    // Set family and daemon's proc name and register hook points.
    isc::dhcp::CfgMgr::instance().setFamily(AF_INET);
    isc::process::Daemon::setProcName("kea-dhcp4");
    registerHooks();

    // Add library to config and load it.
    ASSERT_NO_THROW_LOG(addLibrary(lib_so_name_, valid_params_));
    ASSERT_NO_THROW_LOG(loadLibraries());

    // Verify that expected callouts are present.
    calloutsPresent();

    // Unload the library.
    ASSERT_NO_THROW_LOG(unloadLibraries());
}

// Verifies that callout functions exist after loading the library.
TEST_F(PerfMonLibLoadTest, verifyCallouts6) {
    // Set family and daemon's proc name and register hook points.
    isc::dhcp::CfgMgr::instance().setFamily(AF_INET6);
    isc::process::Daemon::setProcName("kea-dhcp6");
    registerHooks();

    // Add library to config and load it.
    ASSERT_NO_THROW_LOG(addLibrary(lib_so_name_, valid_params_));
    ASSERT_NO_THROW_LOG(loadLibraries());

    // Verify that expected callouts are present.
    calloutsPresent();

    // Unload the library.
    ASSERT_NO_THROW_LOG(unloadLibraries());
}

} // end of anonymous namespace
