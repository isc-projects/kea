// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <util/unittests/wiredata.h>
#include <util/unittests/test_exceptions.h>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace isc {
namespace dns {
namespace rdata {
RdataTest::RdataTest() :
    obuffer(0), rdata_nomatch(createRdata(RRType(0), RRClass(1), "\\# 0")),
    loader_cb(MasterLoaderCallbacks::getNullCallbacks())
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

RdataPtr
createRdataUsingLexer(const RRType& rrtype, const RRClass& rrclass,
                      const std::string& str)
{
    std::stringstream ss(str);
    MasterLexer lexer;
    lexer.pushSource(ss);

    MasterLoaderCallbacks callbacks =
        MasterLoaderCallbacks::getNullCallbacks();
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

    // Return if callback is called since the previous call to clear().
    bool isCalled() const { return (type_ != NONE); }

    void check(const string& expected_srcname, size_t expected_line,
               CallbackType expected_type, const string& expected_reason)
        const
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
    ss << aaaa_rdata.toText() << "; comment, should be ignored\n";
    ss << aaaa_rdata.toText() << " extra-token\n"; // extra token
    ss << aaaa_rdata.toText() << " extra token\n"; // 2 extra tokens
    ss << ")\n"; // causing lexer error in parsing the RDATA text
    ss << "192.0.2.1\n"; // semantics error: IPv4 address is given for AAAA
    ss << aaaa_rdata.toText();  // valid, but end with EOF, not EOL
    lexer.pushSource(ss);

    CreateRdataCallback callback;
    MasterLoaderCallbacks callbacks(
        boost::bind(&CreateRdataCallback::callback, &callback,
                    CreateRdataCallback::ERROR, _1, _2, _3),
        boost::bind(&CreateRdataCallback::callback, &callback,
                    CreateRdataCallback::WARN,  _1, _2, _3));

    size_t line = 0;

    // Valid case.
    ++line;
    ConstRdataPtr rdata = createRdata(RRType::AAAA(), RRClass::IN(), lexer,
                                      NULL, MasterLoader::MANY_ERRORS,
                                      callbacks);
    EXPECT_EQ(0, aaaa_rdata.compare(*rdata));
    EXPECT_FALSE(callback.isCalled());

    // Similar to the previous case, but RDATA is followed by a comment.
    // It should cause any confusion.
    ++line;
    callback.clear();
    rdata = createRdata(RRType::AAAA(), RRClass::IN(), lexer, NULL,
                        MasterLoader::MANY_ERRORS, callbacks);
    EXPECT_EQ(0, aaaa_rdata.compare(*rdata));
    EXPECT_FALSE(callback.isCalled());

    // Broken RDATA text: extra token.  createRdata() returns NULL, error
    // callback is called.
    ++line;
    callback.clear();
    EXPECT_FALSE(createRdata(RRType::AAAA(), RRClass::IN(), lexer, NULL,
                             MasterLoader::MANY_ERRORS, callbacks));
    callback.check(src_name, line, CreateRdataCallback::ERROR,
                   "createRdata from text failed near 'extra-token': "
                   "extra input text");

    // Similar to the previous case, but only the first extra token triggers
    // callback.
    ++line;
    callback.clear();
    EXPECT_FALSE(createRdata(RRType::AAAA(), RRClass::IN(), lexer, NULL,
                             MasterLoader::MANY_ERRORS, callbacks));
    callback.check(src_name, line, CreateRdataCallback::ERROR,
                   "createRdata from text failed near 'extra': "
                   "extra input text");

    // Lexer error will happen, corresponding error callback will be triggered.
    ++line;
    callback.clear();
    EXPECT_FALSE(createRdata(RRType::AAAA(), RRClass::IN(), lexer, NULL,
                             MasterLoader::MANY_ERRORS, callbacks));
    callback.check(src_name, line, CreateRdataCallback::ERROR,
                   "createRdata from text failed: unbalanced parentheses");

    // Semantics level error will happen, corresponding error callback will be
    // triggered.
    ++line;
    callback.clear();
    EXPECT_FALSE(createRdata(RRType::AAAA(), RRClass::IN(), lexer, NULL,
                             MasterLoader::MANY_ERRORS, callbacks));
    callback.check(src_name, line, CreateRdataCallback::ERROR,
                   "createRdata from text failed: Bad IN/AAAA RDATA text: "
                   "'192.0.2.1'");

    // Input is valid and parse will succeed, but with a warning that the
    // file is not ended with a newline.
    ++line;
    callback.clear();
    rdata = createRdata(RRType::AAAA(), RRClass::IN(), lexer, NULL,
                        MasterLoader::MANY_ERRORS, callbacks);
    EXPECT_EQ(0, aaaa_rdata.compare(*rdata));
    callback.check(src_name, line, CreateRdataCallback::WARN,
                   "file does not end with newline");
}

TEST_F(RdataTest, getLength) {
    const in::AAAA aaaa_rdata("2001:db8::1");
    EXPECT_EQ(16, aaaa_rdata.getLength());

    const generic::TXT txt_rdata("Hello World");
    EXPECT_EQ(12, txt_rdata.getLength());
}

}
}
}

