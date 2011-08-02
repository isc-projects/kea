// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
#include <dns/exceptions.h>
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
using namespace isc::dns::rdata::in;

namespace {
class Rdata_IN_NAPTR_Test : public RdataTest {
};

// 10 100 "S" "SIP+D2U" "" _sip._udp.example.com.
static uint8_t naptr_rdata[] = {0x00,0x0a,0x00,0x64,0x01,0x53,0x07,0x53,0x49,0x50,0x2b,0x44,0x32,0x55,0x00,0x04,0x5f,0x73,0x69,0x70,
    0x04,0x5f,0x75,0x64,0x70,0x07,0x65,0x78,0x61,0x6d,0x70,0x6c,0x65,0x03,0x63,0x6f,0x6d,0x00};

static const char *naptr_str = "10 100 \"S\" \"SIP+D2U\" \"\" _sip._udp.example.com.";

TEST_F(Rdata_IN_NAPTR_Test, createFromText) {
    NAPTR naptr(naptr_str);
    EXPECT_EQ(10, naptr.getOrder());
    EXPECT_EQ(100, naptr.getPreference());
    EXPECT_EQ(string("S"), naptr.getFlags());
}

TEST_F(Rdata_IN_NAPTR_Test, createFromWire) {
}

}
