// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
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

/// @brief Test fixture for testing loading and unloading the MySQL lb library
class MySqlLbLibLoadTest : public isc::test::LibLoadTest {
public:
    /// @brief Constructor
    MySqlLbLibLoadTest() : LibLoadTest(LIBDHCP_MYSQL_LB_SO) {
    }

    /// @brief Destructor
    virtual ~MySqlLbLibLoadTest() {
        unloadLibraries();
    }
};

// Simple V4 test that checks the library can be loaded and unloaded several times.
TEST_F(MySqlLbLibLoadTest, validLoad4) {
    validDaemonTest("kea-dhcp4");
}

// Simple V6 test that checks the library can be loaded and unloaded several times.
TEST_F(MySqlLbLibLoadTest, validLoad6) {
    validDaemonTest("kea-dhcp6", AF_INET6);
}

// Simple test that checks the library cannot by loaded by invalid daemons.
TEST_F(MySqlLbLibLoadTest, invalidDaemonLoad) {
    invalidDaemonTest("kea-ctrl-agent");
    invalidDaemonTest("kea-dhcp-ddns");
    invalidDaemonTest("bogus");
}

} // end of anonymous namespace
