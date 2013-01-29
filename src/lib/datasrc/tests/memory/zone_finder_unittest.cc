// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include "memory_segment_test.h"
#include "zone_table_segment_test.h"

// NOTE: this faked_nsec3 inclusion (and all related code below)
// was ported during #2109 for the convenience of implementing #2218
// In #2218 the NSEC3 test code in this file is expected to be finalized.
// In #2219 the original is expected to be removed, and this file should
// probably be moved here (and any leftover code not handled in #2218 should
// be cleaned up)
#include "../../tests/faked_nsec3.h"

#include <datasrc/memory/zone_finder.h>
#include <datasrc/memory/zone_data_updater.h>
#include <datasrc/memory/rdata_serialization.h>
#include <datasrc/memory/zone_table_segment.h>
#include <datasrc/memory/memory_client.h>
#include <datasrc/data_source.h>
#include <datasrc/client.h>
#include <testutils/dnsmessage_test.h>

#include <boost/foreach.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc;
using namespace isc::testutils;
using boost::shared_ptr;
using namespace isc::datasrc::test;
using namespace isc::datasrc::memory::test;
using namespace isc::datasrc::memory;

namespace {
// Commonly used result codes (Who should write the prefix all the time)
using result::SUCCESS;
using result::EXIST;

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

    InMemoryZoneFinderTest() :
        class_(RRClass::IN()),
        origin_("example.org"),
        zone_data_(ZoneData::create(mem_sgmt_, origin_)),
        zone_finder_(*zone_data_, class_),
        updater_(mem_sgmt_, class_, origin_, *zone_data_)
    {
        // Build test RRsets.  Below, we construct an RRset for
        // each textual RR(s) of zone_data, and assign it to the corresponding
        // rr_xxx.
        // Note that this contains an out-of-zone RR, and due to the
        // validation check of masterLoad() used below, we cannot add SOA.
        const RRsetData zone_data[] = {
            {"example.org. 300 IN SOA . . 0 0 0 0 100", &rr_soa_},
            {"example.org. 300 IN NS ns.example.org.", &rr_ns_},
            {"example.org. 300 IN A 192.0.2.1", &rr_a_},
            {"ns.example.org. 300 IN A 192.0.2.2", &rr_ns_a_},
            // This one will place rr_ns_a_ at a zone cut, making it a glue:
            {"ns.example.org. 300 IN NS 192.0.2.2", &rr_ns_ns_},
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

        for (unsigned int i = 0; zone_data[i].text != NULL; ++i) {
            if (zone_data[i].rrset == &rr_soa_) {
                // This is zone's SOA.  We need to specify the origin for
                // textToRRset; otherwise it would throw.
                *zone_data[i].rrset = textToRRset(zone_data[i].text, class_,
                                                  origin_);
            } else {
                // For other data, we should rather omit the origin (the root
                // name will be used by default); there's some out-of-zone
                // name, which would trigger an exception if we specified
                // origin_.
                *zone_data[i].rrset = textToRRset(zone_data[i].text);
            }
        }

    }

    ~InMemoryZoneFinderTest() {
        // Make sure we reset the hash creator to the default
        setNSEC3HashCreator(NULL);
        ZoneData::destroy(mem_sgmt_, zone_data_, RRClass::IN());
    }

    void addToZoneData(const ConstRRsetPtr rrset) {
        updater_.add(rrset, rrset->getRRsig());
    }

    /// \brief expensive rrset converter
    ///
    /// converts any specialized rrset (which may not have implemented some
    /// methods for efficiency) into a 'full' RRsetPtr, for easy use in test
    /// checks.
    ///
    /// Done very inefficiently through text representation, speed should not
    /// be a concern here.
    ConstRRsetPtr
    convertRRset(ConstRRsetPtr src) {
        // If the type is SOA, textToRRset performs a stricter check, so we
        // should specify the origin.  For now we don't use out-of-zone
        // owner names (e.g. for pathological cases) with this method, so it
        // works for all test data.  If future changes break this assumption
        // we should adjust it.
        return (textToRRset(src->toText(), class_, origin_));
    }

    // Some data to test with
    const RRClass class_;
    const Name origin_;
    // The zone finder to torture by tests
    MemorySegmentTest mem_sgmt_;
    memory::ZoneData* zone_data_;
    memory::InMemoryZoneFinder zone_finder_;
    ZoneDataUpdater updater_;

    // Placeholder for storing RRsets to be checked with rrsetsCheck()
    vector<ConstRRsetPtr> actual_rrsets_;

    /*
     * Some RRsets to put inside the zone.
     */
    RRsetPtr
        // Out of zone RRset
        rr_out_,
        // SOA of example.org
        rr_soa_,
        // NS of example.org
        rr_ns_,
        // A of ns.example.org
        rr_ns_a_,
        // AAAA of ns.example.org
        rr_ns_aaaa_,
        // A of example.org
        rr_a_;
    RRsetPtr rr_ns_ns_;         // used to make rr_ns_a_ a glue.
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
                  memory::InMemoryZoneFinder* zone_finder = NULL,
                  ZoneFinder::FindOptions options = ZoneFinder::FIND_DEFAULT,
                  bool check_wild_answer = false)
    {
        SCOPED_TRACE("findTest for " + name.toText() + "/" + rrtype.toText());

        if (zone_finder == NULL) {
            zone_finder = &zone_finder_;
        }
        // The whole block is inside, because we need to check the result and
        // we can't assign to FindResult
        EXPECT_NO_THROW({
                ZoneFinderContextPtr find_result(zone_finder->find(
                                                     name, rrtype, options));
                findTestCommon(name, result, find_result, check_answer,
                               answer, expected_flags, options,
                               check_wild_answer);
            });
    }

