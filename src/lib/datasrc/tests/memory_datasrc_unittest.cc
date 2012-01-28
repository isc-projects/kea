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

#include <sstream>
#include <vector>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <exceptions/exceptions.h>

#include <dns/masterload.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrsetlist.h>
#include <dns/rrttl.h>
#include <dns/masterload.h>

#include <datasrc/memory_datasrc.h>
#include <datasrc/data_source.h>
#include <datasrc/iterator.h>

#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc;
using namespace isc::testutils;

namespace {
// Commonly used result codes (Who should write the prefix all the time)
using result::SUCCESS;
using result::EXIST;

class InMemoryClientTest : public ::testing::Test {
protected:
    InMemoryClientTest() : rrclass(RRClass::IN())
    {}
    RRClass rrclass;
    InMemoryClient memory_client;
};

TEST_F(InMemoryClientTest, add_find_Zone) {
    // test add zone
    // Bogus zone (NULL)
    EXPECT_THROW(memory_client.addZone(ZoneFinderPtr()),
                 isc::InvalidParameter);

    // add zones with different names one by one
    EXPECT_EQ(result::SUCCESS, memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(RRClass::IN(),
                                                       Name("a")))));
    EXPECT_EQ(result::SUCCESS, memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(RRClass::CH(),
                                                       Name("b")))));
    EXPECT_EQ(result::SUCCESS, memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(RRClass::IN(),
                                                       Name("c")))));
    // add zones with the same name suffix
    EXPECT_EQ(result::SUCCESS, memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(RRClass::CH(),
                                                       Name("x.d.e.f")))));
    EXPECT_EQ(result::SUCCESS, memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(RRClass::CH(),
                                                       Name("o.w.y.d.e.f")))));
    EXPECT_EQ(result::SUCCESS, memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(RRClass::CH(),
                                                       Name("p.w.y.d.e.f")))));
    EXPECT_EQ(result::SUCCESS, memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(RRClass::IN(),
                                                       Name("q.w.y.d.e.f")))));
    // add super zone and its subzone
    EXPECT_EQ(result::SUCCESS, memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(RRClass::CH(),
                                                       Name("g.h")))));
    EXPECT_EQ(result::SUCCESS, memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(RRClass::IN(),
                                               Name("i.g.h")))));
    EXPECT_EQ(result::SUCCESS, memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(RRClass::IN(),
                                                       Name("z.d.e.f")))));
    EXPECT_EQ(result::SUCCESS, memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(RRClass::IN(),
                                                       Name("j.z.d.e.f")))));

    // different zone class isn't allowed.
    EXPECT_EQ(result::EXIST, memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(RRClass::CH(),
                                                       Name("q.w.y.d.e.f")))));

    // names are compared in a case insensitive manner.
    EXPECT_EQ(result::EXIST, memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(RRClass::IN(),
                                                       Name("Q.W.Y.d.E.f")))));

    // test find zone
    EXPECT_EQ(result::SUCCESS, memory_client.findZone(Name("a")).code);
    EXPECT_EQ(Name("a"),
              memory_client.findZone(Name("a")).zone_finder->getOrigin());

    EXPECT_EQ(result::SUCCESS,
              memory_client.findZone(Name("j.z.d.e.f")).code);
    EXPECT_EQ(Name("j.z.d.e.f"),
              memory_client.findZone(Name("j.z.d.e.f")).zone_finder->
                  getOrigin());

    // NOTFOUND
    EXPECT_EQ(result::NOTFOUND, memory_client.findZone(Name("d.e.f")).code);
    EXPECT_EQ(ConstZoneFinderPtr(),
              memory_client.findZone(Name("d.e.f")).zone_finder);

    EXPECT_EQ(result::NOTFOUND,
              memory_client.findZone(Name("w.y.d.e.f")).code);
    EXPECT_EQ(ConstZoneFinderPtr(),
              memory_client.findZone(Name("w.y.d.e.f")).zone_finder);

    // there's no exact match.  the result should be the longest match,
    // and the code should be PARTIALMATCH.
    EXPECT_EQ(result::PARTIALMATCH,
              memory_client.findZone(Name("j.g.h")).code);
    EXPECT_EQ(Name("g.h"),
              memory_client.findZone(Name("g.h")).zone_finder->getOrigin());

    EXPECT_EQ(result::PARTIALMATCH,
              memory_client.findZone(Name("z.i.g.h")).code);
    EXPECT_EQ(Name("i.g.h"),
              memory_client.findZone(Name("z.i.g.h")).zone_finder->
                  getOrigin());
}

TEST_F(InMemoryClientTest, iterator) {
    // Just some preparations of data
    boost::shared_ptr<InMemoryZoneFinder>
        zone(new InMemoryZoneFinder(RRClass::IN(), Name("a")));
    RRsetPtr aRRsetA(new RRset(Name("a"), RRClass::IN(), RRType::A(),
                                  RRTTL(300)));
    aRRsetA->addRdata(rdata::in::A("192.0.2.1"));
    RRsetPtr aRRsetAAAA(new RRset(Name("a"), RRClass::IN(), RRType::AAAA(),
                                  RRTTL(300)));
    aRRsetAAAA->addRdata(rdata::in::AAAA("2001:db8::1"));
    aRRsetAAAA->addRdata(rdata::in::AAAA("2001:db8::2"));
    RRsetPtr subRRsetA(new RRset(Name("sub.x.a"), RRClass::IN(), RRType::A(),
                                  RRTTL(300)));
    subRRsetA->addRdata(rdata::in::A("192.0.2.2"));
    EXPECT_EQ(result::SUCCESS, memory_client.addZone(zone));
    // First, the zone is not there, so it should throw
    EXPECT_THROW(memory_client.getIterator(Name("b")), DataSourceError);
    // This zone is not there either, even when there's a zone containing this
    EXPECT_THROW(memory_client.getIterator(Name("x.a")), DataSourceError);
    // Now, an empty zone
    ZoneIteratorPtr iterator(memory_client.getIterator(Name("a")));
    EXPECT_EQ(ConstRRsetPtr(), iterator->getNextRRset());
    // It throws Unexpected when we are past the end
    EXPECT_THROW(iterator->getNextRRset(), isc::Unexpected);
    EXPECT_EQ(result::SUCCESS, zone->add(aRRsetA));
    EXPECT_EQ(result::SUCCESS, zone->add(aRRsetAAAA));
    EXPECT_EQ(result::SUCCESS, zone->add(subRRsetA));
    // Check it with full zone, one by one.
    // It should be in ascending order in case of InMemory data source
    // (isn't guaranteed in general)
    iterator = memory_client.getIterator(Name("a"));
    EXPECT_EQ(aRRsetA, iterator->getNextRRset());
    EXPECT_EQ(aRRsetAAAA, iterator->getNextRRset());
    EXPECT_EQ(subRRsetA, iterator->getNextRRset());
    EXPECT_EQ(ConstRRsetPtr(), iterator->getNextRRset());
}

