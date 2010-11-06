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

#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

#include <string.h>
#include <vector>
#include <cassert>

#include "nameserver_address_store.h"
#include "nsas_entry_compare.h"
#include "nameserver_entry.h"
#include "zone_entry.h"
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
    DerivedNsas(ResolverInterface& resolver, uint32_t hashsize,
        uint32_t lrusize) :
        NameserverAddressStore(resolver, hashsize, lrusize)
    {}

    /// \brief Virtual Destructor
    virtual ~DerivedNsas()
    {}

    /// \brief Add Nameserver Entry to Hash and LRU Tables
    void AddNameserverEntry(boost::shared_ptr<NameserverEntry>& entry) {
        HashKey h = entry->hashKey();
        nameserver_hash_.add(entry, h);
        nameserver_lru_.add(entry);
    }

    /// \brief Add Zone Entry to Hash and LRU Tables
    void AddZoneEntry(boost::shared_ptr<ZoneEntry>& entry) {
        HashKey h = entry->hashKey();
        zone_hash_.add(entry, h);
        zone_lru_.add(entry);
    }
};



/// \brief Text Fixture Class
class NameserverAddressStoreTest : public ::testing::Test {
protected:

    NameserverAddressStoreTest() :
        authority_(new RRset(Name("example.net."), RRClass::IN(), RRType::NS(),
            RRTTL(128)))
    {
        // Constructor - initialize a set of nameserver and zone objects.  For convenience,
        // these are stored in vectors.
        for (int i = 1; i <= 9; ++i) {
            std::string name = "nameserver" + boost::lexical_cast<std::string>(i);
            nameservers_.push_back(boost::shared_ptr<NameserverEntry>(new NameserverEntry(name, (40 + i))));
        }

        for (int i = 1; i <= 9; ++i) {
            std::string name = "zone" + boost::lexical_cast<std::string>(i);
            zones_.push_back(boost::shared_ptr<ZoneEntry>(new ZoneEntry(name, (40 + i))));
        }

        // A nameserver serving data
        authority_->addRdata(rdata::generic::NS(Name("ns.example.com.")));

        // This is reused because of convenience, clear it just in case
        NSASCallback::results.clear();
    }

    // Vector of pointers to nameserver and zone entries.
    std::vector<boost::shared_ptr<NameserverEntry> > nameservers_;
    std::vector<boost::shared_ptr<ZoneEntry> >       zones_;

    RRsetPtr authority_;

    class TestResolver : public ResolverInterface {
        public:
            typedef pair<QuestionPtr, CallbackPtr> Request;
            vector<Request> requests;
            virtual void resolve(QuestionPtr q, CallbackPtr c) {
                requests.push_back(Request(q, c));
            }
            QuestionPtr operator[](size_t index) {
                return (requests[index].first);
            }
    } defaultTestResolver;

    /**
     * Looks if the two provided requests in resolver are A and AAAA.
     * Sorts them so index1 is A.
     */
    void asksIPs(const Name& name, size_t index1, size_t index2) {
        size_t max = (index1 < index2) ? index2 : index1;
        ASSERT_GT(defaultTestResolver.requests.size(), max);
        EXPECT_EQ(name, defaultTestResolver[index1]->getName());
        EXPECT_EQ(name, defaultTestResolver[index2]->getName());
        EXPECT_EQ(RRClass::IN(), defaultTestResolver[index1]->getClass());
        EXPECT_EQ(RRClass::IN(), defaultTestResolver[index2]->getClass());
        // If they are the other way around, swap
        if (defaultTestResolver[index1]->getType() == RRType::AAAA() &&
            defaultTestResolver[index2]->getType() == RRType::A())
        {
            TestResolver::Request tmp(defaultTestResolver.requests[index1]);
            defaultTestResolver.requests[index1] =
                defaultTestResolver.requests[index2];
            defaultTestResolver.requests[index2] = tmp;
        }
        // Check the correct addresses
        EXPECT_EQ(RRType::A(), defaultTestResolver[index1]->getType());
        EXPECT_EQ(RRType::AAAA(), defaultTestResolver[index1]->getType());
    }

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
    DerivedNsas nsas(defaultTestResolver, 2, 2);

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
    DerivedNsas nsas(defaultTestResolver, 2, 2);

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
    DerivedNsas nsas(defaultTestResolver, 10, 10);
    // Ask it a question
    nsas.lookup("example.net.", RRClass::IN().getCode(), *authority_,
        vector<AbstractRRset>(), getCallback());
    // It should ask for IP addresses for example.com.
    ASSERT_EQ(2, defaultTestResolver.requests.size());
    asksIPs(Name("example.com."), 0, 1);

    // Ask another question for the same zone
    nsas.lookup("example.net.", RRClass::IN().getCode(), *authority_,
        vector<AbstractRRset>(), getCallback());
    // It should ask no more questions now
    EXPECT_EQ(2, defaultTestResolver.requests.size());

    // Ask another question with different zone but the same nameserver
    authority_->setName(Name("example.com."));
    nsas.lookup("example.com.", RRClass::IN().getCode(), *authority_,
        vector<AbstractRRset>(), getCallback());
    // It still should ask nothing
    EXPECT_EQ(2, defaultTestResolver.requests.size());

    // We provide IP address of one nameserver, it should generate all the
    // results
    RRsetPtr answer(new RRset(Name("example.com."), RRClass::IN(), RRType::A(),
        RRTTL(100)));
    answer->addRdata(rdata::in::A("192.0.2.1"));
    Message address(Message::RENDER); // Not able to create different one
    address.addRRset(Section::ANSWER(), answer);
    address.addRRset(Section::AUTHORITY(), authority_);
    address.addQuestion(defaultTestResolver[0]);
    defaultTestResolver.requests[0].second->success(address);
    EXPECT_EQ(3, NSASCallback::results.size());
    BOOST_FOREACH(const NSASCallback::Result& result, NSASCallback::results) {
        EXPECT_TRUE(result.first);
        EXPECT_EQ("192.0.2.1", result.second.toText());
    }
}

/// \short Test invalid authority section.
TEST_F(NameserverAddressStoreTest, invalidAuthority) {
    DerivedNsas nsas(defaultTestResolver, 2, 2);
    EXPECT_THROW(nsas.lookup("example.net.", RRClass::CH().getCode(),
        *authority_, vector<AbstractRRset>(), getCallback()),
        InconsistentZone);
    EXPECT_EQ(0, defaultTestResolver.requests.size());
    EXPECT_EQ(0, NSASCallback::results.size());
    EXPECT_THROW(nsas.lookup("example.com.", RRClass::IN().getCode(),
        *authority_, vector<AbstractRRset>(), getCallback()),
        InconsistentZone);
    EXPECT_EQ(0, defaultTestResolver.requests.size());
    EXPECT_EQ(0, NSASCallback::results.size());
    BasicRRset aAuthority(Name("example.net."), RRClass::IN(), RRType::A(),
            RRTTL(128));
    EXPECT_THROW(nsas.lookup("example.net.", RRClass::IN().getCode(),
        aAuthority, vector<AbstractRRset>(),
        getCallback()), NotNS);
    EXPECT_EQ(0, defaultTestResolver.requests.size());
    EXPECT_EQ(0, NSASCallback::results.size());
}

} // namespace nsas
} // namespace isc
