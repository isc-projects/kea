// Copyright (C) 2013-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include "rate_control.h"
#include <gtest/gtest.h>


using namespace isc;
using namespace isc::perfdhcp;

/// \brief A class which exposes protected methods and members of the
/// RateControl class (under test).
class NakedRateControl : public RateControl {
public:

    /// \brief Default constructor.
    NakedRateControl()
        : RateControl() {
    }

    /// \brief Constructor which sets up the rate.
    ///
    /// \param rate A rate at which messages are sent.
    /// maximal number of messages sent in one chunk.
    NakedRateControl(const int rate)
        : RateControl(rate) {
    }

    using RateControl::currentTime;
    using RateControl::start_time_;
};

// Test default constructor.
TEST(RateControl, constructorDefault) {
    NakedRateControl rc;
    EXPECT_EQ(0, rc.getRate());
}

// Test the constructor which sets the rate.
TEST(RateControl, constructor) {
    // Call the constructor and verify that it sets the appropriate
    // values.
    NakedRateControl rc1(3);
    EXPECT_EQ(3, rc1.getRate());

    // Call the constructor again and make sure that different values
    // will be set correctly.
    NakedRateControl rc2(5);
    EXPECT_EQ(5, rc2.getRate());
}

// Check the rate accessor.
TEST(RateControl, getRate) {
    RateControl rc;
    ASSERT_EQ(0, rc.getRate());
    rc.setRate(5);
    ASSERT_EQ(5, rc.getRate());
    rc.setRate(10);
    EXPECT_EQ(10, rc.getRate());
}

// Check that the function returns the number of messages to be sent "now"
// correctly.
// @todo Possibly extend this test to cover more complex scenarios. Note that
// it is quite hard to fully test this function as its behaviour strongly
// depends on time.
TEST(RateControl, getOutboundMessageCount) {
    // Test that the number of outbound messages is correctly defined by the
    // rate.
    NakedRateControl rc(2);

    // The first call to getOutboundMessageCount always returns 0 as there is
    // no good estimate at the beginning how many packets to send.
    uint64_t count = 0;
    ASSERT_NO_THROW(count = rc.getOutboundMessageCount());
    EXPECT_EQ(count, 1);

    // After a given amount of time number of packets to send should
    // allow to catch up with requested rate, ie for rate 2pks/s after 1500ms
    // it should send 2 pkts/s * 1.5s = about 2 pkts.
    // To simulate 1500ms lets get back start time by 1500ms.
    rc.start_time_ -= boost::posix_time::milliseconds(1500);
    ASSERT_NO_THROW(count = rc.getOutboundMessageCount());
    EXPECT_EQ(count, 2);

    // If elapsed time is big then a big number of packets would need to be sent.
    // But the pkts number is capped to 3. Check it.
    rc.start_time_ -= boost::posix_time::milliseconds(10000);
    ASSERT_NO_THROW(count = rc.getOutboundMessageCount());
    EXPECT_EQ(count, 3);
}

// Test the rate modifier for valid and invalid rate values.
TEST(RateControl, setRate) {
    NakedRateControl rc;
    EXPECT_NO_THROW(rc.setRate(1));
    EXPECT_NO_THROW(rc.setRate(0));
    EXPECT_THROW(rc.setRate(-1), isc::BadValue);
}