TEST_F(InMemoryClientTest, iterator_separate_rrs) {
    // Exactly the same tests as for iterator, but now with separate_rrs = true
    // For the one that returns actual data, the AAAA should now be split up
    boost::shared_ptr<InMemoryZoneFinder>
        zone(new InMemoryZoneFinder(RRClass::IN(), Name("a")));
    RRsetPtr aRRsetA(new RRset(Name("a"), RRClass::IN(), RRType::A(),
                                  RRTTL(300)));
    aRRsetA->addRdata(rdata::in::A("192.0.2.1"));
    RRsetPtr aRRsetAAAA(new RRset(Name("a"), RRClass::IN(), RRType::AAAA(),
                                  RRTTL(300)));
    aRRsetAAAA->addRdata(rdata::in::AAAA("2001:db8::1"));
    aRRsetAAAA->addRdata(rdata::in::AAAA("2001:db8::2"));
    RRsetPtr aRRsetAAAA_r1(new RRset(Name("a"), RRClass::IN(), RRType::AAAA(),
                                  RRTTL(300)));
    aRRsetAAAA_r1->addRdata(rdata::in::AAAA("2001:db8::1"));
    RRsetPtr aRRsetAAAA_r2(new RRset(Name("a"), RRClass::IN(), RRType::AAAA(),
                                  RRTTL(300)));
    aRRsetAAAA_r2->addRdata(rdata::in::AAAA("2001:db8::2"));

    RRsetPtr subRRsetA(new RRset(Name("sub.x.a"), RRClass::IN(), RRType::A(),
                                  RRTTL(300)));
    subRRsetA->addRdata(rdata::in::A("192.0.2.2"));
    EXPECT_EQ(result::SUCCESS, memory_client.addZone(zone));

    // First, the zone is not there, so it should throw
    EXPECT_THROW(memory_client.getIterator(Name("b"), true), DataSourceError);
    // This zone is not there either, even when there's a zone containing this
    EXPECT_THROW(memory_client.getIterator(Name("x.a")), DataSourceError);
    // Now, an empty zone
    ZoneIteratorPtr iterator(memory_client.getIterator(Name("a"), true));
    EXPECT_EQ(ConstRRsetPtr(), iterator->getNextRRset());
    // It throws Unexpected when we are past the end
    EXPECT_THROW(iterator->getNextRRset(), isc::Unexpected);

    ASSERT_EQ(result::SUCCESS, zone->add(aRRsetA));
    ASSERT_EQ(result::SUCCESS, zone->add(aRRsetAAAA));
    ASSERT_EQ(result::SUCCESS, zone->add(subRRsetA));
    // Check it with full zone, one by one.
    // It should be in ascending order in case of InMemory data source
    // (isn't guaranteed in general)
    iterator = memory_client.getIterator(Name("a"), true);
    EXPECT_EQ(aRRsetA->toText(), iterator->getNextRRset()->toText());
    EXPECT_EQ(aRRsetAAAA_r1->toText(), iterator->getNextRRset()->toText());
    EXPECT_EQ(aRRsetAAAA_r2->toText(), iterator->getNextRRset()->toText());
    EXPECT_EQ(subRRsetA->toText(), iterator->getNextRRset()->toText());
    EXPECT_EQ(ConstRRsetPtr(), iterator->getNextRRset());
}

TEST_F(InMemoryClientTest, getZoneCount) {
    EXPECT_EQ(0, memory_client.getZoneCount());
    memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(rrclass,
                                                       Name("example.com"))));
    EXPECT_EQ(1, memory_client.getZoneCount());

    // duplicate add.  counter shouldn't change
    memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(rrclass,
                                                       Name("example.com"))));
    EXPECT_EQ(1, memory_client.getZoneCount());

    // add one more
    memory_client.addZone(
                  ZoneFinderPtr(new InMemoryZoneFinder(rrclass,
                                                       Name("example.org"))));
    EXPECT_EQ(2, memory_client.getZoneCount());
}

TEST_F(InMemoryClientTest, startUpdateZone) {
    EXPECT_THROW(memory_client.getUpdater(Name("example.org"), false),
                 isc::NotImplemented);
}

// Commonly used RRSIG data
const char* const rrsig_a_txt =
    "example.org. 300 IN RRSIG A 5 3 3600 20000101000000 20000201000000 12345 "
    "example.org. FAKEFAKEFAKE\n";
const char* const rrsig_ns_txt =
    "example.org. 300 IN RRSIG NS 5 3 3600 20000101000000 20000201000000 "
    "54321 example.org. FAKEFAKEFAKEFAKE\n";
// This RRset has two RRSIGs
const char* const rrsig_aaaa_txt =
    "ns.example.org. 300 IN RRSIG AAAA 5 3 3600 20000101000000 20000201000000 "
    "12345 example.org. FAKEFAKEFAKE\n"
    "ns.example.org. 300 IN RRSIG AAAA 5 3 3600 20000101000000 20000201000000 "
    "54321 example.org. FAKEFAKEFAKEFAKE\n";

// A helper callback of masterLoad() used in InMemoryZoneFinderTest.
void
setRRset(RRsetPtr rrset, vector<RRsetPtr*>::iterator& it) {
    *(*it) = rrset;
    ++it;
}

/// \brief Test fixture for the InMemoryZoneFinder class
class InMemoryZoneFinderTest : public ::testing::Test {
    // A straightforward pair of textual RR(set) and a RRsetPtr variable
    // to store the RRset.  Used to build test data below.
    struct RRsetData {
        const char* const text; // textual representation of an RRset
        RRsetPtr* rrset;
    };
public:
    InMemoryZoneFinderTest() :
        class_(RRClass::IN()),
        origin_("example.org"),
        zone_finder_(class_, origin_)
    {
        // Build test RRsets.  Below, we construct an RRset for
        // each textual RR(s) of zone_data, and assign it to the corresponding
        // rr_xxx.
        const RRsetData zone_data[] = {
            {"example.org. 300 IN NS ns.example.org.", &rr_ns_},
            {"example.org. 300 IN A 192.0.2.1", &rr_a_},
            {"ns.example.org. 300 IN A 192.0.2.2", &rr_ns_a_},
            {"ns.example.org. 300 IN AAAA 2001:db8::2", &rr_ns_aaaa_},
            {"cname.example.org. 300 IN CNAME canonical.example.org",
             &rr_cname_},
            {"cname.example.org. 300 IN A 192.0.2.3", &rr_cname_a_},
            {"dname.example.org. 300 IN DNAME target.example.org.",
             &rr_dname_},
            {"dname.example.org. 300 IN A 192.0.2.39", &rr_dname_a_},
            {"dname.example.org. 300 IN NS ns.dname.example.org.",
             &rr_dname_ns_},
            {"example.org. 300 IN DNAME example.com.", &rr_dname_apex_},
            {"child.example.org. 300 IN NS ns.child.example.org.",
             &rr_child_ns_},
            {"child.example.org. 300 IN DS 12345 5 1 DEADBEEF",
             &rr_child_ds_},
            {"ns.child.example.org. 300 IN A 192.0.2.153",
             &rr_child_glue_},
            {"grand.child.example.org. 300 IN NS ns.grand.child.example.org.",
             &rr_grandchild_ns_},
            {"ns.grand.child.example.org. 300 IN AAAA 2001:db8::253",
             &rr_grandchild_glue_},
            {"dname.child.example.org. 300 IN DNAME example.com.",
             &rr_child_dname_},
            {"example.com. 300 IN A 192.0.2.10", &rr_out_},
            {"*.wild.example.org. 300 IN A 192.0.2.1", &rr_wild_},
            {"foo.wild.example.org. 300 IN A 192.0.2.3", &rr_under_wild_},
            {"wild.*.foo.example.org. 300 IN A 192.0.2.1", &rr_emptywild_},
            {"wild.*.foo.*.bar.example.org. 300 IN A 192.0.2.1",
             &rr_nested_emptywild_},
            {"*.nswild.example.org. 300 IN NS nswild.example.", &rr_nswild_},
            {"*.dnamewild.example.org. 300 IN DNAME dnamewild.example.",
             &rr_dnamewild_},
            {"*.child.example.org. 300 IN A 192.0.2.1", &rr_child_wild_},
            {"bar.foo.wild.example.org. 300 IN A 192.0.2.2", &rr_not_wild_},
            {"baz.foo.wild.example.org. 300 IN A 192.0.2.3",
             &rr_not_wild_another_},
            {NULL, NULL}
        };

        stringstream zone_data_stream;
        vector<RRsetPtr*> rrsets;
        for (unsigned int i = 0; zone_data[i].text != NULL; ++i) {
            zone_data_stream << zone_data[i].text << "\n";
            rrsets.push_back(zone_data[i].rrset);
        }

        masterLoad(zone_data_stream, Name::ROOT_NAME(), class_,
                   boost::bind(setRRset, _1, rrsets.begin()));
    }
    // Some data to test with
    const RRClass class_;
    const Name origin_;
    // The zone finder to torture by tests
    InMemoryZoneFinder zone_finder_;

