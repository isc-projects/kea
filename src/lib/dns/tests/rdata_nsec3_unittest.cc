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

#include <string>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <util/encode/hex.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::dns::rdata;

namespace {

// Note: some tests can be shared with NSEC3PARAM.  They are unified as
// typed tests defined in nsec3param_like_unittest.
class Rdata_NSEC3_Test : public RdataTest {
    // there's nothing to specialize
public:
    Rdata_NSEC3_Test() :
        nsec3_txt("1 1 1 D399EAAB H9RSFB7FPF2L8HG35CMPC765TDK23RP6 "
                  "NS SOA RRSIG DNSKEY NSEC3PARAM"),
        nsec3_nosalt_txt("1 1 1 - H9RSFB7FPF2L8HG35CMPC765TDK23RP6 A" )
    {}
    const string nsec3_txt;
    const string nsec3_nosalt_txt;
};

TEST_F(Rdata_NSEC3_Test, fromText) {
    // A normal case: the test constructor should successfully parse the
    // text and construct nsec3_txt.  It will be tested against the wire format
    // representation in the createFromWire test.

    // hash that has the possible max length (see badText about the magic
    // numbers)
    EXPECT_EQ(255, generic::NSEC3("1 1 1 D399EAAB " +
                                  string((255 * 8) / 5, '0') +
                                  " NS").getNext().size());

    // type bitmap is empty.  it's possible and allowed for NSEC3.
    EXPECT_NO_THROW(generic::NSEC3(
                        "1 1 1 D399EAAB H9RSFB7FPF2L8HG35CMPC765TDK23RP6"));
}

TEST_F(Rdata_NSEC3_Test, badText) {
    EXPECT_THROW(generic::NSEC3("1 1 1 ADDAFEEE "
                                "0123456789ABCDEFGHIJKLMNOPQRSTUV "
                                "BIFF POW SPOON"),
                 InvalidRdataText);
    EXPECT_THROW(generic::NSEC3("1 1 1 ADDAFEEE "
                                "WXYZWXYZWXYZ=WXYZWXYZ==WXYZWXYZW A NS SOA"),
                 BadValue);     // bad base32hex
    EXPECT_THROW(generic::NSEC3("1 1 1000000 ADDAFEEE "
                                "0123456789ABCDEFGHIJKLMNOPQRSTUV A NS SOA"),
                 InvalidRdataText);

    // Next hash shouldn't be padded
    EXPECT_THROW(generic::NSEC3("1 1 1 ADDAFEEE CPNMU=== A NS SOA"),
                 InvalidRdataText);

    // Hash is too long.  Max = 255 bytes, base32-hex converts each 5 bytes
    // of the original to 8 characters, so 260 * 8 / 5 is the smallest length
    // of the encoded string that exceeds the max and doesn't require padding.
    EXPECT_THROW(generic::NSEC3("1 1 1 D399EAAB " + string((260 * 8) / 5, '0') +
                                " NS"),
                 InvalidRdataText);
}

TEST_F(Rdata_NSEC3_Test, createFromWire) {
    // A valid NSEC3 RR with empty type bitmap.
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                         "rdata_nsec3_fromWire15.wire"));

    // Invalid bitmap cases are tested in Rdata_NSECBITMAP_Test.

    // hash length is too large
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                      "rdata_nsec3_fromWire12.wire"),
                 DNSMessageFORMERR);

    // empty hash.  invalid.
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                      "rdata_nsec3_fromWire14.wire"),
                 DNSMessageFORMERR);

    // RDLEN is too short to hold the hash length field
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                      "rdata_nsec3_fromWire17.wire"),
                 DNSMessageFORMERR);

    // Short buffer cases.  The data is valid NSEC3 RDATA, but the buffer
    // is trimmed at the end.  All cases should result in an exception from
    // the buffer class.
    vector<uint8_t> data;
    UnitTestUtil::readWireData("rdata_nsec3_fromWire1", data);
    const uint16_t rdlen = (data.at(0) << 8) + data.at(1);
    for (int i = 0; i < rdlen; ++i) {
        // intentionally construct a short buffer
        InputBuffer b(&data[0] + 2, i);
        EXPECT_THROW(createRdata(RRType::NSEC3(), RRClass::IN(), b, 39),
                     InvalidBufferPosition);
    }
}

TEST_F(Rdata_NSEC3_Test, createFromLexer) {
    const generic::NSEC3 rdata_nsec3(nsec3_txt);
    EXPECT_EQ(0, rdata_nsec3.compare(
        *test::createRdataUsingLexer(RRType::NSEC3(), RRClass::IN(),
                                     nsec3_txt)));

    // Check that bad input throws as usual (next hash shouldn't be
    // padded)
    EXPECT_THROW({
        *test::createRdataUsingLexer(RRType::NSEC3(), RRClass::IN(),
                                     "1 1 1 ADDAFEEE CPNMU=== A NS SOA");
    }, InvalidRdataText);
}

TEST_F(Rdata_NSEC3_Test, assign) {
    generic::NSEC3 rdata_nsec3(nsec3_txt);
    generic::NSEC3 other_nsec3 = rdata_nsec3;
    EXPECT_EQ(0, rdata_nsec3.compare(other_nsec3));
}

TEST_F(Rdata_NSEC3_Test, compare) {
    // trivial case: self equivalence
    EXPECT_EQ(0, generic::NSEC3(nsec3_txt).compare(generic::NSEC3(nsec3_txt)));

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(generic::NSEC3(nsec3_txt).compare(*rdata_nomatch),
                 bad_cast);

    // test RDATAs, sorted in the ascendent order.  We only check comparison
    // on NSEC3-specific fields.  Bitmap comparison is tested in the bitmap
    // tests.  Common cases for NSEC3 and NSECPARAM3 are in their shared tests.
    vector<generic::NSEC3> compare_set;
    compare_set.push_back(generic::NSEC3("1 1 1 FF99EA0000 D1K6GQ38"));
    compare_set.push_back(generic::NSEC3("1 1 1 FF99EA0000 D1K6GQ0000000000"));
    compare_set.push_back(generic::NSEC3("1 1 1 FF99EA0000 D1K6GQ00UUUUUUUU"));

    vector<generic::NSEC3>::const_iterator it;
    const vector<generic::NSEC3>::const_iterator it_end = compare_set.end();
    for (it = compare_set.begin(); it != it_end - 1; ++it) {
        SCOPED_TRACE("compare " + it->toText() + " to " + (it + 1)->toText());
        EXPECT_GT(0, (*it).compare(*(it + 1)));
        EXPECT_LT(0, (*(it + 1)).compare(*it));
    }
}

}
