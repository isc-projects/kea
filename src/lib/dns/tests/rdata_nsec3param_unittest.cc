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

#include <exceptions/exceptions.h>

#include <dns/util/base32hex.h>
#include <dns/buffer.h>
#include <dns/util/hex.h>
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
using namespace isc::dns::rdata;

namespace {
class Rdata_NSEC3PARAM_Test : public RdataTest {
    // there's nothing to specialize
};
string nsec3param_txt("1 0 1 D399EAAB");

TEST_F(Rdata_NSEC3PARAM_Test, toText) {
    const generic::NSEC3PARAM rdata_nsec3param(nsec3param_txt);
    EXPECT_EQ(nsec3param_txt, rdata_nsec3param.toText());
}

TEST_F(Rdata_NSEC3PARAM_Test, badText) {
    EXPECT_THROW(generic::NSEC3PARAM("1 1 1 SPORK"), BadValue); // bad hex
    EXPECT_THROW(generic::NSEC3PARAM("100000 1 1 ADDAFEE"), InvalidRdataText);
    EXPECT_THROW(generic::NSEC3PARAM("1 100000 1 ADDAFEE"), InvalidRdataText);
    EXPECT_THROW(generic::NSEC3PARAM("1 1 100000 ADDAFEE"), InvalidRdataText);
    EXPECT_THROW(generic::NSEC3PARAM("1"), InvalidRdataText);
}

TEST_F(Rdata_NSEC3PARAM_Test, DISABLED_badText) {
    // this currently fails
    EXPECT_THROW(generic::NSEC3PARAM("1 0 1D399EAAB"), InvalidRdataText);
}

TEST_F(Rdata_NSEC3PARAM_Test, createFromWire) {
    const generic::NSEC3PARAM rdata_nsec3param(nsec3param_txt);
    EXPECT_EQ(0, rdata_nsec3param.compare(
                  *rdataFactoryFromFile(RRType::NSEC3PARAM(), RRClass::IN(),
                                       "rdata_nsec3param_fromWire1")));
}

TEST_F(Rdata_NSEC3PARAM_Test, toWireRenderer) {
    renderer.skip(2);
    const generic::NSEC3PARAM rdata_nsec3param(nsec3param_txt);
    rdata_nsec3param.toWire(renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_nsec3param_fromWire1", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(obuffer.getData()) + 2,
                        obuffer.getLength() - 2, &data[2], data.size() - 2);
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

}
