// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
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
class LibLoadTest : public ::testing::Test {
public:
    /// @brief Constructor
    LibLoadTest() {
        reset();
    }

    /// @brief Destructor
    /// Removes files that may be left over from previous tests
    virtual ~LibLoadTest() {
        reset();
    }

    /// @brief Removes files that may be left over from previous tests
    virtual void reset() {
        HooksManager::unloadLibraries();
    }

    /// @brief Adds library/parameters to list of libraries to be loaded
    void addLib(const std::string& lib, ConstElementPtr params) {
        libraries_.push_back(make_pair(lib, params));
    }

    /// @brief Load all specified libraries.
    ///
    /// The libraries are stored in libraries_
    bool loadLibs() {
        return (HooksManager::loadLibraries(libraries_));
    }

    /// @brief Unloads all libraries.
    void unloadLibs() {
        EXPECT_NO_THROW(HooksManager::unloadLibraries());
    }

    /// @brief Return HA configuration with three servers in JSON format.
    ConstElementPtr createValidJsonConfiguration() const;

    HookLibsCollection libraries_;
};

ConstElementPtr
LibLoadTest::createValidJsonConfiguration() const {
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

    return (Element::fromJSON(config_text));
}

// Simple test that checks the library can be loaded in a DHCPv4 server.
TEST_F(LibLoadTest, validLoadDhcp4) {
    // Prepare parameters,
    ElementPtr params = Element::createMap();
    params->set("high-availability", createValidJsonConfiguration());

    // Set family and proc name.
    CfgMgr::instance().setFamily(AF_INET);
    Daemon::setProcName("kea-dhcp4");

    addLib(LIBDHCP_HA_SO, params);
    EXPECT_TRUE(loadLibs());
}

// Simple test that checks the library can be loaded in a DHCPv6 server.
TEST_F(LibLoadTest, validLoadDhcp6) {
    // Prepare parameters,
    ElementPtr params = Element::createMap();
    params->set("high-availability", createValidJsonConfiguration());

    // Set family and proc name.
    CfgMgr::instance().setFamily(AF_INET6);
    Daemon::setProcName("kea-dhcp6");

    addLib(LIBDHCP_HA_SO, params);
    EXPECT_TRUE(loadLibs());
}

// Simple test that checks the library can be loaded in a DHCPv4 server
// only if it is set for IPv4.
TEST_F(LibLoadTest, invalidLoadDhcp4) {
    // Prepare parameters,
    ElementPtr params = Element::createMap();
    params->set("high-availability", createValidJsonConfiguration());

    // Set family and proc name.
    CfgMgr::instance().setFamily(AF_INET);
    Daemon::setProcName("kea-dhcp6");

    addLib(LIBDHCP_HA_SO, params);

    // The process name must be kea-dhcp4 so load shall fail.
    EXPECT_FALSE(loadLibs());
}

// Simple test that checks the library can be loaded in a DHCPv6 server
// only if it is set for IPv6.
TEST_F(LibLoadTest, invalidLoadDhcp6) {
    // Prepare parameters,
    ElementPtr params = Element::createMap();
    params->set("high-availability", createValidJsonConfiguration());

    // Set family and proc name.
    CfgMgr::instance().setFamily(AF_INET6);
    Daemon::setProcName("kea-dhcp4");

    addLib(LIBDHCP_HA_SO, params);

    // The process name must be kea-dhcp6 so load shall fail.
    EXPECT_FALSE(loadLibs());
}

// Simple test that checks the library can be loaded and unloaded several times
// in a DHCPv4 server.
TEST_F(LibLoadTest, validLoadsDhcp4) {

    // Prepare parameters,
    ElementPtr params = Element::createMap();
    params->set("high-availability", createValidJsonConfiguration());

    // Set family and proc name.
    CfgMgr::instance().setFamily(AF_INET);
    Daemon::setProcName("kea-dhcp4");

    addLib(LIBDHCP_HA_SO, params);

    EXPECT_TRUE(loadLibs());
    unloadLibs();

    EXPECT_TRUE(loadLibs());
    unloadLibs();
}

// Simple test that checks the library can be loaded and unloaded several times
// in a DHCPv6 server.
TEST_F(LibLoadTest, validLoadsDhcp6) {

    // Prepare parameters,
    ElementPtr params = Element::createMap();
    params->set("high-availability", createValidJsonConfiguration());

    // Set family and proc name.
    CfgMgr::instance().setFamily(AF_INET6);
    Daemon::setProcName("kea-dhcp6");

    addLib(LIBDHCP_HA_SO, params);

    EXPECT_TRUE(loadLibs());
    unloadLibs();

    EXPECT_TRUE(loadLibs());
    unloadLibs();
}

} // end of anonymous namespace
