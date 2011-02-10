// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
// Copyright (C) 2011  CZ NIC
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

#include <gtest/gtest.h>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc;

namespace {
// Commonly used result codes (Who should write the prefix all the time)
using result::SUCCESS;
using result::EXIST;

class MemoryDataSrcTest : public ::testing::Test {
protected:
    MemoryDataSrcTest() : rrclass(RRClass::IN())
    {}
    RRClass rrclass;
    MemoryDataSrc memory_datasrc;
};

TEST_F(MemoryDataSrcTest, add_find_Zone) {
    // test add zone
    // Bogus zone (NULL)
    EXPECT_THROW(memory_datasrc.addZone(ZonePtr()), isc::InvalidParameter);

    // add zones with different names one by one
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::IN(), Name("a")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::CH(), Name("b")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::IN(), Name("c")))));
    // add zones with the same name suffix
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::CH(),
                                         Name("x.d.e.f")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::CH(),
                                         Name("o.w.y.d.e.f")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::CH(),
                                         Name("p.w.y.d.e.f")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::IN(),
                                         Name("q.w.y.d.e.f")))));
    // add super zone and its subzone
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::CH(), Name("g.h")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::IN(), Name("i.g.h")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::IN(),
                                         Name("z.d.e.f")))));
    EXPECT_EQ(result::SUCCESS, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::IN(),
                                         Name("j.z.d.e.f")))));

    // different zone class isn't allowed.
    EXPECT_EQ(result::EXIST, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::CH(),
                                         Name("q.w.y.d.e.f")))));

    // names are compared in a case insensitive manner.
    EXPECT_EQ(result::EXIST, memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(RRClass::IN(),
                                         Name("Q.W.Y.d.E.f")))));

    // test find zone
    EXPECT_EQ(result::SUCCESS, memory_datasrc.findZone(Name("a")).code);
    EXPECT_EQ(Name("a"),
              memory_datasrc.findZone(Name("a")).zone->getOrigin());

    EXPECT_EQ(result::SUCCESS,
              memory_datasrc.findZone(Name("j.z.d.e.f")).code);
    EXPECT_EQ(Name("j.z.d.e.f"),
              memory_datasrc.findZone(Name("j.z.d.e.f")).zone->getOrigin());

    // NOTFOUND
    EXPECT_EQ(result::NOTFOUND, memory_datasrc.findZone(Name("d.e.f")).code);
    EXPECT_EQ(ConstZonePtr(), memory_datasrc.findZone(Name("d.e.f")).zone);

    EXPECT_EQ(result::NOTFOUND,
              memory_datasrc.findZone(Name("w.y.d.e.f")).code);
    EXPECT_EQ(ConstZonePtr(),
              memory_datasrc.findZone(Name("w.y.d.e.f")).zone);

    // there's no exact match.  the result should be the longest match,
    // and the code should be PARTIALMATCH.
    EXPECT_EQ(result::PARTIALMATCH,
              memory_datasrc.findZone(Name("j.g.h")).code);
    EXPECT_EQ(Name("g.h"),
              memory_datasrc.findZone(Name("g.h")).zone->getOrigin());

    EXPECT_EQ(result::PARTIALMATCH,
              memory_datasrc.findZone(Name("z.i.g.h")).code);
    EXPECT_EQ(Name("i.g.h"),
              memory_datasrc.findZone(Name("z.i.g.h")).zone->getOrigin());
}

TEST_F(MemoryDataSrcTest, getZoneCount) {
    EXPECT_EQ(0, memory_datasrc.getZoneCount());
    memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(rrclass, Name("example.com"))));
    EXPECT_EQ(1, memory_datasrc.getZoneCount());

    // duplicate add.  counter shouldn't change
    memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(rrclass, Name("example.com"))));
    EXPECT_EQ(1, memory_datasrc.getZoneCount());

    // add one more
    memory_datasrc.addZone(
                  ZonePtr(new MemoryZone(rrclass, Name("example.org"))));
    EXPECT_EQ(2, memory_datasrc.getZoneCount());
}

// A helper callback of masterLoad() used in MemoryZoneTest.
void
setRRset(RRsetPtr rrset, vector<RRsetPtr*>::iterator& it) {
    *(*it) = rrset;
    ++it;
}

