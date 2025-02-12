// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the Radius hooks library. In order to test the load
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
using namespace hooks;
using namespace isc::data;

namespace {

/// @brief Test fixture for testing loading and unloading the
/// radius library
class RadiusLibLoadTest : public isc::test::LibLoadTest {
public:
    /// @brief Constructor
    RadiusLibLoadTest() : LibLoadTest(LIB_SO) {
    }

    /// @brief Destructor
    /// Removes files that may be left over from previous tests
    virtual ~RadiusLibLoadTest() {
    }
};

// Simple test that checks the library can be loaded and unloaded several times.
TEST_F(RadiusLibLoadTest, validLoad) {
    ElementPtr params = Element::createMap();
    params->set("dictionary", Element::create(TEST_DICTIONARY));
    validDaemonTest("kea-dhcp4", AF_INET, params);
    validDaemonTest("kea-dhcp6", AF_INET6, params);
}

// Simple test that checks the library cannot by loaded by invalid daemons.
TEST_F(RadiusLibLoadTest, invalidDaemonLoad) {
    // V4 is invalid when family is AF_INET6
    invalidDaemonTest("kea-dhcp4", AF_INET6);

    // V6 is invalid when family is AF_INET
    invalidDaemonTest("kea-dhcp6", AF_INET);

    invalidDaemonTest("kea-ctrl-agent", AF_INET);
    invalidDaemonTest("kea-dhcp-ddns", AF_INET);
    invalidDaemonTest("bogus", AF_INET);
}

// Simple test that checks the library does not accept unknown parameters.
TEST_F(RadiusLibLoadTest, unknown) {
    // Prepare parameters for the callout parameters library.
    ElementPtr params = Element::createMap();
    params->set("foobar", Element::create(1));
    invalidDaemonTest("kea-dhcp4", AF_INET, params);
}

} // end of anonymous namespace
