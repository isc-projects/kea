// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the ddns tuning hook library. In order to test the load
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

/// @brief Test fixture for testing loading and unloading the ddns tuning library
class PingCheckLibLoadTest : public isc::test::LibLoadTest {
public:
    /// @brief Constructor
    PingCheckLibLoadTest() : LibLoadTest(PING_CHECK_LIB_SO) {
    }

    /// @brief Destructor
    virtual ~PingCheckLibLoadTest() {
    }

    /// @brief Registers hooks in the hook manager.
    /// Normally this is done by the server core code (@c Dhcpv4Srv).
    void registerHooks() {
        hook_index_dhcp4_srv_configured_ = HooksManager::registerHook("dhcp4_srv_configured");
        hook_index_lease4_offer_ = HooksManager::registerHook("lease4_offer");
    }

    /// @brief  Checks that expected callouts are present.
    void calloutsPresent() {
        bool result;
        ASSERT_NO_THROW_LOG(result = HooksManager::calloutsPresent(hook_index_dhcp4_srv_configured_));
        EXPECT_TRUE(result);
        ASSERT_NO_THROW_LOG(result = HooksManager::calloutsPresent(hook_index_lease4_offer_));
        EXPECT_TRUE(result);
    }

    /// @brief Creates a valid set of ping-check hook parameters.
    virtual ElementPtr validConfigParams() {
        ElementPtr params = Element::createMap();
        params->set("min-ping-requests", Element::create(3));
        params->set("reply-timeout", Element::create(100));
        params->set("enable-ping-check", Element::create(true));
        params->set("ping-cltt-secs", Element::create(60));
        params->set("ping-channel-threads", Element::create(1));
        return (params);
    }

    /// @brief Hook index values.
    int hook_index_dhcp4_srv_configured_;
    int hook_index_lease4_offer_;
};

// Simple V4 test that checks the library can be loaded and unloaded several times.
TEST_F(PingCheckLibLoadTest, validLoad4) {
    validDaemonTest("kea-dhcp4", AF_INET, valid_params_);
}

// Simple test that checks the library cannot be loaded by invalid daemons.
TEST_F(PingCheckLibLoadTest, invalidDaemonLoad) {
    // V6 is invalid  regardless of family.
    invalidDaemonTest("kea-dhcp6", AF_INET, valid_params_);
    invalidDaemonTest("kea-dhcp6", AF_INET6, valid_params_);

    invalidDaemonTest("kea-ctrl-agent", AF_INET, valid_params_);
    invalidDaemonTest("kea-dhcp-ddns", AF_INET, valid_params_);
    invalidDaemonTest("bogus", AF_INET, valid_params_);
}

// Verifies that callout functions exist after loading the library.
TEST_F(PingCheckLibLoadTest, verifyCallouts) {
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

} // end of anonymous namespace
