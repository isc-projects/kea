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

void
detailCompareLease(const Lease4Ptr& first, const Lease4Ptr& second) {
    // Compare address strings.  Comparison of address objects is not used, as
    // odd things happen when they are different: the EXPECT_EQ macro appears to
    // call the operator uint32_t() function, which causes an exception to be
    // thrown for IPv6 addresses.
    EXPECT_EQ(first->addr_.toText(), second->addr_.toText());
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
}

void
detailCompareLease(const Lease6Ptr& first, const Lease6Ptr& second) {
    EXPECT_EQ(first->type_, second->type_);

    // Compare address strings.  Comparison of address objects is not used, as
    // odd things happen when they are different: the EXPECT_EQ macro appears to
    // call the operator uint32_t() function, which causes an exception to be
    // thrown for IPv6 addresses.
    EXPECT_EQ(first->addr_.toText(), second->addr_.toText());
    EXPECT_EQ(first->prefixlen_, second->prefixlen_);
    EXPECT_EQ(first->iaid_, second->iaid_);
    ASSERT_TRUE(first->duid_);
    ASSERT_TRUE(second->duid_);
    EXPECT_TRUE(*first->duid_ == *second->duid_);
    EXPECT_EQ(first->preferred_lft_, second->preferred_lft_);
    EXPECT_EQ(first->valid_lft_, second->valid_lft_);
    EXPECT_EQ(first->cltt_, second->cltt_);
    EXPECT_EQ(first->subnet_id_, second->subnet_id_);
}


GenericLeaseMgrTest::GenericLeaseMgrTest()
    :lmptr_(NULL) {
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
    }
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
    lease->hostname_ = std::string("");         // Unused
    lease->fqdn_fwd_ = false;                   // Unused
    lease->fqdn_rev_ = false;                   // Unused
    lease->comments_ = std::string("");         // Unused

    // Set other parameters.  For historical reasons, address 0 is not used.
    if (address == straddress4_[0]) {
        lease->hwaddr_ = vector<uint8_t>(6, 0x08);
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x42)));
        lease->valid_lft_ = 8677;
        lease->cltt_ = 168256;
        lease->subnet_id_ = 23;

    } else if (address == straddress4_[1]) {
        lease->hwaddr_ = vector<uint8_t>(6, 0x19);
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x53)));
        lease->valid_lft_ = 3677;
        lease->cltt_ = 123456;
        lease->subnet_id_ = 73;

    } else if (address == straddress4_[2]) {
        lease->hwaddr_ = vector<uint8_t>(6, 0x2a);
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x64)));
        lease->valid_lft_ = 5412;
        lease->cltt_ = 234567;
        lease->subnet_id_ = 73;                         // Same as lease 1

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

    } else if (address == straddress4_[4]) {
        lease->hwaddr_ = vector<uint8_t>(6, 0x4c);
        // Same ClientId as straddr4_[1]
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x53)));    // Same as lease 1
        lease->valid_lft_ = 7736;
        lease->cltt_ = 222456;
        lease->subnet_id_ = 85;

    } else if (address == straddress4_[5]) {
        lease->hwaddr_ = vector<uint8_t>(6, 0x19);      // Same as lease 1
        // Same ClientId and IAID as straddress4_1
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x53)));    // Same as lease 1
        lease->valid_lft_ = 7832;
        lease->cltt_ = 227476;
        lease->subnet_id_ = 175;

    } else if (address == straddress4_[6]) {
        lease->hwaddr_ = vector<uint8_t>(6, 0x6e);
        // Same ClientId as straddress4_1
        lease->client_id_ = ClientIdPtr(
            new ClientId(vector<uint8_t>(8, 0x53)));    // Same as lease 1
        lease->valid_lft_ = 1832;
        lease->cltt_ = 627476;
        lease->subnet_id_ = 112;

    } else if (address == straddress4_[7]) {
        lease->hwaddr_ = vector<uint8_t>();             // Empty
        lease->client_id_ = ClientIdPtr();              // Empty
        lease->valid_lft_ = 7975;
        lease->cltt_ = 213876;
        lease->subnet_id_ = 19;

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
    lease->hostname_ = std::string("");         // Unused
    lease->fqdn_fwd_ = false;                   // Unused
    lease->fqdn_rev_ = false;                   // Unused
    lease->comments_ = std::string("");         // Unused

    // Set other parameters.  For historical reasons, address 0 is not used.
    if (address == straddress6_[0]) {
        lease->type_ = Lease6::LEASE_IA_TA;
        lease->prefixlen_ = 4;
        lease->iaid_ = 142;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x77)));
        lease->preferred_lft_ = 900;
        lease->valid_lft_ = 8677;
        lease->cltt_ = 168256;
        lease->subnet_id_ = 23;

    } else if (address == straddress6_[1]) {
        lease->type_ = Lease6::LEASE_IA_TA;
        lease->prefixlen_ = 0;
        lease->iaid_ = 42;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x42)));
        lease->preferred_lft_ = 3600;
        lease->valid_lft_ = 3677;
        lease->cltt_ = 123456;
        lease->subnet_id_ = 73;

    } else if (address == straddress6_[2]) {
        lease->type_ = Lease6::LEASE_IA_PD;
        lease->prefixlen_ = 7;
        lease->iaid_ = 89;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x3a)));
        lease->preferred_lft_ = 1800;
        lease->valid_lft_ = 5412;
        lease->cltt_ = 234567;
        lease->subnet_id_ = 73;                     // Same as lease 1

    } else if (address == straddress6_[3]) {
        lease->type_ = Lease6::LEASE_IA_NA;
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

    } else if (address == straddress6_[4]) {
        // Same DUID and IAID as straddress6_1
        lease->type_ = Lease6::LEASE_IA_PD;
        lease->prefixlen_ = 15;
        lease->iaid_ = 42;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x42)));
        lease->preferred_lft_ = 4800;
        lease->valid_lft_ = 7736;
        lease->cltt_ = 222456;
        lease->subnet_id_ = 671;

    } else if (address == straddress6_[5]) {
        // Same DUID and IAID as straddress6_1
        lease->type_ = Lease6::LEASE_IA_PD;
        lease->prefixlen_ = 24;
        lease->iaid_ = 42;                          // Same as lease 4
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x42)));
        // Same as lease 4
        lease->preferred_lft_ = 5400;
        lease->valid_lft_ = 7832;
        lease->cltt_ = 227476;
        lease->subnet_id_ = 175;

    } else if (address == straddress6_[6]) {
        // Same DUID as straddress6_1
        lease->type_ = Lease6::LEASE_IA_PD;
        lease->prefixlen_ = 24;
        lease->iaid_ = 93;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0x42)));
        // Same as lease 4
        lease->preferred_lft_ = 5400;
        lease->valid_lft_ = 1832;
        lease->cltt_ = 627476;
        lease->subnet_id_ = 112;

    } else if (address == straddress6_[7]) {
        // Same IAID as straddress6_1
        lease->type_ = Lease6::LEASE_IA_PD;
        lease->prefixlen_ = 24;
        lease->iaid_ = 42;
        lease->duid_ = DuidPtr(new DUID(vector<uint8_t>(8, 0xe5)));
        lease->preferred_lft_ = 5600;
        lease->valid_lft_ = 7975;
        lease->cltt_ = 213876;
        lease->subnet_id_ = 19;

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

vector<Lease6Ptr> GenericLeaseMgrTest::createLeases6() {

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

};
};
};
