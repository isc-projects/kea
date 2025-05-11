// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the Host Cache hooks library. In order to test the load
/// function, one must be able to pass it hook library parameters. The
/// the only way to populate these parameters is by actually loading the
/// library via HooksManager::loadLibraries().

#include <config.h>

#include <config/command_mgr.h>
#include <dhcpsrv/testutils/lib_load_test_fixture.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>
#include <errno.h>

using namespace std;
using namespace isc;
using namespace hooks;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::process;

namespace {

/// @brief Test fixture for testing loading and unloading the
/// host-cache library
class HostCacheLibLoadTest : public isc::test::LibLoadTest {
public:
    /// @brief Constructor
    HostCacheLibLoadTest() : LibLoadTest(LIB_SO) {
    }

    /// @brief Destructor
    virtual ~HostCacheLibLoadTest() {
    }
};

// Simple test that checks the library can be loaded and unloaded several times.
TEST_F(HostCacheLibLoadTest, validLoad) {
    validDaemonTest("kea-dhcp4", AF_INET);
    validDaemonTest("kea-dhcp6", AF_INET6);
}

// Simple test that checks the library cannot by loaded by invalid daemons.
TEST_F(HostCacheLibLoadTest, invalidDaemonLoad) {
    // V4 is invalid when family is AF_INET6
    invalidDaemonTest("kea-dhcp4", AF_INET6, valid_params_);

    // V6 is invalid when family is AF_INET
    invalidDaemonTest("kea-dhcp6", AF_INET, valid_params_);

    invalidDaemonTest("kea-ctrl-agent", AF_INET, valid_params_);
    invalidDaemonTest("kea-dhcp-ddns", AF_INET, valid_params_);
    invalidDaemonTest("bogus", AF_INET, valid_params_);
}

// Check that expected commands are registered (v4).
TEST_F(HostCacheLibLoadTest, commands4) {
    CfgMgr::instance().setFamily(AF_INET);
    Daemon::setProcName("kea-dhcp4");
    addLibrary(LIB_SO, ConstElementPtr());
    EXPECT_TRUE(loadLibraries());

    // Prepare and send a list-commands to get the list of registered commands.
    ConstElementPtr cmd =
        Element::fromJSON("{ \"command\": \"list-commands\" }");
    ConstElementPtr rsp = CommandMgr::instance().processCommand(cmd);
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    string args_txt = args->str();
    EXPECT_NE(string::npos, args_txt.find("cache-size"));
    EXPECT_NE(string::npos, args_txt.find("cache-clear"));
    EXPECT_NE(string::npos, args_txt.find("cache-flush"));
    EXPECT_NE(string::npos, args_txt.find("cache-get"));
    EXPECT_NE(string::npos, args_txt.find("cache-get-by-id"));
    EXPECT_NE(string::npos, args_txt.find("cache-write"));
    EXPECT_NE(string::npos, args_txt.find("cache-insert"));
    EXPECT_NE(string::npos, args_txt.find("cache-load"));
    EXPECT_NE(string::npos, args_txt.find("cache-remove"));
}

// Check that expected commands are registered (v6).
TEST_F(HostCacheLibLoadTest, commands6) {
    CfgMgr::instance().setFamily(AF_INET6);
    Daemon::setProcName("kea-dhcp6");
    addLibrary(LIB_SO, ConstElementPtr());
    EXPECT_TRUE(loadLibraries());

    // Prepare and send a list-commands to get the list of registered commands.
    ConstElementPtr cmd =
        Element::fromJSON("{ \"command\": \"list-commands\" }");
    ConstElementPtr rsp = CommandMgr::instance().processCommand(cmd);
    ASSERT_TRUE(rsp);
    ConstElementPtr args = rsp->get("arguments");
    ASSERT_TRUE(args);
    string args_txt = args->str();
    EXPECT_NE(string::npos, args_txt.find("cache-size"));
    EXPECT_NE(string::npos, args_txt.find("cache-clear"));
    EXPECT_NE(string::npos, args_txt.find("cache-flush"));
    EXPECT_NE(string::npos, args_txt.find("cache-get"));
    EXPECT_NE(string::npos, args_txt.find("cache-get-by-id"));
    EXPECT_NE(string::npos, args_txt.find("cache-write"));
    EXPECT_NE(string::npos, args_txt.find("cache-insert"));
    EXPECT_NE(string::npos, args_txt.find("cache-load"));
    EXPECT_NE(string::npos, args_txt.find("cache-remove"));
}

} // end of anonymous namespace
