// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dns/tests/unittest_util.h>

#include <dns/exceptions.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include <dns/tests/rdata_unittest.h>
#include <util/unittests/wiredata.h>

#include <boost/lexical_cast.hpp>

#include <string>
#include <vector>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::util;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;
using boost::lexical_cast;

namespace {

// Template for shared tests for NSEC and NSEC3 bitmaps
template <typename RDATA_TYPE>
class NSECLikeBitmapTest : public RdataTest {
protected:
    RDATA_TYPE fromText(const string& rdata_text) {
        return (RDATA_TYPE(rdata_text));
    }

    vector<RDATA_TYPE> compare_set; // used in compare() tests

    void compareCheck() const {
        typename vector<RDATA_TYPE>::const_iterator it;
        typename vector<RDATA_TYPE>::const_iterator const it_end =
            compare_set.end();
        for (it = compare_set.begin(); it != it_end - 1; ++it) {
            SCOPED_TRACE("compare " + it->toText() + " to " +
                         (it + 1)->toText());
            EXPECT_GT(0, (*it).compare(*(it + 1)));
            EXPECT_LT(0, (*(it + 1)).compare(*it));
        }
    }

    // These depend on the specific RR type.  We use specialized methods
    // for them.
    static RRType getType();    // return either RRType::NSEC() or NSEC3()
    static string getWireFilePrefix();
    static string getCommonText(); // commonly used part of textual form
};

// Instantiate specific typed tests
typedef ::testing::Types<generic::NSEC, generic::NSEC3> TestRdataTypes;
TYPED_TEST_CASE(NSECLikeBitmapTest, TestRdataTypes);

// NSEC and NSEC3 bitmaps have some subtle differences, in which case we
// need to test them separately.  Using these typedef type names with TEST_F
// will do the trick.
typedef NSECLikeBitmapTest<generic::NSEC3> NSEC3BitmapTest;
typedef NSECLikeBitmapTest<generic::NSEC> NSECBitmapTest;

template <>
string
NSECLikeBitmapTest<generic::NSEC>::getWireFilePrefix() {
    return ("rdata_nsec_");
}

template <>
RRType
NSECLikeBitmapTest<generic::NSEC>::getType() {
    return (RRType::NSEC());
}

template <>
string
NSECLikeBitmapTest<generic::NSEC3>::getWireFilePrefix() {
    return ("rdata_nsec3_");
}

template <>
RRType
NSECLikeBitmapTest<generic::NSEC3>::getType() {
    return (RRType::NSEC3());
}

template <>
string
NSECLikeBitmapTest<generic::NSEC>::getCommonText() {
    return ("next. ");
}

template <>
string
NSECLikeBitmapTest<generic::NSEC3>::getCommonText() {
    return ("1 1 12 AABBCCDD 2T7B4G4VSA5SMI47K61MV5BV1A22BOJR ");
}

// Tests against various types of bogus NSEC/NSEC3 type bitmaps.
// The syntax and semantics are common for both RR types, and our
// implementation of that part is shared, so in theory it should be sufficient
// to test for only one RR type.  But we check for both just in case.
TYPED_TEST(NSECLikeBitmapTest, createFromWire) {
    // A malformed NSEC bitmap length field that could cause overflow.
    EXPECT_THROW(this->rdataFactoryFromFile(this->getType(), RRClass::IN(),
                                            (this->getWireFilePrefix() +
                                             "fromWire4.wire").c_str()),
                 DNSMessageFORMERR);

    // The bitmap field is incomplete (only the first byte is included)
    EXPECT_THROW(this->rdataFactoryFromFile(this->getType(), RRClass::IN(),
                                            (this->getWireFilePrefix() +
                                             "fromWire5.wire").c_str()),
                 DNSMessageFORMERR);

    // Bitmap length is 0, which is invalid.
    EXPECT_THROW(this->rdataFactoryFromFile(this->getType(), RRClass::IN(),
                                            (this->getWireFilePrefix() +
                                             "fromWire6.wire").c_str()),
                 DNSMessageFORMERR);

    // Too large bitmap length with a short buffer.
    EXPECT_THROW(this->rdataFactoryFromFile(this->getType(), RRClass::IN(),
                                            (this->getWireFilePrefix() +
                                             "fromWire3").c_str()),
                 DNSMessageFORMERR);

    // A boundary case: longest possible bitmaps (32 maps).  This should be
    // accepted.
    EXPECT_NO_THROW(this->rdataFactoryFromFile(this->getType(), RRClass::IN(),
                                               (this->getWireFilePrefix() +
                                                "fromWire7.wire").c_str()));

    // Another boundary condition: 33 bitmaps, which should be rejected.
    EXPECT_THROW(this->rdataFactoryFromFile(this->getType(), RRClass::IN(),
                                            (this->getWireFilePrefix() +
                                             "fromWire8.wire").c_str()),
                 DNSMessageFORMERR);

    // Disordered bitmap window blocks.
    EXPECT_THROW(this->rdataFactoryFromFile(this->getType(), RRClass::IN(),
                                            (this->getWireFilePrefix() +
                                             "fromWire9.wire").c_str()),
                 DNSMessageFORMERR);

    // Bitmap ending with all-zero bytes.  Not necessarily harmful except
    // the additional overhead of parsing, but invalid according to the
    // spec anyway.
    EXPECT_THROW(this->rdataFactoryFromFile(this->getType(), RRClass::IN(),
                                            (this->getWireFilePrefix() +
                                             "fromWire10.wire").c_str()),
                 DNSMessageFORMERR);
}

// This tests the result of toText() with various kinds of NSEC/NSEC3 bitmaps.
// It also tests the "from text" constructor as a result.
TYPED_TEST(NSECLikeBitmapTest, toText) {
    // A simple case (some commonly seen RR types in NSEC(3) bitmaps)
    string rdata_text = this->getCommonText() + "NS SOA RRSIG DNSKEY";
    EXPECT_EQ(rdata_text, this->fromText(rdata_text).toText());

    // Similar to above, but involves more than one bitmap window blocks.
    rdata_text = this->getCommonText() + "NS DLV";
    EXPECT_EQ(rdata_text, this->fromText(rdata_text).toText());

    // Make sure all possible bits in a one-octet bitmap field are handled
    // correctly.
    // We use the range around 1024 (reasonably higher number) so it's
    // unlikely that they have predefined mnemonic and can be safely converted
    // to TYPEnnnn by toText().
    for (unsigned int i = 1024; i < 1032; ++i) {
        rdata_text = this->getCommonText() + "TYPE" + lexical_cast<string>(i);
        EXPECT_EQ(rdata_text, this->fromText(rdata_text).toText());
    }

    // Make sure all possible 32 octets in a longest possible block are
    // handled correctly.
    for (unsigned int i = 1024; i < 1024 + 256; i += 8) {
        rdata_text = this->getCommonText() + "TYPE" + lexical_cast<string>(i);
        EXPECT_EQ(rdata_text, this->fromText(rdata_text).toText());
    }

    // Check for the highest window block.
    rdata_text = this->getCommonText() + "TYPE65535";
    EXPECT_EQ(rdata_text, this->fromText(rdata_text).toText());
}

TYPED_TEST(NSECLikeBitmapTest, compare) {
    // Bit map: [win=0][len=1] 00000010
    this->compare_set.push_back(this->fromText(this->getCommonText() + "SOA"));
    // Bit map: [win=0][len=1] 00000010, [win=4][len=1] 10000000
    this->compare_set.push_back(this->fromText(this->getCommonText() +
                                               "SOA TYPE1024"));
    // Bit map: [win=0][len=1] 00100000
    this->compare_set.push_back(this->fromText(this->getCommonText() + "NS"));
    // Bit map: [win=0][len=1] 00100010
    this->compare_set.push_back(this->fromText(this->getCommonText() +
                                               "NS SOA"));
    // Bit map: [win=0][len=2] 00100000, 00000001
    this->compare_set.push_back(this->fromText(this->getCommonText() +
                                               "NS MX"));
    // Bit map: [win=4][len=1] 10000000
    this->compare_set.push_back(this->fromText(this->getCommonText() +
                                               "TYPE1024"));

    this->compareCheck();
}

// NSEC bitmaps must not be empty
TEST_F(NSECBitmapTest, emptyMap) {
    EXPECT_THROW(this->fromText("next.example.").toText(), InvalidRdataText);

    EXPECT_THROW(this->rdataFactoryFromFile(this->getType(), RRClass::IN(),
                                            (this->getWireFilePrefix() +
                                             "fromWire16.wire").c_str()),
                 DNSMessageFORMERR);
}

// NSEC3 bitmaps can be empty
TEST_F(NSEC3BitmapTest, emptyMap) {
    // Read wire data wit an empty NSEC3 bitmap.  This should succeed.
    vector<uint8_t> data;
    UnitTestUtil::readWireData((this->getWireFilePrefix() +
                                "fromWire16.wire").c_str(), data);
    InputBuffer buffer(&data[0], data.size());
    const uint16_t rdlen = buffer.readUint16();
    const generic::NSEC3 empty_nsec3 =
        dynamic_cast<const generic::NSEC3&>(*createRdata(
                                                RRType::NSEC3(), RRClass::IN(),
                                                buffer, rdlen));

    // Check the toText() result.
    EXPECT_EQ("1 0 1 7373737373 D1K6GQ38D1K6GQ38D1K6GQ38D1K6GQ38",
              empty_nsec3.toText());

    // Check the toWire() result.
    OutputBuffer obuffer(0);
    obuffer.writeUint16(rdlen);
    empty_nsec3.toWire(obuffer);
    matchWireData(&data[0], data.size(),
                  obuffer.getData(), obuffer.getLength());

    // Same for MessageRenderer.
    obuffer.clear();
    MessageRenderer renderer;
    renderer.writeUint16(rdlen);
    empty_nsec3.toWire(renderer);
    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());
}

}
