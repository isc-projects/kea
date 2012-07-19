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
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;

namespace {
class Rdata_TSIG_Test : public RdataTest {
protected:
    vector<uint8_t> expect_data;
};

const char* const valid_text1 = "hmac-md5.sig-alg.reg.int. 1286779327 300 "
    "0 16020 BADKEY 0";
const char* const valid_text2 = "hmac-sha256. 1286779327 300 12 "
    "FAKEFAKEFAKEFAKE 16020 BADSIG 0";

const char* const valid_text3 = "hmac-sha1. 1286779327 300 12 "
    "FAKEFAKEFAKEFAKE 16020 BADTIME 6 FAKEFAKE";
const char* const valid_text4 = "hmac-sha1. 1286779327 300 12 "
    "FAKEFAKEFAKEFAKE 16020 BADSIG 6 FAKEFAKE";
const char* const valid_text5 = "hmac-sha256. 1286779327 300 12 "
    "FAKEFAKEFAKEFAKE 16020 2845 0"; // using numeric error code
const char* const too_long_label = "012345678901234567890123456789"
    "0123456789012345678901234567890123";

// commonly used test RDATA
const any::TSIG rdata_tsig((string(valid_text1)));

TEST_F(Rdata_TSIG_Test, createFromText) {
    // normal case.  it also tests getter methods.
    EXPECT_EQ(Name("hmac-md5.sig-alg.reg.int"), rdata_tsig.getAlgorithm());
    EXPECT_EQ(1286779327, rdata_tsig.getTimeSigned());
    EXPECT_EQ(300, rdata_tsig.getFudge());
    EXPECT_EQ(0, rdata_tsig.getMACSize());
    EXPECT_EQ(static_cast<void*>(NULL), rdata_tsig.getMAC());
    EXPECT_EQ(16020, rdata_tsig.getOriginalID());
    EXPECT_EQ(17, rdata_tsig.getError()); // TODO: use constant
    EXPECT_EQ(0, rdata_tsig.getOtherLen());
    EXPECT_EQ(static_cast<void*>(NULL), rdata_tsig.getOtherData());

    any::TSIG tsig2((string(valid_text2)));
    EXPECT_EQ(12, tsig2.getMACSize());
    EXPECT_EQ(16, tsig2.getError()); // TODO: use constant

    any::TSIG tsig3((string(valid_text3)));
    EXPECT_EQ(6, tsig3.getOtherLen());

    // The other data is unusual, but we don't reject it.
    EXPECT_NO_THROW(any::TSIG(string(valid_text4)));

    // numeric representation of TSIG error
    any::TSIG tsig5((string(valid_text5)));
    EXPECT_EQ(2845, tsig5.getError());

    //
    // invalid cases
    //
    // there's a garbage parameter at the end
    EXPECT_THROW(any::TSIG("foo 0 0 0 0 BADKEY 0 0"), InvalidRdataText);
    // input is too short
    EXPECT_THROW(any::TSIG("foo 0 0 0 0 BADKEY"), InvalidRdataText);
    // bad domain name
    EXPECT_THROW(any::TSIG(string(too_long_label) + "0 0 0 0 BADKEY 0"),
                 TooLongLabel);
    // time is too large (2814...6 is 2^48)
    EXPECT_THROW(any::TSIG("foo 281474976710656 0 0 0 BADKEY 0"),
                 InvalidRdataText);
    // invalid time (negative)
    EXPECT_THROW(any::TSIG("foo -1 0 0 0 BADKEY 0"), InvalidRdataText);
    // fudge is too large
    EXPECT_THROW(any::TSIG("foo 0 65536 0 0 BADKEY 0"), InvalidRdataText);
    // invalid fudge (negative)
    EXPECT_THROW(any::TSIG("foo 0 -1 0 0 BADKEY 0"), InvalidRdataText);
    // MAC size is too large
    EXPECT_THROW(any::TSIG("foo 0 0 65536 0 BADKEY 0"), InvalidRdataText);
    // MAC size and MAC mismatch
    EXPECT_THROW(any::TSIG("foo 0 0 9 FAKE 0 BADKEY 0"), InvalidRdataText);
    EXPECT_THROW(any::TSIG("foo 0 0 0 FAKE 0 BADKEY 0"), InvalidRdataText);
    // MAC is bad base64
    EXPECT_THROW(any::TSIG("foo 0 0 3 FAK= 0 BADKEY 0"), isc::BadValue);
    // Unknown error code
    EXPECT_THROW(any::TSIG("foo 0 0 0 0 TEST 0"), InvalidRdataText);
    // Numeric error code is too large
    EXPECT_THROW(any::TSIG("foo 0 0 0 0 65536 0"), InvalidRdataText);
    // Other len is too large
    EXPECT_THROW(any::TSIG("foo 0 0 0 0 NOERROR 65536 FAKE"), InvalidRdataText);
    // Other len and data mismatch
    EXPECT_THROW(any::TSIG("foo 0 0 0 0 NOERROR 9 FAKE"), InvalidRdataText);
    EXPECT_THROW(any::TSIG("foo 0 0 0 0 NOERROR 0 FAKE"), InvalidRdataText);
}

void
fromWireCommonChecks(const any::TSIG& tsig) {
    EXPECT_EQ(Name("hmac-sha256"), tsig.getAlgorithm());
    EXPECT_EQ(1286978795, tsig.getTimeSigned());
    EXPECT_EQ(300, tsig.getFudge());

    vector<uint8_t> expect_mac(32, 'x');
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        &expect_mac[0], expect_mac.size(),
                        tsig.getMAC(), tsig.getMACSize());

