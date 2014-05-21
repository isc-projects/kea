// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/tests/generic_lease_mgr_unittest.h>
#include <dhcpsrv/tests/test_utils.h>
#include <asiolink/io_address.h>
#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc::asiolink;

namespace isc {
namespace dhcp {
namespace test {

// IPv4 and IPv6 addresses used in the tests
const char* ADDRESS4[] = {
    "192.0.2.0", "192.0.2.1", "192.0.2.2", "192.0.2.3",
    "192.0.2.4", "192.0.2.5", "192.0.2.6", "192.0.2.7",
    NULL
};
const char* ADDRESS6[] = {
    "2001:db8::0", "2001:db8::1", "2001:db8::2", "2001:db8::3",
    "2001:db8::4", "2001:db8::5", "2001:db8::6", "2001:db8::7",
    NULL
};

// Lease types that correspond to ADDRESS6 leases
static const Lease::Type LEASETYPE6[] = {
    Lease::TYPE_NA, Lease::TYPE_TA, Lease::TYPE_PD, Lease::TYPE_NA,
    Lease::TYPE_TA, Lease::TYPE_PD, Lease::TYPE_NA, Lease::TYPE_TA
};

GenericLeaseMgrTest::GenericLeaseMgrTest()
    : lmptr_(NULL) {
    // Initialize address strings and IOAddresses
    for (int i = 0; ADDRESS4[i] != NULL; ++i) {
        string addr(ADDRESS4[i]);
        straddress4_.push_back(addr);
        IOAddress ioaddr(addr);
        ioaddress4_.push_back(ioaddr);
    }

    for (int i = 0; ADDRESS6[i] != NULL; ++i) {
        string addr(ADDRESS6[i]);
        straddress6_.push_back(addr);
        IOAddress ioaddr(addr);
        ioaddress6_.push_back(ioaddr);

        /// Let's create different lease types. We use LEASETYPE6 values as
        /// a template
        leasetype6_.push_back(LEASETYPE6[i]);
    }
}

GenericLeaseMgrTest::~GenericLeaseMgrTest() {
    // Does nothing. The derived classes are expected to clean up, i.e.
    // remove the lmptr_ pointer.
}

Lease4Ptr
GenericLeaseMgrTest::initializeLease4(std::string address) {
    Lease4Ptr lease(new Lease4());

    // Set the address of the lease
    lease->addr_ = IOAddress(address);

    // Initialize unused fields.
    lease->ext_ = 0;                            // Not saved
    lease->t1_ = 0;                             // Not saved
    lease->t2_ = 0;                             // Not saved
    lease->fixed_ = false;                      // Unused
    lease->comments_ = std::string("");         // Unused

    // Set other parameters.  For historical reasons, address 0 is not used.
    if (address == straddress4_[0]) {
        lease->hwaddr_ = vector<uint8_t>(6, 0x08);
        lease->client_id_ = ClientIdPtr(new ClientId(vector<uint8_t>(8, 0x42)));
        lease->valid_lft_ = 8677;
        lease->cltt_ = 168256;
        lease->subnet_id_ = 23;
        lease->fqdn_rev_ = true;
        lease->fqdn_fwd_ = false;
        lease->hostname_ = "myhost.example.com.";

        } else if (address == straddress4_[1]) {
        lease->hwaddr_ = vector<uint8_t>(6, 0x19);
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x53)));
        lease->valid_lft_ = 3677;
        lease->cltt_ = 123456;
        lease->subnet_id_ = 73;
        lease->fqdn_rev_ = true;
        lease->fqdn_fwd_ = true;
        lease->hostname_ = "myhost.example.com.";

    } else if (address == straddress4_[2]) {
        lease->hwaddr_ = vector<uint8_t>(6, 0x2a);
        lease->client_id_ = ClientIdPtr(new ClientId(vector<uint8_t>(8, 0x64)));
        lease->valid_lft_ = 5412;
        lease->cltt_ = 234567;
        lease->subnet_id_ = 73;                         // Same as lease 1
        lease->fqdn_rev_ = false;
        lease->fqdn_fwd_ = false;
        lease->hostname_ = "";

    } else if (address == straddress4_[3]) {
        lease->hwaddr_ = vector<uint8_t>(6, 0x19);      // Same as lease 1
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x75)));

        // The times used in the next tests are deliberately restricted - we
        // should be able to cope with valid lifetimes up to 0xffffffff.
        //  However, this will lead to overflows.
        // @TODO: test overflow conditions when code has been fixed
        lease->valid_lft_ = 7000;
        lease->cltt_ = 234567;
        lease->subnet_id_ = 37;
        lease->fqdn_rev_ = true;
        lease->fqdn_fwd_ = true;
        lease->hostname_ = "otherhost.example.com.";

    } else if (address == straddress4_[4]) {
        lease->hwaddr_ = vector<uint8_t>(6, 0x4c);
        // Same ClientId as straddr4_[1]
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x53)));    // Same as lease 1
        lease->valid_lft_ = 7736;
        lease->cltt_ = 222456;
        lease->subnet_id_ = 85;
        lease->fqdn_rev_ = true;
        lease->fqdn_fwd_ = true;
        lease->hostname_ = "otherhost.example.com.";

    } else if (address == straddress4_[5]) {
        lease->hwaddr_ = vector<uint8_t>(6, 0x19);      // Same as lease 1
        // Same ClientId and IAID as straddress4_1
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x53)));    // Same as lease 1
        lease->valid_lft_ = 7832;
        lease->cltt_ = 227476;
        lease->subnet_id_ = 175;
        lease->fqdn_rev_ = false;
        lease->fqdn_fwd_ = false;
        lease->hostname_ = "otherhost.example.com.";
    } else if (address == straddress4_[6]) {
        lease->hwaddr_ = vector<uint8_t>(6, 0x6e);
        // Same ClientId as straddress4_1
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x53)));    // Same as lease 1
        lease->valid_lft_ = 1832;
        lease->cltt_ = 627476;
        lease->subnet_id_ = 112;
        lease->fqdn_rev_ = false;
        lease->fqdn_fwd_ = true;
        lease->hostname_ = "myhost.example.com.";

    } else if (address == straddress4_[7]) {
        lease->hwaddr_ = vector<uint8_t>();             // Empty
        lease->client_id_ = ClientIdPtr();              // Empty
        lease->valid_lft_ = 7975;
        lease->cltt_ = 213876;
        lease->subnet_id_ = 19;
        lease->fqdn_rev_ = true;
        lease->fqdn_fwd_ = true;
        lease->hostname_ = "myhost.example.com.";

    } else {
        // Unknown address, return an empty pointer.
        lease.reset();

    }

    return (lease);
}