/// \brief Test fixture for the MemoryZone class
class MemoryZoneTest : public ::testing::Test {
    // A straightforward pair of textual RR(set) and a RRsetPtr variable
    // to store the RRset.  Used to build test data below.
    struct RRsetData {
        const char* const text; // textual representation of an RRset
        RRsetPtr* rrset;
    };
public:
    MemoryZoneTest() :
        class_(RRClass::IN()),
        origin_("example.org"),
        zone_(class_, origin_)
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
            {"wild.*.foo.example.org. 300 IN A 192.0.2.1", &rr_emptywild_},
            {"wild.*.foo.*.bar.example.org. 300 IN A 192.0.2.1",
             &rr_nested_emptywild_},
            {"*.nswild.example.org. 300 IN NS nswild.example.", &rr_nswild_},
            {"*.dnamewild.example.org. 300 IN DNAME dnamewild.example.",
             &rr_dnamewild_},
            {"*.child.example.org. 300 IN A 192.0.2.1", &rr_child_wild_},
            {NULL, NULL}
        };

        stringstream zone_data_stream;
        vector<RRsetPtr*> rrsets;
        for (unsigned int i = 0; zone_data[i].text != NULL; ++i) {
            zone_data_stream << zone_data[i].text << "\n";
            rrsets.push_back(zone_data[i].rrset);
        }

        vector<RRsetPtr*>::iterator it = rrsets.begin();
        masterLoad(zone_data_stream, Name::ROOT_NAME(), class_,
                   boost::bind(setRRset, _1, it));
    }
    // Some data to test with
    const RRClass class_;
    const Name origin_;
    // The zone to torture by tests
    MemoryZone zone_;

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
    RRsetPtr rr_child_glue_; // glue RR of the child domain
    RRsetPtr rr_grandchild_ns_; // NS below a zone cut (unusual)
    RRsetPtr rr_grandchild_glue_; // glue RR below a deeper zone cut
    RRsetPtr rr_child_dname_; // A DNAME under NS
    RRsetPtr rr_wild_;
    RRsetPtr rr_emptywild_;
    RRsetPtr rr_nested_emptywild_;
    RRsetPtr rr_nswild_, rr_dnamewild_;
    RRsetPtr rr_child_wild_;

    /**
     * \brief Test one find query to the zone.
     *
     * Asks a query to the zone and checks it does not throw and returns
     * expected results. It returns nothing, it just signals failures
     * to GTEST.
     *
     * \param name The name to ask for.
     * \param rrtype The RRType to ask of.
     * \param result The expected code of the result.
     * \param check_answer Should a check against equality of the answer be
     *     done?
     * \param answer The expected rrset, if any should be returned.
     * \param zone Check different MemoryZone object than zone_ (if NULL,
     *     uses zone_)
     * \param check_wild_answer Checks that the answer has the same RRs, type
     *     class and TTL as the eqxpected answer and that the name corresponds
     *     to the one searched. It is meant for checking answers for wildcard
     *     queries.
     */
    void findTest(const Name& name, const RRType& rrtype, Zone::Result result,
                  bool check_answer = true,
                  const ConstRRsetPtr& answer = ConstRRsetPtr(),
                  RRsetList* target = NULL,
                  MemoryZone* zone = NULL,
                  Zone::FindOptions options = Zone::FIND_DEFAULT,
                  bool check_wild_answer = false)
    {
        if (!zone) {
            zone = &zone_;
        }
        // The whole block is inside, because we need to check the result and
        // we can't assign to FindResult
        EXPECT_NO_THROW({
                Zone::FindResult find_result(zone->find(name, rrtype, target,
                                                        options));
                // Check it returns correct answers
                EXPECT_EQ(result, find_result.code);
                if (check_answer) {
                    EXPECT_EQ(answer, find_result.rrset);
                } else if (check_wild_answer) {
                    RdataIteratorPtr expectedIt(answer->getRdataIterator());
                    RdataIteratorPtr gotIt(answer->getRdataIterator());
                    while (!expectedIt->isLast() && !gotIt->isLast()) {
                        EXPECT_EQ(0, expectedIt->getCurrent().compare(
                            gotIt->getCurrent())) << "The RRs differ ('" <<
                            expectedIt->getCurrent().toText() << "', '" <<
                            gotIt->getCurrent().toText() << "')";
                        expectedIt->next();
                        gotIt->next();
                    }
                    EXPECT_TRUE(expectedIt->isLast()) <<
                        "Result has less RRs than expected";
                    EXPECT_TRUE(gotIt->isLast()) <<
                        "Result has more RRs than expected";
                    EXPECT_EQ(answer->getType(),
                        find_result.rrset->getType());
                    EXPECT_EQ(answer->getType(),
                        find_result.rrset->getType());
                    EXPECT_EQ(answer->getTTL(),
                        find_result.rrset->getTTL());
                    EXPECT_EQ(name, find_result.rrset->getName());
                }
            });
    }
};

