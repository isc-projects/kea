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

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <util/memory_segment_local.h>

#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrset.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>

#include <datasrc/memory/segment_object_holder.h>
#include <datasrc/memory/rdata_serialization.h>
#include <datasrc/memory/rdataset.h>

#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include <vector>
#include <string>

using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc::memory;
using namespace isc::testutils;
using std::string;
using std::vector;
using isc::datasrc::memory::detail::SegmentObjectHolder;
using boost::lexical_cast;

namespace {

class RdataSetTest : public ::testing::Test {
protected:
    RdataSetTest() :
        rrclass(RRClass::IN()),
        // 1076895760 = 0x40302010.  Use this so we fill in all 8-bit "field"
        // of the 32-bit TTL
        a_rrset_(textToRRset("www.example.com. 1076895760 IN A 192.0.2.1")),
        rrsig_rrset_(textToRRset("www.example.com. 1076895760 IN RRSIG "
                                 "A 5 2 3600 20120814220826 20120715220826 "
                                 "1234 example.com. FAKE"))
    {
        def_rdata_txt_.push_back("192.0.2.1");
        def_rrsig_txt_.push_back("A 5 2 3600 20120814220826 20120715220826 "
                                 "1234 example.com. FAKE");
    }
    void TearDown() {
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated());
    }

    // Helper for checking common cases against both versions of create()
    typedef boost::function<RdataSet*(isc::util::MemorySegment&, RdataEncoder&,
                                      ConstRRsetPtr, ConstRRsetPtr)> CreateFn;
    void checkCreateManyRRs(CreateFn create_fn, size_t n_old_rdata);
    void checkCreateManyRRSIGs(CreateFn create_fn, size_t n_old_sig);
    void checkBadCreate(CreateFn create_fn);

    const RRClass rrclass;
    ConstRRsetPtr a_rrset_, rrsig_rrset_;
    isc::util::MemorySegmentLocal mem_sgmt_;
    RdataEncoder encoder_;

    // These are placeholder for default expected values used in checkRdataSet.
    vector<string> def_rdata_txt_;
    vector<string> def_rrsig_txt_;
};

// Convert the given 32-bit integer (network byte order) to the corresponding
// RRTTL object.
RRTTL
restoreTTL(const void* ttl_data) {
    isc::util::InputBuffer b(ttl_data, sizeof(uint32_t));
    return (RRTTL(b));
}

// A helper callback for checkRdataSet.  This confirms the given data
// is the expected RDATA of the specified type.
void
checkData(const void* data, size_t size, const RRType* rrtype,
          vector<string>::const_iterator* it,
          vector<string>::const_iterator it_end)
{
    ASSERT_TRUE(*it != it_end); // shouldn't reach the end yet

    isc::util::InputBuffer b(data, size);
    EXPECT_EQ(0, createRdata(*rrtype, RRClass::IN(), b, size)->compare(
                  *createRdata(*rrtype, RRClass::IN(), **it)));
    ++(*it);                    // move to the next expected data
}

// This is a set of checks for an RdataSet created with some simple
// conditions.  expected_data/sigs contain the RDATAs and RRSIGs that are
// supposed to be contained in rdataset.  They can be empty if rdataset misses
// RDATA or RRSIG (but not both).
void
checkRdataSet(const RdataSet& rdataset,
              vector<string> expected_data, // we use a local copy
              const vector<string>& expected_sigs)
{
    EXPECT_FALSE(rdataset.next); // by default the next pointer should be NULL
    EXPECT_EQ(RRType::A(), rdataset.type);
    // See the RdataSetTest constructor for the magic number.
    EXPECT_EQ(RRTTL(1076895760), restoreTTL(rdataset.getTTLData()));
    EXPECT_EQ(expected_data.size(), rdataset.getRdataCount());
    EXPECT_EQ(expected_sigs.size(), rdataset.getSigRdataCount());

    // extend expected_data with sigs for the convenience of RdataReader
    expected_data.insert(expected_data.end(), expected_sigs.begin(),
                         expected_sigs.end());

    // A simple test for the data content.  Detailed tests for the encoder/
    // reader should be basically sufficient for various cases of the data,
    // and the fact that this test doesn't detect memory leak should be
    // reasonably sufficient that the implementation handles the data region
    // correctly.  Here we check one simple case for a simple form of RDATA
    // and RRSIG, mainly for checking the behavior of getDataBuf().
    vector<string>::const_iterator it = expected_data.begin();
    RRType rrtype = RRType::A();
    RdataReader reader(RRClass::IN(), RRType::A(),
                       reinterpret_cast<const uint8_t*>(
                           rdataset.getDataBuf()),
                       rdataset.getRdataCount(), rdataset.getSigRdataCount(),
                       &RdataReader::emptyNameAction,
                       boost::bind(checkData, _1, _2, &rrtype, &it,
                                   expected_data.end()));
    reader.iterate();
    rrtype = RRType::RRSIG();
    reader.iterateAllSigs();

    EXPECT_TRUE(it == expected_data.end());
}