    // Placeholder for storing RRsets to be checked with rrsetsCheck()
    vector<ConstRRsetPtr> actual_rrsets_;

    /*
     * Some RRsets to put inside the zone.
     */
    RRsetPtr
        // Out of zone RRset
        rr_out_,
        // NS of example.org
        rr_ns_,
        // A of ns.example.org
        rr_ns_a_,
        // AAAA of ns.example.org
        rr_ns_aaaa_,
        // A of example.org
        rr_a_;
    RRsetPtr rr_cname_;         // CNAME in example.org (RDATA will be added)
    RRsetPtr rr_cname_a_; // for mixed CNAME + A case
    RRsetPtr rr_dname_;         // DNAME in example.org (RDATA will be added)
    RRsetPtr rr_dname_a_; // for mixed DNAME + A case
    RRsetPtr rr_dname_ns_; // for mixed DNAME + NS case
    RRsetPtr rr_dname_apex_; // for mixed DNAME + NS case in the apex
    RRsetPtr rr_child_ns_; // NS of a child domain (for delegation)
    RRsetPtr rr_child_ds_; // DS of a child domain (for delegation, auth data)
    RRsetPtr rr_child_glue_; // glue RR of the child domain
    RRsetPtr rr_grandchild_ns_; // NS below a zone cut (unusual)
    RRsetPtr rr_grandchild_glue_; // glue RR below a deeper zone cut
    RRsetPtr rr_child_dname_; // A DNAME under NS
    RRsetPtr rr_wild_;
    RRsetPtr rr_emptywild_;
    RRsetPtr rr_nested_emptywild_;
    RRsetPtr rr_nswild_, rr_dnamewild_;
    RRsetPtr rr_child_wild_;
    RRsetPtr rr_under_wild_;
    RRsetPtr rr_not_wild_;
    RRsetPtr rr_not_wild_another_;

    /**
     * \brief Test one find query to the zone finder.
     *
     * Asks a query to the zone finder and checks it does not throw and returns
     * expected results. It returns nothing, it just signals failures
     * to GTEST.
     *
     * \param name The name to ask for.
     * \param rrtype The RRType to ask of.
     * \param result The expected code of the result.
     * \param check_answer Should a check against equality of the answer be
     *     done?
     * \param answer The expected rrset, if any should be returned.
     * \param zone_finder Check different InMemoryZoneFinder object than
     *     zone_finder_ (if NULL, uses zone_finder_)
     * \param check_wild_answer Checks that the answer has the same RRs, type
     *     class and TTL as the eqxpected answer and that the name corresponds
     *     to the one searched. It is meant for checking answers for wildcard
     *     queries.
     */
    void findTest(const Name& name, const RRType& rrtype,
                  ZoneFinder::Result result,
                  bool check_answer = true,
                  const ConstRRsetPtr& answer = ConstRRsetPtr(),
                  InMemoryZoneFinder* zone_finder = NULL,
                  ZoneFinder::FindOptions options = ZoneFinder::FIND_DEFAULT,
                  bool check_wild_answer = false)
    {
        if (zone_finder == NULL) {
            zone_finder = &zone_finder_;
        }
        // The whole block is inside, because we need to check the result and
        // we can't assign to FindResult
        EXPECT_NO_THROW({
                ZoneFinder::FindResult find_result(zone_finder->find(
                                                       name, rrtype,
                                                       options));
                // Check it returns correct answers
                EXPECT_EQ(result, find_result.code);
                if (check_answer) {
                    EXPECT_EQ(answer, find_result.rrset);
                } else if (check_wild_answer) {
                    ASSERT_NE(ConstRRsetPtr(), answer) <<
                        "Wrong test, don't check for wild names if you expect "
                        "empty answer";
                    ASSERT_NE(ConstRRsetPtr(), find_result.rrset) <<
                        "No answer found";
                    RdataIteratorPtr expectedIt(answer->getRdataIterator());
                    RdataIteratorPtr actualIt(
                        find_result.rrset->getRdataIterator());
                    while (!expectedIt->isLast() && !actualIt->isLast()) {
                        EXPECT_EQ(0, expectedIt->getCurrent().compare(
                            actualIt->getCurrent())) << "The RRs differ ('" <<
                            expectedIt->getCurrent().toText() << "', '" <<
                            actualIt->getCurrent().toText() << "')";
                        expectedIt->next();
                        actualIt->next();
                    }
                    EXPECT_TRUE(expectedIt->isLast()) <<
                        "Result has less RRs than expected";
                    EXPECT_TRUE(actualIt->isLast()) <<
                        "Result has more RRs than expected";
                    EXPECT_EQ(answer->getClass(),
                        find_result.rrset->getClass());
                    EXPECT_EQ(answer->getType(),
                        find_result.rrset->getType());
                    EXPECT_EQ(answer->getTTL(),
                        find_result.rrset->getTTL());
                    EXPECT_EQ(name, find_result.rrset->getName());
                }
            });
    }
    /**
     * \brief Calls the findAll on the finder and checks the result.
     */
    std::vector<ConstRRsetPtr> findAllTest(const Name& name,
                                           ZoneFinder::Result result,
                                           size_t expected_size,
                                           InMemoryZoneFinder* finder = NULL,
                                           const ConstRRsetPtr &rrset_result =
                                           ConstRRsetPtr(),
                                           ZoneFinder::FindOptions options =
                                           ZoneFinder::FIND_DEFAULT)
    {
        if (finder == NULL) {
            finder = &zone_finder_;
        }
        std::vector<ConstRRsetPtr> target;
        ZoneFinder::FindResult findResult(finder->findAll(name, target,
                                                          options));
        EXPECT_EQ(result, findResult.code);
        EXPECT_EQ(rrset_result, findResult.rrset);
        BOOST_FOREACH(const ConstRRsetPtr& rrset, target) {
            EXPECT_EQ(name, rrset->getName());
        }
        EXPECT_EQ(expected_size, target.size());
        return (target);
    }
    // Internal part of the cancelWildcard test that is multiple times
    void doCancelWildcardTest();

    ConstRRsetPtr textToRRset(const string& text_rrset,
                              const RRClass& rrclass = RRClass::IN()) const
    {
        stringstream ss(text_rrset);
        RRsetPtr rrset;
        vector<RRsetPtr*> rrsets;
        rrsets.push_back(&rrset);
        masterLoad(ss, Name::ROOT_NAME(), rrclass,
                   boost::bind(setRRset, _1, rrsets.begin()));
        return (rrset);
    }
};

