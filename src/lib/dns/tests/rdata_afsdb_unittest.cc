// Copyright (C) 2011-2013  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

const char* const afsdb_text = "1 afsdb.example.com.";
const char* const afsdb_text2 = "0 root.example.com.";
const char* const too_long_label("012345678901234567890123456789"
        "0123456789012345678901234567890123.");

namespace {
class Rdata_AFSDB_Test : public RdataTest {
protected:
    Rdata_AFSDB_Test() :
        rdata_afsdb(string(afsdb_text)), rdata_afsdb2(string(afsdb_text2))
    {}

    const generic::AFSDB rdata_afsdb;
    const generic::AFSDB rdata_afsdb2;
    vector<uint8_t> expected_wire;
};


TEST_F(Rdata_AFSDB_Test, createFromText) {
    EXPECT_EQ(1, rdata_afsdb.getSubtype());
    EXPECT_EQ(Name("afsdb.example.com."), rdata_afsdb.getServer());

    EXPECT_EQ(0, rdata_afsdb2.getSubtype());
    EXPECT_EQ(Name("root.example.com."), rdata_afsdb2.getServer());
}

TEST_F(Rdata_AFSDB_Test, badText) {
    // subtype is too large
    EXPECT_THROW(const generic::AFSDB rdata_afsdb("99999999 afsdb.example.com."),
                 InvalidRdataText);
    // incomplete text
    EXPECT_THROW(const generic::AFSDB rdata_afsdb("10"), InvalidRdataText);
    EXPECT_THROW(const generic::AFSDB rdata_afsdb("SPOON"), InvalidRdataText);
    EXPECT_THROW(const generic::AFSDB rdata_afsdb("1root.example.com."), InvalidRdataText);
    // number of fields (must be 2) is incorrect
    EXPECT_THROW(const generic::AFSDB rdata_afsdb("10 afsdb. example.com."),
                 InvalidRdataText);
    // No origin and relative
    EXPECT_THROW(const generic::AFSDB rdata_afsdb("1 afsdb.example.com"),
                 MissingNameOrigin);
    // bad name
    EXPECT_THROW(const generic::AFSDB rdata_afsdb("1 afsdb.example.com." +
                 string(too_long_label)), TooLongLabel);
}

TEST_F(Rdata_AFSDB_Test, copy) {
    const generic::AFSDB rdata_afsdb2(rdata_afsdb);
    EXPECT_EQ(0, rdata_afsdb.compare(rdata_afsdb2));
}

TEST_F(Rdata_AFSDB_Test, assignment) {
    generic::AFSDB copy((string(afsdb_text2)));
    copy = rdata_afsdb;
    EXPECT_EQ(0, copy.compare(rdata_afsdb));

    // Check if the copied data is valid even after the original is deleted
    generic::AFSDB* copy2 = new generic::AFSDB(rdata_afsdb);
    generic::AFSDB copy3((string(afsdb_text2)));
    copy3 = *copy2;
    delete copy2;
    EXPECT_EQ(0, copy3.compare(rdata_afsdb));

    // Self assignment
    copy = copy;
    EXPECT_EQ(0, copy.compare(rdata_afsdb));
}

TEST_F(Rdata_AFSDB_Test, createFromWire) {
    // uncompressed names
    EXPECT_EQ(0, rdata_afsdb.compare(
                  *rdataFactoryFromFile(RRType::AFSDB(), RRClass::IN(),
                                     "rdata_afsdb_fromWire1.wire")));
    // compressed name
    EXPECT_EQ(0, rdata_afsdb.compare(
                  *rdataFactoryFromFile(RRType::AFSDB(), RRClass::IN(),
                                     "rdata_afsdb_fromWire2.wire", 13)));
    // RDLENGTH is too short
    EXPECT_THROW(rdataFactoryFromFile(RRType::AFSDB(), RRClass::IN(),
                                     "rdata_afsdb_fromWire3.wire"),
                 InvalidRdataLength);
    // RDLENGTH is too long
    EXPECT_THROW(rdataFactoryFromFile(RRType::AFSDB(), RRClass::IN(),
                                      "rdata_afsdb_fromWire4.wire"),
                 InvalidRdataLength);
    // bogus server name, the error should be detected in the name
    // constructor
    EXPECT_THROW(rdataFactoryFromFile(RRType::AFSDB(), RRClass::IN(),
                                      "rdata_afsdb_fromWire5.wire"),
                 DNSMessageFORMERR);
}

TEST_F(Rdata_AFSDB_Test, createFromLexer) {
    EXPECT_EQ(0, rdata_afsdb.compare(
        *test::createRdataUsingLexer(RRType::AFSDB(), RRClass::IN(),
                                     afsdb_text)));

    // test::createRdataUsingLexer() constructs relative to
    // "example.org." origin.
    generic::AFSDB tmp = generic::AFSDB("1 afsdb2.example.org.");
    EXPECT_EQ(0, tmp.compare(
        *test::createRdataUsingLexer(RRType::AFSDB(), RRClass::IN(),
                                     "1 afsdb2")));

    // Exceptions cause NULL to be returned.
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::AFSDB(), RRClass::IN(),
                                             "1root.example.com."));

    // 65536 is larger than maximum possible subtype
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::AFSDB(), RRClass::IN(),
                                             "65536 afsdb.example.com."));

    // Extra text at end of line
    EXPECT_FALSE(test::createRdataUsingLexer(RRType::AFSDB(), RRClass::IN(),
                                             "1 afsdb.example.com. extra."));
}

