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

#include <config.h>

#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <cmath>

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
using namespace isc::asiolink;
using namespace std;
using namespace isc::dns;
using namespace isc::util;

namespace {

/// \brief Inherited version with access into its internals for tests
class InheritedZoneEntry : public ZoneEntry {
    public:
        InheritedZoneEntry(
            boost::shared_ptr<isc::resolve::ResolverInterface> resolver,
            const std::string& name, const RRClass& class_code,
            boost::shared_ptr<HashTable<NameserverEntry> > nameserver_table,
            boost::shared_ptr<LruList<NameserverEntry> > nameserver_lru) :
            ZoneEntry(resolver.get(), name, class_code, nameserver_table,
                nameserver_lru)
        { }
        NameserverVector& nameservers() { return nameservers_; }
};

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
    boost::shared_ptr<HashTable<NameserverEntry> > nameserver_table_;
    boost::shared_ptr<LruList<NameserverEntry> > nameserver_lru_;
    /// \brief The resolver
    boost::shared_ptr<TestResolver> resolver_;

    /**
     * \short A callback we use into the zone.
     *
     * It counts failures and stores successufll results.
     */
    struct Callback : public AddressRequestCallback {
        Callback() : unreachable_count_(0) {}
        size_t unreachable_count_;
        vector<NameserverAddress> successes_;
        virtual void unreachable() { unreachable_count_ ++; }
        virtual void success(const NameserverAddress& address) {
            successes_.push_back(address);
        }
    };
    boost::shared_ptr<Callback> callback_;

    // Empty callback to pass to nameserver entry, to do injection of them
    struct NseCallback : public NameserverEntry::Callback {
        virtual void operator()(boost::shared_ptr<NameserverEntry>) { }
    };

    boost::shared_ptr<NseCallback> nseCallback() {
        return (boost::shared_ptr<NseCallback>(new NseCallback));
    }

    /**
     * \short Function returning a new zone.
     *
     * Convenience function, just creating a new zone, to shorten the code.
     */
    boost::shared_ptr<InheritedZoneEntry> getZone() {
        return (boost::shared_ptr<InheritedZoneEntry>(new InheritedZoneEntry(
            resolver_, EXAMPLE_CO_UK, RRClass::IN(), nameserver_table_,
            nameserver_lru_)));
    }

    /**
     * \short Creates and injects a NameserverEntry
     *
     * This is used by few tests checking it works when the nameserver
     * hash table already contains the NameserverEntry. This function
     * creates one and puts it into the hash table.
     */
    boost::shared_ptr<NameserverEntry> injectEntry() {
        boost::shared_ptr<NameserverEntry> nse(new NameserverEntry(ns_name_.toText(),
            RRClass::IN()));
        nameserver_table_->add(nse, HashKey(ns_name_.toText(), RRClass::IN()));
        EXPECT_EQ(Fetchable::NOT_ASKED, nse->getState());
        return (nse);
    }