Lease6Ptr
GenericLeaseMgrTest::initializeLease6(std::string address) {
    Lease6Ptr lease(new Lease6());

    // Set the address of the lease
    lease->addr_ = IOAddress(address);

    // Initialize unused fields.
    lease->t1_ = 0;                             // Not saved
    lease->t2_ = 0;                             // Not saved
    lease->fixed_ = false;                      // Unused
    lease->comments_ = std::string("");         // Unused

    // Set other parameters.  For historical reasons, address 0 is not used.
    if (address == straddress6_[0]) {
        lease->type_ = leasetype6_[0];
        lease->prefixlen_ = 4;
        lease->iaid_ = 142;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x77)));
        lease->preferred_lft_ = 900;
        lease->valid_lft_ = 8677;
        lease->cltt_ = 168256;
        lease->subnet_id_ = 23;
        lease->fqdn_fwd_ = true;
        lease->fqdn_rev_ = true;
        lease->hostname_ = "myhost.example.com.";

    } else if (address == straddress6_[1]) {
        lease->type_ = leasetype6_[1];
        lease->prefixlen_ = 0;
        lease->iaid_ = 42;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x42)));
        lease->preferred_lft_ = 3600;
        lease->valid_lft_ = 3677;
        lease->cltt_ = 123456;
        lease->subnet_id_ = 73;
        lease->fqdn_fwd_ = false;
        lease->fqdn_rev_ = true;
        lease->hostname_ = "myhost.example.com.";

    } else if (address == straddress6_[2]) {
        lease->type_ = leasetype6_[2];
        lease->prefixlen_ = 7;
        lease->iaid_ = 89;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x3a)));
        lease->preferred_lft_ = 1800;
        lease->valid_lft_ = 5412;
        lease->cltt_ = 234567;
        lease->subnet_id_ = 73;                     // Same as lease 1
        lease->fqdn_fwd_ = false;
        lease->fqdn_rev_ = false;
        lease->hostname_ = "myhost.example.com.";

    } else if (address == straddress6_[3]) {
        lease->type_ = leasetype6_[3];
        lease->prefixlen_ = 28;
        lease->iaid_ = 0xfffffffe;
        vector<uint8_t> duid;
        for (uint8_t i = 31; i < 126; ++i) {
            duid.push_back(i);
        }
        lease->duid_ = DuidPtr(new DUID(duid));

        // The times used in the next tests are deliberately restricted - we
        // should be able to cope with valid lifetimes up to 0xffffffff.
        //  However, this will lead to overflows.
        // @TODO: test overflow conditions when code has been fixed
        lease->preferred_lft_ = 7200;
        lease->valid_lft_ = 7000;
        lease->cltt_ = 234567;
        lease->subnet_id_ = 37;
        lease->fqdn_fwd_ = true;
        lease->fqdn_rev_ = false;
        lease->hostname_ = "myhost.example.com.";

    } else if (address == straddress6_[4]) {
        // Same DUID and IAID as straddress6_1
        lease->type_ = leasetype6_[4];
        lease->prefixlen_ = 15;
        lease->iaid_ = 42;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x42)));
        lease->preferred_lft_ = 4800;
        lease->valid_lft_ = 7736;
        lease->cltt_ = 222456;
        lease->subnet_id_ = 671;
        lease->fqdn_fwd_ = true;
        lease->fqdn_rev_ = true;
        lease->hostname_ = "otherhost.example.com.";

    } else if (address == straddress6_[5]) {
        // Same DUID and IAID as straddress6_1
        lease->type_ = leasetype6_[5];
        lease->prefixlen_ = 24;
        lease->iaid_ = 42;                          // Same as lease 4
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x42)));
        // Same as lease 4
        lease->preferred_lft_ = 5400;
        lease->valid_lft_ = 7832;
        lease->cltt_ = 227476;
        lease->subnet_id_ = 175;
        lease->fqdn_fwd_ = false;
        lease->fqdn_rev_ = true;
        lease->hostname_ = "hostname.example.com.";

    } else if (address == straddress6_[6]) {
        // Same DUID as straddress6_1
        lease->type_ = leasetype6_[6];
        lease->prefixlen_ = 24;
        lease->iaid_ = 93;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x42)));
        // Same as lease 4
        lease->preferred_lft_ = 5400;
        lease->valid_lft_ = 1832;
        lease->cltt_ = 627476;
        lease->subnet_id_ = 112;
        lease->fqdn_fwd_ = false;
        lease->fqdn_rev_ = true;
        lease->hostname_ = "hostname.example.com.";

    } else if (address == straddress6_[7]) {
        // Same IAID as straddress6_1
        lease->type_ = leasetype6_[7];
        lease->prefixlen_ = 24;
        lease->iaid_ = 42;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0xe5)));
        lease->preferred_lft_ = 5600;
        lease->valid_lft_ = 7975;
        lease->cltt_ = 213876;
        lease->subnet_id_ = 19;
        lease->fqdn_fwd_ = false;
        lease->fqdn_rev_ = true;
        lease->hostname_ = "hostname.example.com.";

    } else {
        // Unknown address, return an empty pointer.
        lease.reset();

    }

    return (lease);
}

template <typename T>
void GenericLeaseMgrTest::checkLeasesDifferent(const std::vector<T>& leases) const {

    // Check they were created
    for (int i = 0; i < leases.size(); ++i) {
        ASSERT_TRUE(leases[i]);
    }

    // Check they are different
    for (int i = 0; i < (leases.size() - 1); ++i) {
        for (int j = (i + 1); j < leases.size(); ++j) {
            stringstream s;
            s << "Comparing leases " << i << " & " << j << " for equality";
            SCOPED_TRACE(s.str());
            EXPECT_TRUE(*leases[i] != *leases[j]);
        }
    }
}

vector<Lease4Ptr>
GenericLeaseMgrTest::createLeases4() {

    // Create leases for each address
    vector<Lease4Ptr> leases;
    for (int i = 0; i < straddress4_.size(); ++i) {
        leases.push_back(initializeLease4(straddress4_[i]));
    }
    EXPECT_EQ(8, leases.size());

    // Check all were created and that they are different.
    checkLeasesDifferent(leases);

    return (leases);
}

vector<Lease6Ptr>
GenericLeaseMgrTest::createLeases6() {

    // Create leases for each address
    vector<Lease6Ptr> leases;
    for (int i = 0; i < straddress6_.size(); ++i) {
        leases.push_back(initializeLease6(straddress6_[i]));
    }
    EXPECT_EQ(8, leases.size());

    // Check all were created and that they are different.
    checkLeasesDifferent(leases);

    return (leases);
}

void
GenericLeaseMgrTest::testGetLease4ClientId() {
    // Let's initialize a specific lease ...
    Lease4Ptr lease = initializeLease4(straddress4_[1]);
    EXPECT_TRUE(lmptr_->addLease(lease));
    Lease4Collection returned = lmptr_->getLease4(*lease->client_id_);

    ASSERT_EQ(1, returned.size());
    // We should retrieve our lease...
    detailCompareLease(lease, *returned.begin());
    lease = initializeLease4(straddress4_[2]);
    returned = lmptr_->getLease4(*lease->client_id_);

    ASSERT_EQ(0, returned.size());
}

