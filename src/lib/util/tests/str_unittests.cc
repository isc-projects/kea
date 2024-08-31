// Copyright (C) 2011-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/gtest_utils.h>
#include <util/encode/encode.h>
#include <util/str.h>

#include <cstdint>
#include <exception>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::util::str;
using namespace std;

namespace {

/// @brief Fixture used to test StringSanitizer.
struct StringUtilTest : ::testing::Test {
    /// @brief Pass string through scrub and check the result.
    ///
    /// @param original The string to sanitize.
    /// @param char_set The regular expression string describing invalid characters.
    /// @param char_replacement - character(s) which replace invalid
    /// characters
    /// @param expected - expected sanitized string
    void checkScrub(const string& original,
                    const string& char_set,
                    const string& char_replacement,
                    const string& expected) {
        StringSanitizerPtr ss;
        string sanitized;

        try {
            ss.reset(new StringSanitizer(char_set, char_replacement));
        } catch (const exception& ex) {
            ADD_FAILURE() << "Could not construct sanitizer:" << ex.what();
            return;
        }

        try {
            sanitized = ss->scrub(original);
        } catch (const exception& ex) {
            ADD_FAILURE() << "Could not scrub string:" << ex.what();
            return;
        }

        EXPECT_EQ(sanitized, expected);
    }

    /// @brief Check that hex strings with colons can be decoded.
    ///
    /// @param input Input string to be decoded.
    /// @param reference The expected result.
    void checkColonSeparated(const string& input, const string& reference) {
        // Create a reference vector.
        vector<uint8_t> reference_vector;
        ASSERT_NO_THROW_LOG(decodeHex(reference, reference_vector));

        // Fill the output vector with some garbage to make sure that
        // the data is erased when a string is decoded successfully.
        vector<uint8_t> decoded(1, 10);
        ASSERT_NO_THROW_LOG(decodeColonSeparatedHexString(input, decoded));

        // Get the string representation of the decoded data for logging
        // purposes.
        string encoded;
        ASSERT_NO_THROW_LOG(encoded = encodeHex(decoded));

        // Check if the decoded data matches the reference.
        EXPECT_EQ(decoded, reference_vector) << "decoded data don't match the reference, input='"
                                             << input << "', reference='" << reference
                                             << "'"
                                                ", decoded='"
                                             << encoded << "'";
    }

    /// @brief Check that formatted hex strings can be decoded.
    ///
    /// @param input Input string to be decoded.
    /// @param reference The expected result.
    void checkFormatted(const string& input, const string& reference) {
        // Create a reference vector.
        vector<uint8_t> reference_vector;
        ASSERT_NO_THROW_LOG(decodeHex(reference, reference_vector));

        // Fill the output vector with some garbage to make sure that
        // the data is erased when a string is decoded successfully.
        vector<uint8_t> decoded(1, 10);
        ASSERT_NO_THROW_LOG(decodeFormattedHexString(input, decoded));

        // Get the string representation of the decoded data for logging
        // purposes.
        string encoded;
        ASSERT_NO_THROW_LOG(encoded = encodeHex(decoded));

        // Check if the decoded data matches the reference.
        EXPECT_EQ(decoded, reference_vector)
            << "decoded data don't match the reference, input='" << input << "', reference='"
            << reference << "', decoded='" << encoded << "'";
    }