    void findAtOriginTest(const RRType& rrtype,
                          ZoneFinder::Result result,
                          bool check_answer = true,
                          const ConstRRsetPtr& answer = ConstRRsetPtr(),
                          ZoneFinder::FindResultFlags expected_flags =
                          ZoneFinder::RESULT_DEFAULT,
                          memory::InMemoryZoneFinder* zone_finder = NULL,
                          ZoneFinder::FindOptions options =
                          ZoneFinder::FIND_DEFAULT,
                          bool use_minttl = false)
    {
        SCOPED_TRACE("findAtOriginTest for " + rrtype.toText());

        if (zone_finder == NULL) {
            zone_finder = &zone_finder_;
        }
        ZoneFinderContextPtr find_result(zone_finder->findAtOrigin(
                                             rrtype, use_minttl, options));
        findTestCommon(origin_, result, find_result, check_answer, answer,
                       expected_flags, options, false);
    }

private:
    void findTestCommon(const Name& name, ZoneFinder::Result result,
                        ZoneFinderContextPtr find_result,
                        bool check_answer,
                        const ConstRRsetPtr& answer,
                        ZoneFinder::FindResultFlags expected_flags,
                        ZoneFinder::FindOptions options,
                        bool check_wild_answer)
    {
        const ConstRRsetPtr answer_sig = answer ? answer->getRRsig() :
            RRsetPtr(); // note we use the same type as of retval of getRRsig()

        // Check it returns correct answers
        EXPECT_EQ(result, find_result->code);
        EXPECT_EQ((expected_flags & ZoneFinder::RESULT_WILDCARD) != 0,
                  find_result->isWildcard());
        EXPECT_EQ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0,
                  find_result->isNSECSigned());
        EXPECT_EQ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0,
                  find_result->isNSEC3Signed());
        if (check_answer) {
            if (!answer) {
                ASSERT_FALSE(find_result->rrset);
            } else {
                ASSERT_TRUE(find_result->rrset);
                ConstRRsetPtr result_rrset(convertRRset(find_result->rrset));
                rrsetCheck(answer, result_rrset);
                if (answer_sig && (options & ZoneFinder::FIND_DNSSEC) != 0) {
                    ASSERT_TRUE(result_rrset->getRRsig());
                    rrsetCheck(answer_sig, result_rrset->getRRsig());
                } else {
                    EXPECT_FALSE(result_rrset->getRRsig());
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

            ConstRRsetPtr result_rrset(convertRRset(find_result->rrset));
            rrsetCheck(wildanswer, result_rrset);

            // Same for the RRSIG, if any.
            if (answer_sig) {
                ASSERT_TRUE(result_rrset->getRRsig());

                RRsetPtr wildsig(new RRset(name, answer_sig->getClass(),
                                           RRType::RRSIG(),
                                           answer_sig->getTTL()));
                RdataIteratorPtr expectedIt(
                    answer_sig->getRdataIterator());
                for (; !expectedIt->isLast(); expectedIt->next()) {
                    wildsig->addRdata(expectedIt->getCurrent());
                }
                rrsetCheck(wildsig, result_rrset->getRRsig());
            }
        }
    }

protected:
    /**
     * \brief Calls the findAll on the finder and checks the result.
     */
    void findAllTest(const Name& name, ZoneFinder::Result result,
                     const vector<ConstRRsetPtr>& expected_rrsets,
                     ZoneFinder::FindResultFlags expected_flags =
                     ZoneFinder::RESULT_DEFAULT,
                     memory::InMemoryZoneFinder* finder = NULL,
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
            rrsetCheck(rrset_result, convertRRset(find_result->rrset));
        }
        EXPECT_EQ((expected_flags & ZoneFinder::RESULT_WILDCARD) != 0,
                  find_result->isWildcard());
        EXPECT_EQ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED)
                  != 0, find_result->isNSECSigned());
        EXPECT_EQ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED)
                  != 0, find_result->isNSEC3Signed());
        // Convert all rrsets to 'full' ones before checking
        std::vector<ConstRRsetPtr> converted_rrsets;
        BOOST_FOREACH(ConstRRsetPtr cur_rrset, target) {
            converted_rrsets.push_back(convertRRset(cur_rrset));
        }
        rrsetsCheck(expected_rrsets.begin(), expected_rrsets.end(),
                    converted_rrsets.begin(), converted_rrsets.end());
    }
};

/**
 * \brief Test InMemoryZoneFinder::InMemoryZoneFinder constructor.
 *
 * Takes the created zone finder and checks its properties they are the same
 * as passed parameters.
 */
