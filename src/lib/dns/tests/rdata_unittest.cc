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

#include <vector>
#include <string>
#include <sstream>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;

namespace isc {
namespace dns {
namespace rdata {
RdataTest::RdataTest() :
    obuffer(0), rdata_nomatch(createRdata(RRType(0), RRClass(1), "\\# 0"))
{}

RdataPtr
RdataTest::rdataFactoryFromFile(const RRType& rrtype, const RRClass& rrclass,
                                const char* datafile, size_t position)
{
    std::vector<unsigned char> data;
    UnitTestUtil::readWireData(datafile, data);

    InputBuffer buffer(&data[0], data.size());
    buffer.setPosition(position);

    uint16_t rdlen = buffer.readUint16();
    return (createRdata(rrtype, rrclass, buffer, rdlen));
}

namespace test {

void
dummyCallback(const string&, size_t, const string&) {
}

RdataPtr
createRdataUsingLexer(const RRType& rrtype, const RRClass& rrclass,
                      const std::string& str)
{
    std::stringstream ss(str);
    MasterLexer lexer;
    lexer.pushSource(ss);

    const MasterLoaderCallbacks::IssueCallback callback
        (boost::bind(&dummyCallback, _1, _2, _3));
    MasterLoaderCallbacks callbacks(callback, callback);
    const Name origin("example.org.");

    return (createRdata(rrtype, rrclass, lexer, &origin,
                        MasterLoader::MANY_ERRORS, callbacks));
}

} // end of namespace isc::dns::rdata::test

// A mock class to check parameters passed via loader callbacks.  Its callback
// records the passed parameters, allowing the test to check them later via
// the check() method.
class CreateRdataCallback {
public:
    enum CallbackType { NONE, ERROR, WARN };
    CreateRdataCallback() : type_(NONE), line_(0) {}
    void callback(CallbackType type, const string& source, size_t line,
                  const string& reason_txt) {
        type_ = type;
        source_ = source;
        line_ = line;
        reason_txt_ = reason_txt;
    }

    void clear() {
        type_ = NONE;
        source_.clear();
        line_ = 0;
        reason_txt_.clear();
    }

    void check(const string& expected_srcname, size_t expected_line,
               CallbackType expected_type, const string& expected_reason)
    {
        EXPECT_EQ(expected_srcname, source_);
        EXPECT_EQ(expected_line, line_);
        EXPECT_EQ(expected_type, type_);
        EXPECT_EQ(expected_reason, reason_txt_);
    }

private:
    CallbackType type_;
    string source_;
    size_t line_;
    string reason_txt_;
};

// Test class/type-independent behavior of createRdata().
TEST_F(RdataTest, createRdataWithLexer) {
    const in::AAAA aaaa_rdata("2001:db8::1");

    stringstream ss;
    const string src_name = "stream-" + boost::lexical_cast<string>(&ss);
    ss << aaaa_rdata.toText() << "\n"; // valid case
    ss << aaaa_rdata.toText() << " extra-token\n"; // extra token
    lexer.pushSource(ss);

    CreateRdataCallback callback;
    MasterLoaderCallbacks callbacks(
        boost::bind(&CreateRdataCallback::callback, &callback,
                    CreateRdataCallback::ERROR, _1, _2, _3),
        boost::bind(&CreateRdataCallback::callback, &callback,
                    CreateRdataCallback::WARN,  _1, _2, _3));
    ConstRdataPtr rdata = createRdata(RRType::AAAA(), RRClass::IN(), lexer,
                                      NULL, MasterLoader::MANY_ERRORS,
                                      callbacks);
    EXPECT_EQ(0, aaaa_rdata.compare(*rdata));

    callback.clear();
    EXPECT_FALSE(createRdata(RRType::AAAA(), RRClass::IN(), lexer, NULL,
                             MasterLoader::MANY_ERRORS, callbacks));
    callback.check(src_name, 2, CreateRdataCallback::ERROR,
                   "createRdata from text failed near 'extra-token': "
                   "extra input text");
}

}
}
}

