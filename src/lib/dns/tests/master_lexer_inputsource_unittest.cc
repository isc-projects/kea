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

#include <dns/master_lexer_inputsource.h>
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
        str_("Line1 to scan.\nLine2 to scan.\nLine3 to scan.\n"),
        str_length_(strlen(str_)),
        iss_(str_),
        source_(iss_)
    {}

    const char* str_;
    const size_t str_length_;
    stringstream iss_;
    InputSource source_;
};

// Test the default return values set during InputSource construction.
TEST_F(InputSourceTest, defaults) {
    EXPECT_EQ(1, source_.getCurrentLine());
    EXPECT_FALSE(source_.atEOF());
}

// getName() on file and stream sources
TEST_F(InputSourceTest, getName) {
    EXPECT_EQ(0, source_.getName().find("stream-"));

    // Use some file; doesn't really matter what.
    InputSource source2(TEST_DATA_SRCDIR "/masterload.txt");
    EXPECT_EQ(TEST_DATA_SRCDIR "/masterload.txt", source2.getName());
}

TEST_F(InputSourceTest, nonExistentFile) {
    EXPECT_THROW({
        InputSource source(TEST_DATA_SRCDIR "/does-not-exist");
    }, InputSource::OpenError);
}

// getChar() should return characters from the input stream in
// sequence. ungetChar() should skip backwards.
void
checkGetAndUngetChar(InputSource& source,
                     const char* str, const size_t str_length)
{
    for (size_t i = 0; i < str_length; ++i) {
        EXPECT_EQ(str[i], source.getChar());
        EXPECT_FALSE(source.atEOF());
    }

    // At this point, we still have not reached EOF.
    EXPECT_FALSE(source.atEOF());

    // This should cause EOF to be set.
    EXPECT_EQ(InputSource::END_OF_STREAM, source.getChar());

    // Now, EOF should be set.
    EXPECT_TRUE(source.atEOF());

    // Now, let's go backwards. This should cause the EOF to be set to
    // false.
    source.ungetChar();

    // Now, EOF should be false.
    EXPECT_FALSE(source.atEOF());

    // This should cause EOF to be set again.
    EXPECT_EQ(InputSource::END_OF_STREAM, source.getChar());

    // Now, EOF should be set.
    EXPECT_TRUE(source.atEOF());

    // Now, let's go backwards in a loop. Start by skipping the EOF.
    source.ungetChar();

    for (size_t i = 0; i < str_length; ++i) {
        const size_t index = str_length - 1 - i;
        // Skip one character.
        source.ungetChar();
        EXPECT_EQ(str[index], source.getChar());
        // Skip the character we received again.
        source.ungetChar();
    }

    // Skipping past the start of buffer should throw.
    EXPECT_THROW(source.ungetChar(), InputSource::UngetBeforeBeginning);
}

TEST_F(InputSourceTest, stream) {
    checkGetAndUngetChar(source_, str_, str_length_);
}

