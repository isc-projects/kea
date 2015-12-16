// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dns/master_lexer.h>
#include <dns/master_lexer_inputsource.h>
#include <dns/master_lexer_state.h>

#include <gtest/gtest.h>

#include <sstream>

using namespace isc::dns;
using namespace master_lexer_internal;

namespace {
typedef MasterToken Token; // shortcut

class MasterLexerStateTest : public ::testing::Test {
protected:
    MasterLexerStateTest() : common_options(MasterLexer::INITIAL_WS),
                             s_null(NULL),
                             s_crlf(State::getInstance(State::CRLF)),
                             s_string(State::getInstance(State::String)),
                             s_qstring(State::getInstance(State::QString)),
                             s_number(State::getInstance(State::Number)),
                             options(MasterLexer::NONE),
                             orig_options(options)
    {}

    // Specify INITIAL_WS as common initial options.
    const MasterLexer::Options common_options;
    MasterLexer lexer;
    const State* const s_null;
    const State& s_crlf;
    const State& s_string;
    const State& s_qstring;
    const State& s_number;
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
    lexer.pushSource(ss);
    EXPECT_EQ(s_null, State::start(lexer, common_options));
    eofCheck(s_crlf, lexer);
}

TEST_F(MasterLexerStateTest, startToEOL) {
    ss << "\n";
    lexer.pushSource(ss);

    EXPECT_EQ(s_null, State::start(lexer, common_options));
    EXPECT_TRUE(s_crlf.wasLastEOL(lexer));
    EXPECT_EQ(Token::END_OF_LINE, s_crlf.getToken(lexer).getType());

    // The next lexer session will reach EOF.  Same eof check should pass.
    EXPECT_EQ(s_null, State::start(lexer, common_options));
    eofCheck(s_crlf, lexer);
}

TEST_F(MasterLexerStateTest, space) {
    // repeat '\t\n' twice (see below), then space after EOL
    ss << " \t\n\t\n ";
    lexer.pushSource(ss);

    // by default space characters and tabs will be ignored.  We check this
    // twice; at the second iteration, it's a white space at the beginning
    // of line, but since we don't specify INITIAL_WS option, it's treated as
    // normal space and ignored.
    for (size_t i = 0; i < 2; ++i) {
        EXPECT_EQ(s_null, State::start(lexer, MasterLexer::NONE));
        EXPECT_TRUE(s_crlf.wasLastEOL(lexer));
        EXPECT_EQ(Token::END_OF_LINE, s_crlf.getToken(lexer).getType());
    }

    // Now we specify the INITIAL_WS option.  It will be recognized and the
    // corresponding token will be returned.
    EXPECT_EQ(s_null, State::start(lexer, MasterLexer::INITIAL_WS));
    EXPECT_FALSE(s_crlf.wasLastEOL(lexer));
    EXPECT_EQ(Token::INITIAL_WS, s_crlf.getToken(lexer).getType());
}

TEST_F(MasterLexerStateTest, parentheses) {
    ss << "\n(\na\n )\n "; // 1st \n is to check if 'was EOL' is set to false
    lexer.pushSource(ss);

    EXPECT_EQ(s_null, State::start(lexer, common_options)); // handle \n

    // Now handle '('.  It skips \n and recognize 'a' as string
    EXPECT_EQ(0, s_crlf.getParenCount(lexer)); // check pre condition
    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    EXPECT_EQ(1, s_crlf.getParenCount(lexer)); // check post condition
    EXPECT_FALSE(s_crlf.wasLastEOL(lexer));

    // skip 'a'
    s_string.handle(lexer);

    // Then handle ')'.  '\n' before ')' isn't recognized because
    // it's canceled due to the '('.  Likewise, the space after the '\n'
    // shouldn't be recognized but should be just ignored.
    EXPECT_EQ(s_null, State::start(lexer, common_options));
    EXPECT_EQ(0, s_crlf.getParenCount(lexer));

    // Now, temporarily disabled options are restored: Both EOL and the
    // initial WS are recognized
    EXPECT_EQ(Token::END_OF_LINE, s_crlf.getToken(lexer).getType());
    EXPECT_EQ(s_null, State::start(lexer, common_options));
    EXPECT_EQ(Token::INITIAL_WS, s_crlf.getToken(lexer).getType());
}

TEST_F(MasterLexerStateTest, nestedParentheses) {
    // This is an unusual, but allowed (in this implementation) case.
    ss << "(a(b)\n c)\n ";
    lexer.pushSource(ss);

    EXPECT_EQ(&s_string, State::start(lexer, common_options)); // consume '('
    s_string.handle(lexer);                      // consume 'a'
    EXPECT_EQ(&s_string, State::start(lexer, common_options)); // consume '('
    s_string.handle(lexer);                     // consume 'b'
    EXPECT_EQ(2, s_crlf.getParenCount(lexer)); // now the count is 2

    // Close the inner most parentheses.  count will be decreased, but option
    // shouldn't be restored yet, so the intermediate EOL or initial WS won't
    // be recognized.
    EXPECT_EQ(&s_string, State::start(lexer, common_options)); // consume ')'
    s_string.handle(lexer);                      // consume 'c'
    EXPECT_EQ(1, s_crlf.getParenCount(lexer));

    // Close the outermost parentheses.  count will be reset to 0, and original
    // options are restored.
    EXPECT_EQ(s_null, State::start(lexer, common_options));

    // Now, temporarily disabled options are restored: Both EOL and the
    // initial WS are recognized
    EXPECT_EQ(Token::END_OF_LINE, s_crlf.getToken(lexer).getType());
    EXPECT_EQ(s_null, State::start(lexer, common_options));
    EXPECT_EQ(Token::INITIAL_WS, s_crlf.getToken(lexer).getType());
}

TEST_F(MasterLexerStateTest, unbalancedParentheses) {
    // Only closing paren is provided.  We prepend a \n to check if it's
    // correctly canceled after detecting the error.
    ss << "\n)";
    ss << "(a";
    lexer.pushSource(ss);

    EXPECT_EQ(s_null, State::start(lexer, common_options)); // consume '\n'
    EXPECT_TRUE(s_crlf.wasLastEOL(lexer)); // this \n was remembered

    // Now checking ')'.  The result should be error, count shouldn't be
    // changed.  "last EOL" should be canceled.
    EXPECT_EQ(0, s_crlf.getParenCount(lexer));
    EXPECT_EQ(s_null, State::start(lexer, common_options));
    EXPECT_EQ(0, s_crlf.getParenCount(lexer));
    ASSERT_EQ(Token::ERROR, s_crlf.getToken(lexer).getType());
    EXPECT_EQ(Token::UNBALANCED_PAREN, s_crlf.getToken(lexer).getErrorCode());
    EXPECT_FALSE(s_crlf.wasLastEOL(lexer));

    // Reach EOF with a dangling open parenthesis.
    EXPECT_EQ(&s_string, State::start(lexer, common_options)); // consume '('
    s_string.handle(lexer);                      // consume 'a'
    EXPECT_EQ(1, s_crlf.getParenCount(lexer));
    EXPECT_EQ(s_null, State::start(lexer, common_options));    // reach EOF
    ASSERT_EQ(Token::ERROR, s_crlf.getToken(lexer).getType());
    EXPECT_EQ(Token::UNBALANCED_PAREN, s_crlf.getToken(lexer).getErrorCode());
    EXPECT_EQ(0, s_crlf.getParenCount(lexer)); // should be reset to 0
}

TEST_F(MasterLexerStateTest, startToComment) {
    // Begin with 'start', detect space, then encounter a comment.  Skip
    // the rest of the line, and recognize the new line.  Note that the
    // second ';' is simply ignored.
    ss << "  ;a;\n";
    ss << ";a;";           // Likewise, but the comment ends with EOF.
    lexer.pushSource(ss);

    // Initial whitespace (asked for in common_options)
    EXPECT_EQ(s_null, State::start(lexer, common_options));
    EXPECT_EQ(Token::INITIAL_WS, s_crlf.getToken(lexer).getType());
    // Comment ending with EOL
    EXPECT_EQ(s_null, State::start(lexer, common_options));
    EXPECT_EQ(Token::END_OF_LINE, s_crlf.getToken(lexer).getType());

    // Comment ending with EOF
    EXPECT_EQ(s_null, State::start(lexer, common_options));
    EXPECT_EQ(Token::END_OF_FILE, s_crlf.getToken(lexer).getType());
}

TEST_F(MasterLexerStateTest, commentAfterParen) {
    // comment after an opening parenthesis.  The code that is tested by
    // other tests should also ensure that it works correctly, but we
    // check it explicitly.
    ss << "( ;this is a comment\na)\n";
    lexer.pushSource(ss);

    // consume '(', skip comments, consume 'a', then consume ')'
    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer);
    EXPECT_EQ(s_null, State::start(lexer, common_options));
    EXPECT_EQ(Token::END_OF_LINE, s_crlf.getToken(lexer).getType());
}

