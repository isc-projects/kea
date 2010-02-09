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

#include <vector>

#include <dns/buffer.h>
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

namespace isc {
namespace dns {
namespace rdata {
RdataTest::RdataTest() :
    obuffer(0), renderer(obuffer),
    rdata_nomatch(createRdata(RRType(0), RRClass(1), "\\# 0"))
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
}
}
}

namespace {
class Rdata_Unknown_Test : public RdataTest {
    // there's nothing to specialize
};

// "Unknown" RR Type used for the test cases below.  If/when we use this
// type number as a "well-known" (probably experimental) type, we'll need to
// renumber it.
const RRType unknown_rrtype = RRType("TYPE65000");

TEST_F(Rdata_Unknown_Test, createFromText)
{
    // valid construction.  This also tests a normal case of "FromWire".
    EXPECT_EQ(0, generic::Generic("\\# 4 a1b2c30d").compare(
                  *rdataFactoryFromFile(unknown_rrtype, RRClass("IN"),
                                        "testdata/rdata_unknown_fromWire")));
    // 0-length RDATA should be accepted
    EXPECT_EQ(0, generic::Generic("\\# 0").compare(
                  *rdataFactoryFromFile(unknown_rrtype, RRClass("IN"),
                                        "testdata/rdata_unknown_fromWire", 6)));
    // the length field must match the encoding data length.
    EXPECT_THROW(generic::Generic("\\# 4 1080c0ff00"), InvalidRdataLength);
    EXPECT_THROW(generic::Generic("\\# 3 1080c0ff"), InvalidRdataLength);
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

TEST_F(Rdata_Unknown_Test, createFromWire)
{
    // normal case (including 0-length data) is covered in createFromText.

    // buffer too short.  the error should be detected in buffer read
    EXPECT_THROW(rdataFactoryFromFile(unknown_rrtype, RRClass("IN"),
                                      "testdata/rdata_unknown_fromWire", 8),
                 InvalidBufferPosition);
}
}