TEST_F(InMemoryZoneFinderTest, constructor) {
    ASSERT_EQ(origin_, zone_finder_.getOrigin());

    // Some unusual (abnormal case): if we add a super domain name of the
    // zone somehow, the label of the origin node won't be absolute.
    // getOrigin() should still be the correct one.
    ZoneNode *node;
    zone_data_->insertName(mem_sgmt_, Name("org"), &node);
    ASSERT_EQ(origin_, zone_finder_.getOrigin());
}

TEST_F(InMemoryZoneFinderTest, findCNAME) {
    // install CNAME RR
    addToZoneData(rr_cname_);

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
    addToZoneData(rr_child_ns_);
    ConstRRsetPtr rr_cname_under_cut_ = textToRRset(
        "cname.child.example.org. 300 IN CNAME target.child.example.org.");
    addToZoneData(rr_cname_under_cut_);
    findTest(Name("cname.child.example.org"), RRType::AAAA(),
             ZoneFinder::CNAME, true, rr_cname_under_cut_,
             ZoneFinder::RESULT_DEFAULT, NULL, ZoneFinder::FIND_GLUE_OK);
}

// Search under a DNAME record. It should return the DNAME
TEST_F(InMemoryZoneFinderTest, findBelowDNAME) {
    EXPECT_NO_THROW(addToZoneData(rr_dname_));
    findTest(Name("below.dname.example.org"), RRType::A(), ZoneFinder::DNAME,
             true, rr_dname_);
}

// Search at the domain with DNAME. It should act as DNAME isn't there, DNAME
// influences only the data below (see RFC 2672, section 3)
TEST_F(InMemoryZoneFinderTest, findAtDNAME) {
    EXPECT_NO_THROW(addToZoneData(rr_dname_));
    EXPECT_NO_THROW(addToZoneData(rr_dname_a_));

    const Name dname_name(rr_dname_->getName());
    findTest(dname_name, RRType::A(), ZoneFinder::SUCCESS, true, rr_dname_a_);
    findTest(dname_name, RRType::DNAME(), ZoneFinder::SUCCESS, true,
             rr_dname_);
    findTest(dname_name, RRType::TXT(), ZoneFinder::NXRRSET, true);
}

// Try searching something that is both under NS and DNAME, without and with
// GLUE_OK mode (it should stop at the NS and DNAME respectively).
TEST_F(InMemoryZoneFinderTest, DNAMEUnderNS) {
    addToZoneData(rr_child_ns_);
    addToZoneData(rr_child_dname_);

    Name lowName("below.dname.child.example.org.");

    findTest(lowName, RRType::A(), ZoneFinder::DELEGATION, true, rr_child_ns_);
    findTest(lowName, RRType::A(), ZoneFinder::DNAME, true, rr_child_dname_,
             ZoneFinder::RESULT_DEFAULT, NULL, ZoneFinder::FIND_GLUE_OK);
}

// Test adding child zones and zone cut handling
TEST_F(InMemoryZoneFinderTest, delegationNS) {
    // add in-zone data
    EXPECT_NO_THROW(addToZoneData(rr_ns_));

    // install a zone cut
    EXPECT_NO_THROW(addToZoneData(rr_child_ns_));

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
    EXPECT_NO_THROW(addToZoneData(rr_grandchild_ns_));
    findTest(Name("www.grand.child.example.org"), RRType::A(),
             // note: !rr_grandchild_ns_
             ZoneFinder::DELEGATION, true, rr_child_ns_);
}

TEST_F(InMemoryZoneFinderTest, delegationWithDS) {
    // Similar setup to the previous one, but with DS RR at the delegation
    // point.
    addToZoneData(rr_ns_);
    addToZoneData(rr_child_ns_);
    addToZoneData(rr_child_ds_);

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
    EXPECT_NO_THROW(addToZoneData(rr_a_));
    EXPECT_NO_THROW(addToZoneData(rr_ns_));
    EXPECT_NO_THROW(addToZoneData(rr_child_glue_));

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
    EXPECT_NO_THROW(addToZoneData(rr_child_ns_));

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
    EXPECT_NO_THROW(addToZoneData(rr_child_ns_));
    // glue for this cut
    EXPECT_NO_THROW(addToZoneData(rr_child_glue_));
    // a nested zone cut (unusual)
    EXPECT_NO_THROW(addToZoneData(rr_grandchild_ns_));
    // glue under the deeper zone cut
    EXPECT_NO_THROW(addToZoneData(rr_grandchild_glue_));
    // glue 'at the' zone cut
    EXPECT_NO_THROW(addToZoneData(rr_ns_a_));
    EXPECT_NO_THROW(addToZoneData(rr_ns_ns_));

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

    // Glue at a zone cut
    findTest(Name("ns.example.org"), RRType::A(),
             ZoneFinder::DELEGATION, true, rr_ns_ns_);
    findTest(Name("ns.example.org"), RRType::A(), ZoneFinder::SUCCESS,
             true, rr_ns_a_, ZoneFinder::RESULT_DEFAULT,
             NULL, ZoneFinder::FIND_GLUE_OK);
}

