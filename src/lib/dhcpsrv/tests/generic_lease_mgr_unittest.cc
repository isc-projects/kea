// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <database/database_connection.h>
#include <database/db_exceptions.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcpsrv_exceptions.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/tests/generic_lease_mgr_unittest.h>
#include <dhcpsrv/testutils/test_utils.h>
#include <exceptions/exceptions.h>
#include <stats/stats_mgr.h>
#include <testutils/gtest_utils.h>

#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>

#include <gtest/gtest.h>

#include <functional>
#include <limits>
#include <sstream>

using namespace std;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;
namespace ph = std::placeholders;

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

    // Set other parameters.  For historical reasons, address 0 is not used.
    if (address == straddress4_[0]) {
        lease->hwaddr_.reset(new HWAddr(vector<uint8_t>(6, 0x08), HTYPE_ETHER));
        lease->client_id_ = ClientIdPtr(new ClientId(vector<uint8_t>(8, 0x42)));
        lease->valid_lft_ = 8677;
        lease->cltt_ = 168256;
        lease->updateCurrentExpirationTime();
        lease->subnet_id_ = 23;
        lease->fqdn_rev_ = true;
        lease->fqdn_fwd_ = false;
        lease->hostname_ = "myhost.example.com.";

    } else if (address == straddress4_[1]) {
        lease->hwaddr_.reset(new HWAddr(vector<uint8_t>(6, 0x19), HTYPE_ETHER));
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x53)));
        lease->valid_lft_ = 3677;
        lease->cltt_ = 123456;
        lease->updateCurrentExpirationTime();
        lease->subnet_id_ = 73;
        lease->fqdn_rev_ = true;
        lease->fqdn_fwd_ = true;
        lease->hostname_ = "myhost.example.com.";

    } else if (address == straddress4_[2]) {
        lease->hwaddr_.reset(new HWAddr(vector<uint8_t>(6, 0x2a), HTYPE_ETHER));
        lease->client_id_ = ClientIdPtr(new ClientId(vector<uint8_t>(8, 0x64)));
        lease->valid_lft_ = 5412;
        lease->cltt_ = 234567;
        lease->updateCurrentExpirationTime();
        lease->subnet_id_ = 73;                         // Same as lease 1
        lease->fqdn_rev_ = false;
        lease->fqdn_fwd_ = false;
        lease->hostname_ = "";

    } else if (address == straddress4_[3]) {
        // Hardware address same as lease 1.
        lease->hwaddr_.reset(new HWAddr(vector<uint8_t>(6, 0x19), HTYPE_ETHER));
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x75)));

        // The times used in the next tests are deliberately restricted - we
        // should be able to cope with valid lifetimes up to 0xffffffff.
        //  However, this will lead to overflows.
        // @TODO: test overflow conditions when code has been fixed.
        lease->valid_lft_ = 7000;
        lease->cltt_ = 234567;
        lease->updateCurrentExpirationTime();
        lease->subnet_id_ = 37;
        lease->fqdn_rev_ = true;
        lease->fqdn_fwd_ = true;
        lease->hostname_ = "otherhost.example.com.";

    } else if (address == straddress4_[4]) {
        lease->hwaddr_.reset(new HWAddr(vector<uint8_t>(6, 0x4c), HTYPE_ETHER));
        // Same ClientId as straddr4_[1]
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x53)));    // Same as lease 1
        lease->valid_lft_ = 7736;
        lease->cltt_ = 222456;
        lease->updateCurrentExpirationTime();
        lease->subnet_id_ = 85;
        lease->fqdn_rev_ = true;
        lease->fqdn_fwd_ = true;
        lease->hostname_ = "otherhost.example.com.";

    } else if (address == straddress4_[5]) {
        // Same as lease 1
        lease->hwaddr_.reset(new HWAddr(vector<uint8_t>(6, 0x19), HTYPE_ETHER));
        // Same ClientId and IAID as straddress4_1
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x53)));    // Same as lease 1
        lease->valid_lft_ = 7832;
        lease->cltt_ = 227476;
        lease->updateCurrentExpirationTime();
        lease->subnet_id_ = 175;
        lease->fqdn_rev_ = false;
        lease->fqdn_fwd_ = false;
        lease->hostname_ = "otherhost.example.com.";
        lease->setContext(Element::fromJSON("{ \"foo\": true }"));

    } else if (address == straddress4_[6]) {
        lease->hwaddr_.reset(new HWAddr(vector<uint8_t>(6, 0x6e), HTYPE_ETHER));
        // Same ClientId as straddress4_1
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x53)));    // Same as lease 1
        lease->valid_lft_ = 1832;
        lease->cltt_ = 627476;
        lease->updateCurrentExpirationTime();
        lease->subnet_id_ = 112;
        lease->fqdn_rev_ = false;
        lease->fqdn_fwd_ = true;
        lease->hostname_ = "myhost.example.com.";

    } else if (address == straddress4_[7]) {
        lease->hwaddr_.reset(new HWAddr(vector<uint8_t>(), HTYPE_ETHER)); // Empty
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x77)));
        lease->valid_lft_ = 7975;
        lease->cltt_ = 213876;
        lease->updateCurrentExpirationTime();
        lease->subnet_id_ = 19;
        lease->fqdn_rev_ = true;
        lease->fqdn_fwd_ = true;
        lease->hostname_ = "myhost.example.com.";
        lease->setContext(Element::fromJSON("{ \"bar\": false }"));

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

    // Set other parameters.  For historical reasons, address 0 is not used.
    if (address == straddress6_[0]) {
        lease->type_ = leasetype6_[0];
        lease->prefixlen_ = 4;
        lease->iaid_ = 142;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x77)));
        lease->preferred_lft_ = 900;
        lease->valid_lft_ = 8677;
        lease->cltt_ = 168256;
        lease->updateCurrentExpirationTime();
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
        lease->updateCurrentExpirationTime();
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
        lease->updateCurrentExpirationTime();
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
        // @TODO: test overflow conditions when code has been fixed.
        lease->preferred_lft_ = 7200;
        lease->valid_lft_ = 7000;
        lease->cltt_ = 234567;
        lease->updateCurrentExpirationTime();
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
        lease->updateCurrentExpirationTime();
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
        lease->updateCurrentExpirationTime();
        lease->subnet_id_ = 175;
        lease->fqdn_fwd_ = false;
        lease->fqdn_rev_ = true;
        lease->hostname_ = "hostname.example.com.";
        lease->setContext(Element::fromJSON("{ \"foo\": true }"));

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
        lease->updateCurrentExpirationTime();
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
        lease->updateCurrentExpirationTime();
        lease->subnet_id_ = 19;
        lease->fqdn_fwd_ = false;
        lease->fqdn_rev_ = true;
        lease->hostname_ = "hostname.example.com.";
        lease->setContext(Element::fromJSON("{ \"bar\": false }"));

    } else {
        // Unknown address, return an empty pointer.
        lease.reset();

    }

    return (lease);
}