TEST_F(RdataSetTest, create) {
    // A simple case of creating an RdataSet.  Confirming the resulting
    // fields have the expected values, and then destroying it (TearDown()
    // would detect any memory leak)
    RdataSet* rdataset = RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                          ConstRRsetPtr());
    checkRdataSet(*rdataset, def_rdata_txt_, vector<string>());
    RdataSet::destroy(mem_sgmt_, rdataset, RRClass::IN());
}

// This is similar to the simple create test, but we check all combinations
// of old and new data.
TEST_F(RdataSetTest, mergeCreate) {
    // Prepare test data
    const char* const a_rdatas[] = { "192.0.2.1", "192.0.2.2" };
    const char* const sig_rdatas[] = {
        "A 5 2 3600 20120814220826 20120715220826 1234 example.com. FAKE",
        "A 5 2 3600 20120814220826 20120715220826 4321 example.com. FAKE" };
    vector<ConstRRsetPtr> a_rrsets;
    a_rrsets.push_back(textToRRset("www.example.com. 1076895760 IN A "
                                   + string(a_rdatas[0])));
    a_rrsets.push_back(textToRRset("www.example.com. 1076895760 IN A "
                                   + string(a_rdatas[1])));
    vector<ConstRRsetPtr> rrsig_rrsets;
    rrsig_rrsets.push_back(textToRRset("www.example.com. 1076895760 IN RRSIG "
                                       + string(sig_rdatas[0])));
    rrsig_rrsets.push_back(textToRRset("www.example.com. 1076895760 IN RRSIG "
                                       + string(sig_rdatas[1])));
    ConstRRsetPtr null_rrset;   // convenience shortcut

    // We are going to check all combinations of:
    // with/without old/new RDATA/RRSIGs.
    // counter variables i, j control the old and new data, respectively, and
    // the meaning of the value is: bit 1: with RDATA, bit 2: with RRSIG.
    // Note that at least one RDATA or RRSIG should be contained, so there's
    // no case for value 0.
    for (int i = 1; i < 4; ++i) {
        for (int j = 1; j < 4; ++j) {
            SCOPED_TRACE("creating merge case " + lexical_cast<string>(i) +
                         ", " + lexical_cast<string>(j));
            // Create old rdataset
            SegmentObjectHolder<RdataSet, RRClass> holder1(
                mem_sgmt_,
                RdataSet::create(mem_sgmt_, encoder_,
                                 (i & 1) != 0 ? a_rrsets[0] : null_rrset,
                                 (i & 2) != 0 ? rrsig_rrsets[0] : null_rrset),
                rrclass);
            // Create merged rdataset, based on the old one and RRsets
            SegmentObjectHolder<RdataSet, RRClass> holder2(
                mem_sgmt_,
                RdataSet::create(mem_sgmt_, encoder_,
                                 (j & 1) != 0 ? a_rrsets[1] : null_rrset,
                                 (j & 2) != 0 ? rrsig_rrsets[1] : null_rrset,
                                 holder1.get()),
                rrclass);

            // Set up the expected data for the case.
            vector<string> expected_rdata;
            if ((i & 1) != 0) {
                expected_rdata.push_back(a_rdatas[0]);
            }
            if ((j & 1) != 0) {
                expected_rdata.push_back(a_rdatas[1]);
            }
            vector<string> expected_sigs;
            if ((i & 2) != 0) {
                expected_sigs.push_back(sig_rdatas[0]);
            }
            if ((j & 2) != 0) {
                expected_sigs.push_back(sig_rdatas[1]);
            }

            // Then perform the check
            checkRdataSet(*holder2.get(), expected_rdata, expected_sigs);
        }
    }
}

