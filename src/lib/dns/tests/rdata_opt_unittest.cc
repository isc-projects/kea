// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

    EXPECT_THROW(rdata_opt.toText(),
                 isc::InvalidOperation);
}

TEST_F(Rdata_OPT_Test, compare) {
    // empty OPT
    const generic::OPT rdata_opt;

    EXPECT_THROW(rdata_opt.compare(
                  *rdataFactoryFromFile(RRType::OPT(), RRClass::CH(),
                                        "rdata_opt_fromWire1", 2)),
                 isc::InvalidOperation);

    // comparison attempt between incompatible RR types also results in
    // isc::InvalidOperation.
    EXPECT_THROW(rdata_opt.compare(*RdataTest::rdata_nomatch),
                 isc::InvalidOperation);
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
    EXPECT_THROW(rdata_opt.appendPseudoRR(0x0044, &buffer[0], buffer.size()),
                 isc::InvalidParameter);

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
