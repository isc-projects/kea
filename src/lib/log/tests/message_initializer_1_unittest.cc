// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>
#include <gtest/gtest.h>
#include <boost/lexical_cast.hpp>
#include <log/message_dictionary.h>
#include <log/message_initializer.h>

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

TEST(MessageInitializerTest1, MessageTest) {
    MessageDictionary& global = MessageDictionary::globalDictionary();

    // Pointers to the message arrays should have been stored, but none of the
    // messages should yet be in the dictionary.
    for (int i = 1; i <= 6; ++i) {
        string symbol = string("GLOBAL") + boost::lexical_cast<std::string>(i);
        EXPECT_EQ(string(""), global.getText(symbol));
    }

    // Load the dictionary - this should clear the message array pending count.
    // (N.B. We do not check for a known value before the call, only that the
    // value is not zero.  This is because libraries against which the test
    // is linked may have registered their own message arrays.)
    EXPECT_NE(0, MessageInitializer::getPendingCount());
    MessageInitializer::loadDictionary();
    EXPECT_EQ(0, MessageInitializer::getPendingCount());

    // ... and check the messages loaded.
    EXPECT_EQ(string("global message one"), global.getText("GLOBAL1"));
    EXPECT_EQ(string("global message two"), global.getText("GLOBAL2"));
    EXPECT_EQ(string("global message three"), global.getText("GLOBAL3"));
    EXPECT_EQ(string("global message four"), global.getText("GLOBAL4"));
    EXPECT_EQ(string("global message five"), global.getText("GLOBAL5"));
    EXPECT_EQ(string("global message six"), global.getText("GLOBAL6"));
}
