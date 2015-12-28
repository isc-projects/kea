// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/tests/alloc_engine_utils.h>
#include <dhcpsrv/tests/test_utils.h>

#include <hooks/server_hooks.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks_manager.h>

using namespace std;
using namespace isc::hooks;
using namespace isc::asiolink;

namespace isc {
namespace dhcp {
namespace test {

/// @brief helper class used in Hooks testing in AllocEngine6
///
/// It features a couple of callout functions and buffers to store
/// the data that is accessible via callouts.
class HookAllocEngine6Test : public AllocEngine6Test {
public:
    HookAllocEngine6Test() {
        resetCalloutBuffers();
    }

    virtual ~HookAllocEngine6Test() {
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts(
            "lease6_select");
    }

    /// @brief clears out buffers, so callouts can store received arguments
    void resetCalloutBuffers() {
        callback_name_ = string("");
        callback_subnet6_.reset();
        callback_fake_allocation_ = false;
        callback_lease6_.reset();
        callback_argument_names_.clear();
        callback_addr_original_ = IOAddress("::");
        callback_addr_updated_ = IOAddress("::");
    }

    /// callback that stores received callout name and received values
    static int
    lease6_select_callout(CalloutHandle& callout_handle) {

        callback_name_ = string("lease6_select");

        callout_handle.getArgument("subnet6", callback_subnet6_);
        callout_handle.getArgument("fake_allocation", callback_fake_allocation_);
        callout_handle.getArgument("lease6", callback_lease6_);

        callback_addr_original_ = callback_lease6_->addr_;

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// callback that overrides the lease with different values
    static int
    lease6_select_different_callout(CalloutHandle& callout_handle) {

        // Let's call the basic callout, so it can record all parameters
        lease6_select_callout(callout_handle);

        // Now we need to tweak the least a bit
        Lease6Ptr lease;
        callout_handle.getArgument("lease6", lease);
        callback_addr_updated_ = addr_override_;
        lease->addr_ = callback_addr_updated_;
        lease->t1_ = t1_override_;
        lease->t2_ = t2_override_;
        lease->preferred_lft_ = pref_override_;
        lease->valid_lft_ = valid_override_;

        return (0);
    }

    // Values to be used in callout to override lease6 content
    static const IOAddress addr_override_;
    static const uint32_t t1_override_;
    static const uint32_t t2_override_;
    static const uint32_t pref_override_;
    static const uint32_t valid_override_;

    // Callback will store original and overridden values here
    static IOAddress callback_addr_original_;
    static IOAddress callback_addr_updated_;

    // Buffers (callback will store received values here)
    static string callback_name_;
    static Subnet6Ptr callback_subnet6_;
    static Lease6Ptr callback_lease6_;
    static bool callback_fake_allocation_;
    static vector<string> callback_argument_names_;
};

// For some reason intialization within a class makes the linker confused.
// linker complains about undefined references if they are defined within
// the class declaration.
const IOAddress HookAllocEngine6Test::addr_override_("2001:db8::abcd");
const uint32_t HookAllocEngine6Test::t1_override_ = 6000;
const uint32_t HookAllocEngine6Test::t2_override_ = 7000;
const uint32_t HookAllocEngine6Test::pref_override_ = 8000;
const uint32_t HookAllocEngine6Test::valid_override_ = 9000;

IOAddress HookAllocEngine6Test::callback_addr_original_("::");
IOAddress HookAllocEngine6Test::callback_addr_updated_("::");

string HookAllocEngine6Test::callback_name_;
Subnet6Ptr HookAllocEngine6Test::callback_subnet6_;
Lease6Ptr HookAllocEngine6Test::callback_lease6_;
bool HookAllocEngine6Test::callback_fake_allocation_;
vector<string> HookAllocEngine6Test::callback_argument_names_;

// This test checks if the lease6_select callout is executed and expected
// parameters as passed.
TEST_F(HookAllocEngine6Test, lease6_select) {

    // Note: The following order is working as expected:
    // 1. create AllocEngine (that register hook points)
    // 2. call loadLibraries()
    //
    // This order, however, causes segfault in HooksManager
    // 1. call loadLibraries()
    // 2. create AllocEngine (that register hook points)

    // Create allocation engine (hook names are registered in its ctor)
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Initialize Hooks Manager
    vector<string> libraries; // no libraries at this time
    HooksManager::loadLibraries(libraries);

    // Install pkt6_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_select", lease6_select_callout));

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    Lease6Ptr lease;
    AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, IOAddress("::"),
                                    Lease::TYPE_NA, false, false, "", false);
    ctx.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));
    ctx.callout_handle_ = callout_handle;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Do all checks on the lease
    checkLease6(lease, Lease::TYPE_NA, 128);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Check that callouts were indeed called
    EXPECT_EQ("lease6_select", callback_name_);