TEST_F(InputSourceTest, file) {
    std::ifstream fs(TEST_DATA_SRCDIR "/masterload.txt");
    const std::string str((std::istreambuf_iterator<char>(fs)),
                          std::istreambuf_iterator<char>());
    fs.close();

    InputSource source(TEST_DATA_SRCDIR "/masterload.txt");
    checkGetAndUngetChar(source, str.c_str(), str.size());
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

TEST_F(InputSourceTest, compact) {
    // Compact at the start
    source_.compact();

    // Ungetting here must throw.
    EXPECT_THROW(source_.ungetChar(), InputSource::UngetBeforeBeginning);

    for (size_t i = 0; i < str_length_; ++i) {
        EXPECT_EQ(str_[i], source_.getChar());
        EXPECT_FALSE(source_.atEOF());
    }

    // At this point, we still have not reached EOF.
    EXPECT_FALSE(source_.atEOF());

    // This should cause EOF to be set.
    EXPECT_EQ(InputSource::END_OF_STREAM, source_.getChar());

    // Now, EOF should be set.
    EXPECT_TRUE(source_.atEOF());
    EXPECT_EQ(4, source_.getCurrentLine());

    // Compact again
    source_.compact();

    // We are still at EOF.
    EXPECT_TRUE(source_.atEOF());
    EXPECT_EQ(4, source_.getCurrentLine());

    // Skip the EOF.
    source_.ungetChar();

    // Ungetting here must throw.
    EXPECT_THROW(source_.ungetChar(), InputSource::UngetBeforeBeginning);

    EXPECT_EQ(InputSource::END_OF_STREAM, source_.getChar());
    EXPECT_TRUE(source_.atEOF());
}

TEST_F(InputSourceTest, markDuring) {
    // First, skip to line 2.
    while (!source_.atEOF() &&
           (source_.getCurrentLine() != 2)) {
        source_.getChar();
    }
    EXPECT_FALSE(source_.atEOF());
    EXPECT_EQ(2, source_.getCurrentLine());

    // Now, unget a couple of characters. This should cause the
    // buffer_pos_ to be not equal to the size of the buffer.
    source_.ungetChar();
    source_.ungetChar();

    // Now "mark" the source, meaning that we save line number and also
    // compact the internal buffer at this stage.
    source_.mark();

    // Ungetting here must throw.
    EXPECT_THROW(source_.ungetChar(), InputSource::UngetBeforeBeginning);

    for (size_t i = 13; i < str_length_; ++i) {
        EXPECT_EQ(str_[i], source_.getChar());
        EXPECT_FALSE(source_.atEOF());
    }

    // At this point, we still have not reached EOF.
    EXPECT_FALSE(source_.atEOF());

    // This should cause EOF to be set.
    EXPECT_EQ(InputSource::END_OF_STREAM, source_.getChar());

    // Now, EOF should be set.
    EXPECT_TRUE(source_.atEOF());

    // Now, ungetAll() and check where it goes back.
    source_.ungetAll();

    // Ungetting here must throw.
    EXPECT_THROW(source_.ungetChar(), InputSource::UngetBeforeBeginning);

    for (size_t i = 13; i < str_length_; ++i) {
        EXPECT_EQ(str_[i], source_.getChar());
        EXPECT_FALSE(source_.atEOF());
    }

    // At this point, we still have not reached EOF.
    EXPECT_FALSE(source_.atEOF());

    // This should cause EOF to be set.
    EXPECT_EQ(InputSource::END_OF_STREAM, source_.getChar());

    // Now, EOF should be set.
    EXPECT_TRUE(source_.atEOF());
}

// Test line counters.
TEST_F(InputSourceTest, lines) {
    size_t line = 1;
    while (!source_.atEOF()) {
        if (source_.getChar() == '\n') {
            ++line;
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
    }, InputSource::UngetBeforeBeginning);

    // Now we are back to where we started.
    EXPECT_EQ(1, source_.getCurrentLine());
}

// ungetAll() after saveLine() should skip back to the last-saved place.
TEST_F(InputSourceTest, saveLine) {
    // First, skip to line 2.
    while (!source_.atEOF() &&
           (source_.getCurrentLine() != 2)) {
        source_.getChar();
    }
    EXPECT_FALSE(source_.atEOF());
    EXPECT_EQ(2, source_.getCurrentLine());

    // Now, save the line.
    source_.saveLine();

    // Now, go to EOF
    while (!source_.atEOF()) {
        source_.getChar();
    }

    // Now, we are at EOF.
    EXPECT_TRUE(source_.atEOF());
    EXPECT_EQ(4, source_.getCurrentLine());

    // Now, ungetAll() and check where it goes back.
    source_.ungetAll();

    // Now we are back to where we last-saved.
    EXPECT_EQ(2, source_.getCurrentLine());
    EXPECT_FALSE(source_.atEOF());
}

} // end namespace