TEST_F(RdataSetTest, duplicate) {
    // Create RRset and RRSIG containing duplicate RDATA.
    ConstRRsetPtr dup_rrset =
        textToRRset("www.example.com. 1076895760 IN A 192.0.2.1\n"
                    "www.example.com. 1076895760 IN A 192.0.2.1\n");
    ConstRRsetPtr dup_rrsig =
        textToRRset("www.example.com. 1076895760 IN RRSIG " +
                    def_rrsig_txt_[0] +
                    "\nwww.example.com. 1076895760 IN RRSIG " +
                    def_rrsig_txt_[0]);

    // After suppressing duplicates, it should be the same as the default
    // RdataSet.  Check that.
    SegmentObjectHolder<RdataSet, RRClass> holder1(
        mem_sgmt_,
        RdataSet::create(mem_sgmt_, encoder_, dup_rrset, dup_rrsig), rrclass);
    checkRdataSet(*holder1.get(), def_rdata_txt_, def_rrsig_txt_);

    // Confirm the same thing for the merge mode.
    SegmentObjectHolder<RdataSet, RRClass> holder2(
        mem_sgmt_,
        RdataSet::create(mem_sgmt_, encoder_, a_rrset_, rrsig_rrset_,
                         holder1.get()), rrclass);
    checkRdataSet(*holder2.get(), def_rdata_txt_, def_rrsig_txt_);
}

TEST_F(RdataSetTest, getNext) {
    RdataSet* rdataset = RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                          ConstRRsetPtr());

    // By default, the next pointer should be NULL (already tested in other
    // test cases), which should be the case with getNext().  We test both
    // mutable and immutable versions of getNext().
    EXPECT_EQ(static_cast<RdataSet*>(NULL), rdataset->getNext());
    EXPECT_EQ(static_cast<const RdataSet*>(NULL),
              static_cast<const RdataSet*>(rdataset)->getNext());

    // making a link (it would form an infinite loop, but it doesn't matter
    // in this test), and check the pointer returned by getNext().
    rdataset->next = rdataset;
    EXPECT_EQ(rdataset, static_cast<const RdataSet*>(rdataset)->getNext());

    RdataSet::destroy(mem_sgmt_, rdataset, RRClass::IN());
}

TEST_F(RdataSetTest, find) {
    // Create some RdataSets and make a chain of them.
    SegmentObjectHolder<RdataSet, RRClass> holder1(
        mem_sgmt_,
        RdataSet::create(mem_sgmt_, encoder_, a_rrset_, ConstRRsetPtr()),
        RRClass::IN());
    ConstRRsetPtr aaaa_rrset =
        textToRRset("www.example.com. 1076895760 IN AAAA 2001:db8::1");
    SegmentObjectHolder<RdataSet, RRClass> holder2(
        mem_sgmt_,
        RdataSet::create(mem_sgmt_, encoder_, aaaa_rrset, ConstRRsetPtr()),
        RRClass::IN());
    ConstRRsetPtr sigonly_rrset =
        textToRRset("www.example.com. 1076895760 IN RRSIG "
                    "TXT 5 2 3600 20120814220826 20120715220826 "
                    "1234 example.com. FAKE");
    SegmentObjectHolder<RdataSet, RRClass> holder3(
        mem_sgmt_,
        RdataSet::create(mem_sgmt_, encoder_, ConstRRsetPtr(), sigonly_rrset),
        RRClass::IN());

    RdataSet* rdataset_a = holder1.get();
    RdataSet* rdataset_aaaa = holder2.get();
    RdataSet* rdataset_sigonly = holder3.get();
    RdataSet* rdataset_null = NULL;
    rdataset_a->next = rdataset_aaaa;
    rdataset_aaaa->next = rdataset_sigonly;

    // If a non-RRSIG part of rdataset exists for the given type, it will be
    // returned regardless of the value of sigonly_ok.  If it's RRSIG-only
    // rdataset, it returns non NULL iff sigonly_ok is explicitly set to true.
    EXPECT_EQ(rdataset_aaaa, RdataSet::find(rdataset_a, RRType::AAAA()));
    EXPECT_EQ(rdataset_aaaa, RdataSet::find(rdataset_a, RRType::AAAA(), true));
    EXPECT_EQ(rdataset_aaaa, RdataSet::find(rdataset_a, RRType::AAAA(), false));

    EXPECT_EQ(rdataset_null, RdataSet::find(rdataset_a, RRType::TXT()));
    EXPECT_EQ(rdataset_sigonly, RdataSet::find(rdataset_a, RRType::TXT(),
                                               true));
    EXPECT_EQ(rdataset_null, RdataSet::find(rdataset_a, RRType::TXT(), false));

    // Same tests for the const version of find().
    const RdataSet* rdataset_a_const = holder1.get();
    EXPECT_EQ(rdataset_aaaa, RdataSet::find(rdataset_a_const, RRType::AAAA()));
    EXPECT_EQ(rdataset_aaaa, RdataSet::find(rdataset_a_const, RRType::AAAA(),
                                            true));
    EXPECT_EQ(rdataset_aaaa, RdataSet::find(rdataset_a_const, RRType::AAAA(),
                                            false));

    EXPECT_EQ(rdataset_null, RdataSet::find(rdataset_a_const, RRType::TXT()));
    EXPECT_EQ(rdataset_sigonly, RdataSet::find(rdataset_a_const, RRType::TXT(),
                                               true));
    EXPECT_EQ(rdataset_null, RdataSet::find(rdataset_a_const, RRType::TXT(),
                                            false));
}