    // Now check that the lease in LeaseMgr has the same parameters
    ASSERT_TRUE(callback_lease6_);
    detailCompareLease(callback_lease6_, from_mgr);

    ASSERT_TRUE(callback_subnet6_);
    EXPECT_EQ(subnet_->toText(), callback_subnet6_->toText());

    EXPECT_FALSE(callback_fake_allocation_);

    // Check if all expected parameters are reported. It's a bit tricky, because
    // order may be different. If the test starts failing, because someone tweaked
    // hooks engine, we'll have to implement proper vector matching (ignoring order)
    vector<string> expected_argument_names;
    expected_argument_names.push_back("fake_allocation");
    expected_argument_names.push_back("lease6");
    expected_argument_names.push_back("subnet6");

    sort(callback_argument_names_.begin(), callback_argument_names_.end());
    sort(expected_argument_names.begin(), expected_argument_names.end());

    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);
}

// This test checks if lease6_select callout is able to override the values
// in a lease6.
TEST_F(HookAllocEngine6Test, change_lease6_select) {

    // Make sure that the overridden values are different than the ones from
    // subnet originally used to create the lease
    ASSERT_NE(t1_override_, subnet_->getT1());
    ASSERT_NE(t2_override_, subnet_->getT2());
    ASSERT_NE(pref_override_, subnet_->getPreferred());
    ASSERT_NE(valid_override_, subnet_->getValid());
    ASSERT_FALSE(subnet_->inRange(addr_override_));

    // Create allocation engine (hook names are registered in its ctor)
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100)));
    ASSERT_TRUE(engine);

    // Initialize Hooks Manager
    vector<string> libraries; // no libraries at this time
    HooksManager::loadLibraries(libraries);

    // Install a callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease6_select", lease6_select_different_callout));

    // Normally, dhcpv6_srv would passed the handle when calling allocateLeases6,
    // but in tests we need to create it on our own.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    // Call allocateLeases6. Callouts should be triggered here.
    Lease6Ptr lease;
    AllocEngine::ClientContext6 ctx(subnet_, duid_, iaid_, IOAddress("::"),
                                    Lease::TYPE_NA, false, false, "", false);
    ctx.query_.reset(new Pkt6(DHCPV6_REQUEST, 1234));
    ctx.callout_handle_ = callout_handle;
    EXPECT_NO_THROW(lease = expectOneLease(engine->allocateLeases6(ctx)));
    // Check that we got a lease
    ASSERT_TRUE(lease);

    // See if the values overridden by callout are there
    EXPECT_TRUE(lease->addr_.equals(addr_override_));
    EXPECT_EQ(t1_override_, lease->t1_);
    EXPECT_EQ(t2_override_, lease->t2_);
    EXPECT_EQ(pref_override_, lease->preferred_lft_);
    EXPECT_EQ(valid_override_, lease->valid_lft_);

    // Now check if the lease is in the database
    Lease6Ptr from_mgr = LeaseMgrFactory::instance().getLease6(lease->type_,
                                                               lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Check if values in the database are overridden
    EXPECT_TRUE(from_mgr->addr_.equals(addr_override_));
    EXPECT_EQ(t1_override_, from_mgr->t1_);
    EXPECT_EQ(t2_override_, from_mgr->t2_);
    EXPECT_EQ(pref_override_, from_mgr->preferred_lft_);
    EXPECT_EQ(valid_override_, from_mgr->valid_lft_);
}


