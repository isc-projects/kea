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

// This acts like the normal MasterLexer. It, however, allows to mock the start()
// method to return some given state instead of the auto-detected ones.
class TestedMasterLexer : public MasterLexer {
public:
    TestedMasterLexer() :
        fake_start_(NULL)
    {}
    // During the next call to start(), return the given state instead of the
    // auto-detected one.
    void pushFakeStart(const State* state) {
        fake_start_ = state;
    }
protected:
    virtual const State* start(Options options) {
        if (fake_start_ != NULL) {
            // There's a fake start, so remove it (not to be used next time)
            // and return it.
            const State* result = fake_start_;
            fake_start_ = NULL;
            return (result);
        } else {
            // No fake start ready. So we act the usual way, by delegating it to
            // the parent class.
            return (MasterLexer::start(options));
        }
    }
private:
    const State* fake_start_;
};

class MasterLexerTest : public ::testing::Test {
protected:
    MasterLexerTest() :
        expected_stream_name("stream-" + lexical_cast<string>(&ss))
    {}

    TestedMasterLexer lexer;
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

// Getting a token directly from the start() method.
TEST_F(MasterLexerTest, tokenFromStart) {
    // A class that sets the token directly in start() and returns no
    // state. This is equivalent to the State::start() doing so.
    class StartLexer : public MasterLexer {
    public:
        StartLexer() :
            token_(MasterLexer::Token::END_OF_LINE)
        {}
        virtual const State* start(Options) {
            // We don't have access directly inside the implementation.
            // We get the fake state, run it to install the token.
            // Then we just delete it ourself and return NULL.
            State* state(State::getFakeState(NULL, 0, &token_));
            state->handle(*this);
            delete state;
            return (NULL);
        }
    private:
        MasterLexer::Token token_;
    } lexer;
    lexer.pushSource(ss);

    // The token gets out.
    MasterLexer::Token generated(lexer.getNextToken());
    EXPECT_EQ(MasterLexer::Token::END_OF_LINE, generated.getType());
}

// Getting a token with a single iteration through the states.
TEST_F(MasterLexerTest, simpleGetToken) {
    // Prepare the fake state.
    MasterLexer::Token token(MasterLexer::Token::END_OF_LINE);
    scoped_ptr<State> state(State::getFakeState(NULL, 3, &token));
    lexer.pushFakeStart(state.get());
    // Push some source inside.
    ss << "12345";
    lexer.pushSource(ss);

    // Get the token.
    MasterLexer::Token generated(lexer.getNextToken());
    // It is the same token (well, on a different address)
    // We can't compare directly, so compare types.
    EXPECT_EQ(token.getType(), generated.getType());
    // 3 characters were read from the source.
    // We test by extracting the rest and comparing.
    int rest;
    ss >> rest;
    EXPECT_EQ(45, rest);
}

// A token that takes multiple states.
//
// The first state sets the token as well as the second. The second one should
// survive and be returned.
TEST_F(MasterLexerTest, chainGetToken) {
    // Build the states
    MasterLexer::Token t1(MasterLexer::Token::END_OF_LINE);
    MasterLexer::Token t2(MasterLexer::Token::INITIAL_WS);
    scoped_ptr<State> s2(State::getFakeState(NULL, 1, &t2));
    scoped_ptr<State> s1(State::getFakeState(s2.get(), 2, &t1));
    lexer.pushFakeStart(s1.get());
    // Put something into the source
    ss << "12345";
    lexer.pushSource(ss);

    // Get the token.
    MasterLexer::Token generated(lexer.getNextToken());
    // It is the same token as the second one (well, on a different address)
    // We can't compare directly, so compare types.
    EXPECT_EQ(t2.getType(), generated.getType());
    // 3 characters were read from the source.
    // We test by extracting the rest and comparing.
    int rest;
    ss >> rest;
    EXPECT_EQ(45, rest);
}

// Test getting a token without overriding the start() method (well, it
// is overriden, but no fake state is set, so it refers to the real one).
//
// This also tests the real start() passes the options, otherwise we wouldn't
// get the initial whitespace.
TEST_F(MasterLexerTest, realStart) {
    ss << "\n   \n";
    lexer.pushSource(ss);

    // First, the newline should get out.
    EXPECT_EQ(MasterLexer::Token::END_OF_LINE, lexer.getNextToken().getType());
    // Then the whitespace, if we specify the option.
    EXPECT_EQ(MasterLexer::Token::INITIAL_WS,
              lexer.getNextToken(MasterLexer::INITIAL_WS).getType());
}

// Test we correctly find end of file. Then, upon more attempts to produce
// tokens past the end, it throws.
TEST_F(MasterLexerTest, eof) {
    // Let the ss empty.
    lexer.pushSource(ss);

    // The first one is found to be EOF
    EXPECT_EQ(MasterLexer::Token::END_OF_FILE, lexer.getNextToken().getType());
    // And it is not allowed to use this one any more.
    EXPECT_THROW(lexer.getNextToken(), isc::InvalidOperation);
}

void
checkInput(const std::string& expected, const std::string& received) {
    EXPECT_EQ(expected, received);
}

// Check ungetting a token, which should get to the previous state. We do
// so with changing the state a little bit.
TEST_F(MasterLexerTest, ungetSimple) {
    ss << "12345";
    lexer.pushSource(ss);

    const bool true_value = true, false_value = false;
    // Make sure we change the state to non-default, so we return to previous
    // not default state.
    MasterLexer::Token t0(MasterLexer::Token::INITIAL_WS);
    scoped_ptr<State> s0(State::getFakeState(NULL, 1, &t0, 1, &true_value));
    lexer.pushFakeStart(s0.get());
    EXPECT_EQ(MasterLexer::Token::INITIAL_WS, lexer.getNextToken().getType());

    // Prepare the token to get and return
    const std::string expected = "234";
    MasterLexer::Token token(MasterLexer::Token::END_OF_LINE);
    // Change the internal state with it too. So we can check it is retured.
    scoped_ptr<State> state(State::getFakeState(NULL, 3, &token, 1,
                                                &false_value,
                                                boost::bind(&checkInput,
                                                            expected, _1)));
    lexer.pushFakeStart(state.get());

    // Check the internal state before getting the token
    // We access the lexer through any state, so use the one we have.
    EXPECT_EQ(1, state->getParenCount(lexer));
    EXPECT_TRUE(state->wasLastEOL(lexer));

    // Now get the token and check the state changed
    EXPECT_EQ(MasterLexer::Token::END_OF_LINE, lexer.getNextToken().getType());
    EXPECT_EQ(2, state->getParenCount(lexer));
    EXPECT_FALSE(state->wasLastEOL(lexer));

    // Return the token back. Check the state is as it was before.
    lexer.ungetToken();
    EXPECT_EQ(1, state->getParenCount(lexer));
    EXPECT_TRUE(state->wasLastEOL(lexer));
    // By calling getToken again, we verify even the source got back to
    // original. We must push it as a fake start again so it is picked.
    lexer.pushFakeStart(state.get());
    EXPECT_EQ(MasterLexer::Token::END_OF_LINE, lexer.getNextToken().getType());
    EXPECT_EQ(2, state->getParenCount(lexer));
    EXPECT_FALSE(state->wasLastEOL(lexer));
}

// Check ungetting token without overriding the start method. We also
// check it works well with changing options between the calls.
TEST_F(MasterLexerTest, ungetRealOptions) {
    ss << "\n    \n";
    lexer.pushSource(ss);
    // Skip the first newline
    EXPECT_EQ(MasterLexer::Token::END_OF_LINE, lexer.getNextToken().getType());

    // If we call it the usual way, it skips up to the newline and returns
    // it
    EXPECT_EQ(MasterLexer::Token::END_OF_LINE, lexer.getNextToken().getType());

    // Now we return it. If we call it again, but with different options,
    // we get the initial whitespace.
    lexer.ungetToken();
    EXPECT_EQ(MasterLexer::Token::INITIAL_WS,
              lexer.getNextToken(MasterLexer::INITIAL_WS).getType());
}

// Test only one token can be ungotten
TEST_F(MasterLexerTest, ungetTwice) {
    ss << "\n";
    lexer.pushSource(ss);

    EXPECT_EQ(MasterLexer::Token::END_OF_LINE, lexer.getNextToken().getType());
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
    EXPECT_EQ(MasterLexer::Token::END_OF_LINE, lexer.getNextToken().getType());
    // Switch the source
    std::stringstream ss2;
    ss2 << "\n\n";
    lexer.pushSource(ss2);
    EXPECT_THROW(lexer.ungetToken(), isc::InvalidOperation);
    // We can get from the new source
    EXPECT_EQ(MasterLexer::Token::END_OF_LINE, lexer.getNextToken().getType());
    // And when we drop the current source, we can't unget again
    lexer.popSource();
    EXPECT_THROW(lexer.ungetToken(), isc::InvalidOperation);
}

class TestException {};

void
doThrow(const std::string&) {
    throw TestException();
}

// Check the getNextToken provides at least the weak exception guarantee.
TEST_F(MasterLexerTest, getTokenExceptions) {
    ss << "\n12345";
    lexer.pushSource(ss);

    // Prepare a chain that changes the internal state, reads something.
    // The next item in the chain will throw an exception (we explicitly
    // throw something not known to it, so we know it can handle anything).
    // Then the thing should get to the previous state and getting the
    // token the usual way without mock should work.
    const bool true_value = true;
    boost::scoped_ptr<State> s2(State::getFakeState(NULL, 3, NULL, 0, NULL,
                                                    &doThrow));
    boost::scoped_ptr<State> s1(State::getFakeState(s2.get(), 3, NULL, 1,
                                                    &true_value));
    lexer.pushFakeStart(s1.get());

    // Getting the token with the fake start should throw. But then, the
    // current state should be untouched.
    EXPECT_THROW(lexer.getNextToken(), TestException);
    EXPECT_EQ(0, s1->getParenCount(lexer));
    EXPECT_FALSE(s1->wasLastEOL(lexer));

    // It gets back to the original state, so getting the newline works.
    EXPECT_EQ(MasterLexer::Token::END_OF_LINE, lexer.getNextToken().getType());
}

}
