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

#include "../../tests/faked_nsec3.h"

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

#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

#include <sstream>
#include <vector>

#include <datasrc/memory/zone_finder.h>
#include <datasrc/memory/rdata_serialization.h>

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

// Some faked NSEC3 hash values commonly used in tests and the faked NSEC3Hash
// object.
//
// For apex (example.org)
const char* const apex_hash = "0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM";
const char* const apex_hash_lower = "0p9mhaveqvm6t7vbl5lop2u3t2rp3tom";
// For ns1.example.org
const char* const ns1_hash = "2T7B4G4VSA5SMI47K61MV5BV1A22BOJR";
// For w.example.org
const char* const w_hash = "01UDEMVP1J2F7EG6JEBPS17VP3N8I58H";
// For x.y.w.example.org (lower-cased)
const char* const xyw_hash = "2vptu5timamqttgl4luu9kg21e0aor3s";
// For zzz.example.org.
const char* const zzz_hash = "R53BQ7CC2UVMUBFU5OCMM6PERS9TK9EN";

// A simple faked NSEC3 hash calculator with a dedicated creator for it.
//
// This is used in some NSEC3-related tests below.
class TestNSEC3HashCreator : public NSEC3HashCreator {
    class TestNSEC3Hash : public NSEC3Hash {
    private:
        typedef map<Name, string> NSEC3HashMap;
        typedef NSEC3HashMap::value_type NSEC3HashPair;
        NSEC3HashMap map_;
    public:
        TestNSEC3Hash() {
            // Build pre-defined hash
            map_[Name("example.org")] = apex_hash;
            map_[Name("www.example.org")] = "2S9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM";
            map_[Name("xxx.example.org")] = "Q09MHAVEQVM6T7VBL5LOP2U3T2RP3TOM";
            map_[Name("yyy.example.org")] = "0A9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM";
            map_[Name("x.y.w.example.org")] =
                "2VPTU5TIMAMQTTGL4LUU9KG21E0AOR3S";
            map_[Name("y.w.example.org")] = "K8UDEMVP1J2F7EG6JEBPS17VP3N8I58H";
            map_[Name("w.example.org")] = w_hash;
            map_[Name("zzz.example.org")] = zzz_hash;
            map_[Name("smallest.example.org")] =
                "00000000000000000000000000000000";
            map_[Name("largest.example.org")] =
                "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU";
        }
        virtual string calculate(const Name& name) const {
            const NSEC3HashMap::const_iterator found = map_.find(name);
            if (found != map_.end()) {
                return (found->second);
            }
            isc_throw(isc::Unexpected, "unexpected name for NSEC3 test: "
                      << name);
        }
        virtual bool match(const generic::NSEC3PARAM&) const {
            return (true);
        }
        virtual bool match(const generic::NSEC3&) const {
            return (true);
        }
    };

public:
    virtual NSEC3Hash* create(const generic::NSEC3PARAM&) const {
        return (new TestNSEC3Hash);
    }
    virtual NSEC3Hash* create(const generic::NSEC3&) const {
        return (new TestNSEC3Hash);
    }
};


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
    return (textToRRset(src->toText()));
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
        zone_data_(ZoneData::create(mem_sgmt_, origin_)),
        zone_finder_(*zone_data_)
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

        for (unsigned int i = 0; zone_data[i].text != NULL; ++i) {
            *zone_data[i].rrset = textToRRset(zone_data[i].text);
        }

    }

    ~InMemoryZoneFinderTest() {
        // Make sure we reset the hash creator to the default
        setNSEC3HashCreator(NULL);
        ZoneData::destroy(mem_sgmt_, zone_data_, RRClass::IN());
    }

    // NSEC3-specific call for 'loading' data
    void addZoneDataNSEC3(const ConstRRsetPtr rrset) {
        // we're only adding one anyway so this is a simplified version
        // base nsec3 chain of rrset rdata
        // TODO: add if already exists?
        assert(rrset->getType() == RRType::NSEC3());

        const Rdata* rdata = &rrset->getRdataIterator()->getCurrent();
        const generic::NSEC3* nsec3_rdata = dynamic_cast<const generic::NSEC3*>(rdata);
        NSEC3Data* nsec3_data = NSEC3Data::create(mem_sgmt_, *nsec3_rdata);
        // in case we happen to be replacing, destroy old
        NSEC3Data* old_data = zone_data_->setNSEC3Data(nsec3_data);
        if (old_data != NULL) {
            NSEC3Data::destroy(mem_sgmt_, old_data, rrset->getClass());
        }
    }

    // simplified version of 'loading' data
    void addZoneData(const ConstRRsetPtr rrset) {
        ZoneNode* node = NULL;

        if (rrset->getType() == RRType::NSEC3()) {
            return (addZoneDataNSEC3(rrset));
        }
        zone_data_->insertName(mem_sgmt_, rrset->getName(), &node);
        RdataSet* next_rds = node->getData();

        if (rrset->getType() == RRType::NS() &&
            rrset->getName() != zone_data_->getOriginNode()->getName()) {
            node->setFlag(DomainTreeNode<RdataSet>::FLAG_CALLBACK);
        } else if (rrset->getType() == RRType::DNAME()) {
            node->setFlag(DomainTreeNode<RdataSet>::FLAG_CALLBACK);
        }

        RdataSet* rdataset =
            RdataSet::create(mem_sgmt_, encoder_, rrset, ConstRRsetPtr());
        rdataset->next = next_rds;
        node->setData(rdataset);
    }

    // Some data to test with
    const RRClass class_;
    const Name origin_;
    // The zone finder to torture by tests
    MemorySegmentTest mem_sgmt_;
    memory::ZoneData* zone_data_;
    memory::InMemoryZoneFinder zone_finder_;
    isc::datasrc::memory::RdataEncoder encoder_;

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
                  memory::InMemoryZoneFinder* zone_finder = NULL,
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
                        rrsetCheck(answer, convertRRset(find_result->rrset));
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
}

