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

#include <util/buffer.h>
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
class Rdata_SOA_Test : public RdataTest {
    // there's nothing to specialize
};

const generic::SOA rdata_soa(Name("ns.example.com"), Name("root.example.com"),
                             2010012601, 3600, 300, 3600000, 1200);

TEST_F(Rdata_SOA_Test, createFromText) {
    //TBD
}

TEST_F(Rdata_SOA_Test, createFromWire) {
    EXPECT_EQ(0, rdata_soa.compare(
                  *rdataFactoryFromFile(RRType("SOA"), RRClass("IN"),
                                        "rdata_soa_fromWire")));
    // TBD: more tests
}

TEST_F(Rdata_SOA_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_soa.compare(
        *test::createRdataUsingLexer(RRType::SOA(), RRClass::IN(),
                                     "ns.example.com. root.example.com. "
                                     "2010012601 3600 300 3600000 1200")));
}

TEST_F(Rdata_SOA_Test, toWireRenderer) {
    renderer.skip(2);
    rdata_soa.toWire(renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_soa_fromWire", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(renderer.getData()) + 2,
                        renderer.getLength() - 2, &data[2], data.size() - 2);
}

TEST_F(Rdata_SOA_Test, toWireBuffer) {
    obuffer.skip(2);
    rdata_soa.toWire(obuffer);
    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_soa_toWireUncompressed.wire", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(obuffer.getData()) + 2,
                        obuffer.getLength() - 2, &data[2], data.size() - 2);
}

TEST_F(Rdata_SOA_Test, toText) {
    EXPECT_EQ("ns.example.com. root.example.com. "
              "2010012601 3600 300 3600000 1200", rdata_soa.toText());
}

TEST_F(Rdata_SOA_Test, getSerial) {
    EXPECT_EQ(2010012601, rdata_soa.getSerial().getValue());
}

}
