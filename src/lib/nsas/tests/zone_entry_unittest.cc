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

#include <dns/rrclass.h>
#include <dns/rdataclass.h>

#include "../asiolink.h"
#include "../zone_entry.h"
#include "../nameserver_entry.h"
#include "../address_request_callback.h"
#include "../nsas_entry_compare.h"
#include "../hash_deleter.h"

#include "nsas_test.h"

using namespace isc::nsas;
using namespace asiolink;
using namespace std;
using namespace boost;
using namespace isc::dns;

namespace {

/// \brief Test Fixture Class
class ZoneEntryTest : public TestWithRdata {
protected:
    /// \brief Constructor
    ZoneEntryTest() :
        nameserver_table_(new HashTable<NameserverEntry>(
            new NsasEntryCompare<NameserverEntry>)),
        nameserver_lru_(new LruList<NameserverEntry>(
            (3 * nameserver_table_->tableSize()),
            new HashDeleter<NameserverEntry>(*nameserver_table_))),
        resolver_(new TestResolver),
        callback_(new Callback)
    { }
    /// \brief Tables of nameservers to pass into zone entry constructor
    shared_ptr<HashTable<NameserverEntry> > nameserver_table_;
    shared_ptr<LruList<NameserverEntry> > nameserver_lru_;
    /// \brief The resolver
    shared_ptr<TestResolver> resolver_;