/**
 * \brief Check that findPreviousName throws as it should now.
 */
TEST_F(InMemoryZoneFinderTest, findPreviousName) {
    EXPECT_THROW(zone_finder_.findPreviousName(Name("www.example.org")),
                 isc::NotImplemented);
}

/**
 * \brief Test InMemoryZoneFinder::InMemoryZoneFinder constructor.
 *
 * Takes the created zone finder and checks its properties they are the same
 * as passed parameters.
 */
TEST_F(InMemoryZoneFinderTest, constructor) {
    ASSERT_EQ(class_, zone_finder_.getClass());
    ASSERT_EQ(origin_, zone_finder_.getOrigin());
}
/**
 * \brief Test adding.
 *
 * We test that it throws at the correct moments and the correct exceptions.
 * And we test the return value.
 */
TEST_F(InMemoryZoneFinderTest, add) {
    // This one does not belong to this zone
    EXPECT_THROW(zone_finder_.add(rr_out_), InMemoryZoneFinder::OutOfZone);
    // Test null pointer
    EXPECT_THROW(zone_finder_.add(ConstRRsetPtr()),
                 InMemoryZoneFinder::NullRRset);

    // Now put all the data we have there. It should throw nothing
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_a_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_aaaa_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_a_)));

    // Try putting there something twice, it should be rejected
    EXPECT_NO_THROW(EXPECT_EQ(EXIST, zone_finder_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(EXIST, zone_finder_.add(rr_ns_a_)));
}

TEST_F(InMemoryZoneFinderTest, addMultipleCNAMEs) {
    rr_cname_->addRdata(generic::CNAME("canonical2.example.org."));
    EXPECT_THROW(zone_finder_.add(rr_cname_), InMemoryZoneFinder::AddError);
}

TEST_F(InMemoryZoneFinderTest, addCNAMEThenOther) {
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_cname_));
    EXPECT_THROW(zone_finder_.add(rr_cname_a_), InMemoryZoneFinder::AddError);
}

TEST_F(InMemoryZoneFinderTest, addOtherThenCNAME) {
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_cname_a_));
    EXPECT_THROW(zone_finder_.add(rr_cname_), InMemoryZoneFinder::AddError);
}

TEST_F(InMemoryZoneFinderTest, findCNAME) {
    // install CNAME RR
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_cname_));

    // Find A RR of the same.  Should match the CNAME
    findTest(rr_cname_->getName(), RRType::NS(), ZoneFinder::CNAME, true,
             rr_cname_);

    // Find the CNAME itself.  Should result in normal SUCCESS
    findTest(rr_cname_->getName(), RRType::CNAME(), ZoneFinder::SUCCESS, true,
             rr_cname_);
}

TEST_F(InMemoryZoneFinderTest, findCNAMEUnderZoneCut) {
    // There's nothing special when we find a CNAME under a zone cut
    // (with FIND_GLUE_OK).  The behavior is different from BIND 9,
    // so we test this case explicitly.
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_child_ns_));
    ConstRRsetPtr rr_cname_under_cut_ = textToRRset(
        "cname.child.example.org. 300 IN CNAME target.child.example.org.");
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_cname_under_cut_));
    findTest(Name("cname.child.example.org"), RRType::AAAA(),
             ZoneFinder::CNAME, true, rr_cname_under_cut_, NULL,
             ZoneFinder::FIND_GLUE_OK);
}

// Two DNAMEs at single domain are disallowed by RFC 2672, section 3)
// Having a CNAME there is disallowed too, but it is tested by
// addOtherThenCNAME and addCNAMEThenOther.
TEST_F(InMemoryZoneFinderTest, addMultipleDNAMEs) {
    rr_dname_->addRdata(generic::DNAME("target2.example.org."));
    EXPECT_THROW(zone_finder_.add(rr_dname_), InMemoryZoneFinder::AddError);
}

/*
 * These two tests ensure that we can't have DNAME and NS at the same
 * node with the exception of the apex of zone (forbidden by RFC 2672)
 */
TEST_F(InMemoryZoneFinderTest, addDNAMEThenNS) {
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_dname_)));
    EXPECT_THROW(zone_finder_.add(rr_dname_ns_), InMemoryZoneFinder::AddError);
}

TEST_F(InMemoryZoneFinderTest, addNSThenDNAME) {
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_dname_ns_)));
    EXPECT_THROW(zone_finder_.add(rr_dname_), InMemoryZoneFinder::AddError);
}

// It is allowed to have NS and DNAME at apex
TEST_F(InMemoryZoneFinderTest, DNAMEAndNSAtApex) {
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_dname_apex_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_)));

    // The NS should be possible to be found, below should be DNAME, not
    // delegation
    findTest(origin_, RRType::NS(), ZoneFinder::SUCCESS, true, rr_ns_);
    findTest(rr_child_ns_->getName(), RRType::A(), ZoneFinder::DNAME, true,
             rr_dname_apex_);
}

TEST_F(InMemoryZoneFinderTest, NSAndDNAMEAtApex) {
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_dname_apex_)));
}

// TODO: Test (and implement) adding data under DNAME. That is forbidden by
// 2672 as well.

// Search under a DNAME record. It should return the DNAME
TEST_F(InMemoryZoneFinderTest, findBelowDNAME) {
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_dname_)));
    findTest(Name("below.dname.example.org"), RRType::A(), ZoneFinder::DNAME,
             true, rr_dname_);
}

// Search at the domain with DNAME. It should act as DNAME isn't there, DNAME
// influences only the data below (see RFC 2672, section 3)
TEST_F(InMemoryZoneFinderTest, findAtDNAME) {
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_dname_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_dname_a_)));

    const Name dname_name(rr_dname_->getName());
    findTest(dname_name, RRType::A(), ZoneFinder::SUCCESS, true, rr_dname_a_);
    findTest(dname_name, RRType::DNAME(), ZoneFinder::SUCCESS, true,
             rr_dname_);
    findTest(dname_name, RRType::TXT(), ZoneFinder::NXRRSET, true);
}

// Try searching something that is both under NS and DNAME, without and with
// GLUE_OK mode (it should stop at the NS and DNAME respectively).
TEST_F(InMemoryZoneFinderTest, DNAMEUnderNS) {
    zone_finder_.add(rr_child_ns_);
    zone_finder_.add(rr_child_dname_);

    Name lowName("below.dname.child.example.org.");

    findTest(lowName, RRType::A(), ZoneFinder::DELEGATION, true, rr_child_ns_);
    findTest(lowName, RRType::A(), ZoneFinder::DNAME, true, rr_child_dname_,
             NULL, ZoneFinder::FIND_GLUE_OK);
}

// Test adding child zones and zone cut handling
TEST_F(InMemoryZoneFinderTest, delegationNS) {
    // add in-zone data
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_)));

    // install a zone cut
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_child_ns_)));

    // below the zone cut
    findTest(Name("www.child.example.org"), RRType::A(),
             ZoneFinder::DELEGATION, true, rr_child_ns_);

    // at the zone cut
    findTest(Name("child.example.org"), RRType::A(), ZoneFinder::DELEGATION,
             true, rr_child_ns_);
    findTest(Name("child.example.org"), RRType::NS(), ZoneFinder::DELEGATION,
             true, rr_child_ns_);

    // finding NS for the apex (origin) node.  This must not be confused
    // with delegation due to the existence of an NS RR.
    findTest(origin_, RRType::NS(), ZoneFinder::SUCCESS, true, rr_ns_);

    // unusual case of "nested delegation": the highest cut should be used.
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_grandchild_ns_)));
    findTest(Name("www.grand.child.example.org"), RRType::A(),
             // note: !rr_grandchild_ns_
             ZoneFinder::DELEGATION, true, rr_child_ns_);
}