    /**
     * \short Common part of few tests.
     *
     * All the tests NameserverEntryReady, NameserverEntryNotAsked,
     * NameserverEntryInProgress, NameserverEntryExpired,
     * NameserverEntryUnreachable check that it does not break
     * when the nameserver hash table already contains the nameserver
     * in one of the Fetchable::State.
     *
     * All the tests prepare the NameserverEntry and then call this
     * to see if the zone really works. This asks and checks if it
     * asks for the IP addresses or not and if it succeeds or fails.
     *
     * \param answer Should it ask for IP addresses of the nameserver?
     *     If not, it expects it already asked during the preparation
     *     (therefore the request count in resolver is 2).
     * \param success_count How many callbacks to the zone should
     *     succeed.
     * \param failure_count How many callbacks to the zone should
     *     fail.
     */
    void checkInjected(bool answer, size_t success_count = 1,
        size_t failure_count = 0)
    {
        // Create the zone and check it acts correctly
        boost::shared_ptr<InheritedZoneEntry> zone(getZone());
        resolver_->addPresetAnswer(Question(Name(EXAMPLE_CO_UK), RRClass::IN(),
            RRType::NS()), rr_single_);
        zone->addCallback(callback_, ANY_OK);
        EXPECT_EQ(2, resolver_->requests.size());
        EXPECT_TRUE(resolver_->asksIPs(ns_name_, 0, 1));
        if (answer) {
            EXPECT_NO_THROW(resolver_->answer(0, ns_name_, RRType::A(),
                rdata::in::A("192.0.2.1")));
            EXPECT_NO_THROW(resolver_->answer(1, ns_name_, RRType::AAAA(),
                rdata::in::AAAA("2001:db8::1")));
        }
        // Check the answers
        EXPECT_EQ(Fetchable::READY, zone->getState());
        EXPECT_EQ(failure_count, callback_->unreachable_count_);
        EXPECT_EQ(success_count, callback_->successes_.size());
        for (size_t i = 0; i < callback_->successes_.size(); ++ i) {
            EXPECT_TRUE(IOAddress("192.0.2.1").equals(
                callback_->successes_[i].getAddress()) ||
                IOAddress("2001:db8::1").equals(
                callback_->successes_[i].getAddress()));
        }
    }
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

/**
 * \short Test with no nameservers.
 *
 * When we create a zone that does not have any nameservers,
 * it should return failures right away (eg. no queries to nameservers
 * should be generated anywhere and the failure should be provided).
 */
TEST_F(ZoneEntryTest, CallbackNoNS) {
    boost::shared_ptr<InheritedZoneEntry> zone(getZone());
    EXPECT_EQ(Fetchable::NOT_ASKED, zone->getState());
    // feed it with a callback
    zone->addCallback(callback_, ANY_OK);
    EXPECT_EQ(Fetchable::IN_PROGRESS, zone->getState());
    // Give it the (empty) nameserver list
    EXPECT_NO_THROW(resolver_->provideNS(0, rr_empty_));
    // It should tell us it is unreachable.
    EXPECT_TRUE(callback_->successes_.empty());
    EXPECT_EQ(1, callback_->unreachable_count_);
}

/**
 * \short Test how the zone behaves when the list of nameserves change.
 *
 * We use TTL of 0, so it asks every time for new list of nameservers.
 * This allows us to pass a different list each time.
 *
 * So, this implicitly tests that it behaves correctly with 0 TTL as well,
 * it means that it answers even with 0 TTL and that it answers only
 * one query (or, all queries queued at that time).
 *
 * We change the list twice, to see it can ask for another nameserver and
 * then to see if it can return to the previous (already cached) nameserver.
 */
TEST_F(ZoneEntryTest, ChangedNS) {
    // Make it zero TTL, so it expires right away
    rr_single_->setTTL(RRTTL(0));
    boost::shared_ptr<InheritedZoneEntry> zone(getZone());
    EXPECT_EQ(Fetchable::NOT_ASKED, zone->getState());
    // Feed it with callback
    zone->addCallback(callback_, ANY_OK);
    EXPECT_EQ(Fetchable::IN_PROGRESS, zone->getState());
    EXPECT_NO_THROW(resolver_->provideNS(0, rr_single_));
    // It should not be answered yet, it should ask for the IP addresses
    // (through the NameserverEntry there)
    EXPECT_TRUE(callback_->successes_.empty());
    EXPECT_EQ(0, callback_->unreachable_count_);
    EXPECT_TRUE(resolver_->asksIPs(ns_name_, 1, 2));
    EXPECT_NO_THROW(resolver_->answer(1, ns_name_, RRType::A(),
        rdata::in::A("192.0.2.1")));
    ASSERT_EQ(1, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("192.0.2.1").equals(
        callback_->successes_[0].getAddress()));
    EXPECT_NO_THROW(resolver_->answer(2, ns_name_, RRType::AAAA(),
        rdata::in::AAAA("2001:db8::1")));
    EXPECT_EQ(1, callback_->successes_.size());
    // It should request the NSs again, as TTL is 0
    zone->addCallback(callback_, ANY_OK);
    EXPECT_EQ(4, resolver_->requests.size());
    EXPECT_EQ(Fetchable::IN_PROGRESS, zone->getState());

    Name different_name("ns.example.com");
    // Create a different answer
    RRsetPtr different_ns(new RRset(Name(EXAMPLE_CO_UK), RRClass::IN(),
        RRType::NS(), RRTTL(0)));
    different_ns->addRdata(rdata::generic::NS(different_name));
    EXPECT_NO_THROW(resolver_->provideNS(3, different_ns));
    // It should become ready and ask for the new nameserver addresses
    EXPECT_EQ(Fetchable::READY, zone->getState());
    // Answer one of the IP addresses, we should get an address now
    EXPECT_TRUE(resolver_->asksIPs(different_name, 4, 5));
    EXPECT_NO_THROW(resolver_->answer(4, different_name, RRType::A(),
        rdata::in::A("192.0.2.2")));
    ASSERT_EQ(2, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("192.0.2.2").equals(
        callback_->successes_[1].getAddress()));

    // And now, switch back, as it timed out again
    zone->addCallback(callback_, ANY_OK);
    EXPECT_EQ(7, resolver_->requests.size());
    EXPECT_EQ(Fetchable::IN_PROGRESS, zone->getState());
    // When we answer with the original, it should still be cached and
    // we should get the answer
    EXPECT_NO_THROW(resolver_->provideNS(0, rr_single_));
    EXPECT_EQ(7, resolver_->requests.size());
    EXPECT_EQ(Fetchable::READY, zone->getState());
    ASSERT_EQ(3, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("192.0.2.1").equals(
        callback_->successes_[0].getAddress()));
}

/**
 * \short Check it works when everything is answered.
 *
 * This test emulates a situation when all queries for NS rrsets and
 * IP addresses (of the NameserverEntry objects inside) are answered
 * positively. All the callbacks should be called and answer to them
 * provided.
 */
TEST_F(ZoneEntryTest, CallbacksAnswered) {
    boost::shared_ptr<InheritedZoneEntry> zone(getZone());
    EXPECT_EQ(Fetchable::NOT_ASKED, zone->getState());
    // Feed it with a callback
    zone->addCallback(callback_, ANY_OK);
    EXPECT_EQ(Fetchable::IN_PROGRESS, zone->getState());
    EXPECT_NO_THROW(resolver_->provideNS(0, rr_single_));
    // It should not be answered yet, its NameserverEntry should ask for the
    // IP addresses
    EXPECT_TRUE(callback_->successes_.empty());
    EXPECT_EQ(0, callback_->unreachable_count_);
    EXPECT_TRUE(resolver_->asksIPs(ns_name_, 1, 2));
    // We should be READY, as it marks we have nameservers
    // (not that they are ready)
    EXPECT_EQ(Fetchable::READY, zone->getState());
    // Give two more callbacks, with different address families
    zone->addCallback(callback_, V4_ONLY);
    zone->addCallback(callback_, V6_ONLY);
    // Nothing more is asked
    EXPECT_EQ(3, resolver_->requests.size());
    EXPECT_NO_THROW(resolver_->answer(1, ns_name_, RRType::A(),
         rdata::in::A("192.0.2.1")));
    // Two are answered (ANY and V4)
    ASSERT_EQ(2, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("192.0.2.1").equals(
        callback_->successes_[0].getAddress()));
    EXPECT_TRUE(IOAddress("192.0.2.1").equals(
        callback_->successes_[1].getAddress()));
    // None are rejected
    EXPECT_EQ(0, callback_->unreachable_count_);
    // Answer the IPv6 one as well
    EXPECT_NO_THROW(resolver_->answer(2, ns_name_, RRType::AAAA(),
        rdata::in::AAAA("2001:db8::1")));
    // This should answer the third callback
    EXPECT_EQ(0, callback_->unreachable_count_);
    ASSERT_EQ(3, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("2001:db8::1").equals(
        callback_->successes_[2].getAddress()));
    // It should think it is ready
    EXPECT_EQ(Fetchable::READY, zone->getState());
    // When we ask something more, it should be answered right away
    zone->addCallback(callback_, V4_ONLY);
    EXPECT_EQ(3, resolver_->requests.size());
    ASSERT_EQ(4, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("192.0.2.1").equals(
        callback_->successes_[3].getAddress()));
    EXPECT_EQ(0, callback_->unreachable_count_);
}

/**
 * \short Test zone reachable only on IPv4.
 *
 * This test simulates a zone with its nameservers reachable only
 * over IPv4. It means we answer the NS query, the A query, but
 * we generate a failure for AAAA.
 *
 * The callbacks asking for any address and IPv4 address should be
 * called successfully, while the ones asking for IPv6 addresses should
 * fail.
 */
TEST_F(ZoneEntryTest, CallbacksAOnly) {
    boost::shared_ptr<InheritedZoneEntry> zone(getZone());
    EXPECT_EQ(Fetchable::NOT_ASKED, zone->getState());
    zone->addCallback(callback_, ANY_OK);
    EXPECT_EQ(Fetchable::IN_PROGRESS, zone->getState());
    EXPECT_NO_THROW(resolver_->provideNS(0, rr_single_));
    // It should not be answered yet, it should ask for the IP addresses
    EXPECT_TRUE(callback_->successes_.empty());
    EXPECT_EQ(0, callback_->unreachable_count_);
    EXPECT_TRUE(resolver_->asksIPs(ns_name_, 1, 2));
    EXPECT_EQ(Fetchable::READY, zone->getState());
    // Give two more callbacks, with different address families
    zone->addCallback(callback_, V4_ONLY);
    zone->addCallback(callback_, V6_ONLY);
    ASSERT_GE(resolver_->requests.size(), 3);
    // We tell its NameserverEntry we can't get IPv6 address
    resolver_->requests[2].second->failure();
    // One should be rejected (V6_ONLY one), but two still stay
    EXPECT_EQ(0, callback_->successes_.size());
    EXPECT_EQ(1, callback_->unreachable_count_);
    // Answer the A one and see it answers what can be answered
    EXPECT_NO_THROW(resolver_->answer(1, ns_name_, RRType::A(),
        rdata::in::A("192.0.2.1")));
    ASSERT_EQ(2, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("192.0.2.1").equals(
        callback_->successes_[0].getAddress()));
    EXPECT_TRUE(IOAddress("192.0.2.1").equals(
        callback_->successes_[1].getAddress()));
    EXPECT_EQ(1, callback_->unreachable_count_);
    // Everything arrived, so we are ready
    EXPECT_EQ(Fetchable::READY, zone->getState());
    // Try asking something more and see it asks no more
    zone->addCallback(callback_, V4_ONLY);
    EXPECT_EQ(3, resolver_->requests.size());
    ASSERT_EQ(3, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("192.0.2.1").equals(
        callback_->successes_[2].getAddress()));
    EXPECT_EQ(1, callback_->unreachable_count_);

    zone->addCallback(callback_, V6_ONLY);
    EXPECT_EQ(3, resolver_->requests.size());
    EXPECT_EQ(3, callback_->successes_.size());
    EXPECT_EQ(2, callback_->unreachable_count_);
}

/**
 * \short Test with unreachable and v6-reachable nameserver.
 *
 * In this test we have a zone with two nameservers. The first one of them
 * is unreachable, it will not have any addresses. We check that the ZoneEntry
 * is patient and asks and waits for the second one and then returns the
 * (successful) answers to us.
 */
TEST_F(ZoneEntryTest, CallbackTwoNS) {
    boost::shared_ptr<InheritedZoneEntry> zone(getZone());
    EXPECT_EQ(Fetchable::NOT_ASKED, zone->getState());
    zone->addCallback(callback_, V4_ONLY);
    EXPECT_EQ(Fetchable::IN_PROGRESS, zone->getState());
    EXPECT_NO_THROW(resolver_->provideNS(0, rrns_));
    EXPECT_EQ(Fetchable::READY, zone->getState());
    // It asks a question (we do not know which nameserver)
    boost::shared_ptr<Name> name;
    ASSERT_NO_THROW(name.reset(new Name((*resolver_)[1]->getName())));
    ASSERT_TRUE(resolver_->asksIPs(*name, 1, 2));
    resolver_->requests[1].second->failure();
    // Nothing should be answered or failed yet, there's second one
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
    zone->addCallback(callback_, V6_ONLY);
    EXPECT_EQ(1, callback_->unreachable_count_);
    EXPECT_EQ(0, callback_->successes_.size());

    zone->addCallback(callback_, ANY_OK);
    EXPECT_EQ(1, callback_->unreachable_count_);
    EXPECT_EQ(0, callback_->successes_.size());

    zone->addCallback(callback_, V4_ONLY);
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
    EXPECT_TRUE(IOAddress("2001:db8::1").equals(
        callback_->successes_[0].getAddress()));
    EXPECT_TRUE(IOAddress("2001:db8::1").equals(
        callback_->successes_[1].getAddress()));
}

/**
 * \short This test checks it works with answers from cache.
 *
 * The resolver might provide the answer by calling the callback both sometime
 * later or directly from its resolve method, causing recursion back inside
 * the ZoneEntry. This test checks it works even in the second case (eg. that
 * the ZoneEntry is able to handle callback called directly from the
 * resolve). Tries checking both positive and negative answers.
 */
TEST_F(ZoneEntryTest, DirectAnswer) {
    boost::shared_ptr<InheritedZoneEntry> zone(getZone());
    EXPECT_EQ(Fetchable::NOT_ASKED, zone->getState());

    // One unsuccessfull attempt, nameservers fail
    resolver_->addPresetAnswer(Question(Name(EXAMPLE_CO_UK), RRClass::IN(),
        RRType::NS()), RRsetPtr());
    zone->addCallback(callback_, ANY_OK);
    EXPECT_EQ(0, callback_->successes_.size());
    EXPECT_EQ(1, callback_->unreachable_count_);
    EXPECT_EQ(0, resolver_->requests.size());
    EXPECT_EQ(Fetchable::UNREACHABLE, zone->getState());

    // Successfull attempt now
    zone = getZone();
    // First, fill the answers to all the questions it should ask
    EXPECT_EQ(Fetchable::NOT_ASKED, zone->getState());
    resolver_->addPresetAnswer(Question(Name(EXAMPLE_CO_UK), RRClass::IN(),
        RRType::NS()), rr_single_);
    Name ns_name("ns.example.net");
    rrv4_->setName(ns_name);
    resolver_->addPresetAnswer(Question(ns_name, RRClass::IN(), RRType::A()),
        rrv4_);
    rrv6_->setName(ns_name);
    resolver_->addPresetAnswer(Question(ns_name, RRClass::IN(),
        RRType::AAAA()), rrv6_);
    // Reset the results
    callback_->unreachable_count_ = 0;
    // Ask for the IP address
    zone->addCallback(callback_, ANY_OK);
    // It should be answered right away, positively
    EXPECT_EQ(1, callback_->successes_.size());
    EXPECT_EQ(0, callback_->unreachable_count_);
    EXPECT_EQ(0, resolver_->requests.size());
    EXPECT_EQ(Fetchable::READY, zone->getState());

    // Reset the results
    callback_->successes_.clear();
    // Now, pretend we do not have IP addresses
    resolver_->addPresetAnswer(Question(ns_name, RRClass::IN(), RRType::A()),
        RRsetPtr());
    resolver_->addPresetAnswer(Question(ns_name, RRClass::IN(),
        RRType::AAAA()), RRsetPtr());
    // Get another zone and ask it again. It should fail.
    // Clean the table first, though, so it does not find the old nameserver
    nameserver_table_->remove(HashKey(ns_name.toText(), RRClass::IN()));
    zone = getZone();
    EXPECT_EQ(Fetchable::NOT_ASKED, zone->getState());
    zone->addCallback(callback_, ANY_OK);
    EXPECT_EQ(0, callback_->successes_.size());
    EXPECT_EQ(1, callback_->unreachable_count_);
    EXPECT_EQ(0, resolver_->requests.size());
    // It should be ready, but have no IP addresses on the nameservers
    EXPECT_EQ(Fetchable::READY, zone->getState());
}

/**
 * \short Test it works with timeouting NameserverEntries.
 *
 * In this test we have a zone with nameserver addresses at TTL 0.
 * So, the NameserverEntry expires each time the ZoneEntry tries to get
 * its addresses and must ask it again.
 */
TEST_F(ZoneEntryTest, AddressTimeout) {
    boost::shared_ptr<InheritedZoneEntry> zone(getZone());
    EXPECT_EQ(Fetchable::NOT_ASKED, zone->getState());
    zone->addCallback(callback_, ANY_OK);
    EXPECT_EQ(Fetchable::IN_PROGRESS, zone->getState());
    EXPECT_NO_THROW(resolver_->provideNS(0, rr_single_));
    // It should not be answered yet, it should ask for the IP addresses
    EXPECT_TRUE(callback_->successes_.empty());
    EXPECT_EQ(0, callback_->unreachable_count_);
    EXPECT_TRUE(resolver_->asksIPs(ns_name_, 1, 2));
    // We should be READY, as it marks we have nameservers
    // (not that they are ready)
    EXPECT_EQ(Fetchable::READY, zone->getState());
    EXPECT_NO_THROW(resolver_->answer(1, ns_name_, RRType::A(),
         rdata::in::A("192.0.2.1"), 0));
    // It answers, not rejects
    ASSERT_EQ(1, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("192.0.2.1").equals(
        callback_->successes_[0].getAddress()));
    EXPECT_EQ(0, callback_->unreachable_count_);
    // As well with IPv6
    EXPECT_NO_THROW(resolver_->answer(2, ns_name_, RRType::AAAA(),
        rdata::in::AAAA("2001:db8::1"), 0));
    EXPECT_EQ(1, callback_->successes_.size());
    EXPECT_EQ(Fetchable::READY, zone->getState());
    // When we ask for another one, it should ask for the addresses again
    zone->addCallback(callback_, ANY_OK);
    EXPECT_TRUE(resolver_->asksIPs(ns_name_, 3, 4));
    EXPECT_EQ(0, callback_->unreachable_count_);
    EXPECT_EQ(1, callback_->successes_.size());
    EXPECT_NO_THROW(resolver_->answer(3, ns_name_, RRType::A(),
         rdata::in::A("192.0.2.1"), 0));
    EXPECT_EQ(0, callback_->unreachable_count_);
    ASSERT_EQ(2, callback_->successes_.size());
    EXPECT_TRUE(IOAddress("192.0.2.1").equals(
        callback_->successes_[1].getAddress()));
}

/**
 * \short Injection tests.
 *
 * These tests check the ZoneEntry does not break when the nameserver hash
 * table already contains a NameserverEntry in some given state. Each test
 * for a different state.
 */
//@{

/// \short Test how the zone reacts to a nameserver entry in ready state
TEST_F(ZoneEntryTest, NameserverEntryReady) {
    // Inject the entry
    boost::shared_ptr<NameserverEntry> nse(injectEntry());
    // Fill it with data
    nse->askIP(resolver_.get(), nseCallback(), ANY_OK);
    EXPECT_EQ(Fetchable::IN_PROGRESS, nse->getState());
    EXPECT_TRUE(resolver_->asksIPs(ns_name_, 0, 1));
    EXPECT_NO_THROW(resolver_->answer(0, ns_name_, RRType::A(),
        rdata::in::A("192.0.2.1")));
    EXPECT_NO_THROW(resolver_->answer(1, ns_name_, RRType::AAAA(),
        rdata::in::AAAA("2001:db8::1")));
    EXPECT_EQ(Fetchable::READY, nse->getState());

    checkInjected(false);
}

/// \short Test how the zone reacts to a nameserver in not asked state
TEST_F(ZoneEntryTest, NameserverEntryNotAsked) {
    // Inject the entry
    injectEntry();
    // We do not need it, nothing to modify on it

    checkInjected(true);
}

/// \short What if the zone finds a nameserver in progress?
TEST_F(ZoneEntryTest, NameserverEntryInProgress) {
    // Prepare the nameserver entry
    boost::shared_ptr<NameserverEntry> nse(injectEntry());
    nse->askIP(resolver_.get(), nseCallback(), ANY_OK);
    EXPECT_EQ(Fetchable::IN_PROGRESS, nse->getState());
    EXPECT_TRUE(resolver_->asksIPs(ns_name_, 0, 1));

    checkInjected(true);
}

/// \short Check Zone's reaction to found expired nameserver
TEST_F(ZoneEntryTest, NameserverEntryExpired) {
    boost::shared_ptr<NameserverEntry> nse(injectEntry());
    nse->askIP(resolver_.get(), nseCallback(), ANY_OK);
    EXPECT_EQ(Fetchable::IN_PROGRESS, nse->getState());
    EXPECT_TRUE(resolver_->asksIPs(ns_name_, 0, 1));
    EXPECT_NO_THROW(resolver_->answer(0, ns_name_, RRType::A(),
        rdata::in::A("192.0.2.1"), 0));
    EXPECT_NO_THROW(resolver_->answer(1, ns_name_, RRType::AAAA(),
        rdata::in::AAAA("2001:db8::1"), 0));
    EXPECT_EQ(Fetchable::READY, nse->getState());
    NameserverEntry::AddressVector addresses;
    EXPECT_EQ(Fetchable::EXPIRED, nse->getAddresses(addresses));
    EXPECT_EQ(Fetchable::EXPIRED, nse->getState());
    resolver_->requests.clear();

    checkInjected(true);
}

/// \short Check how it reacts to an unreachable zone already in the table
TEST_F(ZoneEntryTest, NameserverEntryUnreachable) {
    boost::shared_ptr<NameserverEntry> nse(injectEntry());
    nse->askIP(resolver_.get(), nseCallback(), ANY_OK);
    ASSERT_EQ(2, resolver_->requests.size());
    resolver_->requests[0].second->failure();
    resolver_->requests[1].second->failure();
    EXPECT_EQ(Fetchable::UNREACHABLE, nse->getState());

    checkInjected(false, 0, 1);
}

//@}

// Count hits of each address
void
countHits(size_t *counts, const vector<NameserverAddress>& successes) {
    BOOST_FOREACH(const NameserverAddress& address, successes) {
        // We use the last digit as an index
        string address_string(address.getAddress().toText());
        size_t index(address_string[address_string.size() - 1] - '0' - 1);
        ASSERT_LT(index, 3);
        counts[index] ++;
    }
}

// Select one address from the address list
TEST_F(ZoneEntryTest, AddressSelection) {
    const size_t repeats = 100000;
    // Create the zone, give it 2 nameservers and total of 3 addresses
    // (one of them is ipv6)
    boost::shared_ptr<ZoneEntry> zone(getZone());
    zone->addCallback(callback_, ANY_OK);
    EXPECT_NO_THROW(resolver_->provideNS(0, rrns_));
    ASSERT_GT(resolver_->requests.size(), 1);
    Name name1(resolver_->requests[1].first->getName());
    EXPECT_TRUE(resolver_->asksIPs(name1, 1, 2));
    resolver_->answer(1, name1, RRType::A(), rdata::in::A("192.0.2.1"));
    resolver_->answer(2, name1, RRType::AAAA(),
        rdata::in::AAAA("2001:db8::2"));
    ASSERT_GT(resolver_->requests.size(), 3);
    Name name2(resolver_->requests[3].first->getName());
    EXPECT_TRUE(resolver_->asksIPs(name2, 3, 4));
    resolver_->answer(3, name2, RRType::A(), rdata::in::A("192.0.2.3"));
    resolver_->requests[4].second->failure();

    boost::shared_ptr<NameserverEntry> ns1(nameserver_table_->get(HashKey(
        name1.toText(), RRClass::IN()))),
        ns2(nameserver_table_->get(HashKey(name2.toText(), RRClass::IN())));

    size_t counts[3] = {0, 0, 0};
    callback_->successes_.clear();

    // Test they have the same probabilities when they have the same RTT
    for (size_t i(0); i < repeats; ++ i) {
        zone->addCallback(callback_, ANY_OK);
    }
    countHits(counts, callback_->successes_);
    // We repeat the simulation for N=repeats times
    // for each address, the probability is p = 1/3, the average mu = N*p
    // variance sigma^2 = N * p * (1-p) = N * 1/3 * 2/3 = N*2/9
    // sigma = sqrt(N*2/9)
    // we should make sure that mu - 4sigma < c < mu + 4sigma
    // which means for 99.99366% of the time this should be true
    double p = 1.0 / 3.0;
    double mu = repeats * p;
    double sigma = sqrt(repeats * p * (1 - p));
    for (size_t i(0); i < 3; ++ i) {
        ASSERT_TRUE(fabs(counts[i] - mu) < 4*sigma);
    }

    // reset the environment
    callback_->successes_.clear();
    counts[0] = counts[1] = counts[2] = 0;

    // Test when the RTT is not the same
    ns1->setAddressRTT(IOAddress("192.0.2.1"), 1);
    ns1->setAddressRTT(IOAddress("2001:db8::2"), 2);
    ns2->setAddressRTT(IOAddress("192.0.2.3"), 3);
    for (size_t i(0); i < repeats; ++ i) {
        zone->addCallback(callback_, ANY_OK);
    }
    countHits(counts, callback_->successes_);
    // We expect that the selection probability for each address that
    // it will be in the range of [mu-4Sigma, mu+4Sigma]
    double ps[3];
    ps[0] = 1.0/(1.0 + 1.0/4.0 + 1.0/9.0);
    ps[1] = (1.0/4.0)/(1.0 + 1.0/4.0 + 1.0/9.0);
    ps[2] = (1.0/9.0)/(1.0 + 1.0/4.0 + 1.0/9.0);
    for (size_t i(0); i < 3; ++ i) {
        double mu = repeats * ps[i];
        double sigma = sqrt(repeats * ps[i] * (1 - ps[i]));
        ASSERT_TRUE(fabs(counts[i] - mu) < 4 * sigma);
    }

    // reset the environment
    callback_->successes_.clear();
    counts[0] = counts[1] = counts[2] = 0;

    // Test with unreachable address
    ns1->setAddressRTT(IOAddress("192.0.2.1"), 1);
    ns1->setAddressRTT(IOAddress("2001:db8::2"), 100);
    ns2->setAddressUnreachable(IOAddress("192.0.2.3"));
    for (size_t i(0); i < repeats; ++ i) {
        zone->addCallback(callback_, ANY_OK);
    }
    countHits(counts, callback_->successes_);
    // The unreachable one shouldn't be called
    EXPECT_EQ(0, counts[2]);

    // reset the environment
    callback_->successes_.clear();
    counts[0] = counts[1] = counts[2] = 0;

    // Test with all unreachable
    ns1->setAddressUnreachable(IOAddress("192.0.2.1"));
    ns1->setAddressUnreachable(IOAddress("2001:db8::2"));
    ns2->setAddressUnreachable(IOAddress("192.0.2.3"));
    for (size_t i(0); i < repeats; ++ i) {
        zone->addCallback(callback_, ANY_OK);
    }
    countHits(counts, callback_->successes_);
    // They should have about the same probability
    for (size_t i(0); i < 3; ++ i) {
        ASSERT_TRUE(fabs(counts[i] - mu) < 4*sigma);
    }

    // TODO: The unreachable server should be changed to reachable after 5minutes, but how to test?
}

}   // namespace
