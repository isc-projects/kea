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

/// \brief Test Deleter Objects
///
/// This file contains tests for the "deleter" classes within the nameserver
/// address store.  These act to delete zones from the zone hash table when
/// the element reaches the top of the LRU list.

#include <dns/rrttl.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>

#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

#include <string.h>
#include <cassert>

#include "../nameserver_address_store.h"
#include "../nsas_entry_compare.h"
#include "../nameserver_entry.h"
#include "../zone_entry.h"
#include "../address_request_callback.h"
#include "nsas_test.h"

using namespace isc::dns;
using namespace std;
using namespace boost;

namespace isc {
namespace nsas {


/// \brief NSAS Store
///
/// This is a subclass of the NameserverAddressStore class, with methods to
/// access the internal members to check that the deleter objects are working.
class DerivedNsas : public NameserverAddressStore {
public:
    /// \brief Constructor
    ///
    /// \param hashsize Size of the zone hash table
    /// \param lrusize Size of the zone hash table
    DerivedNsas(shared_ptr<TestResolver> resolver, uint32_t hashsize,
        uint32_t lrusize) :
        NameserverAddressStore(resolver, hashsize, lrusize),
        resolver_(resolver)
    {}

    /// \brief Virtual Destructor
    virtual ~DerivedNsas()
    {}

    /// \brief Add Nameserver Entry to Hash and LRU Tables
    void AddNameserverEntry(boost::shared_ptr<NameserverEntry>& entry) {
        HashKey h = entry->hashKey();
        nameserver_hash_->add(entry, h);
        nameserver_lru_->add(entry);
    }

    /// \brief Add Zone Entry to Hash and LRU Tables
    void AddZoneEntry(boost::shared_ptr<ZoneEntry>& entry) {
        HashKey h = entry->hashKey();
        zone_hash_->add(entry, h);
        zone_lru_->add(entry);
    }
    /**
     * \short Just wraps the common lookup
     *
     * It calls the lookup and provides the authority section
     * if it is asked for by the resolver.
     */
    void lookupAndAnswer(const string& name, const RRClass& class_code,
        shared_ptr<AbstractRRset> authority,
        shared_ptr<AddressRequestCallback> callback)
    {
        size_t size(resolver_->requests.size());
        NameserverAddressStore::lookup(name, class_code, callback, ANY_OK);
        // It asked something, the only thing it can ask is the NS list
        if (size < resolver_->requests.size()) {
            resolver_->provideNS(size, authority);
            // Once answered, drop the request so noone else sees it
            resolver_->requests.erase(resolver_->requests.begin() + size);
        } else {
            ADD_FAILURE() << "Not asked for NS";
        }
    }
private:
    shared_ptr<TestResolver> resolver_;
};



/// \brief Text Fixture Class
class NameserverAddressStoreTest : public ::testing::Test {
protected:

    NameserverAddressStoreTest() :
        authority_(new RRset(Name("example.net."), RRClass::IN(), RRType::NS(),
            RRTTL(128))),
        empty_authority_(new RRset(Name("example.net."), RRClass::IN(),
            RRType::NS(), RRTTL(128))),
        resolver_(new TestResolver)
    {
        // Constructor - initialize a set of nameserver and zone objects.  For
        // convenience, these are stored in vectors.
        for (int i = 1; i <= 9; ++i) {
            std::string name = "nameserver" + boost::lexical_cast<std::string>(
                i);
            nameservers_.push_back(boost::shared_ptr<NameserverEntry>(
                new NameserverEntry(name, RRClass(40 + i))));
        }

        // Some zones. They will not use the tables in this test, so it can be
        // empty
        for (int i = 1; i <= 9; ++i) {
            std::string name = "zone" + boost::lexical_cast<std::string>(i);
            zones_.push_back(boost::shared_ptr<ZoneEntry>(new ZoneEntry(
                resolver_, name, RRClass(40 + i),
                shared_ptr<HashTable<NameserverEntry> >(),
                shared_ptr<LruList<NameserverEntry> >())));
        }

        // A nameserver serving data
        authority_->addRdata(ConstRdataPtr(new rdata::generic::NS(Name(
            "ns.example.com."))));

        // This is reused because of convenience, clear it just in case
        NSASCallback::results.clear();
    }