template <typename T>
void GenericLeaseMgrTest::checkLeasesDifferent(const std::vector<T>& leases) const {

    // Check they were created
    for (size_t i = 0; i < leases.size(); ++i) {
        ASSERT_TRUE(leases[i]);
    }

    // Check they are different
    for (size_t i = 0; i < (leases.size() - 1); ++i) {
        for (size_t j = (i + 1); j < leases.size(); ++j) {
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
    for (size_t i = 0; i < straddress4_.size(); ++i) {
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
    for (size_t i = 0; i < straddress6_.size(); ++i) {
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
    HWAddr tmp(*leases[2]->hwaddr_);
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
    EXPECT_TRUE(lmptr_->deleteLease(leases[1]));
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    EXPECT_FALSE(l_returned);
    EXPECT_FALSE(lmptr_->deleteLease(leases[1]));

    // Check that the second address is still there.
    l_returned = lmptr_->getLease4(ioaddress4_[2]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[2], l_returned);
}

void
GenericLeaseMgrTest::testGetLease4HWAddr1() {
    // Let's initialize two different leases 4 and just add the first ...
    Lease4Ptr leaseA = initializeLease4(straddress4_[5]);
    HWAddr hwaddrA(*leaseA->hwaddr_);
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
    for (size_t i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the hardware address of lease 1
    /// @todo: Simply use HWAddr directly once 2589 is implemented
    HWAddr tmp(*leases[1]->hwaddr_);
    Lease4Collection returned = lmptr_->getLease4(tmp);

    // Should be three leases, matching leases[1], [3] and [5].
    ASSERT_EQ(3, returned.size());

    // Check the lease[5] (and only this one) has an user context.
    size_t contexts = 0;
    for (Lease4Collection::const_iterator i = returned.begin();
         i != returned.end(); ++i) {
        if ((*i)->getContext()) {
            ++contexts;
            EXPECT_EQ("{ \"foo\": true }", (*i)->getContext()->str());
        }
    }
    EXPECT_EQ(1, contexts);

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
    returned = lmptr_->getLease4(*leases[2]->hwaddr_);
    ASSERT_EQ(1, returned.size());
    detailCompareLease(leases[2], *returned.begin());

    // Check that an empty vector is valid
    EXPECT_TRUE(leases[7]->hwaddr_->hwaddr_.empty());
    EXPECT_FALSE(leases[7]->client_id_->getClientId().empty());
    returned = lmptr_->getLease4(*leases[7]->hwaddr_);
    ASSERT_EQ(1, returned.size());
    detailCompareLease(leases[7], *returned.begin());

    // Try to get something with invalid hardware address
    vector<uint8_t> invalid(6, 0);
    returned = lmptr_->getLease4(invalid);
    EXPECT_EQ(0, returned.size());
}

void
GenericLeaseMgrTest::testAddGetDelete6() {
    const std::string addr234("2001:db8:1::234");
    const std::string addr456("2001:db8:1::456");
    const std::string addr789("2001:db8:1::789");
    IOAddress addr(addr456);

    uint8_t llt[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    DuidPtr duid(new DUID(llt, sizeof(llt)));

    uint32_t iaid = 7; // just a number

    SubnetID subnet_id = 8; // just another number

    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, iaid, 100, 200,
                               subnet_id));

    EXPECT_TRUE(lmptr_->addLease(lease));

    // should not be allowed to add a second lease with the same address
    EXPECT_FALSE(lmptr_->addLease(lease));

    Lease6Ptr x = lmptr_->getLease6(Lease::TYPE_NA, IOAddress(addr234));
    EXPECT_EQ(Lease6Ptr(), x);

    x = lmptr_->getLease6(Lease::TYPE_NA, IOAddress(addr456));
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
    Lease6Ptr non_existing_lease(new Lease6(Lease::TYPE_NA, IOAddress(addr789),
                                            duid, iaid, 100, 200,
                                            subnet_id));
    EXPECT_FALSE(lmptr_->deleteLease(non_existing_lease));

    // this one should succeed
    EXPECT_TRUE(lmptr_->deleteLease(x));

    // after the lease is deleted, it should really be gone
    x = lmptr_->getLease6(Lease::TYPE_NA, IOAddress(addr456));
    EXPECT_FALSE(x);

    // Reopen the lease storage to make sure that lease is gone from the
    // persistent storage.
    reopen(V6);
    x = lmptr_->getLease6(Lease::TYPE_NA, IOAddress(addr456));
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
    lease->cltt_ = DatabaseConnection::MAX_DB_TIME;

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
GenericLeaseMgrTest::testInfiniteLifeTime4() {
    // Get the leases to be used for the test.
    vector<Lease4Ptr> leases = createLeases4();
    Lease4Ptr lease = leases[1];

    // Set valid_lft_ to infinite, cllt_ to now.
    lease->valid_lft_ = Lease::INFINITY_LFT;
    lease->cltt_ = time(NULL);

    // Insert should not throw.
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    Lease4Ptr l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);
}

void
GenericLeaseMgrTest::testBasicLease4() {
    // Get the leases to be used for the test.
    vector<Lease4Ptr> leases = createLeases4();
    leases[2]->setContext(Element::fromJSON("{ \"foobar\": 1234 }"));

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
    EXPECT_TRUE(lmptr_->deleteLease(leases[1]));
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    EXPECT_FALSE(l_returned);
    EXPECT_FALSE(lmptr_->deleteLease(leases[1]));

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
    leases[2]->setContext(Element::fromJSON("{ \"foobar\": 1234 }"));

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
    EXPECT_TRUE(lmptr_->deleteLease(leases[1]));
    l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    EXPECT_FALSE(l_returned);
    EXPECT_FALSE(lmptr_->deleteLease(leases[1]));

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
    lease->cltt_ = DatabaseConnection::MAX_DB_TIME;

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
GenericLeaseMgrTest::testInfiniteLifeTime6() {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();
    Lease6Ptr lease = leases[1];

    // Set valid_lft_ to infinite, cllt_ to now.
    lease->valid_lft_ = Lease::INFINITY_LFT;
    lease->cltt_ = time(NULL);

    // Insert should not throw.
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    Lease6Ptr l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);
}

// Checks whether a MAC address can be stored and retrieved together with
// a lease.
void
GenericLeaseMgrTest::testLease6MAC() {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();

    HWAddrPtr hwaddr1(new HWAddr(vector<uint8_t>(6, 11), HTYPE_ETHER));
    HWAddrPtr hwaddr2(new HWAddr(vector<uint8_t>(6, 22), HTYPE_DOCSIS));

    leases[1]->hwaddr_ = hwaddr1;     // Add hardware address to leases 1 and 2
    leases[2]->hwaddr_ = hwaddr2;
    leases[3]->hwaddr_ = HWAddrPtr(); // No hardware address for the third one

    // Start the tests.  Add three leases to the database, read them back and
    // check they are what we think they are.
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    EXPECT_TRUE(lmptr_->addLease(leases[2]));
    EXPECT_TRUE(lmptr_->addLease(leases[3]));
    lmptr_->commit();

    // Reopen the database to ensure that they actually got stored.
    reopen(V6);

    // First lease should have a hardware address in it
    Lease6Ptr stored1 = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    ASSERT_TRUE(stored1);
    ASSERT_TRUE(stored1->hwaddr_);
    EXPECT_TRUE(*hwaddr1 == *stored1->hwaddr_);

    // Second lease should have a hardware address in it
    Lease6Ptr stored2 = lmptr_->getLease6(leasetype6_[2], ioaddress6_[2]);
    ASSERT_TRUE(stored2);
    ASSERT_TRUE(stored2->hwaddr_);
    EXPECT_TRUE(*hwaddr2 == *stored2->hwaddr_);

    // Third lease should NOT have any hardware address.
    Lease6Ptr stored3 = lmptr_->getLease6(leasetype6_[3], ioaddress6_[3]);
    ASSERT_TRUE(stored3);
    EXPECT_FALSE(stored3->hwaddr_);
}

// Checks whether a hardware address type can be stored and retrieved.
void
GenericLeaseMgrTest::testLease6HWTypeAndSource() {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();

    HWAddrPtr hwaddr1(new HWAddr(vector<uint8_t>(6, 11), 123));
    HWAddrPtr hwaddr2(new HWAddr(vector<uint8_t>(6, 22), 456));

    // Those should use defines from Pkt::HWADDR_SOURCE_*, but let's
    // test an uncommon value (and 0 which means unknown).
    hwaddr1->source_ = HWAddr::HWADDR_SOURCE_RAW;
    hwaddr2->source_ = HWAddr::HWADDR_SOURCE_DUID;

    leases[1]->hwaddr_ = hwaddr1;     // Add hardware address to leases 1 and 2
    leases[2]->hwaddr_ = hwaddr2;
    leases[3]->hwaddr_ = HWAddrPtr(); // No hardware address for the third one

    // Start the tests.  Add three leases to the database, read them back and
    // check they are what we think they are.
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    EXPECT_TRUE(lmptr_->addLease(leases[2]));
    EXPECT_TRUE(lmptr_->addLease(leases[3]));
    lmptr_->commit();

    // Reopen the database to ensure that they actually got stored.
    reopen(V6);

    // First lease should have a hardware address in it
    Lease6Ptr stored1 = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    ASSERT_TRUE(stored1);
    ASSERT_TRUE(stored1->hwaddr_);
    EXPECT_EQ(123, stored1->hwaddr_->htype_);
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_RAW, stored1->hwaddr_->source_);

    // Second lease should have a hardware address in it
    Lease6Ptr stored2 = lmptr_->getLease6(leasetype6_[2], ioaddress6_[2]);
    ASSERT_TRUE(stored2);
    ASSERT_TRUE(stored2->hwaddr_);
    EXPECT_EQ(456, stored2->hwaddr_->htype_);
    EXPECT_EQ(HWAddr::HWADDR_SOURCE_DUID, stored2->hwaddr_->source_);

    // Third lease should NOT have any hardware address.
    Lease6Ptr stored3 = lmptr_->getLease6(leasetype6_[3], ioaddress6_[3]);
    ASSERT_TRUE(stored3);
    EXPECT_FALSE(stored3->hwaddr_);
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
    EXPECT_TRUE(lmptr_->deleteLease(leases[1]));

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
    EXPECT_TRUE(lmptr_->deleteLease(leases[1]));

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
        leases[1]->hwaddr_->hwaddr_.resize(i, i);
        EXPECT_TRUE(lmptr_->addLease(leases[1]));
        /// @todo: Simply use HWAddr directly once 2589 is implemented
        Lease4Collection returned =
            lmptr_->getLease4(*leases[1]->hwaddr_);

        ASSERT_EQ(1, returned.size());
        detailCompareLease(leases[1], *returned.begin());
        ASSERT_TRUE(lmptr_->deleteLease(leases[1]));
    }

    // Database should not let us add one that is too big
    // (The 42 is a random value put in each byte of the address.)
    leases[1]->hwaddr_->hwaddr_.resize(HWAddr::MAX_HWADDR_LEN + 100, 42);
    EXPECT_THROW(lmptr_->addLease(leases[1]), isc::db::DbOperationError);
}

void
GenericLeaseMgrTest::testGetLease4HWAddrSubnetId() {
    // Get the leases to be used for the test and add to the database
    vector<Lease4Ptr> leases = createLeases4();
    for (size_t i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the hardware address of lease 1 and
    // subnet ID of lease 1.  Result should be a single lease - lease 1.
    /// @todo: Simply use HWAddr directly once 2589 is implemented
    Lease4Ptr returned = lmptr_->getLease4(*leases[1]->hwaddr_,
                                           leases[1]->subnet_id_);

    ASSERT_TRUE(returned);
    detailCompareLease(leases[1], returned);

    // Try for a match to the hardware address of lease 1 and the wrong
    // subnet ID.
    /// @todo: Simply use HWAddr directly once 2589 is implemented
    returned = lmptr_->getLease4(*leases[1]->hwaddr_, leases[1]->subnet_id_ + 1);
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
    EXPECT_TRUE(lmptr_->deleteLease(leases[2]));
    leases[1]->addr_ = leases[2]->addr_;
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    /// @todo: Simply use HWAddr directly once 2589 is implemented
    EXPECT_THROW(returned = lmptr_->getLease4(*leases[1]->hwaddr_,
                                              leases[1]->subnet_id_),
                 isc::db::MultipleRecords);

}

void
GenericLeaseMgrTest::testGetLease4HWAddrSubnetIdSize() {
    // Create leases, although we need only one.
    vector<Lease4Ptr> leases = createLeases4();

    // Now add leases with increasing hardware address size and check
    // that they can be retrieved.
    for (uint8_t i = 0; i <= HWAddr::MAX_HWADDR_LEN; ++i) {
        leases[1]->hwaddr_->hwaddr_.resize(i, i);
        EXPECT_TRUE(lmptr_->addLease(leases[1]));
        /// @todo: Simply use HWAddr directly once 2589 is implemented
        Lease4Ptr returned = lmptr_->getLease4(*leases[1]->hwaddr_,
                                               leases[1]->subnet_id_);
        ASSERT_TRUE(returned);
        detailCompareLease(leases[1], returned);
        ASSERT_TRUE(lmptr_->deleteLease(leases[1]));
    }

    // Database should not let us add one that is too big
    // (The 42 is a random value put in each byte of the address.)
    leases[1]->hwaddr_->hwaddr_.resize(HWAddr::MAX_HWADDR_LEN + 100, 42);
    EXPECT_THROW(lmptr_->addLease(leases[1]), isc::db::DbOperationError);
}

void
GenericLeaseMgrTest::testGetLease4ClientId2() {
    // Get the leases to be used for the test and add to the database
    vector<Lease4Ptr> leases = createLeases4();
    for (size_t i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Get the leases matching the Client ID address of lease 1
    Lease4Collection returned = lmptr_->getLease4(*leases[1]->client_id_);

    // Should be four leases, matching leases[1], [4], [5] and [6].
    ASSERT_EQ(4, returned.size());

    // Check the lease[5] (and only this one) has an user context.
    size_t contexts = 0;
    for (Lease4Collection::const_iterator i = returned.begin();
         i != returned.end(); ++i) {
        if ((*i)->getContext()) {
            ++contexts;
            EXPECT_EQ("{ \"foo\": true }", (*i)->getContext()->str());
        }
    }
    EXPECT_EQ(1, contexts);

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
        ASSERT_EQ(returned.size(), 1u);
        detailCompareLease(leases[1], *returned.begin());
        ASSERT_TRUE(lmptr_->deleteLease(leases[1]));
    }

    // Don't bother to check client IDs longer than the maximum -
    // these cannot be constructed, and that limitation is tested
    // in the DUID/Client ID unit tests.
}

void
GenericLeaseMgrTest::testGetLease4ClientIdSubnetId() {
    // Get the leases to be used for the test and add to the database
    vector<Lease4Ptr> leases = createLeases4();
    for (size_t i = 0; i < leases.size(); ++i) {
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
GenericLeaseMgrTest::testGetLeases4SubnetId() {
    // Get the leases to be used for the test and add to the database.
    vector<Lease4Ptr> leases = createLeases4();
    for (size_t i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // There should be exactly two leases for the subnet id that the second
    // lease belongs to.
    Lease4Collection returned = lmptr_->getLeases4(leases[1]->subnet_id_);
    ASSERT_EQ(2, returned.size());
}

void
GenericLeaseMgrTest::testGetLeases4Hostname() {
    // Get the leases to be used for the test and add to the database.
    vector<Lease4Ptr> leases = createLeases4();
    for (size_t i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // There should be no lease for hostname foobar.
    Lease4Collection returned = lmptr_->getLeases4(string("foobar"));
    EXPECT_TRUE(returned.empty());

    // There should be exactly 4 leases for the hostname of the second lease.
    ASSERT_FALSE(leases[1]->hostname_.empty());
    returned = lmptr_->getLeases4(leases[1]->hostname_);
    EXPECT_EQ(4, returned.size());

    // And 3 for the forth lease.
    ASSERT_FALSE(leases[3]->hostname_.empty());
    returned = lmptr_->getLeases4(leases[3]->hostname_);
    EXPECT_EQ(3, returned.size());
}

void
GenericLeaseMgrTest::testGetLeases4() {
    // Get the leases to be used for the test and add to the database
    vector<Lease4Ptr> leases = createLeases4();
    for (size_t i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // All leases should be returned.
    Lease4Collection returned = lmptr_->getLeases4();
    ASSERT_EQ(leases.size(), returned.size());
}

void
GenericLeaseMgrTest::testGetLeases4Paged() {
    // Get the leases to be used for the test and add to the database.
    vector<Lease4Ptr> leases = createLeases4();
    for (size_t i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    Lease4Collection all_leases;

    IOAddress last_address = IOAddress("0.0.0.0");
    for (auto i = 0; i < 4; ++i) {
        Lease4Collection page = lmptr_->getLeases4(last_address, LeasePageSize(3));

        // Collect leases in a common structure. They may be out of order.
        for (Lease4Ptr lease : page) {
            all_leases.push_back(lease);
        }

        // Empty page means there are no more leases.
        if (page.empty()) {
            break;

        } else {
            // Record last returned address because it is going to be used
            // as an argument for the next call.
            last_address = page[page.size() - 1]->addr_;
        }
    }

    // Make sure that we got exactly the number of leases that we earlier
    // stored in the database.
    EXPECT_EQ(leases.size(), all_leases.size());

    // Make sure that all leases that we stored in the lease database
    // have been retrieved.
    for (Lease4Ptr lease : leases) {
        bool found = false;
        for (Lease4Ptr returned_lease : all_leases) {
            if (lease->addr_ == returned_lease->addr_) {
                found = true;
                break;
            }
        }
        EXPECT_TRUE(found) << "lease for address " << lease->addr_.toText()
            << " was not returned in any of the pages";
    }

    boost::scoped_ptr<LeasePageSize> lease_page_size;

    // The maximum allowed value for the limit is max for uint32_t.
    size_t oor = static_cast<size_t>(std::numeric_limits<uint32_t>::max()) + 1;
    EXPECT_THROW(lease_page_size.reset(new LeasePageSize(oor)), OutOfRange);

    // Zero page size is illegal too.
    EXPECT_THROW(lease_page_size.reset(new LeasePageSize(0)), OutOfRange);

    // Only IPv4 address can be used.
    EXPECT_THROW(lmptr_->getLeases4(IOAddress("2001:db8::1"), LeasePageSize(3)),
                 InvalidAddressFamily);
}

void
GenericLeaseMgrTest::testGetLeases6SubnetId() {
    // Get the leases to be used for the test and add to the database.
    vector<Lease6Ptr> leases = createLeases6();
    for (size_t i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // There should be exactly two leases for the subnet id that the second
    // lease belongs to.
    Lease6Collection returned = lmptr_->getLeases6(leases[1]->subnet_id_);
    EXPECT_EQ(2, returned.size());
}

void
GenericLeaseMgrTest::testGetLeases6Hostname() {
    // Get the leases to be used for the test and add to the database.
    vector<Lease6Ptr> leases = createLeases6();
    for (size_t i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // There should be no lease for hostname foobar.
    Lease6Collection returned = lmptr_->getLeases6(string("foobar"));
    EXPECT_TRUE(returned.empty());

    // There should be exactly 4 leases for the hostname of the second lease.
    ASSERT_FALSE(leases[1]->hostname_.empty());
    returned = lmptr_->getLeases6(leases[1]->hostname_);
    EXPECT_EQ(4, returned.size());

    // One for the fifth lease.
    ASSERT_FALSE(leases[4]->hostname_.empty());
    returned = lmptr_->getLeases6(leases[4]->hostname_);
    EXPECT_EQ(1, returned.size());

    // And 3 for the sixth lease.
    ASSERT_FALSE(leases[5]->hostname_.empty());
    returned = lmptr_->getLeases6(leases[5]->hostname_);
    EXPECT_EQ(3, returned.size());
}

void
GenericLeaseMgrTest::testGetLeases6() {
    // Get the leases to be used for the test and add to the database
    vector<Lease6Ptr> leases = createLeases6();
    for (size_t i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // All leases should be returned.
    Lease6Collection returned = lmptr_->getLeases6();
    ASSERT_EQ(leases.size(), returned.size());
}

void
GenericLeaseMgrTest::testGetLeases6Paged() {
    // Get the leases to be used for the test and add to the database.
    vector<Lease6Ptr> leases = createLeases6();
    for (size_t i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    Lease6Collection all_leases;

    IOAddress last_address = IOAddress::IPV6_ZERO_ADDRESS();
    for (auto i = 0; i < 4; ++i) {
        Lease6Collection page = lmptr_->getLeases6(last_address, LeasePageSize(3));

        // Collect leases in a common structure. They may be out of order.
        for (Lease6Ptr lease : page) {
            all_leases.push_back(lease);
        }

        // Empty page means there are no more leases.
        if (page.empty()) {
            break;

        } else {
            // Record last returned address because it is going to be used
            // as an argument for the next call.
            last_address = page[page.size() - 1]->addr_;
        }
    }

    // Make sure that we got exactly the number of leases that we earlier
    // stored in the database.
    EXPECT_EQ(leases.size(), all_leases.size());

    // Make sure that all leases that we stored in the lease database
    // have been retrieved.
    for (Lease6Ptr lease : leases) {
        bool found = false;
        for (Lease6Ptr returned_lease : all_leases) {
            if (lease->addr_ == returned_lease->addr_) {
                found = true;
                break;
            }
        }
        EXPECT_TRUE(found) << "lease for address " << lease->addr_.toText()
            << " was not returned in any of the pages";
    }

    // Only IPv6 address can be used.
    EXPECT_THROW(lmptr_->getLeases6(IOAddress("192.0.2.0"), LeasePageSize(3)),
                 InvalidAddressFamily);
}

void
GenericLeaseMgrTest::testGetLeases6DuidIaid() {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();
    ASSERT_LE(6, leases.size());    // Expect to access leases 0 through 5

    // Add them to the database
    for (size_t i = 0; i < leases.size(); ++i) {
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
        ASSERT_TRUE(lmptr_->deleteLease(leases[1]));
    }

    // Don't bother to check DUIDs longer than the maximum - these cannot be
    // constructed, and that limitation is tested in the DUID/Client ID unit
    // tests.

}

void
GenericLeaseMgrTest::testLease6LeaseTypeCheck() {
    Lease6Ptr empty_lease(new Lease6());

    DuidPtr duid(new DUID(vector<uint8_t>(8, 0x77)));

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
GenericLeaseMgrTest::testLease6LargeIaidCheck() {

    DuidPtr duid(new DUID(vector<uint8_t>(8, 0x77)));
    IOAddress addr(std::string("2001:db8:1::111"));
    SubnetID subnet_id = 8; // random number

    // Use a value we know is larger than 32-bit signed max.
    uint32_t large_iaid = 0xFFFFFFFE;

    // We should be able to add with no problems.
    Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr, duid, large_iaid,
                               100, 200, subnet_id));
    ASSERT_TRUE(lmptr_->addLease(lease));

    // Sanity check that we added it.
    Lease6Ptr found_lease = lmptr_->getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(found_lease);
    EXPECT_TRUE(*found_lease == *lease);

    // Verify getLease6() duid/iaid finds it.
    found_lease = lmptr_->getLease6(Lease::TYPE_NA, *duid, large_iaid, subnet_id);
    ASSERT_TRUE(found_lease);
    EXPECT_TRUE(*found_lease == *lease);

    // Verify getLeases6() duid/iaid finds it.
    Lease6Collection found_leases = lmptr_->getLeases6(Lease::TYPE_NA,
                                                       *duid, large_iaid);
    // We should match the lease.
    ASSERT_EQ(1, found_leases.size());
    EXPECT_TRUE(*(found_leases[0]) == *lease);
}

void
GenericLeaseMgrTest::testGetLease6DuidIaidSubnetId() {
    // Get the leases to be used for the test and add them to the database.
    vector<Lease6Ptr> leases = createLeases6();
    for (size_t i = 0; i < leases.size(); ++i) {
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

/// @brief verifies getLeases6(DUID)
void
GenericLeaseMgrTest::testGetLeases6Duid() {
    //add leases
    IOAddress addr1(std::string("2001:db8:1::111"));
    IOAddress addr2(std::string("2001:db8:1::222"));
    IOAddress addr3(std::string("2001:db8:1::333"));

    DuidPtr duid1(new DUID({0, 1, 1, 1, 1, 1, 1, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf}));
    DuidPtr duid2(new DUID({0, 2, 2, 2, 2, 2, 2, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf}));
    DuidPtr duid3(new DUID({0, 3, 3, 3, 3, 3, 3, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf}));
    DuidPtr duid4(new DUID({0, 4, 4, 4, 4, 4, 4, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf}));

    uint32_t iaid = 7; // random number

    SubnetID subnet_id = 8; // random number

    Lease6Ptr lease1(new Lease6(Lease::TYPE_NA, addr1, duid1, iaid, 100, 200,
                                subnet_id));
    Lease6Ptr lease2(new Lease6(Lease::TYPE_NA, addr2, duid2, iaid, 100, 200,
                                subnet_id));
    Lease6Ptr lease3(new Lease6(Lease::TYPE_PD, addr3, duid3, iaid, 100, 200,
                                subnet_id, HWAddrPtr(), 64));

    EXPECT_TRUE(lmptr_->addLease(lease1));
    EXPECT_TRUE(lmptr_->addLease(lease2));
    EXPECT_TRUE(lmptr_->addLease(lease3));

    Lease6Collection returned1 = lmptr_->getLeases6(*(lease1->duid_));
    Lease6Collection returned2 = lmptr_->getLeases6(*(lease2->duid_));
    Lease6Collection returned3 = lmptr_->getLeases6(*(lease3->duid_));

    //verify if the returned lease mathces
    ASSERT_EQ(returned1.size(), 1);
    ASSERT_EQ(returned2.size(), 1);
    ASSERT_EQ(returned3.size(), 1);

    //verify that the returned lease are same
    EXPECT_TRUE(returned1[0]->addr_ == lease1->addr_);
    EXPECT_TRUE(returned2[0]->addr_ == lease2->addr_);
    EXPECT_TRUE(returned3[0]->addr_ == lease3->addr_);

    //now verify we return empty for a lease that has not been stored
    returned3 = lmptr_->getLeases6(*duid4);
    EXPECT_TRUE(returned3.empty());

    //clean up
    ASSERT_TRUE(lmptr_->deleteLease(lease1));
    ASSERT_TRUE(lmptr_->deleteLease(lease2));
    ASSERT_TRUE(lmptr_->deleteLease(lease3));

    //now verify we return empty for a lease that has not been stored
    returned3 = lmptr_->getLeases6(*duid4);
    EXPECT_TRUE(returned3.empty());
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
        ASSERT_TRUE(lmptr_->deleteLease(leases[1]));
    }

    // Don't bother to check DUIDs longer than the maximum - these cannot be
    // constructed, and that limitation is tested in the DUID/Client ID unit
    // tests.
}

void
GenericLeaseMgrTest::testUpdateLease4() {
    // Get the leases to be used for the test and add them to the database.
    vector<Lease4Ptr> leases = createLeases4();
    for (size_t i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }
    lmptr_->commit();

    Lease4Ptr l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Modify some fields in lease 1 (not the address) and update it.
    ++leases[1]->subnet_id_;
    leases[1]->valid_lft_ *= 2;
    leases[1]->hostname_ = "modified.hostname.";
    leases[1]->fqdn_fwd_ = !leases[1]->fqdn_fwd_;
    leases[1]->fqdn_rev_ = !leases[1]->fqdn_rev_;;
    leases[1]->setContext(Element::fromJSON("{ \"foobar\": 1234 }"));
    lmptr_->updateLease4(leases[1]);

    // ... and check what is returned is what is expected.
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Alter the lease again and check.
    ++leases[1]->subnet_id_;
    leases[1]->cltt_ += 6;
    leases[1]->setContext(Element::fromJSON("{ \"foo\": \"bar\" }"));
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
    EXPECT_THROW(lmptr_->updateLease4(leases[1]), isc::db::DbOperationError);

    // Try updating a lease not in the database.
    ASSERT_TRUE(lmptr_->deleteLease(leases[2]));
    EXPECT_THROW(lmptr_->updateLease4(leases[2]), isc::dhcp::NoSuchLease);
}

void
GenericLeaseMgrTest::testConcurrentUpdateLease4() {
    // Get the leases to be used for the test and add them to the database.
    vector<Lease4Ptr> leases = createLeases4();
    for (size_t i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }
    lmptr_->commit();

    Lease4Ptr l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Save initial lease to be used for concurrent update
    Lease4Ptr initialLease = boost::make_shared<Lease4>(*leases[1]);
    detailCompareLease(leases[1], initialLease);

    // Modify some fields in lease 1 (not the address) and update it.
    ++leases[1]->subnet_id_;
    leases[1]->valid_lft_ *= 2;
    leases[1]->hostname_ = "modified.hostname.";
    leases[1]->fqdn_fwd_ = !leases[1]->fqdn_fwd_;
    leases[1]->fqdn_rev_ = !leases[1]->fqdn_rev_;;
    leases[1]->setContext(Element::fromJSON("{ \"foobar\": 1234 }"));
    lmptr_->updateLease4(leases[1]);

    // ... and check what is returned is what is expected.
    l_returned = lmptr_->getLease4(ioaddress4_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Concurrently updating lease should fail
    EXPECT_THROW(lmptr_->updateLease4(initialLease), isc::dhcp::NoSuchLease);
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
    leases[1]->setContext(Element::fromJSON("{ \"foobar\": 1234 }"));
    lmptr_->updateLease6(leases[1]);

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
    leases[1]->setContext(Element::fromJSON("{ \"foo\": \"bar\" }"));
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
    EXPECT_THROW(lmptr_->updateLease6(leases[1]), isc::db::DbOperationError);

    // Try updating a lease not in the database.
    EXPECT_THROW(lmptr_->updateLease6(leases[2]), isc::dhcp::NoSuchLease);
}

void
GenericLeaseMgrTest::testConcurrentUpdateLease6() {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();
    ASSERT_LE(3, leases.size());    // Expect to access leases 0 through 2

    // Add a lease to the database and check that the lease is there.
    EXPECT_TRUE(lmptr_->addLease(leases[1]));
    lmptr_->commit();

    Lease6Ptr l_returned = lmptr_->getLease6(leasetype6_[1], ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Save initial lease to be used for concurrent update
    Lease6Ptr initialLease = boost::make_shared<Lease6>(*leases[1]);
    detailCompareLease(leases[1], initialLease);

    // Modify some fields in lease 1 (not the address) and update it.
    ++leases[1]->iaid_;
    leases[1]->type_ = Lease::TYPE_PD;
    leases[1]->valid_lft_ *= 2;
    leases[1]->hostname_ = "modified.hostname.v6.";
    leases[1]->fqdn_fwd_ = !leases[1]->fqdn_fwd_;
    leases[1]->fqdn_rev_ = !leases[1]->fqdn_rev_;;
    leases[1]->setContext(Element::fromJSON("{ \"foobar\": 1234 }"));
    lmptr_->updateLease6(leases[1]);

    // ... and check what is returned is what is expected.
    l_returned.reset();
    l_returned = lmptr_->getLease6(Lease::TYPE_PD, ioaddress6_[1]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(leases[1], l_returned);

    // Concurrently updating lease should fail
    EXPECT_THROW(lmptr_->updateLease6(initialLease), isc::dhcp::NoSuchLease);
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

    // Check that the lease has been successfully added.
    Lease4Ptr l_returned = lmptr_->getLease4(ioaddress4_[0]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(lease, l_returned);

    // Delete a lease, check that it's gone.
    EXPECT_TRUE(lmptr_->deleteLease(leases[0]));
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

    // Check that the lease has been successfully added.
    Lease6Ptr l_returned = lmptr_->getLease6(Lease::TYPE_NA, ioaddress6_[0]);
    ASSERT_TRUE(l_returned);
    detailCompareLease(lease, l_returned);

    // Delete a lease, check that it's gone.
    EXPECT_TRUE(lmptr_->deleteLease(leases[0]));
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

void
GenericLeaseMgrTest::testVersion(int major, int minor) {
    EXPECT_EQ(major, lmptr_->getVersion().first);
    EXPECT_EQ(minor, lmptr_->getVersion().second);
}

void
GenericLeaseMgrTest::testGetExpiredLeases4() {
    // Get the leases to be used for the test.
    vector<Lease4Ptr> leases = createLeases4();
    // Make sure we have at least 6 leases there.
    ASSERT_GE(leases.size(), 6);

    // Use the same current time for all leases.
    time_t current_time = time(NULL);

    // Add them to the database
    for (size_t i = 0; i < leases.size(); ++i) {
        // Mark every other lease as expired.
        if (i % 2 == 0) {
            // Set client last transmission time to the value older than the
            // valid lifetime to make it expired. The expiration time also
            // depends on the lease index, so as we can later check that the
            // leases are ordered by the expiration time.
            leases[i]->cltt_ = current_time - leases[i]->valid_lft_ - 10 - i;

        } else {
            // Set current time as cltt for remaining leases. These leases are
            // not expired.
            leases[i]->cltt_ = current_time;
        }
        ASSERT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Retrieve at most 1000 expired leases.
    Lease4Collection expired_leases;
    ASSERT_NO_THROW(lmptr_->getExpiredLeases4(expired_leases, 1000));
    // Leases with even indexes should be returned as expired.
    ASSERT_EQ(static_cast<size_t>(leases.size() / 2), expired_leases.size());

    // The expired leases should be returned from the most to least expired.
    // This matches the reverse order to which they have been added.
    for (Lease4Collection::reverse_iterator lease = expired_leases.rbegin();
         lease != expired_leases.rend(); ++lease) {
        int index = static_cast<int>(std::distance(expired_leases.rbegin(), lease));
        // Multiple current index by two, because only leases with even indexes
        // should have been returned.
        ASSERT_LE(2 * index, leases.size());
        EXPECT_EQ(leases[2 * index]->addr_, (*lease)->addr_);
    }

    // Update current time for the next test.
    current_time = time(NULL);
    // Also, remove expired leases collected during the previous test.
    expired_leases.clear();

    // This time let's reverse the expiration time and see if they will be returned
    // in the correct order.
    for (int i = 0; i < leases.size(); ++i) {
        // Update the time of expired leases with even indexes.
        if (i % 2 == 0) {
            leases[i]->cltt_ = current_time - leases[i]->valid_lft_ - 1000 + i;
        } else {
            // Make sure remaining leases remain unexpired.
            leases[i]->cltt_ = current_time + 100;
        }
        ASSERT_NO_THROW(lmptr_->updateLease4(leases[i]));
    }

    // Retrieve expired leases again. The limit of 0 means return all expired
    // leases.
    ASSERT_NO_THROW(lmptr_->getExpiredLeases4(expired_leases, 0));
    // The same leases should be returned.
    ASSERT_EQ(static_cast<size_t>(leases.size() / 2), expired_leases.size());

    // This time leases should be returned in the non-reverse order.
    for (Lease4Collection::iterator lease = expired_leases.begin();
         lease != expired_leases.end(); ++lease) {
        int index = static_cast<int>(std::distance(expired_leases.begin(), lease));
        ASSERT_LE(2 * index, leases.size());
        EXPECT_EQ(leases[2 * index]->addr_, (*lease)->addr_);
    }

    // Remember expired leases returned.
    std::vector<Lease4Ptr> saved_expired_leases = expired_leases;

    // Remove expired leases again.
    expired_leases.clear();

    // Limit the number of leases to be returned to 2.
    ASSERT_NO_THROW(lmptr_->getExpiredLeases4(expired_leases, 2));

    // Make sure we have exactly 2 leases returned.
    ASSERT_EQ(2, expired_leases.size());

    // Test that most expired leases have been returned.
    for (Lease4Collection::iterator lease = expired_leases.begin();
         lease != expired_leases.end(); ++lease) {
        int index = static_cast<int>(std::distance(expired_leases.begin(), lease));
        ASSERT_LE(2 * index, leases.size());
        EXPECT_EQ(leases[2 * index]->addr_, (*lease)->addr_);
    }

    // Mark every other expired lease as reclaimed.
    for (int i = 0; i < saved_expired_leases.size(); ++i) {
        if (i % 2 != 0) {
            saved_expired_leases[i]->state_ = Lease::STATE_EXPIRED_RECLAIMED;
        }
        ASSERT_NO_THROW(lmptr_->updateLease4(saved_expired_leases[i]));
    }

    expired_leases.clear();

    // This the returned leases should exclude reclaimed ones. So the number
    // of returned leases should be roughly half of the expired leases.
    ASSERT_NO_THROW(lmptr_->getExpiredLeases4(expired_leases, 0));
    ASSERT_EQ(static_cast<size_t>(saved_expired_leases.size() / 2),
              expired_leases.size());

    // Make sure that returned leases are those that are not reclaimed, i.e.
    // those that have even index.
    for (Lease4Collection::iterator lease = expired_leases.begin();
         lease != expired_leases.end(); ++lease) {
        int index = static_cast<int>(std::distance(expired_leases.begin(), lease));
        EXPECT_EQ(saved_expired_leases[2 * index]->addr_, (*lease)->addr_);
    }
}

void
GenericLeaseMgrTest::testGetExpiredLeases6() {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();
    // Make sure we have at least 6 leases there.
    ASSERT_GE(leases.size(), 6);

    // Use the same current time for all leases.
    time_t current_time = time(NULL);

    // Add them to the database
    for (size_t i = 0; i < leases.size(); ++i) {
        // Mark every other lease as expired.
        if (i % 2 == 0) {
            // Set client last transmission time to the value older than the
            // valid lifetime to make it expired. The expiration time also
            // depends on the lease index, so as we can later check that the
            // leases are ordered by the expiration time.
            leases[i]->cltt_ = current_time - leases[i]->valid_lft_ - 10 - i;

        } else {
            // Set current time as cltt for remaining leases. These leases are
            // not expired.
            leases[i]->cltt_ = current_time;
        }
        ASSERT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Retrieve at most 1000 expired leases.
    Lease6Collection expired_leases;
    ASSERT_NO_THROW(lmptr_->getExpiredLeases6(expired_leases, 1000));
    // Leases with even indexes should be returned as expired.
    ASSERT_EQ(static_cast<size_t>(leases.size() / 2), expired_leases.size());

    // The expired leases should be returned from the most to least expired.
    // This matches the reverse order to which they have been added.
    for (Lease6Collection::reverse_iterator lease = expired_leases.rbegin();
         lease != expired_leases.rend(); ++lease) {
        int index = static_cast<int>(std::distance(expired_leases.rbegin(), lease));
        // Multiple current index by two, because only leases with even indexes
        // should have been returned.
        EXPECT_EQ(leases[2 * index]->addr_, (*lease)->addr_);
    }

    // Update current time for the next test.
    current_time = time(NULL);
    // Also, remove expired leases collected during the previous test.
    expired_leases.clear();

    // This time let's reverse the expiration time and see if they will be returned
    // in the correct order.
    for (int i = 0; i < leases.size(); ++i) {
        // Update the time of expired leases with even indexes.
        if (i % 2 == 0) {
            leases[i]->cltt_ = current_time - leases[i]->valid_lft_ - 1000 + i;

        } else {
            // Make sure remaining leases remain unexpired.
            leases[i]->cltt_ = current_time + 100;
        }
        ASSERT_NO_THROW(lmptr_->updateLease6(leases[i]));
    }

    // Retrieve expired leases again. The limit of 0 means return all expired
    // leases.
    ASSERT_NO_THROW(lmptr_->getExpiredLeases6(expired_leases, 0));
    // The same leases should be returned.
    ASSERT_EQ(static_cast<size_t>(leases.size() / 2), expired_leases.size());

    // This time leases should be returned in the non-reverse order.
    for (Lease6Collection::iterator lease = expired_leases.begin();
         lease != expired_leases.end(); ++lease) {
        int index = static_cast<int>(std::distance(expired_leases.begin(), lease));
        EXPECT_EQ(leases[2 * index]->addr_, (*lease)->addr_);
    }

    // Remember expired leases returned.
    std::vector<Lease6Ptr> saved_expired_leases = expired_leases;

    // Remove expired leases again.
    expired_leases.clear();

    // Limit the number of leases to be returned to 2.
    ASSERT_NO_THROW(lmptr_->getExpiredLeases6(expired_leases, 2));

    // Make sure we have exactly 2 leases returned.
    ASSERT_EQ(2, expired_leases.size());

    // Test that most expired leases have been returned.
    for (Lease6Collection::iterator lease = expired_leases.begin();
         lease != expired_leases.end(); ++lease) {
        int index = static_cast<int>(std::distance(expired_leases.begin(), lease));
        EXPECT_EQ(leases[2 * index]->addr_, (*lease)->addr_);
    }

    // Mark every other expired lease as reclaimed.
    for (int i = 0; i < saved_expired_leases.size(); ++i) {
        if (i % 2 != 0) {
            saved_expired_leases[i]->state_ = Lease::STATE_EXPIRED_RECLAIMED;
        }
        ASSERT_NO_THROW(lmptr_->updateLease6(saved_expired_leases[i]));
    }

    expired_leases.clear();

    // This the returned leases should exclude reclaimed ones. So the number
    // of returned leases should be roughly half of the expired leases.
    ASSERT_NO_THROW(lmptr_->getExpiredLeases6(expired_leases, 0));
    ASSERT_EQ(static_cast<size_t>(saved_expired_leases.size() / 2),
              expired_leases.size());

    // Make sure that returned leases are those that are not reclaimed, i.e.
    // those that have even index.
    for (Lease6Collection::iterator lease = expired_leases.begin();
         lease != expired_leases.end(); ++lease) {
        int index = static_cast<int>(std::distance(expired_leases.begin(), lease));
        EXPECT_EQ(saved_expired_leases[2 * index]->addr_, (*lease)->addr_);
    }
}

void
GenericLeaseMgrTest::testInfiniteAreNotExpired4() {
    // Get the leases to be used for the test.
    vector<Lease4Ptr> leases = createLeases4();
    Lease4Ptr lease = leases[1];

    // Set valid_lft_ to infinite. Leave the small cltt even it won't happen
    // in the real world to catch more possible issues.
    lease->valid_lft_ = Lease::INFINITY_LFT;

    // Add it to the database.
    ASSERT_TRUE(lmptr_->addLease(leases[1]));

    // Retrieve at most 10 expired leases.
    Lease4Collection expired_leases;
    ASSERT_NO_THROW(lmptr_->getExpiredLeases4(expired_leases, 10));

    // No lease should be returned.
    EXPECT_EQ(0, expired_leases.size());
}

void
GenericLeaseMgrTest::testInfiniteAreNotExpired6() {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();
    Lease6Ptr lease = leases[1];

    // Set valid_lft_ to infinite. Leave the small cltt even it won't happen
    // in the real world to catch more possible issues.
    lease->valid_lft_ = Lease::INFINITY_LFT;

    // Add it to the database.
    ASSERT_TRUE(lmptr_->addLease(leases[1]));

    // Retrieve at most 10 expired leases.
    Lease6Collection expired_leases;
    ASSERT_NO_THROW(lmptr_->getExpiredLeases6(expired_leases, 10));

    // No lease should be returned.
    EXPECT_EQ(0, expired_leases.size());
}

void
GenericLeaseMgrTest::testDeleteExpiredReclaimedLeases4() {
    // Get the leases to be used for the test.
    vector<Lease4Ptr> leases = createLeases4();
    // Make sure we have at least 6 leases there.
    ASSERT_GE(leases.size(), 6);

    time_t current_time = time(NULL);

    // Add them to the database
    for (size_t i = 0; i < leases.size(); ++i) {
        // Mark every other lease as expired.
        if (i % 2 == 0) {
            // Set client last transmission time to the value older than the
            // valid lifetime to make it expired. We also substract the value
            // of 10, 20, 30, 40 etc, depending on the lease index. This
            // simulates different expiration times for various leases.
            leases[i]->cltt_ = current_time - leases[i]->valid_lft_ - i * 10;
            // Set reclaimed state.
            leases[i]->state_ = Lease::STATE_EXPIRED_RECLAIMED;

        } else {
            // Other leases are left as not expired - client last transmission
            // time set to current time.
            leases[i]->cltt_ = current_time;
        }
        ASSERT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Keep reclaimed lease for 15 seconds after expiration.
    const uint32_t lease_affinity_time = 15;

    // Delete expired and reclaimed leases which have expired earlier than
    // 15 seconds ago. This should affect leases with index 2, 3, 4 etc.
    uint64_t deleted_num;
    uint64_t should_delete_num = 0;
    ASSERT_NO_THROW(
        deleted_num = lmptr_->deleteExpiredReclaimedLeases4(lease_affinity_time)
    );

    for (size_t i = 0; i < leases.size(); ++i) {
        // Obtain lease from the server.
        Lease4Ptr lease = lmptr_->getLease4(leases[i]->addr_);

        // If the lease is reclaimed and the expiration time passed more than
        // 15 seconds ago, the lease should have been deleted.
        if (leases[i]->stateExpiredReclaimed() &&
            ((leases[i]->getExpirationTime() + lease_affinity_time) < current_time)) {
            EXPECT_FALSE(lease) << "The following lease should have been"
                " deleted: " << leases[i]->toText();
            ++should_delete_num;
        } else {
            // If the lease is not reclaimed or it has expired less than
            // 15 seconds ago, the lease should still be there.
            EXPECT_TRUE(lease) << "The following lease shouldn't have been"
                " deleted: " << leases[i]->toText();
        }
    }

    // Check that the number of leases deleted is correct.
    EXPECT_EQ(deleted_num, should_delete_num);

    // Make sure we can make another attempt, when there are no more leases
    // to be deleted.
    ASSERT_NO_THROW(
        deleted_num = lmptr_->deleteExpiredReclaimedLeases4(lease_affinity_time)
    );
    // No lease should have been deleted.
    EXPECT_EQ(0, deleted_num);

    // Reopen the database. This to ensure that the leases have been deleted
    // from the persistent storage.
    reopen(V4);

    for (size_t i = 0; i < leases.size(); ++i) {
        /// @todo Leases with empty HW address are dropped by the memfile
        /// backend. We will have to reevaluate if this is right behavior
        /// of the backend when client identifier is present.
        if (leases[i]->hwaddr_ && leases[i]->hwaddr_->hwaddr_.empty()) {
            continue;
        }
        // Obtain lease from the server.
        Lease4Ptr lease = lmptr_->getLease4(leases[i]->addr_);

        // If the lease is reclaimed and the expiration time passed more than
        // 15 seconds ago, the lease should have been deleted.
        if (leases[i]->stateExpiredReclaimed() &&
            ((leases[i]->getExpirationTime() + lease_affinity_time) < current_time)) {
            EXPECT_FALSE(lease) << "The following lease should have been"
                " deleted: " << leases[i]->toText();

        } else {
            // If the lease is not reclaimed or it has expired less than
            // 15 seconds ago, the lease should still be there.
            EXPECT_TRUE(lease) << "The following lease shouldn't have been"
                " deleted: " << leases[i]->toText();
        }
    }
}

void
GenericLeaseMgrTest::testDeleteExpiredReclaimedLeases6() {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();
    // Make sure we have at least 6 leases there.
    ASSERT_GE(leases.size(), 6);

    time_t current_time = time(NULL);

    // Add them to the database
    for (size_t i = 0; i < leases.size(); ++i) {
        // Mark every other lease as expired.
        if (i % 2 == 0) {
            // Set client last transmission time to the value older than the
            // valid lifetime to make it expired. We also substract the value
            // of 10, 20, 30, 40 etc, depending on the lease index. This
            // simulates different expiration times for various leases.
            leases[i]->cltt_ = current_time - leases[i]->valid_lft_ - i * 10;
            // Set reclaimed state.
            leases[i]->state_ = Lease::STATE_EXPIRED_RECLAIMED;

        } else {
            // Other leases are left as not expired - client last transmission
            // time set to current time.
            leases[i]->cltt_ = current_time;
        }
        ASSERT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Keep reclaimed lease for 15 seconds after expiration.
    const uint32_t lease_affinity_time = 15;

    // Delete expired and reclaimed leases which have expired earlier than
    // 15 seconds ago. This should affect leases with index 2, 3, 4 etc.
    uint64_t deleted_num;
    uint64_t should_delete_num = 0;
    ASSERT_NO_THROW(
        deleted_num = lmptr_->deleteExpiredReclaimedLeases6(lease_affinity_time)
    );

    for (size_t i = 0; i < leases.size(); ++i) {
        // Obtain lease from the server.
        Lease6Ptr lease = lmptr_->getLease6(leases[i]->type_, leases[i]->addr_);

        // If the lease is reclaimed and the expiration time passed more than
        // 15 seconds ago, the lease should have been deleted.
        if (leases[i]->stateExpiredReclaimed() &&
            ((leases[i]->getExpirationTime() + lease_affinity_time) < current_time)) {
            EXPECT_FALSE(lease) << "The following lease should have been"
                " deleted: " << leases[i]->toText();
            ++should_delete_num;

        } else {
            // If the lease is not reclaimed or it has expired less than
            // 15 seconds ago, the lease should still be there.
            EXPECT_TRUE(lease) << "The following lease shouldn't have been"
                " deleted: " << leases[i]->toText();
        }
    }
    // Check that the number of deleted leases is correct.
    EXPECT_EQ(should_delete_num, deleted_num);

    // Make sure we can make another attempt, when there are no more leases
    // to be deleted.
    ASSERT_NO_THROW(
        deleted_num = lmptr_->deleteExpiredReclaimedLeases6(lease_affinity_time)
    );
    // No lease should have been deleted.
    EXPECT_EQ(0, deleted_num);

    // Reopen the database. This to ensure that the leases have been deleted
    // from the persistent storage.
    reopen(V6);

    for (size_t i = 0; i < leases.size(); ++i) {
        // Obtain lease from the server.
        Lease6Ptr lease = lmptr_->getLease6(leases[i]->type_, leases[i]->addr_);

        // If the lease is reclaimed and the expiration time passed more than
        // 15 seconds ago, the lease should have been deleted.
        if (leases[i]->stateExpiredReclaimed() &&
            ((leases[i]->getExpirationTime() + lease_affinity_time) < current_time)) {
            EXPECT_FALSE(lease) << "The following lease should have been"
                " deleted: " << leases[i]->toText();

        } else {
            // If the lease is not reclaimed or it has expired less than
            // 15 seconds ago, the lease should still be there.
            EXPECT_TRUE(lease) << "The following lease shouldn't have been"
                " deleted: " << leases[i]->toText();
        }
    }
}

void
GenericLeaseMgrTest::testGetDeclinedLeases4() {
    // Get the leases to be used for the test.
    vector<Lease4Ptr> leases = createLeases4();

    // Make sure we have at least 8 leases there.
    ASSERT_GE(leases.size(), 8);

    // Use the same current time for all leases.
    time_t current_time = time(NULL);

    // Add them to the database
    for (size_t i = 0; i < leases.size(); ++i) {

        // Mark the first half of the leases as DECLINED
        if (i < leases.size()/2) {
            // Mark as declined with 1000 seconds of probation-period
            leases[i]->decline(1000);
        }

        // Mark every second lease as expired.
        if (i % 2 == 0) {
            // Set client last transmission time to the value older than the
            // valid lifetime to make it expired. The expiration time also
            // depends on the lease index, so as we can later check that the
            // leases are ordered by the expiration time.
            leases[i]->cltt_ = current_time - leases[i]->valid_lft_ - 10 - i;

        } else {
            // Set current time as cltt for remaining leases. These leases are
            // not expired.
            leases[i]->cltt_ = current_time;
        }

        ASSERT_TRUE(lmptr_->addLease(leases[i]));
    }

    // The leases are:
    // 0 - declined, expired
    // 1 - declined, not expired
    // 2 - declined, expired
    // 3 - declined, not expired
    // 4 - default, expired
    // 5 - default, not expired
    // 6 - default, expired
    // 7 - default, not expired

    // Retrieve at most 1000 expired leases.
    Lease4Collection expired_leases;
    ASSERT_NO_THROW(lmptr_->getExpiredLeases4(expired_leases, 1000));

    // Leases with even indexes should be returned as expired. It shouldn't
    // matter if the state is default or expired. The getExpiredLeases4 does
    // not pay attention to state, just expiration timers.
    ASSERT_EQ(static_cast<size_t>(leases.size() / 2), expired_leases.size());

    unsigned int declined_state = 0;
    unsigned int default_state = 0;

    // The expired leases should be returned from the most to least expired.
    // This matches the reverse order to which they have been added.
    for (Lease4Collection::reverse_iterator lease = expired_leases.rbegin();
         lease != expired_leases.rend(); ++lease) {
        int index = static_cast<int>(std::distance(expired_leases.rbegin(), lease));
        // Multiple current index by two, because only leases with even indexes
        // should have been returned.
        EXPECT_EQ(leases[2 * index]->addr_, (*lease)->addr_);

        // Count leases in default and declined states
        if ((*lease)->state_ == Lease::STATE_DEFAULT) {
            default_state++;
        } else if ((*lease)->state_ == Lease::STATE_DECLINED) {
            declined_state++;
        }
    }

    // LeaseMgr is supposed to return both default and declined leases
    EXPECT_NE(0, declined_state);
    EXPECT_NE(0, default_state);

    // Update current time for the next test.
    current_time = time(NULL);
    // Also, remove expired leases collected during the previous test.
    expired_leases.clear();

    // This time let's reverse the expiration time and see if they will be returned
    // in the correct order.
    leases = createLeases4();
    for (int i = 0; i < leases.size(); ++i) {

        // Mark the second half of the leases as DECLINED
        if (i >= leases.size()/2) {
            // Mark as declined with 1000 seconds of probation-period
            leases[i]->decline(1000);
        }

        // Update the time of expired leases with even indexes.
        if (i % 2 == 0) {
            leases[i]->cltt_ = current_time - leases[i]->valid_lft_ - 1000 + i;

        } else {
            // Make sure remaining leases remain unexpired.
            leases[i]->cltt_ = current_time + 100;
        }
        ASSERT_NO_THROW(lmptr_->updateLease4(leases[i]));
    }

    // Retrieve expired leases again. The limit of 0 means return all expired
    // leases.
    ASSERT_NO_THROW(lmptr_->getExpiredLeases4(expired_leases, 0));
    // The same leases should be returned.
    ASSERT_EQ(static_cast<size_t>(leases.size() / 2), expired_leases.size());

    // This time leases should be returned in the non-reverse order.
    declined_state = 0;
    default_state = 0;
    for (Lease4Collection::iterator lease = expired_leases.begin();
         lease != expired_leases.end(); ++lease) {
        int index = static_cast<int>(std::distance(expired_leases.begin(), lease));
        EXPECT_EQ(leases[2 * index]->addr_, (*lease)->addr_);

        // Count leases in default and declined states
        if ((*lease)->state_ == Lease::STATE_DEFAULT) {
            default_state++;
        } else if ((*lease)->state_ == Lease::STATE_DECLINED) {
            declined_state++;
        }
    }

    // Check that both declined and default state leases were returned.
    EXPECT_NE(0, declined_state);
    EXPECT_NE(0, default_state);

    // Remove expired leases again.
    expired_leases.clear();

    // Limit the number of leases to be returned to 2.
    ASSERT_NO_THROW(lmptr_->getExpiredLeases4(expired_leases, 2));

    // Make sure we have exactly 2 leases returned.
    ASSERT_EQ(2, expired_leases.size());

    // Test that most expired leases have been returned.
    for (Lease4Collection::iterator lease = expired_leases.begin();
         lease != expired_leases.end(); ++lease) {
        int index = static_cast<int>(std::distance(expired_leases.begin(), lease));
        EXPECT_EQ(leases[2 * index]->addr_, (*lease)->addr_);
    }
}

void
GenericLeaseMgrTest::testGetDeclinedLeases6() {
    // Get the leases to be used for the test.
    vector<Lease6Ptr> leases = createLeases6();

    // Make sure we have at least 8 leases there.
    ASSERT_GE(leases.size(), 8);

    // Use the same current time for all leases.
    time_t current_time = time(NULL);

    // Add them to the database
    for (size_t i = 0; i < leases.size(); ++i) {

        // Mark the first half of the leases as DECLINED
        if (i < leases.size()/2) {
            // Mark as declined with 1000 seconds of probation-period
            leases[i]->decline(1000);
        }

        // Mark every second lease as expired.
        if (i % 2 == 0) {
            // Set client last transmission time to the value older than the
            // valid lifetime to make it expired. The expiration time also
            // depends on the lease index, so as we can later check that the
            // leases are ordered by the expiration time.
            leases[i]->cltt_ = current_time - leases[i]->valid_lft_ - 10 - i;

        } else {
            // Set current time as cltt for remaining leases. These leases are
            // not expired.
            leases[i]->cltt_ = current_time;
        }

        ASSERT_TRUE(lmptr_->addLease(leases[i]));
    }

    // The leases are:
    // 0 - declined, expired
    // 1 - declined, not expired
    // 2 - declined, expired
    // 3 - declined, not expired
    // 4 - default, expired
    // 5 - default, not expired
    // 6 - default, expired
    // 7 - default, not expired

    // Retrieve at most 1000 expired leases.
    Lease6Collection expired_leases;
    ASSERT_NO_THROW(lmptr_->getExpiredLeases6(expired_leases, 1000));

    // Leases with even indexes should be returned as expired. It shouldn't
    // matter if the state is default or expired. The getExpiredLeases4 does
    // not pay attention to state, just expiration timers.
    ASSERT_EQ(static_cast<size_t>(leases.size() / 2), expired_leases.size());

    unsigned int declined_state = 0;
    unsigned int default_state = 0;

    // The expired leases should be returned from the most to least expired.
    // This matches the reverse order to which they have been added.
    for (Lease6Collection::reverse_iterator lease = expired_leases.rbegin();
         lease != expired_leases.rend(); ++lease) {
        int index = static_cast<int>(std::distance(expired_leases.rbegin(), lease));
        // Multiple current index by two, because only leases with even indexes
        // should have been returned.
        EXPECT_EQ(leases[2 * index]->addr_, (*lease)->addr_);

        // Count leases in default and declined states
        if ((*lease)->state_ == Lease::STATE_DEFAULT) {
            default_state++;
        } else if ((*lease)->state_ == Lease::STATE_DECLINED) {
            declined_state++;
        }
    }

    // LeaseMgr is supposed to return both default and declined leases
    EXPECT_NE(0, declined_state);
    EXPECT_NE(0, default_state);

    // Update current time for the next test.
    current_time = time(NULL);
    // Also, remove expired leases collected during the previous test.
    expired_leases.clear();

    // This time let's reverse the expiration time and see if they will be returned
    // in the correct order.
    leases = createLeases6();
    for (int i = 0; i < leases.size(); ++i) {

        // Mark the second half of the leases as DECLINED
        if (i >= leases.size()/2) {
            // Mark as declined with 1000 seconds of probation-period
            leases[i]->decline(1000);
        }

        // Update the time of expired leases with even indexes.
        if (i % 2 == 0) {
            leases[i]->cltt_ = current_time - leases[i]->valid_lft_ - 1000 + i;

        } else {
            // Make sure remaining leases remain unexpired.
            leases[i]->cltt_ = current_time + 100;
        }
        ASSERT_NO_THROW(lmptr_->updateLease6(leases[i]));
    }

    // Retrieve expired leases again. The limit of 0 means return all expired
    // leases.
    ASSERT_NO_THROW(lmptr_->getExpiredLeases6(expired_leases, 0));
    // The same leases should be returned.
    ASSERT_EQ(static_cast<size_t>(leases.size() / 2), expired_leases.size());

    // This time leases should be returned in the non-reverse order.
    declined_state = 0;
    default_state = 0;
    for (Lease6Collection::iterator lease = expired_leases.begin();
         lease != expired_leases.end(); ++lease) {
        int index = static_cast<int>(std::distance(expired_leases.begin(), lease));
        EXPECT_EQ(leases[2 * index]->addr_, (*lease)->addr_);

        // Count leases in default and declined states
        if ((*lease)->state_ == Lease::STATE_DEFAULT) {
            default_state++;
        } else if ((*lease)->state_ == Lease::STATE_DECLINED) {
            declined_state++;
        }
    }

    // Check that both declined and default state leases were returned.
    EXPECT_NE(0, declined_state);
    EXPECT_NE(0, default_state);

    // Remove expired leases again.
    expired_leases.clear();

    // Limit the number of leases to be returned to 2.
    ASSERT_NO_THROW(lmptr_->getExpiredLeases6(expired_leases, 2));

    // Make sure we have exactly 2 leases returned.
    ASSERT_EQ(2, expired_leases.size());

    // Test that most expired leases have been returned.
    for (Lease6Collection::iterator lease = expired_leases.begin();
         lease != expired_leases.end(); ++lease) {
        int index = static_cast<int>(std::distance(expired_leases.begin(), lease));
        EXPECT_EQ(leases[2 * index]->addr_, (*lease)->addr_);
    }
}

void
GenericLeaseMgrTest::checkStat(const std::string& name,
                               const int64_t expected_value) {
    stats::ObservationPtr obs =
        stats::StatsMgr::instance().getObservation(name);

    ASSERT_TRUE(obs) << " stat: " << name << " not found ";
    ASSERT_EQ(expected_value, obs->getInteger().first)
                << " stat: " << name << " value wrong";
}

void
GenericLeaseMgrTest::checkLeaseStats(const StatValMapList& expectedStats) {
    // Global accumulators
    int64_t declined_addresses = 0;
    int64_t reclaimed_declined_addresses = 0;

    // Iterate over all stats for each subnet
    for (int subnet_idx = 0; subnet_idx < expectedStats.size(); ++subnet_idx) {
        BOOST_FOREACH(StatValPair expectedStat, expectedStats[subnet_idx]) {
            // Verify the per subnet value.
            checkStat(stats::StatsMgr::generateName("subnet", subnet_idx+1,
                                                    expectedStat.first),
                      expectedStat.second);

            // Add the value to globals as needed.
            if (expectedStat.first == "declined-addresses") {
                declined_addresses += expectedStat.second;
            } else if (expectedStat.first == "reclaimed-declined-addresses") {
                reclaimed_declined_addresses += expectedStat.second;
            }
        }
    }

    // Verify the globals.
    checkStat("declined-addresses", declined_addresses);
    checkStat("reclaimed-declined-addresses", reclaimed_declined_addresses);
}

Lease4Ptr
GenericLeaseMgrTest::makeLease4(const std::string& address,
                                const SubnetID& subnet_id,
                                const uint32_t state,
                                const ConstElementPtr user_context /* = ConstElementPtr() */) {
    Lease4Ptr lease(new Lease4());

    // set the address
    lease->addr_ = IOAddress(address);

    // make a MAC from the address
    std::vector<uint8_t> hwaddr = lease->addr_.toBytes();
    hwaddr.push_back(0);
    hwaddr.push_back(0);

    lease->hwaddr_.reset(new HWAddr(hwaddr, HTYPE_ETHER));
    lease->valid_lft_ = 86400;
    lease->cltt_ = 168256;
    lease->subnet_id_ = subnet_id;
    lease->state_ = state;
    if (user_context) {
        lease->setContext(user_context);
    }

    EXPECT_TRUE(lmptr_->addLease(lease));
    return lease;
}

Lease6Ptr
GenericLeaseMgrTest::makeLease6(const Lease::Type& type,
                                const std::string& address,
                                uint8_t prefix_len,
                                const SubnetID& subnet_id,
                                const uint32_t state,
                                const ConstElementPtr user_context /* = ConstElementPtr() */) {
    IOAddress addr(address);

    // make a DUID from the address
    std::vector<uint8_t> bytes = addr.toBytes();
    bytes.push_back(prefix_len);

    Lease6Ptr lease(new Lease6(type, addr, DuidPtr(new DUID(bytes)), 77,
                               16000, 24000, subnet_id, HWAddrPtr(),
                               prefix_len));
    lease->state_ = state;
    if (user_context) {
        lease->setContext(user_context);
    }

    EXPECT_TRUE(lmptr_->addLease(lease));
    return lease;
}

void
GenericLeaseMgrTest::logCallback(TrackingLeaseMgr::CallbackType type, SubnetID subnet_id,
                                 LeasePtr lease, bool mt_safe) {
    auto locked = (lmptr_ ? lmptr_->isLocked(lease) : false);
    logs_.push_back(Log{type, subnet_id, lease, mt_safe, locked});
}

int
GenericLeaseMgrTest::countLogs(TrackingLeaseMgr::CallbackType type, SubnetID subnet_id,
                               Lease::Type lease_type) const {
    int count = 0;
    for (auto log : logs_) {
        if ((log.type == type) && (log.subnet_id == subnet_id) && (log.lease->getType() == lease_type)) {
            ++count;
        }
    }
    return (count);
}

void
GenericLeaseMgrTest::testRecountLeaseStats4() {
    using namespace stats;

    StatsMgr::instance().removeAll();

    // Create two subnets.
    int num_subnets = 2;
    CfgSubnets4Ptr cfg = CfgMgr::instance().getStagingCfg()->getCfgSubnets4();
    Subnet4Ptr subnet;
    Pool4Ptr pool;

    subnet.reset(new Subnet4(IOAddress("192.0.1.0"), 24, 1, 2, 3, 1));
    pool.reset(new Pool4(IOAddress("192.0.1.0"), 24));
    subnet->addPool(pool);
    cfg->add(subnet);

    subnet.reset(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 2));
    pool.reset(new Pool4(IOAddress("192.0.2.0"), 24));
    subnet->addPool(pool);
    cfg->add(subnet);


    ASSERT_NO_THROW(CfgMgr::instance().commit());

    // Create the expected stats list.  At this point, the only stat
    // that should be non-zero is total-addresses.
    StatValMapList expectedStats(num_subnets);
    for (int i = 0; i < num_subnets; ++i) {
        expectedStats[i]["total-addresses"] = 256;
        expectedStats[i]["assigned-addresses"] = 0;
        expectedStats[i]["declined-addresses"] = 0;
        expectedStats[i]["reclaimed-declined-addresses"] = 0;
        expectedStats[i]["reclaimed-leases"] = 0;
    }

    // Make sure stats are as expected.
    ASSERT_NO_FATAL_FAILURE(checkLeaseStats(expectedStats));

    // Recount stats.  We should have the same results.
    ASSERT_NO_THROW(lmptr_->recountLeaseStats4());

    // Make sure stats are as expected.
    ASSERT_NO_FATAL_FAILURE(checkLeaseStats(expectedStats));

    // Check that cumulative global stats always exist.
    EXPECT_TRUE(StatsMgr::instance().getObservation("cumulative-assigned-addresses"));

    // Now let's insert some leases into subnet 1.
    int subnet_id = 1;

    // Insert one lease in default state, i.e. assigned.
    Lease4Ptr lease1 = makeLease4("192.0.1.1", subnet_id);

    // Insert one lease in declined state.
    Lease4Ptr lease2 = makeLease4("192.0.1.2", subnet_id, Lease::STATE_DECLINED);

    // Insert one lease in the expired state.
    makeLease4("192.0.1.3", subnet_id, Lease::STATE_EXPIRED_RECLAIMED);

    // Insert another lease in default state, i.e. assigned.
    makeLease4("192.0.1.4", subnet_id);

    // Update the expected stats list for subnet 1.
    expectedStats[subnet_id - 1]["assigned-addresses"] = 3; // 2 + 1 declined
    expectedStats[subnet_id - 1]["declined-addresses"] = 1;

    // Now let's add leases to subnet 2.
    subnet_id = 2;

    // Insert one declined lease.
    makeLease4("192.0.2.2", subnet_id, Lease::STATE_DECLINED);

    // Update the expected stats.
    expectedStats[subnet_id - 1]["assigned-addresses"] = 1; // 0 + 1 declined
    expectedStats[subnet_id - 1]["declined-addresses"] = 1;

    // Now Recount the stats.
    ASSERT_NO_THROW(lmptr_->recountLeaseStats4());

    // Make sure stats are as expected.
    ASSERT_NO_FATAL_FAILURE(checkLeaseStats(expectedStats));

    // Delete some leases from subnet, and update the expected stats.
    EXPECT_TRUE(lmptr_->deleteLease(lease1));
    expectedStats[0]["assigned-addresses"] = 2;

    EXPECT_TRUE(lmptr_->deleteLease(lease2));
    expectedStats[0]["assigned-addresses"] = 1;
    expectedStats[0]["declined-addresses"] = 0;

    // Recount the stats.
    ASSERT_NO_THROW(lmptr_->recountLeaseStats4());

    // Make sure stats are as expected.
    ASSERT_NO_FATAL_FAILURE(checkLeaseStats(expectedStats));
}


void
GenericLeaseMgrTest::testRecountLeaseStats6() {
    using namespace stats;

    StatsMgr::instance().removeAll();

    // Create two subnets.
    int num_subnets = 2;
    CfgSubnets6Ptr cfg = CfgMgr::instance().getStagingCfg()->getCfgSubnets6();
    Subnet6Ptr subnet;
    Pool6Ptr pool;
    StatValMapList expectedStats(num_subnets);

    int subnet_id = 1;
    subnet.reset(new Subnet6(IOAddress("3001:1::"), 64, 1, 2, 3, 4, subnet_id));
    pool.reset(new Pool6(Lease::TYPE_NA, IOAddress("3001:1::"),
                         IOAddress("3001:1::FF")));
    subnet->addPool(pool);
    expectedStats[subnet_id - 1]["total-nas"] = 256;

    pool.reset(new Pool6(Lease::TYPE_PD, IOAddress("3001:1:2::"),96,112));
    subnet->addPool(pool);
    expectedStats[subnet_id - 1]["total-pds"] = 65536;
    cfg->add(subnet);

    ++subnet_id;
    subnet.reset(new Subnet6(IOAddress("2001:db8:1::"), 64, 1, 2, 3, 4,
                             subnet_id));
    pool.reset(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::"), 120));
    subnet->addPool(pool);
    expectedStats[subnet_id - 1]["total-nas"] = 256;
    expectedStats[subnet_id - 1]["total-pds"] = 0;
    cfg->add(subnet);

    ASSERT_NO_THROW(CfgMgr::instance().commit());


    // Create the expected stats list.  At this point, the only stat
    // that should be non-zero is total-nas/total-pds.
    for (int i = 0; i < num_subnets; ++i) {
        expectedStats[i]["assigned-nas"] = 0;
        expectedStats[i]["declined-addresses"] = 0;
        expectedStats[i]["reclaimed-declined-addresses"] = 0;
        expectedStats[i]["assigned-pds"] = 0;
        expectedStats[i]["reclaimed-leases"] = 0;
    }

    // Make sure stats are as expected.
    ASSERT_NO_FATAL_FAILURE(checkLeaseStats(expectedStats));


    // Recount stats.  We should have the same results.
    ASSERT_NO_THROW(lmptr_->recountLeaseStats6());

    // Make sure stats are as expected.
    ASSERT_NO_FATAL_FAILURE(checkLeaseStats(expectedStats));

    // Check that cumulative global stats always exist.
    EXPECT_TRUE(StatsMgr::instance().getObservation("cumulative-assigned-nas"));
    EXPECT_TRUE(StatsMgr::instance().getObservation("cumulative-assigned-pds"));

    // Now let's insert some leases into subnet 1.
    subnet_id = 1;

    // Insert three assigned NAs.
    makeLease6(Lease::TYPE_NA, "3001:1::1", 0, subnet_id);
    Lease6Ptr lease2 = makeLease6(Lease::TYPE_NA, "3001:1::2", 0, subnet_id);
    makeLease6(Lease::TYPE_NA, "3001:1::3", 0, subnet_id);
    expectedStats[subnet_id - 1]["assigned-nas"] = 5; // 3 + 2 declined

    // Insert two declined NAs.
    makeLease6(Lease::TYPE_NA, "3001:1::4", 0, subnet_id,
               Lease::STATE_DECLINED);
    makeLease6(Lease::TYPE_NA, "3001:1::5", 0, subnet_id,
               Lease::STATE_DECLINED);
    expectedStats[subnet_id - 1]["declined-addresses"] = 2;

    // Insert one expired NA.
    makeLease6(Lease::TYPE_NA, "3001:1::6", 0, subnet_id,
               Lease::STATE_EXPIRED_RECLAIMED);

    // Insert two assigned PDs.
    makeLease6(Lease::TYPE_PD, "3001:1:2:0100::", 112, subnet_id);
    makeLease6(Lease::TYPE_PD, "3001:1:2:0200::", 112, subnet_id);
    expectedStats[subnet_id - 1]["assigned-pds"] = 2;

    // Insert two expired PDs.
    makeLease6(Lease::TYPE_PD, "3001:1:2:0300::", 112, subnet_id,
               Lease::STATE_EXPIRED_RECLAIMED);
    makeLease6(Lease::TYPE_PD, "3001:1:2:0400::", 112, subnet_id,
               Lease::STATE_EXPIRED_RECLAIMED);

    // Now let's add leases to subnet 2.
    subnet_id = 2;

    // Insert two assigned NAs.
    makeLease6(Lease::TYPE_NA, "2001:db81::1", 0, subnet_id);
    makeLease6(Lease::TYPE_NA, "2001:db81::2", 0, subnet_id);
    expectedStats[subnet_id - 1]["assigned-nas"] = 3; // 2 + 1 declined

    // Insert one declined NA.
    Lease6Ptr lease3 = makeLease6(Lease::TYPE_NA, "2001:db81::3", 0, subnet_id,
               Lease::STATE_DECLINED);
    expectedStats[subnet_id - 1]["declined-addresses"] = 1;

    // Now Recount the stats.
    ASSERT_NO_THROW(lmptr_->recountLeaseStats6());

    // Make sure stats are as expected.
    ASSERT_NO_FATAL_FAILURE(checkLeaseStats(expectedStats));

    // Delete some leases and update the expected stats.
    EXPECT_TRUE(lmptr_->deleteLease(lease2));
    expectedStats[0]["assigned-nas"] = 4;

    EXPECT_TRUE(lmptr_->deleteLease(lease3));
    expectedStats[1]["assigned-nas"] = 2;
    expectedStats[1]["declined-addresses"] = 0;

    // Recount the stats.
    ASSERT_NO_THROW(lmptr_->recountLeaseStats6());

    // Make sure stats are as expected.
    ASSERT_NO_FATAL_FAILURE(checkLeaseStats(expectedStats));
}

void
GenericLeaseMgrTest::testWipeLeases6() {
    // Get the leases to be used for the test and add to the database
    vector<Lease6Ptr> leases = createLeases6();
    leases[0]->subnet_id_ = 1;
    leases[1]->subnet_id_ = 1;
    leases[2]->subnet_id_ = 1;
    leases[3]->subnet_id_ = 22;
    leases[4]->subnet_id_ = 333;
    leases[5]->subnet_id_ = 333;
    leases[6]->subnet_id_ = 333;
    leases[7]->subnet_id_ = 333;

    for (size_t i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Let's try something simple. There shouldn't be any leases in
    // subnet 2. The keep deleting the leases, perhaps in a different
    // order they were added.
    EXPECT_EQ(0, lmptr_->wipeLeases6(2));
    EXPECT_EQ(4, lmptr_->wipeLeases6(333));
    EXPECT_EQ(3, lmptr_->wipeLeases6(1));
    EXPECT_EQ(1, lmptr_->wipeLeases6(22));

    // All the leases should be gone now. Check that that repeated
    // attempt to delete them will not result in any additional removals.
    EXPECT_EQ(0, lmptr_->wipeLeases6(1));
    EXPECT_EQ(0, lmptr_->wipeLeases6(22));
    EXPECT_EQ(0, lmptr_->wipeLeases6(333));
}

void
GenericLeaseMgrTest::testWipeLeases4() {
    // Get the leases to be used for the test and add to the database
    vector<Lease4Ptr> leases = createLeases4();
    leases[0]->subnet_id_ = 1;
    leases[1]->subnet_id_ = 1;
    leases[2]->subnet_id_ = 1;
    leases[3]->subnet_id_ = 22;
    leases[4]->subnet_id_ = 333;
    leases[5]->subnet_id_ = 333;
    leases[6]->subnet_id_ = 333;
    leases[7]->subnet_id_ = 333;

    for (size_t i = 0; i < leases.size(); ++i) {
        EXPECT_TRUE(lmptr_->addLease(leases[i]));
    }

    // Let's try something simple. There shouldn't be any leases in
    // subnet 2. The keep deleting the leases, perhaps in a different
    // order they were added.
    EXPECT_EQ(0, lmptr_->wipeLeases4(2));
    EXPECT_EQ(4, lmptr_->wipeLeases4(333));
    EXPECT_EQ(3, lmptr_->wipeLeases4(1));
    EXPECT_EQ(1, lmptr_->wipeLeases4(22));

    // All the leases should be gone now. Check that that repeated
    // attempt to delete them will not result in any additional removals.
    EXPECT_EQ(0, lmptr_->wipeLeases4(1));
    EXPECT_EQ(0, lmptr_->wipeLeases4(22));
    EXPECT_EQ(0, lmptr_->wipeLeases4(333));
}

void
LeaseMgrDbLostCallbackTest::SetUp() {
    destroySchema();
    createSchema();
    isc::dhcp::LeaseMgrFactory::destroy();
}

void
LeaseMgrDbLostCallbackTest::TearDown() {
    destroySchema();
    isc::dhcp::LeaseMgrFactory::destroy();
}

void
LeaseMgrDbLostCallbackTest::testNoCallbackOnOpenFailure() {
    DatabaseConnection::db_lost_callback_ =
        std::bind(&LeaseMgrDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    DatabaseConnection::db_recovered_callback_ =
        std::bind(&LeaseMgrDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    DatabaseConnection::db_failed_callback_ =
        std::bind(&LeaseMgrDbLostCallbackTest::db_failed_callback, this, ph::_1);

    ASSERT_THROW(LeaseMgrFactory::create(invalidConnectString()),
                 DbOpenError);

    io_service_->poll();

    EXPECT_EQ(0, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);
}

void
LeaseMgrDbLostCallbackTest::testDbLostAndRecoveredCallback() {
    // Set the connectivity lost callback.
    DatabaseConnection::db_lost_callback_ =
        std::bind(&LeaseMgrDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    DatabaseConnection::db_recovered_callback_ =
        std::bind(&LeaseMgrDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    DatabaseConnection::db_failed_callback_ =
        std::bind(&LeaseMgrDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = validConnectString();
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setLeaseDbAccessString(access);

    // Connect to the lease backend.
    ASSERT_NO_THROW(LeaseMgrFactory::create(access));

    // The most recently opened socket should be for our SQL client.
    int sql_socket = test::findLastSocketFd();
    ASSERT_TRUE(sql_socket > -1);

    // Verify we can execute a query.  We do not care if
    // we find a lease or not.
    LeaseMgr& lm = LeaseMgrFactory::instance();

    Lease4Ptr lease;
    ASSERT_NO_THROW(lease = lm.getLease4(IOAddress("192.0.1.0")));

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(lease = lm.getLease4(IOAddress("192.0.1.0")),
                 DbConnectionUnusable);

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);
}

void
LeaseMgrDbLostCallbackTest::testDbLostAndFailedCallback() {
    // Set the connectivity lost callback.
    DatabaseConnection::db_lost_callback_ =
        std::bind(&LeaseMgrDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    DatabaseConnection::db_recovered_callback_ =
        std::bind(&LeaseMgrDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    DatabaseConnection::db_failed_callback_ =
        std::bind(&LeaseMgrDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = validConnectString();
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setLeaseDbAccessString(access);

    // Connect to the lease backend.
    ASSERT_NO_THROW(LeaseMgrFactory::create(access));

    // The most recently opened socket should be for our SQL client.
    int sql_socket = test::findLastSocketFd();
    ASSERT_TRUE(sql_socket > -1);

    // Verify we can execute a query.  We do not care if
    // we find a lease or not.
    LeaseMgr& lm = LeaseMgrFactory::instance();

    Lease4Ptr lease;
    ASSERT_NO_THROW(lease = lm.getLease4(IOAddress("192.0.1.0")));

    access = invalidConnectString();
    // by adding an invalid access will cause the manager factory to throw
    // resulting in failure to recreate the manager
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setLeaseDbAccessString(access);

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(lease = lm.getLease4(IOAddress("192.0.1.0")),
                 DbConnectionUnusable);

    io_service_->poll();

    // Our lost and failed connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);
}

void
LeaseMgrDbLostCallbackTest::testDbLostAndRecoveredAfterTimeoutCallback() {
    // Set the connectivity lost callback.
    DatabaseConnection::db_lost_callback_ =
        std::bind(&LeaseMgrDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    DatabaseConnection::db_recovered_callback_ =
        std::bind(&LeaseMgrDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    DatabaseConnection::db_failed_callback_ =
        std::bind(&LeaseMgrDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = validConnectString();
    std::string extra = " max-reconnect-tries=3 reconnect-wait-time=1";
    access += extra;
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setLeaseDbAccessString(access);

    // Connect to the lease backend.
    ASSERT_NO_THROW(LeaseMgrFactory::create(access));

    // The most recently opened socket should be for our SQL client.
    int sql_socket = test::findLastSocketFd();
    ASSERT_TRUE(sql_socket > -1);

    // Verify we can execute a query.  We do not care if
    // we find a lease or not.
    LeaseMgr& lm = LeaseMgrFactory::instance();

    Lease4Ptr lease;
    ASSERT_NO_THROW(lease = lm.getLease4(IOAddress("192.0.1.0")));

    access = invalidConnectString();
    access += extra;
    // by adding an invalid access will cause the manager factory to throw
    // resulting in failure to recreate the manager
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setLeaseDbAccessString(access);

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(lease = lm.getLease4(IOAddress("192.0.1.0")),
                 DbConnectionUnusable);

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    access = validConnectString();
    access += extra;
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setLeaseDbAccessString(access);

    sleep(1);

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    sleep(1);

    io_service_->poll();

    // No callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);
}

void
LeaseMgrDbLostCallbackTest::testDbLostAndFailedAfterTimeoutCallback() {
    // Set the connectivity lost callback.
    DatabaseConnection::db_lost_callback_ =
        std::bind(&LeaseMgrDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    DatabaseConnection::db_recovered_callback_ =
        std::bind(&LeaseMgrDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    DatabaseConnection::db_failed_callback_ =
        std::bind(&LeaseMgrDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = validConnectString();
    std::string extra = " max-reconnect-tries=3 reconnect-wait-time=1";
    access += extra;
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setLeaseDbAccessString(access);

    // Connect to the lease backend.
    ASSERT_NO_THROW(LeaseMgrFactory::create(access));

    // The most recently opened socket should be for our SQL client.
    int sql_socket = test::findLastSocketFd();
    ASSERT_TRUE(sql_socket > -1);

    // Verify we can execute a query.  We do not care if
    // we find a lease or not.
    LeaseMgr& lm = LeaseMgrFactory::instance();

    Lease4Ptr lease;
    ASSERT_NO_THROW(lease = lm.getLease4(IOAddress("192.0.1.0")));

    access = invalidConnectString();
    access += extra;
    // by adding an invalid access will cause the manager factory to throw
    // resulting in failure to recreate the manager
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setLeaseDbAccessString(access);

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(lease = lm.getLease4(IOAddress("192.0.1.0")),
                 DbConnectionUnusable);

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    sleep(1);

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    sleep(1);

    io_service_->poll();

    // Our lost and failed connectivity callback should have been invoked.
    EXPECT_EQ(3, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);
}

void
GenericLeaseMgrTest::checkLeaseRange(const Lease4Collection& returned,
                                     const std::vector<std::string>& expected_addresses) {
    ASSERT_EQ(expected_addresses.size(), returned.size());

    for (auto a = returned.cbegin(); a != returned.cend(); ++a) {
        EXPECT_EQ(expected_addresses[std::distance(returned.cbegin(), a)],
                  (*a)->addr_.toText());
    }
}

void
GenericLeaseMgrTest::checkQueryAgainstRowSet(const LeaseStatsQueryPtr& query,
                                             const RowSet& expected_rows) {
    ASSERT_TRUE(query) << "query is null";

    int rows_matched = 0;
    LeaseStatsRow row;
    while (query->getNextRow(row)) {
        auto found_row = expected_rows.find(row);
        if (found_row == expected_rows.end()) {
            ADD_FAILURE() << "query row not in expected set"
                << " id: " << row.subnet_id_
                << " type: " << row.lease_type_
                << " state: " << row.lease_state_
                << " count: " << row.state_count_;
        } else {
            if (row.state_count_ != (*found_row).state_count_) {
                ADD_FAILURE() << "row count wrong for"
                              << " id: " << row.subnet_id_
                              << " type: " << row.lease_type_
                              << " state: " << row.lease_state_
                              << " count: " << row.state_count_
                              << "; expected: " << (*found_row).state_count_;
            } else {
                ++rows_matched;
            }
        }
    }

    ASSERT_EQ(rows_matched, expected_rows.size()) << "rows mismatched";
}

void
GenericLeaseMgrTest::testLeaseStatsQuery4() {
    // Create three subnets.
    CfgSubnets4Ptr cfg = CfgMgr::instance().getStagingCfg()->getCfgSubnets4();
    Subnet4Ptr subnet;
    Pool4Ptr pool;

    subnet.reset(new Subnet4(IOAddress("192.0.1.0"), 24, 1, 2, 3, 1));
    pool.reset(new Pool4(IOAddress("192.0.1.0"), 24));
    subnet->addPool(pool);
    cfg->add(subnet);

    subnet.reset(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 2));
    pool.reset(new Pool4(IOAddress("192.0.2.0"), 24));
    subnet->addPool(pool);
    cfg->add(subnet);

    subnet.reset(new Subnet4(IOAddress("192.0.3.0"), 24, 1, 2, 3, 3));
    pool.reset(new Pool4(IOAddress("192.0.3.0"), 24));
    subnet->addPool(pool);
    cfg->add(subnet);

    ASSERT_NO_THROW(CfgMgr::instance().commit());

    // Make sure invalid values throw.
    LeaseStatsQueryPtr query;
    ASSERT_THROW(query = lmptr_->startSubnetLeaseStatsQuery4(0), BadValue);
    ASSERT_THROW(query = lmptr_->startSubnetRangeLeaseStatsQuery4(0,1), BadValue);
    ASSERT_THROW(query = lmptr_->startSubnetRangeLeaseStatsQuery4(1,0), BadValue);
    ASSERT_THROW(query = lmptr_->startSubnetRangeLeaseStatsQuery4(10,1), BadValue);

    // Start tests with an empty expected row set.
    RowSet expected_rows;

    // Before we add leases, test an empty return for get all subnets
    {
        SCOPED_TRACE("GET ALL WITH NO LEASES");
        ASSERT_NO_THROW(query = lmptr_->startLeaseStatsQuery4());
        checkQueryAgainstRowSet(query, expected_rows);
    }

    // Now let's insert some leases into subnet 1.
    // Two leases in  the default state, i.e. assigned.
    // One lease in declined state.
    // One lease in the expired state.
    int subnet_id = 1;
    makeLease4("192.0.1.1", subnet_id);
    makeLease4("192.0.1.2", subnet_id, Lease::STATE_DECLINED);
    makeLease4("192.0.1.3", subnet_id, Lease::STATE_EXPIRED_RECLAIMED);
    makeLease4("192.0.1.4", subnet_id);

    // Now let's add leases to subnet 2.
    // One declined lease.
    subnet_id = 2;
    makeLease4("192.0.2.2", subnet_id, Lease::STATE_DECLINED);

    // Now add leases to subnet 3
    // Two leases in default state, i.e. assigned.
    // One declined lease.
    subnet_id = 3;
    makeLease4("192.0.3.1", subnet_id);
    makeLease4("192.0.3.2", subnet_id);
    makeLease4("192.0.3.3", subnet_id, Lease::STATE_DECLINED);

    // Test single subnet for non-matching subnet
    {
        SCOPED_TRACE("NO MATCHING SUBNET");
        ASSERT_NO_THROW(query = lmptr_->startSubnetLeaseStatsQuery4(777));
        checkQueryAgainstRowSet(query, expected_rows);
    }

    // Test an empty range
    {
        SCOPED_TRACE("EMPTY SUBNET RANGE");
        ASSERT_NO_THROW(query = lmptr_->startSubnetRangeLeaseStatsQuery4(777, 900));
        checkQueryAgainstRowSet(query, expected_rows);
    }

    // Test a single subnet
    {
        SCOPED_TRACE("SINGLE SUBNET");
        // Add expected rows for Subnet 2
        expected_rows.insert(LeaseStatsRow(2, Lease::STATE_DECLINED, 1));
        // Start the query
        ASSERT_NO_THROW(query = lmptr_->startSubnetLeaseStatsQuery4(2));
        // Verify contents
        checkQueryAgainstRowSet(query, expected_rows);
    }

    // Test a range of subnets
    {
        SCOPED_TRACE("SUBNET RANGE");
        // Add expected rows for Subnet 3
        expected_rows.insert(LeaseStatsRow(3, Lease::STATE_DEFAULT, 2));
        expected_rows.insert(LeaseStatsRow(3, Lease::STATE_DECLINED, 1));
        // Start the query
        ASSERT_NO_THROW(query = lmptr_->startSubnetRangeLeaseStatsQuery4(2,3));
        // Verify contents
        checkQueryAgainstRowSet(query, expected_rows);
    }

    // Test all subnets
    {
        SCOPED_TRACE("ALL SUBNETS");
        // Add expected rows for Subnet 1
        expected_rows.insert(LeaseStatsRow(1, Lease::STATE_DEFAULT, 2));
        expected_rows.insert(LeaseStatsRow(1, Lease::STATE_DECLINED, 1));
        // Start the query
        ASSERT_NO_THROW(query = lmptr_->startLeaseStatsQuery4());
        // Verify contents
        checkQueryAgainstRowSet(query, expected_rows);
    }
}

void
GenericLeaseMgrTest::testLeaseStatsQuery6() {
    // Create three subnets.
    CfgSubnets6Ptr cfg = CfgMgr::instance().getStagingCfg()->getCfgSubnets6();
    Subnet6Ptr subnet;
    Pool6Ptr pool;

    int subnet_id = 1;
    subnet.reset(new Subnet6(IOAddress("3001:1::"), 64, 1, 2, 3, 4, subnet_id));
    pool.reset(new Pool6(Lease::TYPE_NA, IOAddress("3001:1::"),
                         IOAddress("3001:1::FF")));
    subnet->addPool(pool);

    pool.reset(new Pool6(Lease::TYPE_PD, IOAddress("3001:1:2::"),96,112));
    subnet->addPool(pool);
    cfg->add(subnet);

    ++subnet_id;
    subnet.reset(new Subnet6(IOAddress("2001:db8:1::"), 64, 1, 2, 3, 4,
                             subnet_id));
    pool.reset(new Pool6(Lease::TYPE_NA, IOAddress("2001:db8:1::"), 120));
    subnet->addPool(pool);
    cfg->add(subnet);

    ++subnet_id;
    subnet.reset(new Subnet6(IOAddress("2002:db8:1::"), 64, 1, 2, 3, 4,
                             subnet_id));
    pool.reset(new Pool6(Lease::TYPE_NA, IOAddress("2002:db8:1::"), 120));
    subnet->addPool(pool);
    cfg->add(subnet);

    ASSERT_NO_THROW(CfgMgr::instance().commit());

    // Make sure invalid values throw.
    LeaseStatsQueryPtr query;
    ASSERT_THROW(query = lmptr_->startSubnetLeaseStatsQuery6(0), BadValue);
    ASSERT_THROW(query = lmptr_->startSubnetRangeLeaseStatsQuery6(0,1), BadValue);
    ASSERT_THROW(query = lmptr_->startSubnetRangeLeaseStatsQuery6(1,0), BadValue);
    ASSERT_THROW(query = lmptr_->startSubnetRangeLeaseStatsQuery6(10,1), BadValue);

    // Start tests with an empty expected row set.
    RowSet expected_rows;

    // Before we add leases, test an empty return for get all subnets
    {
        SCOPED_TRACE("GET ALL WITH NO LEASES");
        ASSERT_NO_THROW(query = lmptr_->startLeaseStatsQuery6());
        checkQueryAgainstRowSet(query, expected_rows);
    }


    // Now let's insert some leases into subnet 1.
    // Three assigned NAs.
    // Two declined NAs.
    // One expired NA.
    // Two assigned PDs.
    // Two expired PDs.
    subnet_id = 1;
    makeLease6(Lease::TYPE_NA, "3001:1::1", 0, subnet_id);
    makeLease6(Lease::TYPE_NA, "3001:1::2", 0, subnet_id);
    makeLease6(Lease::TYPE_NA, "3001:1::3", 0, subnet_id);
    makeLease6(Lease::TYPE_NA, "3001:1::4", 0, subnet_id,
               Lease::STATE_DECLINED);
    makeLease6(Lease::TYPE_NA, "3001:1::5", 0, subnet_id,
               Lease::STATE_DECLINED);
    makeLease6(Lease::TYPE_NA, "3001:1::6", 0, subnet_id,
               Lease::STATE_EXPIRED_RECLAIMED);
    makeLease6(Lease::TYPE_PD, "3001:1:2:0100::", 112, subnet_id);
    makeLease6(Lease::TYPE_PD, "3001:1:2:0200::", 112, subnet_id);
    makeLease6(Lease::TYPE_PD, "3001:1:2:0300::", 112, subnet_id,
               Lease::STATE_EXPIRED_RECLAIMED);
    makeLease6(Lease::TYPE_PD, "3001:1:2:0400::", 112, subnet_id,
               Lease::STATE_EXPIRED_RECLAIMED);

    // Now let's add leases to subnet 2.
    // Two assigned NAs
    // One declined NAs
    subnet_id = 2;
    makeLease6(Lease::TYPE_NA, "2001:db81::1", 0, subnet_id);
    makeLease6(Lease::TYPE_NA, "2001:db81::2", 0, subnet_id);
    makeLease6(Lease::TYPE_NA, "2001:db81::3", 0, subnet_id,
               Lease::STATE_DECLINED);

    // Now let's add leases to subnet 3.
    // Two assigned NAs
    // One declined NAs
    subnet_id = 3;
    makeLease6(Lease::TYPE_NA, "2002:db81::1", 0, subnet_id);
    makeLease6(Lease::TYPE_NA, "2002:db81::2", 0, subnet_id);
    makeLease6(Lease::TYPE_NA, "2002:db81::3", 0, subnet_id,
               Lease::STATE_DECLINED);

    // Test single subnet for non-matching subnet
    {
        SCOPED_TRACE("NO MATCHING SUBNET");
        ASSERT_NO_THROW(query = lmptr_->startSubnetLeaseStatsQuery6(777));
        checkQueryAgainstRowSet(query, expected_rows);
    }

    // Test an empty range
    {
        SCOPED_TRACE("EMPTY SUBNET RANGE");
        ASSERT_NO_THROW(query = lmptr_->startSubnetRangeLeaseStatsQuery6(777, 900));
        checkQueryAgainstRowSet(query, expected_rows);
    }

    // Test a single subnet
    {
        SCOPED_TRACE("SINGLE SUBNET");
        // Add expected row for Subnet 2
        expected_rows.insert(LeaseStatsRow(2, Lease::TYPE_NA, Lease::STATE_DEFAULT, 2));
        expected_rows.insert(LeaseStatsRow(2, Lease::TYPE_NA, Lease::STATE_DECLINED, 1));
        // Start the query
        ASSERT_NO_THROW(query = lmptr_->startSubnetLeaseStatsQuery6(2));
        // Verify contents
        checkQueryAgainstRowSet(query, expected_rows);
    }

    // Test a range of subnets
    {
        SCOPED_TRACE("SUBNET RANGE");
        // Add expected rows for Subnet 3
        expected_rows.insert(LeaseStatsRow(3, Lease::TYPE_NA, Lease::STATE_DEFAULT, 2));
        expected_rows.insert(LeaseStatsRow(3, Lease::TYPE_NA, Lease::STATE_DECLINED, 1));
        // Start the query
        ASSERT_NO_THROW(query = lmptr_->startSubnetRangeLeaseStatsQuery6(2,3));
        // Verify contents
        checkQueryAgainstRowSet(query, expected_rows);
    }

    // Test all subnets
    {
        SCOPED_TRACE("ALL SUBNETS");
        // Add expected rows for Subnet 1
        expected_rows.insert(LeaseStatsRow(1, Lease::TYPE_NA, Lease::STATE_DEFAULT, 3));
        expected_rows.insert(LeaseStatsRow(1, Lease::TYPE_NA, Lease::STATE_DECLINED, 2));
        expected_rows.insert(LeaseStatsRow(1, Lease::TYPE_PD, Lease::STATE_DEFAULT, 2));
        // Start the query
        ASSERT_NO_THROW(query = lmptr_->startLeaseStatsQuery6());

        // Verify contents
        checkQueryAgainstRowSet(query, expected_rows);
    }
}

void
GenericLeaseMgrTest::testLeaseStatsQueryAttribution4() {
    // Create two subnets for the same range.
    CfgSubnets4Ptr cfg = CfgMgr::instance().getStagingCfg()->getCfgSubnets4();
    Subnet4Ptr subnet;

    subnet.reset(new Subnet4(IOAddress("192.0.1.0"), 24, 1, 2, 3, 1));
    cfg->add(subnet);

    // Note it is even allowed to use 192.0.1.1/24 here...
    subnet.reset(new Subnet4(IOAddress("192.0.1.0"), 25, 1, 2, 3, 2));
    cfg->add(subnet);

    ASSERT_NO_THROW(CfgMgr::instance().commit());

    LeaseStatsQueryPtr query;
    RowSet expected_rows;

    // Now let's insert two leases into subnet 1.
    int subnet_id = 1;
    makeLease4("192.0.1.1", subnet_id);
    Lease4Ptr lease = makeLease4("192.0.1.2", subnet_id);

    // And one lease into subnet 2.
    subnet_id = 2;
    makeLease4("192.0.1.3", subnet_id);

    // Move a lease to the second subnet.
    lease->subnet_id_ = subnet_id;
    EXPECT_NO_THROW(lmptr_->updateLease4(lease));

    // Add expected rows for Subnets.
    expected_rows.insert(LeaseStatsRow(1, Lease::STATE_DEFAULT, 1));
    expected_rows.insert(LeaseStatsRow(2, Lease::STATE_DEFAULT, 2));

    // Start the query
    ASSERT_NO_THROW(query = lmptr_->startLeaseStatsQuery4());

    // Verify contents
    checkQueryAgainstRowSet(query, expected_rows);
}

void
GenericLeaseMgrTest::testLeaseStatsQueryAttribution6() {
    // Create two subnets.
    CfgSubnets6Ptr cfg = CfgMgr::instance().getStagingCfg()->getCfgSubnets6();
    Subnet6Ptr subnet;

    int subnet_id = 1;
    subnet.reset(new Subnet6(IOAddress("2001:db8:1::"), 64, 1, 2, 3, 4,
                             subnet_id));
    cfg->add(subnet);

    ++subnet_id;
    subnet.reset(new Subnet6(IOAddress("2001:db8:1::1"), 64, 1, 2, 3, 4,
                             subnet_id));
    cfg->add(subnet);

    ASSERT_NO_THROW(CfgMgr::instance().commit());

    LeaseStatsQueryPtr query;
    RowSet expected_rows;

    // Now let's insert two leases into subnet 1.
    subnet_id = 1;
    makeLease6(Lease::TYPE_NA, "2001:db81::1", 0, subnet_id);
    Lease6Ptr lease = makeLease6(Lease::TYPE_NA, "2001:db81::2", 0, subnet_id);

    // And one lease into subnet 2.
    subnet_id = 2;
    makeLease6(Lease::TYPE_NA, "2001:db81::3", 0, subnet_id);

    // Move a lease to the second subnet.
    lease->subnet_id_ = subnet_id;
    EXPECT_NO_THROW(lmptr_->updateLease6(lease));

    // Add expected rows for Subnets.
    expected_rows.insert(LeaseStatsRow(1, Lease::TYPE_NA,
                                       Lease::STATE_DEFAULT, 1));
    expected_rows.insert(LeaseStatsRow(2, Lease::TYPE_NA,
                                       Lease::STATE_DEFAULT, 2));
    // Start the query
    ASSERT_NO_THROW(query = lmptr_->startLeaseStatsQuery6());

    // Verify contents
    checkQueryAgainstRowSet(query, expected_rows);
}

void
GenericLeaseMgrTest::testLeaseLimits4() {
    std::string text;
    ElementPtr user_context;

    // -- A limit of 0 always denies a lease. --

    user_context = Element::fromJSON(R"({ "ISC": { "limits": {
        "client-classes": [ { "name": "foo", "address-limit": 0 } ] } } })");
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits4(user_context));
    EXPECT_EQ(text, "address limit 0 for client class \"foo\", current lease count 0");

    user_context = Element::fromJSON(R"({ "ISC": { "limits": {
        "subnet": { "id": 1, "address-limit": 0 } } } })");
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits4(user_context));
    EXPECT_EQ(text, "address limit 0 for subnet ID 1, current lease count 0");

    // -- A limit of 1 with no leases should allow a lease. --

    user_context = Element::fromJSON(R"({ "ISC": { "limits": {
        "client-classes": [ { "name": "foo", "address-limit": 1 } ] } } })");
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits4(user_context));
    EXPECT_EQ(text, "");

    user_context = Element::fromJSON(R"({ "ISC": { "limits": {
        "subnet": { "id": 1, "address-limit": 1 } } } })");
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits4(user_context));
    EXPECT_EQ(text, "");

    // -- A limit of 1 with 1 current lease should deny further leases. --

    makeLease4("192.0.1.1", 1, Lease::STATE_DEFAULT, Element::fromJSON(
        R"({ "ISC": { "client-classes": [ "foo" ] } })"));

    // Since we did not go through allocation engine stats won't be altered.
    ASSERT_NO_THROW(lmptr_->recountLeaseStats4());

    user_context = Element::fromJSON(R"({ "ISC": { "limits": {
        "client-classes": [ { "name": "foo", "address-limit": 1 } ] } } })");
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits4(user_context));
    EXPECT_EQ(text, "address limit 1 for client class \"foo\", current lease count 1");

    user_context = Element::fromJSON(R"({ "ISC": { "limits": {
        "subnet": { "id": 1, "address-limit": 1 } } } })");
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits4(user_context));
    EXPECT_EQ(text, "address limit 1 for subnet ID 1, current lease count 1");
}

void
GenericLeaseMgrTest::testLeaseLimits6() {
    std::string text;
    ElementPtr user_context;

    // -- A limit of 0 always denies a lease. --

    user_context = Element::fromJSON(R"({ "ISC": { "limits": {
        "client-classes": [ { "name": "foo", "address-limit": 0 } ] } } })");
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits6(user_context));
    EXPECT_EQ(text, "address limit 0 for client class \"foo\", current lease count 0");

    user_context = Element::fromJSON(R"({ "ISC": { "limits": {
        "subnet": { "id": 1, "address-limit": 0 } } } })");
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits6(user_context));
    EXPECT_EQ(text, "address limit 0 for subnet ID 1, current lease count 0");

    // -- A limit of 1 with no leases should allow a lease. --

    user_context = Element::fromJSON(R"({ "ISC": { "limits": {
        "client-classes": [ { "name": "foo", "address-limit": 1 } ] } } })");
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits6(user_context));
    EXPECT_EQ(text, "");

    user_context = Element::fromJSON(R"({ "ISC": { "limits": {
        "subnet": { "id": 1, "address-limit": 1 } } } })");
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits6(user_context));
    EXPECT_EQ(text, "");

    // -- A limit of 1 with 1 current lease should deny further leases. --
    makeLease6(Lease::TYPE_NA, "2001:db8::", 0, 1, Lease::STATE_DEFAULT, Element::fromJSON(
        R"({ "ISC": { "client-classes": [ "foo" ] } })"));

    makeLease6(Lease::TYPE_PD, "2001:db8:1::", 64, 1, Lease::STATE_DEFAULT, Element::fromJSON(
        R"({ "ISC": { "client-classes": [ "foo" ] } })"));

    // Since we did not go through allocation engine stats won't be altered.
    ASSERT_NO_THROW(lmptr_->recountLeaseStats6());

    user_context = Element::fromJSON(R"({ "ISC": { "limits": {
        "client-classes": [ { "name": "foo", "address-limit": 1 } ] } } })");
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits6(user_context));
    EXPECT_EQ(text, "address limit 1 for client class \"foo\", current lease count 1");

    user_context = Element::fromJSON(R"({ "ISC": { "limits": {
        "client-classes": [ { "name": "foo", "prefix-limit": 1 } ] } } })");
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits6(user_context));
    EXPECT_EQ(text, "prefix limit 1 for client class \"foo\", current lease count 1");

    user_context = Element::fromJSON(R"({ "ISC": { "limits": {
        "subnet": { "id": 1, "address-limit": 1 } } } })");
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits6(user_context));
    EXPECT_EQ(text, "address limit 1 for subnet ID 1, current lease count 1");

    user_context = Element::fromJSON(R"({ "ISC": { "limits": {
        "subnet": { "id": 1, "prefix-limit": 1 } } } })");
    ASSERT_NO_THROW_LOG(text = LeaseMgrFactory::instance().checkLimits6(user_context));
    EXPECT_EQ(text, "prefix limit 1 for subnet ID 1, current lease count 1");
}

