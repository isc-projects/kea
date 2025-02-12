// Copyright (C) 2022-2024 Internet Systems Consortium, Inc. ("ISC")
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
class DdnsTuningLibLoadTest : public isc::test::LibLoadTest {
public:
    /// @brief Constructor
    DdnsTuningLibLoadTest() : LibLoadTest(DDNS_TUNING_LIB_SO) {
    }

    /// @brief Destructor
    virtual ~DdnsTuningLibLoadTest() {
    }

    /// @brief Creates valid configuration.
    /// @todo Find an expression working on v6 too.
    virtual ElementPtr validConfigParams() {
        ElementPtr params = Element::createMap();
        params->set("hostname-expr",
                    Element::create("'just a string'"));
        return (params);
    }
};

// Simple V4 test that checks the library can be loaded and unloaded several times.
TEST_F(DdnsTuningLibLoadTest, validLoad4) {
    validDaemonTest("kea-dhcp4", AF_INET, valid_params_);
}

// Simple V6 test that checks the library can be loaded and unloaded several times.
TEST_F(DdnsTuningLibLoadTest, validLoad6) {
    validDaemonTest("kea-dhcp6", AF_INET6, valid_params_);
}

// Simple test that checks the library cannot by loaded by invalid daemons.
TEST_F(DdnsTuningLibLoadTest, invalidDaemonLoad) {
    // V4 is invalid when family is AF_INET6.
    invalidDaemonTest("kea-dhcp4", AF_INET6, valid_params_);

    // V6 is invalid when family is AF_INET.
    invalidDaemonTest("kea-dhcp6", AF_INET, valid_params_);

    invalidDaemonTest("kea-ctrl-agent", AF_INET, valid_params_);
    invalidDaemonTest("kea-dhcp-ddns", AF_INET, valid_params_);
    invalidDaemonTest("bogus", AF_INET, valid_params_);
}

} // end of anonymous namespace