TEST_F(MasterLexerStateTest, crlf) {
    ss << "\r\n";               // case 1
    ss << "\r ";                // case 2
    ss << "\r;comment\na";      // case 3
    ss << "\r";                 // case 4
    lexer.pushSource(ss);

    // 1. A sequence of \r, \n is recognized as a single 'end-of-line'
    EXPECT_EQ(&s_crlf, State::start(lexer, common_options)); // recognize '\r'
    s_crlf.handle(lexer);   // recognize '\n'
    EXPECT_EQ(Token::END_OF_LINE, s_crlf.getToken(lexer).getType());
    EXPECT_TRUE(s_crlf.wasLastEOL(lexer));

    // 2. Single '\r' (not followed by \n) is recognized as a single
    // 'end-of-line'.  then there will be "initial WS"
    EXPECT_EQ(&s_crlf, State::start(lexer, common_options)); // recognize '\r'
    // see ' ', "unget" it
    s_crlf.handle(lexer);
    EXPECT_EQ(s_null, State::start(lexer, common_options)); // recognize ' '
    EXPECT_EQ(Token::INITIAL_WS, s_crlf.getToken(lexer).getType());

    // 3. comment between \r and \n
    EXPECT_EQ(&s_crlf, State::start(lexer, common_options)); // recognize '\r'
    // skip comments, recognize '\n'
    s_crlf.handle(lexer);
    EXPECT_EQ(Token::END_OF_LINE, s_crlf.getToken(lexer).getType());
    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer); // skip 'a'

    // 4. \r then EOF
    EXPECT_EQ(&s_crlf, State::start(lexer, common_options)); // recognize '\r'
    // see EOF, then "unget" it
    s_crlf.handle(lexer);
    EXPECT_EQ(s_null, State::start(lexer, common_options));  // recognize EOF
    EXPECT_EQ(Token::END_OF_FILE, s_crlf.getToken(lexer).getType());
}

