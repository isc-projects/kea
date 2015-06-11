// Copyright (C) 2012, 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>
#include <util/unittests/wiredata.h>
#include <util/unittests/test_exceptions.h>

#include <string>
#include <vector>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::util;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {

// Template for shared tests for NSEC3 and NSEC3PARAM
template <typename RDATA_TYPE>
class NSEC3PARAMLikeTest : public RdataTest {
protected:
    NSEC3PARAMLikeTest() :
        salt_txt("1 1 1 D399EAAB" + getCommonText()),
        nosalt_txt("1 1 1 -" + getCommonText()),
        obuffer(0)
    {}

    RDATA_TYPE fromText(const string& rdata_text) {
        return (RDATA_TYPE(rdata_text));
    }

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

    const string salt_txt;      // RDATA text with salt
    const string nosalt_txt;    // RDATA text without salt
    OutputBuffer obuffer;       // used in toWire() tests
    MessageRenderer renderer;   // ditto
    vector<RDATA_TYPE> compare_set; // used in compare() tests

    // Convert generic Rdata to the corresponding derived Rdata class object.
    // Defined here because it depends on the template parameter.
    static const RDATA_TYPE& convert(const Rdata& rdata) {
        return (dynamic_cast<const RDATA_TYPE&>(rdata));
    }

    // These depend on the specific RR type.  We use specialized methods
    // for them.
    static RRType getType(); // return either RRType::NSEC3() or NSEC3PARAM()
    static string getWireFilePrefix();
    static string getCommonText(); // commonly used part of textual form
};

// Instantiate specific typed tests
typedef ::testing::Types<generic::NSEC3, generic::NSEC3PARAM> TestRdataTypes;
TYPED_TEST_CASE(NSEC3PARAMLikeTest, TestRdataTypes);

template <>
RRType
NSEC3PARAMLikeTest<generic::NSEC3>::getType() {
    return (RRType::NSEC3());
}

template <>
RRType
NSEC3PARAMLikeTest<generic::NSEC3PARAM>::getType() {
    return (RRType::NSEC3PARAM());
}

template <>
string
NSEC3PARAMLikeTest<generic::NSEC3>::getWireFilePrefix() {
    return ("rdata_nsec3_");
}

template <>
string
NSEC3PARAMLikeTest<generic::NSEC3PARAM>::getWireFilePrefix() {
    return ("rdata_nsec3param_");
}

template <>
string
NSEC3PARAMLikeTest<generic::NSEC3>::getCommonText() {
    // next hash + RR type bitmap
    return (" H9RSFB7FPF2L8HG35CMPC765TDK23RP6 "
            "NS SOA RRSIG DNSKEY NSEC3PARAM");
}

template <>
string
NSEC3PARAMLikeTest<generic::NSEC3PARAM>::getCommonText() {
    // there's no more text for NSEC3PARAM
    return ("");
}

TYPED_TEST(NSEC3PARAMLikeTest, fromText) {
    // Numeric parameters have possible maximum values.  Unusual, but must
    // be accepted.
    EXPECT_NO_THROW(this->fromText("255 255 65535 D399EAAB" +
                                   this->getCommonText()));

    // 0-length salt
    EXPECT_EQ(0, this->fromText(this->nosalt_txt).getSalt().size());

    // salt that has the possible max length
    EXPECT_EQ(255, this->fromText("1 1 1 " + string(255 * 2, '0') +
                                  this->getCommonText()).getSalt().size());
}

TYPED_TEST(NSEC3PARAMLikeTest, badText) {
    // Bad salt hex
    EXPECT_THROW_WITH(this->fromText("1 1 1 SPORK0" + this->getCommonText()),
                      isc::BadValue,
                      "attempt to decode a value not in base16 char set");
    EXPECT_THROW_WITH(this->fromText("1 1 1 ADDAFEE" + this->getCommonText()),
                      isc::BadValue, "Incomplete input for base16: ADDAFEE");

    // Space within salt
    EXPECT_THROW(this->fromText("1 1 1 ADDAFE ADDAFEEE" + 
                                this->getCommonText()),
                 InvalidRdataText);

    // Similar to empty salt, but not really.  This shouldn't cause confusion.
    EXPECT_THROW_WITH(this->fromText("1 1 1 --" + this->getCommonText()),
                      isc::BadValue,
                      "attempt to decode a value not in base16 char set");

    // Too large algorithm
    EXPECT_THROW_WITH(this->fromText("1000000 1 1 ADDAFEEE" +
                                     this->getCommonText()),
                      InvalidRdataText, this->getType()
                      << " hash algorithm out of range: 1000000");

    // Too large flags
    EXPECT_THROW_WITH(this->fromText("1 1000000 1 ADDAFEEE" +
                                     this->getCommonText()),
                      InvalidRdataText, this->getType()
                      << " flags out of range: 1000000");

    // Too large iterations
    EXPECT_THROW_WITH(this->fromText("1 1 65536 ADDAFEEE" + this->getCommonText()),
                      InvalidRdataText, this->getType()
                      << " iterations out of range: 65536");

    // There should be a space between "1" and "D399EAAB" (salt)
    EXPECT_THROW_WITH(this->fromText("1 1 1D399EAAB" + this->getCommonText()),
                      InvalidRdataText,
                      "Failed to construct " << this->getType()
                      << " from '1 1 1D399EAAB" << this->getCommonText()
                      << "': not a valid number");

    // Salt is too long (possible max + 1 bytes)
    EXPECT_THROW_WITH(this->fromText("1 1 1 " + string(256 * 2, '0') +
                                     this->getCommonText()),
                      InvalidRdataText, this->getType()
                      << " salt is too long: 512 (encoded) bytes");
}