TEST_F(InMemoryZoneFinderTest, delegationWithDS) {
    // Similar setup to the previous one, but with DS RR at the delegation
    // point.
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_));
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_child_ns_));
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_child_ds_));

    // Normal types of query should result in delegation, but DS query
    // should be considered in-zone.
    findTest(Name("child.example.org"), RRType::A(), ZoneFinder::DELEGATION,
             true, rr_child_ns_);
    findTest(Name("child.example.org"), RRType::DS(), ZoneFinder::SUCCESS,
             true, rr_child_ds_);

    // There's nothing special for DS query at the zone apex.  It would
    // normally result in NXRRSET.
    findTest(Name("example.org"), RRType::DS(), ZoneFinder::NXRRSET,
             true, ConstRRsetPtr());
}

TEST_F(InMemoryZoneFinderTest, findAny) {
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_a_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_child_glue_)));

    // origin
    std::vector<ConstRRsetPtr> rrsets(findAllTest(origin_, ZoneFinder::SUCCESS,
                                                  2));
    EXPECT_FALSE(rrsets.end() == std::find(rrsets.begin(), rrsets.end(),
                                           rr_a_));
    EXPECT_FALSE(rrsets.end() == std::find(rrsets.begin(), rrsets.end(),
                                           rr_ns_));

    // out zone name
    findAllTest(Name("example.com"), ZoneFinder::NXDOMAIN, 0);

    rrsets = findAllTest(rr_child_glue_->getName(), ZoneFinder::SUCCESS, 1);
    EXPECT_FALSE(rrsets.end() == std::find(rrsets.begin(), rrsets.end(),
                                           rr_child_glue_));

    // TODO: test NXRRSET case after rbtree non-terminal logic has
    // been implemented

    // add zone cut
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_child_ns_)));

    // zone cut
    findAllTest(rr_child_ns_->getName(), ZoneFinder::DELEGATION, 0, NULL,
                rr_child_ns_);

    // glue for this zone cut
    findAllTest(rr_child_glue_->getName(),ZoneFinder::DELEGATION, 0, NULL,
                rr_child_ns_);
}

TEST_F(InMemoryZoneFinderTest, glue) {
    // install zone data:
    // a zone cut
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_child_ns_)));
    // glue for this cut
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_child_glue_)));
    // a nested zone cut (unusual)
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_grandchild_ns_)));
    // glue under the deeper zone cut
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_grandchild_glue_)));

    // by default glue is hidden due to the zone cut
    findTest(rr_child_glue_->getName(), RRType::A(), ZoneFinder::DELEGATION,
             true, rr_child_ns_);


    // If we do it in the "glue OK" mode, we should find the exact match.
    findTest(rr_child_glue_->getName(), RRType::A(), ZoneFinder::SUCCESS, true,
             rr_child_glue_, NULL, ZoneFinder::FIND_GLUE_OK);

    // glue OK + NXRRSET case
    findTest(rr_child_glue_->getName(), RRType::AAAA(), ZoneFinder::NXRRSET,
             true, ConstRRsetPtr(), NULL, ZoneFinder::FIND_GLUE_OK);

    // glue OK + NXDOMAIN case
    findTest(Name("www.child.example.org"), RRType::A(),
             ZoneFinder::DELEGATION, true, rr_child_ns_, NULL,
             ZoneFinder::FIND_GLUE_OK);

    // nested cut case.  The glue should be found.
    findTest(rr_grandchild_glue_->getName(), RRType::AAAA(),
             ZoneFinder::SUCCESS,
             true, rr_grandchild_glue_, NULL, ZoneFinder::FIND_GLUE_OK);

    // A non-existent name in nested cut.  This should result in delegation
    // at the highest zone cut.
    findTest(Name("www.grand.child.example.org"), RRType::TXT(),
             ZoneFinder::DELEGATION, true, rr_child_ns_, NULL,
             ZoneFinder::FIND_GLUE_OK);
}

/**
 * \brief Test searching.
 *
 * Check it finds or does not find correctly and does not throw exceptions.
 * \todo This doesn't do any kind of CNAME and so on. If it isn't
 *     directly there, it just tells it doesn't exist.
 */
TEST_F(InMemoryZoneFinderTest, find) {
    // Fill some data inside
    // Now put all the data we have there. It should throw nothing
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_a_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_aaaa_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_a_)));

    // These two should be successful
    findTest(origin_, RRType::NS(), ZoneFinder::SUCCESS, true, rr_ns_);
    findTest(rr_ns_a_->getName(), RRType::A(), ZoneFinder::SUCCESS, true,
             rr_ns_a_);

    // These domain exist but don't have the provided RRType
    findTest(origin_, RRType::AAAA(), ZoneFinder::NXRRSET);
    findTest(rr_ns_a_->getName(), RRType::NS(), ZoneFinder::NXRRSET);

    // These domains don't exist (and one is out of the zone)
    findTest(Name("nothere.example.org"), RRType::A(), ZoneFinder::NXDOMAIN);
    findTest(Name("example.net"), RRType::A(), ZoneFinder::NXDOMAIN);
}

TEST_F(InMemoryZoneFinderTest, emptyNode) {
    /*
     * The backend RBTree for this test should look like as follows:
     *          example.org
     *               |
     *              baz (empty; easy case)
     *            /  |  \
     *          bar  |  x.foo ('foo' part is empty; a bit trickier)
     *              bbb
     *             /
     *           aaa
     */

    // Construct the test zone
    const char* const names[] = {
        "bar.example.org.", "x.foo.example.org.", "aaa.baz.example.org.",
        "bbb.baz.example.org.", NULL};
    for (int i = 0; names[i] != NULL; ++i) {
        ConstRRsetPtr rrset = textToRRset(string(names[i]) +
                                          " 300 IN A 192.0.2.1");
        EXPECT_EQ(SUCCESS, zone_finder_.add(rrset));
    }

    // empty node matching, easy case: the node for 'baz' exists with
    // no data.
    findTest(Name("baz.example.org"), RRType::A(), ZoneFinder::NXRRSET);

    // empty node matching, a trickier case: the node for 'foo' is part of
    // "x.foo", which should be considered an empty node.
    findTest(Name("foo.example.org"), RRType::A(), ZoneFinder::NXRRSET);

    // "org" is contained in "example.org", but it shouldn't be treated as
    // NXRRSET because it's out of zone.
    // Note: basically we don't expect such a query to be performed (the common
    // operation is to identify the best matching zone first then perform
    // search it), but we shouldn't be confused even in the unexpected case.
    findTest(Name("org"), RRType::A(), ZoneFinder::NXDOMAIN);
}