    EXPECT_EQ(2845, tsig.getOriginalID());

    EXPECT_EQ(0, tsig.getOtherLen());
    EXPECT_EQ(static_cast<const void*>(NULL), tsig.getOtherData());
}

TEST_F(Rdata_TSIG_Test, createFromWire) {
    RdataPtr rdata(rdataFactoryFromFile(RRType::TSIG(), RRClass::ANY(),
                                        "rdata_tsig_fromWire1.wire"));
    fromWireCommonChecks(dynamic_cast<any::TSIG&>(*rdata));
}

TEST_F(Rdata_TSIG_Test, createFromWireWithOtherData) {
    RdataPtr rdata(rdataFactoryFromFile(RRType::TSIG(), RRClass::ANY(),
                                        "rdata_tsig_fromWire2.wire"));
    const any::TSIG& tsig(dynamic_cast<any::TSIG&>(*rdata));

    EXPECT_EQ(18, tsig.getError());
    const uint64_t otherdata = 1286978795 + 300 + 1; // time-signed + fudge + 1
    expect_data.resize(6);
    expect_data[0] = (otherdata >> 40);
    expect_data[1] = ((otherdata >> 32) & 0xff);
    expect_data[2] = ((otherdata >> 24) & 0xff);
    expect_data[3] = ((otherdata >> 16) & 0xff);
    expect_data[4] = ((otherdata >> 8) & 0xff);
    expect_data[5] = (otherdata & 0xff);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        &expect_data[0], expect_data.size(),
                        tsig.getOtherData(), tsig.getOtherLen());
}

TEST_F(Rdata_TSIG_Test, createFromWireWithoutMAC) {
    RdataPtr rdata(rdataFactoryFromFile(RRType::TSIG(), RRClass::ANY(),
                                        "rdata_tsig_fromWire3.wire"));
    const any::TSIG& tsig(dynamic_cast<any::TSIG&>(*rdata));
    EXPECT_EQ(16, tsig.getError());
    EXPECT_EQ(0, tsig.getMACSize());
    EXPECT_EQ(static_cast<const void*>(NULL), tsig.getMAC());
}

TEST_F(Rdata_TSIG_Test, createFromWireWithCompression) {
    RdataPtr rdata(rdataFactoryFromFile(RRType::TSIG(), RRClass::ANY(),
                                        "rdata_tsig_fromWire4.wire",
                                        // we need to skip the dummy name:
                                        Name("hmac-sha256").getLength()));
    fromWireCommonChecks(dynamic_cast<any::TSIG&>(*rdata));
}

