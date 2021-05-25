// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <string>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <util/time_utilities.h>
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

class Rdata_TKEY_Test : public RdataTest {
protected:
    Rdata_TKEY_Test() :
        // no Key or Other Data
        valid_text1("gss-tsig. 20210501120000 20210501130000 GSS-API NOERROR 0 0"),
        // Key but no Other Data
        valid_text2("GSS-TSIG. 20210501120000 20210501130000 GSS-API BADSIG "
                    "12 FAKEFAKEFAKEFAKE 0"),
        // Key and Other Data
        valid_text3("gss.tsig. 20210501120000 20210501130000 GSS-API BADSIG "
                    "12 FAKEFAKEFAKEFAKE 6 FAKEFAKE"),
        // Key and Other Data (with Error that doesn't expect Other Data)
        valid_text4("gss.tsig. 20210501120000 20210501130000 3 BADSIG 12 "
                    "FAKEFAKEFAKEFAKE 6 FAKEFAKE"),
        // numeric error code
        valid_text5("GSS-TSIG. 20210501120000 20210501130000 GSS-API 2845 12 "
                    "FAKEFAKEFAKEFAKE 0"),
        // GSS-API mode
        valid_text6("gss-tsig. 20210501120000 20210501130000 GSS-API 0 12 "
                    "FAKEFAKEFAKEFAKE 0"),
        rdata_tkey(valid_text1)
    {}

    void checkFromText_None(const string& rdata_str) {
        checkFromText<generic::TKEY, isc::Exception, isc::Exception>(
            rdata_str, rdata_tkey, false, false);
    }

    void checkFromText_InvalidTime(const string& rdata_str) {
        checkFromText<generic::TKEY, InvalidTime, InvalidTime>(
            rdata_str, rdata_tkey, true, true);
    }

    void checkFromText_InvalidText(const string& rdata_str) {
        checkFromText<generic::TKEY, InvalidRdataText, InvalidRdataText>(
            rdata_str, rdata_tkey, true, true);
    }

    void checkFromText_BadValue(const string& rdata_str) {
        checkFromText<generic::TKEY, BadValue, BadValue>(
            rdata_str, rdata_tkey, true, true);
    }

    void checkFromText_LexerError(const string& rdata_str) {
        checkFromText
            <generic::TKEY, InvalidRdataText, MasterLexer::LexerError>(
                rdata_str, rdata_tkey, true, true);
    }

    void checkFromText_TooLongLabel(const string& rdata_str) {
        checkFromText<generic::TKEY, TooLongLabel, TooLongLabel>(
            rdata_str, rdata_tkey, true, true);
    }

    void checkFromText_EmptyLabel(const string& rdata_str) {
        checkFromText<generic::TKEY, EmptyLabel, EmptyLabel>(
            rdata_str, rdata_tkey, true, true);
    }

    void checkFromText_BadString(const string& rdata_str) {
        checkFromText
            <generic::TKEY, InvalidRdataText, isc::Exception>(
                rdata_str, rdata_tkey, true, false);
    }

    template <typename Output>
    void toWireCommonChecks(Output& output) const;

    const string valid_text1;
    const string valid_text2;
    const string valid_text3;
    const string valid_text4;
    const string valid_text5;
    const string valid_text6;
    vector<uint8_t> expect_data;
    const generic::TKEY rdata_tkey; // commonly used test RDATA
};