/**
 * \brief Test MemoryZone::MemoryZone constructor.
 *
 * Takes the created zone and checks its properties they are the same
 * as passed parameters.
 */
TEST_F(MemoryZoneTest, constructor) {
    ASSERT_EQ(class_, zone_.getClass());
    ASSERT_EQ(origin_, zone_.getOrigin());
}
/**
 * \brief Test adding.
 *
 * We test that it throws at the correct moments and the correct exceptions.
 * And we test the return value.
 */
TEST_F(MemoryZoneTest, add) {
    // This one does not belong to this zone
    EXPECT_THROW(zone_.add(rr_out_), MemoryZone::OutOfZone);
    // Test null pointer
    EXPECT_THROW(zone_.add(ConstRRsetPtr()), MemoryZone::NullRRset);

    // Now put all the data we have there. It should throw nothing
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_a_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_aaaa_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_a_)));

    // Try putting there something twice, it should be rejected
    EXPECT_NO_THROW(EXPECT_EQ(EXIST, zone_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(EXIST, zone_.add(rr_ns_a_)));
}

TEST_F(MemoryZoneTest, addMultipleCNAMEs) {
    rr_cname_->addRdata(generic::CNAME("canonical2.example.org."));
    EXPECT_THROW(zone_.add(rr_cname_), MemoryZone::AddError);
}

TEST_F(MemoryZoneTest, addCNAMEThenOther) {
    EXPECT_EQ(SUCCESS, zone_.add(rr_cname_));
    EXPECT_THROW(zone_.add(rr_cname_a_), MemoryZone::AddError);
}

TEST_F(MemoryZoneTest, addOtherThenCNAME) {
    EXPECT_EQ(SUCCESS, zone_.add(rr_cname_a_));
    EXPECT_THROW(zone_.add(rr_cname_), MemoryZone::AddError);
}

TEST_F(MemoryZoneTest, findCNAME) {
    // install CNAME RR
    EXPECT_EQ(SUCCESS, zone_.add(rr_cname_));

    // Find A RR of the same.  Should match the CNAME
    findTest(rr_cname_->getName(), RRType::NS(), Zone::CNAME, true, rr_cname_);

    // Find the CNAME itself.  Should result in normal SUCCESS
    findTest(rr_cname_->getName(), RRType::CNAME(), Zone::SUCCESS, true,
             rr_cname_);
}

TEST_F(MemoryZoneTest, findCNAMEUnderZoneCut) {
    // There's nothing special when we find a CNAME under a zone cut
    // (with FIND_GLUE_OK).  The behavior is different from BIND 9,
    // so we test this case explicitly.
    EXPECT_EQ(SUCCESS, zone_.add(rr_child_ns_));
    RRsetPtr rr_cname_under_cut_(new RRset(Name("cname.child.example.org"),
                                           class_, RRType::CNAME(),
                                           RRTTL(300)));
    EXPECT_EQ(SUCCESS, zone_.add(rr_cname_under_cut_));
    findTest(Name("cname.child.example.org"), RRType::AAAA(),
             Zone::CNAME, true, rr_cname_under_cut_, NULL, NULL,
             Zone::FIND_GLUE_OK);
}

// Two DNAMEs at single domain are disallowed by RFC 2672, section 3)
// Having a CNAME there is disallowed too, but it is tested by
// addOtherThenCNAME and addCNAMEThenOther.
TEST_F(MemoryZoneTest, addMultipleDNAMEs) {
    rr_dname_->addRdata(generic::DNAME("target2.example.org."));
    EXPECT_THROW(zone_.add(rr_dname_), MemoryZone::AddError);
}

