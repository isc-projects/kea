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

#include <datasrc/memory/rdata_encoder.h>
#include <datasrc/memory/rdata_reader.h>
#include <datasrc/memory/rdataset.h>

#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>

#include <string>

using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc::memory;
using namespace isc::testutils;
using boost::lexical_cast;

namespace {

class RdataSetTest : public ::testing::Test {
protected:
    RdataSetTest() :
        // 1076895760 = 0x40302010.  Use this so we fill in all 8-bit "field"
        // of the 32-bit TTL
        a_rrset_(textToRRset("www.example.com. 1076895760 IN A 192.0.2.1")),
        rrsig_rrset_(textToRRset("www.example.com. 1076895760 IN RRSIG "
                                 "A 5 2 3600 20120814220826 20120715220826 "
                                 "1234 example.com. FAKE"))
    {}
    void TearDown() {
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated());
    }

    ConstRRsetPtr a_rrset_, rrsig_rrset_;
    isc::util::MemorySegmentLocal mem_sgmt_;
    RdataEncoder encoder_;
};

// Convert the given 32-bit integer (network byte order) to the corresponding
// RRTTL object.
RRTTL
restoreTTL(const void* ttl_data) {
    isc::util::InputBuffer b(ttl_data, sizeof(uint32_t));
    return (RRTTL(b));
}

// A helper callback for checkRdataSet.  This confirms the given data
// is the expected in::A RDATA (the value is taken from the RdataSetTest
// constructor).
void
checkData(const uint8_t* data, size_t size) {
    isc::util::InputBuffer b(data, size);
    EXPECT_EQ(0, in::A(b, size).compare(in::A("192.0.2.1")));
}

// This is a set of checks for an RdataSet created with some simple
// conditions.  with_rrset/with_rrsig is true iff the RdataSet is supposed to
// contain normal/RRSIG RDATA.
void
checkRdataSet(const RdataSet& rdataset, bool with_rrset, bool with_rrsig) {
    EXPECT_FALSE(rdataset.next); // by default the next pointer should be NULL
    EXPECT_EQ(RRType::A(), rdataset.type);
    // See the RdataSetTest constructor for the magic number.
    EXPECT_EQ(RRTTL(1076895760), restoreTTL(rdataset.getTTLData()));
    EXPECT_EQ(with_rrset ? 1 : 0, rdataset.getRdataCount());
    EXPECT_EQ(with_rrsig ? 1 : 0, rdataset.getSigRdataCount());

    // A simple test for the data content.  Details tests for the encoder/
    // reader should be basically sufficient for various cases of the data,
    // and the fact that this test doesn't detect memory leak should be
    // reasonably sufficient that the implementation handles the data region
    // correctly.  Here we check one simple case for a simple form of RDATA,
    // mainly for checking the behavior of getDataBuf().
    RdataReader reader(RRClass::IN(), RRType::A(),
                       reinterpret_cast<const uint8_t*>(
                           rdataset.getDataBuf()),
                       rdataset.getRdataCount(), rdataset.getSigRdataCount(),
                       &RdataReader::emptyNameAction, checkData);
    reader.iterate();
}

TEST_F(RdataSetTest, create) {
    // A simple case of creating an RdataSet.  Confirming the resulting
    // fields have the expected values, and then destroying it (TearDown()
    // would detect any memory leak)
    RdataSet* rdataset = RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                          ConstRRsetPtr());
    checkRdataSet(*rdataset, true, false);
    RdataSet::destroy(mem_sgmt_, RRClass::IN(), rdataset);
}

// A helper function to create an RRset containing the given number of
// unique RDATAs.
ConstRRsetPtr
getRRsetWithRdataCount(size_t rdata_count) {
    RRsetPtr rrset(new RRset(Name("example.com"), RRClass::IN(), RRType::TXT(),
                             RRTTL(3600)));
    for (size_t i = 0; i < rdata_count; ++i) {
        rrset->addRdata(rdata::createRdata(RRType::TXT(), RRClass::IN(),
                                           lexical_cast<std::string>(i)));
    }
    return (rrset);
}

TEST_F(RdataSetTest, createManyRRs) {
    // RRset with possible maximum number of RDATAs
    RdataSet* rdataset = RdataSet::create(mem_sgmt_, encoder_,
                                          getRRsetWithRdataCount(8191),
                                          ConstRRsetPtr());
    EXPECT_EQ(8191, rdataset->getRdataCount());
    EXPECT_EQ(0, rdataset->getSigRdataCount());
    RdataSet::destroy(mem_sgmt_, RRClass::IN(), rdataset);

    // Exceeding that will result in an exception.
    EXPECT_THROW(RdataSet::create(mem_sgmt_, encoder_,
                                  getRRsetWithRdataCount(8192),
                                  ConstRRsetPtr()),
                 RdataSetError);
}

