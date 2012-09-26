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

#include "faked_nsec3.h"

#include <exceptions/exceptions.h>

#include <dns/masterload.h>
#include <dns/name.h>
#include <dns/nsec3hash.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrsetlist.h>
#include <dns/rrttl.h>
#include <dns/masterload.h>

#include <datasrc/client.h>
#include <datasrc/memory_datasrc.h>
#include <datasrc/data_source.h>
#include <datasrc/iterator.h>

#include "test_client.h"

#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

#include <sstream>
#include <vector>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc;
using namespace isc::testutils;
using boost::shared_ptr;
using namespace isc::datasrc::test;

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

    // Check it with full zone.
    vector<ConstRRsetPtr> expected_rrsets;
    expected_rrsets.push_back(aRRsetA);
    expected_rrsets.push_back(aRRsetAAAA);
    expected_rrsets.push_back(subRRsetA);

    iterator = memory_client.getIterator(Name("a"));
    vector<ConstRRsetPtr> actual_rrsets;
    ConstRRsetPtr actual;
    while ((actual = iterator->getNextRRset()) != NULL) {
        actual_rrsets.push_back(actual);
    }

    rrsetsCheck(expected_rrsets.begin(), expected_rrsets.end(),
                actual_rrsets.begin(), actual_rrsets.end());

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
protected:
    // The following sub tests are shared by multiple test cases, changing
    // the zone's DNSSEC status (unsigned, NSEC-signed or NSEC3-signed).
    // expected_flags is set to either RESULT_NSEC_SIGNED or
    // RESULT_NSEC3_SIGNED when it's NSEC/NSEC3 signed respectively and
    // find() is expected to set the corresponding flags.
    // find_options should be set to FIND_DNSSEC for NSEC-signed case when
    // NSEC is expected to be returned.
    void findCheck(ZoneFinder::FindResultFlags expected_flags =
                   ZoneFinder::RESULT_DEFAULT,
                   ZoneFinder::FindOptions find_options =
                   ZoneFinder::FIND_DEFAULT);
    void emptyNodeCheck(ZoneFinder::FindResultFlags expected_flags =
                        ZoneFinder::RESULT_DEFAULT);
    void wildcardCheck(ZoneFinder::FindResultFlags expected_flags =
                       ZoneFinder::RESULT_DEFAULT,
                       ZoneFinder::FindOptions find_options =
                       ZoneFinder::FIND_DEFAULT);
    void doCancelWildcardCheck(ZoneFinder::FindResultFlags expected_flags =
                               ZoneFinder::RESULT_DEFAULT,
                               ZoneFinder::FindOptions find_options =
                               ZoneFinder::FIND_DEFAULT);
    void anyWildcardCheck(ZoneFinder::FindResultFlags expected_flags =
                          ZoneFinder::RESULT_DEFAULT);
    void emptyWildcardCheck(ZoneFinder::FindResultFlags expected_flags =
                            ZoneFinder::RESULT_DEFAULT);
    void findNSECENTCheck(const Name& ent_name,
                          ConstRRsetPtr expected_nsec,
                          ZoneFinder::FindResultFlags expected_flags =
                          ZoneFinder::RESULT_DEFAULT);

public:
    InMemoryZoneFinderTest() :
        class_(RRClass::IN()),
        origin_("example.org"),
        zone_finder_(class_, origin_)
    {
        // Build test RRsets.  Below, we construct an RRset for
        // each textual RR(s) of zone_data, and assign it to the corresponding
        // rr_xxx.
        // Note that this contains an out-of-zone RR, and due to the
        // validation check of masterLoad() used below, we cannot add SOA.
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
            {"*.cnamewild.example.org. 300 IN CNAME canonial.example.org.",
             &rr_cnamewild_},
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
            {"0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM.example.org. 300 IN "
             "NSEC3 1 1 12 aabbccdd 2T7B4G4VSA5SMI47K61MV5BV1A22BOJR A RRSIG",
             &rr_nsec3_},
            {"example.org. 300 IN NSEC wild.*.foo.example.org. "
             "NS SOA RRSIG NSEC DNSKEY", &rr_nsec_},
            // Together with the apex NSEC, these next NSECs make a complete
            // chain in the case of the zone for the emptyNonterminal tests
            // (We may want to clean up this generator code and/or masterLoad
            // so that we can prepare conflicting datasets better)
            {"wild.*.foo.example.org. 3600 IN NSEC ns.example.org. "
             "A RRSIG NSEC", &rr_ent_nsec2_},
            {"ns.example.org. 3600 IN NSEC foo.wild.example.org. A RRSIG NSEC",
             &rr_ent_nsec3_},
            {"foo.wild.example.org. 3600 IN NSEC example.org. A RRSIG NSEC",
             &rr_ent_nsec4_},
            // And these are NSECs used in different tests
            {"ns.example.org. 300 IN NSEC *.nswild.example.org. A AAAA NSEC",
             &rr_ns_nsec_},
            {"*.wild.example.org. 300 IN NSEC foo.wild.example.org. A NSEC",
             &rr_wild_nsec_},
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

    ~InMemoryZoneFinderTest() {
        // Make sure we reset the hash creator to the default
        setNSEC3HashCreator(NULL);
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
    RRsetPtr rr_wild_;        // Wildcard record
    RRsetPtr rr_cnamewild_;     // CNAME at a wildcard
    RRsetPtr rr_emptywild_;
    RRsetPtr rr_nested_emptywild_;
    RRsetPtr rr_nswild_, rr_dnamewild_;
    RRsetPtr rr_child_wild_;
    RRsetPtr rr_under_wild_;
    RRsetPtr rr_not_wild_;
    RRsetPtr rr_not_wild_another_;
    RRsetPtr rr_nsec3_;
    RRsetPtr rr_nsec_;
    RRsetPtr rr_ent_nsec2_;
    RRsetPtr rr_ent_nsec3_;
    RRsetPtr rr_ent_nsec4_;
    RRsetPtr rr_ns_nsec_;
    RRsetPtr rr_wild_nsec_;

    // A faked NSEC3 hash calculator for convenience.
    // Tests that need to use the faked hashed values should call
    // setNSEC3HashCreator() with a pointer to this variable at the beginning
    // of the test (at least before adding any NSEC3/NSEC3PARAM RR).
    TestNSEC3HashCreator nsec3_hash_creator_;

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
     * \param expected_flags The expected result flags returned via find().
     *     These can be tested using isWildcard() etc.
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
                  ZoneFinder::FindResultFlags expected_flags =
                  ZoneFinder::RESULT_DEFAULT,
                  InMemoryZoneFinder* zone_finder = NULL,
                  ZoneFinder::FindOptions options = ZoneFinder::FIND_DEFAULT,
                  bool check_wild_answer = false)
    {
        SCOPED_TRACE("findTest for " + name.toText() + "/" + rrtype.toText());

        if (zone_finder == NULL) {
            zone_finder = &zone_finder_;
        }
        const ConstRRsetPtr answer_sig = answer ? answer->getRRsig() :
            RRsetPtr(); // note we use the same type as of retval of getRRsig()
        // The whole block is inside, because we need to check the result and
        // we can't assign to FindResult
        EXPECT_NO_THROW({
                ZoneFinderContextPtr find_result(zone_finder->find(
                                                     name, rrtype, options));
                // Check it returns correct answers
                EXPECT_EQ(result, find_result->code);
                EXPECT_EQ((expected_flags & ZoneFinder::RESULT_WILDCARD) != 0,
                          find_result->isWildcard());
                EXPECT_EQ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED)
                          != 0, find_result->isNSECSigned());
                EXPECT_EQ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED)
                          != 0, find_result->isNSEC3Signed());
                if (check_answer) {
                    if (!answer) {
                        ASSERT_FALSE(find_result->rrset);
                    } else {
                        ASSERT_TRUE(find_result->rrset);
                        rrsetCheck(answer, find_result->rrset);
                        if (answer_sig) {
                            ASSERT_TRUE(find_result->rrset->getRRsig());
                            rrsetCheck(answer_sig,
                                       find_result->rrset->getRRsig());
                        }
                    }
                } else if (check_wild_answer) {
                    ASSERT_NE(ConstRRsetPtr(), answer) <<
                        "Wrong test, don't check for wild names if you expect "
                        "empty answer";
                    ASSERT_NE(ConstRRsetPtr(), find_result->rrset) <<
                        "No answer found";
                    // Build the expected answer using the given name and
                    // other parameter of the base wildcard RRset.
                    RRsetPtr wildanswer(new RRset(name, answer->getClass(),
                                                  answer->getType(),
                                                  answer->getTTL()));
                    RdataIteratorPtr expectedIt(answer->getRdataIterator());
                    for (; !expectedIt->isLast(); expectedIt->next()) {
                        wildanswer->addRdata(expectedIt->getCurrent());
                    }
                    rrsetCheck(wildanswer, find_result->rrset);

                    // Same for the RRSIG, if any.
                    if (answer_sig) {
                        ASSERT_TRUE(find_result->rrset->getRRsig());

                        RRsetPtr wildsig(new RRset(name,
                                                   answer_sig->getClass(),
                                                   RRType::RRSIG(),
                                                   answer_sig->getTTL()));
                        RdataIteratorPtr expectedIt(
                            answer_sig->getRdataIterator());
                        for (; !expectedIt->isLast(); expectedIt->next()) {
                            wildsig->addRdata(expectedIt->getCurrent());
                        }
                        rrsetCheck(wildsig, find_result->rrset->getRRsig());
                    }
                }
            });
    }
    /**
     * \brief Calls the findAll on the finder and checks the result.
     */
    void findAllTest(const Name& name, ZoneFinder::Result result,
                     const vector<ConstRRsetPtr>& expected_rrsets,
                     ZoneFinder::FindResultFlags expected_flags =
                     ZoneFinder::RESULT_DEFAULT,
                     InMemoryZoneFinder* finder = NULL,
                     const ConstRRsetPtr &rrset_result = ConstRRsetPtr(),
                     ZoneFinder::FindOptions options =
                     ZoneFinder::FIND_DEFAULT)
    {
        if (finder == NULL) {
            finder = &zone_finder_;
        }
        std::vector<ConstRRsetPtr> target;
        ZoneFinderContextPtr find_result(finder->findAll(name, target,
                                                         options));
        EXPECT_EQ(result, find_result->code);
        if (!rrset_result) {
            EXPECT_FALSE(find_result->rrset);
        } else {
            ASSERT_TRUE(find_result->rrset);
            rrsetCheck(rrset_result, find_result->rrset);
        }
        EXPECT_EQ((expected_flags & ZoneFinder::RESULT_WILDCARD) != 0,
                  find_result->isWildcard());
        EXPECT_EQ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED)
                  != 0, find_result->isNSECSigned());
        EXPECT_EQ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED)
                  != 0, find_result->isNSEC3Signed());
        rrsetsCheck(expected_rrsets.begin(), expected_rrsets.end(),
                    target.begin(), target.end());
    }
};

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
    EXPECT_THROW(zone_finder_.add(rr_out_), OutOfZone);
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

