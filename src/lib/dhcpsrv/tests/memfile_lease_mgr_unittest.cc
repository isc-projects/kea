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
#include <dhcp/duid.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/memfile_lease_mgr.h>
#include <dhcpsrv/tests/test_utils.h>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {
// empty class for now, but may be extended once Addr6 becomes bigger
class MemfileLeaseMgrTest : public GenericLeaseMgrTest {
public:
    MemfileLeaseMgrTest() {
    }
};

// This test checks if the LeaseMgr can be instantiated and that it
// parses parameters string properly.
TEST_F(MemfileLeaseMgrTest, constructor) {

    const LeaseMgr::ParameterMap pmap;  // Empty parameter map
    boost::scoped_ptr<Memfile_LeaseMgr> lease_mgr;

    ASSERT_NO_THROW(lease_mgr.reset(new Memfile_LeaseMgr(pmap)));
}

// Checks if the getType() and getName() methods both return "memfile".
TEST_F(MemfileLeaseMgrTest, getTypeAndName) {
    const LeaseMgr::ParameterMap pmap;  // Empty parameter map
    boost::scoped_ptr<Memfile_LeaseMgr> lease_mgr(new Memfile_LeaseMgr(pmap));

    EXPECT_EQ(std::string("memfile"), lease_mgr->getType());
    EXPECT_EQ(std::string("memory"), lease_mgr->getName());
}

