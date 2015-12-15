// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>

#include <dns/master_lexer.h>
#include <dns/master_lexer_state.h>

#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>
#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/bind.hpp>

#include <string>
#include <sstream>

using namespace isc::dns;
using std::string;
using std::stringstream;
using boost::lexical_cast;
using boost::scoped_ptr;
using master_lexer_internal::State;

namespace {

class MasterLexerTest : public ::testing::Test {
protected:
    MasterLexerTest() :
        expected_stream_name("stream-" + lexical_cast<string>(&ss))
    {}

    MasterLexer lexer;
    stringstream ss;
    const string expected_stream_name;
};

// Commonly used check case where the input sources stack is empty.
void
checkEmptySource(const MasterLexer& lexer) {
    EXPECT_TRUE(lexer.getSourceName().empty());
    EXPECT_EQ(0, lexer.getSourceLine());
    EXPECT_EQ(0, lexer.getPosition());
}

TEST_F(MasterLexerTest, preOpen) {
    // Initially sources stack is empty.
    checkEmptySource(lexer);
}

TEST_F(MasterLexerTest, pushStream) {
    EXPECT_EQ(0, lexer.getSourceCount());
    ss << "test";
    lexer.pushSource(ss);
    EXPECT_EQ(expected_stream_name, lexer.getSourceName());
    EXPECT_EQ(1, lexer.getSourceCount());
    EXPECT_EQ(4, lexer.getTotalSourceSize()); // 4 = len("test")

    // From the point of view of this test, we only have to check (though
    // indirectly) getSourceLine calls InputSource::getCurrentLine.  It should
    // return 1 initially.
    EXPECT_EQ(1, lexer.getSourceLine());

    // By popping it the stack will be empty again.
    lexer.popSource();
    EXPECT_EQ(0, lexer.getSourceCount());
    checkEmptySource(lexer);
    EXPECT_EQ(4, lexer.getTotalSourceSize()); // this shouldn't change
}

TEST_F(MasterLexerTest, pushStreamFail) {
    // Pretend a "bad" thing happened in the stream.  This will make the
    // initialization throw an exception.
    ss << "test";
    ss.setstate(std::ios_base::badbit);

    EXPECT_THROW(lexer.pushSource(ss), isc::Unexpected);
}

TEST_F(MasterLexerTest, pushFile) {
    // We use zone file (-like) data, but in this test that actually doesn't
    // matter.
    EXPECT_EQ(0, lexer.getSourceCount());
    EXPECT_TRUE(lexer.pushSource(TEST_DATA_SRCDIR "/masterload.txt"));
    EXPECT_EQ(1, lexer.getSourceCount());
    EXPECT_EQ(TEST_DATA_SRCDIR "/masterload.txt", lexer.getSourceName());
    EXPECT_EQ(1, lexer.getSourceLine());

    // 143 = size of the test zone file.  hardcode it assuming it won't change
    // too often.
    EXPECT_EQ(143, lexer.getTotalSourceSize());

    lexer.popSource();
    checkEmptySource(lexer);
    EXPECT_EQ(0, lexer.getSourceCount());
    EXPECT_EQ(143, lexer.getTotalSourceSize()); // this shouldn't change

    // If we give a non NULL string pointer, its content will be intact
    // if pushSource succeeds.
    std::string error_txt = "dummy";
    EXPECT_TRUE(lexer.pushSource(TEST_DATA_SRCDIR "/masterload.txt",
                                 &error_txt));
    EXPECT_EQ("dummy", error_txt);
}

TEST_F(MasterLexerTest, pushBadFileName) {
    EXPECT_THROW(lexer.pushSource(NULL), isc::InvalidParameter);
}

TEST_F(MasterLexerTest, pushFileFail) {
    // The file to be pushed doesn't exist.  pushSource() fails and
    // some non empty error string should be set.
    std::string error_txt;
    EXPECT_TRUE(error_txt.empty());
    EXPECT_FALSE(lexer.pushSource("no-such-file", &error_txt));
    EXPECT_FALSE(error_txt.empty());

    // It's safe to pass NULL error_txt (either explicitly or implicitly as
    // the default)
    EXPECT_FALSE(lexer.pushSource("no-such-file", NULL));
    EXPECT_FALSE(lexer.pushSource("no-such-file"));
}

TEST_F(MasterLexerTest, nestedPush) {
    const string test_txt = "test";
    ss << test_txt;
    lexer.pushSource(ss);

    EXPECT_EQ(test_txt.size(), lexer.getTotalSourceSize());
    EXPECT_EQ(0, lexer.getPosition());

    EXPECT_EQ(expected_stream_name, lexer.getSourceName());

    // Read the string; getPosition() should reflect that.
    EXPECT_EQ(MasterToken::STRING, lexer.getNextToken().getType());
    EXPECT_EQ(test_txt.size(), lexer.getPosition());

    // We can push another source without popping the previous one.
    lexer.pushSource(TEST_DATA_SRCDIR "/masterload.txt");
    EXPECT_EQ(TEST_DATA_SRCDIR "/masterload.txt", lexer.getSourceName());
    EXPECT_EQ(143 + test_txt.size(),
              lexer.getTotalSourceSize()); // see above for magic nums

    // the next token should be the EOL (skipping a comment line), its
    // position in the file is 35 (hardcoded).
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());
    EXPECT_EQ(test_txt.size() + 35, lexer.getPosition());