TEST_F(InMemoryZoneFinderTest, addCNAMEAndDNSSECRecords) {
    // CNAME and RRSIG can coexist
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_cname_));
    EXPECT_EQ(SUCCESS, zone_finder_.add(
                  textToRRset("cname.example.org. 300 IN RRSIG CNAME 5 3 "
                              "3600 20000101000000 20000201000000 12345 "
                              "example.org. FAKEFAKEFAKE")));

    // Same for NSEC
    EXPECT_EQ(SUCCESS, zone_finder_.add(
                  textToRRset("cname.example.org. 300 IN NSEC "
                              "dname.example.org. CNAME RRSIG NSEC")));

    // Same as above, but adding NSEC first.
    EXPECT_EQ(SUCCESS, zone_finder_.add(
                  textToRRset("cname2.example.org. 300 IN NSEC "
                              "dname.example.org. CNAME RRSIG NSEC")));
    EXPECT_EQ(SUCCESS, zone_finder_.add(
                  textToRRset("cname2.example.org. 300 IN CNAME c.example.")));

    // If there's another type of RRset with NSEC, it should still fail.
    EXPECT_EQ(SUCCESS, zone_finder_.add(
                  textToRRset("cname3.example.org. 300 IN A 192.0.2.1")));
    EXPECT_EQ(SUCCESS, zone_finder_.add(
                  textToRRset("cname3.example.org. 300 IN NSEC "
                              "dname.example.org. CNAME RRSIG NSEC")));
    EXPECT_THROW(zone_finder_.add(textToRRset("cname3.example.org. 300 "
                                              "IN CNAME c.example.")),
                 InMemoryZoneFinder::AddError);
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
             ZoneFinder::CNAME, true, rr_cname_under_cut_,
             ZoneFinder::RESULT_DEFAULT, NULL, ZoneFinder::FIND_GLUE_OK);
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
             ZoneFinder::RESULT_DEFAULT, NULL, ZoneFinder::FIND_GLUE_OK);
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
    // should be considered in-zone (but only exactly at the delegation point).
    findTest(Name("child.example.org"), RRType::A(), ZoneFinder::DELEGATION,
             true, rr_child_ns_);
    findTest(Name("child.example.org"), RRType::DS(), ZoneFinder::SUCCESS,
             true, rr_child_ds_);
    findTest(Name("grand.child.example.org"), RRType::DS(),
             ZoneFinder::DELEGATION, true, rr_child_ns_);

    // There's nothing special for DS query at the zone apex.  It would
    // normally result in NXRRSET.
    findTest(Name("example.org"), RRType::DS(), ZoneFinder::NXRRSET,
             true, ConstRRsetPtr());
}

TEST_F(InMemoryZoneFinderTest, findAny) {
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_a_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_child_glue_)));

    vector<ConstRRsetPtr> expected_sets;

    // origin
    expected_sets.push_back(rr_a_);
    expected_sets.push_back(rr_ns_);
    findAllTest(origin_, ZoneFinder::SUCCESS, expected_sets);

    // out zone name
    EXPECT_THROW(findAllTest(Name("example.com"), ZoneFinder::NXDOMAIN,
                             vector<ConstRRsetPtr>()),
                 OutOfZone);

    expected_sets.clear();
    expected_sets.push_back(rr_child_glue_);
    findAllTest(rr_child_glue_->getName(), ZoneFinder::SUCCESS, expected_sets);

    // add zone cut
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_child_ns_)));

    // zone cut
    findAllTest(rr_child_ns_->getName(), ZoneFinder::DELEGATION,
                vector<ConstRRsetPtr>(), ZoneFinder::RESULT_DEFAULT,
                NULL, rr_child_ns_);

    // glue for this zone cut
    findAllTest(rr_child_glue_->getName(),ZoneFinder::DELEGATION,
                vector<ConstRRsetPtr>(), ZoneFinder::RESULT_DEFAULT,
                NULL, rr_child_ns_);
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
             rr_child_glue_, ZoneFinder::RESULT_DEFAULT, NULL,
             ZoneFinder::FIND_GLUE_OK);

    // glue OK + NXRRSET case
    findTest(rr_child_glue_->getName(), RRType::AAAA(), ZoneFinder::NXRRSET,
             true, ConstRRsetPtr(), ZoneFinder::RESULT_DEFAULT, NULL,
             ZoneFinder::FIND_GLUE_OK);

    // glue OK + NXDOMAIN case
    findTest(Name("www.child.example.org"), RRType::A(),
             ZoneFinder::DELEGATION, true, rr_child_ns_,
             ZoneFinder::RESULT_DEFAULT, NULL, ZoneFinder::FIND_GLUE_OK);

    // nested cut case.  The glue should be found.
    findTest(rr_grandchild_glue_->getName(), RRType::AAAA(),
             ZoneFinder::SUCCESS,
             true, rr_grandchild_glue_, ZoneFinder::RESULT_DEFAULT, NULL,
             ZoneFinder::FIND_GLUE_OK);

    // A non-existent name in nested cut.  This should result in delegation
    // at the highest zone cut.
    findTest(Name("www.grand.child.example.org"), RRType::TXT(),
             ZoneFinder::DELEGATION, true, rr_child_ns_,
             ZoneFinder::RESULT_DEFAULT, NULL, ZoneFinder::FIND_GLUE_OK);
}

