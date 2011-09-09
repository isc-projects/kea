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

// This is the common code for TXT and SPF tests.

#if !defined(TXT_LIKE)
#error Please define TXT_LIKE
#endif

#if !defined(txt_LIKE)
#error Please define txt_LIKE
#endif

#define xstr_(a)        #a
#define str_(a)         xstr_(a)

#define strTXT_LIKE     str_(TXT_LIKE)
#define strtxt_LIKE     str_(txt_LIKE)

#define xcat2_(a,b)     a##b
#define cat2_(a,b)      xcat2_(a, b)

#define xcat3_(a,b,c)   a##b##c
#define cat3_(a,b,c)    xcat3_(a, b, c)

#define rdata_txt_like                  cat2_(rdata_, txt_LIKE)
#define rdata_txt_like_empty            cat3_(rdata_, txt_LIKE, _empty)
#define rdata_txt_like_quoted           cat3_(rdata_, txt_LIKE, _quoted)
#define Rdata_TXT_LIKE_Test             cat3_(Rdata_, TXT_LIKE, _Test)
#define wiredata_longesttxt_like        cat2_(wiredata_longest, txt_LIKE)
#define wiredata_nulltxt_like           cat2_(wiredata_null, txt_LIKE)
#define wiredata_txt_like               cat2_(wiredata_, txt_LIKE)
#define largest_txt_like                cat2_(largest_, txt_LIKE)
#define largest_txt_like_data           cat3_(largest_, txt_LIKE, _data)

#define rdata_txt_like_fromWire1        cat3_(rdata_, txt_LIKE, _fromWire1)
#define rdata_txt_like_fromWire2        cat3_(rdata_, txt_LIKE, _fromWire2)
#define rdata_txt_like_fromWire3        cat3_(rdata_, txt_LIKE, _fromWire3)
#define rdata_txt_like_fromWire4        cat3_(rdata_, txt_LIKE, _fromWire4)
#define rdata_txt_like_fromWire5        cat3_(rdata_, txt_LIKE, _fromWire5)

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
const generic::TXT_LIKE rdata_txt_like("Test String");
const generic::TXT_LIKE rdata_txt_like_empty("");
const generic::TXT_LIKE rdata_txt_like_quoted("\"Test String\"");
const uint8_t wiredata_txt_like[] = {
    sizeof("Test String") - 1,
    'T', 'e', 's', 't', ' ', 'S', 't', 'r', 'i', 'n', 'g'
};
const uint8_t wiredata_nulltxt[] = { 0 };
vector<uint8_t> wiredata_longesttxt(256, 'a');

class Rdata_TXT_LIKE_Test : public RdataTest {
protected:
    Rdata_TXT_LIKE_Test() {
        wiredata_longesttxt[0] = 255; // adjust length
    }
};

TEST_F(Rdata_TXT_LIKE_Test, createFromText) {
    // normal case is covered in toWireBuffer.

    // surrounding double-quotes shouldn't change the result.
    EXPECT_EQ(0, rdata_txt_like.compare(rdata_txt_like_quoted));

    // Null character-string.
    obuffer.clear();
    generic::TXT_LIKE(string("")).toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_nulltxt, sizeof(wiredata_nulltxt));

    // Longest possible character-string.
    obuffer.clear();
    generic::TXT_LIKE(string(255, 'a')).toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        &wiredata_longesttxt[0], wiredata_longesttxt.size());

    // Too long text for a valid character-string.
    EXPECT_THROW(generic::TXT_LIKE(string(256, 'a')), CharStringTooLong);

    // The escape character makes the double quote a part of character-string,
    // so this is invalid input and should be rejected.
    EXPECT_THROW(generic::TXT_LIKE("\"Test String\\\""), InvalidRdataText);

    // Terminating double-quote is provided, so this is valid, but in this
    // version of implementation we reject escaped characters.
    EXPECT_THROW(generic::TXT_LIKE("\"Test String\\\"\""), InvalidRdataText);
}

void
makeLargest(vector<uint8_t>& data) {
    uint8_t ch = 0;

    // create 255 sets of character-strings, each of which has the longest
    // length (255bytes string + 1-byte length field)
    for (int i = 0; i < 255; ++i, ++ch) {
        data.push_back(255);
        data.insert(data.end(), 255, ch);
    }
    // the last character-string should be 255 bytes (including the one-byte
    // length field) in length so that the total length should be in the range
    // of 16-bit integers.
    data.push_back(254);
    data.insert(data.end(), 254, ch);

    assert(data.size() == 65535);
}

TEST_F(Rdata_TXT_LIKE_Test, createFromWire) {
    EXPECT_EQ(0, rdata_txt_like.compare(
                  *rdataFactoryFromFile(RRType(strTXT_LIKE), RRClass("IN"),
                                        "rdata_txt_fromWire1")));

    // Empty character string
    EXPECT_EQ(0, rdata_txt_like_empty.compare(
                  *rdataFactoryFromFile(RRType(strTXT_LIKE), RRClass("IN"),
                                        "rdata_txt_fromWire2.wire")));

    // Multiple character strings
    obuffer.clear();
    rdataFactoryFromFile(RRType(strTXT_LIKE), RRClass("IN"),
                         "rdata_txt_fromWire3.wire")->toWire(obuffer);
    // the result should be 'wiredata_txt' repeated twice
    vector<uint8_t> expected_data(wiredata_txt_like, wiredata_txt_like +
                                  sizeof(wiredata_txt_like));
    expected_data.insert(expected_data.end(), wiredata_txt_like,
                         wiredata_txt_like + sizeof(wiredata_txt_like));
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        &expected_data[0], expected_data.size());

    // Largest length of data.  There's nothing special, but should be
    // constructed safely, and the content should be identical to the original
    // data.
    vector<uint8_t> largest_txt_like_data;
    makeLargest(largest_txt_like_data);
    InputBuffer ibuffer(&largest_txt_like_data[0],
                        largest_txt_like_data.size());
    generic::TXT_LIKE largest_txt_like(ibuffer, largest_txt_like_data.size());
    obuffer.clear();
    largest_txt_like.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        &largest_txt_like_data[0],
                        largest_txt_like_data.size());

    // rdlen parameter is out of range.  This is a rare event because we'd
    // normally call the constructor via a polymorphic wrapper, where the
    // length is validated.  But this should be checked explicitly.
    InputBuffer ibuffer2(&largest_txt_like_data[0],
                         largest_txt_like_data.size());
    EXPECT_THROW(generic::TXT_LIKE(ibuffer2, 65536), InvalidRdataLength);

    // RDATA is empty, which is invalid for TXT_LIKE.
    EXPECT_THROW(rdataFactoryFromFile(RRType(strTXT_LIKE), RRClass("IN"),
                                      "rdata_txt_fromWire4.wire"),
                 DNSMessageFORMERR);

    // character-string length is too large, which could cause overrun.
    EXPECT_THROW(rdataFactoryFromFile(RRType(strTXT_LIKE), RRClass("IN"),
                                      "rdata_txt_fromWire5.wire"),
                 DNSMessageFORMERR);
}

TEST_F(Rdata_TXT_LIKE_Test, toWireBuffer) {
    rdata_txt_like.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_txt_like, sizeof(wiredata_txt_like));
}

TEST_F(Rdata_TXT_LIKE_Test, toText) {
    EXPECT_EQ("\"Test String\"", rdata_txt_like.toText());
}
}