TEST_F(Rdata_TKEY_Test, fromText) {
    // normal case.  it also tests getter methods.
    EXPECT_EQ(Name("gss-tsig"), rdata_tkey.getAlgorithm());
    EXPECT_EQ(1619870400, rdata_tkey.getInception());
    EXPECT_EQ("20210501120000", rdata_tkey.getInceptionDate());
    EXPECT_EQ(1619874000, rdata_tkey.getExpire());
    EXPECT_EQ("20210501130000", rdata_tkey.getExpireDate());
    EXPECT_EQ(3, rdata_tkey.getMode());
    EXPECT_EQ(0, rdata_tkey.getError());
    EXPECT_EQ(0, rdata_tkey.getKeyLen());
    EXPECT_EQ(static_cast<void*>(0), rdata_tkey.getKey());
    EXPECT_EQ(0, rdata_tkey.getOtherLen());
    EXPECT_EQ(static_cast<void*>(0), rdata_tkey.getOtherData());

    generic::TKEY tkey2(valid_text2);
    EXPECT_EQ(12, tkey2.getKeyLen());
    EXPECT_EQ(TSIGError::BAD_SIG_CODE, tkey2.getError());

    generic::TKEY tkey3(valid_text3);
    EXPECT_EQ(6, tkey3.getOtherLen());

    // The other data is unusual, but we don't reject it.
    EXPECT_NO_THROW(generic::TKEY tkey4(valid_text4));

    // numeric representation of TKEY error
    generic::TKEY tkey5(valid_text5);
    EXPECT_EQ(2845, tkey5.getError());

    // symbolic representation of TKEY mode
    generic::TKEY tkey6(valid_text6);
    EXPECT_EQ(generic::TKEY::GSS_API_MODE, tkey6.getMode());

    // not fully qualified algorithm name
    generic::TKEY tkey1("gss-tsig 20210501120000 20210501130000 3 0 0 0");
    EXPECT_EQ(0, tkey1.compare(rdata_tkey));

    // multi-line rdata
    checkFromText_None("gss-tsig. ( 20210501120000 20210501130000 GSS-API \n"
                       "NOERROR 0 0 )");
};

TEST_F(Rdata_TKEY_Test, badText) {
    // too many fields
    checkFromText_BadString(valid_text1 + " 0 0");
    // not enough fields
    checkFromText_LexerError("foo 20210501120000 20210501130000 0 BADKEY");
    // bad domain name
    checkFromText_TooLongLabel(
        "0123456789012345678901234567890123456789012345678901234567890123"
        " 20210501120000 20210501130000 0 0 0 0");
    checkFromText_EmptyLabel("foo..bar 20210501120000 20210501130000 0 0 0 0");
    // invalid inception (no digit)
    checkFromText_InvalidTime("foo TIME 20210501130000 0 0 0 0");
    // invalid inception (bad format)
    checkFromText_InvalidTime("foo 0 20210501130000 0 0 0 0");
    // invalid expire (no digit)
    checkFromText_InvalidTime("foo 20210501120000 TIME 0 0 0 0");
    // invalid expire (bad format)
    checkFromText_InvalidTime("foo 20210501120000 0 0 0 0 0");
    // Unknown mode
    checkFromText_InvalidText("foo 20210501120000 20210501130000 TEST 0 0 0");
    // Numeric mode is is too large
    checkFromText_InvalidText("foo 20210501120000 20210501130000 65536 0 0 0");
    // Numeric mode is negative
    checkFromText_InvalidText("foo 20210501120000 20210501130000 -1 0 0 0 0");
    // Unknown error code
    checkFromText_InvalidText("foo 20210501120000 20210501130000 0 TEST 0 0");
    // Numeric error code is too large
    checkFromText_InvalidText("foo 20210501120000 20210501130000 0 65536 0 0");
    // Numeric error code is negative
    checkFromText_InvalidText("foo 20210501120000 20210501130000 0 -1 0 0");
    // Key len is too large
    checkFromText_InvalidText("foo 20210501120000 20210501130000 0 0 65536 0");
    // invalid Key len (negative)
    checkFromText_LexerError("foo 20210501120000 20210501130000 0 0 -1 0");
    // invalid Key len (not a number)
    checkFromText_LexerError("foo 20210501120000 20210501130000 0 0 MACSIZE 0");
    // Key len and Key mismatch
    checkFromText_InvalidText("foo 20210501120000 20210501130000 0 0 9 FAKE 0");
    // Key is bad base64
    checkFromText_BadValue("foo 20210501120000 20210501130000 0 0 3 FAK= 0");
    // Other len is too large
    checkFromText_InvalidText("foo 20210501120000 20210501130000 0 0 0 65536 FAKE");
    // Other len is negative
    checkFromText_LexerError("foo 20210501120000 20210501130000 0 0 0 -1 FAKE");
    // invalid Other len
    checkFromText_LexerError("foo 20210501120000 20210501130000 0 0 0 LEN FAKE");
    // Other len and data mismatch
    checkFromText_InvalidText("foo 20210501120000 20210501130000 0 0 0 9 FAKE");
}

