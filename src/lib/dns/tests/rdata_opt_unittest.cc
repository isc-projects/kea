// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
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
#include <util/unittests/wiredata.h>
#include <util/unittests/test_exceptions.h>

using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
class Rdata_OPT_Test : public RdataTest {
    // there's nothing to specialize
};

const uint8_t rdata_opt_wiredata[] = {
    // Option code
    0x00, 0x2a,
    // Option length
    0x00, 0x03,
    // Option data
    0x00, 0x01, 0x02
};

TEST_F(Rdata_OPT_Test, createFromText) {
    // OPT RR cannot be created from text.
    EXPECT_THROW_WITH(generic::OPT("this does not matter"), InvalidRdataText,
                      "OPT RR cannot be constructed from text");
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
    EXPECT_THROW_WITH(rdataFactoryFromFile(RRType::OPT(), RRClass::IN(),
                                           "rdata_opt_fromWire2"),
                      InvalidRdataLength,
                      "Pseudo OPT RR record too short: 1 bytes");
    EXPECT_THROW_WITH(rdataFactoryFromFile(RRType::OPT(), RRClass::IN(),
                                           "rdata_opt_fromWire3"),
                      InvalidRdataLength,
                      "Pseudo OPT RR record too short: 1 bytes");
    // Option lengths can add up and overflow RDLEN. Unlikely when
    // parsed from wire data, but we'll check for it anyway.
    EXPECT_THROW_WITH(rdataFactoryFromFile(RRType::OPT(), RRClass::IN(),
                                           "rdata_opt_fromWire4"),
                      InvalidRdataText,
                      "Option length 65535 would overflow "
                      "OPT RR RDLEN (currently 3).");

    // short buffer case.
    EXPECT_THROW_WITH(rdataFactoryFromFile(RRType::OPT(), RRClass::IN(),
                                           "rdata_opt_fromWire1", 11),
                      InvalidBufferPosition, "read beyond end of buffer");
}

TEST_F(Rdata_OPT_Test, createFromLexer) {
    // OPT RR cannot be created from text. Exceptions cause NULL to be
    // returned.
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::OPT(), RRClass::IN(),
                                             "this does not matter"));
}

TEST_F(Rdata_OPT_Test, toWireBuffer) {
    const generic::OPT rdata_opt =
        dynamic_cast<const generic::OPT&>
        (*rdataFactoryFromFile(RRType("OPT"), RRClass("IN"),
                               "rdata_opt_fromWire1", 2));

    obuffer.clear();
    rdata_opt.toWire(obuffer);

    matchWireData(rdata_opt_wiredata, sizeof(rdata_opt_wiredata),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_OPT_Test, toWireRenderer) {
    const generic::OPT rdata_opt =
        dynamic_cast<const generic::OPT&>
        (*rdataFactoryFromFile(RRType("OPT"), RRClass("IN"),
                               "rdata_opt_fromWire1", 2));

    renderer.clear();
    rdata_opt.toWire(renderer);

    matchWireData(rdata_opt_wiredata, sizeof(rdata_opt_wiredata),
                  renderer.getData(), renderer.getLength());
}

TEST_F(Rdata_OPT_Test, toText) {
    // empty OPT
    const generic::OPT rdata_opt;

    EXPECT_THROW_WITH(rdata_opt.toText(), isc::InvalidOperation,
                      "OPT RRs do not have a presentation format");
}

TEST_F(Rdata_OPT_Test, compare) {
    // empty OPT
    const generic::OPT rdata_opt;

    EXPECT_THROW_WITH(rdata_opt.compare(
                          *rdataFactoryFromFile(RRType::OPT(), RRClass::CH(),
                                                "rdata_opt_fromWire1", 2)),
                      isc::InvalidOperation,
                      "It is meaningless to compare a set of OPT pseudo RRs; "
                      "they have unspecified order");

    // comparison attempt between incompatible RR types also results in
    // isc::InvalidOperation.
    EXPECT_THROW_WITH(rdata_opt.compare(*RdataTest::rdata_nomatch),
                      isc::InvalidOperation,
                      "It is meaningless to compare a set of OPT pseudo RRs; "
                      "they have unspecified order");
}

TEST_F(Rdata_OPT_Test, appendPseudoRR) {
    generic::OPT rdata_opt;

    // Append empty option data
    rdata_opt.appendPseudoRR(0x0042, NULL, 0);

    // Append simple option data
    const uint8_t option_data[] = {'H', 'e', 'l', 'l', 'o'};
    rdata_opt.appendPseudoRR(0x0043, option_data, sizeof(option_data));

    // Duplicate option codes are okay.
    rdata_opt.appendPseudoRR(0x0042, option_data, sizeof(option_data));

    // When option length may overflow RDLEN, append should throw.
    const std::vector<uint8_t> buffer((1 << 16) - 1);
    EXPECT_THROW_WITH(rdata_opt.appendPseudoRR(0x0044, &buffer[0],
                                               buffer.size()),
                      isc::InvalidParameter,
                      "Option length 65535 would overflow "
                      "OPT RR RDLEN (currently 10).");

    const uint8_t rdata_opt_wiredata2[] = {
        // OPTION #1
        // ` Option code
        0x00, 0x42,
        // ` Option length
        0x00, 0x00,

        // OPTION #2
        // ` Option code
        0x00, 0x43,
        // ` Option length
        0x00, 0x05,
        // ` Option data
        'H', 'e', 'l', 'l', 'o',

        // OPTION #3
        // ` Option code
        0x00, 0x42,
        // ` Option length
        0x00, 0x05,
        // ` Option data
        'H', 'e', 'l', 'l', 'o'
    };

    obuffer.clear();
    rdata_opt.toWire(obuffer);

    matchWireData(rdata_opt_wiredata2, sizeof(rdata_opt_wiredata2),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_OPT_Test, getPseudoRRs) {
    const generic::OPT rdf =
        dynamic_cast<const generic::OPT&>
        (*rdataFactoryFromFile(RRType("OPT"), RRClass("IN"),
                               "rdata_opt_fromWire1", 2));

    const std::vector<generic::OPT::PseudoRR>& rrs = rdf.getPseudoRRs();
    ASSERT_FALSE(rrs.empty());
    EXPECT_EQ(1, rrs.size());
    EXPECT_EQ(0x2a, rrs.at(0).getCode());
    EXPECT_EQ(3, rrs.at(0).getLength());

    const uint8_t expected_data[] = {0x00, 0x01, 0x02};
    const uint8_t* actual_data = rrs.at(0).getData();
    EXPECT_EQ(0, std::memcmp(expected_data, actual_data,
                             sizeof(expected_data)));
}
}
