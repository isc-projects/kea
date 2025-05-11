// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the flexible identifier hook library. In order to test the load
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
using namespace isc::dhcp;
using namespace isc::process;

namespace {

/// @brief Test fixture for testing loading and unloading the flex-id library
class FlexIdLibLoadTest : public ::test::LibLoadTest {
public:
    /// @brief Constructor
    FlexIdLibLoadTest() : LibLoadTest(LIB_SO) {
    }

    /// @brief Destructor
    /// Removes files that may be left over from previous tests
    virtual ~FlexIdLibLoadTest() {
    }

    /// @brief Creates valid configuration.
    virtual ElementPtr validConfigParams() {
        ElementPtr params = data::Element::createMap();
        params->set("identifier-expression", Element::create("option[100].hex"));
        params->set("replace-client-id", Element::create(true));
        return (params);
    }
};

// Simple test that checks the library can be loaded and unloaded several times.
TEST_F(FlexIdLibLoadTest, validLoad) {
    validDaemonTest("kea-dhcp4", AF_INET, valid_params_);
    validDaemonTest("kea-dhcp6", AF_INET6, valid_params_);
}

// Simple test that checks the library cannot by loaded by invalid daemons.
TEST_F(FlexIdLibLoadTest, invalidDaemonLoad) {
    // V4 is invalid when family is AF_INET6.
    invalidDaemonTest("kea-dhcp4", AF_INET6, valid_params_);

    // V6 is invalid when family is AF_INET.
    invalidDaemonTest("kea-dhcp6", AF_INET, valid_params_);

    invalidDaemonTest("kea-ctrl-agent", AF_INET, valid_params_);
    invalidDaemonTest("kea-dhcp-ddns", AF_INET, valid_params_);
    invalidDaemonTest("bogus", AF_INET, valid_params_);
}

// Simple test that checks the library fails to load on bad expressions.
TEST_F(FlexIdLibLoadTest, badExpression) {
    // Prepare parameters for the callout parameters library.
    ElementPtr params = Element::createMap();
    params->set("replace-client-id", Element::create(true));
    invalidDaemonTest("kea-dhcp4", AF_INET, params);

    // Empty expression.
    params->set("identifier-expression", Element::create(string("")));
    // Warning (vs error)
    validDaemonTest("kea-dhcp4", AF_INET, params);

    // Bad expression.
    params->set("identifier-expression", Element::create("foobar"));
    invalidDaemonTest("kea-dhcp4", AF_INET, params);

    // Not a string expression.
    params->set("identifier-expression", Element::create("'foo' = 'bar'"));
    invalidDaemonTest("kea-dhcp4", AF_INET, params);

    // IPv6 expression in IPv4 context.
    params->set("identifier-expression", Element::create("relay6[0].linkaddr"));
    invalidDaemonTest("kea-dhcp4", AF_INET, params);

    // IPv4 expression in IPv6 context.
    params->set("identifier-expression", Element::create("pkt4.yiaddr"));
    invalidDaemonTest("kea-dhcp6", AF_INET6, params);
}

// Simple test that checks the library fails to load on bad ignore-iaid.
TEST_F(FlexIdLibLoadTest, badIgnoreIAID) {
    // Prepare parameters for the callout parameters library.
    // Needs to include identifier-expression or load fails because it's required.
    ElementPtr params = Element::createMap();
    params->set("identifier-expression", Element::create("'somestring'"));

    // Bad expression ignored in v4.
    params->set("ignore-iaid", Element::create("foobar"));
    validDaemonTest("kea-dhcp4", AF_INET, params);

    // Bad expression is not ignored in v6.
    invalidDaemonTest("kea-dhcp6", AF_INET6, params);

    // IPv6 ignore-iaid in IPv6 context.
    params->set("ignore-iaid", Element::create(true));
    validDaemonTest("kea-dhcp6", AF_INET6, params);
}

} // end of anonymous namespace