namespace {
class Rdata_Unknown_Test : public RdataTest {
protected:
    static string getLongestRdataTxt();
    static void getLongestRdataWire(vector<uint8_t>& v);
};

string
Rdata_Unknown_Test::getLongestRdataTxt() {
    ostringstream oss;

    oss << "\\# " << MAX_RDLENGTH << " ";
    oss.fill('0');
    oss << right << hex;
    for (int i = 0; i < MAX_RDLENGTH; i++) {
        oss << setw(2) << (i & 0xff);
    }

    return (oss.str());
}

void
Rdata_Unknown_Test::getLongestRdataWire(vector<uint8_t>& v) {
    unsigned char ch = 0;
    for (int i = 0; i < MAX_RDLENGTH; ++i, ++ch) {
        v.push_back(ch);
    }
}

const string rdata_unknowntxt("\\# 4 a1b2c30d");
const generic::Generic rdata_unknown(rdata_unknowntxt);
// Wire-format data correspond to rdata_unknown.  Note that it doesn't include
// RDLENGTH
const uint8_t wiredata_unknown[] = { 0xa1, 0xb2, 0xc3, 0x0d };

// "Unknown" RR Type used for the test cases below.  If/when we use this
// type number as a "well-known" (probably experimental) type, we'll need to
// renumber it.
const RRType unknown_rrtype = RRType(65000);

TEST_F(Rdata_Unknown_Test, createFromText) {
    // valid construction.  This also tests a normal case of "FromWire".
    EXPECT_EQ(0, generic::Generic("\\# 4 a1b2c30d").compare(
                  *rdataFactoryFromFile(unknown_rrtype, RRClass::IN(),
                                        "rdata_unknown_fromWire")));
    // upper case hexadecimal digits should also be okay. 
    EXPECT_EQ(0, generic::Generic("\\# 4 A1B2C30D").compare(
                  *rdataFactoryFromFile(unknown_rrtype, RRClass::IN(),
                                        "rdata_unknown_fromWire")));
    // 0-length RDATA should be accepted
    EXPECT_EQ(0, generic::Generic("\\# 0").compare(
                  *rdataFactoryFromFile(unknown_rrtype, RRClass::IN(),
                                        "rdata_unknown_fromWire", 6)));
    // hex encoding can be space-separated
    EXPECT_EQ(0, generic::Generic("\\# 4 a1 b2c30d").compare(rdata_unknown));
    EXPECT_EQ(0, generic::Generic("\\# 4 a1b2 c30d").compare(rdata_unknown));
    EXPECT_EQ(0, generic::Generic("\\# 4 a1 b2 c3 0d").compare(rdata_unknown));
    EXPECT_EQ(0, generic::Generic("\\# 4 a1\tb2c3 0d").compare(rdata_unknown));

    // Max-length RDATA
    vector<uint8_t> v;
    getLongestRdataWire(v);
    InputBuffer ibuffer(&v[0], v.size());
    EXPECT_EQ(0, generic::Generic(getLongestRdataTxt()).compare(
                  generic::Generic(ibuffer, v.size())));

    // the length field must match the encoding data length.
    EXPECT_THROW(generic::Generic("\\# 4 1080c0ff00"), InvalidRdataLength);
    EXPECT_THROW(generic::Generic("\\# 5 1080c0ff"), InvalidRdataLength);
    // RDATA encoding part must consist of an even number of hex digits.
    EXPECT_THROW(generic::Generic("\\# 1 1"), InvalidRdataText);
    EXPECT_THROW(generic::Generic("\\# 1 ax"), InvalidRdataText);
    // the length should be 16-bit unsigned integer
    EXPECT_THROW(generic::Generic("\\# 65536 a1b2c30d"), InvalidRdataLength);
    EXPECT_THROW(generic::Generic("\\# -1 a1b2c30d"), InvalidRdataLength);
    EXPECT_THROW(generic::Generic("\\# 1.1 a1"), InvalidRdataText);
    EXPECT_THROW(generic::Generic("\\# 0a 00010203040506070809"),
                 InvalidRdataText);
    // should reject if the special token is missing.
    EXPECT_THROW(generic::Generic("4 a1b2c30d"), InvalidRdataText);
    // the special token, the RDLENGTH and the data must be space separated.
    EXPECT_THROW(generic::Generic("\\#0"), InvalidRdataText);
    EXPECT_THROW(generic::Generic("\\# 1ff"), InvalidRdataText);
}

TEST_F(Rdata_Unknown_Test, createFromWire) {
    // normal case (including 0-length data) is covered in createFromText.

    // buffer too short.  the error should be detected in buffer read
    EXPECT_THROW(rdataFactoryFromFile(unknown_rrtype, RRClass::IN(),
                                      "rdata_unknown_fromWire", 8),
                 InvalidBufferPosition);

    // too large data
    vector<uint8_t> v;
    getLongestRdataWire(v);
    v.push_back(0);             // making it too long
    InputBuffer ibuffer(&v[0], v.size());
    EXPECT_THROW(generic::Generic(ibuffer, v.size()), InvalidRdataLength);
}

// The following 3 sets of tests check the behavior of createRdata() variants
// with the "unknown" RRtype.  The result should be RRclass independent.
TEST_F(Rdata_Unknown_Test, createRdataFromString) {
    EXPECT_EQ(0, rdata_unknown.compare(
                  *createRdata(unknown_rrtype, RRClass::IN(),
                               rdata_unknowntxt)));
    EXPECT_EQ(0, rdata_unknown.compare(
                  *createRdata(unknown_rrtype, RRClass::CH(),
                               rdata_unknowntxt)));
    EXPECT_EQ(0, rdata_unknown.compare(
                  *createRdata(unknown_rrtype, RRClass("CLASS65000"),
                               rdata_unknowntxt)));
}

TEST_F(Rdata_Unknown_Test, createRdataFromWire) {
    InputBuffer ibuffer(wiredata_unknown, sizeof(wiredata_unknown));
    EXPECT_EQ(0, rdata_unknown.compare(
                  *createRdata(unknown_rrtype, RRClass::IN(),
                               ibuffer, sizeof(wiredata_unknown))));

    InputBuffer ibuffer2(wiredata_unknown, sizeof(wiredata_unknown));
    EXPECT_EQ(0, rdata_unknown.compare(
                  *createRdata(unknown_rrtype, RRClass::CH(),
                               ibuffer2, sizeof(wiredata_unknown))));

    InputBuffer ibuffer3(wiredata_unknown, sizeof(wiredata_unknown));
    EXPECT_EQ(0, rdata_unknown.compare(
                  *createRdata(unknown_rrtype, RRClass(65000),
                               ibuffer3, sizeof(wiredata_unknown))));
}

TEST_F(Rdata_Unknown_Test, createRdataByCopy) {
    EXPECT_EQ(0, rdata_unknown.compare(
                  *createRdata(unknown_rrtype, RRClass::IN(), rdata_unknown)));
    EXPECT_EQ(0, rdata_unknown.compare(
                  *createRdata(unknown_rrtype, RRClass::CH(), rdata_unknown)));
    EXPECT_EQ(0, rdata_unknown.compare(
                  *createRdata(unknown_rrtype, RRClass(65000),
                               rdata_unknown)));
}

TEST_F(Rdata_Unknown_Test, copyConstruct) {
    generic::Generic copy(rdata_unknown);
    EXPECT_EQ(0, copy.compare(rdata_unknown));

    // Check the copied data is valid even after the original is deleted
    generic::Generic* copy2 = new generic::Generic(rdata_unknown);
    generic::Generic copy3(*copy2);
    delete copy2;
    EXPECT_EQ(0, copy3.compare(rdata_unknown));
}

TEST_F(Rdata_Unknown_Test, assignment) {
    generic::Generic copy("\\# 1 10");
    copy = rdata_unknown;
    EXPECT_EQ(0, copy.compare(rdata_unknown));

    // Check if the copied data is valid even after the original is deleted
    generic::Generic* copy2 = new generic::Generic(rdata_unknown);
    generic::Generic copy3("\\# 1 10");
    copy3 = *copy2;
    delete copy2;
    EXPECT_EQ(0, copy3.compare(rdata_unknown));

    // Self assignment
    copy = copy;
    EXPECT_EQ(0, copy.compare(rdata_unknown));
}

TEST_F(Rdata_Unknown_Test, toText) {
    EXPECT_EQ(rdata_unknowntxt, rdata_unknown.toText());
    EXPECT_EQ(getLongestRdataTxt(),
              generic::Generic(getLongestRdataTxt()).toText());
}

TEST_F(Rdata_Unknown_Test, toWireBuffer) {
    rdata_unknown.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_unknown, sizeof(wiredata_unknown));
}

