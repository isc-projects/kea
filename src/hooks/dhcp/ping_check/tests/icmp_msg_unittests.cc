// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the ICMPMsg class.

#include <config.h>
#include <icmp_msg.h>
#include <asiolink/io_address.h>
#include <testutils/gtest_utils.h>
#include <util/str.h>

#include <gtest/gtest.h>
#include <list>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::ping_check;

namespace {

// Verifies accessors.
TEST(ICMPMsgTest, basics) {
    ICMPMsgPtr msg(new ICMPMsg());

    msg->setType(ICMPMsg::ECHO_REPLY);
    EXPECT_EQ(ICMPMsg::ECHO_REPLY, msg->getType());

    msg->setCode(77);
    EXPECT_EQ(77, msg->getCode());

    msg->setChecksum(0x8899);
    EXPECT_EQ(0x8899, msg->getChecksum());

    msg->setId(0x1122);
    EXPECT_EQ(0x1122, msg->getId());

    msg->setSequence(0x3344);
    EXPECT_EQ(0x3344, msg->getSequence());

    msg->setSource(IOAddress("192.0.2.1"));
    EXPECT_EQ(IOAddress("192.0.2.1"), msg->getSource());

    msg->setDestination(IOAddress("192.0.2.2"));
    EXPECT_EQ(IOAddress("192.0.2.2"), msg->getDestination());

    std::vector<uint8_t> payload{ 0x55, 0x66, 0x77, 0x88, 0x99 };
    msg->setPayload(payload.data(), payload.size());
    EXPECT_EQ(payload, msg->getPayload());
}

// Verifies that  a valid ECHO REPLY message can be unpacked.
TEST(ICMPMsgTest, unpackValidEchoReply) {
    // Create wire data for a valid ECHO REPLY.
    std::string echo_reply =
        "45:00:00:30:73:8a:00:00:40:01:a0:ff:b2:10:01:19:b2:10:01:0a:"
        "00:00:33:11:55:66:77:88:"
        "00:00:00:00:00:00:00:00:"
        "00:00:00:00:00:00:00:00:"
        "00:00:00:00";

    std::vector<uint8_t> wire_data;
    ASSERT_NO_THROW_LOG(util::str::decodeSeparatedHexString(echo_reply, ":", wire_data));

    // Unpack the wire data.
    ICMPMsgPtr msg;
    ASSERT_NO_THROW_LOG(msg = ICMPMsg::unpack(wire_data.data(), wire_data.size()));
    ASSERT_TRUE(msg);

    // Verify the reply contents.
    EXPECT_EQ(ICMPMsg::ECHO_REPLY, msg->getType());
    EXPECT_EQ(0, msg->getCode());
    EXPECT_EQ(0x3311, msg->getChecksum());
    EXPECT_EQ(0x5566, msg->getId());
    EXPECT_EQ(0x7788, msg->getSequence());
    EXPECT_EQ(IOAddress("178.16.1.25"), msg->getSource());
    EXPECT_EQ(IOAddress("178.16.1.10"), msg->getDestination());

    std::vector<uint8_t> payload{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    EXPECT_EQ(payload, msg->getPayload());
}

// Verifies that a valid DESTINATION UNREACHABLE message can be unpacked.
TEST(ICMPMsgTest, unpackValidUnreachable) {
    // Valid destination unreachable message.  Payload is the original
    // ECHO request.
    std::string unreachable =
        "45:c0:00:4c:31:b3:00:00:40:01:e2:09:b2:10:01:0a:b2:10:01:0a:"
        "03:01:fc:fe:00:00:00:00:"
        "45:00:00:30:e3:e2:40:00:40:01:f0:5c:"
        "b2:10:01:0a:b2:10:01:63:08:00:2b:11:"
        "55:66:77:88:00:00:00:00:00:00:00:00:"
        "00:00:00:00:00:00:00:00:00:00:00:00";

    // Create the wire data.
    std::vector<uint8_t> wire_data;
    ASSERT_NO_THROW_LOG(util::str::decodeSeparatedHexString(unreachable, ":", wire_data));

    // Unpack  the outer message.
    ICMPMsgPtr msg;
    ASSERT_NO_THROW_LOG(msg = ICMPMsg::unpack(wire_data.data(), wire_data.size()));
    ASSERT_TRUE(msg);

    // Verify its contents.
    EXPECT_EQ(ICMPMsg::TARGET_UNREACHABLE, msg->getType());
    EXPECT_EQ(1, msg->getCode());
    EXPECT_EQ(0xfcfe, msg->getChecksum());
    EXPECT_EQ(0, msg->getId());
    EXPECT_EQ(0, msg->getSequence());
    EXPECT_EQ(IOAddress("178.16.1.10"), msg->getSource());
    EXPECT_EQ(IOAddress("178.16.1.10"), msg->getDestination());

    // Now unpack the original ECHO from the outer message payload.
    std::vector<uint8_t> payload(wire_data.begin() + 28, wire_data.end());
    EXPECT_EQ(payload, msg->getPayload());

    ICMPMsgPtr payload_msg;
    ASSERT_NO_THROW_LOG(payload_msg = ICMPMsg::unpack(payload.data(), payload.size()));
    ASSERT_TRUE(payload_msg);

    // Verify the original ECHO contents.
    EXPECT_EQ(ICMPMsg::ECHO_REQUEST, payload_msg->getType());
    EXPECT_EQ(0, payload_msg->getCode());
    EXPECT_EQ(0x2b11, payload_msg->getChecksum());
    EXPECT_EQ(0x5566, payload_msg->getId());
    EXPECT_EQ(0x7788, payload_msg->getSequence());
    EXPECT_EQ(IOAddress("178.16.1.10"), payload_msg->getSource());
    EXPECT_EQ(IOAddress("178.16.1.99"), payload_msg->getDestination());
}

// Verifies the malformed packets are detected.
TEST(ICMPMsgTest, unpackInValidPackets) {
    // Contains a test scenario.
    struct Scenario {
        // Wire data to submit to unpack.
        std::string wire_data_;
        // Expected exception message.
        std::string error_msg_;
    };

    // List of scenarios to test.
    std::list<Scenario> scenarios = {
        {
            // Truncated IP header
            "45:c0:00:4c:31:b3:00:00:40:01:e2:09:b2",
            "ICMPMsg::unpack - truncated ip header, length: 13"
        },
        {
            // Truncated packet
            "45:c0:00:4c:31:b3:00:00:40:01:e2:09:b2:10:01:0a:b2:10:01:0a:"
            "03:01:fc:fe:00:00:00:00:"
            "45:00:00:30:e3:e2:40:00:40:01:f0:5c",
            "ICMPMsg::truncated packet? length: 40, hlen: 20"
        }

    };

    // Iterate over scenarios.
    for (auto const& scenario : scenarios) {
        // Create the wire data.
        std::vector<uint8_t> wire_data;
        ASSERT_NO_THROW_LOG(util::str::decodeSeparatedHexString(scenario.wire_data_, ":", wire_data));
        ASSERT_THROW_MSG(ICMPMsg::unpack(wire_data.data(), wire_data.size()), BadValue, scenario.error_msg_);
    }
}

/// @todo  YOU NEED some round trip tests that test packing!

} // end of anonymous namespace