TEST_F(RdataSetTest, createWithRRSIG) {
    // Normal case.
    RdataSet* rdataset = RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                          rrsig_rrset_);
    checkRdataSet(*rdataset, true, true);
    RdataSet::destroy(mem_sgmt_, RRClass::IN(), rdataset);

    // Unusual case: TTL doesn't match.  This implementation accepts that,
    // using the TTL of the covered RRset.
    ConstRRsetPtr rrsig_badttl(textToRRset(
                                   "www.example.com. 3600 IN RRSIG "
                                   "A 5 2 3600 20120814220826 "
                                   "20120715220826 1234 example.com. FAKE"));
    rdataset = RdataSet::create(mem_sgmt_, encoder_, a_rrset_, rrsig_badttl);
    checkRdataSet(*rdataset, true, true);
    RdataSet::destroy(mem_sgmt_, RRClass::IN(), rdataset);
}

// A helper function to create an RRSIG RRset containing the given number of
// unique RDATAs.
ConstRRsetPtr
getRRSIGWithRdataCount(size_t sig_count) {
    RRsetPtr rrset(new RRset(Name("example.com"), RRClass::IN(),
                             RRType::RRSIG(), RRTTL(3600)));
    for (size_t i = 0; i < sig_count; ++i) {
        rrset->addRdata(rdata::createRdata(
                            RRType::RRSIG(), RRClass::IN(),
                            "A 5 2 3600 20120814220826 20120715220826 " +
                            lexical_cast<std::string>(i) +
                            " example.com. FAKE"));
    }
    return (rrset);
}

TEST_F(RdataSetTest, createManyRRSIGs) {
    // 7 has a special meaning in the implementation: if the number of the
    // RRSIGs reaches this value, an extra 'sig count' field will be created.
    RdataSet* rdataset = RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                          getRRSIGWithRdataCount(7));
    EXPECT_EQ(7, rdataset->getSigRdataCount());
    RdataSet::destroy(mem_sgmt_, RRClass::IN(), rdataset);

    // 8 would cause overflow in the normal 3-bit field if there were no extra
    // count field.
    rdataset = RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                getRRSIGWithRdataCount(8));
    EXPECT_EQ(8, rdataset->getSigRdataCount());
    RdataSet::destroy(mem_sgmt_, RRClass::IN(), rdataset);

    // Up to 2^16-1 RRSIGs are allowed (although that would be useless
    // in practice)
    rdataset = RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                getRRSIGWithRdataCount(65535));
    EXPECT_EQ(65535, rdataset->getSigRdataCount());
    RdataSet::destroy(mem_sgmt_, RRClass::IN(), rdataset);

    // Exceeding this limit will result in an exception.
    EXPECT_THROW(RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                  getRRSIGWithRdataCount(65536)),
                 RdataSetError);
}

TEST_F(RdataSetTest, createWithRRSIGOnly) {
    // A rare, but allowed, case: RdataSet without the main RRset but with
    // RRSIG.
    RdataSet* rdataset = RdataSet::create(mem_sgmt_, encoder_, ConstRRsetPtr(),
                                          rrsig_rrset_);
    checkRdataSet(*rdataset, false, true);
    RdataSet::destroy(mem_sgmt_, RRClass::IN(), rdataset);
}

TEST_F(RdataSetTest, badCeate) {
    // Neither the RRset nor RRSIG RRset is given
    EXPECT_THROW(RdataSet::create(mem_sgmt_, encoder_, ConstRRsetPtr(),
                                  ConstRRsetPtr()), isc::BadValue);

    // Empty RRset (An RRset without RDATA)
    ConstRRsetPtr empty_rrset(new RRset(Name("example.com"), RRClass::IN(),
                                        RRType::A(), RRTTL(3600)));
    EXPECT_THROW(RdataSet::create(mem_sgmt_, encoder_, empty_rrset,
                                  ConstRRsetPtr()), isc::BadValue);
    ConstRRsetPtr empty_rrsig(new RRset(Name("example.com"), RRClass::IN(),
                                        RRType::RRSIG(), RRTTL(3600)));
    EXPECT_THROW(RdataSet::create(mem_sgmt_, encoder_, ConstRRsetPtr(),
                                  empty_rrsig), isc::BadValue);

    // The RRset type and RRSIG's type covered don't match
    ConstRRsetPtr bad_rrsig(textToRRset(
                                "www.example.com. 1076895760 IN RRSIG "
                                "NS 5 2 3600 20120814220826 20120715220826 "
                                "1234 example.com. FAKE"));
    EXPECT_THROW(RdataSet::create(mem_sgmt_, encoder_, a_rrset_, bad_rrsig),
                 isc::BadValue);

    // Pass non RRSIG for the sig parameter
    EXPECT_THROW(RdataSet::create(mem_sgmt_, encoder_, a_rrset_, a_rrset_),
                 isc::BadValue);

    // Pass RRSIG for normal RRset (the RdataEncoder will catch this and throw)
    EXPECT_THROW(RdataSet::create(mem_sgmt_, encoder_, rrsig_rrset_,
                                  rrsig_rrset_),
                 isc::BadValue);

    // RR class doesn't match between RRset and RRSIG
    ConstRRsetPtr badclass_rrsig(textToRRset(
                                     "www.example.com. 1076895760 CH RRSIG "
                                     "A 5 2 3600 20120814220826 "
                                     "20120715220826 1234 example.com. FAKE",
                                     RRClass::CH()));
    EXPECT_THROW(RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                  badclass_rrsig),
                 isc::BadValue);
}
}
