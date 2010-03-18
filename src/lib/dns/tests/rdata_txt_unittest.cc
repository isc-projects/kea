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

// $Id$

#include <dns/buffer.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include "unittest_util.h"
#include "rdata_unittest.h"

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {
const generic::TXT rdata_txt("Test String");
const generic::TXT rdata_txt_empty("");
const generic::TXT rdata_txt_quoated("\"Test String\"");
const uint8_t wiredata_txt[] = {
    sizeof("Test String") - 1,
    'T', 'e', 's', 't', ' ', 'S', 't', 'r', 'i', 'n', 'g'
};
const uint8_t wiredata_nulltxt[] = { 0 };
vector<uint8_t> wiredata_longesttxt(256, 'a');

class Rdata_TXT_Test : public RdataTest {
protected:
    Rdata_TXT_Test() {
        wiredata_longesttxt[0] = 255; // adjust length
    }
};

TEST_F(Rdata_TXT_Test, createFromText) {
    // normal case is covered in toWireBuffer.

    // surrounding double-quotes shouldn't change the result.
    EXPECT_EQ(0, rdata_txt.compare(rdata_txt_quoated));

    // Null character-string.
    obuffer.clear();
    generic::TXT(string("")).toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_nulltxt, sizeof(wiredata_nulltxt));

    // Longest possible character-string.
    obuffer.clear();
    generic::TXT(string(255, 'a')).toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        &wiredata_longesttxt[0], wiredata_longesttxt.size());

    // Too long text for a valid character-string.
    EXPECT_THROW(generic::TXT(string(256, 'a')), CharStringTooLong);

    // The escape character makes the double quote a part of character-string,
    // so this is invalid input and should be rejected.
    EXPECT_THROW(generic::TXT("\"Test String\\\""), InvalidRdataText);

    // Terminating double-quote is provided, so this is valid, but in this
    // version of implementation we reject escaped characters.
    EXPECT_THROW(generic::TXT("\"Test String\\\"\""), InvalidRdataText);
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

TEST_F(Rdata_TXT_Test, createFromWire) {
    EXPECT_EQ(0, rdata_txt.compare(
                  *rdataFactoryFromFile(RRType("TXT"), RRClass("IN"),
                                        "testdata/rdata_txt_fromWire1")));

    // Empty character string
    EXPECT_EQ(0, rdata_txt_empty.compare(
                  *rdataFactoryFromFile(RRType("TXT"), RRClass("IN"),
                                        "testdata/rdata_txt_fromWire2")));

    // Multiple character strings
    obuffer.clear();
    rdataFactoryFromFile(RRType("TXT"), RRClass("IN"),
                         "testdata/rdata_txt_fromWire3")->toWire(obuffer);
    // the result should be 'wiredata_txt' repeated twice
    vector<uint8_t> expected_data(wiredata_txt, wiredata_txt +
                                  sizeof(wiredata_txt));
    expected_data.insert(expected_data.end(), wiredata_txt,
                         wiredata_txt + sizeof(wiredata_txt));
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        &expected_data[0], expected_data.size());

    // Largest length of data.  There's nothing special, but should be
    // constructed safely, and the content should be identical to the original
    // data.
    vector<uint8_t> largest_txt_data;
    makeLargest(largest_txt_data);
    InputBuffer ibuffer(&largest_txt_data[0], largest_txt_data.size());
    generic::TXT largest_txt(ibuffer, largest_txt_data.size());
    obuffer.clear();
    largest_txt.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        &largest_txt_data[0], largest_txt_data.size());

    // rdlen parameter is out of range.  This is a rare event because we'd
    // normally call the constructor via a polymorphic wrapper, where the
    // length is validated.  But this should be checked explicitly.
    InputBuffer ibuffer2(&largest_txt_data[0], largest_txt_data.size());
    EXPECT_THROW(generic::TXT(ibuffer2, 65536), InvalidRdataLength);

    // RDATA is empty, which is invalid for TXT.
    EXPECT_THROW(rdataFactoryFromFile(RRType("TXT"), RRClass("IN"),
                                      "testdata/rdata_txt_fromWire4"),
                 DNSMessageFORMERR);

    // character-string length is too large, which could cause overrun.
    EXPECT_THROW(rdataFactoryFromFile(RRType("TXT"), RRClass("IN"),
                                      "testdata/rdata_txt_fromWire5"),
                 DNSMessageFORMERR);
}

TEST_F(Rdata_TXT_Test, toWireBuffer) {
    rdata_txt.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_txt, sizeof(wiredata_txt));
}

TEST_F(Rdata_TXT_Test, toText) {
    EXPECT_EQ("\"Test String\"", rdata_txt.toText());
}
}
