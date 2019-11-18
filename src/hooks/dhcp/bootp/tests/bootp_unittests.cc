// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
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

extern "C" {
extern int pkt4_receive(CalloutHandle& handle);
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
        return(co_manager_);
    }

    /// @brief Tests pkt4_receive callout.
    ///
    /// @param pkt The packet to submit.
    /// @param processed True if the packet must be processed, false otherwise.
    void pkt4_receiveCall(Pkt4Ptr& pkt, bool processed) {
        // Get callout handle.
        CalloutHandle handle(getCalloutManager());

        // Set query.
        handle.setArgument("query4", pkt);

        // Get type.
        uint8_t type = pkt->getType();

        // Execute pkt4_receive callout.
        int ret;
        ASSERT_NO_THROW(ret = pkt4_receive(handle));
        EXPECT_EQ(0, ret);

        // Verify processing.
        if (processed) {
            EXPECT_TRUE(pkt->inClass("BOOTP"));
            EXPECT_EQ(DHCPREQUEST, pkt->getType());
        } else {
            EXPECT_FALSE(pkt->inClass("BOOTP"));
            EXPECT_EQ(type, pkt->getType());
        }
    }

    /// @brief Callout manager accessed by this CalloutHandle.
    boost::shared_ptr<CalloutManager> co_manager_;
};

// Verifies that DHCPDISCOVER goes through unmodified.
TEST_F(BootpTest, dhcpDiscover) {
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, 12345));
    pkt4_receiveCall(pkt, false);
}

// Verifies that DHCPREQUEST goes through unmodified.
TEST_F(BootpTest, dhcpRequest) {
    Pkt4Ptr pkt(new Pkt4(DHCPREQUEST, 12345));
    pkt4_receiveCall(pkt, false);
}

// Verifies that DHCPOFFER goes through unmodified.
TEST_F(BootpTest, dhcpOffer) {
    Pkt4Ptr pkt(new Pkt4(DHCPOFFER, 12345));
    pkt4_receiveCall(pkt, false);
}

// Verifies that BOOTREPLY goes through unmodified.
TEST_F(BootpTest, bootReply) {
    // The constructor does not allow to directly create a BOOTREPLY packet.
    Pkt4Ptr pkt(new Pkt4(DHCPOFFER, 12345));
    pkt->setType(DHCP_NOTYPE);
    pkt->delOption(DHO_DHCP_MESSAGE_TYPE);
    ASSERT_EQ(BOOTREPLY, pkt->getOp());
    pkt4_receiveCall(pkt, false);
}

// Verifies that BOOTREQUEST is recognized and processed.
TEST_F(BootpTest, bootRequest) {
    // The constructor does not allow to directly create a BOOTREQUEST packet.
    Pkt4Ptr pkt(new Pkt4(DHCPDISCOVER, 12345));
    pkt->setType(DHCP_NOTYPE);
    pkt->delOption(DHO_DHCP_MESSAGE_TYPE);
    ASSERT_EQ(BOOTREQUEST, pkt->getOp());
    pkt4_receiveCall(pkt, true);
}

} // end of anonymous namespace
