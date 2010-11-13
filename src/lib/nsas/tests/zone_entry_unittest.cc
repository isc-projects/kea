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

#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include <dns/rrclass.h>

#include "../asiolink.h"
#include "../zone_entry.h"
#include "../nameserver_entry.h"
#include "../address_request_callback.h"

#include "nsas_test.h"

using namespace asiolink;
using namespace std;
using namespace boost;
using namespace isc::dns;

namespace isc {
namespace nsas {

// String constants.  These should end in a dot.
static const std::string EXAMPLE_CO_UK("example.co.uk.");
static const std::string EXAMPLE_NET("example.net.");

/// \brief Test Fixture Class
class ZoneEntryTest : public ::testing::Test {
protected:

};

/// Tests of the default constructor
TEST_F(ZoneEntryTest, DefaultConstructor) {

    // Default constructor should not create any RRsets
    ZoneEntry alpha(EXAMPLE_CO_UK, RRClass::IN().getCode());
    EXPECT_EQ(EXAMPLE_CO_UK, alpha.getName());
    EXPECT_EQ(RRClass::IN().getCode(), alpha.getClass());
}

namespace {
// Just something that can be created and passed
class Callback : public AddressRequestCallback {
    public:
        void success(const asiolink::IOAddress&) { };
        void unreachable() { };
};
}

TEST_F(ZoneEntryTest, Callbacks) {
    const size_t count(3);
    shared_ptr<AddressRequestCallback> callbacks[count];

    ZoneEntry zone(EXAMPLE_CO_UK, RRClass::IN().getCode());
    EXPECT_FALSE(zone.hasCallbacks());
    for (size_t i(0); i < count; ++ i) {
        zone.addCallback(callbacks[i] = shared_ptr<AddressRequestCallback>(
            new Callback));
    }
    for (size_t i(0); i < count; ++ i) {
        ASSERT_TRUE(zone.hasCallbacks());
        EXPECT_EQ(callbacks[i], zone.popCallback());
    }
    EXPECT_FALSE(zone.hasCallbacks());
}

TEST_F(ZoneEntryTest, NameserverIterators) {
    ZoneEntry zone(EXAMPLE_CO_UK, RRClass::IN().getCode());
    shared_ptr<NameserverEntry> nse(new NameserverEntry(EXAMPLE_CO_UK,
        RRClass::IN().getCode()));
    // The iterator can't be printed, so we can't use EQ
    const ZoneEntry& zone_const(zone);
    EXPECT_TRUE(zone.begin() == zone.end());
    EXPECT_TRUE(zone_const.begin() == zone_const.end());
    zone.nameserverAdd(nse);
    EXPECT_FALSE(zone.begin() == zone.end());
    EXPECT_FALSE(zone_const.begin() == zone_const.end());
    EXPECT_TRUE(*zone.begin() == nse);
    EXPECT_TRUE(*zone_const.begin() == nse);
    EXPECT_TRUE(zone.begin() + 1 == zone.end());
    EXPECT_TRUE(zone_const.begin() + 1 == zone_const.end());
}

void lockAndWait(ZoneEntry* zone, barrier* when) {
    ZoneEntry::Lock lock(zone->getLock());
    when->wait();
}

void lockAndKeep(ZoneEntry* zone, bool* locked_self, bool* locked_other,
    barrier* when)
{
    // Lock
    ZoneEntry::Lock lock(zone->getLock());
    *locked_self = true;
    // Wait for the start of the other thread
    when->wait();
    // Make sure the other thread gets a chance to run
    for (int i(0); i < 100; ++ i) {
        this_thread::yield();
        EXPECT_FALSE(*locked_other);
    }
    *locked_self = false;
}

TEST_F(ZoneEntryTest, Lock) {
    // Create some testing data
    ZoneEntry z1(EXAMPLE_CO_UK, RRClass::IN().getCode());
    ZoneEntry z2(EXAMPLE_NET, RRClass::IN().getCode());
    shared_ptr<NameserverEntry> ns1(new NameserverEntry(EXAMPLE_CO_UK,
        RRClass::IN().getCode()));
    shared_ptr<NameserverEntry> ns2(new NameserverEntry(EXAMPLE_NET,
        RRClass::IN().getCode()));
    z1.nameserverAdd(ns1);
    z2.nameserverAdd(ns2);

    barrier both(2);

    // This tries that both can lock right now.
    // FIXME If they can't it will deadlock. Any idea how to do it better?
    thread t1(lockAndWait, &z1, &both);
    thread t2(lockAndWait, &z2, &both);
    t1.join();
    t2.join();

    z1.nameserverAdd(ns2);
    z2.nameserverAdd(ns1);
    // Now check that they can't both lock at the same time.
    barrier both_second(2);
    bool l1(false), l2(false);
    thread t3(lockAndKeep, &z1, &l1, &l2, &both);
    thread t4(lockAndKeep, &z2, &l2, &l1, &both_second);
    both.wait();
    // Make sure one of them is started
    for (int i(0); i < 100; ++ i) {
        this_thread::yield();
    }
    both_second.wait();
    t3.join();
    t4.join();

    // Try it the other way around (so it does not depend on the order of nameservers
    thread t6(lockAndKeep, &z2, &l2, &l1, &both);
    thread t5(lockAndKeep, &z1, &l1, &l2, &both_second);
    both.wait();
    // Make sure one of them is started
    for (int i(0); i < 100; ++ i) {
        this_thread::yield();
    }
    both_second.wait();
    t5.join();
    t6.join();
}

}   // namespace nsas
}   // namespace isc