TEST_F(Rdata_Unknown_Test, toWireRenderer) {
    rdata_unknown.toWire(renderer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        renderer.getData(), renderer.getLength(),
                        wiredata_unknown, sizeof(wiredata_unknown));
}

TEST_F(Rdata_Unknown_Test, compare) {
    // comparison as left-justified unsigned octet sequences:
    // cppcheck-suppress uselessCallsCompare
    EXPECT_EQ(0, rdata_unknown.compare(rdata_unknown));

    generic::Generic rdata_unknown_small("\\# 4 00b2c3ff");
    EXPECT_GT(0, rdata_unknown_small.compare(rdata_unknown));
    EXPECT_LT(0, rdata_unknown.compare(rdata_unknown_small));

    generic::Generic rdata_unknown_large("\\# 4 ffb2c300");
    EXPECT_LT(0, rdata_unknown_large.compare(rdata_unknown));
    EXPECT_GT(0, rdata_unknown.compare(rdata_unknown_large));

    // the absence of an octet sorts before a zero octet.
    generic::Generic rdata_unknown_short("\\# 3 a1b2c3");
    EXPECT_GT(0, rdata_unknown_short.compare(rdata_unknown));
    EXPECT_LT(0, rdata_unknown.compare(rdata_unknown_short));
}

TEST_F(Rdata_Unknown_Test, LeftShiftOperator) {
    ostringstream oss;
    oss << rdata_unknown;
    EXPECT_EQ(rdata_unknown.toText(), oss.str());
}

//
// Tests for global utility functions
//
TEST_F(RdataTest, compareNames) {
    Name small("a.example");
    Name large("example");

    // Check the case where the order is different from the owner name
    // comparison:
    EXPECT_TRUE(small > large);
    EXPECT_EQ(-1, compareNames(small, large));
    EXPECT_EQ(1, compareNames(large, small));

    // Check case insensitive comparison:
    Name small_upper("A.EXAMPLE");
    EXPECT_EQ(0, compareNames(small, small_upper));

    // the absence of an octet sorts before a zero octet.
    Name large2("a.example2");
    EXPECT_EQ(-1, compareNames(small, large2));
    EXPECT_EQ(1, compareNames(large2, small));
}
}
