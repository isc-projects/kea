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
// are used to check that the declaration of separate initializer objects really// does combine the messages. (The third set is declared in the separately-
// compiled file message_identifier_initializer_unittest_2.cc.)

MessageInitializer init_message_initializer_unittest_1(values1);
MessageInitializer init_message_initializer_unittest_2(values2);


class MessageInitializerTest : public ::testing::Test {
protected:
    MessageInitializerTest()
    {
    }
};


// Check that the global dictionary is initialized with the specified
// messages.

TEST_F(MessageInitializerTest, MessageTest) {
    MessageDictionary* global = MessageDictionary::globalDictionary();

    EXPECT_EQ(string("global message one"), global->getText("GLOBAL1"));
    EXPECT_EQ(string("global message two"), global->getText("GLOBAL2"));
    EXPECT_EQ(string("global message three"), global->getText("GLOBAL3"));
    EXPECT_EQ(string("global message four"), global->getText("GLOBAL4"));
    EXPECT_EQ(string("global message five"), global->getText("GLOBAL5"));
    EXPECT_EQ(string("global message six"), global->getText("GLOBAL6"));
}
