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
#include <iostream>
#include <sstream>
#include <gtest/gtest.h>
#include <asiolink/io_address.h>
#include <dhcp/lease_mgr.h>
#include <dhcp/duid.h>
#include "memfile_lease_mgr.h"

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test; // Memfile_LeaseMgr

namespace {
// empty class for now, but may be extended once Addr6 becomes bigger
class LeaseMgrTest : public ::testing::Test {
public:
    LeaseMgrTest() {
    }
};

// This test checks if the LeaseMgr can be instantiated and that it
// parses parameters string properly.
TEST_F(LeaseMgrTest, constructor) {

    // should not throw any exceptions here
    Memfile_LeaseMgr * leaseMgr = new Memfile_LeaseMgr("");
    delete leaseMgr;

    leaseMgr = new Memfile_LeaseMgr("param1=value1 param2=value2");

    EXPECT_EQ("value1", leaseMgr->getParameter("param1"));
    EXPECT_EQ("value2", leaseMgr->getParameter("param2"));
    EXPECT_THROW(leaseMgr->getParameter("param3"), BadValue);

    delete leaseMgr;
}

// There's no point in calling any other methods in LeaseMgr, as they
// are purely virtual, so we would only call Memfile_LeaseMgr methods.
// Those methods are just stubs that does not return anything.
// It seems likely that we will need to extend the memfile code for
// allocation engine tests, so we may implement tests that call
// Memfile_LeaseMgr methods then.

TEST_F(LeaseMgrTest, addGetDelete) {
    Memfile_LeaseMgr * leaseMgr = new Memfile_LeaseMgr("");

    IOAddress addr("2001:db8:1::456");

    uint8_t llt[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    DuidPtr duid(new DUID(llt, sizeof(llt)));

    uint32_t iaid = 7; // just a number

    SubnetID subnet_id = 8; // just another number

    Lease6Ptr lease(new Lease6(Lease6::LEASE_IA_NA, addr,
                               duid, iaid, 100, 200, 50, 80,
                               subnet_id));

    EXPECT_TRUE(leaseMgr->addLease(lease));

    // should not be allowed to add a second lease with the same address
    EXPECT_FALSE(leaseMgr->addLease(lease));

    Lease6Ptr x = leaseMgr->getLease6(IOAddress("2001:db8:1::234"));
    EXPECT_EQ(Lease6Ptr(), x);

    x = leaseMgr->getLease6(IOAddress("2001:db8:1::456"));
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
    Lease6Ptr y = leaseMgr->getLease6(*duid, iaid, subnet_id);
    ASSERT_TRUE(y);
    EXPECT_TRUE(*y->duid_ == *duid);
    EXPECT_EQ(y->iaid_, iaid);
    EXPECT_EQ(y->addr_.toText(), addr.toText());

    // Test getLease6(duid, iaid, subnet_id) - wrong iaid
    uint32_t invalid_iaid = 9; // no such iaid
    y = leaseMgr->getLease6(*duid, invalid_iaid, subnet_id);
    EXPECT_FALSE(y);

    uint32_t invalid_subnet_id = 999;
    y = leaseMgr->getLease6(*duid, iaid, invalid_subnet_id);
    EXPECT_FALSE(y);

    // truncated duid
    DuidPtr invalid_duid(new DUID(llt, sizeof(llt) - 1));
    y = leaseMgr->getLease6(*invalid_duid, iaid, subnet_id);
    EXPECT_FALSE(y);

    // should return false - there's no such address
    EXPECT_FALSE(leaseMgr->deleteLease6(IOAddress("2001:db8:1::789")));

    // this one should succeed
    EXPECT_TRUE(leaseMgr->deleteLease6(IOAddress("2001:db8:1::456")));

    // after the lease is deleted, it should really be gone
    x = leaseMgr->getLease6(IOAddress("2001:db8:1::456"));
    EXPECT_EQ(Lease6Ptr(), x);

    delete leaseMgr;
}

// This test checks there that leaseMgr is really a singleton and that
// no more than one can be created.
TEST_F(LeaseMgrTest, singleton) {
    Memfile_LeaseMgr* leaseMgr1 = NULL;
    Memfile_LeaseMgr* leaseMgr2 = NULL;

    EXPECT_THROW(LeaseMgr::instance(), InvalidOperation);

    EXPECT_NO_THROW( leaseMgr1 = new Memfile_LeaseMgr("") );

    EXPECT_NO_THROW(LeaseMgr::instance());

    // There can be only one instance of any LeaseMgr derived
    // objects instantiated at any time.
    ASSERT_THROW(leaseMgr2 = new Memfile_LeaseMgr(""), InvalidOperation);

    delete leaseMgr1;

    ASSERT_NO_THROW(leaseMgr2 = new Memfile_LeaseMgr("") );

    delete leaseMgr2;
}

// This test checks if the Lease6 structure can be instantiated correctly
TEST(Lease6, ctor) {

    IOAddress addr("2001:db8:1::456");

    uint8_t llt[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    DuidPtr duid(new DUID(llt, sizeof(llt)));

    uint32_t iaid = 7; // just a number

    SubnetID subnet_id = 8; // just another number

    Lease6Ptr x(new Lease6(Lease6::LEASE_IA_NA, addr,
                           duid, iaid, 100, 200, 50, 80,
                           subnet_id));

    EXPECT_TRUE(x->addr_ == addr);
    EXPECT_TRUE(*x->duid_ == *duid);
    EXPECT_TRUE(x->iaid_ == iaid);
    EXPECT_TRUE(x->subnet_id_ == subnet_id);
    EXPECT_TRUE(x->type_ == Lease6::LEASE_IA_NA);
    EXPECT_TRUE(x->preferred_lft_ == 100);
    EXPECT_TRUE(x->valid_lft_ == 200);
    EXPECT_TRUE(x->t1_ == 50);
    EXPECT_TRUE(x->t2_ == 80);

    // Lease6 must be instantiated with a DUID, not with NULL pointer
    EXPECT_THROW(new Lease6(Lease6::LEASE_IA_NA, addr,
                            DuidPtr(), iaid, 100, 200, 50, 80,
                            subnet_id), InvalidOperation);
}

}; // end of anonymous namespace
