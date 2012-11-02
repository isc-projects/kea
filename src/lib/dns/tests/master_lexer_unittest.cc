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

#include <boost/lexical_cast.hpp>

#include <string>
#include <sstream>

using namespace isc::dns;
using std::string;
using std::stringstream;
using boost::lexical_cast;

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

TEST_F(MasterLexerTest, openStream) {
    lexer.pushSource(ss);
    EXPECT_EQ(expected_stream_name, lexer.getSourceName());

    // From the point of view of this test, we only have to check (though
    // indirectly) getSourceLine calls InputSource::getCurrentLine.  It should
    // return 1 initially.
    EXPECT_EQ(1, lexer.getSourceLine());

    // By closing it the stack will be empty again.
    lexer.popSource();
    checkEmptySource(lexer);
}

TEST_F(MasterLexerTest, openFile) {
    // We use zone file (-like) data, but in this test that actually doesn't
    // matter.
    lexer.pushSource(TEST_DATA_SRCDIR "/masterload.txt");
    EXPECT_EQ(TEST_DATA_SRCDIR "/masterload.txt", lexer.getSourceName());
    EXPECT_EQ(1, lexer.getSourceLine());

    lexer.popSource();
    checkEmptySource(lexer);
}

TEST_F(MasterLexerTest, openBadFileName) {
    EXPECT_THROW(lexer.pushSource(NULL), isc::InvalidParameter);
}

TEST_F(MasterLexerTest, nestedOpen) {
    lexer.pushSource(ss);
    EXPECT_EQ(expected_stream_name, lexer.getSourceName());

    // We can open another source without closing the previous one.
    lexer.pushSource(TEST_DATA_SRCDIR "/masterload.txt");
    EXPECT_EQ(TEST_DATA_SRCDIR "/masterload.txt", lexer.getSourceName());

    // Close works on the "topmost" (last-opened) source
    lexer.popSource();
    EXPECT_EQ(expected_stream_name, lexer.getSourceName());

    lexer.popSource();
    EXPECT_TRUE(lexer.getSourceName().empty());
}

TEST_F(MasterLexerTest, invalidClose) {
    // popSource() cannot be called if the sources stack is empty.
    EXPECT_THROW(lexer.popSource(), isc::InvalidOperation);
}

}
