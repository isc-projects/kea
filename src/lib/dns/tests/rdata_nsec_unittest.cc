// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>

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
#include <util/unittests/wiredata.h>

using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
class Rdata_NSEC_Test : public RdataTest {
    // there's nothing to specialize
};

const char* const nsec_txt = "www2.isc.org. CNAME RRSIG NSEC";

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
                                        "rdata_nsec_fromWire1")));

    // Too short RDLENGTH
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "rdata_nsec_fromWire2"),
                 DNSMessageFORMERR);

    // Invalid bitmap cases are tested in Rdata_NSECBITMAP_Test.
}

TEST_F(Rdata_NSEC_Test, createFromLexer_NSEC) {
    const generic::NSEC rdata_nsec(nsec_txt);
    EXPECT_EQ(0, rdata_nsec.compare(
        *test::createRdataUsingLexer(RRType::NSEC(), RRClass::IN(),
                                     nsec_txt)));

    // test::createRdataUsingLexer() constructs relative to
    // "example.org." origin.
    EXPECT_EQ(0, generic::NSEC("www2.example.org. CNAME RRSIG NSEC").compare(
        *test::createRdataUsingLexer(RRType::NSEC(), RRClass::IN(),
                                     "www2 CNAME RRSIG NSEC")));

    // Exceptions cause NULL to be returned.
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::NSEC(), RRClass::IN(),
                                             "www.isc.org."));
}

TEST_F(Rdata_NSEC_Test, toWireRenderer_NSEC) {
    renderer.skip(2);
    const generic::NSEC rdata_nsec(nsec_txt);
    rdata_nsec.toWire(renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_nsec_fromWire1", data);
    matchWireData(&data[2], data.size() - 2,
                  static_cast<const uint8_t *>(renderer.getData()) + 2,
                  renderer.getLength() - 2);
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

TEST_F(Rdata_NSEC_Test, getNextName) {
    // The implementation is quite trivial, so we simply check it's actually
    // defined and does work as intended in a simple case.
    EXPECT_EQ(Name("www2.isc.org"), generic::NSEC((nsec_txt)).getNextName());
}

TEST_F(Rdata_NSEC_Test, compare) {
    // trivial case: self equivalence
    EXPECT_EQ(0, generic::NSEC("example. A").
              compare(generic::NSEC("example. A")));
    EXPECT_EQ(0, generic::NSEC("EXAMPLE. A"). // should be case insensitive
              compare(generic::NSEC("example. A")));

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(generic::NSEC(nsec_txt).compare(*rdata_nomatch),
                 bad_cast);

    // test RDATAs, sorted in the ascendent order.  We only compare the
    // next name here.  Bitmap comparison is tested in the bitmap tests.
    // Note that names are compared as wire-format data, not based on the
    // domain name comparison.
    vector<generic::NSEC> compare_set;
    compare_set.push_back(generic::NSEC("a.example. A"));
    compare_set.push_back(generic::NSEC("example. A"));
    vector<generic::NSEC>::const_iterator it;
    const vector<generic::NSEC>::const_iterator it_end = compare_set.end();
    for (it = compare_set.begin(); it != it_end - 1; ++it) {
        SCOPED_TRACE("compare " + it->toText() + " to " + (it + 1)->toText());
        EXPECT_GT(0, (*it).compare(*(it + 1)));
        EXPECT_LT(0, (*(it + 1)).compare(*it));
    }
}

}