    // popSource() works on the "topmost" (last-pushed) source
    lexer.popSource();
    EXPECT_EQ(expected_stream_name, lexer.getSourceName());

    // pop shouldn't change the total size and the current position
    EXPECT_EQ(143 + test_txt.size(), lexer.getTotalSourceSize());
    EXPECT_EQ(test_txt.size() + 35, lexer.getPosition());

    lexer.popSource();
    EXPECT_TRUE(lexer.getSourceName().empty());

    // size and position still shouldn't change
    EXPECT_EQ(143 + test_txt.size(), lexer.getTotalSourceSize());
    EXPECT_EQ(test_txt.size() + 35, lexer.getPosition());
}

TEST_F(MasterLexerTest, unknownSourceSize) {
    // Similar to the previous case, but the size of the second source
    // will be considered "unknown" (by emulating an error).
    ss << "test";
    lexer.pushSource(ss);
    EXPECT_EQ(4, lexer.getTotalSourceSize());

    stringstream ss2;
    ss2.setstate(std::ios_base::failbit); // this will make the size unknown
    lexer.pushSource(ss2);
    // Then the total size is also unknown.
    EXPECT_EQ(MasterLexer::SOURCE_SIZE_UNKNOWN, lexer.getTotalSourceSize());

    // Even if we pop that source, the size is still unknown.
    lexer.popSource();
    EXPECT_EQ(MasterLexer::SOURCE_SIZE_UNKNOWN, lexer.getTotalSourceSize());
}

TEST_F(MasterLexerTest, invalidPop) {
    // popSource() cannot be called if the sources stack is empty.
    EXPECT_THROW(lexer.popSource(), isc::InvalidOperation);
}

// Test it is not possible to get token when no source is available.
TEST_F(MasterLexerTest, noSource) {
    EXPECT_THROW(lexer.getNextToken(), isc::InvalidOperation);
}

// Test getting some tokens.  It also check basic behavior of getPosition().
TEST_F(MasterLexerTest, getNextToken) {
    ss << "\n   \n\"STRING\"\n";
    lexer.pushSource(ss);

    // First, the newline should get out.
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());
    EXPECT_EQ(1, lexer.getPosition());
    // Then the whitespace, if we specify the option.
    EXPECT_EQ(MasterToken::INITIAL_WS,
              lexer.getNextToken(MasterLexer::INITIAL_WS).getType());
    EXPECT_EQ(2, lexer.getPosition());
    // The newline
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());
    EXPECT_EQ(5, lexer.getPosition()); // 1st \n + 3 spaces, then 2nd \n
    // The (quoted) string
    EXPECT_EQ(MasterToken::QSTRING,
              lexer.getNextToken(MasterLexer::QSTRING).getType());
    EXPECT_EQ(5 + 8, lexer.getPosition()); // 8 = len("STRING') + quotes

    // And the end of line and file
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());
    EXPECT_EQ(5 + 8 + 1, lexer.getPosition()); // previous + 3rd \n
    EXPECT_EQ(MasterToken::END_OF_FILE, lexer.getNextToken().getType());
    EXPECT_EQ(5 + 8 + 1, lexer.getPosition()); // position doesn't change
}

