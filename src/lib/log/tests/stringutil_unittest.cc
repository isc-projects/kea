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

// $Id: base64_unittest.cc 2549 2010-07-20 19:09:37Z jinmei $

#include <string>

#include <gtest/gtest.h>

#include <log/stringutil.h>

using namespace isc;
using namespace isc::log;
using namespace std;

class StringUtilTest : public ::testing::Test {
protected:
    StringUtilTest()
    {
    }
};


// Check for slash replacement

TEST_F(StringUtilTest, Slash) {

    string instring = "";
    StringUtil::normalizeSlash(instring);
    EXPECT_EQ("", instring);

    instring = "C:\\A\\B\\C.D";
    StringUtil::normalizeSlash(instring);
    EXPECT_EQ("C:/A/B/C.D", instring);

    instring = "// \\ //";
    StringUtil::normalizeSlash(instring);
    EXPECT_EQ("// / //", instring);
}

// Check that leading and trailing space trimming works

TEST_F(StringUtilTest, Trim) {

    // Empty and full string.
    EXPECT_EQ("", StringUtil::trim(""));
    EXPECT_EQ("abcxyz", StringUtil::trim("abcxyz"));

    // Trim right-most blanks
    EXPECT_EQ("ABC", StringUtil::trim("ABC   "));
    EXPECT_EQ("ABC", StringUtil::trim("ABC\t\t  \n\t"));

    // Left-most blank trimming
    EXPECT_EQ("XYZ", StringUtil::trim("  XYZ"));
    EXPECT_EQ("XYZ", StringUtil::trim("\t\t  \tXYZ"));

    // Right and left, with embedded spaces
    EXPECT_EQ("MN \t OP", StringUtil::trim("\t\tMN \t OP \t"));
}

// Check tokenization.  Note that ASSERT_EQ is used to check the size of the
// returned vector; if not as expected, the following references may be invalid
// so should not be used.

TEST_F(StringUtilTest, Tokens) {
    vector<string>  result;

    // Default delimiters
    result = StringUtil::tokens(" \n ");    // Empty string
    EXPECT_EQ(0, result.size());

    result = StringUtil::tokens("abc");     // Full string
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(string("abc"), result[0]);

    result = StringUtil::tokens("\t xyz \n");
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(string("xyz"), result[0]);

    result = StringUtil::tokens("abc\ndef\t\tghi ");
    ASSERT_EQ(3, result.size());
    EXPECT_EQ(string("abc"), result[0]);
    EXPECT_EQ(string("def"), result[1]);
    EXPECT_EQ(string("ghi"), result[2]);

    // Non-default delimiters
    result = StringUtil::tokens("alpha/beta/ /gamma//delta/epsilon/", "/");
    ASSERT_EQ(6, result.size());
    EXPECT_EQ(string("alpha"), result[0]);
    EXPECT_EQ(string("beta"), result[1]);
    EXPECT_EQ(string(" "), result[2]);
    EXPECT_EQ(string("gamma"), result[3]);
    EXPECT_EQ(string("delta"), result[4]);
    EXPECT_EQ(string("epsilon"), result[5]);
}

// Changing case

TEST_F(StringUtilTest, ChangeCase) {
    string mixed("abcDEFghiJKLmno123[]{=+--+]}");
    string upper("ABCDEFGHIJKLMNO123[]{=+--+]}");
    string lower("abcdefghijklmno123[]{=+--+]}");

    string test = mixed;
    StringUtil::lowercase(test);
    EXPECT_EQ(lower, test);

    test = mixed;
    StringUtil::uppercase(test);
    EXPECT_EQ(upper, test);
}
