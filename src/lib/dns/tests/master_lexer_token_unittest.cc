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
// This excludes the ending \0 character
const size_t TEST_STRING_LEN = sizeof(TEST_STRING) - 1;

class MasterLexerTokenTest : public ::testing::Test {
protected:
    MasterLexerTokenTest() :
        token_eof(MasterLexer::Token::END_OF_FILE),
        token_str(TEST_STRING, TEST_STRING_LEN),
        token_num(42),
        token_err(MasterLexer::Token::UNEXPECTED_END)
    {}

    const MasterLexer::Token token_eof; // an example of non-value type token
    const MasterLexer::Token token_str;
    const MasterLexer::Token token_num;
    const MasterLexer::Token token_err;
};


TEST_F(MasterLexerTokenTest, strings) {
    // basic construction and getter checks
    EXPECT_EQ(MasterLexer::Token::STRING, token_str.getType());
    EXPECT_EQ(std::string("string token"), token_str.getString());
    std::string strval = "dummy"; // this should be replaced
    token_str.getString(strval);
    EXPECT_EQ(std::string("string token"), strval);
    const MasterLexer::Token::StringRegion str_region =
        token_str.getStringRegion();
    EXPECT_EQ(TEST_STRING, str_region.beg);
    EXPECT_EQ(TEST_STRING_LEN, str_region.len);

    // Even if the stored string contains a nul character (in this case,
    // it happens to be at the end of the string, but could be in the middle),
    // getString() should return a string object containing the nul.
    std::string expected_str("string token");
    expected_str.push_back('\0');
    EXPECT_EQ(expected_str,
              MasterLexer::Token(TEST_STRING, TEST_STRING_LEN + 1).getString());
    MasterLexer::Token(TEST_STRING, TEST_STRING_LEN + 1).getString(strval);
    EXPECT_EQ(expected_str, strval);

    // Construct type of qstring
    EXPECT_EQ(MasterLexer::Token::QSTRING,
              MasterLexer::Token(TEST_STRING, sizeof(TEST_STRING), true).
              getType());
    // if we explicitly set 'quoted' to false, it should be normal string
    EXPECT_EQ(MasterLexer::Token::STRING,
              MasterLexer::Token(TEST_STRING, sizeof(TEST_STRING), false).
              getType());

    // getString/StringRegion() aren't allowed for non string(-variant) types
    EXPECT_THROW(token_eof.getString(), isc::InvalidOperation);
    EXPECT_THROW(token_eof.getString(strval), isc::InvalidOperation);
    EXPECT_THROW(token_num.getString(), isc::InvalidOperation);
    EXPECT_THROW(token_num.getString(strval), isc::InvalidOperation);
    EXPECT_THROW(token_eof.getStringRegion(), isc::InvalidOperation);
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
    token = token_eof;
    EXPECT_EQ(MasterLexer::Token::END_OF_FILE, token.getType());

    // Possible max value
    token = MasterLexer::Token(0xffffffff);
    EXPECT_EQ(4294967295u, token.getNumber());

    // getNumber() isn't allowed for non number types
    EXPECT_THROW(token_eof.getNumber(), isc::InvalidOperation);
    EXPECT_THROW(token_str.getNumber(), isc::InvalidOperation);
}

TEST_F(MasterLexerTokenTest, novalues) {
    // Just checking we can construct them and getType() returns correct value.
    EXPECT_EQ(MasterLexer::Token::END_OF_FILE, token_eof.getType());
    EXPECT_EQ(MasterLexer::Token::END_OF_LINE,
              MasterLexer::Token(MasterLexer::Token::END_OF_LINE).getType());
    EXPECT_EQ(MasterLexer::Token::INITIAL_WS,
              MasterLexer::Token(MasterLexer::Token::INITIAL_WS).getType());

    // Special types of tokens cannot have value-based types
    EXPECT_THROW(MasterLexer::Token t(MasterLexer::Token::STRING),
                 isc::InvalidParameter);
    EXPECT_THROW(MasterLexer::Token t(MasterLexer::Token::QSTRING),
                 isc::InvalidParameter);
    EXPECT_THROW(MasterLexer::Token t(MasterLexer::Token::NUMBER),
                 isc::InvalidParameter);
    EXPECT_THROW(MasterLexer::Token t(MasterLexer::Token::ERROR),
                 isc::InvalidParameter);
}

TEST_F(MasterLexerTokenTest, errors) {
    EXPECT_EQ(MasterLexer::Token::ERROR, token_err.getType());
    EXPECT_EQ(MasterLexer::Token::UNEXPECTED_END, token_err.getErrorCode());
    EXPECT_EQ("unexpected end of input", token_err.getErrorText());
    EXPECT_EQ("lexer not started",
              MasterLexer::Token(MasterLexer::Token::NOT_STARTED).
              getErrorText());
    EXPECT_EQ("unbalanced parentheses",
              MasterLexer::Token(MasterLexer::Token::UNBALANCED_PAREN).
              getErrorText());
    EXPECT_EQ("unbalanced quotes",
              MasterLexer::Token(MasterLexer::Token::UNBALANCED_QUOTES).
              getErrorText());
    EXPECT_EQ("no token produced",
              MasterLexer::Token(MasterLexer::Token::NO_TOKEN_PRODUCED).
              getErrorText());
    EXPECT_EQ("number out of range",
              MasterLexer::Token(MasterLexer::Token::NUMBER_RANGE).
              getErrorText());

    // getErrorCode/Text() isn't allowed for non number types
    EXPECT_THROW(token_num.getErrorCode(), isc::InvalidOperation);
    EXPECT_THROW(token_num.getErrorText(), isc::InvalidOperation);

    // Only the pre-defined error code is accepted.  Hardcoding '6' (max code
    // + 1) is intentional; it'd be actually better if we notice it when we
    // update the enum list (which shouldn't happen too often).
    EXPECT_THROW(MasterLexer::Token(MasterLexer::Token::ErrorCode(6)),
                 isc::InvalidParameter);

    // Check the coexistence of "from number" and "from error-code"
    // constructors won't cause confusion.
    EXPECT_EQ(MasterLexer::Token::NUMBER,
              MasterLexer::Token(static_cast<uint32_t>(
                                     MasterLexer::Token::NOT_STARTED)).
              getType());
}
}