ElementPtr
GenericLeaseMgrTest::makeContextWithClasses(const std::list<ClientClass>& classes) {
    ElementPtr ctx = Element::createMap();
    if (classes.size()) {
        ElementPtr clist = Element::createList();
        for (auto client_class : classes ) {
            clist->add(Element::create(client_class));
        }

        ElementPtr client_classes = Element::createMap();
        client_classes->set("client-classes", clist);
        ctx->set("ISC", client_classes);
    }

    return (ctx);
}

void
GenericLeaseMgrTest::testClassLeaseCount4() {
    // Make user-contexts with different class lists.
    std::list<ClientClass> classes1{"water"};
    ElementPtr ctx1 = makeContextWithClasses(classes1);

    std::list<ClientClass> classes2{"melon"};
    ElementPtr ctx2 = makeContextWithClasses(classes2);

    // Counts should be 0.
    EXPECT_EQ(0, lmptr_->getClassLeaseCount("water"));
    EXPECT_EQ(0, lmptr_->getClassLeaseCount("melon"));

    // Create a lease to add to the lease store.
    vector<Lease4Ptr> leases = createLeases4();
    Lease4Ptr lease = leases[1];

    // Set the lease state to STATE_DEFAULT so it classes should be counted.
    lease->state_ = Lease::STATE_DEFAULT;

    // Add class list 1 to the lease.
    lease->setContext(ctx1);

    // Add the lease to the lease store and verify class lease counts.
    ASSERT_NO_THROW_LOG(lmptr_->addLease(lease));
    EXPECT_EQ(1, lmptr_->getClassLeaseCount("water"));
    EXPECT_EQ(0, lmptr_->getClassLeaseCount("melon"));

    // Re-fetch lease. This returns a copy of the persisted lease, which is
    // what Kea logic always does. Fetches a copy.  Otherwise we're changing
    // the persisted lease which would make old and new the same thing.
    lease = lmptr_->getLease4(lease->addr_);
    ASSERT_TRUE(lease);

    // Change the class list.
    lease->setContext(ctx2);

    // Update the lease in the lease store and verify class lease counts.
    ASSERT_NO_THROW_LOG(lmptr_->updateLease4(lease));
    EXPECT_EQ(0, lmptr_->getClassLeaseCount("water"));
    EXPECT_EQ(1, lmptr_->getClassLeaseCount("melon"));

    lease = lmptr_->getLease4(lease->addr_);
    ASSERT_TRUE(lease);

    // Now delete the lease from the store and verify counts.
    ASSERT_NO_THROW_LOG(lmptr_->deleteLease(lease));
    EXPECT_EQ(0, lmptr_->getClassLeaseCount("water"));
    EXPECT_EQ(0, lmptr_->getClassLeaseCount("melon"));

    lease = lmptr_->getLease4(lease->addr_);
    ASSERT_FALSE(lease);
}

