// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>

#include <gtest/gtest.h>

#include <util/strutil.h>

#include <util/unittests/test_exceptions.h>

using namespace isc;
using namespace isc::util;
using namespace std;

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
    EXPECT_THROW_WITH(isc::util::str::getToken(ss),
                      isc::util::str::StringTokenError,
                      "could not read token from string");
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

    EXPECT_THROW_WITH(tokenToNumCall_32_16(""),
                      isc::util::str::StringTokenError,
                      "Invalid SRV numeric parameter: ");
    EXPECT_THROW_WITH(tokenToNumCall_32_16("a"),
                      isc::util::str::StringTokenError,
                      "Invalid SRV numeric parameter: a");
    EXPECT_THROW_WITH(tokenToNumCall_32_16("-1"),
                      isc::util::str::StringTokenError,
                      "Numeric SRV parameter out of range: -1");
    EXPECT_THROW_WITH(tokenToNumCall_32_16("65536"),
                      isc::util::str::StringTokenError,
                      "Numeric SRV parameter out of range: 65536");
    EXPECT_THROW_WITH(tokenToNumCall_32_16("1234567890"),
                      isc::util::str::StringTokenError,
                      "Numeric SRV parameter out of range: 1234567890");
    EXPECT_THROW_WITH(tokenToNumCall_32_16("-1234567890"),
                      isc::util::str::StringTokenError,
                      "Numeric SRV parameter out of range: -1234567890");

    uint16_t num16 = tokenToNumCall_16_8("123");
    EXPECT_EQ(123, num16);
    num16 = tokenToNumCall_16_8("0");
    EXPECT_EQ(0, num16);
    num16 = tokenToNumCall_16_8("255");
    EXPECT_EQ(255, num16);

    EXPECT_THROW_WITH(tokenToNumCall_16_8(""),
                      isc::util::str::StringTokenError,
                      "Invalid SRV numeric parameter: ");
    EXPECT_THROW_WITH(tokenToNumCall_16_8("a"),
                      isc::util::str::StringTokenError,
                      "Invalid SRV numeric parameter: a");
    EXPECT_THROW_WITH(tokenToNumCall_16_8("-1"),
                      isc::util::str::StringTokenError,
                      "Numeric SRV parameter out of range: -1");;
    EXPECT_THROW_WITH(tokenToNumCall_16_8("256"),
                      isc::util::str::StringTokenError,
                      "Numeric SRV parameter out of range: 256");
    EXPECT_THROW_WITH(tokenToNumCall_16_8("1234567890"),
                      isc::util::str::StringTokenError,
                      "Invalid SRV numeric parameter: 1234567890");
    EXPECT_THROW_WITH(tokenToNumCall_16_8("-1234567890"),
                      isc::util::str::StringTokenError,
                      "Invalid SRV numeric parameter: -1234567890");
}
