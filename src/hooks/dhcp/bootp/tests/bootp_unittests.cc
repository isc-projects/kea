// Copyright (C) 2019-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which verify flexible option.

#include <config.h>
#include <bootp_log.h>
#include <dhcp/pkt4.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::bootp;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::util;

extern "C" {
extern int buffer4_receive(CalloutHandle& handle);
extern int pkt4_send(CalloutHandle& handle);
}

namespace {

/// @brief Test fixture for exercising bootp library callout.
/// It fetches the CalloutManager and prepares stub packets that can be used in
/// tests.
class BootpTest : public ::testing::Test {
public:

    /// @brief Constructor.
    BootpTest() : co_manager_(new CalloutManager(1)) {
    }

    /// @brief Destructor.
    virtual ~BootpTest() {
    }

    /// @brief Fetches the callout manager instance.
    boost::shared_ptr<CalloutManager>getCalloutManager() {
        return (co_manager_);
    }

    /// @brief Tests buffer4_receive callout.
    ///
    /// @param pkt The packet to submit.
    /// @param processed True if the packet must be processed, false otherwise.
    void buffer4ReceiveCalloutCall(Pkt4Ptr& pkt, bool processed) {
        // Get callout handle.
        CalloutHandle handle(getCalloutManager());

        // Get type.
        uint8_t type = pkt->getType();

        // Get data so it becomes possible to reset it to unpacked state.
        ASSERT_NO_THROW(pkt->pack());
        const OutputBuffer& buffer = pkt->getBuffer();
        pkt.reset(new Pkt4(reinterpret_cast<const uint8_t*>(buffer.getData()),
                           buffer.getLength()));

        // Set query.
        handle.setArgument("query4", pkt);

        // Execute buffer4_receive callout.
        int ret;
        ASSERT_NO_THROW(ret = buffer4_receive(handle));
        EXPECT_EQ(0, ret);

        // Verify status (SKIP means unpacked).
        EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, handle.getStatus());

        // Verify processing.
        if (processed) {
            EXPECT_TRUE(pkt->inClass("BOOTP"));
            EXPECT_EQ(DHCPREQUEST, pkt->getType());
        } else {
            EXPECT_FALSE(pkt->inClass("BOOTP"));
            EXPECT_EQ(type, pkt->getType());
        }
    }

    /// @brief Tests pkt4_send callout.
    ///
    /// @param pkt The packet to submit.
    /// @param bootp True if the query is in the BOOTP class.
    /// @param processed True if the packet must be processed, false otherwise.
    void pkt4SendCalloutCall(Pkt4Ptr& pkt, bool bootp, bool processed) {
        // Get callout handle.
        CalloutHandle handle(getCalloutManager());

        // Set query.
        Pkt4Ptr query(new Pkt4(DHCPREQUEST, 12345));
        if (bootp) {
            query->addClass("BOOTP");
        }
        handle.setArgument("query4", query);

        // Set response.
        handle.setArgument("response4", pkt);

        // Execute buffer4_receive callout.
        int ret;
        ASSERT_NO_THROW(ret = pkt4_send(handle));
        EXPECT_EQ(0, ret);

        // Verify processing.
        if (processed) {
            EXPECT_EQ(CalloutHandle::NEXT_STEP_SKIP, handle.getStatus());
            EXPECT_FALSE(pkt->getOption(DHO_DHCP_MESSAGE_TYPE));
            EXPECT_LE(300, pkt->getBuffer().getLength());
        } else {
            EXPECT_EQ(CalloutHandle::NEXT_STEP_CONTINUE, handle.getStatus());
            EXPECT_TRUE(pkt->getOption(DHO_DHCP_MESSAGE_TYPE));
            // This works because we did not add options to the response.
            EXPECT_GT(300, pkt->getBuffer().getLength());
        }
    }

    /// @brief Callout manager accessed by this CalloutHandle.
    boost::shared_ptr<CalloutManager> co_manager_;
};

// Verifies that DHCPDISCOVER goes through unmodified.
TEST_F(BootpTest, dhcpDiscover) {
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, 12345));
    buffer4ReceiveCalloutCall(pkt, false);
}

// Verifies that DHCPREQUEST goes through unmodified.
TEST_F(BootpTest, dhcpRequest) {
    Pkt4Ptr pkt(new Pkt4(DHCPREQUEST, 12345));
    buffer4ReceiveCalloutCall(pkt, false);
}

// Verifies that DHCPOFFER goes through unmodified.
TEST_F(BootpTest, dhcpOffer) {
    Pkt4Ptr pkt(new Pkt4(DHCPOFFER, 12345));
    buffer4ReceiveCalloutCall(pkt, false);
}

// Verifies that BOOTREPLY goes through unmodified.
TEST_F(BootpTest, bootReply) {
    // The constructor does not allow to directly create a BOOTREPLY packet.
    Pkt4Ptr pkt(new Pkt4(DHCPOFFER, 12345));
    pkt->setType(DHCP_NOTYPE);
    pkt->delOption(DHO_DHCP_MESSAGE_TYPE);
    ASSERT_EQ(BOOTREPLY, pkt->getOp());
    buffer4ReceiveCalloutCall(pkt, false);
}

// Verifies that BOOTREQUEST is recognized and processed.
TEST_F(BootpTest, bootRequest) {
    // The constructor does not allow to directly create a BOOTREQUEST packet.
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, 12345));
    pkt->setType(DHCP_NOTYPE);
    pkt->delOption(DHO_DHCP_MESSAGE_TYPE);
    ASSERT_EQ(BOOTREQUEST, pkt->getOp());
    buffer4ReceiveCalloutCall(pkt, true);
}

// Verifies that pure DHCPACK goes through unmodified.
TEST_F(BootpTest, dhcpAck) {
    Pkt4Ptr pkt(new Pkt4(DHCPACK, 12345));
    pkt4SendCalloutCall(pkt, false, false);
}

// Verifies that ACK is processed when responding to BOOTP packet.  There's no
// such thing as BOOTP ACK. This test checks that when the server responding to
// BOOTPREQUEST (modified by the hook to look like a DHCPREQUEST), it will
// send back an ACK. The hooks is supposed to strip down the DHCP specific stuff,
// so the response looks like a BOOTPREPLY.
TEST_F(BootpTest, bootpAck) {
    Pkt4Ptr pkt(new Pkt4(DHCPACK, 12345));
    pkt4SendCalloutCall(pkt, true, true);
}

// Verifies that pure DHCPNAK goes through unmodified.
TEST_F(BootpTest, dhcpNak) {
    Pkt4Ptr pkt(new Pkt4(DHCPNAK, 12345));
    pkt4SendCalloutCall(pkt, false, false);
}

// Verifies that BOOTP NAK is processed.
// This particular scenario doesn't make much sense. Since there's not way to
// convey back to the BOOTP client that its request has been declined (and
// IIRC the BOOTP client never sends its address), so there are no cases of
// the server responding with NAK), this scenario seems mostly theoretical.
// But it's good to check that the code is robust.
TEST_F(BootpTest, bootpNak) {
    Pkt4Ptr pkt(new Pkt4(DHCPNAK, 12345));
    pkt4SendCalloutCall(pkt, true, true);
}

} // end of anonymous namespace