// Checks that adding/getting/deleting a Lease6 object works.
TEST_F(MemfileLeaseMgrTest, addGetDelete6) {
    const LeaseMgr::ParameterMap pmap;  // Empty parameter map
    boost::scoped_ptr<LeaseMgr> lease_mgr(new Memfile_LeaseMgr(pmap));

    IOAddress addr("2001:db8:1::456");

    uint8_t llt[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    DuidPtr duid(new DUID(llt, sizeof(llt)));

    uint32_t iaid = 7; // just a number

    SubnetID subnet_id = 8; // just another number

    Lease6Ptr lease(new Lease6(Lease6::LEASE_IA_NA, addr,
                               duid, iaid, 100, 200, 50, 80,
                               subnet_id));

    EXPECT_TRUE(lease_mgr->addLease(lease));

    // should not be allowed to add a second lease with the same address
    EXPECT_FALSE(lease_mgr->addLease(lease));

    Lease6Ptr x = lease_mgr->getLease6(Lease6::LEASE_IA_NA,
                                       IOAddress("2001:db8:1::234"));
    EXPECT_EQ(Lease6Ptr(), x);

    x = lease_mgr->getLease6(Lease6::LEASE_IA_NA,
                             IOAddress("2001:db8:1::456"));
    ASSERT_TRUE(x);

    EXPECT_EQ(x->addr_.toText(), addr.toText());
    EXPECT_TRUE(*x->duid_ == *duid);
    EXPECT_EQ(x->iaid_, iaid);
    EXPECT_EQ(x->subnet_id_, subnet_id);

    // These are not important from lease management perspective, but
    // let's check them anyway.
    EXPECT_EQ(x->type_, Lease6::LEASE_IA_NA);
    EXPECT_EQ(x->preferred_lft_, 100);
    EXPECT_EQ(x->valid_lft_, 200);
    EXPECT_EQ(x->t1_, 50);
    EXPECT_EQ(x->t2_, 80);

    // Test getLease6(duid, iaid, subnet_id) - positive case
    Lease6Ptr y = lease_mgr->getLease6(Lease6::LEASE_IA_NA, *duid, iaid,
                                       subnet_id);
    ASSERT_TRUE(y);
    EXPECT_TRUE(*y->duid_ == *duid);
    EXPECT_EQ(y->iaid_, iaid);
    EXPECT_EQ(y->addr_.toText(), addr.toText());

    // Test getLease6(duid, iaid, subnet_id) - wrong iaid
    uint32_t invalid_iaid = 9; // no such iaid
    y = lease_mgr->getLease6(Lease6::LEASE_IA_NA, *duid, invalid_iaid,
                             subnet_id);
    EXPECT_FALSE(y);

    uint32_t invalid_subnet_id = 999;
    y = lease_mgr->getLease6(Lease6::LEASE_IA_NA, *duid, iaid,
                             invalid_subnet_id);
    EXPECT_FALSE(y);

    // truncated duid
    DuidPtr invalid_duid(new DUID(llt, sizeof(llt) - 1));
    y = lease_mgr->getLease6(Lease6::LEASE_IA_NA, *invalid_duid, iaid,
                             subnet_id);
    EXPECT_FALSE(y);

    // should return false - there's no such address
    EXPECT_FALSE(lease_mgr->deleteLease(IOAddress("2001:db8:1::789")));

    // this one should succeed
    EXPECT_TRUE(lease_mgr->deleteLease(IOAddress("2001:db8:1::456")));

    // after the lease is deleted, it should really be gone
    x = lease_mgr->getLease6(Lease6::LEASE_IA_NA, IOAddress("2001:db8:1::456"));
    EXPECT_EQ(Lease6Ptr(), x);
}

// @todo Write more memfile tests

// Simple test about lease4 retrieval through client id method
TEST_F(MemfileLeaseMgrTest, getLease4ClientId) {
    const LeaseMgr::ParameterMap pmap;
    boost::scoped_ptr<Memfile_LeaseMgr> lease_mgr(new Memfile_LeaseMgr(pmap));
    // Let's initialize a specific lease ...
    Lease4Ptr lease = initializeLease4(straddress4_[1]);
    EXPECT_TRUE(lease_mgr->addLease(lease));
    Lease4Collection returned = lease_mgr->getLease4(*lease->client_id_);

    ASSERT_EQ(1, returned.size());
    // We should retrieve our lease...
    detailCompareLease(lease, *returned.begin());
    lease = initializeLease4(straddress4_[2]);
    returned = lease_mgr->getLease4(*lease->client_id_);

    ASSERT_EQ(0, returned.size());
}

// Checks that lease4 retrieval client id is null is working
TEST_F(MemfileLeaseMgrTest, getLease4NullClientId) {
    const LeaseMgr::ParameterMap pmap;
    boost::scoped_ptr<Memfile_LeaseMgr> lease_mgr(new Memfile_LeaseMgr(pmap));
    // Let's initialize a specific lease ... But this time
    // We keep its client id for further lookup and
    // We clearly 'reset' it ...
    Lease4Ptr lease = initializeLease4(straddress4_[4]);
    ClientIdPtr client_id = lease->client_id_;
    lease->client_id_ = ClientIdPtr();
    EXPECT_TRUE(lease_mgr->addLease(lease));

    Lease4Collection returned = lease_mgr->getLease4(*client_id);
    // Shouldn't have our previous lease ...
    ASSERT_EQ(0, returned.size());
}

// Checks lease4 retrieval through HWAddr
TEST_F(MemfileLeaseMgrTest, getLease4HWAddr) {
    const LeaseMgr::ParameterMap pmap;
    boost::scoped_ptr<Memfile_LeaseMgr> lease_mgr(new Memfile_LeaseMgr(pmap));
    // Let's initialize two different leases 4 and just add the first ...
    Lease4Ptr leaseA = initializeLease4(straddress4_[5]);
    HWAddr hwaddrA(leaseA->hwaddr_, HTYPE_ETHER);
    HWAddr hwaddrB(vector<uint8_t>(6, 0x80), HTYPE_ETHER);

    EXPECT_TRUE(lease_mgr->addLease(leaseA));

    // we should not have a lease, with this MAC Addr
    Lease4Collection returned = lease_mgr->getLease4(hwaddrB);
    ASSERT_EQ(0, returned.size());

    // But with this one
    returned = lease_mgr->getLease4(hwaddrA);
    ASSERT_EQ(1, returned.size());
}

// Checks lease4 retrieval with clientId, HWAddr and subnet_id
TEST_F(MemfileLeaseMgrTest, getLease4ClientIdHWAddrSubnetId) {
    const LeaseMgr::ParameterMap pmap;
    boost::scoped_ptr<Memfile_LeaseMgr> lease_mgr(new Memfile_LeaseMgr(pmap));

    Lease4Ptr leaseA = initializeLease4(straddress4_[4]);
    Lease4Ptr leaseB = initializeLease4(straddress4_[5]);
    HWAddr hwaddrA(leaseA->hwaddr_, HTYPE_ETHER);
    HWAddr hwaddrB(leaseB->hwaddr_, HTYPE_ETHER);
    EXPECT_TRUE(lease_mgr->addLease(leaseA));
    // First case we should retrieve our lease
    Lease4Ptr lease = lease_mgr->getLease4(*leaseA->client_id_, hwaddrA, leaseA->subnet_id_);
    detailCompareLease(lease, leaseA);
    lease = lease_mgr->getLease4(*leaseB->client_id_, hwaddrA, leaseA->subnet_id_);
    detailCompareLease(lease, leaseA);
    // But not the folowing, with different  hwaddr and subnet
    lease = lease_mgr->getLease4(*leaseA->client_id_, hwaddrB, leaseA->subnet_id_);
    EXPECT_TRUE(lease == Lease4Ptr());
    lease = lease_mgr->getLease4(*leaseA->client_id_, hwaddrA, leaseB->subnet_id_);
    EXPECT_TRUE(lease == Lease4Ptr());
}

}; // end of anonymous namespace
