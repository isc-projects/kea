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
class Rdata_DS_Test : public RdataTest {
    // there's nothing to specialize
};

string ds_txt("12892 5 2 F1E184C0E1D615D20EB3C223ACED3B03C773DD952D"
              "5F0EB5C777586DE18DA6B5");
const generic::DS rdata_ds(ds_txt);

TEST_F(Rdata_DS_Test, toText_DS) {
    EXPECT_EQ(ds_txt, rdata_ds.toText());
}

TEST_F(Rdata_DS_Test, badText_DS) {
    EXPECT_THROW(const generic::DS ds2("99999 5 2 BEEF"), InvalidRdataText);
    EXPECT_THROW(const generic::DS ds2("11111 555 2 BEEF"), InvalidRdataText);
    EXPECT_THROW(const generic::DS ds2("11111 5 22222 BEEF"), InvalidRdataText);
    EXPECT_THROW(const generic::DS ds2("11111 5 2"), InvalidRdataText);
    EXPECT_THROW(const generic::DS ds2("GARBAGE IN"), InvalidRdataText);
}

TEST_F(Rdata_DS_Test, createFromWire_DS) {
    EXPECT_EQ(0, rdata_ds.compare(
                  *rdataFactoryFromFile(RRType::DS(), RRClass::IN(),
                                        "testdata/rdata_ds_fromWire")));
}

TEST_F(Rdata_DS_Test, getTag_DS) {
    EXPECT_EQ(12892, rdata_ds.getTag());
}

TEST_F(Rdata_DS_Test, toWireRenderer) {
    renderer.skip(2);
    generic::DS rdata_ds(ds_txt);
    rdata_ds.toWire(renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("testdata/rdata_ds_fromWire", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(obuffer.getData()) + 2,
                        obuffer.getLength() - 2, &data[2], data.size() - 2);
}

TEST_F(Rdata_DS_Test, toWireBuffer) {
    generic::DS rdata_ds(ds_txt);
    rdata_ds.toWire(obuffer);
}

TEST_F(Rdata_DS_Test, compare) {
    // trivial case: self equivalence
    EXPECT_EQ(0, generic::DS(ds_txt).compare(generic::DS(ds_txt)));

    // TODO: need more tests
}

}