/**
 * \brief Test searching.
 *
 * Check it finds or does not find correctly and does not throw exceptions.
 * \todo This doesn't do any kind of CNAME and so on. If it isn't
 *     directly there, it just tells it doesn't exist.
 */
void
InMemoryZoneFinderTest::findCheck(ZoneFinder::FindResultFlags expected_flags,
                                  ZoneFinder::FindOptions find_options)
{
    // Fill some data inside
    // Now put all the data we have there. It should throw nothing
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_a_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_aaaa_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_finder_.add(rr_a_)));
    if ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0) {
        EXPECT_EQ(SUCCESS, zone_finder_.add(rr_nsec3_));
    }
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        EXPECT_EQ(SUCCESS, zone_finder_.add(rr_nsec_));
    }

    // These two should be successful
    findTest(origin_, RRType::NS(), ZoneFinder::SUCCESS, true, rr_ns_);
    findTest(rr_ns_a_->getName(), RRType::A(), ZoneFinder::SUCCESS, true,
             rr_ns_a_);

    // These domains don't exist. (and one is out of the zone).  In an
    // NSEC-signed zone with DNSSEC records requested, it should return the
    // covering NSEC for the query name (the actual NSEC in the test data may
    // not really "cover" it, but for the purpose of this test it's okay).
    ConstRRsetPtr expected_nsec; // by default it's NULL
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0 &&
        (find_options & ZoneFinder::FIND_DNSSEC) != 0) {
        expected_nsec = rr_nsec_;
    }

    // There's no other name between this one and the origin, so when NSEC
    // is to be returned it should be the origin NSEC.
    findTest(Name("nothere.example.org"), RRType::A(),
             ZoneFinder::NXDOMAIN, true, expected_nsec, expected_flags,
             NULL, find_options);

    // The previous name in the zone is "ns.example.org", but it doesn't
    // have an NSEC.  It should be skipped and the origin NSEC will be
    // returned as the "closest NSEC".
    findTest(Name("nxdomain.example.org"), RRType::A(),
             ZoneFinder::NXDOMAIN, true, expected_nsec, expected_flags,
             NULL, find_options);
    EXPECT_THROW(zone_finder_.find(Name("example.net"), RRType::A()),
                 OutOfZone);

    // These domain exist but don't have the provided RRType.  For the latter
    // one we now add its NSEC (which was delayed so that it wouldn't break
    // other cases above).
    findTest(origin_, RRType::AAAA(), ZoneFinder::NXRRSET, true,
             expected_nsec, expected_flags, NULL, find_options);
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ns_nsec_));
        if ((find_options & ZoneFinder::FIND_DNSSEC) != 0) {
            expected_nsec = rr_ns_nsec_;
        }
    }
    findTest(rr_ns_a_->getName(), RRType::NS(), ZoneFinder::NXRRSET, true,
             expected_nsec, expected_flags, NULL, find_options);
}

TEST_F(InMemoryZoneFinderTest, find) {
    findCheck();
}

TEST_F(InMemoryZoneFinderTest, findNSEC3Signed) {
    findCheck(ZoneFinder::RESULT_NSEC3_SIGNED);
}

TEST_F(InMemoryZoneFinderTest, findNSEC3SignedWithDNSSEC) {
    // For NSEC3-signed zones, specifying the DNSSEC option shouldn't change
    // anything (the NSEC3_SIGNED flag is always set, and no records are
    // returned for negative cases regardless).
    findCheck(ZoneFinder::RESULT_NSEC3_SIGNED, ZoneFinder::FIND_DNSSEC);
}

TEST_F(InMemoryZoneFinderTest, findNSECSigned) {
    // NSEC-signed zone, without requesting DNSSEC (no NSEC should be provided)
    findCheck(ZoneFinder::RESULT_NSEC_SIGNED);
}

// Generalized test for Empty Nonterminal (ENT) cases with NSEC
void
InMemoryZoneFinderTest::findNSECENTCheck(const Name& ent_name,
    ConstRRsetPtr expected_nsec,
    ZoneFinder::FindResultFlags expected_flags)
{
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_emptywild_));
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_under_wild_));

    // Sanity check: Should result in NXRRSET
    findTest(ent_name, RRType::A(), ZoneFinder::NXRRSET, true,
             ConstRRsetPtr(), expected_flags);
    // Sanity check: No NSEC added yet
    findTest(ent_name, RRType::A(), ZoneFinder::NXRRSET, true,
             ConstRRsetPtr(), expected_flags,
             NULL, ZoneFinder::FIND_DNSSEC);

    // Now add the NSEC rrs making it a 'complete' zone (in terms of NSEC,
    // there are no sigs)
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_nsec_));
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ent_nsec2_));
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ent_nsec3_));
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_ent_nsec4_));

    // Should result in NXRRSET, and RESULT_NSEC_SIGNED
    findTest(ent_name, RRType::A(), ZoneFinder::NXRRSET, true,
             ConstRRsetPtr(),
             expected_flags | ZoneFinder::RESULT_NSEC_SIGNED);

    // And check for the NSEC if DNSSEC_OK
    findTest(ent_name, RRType::A(), ZoneFinder::NXRRSET, true,
             expected_nsec, expected_flags | ZoneFinder::RESULT_NSEC_SIGNED,
             NULL, ZoneFinder::FIND_DNSSEC);
}

TEST_F(InMemoryZoneFinderTest,findNSECEmptyNonterminal) {
    // Non-wildcard case
    findNSECENTCheck(Name("wild.example.org"), rr_ent_nsec3_);
}

TEST_F(InMemoryZoneFinderTest,findNSECEmptyNonterminalWildcard) {
    // Wildcard case, above actual wildcard
    findNSECENTCheck(Name("foo.example.org"), rr_nsec_);
}

TEST_F(InMemoryZoneFinderTest,findNSECEmptyNonterminalAtWildcard) {
    // Wildcard case, at actual wildcard
    findNSECENTCheck(Name("bar.foo.example.org"), rr_nsec_,
                     ZoneFinder::RESULT_WILDCARD);
}

TEST_F(InMemoryZoneFinderTest, findNSECSignedWithDNSSEC) {
    // NSEC-signed zone, requesting DNSSEC (NSEC should be provided)
    findCheck(ZoneFinder::RESULT_NSEC_SIGNED, ZoneFinder::FIND_DNSSEC);
}

void
InMemoryZoneFinderTest::emptyNodeCheck(
    ZoneFinder::FindResultFlags expected_flags)
{
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
    if ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0) {
        EXPECT_EQ(SUCCESS, zone_finder_.add(rr_nsec3_));
    }
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        EXPECT_EQ(SUCCESS, zone_finder_.add(rr_nsec_));
    }

    // empty node matching, easy case: the node for 'baz' exists with
    // no data.
    findTest(Name("baz.example.org"), RRType::A(), ZoneFinder::NXRRSET, true,
             ConstRRsetPtr(), expected_flags);

    // empty node matching, a trickier case: the node for 'foo' is part of
    // "x.foo", which should be considered an empty node.
    findTest(Name("foo.example.org"), RRType::A(), ZoneFinder::NXRRSET, true,
             ConstRRsetPtr(), expected_flags);

    // "org" is contained in "example.org", but it shouldn't be treated as
    // NXRRSET because it's out of zone.
    // Note: basically we don't expect such a query to be performed (the common
    // operation is to identify the best matching zone first then perform
    // search it), but we shouldn't be confused even in the unexpected case.
    EXPECT_THROW(zone_finder_.find(Name("org"), RRType::A()), OutOfZone);
}

TEST_F(InMemoryZoneFinderTest, emptyNode) {
    emptyNodeCheck();
}

TEST_F(InMemoryZoneFinderTest, emptyNodeNSEC3) {
    emptyNodeCheck(ZoneFinder::RESULT_NSEC3_SIGNED);
}

