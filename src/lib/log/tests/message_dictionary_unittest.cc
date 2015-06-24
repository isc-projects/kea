// Copyright (C) 2011,2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <cstddef>
#include <string>
#include <gtest/gtest.h>
#include <log/message_dictionary.h>
#include <log/message_initializer.h>
#include <log/message_types.h>

using namespace isc;
using namespace isc::log;
using namespace std;

// set up another message initializer.  This will add a symbol found in the
// logging library and a symbol not found in the logging library.  When the
// global dictionary is loaded, the former should be marked as a duplicate
// and the latter should be present.

namespace {
const char* values[] = {
    // This message for DUPLICATE_NAMESPACE must be copied from
    // ../log_messages.mes; otherwise logger check might fail.
    "LOG_DUPLICATE_NAMESPACE", "line %1: duplicate $NAMESPACE directive found",
    "NEWSYM", "new symbol added",
    NULL
};

MessageInitializer init(values);
}

class MessageDictionaryTest : public ::testing::Test {
protected:
    MessageDictionaryTest() :
        alpha_id("ALPHA"), alpha_text("This is alpha"),
        beta_id("BETA"), beta_text("This is beta"),
        gamma_id("GAMMA"), gamma_text("This is gamma")
    {
    }

    MessageID alpha_id;
    std::string alpha_text;
    MessageID beta_id;
    std::string beta_text;
    MessageID gamma_id;
    std::string gamma_text;

};

// Check that adding messages works

TEST_F(MessageDictionaryTest, Add) {
    MessageDictionary dictionary;
    EXPECT_EQ(0, dictionary.size());

    // Add a few messages and check that we can look them up and that there is
    // nothing in the overflow vector.
    EXPECT_TRUE(dictionary.add(alpha_id, alpha_text));
    EXPECT_TRUE(dictionary.add(beta_id, beta_text));
    EXPECT_EQ(2, dictionary.size());

    EXPECT_EQ(alpha_text, dictionary.getText(alpha_id));
    EXPECT_EQ(beta_text, dictionary.getText(beta_id));
    EXPECT_EQ(string(""), dictionary.getText(gamma_id));

    // Try adding a duplicate with different text.  It should not replace the
    // current text and the ID should be in the overflow section.
    EXPECT_FALSE(dictionary.add(alpha_id, gamma_text));
    EXPECT_EQ(2, dictionary.size());
}

// Check that replacing messages works.

TEST_F(MessageDictionaryTest, Replace) {
    MessageDictionary dictionary;
    EXPECT_EQ(0, dictionary.size());

    // Try to replace a non-existent message
    EXPECT_FALSE(dictionary.replace(alpha_id, alpha_text));
    EXPECT_EQ(0, dictionary.size());

    // Add a couple of messages.
    EXPECT_TRUE(dictionary.add(alpha_id, alpha_text));
    EXPECT_TRUE(dictionary.add(beta_id, beta_text));
    EXPECT_EQ(2, dictionary.size());

    // Replace an existing message
    EXPECT_TRUE(dictionary.replace(alpha_id, gamma_text));
    EXPECT_EQ(2, dictionary.size());
    EXPECT_EQ(gamma_text, dictionary.getText(alpha_id));

    // ... and replace non-existent message (but now the dictionary has some
    // items in it).
    EXPECT_FALSE(dictionary.replace(gamma_id, alpha_text));
    EXPECT_EQ(2, dictionary.size());
    EXPECT_EQ(string(""), dictionary.getText(gamma_id));
}

// Check that removing message works.

