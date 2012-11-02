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

#include <dns/inputsource.h>
#include <dns/master_lexer.h>
#include <dns/master_lexer_state.h>

#include <gtest/gtest.h>

#include <sstream>

using namespace isc::dns;
using namespace master_lexer_internal;

namespace {
typedef MasterLexer::Token Token; // shortcut

class MasterLexerStateTest : public ::testing::Test {
protected:
    MasterLexerStateTest() : s_start(State::getInstance(State::Start)),
                             s_crlf(State::getInstance(State::CRLF)),
                             s_string(State::getInstance(State::String)),
                             options(MasterLexer::END_OF_LINE),
                             orig_options(options)
    {
        lexer.open(ss);
    }
    const State& s_start;
    const State& s_crlf;
    const State& s_string;
    MasterLexer lexer;
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
    const State* s_next = s_start.handle(lexer, options);
    EXPECT_EQ(static_cast<const State*>(NULL), s_next);
    eofCheck(s_start, lexer);
}

TEST_F(MasterLexerStateTest, startToEOL) {
    ss << "\n";
    const State* s_next = s_start.handle(lexer, options);
    EXPECT_EQ(static_cast<const State*>(NULL), s_next);
    EXPECT_TRUE(s_start.wasLastEOL(lexer));
    EXPECT_EQ(Token::END_OF_LINE, s_start.getToken(lexer).getType());

    // The next lexer session will reach EOF.  Same eof check should pass.
    s_start.handle(lexer, options);
    eofCheck(s_start, lexer);

    // TBD: EOL after (
}

TEST_F(MasterLexerStateTest, space) {
    // by default space characters and tabs will be ignored.  We check this
    // twice; at the second iteration, it's a white space at the beginning
    // of line, but since we don't specify INITIAL_WS option, it's treated as
    // normal space and ignored.
    const State* s_next;
    for (size_t i = 0; i < 2; ++i) {
        ss << " \t\n";
        s_next = s_start.handle(lexer, options);
        EXPECT_EQ(static_cast<const State*>(NULL), s_next);
        EXPECT_TRUE(s_start.wasLastEOL(lexer));
        EXPECT_EQ(Token::END_OF_LINE, s_start.getToken(lexer).getType());
    }

    // Now we specify the INITIAL_WS option.  It will be recognized and the
    // corresponding token will be returned.
    ss << " ";
    options = MasterLexer::INITIAL_WS;
    s_next = s_start.handle(lexer, options);
    EXPECT_EQ(static_cast<const State*>(NULL), s_next);
    EXPECT_FALSE(s_start.wasLastEOL(lexer));
    EXPECT_EQ(Token::INITIAL_WS, s_start.getToken(lexer).getType());
}

TEST_F(MasterLexerStateTest, parentheses) {
    ss << "\n(a)";         // add \n to check if 'was EOL' is set to false

    const State* s_next = s_start.handle(lexer, options); // handle \n
    EXPECT_EQ(static_cast<const State*>(NULL), s_next);

    // Now handle '('
    EXPECT_EQ(0, s_start.getParenCount(lexer)); // check pre condition
    options = MasterLexer::END_OF_LINE | MasterLexer::INITIAL_WS;
    s_next = s_start.handle(lexer, options, options);
    EXPECT_EQ(&s_string, s_next); // should recognize 'a' as string

    // Check post '(' conditions.  paren_count should be incremented, and
    // end-of-line and ws should be canceled at the first open paren
    EXPECT_FALSE(s_start.wasLastEOL(lexer));
    EXPECT_TRUE((options & MasterLexer::END_OF_LINE) == 0); // eol is canceled
    EXPECT_TRUE((options & MasterLexer::INITIAL_WS) == 0); // same for init WS
    EXPECT_EQ(1, s_start.getParenCount(lexer));

    // Then handle ')'.  eol and init_ws are kept cleared, and will be set
    // again.
    s_next = s_start.handle(lexer, options, (MasterLexer::END_OF_LINE |
                                             MasterLexer::INITIAL_WS));
    EXPECT_EQ(0, s_start.getParenCount(lexer));
    EXPECT_TRUE((options & MasterLexer::END_OF_LINE) != 0);
    EXPECT_TRUE((options & MasterLexer::INITIAL_WS) != 0);

    // TBD: Test case: '(;'
}

}
