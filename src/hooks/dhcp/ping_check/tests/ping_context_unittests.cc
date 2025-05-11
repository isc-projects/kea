// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the PingContext class.

#include <config.h>
#include <ping_context.h>
#include <asiolink/io_address.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::ping_check;
using namespace std::chrono;

namespace {

TEST(PingContextTest, validConstruction) {
    // Make a valid lease and query.
    Lease4Ptr lease(new Lease4());
    lease->addr_ = IOAddress("192.0.2.1");
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));

    // Capture time now.
    auto start_time = PingContext::now();

    // Construct the context.
    PingContextPtr context;
    ASSERT_NO_THROW_LOG(context.reset(new PingContext(lease, query)));

    // Verify initial content.
    EXPECT_EQ(lease->addr_, context->getTarget());
    EXPECT_EQ(1, context->getMinEchos());
    EXPECT_EQ(100, context->getReplyTimeout());
    EXPECT_EQ(0, context->getEchosSent());
    EXPECT_EQ(PingContext::EMPTY_TIME(), context->getLastEchoSentTime());
    EXPECT_EQ(PingContext::EMPTY_TIME(), context->getSendWaitStart());
    EXPECT_EQ(PingContext::EMPTY_TIME(), context->getNextExpiry());
    EXPECT_EQ(PingContext::NEW, context->getState());

    // Start time should be less than or equal to created time.
    EXPECT_LE(start_time, context->getCreatedTime());
    EXPECT_EQ(lease, context->getLease());
    EXPECT_EQ(query, context->getQuery());
}

TEST(PingContextTest, invalidConstruction) {
    // Make a valid lease and query.
    Lease4Ptr lease(new Lease4());
    lease->addr_ = IOAddress("192.0.2.1");
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));

    // Empty lease should throw.
    Lease4Ptr empty_lease;
    PingContextPtr context;
    ASSERT_THROW_MSG(context.reset(new PingContext(empty_lease, query)), BadValue,
                     "PingContext ctor - lease cannot be empty");

    // Empty query should throw.
    Pkt4Ptr empty_query;
    ASSERT_THROW_MSG(context.reset(new PingContext(lease, empty_query)), BadValue,
                     "PingContext ctor - query cannot be empty");

    // Empty lease address should throw.
    lease->addr_ = IOAddress::IPV4_ZERO_ADDRESS();
    ASSERT_THROW_MSG(context.reset(new PingContext(lease, query)), BadValue,
                     "PingContext ctor - target address cannot be 0.0.0.0");
}

// Tests conversion of PingContext::State to string and vice-versa.
TEST(PingContext, stateConversion) {
    EXPECT_EQ(PingContext::NEW, PingContext::stringToState("NEW"));
    EXPECT_EQ(PingContext::WAITING_TO_SEND, PingContext::stringToState("WAITING_TO_SEND"));
    EXPECT_EQ(PingContext::SENDING, PingContext::stringToState("SENDING"));
    EXPECT_EQ(PingContext::WAITING_FOR_REPLY, PingContext::stringToState("WAITING_FOR_REPLY"));
    EXPECT_EQ(PingContext::TARGET_FREE, PingContext::stringToState("TARGET_FREE"));
    EXPECT_EQ(PingContext::TARGET_IN_USE, PingContext::stringToState("TARGET_IN_USE"));
    ASSERT_THROW_MSG(PingContext::stringToState("bogus"), BadValue,
                     "Invalid PingContext::State: 'bogus'");

    EXPECT_EQ("NEW", PingContext::stateToString(PingContext::NEW));
    EXPECT_EQ("WAITING_TO_SEND", PingContext::stateToString(PingContext::WAITING_TO_SEND));
    EXPECT_EQ("SENDING", PingContext::stateToString(PingContext::SENDING));
    EXPECT_EQ("WAITING_FOR_REPLY", PingContext::stateToString(PingContext::WAITING_FOR_REPLY));
    EXPECT_EQ("TARGET_FREE", PingContext::stateToString(PingContext::TARGET_FREE));
    EXPECT_EQ("TARGET_IN_USE", PingContext::stateToString(PingContext::TARGET_IN_USE));
}

TEST(PingContext, accessors) {
    // Make a valid lease and query.
    Lease4Ptr lease(new Lease4());
    lease->addr_ = IOAddress("192.0.2.1");
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));

    // Capture time now.
    auto time_now = PingContext::now();

    // Construct a context.
    PingContextPtr context;
    ASSERT_NO_THROW_LOG(context.reset(new PingContext(lease, query, 1, 50)));

    EXPECT_NO_THROW_LOG(context->setMinEchos(4));
    EXPECT_EQ(4, context->getMinEchos());

    EXPECT_NO_THROW_LOG(context->setReplyTimeout(200));
    EXPECT_EQ(200, context->getReplyTimeout());

    EXPECT_NO_THROW_LOG(context->setEchosSent(7));
    EXPECT_EQ(7, context->getEchosSent());

    EXPECT_NO_THROW_LOG(context->setLastEchoSentTime(time_now));
    EXPECT_EQ(time_now, context->getLastEchoSentTime());

    EXPECT_NO_THROW_LOG(context->setState(PingContext::SENDING));
    EXPECT_EQ(PingContext::SENDING, context->getState());

    time_now += milliseconds(100);
    EXPECT_NO_THROW_LOG(context->setSendWaitStart(time_now));
    EXPECT_EQ(time_now, context->getSendWaitStart());

    time_now += milliseconds(100);
    EXPECT_NO_THROW_LOG(context->setNextExpiry(time_now));
    EXPECT_EQ(time_now, context->getNextExpiry());

    EXPECT_FALSE(context->isWaitingToSend());
    time_now += milliseconds(100);
    ASSERT_NO_THROW_LOG(context->beginWaitingToSend(time_now));
    EXPECT_EQ(time_now, context->getSendWaitStart());
    EXPECT_TRUE(context->isWaitingToSend());

    EXPECT_FALSE(context->isWaitingForReply());
    auto exp_expiry = time_now + milliseconds(context->getReplyTimeout());
    ASSERT_NO_THROW_LOG(context->beginWaitingForReply(time_now));
    EXPECT_EQ(exp_expiry, context->getNextExpiry());
    EXPECT_TRUE(context->isWaitingForReply());
}

} // end of anonymous namespace
