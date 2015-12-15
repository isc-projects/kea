// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <algorithm>
#include <string>
#include <gtest/gtest.h>

#include <log/log_messages.h>
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
    EXPECT_NO_THROW(reader_.processLine("  A description line"));
    EXPECT_NO_THROW(reader_.processLine("# A comment"));
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

// Check that it recognizes invalid directives

TEST_F(MessageReaderTest, InvalidDirectives) {

    // Check that a "$" with nothing else generates an error
    processLineException(reader_, "$", LOG_UNRECOGNIZED_DIRECTIVE);
    processLineException(reader_, "$xyz", LOG_UNRECOGNIZED_DIRECTIVE);
}

// Check that it can parse a prefix

TEST_F(MessageReaderTest, Prefix) {

    // Check that no $PREFIX is present
    EXPECT_EQ(string(""), reader_.getPrefix());

    // Check that a $PREFIX directive with no argument is OK
    EXPECT_NO_THROW(reader_.processLine("$PREFIX"));

    // Check a $PREFIX with multiple arguments is invalid
    processLineException(reader_, "$prefix A B", LOG_PREFIX_EXTRA_ARGS);

    // Prefixes should be alphanumeric (with underscores) and not start
    // with a number.
    processLineException(reader_, "$prefix ab[cd", LOG_PREFIX_INVALID_ARG);
    processLineException(reader_, "$prefix 123", LOG_PREFIX_INVALID_ARG);
    processLineException(reader_, "$prefix 1ABC", LOG_PREFIX_INVALID_ARG);

    // A valid prefix should be accepted
    EXPECT_NO_THROW(reader_.processLine("$PREFIX   dlm__"));
    EXPECT_EQ(string("dlm__"), reader_.getPrefix());

    // And check that the parser fails on invalid prefixes...
    processLineException(reader_, "$prefix 1ABC", LOG_PREFIX_INVALID_ARG);

    // Check that we can clear the prefix as well
    reader_.clearPrefix();
    EXPECT_EQ(string(""), reader_.getPrefix());

    EXPECT_NO_THROW(reader_.processLine("$PREFIX   dlm__"));
    EXPECT_EQ(string("dlm__"), reader_.getPrefix());
    EXPECT_NO_THROW(reader_.processLine("$PREFIX"));
    EXPECT_EQ(string(""), reader_.getPrefix());
}

// Check that it can parse a namespace

TEST_F(MessageReaderTest, Namespace) {

    // Check that no $NAMESPACE is present
    EXPECT_EQ(string(""), reader_.getNamespace());

    // Check that a $NAMESPACE directive with no argument generates an error.
    processLineException(reader_, "$NAMESPACE", LOG_NAMESPACE_NO_ARGS);

    // Check a $NAMESPACE with multiple arguments is invalid
    processLineException(reader_, "$namespace A B", LOG_NAMESPACE_EXTRA_ARGS);

    // Namespaces should be alphanumeric (with underscores and colons)
    processLineException(reader_, "$namespace ab[cd", LOG_NAMESPACE_INVALID_ARG);

    // A valid $NAMESPACE should be accepted
    EXPECT_NO_THROW(reader_.processLine("$NAMESPACE isc"));
    EXPECT_EQ(string("isc"), reader_.getNamespace());

    // (Check that we can clear the namespace)
    reader_.clearNamespace();
    EXPECT_EQ(string(""), reader_.getNamespace());

    // Check that a valid namespace can include colons
    EXPECT_NO_THROW(reader_.processLine("$NAMESPACE isc::log"));
    EXPECT_EQ(string("isc::log"), reader_.getNamespace());

    // Check that the indication of the anonymous namespace will be recognized.
    reader_.clearNamespace();
    EXPECT_NO_THROW(reader_.processLine("$NAMESPACE ::"));
    EXPECT_EQ(string("::"), reader_.getNamespace());

    // ... and that another $NAMESPACE is rejected
    processLineException(reader_, "$NAMESPACE ABC", LOG_DUPLICATE_NAMESPACE);
}

// Check that it can parse a line

TEST_F(MessageReaderTest, ValidMessageAddDefault) {

    // Add a couple of valid messages
    reader_.processLine("% GLOBAL1\t\tthis is message global one\n");
    reader_.processLine("%GLOBAL2 this is message global two");

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
    reader_.processLine("%GLOBAL1\t\tthis is message global one\n",
        MessageReader::ADD);
    reader_.processLine("% GLOBAL2 this is message global two",
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
    reader_.processLine("% GLOBAL1\t\tthis is message global one\n",
        MessageReader::REPLACE);
    reader_.processLine("% GLOBAL2 this is message global two",
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
    reader_.processLine("% GLOBAL1\t\tthis is message global one\n");
    reader_.processLine("% GLOBAL2 this is message global two");

    // Add a duplicate in ADD mode.
    reader_.processLine("% GLOBAL1\t\tthis is a replacement for global one");

    // Replace a non-existent one in REPLACE mode
    reader_.processLine("% LOCAL\t\tthis is a new message",
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
