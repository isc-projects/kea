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
                                         "rdata_opt_fromWire1"));
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType::OPT(), RRClass::CH(),
                                         "rdata_opt_fromWire1", 2));

    // Short RDLEN. This throws InvalidRdataLength even if subsequent
    // pseudo RRs cause RDLEN size to be exhausted.
    EXPECT_THROW(rdataFactoryFromFile(RRType::OPT(), RRClass::IN(),
                                      "rdata_opt_fromWire2"),
                 InvalidRdataLength);
    EXPECT_THROW(rdataFactoryFromFile(RRType::OPT(), RRClass::IN(),
                                      "rdata_opt_fromWire3"),
                 InvalidRdataLength);
    // Option lengths can add up and overflow RDLEN. Unlikely when
    // parsed from wire data, but we'll check for it anyway.
    EXPECT_THROW(rdataFactoryFromFile(RRType::OPT(), RRClass::IN(),
                                      "rdata_opt_fromWire4"),
                 InvalidRdataText);

    // short buffer case.
    EXPECT_THROW(rdataFactoryFromFile(RRType::OPT(), RRClass::IN(),
                                      "rdata_opt_fromWire1", 11),
                 InvalidBufferPosition);
}

TEST_F(Rdata_OPT_Test, createFromLexer) {
    // OPT RR cannot be created from text. Exceptions cause NULL to be
    // returned.
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::OPT(), RRClass::IN(),
                                             "this does not matter"));
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
    EXPECT_THROW(rdata_opt.toText(),
                 isc::InvalidOperation);
}

TEST_F(Rdata_OPT_Test, compare) {
    EXPECT_THROW(rdata_opt.compare(
                  *rdataFactoryFromFile(RRType::OPT(), RRClass::CH(),
                                        "rdata_opt_fromWire1", 2)),
                 isc::InvalidOperation);

    // comparison attempt between incompatible RR types also results in
    // isc::InvalidOperation.
    EXPECT_THROW(rdata_opt.compare(*RdataTest::rdata_nomatch),
                 isc::InvalidOperation);
}

TEST_F(Rdata_OPT_Test, append) {
    EXPECT_THROW(rdata_opt.toText(),
                 isc::InvalidOperation);
}

TEST_F(Rdata_OPT_Test, getPseudoRRs) {
    const generic::OPT rdf =
        dynamic_cast<const generic::OPT&>
        (*rdataFactoryFromFile(RRType("OPT"), RRClass("IN"),
                               "rdata_opt_fromWire1", 2));

    const std::vector<generic::OPT::PseudoRR>& rrs = rdf.getPseudoRRs();
    ASSERT_FALSE(rrs.empty());
    EXPECT_EQ(1, rrs.size());
    EXPECT_EQ(3, rrs.at(0).getCode());
    EXPECT_EQ(3, rrs.at(0).getLength());

    const uint8_t expected_data[] = {0x00, 0x01, 0x02};
    const uint8_t* actual_data = rrs.at(0).getData();
    EXPECT_EQ(0, std::memcmp(expected_data, actual_data,
                             sizeof(expected_data)));
}
}
