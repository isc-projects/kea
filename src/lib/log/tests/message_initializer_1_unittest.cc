// Copyright (C) 2012,2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <log/message_dictionary.h>
#include <log/message_initializer.h>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>
#include <string>

using namespace isc;
using namespace isc::log;
using namespace std;

// Declare a set of messages to go into the global dictionary.

namespace {
const char* values1[] = {
    "GLOBAL1", "global message one",
    "GLOBAL2", "global message two",
    NULL
};

const char* values2[] = {
    "GLOBAL3", "global message three",
    "GLOBAL4", "global message four",
    NULL
};

const char* values3[] = {
    "GLOBAL7", "global message seven",
    "GLOBAL8", "global message eight",
    NULL
};

const char* values4[] = {
    "GLOBAL8", "global message eight",
    "GLOBAL9", "global message nine",
    NULL
};

/// @brief Scoped pointer to the @c MessageInitializer object.
typedef boost::scoped_ptr<MessageInitializer> MessageInitializerPtr;

}

// Statically initialize the global dictionary with those messages.  Three sets
// are used to check that the declaration of separate initializer objects
// really does combine the messages. (The third set - declaring message IDs
// GLOBAL5 and GLOBAL6) is declared in the separately-compiled file,
// message_identifier_initializer_1a_unittest.cc.)

const MessageInitializer init_message_initializer_unittest_1(values1);
const MessageInitializer init_message_initializer_unittest_2(values2);

// Check that the global dictionary is initialized with the specified
// messages.

TEST(MessageInitializerTest1, messageTest) {
    const MessageDictionaryPtr& global = MessageDictionary::globalDictionary();

    // Pointers to the message arrays should have been stored, but none of the
    // messages should yet be in the dictionary.
    for (int i = 1; i <= 6; ++i) {
        string symbol = string("GLOBAL") + boost::lexical_cast<std::string>(i);
        EXPECT_EQ(string(""), global->getText(symbol));
    }

    // Load the dictionary - this should clear the message array pending count.
    // (N.B. We do not check for a known value before the call, only that the
    // value is not zero.  This is because libraries against which the test
    // is linked may have registered their own message arrays.)
    EXPECT_NE(0, MessageInitializer::getPendingCount());
    MessageInitializer::loadDictionary();
    EXPECT_EQ(0, MessageInitializer::getPendingCount());

    // ... and check the messages loaded.
    EXPECT_EQ(string("global message one"), global->getText("GLOBAL1"));
    EXPECT_EQ(string("global message two"), global->getText("GLOBAL2"));
    EXPECT_EQ(string("global message three"), global->getText("GLOBAL3"));
    EXPECT_EQ(string("global message four"), global->getText("GLOBAL4"));
    EXPECT_EQ(string("global message five"), global->getText("GLOBAL5"));
    EXPECT_EQ(string("global message six"), global->getText("GLOBAL6"));
}

// Check that destroying the MessageInitializer causes the relevant
// messages to be removed from the dictionary.

TEST(MessageInitializerTest1, dynamicLoadUnload) {
    // Obtain the instance of the global dictionary.
    const MessageDictionaryPtr& global = MessageDictionary::globalDictionary();

    // Dynamically create the first initializer.
    MessageInitializerPtr init1(new MessageInitializer(values3));
    EXPECT_EQ(1, MessageInitializer::getPendingCount());

    // Dynamically create the second initializer.
    MessageInitializerPtr init2(new MessageInitializer(values4));
    EXPECT_EQ(2, MessageInitializer::getPendingCount());

    // Load messages from both initializers to the global dictionary.
    MessageInitializer::loadDictionary();
    // There should be no pending messages.
    EXPECT_EQ(0, MessageInitializer::getPendingCount());

    // Make sure that the messages have been loaded.
    EXPECT_EQ("global message seven", global->getText("GLOBAL7"));
    EXPECT_EQ("global message eight", global->getText("GLOBAL8"));
    EXPECT_EQ("global message nine", global->getText("GLOBAL9"));

    // Destroy the first initializer. The first message should be removed.
    // The second message should not be removed because it is also held
    // by another object.
    init1.reset();
    EXPECT_TRUE(global->getText("GLOBAL7").empty());
    EXPECT_EQ("global message eight", global->getText("GLOBAL8"));
    EXPECT_EQ("global message nine", global->getText("GLOBAL9"));

    // Destroy the second initializer. Now, all messages should be
    // unregistered.
    init2.reset();
    EXPECT_TRUE(global->getText("GLOBAL7").empty());
    EXPECT_TRUE(global->getText("GLOBAL8").empty());
    EXPECT_TRUE(global->getText("GLOBAL9").empty());
}