TEST_F(InMemoryZoneFinderTest, emptyNodeNSEC) {
    emptyNodeCheck(ZoneFinder::RESULT_NSEC_SIGNED);
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
             ConstRRsetPtr(), ZoneFinder::RESULT_DEFAULT, &rootzone);
    findTest(Name("."), RRType::NS(), ZoneFinder::SUCCESS, false,
             ConstRRsetPtr(), ZoneFinder::RESULT_DEFAULT, &rootzone);
    findTest(Name("a.root-servers.net."), RRType::A(), ZoneFinder::SUCCESS,
             false, ConstRRsetPtr(), ZoneFinder::RESULT_DEFAULT, &rootzone);
    // But this should no longer be here
    findTest(rr_ns_a_->getName(), RRType::AAAA(), ZoneFinder::NXDOMAIN, true,
             ConstRRsetPtr(), ZoneFinder::RESULT_DEFAULT, &rootzone);

    // Try loading zone that is wrong in a different way
    EXPECT_THROW(zone_finder_.load(TEST_DATA_DIR "/duplicate_rrset.zone"),
                 MasterLoadError);
}

TEST_F(InMemoryZoneFinderTest, loadFromIterator) {
    // The initial test set doesn't have SOA at the apex.
    findTest(origin_, RRType::SOA(), ZoneFinder::NXRRSET, false,
             ConstRRsetPtr());

    // The content of the new version of zone to be first installed to
    // the SQLite3 data source, then to in-memory via SQLite3.  The data are
    // chosen to cover major check points of the implementation:
    // - the previously non-existent record is added (SOA)
    // - An RRSIG is given from the iterator before the RRset it covers
    //   (RRSIG for SOA, because they are sorted by name then rrtype as text)
    // - An RRset containing multiple RRs (ns1/A)
    // - RRSIGs for different owner names
    stringstream ss;
    const char* const soa_txt = "example.org. 300 IN SOA . . 0 0 0 0 0\n";
    const char* const soa_sig_txt = "example.org. 300 IN RRSIG SOA 5 3 300 "
        "20000101000000 20000201000000 12345 example.org. FAKEFAKE\n";
    const char* const a_txt =
        "ns1.example.org. 300 IN A 192.0.2.1\n"
        "ns1.example.org. 300 IN A 192.0.2.2\n";
    const char* const a_sig_txt = "ns1.example.org. 300 IN RRSIG A 5 3 300 "
        "20000101000000 20000201000000 12345 example.org. FAKEFAKE\n";
    ss << soa_txt << soa_sig_txt << a_txt << a_sig_txt;
    shared_ptr<DataSourceClient> db_client = unittest::createSQLite3Client(
        class_, origin_, TEST_DATA_BUILDDIR "/contexttest.sqlite3.copied", ss);
    zone_finder_.load(*db_client->getIterator(origin_));

    // The new content should be visible, including the previously-nonexistent
    // SOA.
    RRsetPtr expected_answer = textToRRset(soa_txt, RRClass::IN(), origin_);
    expected_answer->addRRsig(textToRRset(soa_sig_txt));
    findTest(origin_, RRType::SOA(), ZoneFinder::SUCCESS, true,
             expected_answer, ZoneFinder::RESULT_DEFAULT, NULL,
             ZoneFinder::FIND_DNSSEC);

    expected_answer = textToRRset(a_txt);
    expected_answer->addRRsig(textToRRset(a_sig_txt));
    findTest(Name("ns1.example.org"), RRType::A(), ZoneFinder::SUCCESS, true,
             expected_answer, ZoneFinder::RESULT_DEFAULT, NULL,
             ZoneFinder::FIND_DNSSEC);

    // File name should be (re)set to empty.
    EXPECT_TRUE(zone_finder_.getFileName().empty());

    // Loading the zone with an iterator separating RRs of the same RRset
    // will fail because the resulting sequence doesn't meet assumptions of
    // the (current) in-memory implementation.
    EXPECT_THROW(zone_finder_.load(*db_client->getIterator(origin_, true)),
                 MasterLoadError);

    // Load the zone from a file that contains more realistic data (borrowed
    // from a different test).  There's nothing special in this case for the
    // purpose of this test, so it should just succeed.
    db_client = unittest::createSQLite3Client(
        class_, origin_, TEST_DATA_BUILDDIR "/contexttest.sqlite3.copied",
        TEST_DATA_DIR "/contexttest.zone");
    zone_finder_.load(*db_client->getIterator(origin_));

    // just checking a couple of RRs in the new version of zone.
    findTest(Name("mx1.example.org"), RRType::A(), ZoneFinder::SUCCESS, true,
             textToRRset("mx1.example.org. 3600 IN A 192.0.2.10"));
    findTest(Name("ns1.example.org"), RRType::AAAA(), ZoneFinder::SUCCESS,
             true, textToRRset("ns1.example.org. 3600 IN AAAA 2001:db8::1"));
}

/*
 * Test that puts a (simple) wildcard into the zone and checks we can
 * correctly find the data.
 */
void
InMemoryZoneFinderTest::wildcardCheck(
    ZoneFinder::FindResultFlags expected_flags,
    ZoneFinder::FindOptions find_options)
{
    /*
     *            example.org.
     *                 |
     *             [cname]wild (not *.wild, should have wild mark)
     *                 |
     *                 *
     */

    // If the zone is "signed" (detecting it by the NSEC/NSEC3 signed flags),
    // add RRSIGs to the records.
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0 ||
        (expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0) {
        // Convenience shortcut.  The RDATA is not really validatable, but
        // it doesn't matter for our tests.
        const char* const rrsig_common = "5 3 3600 "
            "20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE";

        find_options = find_options | ZoneFinder::FIND_DNSSEC;
        rr_wild_->addRRsig(textToRRset("*.wild.example.org. 300 IN RRSIG A " +
                                       string(rrsig_common)));
        rr_cnamewild_->addRRsig(textToRRset("*.cnamewild.example.org. 300 IN "
                                            "RRSIG CNAME " +
                                            string(rrsig_common)));
    }
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_wild_));
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_cnamewild_));
    // If the zone is expected to be "signed" with NSEC3, add an NSEC3.
    // (the content of the NSEC3 shouldn't matter)
    if ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0) {
        EXPECT_EQ(SUCCESS, zone_finder_.add(rr_nsec3_));
    }
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        EXPECT_EQ(SUCCESS, zone_finder_.add(rr_nsec_));
    }

    // Search at the parent. The parent will not have the A, but it will
    // be in the wildcard (so check the wildcard isn't matched at the parent)
    {
        SCOPED_TRACE("Search at parent");
        if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
            findTest(Name("wild.example.org"), RRType::A(),
                     ZoneFinder::NXRRSET, true, rr_nsec_, expected_flags,
                     NULL, find_options);
        } else {
            findTest(Name("wild.example.org"), RRType::A(),
                     ZoneFinder::NXRRSET, true, ConstRRsetPtr(),
                     expected_flags, NULL, find_options);
        }
    }

    // For the test setup of "NSEC-signed" zone, we might expect it will
    // be returned with a negative result, either because wildcard match is
    // disabled by the search option or because wildcard match is canceled
    // per protocol.
    ConstRRsetPtr expected_nsec; // by default it's NULL
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0 &&
        (find_options & ZoneFinder::FIND_DNSSEC) != 0) {
        expected_nsec = rr_nsec_;
    }
    // Explicitly converting the following to const pointers; some compilers
    // would complain about mixed use of const and non const in ?: below.
    const ConstRRsetPtr rr_wild = rr_wild_;
    const ConstRRsetPtr rr_cnamewild = rr_cnamewild_;

    // Search the original name of wildcard
    {
        SCOPED_TRACE("Search directly at *");
        findTest(Name("*.wild.example.org"), RRType::A(), ZoneFinder::SUCCESS,
                 true, rr_wild_, ZoneFinder::RESULT_DEFAULT, NULL,
                 find_options);
    }

    // Below some of the test cases will normally result in a wildcard match;
    // if NO_WILDCARD is specified, it should result in NXDOMAIN instead,
    // and, when available and requested, the covering NSEC will be returned.
    // The following are shortcut parameters to unify these cases.
    const bool wild_ok = ((find_options & ZoneFinder::NO_WILDCARD) == 0);
    const ZoneFinder::FindResultFlags wild_expected_flags =
        wild_ok ? (ZoneFinder::RESULT_WILDCARD | expected_flags) :
        expected_flags;

    // Search "created" name.
    {
        SCOPED_TRACE("Search at created child");
        findTest(Name("a.wild.example.org"), RRType::A(),
                 wild_ok ? ZoneFinder::SUCCESS : ZoneFinder::NXDOMAIN, false,
                 wild_ok ? rr_wild : expected_nsec,
                 wild_expected_flags, NULL, find_options, wild_ok);
    }

    // Search name that has CNAME.
    {
        SCOPED_TRACE("Matching CNAME");
        findTest(Name("a.cnamewild.example.org"), RRType::A(),
                 wild_ok ? ZoneFinder::CNAME : ZoneFinder::NXDOMAIN, false,
                 wild_ok ? rr_cnamewild : expected_nsec,
                 wild_expected_flags, NULL, find_options, wild_ok);
    }

    // Search another created name, this time little bit lower
    {
        SCOPED_TRACE("Search at created grand-child");
        findTest(Name("a.b.wild.example.org"), RRType::A(),
                 wild_ok ? ZoneFinder::SUCCESS : ZoneFinder::NXDOMAIN, false,
                 wild_ok ? rr_wild : expected_nsec,
                 wild_expected_flags, NULL, find_options, wild_ok);
    }

    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_under_wild_));
    {
        SCOPED_TRACE("Search under non-wildcard");
        findTest(Name("bar.foo.wild.example.org"), RRType::A(),
                 ZoneFinder::NXDOMAIN, true, expected_nsec, expected_flags,
                 NULL, find_options);
    }

    // Wildcard match, but no data.  We add the additional NSEC at the wildcard
    // at this point so that it wouldn't break other tests above.  Note also
    // that in the NO_WILDCARD case the resulting NSEC is the same.  Ideally
    // we could use a more tricky setup so we can distinguish these cases,
    // but for this purpose it's not bad; what we'd like to test here is that
    // wildcard substitution doesn't happen for either case, and the
    // NO_WILDCARD effect itself can be checked by the result code (NXDOMAIN).
    ConstRRsetPtr expected_wild_nsec; // by default it's NULL
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        EXPECT_EQ(SUCCESS, zone_finder_.add(rr_wild_nsec_));
        expected_wild_nsec = rr_wild_nsec_;
    }
    {
        SCOPED_TRACE("Search at wildcard, no data");
        findTest(Name("a.wild.example.org"), RRType::AAAA(),
                 wild_ok ? ZoneFinder::NXRRSET : ZoneFinder::NXDOMAIN, true,
                 wild_ok ? expected_wild_nsec : expected_wild_nsec,
                 wild_expected_flags, NULL, find_options);
    }
}

