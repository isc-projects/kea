// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/rdata.h>
#include <dns/rdata/generic/detail/char_string.h>

#include <gtest/gtest.h>

#include <string>
#include <vector>

using namespace isc::dns;
using namespace isc::dns::rdata;
using isc::dns::rdata::generic::detail::CharString;
using isc::dns::rdata::generic::detail::stringToCharString;
using isc::dns::rdata::generic::detail::charStringToString;
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
    EXPECT_THROW(stringToCharString(createStringRegion(std::string(256, 'a')),
                                    chstr),
                 CharStringTooLong);

    // input string ending with (non escaped) '\'
    chstr.clear();
    EXPECT_THROW(stringToCharString(createStringRegion("foo\\"), chstr),
                 InvalidRdataText);
}

TEST_F(CharStringTest, badDDD) {
    // Check various type of bad form of \DDD

    // Not a number
    EXPECT_THROW(stringToCharString(createStringRegion("\\1a2"), chstr),
                 InvalidRdataText);
    EXPECT_THROW(stringToCharString(createStringRegion("\\12a"), chstr),
                 InvalidRdataText);

    // Not in the range of uint8_t
    EXPECT_THROW(stringToCharString(createStringRegion("\\256"), chstr),
                 InvalidRdataText);

    // Short buffer
    EXPECT_THROW(stringToCharString(createStringRegion("\\42"), chstr),
                 InvalidRdataText);
}

TEST_F(CharStringTest, charStringToString) {
    const uint8_t double_quotes_buf[] = {
        sizeof("Test\"Test\"") - 1,
        'T', 'e', 's', 't', '"', 'T', 'e', 's', 't', '"'
    };
    const CharString double_quotes
        (double_quotes_buf, double_quotes_buf + sizeof(double_quotes_buf));
    EXPECT_EQ("Test\\\"Test\\\"",
              charStringToString(double_quotes));

    const uint8_t semicolon_buf[] = {
        sizeof("Test;Test") - 1,
        'T', 'e', 's', 't', ';', 'T', 'e', 's', 't'
    };
    const CharString semicolon
        (semicolon_buf, semicolon_buf + sizeof(semicolon_buf));
    EXPECT_EQ("Test\\;Test",
              charStringToString(semicolon));

    const uint8_t backslash_buf[] = {
        sizeof("Test\\Test") - 1,
        'T', 'e', 's', 't', '\\', 'T', 'e', 's', 't'
    };
    const CharString backslash
        (backslash_buf, backslash_buf + sizeof(backslash_buf));
    EXPECT_EQ("Test\\\\Test",
              charStringToString(backslash));

    const uint8_t before_x20_buf[] = {
        sizeof("Test\x1fTest") - 1,
        'T', 'e', 's', 't', 0x1f, 'T', 'e', 's', 't'
    };
    const CharString before_x20
        (before_x20_buf, before_x20_buf + sizeof(before_x20_buf));
    EXPECT_EQ("Test\\031Test",
              charStringToString(before_x20));

    const uint8_t from_x20_to_x7e_buf[] = {
        sizeof("Test ~ Test") - 1,
        'T', 'e', 's', 't', ' ', '~', ' ', 'T', 'e', 's', 't'
    };
    const CharString from_x20_to_x7e
        (from_x20_to_x7e_buf,
         from_x20_to_x7e_buf + sizeof(from_x20_to_x7e_buf));
    EXPECT_EQ("Test ~ Test",
              charStringToString(from_x20_to_x7e));

    const uint8_t after_0x7e_buf[] = {
        sizeof("Test\x7fTest") - 1,
        'T', 'e', 's', 't', 0x7f, 'T', 'e', 's', 't'
    };
    const CharString after_0x7e
        (after_0x7e_buf, after_0x7e_buf + sizeof(after_0x7e_buf));
    EXPECT_EQ("Test\\127Test",
              charStringToString(after_0x7e));
}

} // unnamed namespace