// Test we correctly find end of file.
TEST_F(MasterLexerTest, eof) {
    // Let the ss empty.
    lexer.pushSource(ss);

    // The first one is found to be EOF
    EXPECT_EQ(MasterToken::END_OF_FILE, lexer.getNextToken().getType());
    // And it stays on EOF for any following attempts
    EXPECT_EQ(MasterToken::END_OF_FILE, lexer.getNextToken().getType());
    // And we can step back one token, but that is the EOF too.
    lexer.ungetToken();
    EXPECT_EQ(MasterToken::END_OF_FILE, lexer.getNextToken().getType());
}

// Check we properly return error when there's an opened parentheses and no
// closing one
TEST_F(MasterLexerTest, getUnbalancedParen) {
    ss << "(string";
    lexer.pushSource(ss);

    // The string gets out first
    EXPECT_EQ(MasterToken::STRING, lexer.getNextToken().getType());
    // Then an unbalanced parenthesis
    EXPECT_EQ(MasterToken::UNBALANCED_PAREN,
              lexer.getNextToken().getErrorCode());
    // And then EOF
    EXPECT_EQ(MasterToken::END_OF_FILE, lexer.getNextToken().getType());
}

// Check we properly return error when there's an opened quoted string and no
// closing one
TEST_F(MasterLexerTest, getUnbalancedString) {
    ss << "\"string";
    lexer.pushSource(ss);

    // Then an unbalanced qstring (reported as an unexpected end)
    EXPECT_EQ(MasterToken::UNEXPECTED_END,
              lexer.getNextToken(MasterLexer::QSTRING).getErrorCode());
    // And then EOF
    EXPECT_EQ(MasterToken::END_OF_FILE, lexer.getNextToken().getType());
}

// Test ungetting tokens works.  Also check getPosition() is adjusted
TEST_F(MasterLexerTest, ungetToken) {
    ss << "\n (\"string\"\n) more";
    lexer.pushSource(ss);

    // Try getting the newline
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());
    EXPECT_EQ(1, lexer.getPosition());
    // Return it and get again
    lexer.ungetToken();
    EXPECT_EQ(0, lexer.getPosition());
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());
    EXPECT_EQ(1, lexer.getPosition());
    // Get the string and return it back
    EXPECT_EQ(MasterToken::QSTRING,
              lexer.getNextToken(MasterLexer::QSTRING).getType());
    EXPECT_EQ(string("\n (\"string\"").size(), lexer.getPosition());
    lexer.ungetToken();
    EXPECT_EQ(1, lexer.getPosition()); // back to just after 1st \n
    // But if we change the options, it honors them
    EXPECT_EQ(MasterToken::INITIAL_WS,
              lexer.getNextToken(MasterLexer::QSTRING |
                                 MasterLexer::INITIAL_WS).getType());
    // Get to the "more" string
    EXPECT_EQ(MasterToken::QSTRING,
              lexer.getNextToken(MasterLexer::QSTRING).getType());
    EXPECT_EQ(MasterToken::STRING,
              lexer.getNextToken(MasterLexer::QSTRING).getType());
    // Return it back. It should get inside the parentheses.
    // Upon next attempt to get it again, the newline inside the parentheses
    // should be still ignored.
    lexer.ungetToken();
    EXPECT_EQ(MasterToken::STRING,
              lexer.getNextToken(MasterLexer::QSTRING).getType());
}

// Check ungetting token without overriding the start method. We also
// check it works well with changing options between the calls.
TEST_F(MasterLexerTest, ungetRealOptions) {
    ss << "    \n";
    lexer.pushSource(ss);

    // If we call it the usual way, it skips up to the newline and returns
    // it
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());

    // Now we return it. If we call it again, but with different options,
    // we get the initial whitespace.
    lexer.ungetToken();
    EXPECT_EQ(MasterToken::INITIAL_WS,
              lexer.getNextToken(MasterLexer::INITIAL_WS).getType());
}