TEST_F(InMemoryZoneFinderTest, load) {
    // Put some data inside the zone
    EXPECT_NO_THROW(EXPECT_EQ(result::SUCCESS, zone_finder_.add(rr_ns_)));
    // Loading with different origin should fail
    EXPECT_THROW(zone_finder_.load(TEST_DATA_DIR "/root.zone"),
                 MasterLoadError);
    // See the original data is still there, survived the exception
    findTest(origin_, RRType::NS(), ZoneFinder::SUCCESS, true, rr_ns_);
    // Create correct zone
    InMemoryZoneFinder rootzone(class_, Name("."));
    // Try putting something inside
    EXPECT_NO_THROW(EXPECT_EQ(result::SUCCESS, rootzone.add(rr_ns_aaaa_)));
    // Load the zone. It should overwrite/remove the above RRset
    EXPECT_NO_THROW(rootzone.load(TEST_DATA_DIR "/root.zone"));

    // Now see there are some rrsets (we don't look inside, though)
    findTest(Name("."), RRType::SOA(), ZoneFinder::SUCCESS, false,
             ConstRRsetPtr(), &rootzone);
    findTest(Name("."), RRType::NS(), ZoneFinder::SUCCESS, false,
             ConstRRsetPtr(), &rootzone);
    findTest(Name("a.root-servers.net."), RRType::A(), ZoneFinder::SUCCESS,
             false, ConstRRsetPtr(), &rootzone);
    // But this should no longer be here
    findTest(rr_ns_a_->getName(), RRType::AAAA(), ZoneFinder::NXDOMAIN, true,
             ConstRRsetPtr(), &rootzone);

    // Try loading zone that is wrong in a different way
    EXPECT_THROW(zone_finder_.load(TEST_DATA_DIR "/duplicate_rrset.zone"),
        MasterLoadError);
}

/*
 * Test that puts a (simple) wildcard into the zone and checks we can
 * correctly find the data.
 */
TEST_F(InMemoryZoneFinderTest, wildcard) {
    /*
     *            example.org.
     *                 |
     *                wild (not *.wild, should have wild mark)
     *                 |
     *                 *
     */
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_wild_));

    // Search at the parent. The parent will not have the A, but it will
    // be in the wildcard (so check the wildcard isn't matched at the parent)
    {
        SCOPED_TRACE("Search at parrent");
        findTest(Name("wild.example.org"), RRType::A(), ZoneFinder::NXRRSET);
    }

    // Search the original name of wildcard
    {
        SCOPED_TRACE("Search directly at *");
        findTest(Name("*.wild.example.org"), RRType::A(), ZoneFinder::SUCCESS,
                 true, rr_wild_);
    }
    // Search "created" name.
    {
        SCOPED_TRACE("Search at created child");
        findTest(Name("a.wild.example.org"), RRType::A(), ZoneFinder::SUCCESS,
                 false, rr_wild_, NULL, ZoneFinder::FIND_DEFAULT, true);
    }

    // Search another created name, this time little bit lower
    {
        SCOPED_TRACE("Search at created grand-child");
        findTest(Name("a.b.wild.example.org"), RRType::A(),
                 ZoneFinder::SUCCESS, false, rr_wild_, NULL,
                 ZoneFinder::FIND_DEFAULT, true);
    }

    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_under_wild_));
    {
        SCOPED_TRACE("Search under non-wildcard");
        findTest(Name("bar.foo.wild.example.org"), RRType::A(),
            ZoneFinder::NXDOMAIN);
    }
}

/*
 * Test that we don't match a wildcard if we get under delegation.
 * By 4.3.3 of RFC1034:
 * "Wildcard RRs do not apply:
 *   - When the query is in another zone.  That is, delegation cancels
 *     the wildcard defaults."
 */
TEST_F(InMemoryZoneFinderTest, delegatedWildcard) {
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_child_wild_));
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_child_ns_));

    {
        SCOPED_TRACE("Looking under delegation point");
        findTest(Name("a.child.example.org"), RRType::A(),
                 ZoneFinder::DELEGATION, true, rr_child_ns_);
    }

    {
        SCOPED_TRACE("Looking under delegation point in GLUE_OK mode");
        findTest(Name("a.child.example.org"), RRType::A(),
                 ZoneFinder::DELEGATION, true, rr_child_ns_, NULL,
                 ZoneFinder::FIND_GLUE_OK);
    }
}

// Tests combination of wildcard and ANY.
TEST_F(InMemoryZoneFinderTest, anyWildcard) {
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_wild_));

    // First try directly the name (normal match)
    {
        SCOPED_TRACE("Asking direcly for *");
        const std::vector<ConstRRsetPtr>
            target(findAllTest(Name("*.wild.example.org"), ZoneFinder::SUCCESS,
                               1));
        ASSERT_EQ(1, target.size());
        EXPECT_EQ(RRType::A(), (*target.begin())->getType());
        EXPECT_EQ(Name("*.wild.example.org"), (*target.begin())->getName());
    }

    // Then a wildcard match
    {
        SCOPED_TRACE("Asking in the wild way");
        const std::vector<ConstRRsetPtr>
            target(findAllTest(Name("a.wild.example.org"), ZoneFinder::SUCCESS,
                               1));
        EXPECT_EQ(RRType::A(), (*target.begin())->getType());
        EXPECT_EQ(Name("a.wild.example.org"), (*target.begin())->getName());
    }
}

// Test there's nothing in the wildcard in the middle if we load
// wild.*.foo.example.org.
TEST_F(InMemoryZoneFinderTest, emptyWildcard) {
    /*
     *            example.org.
     *                foo
     *                 *
     *               wild
     */
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_emptywild_));

    {
        SCOPED_TRACE("Asking for the original record under wildcard");
        findTest(Name("wild.*.foo.example.org"), RRType::A(),
                 ZoneFinder::SUCCESS, true, rr_emptywild_);
    }

    {
        SCOPED_TRACE("Asking for A record");
        findTest(Name("a.foo.example.org"), RRType::A(), ZoneFinder::NXRRSET);
        findTest(Name("*.foo.example.org"), RRType::A(), ZoneFinder::NXRRSET);
        findTest(Name("foo.example.org"), RRType::A(), ZoneFinder::NXRRSET);
    }

    {
        SCOPED_TRACE("Asking for ANY record");
        findAllTest(Name("*.foo.example.org"), ZoneFinder::NXRRSET, 0);

        findAllTest(Name("a.foo.example.org"), ZoneFinder::NXRRSET, 0);
    }

    {
        SCOPED_TRACE("Asking on the non-terminal");
        findTest(Name("wild.bar.foo.example.org"), RRType::A(),
            ZoneFinder::NXRRSET);
    }
}

// Same as emptyWildcard, but with multiple * in the path.
TEST_F(InMemoryZoneFinderTest, nestedEmptyWildcard) {
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_nested_emptywild_));

    {
        SCOPED_TRACE("Asking for the original record under wildcards");
        findTest(Name("wild.*.foo.*.bar.example.org"), RRType::A(),
            ZoneFinder::SUCCESS, true, rr_nested_emptywild_);
    }

    {
        SCOPED_TRACE("Matching wildcard against empty nonterminal");

        const char* names[] = {
            "baz.foo.*.bar.example.org",
            "baz.foo.baz.bar.example.org",
            "*.foo.baz.bar.example.org",
            NULL
        };

        for (const char** name = names; *name != NULL; ++ name) {
            SCOPED_TRACE(string("Node ") + *name);
            findTest(Name(*name), RRType::A(), ZoneFinder::NXRRSET);
        }
    }

    // Domains to test
    const char* names[] = {
        "*.foo.*.bar.example.org",
        "foo.*.bar.example.org",
        "*.bar.example.org",
        "bar.example.org",
        NULL
    };

    {
        SCOPED_TRACE("Asking directly for A on parent nodes");

        for (const char** name = names; *name != NULL; ++ name) {
            SCOPED_TRACE(string("Node ") + *name);
            findTest(Name(*name), RRType::A(), ZoneFinder::NXRRSET);
        }
    }

    {
        SCOPED_TRACE("Asking for ANY on parent nodes");

        for (const char** name = names; *name != NULL; ++ name) {
            SCOPED_TRACE(string("Node ") + *name);

            findAllTest(Name(*name), ZoneFinder::NXRRSET, 0);
        }
    }
}

