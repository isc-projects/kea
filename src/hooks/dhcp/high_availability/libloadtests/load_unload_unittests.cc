// Copyright (C) 2019-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the high availability hook library. In order to test
/// the load function, one must be able to pass it hook library
/// parameters. The the only way to populate these parameters is by
/// actually loading the library via HooksManager::loadLibraries().

#include <config.h>

#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <hooks/hooks_manager.h>
#include <process/daemon.h>
#include <testutils/lib_load_test_fixture.h>

#include <gtest/gtest.h>
#include <errno.h>

using namespace std;
using namespace isc;
using namespace isc::hooks;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::process;

namespace {

/// @brief Test fixture for testing loading and unloading the HA library
class HALibLoadTest : public isc::test::LibLoadTest {
public:
    /// @brief Constructor
    HALibLoadTest() : LibLoadTest(LIBDHCP_HA_SO) {
    }

    /// @brief Destructor
    virtual ~HALibLoadTest() {
    }

    /// @brief Creates valid HA configuration with three servers.
    virtual ElementPtr validConfigParams() {
        std::string config_text =
            "["
            "     {"
            "         \"this-server-name\": \"server1\","
            "         \"mode\": \"hot-standby\","
            "         \"sync-page-limit\": 3,"
            "         \"heartbeat-delay\": 1000,"
            "         \"max-response-delay\": 1000,"
            "         \"max-ack-delay\": 10000,"
            "         \"max-unacked-clients\": 10,"
            "         \"peers\": ["
            "             {"
            "                 \"name\": \"server1\","
            "                 \"url\": \"http://127.0.0.1:18123/\","
            "                 \"role\": \"primary\","
            "                 \"auto-failover\": true"
            "             },"
            "             {"
            "                 \"name\": \"server2\","
            "                 \"url\": \"http://127.0.0.1:18124/\","
            "                 \"role\": \"standby\","
            "                 \"auto-failover\": true"
            "             },"
            "             {"
            "                 \"name\": \"server3\","
            "                 \"url\": \"http://127.0.0.1:18125/\","
            "                 \"role\": \"backup\","
            "                 \"auto-failover\": false"
            "             }"
            "         ]"
            "     }"
            "]";

        // Prepare parameters,
        ElementPtr params = Element::createMap();
        params->set("high-availability",  Element::fromJSON(config_text));
        return (params);
    }
};

// Simple V4 test that checks the library can be loaded and unloaded several times.
TEST_F(HALibLoadTest, validLoadDhcp4) {
    validDaemonTest("kea-dhcp4", AF_INET, valid_params_);
}

// Simple test that checks the library can be loaded in a DHCPv6 server.
TEST_F(HALibLoadTest, validLoadDhcp6) {
    validDaemonTest("kea-dhcp6", AF_INET6, valid_params_);
}

// Simple test that checks the library cannot by loaded by invalid daemons.
TEST_F(HALibLoadTest, invalidDaemonLoad) {
    // V4 is invalid when family is AF_INET6
    invalidDaemonTest("kea-dhcp4", AF_INET6, valid_params_);

    // V6 is invalid when family is AF_INET
    invalidDaemonTest("kea-dhcp6", AF_INET, valid_params_);

    invalidDaemonTest("kea-ctrl-agent", AF_INET, valid_params_);
    invalidDaemonTest("kea-dhcp-ddns", AF_INET, valid_params_);
    invalidDaemonTest("bogus", AF_INET, valid_params_);
}

} // end of anonymous namespace
