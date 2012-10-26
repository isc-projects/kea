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

#include <exceptions/exceptions.h>

#include <dns/master_lexer.h>

#include <gtest/gtest.h>

#include <string>

using namespace isc::dns;

namespace {

const char TEST_STRING[] = "string token";

class MasterLexerTokenTest : public ::testing::Test {
public:
    MasterLexerTokenTest() :
        token_err(MasterLexer::Token::ERROR),
        token_str(TEST_STRING, sizeof(TEST_STRING) - 1), // excluding ending 0
        token_num(42)
    {}

    const MasterLexer::Token token_err;
    const MasterLexer::Token token_str;
    const MasterLexer::Token token_num;
};


TEST_F(MasterLexerTokenTest, strings) {
    EXPECT_EQ(MasterLexer::Token::STRING, token_str.getType());
    EXPECT_EQ(std::string("string token"), token_str.getString());
    const MasterLexer::Token::StringRegion str_region =
        token_str.getStringRegion();
    EXPECT_EQ(TEST_STRING, str_region.beg);
    EXPECT_EQ(sizeof(TEST_STRING) - 1, str_region.len);

    // Construct type of qstring
    EXPECT_EQ(MasterLexer::Token::QSTRING,
              MasterLexer::Token(TEST_STRING, sizeof(TEST_STRING), true).
              getType());
    // if we explicitly set 'quoted' to false, it should be normal string
    EXPECT_EQ(MasterLexer::Token::STRING,
              MasterLexer::Token(TEST_STRING, sizeof(TEST_STRING), false).
              getType());

    // getString/StringRegion() aren't allowed for non string(-variant) types
    EXPECT_THROW(token_err.getString(), isc::InvalidOperation);
    EXPECT_THROW(token_num.getString(), isc::InvalidOperation);
    EXPECT_THROW(token_err.getStringRegion(), isc::InvalidOperation);
    EXPECT_THROW(token_num.getStringRegion(), isc::InvalidOperation);
}

TEST_F(MasterLexerTokenTest, numbers) {
    EXPECT_EQ(42, token_num.getNumber());
    EXPECT_EQ(MasterLexer::Token::NUMBER, token_num.getType());

    // It's copyable and assignable.
    MasterLexer::Token token(token_num);
    EXPECT_EQ(42, token.getNumber());
    EXPECT_EQ(MasterLexer::Token::NUMBER, token.getType());

    token = token_num;
    EXPECT_EQ(42, token.getNumber());
    EXPECT_EQ(MasterLexer::Token::NUMBER, token.getType());

    // it's okay to replace it with a different type of token
    token = token_err;
    EXPECT_EQ(MasterLexer::Token::ERROR, token.getType());

    // Possible max value
    token = MasterLexer::Token(0xffffffff);
    EXPECT_EQ(4294967295u, token.getNumber());

    // TBD: getNumber for other type
    EXPECT_THROW(token_err.getNumber(), isc::InvalidOperation);
}

TEST_F(MasterLexerTokenTest, specials) {
    // Just checking we can construct them and getType() returns correct value.
    EXPECT_EQ(MasterLexer::Token::ERROR, token_err.getType());
    EXPECT_EQ(MasterLexer::Token::END_OF_LINE,
              MasterLexer::Token(MasterLexer::Token::END_OF_LINE).getType());
    EXPECT_EQ(MasterLexer::Token::END_OF_FILE,
              MasterLexer::Token(MasterLexer::Token::END_OF_FILE).getType());
    EXPECT_EQ(MasterLexer::Token::INITIAL_WS,
              MasterLexer::Token(MasterLexer::Token::INITIAL_WS).getType());

    // Special types of tokens cannot have value-based types
    EXPECT_THROW(MasterLexer::Token t(MasterLexer::Token::STRING),
                 isc::InvalidParameter);
    EXPECT_THROW(MasterLexer::Token t(MasterLexer::Token::QSTRING),
                 isc::InvalidParameter);
    EXPECT_THROW(MasterLexer::Token t(MasterLexer::Token::NUMBER),
                 isc::InvalidParameter);
}
}