TEST_F(Rdata_AFSDB_Test, toWireBuffer) {
    // construct actual data
    rdata_afsdb.toWire(obuffer);

    // construct expected data
    UnitTestUtil::readWireData("rdata_afsdb_toWire1.wire", expected_wire);

    // then compare them
    matchWireData(&expected_wire[0], expected_wire.size(),
                  obuffer.getData(), obuffer.getLength());

    // clear buffer for the next test
    obuffer.clear();

    // construct actual data
    Name("example.com.").toWire(obuffer);
    rdata_afsdb2.toWire(obuffer);

    // construct expected data
    UnitTestUtil::readWireData("rdata_afsdb_toWire2.wire", expected_wire);

    // then compare them
    matchWireData(&expected_wire[0], expected_wire.size(),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(Rdata_AFSDB_Test, toWireRenderer) {
    // similar to toWireBuffer, but names in RDATA could be compressed due to
    // preceding names.  Actually they must not be compressed according to
    // RFC3597, and this test checks that.

    // construct actual data
    rdata_afsdb.toWire(renderer);

    // construct expected data
    UnitTestUtil::readWireData("rdata_afsdb_toWire1.wire", expected_wire);

    // then compare them
    matchWireData(&expected_wire[0], expected_wire.size(),
                  renderer.getData(), renderer.getLength());

    // clear renderer for the next test
    renderer.clear();

    // construct actual data
    renderer.writeName(Name("example.com."));
    rdata_afsdb2.toWire(renderer);

    // construct expected data
    UnitTestUtil::readWireData("rdata_afsdb_toWire2.wire", expected_wire);

    // then compare them
    matchWireData(&expected_wire[0], expected_wire.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(Rdata_AFSDB_Test, toText) {
    EXPECT_EQ(afsdb_text, rdata_afsdb.toText());
    EXPECT_EQ(afsdb_text2, rdata_afsdb2.toText());
}

TEST_F(Rdata_AFSDB_Test, compare) {
    // check reflexivity
    EXPECT_EQ(0, rdata_afsdb.compare(rdata_afsdb));

    // name must be compared in case-insensitive manner
    EXPECT_EQ(0, rdata_afsdb.compare(generic::AFSDB("1 "
                                "AFSDB.example.com.")));

    const generic::AFSDB small1("10 afsdb.example.com.");
    const generic::AFSDB large1("65535 afsdb.example.com.");
    const generic::AFSDB large2("256 afsdb.example.com.");

    // confirm these are compared as unsigned values
    EXPECT_GT(0, rdata_afsdb.compare(large1));
    EXPECT_LT(0, large1.compare(rdata_afsdb));

    // confirm these are compared in network byte order
    EXPECT_GT(0, small1.compare(large2));
    EXPECT_LT(0, large2.compare(small1));

    // another AFSDB whose server name is larger than that of rdata_afsdb.
    const generic::AFSDB large3("256 zzzzz.example.com.");
    EXPECT_GT(0, large2.compare(large3));
    EXPECT_LT(0, large3.compare(large2));

    // comparison attempt between incompatible RR types should be rejected
    EXPECT_THROW(rdata_afsdb.compare(*rdata_nomatch), bad_cast);
}
}