// A helper function to create an RRset containing the given number of
// unique RDATAs.  We return non const pointer so that we can extend it.
RRsetPtr
getRRsetWithRdataCount(size_t rdata_count) {
    RRsetPtr rrset(new RRset(Name("example.com"), RRClass::IN(), RRType::TXT(),
                             RRTTL(3600)));
    for (size_t i = 0; i < rdata_count; ++i) {
        rrset->addRdata(rdata::createRdata(RRType::TXT(), RRClass::IN(),
                                           lexical_cast<std::string>(i)));
    }
    return (rrset);
}

void
RdataSetTest::checkCreateManyRRs(CreateFn create_fn, size_t n_old_rdata) {
    // RRset with possible maximum number of RDATAs, taking into account
    // "pre-existing" RDATAs
    RRsetPtr large_rrset = getRRsetWithRdataCount(8191 - n_old_rdata);
    RdataSet* rdataset = create_fn(mem_sgmt_, encoder_, large_rrset,
                                   ConstRRsetPtr());
    EXPECT_EQ(8191, rdataset->getRdataCount());
    EXPECT_EQ(0, rdataset->getSigRdataCount());
    RdataSet::destroy(mem_sgmt_, rdataset, rrclass);

    // Duplicate RDATA will be ignored in this check.
    large_rrset->addRdata(createRdata(RRType::TXT(), rrclass, "0"));
    rdataset = create_fn(mem_sgmt_, encoder_, large_rrset, ConstRRsetPtr());
    EXPECT_EQ(8191, rdataset->getRdataCount());
    RdataSet::destroy(mem_sgmt_, rdataset, rrclass);

    // Exceeding that will result in an exception.
    large_rrset->addRdata(createRdata(RRType::TXT(), rrclass, "8192"));
    EXPECT_THROW(create_fn(mem_sgmt_, encoder_, large_rrset, ConstRRsetPtr()),
                 RdataSetError);
    // To be very sure even try larger number than the threshold
    EXPECT_THROW(create_fn(mem_sgmt_, encoder_,
                           getRRsetWithRdataCount(65535 - n_old_rdata),
                           ConstRRsetPtr()),
                 RdataSetError);
}

TEST_F(RdataSetTest, createManyRRs) {
    checkCreateManyRRs(boost::bind(&RdataSet::create, _1, _2, _3, _4,
                                   static_cast<const RdataSet*>(NULL)), 0);
}

TEST_F(RdataSetTest, mergeCreateManyRRs) {
    ConstRRsetPtr rrset = textToRRset("example.com. 3600 IN TXT some-text");
    SegmentObjectHolder<RdataSet, RRClass> holder(
        mem_sgmt_,
        RdataSet::create(mem_sgmt_, encoder_, rrset, ConstRRsetPtr()),
        RRClass::IN());

    checkCreateManyRRs(boost::bind(&RdataSet::create, _1, _2, _3, _4,
                                   holder.get()), rrset->getRdataCount());
}

TEST_F(RdataSetTest, createWithRRSIG) {
    RdataSet* rdataset = RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                          rrsig_rrset_);
    checkRdataSet(*rdataset, def_rdata_txt_, def_rrsig_txt_);
    RdataSet::destroy(mem_sgmt_, rdataset, RRClass::IN());
}

