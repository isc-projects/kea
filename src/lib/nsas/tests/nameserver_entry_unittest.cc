// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <iostream>
#include <algorithm>

#include <limits.h>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

#include <dns/rdata.h>
#include <dns/rrset.h>
#include <dns/rrclass.h>
#include <dns/rdataclass.h>
#include <dns/rrttl.h>
#include <dns/name.h>
#include <exceptions/exceptions.h>

#include "../asiolink.h"
#include "../address_entry.h"
#include "../nameserver_entry.h"
#include "../zone_entry.h"

#include "nsas_test.h"

using namespace isc::nsas;
using namespace asiolink;
using namespace std;
using namespace isc::dns;
using namespace rdata;
using namespace boost;

namespace {

/// \brief Test Fixture Class
class NameserverEntryTest : public TestWithRdata {
protected:
    /// \short Just a really stupid callback counting times called
    struct Callback : public NameserverEntry::Callback {
        size_t count;
        virtual void operator()(shared_ptr<NameserverEntry>) {
            count ++;
        }
        Callback() : count(0) { }
    };
};

/// \brief Compare Vectors of String
///
/// Compares two vectors of strings.  A GoogleTest check is done on the results.
///
/// \param vec1 First vector.  This may be reordered in the comparison.
/// \param vec2 Second vector.  This may be reordered in the comparison
static void CompareStringVectors(vector<string>& vec1, vector<string>& vec2)
{
    // Check that the vectors are the same size.
    EXPECT_EQ(vec1.size(), vec2.size());

    // Get into canonical order
    sort(vec1.begin(), vec1.end());
    sort(vec2.begin(), vec2.end());

    // ... and look for a mismatch.
    EXPECT_TRUE(equal(vec1.begin(), vec1.end(), vec2.begin()));
}

/// \brief Compare Ranges of Addresses
///
/// Compares the addresses held in an address vector with those held in the
/// RRset from which it was dervived and checks that there is a 1:1
/// mapping between the two.
///
/// \param av AddressVector retrieved from NameserverEntry object
/// \param rrs BasicRRSet from which the vector was created
static void CompareAddresses(NameserverEntry::AddressVector& av,
    BasicRRset& rrs)
{

    // Extract addresses from address vector into strings
    vector<string> avs;
    BOOST_FOREACH(AddressEntry addr, av) {
        avs.push_back(addr.getAddress().toText());
    }

    // Do the same for the Basic RRset
    vector<string> rrstr;
    RdataIteratorPtr i = rrs.getRdataIterator();
    // TODO Remove at merge with #410
    i->first();
    while (! i->isLast()) {
        rrstr.push_back(i->getCurrent().toText());
        i->next();
    }

    // ... and compare the results
    CompareStringVectors(avs, rrstr);
}


/// \brief Compare Address Vectors
///
/// Compares two address vectors by converting the addresses to string form
/// and comparing the strings.  Any mismatch will be reported.
///
/// \param vec1 First address vector
/// \param vec2 Second address vector
static void CompareAddressVectors(NameserverEntry::AddressVector& vec1,
    NameserverEntry::AddressVector& vec2) {

    // Extract addresses from address vectors into strings
    vector<string> strvec1;
    BOOST_FOREACH(AddressEntry addr, vec1) {
        strvec1.push_back(addr.getAddress().toText());
    }

    vector<string> strvec2;
    BOOST_FOREACH(AddressEntry addr, vec2) {
        strvec2.push_back(addr.getAddress().toText());
    }

    CompareStringVectors(strvec1, strvec2);
}

/// Tests of the default constructor
TEST_F(NameserverEntryTest, DefaultConstructor) {

    // Default constructor should not create any RRsets
    NameserverEntry alpha(EXAMPLE_CO_UK, RRClass::IN().getCode());
    EXPECT_EQ(EXAMPLE_CO_UK, alpha.getName());
    EXPECT_EQ(RRClass::IN().getCode(), alpha.getClass());

    // Also check that no addresses have been created.
    NameserverEntry::AddressVector addresses;
    alpha.getAddresses(addresses);
    EXPECT_TRUE(addresses.empty());
}


/// Tests of constructor passed a list of addresses.
TEST_F(NameserverEntryTest, AddressListConstructor) {

    // Initialize with no addresses and check that data returned has size of
    // zero and knows it did not ask for the address yet
    NameserverEntry alpha(NULL, NULL);
    NameserverEntry::AddressVector av;
    EXPECT_EQ(Fetchable::NOT_ASKED, alpha.getAddresses(av));
    EXPECT_EQ(0, av.size());

    NameserverEntry::AddressVector av4;
    EXPECT_EQ(Fetchable::NOT_ASKED, alpha.getAddresses(av4, V4_ONLY));
    EXPECT_EQ(0, av4.size());

    NameserverEntry::AddressVector av6;
    EXPECT_EQ(Fetchable::NOT_ASKED, alpha.getAddresses(av6, V6_ONLY));
    EXPECT_EQ(0, av6.size());

    // Initialize with V4 addresses only.
    EXPECT_GT(rrv4_.getRdataCount(), 0);
    NameserverEntry beta(&rrv4_, NULL);

    NameserverEntry::AddressVector bv;
    EXPECT_EQ(Fetchable::READY, beta.getAddresses(bv));
    EXPECT_EQ(rrv4_.getRdataCount(), bv.size());

    NameserverEntry::AddressVector bv4;
    EXPECT_EQ(Fetchable::READY, beta.getAddresses(bv4, V4_ONLY));
    EXPECT_EQ(rrv4_.getRdataCount(), bv4.size());

    NameserverEntry::AddressVector bv6;
    EXPECT_EQ(Fetchable::UNREACHABLE, beta.getAddresses(bv6, V6_ONLY));
    EXPECT_EQ(0, bv6.size());

    // Check that the addresses received are unique.
    SCOPED_TRACE("Checking V4 addresses");
    CompareAddresses(bv4, rrv4_);

    // Initialize with V6 addresses only
    EXPECT_TRUE(rrv6_.getRdataCount() > 0);
    NameserverEntry gamma(NULL, &rrv6_);

    NameserverEntry::AddressVector cv;
    EXPECT_EQ(Fetchable::READY, gamma.getAddresses(cv));
    EXPECT_EQ(rrv6_.getRdataCount(), cv.size());

    NameserverEntry::AddressVector cv4;
    EXPECT_EQ(Fetchable::UNREACHABLE, gamma.getAddresses(cv4, V4_ONLY));
    EXPECT_EQ(0, cv4.size());

    NameserverEntry::AddressVector cv6;
    EXPECT_EQ(Fetchable::READY, gamma.getAddresses(cv6, V6_ONLY));
    EXPECT_EQ(rrv6_.getRdataCount(), cv6.size());

    SCOPED_TRACE("Checking V6 addresses");
    CompareAddresses(cv6, rrv6_);

    // Initialize with both sets of addresses
    NameserverEntry delta(&rrv4_, &rrv6_);

    NameserverEntry::AddressVector dv;
    EXPECT_EQ(Fetchable::READY, delta.getAddresses(dv));
    EXPECT_EQ((rrv4_.getRdataCount() + rrv6_.getRdataCount()), dv.size());

    NameserverEntry::AddressVector dv4;
    EXPECT_EQ(Fetchable::READY, delta.getAddresses(dv4, V4_ONLY));
    EXPECT_EQ(rrv4_.getRdataCount(), dv4.size());
    SCOPED_TRACE("Checking V4 addresses after dual-address family constructor");
    CompareAddresses(dv4, rrv4_);

    NameserverEntry::AddressVector dv6;
    EXPECT_EQ(Fetchable::READY, delta.getAddresses(dv6, V6_ONLY));
    EXPECT_EQ(rrv6_.getRdataCount(), dv6.size());
    SCOPED_TRACE("Checking V6 addresses after dual-address family constructor");
    CompareAddresses(dv6, rrv6_);

    // ... and check that the composite of the v4 and v6 addresses is the same
    // as that returned by the get without a filter.
    NameserverEntry::AddressVector dvcomponent;
    EXPECT_EQ(Fetchable::READY, delta.getAddresses(dvcomponent, V4_ONLY));
    EXPECT_EQ(Fetchable::READY, delta.getAddresses(dvcomponent, V6_ONLY));
    SCOPED_TRACE("Checking V4+V6 addresses same as composite return");
    CompareAddressVectors(dv, dvcomponent);
}

// Test the the RTT on tthe created addresses is not 0 and is different
TEST_F(NameserverEntryTest, InitialRTT) {

    // Get the RTT for the different addresses
    NameserverEntry alpha(&rrv4_, &rrv6_);
    NameserverEntry::AddressVector vec;
    alpha.getAddresses(vec);

    // Copy into a vector of time_t.
    vector<uint32_t> rtt;
    for (NameserverEntry::AddressVectorIterator i = vec.begin();
        i != vec.end(); ++i) {
        rtt.push_back(i->getRTT());
    }

    // Ensure that the addresses are sorted and note how many RTTs we have.
    sort(rtt.begin(), rtt.end());
    int oldcount = rtt.size();

    // Remove duplicates and notw the new size.
    vector<uint32_t>::iterator newend = unique(rtt.begin(), rtt.end());
    rtt.erase(newend, rtt.end());
    int newcount = rtt.size();

    // .. and we don't expect to have lost anything.
    EXPECT_EQ(oldcount, newcount);
}

// Set an address RTT to a given value
TEST_F(NameserverEntryTest, SetRTT) {

    // Get the RTT for the different addresses
    NameserverEntry alpha(&rrv4_, &rrv6_);
    NameserverEntry::AddressVector vec;
    alpha.getAddresses(vec);

    ASSERT_TRUE(vec.size() > 0);

    // Take the first address and change the RTT.
    IOAddress first_address = vec[0].getAddress();
    uint32_t first_rtt = vec[0].getRTT();
    uint32_t new_rtt = first_rtt + 42;
    alpha.setAddressRTT(first_address, new_rtt);

    // Now see if it has changed
    NameserverEntry::AddressVector newvec;
    alpha.getAddresses(newvec);

    int matchcount = 0;
    for (NameserverEntry::AddressVectorIterator i = newvec.begin();
        i != newvec.end(); ++i) {
        if (i->getAddress().equal(first_address)) {
            ++matchcount;
            EXPECT_EQ(i->getRTT(), new_rtt);
        }
    }

    // ... and make sure there was only one match in the set we retrieved
    EXPECT_EQ(1, matchcount);
}

// Set an address RTT to be unreachable
TEST_F(NameserverEntryTest, Unreachable) {

    // Get the RTT for the different addresses
    NameserverEntry alpha(&rrv4_, &rrv6_);
    NameserverEntry::AddressVector vec;
    alpha.getAddresses(vec);

    ASSERT_TRUE(vec.size() > 0);

    // Take the first address and mark as unreachable.
    IOAddress first_address = vec[0].getAddress();
    EXPECT_FALSE(vec[0].isUnreachable());

    alpha.setAddressUnreachable(first_address);

    // Now see if it has changed
    NameserverEntry::AddressVector newvec;
    alpha.getAddresses(newvec);

    int matchcount = 0;
    for (NameserverEntry::AddressVectorIterator i = newvec.begin();
        i != newvec.end(); ++i) {
        if (i->getAddress().equal(first_address)) {
            ++matchcount;
            EXPECT_TRUE(i->isUnreachable());
        }
    }

    // ... and make sure there was only one match in the set we retrieved
    EXPECT_EQ(1, matchcount);
}

// Test that the expiration time of records is set correctly.
//
// Note that for testing purposes we use the three-argument NameserverEntry
// constructor (where we supply the time).  It eliminates intermittent errors
// cause when this test is run just as the clock "ticks over" to another second.
TEST_F(NameserverEntryTest, ExpirationTime) {

    time_t curtime = time(NULL);
    time_t expiration = 0;

    // Test where there is a single TTL
    NameserverEntry alpha(&rrv4_, NULL, curtime);
    expiration = alpha.getExpiration();
    EXPECT_EQ(expiration, curtime + rrv4_.getTTL().getValue());

    NameserverEntry beta(NULL, &rrv6_, curtime);
    expiration = beta.getExpiration();
    EXPECT_EQ(expiration, curtime + rrv6_.getTTL().getValue());

    // Test where there are two different TTLs
    EXPECT_NE(rrv4_.getTTL().getValue(), rrv6_.getTTL().getValue());
    NameserverEntry gamma(&rrv4_, &rrv6_, curtime);
    uint32_t minttl = min(rrv4_.getTTL().getValue(), rrv6_.getTTL().getValue());
    EXPECT_EQ(expiration, curtime + minttl);

    // Finally check where we don't specify a current time.  All we know is
    // that the expiration time should be greater than the TTL (as the current
    // time is greater than zero).

    NameserverEntry delta(&rrv4_, NULL);
    EXPECT_GT(delta.getExpiration(), rrv4_.getTTL().getValue());
}


// Test that the name of this nameserver is set correctly.
TEST_F(NameserverEntryTest, CheckName) {

    // Default constructor
    NameserverEntry alpha(EXAMPLE_CO_UK, RRClass::IN().getCode());
    EXPECT_EQ(EXAMPLE_CO_UK, alpha.getName());

    // Address constructor
    NameserverEntry beta(&rrv4_, NULL);
    EXPECT_EQ(EXAMPLE_CO_UK, beta.getName());

    NameserverEntry gamma(NULL, &rrv6_);
    EXPECT_EQ(EXAMPLE_CO_UK, gamma.getName());

    NameserverEntry delta(&rrv4_, &rrv6_);
    EXPECT_EQ(EXAMPLE_CO_UK, delta.getName());

    // Check that the name is not canonicalised
    NameserverEntry epsilon(&rrcase_, NULL);
    EXPECT_EQ(MIXED_EXAMPLE_CO_UK, epsilon.getName());

    // Check that inconsistent names mean that an exception is generated.
    EXPECT_THROW(NameserverEntry zeta(&rrnet_, &rrv6_),
        isc::nsas::InconsistentOwnerNames);
}

// Check that it can cope with non-IN classes.
TEST_F(NameserverEntryTest, CheckClass) {

    // Default constructor
    NameserverEntry alpha(EXAMPLE_CO_UK, RRClass::CH().getCode());
    EXPECT_EQ(RRClass::CH().getCode(), alpha.getClass());

    // Address constructor
    NameserverEntry beta(&rrch_, NULL);
    EXPECT_EQ(RRClass::CH().getCode(), beta.getClass());

    // Ensure that inconsistent class throws an exception
    EXPECT_THROW(NameserverEntry gamma(&rrch_, &rrv6_),
        isc::nsas::InconsistentClass);

}

// Tests if it asks the IP addresses and calls callbacks when it comes
// including the right addresses are returned and that they expire
TEST_F(NameserverEntryTest, IPCallbacks) {
    shared_ptr<NameserverEntry> entry(new NameserverEntry(EXAMPLE_CO_UK,
        RRClass::IN().getCode()));
    shared_ptr<Callback> callback(new Callback);
    shared_ptr<TestResolver> resolver(new TestResolver);

    entry->askIP(resolver, callback, ANY_OK, entry);
    // Ensure it becomes IN_PROGRESS
    EXPECT_EQ(Fetchable::IN_PROGRESS, entry->getState());
    // Now, there should be two queries in the resolver
    ASSERT_EQ(2, resolver->requests.size());
    resolver->asksIPs(Name(EXAMPLE_CO_UK), 0, 1);

    // Another one might ask
    entry->askIP(resolver, callback, V4_ONLY, entry);
    // There should still be only two queries in the resolver
    ASSERT_EQ(2, resolver->requests.size());

    // Another one, with need of IPv6 address
    entry->askIP(resolver, callback, V6_ONLY, entry);

    // Answer one and see that the callbacks are called
    resolver->answer(0, Name(EXAMPLE_CO_UK), RRType::A(),
        rdata::in::A("192.0.2.1"));

    // Both callbacks that want IPv4 should be called by now
    EXPECT_EQ(2, callback->count);
    // It should contain one IP address
    NameserverEntry::AddressVector addresses;
    // Still in progress, waiting for the other address
    EXPECT_EQ(Fetchable::IN_PROGRESS, entry->getAddresses(addresses));
    EXPECT_EQ(1, addresses.size());
    // Answer IPv6 address
    // It is with zero TTL, so it should expire right away
    resolver->answer(1, Name(EXAMPLE_CO_UK), RRType::AAAA(),
        rdata::in::AAAA("2001:db8::1"), 0);
    // The other callback should appear
    EXPECT_EQ(3, callback->count);
    // It should return the one address. It should be expired, but
    // we ignore it for now
    EXPECT_EQ(Fetchable::READY, entry->getAddresses(addresses, V6_ONLY, true));
    // Another address should appear
    EXPECT_EQ(2, addresses.size());
    // But when we do not ignore it, it should not appear
    EXPECT_EQ(Fetchable::EXPIRED, entry->getAddresses(addresses, V6_ONLY));
    EXPECT_EQ(2, addresses.size());
}

// Test the callback is called even when the address is unreachable
TEST_F(NameserverEntryTest, IPCallbacksUnreachable) {
    shared_ptr<NameserverEntry> entry(new NameserverEntry(EXAMPLE_CO_UK,
        RRClass::IN().getCode()));
    shared_ptr<Callback> callback(new Callback);
    shared_ptr<TestResolver> resolver(new TestResolver);

    // Ask for its IP
    entry->askIP(resolver, callback, ANY_OK, entry);
    // Check it asks the resolver
    ASSERT_EQ(2, resolver->requests.size());
    resolver->asksIPs(Name(EXAMPLE_CO_UK), 0, 1);
    resolver->requests[0].second->failure();
    // It should still wait for the second one
    EXPECT_EQ(0, callback->count);
    EXPECT_EQ(Fetchable::IN_PROGRESS, entry->getState());
    // It should call the callback now and be unrechable
    resolver->requests[1].second->failure();
    EXPECT_EQ(1, callback->count);
    EXPECT_EQ(Fetchable::UNREACHABLE, entry->getState());
    NameserverEntry::AddressVector addresses;
    EXPECT_EQ(Fetchable::UNREACHABLE, entry->getAddresses(addresses));
    EXPECT_EQ(0, addresses.size());
}

}   // namespace