// Commonly used check for string related test cases, checking if the given
// token has expected values.
void
stringTokenCheck(const std::string& expected, const MasterToken& token,
                 bool quoted = false)
{
    EXPECT_EQ(quoted ? Token::QSTRING : Token::STRING, token.getType());
    EXPECT_EQ(expected, token.getString());
    const std::string actual(token.getStringRegion().beg,
                             token.getStringRegion().beg +
                             token.getStringRegion().len);
    EXPECT_EQ(expected, actual);

    // There should be "hidden" nul-terminator after the string data.
    ASSERT_NE(static_cast<const char*>(NULL), token.getStringRegion().beg);
    EXPECT_EQ(0, *(token.getStringRegion().beg + token.getStringRegion().len));
}

TEST_F(MasterLexerStateTest, string) {
    // Check with simple strings followed by separate characters
    ss << "followed-by-EOL\n";
    ss << "followed-by-CR\r";
    ss << "followed-by-space ";
    ss << "followed-by-tab\t";
    ss << "followed-by-comment;this is comment and ignored\n";
    ss << "followed-by-paren(closing)";
    ss << "followed-by-EOF";
    lexer.pushSource(ss);

    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer); // recognize str, see \n
    EXPECT_FALSE(s_string.wasLastEOL(lexer));
    stringTokenCheck("followed-by-EOL", s_string.getToken(lexer));
    EXPECT_EQ(s_null, State::start(lexer, common_options)); // skip \n

    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer); // recognize str, see \r
    stringTokenCheck("followed-by-CR", s_string.getToken(lexer));
    EXPECT_EQ(&s_crlf, State::start(lexer, common_options)); // handle \r...
    s_crlf.handle(lexer); // ...and skip it

    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer); // recognize str, see ' '
    stringTokenCheck("followed-by-space", s_string.getToken(lexer));

    // skip ' ', then recognize the next string
    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer); // recognize str, see \t
    stringTokenCheck("followed-by-tab", s_string.getToken(lexer));

    // skip \t, then recognize the next string
    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer); // recognize str, see comment
    stringTokenCheck("followed-by-comment", s_string.getToken(lexer));
    EXPECT_EQ(s_null, State::start(lexer, common_options)); // skip \n after it

    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer); // recognize str, see '('
    stringTokenCheck("followed-by-paren", s_string.getToken(lexer));
    EXPECT_EQ(&s_string, State::start(lexer, common_options)); // str in ()
    s_string.handle(lexer); // recognize the str, see ')'
    stringTokenCheck("closing", s_string.getToken(lexer));

    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer); // recognize str, see EOF
    stringTokenCheck("followed-by-EOF", s_string.getToken(lexer));
}