TEST_F(InMemoryZoneFinderTest, findCNAME) {
    // install CNAME RR
    addZoneData(rr_cname_);

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
    addZoneData(rr_child_ns_);
    ConstRRsetPtr rr_cname_under_cut_ = textToRRset(
        "cname.child.example.org. 300 IN CNAME target.child.example.org.");
    addZoneData(rr_cname_under_cut_);
    findTest(Name("cname.child.example.org"), RRType::AAAA(),
             ZoneFinder::CNAME, true, rr_cname_under_cut_,
             ZoneFinder::RESULT_DEFAULT, NULL, ZoneFinder::FIND_GLUE_OK);
}

// Search under a DNAME record. It should return the DNAME
TEST_F(InMemoryZoneFinderTest, findBelowDNAME) {
    EXPECT_NO_THROW(addZoneData(rr_dname_));
    findTest(Name("below.dname.example.org"), RRType::A(), ZoneFinder::DNAME,
             true, rr_dname_);
}

// Search at the domain with DNAME. It should act as DNAME isn't there, DNAME
// influences only the data below (see RFC 2672, section 3)
TEST_F(InMemoryZoneFinderTest, findAtDNAME) {
    EXPECT_NO_THROW(addZoneData(rr_dname_));
    EXPECT_NO_THROW(addZoneData(rr_dname_a_));

    const Name dname_name(rr_dname_->getName());
    findTest(dname_name, RRType::A(), ZoneFinder::SUCCESS, true, rr_dname_a_);
    findTest(dname_name, RRType::DNAME(), ZoneFinder::SUCCESS, true,
             rr_dname_);
    findTest(dname_name, RRType::TXT(), ZoneFinder::NXRRSET, true);
}

// Try searching something that is both under NS and DNAME, without and with
// GLUE_OK mode (it should stop at the NS and DNAME respectively).
TEST_F(InMemoryZoneFinderTest, DNAMEUnderNS) {
    addZoneData(rr_child_ns_);
    addZoneData(rr_child_dname_);

    Name lowName("below.dname.child.example.org.");

    findTest(lowName, RRType::A(), ZoneFinder::DELEGATION, true, rr_child_ns_);
    findTest(lowName, RRType::A(), ZoneFinder::DNAME, true, rr_child_dname_,
             ZoneFinder::RESULT_DEFAULT, NULL, ZoneFinder::FIND_GLUE_OK);
}

// Test adding child zones and zone cut handling
TEST_F(InMemoryZoneFinderTest, delegationNS) {
    // add in-zone data
    EXPECT_NO_THROW(addZoneData(rr_ns_));

    // install a zone cut
    EXPECT_NO_THROW(addZoneData(rr_child_ns_));

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
    EXPECT_NO_THROW(addZoneData(rr_grandchild_ns_));
    findTest(Name("www.grand.child.example.org"), RRType::A(),
             // note: !rr_grandchild_ns_
             ZoneFinder::DELEGATION, true, rr_child_ns_);
}