/// @brief helper class used in Hooks testing in AllocEngine4
///
/// It features a couple of callout functions and buffers to store
/// the data that is accessible via callouts.
///
/// Note: lease4_renew callout is tested from DHCPv4 server.
/// See HooksDhcpv4SrvTest.basic_lease4_renew in
/// src/bin/dhcp4/tests/dhcp4_srv_unittest.cc
class HookAllocEngine4Test : public AllocEngine4Test {
public:
    HookAllocEngine4Test() {
        resetCalloutBuffers();
    }

    virtual ~HookAllocEngine4Test() {
        HooksManager::preCalloutsLibraryHandle().deregisterAllCallouts(
            "lease4_select");
    }

    /// @brief clears out buffers, so callouts can store received arguments
    void resetCalloutBuffers() {
        callback_name_ = string("");
        callback_subnet4_.reset();
        callback_fake_allocation_ = false;
        callback_lease4_.reset();
        callback_argument_names_.clear();
        callback_addr_original_ = IOAddress("::");
        callback_addr_updated_ = IOAddress("::");
    }

    /// callback that stores received callout name and received values
    static int
    lease4_select_callout(CalloutHandle& callout_handle) {

        callback_name_ = string("lease4_select");

        callout_handle.getArgument("subnet4", callback_subnet4_);
        callout_handle.getArgument("fake_allocation", callback_fake_allocation_);
        callout_handle.getArgument("lease4", callback_lease4_);

        callback_addr_original_ = callback_lease4_->addr_;

        callback_argument_names_ = callout_handle.getArgumentNames();
        return (0);
    }

    /// callback that overrides the lease with different values
    static int
    lease4_select_different_callout(CalloutHandle& callout_handle) {

        // Let's call the basic callout, so it can record all parameters
        lease4_select_callout(callout_handle);

        // Now we need to tweak the least a bit
        Lease4Ptr lease;
        callout_handle.getArgument("lease4", lease);
        callback_addr_updated_ = addr_override_;
        lease->addr_ = callback_addr_updated_;
        lease->t1_ = t1_override_;
        lease->t2_ = t2_override_;
        lease->valid_lft_ = valid_override_;

        return (0);
    }

    // Values to be used in callout to override lease4 content
    static const IOAddress addr_override_;
    static const uint32_t t1_override_;
    static const uint32_t t2_override_;
    static const uint32_t valid_override_;

    // Callback will store original and overridden values here
    static IOAddress callback_addr_original_;
    static IOAddress callback_addr_updated_;

    // Buffers (callback will store received values here)
    static string callback_name_;
    static Subnet4Ptr callback_subnet4_;
    static Lease4Ptr callback_lease4_;
    static bool callback_fake_allocation_;
    static vector<string> callback_argument_names_;
};

// For some reason intialization within a class makes the linker confused.
// linker complains about undefined references if they are defined within
// the class declaration.
const IOAddress HookAllocEngine4Test::addr_override_("192.0.3.1");
const uint32_t HookAllocEngine4Test::t1_override_ = 4000;
const uint32_t HookAllocEngine4Test::t2_override_ = 7000;
const uint32_t HookAllocEngine4Test::valid_override_ = 9000;

IOAddress HookAllocEngine4Test::callback_addr_original_("::");
IOAddress HookAllocEngine4Test::callback_addr_updated_("::");

string HookAllocEngine4Test::callback_name_;
Subnet4Ptr HookAllocEngine4Test::callback_subnet4_;
Lease4Ptr HookAllocEngine4Test::callback_lease4_;
bool HookAllocEngine4Test::callback_fake_allocation_;
vector<string> HookAllocEngine4Test::callback_argument_names_;

