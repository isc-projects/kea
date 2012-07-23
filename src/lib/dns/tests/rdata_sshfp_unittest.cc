// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <algorithm>
#include <string>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>
#include <boost/algorithm/string.hpp>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;

namespace {
class Rdata_SSHFP_Test : public RdataTest {
    // there's nothing to specialize
};

const string sshfp_txt("2 1 123456789abcdef67890123456789abcdef67890");
const generic::SSHFP rdata_sshfp(2, 1, "123456789abcdef67890123456789abcdef67890");

TEST_F(Rdata_SSHFP_Test, createFromText) {
    // Basic test
    const generic::SSHFP rdata_sshfp2(sshfp_txt);
    EXPECT_EQ(0, rdata_sshfp2.compare(rdata_sshfp));

    // With different spacing
    const generic::SSHFP rdata_sshfp3("2 1   123456789abcdef67890123456789abcdef67890");
    EXPECT_EQ(0, rdata_sshfp3.compare(rdata_sshfp));

    // Combination of lowercase and uppercase
    const generic::SSHFP rdata_sshfp4("2 1   123456789ABCDEF67890123456789abcdef67890");
    EXPECT_EQ(0, rdata_sshfp4.compare(rdata_sshfp));
}

TEST_F(Rdata_SSHFP_Test, algorithmTypes) {
    // Some of these may not be RFC conformant, but we relax the check
    // in our code to work with algorithm and fingerprint types that may
    // show up in the future.
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("1 1 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("2 1 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("3 1 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("128 1 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("255 1 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("1 1 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("1 2 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("1 3 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("1 128 12ab"));
    EXPECT_NO_THROW(const generic::SSHFP rdata_sshfp("1 255 12ab"));

    // 0 is still reserved.
    EXPECT_THROW(const generic::SSHFP rdata_sshfp("0 1 12ab"),
                 InvalidRdataText);
    EXPECT_THROW(const generic::SSHFP rdata_sshfp("1 0 12ab"),
                 InvalidRdataText);

    // > 255 would be broken
    EXPECT_THROW(const generic::SSHFP rdata_sshfp("256 1 12ab"),
                 InvalidRdataText);
    EXPECT_THROW(const generic::SSHFP rdata_sshfp("2 256 12ab"),
                 InvalidRdataText);
}

TEST_F(Rdata_SSHFP_Test, badText) {
    EXPECT_THROW(const generic::SSHFP rdata_sshfp("1"), InvalidRdataText);
    EXPECT_THROW(const generic::SSHFP rdata_sshfp("1 2"), InvalidRdataText);
    EXPECT_THROW(const generic::SSHFP rdata_sshfp("BUCKLE MY SHOES"), InvalidRdataText);
    EXPECT_THROW(const generic::SSHFP rdata_sshfp("1 2 foo bar"), InvalidRdataText);
}

TEST_F(Rdata_SSHFP_Test, copy) {
    const generic::SSHFP rdata_sshfp2(rdata_sshfp);
    EXPECT_EQ(0, rdata_sshfp.compare(rdata_sshfp2));
}

TEST_F(Rdata_SSHFP_Test, createFromWire) {
    // Basic test
    EXPECT_EQ(0, rdata_sshfp.compare(
                  *rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                        "rdata_sshfp_fromWire")));
    // Combination of lowercase and uppercase
    EXPECT_EQ(0, rdata_sshfp.compare(
                  *rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                        "rdata_sshfp_fromWire2")));
    // algorithm=1, fingerprint=1
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                         "rdata_sshfp_fromWire3.wire"));

    // algorithm=255, fingerprint=1
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                         "rdata_sshfp_fromWire4.wire"));

    // algorithm=0, fingerprint=1
    EXPECT_THROW(rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                      "rdata_sshfp_fromWire5.wire"),
                 InvalidRdataText);

    // algorithm=5, fingerprint=0
    EXPECT_THROW(rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                      "rdata_sshfp_fromWire6.wire"),
                 InvalidRdataText);

    // algorithm=255, fingerprint=255
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType("SSHFP"), RRClass("IN"),
                                         "rdata_sshfp_fromWire7.wire"));
}

TEST_F(Rdata_SSHFP_Test, toText) {
    EXPECT_TRUE(boost::iequals(sshfp_txt, rdata_sshfp.toText()));
}

TEST_F(Rdata_SSHFP_Test, getSSHFPAlgorithmNumber) {
    EXPECT_EQ(2, rdata_sshfp.getSSHFPAlgorithmNumber());
}

TEST_F(Rdata_SSHFP_Test, getSSHFPFingerprintType) {
    EXPECT_EQ(1, rdata_sshfp.getSSHFPFingerprintType());
}
}