// A helper function to create an RRSIG RRset containing the given number of
// unique RDATAs.
RRsetPtr
getRRSIGWithRdataCount(size_t sig_count) {
    RRsetPtr rrset(new RRset(Name("example.com"), RRClass::IN(),
                             RRType::RRSIG(), RRTTL(3600)));
    // We use a base wire-format image and tweak the original TTL field to
    // generate unique RDATAs in the loop.  (Creating them from corresponding
    // text is simpler, but doing so for a large number of RRSIGs is
    // relatively heavy and could be too long for unittests).
    ConstRdataPtr rrsig_base =
        rdata::createRdata(RRType::RRSIG(), RRClass::IN(),
                           "A 5 2 3600 20120814220826 20120715220826 1234 "
                           "example.com. FAKE");
    isc::util::OutputBuffer ob(0);
    rrsig_base->toWire(ob);
    for (size_t i = 0; i < sig_count; ++i) {
        ob.writeUint16At((i >> 16) & 0xffff, 4);
        ob.writeUint16At(i & 0xffff, 6);
        isc::util::InputBuffer ib(ob.getData(), ob.getLength());
        rrset->addRdata(rdata::createRdata(RRType::RRSIG(), RRClass::IN(),
                                           ib, ib.getLength()));
    }
    return (rrset);
}

void
RdataSetTest::checkCreateManyRRSIGs(CreateFn create_fn, size_t n_old_sig) {
    // 7 has a special meaning in the implementation: if the number of the
    // RRSIGs reaches this value, an extra 'sig count' field will be created.
    RdataSet* rdataset = create_fn(mem_sgmt_, encoder_, a_rrset_,
                                   getRRSIGWithRdataCount(7 - n_old_sig));
    EXPECT_EQ(7, rdataset->getSigRdataCount());
    RdataSet::destroy(mem_sgmt_, rdataset, RRClass::IN());

    // 8 would cause overflow in the normal 3-bit field if there were no extra
    // count field.
    rdataset = create_fn(mem_sgmt_, encoder_, a_rrset_,
                         getRRSIGWithRdataCount(8 - n_old_sig));
    EXPECT_EQ(8, rdataset->getSigRdataCount());
    RdataSet::destroy(mem_sgmt_, rdataset, RRClass::IN());

    // Up to 2^16-1 RRSIGs are allowed (although that would be useless
    // in practice)
    RRsetPtr large_rrsig = getRRSIGWithRdataCount(65535 - n_old_sig);
    rdataset = create_fn(mem_sgmt_, encoder_, a_rrset_, large_rrsig);
    EXPECT_EQ(65535, rdataset->getSigRdataCount());
    RdataSet::destroy(mem_sgmt_, rdataset, RRClass::IN());

    // Duplicate shouldn't be counted
    large_rrsig->addRdata(
        createRdata(RRType::RRSIG(), rrclass,
                    "A 5 2 0 20120814220826 20120715220826 1234 "
                    "example.com. FAKE"));
    rdataset = create_fn(mem_sgmt_, encoder_, a_rrset_, large_rrsig);
    EXPECT_EQ(65535, rdataset->getSigRdataCount());
    RdataSet::destroy(mem_sgmt_, rdataset, RRClass::IN());

    // Exceeding this limit will result in an exception.
    large_rrsig->addRdata(
        createRdata(RRType::RRSIG(), rrclass,
                    "A 5 2 65536 20120814220826 20120715220826 1234 "
                    "example.com. FAKE"));
    EXPECT_THROW(create_fn(mem_sgmt_, encoder_, a_rrset_, large_rrsig),
                 RdataSetError);
    // To be very sure even try larger number than the threshold
    EXPECT_THROW(create_fn(mem_sgmt_, encoder_, a_rrset_,
                           getRRSIGWithRdataCount(70000 - n_old_sig)),
                 RdataSetError);
}

TEST_F(RdataSetTest, createManyRRSIGs) {
    checkCreateManyRRSIGs(boost::bind(&RdataSet::create, _1, _2, _3, _4,
                                      static_cast<const RdataSet*>(NULL)), 0);
}