void
GenericLeaseMgrTest::testClassLeaseCount6(Lease::Type ltype) {
    ASSERT_TRUE(ltype == Lease::TYPE_NA || ltype == Lease::TYPE_PD);

    // Make user-contexts with different class lists.
    std::list<ClientClass> classes1{"water"};
    ElementPtr ctx1 = makeContextWithClasses(classes1);

    std::list<ClientClass> classes2{"melon"};
    ElementPtr ctx2 = makeContextWithClasses(classes2);

    // Counts should be 0.
    EXPECT_EQ(0, lmptr_->getClassLeaseCount("water", ltype));
    EXPECT_EQ(0, lmptr_->getClassLeaseCount("melon", ltype));

    // Create a lease to add to the lease store.
    vector<Lease6Ptr> leases = createLeases6();
    Lease6Ptr lease = leases[1];
    lease->type_ = ltype;

    // Set the lease state to STATE_DEFAULT so it classes should be counted.
    lease->state_ = Lease::STATE_DEFAULT;

    // Add class list 1 to the lease.
    lease->setContext(ctx1);

    // Add the lease to the lease store and verify class lease counts.
    ASSERT_NO_THROW_LOG(lmptr_->addLease(lease));
    EXPECT_EQ(1, lmptr_->getClassLeaseCount("water", ltype));
    EXPECT_EQ(0, lmptr_->getClassLeaseCount("melon", ltype));

    // Re-fetch lease. This returns a copy of the persisted lease, which is
    // what Kea logic always does. Fetches a copy.  Otherwise we're changing
    // the persisted lease which would make old and new the same thing.
    lease = lmptr_->getLease6(ltype, lease->addr_);
    ASSERT_TRUE(lease);

    // Change the class list.
    lease->setContext(ctx2);

    // Update the lease in the lease store and verify class lease counts.
    ASSERT_NO_THROW_LOG(lmptr_->updateLease6(lease));
    EXPECT_EQ(0, lmptr_->getClassLeaseCount("water", ltype));
    EXPECT_EQ(1, lmptr_->getClassLeaseCount("melon", ltype));

    lease = lmptr_->getLease6(ltype, lease->addr_);
    ASSERT_TRUE(lease);

    // Now delete the lease from the store and verify counts.
    ASSERT_NO_THROW_LOG(lmptr_->deleteLease(lease));
    EXPECT_EQ(0, lmptr_->getClassLeaseCount("water", ltype));
    EXPECT_EQ(0, lmptr_->getClassLeaseCount("melon", ltype));

    lease = lmptr_->getLease6(ltype, lease->addr_);
    ASSERT_FALSE(lease);
}