TEST_F(MasterLexerStateTest, stringEscape) {
    // some of the separate characters should be considered part of the
    // string if escaped.
    ss << "escaped\\ space ";
    ss << "escaped\\\ttab ";
    ss << "escaped\\(paren ";
    ss << "escaped\\)close ";
    ss << "escaped\\;comment ";
    ss << "escaped\\\\ backslash "; // second '\' shouldn't escape ' '
    lexer.pushSource(ss);

    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer); // recognize str, see ' ' at end
    stringTokenCheck("escaped\\ space", s_string.getToken(lexer));

    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer); // recognize str, see ' ' at end
    stringTokenCheck("escaped\\\ttab", s_string.getToken(lexer));

    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer); // recognize str, see ' ' at end
    stringTokenCheck("escaped\\(paren", s_string.getToken(lexer));

    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer); // recognize str, see ' ' at end
    stringTokenCheck("escaped\\)close", s_string.getToken(lexer));

    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer); // recognize str, see ' ' at end
    stringTokenCheck("escaped\\;comment", s_string.getToken(lexer));

    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer); // recognize str, see ' ' in mid
    stringTokenCheck("escaped\\\\", s_string.getToken(lexer));

    // Confirm the word that follows the escaped '\' is correctly recognized.
    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer); // recognize str, see ' ' at end
    stringTokenCheck("backslash", s_string.getToken(lexer));
}

TEST_F(MasterLexerStateTest, quotedString) {
    ss << "\"ignore-quotes\"\n";
    ss << "\"quoted string\" "; // space is part of the qstring
    ss << "\"\" "; // empty quoted string
    // also check other separator characters. note that \r doesn't cause
    // UNBALANCED_QUOTES.  Not sure if it's intentional, but that's how the
    // BIND 9 version works, so we follow it (it should be too minor to matter
    // in practice anyway)
    ss << "\"quoted()\t\rstring\" ";
    ss << "\"escape\\ in quote\" ";
    ss << "\"escaped\\\"\" ";
    ss << "\"escaped backslash\\\\\" ";
    ss << "\"no;comment\"";
    lexer.pushSource(ss);

    // by default, '"' is unexpected (when QSTRING is not specified),
    // and it returns MasterToken::UNEXPECTED_QUOTES.
    EXPECT_EQ(s_null, State::start(lexer, common_options));
    EXPECT_EQ(Token::UNEXPECTED_QUOTES, s_string.getToken(lexer).getErrorCode());
    // Read it as a QSTRING.
    s_qstring.handle(lexer); // recognize quoted str, see \n
    stringTokenCheck("ignore-quotes", s_qstring.getToken(lexer), true);
    EXPECT_EQ(s_null, State::start(lexer, common_options)); // skip \n after it
    EXPECT_TRUE(s_string.wasLastEOL(lexer));

    // If QSTRING is specified in option, '"' is regarded as a beginning of
    // a quoted string.
    const MasterLexer::Options options = common_options | MasterLexer::QSTRING;
    EXPECT_EQ(&s_qstring, State::start(lexer, options));
    EXPECT_FALSE(s_string.wasLastEOL(lexer)); // EOL is canceled due to '"'
    s_qstring.handle(lexer);
    stringTokenCheck("quoted string", s_string.getToken(lexer), true);

    // Empty string is okay as qstring
    EXPECT_EQ(&s_qstring, State::start(lexer, options));
    s_qstring.handle(lexer);
    stringTokenCheck("", s_string.getToken(lexer), true);

    // Also checks other separator characters within a qstring
    EXPECT_EQ(&s_qstring, State::start(lexer, options));
    s_qstring.handle(lexer);
    stringTokenCheck("quoted()\t\rstring", s_string.getToken(lexer), true);

    // escape character mostly doesn't have any effect in the qstring
    // processing
    EXPECT_EQ(&s_qstring, State::start(lexer, options));
    s_qstring.handle(lexer);
    stringTokenCheck("escape\\ in quote", s_string.getToken(lexer), true);

    // The only exception is the quotation mark itself.  Note that the escape
    // only works on the quotation mark immediately after it.
    EXPECT_EQ(&s_qstring, State::start(lexer, options));
    s_qstring.handle(lexer);
    stringTokenCheck("escaped\"", s_string.getToken(lexer), true);

    // quoted '\' then '"'.  Unlike the previous case '"' shouldn't be
    // escaped.
    EXPECT_EQ(&s_qstring, State::start(lexer, options));
    s_qstring.handle(lexer);
    stringTokenCheck("escaped backslash\\\\", s_string.getToken(lexer), true);

    // ';' has no meaning in a quoted string (not indicating a comment)
    EXPECT_EQ(&s_qstring, State::start(lexer, options));
    s_qstring.handle(lexer);
    stringTokenCheck("no;comment", s_string.getToken(lexer), true);
}