void
GenericLeaseMgrTest::testGetLease4NullClientId() {
    // Let's initialize a specific lease ... But this time
    // We keep its client id for further lookup and
    // We clearly 'reset' it ...
    Lease4Ptr leaseA = initializeLease4(straddress4_[4]);
    ClientIdPtr client_id = leaseA->client_id_;
    leaseA->client_id_ = ClientIdPtr();
    ASSERT_TRUE(lmptr_->addLease(leaseA));

    Lease4Collection returned = lmptr_->getLease4(*client_id);
    // Shouldn't have our previous lease ...
    ASSERT_TRUE(returned.empty());

    // Add another lease with the non-NULL client id, and make sure that the
    // lookup will not break due to existence of both leases with non-NULL and
    // NULL client ids.
    Lease4Ptr leaseB = initializeLease4(straddress4_[0]);
    // Shouldn't throw any null pointer exception
    ASSERT_TRUE(lmptr_->addLease(leaseB));
    // Try to get the lease.
    returned = lmptr_->getLease4(*client_id);
    ASSERT_TRUE(returned.empty());

    // Let's make it more interesting and add another lease with NULL client id.
    Lease4Ptr leaseC = initializeLease4(straddress4_[5]);
    leaseC->client_id_.reset();
    ASSERT_TRUE(lmptr_->addLease(leaseC));
    returned = lmptr_->getLease4(*client_id);
    ASSERT_TRUE(returned.empty());

    // But getting the lease with non-NULL client id should be successful.
    returned = lmptr_->getLease4(*leaseB->client_id_);
    ASSERT_EQ(1, returned.size());
}

void
GenericLeaseMgrTest::testLease4NullClientId() {
    // Get the leases to be used for the test.
    vector<Lease4Ptr> leases = createLeases4();

    // Let's clear client-id pointers
    leases[1]->client_id_ = ClientIdPtr();
    leases[2]->client_id_ = ClientIdPtr();
    leases[3]->client_id_ = ClientIdPtr();

    // Start the tests.  Add three leases to the database, read them back and
    // check they are what we think they are.
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    EXPECT_TRUE(lmptr_->addLease(leases[2]));
    EXPECT_TRUE(lmptr_->addLease(leases[3]));
    lmptr_->commit();

    // Reopen the database to ensure that they actually got stored.
    reopen();

    Lease4Ptr l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    l_returned = lmptr_->getLease4(ioaddress4_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);

    l_returned = lmptr_->getLease4(ioaddress4_[3]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[3], l_returned);

    // Check that we can't add a second lease with the same address
    EXPECT_FALSE(lmptr_->addLease(leases[1]));

    // Check that we can get the lease by HWAddr
    HWAddr tmp(leases[2]->hwaddr_, HTYPE_ETHER);
    Lease4Collection returned = lmptr_->getLease4(tmp);
    ASSERT_EQ(1, returned.size());
    detailCompareLease(leases[2], *returned.begin());

    l_returned = lmptr_->getLease4(tmp, leases[2]->subnet_id_);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);

    // Check that we can update the lease
    // Modify some fields in lease 1 (not the address) and update it.
    ++leases[1]->subnet_id_;
    leases[1]->valid_lft_ *= 2;
    lmptr_->updateLease4(leases[1]);

    // ... and check that the lease is indeed updated
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Delete a lease, check that it's gone, and that we can't delete it
    // a second time.
    EXPECT_TRUE(lmptr_->deleteLease(ioaddress4_[1]));
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    EXPECT_FALSE(l_returned);
    EXPECT_FALSE(lmptr_->deleteLease(ioaddress4_[1]));

    // Check that the second address is still there.
    l_returned = lmptr_->getLease4(ioaddress4_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);
}

void
GenericLeaseMgrTest::testGetLease4HWAddr1() {
    // Let's initialize two different leases 4 and just add the first ...
    Lease4Ptr leaseA = initializeLease4(straddress4_[5]);
    HWAddr hwaddrA(leaseA->hwaddr_, HTYPE_ETHER);
    HWAddr hwaddrB(vector<uint8_t>(6, 0x80), HTYPE_ETHER);

    EXPECT_TRUE(lmptr_->addLease(leaseA));

    // we should not have a lease, with this MAC Addr
    Lease4Collection returned = lmptr_->getLease4(hwaddrB);
    ASSERT_EQ(0, returned.size());

    // But with this one
    returned = lmptr_->getLease4(hwaddrA);
    ASSERT_EQ(1, returned.size());
}

void
GenericLeaseMgrTest::testGetLease4HWAddr2() {
    // Get the leases to be used for the test and add to the database
    vector<Lease4Ptr> leases = createLeases4();
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the hardware address of lease 1
    /// @todo: Simply use HWAddr directly once 2589 is implemented
    HWAddr tmp(leases[1]->hwaddr_, HTYPE_ETHER);
    Lease4Collection returned = lmptr_->getLease4(tmp);

    // Should be three leases, matching leases[1], [3] and [5].
    ASSERT_EQ(3, returned.size());

    // Easiest way to check is to look at the addresses.
    vector<string> addresses;
    for (Lease4Collection::const_iterator i = returned.begin();
         i != returned.end(); ++i) {
        addresses.push_back((*i)->addr_.toText());
    }
    sort(addresses.begin(), addresses.end());
    EXPECT_EQ(straddress4_[1], addresses[0]);
    EXPECT_EQ(straddress4_[3], addresses[1]);
    EXPECT_EQ(straddress4_[5], addresses[2]);

    // Repeat test with just one expected match
    /// @todo: Simply use HWAddr directly once 2589 is implemented
    returned = lmptr_->getLease4(HWAddr(leases[2]->hwaddr_, HTYPE_ETHER));
    ASSERT_EQ(1, returned.size());
    detailCompareLease(leases[2], *returned.begin());

    // Check that an empty vector is valid
    EXPECT_TRUE(leases[7]->hwaddr_.empty());
    /// @todo: Simply use HWAddr directly once 2589 is implemented
    returned = lmptr_->getLease4(HWAddr(leases[7]->hwaddr_, HTYPE_ETHER));
    ASSERT_EQ(1, returned.size());
    detailCompareLease(leases[7], *returned.begin());

    // Try to get something with invalid hardware address
    vector<uint8_t> invalid(6, 0);
    returned = lmptr_->getLease4(invalid);
    EXPECT_EQ(0, returned.size());
}

void
GenericLeaseMgrTest::testGetLease4ClientIdHWAddrSubnetId() {
    Lease4Ptr leaseA = initializeLease4(straddress4_[4]);
    Lease4Ptr leaseB = initializeLease4(straddress4_[5]);
    Lease4Ptr leaseC = initializeLease4(straddress4_[6]);
    // Set NULL client id for one of the leases. This is to make sure that such
    // a lease may coexist with other leases with non NULL client id.
    leaseC->client_id_.reset();

    HWAddr hwaddrA(leaseA->hwaddr_, HTYPE_ETHER);
    HWAddr hwaddrB(leaseB->hwaddr_, HTYPE_ETHER);
    HWAddr hwaddrC(leaseC->hwaddr_, HTYPE_ETHER);
    EXPECT_TRUE(lmptr_->addLease(leaseA));
    EXPECT_TRUE(lmptr_->addLease(leaseB));
    EXPECT_TRUE(lmptr_->addLease(leaseC));
    // First case we should retrieve our lease
    Lease4Ptr lease = lmptr_->getLease4(*leaseA->client_id_, hwaddrA, leaseA->subnet_id_);
    detailCompareLease(lease, leaseA);
    // Retrieve the other lease.
    lease = lmptr_->getLease4(*leaseB->client_id_, hwaddrB, leaseB->subnet_id_);
    detailCompareLease(lease, leaseB);
    // The last lease has NULL client id so we will use a different getLease4 function
    // which doesn't require client id (just a hwaddr and subnet id).
    lease = lmptr_->getLease4(hwaddrC, leaseC->subnet_id_);
    detailCompareLease(lease, leaseC);

    // An attempt to retrieve the lease with non matching lease parameters should
    // result in NULL pointer being returned.
    lease = lmptr_->getLease4(*leaseA->client_id_, hwaddrB, leaseA->subnet_id_);
    EXPECT_FALSE(lease);
    lease = lmptr_->getLease4(*leaseA->client_id_, hwaddrA, leaseB->subnet_id_);
    EXPECT_FALSE(lease);
}

