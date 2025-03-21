// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
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
#include <config/command_mgr.h>
#include <dhcpsrv/testutils/lib_load_test_fixture.h>
#include <hooks/hooks_manager.h>

#include <gtest/gtest.h>
#include <errno.h>

using namespace std;
using namespace isc;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::process;

namespace {

/// @brief Test fixture for testing loading and unloading the Lease Query library
class LeaseQueryLibLoadTest : public isc::test::LibLoadTest {
public:
    /// @brief Constructor
    LeaseQueryLibLoadTest() : LibLoadTest(LIBDHCP_LEASE_QUERY_SO) {
    }

    /// @brief Destructor
    /// Removes files that may be left over from previous tests
    virtual ~LeaseQueryLibLoadTest() {
    }

    /// @brief Return basic, valid v4 Lease Query configuration in JSON format.
    ElementPtr validConfigParams4() const {
        std::string config_text = "{ \"requesters\":[ \"192.0.2.1\" ] }";
        return (Element::fromJSON(config_text));
    }

    /// @brief Return basic, valid v6 Lease Query configuration in JSON format.
    ElementPtr validConfigParams6() const {
        std::string config_text = "{ \"requesters\":[ \"2001:db8:1::\" ] }";
        return (Element::fromJSON(config_text));
    }

    /// @brief Check if a command is registered.
    ///
    /// @param name name of the command to be checked
    /// @return true if the command handler has been registered, false otherwise
    bool checkCommandRegistered(const std::string& name) {
        // First get the list of registered commands.
        ConstElementPtr lst =
            Element::fromJSON("{ \"command\": \"list-commands\" }");
        ConstElementPtr rsp = CommandMgr::instance().processCommand(lst);
        if (!rsp) {
            ADD_FAILURE() << "failed to process 'list-commands'";
            return (false);
        }

        ConstElementPtr args = rsp->get("arguments");
        if (!args) {
            ADD_FAILURE() << "response to list-commands does not"
                " contain any arguments";
        }
        std::string args_txt = args->str();
        return (args_txt.find(name) != std::string::npos);
    }
};

// Simple test that checks the library can be loaded in a DHCPv4 server.
TEST_F(LeaseQueryLibLoadTest, validLoadDhcp4) {
    validDaemonTest("kea-dhcp4", AF_INET, validConfigParams4());
}

// Simple test that checks the library can be loaded in a DHCPv6 server.
TEST_F(LeaseQueryLibLoadTest, validLoadDhcp6) {
    validDaemonTest("kea-dhcp6", AF_INET6, validConfigParams6());
}

// Simple test that checks the library cannot by loaded by invalid daemons.
TEST_F(LeaseQueryLibLoadTest, invalidDaemonLoad) {
    // V4 is invalid when family is AF_INET6.
    invalidDaemonTest("kea-dhcp4", AF_INET6, validConfigParams4());
    invalidDaemonTest("kea-dhcp4", AF_INET6, validConfigParams6());
    invalidDaemonTest("kea-dhcp6", AF_INET6, validConfigParams4());

    // V6 is invalid when family is AF_INET.
    invalidDaemonTest("kea-dhcp6", AF_INET, validConfigParams4());
    invalidDaemonTest("kea-dhcp6", AF_INET, validConfigParams6());
    invalidDaemonTest("kea-dhcp4", AF_INET, validConfigParams6());

    invalidDaemonTest("kea-ctrl-agent", AF_INET, validConfigParams4());
    invalidDaemonTest("kea-ctrl-agent", AF_INET6, validConfigParams6());
    invalidDaemonTest("kea-dhcp-ddns", AF_INET, validConfigParams4());
    invalidDaemonTest("kea-dhcp-ddns", AF_INET6, validConfigParams6());
    invalidDaemonTest("bogus", AF_INET, validConfigParams4());
    invalidDaemonTest("bogus", AF_INET6, validConfigParams6());
}

// Verifies that an unknown parameter in an otherwise valid v4
// configuration is detected.
TEST_F(LeaseQueryLibLoadTest, unknownParameterLoadDhcp4) {
    /// Add unknown element "foo" to valid v4 config.
    ElementPtr params = validConfigParams4();
    params->set("foo", Element::create("bar"));

    // The load should fail.
    invalidDaemonTest("kea-dhcp4", AF_INET, params);
}

// Verifies that an unknown parameter in an otherwise valid v6
// configuration is detected.
TEST_F(LeaseQueryLibLoadTest, unknownParameterLoadDhcp6) {
    /// Add unknown element "foo" to valid v6 config.
    ElementPtr params = validConfigParams6();
    params->set("foo", Element::create("bar"));

    // The load should fail.
    invalidDaemonTest("kea-dhcp6", AF_INET6, params);
}

// Verifies that the extended-info4-upgrade command is registered in v4.
TEST_F(LeaseQueryLibLoadTest, commands4) {
    // Set family and daemon's proc name.
    CfgMgr::instance().setFamily(AF_INET);
    Daemon::setProcName("kea-dhcp4");

    // Before loading the hook no commands are known.
    ASSERT_FALSE(checkCommandRegistered("extended-info4-upgrade"));
    ASSERT_FALSE(checkCommandRegistered("extended-info6-upgrade"));

    // Load the library.
    clearLibraries();
    ASSERT_NO_THROW(addLibrary(lib_so_name_, validConfigParams4()));
    ASSERT_NO_THROW(loadLibraries());

    // The v4 command was registered during the load() call.
    EXPECT_TRUE(checkCommandRegistered("extended-info4-upgrade"));
    EXPECT_FALSE(checkCommandRegistered("extended-info6-upgrade"));

    // Unload the library.
    ASSERT_NO_THROW(unloadLibraries());
    EXPECT_FALSE(checkCommandRegistered("extended-info4-upgrade"));
    EXPECT_FALSE(checkCommandRegistered("extended-info6-upgrade"));
}

// Verifies that a few commands are registered in v6.
TEST_F(LeaseQueryLibLoadTest, commands6) {
    // Set family and daemon's proc name.
    CfgMgr::instance().setFamily(AF_INET6);
    Daemon::setProcName("kea-dhcp6");

    // Before loading the hook no commands are known.
    ASSERT_FALSE(checkCommandRegistered("extended-info4-upgrade"));
    ASSERT_FALSE(checkCommandRegistered("extended-info6-upgrade"));

    // Load the library.
    clearLibraries();
    ASSERT_NO_THROW(addLibrary(lib_so_name_, validConfigParams6()));
    ASSERT_NO_THROW(loadLibraries());

    // The v6 command was registered during the load() call.
    EXPECT_FALSE(checkCommandRegistered("extended-info4-upgrade"));
    EXPECT_TRUE(checkCommandRegistered("extended-info6-upgrade"));

    // Unload the library.
    ASSERT_NO_THROW(unloadLibraries());
    EXPECT_FALSE(checkCommandRegistered("extended-info4-upgrade"));
    EXPECT_FALSE(checkCommandRegistered("extended-info6-upgrade"));
}

} // end of anonymous namespace
