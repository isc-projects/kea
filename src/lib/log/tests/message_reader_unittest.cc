// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id: base64_unittest.cc 2549 2010-07-20 19:09:37Z jinmei $

#include <string>
#include <gtest/gtest.h>
#include <log/message_reader.h>

using namespace isc;
using namespace isc::log;
using namespace std;

class MessageReaderTest : public ::testing::Test {
protected:
    MessageReaderTest() : reader_()
    {
    }

    MessageReader   reader_;        // Default reader object
};


// Check for a couple of status messages

TEST_F(MessageReaderTest, StatusMessage) {
    string unknown("Unknown message code");     // Default unknown message

    EXPECT_NE(unknown, reader_.errorText(MessageReader::SUCCESS));
    EXPECT_NE(unknown, reader_.errorText(MessageReader::DUPLPRFX));
    EXPECT_NE(unknown, reader_.errorText(MessageReader::PRFXEXTRARG));
    EXPECT_NE(unknown, reader_.errorText(MessageReader::PRFXINVARG));
    EXPECT_NE(unknown, reader_.errorText(MessageReader::PRFXNOARG));
    EXPECT_NE(unknown, reader_.errorText(MessageReader::UNRECDIR));
}

// Check for parsing blank lines and comments.  These should not add to the map and
// each parse should return success.

TEST_F(MessageReaderTest, BlanksAndComments) {

    // Ensure that the map is empty
    MessageReader::MessageMap mmap = reader_.getMessageMap();
    EXPECT_EQ(0, mmap.size());

    MessageReader::MessageDuplicates mduplicates = reader_.getMessageDuplicates();
    EXPECT_EQ(0, mduplicates.size());

    // Add a number of blank lines and comments and check that (a) they are parsed
    // successfully ...
    MessageReader::Status status = reader_.processLine("");
    EXPECT_EQ(MessageReader::SUCCESS, status);
    status = reader_.processLine(" ");
    EXPECT_EQ(MessageReader::SUCCESS, status);
    status = reader_.processLine(" \n ");
    EXPECT_EQ(MessageReader::SUCCESS, status);
    status = reader_.processLine("# This is a comment");
    EXPECT_EQ(MessageReader::SUCCESS, status);
    status = reader_.processLine("\t\t # Another comment");
    EXPECT_EQ(MessageReader::SUCCESS, status);
    status = reader_.processLine("  + A description line");
    EXPECT_EQ(MessageReader::SUCCESS, status);
    status = reader_.processLine("#+ A comment");
    EXPECT_EQ(MessageReader::SUCCESS, status);
    status = reader_.processLine("  +# A description line");
    EXPECT_EQ(MessageReader::SUCCESS, status);

    // ... and (b) nothing gets added to either the map or the duplicates
    mmap = reader_.getMessageMap();
    EXPECT_EQ(0, mmap.size());

    mduplicates = reader_.getMessageDuplicates();
    EXPECT_EQ(0, mduplicates.size());
}

// Check that it can parse a prefix

TEST_F(MessageReaderTest, Prefix) {

    // Check that no prefix is present
    EXPECT_EQ(string(""), reader_.getPrefix());

    // Check that a prefix directive with no argument generates an error.
    EXPECT_EQ(MessageReader::PRFXNOARG, reader_.processLine("$PREFIX"));

    // Check a prefix with multiple arguments is invalid
    EXPECT_EQ(MessageReader::PRFXEXTRARG, reader_.processLine("$prefix A B"));

    // Prefixes should be alphanumeric (with underscores) and not start
    // with a number.
    EXPECT_EQ(MessageReader::PRFXINVARG, reader_.processLine("$prefix ab[cd"));
    EXPECT_EQ(MessageReader::PRFXINVARG, reader_.processLine("$prefix 123"));
    EXPECT_EQ(MessageReader::PRFXINVARG, reader_.processLine("$prefix 1ABC"));

    // A valid prefix should be accepted
    EXPECT_EQ(MessageReader::SUCCESS, reader_.processLine("$PREFIX   dlm__"));
    EXPECT_EQ(string("DLM__"), reader_.getPrefix());

    // And check that the parser fails on invalid prefixes...
    EXPECT_EQ(MessageReader::PRFXINVARG, reader_.processLine("$prefix 1ABC"));

    // ... and rejects another valid one
    EXPECT_EQ(MessageReader::DUPLPRFX, reader_.processLine("$PREFIX ABC"));
}