TEST_F(InMemoryZoneFinderTest, findAtOrigin) {
    // Add origin NS.
    rr_ns_->addRRsig(createRdata(RRType::RRSIG(), RRClass::IN(),
                                "NS 5 3 3600 20120814220826 20120715220826 "
                                "1234 example.org. FAKE"));
    addToZoneData(rr_ns_);

    // Specified type of RR exists, no DNSSEC
    findAtOriginTest(RRType::NS(), ZoneFinder::SUCCESS, true, rr_ns_);

    // Specified type of RR exists, with DNSSEC
    findAtOriginTest(RRType::NS(), ZoneFinder::SUCCESS, true, rr_ns_,
                     ZoneFinder::RESULT_DEFAULT, NULL,
                     ZoneFinder::FIND_DNSSEC);

    // Specified type of RR doesn't exist, no DNSSEC
    findAtOriginTest(RRType::TXT(), ZoneFinder::NXRRSET);

    // Specified type of RR doesn't exist, with DNSSEC.  First, make the
    // zone "NSEC-signed", then check.
    rr_nsec_->addRRsig(createRdata(RRType::RRSIG(), RRClass::IN(),
                                   "NSEC 5 3 3600 20120814220826 "
                                   "20120715220826 1234 example.org. FAKE"));
    addToZoneData(rr_nsec_);
    findAtOriginTest(RRType::TXT(), ZoneFinder::NXRRSET, true, rr_nsec_,
                     ZoneFinder::RESULT_NSEC_SIGNED, NULL,
                     ZoneFinder::FIND_DNSSEC);

    // Specified type of RR doesn't exist, with DNSSEC, enabling NSEC3.  First,
    // make the zone "NSEC3-signed" (by just installing NSEC3PARAM; we don't
    // need to add NSEC3s for the purpose of this test), then check.
    addToZoneData(textToRRset("example.org. 300 IN NSEC3PARAM "
                            "1 0 12 aabbccdd"));
    findAtOriginTest(RRType::TXT(), ZoneFinder::NXRRSET, true, ConstRRsetPtr(),
                     ZoneFinder::RESULT_NSEC3_SIGNED, NULL,
                     ZoneFinder::FIND_DNSSEC);
}

TEST_F(InMemoryZoneFinderTest, findAtOriginWithMinTTL) {
    // Install zone's SOA.  This also sets internal zone data min TTL field.
    addToZoneData(rr_soa_);

    // Specify the use of min TTL, then the resulting TTL should be derived
    // from the SOA MINTTL (which is smaller).
    findAtOriginTest(RRType::SOA(), ZoneFinder::SUCCESS, true,
                     textToRRset("example.org. 100 IN SOA . . 0 0 0 0 100",
                                 class_, origin_),
                     ZoneFinder::RESULT_DEFAULT, NULL,
                     ZoneFinder::FIND_DEFAULT, true);

    // Add signed NS for the following test.
    RRsetPtr ns_rrset(textToRRset("example.org. 300 IN NS ns.example.org."));
    ns_rrset->addRRsig(createRdata(RRType::RRSIG(), RRClass::IN(),
                                   "NS 5 3 3600 20120814220826 20120715220826 "
                                   "1234 example.org. FAKE"));
    addToZoneData(ns_rrset);

    // If DNSSEC is requested, TTL of the RRSIG should also be the min.
    ns_rrset->setTTL(RRTTL(100));      // reset TTL to the expected one
    findAtOriginTest(RRType::NS(), ZoneFinder::SUCCESS, true, ns_rrset,
                     ZoneFinder::RESULT_DEFAULT, NULL,
                     ZoneFinder::FIND_DEFAULT, true);

    // If we don't request the use of min TTL, the original TTL will be used.
    findAtOriginTest(RRType::SOA(), ZoneFinder::SUCCESS, true, rr_soa_,
                     ZoneFinder::RESULT_DEFAULT, NULL,
                     ZoneFinder::FIND_DEFAULT, false);

    // If the found RRset has a smaller TTL than SOA, the original TTL should
    // win.
    rr_a_->setTTL(RRTTL(10));
    addToZoneData(rr_a_);
    findAtOriginTest(RRType::A(), ZoneFinder::SUCCESS, true, rr_a_,
                     ZoneFinder::RESULT_DEFAULT, NULL,
                     ZoneFinder::FIND_DEFAULT, true);

    // If no RRset is returned, use_minttl doesn't matter (it shouldn't cause
    // disruption)
    findAtOriginTest(RRType::TXT(), ZoneFinder::NXRRSET, true, ConstRRsetPtr(),
                     ZoneFinder::RESULT_DEFAULT, NULL,
                     ZoneFinder::FIND_DEFAULT, true);

    // If it results in NXRRSET with NSEC, and if we specify the use of min
    // TTL, the NSEC and RRSIG should have the min TTL (again, though, this
    // use case is not really the intended one)
    rr_nsec_->addRRsig(createRdata(RRType::RRSIG(), RRClass::IN(),
                                   "NSEC 5 3 3600 20120814220826 "
                                   "20120715220826 1234 example.org. FAKE"));
    addToZoneData(rr_nsec_);
    rr_nsec_->setTTL(RRTTL(100)); // reset it to the expected one
    findAtOriginTest(RRType::TXT(), ZoneFinder::NXRRSET, true, rr_nsec_,
                     ZoneFinder::RESULT_NSEC_SIGNED, NULL,
                     ZoneFinder::FIND_DNSSEC, true);
}

