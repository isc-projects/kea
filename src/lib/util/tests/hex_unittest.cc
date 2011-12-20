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

#include <stdint.h>

#include <vector>
#include <string>

#include <exceptions/exceptions.h>

#include <util/encode/hex.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::util::encode;

namespace {
const string hex_txt("DEADBEEFDECADE");
const string hex_txt_space("DEAD BEEF DECADE");
const string hex_txt_lower("deadbeefdecade");

class HexTest : public ::testing::Test {
protected:
    HexTest() : encoding_chars("0123456789ABCDEF") {}
    vector<uint8_t> decoded_data;
    const string encoding_chars;
};

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
compareData(const std::vector<uint8_t>& data) {
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

    // white space should be ignored
    result.clear();
    decodeHex(hex_txt_space, result);
    compareData(result);

    // Bogus input: should fail
    result.clear();
    EXPECT_THROW(decodeHex("1x", result), BadValue);

    // Bogus input: encoded string must have an even number of characters.
    result.clear();
    EXPECT_THROW(decodeHex("dea", result), BadValue);
}

// For Hex encode/decode we use handmade mappings, so it's prudent to test the
// entire mapping table explicitly.
TEST_F(HexTest, decodeMap) {
    string input("00");       // input placeholder

    // See Base32HexTest.decodeMap for details of the following tests.
    for (int i = 0; i < 256; ++i) {
        input[1] = i;

        const char ch = toupper(i);
        const size_t pos = encoding_chars.find(ch);
        if (pos == string::npos) {
            EXPECT_THROW(decodeHex(input, decoded_data), BadValue);
        } else {
            decodeHex(input, decoded_data);
            EXPECT_EQ(1, decoded_data.size());
            EXPECT_EQ(pos, decoded_data[0]);
        }
    }
}

TEST_F(HexTest, encodeMap) {
    for (uint8_t i = 0; i < 16; ++i) {
        decoded_data.clear();
        decoded_data.push_back(i);
        EXPECT_EQ(encoding_chars[i], encodeHex(decoded_data)[1]);
    }
}

}
