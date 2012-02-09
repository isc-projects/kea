// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/exceptions.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include <dns/tests/rdata_unittest.h>

#include <boost/lexical_cast.hpp>

#include <string>

using namespace std;
using boost::lexical_cast;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {

// Template for shared tests for NSEC and NSEC3 bitmaps
template <typename RDATA_TYPE>
class NSECBitmapTest : public RdataTest {
protected:
    RDATA_TYPE fromText(const string& rdata_text) {
        return (RDATA_TYPE(rdata_text));
    }

    // These depend on the specific RR type.  We use specialized methods
    // for them.
    static RRType getType();    // return either RRType::NSEC() or NSEC3()
    static string getWireFilePrefix();
    static string getCommonText(); // commonly used part of textual form
};

typedef ::testing::Types<generic::NSEC, generic::NSEC3> TestRdataTypes;
TYPED_TEST_CASE(NSECBitmapTest, TestRdataTypes);

template <>
string
NSECBitmapTest<generic::NSEC>::getWireFilePrefix() {
    return ("rdata_nsec_");
}

template <>
RRType
NSECBitmapTest<generic::NSEC>::getType() {
    return (RRType::NSEC());
}

template <>
string
NSECBitmapTest<generic::NSEC3>::getWireFilePrefix() {
    return ("rdata_nsec3_");
}

template <>
RRType
NSECBitmapTest<generic::NSEC3>::getType() {
    return (RRType::NSEC3());
}

template <>
string
NSECBitmapTest<generic::NSEC>::getCommonText() {
    return ("next. ");
}

template <>
string
NSECBitmapTest<generic::NSEC3>::getCommonText() {
    return ("1 1 12 AABBCCDD 2T7B4G4VSA5SMI47K61MV5BV1A22BOJR ");
}

// Tests against various types of bogus NSEC/NSEC3 type bitmaps.
// The syntax and semantics are common for both RR types, and our
// implementation of that part is shared, so in theory it should be sufficient
// to test for only one RR type.  But we check for both just in case.
TYPED_TEST(NSECBitmapTest, createFromWire) {
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
TYPED_TEST(NSECBitmapTest, toText) {
    // A simple case (some commonly seen RR types in NSEC(3) bitmaps)
    string rdata_text = this->getCommonText() + "NS SOA RRSIG DNSKEY";
    EXPECT_EQ(rdata_text, this->fromText(rdata_text).toText());

    // Similar to above, but involves more than one bitmap window blocks.
    rdata_text = this->getCommonText() + "NS DLV";
    EXPECT_EQ(rdata_text, this->fromText(rdata_text).toText());

    // Make sure all possible bits in a one-octet bitmap field correctly.
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
}
