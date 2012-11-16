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

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {
// empty class for now, but may be extended once Addr6 becomes bigger
class MemfileLeaseMgrTest : public ::testing::Test {
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
    EXPECT_EQ(std::string("memfile"), lease_mgr->getName());
}

// Checks that adding/getting/deleting a Lease6 object works.
TEST_F(MemfileLeaseMgrTest, addGetDelete6) {
    const LeaseMgr::ParameterMap pmap;  // Empty parameter map
    boost::scoped_ptr<Memfile_LeaseMgr> lease_mgr(new Memfile_LeaseMgr(pmap));

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

    Lease6Ptr x = lease_mgr->getLease6(IOAddress("2001:db8:1::234"));
    EXPECT_EQ(Lease6Ptr(), x);

    x = lease_mgr->getLease6(IOAddress("2001:db8:1::456"));
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
    Lease6Ptr y = lease_mgr->getLease6(*duid, iaid, subnet_id);
    ASSERT_TRUE(y);
    EXPECT_TRUE(*y->duid_ == *duid);
    EXPECT_EQ(y->iaid_, iaid);
    EXPECT_EQ(y->addr_.toText(), addr.toText());

    // Test getLease6(duid, iaid, subnet_id) - wrong iaid
    uint32_t invalid_iaid = 9; // no such iaid
    y = lease_mgr->getLease6(*duid, invalid_iaid, subnet_id);
    EXPECT_FALSE(y);

    uint32_t invalid_subnet_id = 999;
    y = lease_mgr->getLease6(*duid, iaid, invalid_subnet_id);
    EXPECT_FALSE(y);

    // truncated duid
    DuidPtr invalid_duid(new DUID(llt, sizeof(llt) - 1));
    y = lease_mgr->getLease6(*invalid_duid, iaid, subnet_id);
    EXPECT_FALSE(y);

    // should return false - there's no such address
    EXPECT_FALSE(lease_mgr->deleteLease6(IOAddress("2001:db8:1::789")));

    // this one should succeed
    EXPECT_TRUE(lease_mgr->deleteLease6(IOAddress("2001:db8:1::456")));

    // after the lease is deleted, it should really be gone
    x = lease_mgr->getLease6(IOAddress("2001:db8:1::456"));
    EXPECT_EQ(Lease6Ptr(), x);
}

// TODO: Write more memfile tests

}; // end of anonymous namespace
