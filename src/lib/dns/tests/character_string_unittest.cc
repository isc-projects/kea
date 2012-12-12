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


#include <gtest/gtest.h>

#include <dns/rdata.h>
#include <dns/tests/unittest_util.h>
#include <dns/character_string.h>

using isc::UnitTestUtil;

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::dns::characterstr;
using namespace isc::dns::rdata;

namespace {

class CharacterString {
public:
    CharacterString(const string& str){
        string::const_iterator it = str.begin();
        characterStr_ = getNextCharacterString(str, it, &is_quoted_);
    }
    const string& str() const { return characterStr_; }
    bool quoted() const { return (is_quoted_); }
private:
    string characterStr_;
    bool is_quoted_;
};

TEST(CharacterStringTest, testNormalCase) {
    CharacterString cstr1("foo");
    EXPECT_EQ(string("foo"), cstr1.str());

    // Test <character-string> that separated by space
    CharacterString cstr2("foo bar");
    EXPECT_EQ(string("foo"), cstr2.str());
    EXPECT_FALSE(cstr2.quoted());

    // Test <character-string> that separated by quotes
    CharacterString cstr3("\"foo bar\"");
    EXPECT_EQ(string("foo bar"), cstr3.str());
    EXPECT_TRUE(cstr3.quoted());

    // Test <character-string> that not separate by quotes but ended with quotes
    CharacterString cstr4("foo\"");
    EXPECT_EQ(string("foo\""), cstr4.str());
    EXPECT_FALSE(cstr4.quoted());
}

TEST(CharacterStringTest, testBadCase) {
    // The <character-string> that started with quotes should also be ended
    // with quotes
    EXPECT_THROW(CharacterString cstr("\"foo"), InvalidRdataText);

    // The string length cannot exceed 255 characters
    string str;
    for (int i = 0; i < 257; ++i) {
        str += 'A';
    }
    EXPECT_THROW(CharacterString cstr(str), CharStringTooLong);
}

TEST(CharacterStringTest, testEscapeCharacter) {
    CharacterString cstr1("foo\\bar");
    EXPECT_EQ(string("foobar"), cstr1.str());

    CharacterString cstr2("foo\\\\bar");
    EXPECT_EQ(string("foo\\bar"), cstr2.str());

    CharacterString cstr3("fo\\111bar");
    EXPECT_EQ(string("foobar"), cstr3.str());

    CharacterString cstr4("fo\\1112bar");
    EXPECT_EQ(string("foo2bar"), cstr4.str());

    // There must be at least 3 digits followed by '\'
    EXPECT_THROW(CharacterString cstr("foo\\98ar"), InvalidRdataText);
    EXPECT_THROW(CharacterString cstr("foo\\9ar"), InvalidRdataText);
    EXPECT_THROW(CharacterString cstr("foo\\98"), InvalidRdataText);
}

} // namespace
