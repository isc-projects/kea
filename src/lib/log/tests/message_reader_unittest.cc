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

#include <algorithm>
#include <string>
#include <gtest/gtest.h>

#include <log/messagedef.h>
#include <log/message_dictionary.h>
#include <log/message_exception.h>
#include <log/message_reader.h>

using namespace isc;
using namespace isc::log;
using namespace std;

class MessageReaderTest : public ::testing::Test {
protected:
    MessageReaderTest() : dictionary_(), reader_()
    {
        dictionary_ = new MessageDictionary();
        reader_.setDictionary(dictionary_);
    }

    ~MessageReaderTest() {
        delete dictionary_;
    }

    MessageDictionary*  dictionary_;    // Dictionary to add messages to
    MessageReader       reader_;        // Default reader object
};


// Check the get/set dictionary calls (using a local reader and dictionary).

TEST_F(MessageReaderTest, GetSetDictionary) {
    MessageReader reader;
    EXPECT_TRUE(reader.getDictionary() == NULL);

    MessageDictionary dictionary;
    reader.setDictionary(&dictionary);
    EXPECT_EQ(&dictionary, reader.getDictionary());
}

// Check for parsing blank lines and comments.  These should not add to the
// dictionary and each parse should return success.

TEST_F(MessageReaderTest, BlanksAndComments) {

    // Ensure that the dictionary is empty.
    EXPECT_EQ(0, dictionary_->size());

    // Add a number of blank lines and comments and check that (a) they are
    // parsed successfully ...
    EXPECT_NO_THROW(reader_.processLine(""));
    EXPECT_NO_THROW(reader_.processLine(" "));
    EXPECT_NO_THROW(reader_.processLine(" \n "));
    EXPECT_NO_THROW(reader_.processLine("# This is a comment"));
    EXPECT_NO_THROW(reader_.processLine("\t\t # Another comment"));
    EXPECT_NO_THROW(reader_.processLine("  + A description line"));
    EXPECT_NO_THROW(reader_.processLine("#+ A comment"));
    EXPECT_NO_THROW(reader_.processLine("  +# A description line"));

    // ... and (b) nothing gets added to either the map or the not-added section.
    EXPECT_EQ(0, dictionary_->size());
    vector<string> not_added = reader_.getNotAdded();
    EXPECT_EQ(0, not_added.size());
}


// Local test to check that processLine generates the right exception.

void
processLineException(MessageReader& reader, const char* what,
    const MessageID& expected) {

    try {
        reader.processLine(what);
        FAIL() << "MessageReader::processLine() should throw an exception " <<
            " with message ID " << expected << " for '" << what << "'\n";
    } catch (MessageException& e) {
        EXPECT_EQ(boost::lexical_cast<string>(expected),
            boost::lexical_cast<string>(e.id()));
    } catch (...) {
        FAIL() << "Unknown exception thrown by MessageReader::processLine()\n";
    }
}

// Check that it can parse a prefix

TEST_F(MessageReaderTest, Prefix) {

    // Check that no $PREFIX is present
    EXPECT_EQ(string(""), reader_.getPrefix());

    // Check that a $PREFIX directive with no argument generates an error.
    processLineException(reader_, "$PREFIX", MSG_PRFNOARG);

    // Check a $PREFIX with multiple arguments is invalid
    processLineException(reader_, "$prefix A B", MSG_PRFEXTRARG);

    // Prefixes should be alphanumeric (with underscores) and not start
    // with a number.
    processLineException(reader_, "$prefix ab[cd", MSG_PRFINVARG);
    processLineException(reader_, "$prefix 123", MSG_PRFINVARG);
    processLineException(reader_, "$prefix 1ABC", MSG_PRFINVARG);

    // A valid prefix should be accepted
    EXPECT_NO_THROW(reader_.processLine("$PREFIX   dlm__"));
    EXPECT_EQ(string("DLM__"), reader_.getPrefix());

    // And check that the parser fails on invalid prefixes...
    processLineException(reader_, "$prefix 1ABC", MSG_PRFINVARG);

    // ... and rejects another valid one
    processLineException(reader_, "$PREFIX ABC", MSG_DUPLPRFX);

    // Check that we can clear the prefix as well
    reader_.clearPrefix();
    EXPECT_EQ(string(""), reader_.getPrefix());
}

// Check that it can parse a namespace

