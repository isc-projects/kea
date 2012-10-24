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
// empty class for now, but may be extended once Addr6 becomes bigger
class AllocEngineTest : public ::testing::Test {
public:
    AllocEngineTest() {
    }
};

// This test checks if the Allocation Engine can be instantiated and that it
// parses parameters string properly.
TEST_F(AllocEngineTest, constructor) {

    AllocEngine* x = NULL;

    // Hashed and random allocators are not supported yet
    ASSERT_THROW(x = new AllocEngine(AllocEngine::ALLOC_HASHED, 5), BadValue);
    ASSERT_THROW(x = new AllocEngine(AllocEngine::ALLOC_RANDOM, 5), BadValue);

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
    DuidPtr duid = boost::shared_ptr<DUID>(new DUID(vector<uint8_t>(8, 0x42)));

    const uint32_t iaid = 42;

    // instantiate cfg_mgr
    CfgMgr& cfg_mgr = CfgMgr::instance();
    ASSERT_TRUE(&cfg_mgr != 0);

    Subnet6Ptr subnet(new Subnet6(IOAddress("2001:db8:1::"), 56, 1, 2, 3, 4));

    Pool6Ptr pool(new Pool6(Pool6::TYPE_IA, IOAddress("2001:db8:1:1::"), 64));

    subnet->addPool6(pool);

    cfg_mgr.addSubnet6(subnet);

    Memfile_LeaseMgr* leaseMgr = new Memfile_LeaseMgr("");

    AllocEngine* engine = NULL;
    ASSERT_NO_THROW(engine = new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100));
    ASSERT_TRUE(engine);

    Lease6Ptr lease = engine->allocateAddress6(subnet, duid, iaid, IOAddress("::"),
                                               false);

    // check that we got a lease
    ASSERT_TRUE(lease);

    // that is belongs to the right subnet
    EXPECT_EQ(lease->subnet_id_, subnet->getID());
    EXPECT_TRUE(subnet->inRange(lease->addr_));
    EXPECT_TRUE(subnet->inPool(lease->addr_));

    // that it have proper parameters
    EXPECT_EQ(iaid, lease->iaid_);
    EXPECT_EQ(subnet->getValid(), lease->valid_lft_);
    EXPECT_EQ(subnet->getPreferred(), lease->preferred_lft_);
    EXPECT_EQ(subnet->getT1(), lease->t1_);
    EXPECT_EQ(subnet->getT2(), lease->t2_);
    EXPECT_EQ(0, lease->prefixlen_); // this is IA_NA, not IA_PD
    EXPECT_TRUE(false == lease->fqdn_fwd_);
    EXPECT_TRUE(false == lease->fqdn_rev_);
    EXPECT_TRUE(*lease->duid_ == *duid);
    // @todo: check cltt

    // Check that the lease is indeed in LeaseMgr
    Lease6Ptr from_mgr = LeaseMgr::instance().getLease6(lease->addr_);
    ASSERT_TRUE(from_mgr);

    // Now check that the lease in LeaseMgr has the same parameters
    detailCompareLease6(lease, from_mgr);

    delete leaseMgr;
}


}; // end of anonymous namespace