TEST_F(Rdata_TSIG_Test, badFromWire) {
    // RDLENGTH is too short:
    EXPECT_THROW(rdataFactoryFromFile(RRType::TSIG(), RRClass::ANY(),
                                      "rdata_tsig_fromWire5.wire"),
                 InvalidRdataLength);
    // RDLENGTH is too long:
    EXPECT_THROW(rdataFactoryFromFile(RRType::TSIG(), RRClass::ANY(),
                                      "rdata_tsig_fromWire6.wire"),
                 InvalidRdataLength);
    // Algorithm name is broken:
    EXPECT_THROW(rdataFactoryFromFile(RRType::TSIG(), RRClass::ANY(),
                                      "rdata_tsig_fromWire7.wire"),
                 DNSMessageFORMERR);
    // MAC size is bogus:
    EXPECT_THROW(rdataFactoryFromFile(RRType::TSIG(), RRClass::ANY(),
                                      "rdata_tsig_fromWire8.wire"),
                 InvalidBufferPosition);
    // Other-data length is bogus:
    EXPECT_THROW(rdataFactoryFromFile(RRType::TSIG(), RRClass::ANY(),
                                      "rdata_tsig_fromWire9.wire"),
                 InvalidBufferPosition);
}

TEST_F(Rdata_TSIG_Test, copyConstruct) {
    const any::TSIG copy(rdata_tsig);
    EXPECT_EQ(0, copy.compare(rdata_tsig));

    // Check the copied data is valid even after the original is deleted
    any::TSIG* copy2 = new any::TSIG(rdata_tsig);
    any::TSIG copy3(*copy2);
    delete copy2;
    EXPECT_EQ(0, copy3.compare(rdata_tsig));
}

TEST_F(Rdata_TSIG_Test, createFromParams) {
    EXPECT_EQ(0, rdata_tsig.compare(any::TSIG(Name("hmac-md5.sig-alg.reg.int"),
                                              1286779327, 300, 0, NULL, 16020,
                                              17, 0, NULL)));

    const uint8_t fake_data[] = { 0x14, 0x02, 0x84, 0x14, 0x02, 0x84,
                                  0x14, 0x02, 0x84, 0x14, 0x02, 0x84 }; 
    EXPECT_EQ(0, any::TSIG((string(valid_text2))).compare(
                  any::TSIG(Name("hmac-sha256"), 1286779327, 300, 12,
                            fake_data, 16020, 16, 0, NULL)));

    const uint8_t fake_data2[] = { 0x14, 0x02, 0x84, 0x14, 0x02, 0x84 };
    EXPECT_EQ(0, any::TSIG((string(valid_text3))).compare(
                  any::TSIG(Name("hmac-sha1"), 1286779327, 300, 12,
                            fake_data, 16020, 18, 6, fake_data2)));

    EXPECT_THROW(any::TSIG(Name("hmac-sha256"), 1ULL << 48, 300, 12,
                           fake_data, 16020, 18, 6, fake_data2),
                 isc::OutOfRange);
    EXPECT_THROW(any::TSIG(Name("hmac-sha256"), 0, 300, 0, fake_data, 16020,
                           18, 0, NULL),
                 isc::InvalidParameter);
    EXPECT_THROW(any::TSIG(Name("hmac-sha256"), 0, 300, 12, NULL, 16020,
                           18, 0, NULL),
                 isc::InvalidParameter);
    EXPECT_THROW(any::TSIG(Name("hmac-sha256"), 0, 300, 0, NULL, 16020,
                           18, 0, fake_data),
                 isc::InvalidParameter);
    EXPECT_THROW(any::TSIG(Name("hmac-sha256"), 0, 300, 0, NULL, 16020,
                           18, 6, NULL),
                 isc::InvalidParameter);
}

TEST_F(Rdata_TSIG_Test, assignment) {
    any::TSIG copy((string(valid_text2)));
    copy = rdata_tsig;
    EXPECT_EQ(0, copy.compare(rdata_tsig));

    // Check if the copied data is valid even after the original is deleted
    any::TSIG* copy2 = new any::TSIG(rdata_tsig);
    any::TSIG copy3((string(valid_text2)));
    copy3 = *copy2;
    delete copy2;
    EXPECT_EQ(0, copy3.compare(rdata_tsig));

    // Self assignment
    copy = copy;
    EXPECT_EQ(0, copy.compare(rdata_tsig));
}

