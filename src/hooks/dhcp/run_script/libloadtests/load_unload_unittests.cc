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

#include <cc/data.h>
#include <dhcpsrv/cfgmgr.h>
#include <hooks/hooks_manager.h>
#include <process/daemon.h>
#include <testutils/lib_load_test_fixture.h>

#include <gtest/gtest.h>
#include <errno.h>

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::process;
using namespace std;

namespace {

/// @brief Test fixture for testing loading and unloading the RunScript library.
class RunScriptLibLoadTest : public isc::test::LibLoadTest {
public:
    /// @brief Constructor
    RunScriptLibLoadTest() : LibLoadTest(LIBRUN_SCRIPT_SO) {
    }

    /// @brief Destructor
    virtual ~RunScriptLibLoadTest() {
    }

    /// @brief Creates a set configuration parameters valid for the library.
    virtual ElementPtr validConfigParams() {
        ElementPtr params = Element::createMap();
        ElementPtr name = Element::create(RUN_SCRIPT_TEST_SH);
        params->set("name", name);
        ElementPtr sync = Element::create(false);
        params->set("sync", sync);
        return (params);
    }
};

// Simple V4 test that checks the library can be loaded and unloaded several times.
TEST_F(RunScriptLibLoadTest, validLoadDhcp4) {
    validDaemonTest("kea-dhcp4", AF_INET, valid_params_);
}

// Simple test that checks the library can be loaded in a DHCPv6 server.
TEST_F(RunScriptLibLoadTest, validLoadDhcp6) {
    validDaemonTest("kea-dhcp6", AF_INET6, valid_params_);
}

// Simple test that checks the library cannot by loaded by invalid daemons.
TEST_F(RunScriptLibLoadTest, invalidDaemonLoad) {
    // V4 is invalid when family is AF_INET6
    invalidDaemonTest("kea-dhcp4", AF_INET6, valid_params_);

    // V6 is invalid when family is AF_INET
    invalidDaemonTest("kea-dhcp6", AF_INET, valid_params_);

    invalidDaemonTest("kea-ctrl-agent", AF_INET, valid_params_);
    invalidDaemonTest("kea-dhcp-ddns", AF_INET, valid_params_);
    invalidDaemonTest("bogus", AF_INET, valid_params_);
}

// Simple test that checks the library can not be loaded if using wrong
// parameters.
TEST_F(RunScriptLibLoadTest, invalidParametersLoad) {
    // The name parameter should be mandatory.
    ElementPtr params = Element::createMap();
    invalidDaemonTest("kea-dhcp4", AF_INET, params);

    // Use invalid name parameter type.
    ElementPtr name = Element::create(false);
    params->set("name", name);
    invalidDaemonTest("kea-dhcp4", AF_INET, params);

    // Use invalid name parameter.
    name = Element::create("script_name.sh");
    params->set("name", name);
    invalidDaemonTest("kea-dhcp4", AF_INET, params);

    // Use valid name parameter type but use invalid sync parameter type.
    name = Element::create(RUN_SCRIPT_TEST_SH);
    params->set("name", name);
    ElementPtr sync = Element::create("data");
    params->set("sync", sync);
    invalidDaemonTest("kea-dhcp4", AF_INET, params);
}

} // end of anonymous namespace
