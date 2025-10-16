// Copyright (C) 2019-2025 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_service_mgr.h>
#include <dhcp/pkt4.h>
#include <hooks/hooks.h>
#include <hooks/hooks_manager.h>
#include <hooks/callout_manager.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/network_state.h>
#include <process/daemon.h>
#include <testutils/log_utils.h>

#include <gtest/gtest.h>
#include <errno.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::hooks;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::process;

namespace {

/// @brief Structure that holds registered hook indexes.
struct TestHooks {
    /// @brief Index of lease4_offer callout.
    int hook_index_lease4_offer_;

    /// @brief Constructor
    ///
    /// The constructor registers hook points for callout tests.
    TestHooks() {
        hook_index_lease4_offer_ = HooksManager::registerHook("lease4_offer");
    }
};

TestHooks testHooks;

/// @brief Test fixture for testing callouts called by the flex-option library
class CalloutTest : public LogContentTest {
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
        libraries_.push_back(HookLibInfo(lib, params));
    }

    void loadLibs() {
        EXPECT_TRUE(HooksManager::loadLibraries(libraries_));
    }

    void unloadLibs() {
        EXPECT_NO_THROW(HooksManager::unloadLibraries());
    }

    HookLibsCollection libraries_;
};

// Simple test which exercises the lease4_offer callout when lease is reused.
TEST_F(CalloutTest, lease4Offer) {
    // Set family and proc name.
    CfgMgr::instance().setFamily(AF_INET);
    Daemon::setProcName("kea-dhcp4");

    ElementPtr params = Element::createMap();
    params->set("min-ping-requests", Element::create(3));
    params->set("reply-timeout", Element::create(100));
    params->set("enable-ping-check", Element::create(true));
    params->set("ping-cltt-secs", Element::create(60));
    params->set("ping-channel-threads", Element::create(1));

    // Load the library.
    addLib(PING_CHECK_LIB_SO, params);
    loadLibs();

    // Prepare packets.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Lease4CollectionPtr leases4(new Lease4Collection());
    uint32_t offer_lifetime = 3600;
    Lease4Ptr old_lease;
    ConstHostPtr host;

    // Get and setup the callout handle.
    EXPECT_TRUE(HooksManager::calloutsPresent(testHooks.hook_index_lease4_offer_));
    CalloutHandlePtr handle = HooksManager::createCalloutHandle();

    handle->setArgument("query4", query);
    handle->setArgument("leases4", leases4);
    handle->setArgument("offer_lifetime", offer_lifetime);
    handle->setArgument("old_lease", old_lease);
    handle->setArgument("host", host);

    // Execute the callout.
    EXPECT_NO_THROW(HooksManager::callCallouts(testHooks.hook_index_lease4_offer_,
                                               *handle));
    EXPECT_EQ(CalloutHandle::CalloutNextStep::NEXT_STEP_CONTINUE, handle->getStatus());

    EXPECT_EQ(1, countFile("PING_CHECK_NO_LEASE_OR_LEASE_REUSED Ping check skipped: no lease"));
}

} // end of anonymous namespace
