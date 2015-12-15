// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dns/master_lexer_inputsource.h>
#include <dns/master_lexer.h>
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

const char* const test_input =
    "Line1 to scan.\nLine2 to scan.\nLine3 to scan.\n";

class InputSourceTest : public ::testing::Test {
protected:
    InputSourceTest() :
        str_(test_input),
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
        EXPECT_EQ(i + 1, source.getPosition());
        EXPECT_FALSE(source.atEOF());
    }

    // At this point, we still have not reached EOF.
    EXPECT_FALSE(source.atEOF());

    // This should cause EOF to be set.
    EXPECT_EQ(InputSource::END_OF_STREAM, source.getChar());

    // Now, EOF should be set.
    EXPECT_TRUE(source.atEOF());

    // It doesn't increase the position count.
    EXPECT_EQ(str_length, source.getPosition());
    EXPECT_EQ(str_length, source.getSize()); // this should be == getSize().

    // Now, let's go backwards. This should cause the EOF to be set to
    // false.
    source.ungetChar();

    // Now, EOF should be false.
    EXPECT_FALSE(source.atEOF());

    // But the position shouldn't change.
    EXPECT_EQ(str_length, source.getPosition());

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
        EXPECT_EQ(index + 1, source.getPosition());
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
    EXPECT_EQ(0, source_.getPosition());
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

    // compact shouldn't change the position count.
    EXPECT_EQ(source_.getSize(), source_.getPosition());

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

TEST_F(InputSourceTest, getSize) {
    // A simple case using string stream
    EXPECT_EQ(strlen(test_input), source_.getSize());

    // Check it works with an empty input
    istringstream iss("");
    EXPECT_EQ(0, InputSource(iss).getSize());

    // Pretend there's an error in seeking in the stream.  It will be
    // considered a seek specific error, and getSize() returns "unknown".
    iss.setstate(std::ios_base::failbit);
    EXPECT_EQ(MasterLexer::SOURCE_SIZE_UNKNOWN, InputSource(iss).getSize());
    // The fail bit should have been cleared.
    EXPECT_FALSE(iss.fail());

    // Pretend there's a *critical* error in the stream.  The constructor will
    // throw in the attempt of getting the input size.
    iss.setstate(std::ios_base::badbit);
    EXPECT_THROW(InputSource isrc(iss), InputSource::OpenError);

    // Check with input source from file name.  We hardcode the file size
    // for simplicity.  It won't change too often.
    EXPECT_EQ(143, InputSource(TEST_DATA_SRCDIR "/masterload.txt").getSize());
}

TEST_F(InputSourceTest, getPosition) {
    // Initially the position is set to 0.  Other cases are tested in tests
    // for get and unget.
    EXPECT_EQ(0, source_.getPosition());
    EXPECT_EQ(0, InputSource(TEST_DATA_SRCDIR "/masterload.txt").getPosition());
}

} // end namespace
