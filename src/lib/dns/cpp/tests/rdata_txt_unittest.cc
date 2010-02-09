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

#include <dns/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include "unittest_util.h"
#include "rdata_unittest.h"

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {
class Rdata_TXT_Test : public RdataTest {
    // there's nothing to specialize
};

const generic::TXT rdata_txt("Test String");
const generic::TXT rdata_txt_quoated("\"Test String\"");
const uint8_t wiredata_txt[] = {
    sizeof("Test String") - 1,
    'T', 'e', 's', 't', ' ', 'S', 't', 'r', 'i', 'n', 'g'
};

TEST_F(RdataTest, createFromText)
{
    EXPECT_EQ(0, rdata_txt.compare(rdata_txt_quoated));
}

TEST_F(Rdata_TXT_Test, createFromWire)
{
    EXPECT_EQ(0, rdata_txt.compare(
                  *rdataFactoryFromFile(RRType("TXT"), RRClass("IN"),
                                        "testdata/rdata_txt_fromWire")));
}

TEST_F(Rdata_TXT_Test, toWireBuffer)
{
    rdata_txt.toWire(obuffer);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        obuffer.getData(), obuffer.getLength(),
                        wiredata_txt, sizeof(wiredata_txt));
}

TEST_F(Rdata_TXT_Test, toText)
{
    EXPECT_EQ("\"Test String\"", rdata_txt.toText());
}
}
