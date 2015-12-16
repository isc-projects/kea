// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option6_status_code.h>
#include <gtest/gtest.h>
#include <cstring>

using namespace isc;
using namespace isc::dhcp;

namespace {

// This test verifies that the option can be created and that the
// accessor methods return correct values used for the object
// construction.
TEST(Option6StatusCodeTest, accessors) {
    Option6StatusCode status1(STATUS_NoAddrsAvail, "Sorry, NoAddrsAvail");
    EXPECT_EQ(STATUS_NoAddrsAvail, status1.getStatusCode());
    EXPECT_EQ("Sorry, NoAddrsAvail", status1.getStatusMessage());

    Option6StatusCode status2(STATUS_NoBinding, "There is NoBinding");
    EXPECT_EQ(STATUS_NoBinding, status2.getStatusCode());
    EXPECT_EQ("There is NoBinding", status2.getStatusMessage());
}

// This test verifies that the status code and status message may
// be modified.
TEST(Option6StatusCodeTest, modifiers) {
    Option6StatusCode status(STATUS_NoAddrsAvail, "Sorry, NoAddrsAvail");
    ASSERT_EQ(STATUS_NoAddrsAvail, status.getStatusCode());
    ASSERT_EQ("Sorry, NoAddrsAvail", status.getStatusMessage());

    ASSERT_NO_THROW(status.setStatusCode(STATUS_Success));
    ASSERT_NO_THROW(status.setStatusMessage("Success"));

    EXPECT_EQ(STATUS_Success, status.getStatusCode());
    EXPECT_EQ("Success", status.getStatusMessage());
}

// This test verifies that the option returns its length correctly.
TEST(Option6StatusCodeTest, length) {
    Option6StatusCode status(STATUS_Success, "");
    EXPECT_EQ(6, status.len());

    ASSERT_NO_THROW(status.setStatusMessage("non-empty message"));
    EXPECT_EQ(23, status.len());
}

// This test verifies that the option can be encoded into the wire
// format.
TEST(Option6StatusCodeTest, pack) {
    Option6StatusCode status(STATUS_NoBinding, "text");
    util::OutputBuffer buf(10);
    ASSERT_NO_THROW(status.pack(buf));

    const uint8_t ref[] = {
        0, 13, // Option code is 13
        0, 6,  // Length is 6
        0, 3,  // NoBinding
        't', 'e', 'x', 't'
    };

    ASSERT_EQ(sizeof(ref), buf.getLength());
    const void* packed = buf.getData();
    EXPECT_EQ(0, memcmp(static_cast<const void*>(ref), packed, sizeof(ref)));
}

// This test verifies that the option can be encoded into the
// wire format when the status message is empty.
TEST(Option6StatusCodeTest, packEmptyStatusMessage) {
    Option6StatusCode status(STATUS_NoAddrsAvail, "");
    util::OutputBuffer buf(10);
    ASSERT_NO_THROW(status.pack(buf));

    const uint8_t ref[] = {
        0, 13, // Option code is 13
        0, 2,  // Length is 2
        0, 2,  // NoAddrsAvail
    };

    ASSERT_EQ(sizeof(ref), buf.getLength());
    const void* packed = buf.getData();
    EXPECT_EQ(0, memcmp(static_cast<const void*>(ref), packed, sizeof(ref)));
}


// This test verifies that the option can be parsed from the wire
// format.
TEST(Option6StatusCodeTest, unpack) {
    const uint8_t wire_data[] = {
        0, 1,          // status code = UnspecFail
        'x', 'y', 'z', // short text: xyz
    };
    OptionBuffer buf(wire_data, wire_data + sizeof(wire_data));

    // Create option from buffer.
    Option6StatusCodePtr status;
    ASSERT_NO_THROW(status.reset(new Option6StatusCode(buf.begin(), buf.end())));

    // Verify that the data was parsed correctly.
    EXPECT_EQ(STATUS_UnspecFail, status->getStatusCode());
    EXPECT_EQ("xyz", status->getStatusMessage());

    // Remove the status message and leave only the status code.
    buf.resize(2);
    // Modify the status code.
    buf[1] = 0;

    ASSERT_NO_THROW(status.reset(new Option6StatusCode(buf.begin(), buf.end())));
    EXPECT_EQ(STATUS_Success, status->getStatusCode());
    EXPECT_TRUE(status->getStatusMessage().empty());
}

// This test verifies that the option data can be presented
// in the textual form.
TEST(Option6StatusCodeTest, dataToText) {
    Option6StatusCode status(STATUS_NoBinding, "Sorry, no binding");
    EXPECT_EQ("NoBinding(3) \"Sorry, no binding\"",
              status.dataToText());
}

// This test verifies that the option can be presented in the
// textual form.
TEST(Option6StatusCodeTest, toText) {
    Option6StatusCode status(STATUS_NoAddrsAvail, "Sorry, no address");
    EXPECT_EQ("type=00013, len=00019: NoAddrsAvail(2) \"Sorry, no address\"",
              status.toText());

    Option6StatusCode status_empty(STATUS_NoBinding, "");
    EXPECT_EQ("type=00013, len=00002: NoBinding(3) (no status message)",
              status_empty.toText());
}


/// @brief Test that the status code name is returned correctly.
///
/// @param expected_name Expected name.
/// @param status_code Status code for which test is performed.
void testStatusName(const std::string& expected_name,
                    const uint16_t status_code) {
    Option6StatusCode status(status_code, "some text");
    EXPECT_EQ(expected_name, status.getStatusCodeName());
}

// This test verifies that the status code name is
// returned correctly.
TEST(Option6StatusCodeTest, getStatusCodeName) {
    testStatusName("Success", STATUS_Success);
    testStatusName("UnspecFail", STATUS_UnspecFail);
    testStatusName("NoAddrsAvail", STATUS_NoAddrsAvail);
    testStatusName("NoBinding", STATUS_NoBinding);
    testStatusName("NotOnLink", STATUS_NotOnLink);
    testStatusName("UseMulticast", STATUS_UseMulticast);
    testStatusName("NoPrefixAvail", STATUS_NoPrefixAvail);
    testStatusName("UnknownQueryType", STATUS_UnknownQueryType);
    testStatusName("MalformedQuery", STATUS_MalformedQuery);
    testStatusName("NotConfigured", STATUS_NotConfigured);
    testStatusName("NotAllowed", STATUS_NotAllowed);
    testStatusName("(unknown status code)", 1234);
}

} // anonymous namespace
