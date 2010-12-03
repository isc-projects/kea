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
private:
    void fillSet(shared_ptr<TestResolver> resolver, size_t index,
        shared_ptr<BasicRRset> set)
    {
        if (set) {
            resolver->requests[index].second->success(set);
        } else {
            resolver->requests[index].second->failure();
        }
    }
protected:
    /// Fills the nameserver entry with data trough ask IP
    void fillNSEntry(shared_ptr<NameserverEntry> entry,
        shared_ptr<BasicRRset> rrv4, shared_ptr<BasicRRset> rrv6)
    {
        // Prepare data to run askIP
        shared_ptr<TestResolver> resolver(new TestResolver);
        shared_ptr<Callback> callback(new Callback);
        // Let it ask for data
        entry->askIP(resolver, callback, ANY_OK);
        // Check it really asked and sort the queries
        resolver->asksIPs(Name(entry->getName()), 0, 1);
        // Respond with answers
        fillSet(resolver, 0, rrv4);
        fillSet(resolver, 1, rrv6);
    }
};

/// Tests of the default constructor
TEST_F(NameserverEntryTest, DefaultConstructor) {

    // Default constructor should not create any RRsets
    NameserverEntry alpha(EXAMPLE_CO_UK, RRClass::IN());
    EXPECT_EQ(EXAMPLE_CO_UK, alpha.getName());
    EXPECT_EQ(RRClass::IN(), alpha.getClass());

    // Also check that no addresses have been created.
    NameserverEntry::AddressVector addresses;
    alpha.getAddresses(addresses);
    EXPECT_TRUE(addresses.empty());
}

// Test the the RTT on tthe created addresses is not 0 and is different
TEST_F(NameserverEntryTest, InitialRTT) {

    // Get the RTT for the different addresses
    shared_ptr<NameserverEntry> alpha(new NameserverEntry(EXAMPLE_CO_UK,
        RRClass::IN()));
    fillNSEntry(alpha, rrv4_, rrv6_);
    NameserverEntry::AddressVector vec;
    alpha->getAddresses(vec);

    // Check they are not 0 and they are all small, they should be some kind
    // of randomish numbers, so we can't expect much more here
    BOOST_FOREACH(const AddressEntry& entry, vec) {
        EXPECT_GT(entry.getRTT(), 0);
        // 20 is some arbitrary small value
        EXPECT_LT(entry.getRTT(), 20);
    }
}