void
GenericLeaseMgrTest::testAddGetDelete6(bool check_t1_t2) {
    IOAddress addr("2001:db8:1::456");

    uint8_t llt[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    DuidPtr duid(new DUID(llt, sizeof(llt)));

    uint32_t iaid = 7; // just a number

    SubnetID subnet_id = 8; // just another number

    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, iaid, 100, 200, 50,
                               80, subnet_id));

    EXPECT_TRUE(lmptr_->addLease(lease));

    // should not be allowed to add a second lease with the same address
    EXPECT_FALSE(lmptr_->addLease(lease));

    Lease6Ptr x = lmptr_->getLease6(Lease::TYPE_NA,
                                    IOAddress("2001:db8:1::234"));
    EXPECT_EQ(Lease6Ptr(), x);

    x = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::456"));
    ASSERT_TRUE(x);

    EXPECT_EQ(x->addr_, addr);
    EXPECT_TRUE(*x->duid_ == *duid);
    EXPECT_EQ(x->iaid_, iaid);
    EXPECT_EQ(x->subnet_id_, subnet_id);

    // These are not important from lease management perspective, but
    // let's check them anyway.
    EXPECT_EQ(Lease::TYPE_NA, x->type_);
    EXPECT_EQ(100, x->preferred_lft_);
    EXPECT_EQ(200, x->valid_lft_);
    if (check_t1_t2) {
        // Backend supports T1,T2 storage: check the values
        EXPECT_EQ(50, x->t1_);
        EXPECT_EQ(80, x->t2_);
    } else {
        // Backend does not support storing, check that it returns 0s.
        EXPECT_EQ(0, x->t1_);
        EXPECT_EQ(0, x->t2_);
    }

    // Test getLease6(duid, iaid, subnet_id) - positive case
    Lease6Ptr y = lmptr_->getLease6(Lease::TYPE_NA, *duid, iaid, subnet_id);
    ASSERT_TRUE(y);
    EXPECT_TRUE(*y->duid_ == *duid);
    EXPECT_EQ(y->iaid_, iaid);
    EXPECT_EQ(y->addr_, addr);

    // Test getLease6(duid, iaid, subnet_id) - wrong iaid
    uint32_t invalid_iaid = 9; // no such iaid
    y = lmptr_->getLease6(Lease::TYPE_NA, *duid, invalid_iaid, subnet_id);
    EXPECT_FALSE(y);

    uint32_t invalid_subnet_id = 999;
    y = lmptr_->getLease6(Lease::TYPE_NA, *duid, iaid, invalid_subnet_id);
    EXPECT_FALSE(y);

    // truncated duid
    DuidPtr invalid_duid(new DUID(llt, sizeof(llt) - 1));
    y = lmptr_->getLease6(Lease::TYPE_NA, *invalid_duid, iaid, subnet_id);
    EXPECT_FALSE(y);

    // should return false - there's no such address
    EXPECT_FALSE(lmptr_->deleteLease(IOAddress("2001:db8:1::789")));

    // this one should succeed
    EXPECT_TRUE(lmptr_->deleteLease(IOAddress("2001:db8:1::456")));

    // after the lease is deleted, it should really be gone
    x = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::456"));
    EXPECT_FALSE(x);

    // Reopen the lease storage to make sure that lease is gone from the
    // persistent storage.
    reopen(V6);
    x = lmptr_->getLease6(Lease::TYPE_NA, IOAddress("2001:db8:1::456"));
    EXPECT_FALSE(x);
}

void
GenericLeaseMgrTest::testMaxDate4() {
    // Get the leases to be used for the test.
    vector<Lease4Ptr> leases = createLeases4();
    Lease4Ptr lease = leases[1];

    // Set valid_lft_ to 1 day, cllt_ to max time. This should make expire
    // time too large to store.
    lease->valid_lft_ = 24*60*60;
    lease->cltt_ = LeaseMgr::MAX_DB_TIME;

    // Insert should throw.
    ASSERT_THROW(lmptr_->addLease(leases[1]), DbOperationError);

    // Set valid_lft_ to 0, which should make expire time small enough to
    // store and try again.
    lease->valid_lft_ = 0;
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    Lease4Ptr l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);
}

void
GenericLeaseMgrTest::testBasicLease4() {
    // Get the leases to be used for the test.
    vector<Lease4Ptr> leases = createLeases4();

    // Start the tests.  Add three leases to the database, read them back and
    // check they are what we think they are.
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    EXPECT_TRUE(lmptr_->addLease(leases[2]));
    EXPECT_TRUE(lmptr_->addLease(leases[3]));
    lmptr_->commit();

    // Reopen the database to ensure that they actually got stored.
    reopen(V4);

    Lease4Ptr l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    l_returned = lmptr_->getLease4(ioaddress4_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);

    l_returned = lmptr_->getLease4(ioaddress4_[3]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[3], l_returned);

    // Check that we can't add a second lease with the same address
    EXPECT_FALSE(lmptr_->addLease(leases[1]));

    // Delete a lease, check that it's gone, and that we can't delete it
    // a second time.
    EXPECT_TRUE(lmptr_->deleteLease(ioaddress4_[1]));
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    EXPECT_FALSE(l_returned);
    EXPECT_FALSE(lmptr_->deleteLease(ioaddress4_[1]));

    // Check that the second address is still there.
    l_returned = lmptr_->getLease4(ioaddress4_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);

    reopen(V4);

    // The deleted lease should be still gone after we re-read leases from
    // persistent storage.
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    EXPECT_FALSE(l_returned);

    l_returned = lmptr_->getLease4(ioaddress4_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);

    l_returned = lmptr_->getLease4(ioaddress4_[3]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[3], l_returned);

    // Update some FQDN data, so as we can check that update in
    // persistent storage works as expected.
    leases[2]->hostname_ = "memfile.example.com.";
    leases[2]->fqdn_rev_ = true;

    ASSERT_NO_THROW(lmptr_->updateLease4(leases[2]));

    reopen(V4);

    // The lease should be now updated in the storage.
    l_returned = lmptr_->getLease4(ioaddress4_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);

    l_returned = lmptr_->getLease4(ioaddress4_[3]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[3], l_returned);
}