    /// @brief Convenience function which calls quotedStringToBinary
    /// and converts returned vector back to string.
    ///
    /// @param s Input string.
    ///
    /// @return String holding a copy of a vector returned by the
    /// quotedStringToBinary.
    string checkQuoted(const string& s) {
        vector<uint8_t> vec = quotedStringToBinary(s);
        string s2(vec.begin(), vec.end());
        return (s2);
    }
};

// Check that leading and trailing space trimming works.
TEST_F(StringUtilTest, Trim) {
    // Empty and full string.
    EXPECT_EQ("", trim(""));
    EXPECT_EQ("abcxyz", trim("abcxyz"));

    // Trim right-most blanks
    EXPECT_EQ("ABC", trim("ABC   "));
    EXPECT_EQ("ABC", trim("ABC\t\t  \n\t"));

    // Left-most blank trimming
    EXPECT_EQ("XYZ", trim("  XYZ"));
    EXPECT_EQ("XYZ", trim("\t\t  \tXYZ"));

    // Right and left, with embedded spaces
    EXPECT_EQ("MN \t OP", trim("\t\tMN \t OP \t"));
}

// Check tokenization.
TEST_F(StringUtilTest, Tokens) {
    vector<string> result;

    // Default delimiters

    // Degenerate cases
    result = tokens("");  // Empty string
    EXPECT_EQ(0, result.size());

    result = tokens(" \n ");  // String is all delimiters
    EXPECT_EQ(0, result.size());

    result = tokens("abc");  // String has no delimiters
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(string("abc"), result[0]);

    // String containing leading and/or trailing delimiters, no embedded ones.
    result = tokens("\txyz");  // One leading delimiter
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(string("xyz"), result[0]);

    result = tokens("\t \nxyz");  // Multiple leading delimiters
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(string("xyz"), result[0]);

    result = tokens("xyz\n");  // One trailing delimiter
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(string("xyz"), result[0]);

    result = tokens("xyz  \t");  // Multiple trailing
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(string("xyz"), result[0]);

    result = tokens("\t xyz \n");  // Leading and trailing
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(string("xyz"), result[0]);

    // Embedded delimiters
    result = tokens("abc\ndef");  // 2 tokens, one separator
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(string("abc"), result[0]);
    EXPECT_EQ(string("def"), result[1]);

    result = tokens("abc\t\t\ndef");  // 2 tokens, 3 separators
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(string("abc"), result[0]);
    EXPECT_EQ(string("def"), result[1]);

    result = tokens("abc\n  \tdef\t\tghi");
    ASSERT_EQ(3, result.size());  // Multiple tokens, many delims
    EXPECT_EQ(string("abc"), result[0]);
    EXPECT_EQ(string("def"), result[1]);
    EXPECT_EQ(string("ghi"), result[2]);

    // Embedded and non-embedded delimiters

    result = tokens("\t\t  \nabc\n  \tdef\t\tghi   \n\n");
    ASSERT_EQ(3, result.size());  // Multiple tokens, many delims
    EXPECT_EQ(string("abc"), result[0]);
    EXPECT_EQ(string("def"), result[1]);
    EXPECT_EQ(string("ghi"), result[2]);

    // Non-default delimiter
    result = tokens("alpha/beta/ /gamma//delta/epsilon/", "/");
    ASSERT_EQ(6, result.size());
    EXPECT_EQ(string("alpha"), result[0]);
    EXPECT_EQ(string("beta"), result[1]);
    EXPECT_EQ(string(" "), result[2]);
    EXPECT_EQ(string("gamma"), result[3]);
    EXPECT_EQ(string("delta"), result[4]);
    EXPECT_EQ(string("epsilon"), result[5]);

    // Non-default delimiters (plural)
    result = tokens("+*--alpha*beta+ -gamma**delta+epsilon-+**", "*+-");
    ASSERT_EQ(6, result.size());
    EXPECT_EQ(string("alpha"), result[0]);
    EXPECT_EQ(string("beta"), result[1]);
    EXPECT_EQ(string(" "), result[2]);
    EXPECT_EQ(string("gamma"), result[3]);
    EXPECT_EQ(string("delta"), result[4]);
    EXPECT_EQ(string("epsilon"), result[5]);

    // Escaped delimiter
    result = tokens("foo\\,bar", ",", true);
    EXPECT_EQ(1, result.size());
    EXPECT_EQ(string("foo,bar"), result[0]);

    // Escaped escape
    result = tokens("foo\\\\,bar", ",", true);
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(string("foo\\"), result[0]);
    EXPECT_EQ(string("bar"), result[1]);

    // Double escapes
    result = tokens("foo\\\\\\\\,\\bar", ",", true);
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(string("foo\\\\"), result[0]);
    EXPECT_EQ(string("\\bar"), result[1]);

    // Escaped standard character
    result = tokens("fo\\o,bar", ",", true);
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(string("fo\\o"), result[0]);
    EXPECT_EQ(string("bar"), result[1]);

    // Escape at the end
    result = tokens("foo,bar\\", ",", true);
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(string("foo"), result[0]);
    EXPECT_EQ(string("bar\\"), result[1]);

    // Escape opening a token
    result = tokens("foo,\\,,bar", ",", true);
    ASSERT_EQ(3, result.size());
    EXPECT_EQ(string("foo"), result[0]);
    EXPECT_EQ(string(","), result[1]);
    EXPECT_EQ(string("bar"), result[2]);
}

// Check changing of case.
TEST_F(StringUtilTest, ChangeCase) {
    string mixed("abcDEFghiJKLmno123[]{=+--+]}");
    string upper("ABCDEFGHIJKLMNO123[]{=+--+]}");
    string lower("abcdefghijklmno123[]{=+--+]}");

    string test = mixed;
    lowercase(test);
    EXPECT_EQ(lower, test);

    test = mixed;
    uppercase(test);
    EXPECT_EQ(upper, test);
}

TEST_F(StringUtilTest, quotedStringToBinary) {
    // No opening or closing quote should result in empty string.
    EXPECT_TRUE(quotedStringToBinary("'").empty());
    EXPECT_TRUE(quotedStringToBinary("").empty());
    EXPECT_TRUE(quotedStringToBinary("  ").empty());
    EXPECT_TRUE(quotedStringToBinary("'circuit id").empty());
    EXPECT_TRUE(quotedStringToBinary("circuit id'").empty());

    // If there is only opening and closing quote, an empty
    // vector should be returned.
    EXPECT_TRUE(quotedStringToBinary("''").empty());

    // Both opening and ending quote is present.
    EXPECT_EQ("circuit id", checkQuoted("'circuit id'"));
    EXPECT_EQ("remote id", checkQuoted("  ' remote id'"));
    EXPECT_EQ("duid", checkQuoted("  ' duid'"));
    EXPECT_EQ("duid", checkQuoted("'duid    '  "));
    EXPECT_EQ("remote'id", checkQuoted("  ' remote'id  '"));
    EXPECT_EQ("remote id'", checkQuoted("'remote id''"));
    EXPECT_EQ("'remote id", checkQuoted("''remote id'"));

    // Multiple quotes.
    EXPECT_EQ("'", checkQuoted("'''"));
    EXPECT_EQ("''", checkQuoted("''''"));
}

TEST_F(StringUtilTest, decodeColonSeparatedHexString) {
    // Test valid strings.
    checkColonSeparated("A1:02:C3:d4:e5:F6", "A102C3D4E5F6");
    checkColonSeparated("A:02:3:d:E5:F6", "0A02030DE5F6");
    checkColonSeparated("A:B:C:D", "0A0B0C0D");
    checkColonSeparated("1", "01");
    checkColonSeparated("1e", "1E");
    checkColonSeparated("", "");

    // Test invalid strings.
    vector<uint8_t> decoded;
    // Whitespaces.
    EXPECT_THROW_MSG(decodeColonSeparatedHexString("   ", decoded), BadValue,
                     "invalid format of the decoded string '   '");
    // Whitespace before digits.
    EXPECT_THROW_MSG(decodeColonSeparatedHexString(" A1", decoded), BadValue,
                     "invalid format of the decoded string ' A1'");
    // Two consecutive colons.
    EXPECT_THROW_MSG(decodeColonSeparatedHexString("A::01", decoded), BadValue,
                     "two consecutive separators (':') specified in a decoded string 'A::01'");
    // Three consecutive colons.
    EXPECT_THROW_MSG(decodeColonSeparatedHexString("A:::01", decoded), BadValue,
                     "two consecutive separators (':') specified in a decoded string 'A:::01'");
    // Whitespace within a string.
    EXPECT_THROW_MSG(decodeColonSeparatedHexString("A :01", decoded), BadValue,
                     "' ' is not a valid hexadecimal digit in decoded string 'A :01'");
    // Terminating colon.
    EXPECT_THROW_MSG(decodeColonSeparatedHexString("0A:01:", decoded), BadValue,
                     "two consecutive separators (':') specified in a decoded string '0A:01:'");
    // Opening colon.
    EXPECT_THROW_MSG(decodeColonSeparatedHexString(":0A:01", decoded), BadValue,
                     "two consecutive separators (':') specified in a decoded string ':0A:01'");
    // Three digits before the colon.
    EXPECT_THROW_MSG(decodeColonSeparatedHexString("0A1:B1", decoded), BadValue,
                     "invalid format of the decoded string '0A1:B1'");
}

TEST_F(StringUtilTest, decodeFormattedHexString) {
    // Colon separated.
    checkFormatted("1:A7:B5:4:23", "01A7B50423");
    // Space separated.
    checkFormatted("1 A7 B5 4 23", "01A7B50423");
    // No colons, even number of digits.
    checkFormatted("17a534", "17A534");
    // Odd number of digits.
    checkFormatted("A3A6f78", "0A3A6F78");
    // '0x' prefix.
    checkFormatted("0xA3A6f78", "0A3A6F78");
    // '0x' prefix with a special value of 0.
    checkFormatted("0x0", "00");
    // Empty string.
    checkFormatted("", "");

    vector<uint8_t> decoded;
    // Dangling colon.
    EXPECT_THROW_MSG(decodeFormattedHexString("0a:", decoded), BadValue,
                     "two consecutive separators (':') specified in a decoded string '0a:'");
    // Dangling space.
    EXPECT_THROW_MSG(decodeFormattedHexString("0a ", decoded), BadValue,
                     "two consecutive separators (' ') specified in a decoded string '0a '");
    // '0x' prefix and spaces.
    EXPECT_THROW_MSG(decodeFormattedHexString("0x01 02", decoded), BadValue,
                     "invalid format of the decoded string '0x01 02'");
    // '0x' prefix and colons.
    EXPECT_THROW_MSG(decodeFormattedHexString("0x01:02", decoded), BadValue,
                     "invalid format of the decoded string '0x01:02'");
    // colon and spaces mixed
    EXPECT_THROW_MSG(decodeFormattedHexString("01:02 03", decoded), BadValue,
                     "invalid format of the decoded string '01:02 03'");
    // Missing colon.
    EXPECT_THROW_MSG(decodeFormattedHexString("01:0203", decoded), BadValue,
                     "invalid format of the decoded string '01:0203'");
    // Missing space.
    EXPECT_THROW_MSG(decodeFormattedHexString("01 0203", decoded), BadValue,
                     "invalid format of the decoded string '01 0203'");
    // Invalid prefix.
    EXPECT_THROW_MSG(decodeFormattedHexString("x0102", decoded), BadValue,
                     "'x0102' is not a valid string of hexadecimal digits");
    // Invalid prefix again.
    EXPECT_THROW_MSG(decodeFormattedHexString("1x0102", decoded), BadValue,
                     "'1x0102' is not a valid string of hexadecimal digits");
}

// Verifies StringSantizer class
TEST_F(StringUtilTest, stringSanitizer) {
    // Bad regular expression should throw.
    StringSanitizerPtr ss;

    try {
        ss.reset(new StringSanitizer("[bogus-regex", ""));
    } catch (BadValue const& ex) {
        unordered_set<string> expected{
            // BSD
            "invalid regex: '[bogus-regex', The expression contained mismatched [ and ].",
            // Linux
            "invalid regex: '[bogus-regex', Invalid range in bracket expression.",
        };
        if (!expected.count(ex.what())) {
            FAIL() << "unexpected BadValue exception message: " << ex.what();
        }
    } catch (exception const& ex) {
        FAIL() << "unexpected exception: " << ex.what();
    }

    string good_data(StringSanitizer::MAX_DATA_SIZE, '0');
    string bad_data(StringSanitizer::MAX_DATA_SIZE + 1, '0');

    ASSERT_NO_THROW_LOG(ss.reset(new StringSanitizer(good_data, good_data)));

    ASSERT_THROW_MSG(ss.reset(new StringSanitizer(bad_data, "")), BadValue,
                     "char set size: '4097' exceeds max size: '4096'");
    ASSERT_THROW_MSG(ss.reset(new StringSanitizer("", bad_data)), BadValue,
                     "char replacement size: '4097' exceeds max size: '4096'");

    // List of invalid chars should work: (b,c,2 are invalid)
    checkScrub("abc.123", "[b-c2]", "*", "a**.1*3");
    // Inverted list of valid chars should work: (b,c,2 are valid)
    checkScrub("abc.123", "[^b-c2]", "*", "*bc**2*");

    // A string of all valid chars should return an identical string.
    checkScrub("-_A--B__Cabc34567_-", "[^A-Ca-c3-7_-]", "x", "-_A--B__Cabc34567_-");

    // Replacing with a character should work.
    checkScrub("A[b]c\12JoE3-_x!B$Y#e", "[^A-Za-z0-9_]", "*", "A*b*c*JoE3*_x*B*Y*e");

    // Removing (i.e.replacing with an "empty" string) should work.
    checkScrub("A[b]c\12JoE3-_x!B$Y#e", "[^A-Za-z0-9_]", "", "AbcJoE3_xBYe");

    // More than one non-matching in a row should work.
    checkScrub("%%A%%B%%C%%", "[^A-Za-z0-9_]", "x", "xxAxxBxxCxx");

    // Removing more than one non-matching in a row should work.
    checkScrub("%%A%%B%%C%%", "[^A-Za-z0-9_]", "", "ABC");

    // Replacing with a string should work.
    checkScrub("%%A%%B%%C%%", "[^A-Za-z0-9_]", "xyz", "xyzxyzAxyzxyzBxyzxyzCxyzxyz");

    // Dots as valid chars work.
    checkScrub("abc.123", "[^A-Za-z0-9_.]", "*", "abc.123");

    string withNulls("\000ab\000c.12\0003", 10);
    checkScrub(withNulls, "[^A-Za-z0-9_.]", "*", "*ab*c.12*3");
}

// Verifies templated buffer iterator seekTrimmed() function
TEST_F(StringUtilTest, seekTrimmed) {
    // Empty buffer should be fine.
    vector<uint8_t> buffer;
    auto begin = buffer.end();
    auto end = buffer.end();
    ASSERT_NO_THROW_LOG(end = seekTrimmed(begin, end, 0));
    EXPECT_EQ(0, distance(begin, end));

    // Buffer of only trim values, should be fine.
    buffer = {1, 1};
    begin = buffer.begin();
    end = buffer.end();
    ASSERT_NO_THROW_LOG(end = seekTrimmed(begin, end, 1));
    EXPECT_EQ(0, distance(begin, end));

    // One trailing null should trim off.
    buffer = {'o', 'n', 'e', 0};
    begin = buffer.begin();
    end = buffer.end();
    ASSERT_NO_THROW_LOG(end = seekTrimmed(begin, end, 0));
    EXPECT_EQ(3, distance(begin, end));

    // More than one trailing null should trim off.
    buffer = {'t', 'h', 'r', 'e', 'e', 0, 0, 0};
    begin = buffer.begin();
    end = buffer.end();
    ASSERT_NO_THROW_LOG(end = seekTrimmed(begin, end, 0));
    EXPECT_EQ(5, distance(begin, end));

    // Embedded null should be left in place.
    buffer = {'e', 'm', 0, 'b', 'e', 'd'};
    begin = buffer.begin();
    end = buffer.end();
    ASSERT_NO_THROW_LOG(end = seekTrimmed(begin, end, 0));
    EXPECT_EQ(6, distance(begin, end));

    // Leading null should be left in place.
    buffer = {0, 'l', 'e', 'a', 'd', 'i', 'n', 'g'};
    begin = buffer.begin();
    end = buffer.end();
    ASSERT_NO_THROW_LOG(end = seekTrimmed(begin, end, 0));
    EXPECT_EQ(8, distance(begin, end));
}

// Verifies isPrintable predicate on strings.
TEST_F(StringUtilTest, stringIsPrintable) {
    string content;

    // Empty is printable.
    EXPECT_TRUE(isPrintable(content));

    // Check Abcd.
    content = "Abcd";
    EXPECT_TRUE(isPrintable(content));

    // Add a control character (not printable).
    content += "\a";
    EXPECT_FALSE(isPrintable(content));
}

// Verifies isPrintable predicate on byte vectors.
TEST_F(StringUtilTest, vectorIsPrintable) {
    vector<uint8_t> content;

    // Empty is printable.
    EXPECT_TRUE(isPrintable(content));

    // Check Abcd.
    content = {0x41, 0x62, 0x63, 0x64};
    EXPECT_TRUE(isPrintable(content));

    // Add a control character (not printable).
    content.push_back('\a');
    EXPECT_FALSE(isPrintable(content));
}

}  // namespace