// Check the initial whitespace is found even in the first line of included
// file.  It also confirms getPosition() works for multiple sources, each
// of which is partially parsed.
TEST_F(MasterLexerTest, includeAndInitialWS) {
    ss << "    \n";
    lexer.pushSource(ss);

    stringstream ss2;
    ss2 << "    \n";

    EXPECT_EQ(MasterToken::INITIAL_WS,
              lexer.getNextToken(MasterLexer::INITIAL_WS).getType());
    EXPECT_EQ(1, lexer.getPosition());
    lexer.pushSource(ss2);
    EXPECT_EQ(MasterToken::INITIAL_WS,
              lexer.getNextToken(MasterLexer::INITIAL_WS).getType());
    EXPECT_EQ(2, lexer.getPosition()); // should be sum of pushed positions.
}

// Test only one token can be ungotten
TEST_F(MasterLexerTest, ungetTwice) {
    ss << "\n";
    lexer.pushSource(ss);

    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());
    // Unget the token. It can be done once
    lexer.ungetToken();
    // But not twice
    EXPECT_THROW(lexer.ungetToken(), isc::InvalidOperation);
}

// Test we can't unget a token before we get one
TEST_F(MasterLexerTest, ungetBeforeGet) {
    lexer.pushSource(ss); // Just to eliminate the missing source problem
    EXPECT_THROW(lexer.ungetToken(), isc::InvalidOperation);
}

// Test we can't unget a token after a source switch, even when we got
// something before.
TEST_F(MasterLexerTest, ungetAfterSwitch) {
    ss << "\n\n";
    lexer.pushSource(ss);
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());
    // Switch the source
    std::stringstream ss2;
    ss2 << "\n\n";
    lexer.pushSource(ss2);
    EXPECT_THROW(lexer.ungetToken(), isc::InvalidOperation);
    // We can get from the new source
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());
    // And when we drop the current source, we can't unget again
    lexer.popSource();
    EXPECT_THROW(lexer.ungetToken(), isc::InvalidOperation);
}

// Common checks for the case when getNextToken() should result in LexerError
void
lexerErrorCheck(MasterLexer& lexer, MasterToken::Type expect,
                MasterToken::ErrorCode expected_error)
{
    bool thrown = false;
    try {
        lexer.getNextToken(expect);
    } catch (const MasterLexer::LexerError& error) {
        EXPECT_EQ(expected_error, error.token_.getErrorCode());
        thrown = true;
    }
    EXPECT_TRUE(thrown);
}

// Common checks regarding expected/unexpected end-of-line
//
// The 'lexer' should be at a position before two consecutive '\n's.
// The first one will be recognized, and the second one will be considered an
// unexpected token.  Then this helper consumes the second '\n', so the caller
// can continue the test after these '\n's.
void
eolCheck(MasterLexer& lexer, MasterToken::Type expect) {
    // If EOL is found and eol_ok is true, we get it.
    EXPECT_EQ(MasterToken::END_OF_LINE,
              lexer.getNextToken(expect, true).getType());
    // We'll see the second '\n'; by default it will fail.
    EXPECT_THROW(lexer.getNextToken(expect), MasterLexer::LexerError);
    // Same if eol_ok is explicitly set to false.  This also checks the
    // offending '\n' was "ungotten".
    EXPECT_THROW(lexer.getNextToken(expect, false), MasterLexer::LexerError);

    // And also check the error token set in the exception object.
    lexerErrorCheck(lexer, expect, MasterToken::UNEXPECTED_END);

    // Then skip the 2nd '\n'
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());
}

// Common checks regarding expected/unexpected end-of-file
//
// The 'lexer' should be at a position just before an end-of-file.
void
eofCheck(MasterLexer& lexer, MasterToken::Type expect) {
    EXPECT_EQ(MasterToken::END_OF_FILE,
              lexer.getNextToken(expect, true).getType());
    EXPECT_THROW(lexer.getNextToken(expect), MasterLexer::LexerError);
    EXPECT_THROW(lexer.getNextToken(expect, false), MasterLexer::LexerError);
}

