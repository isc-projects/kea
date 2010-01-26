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

#include "buffer.h"
#include "messagerenderer.h"
#include "name.h"
#include "rdata.h"
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
                  rrset_ns(test_domain, RRClass::IN(), RRType::NS(),
                           RRTTL(86400))
    {}

    OutputBuffer buffer;
    MessageRenderer renderer;
    Name test_name;
    Name test_domain;
    Name test_nsname;
    RRset rrset_a;
    RRset rrset_ns;
    std::vector<unsigned char> wiredata;
};

TEST_F(RRsetTest, addRdata)
{
    rrset_a.addRdata(in::A("192.0.2.1"));
    rrset_a.addRdata(in::A("192.0.2.2"));

    RdataIteratorPtr it = rrset_a.getRdataIterator();
    it->first();
    EXPECT_FALSE(it->isLast());
    EXPECT_EQ("192.0.2.1", it->getCurrent().toText());
    it->next();
    EXPECT_FALSE(it->isLast());
    EXPECT_EQ("192.0.2.2", it->getCurrent().toText());
    it->next();
    EXPECT_TRUE(it->isLast());

    EXPECT_EQ("test.example.com. 3600 IN A 192.0.2.1\n"
              "test.example.com. 3600 IN A 192.0.2.2\n", rrset_a.toText());
}

TEST_F(RRsetTest, toWireBuffer)
{
    rrset_a.addRdata(in::A("192.0.2.1"));
    rrset_a.addRdata(in::A("192.0.2.2"));
    rrset_a.toWire(buffer);

    UnitTestUtil::readWireData("testdata/rrset_toWire1", wiredata);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, buffer.getData(),
                        buffer.getLength(), &wiredata[0], wiredata.size());
}

TEST_F(RRsetTest, toWireRenderer)
{
    rrset_a.addRdata(in::A("192.0.2.1"));
    rrset_a.addRdata(in::A("192.0.2.2"));
    rrset_ns.addRdata(generic::NS(test_nsname));

    rrset_a.toWire(renderer);
    rrset_ns.toWire(renderer);

    UnitTestUtil::readWireData("testdata/rrset_toWire2", wiredata);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, buffer.getData(),
                        buffer.getLength(), &wiredata[0], wiredata.size());
}

}