/**
 * \brief Test searching.
 *
 * Check it finds or does not find correctly and does not throw exceptions.
 */
void
InMemoryZoneFinderTest::findCheck(ZoneFinder::FindResultFlags expected_flags,
                                  ZoneFinder::FindOptions find_options)
{
    // Fill some data inside
    // Now put all the data we have there. It should throw nothing
    rr_a_->addRRsig(createRdata(RRType::RRSIG(), RRClass::IN(),
                                "A 5 3 3600 20120814220826 20120715220826 "
                                "1234 example.com. FAKE"));
    EXPECT_NO_THROW(addToZoneData(rr_ns_));
    EXPECT_NO_THROW(addToZoneData(rr_ns_a_));
    EXPECT_NO_THROW(addToZoneData(rr_ns_aaaa_));
    EXPECT_NO_THROW(addToZoneData(rr_a_));
    if ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0) {
        addToZoneData(rr_nsec3_);
        zone_data_->setSigned(true);
    }
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        addToZoneData(rr_nsec_);
        zone_data_->setSigned(true);
    }

    // These two should be successful
    findTest(origin_, RRType::NS(), ZoneFinder::SUCCESS, true, rr_ns_);
    findTest(rr_ns_a_->getName(), RRType::A(), ZoneFinder::SUCCESS, true,
             rr_ns_a_);

    // Similar test for a signed RRset.  We should see the RRSIG iff
    // FIND_DNSSEC option is specified.
    findTest(rr_a_->getName(), RRType::A(), ZoneFinder::SUCCESS, true, rr_a_);
    findTest(rr_a_->getName(), RRType::A(), ZoneFinder::SUCCESS, true,
             rr_a_, ZoneFinder::RESULT_DEFAULT, NULL, ZoneFinder::FIND_DNSSEC);

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
        addToZoneData(rr_ns_nsec_);
        zone_data_->setSigned(true);
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
    addToZoneData(rr_emptywild_);
    addToZoneData(rr_under_wild_);

    // Sanity check: Should result in NXRRSET
    findTest(ent_name, RRType::A(), ZoneFinder::NXRRSET, true,
             ConstRRsetPtr(), expected_flags);
    // Sanity check: No NSEC added yet
    findTest(ent_name, RRType::A(), ZoneFinder::NXRRSET, true,
             ConstRRsetPtr(), expected_flags,
             NULL, ZoneFinder::FIND_DNSSEC);

    // Now add the NSEC rrs making it a 'complete' zone (in terms of NSEC,
    // there are no sigs)
    addToZoneData(rr_nsec_);
    addToZoneData(rr_ent_nsec2_);
    addToZoneData(rr_ent_nsec3_);
    addToZoneData(rr_ent_nsec4_);
    zone_data_->setSigned(true);

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

TEST_F(InMemoryZoneFinderTest, findNSECEmptyNonterminalWildcard) {
    // Wildcard case, above actual wildcard
    findNSECENTCheck(Name("foo.example.org"), rr_nsec_);
}

TEST_F(InMemoryZoneFinderTest, findNSECEmptyNonterminalAtWildcard) {
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
     * The backend ZoneTree for this test should look like as follows:
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
        addToZoneData(rrset);
    }
    if ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0) {
        addToZoneData(rr_nsec3_);
        zone_data_->setSigned(true);
    }
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        addToZoneData(rr_nsec_);
        zone_data_->setSigned(true);
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
    addToZoneData(rr_wild_);
    addToZoneData(rr_cnamewild_);
    // If the zone is expected to be "signed" with NSEC3, add an NSEC3.
    // (the content of the NSEC3 shouldn't matter)
    if ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0) {
        addToZoneData(rr_nsec3_);
    }
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        addToZoneData(rr_nsec_);
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

    addToZoneData(rr_under_wild_);
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
        addToZoneData(rr_wild_nsec_);
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
    addToZoneData(rr_child_wild_);
    addToZoneData(rr_child_ns_);

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
    addToZoneData(rr_wild_);
    if ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0) {
        addToZoneData(rr_nsec3_);
    }
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        addToZoneData(rr_nsec_);
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
    addToZoneData(rr_emptywild_);
    if ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0) {
        addToZoneData(rr_nsec3_);
    }
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        addToZoneData(rr_nsec_);
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
    addToZoneData(rr_nested_emptywild_);

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
    addToZoneData(rr_wild_);
    addToZoneData(rr_not_wild_);

    {
        SCOPED_TRACE("Runnig with single entry under foo.wild.example.org");
        doCancelWildcardCheck();
    }

    // Try putting another one under foo.wild....
    // The result should be the same but it will be done in another way in the
    // code, because the foo.wild.example.org will exist in the tree.
    addToZoneData(rr_not_wild_another_);
    {
        SCOPED_TRACE("Runnig with two entries under foo.wild.example.org");
        doCancelWildcardCheck();
    }
}