TEST_F(InMemoryZoneFinderTest, wildcard) {
    // Normal case
    wildcardCheck();
}

TEST_F(InMemoryZoneFinderTest, wildcardNSEC3) {
    // Similar to the previous one, but the zone signed with NSEC3
    wildcardCheck(ZoneFinder::RESULT_NSEC3_SIGNED);
}

TEST_F(InMemoryZoneFinderTest, wildcardNSEC) {
    // Similar to the previous one, but the zone is signed with NSEC
    wildcardCheck(ZoneFinder::RESULT_NSEC_SIGNED);
}

TEST_F(InMemoryZoneFinderTest, wildcardDisabledWithNSEC) {
    // Wildcard is disabled.  In practice, this is used as part of query
    // processing for an NSEC-signed zone, so we test that case specifically.
    wildcardCheck(ZoneFinder::RESULT_NSEC_SIGNED, ZoneFinder::NO_WILDCARD);
}

TEST_F(InMemoryZoneFinderTest, wildcardDisabledWithoutNSEC) {
    // Similar to the previous once, but check the behavior for a non signed
    // zone just in case.
    wildcardCheck(ZoneFinder::RESULT_DEFAULT, ZoneFinder::NO_WILDCARD);
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
                 ZoneFinder::DELEGATION, true, rr_child_ns_,
                 ZoneFinder::RESULT_DEFAULT, NULL, ZoneFinder::FIND_GLUE_OK);
    }
}

// Tests combination of wildcard and ANY.
void
InMemoryZoneFinderTest::anyWildcardCheck(
    ZoneFinder::FindResultFlags expected_flags)
{
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_wild_));
    if ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0) {
        EXPECT_EQ(SUCCESS, zone_finder_.add(rr_nsec3_));
    }
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        EXPECT_EQ(SUCCESS, zone_finder_.add(rr_nsec_));
    }

    vector<ConstRRsetPtr> expected_sets;

    // First try directly the name (normal match)
    {
        SCOPED_TRACE("Asking directly for *");
        expected_sets.push_back(rr_wild_);
        findAllTest(Name("*.wild.example.org"), ZoneFinder::SUCCESS,
                    expected_sets);
    }

    // Then a wildcard match
    {
        SCOPED_TRACE("Asking in the wild way");
        expected_sets.clear();
        RRsetPtr expected(new RRset(Name("a.wild.example.org"),
                                    rr_wild_->getClass(), rr_wild_->getType(),
                                    rr_wild_->getTTL()));
        expected->addRdata(rr_wild_->getRdataIterator()->getCurrent());
        expected_sets.push_back(expected);
        findAllTest(Name("a.wild.example.org"), ZoneFinder::SUCCESS,
                    expected_sets,
                    ZoneFinder::RESULT_WILDCARD | expected_flags);
    }
}

TEST_F(InMemoryZoneFinderTest, anyWildcard) {
    anyWildcardCheck();
}

TEST_F(InMemoryZoneFinderTest, anyWildcardNSEC3) {
    anyWildcardCheck(ZoneFinder::RESULT_NSEC3_SIGNED);
}

TEST_F(InMemoryZoneFinderTest, anyWildcardNSEC) {
    anyWildcardCheck(ZoneFinder::RESULT_NSEC_SIGNED);
}

// Test there's nothing in the wildcard in the middle if we load
// wild.*.foo.example.org.
void
InMemoryZoneFinderTest::emptyWildcardCheck(
    ZoneFinder::FindResultFlags expected_flags)
{
    /*
     *            example.org.
     *                foo
     *                 *
     *               wild
     */
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_emptywild_));
    if ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0) {
        EXPECT_EQ(SUCCESS, zone_finder_.add(rr_nsec3_));
    }
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        EXPECT_EQ(SUCCESS, zone_finder_.add(rr_nsec_));
    }

    {
        SCOPED_TRACE("Asking for the original record under wildcard");
        findTest(Name("wild.*.foo.example.org"), RRType::A(),
                 ZoneFinder::SUCCESS, true, rr_emptywild_);
    }

    {
        SCOPED_TRACE("Asking for A record");
        findTest(Name("a.foo.example.org"), RRType::A(), ZoneFinder::NXRRSET,
                 true, ConstRRsetPtr(),
                 ZoneFinder::RESULT_WILDCARD | expected_flags);
        findTest(Name("*.foo.example.org"), RRType::A(), ZoneFinder::NXRRSET,
                 true, ConstRRsetPtr(), expected_flags);
        findTest(Name("foo.example.org"), RRType::A(), ZoneFinder::NXRRSET,
                 true, ConstRRsetPtr(), expected_flags);
    }

    {
        SCOPED_TRACE("Asking for ANY record");
        findAllTest(Name("*.foo.example.org"), ZoneFinder::NXRRSET,
                    vector<ConstRRsetPtr>(), expected_flags);

        findAllTest(Name("a.foo.example.org"), ZoneFinder::NXRRSET,
                    vector<ConstRRsetPtr>(),
                    ZoneFinder::RESULT_WILDCARD | expected_flags);
    }

    {
        SCOPED_TRACE("Asking on the non-terminal");
        findTest(Name("wild.bar.foo.example.org"), RRType::A(),
                 ZoneFinder::NXRRSET, true, ConstRRsetPtr(),
                 ZoneFinder::RESULT_WILDCARD | expected_flags);
    }
}

TEST_F(InMemoryZoneFinderTest, emptyWildcard) {
    emptyWildcardCheck();
}

