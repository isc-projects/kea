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

// $Id: rrtype_unittest.cc 476 2010-01-19 00:29:28Z jinmei $

#include <stdint.h>

#include <vector>
#include <string>

#include <dns/hex.h>

#include <gtest/gtest.h>

#include "unittest_util.h"

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;

namespace {
class HexTest : public ::testing::Test {
protected:
    HexTest() {}
};

const std::string hex_txt("DEADBEEFDECADE");
const std::string hex_txt_lower("deadbeefdecade");

TEST_F(HexTest, encodeHex) {
    std::vector<uint8_t> data;

    data.push_back(0xde);
    data.push_back(0xad);
    data.push_back(0xbe);
    data.push_back(0xef);
    data.push_back(0xde);
    data.push_back(0xca);
    data.push_back(0xde);
    EXPECT_EQ(hex_txt, encodeHex(data));
}

void
compareData(const std::vector<uint8_t>& data)
{
    EXPECT_EQ(0xde, data[0]);
    EXPECT_EQ(0xad, data[1]);
    EXPECT_EQ(0xbe, data[2]);
    EXPECT_EQ(0xef, data[3]);
    EXPECT_EQ(0xde, data[4]);
    EXPECT_EQ(0xca, data[5]);
    EXPECT_EQ(0xde, data[6]);
}

TEST_F(HexTest, decodeHex) {
    std::vector<uint8_t> result;

    decodeHex(hex_txt, result);
    compareData(result);

    // lower case hex digits should be accepted
    result.clear();
    decodeHex(hex_txt_lower, result);
    compareData(result);

    // Bogus input: should fail
    result.clear();
    EXPECT_THROW(decodeHex("1x", result), BadHexString);
}

}