/*
 * These two tests ensure that we can't have DNAME and NS at the same
 * node with the exception of the apex of zone (forbidden by RFC 2672)
 */
TEST_F(MemoryZoneTest, addDNAMEThenNS) {
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_dname_)));
    EXPECT_THROW(zone_.add(rr_dname_ns_), MemoryZone::AddError);
}

TEST_F(MemoryZoneTest, addNSThenDNAME) {
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_dname_ns_)));
    EXPECT_THROW(zone_.add(rr_dname_), MemoryZone::AddError);
}

// It is allowed to have NS and DNAME at apex
TEST_F(MemoryZoneTest, DNAMEAndNSAtApex) {
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_dname_apex_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_)));

    // The NS should be possible to be found, below should be DNAME, not
    // delegation
    findTest(origin_, RRType::NS(), Zone::SUCCESS, true, rr_ns_);
    findTest(rr_child_ns_->getName(), RRType::A(), Zone::DNAME, true,
             rr_dname_apex_);
}

TEST_F(MemoryZoneTest, NSAndDNAMEAtApex) {
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_dname_apex_)));
}

// TODO: Test (and implement) adding data under DNAME. That is forbidden by
// 2672 as well.

// Search under a DNAME record. It should return the DNAME
TEST_F(MemoryZoneTest, findBelowDNAME) {
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_dname_)));
    findTest(Name("below.dname.example.org"), RRType::A(), Zone::DNAME, true,
        rr_dname_);
}

// Search at the domain with DNAME. It should act as DNAME isn't there, DNAME
// influences only the data below (see RFC 2672, section 3)
TEST_F(MemoryZoneTest, findAtDNAME) {
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_dname_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_dname_a_)));

    const Name dname_name(rr_dname_->getName());
    findTest(dname_name, RRType::A(), Zone::SUCCESS, true, rr_dname_a_);
    findTest(dname_name, RRType::DNAME(), Zone::SUCCESS, true, rr_dname_);
    findTest(dname_name, RRType::TXT(), Zone::NXRRSET, true);
}

// Try searching something that is both under NS and DNAME, without and with
// GLUE_OK mode (it should stop at the NS and DNAME respectively).
TEST_F(MemoryZoneTest, DNAMEUnderNS) {
    zone_.add(rr_child_ns_);
    zone_.add(rr_child_dname_);

    Name lowName("below.dname.child.example.org.");

    findTest(lowName, RRType::A(), Zone::DELEGATION, true, rr_child_ns_);
    findTest(lowName, RRType::A(), Zone::DNAME, true, rr_child_dname_, NULL,
        NULL, Zone::FIND_GLUE_OK);
}

// Test adding child zones and zone cut handling
TEST_F(MemoryZoneTest, delegationNS) {
    // add in-zone data
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_)));

    // install a zone cut
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_child_ns_)));

    // below the zone cut
    findTest(Name("www.child.example.org"), RRType::A(), Zone::DELEGATION,
             true, rr_child_ns_);

    // at the zone cut
    findTest(Name("child.example.org"), RRType::A(), Zone::DELEGATION,
             true, rr_child_ns_);
    findTest(Name("child.example.org"), RRType::NS(), Zone::DELEGATION,
             true, rr_child_ns_);

    // finding NS for the apex (origin) node.  This must not be confused
    // with delegation due to the existence of an NS RR.
    findTest(origin_, RRType::NS(), Zone::SUCCESS, true, rr_ns_);

    // unusual case of "nested delegation": the highest cut should be used.
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_grandchild_ns_)));
    findTest(Name("www.grand.child.example.org"), RRType::A(),
             Zone::DELEGATION, true, rr_child_ns_); // note: !rr_grandchild_ns_
}