TEST_F(RdataSetTest, mergeCreateManyRRSIGs) {
    // Create "old" RRSIG that shouldn't be a duplicate of ones created in
    // checkCreateManyRRSIGs (signature is different).
    ConstRRsetPtr rrsig = textToRRset(
        "example.com. 3600 IN RRSIG A 5 2 3600 20120814220826 20120715220826 "
        "1234 example.com. FAKEFAKE");
    SegmentObjectHolder<RdataSet, RRClass> holder(
        mem_sgmt_,
        RdataSet::create(mem_sgmt_, encoder_, ConstRRsetPtr(), rrsig),
        rrclass);

    checkCreateManyRRSIGs(boost::bind(&RdataSet::create, _1, _2, _3, _4,
                                      holder.get()), rrsig->getRdataCount());
}

TEST_F(RdataSetTest, createWithRRSIGOnly) {
    // A rare, but allowed, case: RdataSet without the main RRset but with
    // RRSIG.
    RdataSet* rdataset = RdataSet::create(mem_sgmt_, encoder_, ConstRRsetPtr(),
                                          rrsig_rrset_);
    checkRdataSet(*rdataset, vector<string>(), def_rrsig_txt_);
    RdataSet::destroy(mem_sgmt_, rdataset, RRClass::IN());
}

// Checking initial validation for both versions of create().
void
RdataSetTest::checkBadCreate(CreateFn create_fn) {
    // Neither the RRset nor RRSIG RRset is given
    EXPECT_THROW(create_fn(mem_sgmt_, encoder_, ConstRRsetPtr(),
                           ConstRRsetPtr()), isc::BadValue);

    // Empty RRset (An RRset without RDATA)
    ConstRRsetPtr empty_rrset(new RRset(Name("example.com"), RRClass::IN(),
                                        RRType::A(), RRTTL(3600)));
    EXPECT_THROW(create_fn(mem_sgmt_, encoder_, empty_rrset,
                           ConstRRsetPtr()), isc::BadValue);
    ConstRRsetPtr empty_rrsig(new RRset(Name("example.com"), RRClass::IN(),
                                        RRType::RRSIG(), RRTTL(3600)));
    EXPECT_THROW(create_fn(mem_sgmt_, encoder_, ConstRRsetPtr(),
                           empty_rrsig), isc::BadValue);

    // The RRset type and RRSIG's type covered don't match
    ConstRRsetPtr bad_rrsig(textToRRset(
                                "www.example.com. 1076895760 IN RRSIG "
                                "NS 5 2 3600 20120814220826 20120715220826 "
                                "1234 example.com. FAKE"));
    EXPECT_THROW(create_fn(mem_sgmt_, encoder_, a_rrset_, bad_rrsig),
                 isc::BadValue);

    // Pass non RRSIG for the sig parameter
    EXPECT_THROW(create_fn(mem_sgmt_, encoder_, a_rrset_, a_rrset_),
                 isc::BadValue);

    // Pass RRSIG for normal RRset (the RdataEncoder will catch this and throw)
    EXPECT_THROW(create_fn(mem_sgmt_, encoder_, rrsig_rrset_, rrsig_rrset_),
                 isc::BadValue);

    // RR class doesn't match between RRset and RRSIG
    ConstRRsetPtr badclass_rrsig(textToRRset(
                                     "www.example.com. 1076895760 CH RRSIG "
                                     "A 5 2 3600 20120814220826 "
                                     "20120715220826 1234 example.com. FAKE",
                                     RRClass::CH()));
    EXPECT_THROW(create_fn(mem_sgmt_, encoder_, a_rrset_, badclass_rrsig),
                 isc::BadValue);
}

TEST_F(RdataSetTest, badCreate) {
    checkBadCreate(boost::bind(&RdataSet::create, _1, _2, _3, _4,
                               static_cast<const RdataSet*>(NULL)));
}

TEST_F(RdataSetTest, badMergeCreate) {
    // The 'old RdataSet' for merge.  Its content doesn't matter much; the test
    // should trigger exception before examining it except for the last checks.
    SegmentObjectHolder<RdataSet, RRClass> holder(
        mem_sgmt_,
        RdataSet::create(mem_sgmt_, encoder_,
                         textToRRset("www.example.com. 0 IN AAAA 2001:db8::1"),
                         ConstRRsetPtr()),
        RRClass::IN());

    checkBadCreate(boost::bind(&RdataSet::create, _1, _2, _3, _4,
                               holder.get()));

    // Type mismatch: this case is specific to the merge create.
    EXPECT_THROW(RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                  ConstRRsetPtr(), holder.get()),
                 isc::BadValue);
    EXPECT_THROW(RdataSet::create(mem_sgmt_, encoder_, ConstRRsetPtr(),
                                  rrsig_rrset_, holder.get()),
                 isc::BadValue);
}