TEST_F(MessageReaderTest, Namespace) {

    // Check that no $NAMESPACE is present
    EXPECT_EQ(string(""), reader_.getNamespace());

    // Check that a $NAMESPACE directive with no argument generates an error.
    processLineException(reader_, "$NAMESPACE", MSG_NSNOARG);

    // Check a $NAMESPACE with multiple arguments is invalid
    processLineException(reader_, "$namespace A B", MSG_NSEXTRARG);

    // Namespaces should be alphanumeric (with underscores and colons)
    processLineException(reader_, "$namespace ab[cd", MSG_NSINVARG);

    // A valid $NAMESPACE should be accepted
    EXPECT_NO_THROW(reader_.processLine("$NAMESPACE isc"));
    EXPECT_EQ(string("isc"), reader_.getNamespace());

    // (Check that we can clear the namespace)
    reader_.clearNamespace();
    EXPECT_EQ(string(""), reader_.getNamespace());

    // Check that a valid namespace can include colons
    EXPECT_NO_THROW(reader_.processLine("$NAMESPACE isc::log"));
    EXPECT_EQ(string("isc::log"), reader_.getNamespace());

    // Check that the indication of the anonymous namespace will be recognised.
    reader_.clearNamespace();
    EXPECT_NO_THROW(reader_.processLine("$NAMESPACE ::"));
    EXPECT_EQ(string("::"), reader_.getNamespace());

    // ... and that another $NAMESPACE is rejected
    processLineException(reader_, "$NAMESPACE ABC", MSG_DUPLNS);
}

// Check that it can parse a line

TEST_F(MessageReaderTest, ValidMessageAddDefault) {

    // Add a couple of valid messages
    reader_.processLine("GLOBAL1\t\tthis is message global one\n");
    reader_.processLine("GLOBAL2 this is message global two");

    // ... and check them
    EXPECT_EQ(string("this is message global one"),
        dictionary_->getText("GLOBAL1"));
    EXPECT_EQ(string("this is message global two"),
        dictionary_->getText("GLOBAL2"));
    EXPECT_EQ(2, dictionary_->size());

    // ... and ensure no messages were not added
    vector<string> not_added = reader_.getNotAdded();
    EXPECT_EQ(0, not_added.size());
}

TEST_F(MessageReaderTest, ValidMessageAdd) {

    // Add a couple of valid messages
    reader_.processLine("GLOBAL1\t\tthis is message global one\n",
        MessageReader::ADD);
    reader_.processLine("GLOBAL2 this is message global two",
        MessageReader::ADD);

    // ... and check them
    EXPECT_EQ(string("this is message global one"),
        dictionary_->getText("GLOBAL1"));
    EXPECT_EQ(string("this is message global two"),
        dictionary_->getText("GLOBAL2"));
    EXPECT_EQ(2, dictionary_->size());

    // ... and ensure no messages were not added
    vector<string> not_added = reader_.getNotAdded();
    EXPECT_EQ(0, not_added.size());
}

TEST_F(MessageReaderTest, ValidMessageReplace) {

    dictionary_->add("GLOBAL1", "original global1 message");
    dictionary_->add("GLOBAL2", "original global2 message");

    // Replace a couple of valid messages
    reader_.processLine("GLOBAL1\t\tthis is message global one\n",
        MessageReader::REPLACE);
    reader_.processLine("GLOBAL2 this is message global two",
        MessageReader::REPLACE);

    // ... and check them
    EXPECT_EQ(string("this is message global one"),
        dictionary_->getText("GLOBAL1"));
    EXPECT_EQ(string("this is message global two"),
        dictionary_->getText("GLOBAL2"));
    EXPECT_EQ(2, dictionary_->size());

    // ... and ensure no messages were not added
    vector<string> not_added = reader_.getNotAdded();
    EXPECT_EQ(0, not_added.size());
}

// Do checks on overflows, although this essentially duplicates the checks
// in MessageDictionary.

TEST_F(MessageReaderTest, Overflows) {

    // Add a couple of valid messages
    reader_.processLine("GLOBAL1\t\tthis is message global one\n");
    reader_.processLine("GLOBAL2 this is message global two");

    // Add a duplicate in ADD mode.
    reader_.processLine("GLOBAL1\t\tthis is a replacement for global one");

    // Replace a non-existent one in REPLACE mode
    reader_.processLine("LOCAL\t\tthis is a new message",
        MessageReader::REPLACE);

    // Check what is in the dictionary.
    EXPECT_EQ(string("this is message global one"),
        dictionary_->getText("GLOBAL1"));
    EXPECT_EQ(string("this is message global two"),
        dictionary_->getText("GLOBAL2"));
    EXPECT_EQ(2, dictionary_->size());

    // ... and ensure no overflows
    vector<string> not_added = reader_.getNotAdded();
    ASSERT_EQ(2, not_added.size());

    sort(not_added.begin(), not_added.end());
    EXPECT_EQ(string("GLOBAL1"), not_added[0]);
    EXPECT_EQ(string("LOCAL"), not_added[1]);
}