void
GenericLeaseMgrTest::testTrackAddLease4(bool expect_locked, bool expect_mt_safe) {
    // Register a callback for all subnets.
    lmptr_->registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, "flq",
                             SUBNET_ID_GLOBAL, Lease::TYPE_V4,
                             std::bind(&GenericLeaseMgrTest::logCallback,
                                       this,
                                       TrackingLeaseMgr::TRACK_ADD_LEASE,
                                       SUBNET_ID_GLOBAL,
                                       ph::_1,
                                       ph::_2));
    // Add a lease. It should trigger the callback.
    Lease4Ptr lease = initializeLease4(straddress4_[1]);
    EXPECT_TRUE(lmptr_->addLease(lease));

    // Make sure that the callback has been invoked.
    ASSERT_EQ(1, logs_.size());

    // This flag should be false for the Memfile backend and true
    // for the SQL backends.
    if (expect_locked) {
        EXPECT_TRUE(logs_[0].locked);
    } else {
        EXPECT_FALSE(logs_[0].locked);
    }
    // This flag should be set to true for the Memfile backends.
    // It should be false for other backends. If the backends do
    // not provide the MT-safe context, the callbacks must protect
    // against the concurrent access on their own.
    if (expect_mt_safe) {
        EXPECT_TRUE(logs_[0].mt_safe);
    } else {
        EXPECT_FALSE(logs_[0].mt_safe);
    }

    // The lease locks should have been released.
    EXPECT_FALSE(lmptr_->isLocked(lease));
}

