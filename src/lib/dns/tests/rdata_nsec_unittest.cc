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

#include <string>

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
class Rdata_NSEC_Test : public RdataTest {
    // there's nothing to specialize
};

string nsec_txt("www2.isc.org. CNAME RRSIG NSEC");

TEST_F(Rdata_NSEC_Test, toText_NSEC) {
    const generic::NSEC rdata_nsec(nsec_txt);
    EXPECT_EQ(nsec_txt, rdata_nsec.toText());
}

TEST_F(Rdata_NSEC_Test, badText_NSEC) {
    EXPECT_THROW(generic::NSEC rdata_nsec("www.isc.org. BIFF POW SPOON"),
                 InvalidRdataText);
    EXPECT_THROW(generic::NSEC rdata_nsec("www.isc.org."),
                 InvalidRdataText);
}

TEST_F(Rdata_NSEC_Test, createFromWire_NSEC) {
    const generic::NSEC rdata_nsec(nsec_txt);
    EXPECT_EQ(0, rdata_nsec.compare(
                  *rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                        "testdata/rdata_nsec_fromWire1")));

    // Too short RDLENGTH
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "testdata/rdata_nsec_fromWire2"),
                 DNSMessageFORMERR);

    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "testdata/rdata_nsec_fromWire3"),
                 DNSMessageFORMERR);

    // A malformed NSEC bitmap length field that could cause overflow.
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "testdata/rdata_nsec_fromWire4"),
                 DNSMessageFORMERR);

    // The bitmap field is incomplete (only the first byte is included)
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "testdata/rdata_nsec_fromWire5"),
                 DNSMessageFORMERR);

    // Bitmap length is 0, which is invalid.
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "testdata/rdata_nsec_fromWire6"),
                 DNSMessageFORMERR);

    // A boundary case: longest possible bitmaps (32 maps).  This should be
    // accepted.
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                         "testdata/rdata_nsec_fromWire7"));

    // Another boundary condition: 33 bitmaps, which should be rejected.
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "testdata/rdata_nsec_fromWire8"),
                 DNSMessageFORMERR);

    // Disordered bitmap window blocks.
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "testdata/rdata_nsec_fromWire9"),
                 DNSMessageFORMERR);

    // Bitmap ending with all-zero bytes.  Not necessarily harmful except
    // the additional overhead of parsing, but invalid according to the
    // spec anyway.
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "testdata/rdata_nsec_fromWire10"),
                 DNSMessageFORMERR);
}

TEST_F(Rdata_NSEC_Test, toWireRenderer_NSEC) {
    renderer.skip(2);
    const generic::NSEC rdata_nsec(nsec_txt);
    rdata_nsec.toWire(renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("testdata/rdata_nsec_fromWire1", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(obuffer.getData()) + 2,
                        obuffer.getLength() - 2, &data[2], data.size() - 2);
}

TEST_F(Rdata_NSEC_Test, toWireBuffer_NSEC) {
    const generic::NSEC rdata_nsec(nsec_txt);
    rdata_nsec.toWire(obuffer);
}

TEST_F(Rdata_NSEC_Test, assign) {
    generic::NSEC rdata_nsec(nsec_txt);
    generic::NSEC rdata_nsec2 = rdata_nsec;
    EXPECT_EQ(0, rdata_nsec.compare(rdata_nsec2));
}

}