TYPED_TEST(NSEC3PARAMLikeTest, toText) {
    // normal case
    EXPECT_EQ(this->salt_txt, this->fromText(this->salt_txt).toText());

    // empty salt case
    EXPECT_EQ(this->nosalt_txt, this->fromText(this->nosalt_txt).toText());
}

TYPED_TEST(NSEC3PARAMLikeTest, createFromWire) {
    // Normal case
    EXPECT_EQ(0, this->fromText(this->salt_txt).compare(
                  *this->rdataFactoryFromFile(this->getType(), RRClass::IN(),
                                              (this->getWireFilePrefix() +
                                               "fromWire1").c_str())));

    // Too short RDLENGTH: it doesn't even contain the first 5 octets.
    EXPECT_THROW_WITH(this->rdataFactoryFromFile(this->getType(),
                                                 RRClass::IN(),
                                                 (this->getWireFilePrefix() +
                                                  "fromWire2.wire").c_str()),
                      DNSMessageFORMERR,
                      this->getType() << " too short, length: 4");

    // salt length is too large
    EXPECT_THROW_WITH(this->rdataFactoryFromFile(this->getType(),
                                                 RRClass::IN(),
                                                 (this->getWireFilePrefix() +
                                                  "fromWire11.wire").c_str()),
                      DNSMessageFORMERR,
                      this->getType() << " salt length is too large: 5");

    // empty salt.  not so usual, but valid.
    ConstRdataPtr rdata =
        this->rdataFactoryFromFile(this->getType(), RRClass::IN(),
                                   (this->getWireFilePrefix() +
                                    "fromWire13.wire").c_str());
    EXPECT_EQ(0, this->convert(*rdata).getSalt().size());
}

TYPED_TEST(NSEC3PARAMLikeTest, createFromLexer) {
    EXPECT_EQ(0, this->fromText(this->salt_txt).compare(
        *test::createRdataUsingLexer(this->getType(), RRClass::IN(),
                                     this->salt_txt)));

    // Exceptions cause NULL to be returned.
    EXPECT_FALSE(test::createRdataUsingLexer(this->getType(), RRClass::IN(),
                                             "1000000 1 1 ADDAFEEE" +
                                             this->getCommonText()));
}

template <typename OUTPUT_TYPE>
void
toWireCheck(RRType rrtype, OUTPUT_TYPE& output, const string& data_file) {
    vector<uint8_t> data;
    UnitTestUtil::readWireData(data_file.c_str(), data);
    InputBuffer buffer(&data[0], data.size());
    const uint16_t rdlen = buffer.readUint16();

    output.clear();
    output.writeUint16(rdlen);
    createRdata(rrtype, RRClass::IN(), buffer, rdlen)->toWire(output);
    matchWireData(&data[0], data.size(),
                  output.getData(), output.getLength());
}

TYPED_TEST(NSEC3PARAMLikeTest, toWire) {
    // normal case
    toWireCheck(this->getType(), this->renderer,
                this->getWireFilePrefix() + "fromWire1");
    toWireCheck(this->getType(), this->obuffer,
                this->getWireFilePrefix() + "fromWire1");

    // empty salt
    toWireCheck(this->getType(), this->renderer,
                this->getWireFilePrefix() + "fromWire13.wire");
    toWireCheck(this->getType(), this->obuffer,
                this->getWireFilePrefix() + "fromWire13.wire");
}

TYPED_TEST(NSEC3PARAMLikeTest, compare) {
    // test RDATAs, sorted in the ascendent order.
    this->compare_set.push_back(this->fromText("0 0 0 D399EAAB" +
                                               this->getCommonText()));
    this->compare_set.push_back(this->fromText("1 0 0 D399EAAB" +
                                               this->getCommonText()));
    this->compare_set.push_back(this->fromText("1 1 0 D399EAAB" +
                                               this->getCommonText()));
    this->compare_set.push_back(this->fromText("1 1 1 -" +
                                               this->getCommonText()));
    this->compare_set.push_back(this->fromText("1 1 1 D399EAAB" +
                                               this->getCommonText()));
    this->compare_set.push_back(this->fromText("1 1 1 FF99EAAB" +
                                               this->getCommonText()));
    this->compare_set.push_back(this->fromText("1 1 1 FF99EA0000" +
                                               this->getCommonText()));

    this->compareCheck();
}

}
