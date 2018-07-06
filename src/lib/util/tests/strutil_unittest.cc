// Copyright (C) 2011-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/strutil.h>
#include <util/encode/hex.h>

#include <gtest/gtest.h>

#include <stdint.h>
#include <string>

using namespace isc;
using namespace isc::util;
using namespace isc::util::str;
using namespace std;

namespace {

// Check for slash replacement

TEST(StringUtilTest, Slash) {

    string instring = "";
    isc::util::str::normalizeSlash(instring);
    EXPECT_EQ("", instring);

    instring = "C:\\A\\B\\C.D";
    isc::util::str::normalizeSlash(instring);
    EXPECT_EQ("C:/A/B/C.D", instring);

    instring = "// \\ //";
    isc::util::str::normalizeSlash(instring);
    EXPECT_EQ("// / //", instring);
}

// Check that leading and trailing space trimming works

TEST(StringUtilTest, Trim) {

    // Empty and full string.
    EXPECT_EQ("", isc::util::str::trim(""));
    EXPECT_EQ("abcxyz", isc::util::str::trim("abcxyz"));

    // Trim right-most blanks
    EXPECT_EQ("ABC", isc::util::str::trim("ABC   "));
    EXPECT_EQ("ABC", isc::util::str::trim("ABC\t\t  \n\t"));

    // Left-most blank trimming
    EXPECT_EQ("XYZ", isc::util::str::trim("  XYZ"));
    EXPECT_EQ("XYZ", isc::util::str::trim("\t\t  \tXYZ"));

    // Right and left, with embedded spaces
    EXPECT_EQ("MN \t OP", isc::util::str::trim("\t\tMN \t OP \t"));
}

// Check tokenization.  Note that ASSERT_EQ is used to check the size of the
// returned vector; if not as expected, the following references may be invalid
// so should not be used.

TEST(StringUtilTest, Tokens) {
    vector<string>  result;

    // Default delimiters

    // Degenerate cases
    result = isc::util::str::tokens("");          // Empty string
    EXPECT_EQ(0, result.size());

    result = isc::util::str::tokens(" \n ");      // String is all delimiters
    EXPECT_EQ(0, result.size());

    result = isc::util::str::tokens("abc");       // String has no delimiters
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(string("abc"), result[0]);

    // String containing leading and/or trailing delimiters, no embedded ones.
    result = isc::util::str::tokens("\txyz");     // One leading delimiter
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(string("xyz"), result[0]);

    result = isc::util::str::tokens("\t \nxyz");  // Multiple leading delimiters
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(string("xyz"), result[0]);

    result = isc::util::str::tokens("xyz\n");     // One trailing delimiter
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(string("xyz"), result[0]);

    result = isc::util::str::tokens("xyz  \t");   // Multiple trailing
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(string("xyz"), result[0]);

    result = isc::util::str::tokens("\t xyz \n"); // Leading and trailing
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(string("xyz"), result[0]);

    // Embedded delimiters
    result = isc::util::str::tokens("abc\ndef");  // 2 tokens, one separator
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(string("abc"), result[0]);
    EXPECT_EQ(string("def"), result[1]);

    result = isc::util::str::tokens("abc\t\t\ndef");  // 2 tokens, 3 separators
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(string("abc"), result[0]);
    EXPECT_EQ(string("def"), result[1]);

    result = isc::util::str::tokens("abc\n  \tdef\t\tghi");
    ASSERT_EQ(3, result.size());                // Multiple tokens, many delims
    EXPECT_EQ(string("abc"), result[0]);
    EXPECT_EQ(string("def"), result[1]);
    EXPECT_EQ(string("ghi"), result[2]);

    // Embedded and non-embedded delimiters

    result = isc::util::str::tokens("\t\t  \nabc\n  \tdef\t\tghi   \n\n");
    ASSERT_EQ(3, result.size());                // Multiple tokens, many delims
    EXPECT_EQ(string("abc"), result[0]);
    EXPECT_EQ(string("def"), result[1]);
    EXPECT_EQ(string("ghi"), result[2]);

    // Non-default delimiter
    result = isc::util::str::tokens("alpha/beta/ /gamma//delta/epsilon/", "/");
    ASSERT_EQ(6, result.size());
    EXPECT_EQ(string("alpha"), result[0]);
    EXPECT_EQ(string("beta"), result[1]);
    EXPECT_EQ(string(" "), result[2]);
    EXPECT_EQ(string("gamma"), result[3]);
    EXPECT_EQ(string("delta"), result[4]);
    EXPECT_EQ(string("epsilon"), result[5]);

    // Non-default delimiters (plural)
    result = isc::util::str::tokens("+*--alpha*beta+ -gamma**delta+epsilon-+**",
        "*+-");
    ASSERT_EQ(6, result.size());
    EXPECT_EQ(string("alpha"), result[0]);
    EXPECT_EQ(string("beta"), result[1]);
    EXPECT_EQ(string(" "), result[2]);
    EXPECT_EQ(string("gamma"), result[3]);
    EXPECT_EQ(string("delta"), result[4]);
    EXPECT_EQ(string("epsilon"), result[5]);

    // Escaped delimiter
    result = isc::util::str::tokens("foo\\,bar", ",", true);
    EXPECT_EQ(1, result.size());
    EXPECT_EQ(string("foo,bar"), result[0]);

    // Escaped escape
    result = isc::util::str::tokens("foo\\\\,bar", ",", true);
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(string("foo\\"), result[0]);
    EXPECT_EQ(string("bar"), result[1]);

    // Double escapes
    result = isc::util::str::tokens("foo\\\\\\\\,\\bar", ",", true);
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(string("foo\\\\"), result[0]);
    EXPECT_EQ(string("\\bar"), result[1]);

    // Escaped standard character
    result = isc::util::str::tokens("fo\\o,bar", ",", true);
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(string("fo\\o"), result[0]);
    EXPECT_EQ(string("bar"), result[1]);

    // Escape at the end
    result = isc::util::str::tokens("foo,bar\\", ",", true);
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(string("foo"), result[0]);
    EXPECT_EQ(string("bar\\"), result[1]);

    // Escape opening a token
    result = isc::util::str::tokens("foo,\\,,bar", ",", true);
    ASSERT_EQ(3, result.size());
    EXPECT_EQ(string("foo"), result[0]);
    EXPECT_EQ(string(","), result[1]);
    EXPECT_EQ(string("bar"), result[2]);
}

// Changing case

TEST(StringUtilTest, ChangeCase) {
    string mixed("abcDEFghiJKLmno123[]{=+--+]}");
    string upper("ABCDEFGHIJKLMNO123[]{=+--+]}");
    string lower("abcdefghijklmno123[]{=+--+]}");

    string test = mixed;
    isc::util::str::lowercase(test);
    EXPECT_EQ(lower, test);

    test = mixed;
    isc::util::str::uppercase(test);
    EXPECT_EQ(upper, test);
}

// Formatting

TEST(StringUtilTest, Formatting) {

    vector<string> args;
    args.push_back("arg1");
    args.push_back("arg2");
    args.push_back("arg3");

    string format1 = "This is a string with no tokens";
    EXPECT_EQ(format1, isc::util::str::format(format1, args));

    string format2 = "";    // Empty string
    EXPECT_EQ(format2, isc::util::str::format(format2, args));

    string format3 = "   ";    // Empty string
    EXPECT_EQ(format3, isc::util::str::format(format3, args));

    string format4 = "String with %d non-string tokens %lf";
    EXPECT_EQ(format4, isc::util::str::format(format4, args));

    string format5 = "String with %s correct %s number of tokens %s";
    string result5 = "String with arg1 correct arg2 number of tokens arg3";
    EXPECT_EQ(result5, isc::util::str::format(format5, args));

    string format6 = "String with %s too %s few tokens";
    string result6 = "String with arg1 too arg2 few tokens";
    EXPECT_EQ(result6, isc::util::str::format(format6, args));

    string format7 = "String with %s too %s many %s tokens %s !";
    string result7 = "String with arg1 too arg2 many arg3 tokens %s !";
    EXPECT_EQ(result7, isc::util::str::format(format7, args));

    string format8 = "String with embedded%s%s%stokens";
    string result8 = "String with embeddedarg1arg2arg3tokens";
    EXPECT_EQ(result8, isc::util::str::format(format8, args));

    // Handle an empty vector
    args.clear();
    string format9 = "%s %s";
    EXPECT_EQ(format9, isc::util::str::format(format9, args));
}

TEST(StringUtilTest, getToken) {
    string s("a b c");
    istringstream ss(s);
    EXPECT_EQ("a", isc::util::str::getToken(ss));
    EXPECT_EQ("b", isc::util::str::getToken(ss));
    EXPECT_EQ("c", isc::util::str::getToken(ss));
    EXPECT_THROW(isc::util::str::getToken(ss), isc::util::str::StringTokenError);
}

int32_t tokenToNumCall_32_16(const string& token) {
    return isc::util::str::tokenToNum<int32_t, 16>(token);
}

int16_t tokenToNumCall_16_8(const string& token) {
    return isc::util::str::tokenToNum<int16_t, 8>(token);
}

TEST(StringUtilTest, tokenToNum) {
    uint32_t num32 = tokenToNumCall_32_16("0");
    EXPECT_EQ(0, num32);
    num32 = tokenToNumCall_32_16("123");
    EXPECT_EQ(123, num32);
    num32 = tokenToNumCall_32_16("65535");
    EXPECT_EQ(65535, num32);

    EXPECT_THROW(tokenToNumCall_32_16(""),
                 isc::util::str::StringTokenError);
    EXPECT_THROW(tokenToNumCall_32_16("a"),
                 isc::util::str::StringTokenError);
    EXPECT_THROW(tokenToNumCall_32_16("-1"),
                 isc::util::str::StringTokenError);
    EXPECT_THROW(tokenToNumCall_32_16("65536"),
                 isc::util::str::StringTokenError);
    EXPECT_THROW(tokenToNumCall_32_16("1234567890"),
                 isc::util::str::StringTokenError);
    EXPECT_THROW(tokenToNumCall_32_16("-1234567890"),
                 isc::util::str::StringTokenError);

    uint16_t num16 = tokenToNumCall_16_8("123");
    EXPECT_EQ(123, num16);
    num16 = tokenToNumCall_16_8("0");
    EXPECT_EQ(0, num16);
    num16 = tokenToNumCall_16_8("255");
    EXPECT_EQ(255, num16);

    EXPECT_THROW(tokenToNumCall_16_8(""),
                 isc::util::str::StringTokenError);
    EXPECT_THROW(tokenToNumCall_16_8("a"),
                 isc::util::str::StringTokenError);
    EXPECT_THROW(tokenToNumCall_16_8("-1"),
                 isc::util::str::StringTokenError);
    EXPECT_THROW(tokenToNumCall_16_8("256"),
                 isc::util::str::StringTokenError);
    EXPECT_THROW(tokenToNumCall_16_8("1234567890"),
                 isc::util::str::StringTokenError);
    EXPECT_THROW(tokenToNumCall_16_8("-1234567890"),
                 isc::util::str::StringTokenError);

}

/// @brief Convenience function which calls quotedStringToBinary
/// and converts returned vector back to string.
///
/// @param s Input string.
/// @return String holding a copy of a vector returned by the
/// quotedStringToBinary.
std::string testQuoted(const std::string& s) {
    std::vector<uint8_t> vec = str::quotedStringToBinary(s);
    std::string s2(vec.begin(), vec.end());
    return (s2);
}

TEST(StringUtilTest, quotedStringToBinary) {
    // No opening or closing quote should result in empty string.
    EXPECT_TRUE(str::quotedStringToBinary("'").empty());
    EXPECT_TRUE(str::quotedStringToBinary("").empty());
    EXPECT_TRUE(str::quotedStringToBinary("  ").empty());
    EXPECT_TRUE(str::quotedStringToBinary("'circuit id").empty());
    EXPECT_TRUE(str::quotedStringToBinary("circuit id'").empty());

    // If there is only opening and closing quote, an empty
    // vector should be returned.
    EXPECT_TRUE(str::quotedStringToBinary("''").empty());

    // Both opening and ending quote is present.
    EXPECT_EQ("circuit id", testQuoted("'circuit id'"));
    EXPECT_EQ("remote id", testQuoted("  ' remote id'"));
    EXPECT_EQ("duid", testQuoted("  ' duid'"));
    EXPECT_EQ("duid", testQuoted("'duid    '  "));
    EXPECT_EQ("remote'id", testQuoted("  ' remote'id  '"));
    EXPECT_EQ("remote id'", testQuoted("'remote id''"));
    EXPECT_EQ("'remote id", testQuoted("''remote id'"));

    // Multiple quotes.
    EXPECT_EQ("'", testQuoted("'''"));
    EXPECT_EQ("''", testQuoted("''''"));
}

/// @brief Test that hex string with colons can be decoded.
///
/// @param input Input string to be decoded.
/// @param reference A string without colons representing the
/// decoded data.
void testColonSeparated(const std::string& input,
                        const std::string& reference) {
    // Create a reference vector.
    std::vector<uint8_t> reference_vector;
    ASSERT_NO_THROW(encode::decodeHex(reference, reference_vector));

    // Fill the output vector with some garbage to make sure that
    // the data is erased when a string is decoded successfully.
    std::vector<uint8_t> decoded(1, 10);
    ASSERT_NO_THROW(decodeColonSeparatedHexString(input, decoded));

    // Get the string representation of the decoded data for logging
    // purposes.
    std::string encoded;
    ASSERT_NO_THROW(encoded = encode::encodeHex(decoded));

    // Check if the decoded data matches the reference.
    EXPECT_TRUE(decoded == reference_vector)
        << "decoded data don't match the reference, input='"
        << input << "', reference='" << reference << "'"
        ", decoded='" << encoded << "'";
}

TEST(StringUtilTest, decodeColonSeparatedHexString) {
    // Test valid strings.
    testColonSeparated("A1:02:C3:d4:e5:F6", "A102C3D4E5F6");
    testColonSeparated("A:02:3:d:E5:F6", "0A02030DE5F6");
    testColonSeparated("A:B:C:D", "0A0B0C0D");
    testColonSeparated("1", "01");
    testColonSeparated("1e", "1E");
    testColonSeparated("", "");

    // Test invalid strings.
    std::vector<uint8_t> decoded;
    // Whitespaces.
    EXPECT_THROW(decodeColonSeparatedHexString("   ", decoded),
                 isc::BadValue);
    // Whitespace before digits.
    EXPECT_THROW(decodeColonSeparatedHexString(" A1", decoded),
                 isc::BadValue);
    // Two consecutive colons.
    EXPECT_THROW(decodeColonSeparatedHexString("A::01", decoded),
                 isc::BadValue);
    // Three consecutive colons.
    EXPECT_THROW(decodeColonSeparatedHexString("A:::01", decoded),
                 isc::BadValue);
    // Whitespace within a string.
    EXPECT_THROW(decodeColonSeparatedHexString("A :01", decoded),
                 isc::BadValue);
    // Terminating colon.
    EXPECT_THROW(decodeColonSeparatedHexString("0A:01:", decoded),
                 isc::BadValue);
    // Opening colon.
    EXPECT_THROW(decodeColonSeparatedHexString(":0A:01", decoded),
                 isc::BadValue);
    // Three digits before the colon.
    EXPECT_THROW(decodeColonSeparatedHexString("0A1:B1", decoded),
                 isc::BadValue);
}

void testFormatted(const std::string& input,
                   const std::string& reference) {
    // Create a reference vector.
    std::vector<uint8_t> reference_vector;
    ASSERT_NO_THROW(encode::decodeHex(reference, reference_vector));

    // Fill the output vector with some garbage to make sure that
    // the data is erased when a string is decoded successfully.
    std::vector<uint8_t> decoded(1, 10);
    ASSERT_NO_THROW(decodeFormattedHexString(input, decoded));

    // Get the string representation of the decoded data for logging
    // purposes.
    std::string encoded;
    ASSERT_NO_THROW(encoded = encode::encodeHex(decoded));

    // Check if the decoded data matches the reference.
    EXPECT_TRUE(decoded == reference_vector)
        << "decoded data don't match the reference, input='"
        << input << "', reference='" << reference << "'"
        ", decoded='" << encoded << "'";
}

TEST(StringUtilTest, decodeFormattedHexString) {
    // Colon separated.
    testFormatted("1:A7:B5:4:23", "01A7B50423");
    // No colons, even number of digits.
    testFormatted("17a534", "17A534");
    // Odd number of digits.
    testFormatted("A3A6f78", "0A3A6F78");
    // '0x' prefix.
    testFormatted("0xA3A6f78", "0A3A6F78");
    // '0x' prefix with a special value of 0.
    testFormatted("0x0", "00");
    // Empty string.
    testFormatted("", "");

    std::vector<uint8_t> decoded;
    // Whitespace.
    EXPECT_THROW(decodeFormattedHexString("0a ", decoded),
                 isc::BadValue);
    // Whitespace within a string.
    EXPECT_THROW(decodeFormattedHexString("01 02", decoded),
                 isc::BadValue);
    // '0x' prefix and colons.
    EXPECT_THROW(decodeFormattedHexString("0x01:02", decoded),
                 isc::BadValue);
    // Missing colon.
    EXPECT_THROW(decodeFormattedHexString("01:0203", decoded),
                 isc::BadValue);
    // Invalid prefix.
    EXPECT_THROW(decodeFormattedHexString("x0102", decoded),
                 isc::BadValue);
    // Invalid prefix again.
    EXPECT_THROW(decodeFormattedHexString("1x0102", decoded),
                 isc::BadValue);
}

// Verifies sanitizeString() function
TEST(StringUtilTest, sanitizeString) {
    std::string sanitized;

    // Bad regular expression should throw.
    ASSERT_THROW (sanitized = sanitizeString("just a string", "[bogus-regex",""),
                  BadValue);

    // A string of all valid chars should return an identical string.
    ASSERT_NO_THROW (sanitized = sanitizeString("-_A--B__Cabc34567_-", "[^A-Ca-c3-7_-]","x"));
    EXPECT_EQ(sanitized, "-_A--B__Cabc34567_-");

    // Replacing with a character should work.
    ASSERT_NO_THROW (sanitized = sanitizeString("A[b]c\12JoE3-_x!B$Y#e", "[^A-Za-z0-9_]","*"));
    EXPECT_EQ(sanitized, "A*b*c*JoE3*_x*B*Y*e");

    // Removing (i.e.replacing with an "empty" string) should work.
    ASSERT_NO_THROW (sanitized = sanitizeString("A[b]c\12JoE3-_x!B$Y#e", "[^A-Za-z0-9_]",""));
    EXPECT_EQ(sanitized, "AbcJoE3_xBYe");

    // More than one non-matching in a row should work.
    ASSERT_NO_THROW (sanitized = sanitizeString("%%A%%B%%C%%", "[^A-Za-z0-9_]","x"));
    EXPECT_EQ(sanitized, "xxAxxBxxCxx");

    // Removing than one non-matching in a row should work.
    ASSERT_NO_THROW (sanitized = sanitizeString("%%A%%B%%C%%", "[^A-Za-z0-9_]",""));
    EXPECT_EQ(sanitized, "ABC");

    // Replacing with a string should work.
    ASSERT_NO_THROW (sanitized = sanitizeString("%%A%%B%%C%%", "[^A-Za-z0-9_]","xyz"));
    EXPECT_EQ(sanitized, "xyzxyzAxyzxyzBxyzxyzCxyzxyz");
}

} // end of anonymous namespace