// Same tests as cancelWildcard for NSEC3-signed zone
TEST_F(InMemoryZoneFinderTest, cancelWildcardNSEC3) {
    addToZoneData(rr_wild_);
    addToZoneData(rr_not_wild_);
    addToZoneData(rr_nsec3_);

    {
        SCOPED_TRACE("Runnig with single entry under foo.wild.example.org");
        doCancelWildcardCheck(ZoneFinder::RESULT_NSEC3_SIGNED);
    }
    addToZoneData(rr_not_wild_another_);
    {
        SCOPED_TRACE("Runnig with two entries under foo.wild.example.org");
        doCancelWildcardCheck(ZoneFinder::RESULT_NSEC3_SIGNED);
    }
}

// Same tests as cancelWildcard for NSEC-signed zone.  Check both cases with
// or without FIND_DNSSEC option.  NSEC should be returned only when the option
// is given.
TEST_F(InMemoryZoneFinderTest, cancelWildcardNSEC) {
    addToZoneData(rr_wild_);
    addToZoneData(rr_not_wild_);
    addToZoneData(rr_nsec_);

    {
        SCOPED_TRACE("Runnig with single entry under foo.wild.example.org");
        doCancelWildcardCheck(ZoneFinder::RESULT_NSEC_SIGNED,
                              ZoneFinder::FIND_DNSSEC);
        doCancelWildcardCheck(ZoneFinder::RESULT_NSEC_SIGNED);
    }
    addToZoneData(rr_not_wild_another_);
    {
        SCOPED_TRACE("Runnig with two entries under foo.wild.example.org");
        doCancelWildcardCheck(ZoneFinder::RESULT_NSEC_SIGNED,
                              ZoneFinder::FIND_DNSSEC);
        doCancelWildcardCheck(ZoneFinder::RESULT_NSEC_SIGNED);
    }
}


TEST_F(InMemoryZoneFinderTest, findNSEC3ForBadZone) {
    // Set up the faked hash calculator.
    const TestNSEC3HashCreator creator;
    setNSEC3HashCreator(&creator);

    // If the zone has nothing about NSEC3 (neither NSEC3 or NSEC3PARAM),
    // findNSEC3() should be rejected.
    EXPECT_THROW(zone_finder_.findNSEC3(Name("www.example.org"), true),
                 DataSourceError);

    // Only having NSEC3PARAM isn't enough
    addToZoneData(textToRRset("example.org. 300 IN NSEC3PARAM "
                            "1 0 12 aabbccdd"));
    EXPECT_THROW(zone_finder_.findNSEC3(Name("www.example.org"), true),
                 DataSourceError);

    // Unless NSEC3 for apex is added the result in the recursive mode
    // is guaranteed.
    const string ns1_nsec3_text = string(ns1_hash) + ".example.org." +
        string(nsec3_common);
    addToZoneData(textToRRset(ns1_nsec3_text));
    EXPECT_THROW(zone_finder_.findNSEC3(Name("www.example.org"), true),
                 DataSourceError);
}

TEST_F(InMemoryZoneFinderTest, findOrphanRRSIG) {
    // Make the zone "NSEC signed"
    addToZoneData(rr_nsec_);
    const ZoneFinder::FindResultFlags expected_flags =
        ZoneFinder::RESULT_NSEC_SIGNED;

    // Add A for ns.example.org, and RRSIG-only covering TXT for the same name.
    // query for the TXT should result in NXRRSET.
    addToZoneData(rr_ns_a_);
    updater_.add(ConstRRsetPtr(),
                 textToRRset(
                     "ns.example.org. 300 IN RRSIG TXT 5 3 300 20120814220826 "
                     "20120715220826 1234 example.com. FAKE"));
    findTest(Name("ns.example.org"), RRType::TXT(),
             ZoneFinder::NXRRSET, true, ConstRRsetPtr(), expected_flags);

    // Add RRSIG-only covering NSEC.  This shouldn't be returned when NSEC is
    // requested, whether it's for NXRRSET or NXDOMAIN
    updater_.add(ConstRRsetPtr(),
                 textToRRset(
                     "ns.example.org. 300 IN RRSIG NSEC 5 3 300 "
                     "20120814220826 20120715220826 1234 example.com. FAKE"));
    // The added RRSIG for NSEC could be used for NXRRSET but shouldn't
    findTest(Name("ns.example.org"), RRType::TXT(),
             ZoneFinder::NXRRSET, true, ConstRRsetPtr(),
             expected_flags, NULL, ZoneFinder::FIND_DNSSEC);
    // The added RRSIG for NSEC could be used for NXDOMAIN but shouldn't
    findTest(Name("nz.example.org"), RRType::A(),
             ZoneFinder::NXDOMAIN, true, rr_nsec_,
             expected_flags, NULL, ZoneFinder::FIND_DNSSEC);

    // RRSIG-only CNAME shouldn't be accidentally confused with real CNAME.
    updater_.add(ConstRRsetPtr(),
                 textToRRset(
                     "nocname.example.org. 300 IN RRSIG CNAME 5 3 300 "
                     "20120814220826 20120715220826 1234 example.com. FAKE"));
    findTest(Name("nocname.example.org"), RRType::A(),
             ZoneFinder::NXRRSET, true, ConstRRsetPtr(), expected_flags);

    // RRSIG-only for NS wouldn't invoke delegation anyway, but we check this
    // case explicitly.
    updater_.add(ConstRRsetPtr(),
                 textToRRset(
                     "nodelegation.example.org. 300 IN RRSIG NS 5 3 300 "
                     "20120814220826 20120715220826 1234 example.com. FAKE"));
    findTest(Name("nodelegation.example.org"), RRType::A(),
             ZoneFinder::NXRRSET, true, ConstRRsetPtr(), expected_flags);
    findTest(Name("www.nodelegation.example.org"), RRType::A(),
             ZoneFinder::NXDOMAIN, true, ConstRRsetPtr(), expected_flags);

    // Same for RRSIG-only for DNAME
    updater_.add(ConstRRsetPtr(),
                 textToRRset(
                     "nodname.example.org. 300 IN RRSIG DNAME 5 3 300 "
                     "20120814220826 20120715220826 1234 example.com. FAKE"));
    findTest(Name("www.nodname.example.org"), RRType::A(),
             ZoneFinder::NXDOMAIN, true, ConstRRsetPtr(), expected_flags);
    // If we have a delegation NS at this node, it will be a bit trickier,
    // because the zonecut processing actually takes place at the node.
    // But the RRSIG-only for DNAME shouldn't confuse the process and the NS
    // should win.
    ConstRRsetPtr ns_rrset =
        textToRRset("nodname.example.org. 300 IN NS ns.nodname.example.org.");
    addToZoneData(ns_rrset);
    findTest(Name("www.nodname.example.org"), RRType::A(),
             ZoneFinder::DELEGATION, true, ns_rrset);
}