// We run this part twice from the below test, in two slightly different
// situations
void
InMemoryZoneFinderTest::doCancelWildcardTest() {
    // These should be canceled
    {
        SCOPED_TRACE("Canceled under foo.wild.example.org");
        findTest(Name("aaa.foo.wild.example.org"), RRType::A(),
            ZoneFinder::NXDOMAIN);
        findTest(Name("zzz.foo.wild.example.org"), RRType::A(),
            ZoneFinder::NXDOMAIN);
    }

    // This is existing, non-wildcard domain, shouldn't wildcard at all
    {
        SCOPED_TRACE("Existing domain under foo.wild.example.org");
        findTest(Name("bar.foo.wild.example.org"), RRType::A(),
                 ZoneFinder::SUCCESS, true, rr_not_wild_);
    }

    // These should be caught by the wildcard
    {
        SCOPED_TRACE("Neighbor wildcards to foo.wild.example.org");

        const char* names[] = {
            "aaa.bbb.wild.example.org",
            "aaa.zzz.wild.example.org",
            "zzz.wild.example.org",
            NULL
        };

        for (const char** name = names; *name != NULL; ++ name) {
            SCOPED_TRACE(string("Node ") + *name);

            findTest(Name(*name), RRType::A(), ZoneFinder::SUCCESS, false,
                     rr_wild_, NULL, ZoneFinder::FIND_DEFAULT, true);
        }
    }

    // This shouldn't be wildcarded, it's an existing domain
    {
        SCOPED_TRACE("The foo.wild.example.org itself");
        findTest(Name("foo.wild.example.org"), RRType::A(),
                 ZoneFinder::NXRRSET);
    }
}

/*
 * This tests that if there's a name between the wildcard domain and the
 * searched one, it will not trigger wildcard, for example, if we have
 * *.wild.example.org and bar.foo.wild.example.org, then we know
 * foo.wild.example.org exists and is not wildcard. Therefore, search for
 * aaa.foo.wild.example.org should return NXDOMAIN.
 *
 * Tests few cases "around" the canceled wildcard match, to see something that
 * shouldn't be canceled isn't.
 */
TEST_F(InMemoryZoneFinderTest, cancelWildcard) {
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_wild_));
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_not_wild_));

    {
        SCOPED_TRACE("Runnig with single entry under foo.wild.example.org");
        doCancelWildcardTest();
    }

    // Try putting another one under foo.wild....
    // The result should be the same but it will be done in another way in the
    // code, because the foo.wild.example.org will exist in the tree.
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_not_wild_another_));
    {
        SCOPED_TRACE("Runnig with two entries under foo.wild.example.org");
        doCancelWildcardTest();
    }
}

TEST_F(InMemoryZoneFinderTest, loadBadWildcard) {
    // We reject loading the zone if it contains a wildcard name for
    // NS or DNAME.
    EXPECT_THROW(zone_finder_.add(rr_nswild_), InMemoryZoneFinder::AddError);
    EXPECT_THROW(zone_finder_.add(rr_dnamewild_),
                 InMemoryZoneFinder::AddError);
}

TEST_F(InMemoryZoneFinderTest, swap) {
    // build one zone finder with some data
    InMemoryZoneFinder finder1(class_, origin_);
    EXPECT_EQ(result::SUCCESS, finder1.add(rr_ns_));
    EXPECT_EQ(result::SUCCESS, finder1.add(rr_ns_aaaa_));

    // build another zone finder of a different RR class with some other data
    const Name other_origin("version.bind");
    ASSERT_NE(origin_, other_origin); // make sure these two are different
    InMemoryZoneFinder finder2(RRClass::CH(), other_origin);
    EXPECT_EQ(result::SUCCESS,
              finder2.add(textToRRset("version.bind. 0 CH TXT \"test\"",
                                      RRClass::CH())));

    finder1.swap(finder2);
    EXPECT_EQ(other_origin, finder1.getOrigin());
    EXPECT_EQ(origin_, finder2.getOrigin());
    EXPECT_EQ(RRClass::CH(), finder1.getClass());
    EXPECT_EQ(RRClass::IN(), finder2.getClass());
    // make sure the zone data is swapped, too
    findTest(origin_, RRType::NS(), ZoneFinder::NXDOMAIN, false,
             ConstRRsetPtr(), &finder1);
    findTest(other_origin, RRType::TXT(), ZoneFinder::SUCCESS, false,
             ConstRRsetPtr(), &finder1);
    findTest(origin_, RRType::NS(), ZoneFinder::SUCCESS, false,
             ConstRRsetPtr(), &finder2);
    findTest(other_origin, RRType::TXT(), ZoneFinder::NXDOMAIN, false,
             ConstRRsetPtr(), &finder2);
}

TEST_F(InMemoryZoneFinderTest, getFileName) {
    // for an empty zone the file name should also be empty.
    EXPECT_TRUE(zone_finder_.getFileName().empty());

    // if loading a zone fails the file name shouldn't be set.
    EXPECT_THROW(zone_finder_.load(TEST_DATA_DIR "/root.zone"),
                 MasterLoadError);
    EXPECT_TRUE(zone_finder_.getFileName().empty());

    // after a successful load, the specified file name should be set
    InMemoryZoneFinder rootzone(class_, Name("."));
    EXPECT_NO_THROW(rootzone.load(TEST_DATA_DIR "/root.zone"));
    EXPECT_EQ(TEST_DATA_DIR "/root.zone", rootzone.getFileName());
    // overriding load, which will fail
    EXPECT_THROW(rootzone.load(TEST_DATA_DIR "/duplicate_rrset.zone"),
                 MasterLoadError);
    // the file name should be intact.
    EXPECT_EQ(TEST_DATA_DIR "/root.zone", rootzone.getFileName());

    // After swap, file names should also be swapped.
    zone_finder_.swap(rootzone);
    EXPECT_EQ(TEST_DATA_DIR "/root.zone", zone_finder_.getFileName());
    EXPECT_TRUE(rootzone.getFileName().empty());
}