TEST_F(MemoryZoneTest, findAny) {
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_a_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_child_glue_)));

    // origin
    RRsetList origin_rrsets;
    findTest(origin_, RRType::ANY(), Zone::SUCCESS, true,
             ConstRRsetPtr(), &origin_rrsets);
    EXPECT_EQ(2, origin_rrsets.size());
    EXPECT_EQ(rr_a_, origin_rrsets.findRRset(RRType::A(), RRClass::IN()));
    EXPECT_EQ(rr_ns_, origin_rrsets.findRRset(RRType::NS(), RRClass::IN()));

    // out zone name
    RRsetList out_rrsets;
    findTest(Name("example.com"), RRType::ANY(), Zone::NXDOMAIN, true,
             ConstRRsetPtr(), &out_rrsets);
    EXPECT_EQ(0, out_rrsets.size());

    RRsetList glue_child_rrsets;
    findTest(rr_child_glue_->getName(), RRType::ANY(), Zone::SUCCESS, true,
                ConstRRsetPtr(), &glue_child_rrsets);
    EXPECT_EQ(rr_child_glue_, glue_child_rrsets.findRRset(RRType::A(),
                                                     RRClass::IN()));
    EXPECT_EQ(1, glue_child_rrsets.size());

    // TODO: test NXRRSET case after rbtree non-terminal logic has
    // been implemented

    // add zone cut
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_child_ns_)));

    // zone cut
    RRsetList child_rrsets;
    findTest(rr_child_ns_->getName(), RRType::ANY(), Zone::DELEGATION, true,
             rr_child_ns_, &child_rrsets);
    EXPECT_EQ(0, child_rrsets.size());

    // glue for this zone cut
    RRsetList new_glue_child_rrsets;
    findTest(rr_child_glue_->getName(), RRType::ANY(), Zone::DELEGATION, true,
                rr_child_ns_, &new_glue_child_rrsets);
    EXPECT_EQ(0, new_glue_child_rrsets.size());
}

TEST_F(MemoryZoneTest, glue) {
    // install zone data:
    // a zone cut
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_child_ns_)));
    // glue for this cut
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_child_glue_)));
    // a nested zone cut (unusual)
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_grandchild_ns_)));
    // glue under the deeper zone cut
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_grandchild_glue_)));

    // by default glue is hidden due to the zone cut
    findTest(rr_child_glue_->getName(), RRType::A(), Zone::DELEGATION, true,
             rr_child_ns_);


    // If we do it in the "glue OK" mode, we should find the exact match.
    findTest(rr_child_glue_->getName(), RRType::A(), Zone::SUCCESS, true,
             rr_child_glue_, NULL, NULL, Zone::FIND_GLUE_OK);

    // glue OK + NXRRSET case
    findTest(rr_child_glue_->getName(), RRType::AAAA(), Zone::NXRRSET, true,
             ConstRRsetPtr(), NULL, NULL, Zone::FIND_GLUE_OK);

    // glue OK + NXDOMAIN case
    findTest(Name("www.child.example.org"), RRType::A(), Zone::DELEGATION,
             true, rr_child_ns_, NULL, NULL, Zone::FIND_GLUE_OK);

    // TODO:
    // glue name would match a wildcard under a zone cut: wildcard match
    // shouldn't happen under a cut and result must be PARTIALMATCH
    // (This case cannot be tested yet)

    // nested cut case.  The glue should be found.
    findTest(rr_grandchild_glue_->getName(), RRType::AAAA(),
             Zone::SUCCESS,
             true, rr_grandchild_glue_, NULL, NULL, Zone::FIND_GLUE_OK);

    // A non-existent name in nested cut.  This should result in delegation
    // at the highest zone cut.
    findTest(Name("www.grand.child.example.org"), RRType::TXT(),
             Zone::DELEGATION, true, rr_child_ns_, NULL, NULL,
             Zone::FIND_GLUE_OK);
}

/**
 * \brief Test searching.
 *
 * Check it finds or does not find correctly and does not throw exceptions.
 * \todo This doesn't do any kind of CNAME and so on. If it isn't
 *     directly there, it just tells it doesn't exist.
 */
