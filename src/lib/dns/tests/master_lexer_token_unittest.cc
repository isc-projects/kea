// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
        token_eof(MasterToken::END_OF_FILE),
        token_str(TEST_STRING, TEST_STRING_LEN),
        token_num(42),
        token_err(MasterToken::UNEXPECTED_END)
    {}

    const MasterToken token_eof; // an example of non-value type token
    const MasterToken token_str;
    const MasterToken token_num;
    const MasterToken token_err;
};


TEST_F(MasterLexerTokenTest, strings) {
    // basic construction and getter checks
    EXPECT_EQ(MasterToken::STRING, token_str.getType());
    EXPECT_EQ(std::string("string token"), token_str.getString());
    std::string strval = "dummy"; // this should be replaced
    token_str.getString(strval);
    EXPECT_EQ(std::string("string token"), strval);
    const MasterToken::StringRegion str_region =
        token_str.getStringRegion();
    EXPECT_EQ(TEST_STRING, str_region.beg);
    EXPECT_EQ(TEST_STRING_LEN, str_region.len);

    // Even if the stored string contains a nul character (in this case,
    // it happens to be at the end of the string, but could be in the middle),
    // getString() should return a string object containing the nul.
    std::string expected_str("string token");
    expected_str.push_back('\0');
    EXPECT_EQ(expected_str,
              MasterToken(TEST_STRING, TEST_STRING_LEN + 1).getString());
    MasterToken(TEST_STRING, TEST_STRING_LEN + 1).getString(strval);
    EXPECT_EQ(expected_str, strval);

    // Construct type of qstring
    EXPECT_EQ(MasterToken::QSTRING,
              MasterToken(TEST_STRING, sizeof(TEST_STRING), true).
              getType());
    // if we explicitly set 'quoted' to false, it should be normal string
    EXPECT_EQ(MasterToken::STRING,
              MasterToken(TEST_STRING, sizeof(TEST_STRING), false).
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
    EXPECT_EQ(MasterToken::NUMBER, token_num.getType());

    // It's copyable and assignable.
    MasterToken token(token_num);
    EXPECT_EQ(42, token.getNumber());
    EXPECT_EQ(MasterToken::NUMBER, token.getType());

    token = token_num;
    EXPECT_EQ(42, token.getNumber());
    EXPECT_EQ(MasterToken::NUMBER, token.getType());

    // it's okay to replace it with a different type of token
    token = token_eof;
    EXPECT_EQ(MasterToken::END_OF_FILE, token.getType());

    // Possible max value
    token = MasterToken(0xffffffff);
    EXPECT_EQ(4294967295u, token.getNumber());

    // getNumber() isn't allowed for non number types
    EXPECT_THROW(token_eof.getNumber(), isc::InvalidOperation);
    EXPECT_THROW(token_str.getNumber(), isc::InvalidOperation);
}

TEST_F(MasterLexerTokenTest, novalues) {
    // Just checking we can construct them and getType() returns correct value.
    EXPECT_EQ(MasterToken::END_OF_FILE, token_eof.getType());
    EXPECT_EQ(MasterToken::END_OF_LINE,
              MasterToken(MasterToken::END_OF_LINE).getType());
    EXPECT_EQ(MasterToken::INITIAL_WS,
              MasterToken(MasterToken::INITIAL_WS).getType());

    // Special types of tokens cannot have value-based types
    EXPECT_THROW(MasterToken t(MasterToken::STRING), isc::InvalidParameter);
    EXPECT_THROW(MasterToken t(MasterToken::QSTRING), isc::InvalidParameter);
    EXPECT_THROW(MasterToken t(MasterToken::NUMBER), isc::InvalidParameter);
    EXPECT_THROW(MasterToken t(MasterToken::ERROR), isc::InvalidParameter);
}

TEST_F(MasterLexerTokenTest, errors) {
    EXPECT_EQ(MasterToken::ERROR, token_err.getType());
    EXPECT_EQ(MasterToken::UNEXPECTED_END, token_err.getErrorCode());
    EXPECT_EQ("unexpected end of input", token_err.getErrorText());
    EXPECT_EQ("lexer not started", MasterToken(MasterToken::NOT_STARTED).
              getErrorText());
    EXPECT_EQ("unbalanced parentheses",
              MasterToken(MasterToken::UNBALANCED_PAREN).
              getErrorText());
    EXPECT_EQ("unbalanced quotes", MasterToken(MasterToken::UNBALANCED_QUOTES).
              getErrorText());
    EXPECT_EQ("no token produced", MasterToken(MasterToken::NO_TOKEN_PRODUCED).
              getErrorText());
    EXPECT_EQ("number out of range",
              MasterToken(MasterToken::NUMBER_OUT_OF_RANGE).
              getErrorText());
    EXPECT_EQ("not a valid number",
              MasterToken(MasterToken::BAD_NUMBER).getErrorText());
    EXPECT_EQ("unexpected quotes",
              MasterToken(MasterToken::UNEXPECTED_QUOTES).getErrorText());

    // getErrorCode/Text() isn't allowed for non number types
    EXPECT_THROW(token_num.getErrorCode(), isc::InvalidOperation);
    EXPECT_THROW(token_num.getErrorText(), isc::InvalidOperation);

    // Only the pre-defined error code is accepted.  Hardcoding '8' (max code
    // + 1) is intentional; it'd be actually better if we notice it when we
    // update the enum list (which shouldn't happen too often).
    //
    // Note: if you fix this testcase, you probably want to update the
    // getErrorText() tests above too.
    EXPECT_THROW(MasterToken(MasterToken::ErrorCode(8)),
                 isc::InvalidParameter);

    // Check the coexistence of "from number" and "from error-code"
    // constructors won't cause confusion.
    EXPECT_EQ(MasterToken::NUMBER,
              MasterToken(static_cast<uint32_t>(MasterToken::NOT_STARTED)).
              getType());
}
}
