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
}

TEST_F(MasterLexerTest, preOpen) {
    // Initially sources stack is empty.
    checkEmptySource(lexer);
}

TEST_F(MasterLexerTest, pushStream) {
    lexer.pushSource(ss);
    EXPECT_EQ(expected_stream_name, lexer.getSourceName());

    // From the point of view of this test, we only have to check (though
    // indirectly) getSourceLine calls InputSource::getCurrentLine.  It should
    // return 1 initially.
    EXPECT_EQ(1, lexer.getSourceLine());

    // By popping it the stack will be empty again.
    lexer.popSource();
    checkEmptySource(lexer);
}

TEST_F(MasterLexerTest, pushFile) {
    // We use zone file (-like) data, but in this test that actually doesn't
    // matter.
    EXPECT_TRUE(lexer.pushSource(TEST_DATA_SRCDIR "/masterload.txt"));
    EXPECT_EQ(TEST_DATA_SRCDIR "/masterload.txt", lexer.getSourceName());
    EXPECT_EQ(1, lexer.getSourceLine());

    lexer.popSource();
    checkEmptySource(lexer);

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
    lexer.pushSource(ss);
    EXPECT_EQ(expected_stream_name, lexer.getSourceName());

    // We can push another source without popping the previous one.
    lexer.pushSource(TEST_DATA_SRCDIR "/masterload.txt");
    EXPECT_EQ(TEST_DATA_SRCDIR "/masterload.txt", lexer.getSourceName());

    // popSource() works on the "topmost" (last-pushed) source
    lexer.popSource();
    EXPECT_EQ(expected_stream_name, lexer.getSourceName());

    lexer.popSource();
    EXPECT_TRUE(lexer.getSourceName().empty());
}

TEST_F(MasterLexerTest, invalidPop) {
    // popSource() cannot be called if the sources stack is empty.
    EXPECT_THROW(lexer.popSource(), isc::InvalidOperation);
}

// Test it is not possible to get token when no source is available.
TEST_F(MasterLexerTest, noSource) {
    EXPECT_THROW(lexer.getNextToken(), isc::InvalidOperation);
}

// Test getting some tokens
TEST_F(MasterLexerTest, getNextToken) {
    ss << "\n   \n\"STRING\"\n";
    lexer.pushSource(ss);

    // First, the newline should get out.
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());
    // Then the whitespace, if we specify the option.
    EXPECT_EQ(MasterToken::INITIAL_WS,
              lexer.getNextToken(MasterLexer::INITIAL_WS).getType());
    // The newline
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());
    // The (quoted) string
    EXPECT_EQ(MasterToken::QSTRING,
              lexer.getNextToken(MasterLexer::QSTRING).getType());

    // And the end of line and file
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());
    EXPECT_EQ(MasterToken::END_OF_FILE, lexer.getNextToken().getType());
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
    ss << "(\"string\"";
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

// Test ungetting tokens works
TEST_F(MasterLexerTest, ungetToken) {
    ss << "\n (\"string\"\n) more";
    lexer.pushSource(ss);

    // Try getting the newline
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());
    // Return it and get again
    lexer.ungetToken();
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());
    // Get the string and return it back
    EXPECT_EQ(MasterToken::QSTRING,
              lexer.getNextToken(MasterLexer::QSTRING).getType());
    lexer.ungetToken();
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
    ss << "\n    \n";
    lexer.pushSource(ss);
    // Skip the first newline
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());

    // If we call it the usual way, it skips up to the newline and returns
    // it
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());

    // Now we return it. If we call it again, but with different options,
    // we get the initial whitespace.
    lexer.ungetToken();
    EXPECT_EQ(MasterToken::INITIAL_WS,
              lexer.getNextToken(MasterLexer::INITIAL_WS).getType());
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

// Common checks regarding expected/unexpected end-of-line
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
    bool thrown = false;
    try {
        lexer.getNextToken(expect);
    } catch (const MasterLexer::LexerError& error) {
        EXPECT_EQ(MasterToken::UNEXPECTED_END, error.token_.getErrorCode());
        thrown = true;
    }
    EXPECT_TRUE(thrown);
}

// Common checks regarding expected/unexpected end-of-file
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

    // Skip the 2nd '\n'
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());

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

    // Skip the 2nd '\n'
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());

    // Expecting a quoted string but see a normal string.  It's okay.
    EXPECT_EQ("normal-string",
              lexer.getNextToken(MasterToken::QSTRING).getString());
    eofCheck(lexer, MasterToken::QSTRING);
}

TEST_F(MasterLexerTest, getNextTokenNumber) {
    ss << "3600\n";
    ss << "\n";
    ss << "86400";
    lexer.pushSource(ss);

    // Expecting a number string and get one.
    EXPECT_EQ(3600,
              lexer.getNextToken(MasterToken::NUMBER).getNumber());
    eolCheck(lexer, MasterToken::NUMBER);

    // Skip the 2nd '\n'
    EXPECT_EQ(MasterToken::END_OF_LINE, lexer.getNextToken().getType());

    // Unless we specify NUMBER, decimal number string should be recognized
    // as a string.
    EXPECT_EQ("86400",
              lexer.getNextToken(MasterToken::STRING).getString());
    eofCheck(lexer, MasterToken::NUMBER);
}

}