TEST_F(MemoryZoneTest, find) {
    // Fill some data inside
    // Now put all the data we have there. It should throw nothing
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_a_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_ns_aaaa_)));
    EXPECT_NO_THROW(EXPECT_EQ(SUCCESS, zone_.add(rr_a_)));

    // These two should be successful
    findTest(origin_, RRType::NS(), Zone::SUCCESS, true, rr_ns_);
    findTest(rr_ns_a_->getName(), RRType::A(), Zone::SUCCESS, true, rr_ns_a_);

    // These domain exist but don't have the provided RRType
    findTest(origin_, RRType::AAAA(), Zone::NXRRSET);
    findTest(rr_ns_a_->getName(), RRType::NS(), Zone::NXRRSET);

    // These domains don't exist (and one is out of the zone)
    findTest(Name("nothere.example.org"), RRType::A(), Zone::NXDOMAIN);
    findTest(Name("example.net"), RRType::A(), Zone::NXDOMAIN);
}

TEST_F(MemoryZoneTest, emptyNode) {
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
        "bar.example.org", "x.foo.example.org", "aaa.baz.example.org",
        "bbb.baz.example.org.", NULL};
    for (int i = 0; names[i] != NULL; ++i) {
        ConstRRsetPtr rrset(new RRset(Name(names[i]), class_, RRType::A(),
                                      RRTTL(300)));
        EXPECT_EQ(SUCCESS, zone_.add(rrset));
    }

    // empty node matching, easy case: the node for 'baz' exists with
    // no data.
    findTest(Name("baz.example.org"), RRType::A(), Zone::NXRRSET);

    // empty node matching, a trickier case: the node for 'foo' is part of
    // "x.foo", which should be considered an empty node.
    findTest(Name("foo.example.org"), RRType::A(), Zone::NXRRSET);

    // "org" is contained in "example.org", but it shouldn't be treated as
    // NXRRSET because it's out of zone.
    // Note: basically we don't expect such a query to be performed (the common
    // operation is to identify the best matching zone first then perform
    // search it), but we shouldn't be confused even in the unexpected case.
    findTest(Name("org"), RRType::A(), Zone::NXDOMAIN);
}

TEST_F(MemoryZoneTest, load) {
    // Put some data inside the zone
    EXPECT_NO_THROW(EXPECT_EQ(result::SUCCESS, zone_.add(rr_ns_)));
    // Loading with different origin should fail
    EXPECT_THROW(zone_.load(TEST_DATA_DIR "/root.zone"), MasterLoadError);
    // See the original data is still there, survived the exception
    findTest(origin_, RRType::NS(), Zone::SUCCESS, true, rr_ns_);
    // Create correct zone
    MemoryZone rootzone(class_, Name("."));
    // Try putting something inside
    EXPECT_NO_THROW(EXPECT_EQ(result::SUCCESS, rootzone.add(rr_ns_aaaa_)));
    // Load the zone. It should overwrite/remove the above RRset
    EXPECT_NO_THROW(rootzone.load(TEST_DATA_DIR "/root.zone"));

    // Now see there are some rrsets (we don't look inside, though)
    findTest(Name("."), RRType::SOA(), Zone::SUCCESS, false, ConstRRsetPtr(),
        NULL, &rootzone);
    findTest(Name("."), RRType::NS(), Zone::SUCCESS, false, ConstRRsetPtr(),
        NULL, &rootzone);
    findTest(Name("a.root-servers.net."), RRType::A(), Zone::SUCCESS, false,
        ConstRRsetPtr(), NULL, &rootzone);
    // But this should no longer be here
    findTest(rr_ns_a_->getName(), RRType::AAAA(), Zone::NXDOMAIN, true,
             ConstRRsetPtr(), NULL, &rootzone);

    // Try loading zone that is wrong in a different way
    EXPECT_THROW(zone_.load(TEST_DATA_DIR "/duplicate_rrset.zone"),
        MasterLoadError);
}

/*
 * Test that puts a (simple) wildcard into the zone and checks we can
 * correctly find the data.
 */