void
GenericLeaseMgrTest::testTrackAddLeaseNA(bool expect_locked, bool expect_mt_safe) {
    // Register a callback for all subnets.
    lmptr_->registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, "flq",
                             SUBNET_ID_GLOBAL, Lease::TYPE_NA,
                             std::bind(&GenericLeaseMgrTest::logCallback,
                                       this,
                                       TrackingLeaseMgr::TRACK_ADD_LEASE,
                                       SUBNET_ID_GLOBAL,
                                       ph::_1,
                                       ph::_2));
    // Add a lease. It should trigger the callback.
    Lease6Ptr lease = initializeLease6(straddress6_[0]);
    EXPECT_TRUE(lmptr_->addLease(lease));

    // Make sure that the callback has been invoked.
    ASSERT_EQ(1, logs_.size());

    // This flag should be false for the Memfile backend and true
    // for the SQL backends.
    if (expect_locked) {
        EXPECT_TRUE(logs_[0].locked);
    } else {
        EXPECT_FALSE(logs_[0].locked);
    }
    // This flag should be set to true for the Memfile backends.
    // It should be false for other backends. If the backends do
    // not provide the MT-safe context, the callbacks must protect
    // against the concurrent access on their own.
    if (expect_mt_safe) {
        EXPECT_TRUE(logs_[0].mt_safe);
    } else {
        EXPECT_FALSE(logs_[0].mt_safe);
    }

    // The lease locks should have been released.
    EXPECT_FALSE(lmptr_->isLocked(lease));
}

