// Copyright (C) 2019-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the flexible option hook library. In order to test the load
/// function, one must be able to pass it hook library parameters. The
/// the only way to populate these parameters is by actually loading the
/// library via HooksManager::loadLibraries().

#include <config.h>

#include <flex_option.h>
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

/// @brief Test fixture for testing loading and unloading the flex-option library
class FlexOptionLibLoadTest : public isc::test::LibLoadTest {
public:
    /// @brief Constructor
    FlexOptionLibLoadTest() : LibLoadTest(FLEX_OPTION_LIB_SO) {
    }

    /// @brief Destructor
    virtual ~FlexOptionLibLoadTest() {
    }

    /// @brief Creates a set configuration parameters valid for the library.
    virtual ElementPtr validConfigParams() {
        ElementPtr params = Element::createMap();
        ElementPtr options = Element::createList();
        params->set("options", options);
        return (params);
    }
};

// Simple V4 test that checks the library can be loaded and unloaded several times.
TEST_F(FlexOptionLibLoadTest, validLoadDhcp4) {
    validDaemonTest("kea-dhcp4", AF_INET, valid_params_);
}

// Simple test that checks the library can be loaded in a DHCPv6 server.
TEST_F(FlexOptionLibLoadTest, validLoadDhcp6) {
    validDaemonTest("kea-dhcp6", AF_INET6, valid_params_);
}

// Simple test that checks the library cannot by loaded by invalid daemons.
TEST_F(FlexOptionLibLoadTest, invalidDaemonLoad) {
    // V4 is invalid when family is AF_INET6
    invalidDaemonTest("kea-dhcp4", AF_INET6, valid_params_);

    // V6 is invalid when family is AF_INET
    invalidDaemonTest("kea-dhcp6", AF_INET, valid_params_);

    invalidDaemonTest("kea-ctrl-agent", AF_INET, valid_params_);
    invalidDaemonTest("kea-dhcp-ddns", AF_INET, valid_params_);
    invalidDaemonTest("bogus", AF_INET, valid_params_);
}

} // end of anonymous namespace