TEST_F(InMemoryZoneFinderTest, emptyWildcardNSEC3) {
    emptyWildcardCheck(ZoneFinder::RESULT_NSEC3_SIGNED);
}

TEST_F(InMemoryZoneFinderTest, emptyWildcardNSEC) {
    emptyWildcardCheck(ZoneFinder::RESULT_NSEC_SIGNED);
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
            findTest(Name(*name), RRType::A(), ZoneFinder::NXRRSET, true,
                     ConstRRsetPtr(), ZoneFinder::RESULT_WILDCARD);
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

            findAllTest(Name(*name), ZoneFinder::NXRRSET,
                        vector<ConstRRsetPtr>());
        }
    }
}

// We run this part twice from the below test, in two slightly different
// situations
void
InMemoryZoneFinderTest::doCancelWildcardCheck(
    ZoneFinder::FindResultFlags expected_flags,
    ZoneFinder::FindOptions find_options)
{
    // These should be canceled
    {
        SCOPED_TRACE("Canceled under foo.wild.example.org");

        // For an NSEC-signed zone with DNSSEC requested, the covering NSEC
        // should be returned.  The expected NSEC is actually just the only
        // NSEC in the test data, but in this context it doesn't matter;
        // it's sufficient just to check any NSEC is returned (or not).
        ConstRRsetPtr expected_nsec; // by default it's NULL
        if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0 &&
            (find_options & ZoneFinder::FIND_DNSSEC)) {
            expected_nsec = rr_nsec_;
        }

        findTest(Name("aaa.foo.wild.example.org"), RRType::A(),
                 ZoneFinder::NXDOMAIN, true, expected_nsec, expected_flags,
                 NULL, find_options);
        findTest(Name("zzz.foo.wild.example.org"), RRType::A(),
                 ZoneFinder::NXDOMAIN, true, expected_nsec, expected_flags,
                 NULL, find_options);
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
                     rr_wild_,
                     ZoneFinder::RESULT_WILDCARD | expected_flags, NULL,
                     ZoneFinder::FIND_DEFAULT, true);
        }
    }

    // This shouldn't be wildcarded, it's an existing domain
    {
        SCOPED_TRACE("The foo.wild.example.org itself");
        findTest(Name("foo.wild.example.org"), RRType::A(),
                 ZoneFinder::NXRRSET, true, ConstRRsetPtr(), expected_flags);
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
        doCancelWildcardCheck();
    }

    // Try putting another one under foo.wild....
    // The result should be the same but it will be done in another way in the
    // code, because the foo.wild.example.org will exist in the tree.
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_not_wild_another_));
    {
        SCOPED_TRACE("Runnig with two entries under foo.wild.example.org");
        doCancelWildcardCheck();
    }
}

// Same tests as cancelWildcard for NSEC3-signed zone
TEST_F(InMemoryZoneFinderTest, cancelWildcardNSEC3) {
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_wild_));
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_not_wild_));
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_nsec3_));

    {
        SCOPED_TRACE("Runnig with single entry under foo.wild.example.org");
        doCancelWildcardCheck(ZoneFinder::RESULT_NSEC3_SIGNED);
    }
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_not_wild_another_));
    {
        SCOPED_TRACE("Runnig with two entries under foo.wild.example.org");
        doCancelWildcardCheck(ZoneFinder::RESULT_NSEC3_SIGNED);
    }
}

// Same tests as cancelWildcard for NSEC-signed zone.  Check both cases with
// or without FIND_DNSSEC option.  NSEC should be returned only when the option
// is given.
TEST_F(InMemoryZoneFinderTest, cancelWildcardNSEC) {
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_wild_));
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_not_wild_));
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_nsec_));

    {
        SCOPED_TRACE("Runnig with single entry under foo.wild.example.org");
        doCancelWildcardCheck(ZoneFinder::RESULT_NSEC_SIGNED,
                              ZoneFinder::FIND_DNSSEC);
        doCancelWildcardCheck(ZoneFinder::RESULT_NSEC_SIGNED);
    }
    EXPECT_EQ(SUCCESS, zone_finder_.add(rr_not_wild_another_));
    {
        SCOPED_TRACE("Runnig with two entries under foo.wild.example.org");
        doCancelWildcardCheck(ZoneFinder::RESULT_NSEC_SIGNED,
                              ZoneFinder::FIND_DNSSEC);
        doCancelWildcardCheck(ZoneFinder::RESULT_NSEC_SIGNED);
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
    EXPECT_THROW(finder1.find(origin_, RRType::NS()), OutOfZone);
    findTest(other_origin, RRType::TXT(), ZoneFinder::SUCCESS, false,
             ConstRRsetPtr(), ZoneFinder::RESULT_DEFAULT, &finder1);
    findTest(origin_, RRType::NS(), ZoneFinder::SUCCESS, false,
             ConstRRsetPtr(), ZoneFinder::RESULT_DEFAULT, &finder2);
    EXPECT_THROW(finder2.find(other_origin, RRType::TXT()), OutOfZone);
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
    ZoneFinderContextPtr result = zone_finder_.find(origin_, RRType::A(),
                                                    ZoneFinder::FIND_DNSSEC);
    EXPECT_EQ(ZoneFinder::SUCCESS, result->code);
    ASSERT_TRUE(result->rrset);
    ASSERT_TRUE(result->rrset->getRRsig());
    actual_rrsets_.push_back(result->rrset->getRRsig());
    rrsetsCheck(rrsig_a_txt, actual_rrsets_.begin(), actual_rrsets_.end());

    // Confirm a separate RRISG for a different type can be added
    actual_rrsets_.clear();
    zone_finder_.add(rr_ns_);
    zone_finder_.add(textToRRset(rrsig_ns_txt));
    result = zone_finder_.find(origin_, RRType::NS(), ZoneFinder::FIND_DNSSEC);
    EXPECT_EQ(ZoneFinder::SUCCESS, result->code);
    ASSERT_TRUE(result->rrset);
    ASSERT_TRUE(result->rrset->getRRsig());
    actual_rrsets_.push_back(result->rrset->getRRsig());
    rrsetsCheck(rrsig_ns_txt, actual_rrsets_.begin(), actual_rrsets_.end());

    // Check a case with multiple RRSIGs
    actual_rrsets_.clear();
    zone_finder_.add(rr_ns_aaaa_);
    zone_finder_.add(textToRRset(rrsig_aaaa_txt));
    result = zone_finder_.find(Name("ns.example.org"), RRType::AAAA(),
                               ZoneFinder::FIND_DNSSEC);
    EXPECT_EQ(ZoneFinder::SUCCESS, result->code);
    ASSERT_TRUE(result->rrset);
    ASSERT_TRUE(result->rrset->getRRsig());
    actual_rrsets_.push_back(result->rrset->getRRsig());
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

TEST_F(InMemoryZoneFinderTest, addNSEC3) {
    // Set up the faked hash calculator.
    setNSEC3HashCreator(&nsec3_hash_creator_);

    const string nsec3_text = string(apex_hash) + ".example.org." +
        string(nsec3_common);
    // This name shouldn't be found in the normal domain tree.
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(textToRRset(nsec3_text)));
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              zone_finder_.find(Name(string(apex_hash) + ".example.org"),
                                RRType::NSEC3())->code);
    // Dedicated NSEC3 find should be able to find it.
    findNSEC3Check(true, origin_.getLabelCount(), nsec3_text, "",
                   zone_finder_.findNSEC3(Name("example.org"), false));

    // This implementation rejects duplicate/update add of the same hash name
    EXPECT_EQ(result::EXIST,
              zone_finder_.add(textToRRset(
                                   string(apex_hash) + ".example.org." +
                                   string(nsec3_common) + " AAAA")));
    // The original NSEC3 should be intact
    findNSEC3Check(true, origin_.getLabelCount(), nsec3_text, "",
                   zone_finder_.findNSEC3(Name("example.org"), false));

    // NSEC3-like name but of ordinary RR type should go to normal tree.
    const string nonsec3_text = string(apex_hash) + ".example.org. " +
        "300 IN A 192.0.2.1";
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(textToRRset(nonsec3_text)));
    EXPECT_EQ(ZoneFinder::SUCCESS,
              zone_finder_.find(Name(string(apex_hash) + ".example.org"),
                                RRType::A())->code);
}