TEST_F(MasterLexerStateTest, brokenQuotedString) {
    ss << "\"unbalanced-quote\n";
    ss << "\"quoted\\\n\" ";
    ss << "\"unclosed quote and EOF";
    lexer.pushSource(ss);

    // EOL is encountered without closing the quote
    const MasterLexer::Options options = common_options | MasterLexer::QSTRING;
    EXPECT_EQ(&s_qstring, State::start(lexer, options));
    s_qstring.handle(lexer);
    ASSERT_EQ(Token::ERROR, s_qstring.getToken(lexer).getType());
    EXPECT_EQ(Token::UNBALANCED_QUOTES,
              s_qstring.getToken(lexer).getErrorCode());
    // We can resume after the error from the '\n'
    EXPECT_EQ(s_null, State::start(lexer, options));
    EXPECT_EQ(Token::END_OF_LINE, s_crlf.getToken(lexer).getType());

    // \n is okay in a quoted string if escaped
    EXPECT_EQ(&s_qstring, State::start(lexer, options));
    s_qstring.handle(lexer);
    stringTokenCheck("quoted\\\n", s_string.getToken(lexer), true);

    // EOF is encountered without closing the quote
    EXPECT_EQ(&s_qstring, State::start(lexer, options));
    s_qstring.handle(lexer);
    ASSERT_EQ(Token::ERROR, s_qstring.getToken(lexer).getType());
    EXPECT_EQ(Token::UNEXPECTED_END, s_qstring.getToken(lexer).getErrorCode());
    // If we continue we'll simply see the EOF
    EXPECT_EQ(s_null, State::start(lexer, options));
    EXPECT_EQ(Token::END_OF_FILE, s_crlf.getToken(lexer).getType());
}