void
GenericLeaseMgrTest::testTrackAddLeasePD(bool expect_locked, bool expect_mt_safe) {
    // Register a callback for all subnets.
    lmptr_->registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, "flq",
                             SUBNET_ID_GLOBAL, Lease::TYPE_PD,
                             std::bind(&GenericLeaseMgrTest::logCallback,
                                       this,
                                       TrackingLeaseMgr::TRACK_ADD_LEASE,
                                       SUBNET_ID_GLOBAL,
                                       ph::_1,
                                       ph::_2));
    // Add a lease. It should trigger the callback.
    Lease6Ptr lease = initializeLease6(straddress6_[2]);
    EXPECT_TRUE(lmptr_->addLease(lease));

    // Make sure that the callback has been invoked.
    ASSERT_EQ(1, logs_.size());

    // This flag should be false for the Memfile backend and true
    // for the SQL backends.
    if (expect_locked) {
        EXPECT_TRUE(logs_[0].locked);
    } else {
        EXPECT_FALSE(logs_[0].locked);
    }
    // This flag should be set to true for the Memfile backends.
    // It should be false for other backends. If the backends do
    // not provide the MT-safe context, the callbacks must protect
    // against the concurrent access on their own.
    if (expect_mt_safe) {
        EXPECT_TRUE(logs_[0].mt_safe);
    } else {
        EXPECT_FALSE(logs_[0].mt_safe);
    }

    // The lease locks should have been released.
    EXPECT_FALSE(lmptr_->isLocked(lease));
}

