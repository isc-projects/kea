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
                             options(MasterLexer::NONE)
    {
        lexer.open(ss);
    }
    const State& s_start;
    const State& s_crlf;
    MasterLexer lexer;
    std::stringstream ss;
    MasterLexer::Options options;
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

}
