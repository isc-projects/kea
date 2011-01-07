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

#include <cstddef>
#include <string>
#include <gtest/gtest.h>
#include <log/message_dictionary.h>
#include <log/message_types.h>

using namespace isc;
using namespace isc::log;
using namespace std;

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


// Check that the global dictionary is a singleton.

TEST_F(MessageDictionaryTest, GlobalTest) {
    MessageDictionary* global = MessageDictionary::globalDictionary();
    EXPECT_FALSE(NULL == global);

    MessageDictionary* global2 = MessageDictionary::globalDictionary();
    EXPECT_EQ(global2, global);
}

// Check that adding messages works

TEST_F(MessageDictionaryTest, Add) {
    MessageDictionary dictionary;
    EXPECT_EQ(0, dictionary.size());

    vector<MessageID> overflow = dictionary.getOverflow();
    EXPECT_EQ(0, overflow.size());

    // Add a few messages and check that we can look them up and that there is
    // nothing in the overflow vector.
    EXPECT_TRUE(dictionary.add(alpha_id, alpha_text));
    EXPECT_TRUE(dictionary.add(beta_id, beta_text));
    EXPECT_EQ(2, dictionary.size());

    overflow = dictionary.getOverflow();
    EXPECT_EQ(0, overflow.size());

    EXPECT_EQ(alpha_text, dictionary.getText(alpha_id));
    EXPECT_EQ(beta_text, dictionary.getText(beta_id));
    EXPECT_EQ(string(""), dictionary.getText(gamma_id));

    // Try adding a duplicate with different text.  It should not replace the
    // current text and the ID should be in the overflow section.
    EXPECT_FALSE(dictionary.add(alpha_id, gamma_text));
    EXPECT_EQ(2, dictionary.size());

    overflow = dictionary.getOverflow();
    ASSERT_EQ(1, overflow.size());
    EXPECT_EQ(alpha_id, overflow[0]);
    EXPECT_EQ(alpha_text, dictionary.getText(alpha_id));
}

// Check that clearing the overflow vector works

TEST_F(MessageDictionaryTest, ClearOverflow) {
    MessageDictionary dictionary;
    EXPECT_EQ(0, dictionary.size());

    vector<MessageID> overflow = dictionary.getOverflow();

    // Add one message twice to get an overflow
    EXPECT_TRUE(dictionary.add(alpha_id, alpha_text));
    EXPECT_FALSE(dictionary.add(alpha_id, alpha_text));
    EXPECT_EQ(1, dictionary.size());

    // Check the overflow
    overflow = dictionary.getOverflow();
    ASSERT_EQ(1, overflow.size());
    EXPECT_EQ(alpha_id, overflow[0]);

    // ... and check that clearing it works
    dictionary.clearOverflow();
    overflow = dictionary.getOverflow();
    ASSERT_EQ(0, overflow.size());
}

// Check that replacing messages works.

TEST_F(MessageDictionaryTest, Replace) {
    MessageDictionary dictionary;
    EXPECT_EQ(0, dictionary.size());

    vector<MessageID> overflow = dictionary.getOverflow();
    EXPECT_EQ(0, overflow.size());

    // Try to replace a non-existent message
    EXPECT_FALSE(dictionary.replace(alpha_id, alpha_text));
    EXPECT_EQ(0, dictionary.size());
    overflow = dictionary.getOverflow();
    ASSERT_EQ(1, overflow.size());
    EXPECT_EQ(alpha_id, overflow[0]);

    // Clear the overflow and add a couple of messages.
    dictionary.clearOverflow();
    overflow = dictionary.getOverflow();
    ASSERT_EQ(0, overflow.size());

    EXPECT_TRUE(dictionary.add(alpha_id, alpha_text));
    EXPECT_TRUE(dictionary.add(beta_id, beta_text));
    EXPECT_EQ(2, dictionary.size());

    // Replace an existing message
    EXPECT_TRUE(dictionary.replace(alpha_id, gamma_text));
    EXPECT_EQ(2, dictionary.size());
    EXPECT_EQ(gamma_text, dictionary.getText(alpha_id));
    overflow = dictionary.getOverflow();
    ASSERT_EQ(0, overflow.size());

    // ... and replace non-existent message (but now the dictionary has some
    // items in it).
    EXPECT_FALSE(dictionary.replace(gamma_id, alpha_text));
    EXPECT_EQ(2, dictionary.size());
    EXPECT_EQ(string(""), dictionary.getText(gamma_id));
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
    dictionary1.load(data1);
    EXPECT_EQ(3, dictionary1.size());
    EXPECT_EQ(string(data1[1]), dictionary1.getText(data1[0]));
    EXPECT_EQ(string(data1[3]), dictionary1.getText(data1[2]));
    EXPECT_EQ(string(data1[5]), dictionary1.getText(data1[4]));
    vector<MessageID> overflow = dictionary1.getOverflow();
    EXPECT_EQ(0, overflow.size());

    // Attempt an overwrite
    dictionary1.load(data1);
    EXPECT_EQ(3, dictionary1.size());
    overflow = dictionary1.getOverflow();
    EXPECT_EQ(3, overflow.size());

    // Try a new dictionary but with an incorrect number of elements
    MessageDictionary dictionary2;
    EXPECT_EQ(0, dictionary2.size());

    dictionary2.load(data2);
    EXPECT_EQ(2, dictionary2.size());
    EXPECT_EQ(string(data2[1]), dictionary2.getText(data2[0]));
    EXPECT_EQ(string(data2[3]), dictionary2.getText(data2[2]));
    EXPECT_EQ(string(""), dictionary2.getText(data2[4]));
}