TEST_F(InMemoryZoneFinderTest, addNSEC3Lower) {
    // Set up the faked hash calculator.
    setNSEC3HashCreator(&nsec3_hash_creator_);

    // Similar to the previous case, but NSEC3 owner name is lower-cased.
    const string nsec3_text = string(apex_hash_lower) + ".example.org." +
        string(nsec3_common);
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(textToRRset(nsec3_text)));
    findNSEC3Check(true, origin_.getLabelCount(), nsec3_text, "",
                   zone_finder_.findNSEC3(Name("example.org"), false));
}

TEST_F(InMemoryZoneFinderTest, addNSEC3Ordering) {
    // Set up the faked hash calculator.
    setNSEC3HashCreator(&nsec3_hash_creator_);

    // Check that the internal storage ensures comparison based on the NSEC3
    // semantics, regardless of the add order or the letter-case of hash.

    // Adding "0P..", "2v..", then "2T..".
    const string smallest = string(apex_hash) + ".example.org." +
        string(nsec3_common);
    const string middle = string(ns1_hash) + ".example.org." +
        string(nsec3_common);
    const string largest = string(xyw_hash) + ".example.org." +
        string(nsec3_common);
    zone_finder_.add(textToRRset(smallest));
    zone_finder_.add(textToRRset(largest));
    zone_finder_.add(textToRRset(middle));

    // Then look for NSEC3 that covers a name whose hash is "2S.."
    // The covering NSEC3 should be "0P.."
    findNSEC3Check(false, 4, smallest, "",
                   zone_finder_.findNSEC3(Name("www.example.org"), false));

    // Look for NSEC3 that covers names whose hash are "Q0.." and "0A.."
    // The covering NSEC3 should be "2v.." in both cases
    findNSEC3Check(false, 4, largest, "",
                   zone_finder_.findNSEC3(Name("xxx.example.org"), false));
    findNSEC3Check(false, 4, largest, "",
                   zone_finder_.findNSEC3(Name("yyy.example.org"), false));
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
}

TEST_F(InMemoryZoneFinderTest, addMultiNSEC3) {
    // In this current implementation multiple NSEC3 RDATA isn't supported.
    RRsetPtr nsec3(new RRset(Name(string(apex_hash) + ".example.org"),
                             RRClass::IN(), RRType::NSEC3(), RRTTL(300)));
    nsec3->addRdata(
        generic::NSEC3("1 0 12 aabbccdd 2T7B4G4VSA5SMI47K61MV5BV1A22BOJR A"));
    nsec3->addRdata(
        generic::NSEC3("1 1 1 ddccbbaa 2T7B4G4VSA5SMI47K61MV5BV1A22BOJR A"));
    EXPECT_THROW(zone_finder_.add(nsec3), InMemoryZoneFinder::AddError);
}

TEST_F(InMemoryZoneFinderTest, addNSEC3WithRRSIG) {
    // Set up the faked hash calculator.
    setNSEC3HashCreator(&nsec3_hash_creator_);

    // Adding NSEC3 and its RRSIG
    const string nsec3_text = string(apex_hash) + ".example.org." +
        string(nsec3_common);
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(textToRRset(nsec3_text)));
    const string nsec3_rrsig_text = string(apex_hash) + ".example.org." +
        string(nsec3_rrsig_common);
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(textToRRset(nsec3_rrsig_text)));

    // Then look for it.  The NSEC3 should have the RRSIG that was just added.
    findNSEC3Check(true, origin_.getLabelCount(),
                   nsec3_text + "\n" + nsec3_rrsig_text, "",
                   zone_finder_.findNSEC3(Name("example.org"), false));

    // Duplicate add of RRSIG for the same NSEC3 is prohibited.
    EXPECT_THROW(zone_finder_.add(textToRRset(nsec3_rrsig_text)),
                 InMemoryZoneFinder::AddError);

    // Same check using the lower-cased name.  This also confirms matching
    // is case-insensitive.
    EXPECT_THROW(zone_finder_.add(textToRRset(string(apex_hash_lower) +
                                              ".example.org."
                                              + string(nsec3_rrsig_common))),
                 InMemoryZoneFinder::AddError);
}

TEST_F(InMemoryZoneFinderTest, badRRsigForNSEC3) {
    // adding RRSIG for NSEC3 even before adding any NSEC3 (internally,
    // a space for NSEC3 namespace isn't yet allocated)
    EXPECT_THROW(zone_finder_.add(textToRRset(string(apex_hash) +
                                              ".example.org." +
                                              string(nsec3_rrsig_common))),
                 InMemoryZoneFinder::AddError);

    // Add an NSEC3
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(
                  textToRRset(string(apex_hash) + ".example.org." +
                              string(nsec3_common))));

    // Then add an NSEC3 for a non existent NSEC3.  It should fail in the
    // current implementation.
    EXPECT_THROW(zone_finder_.add(textToRRset(string(ns1_hash) +
                                              ".example.org." +
                                              string(nsec3_rrsig_common))),
                 InMemoryZoneFinder::AddError);
}

TEST_F(InMemoryZoneFinderTest, paramConsistencyWithNSEC3PARAM) {
    // First, add an NSEC3PARAM RR
    EXPECT_EQ(result::SUCCESS,
              zone_finder_.add(textToRRset("example.org. 300 IN NSEC3PARAM "
                                           "1 0 12 aabbccdd")));
    // Adding an NSEC3 that has matching parameters is okay.
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(
                  textToRRset(string(apex_hash) + ".example.org." +
                              string(nsec3_common))));
    // NSEC3 with inconsistent parameter will be rejected
    EXPECT_THROW(zone_finder_.add(
                     textToRRset("a.example.org. 300 IN NSEC3 1 0 1 aabbccdd "
                                 "2T7B4G4VSA5SMI47K61MV5BV1A22BOJR A RRSIG")),
                 InMemoryZoneFinder::AddError);
}

TEST_F(InMemoryZoneFinderTest, paramConsistencyWithNSEC3) {
    // Add an NSEC3 without adding NSEC3PARAM
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(
                  textToRRset(string(apex_hash) + ".example.org." +
                              string(nsec3_common))));
    // Adding an NSEC3 with inconsistent parameter will be rejected at this pt.
    EXPECT_THROW(zone_finder_.add(
                     textToRRset("a.example.org. 300 IN NSEC3 1 0 1 aabbccdd "
                                 "2T7B4G4VSA5SMI47K61MV5BV1A22BOJR A RRSIG")),
                 InMemoryZoneFinder::AddError);

    // Likewise, NSEC3PARAM with inconsistent parameter will be rejected.
    EXPECT_THROW(zone_finder_.add(textToRRset("example.org. 300 IN NSEC3PARAM "
                                              "1 0 1 aabbccdd")),
                 InMemoryZoneFinder::AddError);
}

TEST_F(InMemoryZoneFinderTest, multiNSEC3PARAM) {
    // In this current implementation multiple NSEC3PARAM isn't supported.
    RRsetPtr nsec3param(new RRset(Name("example.org"), RRClass::IN(),
                                  RRType::NSEC3PARAM(), RRTTL(300)));
    nsec3param->addRdata(generic::NSEC3PARAM("1 0 12 aabbccdd"));
    nsec3param->addRdata(generic::NSEC3PARAM("1 1 1 ddccbbaa"));
    EXPECT_THROW(zone_finder_.add(nsec3param), InMemoryZoneFinder::AddError);
}

TEST_F(InMemoryZoneFinderTest, nonOriginNSEC3PARAM) {
    // This is a normal NSEC3PARAM at the zone origin
    EXPECT_EQ(result::SUCCESS,
              zone_finder_.add(textToRRset("example.org. 300 IN NSEC3PARAM "
                                           "1 0 12 aabbccdd")));
    // Add another (with different param) at a non origin node.  This is
    // awkward, but the implementation accepts it as an ordinary RR.
    EXPECT_EQ(result::SUCCESS,
              zone_finder_.add(textToRRset("a.example.org. 300 IN NSEC3PARAM "
                                           "1 1 1 aabbccdd")));
}