void
GenericLeaseMgrTest::testBasicLease6() {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();

    // Start the tests.  Add three leases to the database, read them back and
    // check they are what we think they are.
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    EXPECT_TRUE(lmptr_->addLease(leases[2]));
    EXPECT_TRUE(lmptr_->addLease(leases[3]));
    lmptr_->commit();

    // Reopen the database to ensure that they actually got stored.
    reopen(V6);

    Lease6Ptr l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    l_returned = lmptr_->getLease6(leasetype6_[2], ioaddress6_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);

    l_returned = lmptr_->getLease6(leasetype6_[3], ioaddress6_[3]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[3], l_returned);

    // Check that we can't add a second lease with the same address
    EXPECT_FALSE(lmptr_->addLease(leases[1]));

    // Delete a lease, check that it's gone, and that we can't delete it
    // a second time.
    EXPECT_TRUE(lmptr_->deleteLease(ioaddress6_[1]));
    l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    EXPECT_FALSE(l_returned);
    EXPECT_FALSE(lmptr_->deleteLease(ioaddress6_[1]));

    // Check that the second address is still there.
    l_returned = lmptr_->getLease6(leasetype6_[2], ioaddress6_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);

    reopen(V6);

    // The deleted lease should be still gone after we re-read leases from
    // persistent storage.
    l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    EXPECT_FALSE(l_returned);

    // Check that the second address is still there.
    l_returned = lmptr_->getLease6(leasetype6_[2], ioaddress6_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);

    // Update some FQDN data, so as we can check that update in
    // persistent storage works as expected.
    leases[2]->hostname_ = "memfile.example.com.";
    leases[2]->fqdn_rev_ = true;

    ASSERT_NO_THROW(lmptr_->updateLease6(leases[2]));

    reopen(V6);

    // The lease should be now updated in the storage.
    l_returned = lmptr_->getLease6(leasetype6_[2], ioaddress6_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);
}

void
GenericLeaseMgrTest::testMaxDate6() {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();
    Lease6Ptr lease = leases[1];

    // Set valid_lft_ to 1 day, cllt_ to max time. This should make expire
    // time too large to store.
    lease->valid_lft_ = 24*60*60;
    lease->cltt_ = LeaseMgr::MAX_DB_TIME;

    // Insert should throw.
    ASSERT_THROW(lmptr_->addLease(leases[1]), DbOperationError);

    // Set valid_lft_ to 0, which should make expire time small enough to
    // store and try again.
    lease->valid_lft_ = 0;
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    Lease6Ptr l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);
}

void
GenericLeaseMgrTest::testLease4InvalidHostname() {
    // Get the leases to be used for the test.
    vector<Lease4Ptr> leases = createLeases4();

    // Create a dummy hostname, consisting of 255 characters.
    leases[1]->hostname_.assign(255, 'a');
    ASSERT_TRUE(lmptr_->addLease(leases[1]));

    // The new lease must be in the database.
    Lease4Ptr l_returned = lmptr_->getLease4(ioaddress4_[1]);
    detailCompareLease(leases[1], l_returned);

    // Let's delete the lease, so as we can try to add it again with
    // invalid hostname.
    EXPECT_TRUE(lmptr_->deleteLease(ioaddress4_[1]));

    // Create a hostname with 256 characters. It should not be accepted.
    leases[1]->hostname_.assign(256, 'a');
    EXPECT_THROW(lmptr_->addLease(leases[1]), DbOperationError);
}

/// @brief Verify that too long hostname for Lease6 is not accepted.
void
GenericLeaseMgrTest::testLease6InvalidHostname() {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();

    // Create a dummy hostname, consisting of 255 characters.
    leases[1]->hostname_.assign(255, 'a');
    ASSERT_TRUE(lmptr_->addLease(leases[1]));

    // The new lease must be in the database.
    Lease6Ptr l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    detailCompareLease(leases[1], l_returned);

    // Let's delete the lease, so as we can try to add it again with
    // invalid hostname.
    EXPECT_TRUE(lmptr_->deleteLease(ioaddress6_[1]));

    // Create a hostname with 256 characters. It should not be accepted.
    leases[1]->hostname_.assign(256, 'a');
    EXPECT_THROW(lmptr_->addLease(leases[1]), DbOperationError);
}

void
GenericLeaseMgrTest::testGetLease4HWAddrSize() {
    // Create leases, although we need only one.
    vector<Lease4Ptr> leases = createLeases4();

    // Now add leases with increasing hardware address size.
    for (uint8_t i = 0; i <= HWAddr::MAX_HWADDR_LEN; ++i) {
        leases[1]->hwaddr_.resize(i, i);
        EXPECT_TRUE(lmptr_->addLease(leases[1]));
        /// @todo: Simply use HWAddr directly once 2589 is implemented
        Lease4Collection returned =
            lmptr_->getLease4(HWAddr(leases[1]->hwaddr_, HTYPE_ETHER));

        ASSERT_EQ(1, returned.size());
        detailCompareLease(leases[1], *returned.begin());
        (void) lmptr_->deleteLease(leases[1]->addr_);
    }

    // Database should not let us add one that is too big
    // (The 42 is a random value put in each byte of the address.)
    /// @todo: 2589 will make this test impossible
    leases[1]->hwaddr_.resize(HWAddr::MAX_HWADDR_LEN + 100, 42);
    EXPECT_THROW(lmptr_->addLease(leases[1]), isc::dhcp::DbOperationError);
}

void
GenericLeaseMgrTest::testGetLease4HWAddrSubnetId() {
    // Get the leases to be used for the test and add to the database
    vector<Lease4Ptr> leases = createLeases4();
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the hardware address of lease 1 and
    // subnet ID of lease 1.  Result should be a single lease - lease 1.
    /// @todo: Simply use HWAddr directly once 2589 is implemented
    Lease4Ptr returned = lmptr_->getLease4(HWAddr(leases[1]->hwaddr_,
        HTYPE_ETHER), leases[1]->subnet_id_);

    ASSERT_TRUE(returned);
    detailCompareLease(leases[1], returned);

    // Try for a match to the hardware address of lease 1 and the wrong
    // subnet ID.
    /// @todo: Simply use HWAddr directly once 2589 is implemented
    returned = lmptr_->getLease4(HWAddr(leases[1]->hwaddr_, HTYPE_ETHER),
                                 leases[1]->subnet_id_ + 1);
    EXPECT_FALSE(returned);

    // Try for a match to the subnet ID of lease 1 (and lease 4) but
    // the wrong hardware address.
    vector<uint8_t> invalid_hwaddr(15, 0x77);
    /// @todo: Simply use HWAddr directly once 2589 is implemented
    returned = lmptr_->getLease4(HWAddr(invalid_hwaddr, HTYPE_ETHER),
                                 leases[1]->subnet_id_);
    EXPECT_FALSE(returned);

    // Try for a match to an unknown hardware address and an unknown
    // subnet ID.
    /// @todo: Simply use HWAddr directly once 2589 is implemented
    returned = lmptr_->getLease4(HWAddr(invalid_hwaddr, HTYPE_ETHER),
                                 leases[1]->subnet_id_ + 1);
    EXPECT_FALSE(returned);

    // Add a second lease with the same values as the first and check that
    // an attempt to access the database by these parameters throws a
    // "multiple records" exception. (We expect there to be only one record
    // with that combination, so getting them via getLeaseX() (as opposed
    // to getLeaseXCollection() should throw an exception.)
    EXPECT_TRUE(lmptr_->deleteLease(leases[2]->addr_));
    leases[1]->addr_ = leases[2]->addr_;
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    /// @todo: Simply use HWAddr directly once 2589 is implemented
    EXPECT_THROW(returned = lmptr_->getLease4(HWAddr(leases[1]->hwaddr_,
                                                    HTYPE_ETHER),
                                             leases[1]->subnet_id_),
                 isc::dhcp::MultipleRecords);


}

