// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/lease_mgr.h>
#include <dhcp/duid.h>
#include <dhcp/alloc_engine.h>
#include <dhcp/cfgmgr.h>
#include "memfile_lease_mgr.h"
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <sstream>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test; // Memfile_LeaseMgr
using namespace boost;

namespace {

class NakedAllocEngine : public AllocEngine {
public:
    using AllocEngine::Allocator;
    using AllocEngine::IterativeAllocator;
};

// empty class for now, but may be extended once Addr6 becomes bigger
class AllocEngineTest : public ::testing::Test {
public:
    AllocEngineTest() {
        duid_ = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0x42)));
        iaid_ = 42;

        // instantiate cfg_mgr
        CfgMgr& cfg_mgr = CfgMgr::instance();

        subnet_ = Subnet6Ptr(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));
        pool_ = Pool6Ptr(new Pool6(Pool6::TYPE_IA, IOAddress("2001:db8:1::10"),
                                   IOAddress("2001:db8:1::20")));
        subnet_->addPool6(pool_);
        cfg_mgr.addSubnet6(subnet_);

        leasemgr_ = new Memfile_LeaseMgr("");
    }

    void checkLease6(const Lease6Ptr& lease) {
        // that is belongs to the right subnet
        EXPECT_EQ(lease->subnet_id_, subnet_->getID());
        EXPECT_TRUE(subnet_->inRange(lease->addr_));
        EXPECT_TRUE(subnet_->inPool(lease->addr_));

        // that it have proper parameters
        EXPECT_EQ(iaid_, lease->iaid_);
        EXPECT_EQ(subnet_->getValid(), lease->valid_lft_);
        EXPECT_EQ(subnet_->getPreferred(), lease->preferred_lft_);
        EXPECT_EQ(subnet_->getT1(), lease->t1_);
        EXPECT_EQ(subnet_->getT2(), lease->t2_);
        EXPECT_EQ(0, lease->prefixlen_); // this is IA_NA, not IA_PD
        EXPECT_TRUE(false == lease->fqdn_fwd_);
        EXPECT_TRUE(false == lease->fqdn_rev_);
        EXPECT_TRUE(*lease->duid_ == *duid_);
        // @todo: check cltt
     }

    ~AllocEngineTest() {
        LeaseMgr::instance().destroy_instance();
        leasemgr_ = NULL;
    }

    DuidPtr duid_;
    uint32_t iaid_;
    Subnet6Ptr subnet_;
    Pool6Ptr pool_;
    LeaseMgr* leasemgr_;
};

// This test checks if the Allocation Engine can be instantiated and that it
// parses parameters string properly.
TEST_F(AllocEngineTest, constructor) {

    AllocEngine* x = NULL;

    // Hashed and random allocators are not supported yet
    ASSERT_THROW(x = new AllocEngine(AllocEngine::ALLOC_HASHED, 5), NotImplemented);
    ASSERT_THROW(x = new AllocEngine(AllocEngine::ALLOC_RANDOM, 5), NotImplemented);

    ASSERT_NO_THROW(x = new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100));

    delete x;
}

/// @todo: This method is taken from mysql_lease_mgr_utilities.cc from ticket
/// #2342. Get rid of one instance once the code is merged
void
detailCompareLease6(const Lease6Ptr& first, const Lease6Ptr& second) {
    EXPECT_EQ(first->type_, second->type_);

    // Compare address strings - odd things happen when they are different
    // as the EXPECT_EQ appears to call the operator uint32_t() function,
    // which causes an exception to be thrown for IPv6 addresses.
    EXPECT_EQ(first->addr_.toText(), second->addr_.toText());
    EXPECT_EQ(first->prefixlen_, second->prefixlen_);
    EXPECT_EQ(first->iaid_, second->iaid_);
    EXPECT_TRUE(first->hwaddr_ == second->hwaddr_);
    EXPECT_TRUE(*first->duid_ == *second->duid_);
    EXPECT_EQ(first->preferred_lft_, second->preferred_lft_);
    EXPECT_EQ(first->valid_lft_, second->valid_lft_);
    EXPECT_EQ(first->cltt_, second->cltt_);
    EXPECT_EQ(first->subnet_id_, second->subnet_id_);
}


// This test checks if the simple allocation can succeed
TEST_F(AllocEngineTest, simpleAlloc) {

    AllocEngine* engine = NULL;
    ASSERT_NO_THROW(engine = new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100));
    ASSERT_TRUE(engine);

    Lease6Ptr lease = engine->allocateAddress6(subnet_, duid_, iaid_, IOAddress("::"),
                                               false);

    // check that we got a lease
    ASSERT_TRUE(lease);

    // do all checks on the lease
    checkLease6(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgr::instance().getLease6(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease6(lease, from_mgr);
}

// This test checks if the fake allocation (for SOLICIT) can succeed
TEST_F(AllocEngineTest, fakeAlloc) {

    AllocEngine* engine = NULL;
    ASSERT_NO_THROW(engine = new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100));
    ASSERT_TRUE(engine);

    Lease6Ptr lease = engine->allocateAddress6(subnet_, duid_, iaid_, IOAddress("::"),
                                               true);

    // check that we got a lease
    ASSERT_TRUE(lease);

    // do all checks on the lease
    checkLease6(lease);

    // Check that the lease is NOT in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgr::instance().getLease6(lease->addr_);
    ASSERT_FALSE(from_mgr);
}

