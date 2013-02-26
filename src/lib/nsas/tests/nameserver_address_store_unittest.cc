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

/// \brief Nameserver Address Store Tests
///
/// This file contains tests for the nameserver address store as a whole.

#include <config.h>

#include <algorithm>
#include <cassert>
#include <string.h>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>

#include "../address_request_callback.h"
#include "../nameserver_address_store.h"
#include "../nameserver_entry.h"
#include "../nsas_entry_compare.h"
#include "../zone_entry.h"
#include "nsas_test.h"

using namespace isc::dns;
using namespace isc::util;
using namespace std;

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
    DerivedNsas(boost::shared_ptr<TestResolver> resolver, uint32_t hashsize,
        uint32_t lrusize) :
        NameserverAddressStore(resolver, hashsize, lrusize),
        resolver_(resolver)
    {}

    /// \brief Virtual Destructor
    virtual ~DerivedNsas()
    {}

    /// \brief Add Nameserver Entry to hash and LRU tables
    ///
    /// \param entry Nameserver Entry to add.
    void AddNameserverEntry(boost::shared_ptr<NameserverEntry>& entry) {
        HashKey h = entry->hashKey();
        nameserver_hash_->add(entry, h);
        nameserver_lru_->add(entry);
    }

    /// \brief Add Zone Entry to hash and LRU tables
    ///
    /// \param entry Zone Entry to add.
    void AddZoneEntry(boost::shared_ptr<ZoneEntry>& entry) {
        HashKey h = entry->hashKey();
        zone_hash_->add(entry, h);
        zone_lru_->add(entry);
    }

    /// \brief Wrap the common lookup
    ///
    /// Calls the lookup and provides the authority section if it is asked
    /// for by the resolver.
    ///
    /// \param name Name of zone for which an address is required
    /// \param class_code Class of the zone
    /// \param authority Pointer to authority section RRset to which NS
    ///        records will be added.
    /// \param callback Callback object used to pass result back to caller
    void lookupAndAnswer(const string& name, const RRClass& class_code,
                         RRsetPtr authority,
                         boost::shared_ptr<AddressRequestCallback> callback)
    {
        // Note how many requests are in the resolver's queue
        size_t size(resolver_->requests.size());

        // Lookup the name.  This should generate a request for NS records.
        NameserverAddressStore::lookup(name, class_code, callback, ANY_OK);
        if (size < resolver_->requests.size()) {

            // It asked something, the only thing it can ask is the NS list.
            // Once answered, drop the request so no-one else sees it
            resolver_->provideNS(size, authority);
            resolver_->requests.erase(resolver_->requests.begin() + size);

        } else {

            // The test resolver's requests queue has not increased in size,
            // so the lookup did not generate a request.
            ADD_FAILURE() << "Lookup did not generate a request for NS records";
        }
    }

private:
    boost::shared_ptr<TestResolver> resolver_; 
                                ///< Resolver used to answer generated requests
};                                              



/// \brief Text Fixture Class
class NameserverAddressStoreTest : public TestWithRdata {
protected:

    /// \brief Constructor
    NameserverAddressStoreTest() :
        authority_(new RRset(Name("example.net."), RRClass::IN(), RRType::NS(),
            RRTTL(128))),
        empty_authority_(new RRset(Name("example.net."), RRClass::IN(),
            RRType::NS(), RRTTL(128))),
        resolver_(new TestResolver)
    {
        // Initialize a set of nameserver and zone objects.  For convenience,
        // these are stored in vectors.
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
                resolver_.get(), name, RRClass(40 + i),
                boost::shared_ptr<HashTable<NameserverEntry> >(),
                boost::shared_ptr<LruList<NameserverEntry> >())));
        }

        // A nameserver serving data
        authority_->addRdata(ConstRdataPtr(new rdata::generic::NS(Name(
            "ns.example.com."))));

        // This is reused because of convenience, clear it just in case
        NSASCallback::results.clear();
    }

    /// \brief Internal callback object
    ///
    /// Callback object.  It just records whether the success() or
    /// unreachable() methods were called and if success, a copy of the
    /// Nameserver object. (The data is held in a static object that will
    /// outlive the lifetime of the callback object.)
    struct NSASCallback : public AddressRequestCallback {
        typedef pair<bool, NameserverAddress> Result;
        static vector<Result> results;

        virtual void success(const NameserverAddress& address) {
            results.push_back(Result(true, address));
        }
        virtual void unreachable() {
            results.push_back(Result(false, NameserverAddress()));
        }
    };

    /// \brief Return pointer to callback object
    boost::shared_ptr<AddressRequestCallback> getCallback() {
        return (boost::shared_ptr<AddressRequestCallback>(new NSASCallback));
    }

    // Member variables

    // Vector of pointers to nameserver and zone entries.
    std::vector<boost::shared_ptr<NameserverEntry> > nameservers_;
    std::vector<boost::shared_ptr<ZoneEntry> >       zones_;

    // Authority sections used in the tests
    RRsetPtr authority_;
    RRsetPtr empty_authority_;

    // ... and the resolver
    boost::shared_ptr<TestResolver> resolver_;
};