void
GenericLeaseMgrTest::testTrackUpdateLease4(bool expect_locked, bool expect_mt_safe) {
    // Register a callback for all subnets.
    lmptr_->registerCallback(TrackingLeaseMgr::TRACK_UPDATE_LEASE, "flq",
                             SUBNET_ID_GLOBAL,
                             Lease::TYPE_V4,
                             std::bind(&GenericLeaseMgrTest::logCallback,
                                       this,
                                       TrackingLeaseMgr::TRACK_UPDATE_LEASE,
                                       SUBNET_ID_GLOBAL,
                                       ph::_1,
                                       ph::_2));
    // Add a lease.
    Lease4Ptr lease = initializeLease4(straddress4_[1]);
    EXPECT_TRUE(lmptr_->addLease(lease));
    EXPECT_TRUE(logs_.empty());

    lmptr_->updateLease4(lease);

    // Make sure that the callback has been invoked.
    ASSERT_EQ(1, logs_.size());

    // This flag should be false for the Memfile backend and true
    // for the SQL backends.
    if (expect_locked) {
        EXPECT_TRUE(logs_[0].locked);
    } else {
        EXPECT_FALSE(logs_[0].locked);
    }
    // This flag should be set to true for the Memfile backends.
    // It should be false for other backends. If the backends do
    // not provide the MT-safe context, the callbacks must protect
    // against the concurrent access on their own.
    if (expect_mt_safe) {
        EXPECT_TRUE(logs_[0].mt_safe);
    } else {
        EXPECT_FALSE(logs_[0].mt_safe);
    }

    // The lease locks should have been released.
    EXPECT_FALSE(lmptr_->isLocked(lease));
}

void
GenericLeaseMgrTest::testTrackUpdateLeaseNA(bool expect_locked, bool expect_mt_safe) {
    // Register a callback for all subnets.
    lmptr_->registerCallback(TrackingLeaseMgr::TRACK_UPDATE_LEASE, "flq",
                             SUBNET_ID_GLOBAL, Lease::TYPE_NA,
                             std::bind(&GenericLeaseMgrTest::logCallback,
                                       this,
                                       TrackingLeaseMgr::TRACK_UPDATE_LEASE,
                                       SUBNET_ID_GLOBAL,
                                       ph::_1,
                                       ph::_2));
    // Add a lease.
    Lease6Ptr lease = initializeLease6(straddress6_[0]);
    EXPECT_TRUE(lmptr_->addLease(lease));
    EXPECT_TRUE(logs_.empty());

    lmptr_->updateLease6(lease);

    // Make sure that the callback has been invoked.
    ASSERT_EQ(1, logs_.size());

    // This flag should be false for the Memfile backend and true
    // for the SQL backends.
    if (expect_locked) {
        EXPECT_TRUE(logs_[0].locked);
    } else {
        EXPECT_FALSE(logs_[0].locked);
    }
    // This flag should be set to true for the Memfile backends.
    // It should be false for other backends. If the backends do
    // not provide the MT-safe context, the callbacks must protect
    // against the concurrent access on their own.
    if (expect_mt_safe) {
        EXPECT_TRUE(logs_[0].mt_safe);
    } else {
        EXPECT_FALSE(logs_[0].mt_safe);
    }

    // The lease locks should have been released.
    EXPECT_FALSE(lmptr_->isLocked(lease));
}

void
GenericLeaseMgrTest::testTrackUpdateLeasePD(bool expect_locked, bool expect_mt_safe) {
    // Register a callback for all subnets.
    lmptr_->registerCallback(TrackingLeaseMgr::TRACK_UPDATE_LEASE, "flq",
                             SUBNET_ID_GLOBAL, Lease::TYPE_PD,
                             std::bind(&GenericLeaseMgrTest::logCallback,
                                       this,
                                       TrackingLeaseMgr::TRACK_UPDATE_LEASE,
                                       SUBNET_ID_GLOBAL,
                                       ph::_1,
                                       ph::_2));
    // Add a lease.
    Lease6Ptr lease = initializeLease6(straddress6_[2]);
    EXPECT_TRUE(lmptr_->addLease(lease));
    EXPECT_TRUE(logs_.empty());

    lmptr_->updateLease6(lease);

    // Make sure that the callback has been invoked.
    ASSERT_EQ(1, logs_.size());

    // This flag should be false for the Memfile backend and true
    // for the SQL backends.
    if (expect_locked) {
        EXPECT_TRUE(logs_[0].locked);
    } else {
        EXPECT_FALSE(logs_[0].locked);
    }
    // This flag should be set to true for the Memfile backends.
    // It should be false for other backends. If the backends do
    // not provide the MT-safe context, the callbacks must protect
    // against the concurrent access on their own.
    if (expect_mt_safe) {
        EXPECT_TRUE(logs_[0].mt_safe);
    } else {
        EXPECT_FALSE(logs_[0].mt_safe);
    }

    // The lease locks should have been released.
    EXPECT_FALSE(lmptr_->isLocked(lease));
}

void
GenericLeaseMgrTest::testTrackDeleteLease4(bool expect_locked, bool expect_mt_safe) {
    // Register a callback for all subnets.
    lmptr_->registerCallback(TrackingLeaseMgr::TRACK_DELETE_LEASE, "flq",
                             SUBNET_ID_GLOBAL, Lease::TYPE_V4,
                             std::bind(&GenericLeaseMgrTest::logCallback,
                                       this,
                                       TrackingLeaseMgr::TRACK_DELETE_LEASE,
                                       SUBNET_ID_GLOBAL,
                                       ph::_1,
                                       ph::_2));
    // Add a lease.
    Lease4Ptr lease = initializeLease4(straddress4_[1]);
    EXPECT_TRUE(lmptr_->addLease(lease));
    EXPECT_TRUE(logs_.empty());

    lmptr_->deleteLease(lease);

    // Make sure that the callback has been invoked.
    ASSERT_EQ(1, logs_.size());

    // This flag should be false for the Memfile backend and true
    // for the SQL backends.
    if (expect_locked) {
        EXPECT_TRUE(logs_[0].locked);
    } else {
        EXPECT_FALSE(logs_[0].locked);
    }
    // This flag should be set to true for the Memfile backends.
    // It should be false for other backends. If the backends do
    // not provide the MT-safe context, the callbacks must protect
    // against the concurrent access on their own.
    if (expect_mt_safe) {
        EXPECT_TRUE(logs_[0].mt_safe);
    } else {
        EXPECT_FALSE(logs_[0].mt_safe);
    }

    // The lease locks should have been released.
    EXPECT_FALSE(lmptr_->isLocked(lease));
}

void
GenericLeaseMgrTest::testTrackDeleteLeaseNA(bool expect_locked, bool expect_mt_safe) {
    // Register a callback for all subnets.
    lmptr_->registerCallback(TrackingLeaseMgr::TRACK_DELETE_LEASE, "flq",
                             SUBNET_ID_GLOBAL, Lease::TYPE_NA,
                             std::bind(&GenericLeaseMgrTest::logCallback,
                                       this,
                                       TrackingLeaseMgr::TRACK_DELETE_LEASE,
                                       SUBNET_ID_GLOBAL,
                                       ph::_1,
                                       ph::_2));
    // Add a lease.
    Lease6Ptr lease = initializeLease6(straddress6_[0]);
    EXPECT_TRUE(lmptr_->addLease(lease));
    EXPECT_TRUE(logs_.empty());

    lmptr_->deleteLease(lease);

    // Make sure that the callback has been invoked.
    ASSERT_EQ(1, logs_.size());

    // This flag should be false for the Memfile backend and true
    // for the SQL backends.
    if (expect_locked) {
        EXPECT_TRUE(logs_[0].locked);
    } else {
        EXPECT_FALSE(logs_[0].locked);
    }
    // This flag should be set to true for the Memfile backends.
    // It should be false for other backends. If the backends do
    // not provide the MT-safe context, the callbacks must protect
    // against the concurrent access on their own.
    if (expect_mt_safe) {
        EXPECT_TRUE(logs_[0].mt_safe);
    } else {
        EXPECT_FALSE(logs_[0].mt_safe);
    }

    // The lease locks should have been released.
    EXPECT_FALSE(lmptr_->isLocked(lease));
}

void
GenericLeaseMgrTest::testTrackDeleteLeasePD(bool expect_locked, bool expect_mt_safe) {
    // Register a callback for all subnets.
    lmptr_->registerCallback(TrackingLeaseMgr::TRACK_DELETE_LEASE, "flq",
                             SUBNET_ID_GLOBAL, Lease::TYPE_PD,
                             std::bind(&GenericLeaseMgrTest::logCallback,
                                       this,
                                       TrackingLeaseMgr::TRACK_DELETE_LEASE,
                                       SUBNET_ID_GLOBAL,
                                       ph::_1,
                                       ph::_2));
    // Add a lease.
    Lease6Ptr lease = initializeLease6(straddress6_[2]);
    EXPECT_TRUE(lmptr_->addLease(lease));
    EXPECT_TRUE(logs_.empty());

    lmptr_->deleteLease(lease);

    // Make sure that the callback has been invoked.
    ASSERT_EQ(1, logs_.size());

    // This flag should be false for the Memfile backend and true
    // for the SQL backends.
    if (expect_locked) {
        EXPECT_TRUE(logs_[0].locked);
    } else {
        EXPECT_FALSE(logs_[0].locked);
    }
    // This flag should be set to true for the Memfile backends.
    // It should be false for other backends. If the backends do
    // not provide the MT-safe context, the callbacks must protect
    // against the concurrent access on their own.
    if (expect_mt_safe) {
        EXPECT_TRUE(logs_[0].mt_safe);
    } else {
        EXPECT_FALSE(logs_[0].mt_safe);
    }

    // The lease locks should have been released.
    EXPECT_FALSE(lmptr_->isLocked(lease));
}

void
GenericLeaseMgrTest::testRecreateWithCallbacks(const std::string& access) {
    // Register a callback.
    lmptr_->registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, "flq", 0,
                             Lease::TYPE_V4,
                             std::bind(&GenericLeaseMgrTest::logCallback,
                                       this,
                                       TrackingLeaseMgr::TRACK_ADD_LEASE,
                                       0,
                                       ph::_1,
                                       ph::_2));

    // Recreate the lease manager with the callbacks.
    ASSERT_NO_THROW(LeaseMgrFactory::recreate(access, true));
    lmptr_ = &(LeaseMgrFactory::instance());

    // Add a lease. It should trigger the callback.
    Lease4Ptr lease = initializeLease4(straddress4_[1]);
    EXPECT_TRUE(lmptr_->addLease(lease));

    // Make sure that the callback has been invoked.
    EXPECT_EQ(1, logs_.size());
}

void
GenericLeaseMgrTest::testRecreateWithoutCallbacks(const std::string& access) {
    // Register a callback.
    lmptr_->registerCallback(TrackingLeaseMgr::TRACK_ADD_LEASE, "flq", 0,
                             Lease::TYPE_V4,
                             std::bind(&GenericLeaseMgrTest::logCallback,
                                       this,
                                       TrackingLeaseMgr::TRACK_ADD_LEASE,
                                       0,
                                       ph::_1,
                                       ph::_2));

    // Recreate the lease manager without the callbacks.
    ASSERT_NO_THROW(LeaseMgrFactory::recreate(access, false));
    lmptr_ = &(LeaseMgrFactory::instance());

    // Add a lease. It should not trigger the callback.
    Lease4Ptr lease = initializeLease4(straddress4_[1]);
    EXPECT_TRUE(lmptr_->addLease(lease));
    EXPECT_TRUE(logs_.empty());
}

}  // namespace test
}  // namespace dhcp
}  // namespace isc