TEST_F(InMemoryZoneFinderTest, addRRsig) {
    // A simple valid case: adding an RRset to be signed followed by an RRSIG
    // that covers the first RRset
    zone_finder_.add(rr_a_);
    zone_finder_.add(textToRRset(rrsig_a_txt));
    ZoneFinder::FindResult result = zone_finder_.find(origin_, RRType::A(),
                                                      ZoneFinder::FIND_DNSSEC);
    EXPECT_EQ(ZoneFinder::SUCCESS, result.code);
    ASSERT_TRUE(result.rrset);
    ASSERT_TRUE(result.rrset->getRRsig());
    actual_rrsets_.push_back(result.rrset->getRRsig());
    rrsetsCheck(rrsig_a_txt, actual_rrsets_.begin(), actual_rrsets_.end());

    // Confirm a separate RRISG for a different type can be added
    actual_rrsets_.clear();
    zone_finder_.add(rr_ns_);
    zone_finder_.add(textToRRset(rrsig_ns_txt));
    ZoneFinder::FindResult result2 =
        zone_finder_.find(origin_, RRType::NS(), ZoneFinder::FIND_DNSSEC);
    EXPECT_EQ(ZoneFinder::SUCCESS, result2.code);
    ASSERT_TRUE(result2.rrset);
    ASSERT_TRUE(result2.rrset->getRRsig());
    actual_rrsets_.push_back(result2.rrset->getRRsig());
    rrsetsCheck(rrsig_ns_txt, actual_rrsets_.begin(), actual_rrsets_.end());

    // Check a case with multiple RRSIGs
    actual_rrsets_.clear();
    zone_finder_.add(rr_ns_aaaa_);
    zone_finder_.add(textToRRset(rrsig_aaaa_txt));
    ZoneFinder::FindResult result3 =
        zone_finder_.find(Name("ns.example.org"), RRType::AAAA(),
                          ZoneFinder::FIND_DNSSEC);
    EXPECT_EQ(ZoneFinder::SUCCESS, result3.code);
    ASSERT_TRUE(result3.rrset);
    ASSERT_TRUE(result3.rrset->getRRsig());
    actual_rrsets_.push_back(result3.rrset->getRRsig());
    rrsetsCheck(rrsig_aaaa_txt, actual_rrsets_.begin(), actual_rrsets_.end());
}

TEST_F(InMemoryZoneFinderTest, addRRsigWithoutCovered) {
    // The current implementation rejects attempts of adding RRSIG without
    // covered RRsets already in the zone.

    // Name doesn't exist
    EXPECT_THROW(zone_finder_.add(
                     textToRRset("notexist.example.org. 300 IN RRSIG A 5 3 "
                                 "3600 20000101000000 20000201000000 12345 "
                                 "example.org. FAKEFAKEFAKE\n")),
                 InMemoryZoneFinder::AddError);

    // Name exists, but is empty.
    zone_finder_.add(rr_emptywild_);
    EXPECT_THROW(zone_finder_.add(
                     textToRRset("foo.example.org. 300 IN RRSIG A 5 3 "
                                 "3600 20000101000000 20000201000000 12345 "
                                 "example.org. FAKEFAKEFAKE\n")),
                 InMemoryZoneFinder::AddError);

    // Add RRSIG RRset without covered RR
    zone_finder_.add(rr_a_);
    EXPECT_THROW(zone_finder_.add(textToRRset(rrsig_ns_txt)),
                 InMemoryZoneFinder::AddError);
}

TEST_F(InMemoryZoneFinderTest, addbadRRsig) {
    // Tests with other types of bogus input

    // Empty RRSIG RRset.
    EXPECT_THROW(zone_finder_.add(RRsetPtr(new RRset(origin_, class_,
                                                     RRType::RRSIG(),
                                                     RRTTL(300)))),
                                  InMemoryZoneFinder::AddError);

    // RRSIG with mixed covered types
    zone_finder_.add(rr_a_);    // make sure the covered name exists
    // textToRRset() doesn't work as intended for this pathological case,
    // so we need to construct the RRset by hand.
    RRsetPtr rrset(new RRset(origin_, class_, RRType::RRSIG(), RRTTL(300)));
    rrset->addRdata(generic::RRSIG("A 5 3 3600 20000101000000 20000201000000 "
                                   "12345 example.org. FAKEFAKEFAKE"));
    rrset->addRdata(generic::RRSIG("NS 5 3 3600 20000101000000 20000201000000 "
                                   "54321 example.org. FAKEFAKEFAKEFAKE"));
    EXPECT_THROW(zone_finder_.add(rrset), InMemoryZoneFinder::AddError);

    // An attempt of overriding an existing RRSIG.  The current implementation
    // prohibits that.
    zone_finder_.add(textToRRset(rrsig_a_txt));
    EXPECT_THROW(zone_finder_.add(textToRRset(rrsig_a_txt)),
                 InMemoryZoneFinder::AddError);
}

//
// (Faked) NSEC3 hash data.  Arbitrarily borrowed from RFC515 examples.
//
// Commonly used NSEC3 suffix.  It's incorrect to use it for all NSEC3s, but
// doesn't matter for the purpose of our tests.
const char* const nsec3_common = " 300 IN NSEC3 1 1 12 aabbccdd "
    "2T7B4G4VSA5SMI47K61MV5BV1A22BOJR A RRSIG";
// For apex (example.org)
const char* const apex_hash = "0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM";
const char* const apex_hash_down = "0p9mhaveqvm6t7vbl5lop2u3t2rp3tom";

TEST_F(InMemoryZoneFinderTest, addNSEC3) {
    const string nsec3_text = string(apex_hash) + ".example.org." +
        string(nsec3_common);
    // This name shouldn't be found in the normal domain tree.
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(textToRRset(nsec3_text)));
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              zone_finder_.find(Name(string(apex_hash) + ".example.org"),
                                RRType::NSEC3()).code);
    // Dedicated NSEC3 find should be able to find it.
    ZoneFinder::FindNSEC3Result result =
        zone_finder_.findNSEC3Tmp(Name("example.org"), false);
    EXPECT_TRUE(result.matched);
    ASSERT_TRUE(result.closest_proof);
    actual_rrsets_.push_back(result.closest_proof);
    rrsetsCheck(nsec3_text, actual_rrsets_.begin(), actual_rrsets_.end());

    // This implementation rejects duplicate/update add of the same hash name
    EXPECT_EQ(result::EXIST,
              zone_finder_.add(textToRRset(
                                   string(apex_hash) + ".example.org." +
                                   string(nsec3_common) + " AAAA")));
    // The original NSEC3 should be intact
    actual_rrsets_.clear();
    ZoneFinder::FindNSEC3Result result2 =
        zone_finder_.findNSEC3Tmp(Name("example.org"), false);
    actual_rrsets_.push_back(result2.closest_proof);
    rrsetsCheck(nsec3_text, actual_rrsets_.begin(), actual_rrsets_.end());
}

TEST_F(InMemoryZoneFinderTest, addNSEC3Lower) {
    // Similar to the previous case, but NSEC3 owner name is lower-cased.
    const string nsec3_text = string(apex_hash_down) + ".example.org." +
        string(nsec3_common);
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(textToRRset(nsec3_text)));
    ZoneFinder::FindNSEC3Result result =
        zone_finder_.findNSEC3Tmp(Name("example.org"), false);
    EXPECT_TRUE(result.matched);
    ASSERT_TRUE(result.closest_proof);
    actual_rrsets_.push_back(result.closest_proof);
    rrsetsCheck(nsec3_text, actual_rrsets_.begin(), actual_rrsets_.end());
}

TEST_F(InMemoryZoneFinderTest, badNSEC3Name) {
    // Our implementation refuses to load NSEC3 at a wildcard name
    EXPECT_THROW(zone_finder_.add(textToRRset("*.example.org." +
                                              string(nsec3_common))),
                 InMemoryZoneFinder::AddError);

    // Likewise, if the owner name of NSEC3 has too many labels, it's refused.
    EXPECT_THROW(zone_finder_.add(textToRRset("a." + string(apex_hash) +
                                              ".example.org." +
                                              string(nsec3_common))),
                 InMemoryZoneFinder::AddError);

    // - adding RRSIG for NSEC3
    // - case where the main tree has NSEC3 name
    // - parameter consistency
    // - existence of NSEC3PARAM
    // - parameter consistency with NSEC3PARAM
    // - add NSEC3PARAM first/second
}
}
