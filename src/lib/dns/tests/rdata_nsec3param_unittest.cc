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

#include <util/encode/base32hex.h>
#include <util/encode/hex.h>
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
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::dns::rdata;

namespace {
class Rdata_NSEC3PARAM_Test : public RdataTest {
public:
    Rdata_NSEC3PARAM_Test() : nsec3param_txt("1 1 1 D399EAAB") {}
    const string nsec3param_txt;
};

TEST_F(Rdata_NSEC3PARAM_Test, fromText) {
    // With a salt
    EXPECT_EQ(1, generic::NSEC3PARAM(nsec3param_txt).getHashalg());
    EXPECT_EQ(1, generic::NSEC3PARAM(nsec3param_txt).getFlags());
    // (salt is checked in the toText test)

    // With an empty salt
    EXPECT_EQ(0, generic::NSEC3PARAM("1 0 0 -").getSalt().size());
}

TEST_F(Rdata_NSEC3PARAM_Test, toText) {
    const generic::NSEC3PARAM rdata_nsec3param(nsec3param_txt);
    EXPECT_EQ(nsec3param_txt, rdata_nsec3param.toText());
}

TEST_F(Rdata_NSEC3PARAM_Test, badText) {
    // garbage space at the end
    EXPECT_THROW(generic::NSEC3PARAM("1 1 1 D399EAAB "),
                 InvalidRdataText);
}

TEST_F(Rdata_NSEC3PARAM_Test, createFromWire) {
    const generic::NSEC3PARAM rdata_nsec3param(nsec3param_txt);
    EXPECT_EQ(0, rdata_nsec3param.compare(
                  *rdataFactoryFromFile(RRType::NSEC3PARAM(), RRClass::IN(),
                                       "rdata_nsec3param_fromWire1")));

    // Short buffer cases.  The data is valid NSEC3PARAM RDATA, but the buffer
    // is trimmed at the end.  All cases should result in an exception from
    // the buffer class.
    vector<uint8_t> data;
    UnitTestUtil::readWireData("rdata_nsec3param_fromWire1", data);
    const uint16_t rdlen = (data.at(0) << 8) + data.at(1);
    for (int i = 0; i < rdlen; ++i) {
        // intentionally construct a short buffer
        InputBuffer b(&data[0] + 2, i);
        EXPECT_THROW(createRdata(RRType::NSEC3PARAM(), RRClass::IN(), b, 9),
                     InvalidBufferPosition);
    }
}

TEST_F(Rdata_NSEC3PARAM_Test, createFromLexer) {
    const generic::NSEC3PARAM rdata_nsec3param(nsec3param_txt);
    EXPECT_EQ(0, rdata_nsec3param.compare(
        *test::createRdataUsingLexer(RRType::NSEC3PARAM(), RRClass::IN(),
                                     nsec3param_txt)));
}

TEST_F(Rdata_NSEC3PARAM_Test, toWireRenderer) {
    renderer.skip(2);
    const generic::NSEC3PARAM rdata_nsec3param(nsec3param_txt);
    rdata_nsec3param.toWire(renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_nsec3param_fromWire1", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(renderer.getData()) + 2,
                        renderer.getLength() - 2, &data[2], data.size() - 2);
}

TEST_F(Rdata_NSEC3PARAM_Test, toWireBuffer) {
    const generic::NSEC3PARAM rdata_nsec3param(nsec3param_txt);
    rdata_nsec3param.toWire(obuffer);
}

TEST_F(Rdata_NSEC3PARAM_Test, assign) {
    generic::NSEC3PARAM rdata_nsec3param(nsec3param_txt);
    generic::NSEC3PARAM other_nsec3param = rdata_nsec3param;
    EXPECT_EQ(0, rdata_nsec3param.compare(other_nsec3param));
}

TEST_F(Rdata_NSEC3PARAM_Test, compare) {
    // trivial case: self equivalence
    EXPECT_EQ(0, generic::NSEC3PARAM(nsec3param_txt).
              compare(generic::NSEC3PARAM(nsec3param_txt)));
    EXPECT_EQ(0, generic::NSEC3PARAM("1 1 1 -").
              compare(generic::NSEC3PARAM("1 1 1 -")));

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(generic::NSEC3PARAM(nsec3param_txt).compare(*rdata_nomatch),
                 bad_cast);
}

}