// This test checks if the lease4_select callout is executed and expected
// parameters as passed.
TEST_F(HookAllocEngine4Test, lease4_select) {

    // Note: The following order is working as expected:
    // 1. create AllocEngine (that register hook points)
    // 2. call loadLibraries()
    //
    // This order, however, causes segfault in HooksManager
    // 1. call loadLibraries()
    // 2. create AllocEngine (that register hook points)

    // Create allocation engine (hook names are registered in its ctor)
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

    // Initialize Hooks Manager
    vector<string> libraries; // no libraries at this time
    HooksManager::loadLibraries(libraries);

    // Install pkt4_receive_callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_select", lease4_select_callout));

    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_,
                                    IOAddress("0.0.0.0"),
                                    false, false, "", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    ctx.callout_handle_ = callout_handle;

    Lease4Ptr lease = engine->allocateLease4(ctx);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // Do all checks on the lease
    checkLease4(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Check that callouts were indeed called
    EXPECT_EQ("lease4_select", callback_name_);

    // Now check that the lease in LeaseMgr has the same parameters
    ASSERT_TRUE(callback_lease4_);
    detailCompareLease(callback_lease4_, from_mgr);

    ASSERT_TRUE(callback_subnet4_);
    EXPECT_EQ(subnet_->toText(), callback_subnet4_->toText());

    EXPECT_EQ(callback_fake_allocation_, false);

    // Check if all expected parameters are reported. It's a bit tricky, because
    // order may be different. If the test starts failing, because someone tweaked
    // hooks engine, we'll have to implement proper vector matching (ignoring order)
    vector<string> expected_argument_names;
    expected_argument_names.push_back("fake_allocation");
    expected_argument_names.push_back("lease4");
    expected_argument_names.push_back("subnet4");
    EXPECT_TRUE(callback_argument_names_ == expected_argument_names);
}

// This test checks if lease4_select callout is able to override the values
// in a lease4.
TEST_F(HookAllocEngine4Test, change_lease4_select) {

    // Make sure that the overridden values are different than the ones from
    // subnet originally used to create the lease
    ASSERT_NE(t1_override_, subnet_->getT1());
    ASSERT_NE(t2_override_, subnet_->getT2());
    ASSERT_NE(valid_override_, subnet_->getValid());
    ASSERT_FALSE(subnet_->inRange(addr_override_));

    // Create allocation engine (hook names are registered in its ctor)
    boost::scoped_ptr<AllocEngine> engine;
    ASSERT_NO_THROW(engine.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE,
                                                 100, false)));
    ASSERT_TRUE(engine);

    // Initialize Hooks Manager
    vector<string> libraries; // no libraries at this time
    HooksManager::loadLibraries(libraries);

    // Install a callout
    EXPECT_NO_THROW(HooksManager::preCalloutsLibraryHandle().registerCallout(
                        "lease4_select", lease4_select_different_callout));

    // Normally, dhcpv4_srv would passed the handle when calling allocateLease4,
    // but in tests we need to create it on our own.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();


    AllocEngine::ClientContext4 ctx(subnet_, clientid_, hwaddr_, IOAddress("0.0.0.0"),
                                    false, true, "somehost.example.com.", false);
    ctx.query_.reset(new Pkt4(DHCPREQUEST, 1234));
    ctx.callout_handle_ = callout_handle;

    // Call allocateLease4. Callouts should be triggered here.
    Lease4Ptr lease = engine->allocateLease4(ctx);

    // Check that we got a lease
    ASSERT_TRUE(lease);

    // See if the values overridden by callout are there
    EXPECT_TRUE(lease->addr_.equals(addr_override_));
    EXPECT_EQ(t1_override_, lease->t1_);
    EXPECT_EQ(t2_override_, lease->t2_);
    EXPECT_EQ(valid_override_, lease->valid_lft_);

    // Now check if the lease is in the database
    Lease4Ptr from_mgr = LeaseMgrFactory::instance().getLease4(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Check if values in the database are overridden
    EXPECT_TRUE(from_mgr->addr_.equals(addr_override_));
    EXPECT_EQ(t1_override_, from_mgr->t1_);
    EXPECT_EQ(t2_override_, from_mgr->t2_);
    EXPECT_EQ(valid_override_, from_mgr->valid_lft_);
}

}; // namespace test
}; // namespace dhcp
}; // namespace isc