TEST_F(MemoryZoneTest, wildcard) {
    /*
     *            example.org.
     *                 |
     *                wild (not *.wild, should have wild mark)
     *                 |
     *                 *
     */
    EXPECT_EQ(SUCCESS, zone_.add(rr_wild_));

    // Search at the parent. The parent will not have the A, but it will be here
    {
        SCOPED_TRACE("Search at parrent");
        findTest(Name("wild.example.org"), RRType::A(), Zone::NXRRSET);
    }

    // Search the original name of wildcard
    {
        SCOPED_TRACE("Search directly at *");
        findTest(Name("*.wild.example.org"), RRType::A(), Zone::SUCCESS, true,
            rr_wild_);
    }
    // Search "created" name.
    {
        SCOPED_TRACE("Search at created child");
        findTest(Name("a.wild.example.org"), RRType::A(), Zone::SUCCESS, false,
            rr_wild_, NULL, NULL, Zone::FIND_DEFAULT, true);
    }

    // Search another created name, this time little bit lower
    {
        SCOPED_TRACE("Search at created grand-child");
        findTest(Name("a.b.wild.example.org"), RRType::A(), Zone::SUCCESS,
            false, rr_wild_, NULL, NULL, Zone::FIND_DEFAULT, true);
    }
}

/*
 * Test that we don't match a wildcard if we get under delegation.
 */
TEST_F(MemoryZoneTest, delegatedWildcard) {
    EXPECT_EQ(SUCCESS, zone_.add(rr_child_wild_));
    EXPECT_EQ(SUCCESS, zone_.add(rr_child_ns_));

    findTest(Name("a.child.example.org"), RRType::A(), Zone::DELEGATION, true,
        rr_child_ns_);
}

// Tests combination of wildcard and ANY.
TEST_F(MemoryZoneTest, anyWildcard) {
    EXPECT_EQ(SUCCESS, zone_.add(rr_wild_));

    // First try directly the name (normal match)
    {
        SCOPED_TRACE("Asking direcly for *");
        RRsetList target;
        findTest(Name("*.wild.example.org"), RRType::ANY(), Zone::SUCCESS,
            true, ConstRRsetPtr(), &target);
        ASSERT_EQ(1, target.size());
        EXPECT_EQ(RRType::A(), (*target.begin())->getType());
        EXPECT_EQ(Name("*.wild.example.org"), (*target.begin())->getName());
    }

    // Then a wildcard match
    {
        SCOPED_TRACE("Asking in the wild way");
        RRsetList target;
        findTest(Name("a.wild.example.org"), RRType::ANY(), Zone::SUCCESS,
            true, ConstRRsetPtr(), &target);
        ASSERT_EQ(1, target.size());
        EXPECT_EQ(RRType::A(), (*target.begin())->getType());
        EXPECT_EQ(Name("a.wild.example.org"), (*target.begin())->getName());
    }
}

// Test there's nothing in the wildcard in the middle if we load
// wild.*.foo.example.org.
TEST_F(MemoryZoneTest, emptyWildcard) {
    /*
     *            example.org.
     *                foo
     *                 *
     *               wild
     */
    EXPECT_EQ(SUCCESS, zone_.add(rr_emptywild_));

    {
        SCOPED_TRACE("Asking for the original record under wildcard");
        findTest(Name("wild.*.foo.example.org"), RRType::A(), Zone::SUCCESS,
            true, rr_emptywild_);
    }

    {
        SCOPED_TRACE("Asking for A record");
        findTest(Name("a.foo.example.org"), RRType::A(), Zone::NXRRSET);
        findTest(Name("*.foo.example.org"), RRType::A(), Zone::NXRRSET);
        findTest(Name("foo.example.org"), RRType::A(), Zone::NXRRSET);
    }

    {
        SCOPED_TRACE("Asking for ANY record");
        RRsetList normalTarget;
        findTest(Name("*.foo.example.org"), RRType::ANY(), Zone::NXRRSET, true,
            ConstRRsetPtr(), &normalTarget);
        EXPECT_EQ(0, normalTarget.size());

        RRsetList wildTarget;
        findTest(Name("a.foo.example.org"), RRType::ANY(), Zone::NXRRSET, true,
            ConstRRsetPtr(), &wildTarget);
        EXPECT_EQ(0, wildTarget.size());
    }
}