TEST_F(MasterLexerStateTest, basicNumbers) {
    ss << "0 ";
    ss << "1 ";
    ss << "12345 ";
    ss << "4294967295 "; // 2^32-1
    ss << "4294967296 "; // Out of range
    ss << "340282366920938463463374607431768211456 ";
                         // Very much out of range (2^128)
    ss << "005 ";        // Leading zeroes are ignored
    ss << "42;asdf\n";   // Number with comment
    ss << "37";          // Simple number again, here to make
                         // sure none of the above messed up
                         // the tokenizer
    lexer.pushSource(ss);

    // Ask the lexer to recognize numbers as well
    const MasterLexer::Options options = common_options | MasterLexer::NUMBER;

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer);
    EXPECT_EQ(0, s_number.getToken(lexer).getNumber());

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer);
    EXPECT_EQ(1, s_number.getToken(lexer).getNumber());

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer);
    EXPECT_EQ(12345, s_number.getToken(lexer).getNumber());

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer);
    EXPECT_EQ(4294967295u, s_number.getToken(lexer).getNumber());

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer);
    EXPECT_EQ(Token::NUMBER_OUT_OF_RANGE,
              s_number.getToken(lexer).getErrorCode());

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer);
    EXPECT_EQ(Token::NUMBER_OUT_OF_RANGE,
              s_number.getToken(lexer).getErrorCode());

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer);
    EXPECT_EQ(5, s_number.getToken(lexer).getNumber());

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer);
    EXPECT_EQ(42, s_number.getToken(lexer).getNumber());

    EXPECT_EQ(s_null, State::start(lexer, options));
    EXPECT_TRUE(s_crlf.wasLastEOL(lexer));
    EXPECT_EQ(Token::END_OF_LINE, s_crlf.getToken(lexer).getType());

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer);
    EXPECT_EQ(37, s_number.getToken(lexer).getNumber());

    // If we continue we'll simply see the EOF
    EXPECT_EQ(s_null, State::start(lexer, options));
    EXPECT_EQ(Token::END_OF_FILE, s_crlf.getToken(lexer).getType());
}

// Test tokens that look like (or start out as) numbers,
// but turn out to be strings. Tests include escaped characters.
TEST_F(MasterLexerStateTest, stringNumbers) {
    ss << "123 ";        // Should be read as a string if the
                         // NUMBER option is not given
    ss << "-1 ";         // Negative numbers are interpreted
                         // as strings (unsigned integers only)
    ss << "123abc456 ";  // 'Numbers' containing non-digits should
                         // be interpreted as strings
    ss << "123\\456 ";   // Numbers containing escaped digits are
                         // interpreted as strings
    ss << "3scaped\\ space ";
    ss << "3scaped\\\ttab ";
    ss << "3scaped\\(paren ";
    ss << "3scaped\\)close ";
    ss << "3scaped\\;comment ";
    ss << "3scaped\\\\ 8ackslash "; // second '\' shouldn't escape ' '

    lexer.pushSource(ss);

    // Note that common_options does not include MasterLexer::NUMBER,
    // so the token should be recognized as a string
    EXPECT_EQ(&s_string, State::start(lexer, common_options));
    s_string.handle(lexer);
    stringTokenCheck("123", s_string.getToken(lexer), false);

    // Ask the lexer to recognize numbers as well
    const MasterLexer::Options options = common_options | MasterLexer::NUMBER;

    EXPECT_EQ(&s_string, State::start(lexer, options));
    s_string.handle(lexer);
    stringTokenCheck("-1", s_string.getToken(lexer), false);

    // Starts out as a number, but ends up being a string
    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer);
    stringTokenCheck("123abc456", s_number.getToken(lexer), false);

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer);
    stringTokenCheck("123\\456", s_number.getToken(lexer), false);

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer); // recognize str, see ' ' at end
    stringTokenCheck("3scaped\\ space", s_number.getToken(lexer));

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer); // recognize str, see ' ' at end
    stringTokenCheck("3scaped\\\ttab", s_number.getToken(lexer));

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer); // recognize str, see ' ' at end
    stringTokenCheck("3scaped\\(paren", s_number.getToken(lexer));

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer); // recognize str, see ' ' at end
    stringTokenCheck("3scaped\\)close", s_number.getToken(lexer));

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer); // recognize str, see ' ' at end
    stringTokenCheck("3scaped\\;comment", s_number.getToken(lexer));

    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer); // recognize str, see ' ' in mid
    stringTokenCheck("3scaped\\\\", s_number.getToken(lexer));

    // Confirm the word that follows the escaped '\' is correctly recognized.
    EXPECT_EQ(&s_number, State::start(lexer, options));
    s_number.handle(lexer); // recognize str, see ' ' at end
    stringTokenCheck("8ackslash", s_number.getToken(lexer));

    // If we continue we'll simply see the EOF
    EXPECT_EQ(s_null, State::start(lexer, options));
    EXPECT_EQ(Token::END_OF_FILE, s_crlf.getToken(lexer).getType());
}

} // end anonymous namespace