template <typename Output>
void
toWireCommonChecks(Output& output) {
    vector<uint8_t> expect_data;

    output.clear();
    expect_data.clear();
    rdata_tsig.toWire(output);
    // read the expected wire format data and trim the RDLEN part.
    UnitTestUtil::readWireData("rdata_tsig_toWire1.wire", expect_data);
    expect_data.erase(expect_data.begin(), expect_data.begin() + 2);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        &expect_data[0], expect_data.size(),
                        output.getData(), output.getLength());

    expect_data.clear();
    output.clear();
    any::TSIG(string(valid_text2)).toWire(output);
    UnitTestUtil::readWireData("rdata_tsig_toWire2.wire", expect_data);
    expect_data.erase(expect_data.begin(), expect_data.begin() + 2);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        &expect_data[0], expect_data.size(),
                        output.getData(), output.getLength());

    expect_data.clear();
    output.clear();
    any::TSIG(string(valid_text3)).toWire(output);
    UnitTestUtil::readWireData("rdata_tsig_toWire3.wire", expect_data);
    expect_data.erase(expect_data.begin(), expect_data.begin() + 2);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        &expect_data[0], expect_data.size(),
                        output.getData(), output.getLength());
}

TEST_F(Rdata_TSIG_Test, toWireBuffer) {
    toWireCommonChecks<OutputBuffer>(obuffer);
}

TEST_F(Rdata_TSIG_Test, toWireRenderer) {
    toWireCommonChecks<MessageRenderer>(renderer);

    // check algorithm name won't compressed when it would otherwise.
    expect_data.clear();
    renderer.clear();
    renderer.writeName(Name("hmac-md5.sig-alg.reg.int"));
    renderer.writeUint16(42); // RDLEN
    rdata_tsig.toWire(renderer);
    UnitTestUtil::readWireData("rdata_tsig_toWire4.wire", expect_data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        &expect_data[0], expect_data.size(),
                        renderer.getData(), renderer.getLength());

    // check algorithm can be used as a compression target.
    expect_data.clear();
    renderer.clear();
    renderer.writeUint16(42);
    rdata_tsig.toWire(renderer);
    renderer.writeName(Name("hmac-md5.sig-alg.reg.int"));
    UnitTestUtil::readWireData("rdata_tsig_toWire5.wire", expect_data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        &expect_data[0], expect_data.size(),
                        renderer.getData(), renderer.getLength());
}

TEST_F(Rdata_TSIG_Test, toText) {
    EXPECT_EQ(string(valid_text1), rdata_tsig.toText());
    EXPECT_EQ(string(valid_text2), any::TSIG(string(valid_text2)).toText());
    EXPECT_EQ(string(valid_text3), any::TSIG(string(valid_text3)).toText());
    EXPECT_EQ(string(valid_text5), any::TSIG(string(valid_text5)).toText());
}

TEST_F(Rdata_TSIG_Test, compare) {
    // test RDATAs, sorted in the ascendent order.
    // "AAAA" encoded in BASE64 corresponds to 0x000000, so it should be the
    // smallest data of the same length.
    vector<any::TSIG> compare_set;
    compare_set.push_back(any::TSIG("a.example 0 300 0 16020 0 0"));
    compare_set.push_back(any::TSIG("example 0 300 0 16020 0 0"));
    compare_set.push_back(any::TSIG("example 1 300 0 16020 0 0"));
    compare_set.push_back(any::TSIG("example 1 600 0 16020 0 0"));
    compare_set.push_back(any::TSIG("example 1 600 3 AAAA 16020 0 0"));
    compare_set.push_back(any::TSIG("example 1 600 3 FAKE 16020 0 0"));
    compare_set.push_back(any::TSIG("example 1 600 3 FAKE 16021 0 0"));
    compare_set.push_back(any::TSIG("example 1 600 3 FAKE 16021 1 0"));
    compare_set.push_back(any::TSIG("example 1 600 3 FAKE 16021 1 3 AAAA"));
    compare_set.push_back(any::TSIG("example 1 600 3 FAKE 16021 1 3 FAKE"));

    EXPECT_EQ(0, compare_set[0].compare(
                  any::TSIG("A.EXAMPLE 0 300 0 16020 0 0")));

    vector<any::TSIG>::const_iterator it;
    vector<any::TSIG>::const_iterator it_end = compare_set.end();
    for (it = compare_set.begin(); it != it_end - 1; ++it) {
        EXPECT_GT(0, (*it).compare(*(it + 1)));
        EXPECT_LT(0, (*(it + 1)).compare(*it));
    }

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(rdata_tsig.compare(*RdataTest::rdata_nomatch), bad_cast);
}
}