    struct Callback : public AddressRequestCallback {
        Callback() : unreachable_count_(0) {}
        size_t unreachable_count_;
        vector<IOAddress> successes_;
        virtual void unreachable() { unreachable_count_ ++; }
        virtual void success(const IOAddress& address) {
            successes_.push_back(address);
        }
    };
    shared_ptr<Callback> callback_;
};

/// \brief Inherited version with access into its internals for tests
class InheritedZoneEntry : public ZoneEntry {
    public:
        InheritedZoneEntry(shared_ptr<ResolverInterface> resolver,
            const std::string& name, const RRClass& class_code,
            shared_ptr<HashTable<NameserverEntry> > nameserver_table,
            shared_ptr<LruList<NameserverEntry> > nameserver_lru) :
            ZoneEntry(resolver, name, class_code, nameserver_table,
                nameserver_lru)
        { }
        NameserverVector& nameservers() { return nameservers_; }
};

/// Tests of the default constructor
TEST_F(ZoneEntryTest, DefaultConstructor) {

    // Default constructor should not create any RRsets
    InheritedZoneEntry alpha(resolver_, EXAMPLE_CO_UK,
        RRClass::IN(), nameserver_table_, nameserver_lru_);
    EXPECT_EQ(EXAMPLE_CO_UK, alpha.getName());
    EXPECT_EQ(RRClass::IN(), alpha.getClass());
    EXPECT_TRUE(alpha.nameservers().empty());
}

// It should answer negatively right away if there are no nameservers
TEST_F(ZoneEntryTest, CallbackNoNS) {
    shared_ptr<InheritedZoneEntry> zone(new InheritedZoneEntry(resolver_,
        EXAMPLE_CO_UK, RRClass::IN(), nameserver_table_, nameserver_lru_));
    EXPECT_EQ(Fetchable::NOT_ASKED, zone->getState());
    // It should accept the callback
    zone->addCallback(callback_, ANY_OK, zone);
    EXPECT_EQ(Fetchable::IN_PROGRESS, zone->getState());
    // Ask for the nameservers
    EXPECT_NO_THROW(resolver_->provideNS(0, rr_empty_));
    // And tell imediatelly that it is unreachable (when it has no nameservers)
    EXPECT_TRUE(callback_->successes_.empty());
    EXPECT_EQ(1, callback_->unreachable_count_);
}

// Check it accepts the first callback with 0 TTL
TEST_F(ZoneEntryTest, CallbackZeroTTL) {
    // Make it zero TTL, so it expires right away
    rr_single_->setTTL(RRTTL(0));
    shared_ptr<InheritedZoneEntry> zone(new InheritedZoneEntry(resolver_,
        EXAMPLE_CO_UK, RRClass::IN(), nameserver_table_, nameserver_lru_));
    EXPECT_EQ(Fetchable::NOT_ASKED, zone->getState());
    // It should accept the callback
    zone->addCallback(callback_, ANY_OK, zone);
    EXPECT_EQ(Fetchable::IN_PROGRESS, zone->getState());
    EXPECT_NO_THROW(resolver_->provideNS(0, rr_single_));
    // It should not be answered yet, it should ask for the IP addresses
    EXPECT_TRUE(callback_->successes_.empty());
    EXPECT_EQ(0, callback_->unreachable_count_);
    resolver_->asksIPs(ns_name_, 1, 2);
    // It should request the NSs again, as TTL is 0
    zone->addCallback(callback_, ANY_OK, zone);
    EXPECT_EQ(4, resolver_->requests.size());
}

// Check it answers callbacks when we give it addresses
TEST_F(ZoneEntryTest, CallbacksAnswered) {
    shared_ptr<InheritedZoneEntry> zone(new InheritedZoneEntry(resolver_,
        EXAMPLE_CO_UK, RRClass::IN(), nameserver_table_, nameserver_lru_));
    // It should be in NOT_ASKED state
    EXPECT_EQ(Fetchable::NOT_ASKED, zone->getState());
    // It should accept the callback
    zone->addCallback(callback_, ANY_OK, zone);
    EXPECT_EQ(Fetchable::IN_PROGRESS, zone->getState());
    EXPECT_NO_THROW(resolver_->provideNS(0, rr_single_));
    // It should not be answered yet, it should ask for the IP addresses
    EXPECT_TRUE(callback_->successes_.empty());
    EXPECT_EQ(0, callback_->unreachable_count_);
    resolver_->asksIPs(ns_name_, 1, 2);
    // We should be READY, as it marks we have nameservers
    // (not that they are ready)
    EXPECT_EQ(Fetchable::READY, zone->getState());
    // Give two more callbacks, with different address families
    zone->addCallback(callback_, V4_ONLY, zone);
    zone->addCallback(callback_, V6_ONLY, zone);
    // Nothing more is asked
    EXPECT_EQ(3, resolver_->requests.size());
    EXPECT_NO_THROW(resolver_->answer(1, ns_name_, RRType::A(),
         rdata::in::A("192.0.2.1")));
    // Two are answered (ANY and V4)
    ASSERT_EQ(2, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("192.0.2.1").equal(callback_->successes_[0]));
    EXPECT_TRUE(IOAddress("192.0.2.1").equal(callback_->successes_[1]));
    // None are rejected
    EXPECT_EQ(0, callback_->unreachable_count_);
    EXPECT_NO_THROW(resolver_->answer(2, ns_name_, RRType::AAAA(),
        rdata::in::AAAA("2001:db8::1")));
    // This should answer the third callback
    EXPECT_EQ(0, callback_->unreachable_count_);
    ASSERT_EQ(3, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("2001:db8::1").equal(callback_->successes_[2]));
    // It should think it is ready
    EXPECT_EQ(Fetchable::READY, zone->getState());
    // When we ask something more, it should be answered right away
    zone->addCallback(callback_, V4_ONLY, zone);
    EXPECT_EQ(3, resolver_->requests.size());
    ASSERT_EQ(4, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("192.0.2.1").equal(callback_->successes_[3]));
    EXPECT_EQ(0, callback_->unreachable_count_);
}

// Pretend the server can be reached only by IPv4
TEST_F(ZoneEntryTest, CallbacksAOnly) {
    shared_ptr<InheritedZoneEntry> zone(new InheritedZoneEntry(resolver_,
        EXAMPLE_CO_UK, RRClass::IN(), nameserver_table_, nameserver_lru_));
    // It should be in NOT_ASKED state
    EXPECT_EQ(Fetchable::NOT_ASKED, zone->getState());
    // It should accept the callback
    zone->addCallback(callback_, ANY_OK, zone);
    EXPECT_EQ(Fetchable::IN_PROGRESS, zone->getState());
    EXPECT_NO_THROW(resolver_->provideNS(0, rr_single_));
    // It should not be answered yet, it should ask for the IP addresses
    EXPECT_TRUE(callback_->successes_.empty());
    EXPECT_EQ(0, callback_->unreachable_count_);
    resolver_->asksIPs(ns_name_, 1, 2);
    EXPECT_EQ(Fetchable::READY, zone->getState());
    // Give two more callbacks, with different address families
    zone->addCallback(callback_, V4_ONLY, zone);
    zone->addCallback(callback_, V6_ONLY, zone);
    ASSERT_GE(resolver_->requests.size(), 3);
    resolver_->requests[2].second->failure();
    // One should be rejected, but two still stay, they have chance
    EXPECT_EQ(0, callback_->successes_.size());
    EXPECT_EQ(1, callback_->unreachable_count_);
    // Answer the A one and see it answers what can be answered
    EXPECT_NO_THROW(resolver_->answer(1, ns_name_, RRType::A(),
        rdata::in::A("192.0.2.1")));
    ASSERT_EQ(2, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("192.0.2.1").equal(callback_->successes_[0]));
    EXPECT_TRUE(IOAddress("192.0.2.1").equal(callback_->successes_[1]));
    EXPECT_EQ(1, callback_->unreachable_count_);
    // Everything arriwed, so we are ready
    EXPECT_EQ(Fetchable::READY, zone->getState());
    // Try asking something more
    zone->addCallback(callback_, V4_ONLY, zone);
    EXPECT_EQ(3, resolver_->requests.size());
    ASSERT_EQ(3, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("192.0.2.1").equal(callback_->successes_[2]));
    EXPECT_EQ(1, callback_->unreachable_count_);

    zone->addCallback(callback_, V6_ONLY, zone);
    EXPECT_EQ(3, resolver_->requests.size());
    EXPECT_EQ(3, callback_->successes_.size());
    EXPECT_EQ(2, callback_->unreachable_count_);
}

// See it tries hard enough to get address and tries both nameservers
TEST_F(ZoneEntryTest, CallbackTwoNS) {
    shared_ptr<InheritedZoneEntry> zone(new InheritedZoneEntry(resolver_,
        EXAMPLE_CO_UK, RRClass::IN(), nameserver_table_, nameserver_lru_));
    // It should be in NOT_ASKED state
    EXPECT_EQ(Fetchable::NOT_ASKED, zone->getState());
    // It should accept the callback
    zone->addCallback(callback_, V4_ONLY, zone);
    EXPECT_EQ(Fetchable::IN_PROGRESS, zone->getState());
    EXPECT_NO_THROW(resolver_->provideNS(0, rrns_));
    EXPECT_EQ(Fetchable::READY, zone->getState());
    // It asks a question (we do not know which nameserver)
    shared_ptr<Name> name;
    ASSERT_NO_THROW(name.reset(new Name((*resolver_)[1]->getName())));
    ASSERT_TRUE(resolver_->asksIPs(*name, 1, 2));
    resolver_->requests[1].second->failure();
    // Nothing should be answered or failed yet
    EXPECT_EQ(0, callback_->unreachable_count_);
    EXPECT_EQ(0, callback_->successes_.size());
    ASSERT_TRUE(resolver_->asksIPs((*resolver_)[3]->getName(), 3, 4));
    // Fail the second one
    resolver_->requests[3].second->failure();
    // The callback should be failed now, as there is no chance of getting
    // v4 address
    EXPECT_EQ(1, callback_->unreachable_count_);
    EXPECT_EQ(0, callback_->successes_.size());
    // And question for v6 or any should still wait while v4 should be failed
    // right away
    zone->addCallback(callback_, V6_ONLY, zone);
    EXPECT_EQ(1, callback_->unreachable_count_);
    EXPECT_EQ(0, callback_->successes_.size());

    zone->addCallback(callback_, ANY_OK, zone);
    EXPECT_EQ(1, callback_->unreachable_count_);
    EXPECT_EQ(0, callback_->successes_.size());

    zone->addCallback(callback_, V4_ONLY, zone);
    EXPECT_EQ(2, callback_->unreachable_count_);
    EXPECT_EQ(0, callback_->successes_.size());
    // Answer the IPv6 one
    EXPECT_NO_THROW(resolver_->answer(2, (*resolver_)[2]->getName(),
        RRType::AAAA(), rdata::in::AAAA("2001:db8::1")));

    // Ready, as we have at last some address
    EXPECT_EQ(Fetchable::READY, zone->getState());
    // The other callbacks should be answered now
    EXPECT_EQ(2, callback_->unreachable_count_);
    ASSERT_EQ(2, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("2001:db8::1").equal(callback_->successes_[0]));
    EXPECT_TRUE(IOAddress("2001:db8::1").equal(callback_->successes_[1]));
}

}   // namespace