// Same as emptyWildcard, but with multiple * in the path.
TEST_F(MemoryZoneTest, nestedEmptyWildcard) {
    EXPECT_EQ(SUCCESS, zone_.add(rr_nested_emptywild_));

    {
        SCOPED_TRACE("Asking for the original record under wildcards");
        findTest(Name("wild.*.foo.*.bar.example.org"), RRType::A(),
            Zone::SUCCESS, true, rr_nested_emptywild_);
    }

    // Domains to test
    const char *names[] = {
        "*.foo.*.bar.example.org",
        "foo.*.bar.example.org",
        "*.bar.example.org",
        "bar.example.org",
        NULL
    };

    {
        SCOPED_TRACE("Asking directly for A on parent nodes");

        for (const char **name(names); *name; ++ name) {
            SCOPED_TRACE(string("Node ") + *name);
            findTest(Name(*name), RRType::A(), Zone::NXRRSET);
        }
    }

    {
        SCOPED_TRACE("Asking for ANY on parent nodes");

        for (const char **name(names); *name; ++ name) {
            SCOPED_TRACE(string("Node ") + *name);

            RRsetList target;
            findTest(Name(*name), RRType::ANY(), Zone::NXRRSET, true,
                ConstRRsetPtr(), &target);
            EXPECT_EQ(0, target.size());
        }
    }
}

TEST_F(MemoryZoneTest, loadBadWildcard) {
    // We reject loading the zone if it contains a wildcard name for
    // NS or DNAME.
    EXPECT_THROW(zone_.add(rr_nswild_), MemoryZone::AddError);
    EXPECT_THROW(zone_.add(rr_dnamewild_), MemoryZone::AddError);
}

TEST_F(MemoryZoneTest, swap) {
    // build one zone with some data
    MemoryZone zone1(class_, origin_);
    EXPECT_EQ(result::SUCCESS, zone1.add(rr_ns_));
    EXPECT_EQ(result::SUCCESS, zone1.add(rr_ns_aaaa_));

    // build another zone of a different RR class with some other data
    const Name other_origin("version.bind");
    ASSERT_NE(origin_, other_origin); // make sure these two are different
    MemoryZone zone2(RRClass::CH(), other_origin);
    EXPECT_EQ(result::SUCCESS,
              zone2.add(RRsetPtr(new RRset(Name("version.bind"),
                                           RRClass::CH(), RRType::TXT(),
                                           RRTTL(0)))));

    zone1.swap(zone2);
    EXPECT_EQ(other_origin, zone1.getOrigin());
    EXPECT_EQ(origin_, zone2.getOrigin());
    EXPECT_EQ(RRClass::CH(), zone1.getClass());
    EXPECT_EQ(RRClass::IN(), zone2.getClass());
    // make sure the zone data is swapped, too
    findTest(origin_, RRType::NS(), Zone::NXDOMAIN, false, ConstRRsetPtr(),
             NULL, &zone1);
    findTest(other_origin, RRType::TXT(), Zone::SUCCESS, false,
             ConstRRsetPtr(), NULL, &zone1);
    findTest(origin_, RRType::NS(), Zone::SUCCESS, false, ConstRRsetPtr(),
             NULL, &zone2);
    findTest(other_origin, RRType::TXT(), Zone::NXDOMAIN, false,
             ConstRRsetPtr(), NULL, &zone2);
}

TEST_F(MemoryZoneTest, getFileName) {
    // for an empty zone the file name should also be empty.
    EXPECT_TRUE(zone_.getFileName().empty());

    // if loading a zone fails the file name shouldn't be set.
    EXPECT_THROW(zone_.load(TEST_DATA_DIR "/root.zone"), MasterLoadError);
    EXPECT_TRUE(zone_.getFileName().empty());

    // after a successful load, the specified file name should be set
    MemoryZone rootzone(class_, Name("."));
    EXPECT_NO_THROW(rootzone.load(TEST_DATA_DIR "/root.zone"));
    EXPECT_EQ(TEST_DATA_DIR "/root.zone", rootzone.getFileName());
    // overriding load, which will fail
    EXPECT_THROW(rootzone.load(TEST_DATA_DIR "/duplicate_rrset.zone"),
                 MasterLoadError);
    // the file name should be intact.
    EXPECT_EQ(TEST_DATA_DIR "/root.zone", rootzone.getFileName());

    // After swap, file names should also be swapped.
    zone_.swap(rootzone);
    EXPECT_EQ(TEST_DATA_DIR "/root.zone", zone_.getFileName());
    EXPECT_TRUE(rootzone.getFileName().empty());
}

}