// \brief testcase for #2504 (Problem in inmem NSEC denial of existence
// handling)
TEST_F(InMemoryZoneFinderTest, NSECNonExistentTest) {
    shared_ptr<ZoneTableSegment> ztable_segment(
         new ZoneTableSegmentTest(class_, mem_sgmt_));
    InMemoryClient client(ztable_segment, class_);
    Name name("example.com.");

    client.load(name, TEST_DATA_DIR "/2504-test.zone");
    DataSourceClient::FindResult result(client.findZone(name));

    // Check for a non-existing name
    Name search_name("nonexist.example.com.");
    ZoneFinderContextPtr find_result(
        result.zone_finder->find(search_name,
                                 RRType::A(), ZoneFinder::FIND_DNSSEC));
    // We don't find the domain, but find() must complete (not throw or
    // assert).
    EXPECT_EQ(ZoneFinder::NXDOMAIN, find_result->code);
}

/// \brief NSEC3 specific tests fixture for the InMemoryZoneFinder class
class InMemoryZoneFinderNSEC3Test : public InMemoryZoneFinderTest {
public:
    InMemoryZoneFinderNSEC3Test() {
        // Set up the faked hash calculator.
        setNSEC3HashCreator(&creator_);

        // Add a few NSEC3 records:
        // apex (example.org.): hash=0P..
        // ns1.example.org:     hash=2T..
        // w.example.org:       hash=01..
        // zzz.example.org:     hash=R5..
        const string apex_nsec3_text = string(apex_hash) + ".example.org." +
            string(nsec3_common);
        addToZoneData(textToRRset(apex_nsec3_text));
        const string ns1_nsec3_text = string(ns1_hash) + ".example.org." +
            string(nsec3_common);
        addToZoneData(textToRRset(ns1_nsec3_text));
        const string w_nsec3_text = string(w_hash) + ".example.org." +
            string(nsec3_common);
        addToZoneData(textToRRset(w_nsec3_text));
        const string zzz_nsec3_text = string(zzz_hash) + ".example.org." +
            string(nsec3_common);
        addToZoneData(textToRRset(zzz_nsec3_text));
    }

private:
    const TestNSEC3HashCreator creator_;
};

TEST_F(InMemoryZoneFinderNSEC3Test, findNSEC3) {
    performNSEC3Test(zone_finder_);
}

struct TestData {
     // String for the name passed to findNSEC3() (concatenated with
     // "example.org.")
     const char* const name;
     // Should recursive findNSEC3() be performed?
     const bool recursive;
     // The following are members of the FindNSEC3Result returned by
     // findNSEC3(). The proofs are given as char*, which are converted
     // to Name objects and checked against getName() on the returned
     // ConstRRsetPtr. If any of these is NULL, then it's expected that
     // ConstRRsetPtr() will be returned.
     const bool matched;
     const uint8_t closest_labels;
     const char* const closest_proof;
     const char* const next_proof;
};

