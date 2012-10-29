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
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>

#include <string.h>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::master_lexer_internal;

namespace {

class InputSourceTest : public ::testing::Test {
protected:
    InputSourceTest() :
        name_("a90wjer"),
        str_("Line1 to scan.\nLine2 to scan.\nLine3 to scan.\n"),
        str_length_(strlen(str_)),
        iss_(str_),
        source_(iss_, name_)
    {}

    string name_;
    const char* str_;
    size_t str_length_;
    stringstream iss_;
    InputSource source_;
};

// Test the default return values set during InputSource construction.
TEST_F(InputSourceTest, defaults) {
    EXPECT_EQ(name_, source_.getName());
    EXPECT_EQ(1, source_.getCurrentLine());
    EXPECT_FALSE(source_.atEOF());
}

// getChar() should return characters from the input stream in
// sequence. ungetChar() should skip backwards.
TEST_F(InputSourceTest, getAndUngetChar) {
    for (size_t i = 0; i < str_length_; i++) {
        EXPECT_EQ(str_[i], source_.getChar());
        EXPECT_FALSE(source_.atEOF());
    }

    // At this point, we still have not reached EOF.
    EXPECT_FALSE(source_.atEOF());

    // This should cause EOF to be set.
    EXPECT_EQ(-1, source_.getChar());

    // Now, EOF should be set.
    EXPECT_TRUE(source_.atEOF());

    // Now, let's go backwards. This should cause the EOF to be set to
    // false.
    source_.ungetChar();

    // Now, EOF should be false.
    EXPECT_FALSE(source_.atEOF());

    // This should cause EOF to be set again.
    EXPECT_EQ(-1, source_.getChar());

    // Now, EOF should be set.
    EXPECT_TRUE(source_.atEOF());

    // Now, let's go backwards in a loop. Start by skipping the EOF.
    source_.ungetChar();

    for (size_t i = 0; i < str_length_; i++) {
        size_t index = str_length_ - 1 - i;
        // Skip one character.
        source_.ungetChar();
        EXPECT_EQ(str_[index], source_.getChar());
        // Skip the character we received again.
        source_.ungetChar();
    }

    // Skipping past the start of buffer should throw.
    EXPECT_THROW(source_.ungetChar(), isc::OutOfRange);
}

// ungetAll() should skip back to the place where the InputSource
// started at construction, or the last saved start of line.
TEST_F(InputSourceTest, ungetAll) {
    while (!source_.atEOF()) {
        source_.getChar();
    }

    // Now, we are at EOF.
    EXPECT_TRUE(source_.atEOF());
    EXPECT_EQ(4, source_.getCurrentLine());

    source_.ungetAll();

    // Now we are back to where we started.
    EXPECT_EQ(1, source_.getCurrentLine());
    EXPECT_FALSE(source_.atEOF());
}

// Test line counters.
TEST_F(InputSourceTest, lines) {
    size_t line = 1;
    while (!source_.atEOF()) {
        if (source_.getChar() == '\n') {
            line++;
        }
        EXPECT_EQ(line, source_.getCurrentLine());
    }

    // Now, we are at EOF.
    EXPECT_TRUE(source_.atEOF());
    EXPECT_EQ(4, source_.getCurrentLine());

    // Go backwards 2 characters, skipping the last EOF and '\n'.
    source_.ungetChar();
    source_.ungetChar();

    EXPECT_FALSE(source_.atEOF());
    EXPECT_EQ(3, source_.getCurrentLine());

    source_.ungetAll();

    // Now we are back to where we started.
    EXPECT_EQ(1, source_.getCurrentLine());
    EXPECT_FALSE(source_.atEOF());

    // Now check that line numbers are decremented properly (as much as
    // possible using the available API).
    while (!source_.atEOF()) {
        source_.getChar();
    }
    line = source_.getCurrentLine();

    // Now, we are at EOF.
    EXPECT_TRUE(source_.atEOF());
    EXPECT_EQ(4, line);

    EXPECT_THROW({
        while (true) {
            source_.ungetChar();
            EXPECT_TRUE(((line == source_.getCurrentLine()) ||
                         ((line - 1) == source_.getCurrentLine())));
            line = source_.getCurrentLine();
        }
    }, isc::OutOfRange);

    // Now we are back to where we started.
    EXPECT_EQ(1, source_.getCurrentLine());
}

} // end namespace
