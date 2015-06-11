// Copyright (C) 2012, 2015  Internet Systems Consortium, Inc. ("ISC")
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
using isc::dns::rdata::generic::detail::CharString;
using isc::dns::rdata::generic::detail::bufferToCharString;
using isc::dns::rdata::generic::detail::stringToCharString;
using isc::dns::rdata::generic::detail::charStringToString;
using isc::dns::rdata::generic::detail::compareCharStrings;
using isc::util::unittests::matchWireData;

namespace {
const uint8_t test_charstr[] = {
    sizeof("Test String") - 1,
    'T', 'e', 's', 't', ' ', 'S', 't', 'r', 'i', 'n', 'g'
};

class CharStringTest : public ::testing::Test {
protected:
    CharStringTest() :
        // char-string representation for test data using two types of escape
        // ('r' = 114)
        test_str("Test\\ St\\114ing")
    {
        str_region.beg = &test_str[0];
        str_region.len = test_str.size();
    }
    CharString chstr;           // place holder
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

TEST_F(CharStringTest, normalConversion) {
    uint8_t tmp[3];             // placeholder for expected sequence

    stringToCharString(str_region, chstr);
    matchWireData(test_charstr, sizeof(test_charstr), &chstr[0], chstr.size());

    // Empty string
    chstr.clear();
    stringToCharString(createStringRegion(""), chstr);
    tmp[0] = 0;
    matchWireData(tmp, 1, &chstr[0], chstr.size());

    // Possible largest char string
    chstr.clear();
    std::string long_str(255, 'x');
    stringToCharString(createStringRegion(long_str), chstr);
    std::vector<uint8_t> expected;
    expected.push_back(255);    // len of char string
    expected.insert(expected.end(), long_str.begin(), long_str.end());
    matchWireData(&expected[0], expected.size(), &chstr[0], chstr.size());

    // Same data as the previous case, but the original string is longer than
    // the max; this shouldn't be rejected
    chstr.clear();
    long_str.at(254) = '\\';    // replace the last 'x' with '\'
    long_str.append("120");     // 'x' = 120
    stringToCharString(createStringRegion(long_str), chstr);
    matchWireData(&expected[0], expected.size(), &chstr[0], chstr.size());

    // Escaped '\'
    chstr.clear();
    tmp[0] = 1;
    tmp[1] = '\\';
    stringToCharString(createStringRegion("\\\\"), chstr);
    matchWireData(tmp, 2, &chstr[0], chstr.size());

    // Boundary values for \DDD
    chstr.clear();
    tmp[0] = 1;
    tmp[1] = 0;
    stringToCharString(createStringRegion("\\000"), chstr);
    matchWireData(tmp, 2, &chstr[0], chstr.size());

    chstr.clear();
    stringToCharString(createStringRegion("\\255"), chstr);
    tmp[0] = 1;
    tmp[1] = 255;
    matchWireData(tmp, 2, &chstr[0], chstr.size());

    // Another digit follows DDD; it shouldn't cause confusion
    chstr.clear();
    stringToCharString(createStringRegion("\\2550"), chstr);
    tmp[0] = 2;                 // string len is now 2
    tmp[2] = '0';
    matchWireData(tmp, 3, &chstr[0], chstr.size());
}

TEST_F(CharStringTest, badConversion) {
    // string cannot exceed 255 bytes
    EXPECT_THROW_WITH(stringToCharString(createStringRegion(std::string(256,
                                                                        'a')),
                                         chstr),
                      CharStringTooLong,
                      "character-string is too long: 256(+1) characters");

    // input string ending with (non escaped) '\'
    chstr.clear();
    EXPECT_THROW_WITH(stringToCharString(createStringRegion("foo\\"),
                                         chstr),
                      InvalidRdataText, "character-string ends with '\\'");
}

TEST_F(CharStringTest, badDDD) {
    // Check various type of bad form of \DDD

    // Not a number
    EXPECT_THROW_WITH(stringToCharString(createStringRegion("\\1a2"),
                                         chstr),
                      InvalidRdataText,
                      "Invalid form for escaped digits: 1a2");
    EXPECT_THROW_WITH(stringToCharString(createStringRegion("\\12a"), chstr),
                      InvalidRdataText,
                      "Invalid form for escaped digits: 12a");

    // Not in the range of uint8_t
    EXPECT_THROW_WITH(stringToCharString(createStringRegion("\\256"), chstr),
                      InvalidRdataText,  "Escaped digits too large: 256");

    // Short buffer
    EXPECT_THROW_WITH(stringToCharString(createStringRegion("\\42"), chstr),
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

TEST_F(CharStringTest, charStringToString) {
    for (const TestData* cur = conversion_data; cur->data != NULL; ++cur) {
        uint8_t idata[32];
        size_t length = std::strlen(cur->data);
        // length (1 byte) + string (length bytes)
        assert(sizeof(idata) > length);
        idata[0] = static_cast<uint8_t>(length);
        std::memcpy(idata + 1, cur->data, length);
        const CharString test_data(idata, idata + length + 1);
        EXPECT_EQ(cur->expected, charStringToString(test_data));
    }
}

TEST_F(CharStringTest, bufferToCharString) {
    const size_t chstr_size = sizeof(test_charstr);
    isc::util::InputBuffer buf(test_charstr, chstr_size);
    size_t read = bufferToCharString(buf, chstr_size, chstr);

    EXPECT_EQ(chstr_size, read);
    EXPECT_EQ("Test String", charStringToString(chstr));
}

TEST_F(CharStringTest, bufferToCharString_bad) {
    const size_t chstr_size = sizeof(test_charstr);
    isc::util::InputBuffer buf(test_charstr, chstr_size);
    // Set valid data in both so we can make sure the charstr is not
    // modified
    bufferToCharString(buf, chstr_size, chstr);
    ASSERT_EQ("Test String", charStringToString(chstr));

    // Should be at end of buffer now, so it should fail
    EXPECT_THROW_WITH(bufferToCharString(buf, chstr_size - 1, chstr),
                      DNSMessageFORMERR,
                      "insufficient data to read character-string length");
    EXPECT_EQ("Test String", charStringToString(chstr));

    // reset and try to read with too low rdata_len
    buf.setPosition(0);
    EXPECT_THROW_WITH(bufferToCharString(buf, chstr_size - 1, chstr),
                      DNSMessageFORMERR,
                      "character string length is too large: "
                      << chstr_size - 1);
    EXPECT_EQ("Test String", charStringToString(chstr));

    // set internal charstring len too high
    const uint8_t test_charstr_err[] = {
        sizeof("Test String") + 1,
        'T', 'e', 's', 't', ' ', 'S', 't', 'r', 'i', 'n', 'g'
    };
    buf = isc::util::InputBuffer(test_charstr_err, sizeof(test_charstr_err));
    EXPECT_THROW_WITH(bufferToCharString(buf, chstr_size, chstr),
                      DNSMessageFORMERR,
                      "character string length is too large: 13");
    EXPECT_EQ("Test String", charStringToString(chstr));

}



TEST_F(CharStringTest, compareCharString) {
    CharString charstr;
    CharString charstr2;
    CharString charstr_small1;
    CharString charstr_small2;
    CharString charstr_large1;
    CharString charstr_large2;
    CharString charstr_empty;

    stringToCharString(createStringRegion("test string"), charstr);
    stringToCharString(createStringRegion("test string"), charstr2);
    stringToCharString(createStringRegion("test strin"), charstr_small1);
    stringToCharString(createStringRegion("test strina"), charstr_small2);
    stringToCharString(createStringRegion("test stringa"), charstr_large1);
    stringToCharString(createStringRegion("test strinz"), charstr_large2);

    EXPECT_EQ(0, compareCharStrings(charstr, charstr2));
    EXPECT_EQ(0, compareCharStrings(charstr2, charstr));
    EXPECT_EQ(1, compareCharStrings(charstr, charstr_small1));
    EXPECT_EQ(1, compareCharStrings(charstr, charstr_small2));
    EXPECT_EQ(-1, compareCharStrings(charstr, charstr_large1));
    EXPECT_EQ(-1, compareCharStrings(charstr, charstr_large2));
    EXPECT_EQ(-1, compareCharStrings(charstr_small1, charstr));
    EXPECT_EQ(-1, compareCharStrings(charstr_small2, charstr));
    EXPECT_EQ(1, compareCharStrings(charstr_large1, charstr));
    EXPECT_EQ(1, compareCharStrings(charstr_large2, charstr));

    EXPECT_EQ(-1, compareCharStrings(charstr_empty, charstr));
    EXPECT_EQ(1, compareCharStrings(charstr, charstr_empty));
    EXPECT_EQ(0, compareCharStrings(charstr_empty, charstr_empty));
}

} // unnamed namespace