namespace {

// Wire-format data correspond to rdata_unknown.  Note that it doesn't
// include RDLENGTH.
const uint8_t wiredata_unknown[] = { 0xa1, 0xb2, 0xc3, 0x0d };

class Rdata_Unknown_Test : public RdataTest {
public:
    Rdata_Unknown_Test() :
        // "Unknown" RR Type used for the test cases below.  If/when we
        // use this type number as a "well-known" (probably
        // experimental) type, we'll need to renumber it.
        unknown_rrtype(RRType(65000)),
        rdata_unknowntxt("\\# 4 a1b2c30d"),
        rdata_unknown(rdata_unknowntxt)
    {}
protected:
    static string getLongestRdataTxt();
    static void getLongestRdataWire(vector<uint8_t>& v);

    const RRType unknown_rrtype;
    const std::string rdata_unknowntxt;
    const generic::Generic rdata_unknown;
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
    EXPECT_THROW_WITH(generic::Generic("\\# 4 1080c0ff00"),
                      InvalidRdataLength,
                      "Size of unknown RDATA hex data doesn't "
                      "match RDLENGTH: 5 vs. 4");
    EXPECT_THROW_WITH(generic::Generic("\\# 5 1080c0ff"),
                      InvalidRdataLength,
                      "Size of unknown RDATA hex data doesn't "
                      "match RDLENGTH: 4 vs. 5");
    // RDATA encoding part must consist of an even number of hex digits.
    EXPECT_THROW_WITH(generic::Generic("\\# 1 1"),
                      InvalidRdataText,
                      "Invalid hex encoding of generic RDATA: "
                      "Incomplete input for base16: 1");
    EXPECT_THROW_WITH(generic::Generic("\\# 1 ax"),
                      InvalidRdataText,
                      "Invalid hex encoding of generic RDATA: "
                      "attempt to decode a value not in base16 char set");
    // the length should be 16-bit unsigned integer
    EXPECT_THROW_WITH(generic::Generic("\\# 65536 a1b2c30d"),
                      InvalidRdataLength,
                      "Unknown RDATA length is out of range: 65536");
    EXPECT_THROW_WITH(generic::Generic("\\# -1 a1b2c30d"),
                      InvalidRdataLength, "Unknown RDATA length is invalid");
    EXPECT_THROW_WITH(generic::Generic("\\# 1.1 a1"), InvalidRdataLength,
                      "Unknown RDATA length is invalid");
    EXPECT_THROW_WITH(generic::Generic("\\# 0a 00010203040506070809"),
                      InvalidRdataLength, "Unknown RDATA length is invalid");
    // should reject if the special token is missing.
    EXPECT_THROW_WITH(generic::Generic("4 a1b2c30d"), InvalidRdataText,
                      "Missing the special token (\\#) for "
                      "unknown RDATA encoding");
    // the special token, the RDLENGTH and the data must be space separated.
    EXPECT_THROW_WITH(generic::Generic("\\#0"), InvalidRdataText,
                      "Missing the special token (\\#) for "
                      "unknown RDATA encoding");
    EXPECT_THROW_WITH(generic::Generic("\\# 1ff"), InvalidRdataLength,
                      "Unknown RDATA length is invalid");
}

TEST_F(Rdata_Unknown_Test, createFromWire) {
    // normal case (including 0-length data) is covered in createFromText.

    // buffer too short.  the error should be detected in buffer read
    EXPECT_THROW_WITH(rdataFactoryFromFile(unknown_rrtype, RRClass::IN(),
                                           "rdata_unknown_fromWire", 8),
                      InvalidBufferPosition, "read beyond end of buffer");

    // too large data
    vector<uint8_t> v;
    getLongestRdataWire(v);
    v.push_back(0);             // making it too long
    InputBuffer ibuffer(&v[0], v.size());
    EXPECT_THROW_WITH(generic::Generic(ibuffer, v.size()), InvalidRdataLength,
                      "RDLENGTH too large");
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
    matchWireData(wiredata_unknown, sizeof(wiredata_unknown),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_Unknown_Test, toWireRenderer) {
    rdata_unknown.toWire(renderer);
    matchWireData(wiredata_unknown, sizeof(wiredata_unknown),
                  renderer.getData(), renderer.getLength());
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
