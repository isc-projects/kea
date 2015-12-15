// Copyright (C) 2010-2013  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/tsigerror.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>
#include <util/unittests/wiredata.h>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {

class Rdata_TSIG_Test : public RdataTest {
protected:
    Rdata_TSIG_Test() :
        // no MAC or Other Data
        valid_text1("hmac-md5.sig-alg.reg.int. 1286779327 300 "
                    "0 16020 BADKEY 0"),
        // MAC but no Other Data
        valid_text2("hmac-sha256. 1286779327 300 12 "
                    "FAKEFAKEFAKEFAKE 16020 BADSIG 0"),
        // MAC and Other Data
        valid_text3("hmac-sha1. 1286779327 300 12 "
                    "FAKEFAKEFAKEFAKE 16020 BADTIME 6 FAKEFAKE"),
        // MAC and Other Data (with Error that doesn't expect Other Data)
        valid_text4("hmac-sha1. 1286779327 300 12 "
                    "FAKEFAKEFAKEFAKE 16020 BADSIG 6 FAKEFAKE"),
        // numeric error code
        valid_text5("hmac-sha256. 1286779327 300 12 "
                    "FAKEFAKEFAKEFAKE 16020 2845 0"),
        rdata_tsig(valid_text1)
    {}

    void checkFromText_None(const string& rdata_str) {
        checkFromText<any::TSIG, isc::Exception, isc::Exception>(
            rdata_str, rdata_tsig, false, false);
    }

    void checkFromText_InvalidText(const string& rdata_str) {
        checkFromText<any::TSIG, InvalidRdataText, InvalidRdataText>(
            rdata_str, rdata_tsig, true, true);
    }

    void checkFromText_BadValue(const string& rdata_str) {
        checkFromText<any::TSIG, BadValue, BadValue>(
            rdata_str, rdata_tsig, true, true);
    }

    void checkFromText_LexerError(const string& rdata_str) {
        checkFromText
            <any::TSIG, InvalidRdataText, MasterLexer::LexerError>(
                rdata_str, rdata_tsig, true, true);
    }

    void checkFromText_TooLongLabel(const string& rdata_str) {
        checkFromText<any::TSIG, TooLongLabel, TooLongLabel>(
            rdata_str, rdata_tsig, true, true);
    }

    void checkFromText_EmptyLabel(const string& rdata_str) {
        checkFromText<any::TSIG, EmptyLabel, EmptyLabel>(
            rdata_str, rdata_tsig, true, true);
    }

    void checkFromText_BadString(const string& rdata_str) {
        checkFromText
            <any::TSIG, InvalidRdataText, isc::Exception>(
                rdata_str, rdata_tsig, true, false);
    }

    template <typename Output>
    void toWireCommonChecks(Output& output) const;

    const string valid_text1;
    const string valid_text2;
    const string valid_text3;
    const string valid_text4;
    const string valid_text5;
    vector<uint8_t> expect_data;
    const any::TSIG rdata_tsig; // commonly used test RDATA
};

TEST_F(Rdata_TSIG_Test, fromText) {
    // normal case.  it also tests getter methods.
    EXPECT_EQ(Name("hmac-md5.sig-alg.reg.int"), rdata_tsig.getAlgorithm());
    EXPECT_EQ(1286779327, rdata_tsig.getTimeSigned());
    EXPECT_EQ(300, rdata_tsig.getFudge());
    EXPECT_EQ(0, rdata_tsig.getMACSize());
    EXPECT_EQ(static_cast<void*>(NULL), rdata_tsig.getMAC());
    EXPECT_EQ(16020, rdata_tsig.getOriginalID());
    EXPECT_EQ(TSIGError::BAD_KEY_CODE, rdata_tsig.getError());
    EXPECT_EQ(0, rdata_tsig.getOtherLen());
    EXPECT_EQ(static_cast<void*>(NULL), rdata_tsig.getOtherData());

    any::TSIG tsig2(valid_text2);
    EXPECT_EQ(12, tsig2.getMACSize());
    EXPECT_EQ(TSIGError::BAD_SIG_CODE, tsig2.getError());

    any::TSIG tsig3(valid_text3);
    EXPECT_EQ(6, tsig3.getOtherLen());

    // The other data is unusual, but we don't reject it.
    EXPECT_NO_THROW(any::TSIG tsig4(valid_text4));

    // numeric representation of TSIG error
    any::TSIG tsig5(valid_text5);
    EXPECT_EQ(2845, tsig5.getError());

    // not fully qualified algorithm name
    any::TSIG tsig1("hmac-md5.sig-alg.reg.int 1286779327 300 "
                    "0 16020 BADKEY 0");
    EXPECT_EQ(0, tsig1.compare(rdata_tsig));

    // multi-line rdata
    checkFromText_None("hmac-md5.sig-alg.reg.int. ( 1286779327 300 \n"
                       "0 16020 BADKEY 0 )");

    // short-form HMAC-MD5 name
    const any::TSIG tsig6("hmac-md5. 1286779327 300 0 16020 BADKEY 0");
    EXPECT_EQ(0, tsig6.compare(rdata_tsig));
};

