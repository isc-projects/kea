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

#include <dns/master_lexer.h>
#include <dns/master_lexer_inputsource.h>
#include <dns/master_lexer_state.h>

#include <gtest/gtest.h>

#include <sstream>

using namespace isc::dns;
using namespace master_lexer_internal;

namespace {
typedef MasterLexer::Token Token; // shortcut

class MasterLexerStateTest : public ::testing::Test {
protected:
    MasterLexerStateTest() : common_options(MasterLexer::INITIAL_WS),
                             s_null(NULL),
                             s_start(State::getInstance(State::Start)),
                             s_crlf(State::getInstance(State::CRLF)),
                             s_string(State::getInstance(State::String)),
                             options(MasterLexer::NONE),
                             orig_options(options)
    {
        lexer.pushSource(ss);
    }

    // Specify INITIAL_WS as common initial options.
    const MasterLexer::Options common_options;
    MasterLexer lexer;
    const State* const s_null;
    const State& s_start;
    const State& s_crlf;

    const State& s_string;
    std::stringstream ss;
    MasterLexer::Options options, orig_options;
};

// Common check for the end-of-file condition.
// Token is set to END_OF_FILE, and the lexer was NOT last eol state.
// Passed state can be any valid one; they are stateless, just providing the
// interface for inspection.
void
eofCheck(const State& state, MasterLexer& lexer) {
    EXPECT_EQ(Token::END_OF_FILE, state.getToken(lexer).getType());
    EXPECT_FALSE(state.wasLastEOL(lexer));
}

TEST_F(MasterLexerStateTest, startAndEnd) {
    // A simple case: the input is empty, so we begin with start and
    // are immediately done.
    EXPECT_EQ(s_null, s_start.handle(lexer, common_options));
    eofCheck(s_start, lexer);
}

TEST_F(MasterLexerStateTest, startToEOL) {
    ss << "\n";
    EXPECT_EQ(s_null, s_start.handle(lexer, common_options));
    EXPECT_TRUE(s_start.wasLastEOL(lexer));
    EXPECT_EQ(Token::END_OF_LINE, s_start.getToken(lexer).getType());

    // The next lexer session will reach EOF.  Same eof check should pass.
    EXPECT_EQ(s_null, s_start.handle(lexer, common_options));
    eofCheck(s_start, lexer);
}

TEST_F(MasterLexerStateTest, space) {
    // by default space characters and tabs will be ignored.  We check this
    // twice; at the second iteration, it's a white space at the beginning
    // of line, but since we don't specify INITIAL_WS option, it's treated as
    // normal space and ignored.
    for (size_t i = 0; i < 2; ++i) {
        ss << " \t\n";
        EXPECT_EQ(s_null, s_start.handle(lexer, MasterLexer::NONE));
        EXPECT_TRUE(s_start.wasLastEOL(lexer));
        EXPECT_EQ(Token::END_OF_LINE, s_start.getToken(lexer).getType());
    }

    // Now we specify the INITIAL_WS option.  It will be recognized and the
    // corresponding token will be returned.
    ss << " ";
    EXPECT_EQ(s_null, s_start.handle(lexer, MasterLexer::INITIAL_WS));
    EXPECT_FALSE(s_start.wasLastEOL(lexer));
    EXPECT_EQ(Token::INITIAL_WS, s_start.getToken(lexer).getType());
}

TEST_F(MasterLexerStateTest, parentheses) {
    ss << "\n(\na\n )\n "; // 1st \n is to check if 'was EOL' is set to false

    EXPECT_EQ(s_null, s_start.handle(lexer, common_options)); // handle \n

    // Now handle '('.  It skips \n and recognize 'a' as string
    EXPECT_EQ(0, s_start.getParenCount(lexer)); // check pre condition
    EXPECT_EQ(&s_string, s_start.handle(lexer, common_options));
    EXPECT_EQ(1, s_start.getParenCount(lexer)); // check post condition
    EXPECT_FALSE(s_start.wasLastEOL(lexer));

    // skip 'a' (note: until #2373 it's actually skipped as part of the '('
    // handling)
    s_string.handle(lexer, common_options);

    // Then handle ')'.  '\n' before ')' isn't recognized because
    // it's canceled due to the '('.  Likewise, the space after the '\n'
    // shouldn't be recognized but should be just ignored.
    EXPECT_EQ(s_null, s_start.handle(lexer, common_options));
    EXPECT_EQ(0, s_start.getParenCount(lexer));

    // Now, temporarily disabled options are restored: Both EOL and the
    // initial WS are recognized
    EXPECT_EQ(Token::END_OF_LINE, s_start.getToken(lexer).getType());
    EXPECT_EQ(s_null, s_start.handle(lexer, common_options));
    EXPECT_EQ(Token::INITIAL_WS, s_start.getToken(lexer).getType());
}

TEST_F(MasterLexerStateTest, nestedParentheses) {
    // This is an unusual, but allowed (in this implementation) case.
    ss << "(a(b)\n c)\n ";
    EXPECT_EQ(&s_string, s_start.handle(lexer, common_options)); // consume '('
    s_string.handle(lexer, common_options);                      // consume 'a'
    EXPECT_EQ(&s_string, s_start.handle(lexer, common_options)); // consume '('
    s_string.handle(lexer, common_options);                     // consume 'b'
    EXPECT_EQ(2, s_start.getParenCount(lexer)); // now the count is 2

    // Close the inner most parentheses.  count will be decreased, but option
    // shouldn't be restored yet, so the intermediate EOL or initial WS won't
    // be recognized.
    EXPECT_EQ(&s_string, s_start.handle(lexer, common_options)); // consume ')'
    s_string.handle(lexer, common_options);                      // consume 'c'
    EXPECT_EQ(1, s_start.getParenCount(lexer));

    // Close the outermost parentheses.  count will be reset to 0, and original
    // options are restored.
    EXPECT_EQ(s_null, s_start.handle(lexer, common_options));

    // Now, temporarily disabled options are restored: Both EOL and the
    // initial WS are recognized
    EXPECT_EQ(Token::END_OF_LINE, s_start.getToken(lexer).getType());
    EXPECT_EQ(s_null, s_start.handle(lexer, common_options));
    EXPECT_EQ(Token::INITIAL_WS, s_start.getToken(lexer).getType());
}

TEST_F(MasterLexerStateTest, unbalancedParentheses) {
    // Only closing paren is provided.  We prepend a \n to check if it's
    // correctly canceled after detecting the error.
    ss << "\n)";

    EXPECT_EQ(s_null, s_start.handle(lexer, common_options)); // consume '\n'
    EXPECT_TRUE(s_start.wasLastEOL(lexer)); // this \n was remembered

    // Now checking ')'.  The result should be error, count shouldn't be
    // changed.  "last EOL" should be canceled.
    EXPECT_EQ(0, s_start.getParenCount(lexer));
    EXPECT_EQ(s_null, s_start.handle(lexer, common_options));
    EXPECT_EQ(0, s_start.getParenCount(lexer));
    ASSERT_EQ(Token::ERROR, s_start.getToken(lexer).getType());
    EXPECT_EQ(Token::UNBALANCED_PAREN, s_start.getToken(lexer).getErrorCode());
    EXPECT_FALSE(s_start.wasLastEOL(lexer));

    // Reach EOF with a dangling open parenthesis.
    ss << "(a";
    EXPECT_EQ(&s_string, s_start.handle(lexer, common_options)); // consume '('
    s_string.handle(lexer, common_options);                      // consume 'a'
    EXPECT_EQ(1, s_start.getParenCount(lexer));
    EXPECT_EQ(s_null, s_start.handle(lexer, common_options));    // reach EOF
    ASSERT_EQ(Token::ERROR, s_start.getToken(lexer).getType());
    EXPECT_EQ(Token::UNBALANCED_PAREN, s_start.getToken(lexer).getErrorCode());
    EXPECT_EQ(0, s_start.getParenCount(lexer)); // should be reset to 0
}

TEST_F(MasterLexerStateTest, startToComment) {
    // Begin with 'start', skip space, then encounter a comment.  Skip
    // the rest of the line, and recognize the new line.  Note that the
    // second ';' is simply ignored.
    ss << "  ;a;\n";
    EXPECT_EQ(s_null, s_start.handle(lexer, common_options));
    EXPECT_EQ(Token::END_OF_LINE, s_start.getToken(lexer).getType());

    // Likewise, but the comment ends with EOF.
    ss << ";a;";
    EXPECT_EQ(s_null, s_start.handle(lexer, common_options));
    EXPECT_EQ(Token::END_OF_FILE, s_start.getToken(lexer).getType());
}

TEST_F(MasterLexerStateTest, commentAfterParen) {
    // comment after an opening parenthesis.  The code that is tested by
    // other tests should also ensure that it works correctly, but we
    // check it explicitly.
    ss << "( ;this is a comment\na)\n";
    // consume '(', skip comments, consume 'a', then consume ')'
    EXPECT_EQ(&s_string, s_start.handle(lexer, common_options));
    s_string.handle(lexer, common_options);
    EXPECT_EQ(s_null, s_start.handle(lexer, common_options));
    EXPECT_EQ(Token::END_OF_LINE, s_start.getToken(lexer).getType());
}

TEST_F(MasterLexerStateTest, crlf) {
    // A sequence of \r, \n is recognized as a single 'end-of-line'
    ss << "\r\n";
    EXPECT_EQ(&s_crlf, s_start.handle(lexer, common_options)); // recognize '\r'
    EXPECT_EQ(s_null, s_crlf.handle(lexer, common_options));   // recognize '\n'
    EXPECT_EQ(Token::END_OF_LINE, s_start.getToken(lexer).getType());
    EXPECT_TRUE(s_start.wasLastEOL(lexer));

    // Single '\r' (not followed by \n) is recognized as a single 'end-of-line'
    ss << "\r ";                // then there will be "initial WS"
    EXPECT_EQ(&s_crlf, s_start.handle(lexer, common_options)); // recognize '\r'
    // see ' ', "unget" it
    EXPECT_EQ(s_null, s_crlf.handle(lexer, common_options));
    EXPECT_EQ(s_null, s_start.handle(lexer, common_options)); // recognize ' '
    EXPECT_EQ(Token::INITIAL_WS, s_start.getToken(lexer).getType());

    ss << "\r;comment\na";
    EXPECT_EQ(&s_crlf, s_start.handle(lexer, common_options)); // recognize '\r'
    // skip comments, recognize '\n'
    EXPECT_EQ(s_null, s_crlf.handle(lexer, common_options));
    EXPECT_EQ(Token::END_OF_LINE, s_start.getToken(lexer).getType());
    EXPECT_EQ(&s_string, s_start.handle(lexer, common_options));

    // \r then EOF
    ss << "\r";
    EXPECT_EQ(&s_crlf, s_start.handle(lexer, common_options)); // recognize '\r'
    // see EOF, then "unget" it
    EXPECT_EQ(s_null, s_crlf.handle(lexer, common_options));
    EXPECT_EQ(s_null, s_start.handle(lexer, common_options));  // recognize EOF
    EXPECT_EQ(Token::END_OF_FILE, s_start.getToken(lexer).getType());
}

}