/// Definition of the static results object
vector<NameserverAddressStoreTest::NSASCallback::Result>
    NameserverAddressStoreTest::NSASCallback::results;


/// \brief Remove Zone Entry from Hash Table
///
/// Check that when an entry reaches the top of the zone LRU list, it is removed
/// from the hash table as well.
TEST_F(NameserverAddressStoreTest, ZoneDeletionCheck) {

    // Create a NSAS with a hash size of three and a LRU size of 9 (both zone
    // and nameserver tables).
    DerivedNsas nsas(resolver_, 2, 2);

    // Add six entries to the tables.  After addition the reference count of
    // each element should be 3 - one for the entry in the zones_ vector, and
    // one each for the entries in the LRU list and hash table.
    for (int i = 1; i <= 6; ++i) {
        EXPECT_EQ(1, zones_[i].use_count());
        nsas.AddZoneEntry(zones_[i]);
        EXPECT_EQ(3, zones_[i].use_count());
    }

    // Adding another entry should cause the first one to drop off the LRU list,
    // which should also trigger the deletion of the entry from the hash table.
    //  This should reduce its use count to 1.
    EXPECT_EQ(1, zones_[7].use_count());
    nsas.AddZoneEntry(zones_[7]);
    EXPECT_EQ(3, zones_[7].use_count());

    EXPECT_EQ(1, zones_[1].use_count());
}


/// \brief Remove Entry from Hash Table
///
/// Check that when an entry reaches the top of the LRU list, it is removed from
/// the hash table as well.
TEST_F(NameserverAddressStoreTest, NameserverDeletionCheck) {

    // Create a NSAS with a hash size of three and a LRU size of 9 (both zone
    // and nameserver tables).
    DerivedNsas nsas(resolver_, 2, 2);

    // Add six entries to the tables.  After addition the reference count of
    // each element should be 3 - one for the entry in the nameservers_ vector,
    // and one each for the entries in the LRU list and hash table.
    for (int i = 1; i <= 6; ++i) {
        EXPECT_EQ(1, nameservers_[i].use_count());
        nsas.AddNameserverEntry(nameservers_[i]);
        EXPECT_EQ(3, nameservers_[i].use_count());
    }

    // Adding another entry should cause the first one to drop off the LRU list,
    // which should also trigger the deletion of the entry from the hash table.
    // This should reduce its use count to 1.
    EXPECT_EQ(1, nameservers_[7].use_count());
    nsas.AddNameserverEntry(nameservers_[7]);
    EXPECT_EQ(3, nameservers_[7].use_count());

    EXPECT_EQ(1, nameservers_[1].use_count());
}

/// \brief Try lookup on empty store.
///
/// Check if it asks correct questions and it keeps correct internal state.
TEST_F(NameserverAddressStoreTest, emptyLookup) {
    DerivedNsas nsas(resolver_, 10, 10);

    // Ask it a question
    nsas.lookupAndAnswer("example.net.", RRClass::IN(), authority_,
        getCallback());

    // It should ask for IP addresses for ns.example.com.
    EXPECT_NO_THROW(resolver_->asksIPs(Name("ns.example.com."), 0, 1));

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
    EXPECT_NO_THROW(resolver_->answer(0, Name("ns.example.com."), RRType::A(),
        rdata::in::A("192.0.2.1")));
    EXPECT_EQ(3, NSASCallback::results.size());
    BOOST_FOREACH(const NSASCallback::Result& result, NSASCallback::results) {
        EXPECT_TRUE(result.first);
        EXPECT_EQ("192.0.2.1", result.second.getAddress().toText());
    }
}

/// \brief Try looking up a zone that does not have any nameservers.
///
/// It should not ask anything and say it is unreachable right away.
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