void
fromWireCommonChecks(const generic::TKEY& tkey) {
    EXPECT_EQ(Name("gss-tsig"), tkey.getAlgorithm());
    EXPECT_EQ(1619870400, tkey.getInception());
    EXPECT_EQ("20210501120000", tkey.getInceptionDate());
    EXPECT_EQ(1619874000, tkey.getExpire());
    EXPECT_EQ("20210501130000", tkey.getExpireDate());
    EXPECT_EQ(3, tkey.getMode());
    EXPECT_EQ(0, tkey.getError());

    vector<uint8_t> expect_key(32, 'x');
    matchWireData(&expect_key[0], expect_key.size(),
                  tkey.getKey(), tkey.getKeyLen());

    EXPECT_EQ(0, tkey.getOtherLen());
    EXPECT_EQ(static_cast<const void*>(0), tkey.getOtherData());
}

TEST_F(Rdata_TKEY_Test, createFromWire) {
    RdataPtr rdata(rdataFactoryFromFile(RRType::TKEY(), RRClass::ANY(),
                                        "rdata_tkey_fromWire1.wire"));
    fromWireCommonChecks(dynamic_cast<generic::TKEY&>(*rdata));
}

TEST_F(Rdata_TKEY_Test, createFromWireWithOtherData) {
    RdataPtr rdata(rdataFactoryFromFile(RRType::TKEY(), RRClass::ANY(),
                                        "rdata_tkey_fromWire2.wire"));
    const generic::TKEY& tkey(dynamic_cast<generic::TKEY&>(*rdata));

    vector<uint8_t> expect_key(32, 'x');
    matchWireData(&expect_key[0], expect_key.size(),
                  tkey.getKey(), tkey.getKeyLen());

    vector<uint8_t> expect_data = { 'a', 'b', 'c', 'd', '0', '1', '2', '3' };
    matchWireData(&expect_data[0], expect_data.size(),
                  tkey.getOtherData(), tkey.getOtherLen());
}

TEST_F(Rdata_TKEY_Test, createFromWireWithoutKey) {
    RdataPtr rdata(rdataFactoryFromFile(RRType::TKEY(), RRClass::ANY(),
                                        "rdata_tkey_fromWire3.wire"));
    const generic::TKEY& tkey(dynamic_cast<generic::TKEY&>(*rdata));
    EXPECT_EQ(0, tkey.getKeyLen());
    EXPECT_EQ(static_cast<const void*>(0), tkey.getKey());

    vector<uint8_t> expect_data = { 'a', 'b', 'c', 'd', '0', '1', '2', '3' };
    matchWireData(&expect_data[0], expect_data.size(),
                  tkey.getOtherData(), tkey.getOtherLen());
}

TEST_F(Rdata_TKEY_Test, createFromWireWithCompression) {
    RdataPtr rdata(rdataFactoryFromFile(RRType::TKEY(), RRClass::ANY(),
                                        "rdata_tkey_fromWire4.wire",
                                        // we need to skip the dummy name:
                                        Name("gss-tsig").getLength()));
    fromWireCommonChecks(dynamic_cast<generic::TKEY&>(*rdata));
}

TEST_F(Rdata_TKEY_Test, badFromWire) {
    // RDLENGTH is too short:
    EXPECT_THROW(rdataFactoryFromFile(RRType::TKEY(), RRClass::ANY(),
                                      "rdata_tkey_fromWire5.wire"),
                 InvalidRdataLength);
    // RDLENGTH is too long:
    EXPECT_THROW(rdataFactoryFromFile(RRType::TKEY(), RRClass::ANY(),
                                      "rdata_tkey_fromWire6.wire"),
                 InvalidRdataLength);
    // Algorithm name is broken:
    EXPECT_THROW(rdataFactoryFromFile(RRType::TKEY(), RRClass::ANY(),
                                      "rdata_tkey_fromWire7.wire"),
                 DNSMessageFORMERR);
    // Key length is bogus:
    EXPECT_THROW(rdataFactoryFromFile(RRType::TKEY(), RRClass::ANY(),
                                      "rdata_tkey_fromWire8.wire"),
                 InvalidBufferPosition);
    // Other-data length is bogus:
    EXPECT_THROW(rdataFactoryFromFile(RRType::TKEY(), RRClass::ANY(),
                                      "rdata_tkey_fromWire9.wire"),
                 InvalidBufferPosition);
}