// This test checks if the allocation with a hint that is valid (in range,
// in pool and free) can succeed
TEST_F(AllocEngineTest, allocWithValidHint) {

    AllocEngine* engine = NULL;
    ASSERT_NO_THROW(engine = new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100));
    ASSERT_TRUE(engine);

    Lease6Ptr lease = engine->allocateAddress6(subnet_, duid_, iaid_,
                                               IOAddress("2001:db8:1::15"),
                                               false);

    // check that we got a lease
    ASSERT_TRUE(lease);

    // we should get what we asked for
    EXPECT_EQ(lease->addr_.toText(), "2001:db8:1::15");

    // do all checks on the lease
    checkLease6(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgr::instance().getLease6(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease6(lease, from_mgr);
}

// This test checks if the allocation with a hint that is in range,
// in pool, but is currently used) can succeed
TEST_F(AllocEngineTest, allocWithUsedHint) {

    AllocEngine* engine = NULL;
    ASSERT_NO_THROW(engine = new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100));
    ASSERT_TRUE(engine);

    // let's create a lease and put it in the LeaseMgr
    DuidPtr duid2 = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0xff)));
    Lease6Ptr used(new Lease6(Lease6::LEASE_IA_NA, IOAddress("2001:db8:1::1f"),
                              duid2, 1, 2, 3, 4, 5, subnet_->getID()));
    ASSERT_TRUE(LeaseMgr::instance().addLease(used));

    // another client comes in and request an address that is in pool, but
    // unfortunately it is used already. The same address must not be allocated
    // twice.
    Lease6Ptr lease = engine->allocateAddress6(subnet_, duid_, iaid_,
                                               IOAddress("2001:db8:1::1f"),
                                               false);
    // check that we got a lease
    ASSERT_TRUE(lease);

    // allocated address must be different
    EXPECT_TRUE(used->addr_.toText() != lease->addr_.toText());

    // we should NOT get what we asked for, because it is used already
    EXPECT_TRUE(lease->addr_.toText() != "2001:db8:1::1f");

    // do all checks on the lease
    checkLease6(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgr::instance().getLease6(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease6(lease, from_mgr);
}

// This test checks if the allocation with a hint that is out the blue
// can succeed. The invalid hint should be ignored completely.
TEST_F(AllocEngineTest, allocBogusHint) {

    AllocEngine* engine = NULL;
    ASSERT_NO_THROW(engine = new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100));
    ASSERT_TRUE(engine);

    // Client would like to get a 3000::abc lease, which does not belong to any
    // supported lease. Allocation engine should ignore it and carry on
    // with the normal allocation
    Lease6Ptr lease = engine->allocateAddress6(subnet_, duid_, iaid_,
                                               IOAddress("3000::abc"),
                                               false);
    // check that we got a lease
    ASSERT_TRUE(lease);

    // we should NOT get what we asked for, because it is used already
    EXPECT_TRUE(lease->addr_.toText() != "3000::abc");

    // do all checks on the lease
    checkLease6(lease);

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgr::instance().getLease6(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease6(lease, from_mgr);
}

// This test verifies that the allocator picks addresses that belong to the
// pool
TEST_F(AllocEngineTest, IterativeAllocator) {
    NakedAllocEngine::Allocator* alloc = new NakedAllocEngine::IterativeAllocator();

    for (int i = 0; i < 1000; ++i) {
        IOAddress candidate = alloc->pickAddress(subnet_, duid_, IOAddress("::"));

        EXPECT_TRUE(subnet_->inPool(candidate));
    }

    delete alloc;
}


// This test verifies that the iterative allocator really walks over all addresses
// in all pools in specified subnet. It also must not pick the same address twice
// unless it runs out of pool space and must start over.
TEST_F(AllocEngineTest, IterativeAllocator_manyPools) {
    NakedAllocEngine::IterativeAllocator* alloc = new NakedAllocEngine::IterativeAllocator();

    // let's start from 2, as there is 2001:db8:1::10 - 2001:db8:1::20 pool already.
    for (int i = 2; i < 10; ++i) {
        stringstream min, max;

        min << "2001:db8:1::" << hex << i*16 + 1;
        max << "2001:db8:1::" << hex << i*16 + 9;

        Pool6Ptr pool(new Pool6(Pool6::TYPE_IA, IOAddress(min.str()),
                                IOAddress(max.str())));
        // cout << "Adding pool: " << min.str() << "-" << max.str() << endl;
        subnet_->addPool6(pool);
    }

    int total = 17 + 8*9; // first pool (::10 - ::20) has 17 addresses in it,
                          // there are 8 extra pools with 9 addresses in each.

    // Let's keep picked addresses here and check their uniqueness.
    map<IOAddress, int> generated_addrs;
    int cnt = 0;
    while (++cnt) {
        IOAddress candidate = alloc->pickAddress(subnet_, duid_, IOAddress("::"));
        EXPECT_TRUE(subnet_->inPool(candidate));

        // One way to easily verify that the iterative allocator really works is
        // to uncomment the following line and observe its output that it
        // covers all defined subnets.
        // cout << candidate.toText() << endl;

        if (generated_addrs.find(candidate) == generated_addrs.end()) {
            // we haven't had this
            generated_addrs[candidate] = 0;
        } else {
            // we have seen this address before. That should mean that we
            // iterated over all addresses.
            if (generated_addrs.size() == total) {
                // we have exactly the number of address in all pools
                break;
            }
            ADD_FAILURE() << "Too many or not enough unique addresses generated.";
            break;
        }

        if ( cnt>total ) {
            ADD_FAILURE() << "Too many unique addresses generated.";
            break;
        }
    }

    delete alloc;
}

}; // end of anonymous namespace
