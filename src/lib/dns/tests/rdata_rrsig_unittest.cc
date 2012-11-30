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

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <util/time_utilities.h>
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
using namespace isc::dns::rdata;

namespace {
class Rdata_RRSIG_Test : public RdataTest {
public:
    Rdata_RRSIG_Test() :
        rrsig_txt("A 5 4 43200 20100223214617 20100222214617 8496 isc.org. "
                  "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                  "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                  "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                  "f49t+sXKPzbipN9g+s1ZPiIyofc="),
        rdata_rrsig(rrsig_txt)
    {}

    const string rrsig_txt;
    const generic::RRSIG rdata_rrsig;
};

TEST_F(Rdata_RRSIG_Test, fromText) {
    EXPECT_EQ(rrsig_txt, rdata_rrsig.toText());
    EXPECT_EQ(isc::dns::RRType::A(), rdata_rrsig.typeCovered());
}

TEST_F(Rdata_RRSIG_Test, badText) {
    EXPECT_THROW(const generic::RRSIG sig("SPORK"), InvalidRdataText);
    EXPECT_THROW(const generic::RRSIG sig("A 555 4 43200 "
                     "20100223214617 20100222214617 8496 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc="), InvalidRdataText);
    EXPECT_THROW(const generic::RRSIG sig("A 5 4444 43200 "
                     "20100223214617 20100222214617 8496 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc="), InvalidRdataText);
    EXPECT_THROW(const generic::RRSIG sig("A 5 4 999999999999 "
                     "20100223214617 20100222214617 8496 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc="), InvalidRdataText);
    EXPECT_THROW(const generic::RRSIG sig("A 5 4 43200 "
                     "20100223 20100227 8496 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc="), InvalidTime);
    EXPECT_THROW(const generic::RRSIG sig("A 5 4 43200 "
                     "20100223214617 20100222214617 999999 isc.org. "
                     "evxhlGx13mpKLVkKsjpGzycS5twtIoxOmlN14w9t5AgzGBmz"
                     "diGdLIrFabqr72af2rUq+UDBKMWXujwZTZUTws32sVldDPk/"
                     "NbuacJM25fQXfv5mO3Af7TOoow3AjMaVG9icjCW0V55WcWQU"
                     "f49t+sXKPzbipN9g+s1ZPiIyofc="), InvalidRdataText);
    EXPECT_THROW(const generic::RRSIG sig(
                     "A 5 4 43200 "
                     "20100223214617 20100222214617 8496 isc.org. "
                     "EEeeeeeeEEEeeeeeeGaaahAAAAAAAAHHHHHHHHHHH!="),
                 BadValue);     // bad base64 input
}

TEST_F(Rdata_RRSIG_Test, DISABLED_badText) {
    // this currently fails
    // no space between the tag and signer
    EXPECT_THROW(generic::RRSIG("A 5 4 43200 20100223214617 20100222214617 "
                                "8496isc.org. ofc="), InvalidRdataText);
}

TEST_F(Rdata_RRSIG_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_rrsig.compare(
        *test::createRdataUsingLexer(RRType::RRSIG(), RRClass::IN(),
                                     rrsig_txt)));

    // Exceptions cause NULL to be returned.
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::RRSIG(), RRClass::IN(),
                                             "INVALIDINPUT"));
}

TEST_F(Rdata_RRSIG_Test, toWireRenderer) {
    // FIXME: This doesn't check the result.
    rdata_rrsig.toWire(renderer);
}

TEST_F(Rdata_RRSIG_Test, toWireBuffer) {
    // FIXME: This doesn't check the result.
    rdata_rrsig.toWire(obuffer);
}

TEST_F(Rdata_RRSIG_Test, createFromWire) {
    const string rrsig_txt2(
        "A 5 2 43200 20100327070149 20100225070149 2658 isc.org. "
        "HkJk/xZTvzePU8NENl/ley8bbUumhk1hXciyqhLnz1VQFzkDooej6neX"
        "ZgWZzQKeTKPOYWrnYtdZW4PnPQFeUl3orgLev7F8J6FZlDn0y/J/ThR5"
        "m36Mo2/Gdxjj8lJ/IjPVkdpKyBpcnYND8KEIma5MyNCNeyO1UkfPQZGHNSQ=");
    EXPECT_EQ(rrsig_txt2,
              rdataFactoryFromFile(RRType("RRSIG"), RRClass("IN"),
                                   "rdata_rrsig_fromWire1")->toText());
    const generic::RRSIG rdata_rrsig2(rrsig_txt2);
    EXPECT_EQ(0, rdata_rrsig2.compare(
                      *rdataFactoryFromFile(RRType("RRSIG"), RRClass("IN"),
                                          "rdata_rrsig_fromWire1")));

    // RDLEN is too short
    EXPECT_THROW(rdataFactoryFromFile(RRType::RRSIG(), RRClass::IN(),
                                      "rdata_rrsig_fromWire2.wire"),
                 InvalidRdataLength);
}
}