// Set an address RTT to a given value
TEST_F(NameserverEntryTest, SetRTT) {

    // Get the RTT for the different addresses
    shared_ptr<NameserverEntry> alpha(new NameserverEntry(EXAMPLE_CO_UK,
        RRClass::IN()));
    fillNSEntry(alpha, rrv4_, rrv6_);
    NameserverEntry::AddressVector vec;
    alpha->getAddresses(vec);

    ASSERT_TRUE(vec.size() > 0);

    // Take the first address and change the RTT.
    IOAddress first_address = vec[0].getAddress();
    uint32_t first_rtt = vec[0].getRTT();
    uint32_t new_rtt = first_rtt + 42;
    alpha->setAddressRTT(first_address, new_rtt);

    // Now see if it has changed
    NameserverEntry::AddressVector newvec;
    alpha->getAddresses(newvec);

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
    shared_ptr<NameserverEntry> alpha(new NameserverEntry(EXAMPLE_CO_UK,
        RRClass::IN()));
    fillNSEntry(alpha, rrv4_, rrv6_);
    NameserverEntry::AddressVector vec;
    alpha->getAddresses(vec);

    ASSERT_TRUE(vec.size() > 0);

    // Take the first address and mark as unreachable.
    IOAddress first_address = vec[0].getAddress();
    EXPECT_FALSE(vec[0].isUnreachable());

    alpha->setAddressUnreachable(first_address);

    // Now see if it has changed
    NameserverEntry::AddressVector newvec;
    alpha->getAddresses(newvec);

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
// TODO Return the way where we can pass time inside somehow
TEST_F(NameserverEntryTest, ExpirationTime) {

    time_t curtime = time(NULL);
    time_t expiration = 0;

    // Test where there is a single TTL
    shared_ptr<NameserverEntry> alpha(new NameserverEntry(EXAMPLE_CO_UK,
        RRClass::IN()));
    fillNSEntry(alpha, rrv4_, shared_ptr<BasicRRset>());
    expiration = alpha->getExpiration();
    EXPECT_EQ(expiration, curtime + rrv4_->getTTL().getValue());

    shared_ptr<NameserverEntry> beta(new NameserverEntry(EXAMPLE_CO_UK,
        RRClass::IN()));
    fillNSEntry(beta, shared_ptr<BasicRRset>(), rrv6_);
    expiration = beta->getExpiration();
    EXPECT_EQ(expiration, curtime + rrv6_->getTTL().getValue());

    // Test where there are two different TTLs
    EXPECT_NE(rrv4_->getTTL().getValue(), rrv6_->getTTL().getValue());
    shared_ptr<NameserverEntry> gamma(new NameserverEntry(EXAMPLE_CO_UK,
        RRClass::IN()));
    fillNSEntry(gamma, rrv4_, rrv6_);
    uint32_t minttl = min(rrv4_->getTTL().getValue(), rrv6_->getTTL().getValue());
    expiration = gamma->getExpiration();
    EXPECT_EQ(expiration, curtime + minttl);

    // Finally check where we don't specify a current time.  All we know is
    // that the expiration time should be greater than the TTL (as the current
    // time is greater than zero).

    shared_ptr<NameserverEntry> delta(new NameserverEntry(EXAMPLE_CO_UK,
        RRClass::IN()));
    fillNSEntry(delta, rrv4_, shared_ptr<BasicRRset>());
    EXPECT_GT(delta->getExpiration(), rrv4_->getTTL().getValue());
}


// Test that the name of this nameserver is set correctly.
TEST_F(NameserverEntryTest, CheckName) {

    // Default constructor
    NameserverEntry alpha(EXAMPLE_CO_UK, RRClass::IN());
    EXPECT_EQ(EXAMPLE_CO_UK, alpha.getName());
}

// Check that it can cope with non-IN classes.
TEST_F(NameserverEntryTest, CheckClass) {

    // Default constructor
    NameserverEntry alpha(EXAMPLE_CO_UK, RRClass::CH());
    EXPECT_EQ(RRClass::CH(), alpha.getClass());
}

// Tests if it asks the IP addresses and calls callbacks when it comes
// including the right addresses are returned and that they expire
TEST_F(NameserverEntryTest, IPCallbacks) {
    shared_ptr<NameserverEntry> entry(new NameserverEntry(EXAMPLE_CO_UK,
        RRClass::IN()));
    shared_ptr<Callback> callback(new Callback);
    shared_ptr<TestResolver> resolver(new TestResolver);

    entry->askIP(resolver, callback, ANY_OK);
    // Ensure it becomes IN_PROGRESS
    EXPECT_EQ(Fetchable::IN_PROGRESS, entry->getState());
    // Now, there should be two queries in the resolver
    EXPECT_EQ(2, resolver->requests.size());
    ASSERT_TRUE(resolver->asksIPs(Name(EXAMPLE_CO_UK), 0, 1));

    // Another one might ask
    entry->askIP(resolver, callback, V4_ONLY);
    // There should still be only two queries in the resolver
    ASSERT_EQ(2, resolver->requests.size());

    // Another one, with need of IPv6 address
    entry->askIP(resolver, callback, V6_ONLY);

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
        RRClass::IN()));
    shared_ptr<Callback> callback(new Callback);
    shared_ptr<TestResolver> resolver(new TestResolver);

    // Ask for its IP
    entry->askIP(resolver, callback, ANY_OK);
    // Check it asks the resolver
    EXPECT_EQ(2, resolver->requests.size());
    ASSERT_TRUE(resolver->asksIPs(Name(EXAMPLE_CO_UK), 0, 1));
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

/*
 * TODO: There should be some more tests. What happens if it times out, then
 * the data are the same or different. What if the resolver answers directly
 * from within the call (recurses)? Does it still work?
 */

}   // namespace