const TestData nsec3_data[] = {
     // ==== These are non-recursive tests.
     {"n0", false, false, 4, "R53BQ7CC2UVMUBFU5OCMM6PERS9TK9EN", NULL},
     {"n1", false,  true, 4, "01UDEMVP1J2F7EG6JEBPS17VP3N8I58H", NULL},
     {"n2", false, false, 4, "01UDEMVP1J2F7EG6JEBPS17VP3N8I58H", NULL},
     {"n3", false,  true, 4, "0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM", NULL},
     {"n4", false, false, 4, "0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM", NULL},
     {"n5", false,  true, 4, "2T7B4G4VSA5SMI47K61MV5BV1A22BOJR", NULL},
     {"n6", false, false, 4, "2T7B4G4VSA5SMI47K61MV5BV1A22BOJR", NULL},
     {"n7", false,  true, 4, "R53BQ7CC2UVMUBFU5OCMM6PERS9TK9EN", NULL},
     {"n8", false, false, 4, "R53BQ7CC2UVMUBFU5OCMM6PERS9TK9EN", NULL},

     // ==== These are recursive tests.
     {"n0",  true,  true, 3, "0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM",
         "R53BQ7CC2UVMUBFU5OCMM6PERS9TK9EN"},
     {"n1",  true,  true, 4, "01UDEMVP1J2F7EG6JEBPS17VP3N8I58H", NULL},
     {"n2",  true,  true, 3, "0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM",
         "01UDEMVP1J2F7EG6JEBPS17VP3N8I58H"},
     {"n3",  true,  true, 4, "0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM", NULL},
     {"n4",  true,  true, 3, "0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM",
         "0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM"},
     {"n5",  true,  true, 4, "2T7B4G4VSA5SMI47K61MV5BV1A22BOJR", NULL},
     {"n6",  true,  true, 3, "0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM",
         "2T7B4G4VSA5SMI47K61MV5BV1A22BOJR"},
     {"n7",  true,  true, 4, "R53BQ7CC2UVMUBFU5OCMM6PERS9TK9EN", NULL},
     {"n8",  true,  true, 3, "0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM",
         "R53BQ7CC2UVMUBFU5OCMM6PERS9TK9EN"}
};

const size_t data_count(sizeof(nsec3_data) / sizeof(*nsec3_data));

TEST_F(InMemoryZoneFinderNSEC3Test, findNSEC3Walk) {
    // This test basically uses nsec3_data[] declared above along with
    // the fake hash setup to walk the NSEC3 tree. The names and fake
    // hash calculation is specially setup so that the tree search
    // terminates at specific locations in the tree. We findNSEC3() on
    // each of the nsec3_data[], which is setup such that the hash
    // results in the search terminating on either side of each node of
    // the NSEC3 tree. This way, we check what result is returned in
    // every search termination case in the NSEC3 tree.

    const Name origin("example.org");
    for (size_t i = 0; i < data_count; ++i) {
        const Name name = Name(nsec3_data[i].name).concatenate(origin);

        SCOPED_TRACE(name.toText() + (nsec3_data[i].recursive ?
                                      ", recursive" :
                                      ", non-recursive"));

        const ZoneFinder::FindNSEC3Result result =
            zone_finder_.findNSEC3(name, nsec3_data[i].recursive);

        EXPECT_EQ(nsec3_data[i].matched, result.matched);
        EXPECT_EQ(nsec3_data[i].closest_labels, result.closest_labels);

        if (nsec3_data[i].closest_proof != NULL) {
            ASSERT_TRUE(result.closest_proof);
            EXPECT_EQ(Name(nsec3_data[i].closest_proof).concatenate(origin),
                      result.closest_proof->getName());
        } else {
            EXPECT_FALSE(result.closest_proof);
        }

        if (nsec3_data[i].next_proof != NULL) {
            ASSERT_TRUE(result.next_proof);
            EXPECT_EQ(Name(nsec3_data[i].next_proof).concatenate(origin),
                      result.next_proof->getName());
        } else {
            EXPECT_FALSE(result.next_proof);
        }
    }
}

TEST_F(InMemoryZoneFinderNSEC3Test, RRSIGOnly) {
    // add an RRSIG-only NSEC3 to the NSEC3 space, and try to find it; it
    // should result in an exception.
    const string n8_hash = "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ";
    updater_.add(ConstRRsetPtr(),
                 textToRRset(
                     n8_hash + ".example.org. 300 IN RRSIG NSEC3 5 3 300 "
                     "20120814220826 20120715220826 1234 example.com. FAKE"));
    EXPECT_THROW(zone_finder_.findNSEC3(Name("n8.example.org"), false),
                 DataSourceError);
}

// \brief testcase for #2503 (Problem in inmem NSEC3 denial of existence
// handling)
TEST_F(InMemoryZoneFinderNSEC3Test, findNSEC3MissingOrigin) {
     // Set back the default hash calculator.
     DefaultNSEC3HashCreator creator;
     setNSEC3HashCreator(&creator);

     shared_ptr<ZoneTableSegment> ztable_segment(
          new ZoneTableSegmentTest(class_, mem_sgmt_));
     InMemoryClient client(ztable_segment, class_);
     Name name("example.com.");

     client.load(name, TEST_DATA_DIR "/2503-test.zone");
     DataSourceClient::FindResult result(client.findZone(name));

     // Check for a non-existing name
     Name search_name("nonexist.example.com.");
     ZoneFinder::FindNSEC3Result find_result(
          result.zone_finder->findNSEC3(search_name, true));
     // findNSEC3() must have completed (not throw or assert). Because
     // the find was recursive, it always must find something and return
     // true.
     EXPECT_TRUE(find_result.matched);
}

}