void
GenericLeaseMgrTest::testGetLease4HWAddrSubnetIdSize() {
    // Create leases, although we need only one.
    vector<Lease4Ptr> leases = createLeases4();

    // Now add leases with increasing hardware address size and check
    // that they can be retrieved.
    for (uint8_t i = 0; i <= HWAddr::MAX_HWADDR_LEN; ++i) {
        leases[1]->hwaddr_.resize(i, i);
        EXPECT_TRUE(lmptr_->addLease(leases[1]));
        /// @todo: Simply use HWAddr directly once 2589 is implemented
        Lease4Ptr returned = lmptr_->getLease4(HWAddr(leases[1]->hwaddr_,
                                                      HTYPE_ETHER),
                                               leases[1]->subnet_id_);
        ASSERT_TRUE(returned);
        detailCompareLease(leases[1], returned);
        (void) lmptr_->deleteLease(leases[1]->addr_);
    }

    // Database should not let us add one that is too big
    // (The 42 is a random value put in each byte of the address.)
    leases[1]->hwaddr_.resize(HWAddr::MAX_HWADDR_LEN + 100, 42);
    EXPECT_THROW(lmptr_->addLease(leases[1]), isc::dhcp::DbOperationError);
}

void
GenericLeaseMgrTest::testGetLease4ClientId2() {
    // Get the leases to be used for the test and add to the database
    vector<Lease4Ptr> leases = createLeases4();
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the Client ID address of lease 1
    Lease4Collection returned = lmptr_->getLease4(*leases[1]->client_id_);

    // Should be four leases, matching leases[1], [4], [5] and [6].
    ASSERT_EQ(4, returned.size());

    // Easiest way to check is to look at the addresses.
    vector<string> addresses;
    for (Lease4Collection::const_iterator i = returned.begin();
         i != returned.end(); ++i) {
        addresses.push_back((*i)->addr_.toText());
    }
    sort(addresses.begin(), addresses.end());
    EXPECT_EQ(straddress4_[1], addresses[0]);
    EXPECT_EQ(straddress4_[4], addresses[1]);
    EXPECT_EQ(straddress4_[5], addresses[2]);
    EXPECT_EQ(straddress4_[6], addresses[3]);

    // Repeat test with just one expected match
    returned = lmptr_->getLease4(*leases[3]->client_id_);
    ASSERT_EQ(1, returned.size());
    detailCompareLease(leases[3], *returned.begin());

    // Check that client-id is NULL
    EXPECT_FALSE(leases[7]->client_id_);
    HWAddr tmp(leases[7]->hwaddr_, HTYPE_ETHER);
    returned = lmptr_->getLease4(tmp);
    ASSERT_EQ(1, returned.size());
    detailCompareLease(leases[7], *returned.begin());

    // Try to get something with invalid client ID
    const uint8_t invalid_data[] = {0, 0, 0};
    ClientId invalid(invalid_data, sizeof(invalid_data));
    returned = lmptr_->getLease4(invalid);
    EXPECT_EQ(0, returned.size());
}

void
GenericLeaseMgrTest::testGetLease4ClientIdSize() {
    // Create leases, although we need only one.
    vector<Lease4Ptr> leases = createLeases4();

    // Now add leases with increasing Client ID size can be retrieved.
    // For speed, go from 0 to 128 is steps of 16.
    // Intermediate client_id_max is to overcome problem if
    // ClientId::MAX_CLIENT_ID_LEN is used in an EXPECT_EQ.
    int client_id_max = ClientId::MAX_CLIENT_ID_LEN;
    EXPECT_EQ(128, client_id_max);

    int client_id_min = ClientId::MIN_CLIENT_ID_LEN;
    EXPECT_EQ(2, client_id_min); // See RFC2132, section 9.14

    for (uint8_t i = client_id_min; i <= client_id_max; i += 16) {
        vector<uint8_t> clientid_vec(i, i);
        leases[1]->client_id_.reset(new ClientId(clientid_vec));
        EXPECT_TRUE(lmptr_->addLease(leases[1]));
        Lease4Collection returned = lmptr_->getLease4(*leases[1]->client_id_);
        ASSERT_TRUE(returned.size() == 1);
        detailCompareLease(leases[1], *returned.begin());
        (void) lmptr_->deleteLease(leases[1]->addr_);
    }

    // Don't bother to check client IDs longer than the maximum -
    // these cannot be constructed, and that limitation is tested
    // in the DUID/Client ID unit tests.
}

void
GenericLeaseMgrTest::testGetLease4ClientIdSubnetId() {
    // Get the leases to be used for the test and add to the database
    vector<Lease4Ptr> leases = createLeases4();
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the client ID of lease 1 and
    // subnet ID of lease 1.  Result should be a single lease - lease 1.
    Lease4Ptr returned = lmptr_->getLease4(*leases[1]->client_id_,
                                           leases[1]->subnet_id_);
    ASSERT_TRUE(returned);
    detailCompareLease(leases[1], returned);

    // Try for a match to the client ID of lease 1 and the wrong
    // subnet ID.
    returned = lmptr_->getLease4(*leases[1]->client_id_,
                                 leases[1]->subnet_id_ + 1);
    EXPECT_FALSE(returned);

    // Try for a match to the subnet ID of lease 1 (and lease 4) but
    // the wrong client ID
    const uint8_t invalid_data[] = {0, 0, 0};
    ClientId invalid(invalid_data, sizeof(invalid_data));
    returned = lmptr_->getLease4(invalid, leases[1]->subnet_id_);
    EXPECT_FALSE(returned);

    // Try for a match to an unknown hardware address and an unknown
    // subnet ID.
    returned = lmptr_->getLease4(invalid, leases[1]->subnet_id_ + 1);
    EXPECT_FALSE(returned);
}

void
GenericLeaseMgrTest::testGetLeases6DuidIaid() {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();
    ASSERT_LE(6, leases.size());    // Expect to access leases 0 through 5

    // Add them to the database
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the DUID and IAID of lease[1].
    Lease6Collection returned = lmptr_->getLeases6(leasetype6_[1],
                                                   *leases[1]->duid_,
                                                   leases[1]->iaid_);

    // Should be two leases, matching leases[1] and [4].
    ASSERT_EQ(2, returned.size());

    // Easiest way to check is to look at the addresses.
    vector<string> addresses;
    for (Lease6Collection::const_iterator i = returned.begin();
         i != returned.end(); ++i) {
        addresses.push_back((*i)->addr_.toText());
    }
    sort(addresses.begin(), addresses.end());
    EXPECT_EQ(straddress6_[1], addresses[0]);
    EXPECT_EQ(straddress6_[4], addresses[1]);

    // Check that nothing is returned when either the IAID or DUID match
    // nothing.
    returned = lmptr_->getLeases6(leasetype6_[1], *leases[1]->duid_,
                                  leases[1]->iaid_ + 1);
    EXPECT_EQ(0, returned.size());

    // Alter the leases[1] DUID to match nothing in the database.
    vector<uint8_t> duid_vector = leases[1]->duid_->getDuid();
    ++duid_vector[0];
    DUID new_duid(duid_vector);
    returned = lmptr_->getLeases6(leasetype6_[1], new_duid, leases[1]->iaid_);
    EXPECT_EQ(0, returned.size());
}