TEST_F(MasterLexerTest, getNextTokenString) {
    ss << "normal-string\n";
    ss << "\n";
    ss << "another-string";
    lexer.pushSource(ss);

    // Normal successful case: Expecting a string and get one.
    EXPECT_EQ("normal-string",
              lexer.getNextToken(MasterToken::STRING).getString());
    eolCheck(lexer, MasterToken::STRING);

    // Same set of tests but for end-of-file
    EXPECT_EQ("another-string",
              lexer.getNextToken(MasterToken::STRING, true).getString());
    eofCheck(lexer, MasterToken::STRING);
}

TEST_F(MasterLexerTest, getNextTokenQString) {
    ss << "\"quoted-string\"\n";
    ss << "\n";
    ss << "normal-string";
    lexer.pushSource(ss);

    // Expecting a quoted string and get one.
    EXPECT_EQ("quoted-string",
              lexer.getNextToken(MasterToken::QSTRING).getString());
    eolCheck(lexer, MasterToken::QSTRING);

    // Expecting a quoted string but see a normal string.  It's okay.
    EXPECT_EQ("normal-string",
              lexer.getNextToken(MasterToken::QSTRING).getString());
    eofCheck(lexer, MasterToken::QSTRING);
}

TEST_F(MasterLexerTest, getNextTokenNumber) {
    ss << "3600\n";
    ss << "\n";
    ss << "4294967296 ";        // =2^32, out of range
    ss << "not-a-number ";
    ss << "123abc "; // starting with digits, but resulting in a string
    ss << "86400";
    lexer.pushSource(ss);

    // Expecting a number string and get one.
    EXPECT_EQ(3600,
              lexer.getNextToken(MasterToken::NUMBER).getNumber());
    eolCheck(lexer, MasterToken::NUMBER);

    // Expecting a number, but it's too big for uint32.
    lexerErrorCheck(lexer, MasterToken::NUMBER,
                    MasterToken::NUMBER_OUT_OF_RANGE);
    // The token should have been "ungotten".  Re-read and skip it.
    EXPECT_EQ(MasterToken::STRING, lexer.getNextToken().getType());

    // Expecting a number, but see a string.
    lexerErrorCheck(lexer, MasterToken::NUMBER, MasterToken::BAD_NUMBER);
    // The unexpected string should have been "ungotten".  Re-read and skip it.
    EXPECT_EQ(MasterToken::STRING, lexer.getNextToken().getType());

    // Expecting a number, but see a string.
    lexerErrorCheck(lexer, MasterToken::NUMBER, MasterToken::BAD_NUMBER);
    // The unexpected string should have been "ungotten".  Re-read and skip it.
    EXPECT_EQ(MasterToken::STRING, lexer.getNextToken().getType());

    // Unless we specify NUMBER, decimal number string should be recognized
    // as a string.
    EXPECT_EQ("86400",
              lexer.getNextToken(MasterToken::STRING).getString());
    eofCheck(lexer, MasterToken::NUMBER);
}

TEST_F(MasterLexerTest, getNextTokenErrors) {
    // Check miscellaneous error cases

    ss << ") ";                 // unbalanced parenthesis
    ss << "string-after-error ";
    lexer.pushSource(ss);

    // Only string/qstring/number can be "expected".
    EXPECT_THROW(lexer.getNextToken(MasterToken::END_OF_LINE),
                 isc::InvalidParameter);
    EXPECT_THROW(lexer.getNextToken(MasterToken::END_OF_FILE),
                 isc::InvalidParameter);
    EXPECT_THROW(lexer.getNextToken(MasterToken::INITIAL_WS),
                 isc::InvalidParameter);
    EXPECT_THROW(lexer.getNextToken(MasterToken::ERROR),
                 isc::InvalidParameter);

    // If it encounters a syntax error, it results in LexerError exception.
    lexerErrorCheck(lexer, MasterToken::STRING, MasterToken::UNBALANCED_PAREN);

    // Unlike the NUMBER_OUT_OF_RANGE case, the error part has been skipped
    // within getNextToken().  We should be able to get the next token.
    EXPECT_EQ("string-after-error",
              lexer.getNextToken(MasterToken::STRING).getString());
}

}