TEST_F(Rdata_TKEY_Test, copyConstruct) {
    const generic::TKEY copy(rdata_tkey);
    EXPECT_EQ(0, copy.compare(rdata_tkey));

    // Check the copied data is valid even after the original is deleted
    generic::TKEY* copy2 = new generic::TKEY(rdata_tkey);
    generic::TKEY copy3(*copy2);
    delete copy2;
    EXPECT_EQ(0, copy3.compare(rdata_tkey));
}

TEST_F(Rdata_TKEY_Test, createFromParams) {
    EXPECT_EQ(0, rdata_tkey.compare(generic::TKEY(Name("gss-tsig"),
                                                  1619870400,
                                                  1619874000,
                                                  3, 0, 0, 0, 0, 0)));

    const uint8_t fake_data[] = { 0x14, 0x02, 0x84, 0x14, 0x02, 0x84,
                                  0x14, 0x02, 0x84, 0x14, 0x02, 0x84 };
    EXPECT_EQ(0, generic::TKEY(valid_text2).compare(
                  generic::TKEY(Name("GSS-TSIG"), 1619870400, 1619874000,
                                3, 16, 12, fake_data, 0, 0)));

    const uint8_t fake_data2[] = { 0x14, 0x02, 0x84, 0x14, 0x02, 0x84 };
    EXPECT_EQ(0, generic::TKEY(valid_text3).compare(
                  generic::TKEY(Name("gss.tsig"), 1619870400, 1619874000,
                                3, 16, 12, fake_data, 6, fake_data2)));

    EXPECT_THROW(generic::TKEY(Name("gss-tsig"), 0, 0, 0, 0, 0, fake_data, 0, 0),
                 isc::InvalidParameter);
    EXPECT_THROW(generic::TKEY(Name("gss-tsig"), 0, 0, 0, 0, 12, 0, 0, 0),
                 isc::InvalidParameter);
    EXPECT_THROW(generic::TKEY(Name("gss-tsig"), 0, 0, 0, 0, 0, 0, 0, fake_data),
                 isc::InvalidParameter);
    EXPECT_THROW(generic::TKEY(Name("fake_data"),  0, 0, 0, 0, 0, 0, 6, 0),
                 isc::InvalidParameter);
}

TEST_F(Rdata_TKEY_Test, assignment) {
    generic::TKEY copy(valid_text2);
    copy = rdata_tkey;
    EXPECT_EQ(0, copy.compare(rdata_tkey));

    // Check if the copied data is valid even after the original is deleted
    generic::TKEY* copy2 = new generic::TKEY(rdata_tkey);
    generic::TKEY copy3(valid_text2);
    copy3 = *copy2;
    delete copy2;
    EXPECT_EQ(0, copy3.compare(rdata_tkey));

    // Self assignment
    copy = *&copy;
    EXPECT_EQ(0, copy.compare(rdata_tkey));
}

template <typename Output>
void
Rdata_TKEY_Test::toWireCommonChecks(Output& output) const {
    vector<uint8_t> expect_data;

    output.clear();
    expect_data.clear();
    rdata_tkey.toWire(output);
    // read the expected wire format data and trim the RDLEN part.
    UnitTestUtil::readWireData("rdata_tkey_toWire1.wire", expect_data);
    expect_data.erase(expect_data.begin(), expect_data.begin() + 2);
    matchWireData(&expect_data[0], expect_data.size(),
                  output.getData(), output.getLength());

    expect_data.clear();
    output.clear();
    generic::TKEY(valid_text2).toWire(output);
    UnitTestUtil::readWireData("rdata_tkey_toWire2.wire", expect_data);
    expect_data.erase(expect_data.begin(), expect_data.begin() + 2);
    matchWireData(&expect_data[0], expect_data.size(),
                  output.getData(), output.getLength());

    expect_data.clear();
    output.clear();
    generic::TKEY(valid_text3).toWire(output);
    UnitTestUtil::readWireData("rdata_tkey_toWire3.wire", expect_data);
    expect_data.erase(expect_data.begin(), expect_data.begin() + 2);
    matchWireData(&expect_data[0], expect_data.size(),
                  output.getData(), output.getLength());
}