void
GenericLeaseMgrTest::testGetLeases6DuidSize() {
    // Create leases, although we need only one.
    vector<Lease6Ptr> leases = createLeases6();

    // Now add leases with increasing DUID size can be retrieved.
    // For speed, go from 0 to 128 is steps of 16.
    int duid_max = DUID::MAX_DUID_LEN;
    EXPECT_EQ(128, duid_max);

    int duid_min = DUID::MIN_DUID_LEN;
    EXPECT_EQ(1, duid_min);

    for (uint8_t i = duid_min; i <= duid_max; i += 16) {
        vector<uint8_t> duid_vec(i, i);
        leases[1]->duid_.reset(new DUID(duid_vec));
        EXPECT_TRUE(lmptr_->addLease(leases[1]));
        Lease6Collection returned = lmptr_->getLeases6(leasetype6_[1],
                                                       *leases[1]->duid_,
                                                       leases[1]->iaid_);
        ASSERT_EQ(1, returned.size());
        detailCompareLease(leases[1], *returned.begin());
        (void) lmptr_->deleteLease(leases[1]->addr_);
    }

    // Don't bother to check DUIDs longer than the maximum - these cannot be
    // constructed, and that limitation is tested in the DUID/Client ID unit
    // tests.

}

void
GenericLeaseMgrTest::testLease6LeaseTypeCheck() {
    Lease6Ptr empty_lease(new Lease6());

    DuidPtr duid(new DUID(vector<uint8_t>(8, 0x77)));

    // Initialize unused fields.
    empty_lease->t1_ = 0;                             // Not saved
    empty_lease->t2_ = 0;                             // Not saved
    empty_lease->fixed_ = false;                      // Unused
    empty_lease->comments_ = std::string("");         // Unused
    empty_lease->iaid_ = 142;
    empty_lease->duid_ = DuidPtr(new DUID(*duid));
    empty_lease->subnet_id_ = 23;
    empty_lease->preferred_lft_ = 100;
    empty_lease->valid_lft_ = 100;
    empty_lease->cltt_ = 100;
    empty_lease->fqdn_fwd_ = true;
    empty_lease->fqdn_rev_ = true;
    empty_lease->hostname_ = "myhost.example.com.";
    empty_lease->prefixlen_ = 4;

    // Make Two leases per lease type, all with the same  DUID, IAID but
    // alternate the subnet_ids.
    vector<Lease6Ptr> leases;
    for (int i = 0; i < 6; ++i) {
          Lease6Ptr lease(new Lease6(*empty_lease));
          lease->type_ = leasetype6_[i / 2];
          lease->addr_ = IOAddress(straddress6_[i]);
          lease->subnet_id_ += (i % 2);
          leases.push_back(lease);
          EXPECT_TRUE(lmptr_->addLease(lease));
     }

    // Verify getting a single lease by type and address.
    for (int i = 0; i < 6; ++i) {
        // Look for exact match for each lease type.
        Lease6Ptr returned = lmptr_->getLease6(leasetype6_[i / 2],
                                               leases[i]->addr_);
        // We should match one per lease type.
        ASSERT_TRUE(returned);
        EXPECT_TRUE(*returned == *leases[i]);

        // Same address but wrong lease type, should not match.
        returned = lmptr_->getLease6(leasetype6_[i / 2 + 1], leases[i]->addr_);
        ASSERT_FALSE(returned);
    }

    // Verify getting a collection of leases by type, DUID, and IAID.
    // Iterate over the lease types, asking for leases based on
    // lease type, DUID, and IAID.
    for (int i = 0; i < 3; ++i) {
        Lease6Collection returned = lmptr_->getLeases6(leasetype6_[i],
                                                       *duid, 142);
        // We should match two per lease type.
        ASSERT_EQ(2, returned.size());

        // Collection order returned is not guaranteed.
        // Easiest way to check is to look at the addresses.
        vector<string> addresses;
        for (Lease6Collection::const_iterator it = returned.begin();
            it != returned.end(); ++it) {
            addresses.push_back((*it)->addr_.toText());
        }
        sort(addresses.begin(), addresses.end());

        // Now verify that the lease addresses match.
        EXPECT_EQ(addresses[0], leases[(i * 2)]->addr_.toText());
        EXPECT_EQ(addresses[1], leases[(i * 2 + 1)]->addr_.toText());
    }

    // Verify getting a collection of leases by type, DUID, IAID, and subnet id.
    // Iterate over the lease types, asking for leases based on
    // lease type, DUID, IAID, and subnet_id.
    for (int i = 0; i < 3; ++i) {
        Lease6Collection returned = lmptr_->getLeases6(leasetype6_[i],
                                                   *duid, 142, 23);
        // We should match one per lease type.
        ASSERT_EQ(1, returned.size());
        EXPECT_TRUE(*(returned[0]) == *leases[i * 2]);
    }

    // Verify getting a single lease by type, duid, iad, and subnet id.
    for (int i = 0; i < 6; ++i) {
        Lease6Ptr returned = lmptr_->getLease6(leasetype6_[i / 2],
                                                *duid, 142, (23 + (i % 2)));
        // We should match one per lease type.
        ASSERT_TRUE(returned);
        EXPECT_TRUE(*returned == *leases[i]);
    }
}

void
GenericLeaseMgrTest::testGetLease6DuidIaidSubnetId() {
    // Get the leases to be used for the test and add them to the database.
    vector<Lease6Ptr> leases = createLeases6();
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the DUID and IAID of lease[1].
    Lease6Ptr returned = lmptr_->getLease6(leasetype6_[1], *leases[1]->duid_,
                                           leases[1]->iaid_,
                                           leases[1]->subnet_id_);
    ASSERT_TRUE(returned);
    EXPECT_TRUE(*returned == *leases[1]);

    // Modify each of the three parameters (DUID, IAID, Subnet ID) and
    // check that nothing is returned.
    returned = lmptr_->getLease6(leasetype6_[1], *leases[1]->duid_,
                                 leases[1]->iaid_ + 1, leases[1]->subnet_id_);
    EXPECT_FALSE(returned);

    returned = lmptr_->getLease6(leasetype6_[1], *leases[1]->duid_,
                                 leases[1]->iaid_, leases[1]->subnet_id_ + 1);
    EXPECT_FALSE(returned);

    // Alter the leases[1] DUID to match nothing in the database.
    vector<uint8_t> duid_vector = leases[1]->duid_->getDuid();
    ++duid_vector[0];
    DUID new_duid(duid_vector);
    returned = lmptr_->getLease6(leasetype6_[1], new_duid, leases[1]->iaid_,
                                 leases[1]->subnet_id_);
    EXPECT_FALSE(returned);
}

/// @brief Checks that getLease6() works with different DUID sizes
void
GenericLeaseMgrTest::testGetLease6DuidIaidSubnetIdSize() {

    // Create leases, although we need only one.
    vector<Lease6Ptr> leases = createLeases6();

    // Now add leases with increasing DUID size can be retrieved.
    // For speed, go from 0 to 128 is steps of 16.
    int duid_max = DUID::MAX_DUID_LEN;
    EXPECT_EQ(128, duid_max);

    int duid_min = DUID::MIN_DUID_LEN;
    EXPECT_EQ(1, duid_min);

    for (uint8_t i = duid_min; i <= duid_max; i += 16) {
        vector<uint8_t> duid_vec(i, i);
        leases[1]->duid_.reset(new DUID(duid_vec));
        EXPECT_TRUE(lmptr_->addLease(leases[1]));
        Lease6Ptr returned = lmptr_->getLease6(leasetype6_[1], *leases[1]->duid_,
                                               leases[1]->iaid_,
                                               leases[1]->subnet_id_);
        ASSERT_TRUE(returned);
        detailCompareLease(leases[1], returned);
        (void) lmptr_->deleteLease(leases[1]->addr_);
    }

    // Don't bother to check DUIDs longer than the maximum - these cannot be
    // constructed, and that limitation is tested in the DUID/Client ID unit
    // tests.
}