TEST_F(Rdata_TSIG_Test, badText) {
    // too many fields
    checkFromText_BadString(valid_text1 + " 0 0");
    // not enough fields
    checkFromText_LexerError("foo 0 0 0 0 BADKEY");
    // bad domain name
    checkFromText_TooLongLabel(
        "0123456789012345678901234567890123456789012345678901234567890123"
        " 0 0 0 0 BADKEY 0");
    checkFromText_EmptyLabel("foo..bar 0 0 0 0 BADKEY");
    // time is too large (2814...6 is 2^48)
    checkFromText_InvalidText("foo 281474976710656 0 0 0 BADKEY 0");
    // invalid time (negative)
    checkFromText_InvalidText("foo -1 0 0 0 BADKEY 0");
    // invalid time (not a number)
    checkFromText_InvalidText("foo TIME 0 0 0 BADKEY 0");
    // fudge is too large
    checkFromText_InvalidText("foo 0 65536 0 0 BADKEY 0");
    // invalid fudge (negative)
    checkFromText_LexerError("foo 0 -1 0 0 BADKEY 0");
    // invalid fudge (not a number)
    checkFromText_LexerError("foo 0 FUDGE 0 0 BADKEY 0");
    // MAC size is too large
    checkFromText_InvalidText("foo 0 0 65536 0 BADKEY 0");
    // invalide MAC size (negative)
    checkFromText_LexerError("foo 0 0 -1 0 BADKEY 0");
    // invalid MAC size (not a number)
    checkFromText_LexerError("foo 0 0 MACSIZE 0 BADKEY 0");
    // MAC size and MAC mismatch
    checkFromText_InvalidText("foo 0 0 9 FAKE 0 BADKEY 0");
    // MAC is bad base64
    checkFromText_BadValue("foo 0 0 3 FAK= 0 BADKEY 0");
    // Unknown error code
    checkFromText_InvalidText("foo 0 0 0 0 TEST 0");
    // Numeric error code is too large
    checkFromText_InvalidText("foo 0 0 0 0 65536 0");
    // Numeric error code is negative
    checkFromText_InvalidText("foo 0 0 0 0 -1 0");
    // Other len is too large
    checkFromText_InvalidText("foo 0 0 0 0 NOERROR 65536 FAKE");
    // Other len is negative
    checkFromText_LexerError("foo 0 0 0 0 NOERROR -1 FAKE");
    // invalid Other len
    checkFromText_LexerError("foo 0 0 0 0 NOERROR LEN FAKE");
    // Other len and data mismatch
    checkFromText_InvalidText("foo 0 0 0 0 NOERROR 9 FAKE");
}

void
fromWireCommonChecks(const any::TSIG& tsig) {
    EXPECT_EQ(Name("hmac-sha256"), tsig.getAlgorithm());
    EXPECT_EQ(1286978795, tsig.getTimeSigned());
    EXPECT_EQ(300, tsig.getFudge());

    vector<uint8_t> expect_mac(32, 'x');
    matchWireData(&expect_mac[0], expect_mac.size(),
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
    matchWireData(&expect_data[0], expect_data.size(),
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
    EXPECT_EQ(0, any::TSIG(valid_text2).compare(
                  any::TSIG(Name("hmac-sha256"), 1286779327, 300, 12,
                            fake_data, 16020, 16, 0, NULL)));

    const uint8_t fake_data2[] = { 0x14, 0x02, 0x84, 0x14, 0x02, 0x84 };
    EXPECT_EQ(0, any::TSIG(valid_text3).compare(
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
    any::TSIG copy(valid_text2);
    copy = rdata_tsig;
    EXPECT_EQ(0, copy.compare(rdata_tsig));

    // Check if the copied data is valid even after the original is deleted
    any::TSIG* copy2 = new any::TSIG(rdata_tsig);
    any::TSIG copy3(valid_text2);
    copy3 = *copy2;
    delete copy2;
    EXPECT_EQ(0, copy3.compare(rdata_tsig));

    // Self assignment
    copy = copy;
    EXPECT_EQ(0, copy.compare(rdata_tsig));
}

template <typename Output>
void
Rdata_TSIG_Test::toWireCommonChecks(Output& output) const {
    vector<uint8_t> expect_data;

    output.clear();
    expect_data.clear();
    rdata_tsig.toWire(output);
    // read the expected wire format data and trim the RDLEN part.
    UnitTestUtil::readWireData("rdata_tsig_toWire1.wire", expect_data);
    expect_data.erase(expect_data.begin(), expect_data.begin() + 2);
    matchWireData(&expect_data[0], expect_data.size(),
                  output.getData(), output.getLength());

    expect_data.clear();
    output.clear();
    any::TSIG(valid_text2).toWire(output);
    UnitTestUtil::readWireData("rdata_tsig_toWire2.wire", expect_data);
    expect_data.erase(expect_data.begin(), expect_data.begin() + 2);
    matchWireData(&expect_data[0], expect_data.size(),
                  output.getData(), output.getLength());

    expect_data.clear();
    output.clear();
    any::TSIG(valid_text3).toWire(output);
    UnitTestUtil::readWireData("rdata_tsig_toWire3.wire", expect_data);
    expect_data.erase(expect_data.begin(), expect_data.begin() + 2);
    matchWireData(&expect_data[0], expect_data.size(),
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
    matchWireData(&expect_data[0], expect_data.size(),
                  renderer.getData(), renderer.getLength());

    // check algorithm can be used as a compression target.
    expect_data.clear();
    renderer.clear();
    renderer.writeUint16(42);
    rdata_tsig.toWire(renderer);
    renderer.writeName(Name("hmac-md5.sig-alg.reg.int"));
    UnitTestUtil::readWireData("rdata_tsig_toWire5.wire", expect_data);
    matchWireData(&expect_data[0], expect_data.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(Rdata_TSIG_Test, toText) {
    EXPECT_EQ(valid_text1, rdata_tsig.toText());
    EXPECT_EQ(valid_text2, any::TSIG(valid_text2).toText());
    EXPECT_EQ(valid_text3, any::TSIG(valid_text3).toText());
    EXPECT_EQ(valid_text5, any::TSIG(valid_text5).toText());
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
