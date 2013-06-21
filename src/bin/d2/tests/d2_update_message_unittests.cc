// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <d2/d2_update_message.h>
#include <dns/messagerenderer.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::d2;

namespace {

class D2UpdateMessageTest : public ::testing::Test {
public:
    D2UpdateMessageTest() {
    }

    ~D2UpdateMessageTest() {
    };
};

TEST_F(D2UpdateMessageTest, toWire) {
    D2UpdateMessage msg;
    msg.setQid(0x1234);
    msg.setQRFlag(D2UpdateMessage::REQUEST);
    msg.setRcode(Rcode(Rcode::NOERROR_CODE));
    MessageRenderer renderer;
    ASSERT_NO_THROW(msg.toWire(renderer));
    ASSERT_EQ(12, renderer.getLength());
    InputBuffer buf(renderer.getData(), renderer.getLength());
    EXPECT_EQ(0x1234, buf.readUint16());
    EXPECT_EQ(0x2800, buf.readUint16());
    EXPECT_EQ(0x0, buf.readUint16());
    EXPECT_EQ(0x0, buf.readUint16());
    EXPECT_EQ(0x0, buf.readUint16());
    EXPECT_EQ(0x0, buf.readUint16());
}

} // End of anonymous namespace