// Check that destroying the MessageInitializer removes pending messages.

TEST(MessageInitializerTest1, dynamicUnloadPending) {
    // Obtain the instance of the global dictionary.
    const MessageDictionaryPtr& global = MessageDictionary::globalDictionary();

    // Dynamically create the first initializer.
    MessageInitializerPtr init1(new MessageInitializer(values3));
    ASSERT_EQ(1, MessageInitializer::getPendingCount());

    // Create second initializer without committing the first set
    // of messages to the dictionary.
    MessageInitializerPtr init2(new MessageInitializer(values4));
    ASSERT_EQ(2, MessageInitializer::getPendingCount());

    // Destroy the first initializer and make sure that the number of
    // pending message sets drops to 1.
    init1.reset();
    ASSERT_EQ(1, MessageInitializer::getPendingCount());

    // Now destroy the second initializer and make sure that there are
    // no pending messages.
    init2.reset();
    ASSERT_EQ(0, MessageInitializer::getPendingCount());

    init1.reset(new MessageInitializer(values3));
    ASSERT_EQ(1, MessageInitializer::getPendingCount());

    // Load the messages to the dictionary and make sure there are no pending
    // messages.
    MessageInitializer::loadDictionary();
    EXPECT_EQ(0, MessageInitializer::getPendingCount());

    // Create the second initializer. There should be one pending set of
    // messages.
    init2.reset(new MessageInitializer(values4));
    ASSERT_EQ(1, MessageInitializer::getPendingCount());

    // Make sure that the messages defined by the first initializer
    // are in the dictionary.
    ASSERT_EQ("global message seven", global->getText("GLOBAL7"));
    ASSERT_EQ("global message eight", global->getText("GLOBAL8"));
    ASSERT_TRUE(global->getText("GLOBAL9").empty());

    // Destroy the second initializer. There should be no pending messages
    // now.
    init2.reset();
    ASSERT_EQ(0, MessageInitializer::getPendingCount());

    // Loading the messages should be no-op.
    MessageInitializer::loadDictionary();
    ASSERT_EQ(0, MessageInitializer::getPendingCount());

    // Make sure that the messages loaded from the first initializer
    // are not affected.
    ASSERT_EQ("global message seven", global->getText("GLOBAL7"));
    ASSERT_EQ("global message eight", global->getText("GLOBAL8"));
    ASSERT_TRUE(global->getText("GLOBAL9").empty());

    // And remove them.
    init1.reset();
    EXPECT_TRUE(global->getText("GLOBAL7").empty());
    EXPECT_TRUE(global->getText("GLOBAL8").empty());
    EXPECT_TRUE(global->getText("GLOBAL9").empty());
}

TEST(MessageInitializerTest1, duplicates) {
    // Original set should not have dupes
    ASSERT_EQ(0, MessageInitializer::getDuplicates().size());

    // This just defines 1, but we'll add it a number of times
    const char* dupe[] = {
        "DUPE", "dupe",
        NULL
    };
    const MessageInitializer init_message_initializer_unittest_1(dupe);
    const MessageInitializer init_message_initializer_unittest_2(dupe);

    MessageInitializer::loadDictionary();
    // Should be a dupe now
    ASSERT_EQ(1, MessageInitializer::getDuplicates().size());

    // clear them
    MessageInitializer::clearDuplicates();
    ASSERT_EQ(0, MessageInitializer::getDuplicates().size());

    // Do it again to make sure, let's explicitly provide false now
    const MessageInitializer init_message_initializer_unittest_3(dupe);
    MessageInitializer::loadDictionary(false);
    ASSERT_EQ(1, MessageInitializer::getDuplicates().size());

    // Loading with ignore_duplicates=true should result in no (reported)
    // dupes
    MessageInitializer::clearDuplicates();
    ASSERT_EQ(0, MessageInitializer::getDuplicates().size());
    const MessageInitializer init_message_initializer_unittest_4(dupe);
    MessageInitializer::loadDictionary(true);
    ASSERT_EQ(0, MessageInitializer::getDuplicates().size());
}
