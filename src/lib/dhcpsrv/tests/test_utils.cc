// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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

#include "test_utils.h"
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

void
detailCompareLease(const Lease4Ptr& first, const Lease4Ptr& second) {
    // Compare address strings.  Comparison of address objects is not used, as
    // odd things happen when they are different: the EXPECT_EQ macro appears to
    // call the operator uint32_t() function, which causes an exception to be
    // thrown for IPv6 addresses.
    EXPECT_EQ(first->addr_, second->addr_);
    EXPECT_TRUE(first->hwaddr_ == second->hwaddr_);
    if (first->client_id_ && second->client_id_) {
        EXPECT_TRUE(*first->client_id_ == *second->client_id_);
    } else {
        if (first->client_id_ && !second->client_id_) {

            ADD_FAILURE() << "Client-id present in first lease ("
                          << first->client_id_->getClientId().size()
                          << " bytes), but missing in second.";
        }
        if (!first->client_id_ && second->client_id_) {
            ADD_FAILURE() << "Client-id missing in first lease, but present in second ("
                          << second->client_id_->getClientId().size()
                          << " bytes).";
        }
        // else here would mean that both leases do not have client_id_
        // which makes them equal in that regard. It is ok.
    }
    EXPECT_EQ(first->valid_lft_, second->valid_lft_);
    EXPECT_EQ(first->cltt_, second->cltt_);
    EXPECT_EQ(first->subnet_id_, second->subnet_id_);
    EXPECT_EQ(first->fqdn_fwd_, second->fqdn_fwd_);
    EXPECT_EQ(first->fqdn_rev_, second->fqdn_rev_);
    EXPECT_EQ(first->hostname_, second->hostname_);
}

void
detailCompareLease(const Lease6Ptr& first, const Lease6Ptr& second) {
    EXPECT_EQ(first->type_, second->type_);

    // Compare address strings.  Comparison of address objects is not used, as
    // odd things happen when they are different: the EXPECT_EQ macro appears to
    // call the operator uint32_t() function, which causes an exception to be
    // thrown for IPv6 addresses.
    EXPECT_EQ(first->addr_, second->addr_);
    EXPECT_EQ(first->prefixlen_, second->prefixlen_);
    EXPECT_EQ(first->iaid_, second->iaid_);
    ASSERT_TRUE(first->duid_);
    ASSERT_TRUE(second->duid_);
    EXPECT_TRUE(*first->duid_ == *second->duid_);
    EXPECT_EQ(first->preferred_lft_, second->preferred_lft_);
    EXPECT_EQ(first->valid_lft_, second->valid_lft_);
    EXPECT_EQ(first->cltt_, second->cltt_);
    EXPECT_EQ(first->subnet_id_, second->subnet_id_);
    EXPECT_EQ(first->fqdn_fwd_, second->fqdn_fwd_);
    EXPECT_EQ(first->fqdn_rev_, second->fqdn_rev_);
    EXPECT_EQ(first->hostname_, second->hostname_);
}

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

/// @brief Initialize Lease4 Fields
///
/// Returns a pointer to a Lease4 structure.  Different values are put into
/// the lease according to the address passed.
///
/// This is just a convenience function for the test methods.
///
/// @param address Address to use for the initialization
///
/// @return Lease4Ptr.  This will not point to anything if the
///         initialization failed (e.g. unknown address).
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

/// @brief Initialize Lease6 Fields
///
/// Returns a pointer to a Lease6 structure.  Different values are put into
/// the lease according to the address passed.
///
/// This is just a convenience function for the test methods.
///
/// @param address Address to use for the initialization
///
/// @return Lease6Ptr.  This will not point to anything if the initialization
///         failed (e.g. unknown address).
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

/// @brief Check Leases present and different
///
/// Checks a vector of lease pointers and ensures that all the leases
/// they point to are present and different.  If not, a GTest assertion
/// will fail.
///
/// @param leases Vector of pointers to leases
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

/// @brief Creates leases for the test
///
/// Creates all leases for the test and checks that they are different.
///
/// @return vector<Lease4Ptr> Vector of pointers to leases
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

/// @brief Creates leases for the test
///
/// Creates all leases for the test and checks that they are different.
///
/// @return vector<Lease6Ptr> Vector of pointers to leases
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

// Test that IPv6 lease can be added, retrieved and deleted
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
    EXPECT_EQ(Lease6Ptr(), x);
}

/// Checks that the addLease, getLease4 (by address) and deleteLease (with an
/// IPv4 address) works.
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
    reopen();

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

};
};
};