TEST_F(InMemoryZoneFinderTest, delegationWithDS) {
    // Similar setup to the previous one, but with DS RR at the delegation
    // point.
    addZoneData(rr_ns_);
    addZoneData(rr_child_ns_);
    addZoneData(rr_child_ds_);

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
    EXPECT_NO_THROW(addZoneData(rr_a_));
    EXPECT_NO_THROW(addZoneData(rr_ns_));
    EXPECT_NO_THROW(addZoneData(rr_child_glue_));

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
    EXPECT_NO_THROW(addZoneData(rr_child_ns_));

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
    EXPECT_NO_THROW(addZoneData(rr_child_ns_));
    // glue for this cut
    EXPECT_NO_THROW(addZoneData(rr_child_glue_));
    // a nested zone cut (unusual)
    EXPECT_NO_THROW(addZoneData(rr_grandchild_ns_));
    // glue under the deeper zone cut
    EXPECT_NO_THROW(addZoneData(rr_grandchild_glue_));

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
    EXPECT_NO_THROW(addZoneData(rr_ns_));
    EXPECT_NO_THROW(addZoneData(rr_ns_a_));
    EXPECT_NO_THROW(addZoneData(rr_ns_aaaa_));
    EXPECT_NO_THROW(addZoneData(rr_a_));
    if ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0) {
        addZoneData(rr_nsec3_);
        zone_data_->setSigned(true);
    }
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        addZoneData(rr_nsec_);
        zone_data_->setSigned(true);
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
        addZoneData(rr_ns_nsec_);
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
    addZoneData(rr_emptywild_);
    addZoneData(rr_under_wild_);

    // Sanity check: Should result in NXRRSET
    findTest(ent_name, RRType::A(), ZoneFinder::NXRRSET, true,
             ConstRRsetPtr(), expected_flags);
    // Sanity check: No NSEC added yet
    findTest(ent_name, RRType::A(), ZoneFinder::NXRRSET, true,
             ConstRRsetPtr(), expected_flags,
             NULL, ZoneFinder::FIND_DNSSEC);

    // Now add the NSEC rrs making it a 'complete' zone (in terms of NSEC,
    // there are no sigs)
    addZoneData(rr_nsec_);
    addZoneData(rr_ent_nsec2_);
    addZoneData(rr_ent_nsec3_);
    addZoneData(rr_ent_nsec4_);
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

TEST_F(InMemoryZoneFinderTest, DISABLED_findNSECEmptyNonterminalWildcard) {
    // Wildcard case, above actual wildcard
    findNSECENTCheck(Name("foo.example.org"), rr_nsec_);
}

TEST_F(InMemoryZoneFinderTest,DISABLED_findNSECEmptyNonterminalAtWildcard) {
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
        addZoneData(rrset);
    }
    if ((expected_flags & ZoneFinder::RESULT_NSEC3_SIGNED) != 0) {
        addZoneData(rr_nsec3_);
        zone_data_->setSigned(true);
    }
    if ((expected_flags & ZoneFinder::RESULT_NSEC_SIGNED) != 0) {
        addZoneData(rr_nsec_);
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

// DISABLED: nsec3 will be re-added in #2118
TEST_F(InMemoryZoneFinderTest, DISABLED_findNSEC3) {
    // Set up the faked hash calculator.
    setNSEC3HashCreator(&nsec3_hash_creator_);

    // Add a few NSEC3 records:
    // apex (example.org.): hash=0P..
    // ns1.example.org:     hash=2T..
    // w.example.org:       hash=01..
    // zzz.example.org:     hash=R5..
    const string apex_nsec3_text = string(apex_hash) + ".example.org." +
        string(nsec3_common);
    addZoneData(textToRRset(apex_nsec3_text));
    const string ns1_nsec3_text = string(ns1_hash) + ".example.org." +
        string(nsec3_common);
    addZoneData(textToRRset(ns1_nsec3_text));
    const string w_nsec3_text = string(w_hash) + ".example.org." +
        string(nsec3_common);
    addZoneData(textToRRset(w_nsec3_text));
    const string zzz_nsec3_text = string(zzz_hash) + ".example.org." +
        string(nsec3_common);
    addZoneData(textToRRset(zzz_nsec3_text));

    performNSEC3Test(zone_finder_);
}

// DISABLED: NSEC3 will be re-added in #2218
TEST_F(InMemoryZoneFinderTest, DISABLED_findNSEC3ForBadZone) {
    // Set up the faked hash calculator.
    setNSEC3HashCreator(&nsec3_hash_creator_);

    // If the zone has nothing about NSEC3 (neither NSEC3 or NSEC3PARAM),
    // findNSEC3() should be rejected.
    EXPECT_THROW(zone_finder_.findNSEC3(Name("www.example.org"), true),
                 DataSourceError);

    // Only having NSEC3PARAM isn't enough
    addZoneData(textToRRset("example.org. 300 IN NSEC3PARAM "
                            "1 0 12 aabbccdd"));
    EXPECT_THROW(zone_finder_.findNSEC3(Name("www.example.org"), true),
                 DataSourceError);

    // Unless NSEC3 for apex is added the result in the recursive mode
    // is guaranteed.
    const string ns1_nsec3_text = string(ns1_hash) + ".example.org." +
        string(nsec3_common);
    addZoneData(textToRRset(ns1_nsec3_text));
    EXPECT_THROW(zone_finder_.findNSEC3(Name("www.example.org"), true),
                 DataSourceError);
}

}