TEST_F(Rdata_TKEY_Test, toWireBuffer) {
    toWireCommonChecks<OutputBuffer>(obuffer);
}

TEST_F(Rdata_TKEY_Test, toWireRenderer) {
    toWireCommonChecks<MessageRenderer>(renderer);

    // check algorithm name won't compressed when it would otherwise.
    expect_data.clear();
    renderer.clear();
    renderer.writeName(Name("gss-tsig"));
    renderer.writeUint16(26); // RDLEN
    rdata_tkey.toWire(renderer);
    UnitTestUtil::readWireData("rdata_tkey_toWire4.wire", expect_data);
    matchWireData(&expect_data[0], expect_data.size(),
                  renderer.getData(), renderer.getLength());

    // check algorithm can be used as a compression target.
    expect_data.clear();
    renderer.clear();
    renderer.writeUint16(26);
    rdata_tkey.toWire(renderer);
    renderer.writeName(Name("gss-tsig"));
    UnitTestUtil::readWireData("rdata_tkey_toWire5.wire", expect_data);
    matchWireData(&expect_data[0], expect_data.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(Rdata_TKEY_Test, toText) {
    EXPECT_EQ(valid_text1, rdata_tkey.toText());
    EXPECT_EQ(valid_text2, generic::TKEY(valid_text2).toText());
    EXPECT_EQ(valid_text3, generic::TKEY(valid_text3).toText());
    EXPECT_EQ(valid_text5, generic::TKEY(valid_text5).toText());
}

TEST_F(Rdata_TKEY_Test, compare) {
    // test RDATAs, sorted in the ascending order.
    // "AAAA" encoded in BASE64 corresponds to 0x000000, so it should be the
    // smallest data of the same length.
    vector<generic::TKEY> compare_set;
    compare_set.push_back(generic::TKEY("a.example 20210501120000 "
                                        "20210501130000 3 0 0 0"));
    compare_set.push_back(generic::TKEY("example 20210501120000 "
                                        "20210501130000 3 0 0 0"));
    compare_set.push_back(generic::TKEY("example 20210501120001 "
                                        "20210501130000 3 0 0 0"));
    compare_set.push_back(generic::TKEY("example 20210501120001 "
                                        "20210501130001 3 0 0 0"));
    compare_set.push_back(generic::TKEY("example 20210501120001 "
                                        "20210501130001 4 0 0 0"));
    compare_set.push_back(generic::TKEY("example 20210501120001 "
                                        "20210501130001 4 1 0 0"));
    compare_set.push_back(generic::TKEY("example 20210501120001 "
                                        "20210501130001 4 1 3 AAAA 0"));
    compare_set.push_back(generic::TKEY("example 20210501120001 "
                                        "20210501130001 4 1 3 FAKE 0"));
    compare_set.push_back(generic::TKEY("example 20210501120001 "
                                        "20210501130001 4 1 3 FAKE 3 AAAA"));
    compare_set.push_back(generic::TKEY("example 20210501120001 "
                                        "20210501130001 4 1 3 FAKE 3 FAKE"));

    EXPECT_EQ(0,
              compare_set[0].compare(generic::TKEY("A.EXAMPLE 20210501120000 "
                                                   "20210501130000 3 0 0 0")));

    vector<generic::TKEY>::const_iterator it;
    vector<generic::TKEY>::const_iterator it_end = compare_set.end();
    for (it = compare_set.begin(); it != it_end - 1; ++it) {
        EXPECT_GT(0, (*it).compare(*(it + 1)));
        EXPECT_LT(0, (*(it + 1)).compare(*it));
    }

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(rdata_tkey.compare(*RdataTest::rdata_nomatch), bad_cast);
}
}