TEST_F(InMemoryZoneFinderTest, loadNSEC3Zone) {
    // Check if it can load validly NSEC3-signed zone.  At this moment
    // it's sufficient to see it doesn't crash
    zone_finder_.load(TEST_DATA_DIR "/example.org.nsec3-signed");

    // Reload the zone with a version that doesn't have NSEC3PARAM.
    // This is an abnormal case, but the implementation accepts it.
    zone_finder_.load(TEST_DATA_DIR "/example.org.nsec3-signed-noparam");
}

// This test checks that the NSEC3 names don't really exist in the real
// namespace.
TEST_F(InMemoryZoneFinderTest, queryToNSEC3Name) {
    // Add the NSEC3 and NSEC3PARAM there.
    EXPECT_EQ(result::SUCCESS,
              zone_finder_.add(textToRRset("example.org. 300 IN NSEC3PARAM "
                                           "1 0 12 aabbccdd")));
    const Name nsec3domain(string(apex_hash) + ".example.org.");
    // Adding an NSEC3 that has matching parameters is okay.
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(
                  textToRRset(string(apex_hash) + ".example.org." +
                              string(nsec3_common))));
    // Now, the domain should not exist
    findTest(nsec3domain, RRType::AAAA(), ZoneFinder::NXDOMAIN, false,
             ConstRRsetPtr(), ZoneFinder::RESULT_NSEC3_SIGNED, &zone_finder_,
             ZoneFinder::FIND_DNSSEC);
    // If we add an A record, the domain should exist
    ConstRRsetPtr rrset(textToRRset(string(apex_hash) +
                                    ".example.org. 300 IN A 192.0.2.1"));
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(rrset));
    // Searching for a different RRType will tell us this RRset doesn't exist
    findTest(nsec3domain, RRType::AAAA(), ZoneFinder::NXRRSET, false,
             ConstRRsetPtr(), ZoneFinder::RESULT_NSEC3_SIGNED, &zone_finder_,
             ZoneFinder::FIND_DNSSEC);
    // Searching for the A record would find it
    findTest(nsec3domain, RRType::A(), ZoneFinder::SUCCESS, true,
             rrset, ZoneFinder::RESULT_DEFAULT, &zone_finder_,
             ZoneFinder::FIND_DNSSEC);
}

// Continuation of the previous test (queryToNSEC3Name), we check we don't break
// the empty nonterminal case by existence of NSEC3 record with that name.
TEST_F(InMemoryZoneFinderTest, queryToNSEC3NameNonterminal) {
    // Add the NSEC3 and NSEC3PARAM there.
    EXPECT_EQ(result::SUCCESS,
              zone_finder_.add(textToRRset("example.org. 300 IN NSEC3PARAM "
                                           "1 0 12 aabbccdd")));
    const Name nsec3domain(string(apex_hash) + ".example.org.");
    // Adding an NSEC3 that has matching parameters is okay.
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(
                  textToRRset(string(apex_hash) + ".example.org." +
                              string(nsec3_common))));
    // Something below the name
    ConstRRsetPtr rrset(textToRRset("below." + string(apex_hash) +
                                    ".example.org. 300 IN A 192.0.2.1"));
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(rrset));
    // Now, the node is empty non-terminal.
    findTest(nsec3domain, RRType::AAAA(), ZoneFinder::NXRRSET, false,
             ConstRRsetPtr(), ZoneFinder::RESULT_NSEC3_SIGNED, &zone_finder_,
             ZoneFinder::FIND_DNSSEC);
}

TEST_F(InMemoryZoneFinderTest, findNSEC3) {
    // Set up the faked hash calculator.
    setNSEC3HashCreator(&nsec3_hash_creator_);

    // Add a few NSEC3 records:
    // apex (example.org.): hash=0P..
    // ns1.example.org:     hash=2T..
    // w.example.org:       hash=01..
    // zzz.example.org:     hash=R5..
    const string apex_nsec3_text = string(apex_hash) + ".example.org." +
        string(nsec3_common);
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(textToRRset(apex_nsec3_text)));
    const string ns1_nsec3_text = string(ns1_hash) + ".example.org." +
        string(nsec3_common);
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(textToRRset(ns1_nsec3_text)));
    const string w_nsec3_text = string(w_hash) + ".example.org." +
        string(nsec3_common);
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(textToRRset(w_nsec3_text)));
    const string zzz_nsec3_text = string(zzz_hash) + ".example.org." +
        string(nsec3_common);
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(textToRRset(zzz_nsec3_text)));

    performNSEC3Test(zone_finder_);
}

TEST_F(InMemoryZoneFinderTest, findNSEC3ForBadZone) {
    // Set up the faked hash calculator.
    setNSEC3HashCreator(&nsec3_hash_creator_);

    // If the zone has nothing about NSEC3 (neither NSEC3 or NSEC3PARAM),
    // findNSEC3() should be rejected.
    EXPECT_THROW(zone_finder_.findNSEC3(Name("www.example.org"), true),
                 DataSourceError);

    // Only having NSEC3PARAM isn't enough
    EXPECT_EQ(result::SUCCESS,
              zone_finder_.add(textToRRset("example.org. 300 IN NSEC3PARAM "
                                           "1 0 12 aabbccdd")));
    EXPECT_THROW(zone_finder_.findNSEC3(Name("www.example.org"), true),
                 DataSourceError);

    // Unless NSEC3 for apex is added the result in the recursive mode
    // is guaranteed.
    const string ns1_nsec3_text = string(ns1_hash) + ".example.org." +
        string(nsec3_common);
    EXPECT_EQ(result::SUCCESS, zone_finder_.add(textToRRset(ns1_nsec3_text)));
    EXPECT_THROW(zone_finder_.findNSEC3(Name("www.example.org"), true),
                 DataSourceError);
}

TEST_F(InMemoryZoneFinderTest, loadAndFindNSEC3) {
    // Using more realistic example, borrowed from RFC5155, with compliant
    // hash calculator.  We only confirm the data source can load it
    // successfully and find correct NSEC3 RRs for some selected cases
    // (detailed tests have been done above).

    InMemoryZoneFinder finder(class_, Name("example"));
    finder.load(TEST_DATA_COMMONDIR "/rfc5155-example.zone.signed");

    // See RFC5155 B.1
    ZoneFinder::FindNSEC3Result result1 =
        finder.findNSEC3(Name("c.x.w.example"), true);
    ASSERT_TRUE(result1.closest_proof);
    // We compare closest_labels as int so the error report will be more
    // readable in case it fails.
    EXPECT_EQ(4, static_cast<int>(result1.closest_labels));
    EXPECT_EQ(Name("b4um86eghhds6nea196smvmlo4ors995.example"),
              result1.closest_proof->getName());
    ASSERT_TRUE(result1.next_proof);
    EXPECT_EQ(Name("0p9mhaveqvm6t7vbl5lop2u3t2rp3tom.example"),
              result1.next_proof->getName());

    // See RFC5155 B.2.
    ZoneFinder::FindNSEC3Result result2 =
        finder.findNSEC3(Name("ns1.example"), true);
    ASSERT_TRUE(result2.closest_proof);
    EXPECT_EQ(3, static_cast<int>(result2.closest_labels));
    EXPECT_EQ(Name("2t7b4g4vsa5smi47k61mv5bv1a22bojr.example"),
              result2.closest_proof->getName());
    ASSERT_FALSE(result2.next_proof);

    // See RFC5155 B.5.
    ZoneFinder::FindNSEC3Result result3 =
        finder.findNSEC3(Name("a.z.w.example"), true);
    ASSERT_TRUE(result3.closest_proof);
    EXPECT_EQ(3, static_cast<int>(result3.closest_labels));
    EXPECT_EQ(Name("k8udemvp1j2f7eg6jebps17vp3n8i58h.example"),
              result3.closest_proof->getName());
    ASSERT_TRUE(result3.next_proof);
    EXPECT_EQ(Name("q04jkcevqvmu85r014c7dkba38o0ji5r.example"),
              result3.next_proof->getName());
}
}
