// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the pkt[46]_send callouis
/// called by the flexible option hook library. In order to test the callouts
/// one must be able to pass to the load function it hook library parameters
/// because the only way to populate these parameters is by actually loading
/// the library via HooksManager::loadLibraries().

#include <config.h>

#include <flex_option.h>
#include <hooks/hooks.h>
#include <hooks/hooks_manager.h>
#include <hooks/callout_manager.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/cfgmgr.h>

#include <gtest/gtest.h>
#include <errno.h>

using namespace std;
using namespace isc;
using namespace isc::hooks;
using namespace isc::data;
using namespace isc::dhcp;

namespace {

/// @brief Structure that holds registered hook indexes.
struct TestHooks {
    /// @brief Index of pkt4_send callout.
    int hook_index_pkt4_send_;

    /// @brief Index of pkt6_send callout.
    int hook_index_pkt6_send_;

    /// @brief Constructor
    ///
    /// The constructor registers hook points for callout tests.
    TestHooks() {
        hook_index_pkt4_send_ = HooksManager::registerHook("pkt4_send");
        hook_index_pkt6_send_ = HooksManager::registerHook("pkt6_send");
    }
};

TestHooks testHooks;

/// @brief Test fixture for testing callouts called by the flex-option library
class CalloutTest : public ::testing::Test {
public:
    /// @brief Constructor
    CalloutTest() {
        reset();
    }

    /// @brief Destructor
    /// Removes files that may be left over from previous tests
    virtual ~CalloutTest() {
        reset();
    }

    /// @brief Removes files that may be left over from previous tests
    virtual void reset() {
        HooksManager::unloadLibraries();
    }

    void addLib(const std::string& lib, ConstElementPtr params) {
        libraries_.push_back(make_pair(lib, params));
    }

    void loadLibs() {
        EXPECT_TRUE(HooksManager::loadLibraries(libraries_));
    }

    void unloadLibs() {
        EXPECT_NO_THROW(HooksManager::unloadLibraries());
    }

    HookLibsCollection libraries_;
};

// Simple test which exercises the pkt4_send callout.
TEST_F(CalloutTest, pkt4Send) {
    // Prepare load() parameters.
    ElementPtr params = Element::createMap();
    ElementPtr options = Element::createList();
    params->set("options", options);
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(DHO_HOST_NAME);
    option->set("code", code);
    ElementPtr add = Element::create(string("'abc'"));
    option->set("add", add);

    // Load the library.
    addLib(FLEX_OPTION_LIB_SO, params);
    loadLibs();

    // Prepare packets.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Pkt4Ptr response(new Pkt4(DHCPOFFER, 12345));
    EXPECT_FALSE(response->getOption(DHO_HOST_NAME));

    // Get and setup the callout handle.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_pkt4_send_));
    CalloutHandlePtr handle = HooksManager::createCalloutHandle();
    handle->setArgument("query4", query);
    handle->setArgument("response4", response);

    // Execute the callout.
    EXPECT_NO_THROW(HooksManager::callCallouts(testHooks.hook_index_pkt4_send_,
                                               *handle));
    EXPECT_EQ(0, handle->getStatus());

    // Check the result.
    OptionPtr opt = response->getOption(DHO_HOST_NAME);
    ASSERT_TRUE(opt);
    EXPECT_EQ(DHO_HOST_NAME, opt->getType());
    const OptionBuffer& buffer = opt->getData();
    ASSERT_EQ(3, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "abc", 3));
}

// Simple test which exercises the pkt6_send callout.
TEST_F(CalloutTest, pkt6Send) {
    // Move to DHCPv6.
    CfgMgr::instance().setFamily(AF_INET6);

    // Prepare load() parameters.
    ElementPtr params = Element::createMap();
    ElementPtr options = Element::createList();
    params->set("options", options);
    ElementPtr option = Element::createMap();
    options->add(option);
    ElementPtr code = Element::create(D6O_BOOTFILE_URL);
    option->set("code", code);
    ElementPtr supersede = Element::create(string("'abc'"));
    option->set("supersede", supersede);

    // Load the library.
    addLib(FLEX_OPTION_LIB_SO, params);
    loadLibs();

    // Prepare packets.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 12345));
    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 12345));
    EXPECT_FALSE(response->getOption(D6O_BOOTFILE_URL));

    // Get and setup the callout handle.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_pkt6_send_));
    CalloutHandlePtr handle = HooksManager::createCalloutHandle();
    handle->setArgument("query6", query);
    handle->setArgument("response6", response);

    // Execute the callout.
    EXPECT_NO_THROW(HooksManager::callCallouts(testHooks.hook_index_pkt6_send_,
                                               *handle));
    EXPECT_EQ(0, handle->getStatus());

    // Check the result.
    OptionPtr opt = response->getOption(D6O_BOOTFILE_URL);
    ASSERT_TRUE(opt);
    EXPECT_EQ(D6O_BOOTFILE_URL, opt->getType());
    const OptionBuffer& buffer = opt->getData();
    ASSERT_EQ(3, buffer.size());
    EXPECT_EQ(0, memcmp(&buffer[0], "abc", 3));
}

} // end of anonymous namespace
