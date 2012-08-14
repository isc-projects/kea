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

#include <dns/rrset.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>

#include <datasrc/memory/rdata_encoder.h>
#include <datasrc/memory/rdataset.h>

#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

using namespace isc::dns;
using namespace isc::datasrc::memory;
using namespace isc::testutils;

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

TEST_F(RdataSetTest, create) {
    // A simple case of creating an RdataSet.  Confirming the resulting
    // fields have the expected values, and then destroying it (TearDown()
    // would detect any memory leak)
    RdataSet* rdataset = RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                          ConstRRsetPtr());
    EXPECT_FALSE(rdataset->next); // by default the next pointer should be NULL
    EXPECT_EQ(RRType::A(), rdataset->type);
    EXPECT_EQ(RRTTL(1076895760), restoreTTL(rdataset->getTTLData()));
    EXPECT_EQ(1, rdataset->getRdataCount());
    EXPECT_EQ(0, rdataset->getSigRdataCount());
    RdataSet::destroy(mem_sgmt_, RRClass::IN(), rdataset);
}

TEST_F(RdataSetTest, createWithRRSIG) {
    // Normal case.
    RdataSet* rdataset = RdataSet::create(mem_sgmt_, encoder_, a_rrset_,
                                          rrsig_rrset_);
    EXPECT_EQ(RRTTL(1076895760), restoreTTL(rdataset->getTTLData()));
    EXPECT_EQ(1, rdataset->getSigRdataCount());
    RdataSet::destroy(mem_sgmt_, RRClass::IN(), rdataset);

    // Unusual case: TTL doesn't match.  This implementation accepts that,
    // using the TTL of the covered RRset.
    ConstRRsetPtr rrsig_badttl(textToRRset(
                                   "www.example.com. 3600 IN RRSIG "
                                   "A 5 2 3600 20120814220826 "
                                   "20120715220826 1234 example.com. FAKE"));
    rdataset = RdataSet::create(mem_sgmt_, encoder_, a_rrset_, rrsig_badttl);
    EXPECT_EQ(RRTTL(1076895760), restoreTTL(rdataset->getTTLData()));
    RdataSet::destroy(mem_sgmt_, RRClass::IN(), rdataset);
}

TEST_F(RdataSetTest, createWithRRSIGOnly) {
    // A rare, but allowed, case: RdataSet without the main RRset but with
    // RRSIG.
    RdataSet* rdataset = RdataSet::create(mem_sgmt_, encoder_, ConstRRsetPtr(),
                                          rrsig_rrset_);
    EXPECT_EQ(RRType::A(), rdataset->type); // type covered is used as type
    EXPECT_EQ(RRTTL(1076895760), restoreTTL(rdataset->getTTLData()));
    EXPECT_EQ(0, rdataset->getRdataCount());
    EXPECT_EQ(1, rdataset->getSigRdataCount());
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