TEST_F(RdataSetTest, varyingTTL) {
    // Creating RdataSets with different TTLs.  The lowest one should win.

    ConstRRsetPtr aaaa_smaller = textToRRset("example. 5 IN AAAA 2001:db8::");
    ConstRRsetPtr aaaa_small = textToRRset("example. 10 IN AAAA 2001:db8::1");
    ConstRRsetPtr aaaa_large = textToRRset("example. 20 IN AAAA 2001:db8::2");
    ConstRRsetPtr sig_smaller =
        textToRRset("www.example.com. 5 IN RRSIG AAAA 5 2 3600 "
                    "20120814220826 20120715220826 1111 example.com. FAKE");
    ConstRRsetPtr sig_small =
        textToRRset("www.example.com. 10 IN RRSIG AAAA 5 2 3600 "
                    "20120814220826 20120715220826 1234 example.com. FAKE");
    ConstRRsetPtr sig_large =
        textToRRset("www.example.com. 20 IN RRSIG AAAA 5 2 3600 "
                    "20120814220826 20120715220826 4321 example.com. FAKE");

    // RRSIG's TTL is larger
    RdataSet* rdataset = RdataSet::create(mem_sgmt_, encoder_, aaaa_small,
                                          sig_large);
    EXPECT_EQ(RRTTL(10), restoreTTL(rdataset->getTTLData()));
    RdataSet::destroy(mem_sgmt_, rdataset, rrclass);

    // RRSIG's TTL is smaller
    SegmentObjectHolder<RdataSet, RRClass> holder1(
        mem_sgmt_,
        RdataSet::create(mem_sgmt_, encoder_, aaaa_large, sig_small), rrclass);
    EXPECT_EQ(RRTTL(10), restoreTTL(holder1.get()->getTTLData()));

    // Merging another RRset (w/o sig) that has larger TTL
    rdataset = RdataSet::create(mem_sgmt_, encoder_, aaaa_large,
                                ConstRRsetPtr(), holder1.get());
    EXPECT_EQ(RRTTL(10), restoreTTL(rdataset->getTTLData()));
    RdataSet::destroy(mem_sgmt_, rdataset, rrclass);

    // Merging another RRset (w/o sig) that has smaller TTL
    rdataset = RdataSet::create(mem_sgmt_, encoder_, aaaa_smaller,
                                ConstRRsetPtr(), holder1.get());
    EXPECT_EQ(RRTTL(5), restoreTTL(rdataset->getTTLData()));
    RdataSet::destroy(mem_sgmt_, rdataset, rrclass);

    // Merging another RRSIG (w/o RRset) that has larger TTL
    rdataset = RdataSet::create(mem_sgmt_, encoder_, ConstRRsetPtr(),
                                sig_large, holder1.get());
    EXPECT_EQ(RRTTL(10), restoreTTL(rdataset->getTTLData()));
    RdataSet::destroy(mem_sgmt_, rdataset, rrclass);

    // Merging another RRSIG (w/o RRset) that has smaller TTL
    rdataset = RdataSet::create(mem_sgmt_, encoder_, ConstRRsetPtr(),
                                sig_smaller, holder1.get());
    EXPECT_EQ(RRTTL(5), restoreTTL(rdataset->getTTLData()));
    RdataSet::destroy(mem_sgmt_, rdataset, rrclass);

    // Merging another RRset and RRSIG that have larger TTL
    rdataset = RdataSet::create(mem_sgmt_, encoder_, aaaa_large, sig_large,
                                holder1.get());
    EXPECT_EQ(RRTTL(10), restoreTTL(rdataset->getTTLData()));
    RdataSet::destroy(mem_sgmt_, rdataset, rrclass);

    // Merging another RRset and RRSIG that have smaller TTL
    rdataset = RdataSet::create(mem_sgmt_, encoder_, aaaa_smaller, sig_smaller,
                                holder1.get());
    EXPECT_EQ(RRTTL(5), restoreTTL(rdataset->getTTLData()));
    RdataSet::destroy(mem_sgmt_, rdataset, rrclass);
}
}
