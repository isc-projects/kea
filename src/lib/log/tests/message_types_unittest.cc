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

#include <gtest/gtest.h>
#include <log/message_types.h>
#include <log/messagedef.h>

using namespace isc::log;

class MessageTypesTest : public ::testing::Test {
public:
    MessageTypesTest()
    {
    }
};

MessageID MessageTypeTest_MSG_DUPLNS();


// Check that the message type equality check works.  This compares
// two message IDs in the "messagedef.h" file declared here, with
// the returned ID (which should be MSG_DUPLNS) declared elsewhere.

TEST_F(MessageTypesTest, EqualID) {
    EXPECT_TRUE(equalMessageID(MSG_DUPLNS, MSG_DUPLNS));
    EXPECT_FALSE(equalMessageID(MSG_DUPLNS, MSG_DUPLPRFX));
    EXPECT_TRUE(equalMessageID(MSG_DUPLNS, MessageTypeTest_MSG_DUPLNS()));
}
