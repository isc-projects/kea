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
class Rdata_OPT_Test : public RdataTest {
    // there's nothing to specialize
};

const generic::OPT rdata_opt;

TEST_F(Rdata_OPT_Test, createFromText) {
    // OPT RR cannot be created from text.
    EXPECT_THROW(generic::OPT("this does not matter"), InvalidRdataText);
}

TEST_F(Rdata_OPT_Test, createFromWire) {
    // Valid cases: in the simple implementation with no supported options,
    // we can only check these don't throw.
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType::OPT(), RRClass("CLASS4096"),
                                         "rdata_opt_fromWire"));
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType::OPT(), RRClass::CH(),
                                         "rdata_opt_fromWire", 2));

    // short buffer case.
    EXPECT_THROW(rdataFactoryFromFile(RRType::OPT(), RRClass::IN(),
                                      "rdata_opt_fromWire", 11),
                 InvalidRdataLength);
}

TEST_F(Rdata_OPT_Test, createFromLexer) {
    // OPT RR cannot be created from text.
    EXPECT_THROW({
        *test::createRdataUsingLexer(RRType::OPT(), RRClass::IN(),
                                     "this does not matter");
    }, InvalidRdataText);
}

TEST_F(Rdata_OPT_Test, toWireBuffer) {
    rdata_opt.toWire(obuffer);
    EXPECT_EQ(0, obuffer.getLength());
}

TEST_F(Rdata_OPT_Test, toWireRenderer) {
    rdata_opt.toWire(renderer);
    EXPECT_EQ(0, obuffer.getLength());
}

TEST_F(Rdata_OPT_Test, toText) {
    EXPECT_EQ("", rdata_opt.toText());
}

TEST_F(Rdata_OPT_Test, compare) {
    // This simple implementation always returns "true"
    EXPECT_EQ(0, rdata_opt.compare(
                  *rdataFactoryFromFile(RRType::OPT(), RRClass::CH(),
                                        "rdata_opt_fromWire", 2)));

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(rdata_opt.compare(*RdataTest::rdata_nomatch), bad_cast); 
}
}
