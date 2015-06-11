// Copyright (C) 2014, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <util/unittests/wiredata.h>

#include <dns/exceptions.h>
#include <dns/rdata.h>
#include <dns/rdata/generic/detail/char_string.h>
#include <util/buffer.h>

#include <util/unittests/test_exceptions.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

using namespace isc::dns;
using namespace isc::dns::rdata;
using isc::dns::rdata::generic::detail::CharStringData;
using isc::dns::rdata::generic::detail::stringToCharStringData;
using isc::dns::rdata::generic::detail::charStringDataToString;
using isc::dns::rdata::generic::detail::compareCharStringDatas;
using isc::util::unittests::matchWireData;

namespace {
const uint8_t test_charstr[] = {
    'T', 'e', 's', 't', ' ', 'S', 't', 'r', 'i', 'n', 'g'
};

class CharStringDataTest : public ::testing::Test {
protected:
    CharStringDataTest() :
        // char-string representation for test data using two types of escape
        // ('r' = 114)
        test_str("Test\\ St\\114ing")
    {
        str_region.beg = &test_str[0];
        str_region.len = test_str.size();
    }
    CharStringData chstr;           // place holder
    const std::string test_str;
    MasterToken::StringRegion str_region;
};

MasterToken::StringRegion
createStringRegion(const std::string& str) {
    MasterToken::StringRegion region;
    region.beg = &str[0]; // note std ensures this works even if str is empty
    region.len = str.size();
    return (region);
}

TEST_F(CharStringDataTest, normalConversion) {
    uint8_t tmp[3];             // placeholder for expected sequence

    stringToCharStringData(str_region, chstr);
    matchWireData(test_charstr, sizeof(test_charstr), &chstr[0], chstr.size());

    // Empty string
    chstr.clear();
    stringToCharStringData(createStringRegion(""), chstr);
    EXPECT_TRUE(chstr.empty());

    // Possible largest char string
    chstr.clear();
    std::string long_str(255, 'x');
    stringToCharStringData(createStringRegion(long_str), chstr);
    std::vector<uint8_t> expected;
    expected.insert(expected.end(), long_str.begin(), long_str.end());
    matchWireData(&expected[0], expected.size(), &chstr[0], chstr.size());

    // Escaped '\'
    chstr.clear();
    tmp[0] = '\\';
    stringToCharStringData(createStringRegion("\\\\"), chstr);
    matchWireData(tmp, 1, &chstr[0], chstr.size());

    // Boundary values for \DDD
    chstr.clear();
    tmp[0] = 0;
    stringToCharStringData(createStringRegion("\\000"), chstr);
    matchWireData(tmp, 1, &chstr[0], chstr.size());

    chstr.clear();
    stringToCharStringData(createStringRegion("\\255"), chstr);
    tmp[0] = 255;
    matchWireData(tmp, 1, &chstr[0], chstr.size());

    // Another digit follows DDD; it shouldn't cause confusion
    chstr.clear();
    stringToCharStringData(createStringRegion("\\2550"), chstr);
    tmp[1] = '0';
    matchWireData(tmp, 2, &chstr[0], chstr.size());
}

TEST_F(CharStringDataTest, badConversion) {
    // input string ending with (non escaped) '\'
    chstr.clear();
    EXPECT_THROW_WITH(stringToCharStringData(createStringRegion("foo\\"),
                                             chstr),
                      InvalidRdataText, "character-string ends with '\\'");
}

TEST_F(CharStringDataTest, badDDD) {
    // Check various type of bad form of \DDD

    // Not a number
    EXPECT_THROW_WITH(stringToCharStringData(createStringRegion("\\1a2"),
                                             chstr),
                      InvalidRdataText,
                      "Invalid form for escaped digits: 1a2");
    EXPECT_THROW_WITH(stringToCharStringData(createStringRegion("\\12a"),
                                             chstr),
                      InvalidRdataText,
                      "Invalid form for escaped digits: 12a");

    // Not in the range of uint8_t
    EXPECT_THROW_WITH(stringToCharStringData(createStringRegion("\\256"),
                                             chstr),
                      InvalidRdataText, "Escaped digits too large: 256");

    // Short buffer
    EXPECT_THROW_WITH(stringToCharStringData(createStringRegion("\\42"),
                                             chstr),
                      InvalidRdataText, "Escaped digits too short");
}

const struct TestData {
    const char *data;
    const char *expected;
} conversion_data[] = {
    {"Test\"Test", "Test\\\"Test"},
    {"Test;Test", "Test\\;Test"},
    {"Test\\Test", "Test\\\\Test"},
    {"Test\x1fTest", "Test\\031Test"},
    {"Test ~ Test", "Test ~ Test"},
    {"Test\x7fTest", "Test\\127Test"},
    {NULL, NULL}
};

TEST_F(CharStringDataTest, charStringDataToString) {
    for (const TestData* cur = conversion_data; cur->data != NULL; ++cur) {
        uint8_t idata[32];
        size_t length = std::strlen(cur->data);
        ASSERT_LT(length, sizeof(idata));
        std::memcpy(idata, cur->data, length);
        const CharStringData test_data(idata, idata + length);
        EXPECT_EQ(cur->expected, charStringDataToString(test_data));
    }
}

TEST_F(CharStringDataTest, compareCharStringData) {
    CharStringData charstr;
    CharStringData charstr2;
    CharStringData charstr_small1;
    CharStringData charstr_small2;
    CharStringData charstr_large1;
    CharStringData charstr_large2;
    CharStringData charstr_empty;

    stringToCharStringData(createStringRegion("test string"), charstr);
    stringToCharStringData(createStringRegion("test string"), charstr2);
    stringToCharStringData(createStringRegion("test strin"), charstr_small1);
    stringToCharStringData(createStringRegion("test strina"), charstr_small2);
    stringToCharStringData(createStringRegion("test stringa"), charstr_large1);
    stringToCharStringData(createStringRegion("test strinz"), charstr_large2);

    EXPECT_EQ(0, compareCharStringDatas(charstr, charstr2));
    EXPECT_EQ(0, compareCharStringDatas(charstr2, charstr));
    EXPECT_EQ(1, compareCharStringDatas(charstr, charstr_small1));
    EXPECT_EQ(1, compareCharStringDatas(charstr, charstr_small2));
    EXPECT_EQ(-1, compareCharStringDatas(charstr, charstr_large1));
    EXPECT_EQ(-1, compareCharStringDatas(charstr, charstr_large2));
    EXPECT_EQ(-1, compareCharStringDatas(charstr_small1, charstr));
    EXPECT_EQ(-1, compareCharStringDatas(charstr_small2, charstr));
    EXPECT_EQ(1, compareCharStringDatas(charstr_large1, charstr));
    EXPECT_EQ(1, compareCharStringDatas(charstr_large2, charstr));

    EXPECT_EQ(-1, compareCharStringDatas(charstr_empty, charstr));
    EXPECT_EQ(1, compareCharStringDatas(charstr, charstr_empty));
    EXPECT_EQ(0, compareCharStringDatas(charstr_empty, charstr_empty));
}

} // unnamed namespace
