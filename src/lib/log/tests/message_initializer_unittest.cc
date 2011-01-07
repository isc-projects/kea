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
const char* values[] = {
    "GLOBAL1", "global message one",
    "GLOBAL2", "global message two",
    NULL
};
}

// Statically initialize the global dictionary with those messages.
MessageInitializer init_message_initializer_unittest(values);



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
    EXPECT_EQ(string(""), global->getText(""));
}
