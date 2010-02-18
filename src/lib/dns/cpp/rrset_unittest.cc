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

#include <stdexcept>

#include "buffer.h"
#include "messagerenderer.h"
#include "name.h"
#include "rdata.h"
#include "rdataclass.h"
#include "rrclass.h"
#include "rrtype.h"
#include "rrttl.h"
#include "rrset.h"

#include <gtest/gtest.h>

#include "unittest_util.h"

using isc::UnitTestUtil;

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {
class RRsetTest : public ::testing::Test {
protected:
    RRsetTest() : buffer(0), renderer(buffer),
                  test_name("test.example.com"),
                  test_domain("example.com"),
                  test_nsname("ns.example.com"),
                  rrset_a(test_name, RRClass::IN(), RRType::A(), RRTTL(3600)),
                  rrset_a_empty(test_name, RRClass::IN(), RRType::A(),
                                RRTTL(3600)),
                  rrset_ns(test_domain, RRClass::IN(), RRType::NS(),
                           RRTTL(86400)),
                  rrset_ch_txt(test_domain, RRClass::CH(), RRType::TXT(),
                               RRTTL(0))
    {
        rrset_a.addRdata(in::A("192.0.2.1"));
        rrset_a.addRdata(in::A("192.0.2.2"));
    }

    OutputBuffer buffer;
    MessageRenderer renderer;
    Name test_name;
    Name test_domain;
    Name test_nsname;
    RRset rrset_a;
    RRset rrset_a_empty;
    RRset rrset_ns;
    RRset rrset_ch_txt;
    std::vector<unsigned char> wiredata;

    // max number of Rdata objects added to a test RRset object.
    // this is an arbitrary chosen limit, but should be sufficiently large
    // in practice and reasonable even as an extreme test case.
    static const int MAX_RDATA_COUNT = 100;
};

TEST_F(RRsetTest, getRdataCount)
{
    for (int i = 0; i < MAX_RDATA_COUNT; ++i) {
        EXPECT_EQ(i, rrset_a_empty.getRdataCount());
        rrset_a_empty.addRdata(in::A("192.0.2.1"));
    }
}

TEST_F(RRsetTest, getName)
{
    EXPECT_EQ(test_name, rrset_a.getName());
    EXPECT_EQ(test_domain, rrset_ns.getName());
}

TEST_F(RRsetTest, getClass)
{
    EXPECT_EQ(RRClass("IN"), rrset_a.getClass());
    EXPECT_EQ(RRClass("CH"), rrset_ch_txt.getClass());
}

TEST_F(RRsetTest, getType)
{
    EXPECT_EQ(RRType("A"), rrset_a.getType());
    EXPECT_EQ(RRType("NS"), rrset_ns.getType());
    EXPECT_EQ(RRType("TXT"), rrset_ch_txt.getType());
}

TEST_F(RRsetTest, getTTL)
{
    EXPECT_EQ(RRTTL(3600), rrset_a.getTTL());
    EXPECT_EQ(RRTTL(86400), rrset_ns.getTTL());
    EXPECT_EQ(RRTTL(0), rrset_ch_txt.getTTL());
}

TEST_F(RRsetTest, setTTL)
{
    rrset_a.setTTL(RRTTL(86400));
    EXPECT_EQ(RRTTL(86400), rrset_a.getTTL());
    rrset_a.setTTL(RRTTL(0));
    EXPECT_EQ(RRTTL(0), rrset_a.getTTL());
}

void
addRdataTestCommon(const RRset& rrset)
{
    EXPECT_EQ(2, rrset.getRdataCount());

    RdataIteratorPtr it = rrset.getRdataIterator();
    it->first();
    EXPECT_FALSE(it->isLast());
    EXPECT_EQ(0, it->getCurrent().compare(in::A("192.0.2.1")));
    it->next();
    EXPECT_FALSE(it->isLast());
    EXPECT_EQ(0, it->getCurrent().compare(in::A("192.0.2.2")));
    it->next();
    EXPECT_TRUE(it->isLast());
}

TEST_F(RRsetTest, addRdata)
{
    addRdataTestCommon(rrset_a);

    // Reference version of addRdata() doesn't allow to add a different
    // type of Rdata.
    EXPECT_THROW(rrset_a.addRdata(generic::NS(test_nsname)), std::bad_cast);
}

TEST_F(RRsetTest, addRdataPtr)
{
    rrset_a_empty.addRdata(createRdata(rrset_a_empty.getType(),
                                       rrset_a_empty.getClass(),
                                       "192.0.2.1"));
    rrset_a_empty.addRdata(createRdata(rrset_a_empty.getType(),
                                       rrset_a_empty.getClass(),
                                       "192.0.2.2"));

    addRdataTestCommon(rrset_a);

    // Pointer version of addRdata() doesn't type check and does allow to
    //add a different type of Rdata as a result.
    rrset_a_empty.addRdata(createRdata(RRType::NS(), RRClass::IN(),
                                       "ns.example.com"));
    EXPECT_EQ(3, rrset_a_empty.getRdataCount());
}

TEST_F(RRsetTest, iterator)
{
    // Iterator for an empty RRset.
    RdataIteratorPtr it = rrset_a_empty.getRdataIterator();
    it->first();
    EXPECT_TRUE(it->isLast());

    // Normal case (already tested, but do it again just in case)
    rrset_a_empty.addRdata(in::A("192.0.2.1"));
    rrset_a_empty.addRdata(in::A("192.0.2.2"));
    addRdataTestCommon(rrset_a_empty);
}

TEST_F(RRsetTest, toText)
{
    EXPECT_EQ("test.example.com. 3600 IN A 192.0.2.1\n"
              "test.example.com. 3600 IN A 192.0.2.2\n",
              rrset_a.toText());
}

TEST_F(RRsetTest, toWireBuffer)
{
    rrset_a.toWire(buffer);

    UnitTestUtil::readWireData("testdata/rrset_toWire1", wiredata);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, buffer.getData(),
                        buffer.getLength(), &wiredata[0], wiredata.size());
}

TEST_F(RRsetTest, toWireRenderer)
{
    rrset_ns.addRdata(generic::NS(test_nsname));

    rrset_a.toWire(renderer);
    rrset_ns.toWire(renderer);

    UnitTestUtil::readWireData("testdata/rrset_toWire2", wiredata);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, buffer.getData(),
                        buffer.getLength(), &wiredata[0], wiredata.size());
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST_F(RRsetTest, LeftShiftOperator)
{
    ostringstream oss;
    oss << rrset_a;
    EXPECT_EQ(rrset_a.toText(), oss.str());
}
}
