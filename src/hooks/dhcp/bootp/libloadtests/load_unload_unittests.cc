// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
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

#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <hooks/hooks_manager.h>
#include <process/daemon.h>
#include <testutils/gtest_utils.h>
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

/// @brief Test fixture for testing loading and unloading the bootp library
class BootpLibLoadTest : public isc::test::LibLoadTest {
public:
    /// @brief Constructor
    BootpLibLoadTest() : LibLoadTest(LIBDHCP_BOOTP_SO) {
    }

    /// @brief Destructor
    virtual ~BootpLibLoadTest() {
        unloadLibraries();
    }
};

// Simple V4 test that checks the library can be loaded and unloaded several times.
TEST_F(BootpLibLoadTest, validLoad4) {
    validDaemonTest("kea-dhcp4");
}

// Simple V6 test that checks the library cannot by loaded by invalid daemons.
TEST_F(BootpLibLoadTest, invalidDaemonLoad) {
    invalidDaemonTest("kea-dhcp6", AF_INET6);
    invalidDaemonTest("kea-ctrl-agent");
    invalidDaemonTest("kea-dhcp-ddns");
    invalidDaemonTest("bogus");
}

} // end of anonymous namespace