    // Vector of pointers to nameserver and zone entries.
    std::vector<boost::shared_ptr<NameserverEntry> > nameservers_;
    std::vector<boost::shared_ptr<ZoneEntry> >       zones_;

    RRsetPtr authority_, empty_authority_;

    shared_ptr<TestResolver> resolver_;

    class NSASCallback : public AddressRequestCallback {
        public:
            typedef pair<bool, asiolink::IOAddress> Result;
            static vector<Result> results;
            virtual void success(const asiolink::IOAddress& address) {
                results.push_back(Result(true, address));
            }
            virtual void unreachable() {
                results.push_back(Result(false,
                    asiolink::IOAddress("0.0.0.0")));
            }
    };

    boost::shared_ptr<AddressRequestCallback> getCallback() {
        return (boost::shared_ptr<AddressRequestCallback>(new NSASCallback));
    }
};

vector<NameserverAddressStoreTest::NSASCallback::Result>
    NameserverAddressStoreTest::NSASCallback::results;


/// \brief Remove Zone Entry from Hash Table
///
/// Check that when an entry reaches the top of the zone LRU list, it is removed from the
/// hash table as well.
TEST_F(NameserverAddressStoreTest, ZoneDeletionCheck) {

    // Create a NSAS with a hash size of three and a LRU size of 9 (both zone and
    // nameserver tables).
    DerivedNsas nsas(resolver_, 2, 2);

    // Add six entries to the tables.  After addition the reference count of each element
    // should be 3 - one for the entry in the zones_ vector, and one each for the entries
    // in the LRU list and hash table.
    for (int i = 1; i <= 6; ++i) {
        EXPECT_EQ(1, zones_[i].use_count());
        nsas.AddZoneEntry(zones_[i]);
        EXPECT_EQ(3, zones_[i].use_count());
    }

    // Adding another entry should cause the first one to drop off the LRU list, which
    // should also trigger the deletion of the entry from the hash table.  This should
    // reduce its use count to 1.
    EXPECT_EQ(1, zones_[7].use_count());
    nsas.AddZoneEntry(zones_[7]);
    EXPECT_EQ(3, zones_[7].use_count());

    EXPECT_EQ(1, zones_[1].use_count());
}


/// \brief Remove Entry from Hash Table
///
/// Check that when an entry reaches the top of the LRU list, it is removed from the
/// hash table as well.
TEST_F(NameserverAddressStoreTest, NameserverDeletionCheck) {

    // Create a NSAS with a hash size of three and a LRU size of 9 (both zone and
    // nameserver tables).
    DerivedNsas nsas(resolver_, 2, 2);

    // Add six entries to the tables.  After addition the reference count of each element
    // should be 3 - one for the entry in the nameservers_ vector, and one each for the entries
    // in the LRU list and hash table.
    for (int i = 1; i <= 6; ++i) {
        EXPECT_EQ(1, nameservers_[i].use_count());
        nsas.AddNameserverEntry(nameservers_[i]);
        EXPECT_EQ(3, nameservers_[i].use_count());
    }

    // Adding another entry should cause the first one to drop off the LRU list, which
    // should also trigger the deletion of the entry from the hash table.  This should
    // reduce its use count to 1.
    EXPECT_EQ(1, nameservers_[7].use_count());
    nsas.AddNameserverEntry(nameservers_[7]);
    EXPECT_EQ(3, nameservers_[7].use_count());

    EXPECT_EQ(1, nameservers_[1].use_count());
}

/**
 * \short Try lookup on empty store.
 *
 * Check if it asks correct questions and it keeps correct internal state.
 */
TEST_F(NameserverAddressStoreTest, emptyLookup) {
    DerivedNsas nsas(resolver_, 10, 10);
    // Ask it a question
    nsas.lookupAndAnswer("example.net.", RRClass::IN(), authority_,
        getCallback());
    // It should ask for IP addresses for ns.example.com.
    resolver_->asksIPs(Name("ns.example.com."), 0, 1);

    // Ask another question for the same zone
    nsas.lookup("example.net.", RRClass::IN(), getCallback());
    // It should ask no more questions now
    EXPECT_EQ(2, resolver_->requests.size());

    // Ask another question with different zone but the same nameserver
    authority_->setName(Name("example.com."));
    nsas.lookupAndAnswer("example.com.", RRClass::IN(), authority_,
        getCallback());
    // It still should ask nothing
    EXPECT_EQ(2, resolver_->requests.size());

    // We provide IP address of one nameserver, it should generate all the
    // results
    resolver_->answer(0, Name("ns.example.com."), RRType::A(),
        rdata::in::A("192.0.2.1"));
    EXPECT_EQ(3, NSASCallback::results.size());
    BOOST_FOREACH(const NSASCallback::Result& result, NSASCallback::results) {
        EXPECT_TRUE(result.first);
        EXPECT_EQ("192.0.2.1", result.second.toText());
    }
}

/**
 * \short Try looking up a zone that does not have any nameservers.
 *
 * It should not ask anything and say it is unreachable right away.
 */
TEST_F(NameserverAddressStoreTest, zoneWithoutNameservers) {
    DerivedNsas nsas(resolver_, 10, 10);
    // Ask it a question
    nsas.lookupAndAnswer("example.net.", RRClass::IN(), empty_authority_,
        getCallback());
    // There should be no questions, because there's nothing to ask
    EXPECT_EQ(0, resolver_->requests.size());
    // And there should be one "unreachable" answer for the query
    ASSERT_EQ(1, NSASCallback::results.size());
    EXPECT_FALSE(NSASCallback::results[0].first);
}

/**
 * \short Try looking up a zone that has only an unreachable nameserver.
 *
 * It should be unreachable. Furthermore, subsequent questions for that zone
 * or other zone with the same nameserver should be unreachable right away,
 * without further asking.
 */
TEST_F(NameserverAddressStoreTest, unreachableNS) {
    DerivedNsas nsas(resolver_, 10, 10);
    // Ask it a question
    nsas.lookupAndAnswer("example.net.", RRClass::IN(), authority_,
        getCallback());
    // It should ask for IP addresses for example.com.
    ASSERT_EQ(2, resolver_->requests.size());
    resolver_->asksIPs(Name("ns.example.com."), 0, 1);

    // Ask another question with different zone but the same nameserver
    authority_->setName(Name("example.com."));
    nsas.lookupAndAnswer("example.com.", RRClass::IN(), authority_,
        getCallback());
    // It should ask nothing more now
    EXPECT_EQ(2, resolver_->requests.size());

    // We say there are no addresses
    resolver_->requests[0].second->failure();
    resolver_->requests[1].second->failure();

    // We should have 2 answers now
    EXPECT_EQ(2, NSASCallback::results.size());
    // When we ask one same and one other zone with the same nameserver,
    // it should generate no questions and answer right away
    nsas.lookup("example.net.", RRClass::IN(), getCallback());
    authority_->setName(Name("example.org."));
    nsas.lookupAndAnswer("example.org.", RRClass::IN(), authority_,
        getCallback());
    // There should be 4 negative answers now
    EXPECT_EQ(4, NSASCallback::results.size());
    BOOST_FOREACH(const NSASCallback::Result& result, NSASCallback::results) {
        EXPECT_FALSE(result.first);
    }
}

/*
 * TODO: More tests. Some eviction combined with lookups would make sense.
 * Stressing the entries that some nameservers for zone are there and some
 * are not, etc.
 */

} // namespace nsas
} // namespace isc