/// \brief Try looking up a zone that has only an unreachable nameserver.
///
/// It should be unreachable. Furthermore, subsequent questions for that zone
/// or other zone with the same nameserver should be unreachable right away,
/// without further asking.
TEST_F(NameserverAddressStoreTest, unreachableNS) {
    DerivedNsas nsas(resolver_, 10, 10);

    // Ask it a question
    nsas.lookupAndAnswer("example.net.", RRClass::IN(), authority_,
        getCallback());

    // It should ask for IP addresses for example.com.
    EXPECT_NO_THROW(resolver_->asksIPs(Name("ns.example.com."), 0, 1));

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

/// \short Try to stress it little bit by having multiple zones and nameservers.
///
/// Does some asking, on a set of zones that share some nameservers, with
/// slower answering, evicting data, etc.
TEST_F(NameserverAddressStoreTest, CombinedTest) {

    // Create small caches, so we get some evictions
    DerivedNsas nsas(resolver_, 1, 1);

    // Ask for example.net. It has single nameserver out of the zone
    nsas.lookupAndAnswer("example.net.", RRClass::IN(), authority_,
        getCallback());

    // It should ask for the nameserver IP addresses
    EXPECT_NO_THROW(resolver_->asksIPs(Name("ns.example.com."), 0, 1));
    EXPECT_EQ(0, NSASCallback::results.size());

    // But we do not answer it right away. We create a new zone and
    // let this nameserver entry get out.
    rrns_->addRdata(rdata::generic::NS("example.cz."));
    nsas.lookupAndAnswer(EXAMPLE_CO_UK, RRClass::IN(), rrns_, getCallback());

    // It really should ask something, one of the nameservers
    // (or both)
    ASSERT_GT(resolver_->requests.size(), 2);
    Name name(resolver_->requests[2].first->getName());
    EXPECT_TRUE(name == Name("example.fr") || name == Name("example.de") ||
        name == Name("example.cz"));
    EXPECT_NO_THROW(resolver_->asksIPs(name, 2, 3));
    EXPECT_EQ(0, NSASCallback::results.size());

    // This should still be in the hash table, so try it asks no more questions
    size_t request_count(resolver_->requests.size());
    nsas.lookup("example.net.", RRClass::IN(), getCallback());
    EXPECT_EQ(request_count, resolver_->requests.size());
    EXPECT_EQ(0, NSASCallback::results.size());

    // We respond to one of the 3 nameservers
    EXPECT_NO_THROW(resolver_->answer(2, name, RRType::A(),
        rdata::in::A("192.0.2.1")));

    // That should trigger one answer
    EXPECT_EQ(1, NSASCallback::results.size());
    EXPECT_TRUE(NSASCallback::results[0].first);
    EXPECT_EQ("192.0.2.1",
        NSASCallback::results[0].second.getAddress().toText());
    EXPECT_NO_THROW(resolver_->answer(3, name, RRType::AAAA(),
        rdata::in::AAAA("2001:bd8::1")));

    // And there should be yet another query
    ASSERT_GT(resolver_->requests.size(), 4);
    EXPECT_NE(name, resolver_->requests[4].first->getName());
    Name another_name = resolver_->requests[4].first->getName();
    EXPECT_TRUE(another_name == Name("example.fr") ||
        another_name == Name("example.de") ||
        another_name == Name("example.cz"));
    request_count = resolver_->requests.size();

    // But when ask for a different zone with the first nameserver, it should
    // ask again, as it is evicted already
    authority_->setName(Name("example.com."));
    nsas.lookupAndAnswer("example.com.", RRClass::IN(), authority_,
        getCallback());
    EXPECT_EQ(request_count + 2, resolver_->requests.size());
    EXPECT_NO_THROW(resolver_->asksIPs(Name("ns.example.com."), request_count,
        request_count + 1));

    // Now, we answer both queries for the same address and three (one for the
    // original, one for this one) more answers should arrive
    NSASCallback::results.clear();
    EXPECT_NO_THROW(resolver_->answer(0, Name("ns.example.com."), RRType::A(),
        rdata::in::A("192.0.2.2")));
    EXPECT_NO_THROW(resolver_->answer(request_count, Name("ns.example.com."),
        RRType::A(), rdata::in::A("192.0.2.2")));
    EXPECT_EQ(3, NSASCallback::results.size());
    BOOST_FOREACH(const NSASCallback::Result& result, NSASCallback::results) {
        EXPECT_TRUE(result.first);
        EXPECT_EQ("192.0.2.2", result.second.getAddress().toText());
    }
}

// Check that we can update the RTT associated with nameservers successfully.
// Also checks that we can't set the RTT to zero (which would cause problems
// with selection algorithm).
TEST_F(NameserverAddressStoreTest, updateRTT) {

    // Initialization.
    string  zone_name = "example.net.";
    string  ns_name = "ns.example.com."; 
    vector<string> address;
    address.push_back("192.0.2.1");
    address.push_back("192.0.2.2");

    uint32_t HIGH_RTT = 10000;  // 1E4; When squared, the result fits in 32 bits

    DerivedNsas nsas(resolver_, 103, 107);   // Arbitrary cache sizes

    // Ensure that location holding the addresses returned is empty.  We'll
    // be using this throughout the tests.  As the full name is a bit of a
    // mouthful, set up an alias.
    vector<NameserverAddressStoreTest::NSASCallback::Result>& results =
        NameserverAddressStoreTest::NSASCallback::results;
    results.clear();

    // Initialize the test resolver with the answer for the A record query
    // for ns.example.com (the nameserver set for example.net in the class
    // initialization).  We'll set two addresses.
    Name ns_example_com(ns_name);
    isc::dns::RRsetPtr ns_address = boost::shared_ptr<RRset>(new RRset(
        ns_example_com, RRClass::IN(), RRType::A(), RRTTL(300)));
    BOOST_FOREACH(string addr, address) {
        ns_address->addRdata(rdata::in::A(addr));
    }

    // All set.  Ask for example.net.
    boost::shared_ptr<AddressRequestCallback> callback = getCallback();
    nsas.lookupAndAnswer(zone_name, RRClass::IN(), authority_, getCallback());

    // This should generate two requests - one for A and one for AAAA.
    EXPECT_EQ(2, resolver_->requests.size());

    // Provide an answer that has two A records.  This should generate one
    // result.
    EXPECT_NO_THROW(resolver_->answer(0, ns_address));
    EXPECT_EQ(1, results.size());

    // We expect the lookup to be successful.  Check that the address is one of
    // the two we've set and that the RTT associated with this nameserver is
    // non-zero.
    EXPECT_EQ(true, results[0].first);
    vector<string>::iterator addr1 = find(address.begin(), address.end(),
                                     results[0].second.getAddress().toText());
    EXPECT_TRUE(addr1 != address.end());

    // The RTT we got should be non-zero and less than the high value we are
    // using for the test.
    uint32_t rtt1 = results[0].second.getAddressEntry().getRTT();
    EXPECT_NE(0, rtt1);
    EXPECT_LT(rtt1, HIGH_RTT);

    // Update the address with a very high RTT.  Owning to the way the NSAS is
    // written, we can update the RTT but cannot read the new value back from
    // the new object.  
    results[0].second.updateRTT(HIGH_RTT);

    // Get another nameserver.  As the probability of returning a particular
    // address is proporational to 1/t^2, we should get the second address
    // since the first now has a larger RTT.  However, this is not guaranteed
    // - this is a probability (albeit small) of getting the first again. We'll
    // allow three chances of getting the "wrong" address before we declare
    // an error.
    int attempt = 0;
    vector<string>::iterator addr2 = addr1;
    for (attempt = 0; (attempt < 3) && (*addr1 == *addr2); ++attempt) {
        results.clear();
        nsas.lookup(zone_name, RRClass::IN(), 
                             getCallback(), ANY_OK);
        addr2 = find(address.begin(), address.end(),
                     results[0].second.getAddress().toText());
    }
    EXPECT_LT(attempt, 3);

    // Ensure that the RTT is non-zero.
    // obtained earlier.
    uint32_t rtt2 = results[0].second.getAddressEntry().getRTT();
    EXPECT_NE(0, rtt2);

    // The test has shown that the code can return the two nameservers.  Now
    // try to set the RTT for the last one returned to zero.  As there is a
    // smoothing effect in the calculations which damps out an abrupt change
    // in the RTT, the underlying RTT will not be set to zero immediately.  So
    // loop a large number of times, each time setting it to zero.
    //
    // Between each setting of the RTT, we have to retrieve the nameserver from
    // the NSAS again.  This means that we _could_ occasionally get the address
    // of the one whose RTT we have raised to HIGH_RTT.  We overcome this by
    // looping a _very_ large number of times.  Ultimately the RTT of both
    // addresses should decay to a small value.
    for (int i = 0; i < 2000; ++i) {   // 1000 times for each nameserver
        results.clear();
        nsas.lookup(zone_name, RRClass::IN(), getCallback(), ANY_OK);
        EXPECT_EQ(1, results.size());
        uint32_t rtt3 = results[0].second.getAddressEntry().getRTT();
        EXPECT_NE(0, rtt3);
        results[0].second.updateRTT(0);
    }
}


} // namespace nsas
} // namespace isc