void
GenericLeaseMgrTest::testUpdateLease4() {
    // Get the leases to be used for the test and add them to the database.
    vector<Lease4Ptr> leases = createLeases4();
    for (int i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Modify some fields in lease 1 (not the address) and update it.
    ++leases[1]->subnet_id_;
    leases[1]->valid_lft_ *= 2;
    leases[1]->hostname_ = "modified.hostname.";
    leases[1]->fqdn_fwd_ = !leases[1]->fqdn_fwd_;
    leases[1]->fqdn_rev_ = !leases[1]->fqdn_rev_;;
    lmptr_->updateLease4(leases[1]);

    // ... and check what is returned is what is expected.
    Lease4Ptr l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Alter the lease again and check.
    ++leases[1]->subnet_id_;
    leases[1]->cltt_ += 6;
    lmptr_->updateLease4(leases[1]);

    // Explicitly clear the returned pointer before getting new data to ensure
    // that the new data is returned.
    l_returned.reset();
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Check we can do an update without changing data.
    lmptr_->updateLease4(leases[1]);
    l_returned.reset();
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Try to update the lease with the too long hostname.
    leases[1]->hostname_.assign(256, 'a');
    EXPECT_THROW(lmptr_->updateLease4(leases[1]), isc::dhcp::DbOperationError);

    // Try updating a lease not in the database.
    lmptr_->deleteLease(ioaddress4_[2]);
    EXPECT_THROW(lmptr_->updateLease4(leases[2]), isc::dhcp::NoSuchLease);
}

void
GenericLeaseMgrTest::testUpdateLease6() {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();
    ASSERT_LE(3, leases.size());    // Expect to access leases 0 through 2

    // Add a lease to the database and check that the lease is there.
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    lmptr_->commit();

    Lease6Ptr l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Modify some fields in lease 1 (not the address) and update it.
    ++leases[1]->iaid_;
    leases[1]->type_ = Lease::TYPE_PD;
    leases[1]->valid_lft_ *= 2;
    leases[1]->hostname_ = "modified.hostname.v6.";
    leases[1]->fqdn_fwd_ = !leases[1]->fqdn_fwd_;
    leases[1]->fqdn_rev_ = !leases[1]->fqdn_rev_;;
    lmptr_->updateLease6(leases[1]);
    lmptr_->commit();

    // ... and check what is returned is what is expected.
    l_returned.reset();
    l_returned = lmptr_->getLease6(Lease::TYPE_PD, ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Alter the lease again and check.
    ++leases[1]->iaid_;
    leases[1]->type_ = Lease::TYPE_TA;
    leases[1]->cltt_ += 6;
    leases[1]->prefixlen_ = 93;
    lmptr_->updateLease6(leases[1]);

    l_returned.reset();
    l_returned = lmptr_->getLease6(Lease::TYPE_TA, ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Check we can do an update without changing data.
    lmptr_->updateLease6(leases[1]);
    l_returned.reset();
    l_returned = lmptr_->getLease6(Lease::TYPE_TA, ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Try to update the lease with the too long hostname.
    leases[1]->hostname_.assign(256, 'a');
    EXPECT_THROW(lmptr_->updateLease6(leases[1]), isc::dhcp::DbOperationError);

    // Try updating a lease not in the database.
    EXPECT_THROW(lmptr_->updateLease6(leases[2]), isc::dhcp::NoSuchLease);
}

void
GenericLeaseMgrTest::testRecreateLease4() {
    // Create a lease.
    std::vector<Lease4Ptr> leases = createLeases4();
    // Copy the lease so as we can freely modify it.
    Lease4Ptr lease(new Lease4(*leases[0]));

    // Add a lease.
    EXPECT_TRUE(lmptr_->addLease(lease));
    lmptr_->commit();

    // Check that the lease has been successfuly added.
    Lease4Ptr l_returned = lmptr_->getLease4(ioaddress4_[0]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(lease, l_returned);

    // Delete a lease, check that it's gone.
    EXPECT_TRUE(lmptr_->deleteLease(ioaddress4_[0]));
    EXPECT_FALSE(lmptr_->getLease4(ioaddress4_[0]));

    // Modify the copy of the lease. Increasing values or negating them ensures
    // that they are really modified, because we will never get the same values.
    ++lease->subnet_id_;
    ++lease->valid_lft_;
    lease->fqdn_fwd_ = !lease->fqdn_fwd_;
    // Make sure that the lease has been really modified.
    ASSERT_NE(*lease, *leases[0]);
    // Add the updated lease.
    EXPECT_TRUE(lmptr_->addLease(lease));
    lmptr_->commit();

    // Reopen the lease database, so as the lease is re-read.
    reopen(V4);

    // The lease in the database should be modified.
    l_returned = lmptr_->getLease4(ioaddress4_[0]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(lease, l_returned);
}

void
GenericLeaseMgrTest::testRecreateLease6() {
    // Create a lease.
    std::vector<Lease6Ptr> leases = createLeases6();
    // Copy the lease so as we can freely modify it.
    Lease6Ptr lease(new Lease6(*leases[0]));

    // Add a lease.
    EXPECT_TRUE(lmptr_->addLease(lease));
    lmptr_->commit();

    // Check that the lease has been successfuly added.
    Lease6Ptr l_returned = lmptr_->getLease6(Lease::TYPE_NA, ioaddress6_[0]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(lease, l_returned);

    // Delete a lease, check that it's gone.
    EXPECT_TRUE(lmptr_->deleteLease(ioaddress6_[0]));
    EXPECT_FALSE(lmptr_->getLease6(Lease::TYPE_NA, ioaddress6_[0]));

    // Modify the copy of the lease. Increasing values or negating them ensures
    // that they are really modified, because we will never get the same values.
    ++lease->subnet_id_;
    ++lease->valid_lft_;
    lease->fqdn_fwd_ = !lease->fqdn_fwd_;
    // Make sure that the lease has been really modified.
    ASSERT_NE(*lease, *leases[0]);
    // Add the updated lease.
    EXPECT_TRUE(lmptr_->addLease(lease));
    lmptr_->commit();

    // Reopen the lease database, so as the lease is re-read.
    reopen(V6);

    // The lease in the database should be modified.
    l_returned = lmptr_->getLease6(Lease::TYPE_NA, ioaddress6_[0]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(lease, l_returned);
}

void
GenericLeaseMgrTest::testNullDuid() {
    // Create leases, although we need only one.
    vector<Lease6Ptr> leases = createLeases6();

    // Set DUID to empty pointer.
    leases[1]->duid_.reset();

    // Insert should throw.
    ASSERT_THROW(lmptr_->addLease(leases[1]), DbOperationError);
}


}; // namespace test
}; // namespace dhcp
}; // namespace isc