TEST_F(MessageDictionaryTest, erase) {
    MessageDictionary dictionary;
    ASSERT_NO_THROW(dictionary.erase(alpha_id, alpha_text));
    ASSERT_EQ(0, dictionary.size());

    // Add a couple of messages.
    EXPECT_TRUE(dictionary.add(alpha_id, alpha_text));
    EXPECT_TRUE(dictionary.add(beta_id, beta_text));
    // There is no sense to continue if messages haven't been added.
    ASSERT_EQ(2, dictionary.size());

    // Remove one with the existing ID, but non-matching text. It
    // should not remove any message.
    EXPECT_FALSE(dictionary.erase(beta_id, alpha_text));

    // Now, remove the message with matching ID and text.
    EXPECT_TRUE(dictionary.erase(beta_id, beta_text));
    EXPECT_EQ(1, dictionary.size());
    // The other entry should still exist.
    EXPECT_EQ(alpha_text, dictionary.getText(alpha_id));

    // And remove the other message.
    EXPECT_TRUE(dictionary.erase(alpha_id, alpha_text));
    EXPECT_EQ(0, dictionary.size());
}

// Load test

TEST_F(MessageDictionaryTest, LoadTest) {
    static const char* data1[] = {
        "ALPHA", "This is alpha",
        "BETA", "This is beta",
        "GAMMA", "This is gamma",
        NULL
    };

    static const char* data2[] = {
        "DELTA", "This is delta",
        "EPSILON", "This is epsilon",
        "ETA", NULL
    };

    MessageDictionary dictionary1;
    EXPECT_EQ(0, dictionary1.size());

    // Load a dictionary1.
    vector<string> duplicates = dictionary1.load(data1);
    EXPECT_EQ(3, dictionary1.size());
    EXPECT_EQ(string(data1[1]), dictionary1.getText(data1[0]));
    EXPECT_EQ(string(data1[3]), dictionary1.getText(data1[2]));
    EXPECT_EQ(string(data1[5]), dictionary1.getText(data1[4]));
    EXPECT_EQ(0, duplicates.size());

    // Attempt an overwrite
    duplicates = dictionary1.load(data1);
    EXPECT_EQ(3, dictionary1.size());
    EXPECT_EQ(3, duplicates.size());

    // Try a new dictionary but with an incorrect number of elements
    MessageDictionary dictionary2;
    EXPECT_EQ(0, dictionary2.size());

    duplicates = dictionary2.load(data2);
    EXPECT_EQ(2, dictionary2.size());
    EXPECT_EQ(string(data2[1]), dictionary2.getText(data2[0]));
    EXPECT_EQ(string(data2[3]), dictionary2.getText(data2[2]));
    EXPECT_EQ(string(""), dictionary2.getText(data2[4]));
    EXPECT_EQ(0, duplicates.size());
}

// Check for some non-existent items

TEST_F(MessageDictionaryTest, Lookups) {
    static const char* data[] = {
        "ALPHA", "This is alpha",
        "BETA", "This is beta",
        "GAMMA", "This is gamma",
        NULL
    };

    MessageDictionary dictionary;
    vector<string> duplicates = dictionary.load(data);
    EXPECT_EQ(3, dictionary.size());
    EXPECT_EQ(0, duplicates.size());

    // Valid lookups
    EXPECT_EQ(string("This is alpha"), dictionary.getText("ALPHA"));
    EXPECT_EQ(string("This is beta"), dictionary.getText("BETA"));
    EXPECT_EQ(string("This is gamma"), dictionary.getText("GAMMA"));

    // ... and invalid ones
    EXPECT_EQ(string(""), dictionary.getText("XYZZY"));
    EXPECT_EQ(string(""), dictionary.getText(""));
    EXPECT_EQ(string(""), dictionary.getText("\n\n\n"));
}

// Check that the global dictionary is a singleton.

TEST_F(MessageDictionaryTest, GlobalTest) {
    const MessageDictionaryPtr& global = MessageDictionary::globalDictionary();
    const MessageDictionaryPtr& global2 = MessageDictionary::globalDictionary();
    EXPECT_TRUE(global2 == global);
}

// Check that the global dictionary has detected the duplicate and the
// new symbol.

TEST_F(MessageDictionaryTest, GlobalLoadTest) {
    // There were duplicates but the vector should be cleared in init() now
    ASSERT_EQ(0, MessageInitializer::getDuplicates().size());

    string text = MessageDictionary::globalDictionary()->getText("NEWSYM");
    EXPECT_EQ(string("new symbol added"), text);
}
