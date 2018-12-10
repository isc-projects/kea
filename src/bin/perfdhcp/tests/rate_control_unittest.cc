// Copyright (C) 2013-2018 Internet Systems Consortium, Inc. ("ISC")
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

    /// \brief Constructor which sets up the rate and aggressivity.
    ///
    /// \param rate A rate at which messages are sent.
    /// \param aggressivity A value of aggressivity. This value controls the
    /// maximal number of messages sent in one chunk.
    NakedRateControl(const int rate, const int aggressivity)
        : RateControl(rate, aggressivity) {
    }

    using RateControl::currentTime;
    using RateControl::updateSendTime;
    using RateControl::updateSendDue;
    using RateControl::send_due_;
    using RateControl::last_sent_;
    using RateControl::late_sent_;
    using RateControl::start_time_;
    using RateControl::sent_;
};

// Test default constructor.
TEST(RateControl, constructorDefault) {
    NakedRateControl rc;
    EXPECT_EQ(1, rc.getAggressivity());
    EXPECT_EQ(0, rc.getRate());
    EXPECT_FALSE(rc.getDue().is_not_a_date_time());
    EXPECT_FALSE(rc.last_sent_.is_not_a_date_time());
    EXPECT_FALSE(rc.isLateSent());
}

// Test the constructor which sets the rate and aggressivity.
TEST(RateControl, constructor) {
    // Call the constructor and verify that it sets the appropriate
    // values.
    NakedRateControl rc1(3, 2);
    EXPECT_EQ(2, rc1.getAggressivity());
    EXPECT_EQ(3, rc1.getRate());
    EXPECT_FALSE(rc1.getDue().is_not_a_date_time());
    EXPECT_FALSE(rc1.last_sent_.is_not_a_date_time());
    EXPECT_FALSE(rc1.isLateSent());

    // Call the constructor again and make sure that different values
    // will be set correctly.
    NakedRateControl rc2(5, 6);
    EXPECT_EQ(6, rc2.getAggressivity());
    EXPECT_EQ(5, rc2.getRate());
    EXPECT_FALSE(rc2.getDue().is_not_a_date_time());
    EXPECT_FALSE(rc2.last_sent_.is_not_a_date_time());
    EXPECT_FALSE(rc2.isLateSent());

    // The 0 value of aggressivity < 1 is not acceptable.
    EXPECT_THROW(RateControl(3, 0), isc::BadValue);
    // The negative value of rate is not acceptable.
    EXPECT_THROW(RateControl(-1, 3), isc::BadValue);
}

// Check the aggressivity accessor.
TEST(RateControl, getAggressivity) {
    RateControl rc;
    ASSERT_EQ(1, rc.getAggressivity());
    rc.setAggressivity(5);
    ASSERT_EQ(5, rc.getAggressivity());
    rc.setAggressivity(10);
    EXPECT_EQ(10, rc.getAggressivity());
}

// Check the due time accessor.
TEST(RateControl, getDue) {
    NakedRateControl rc;
    ASSERT_FALSE(rc.getDue().is_not_a_date_time());
    rc.send_due_ = NakedRateControl::currentTime();
    EXPECT_TRUE(NakedRateControl::currentTime() >= rc.getDue());
    rc.send_due_ = NakedRateControl::currentTime() +
        boost::posix_time::seconds(10);
    EXPECT_TRUE(NakedRateControl::currentTime() < rc.getDue());
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

// Check if late send flag accessor.
TEST(RateControl, isLateSent) {
    NakedRateControl rc;
    ASSERT_FALSE(rc.isLateSent());
    rc.late_sent_ = true;
    EXPECT_TRUE(rc.isLateSent());
}

// Check that the function returns the number of messages to be sent "now"
// correctly.
// @todo Possibly extend this test to cover more complex scenarios. Note that
// it is quite hard to fully test this function as its behaviour strongly
// depends on time.
TEST(RateControl, getOutboundMessageCount) {
    // Test that the number of outbound messages is correctly defined by the
    // rate.  The aggressivity is set high enough so that it will not restrict
    // the calculated count.
    NakedRateControl rc1(1000, 1000000);
    // Set the start time well to the past.
    rc1.start_time_ =
        NakedRateControl::currentTime() - boost::posix_time::seconds(5) -
        boost::posix_time::milliseconds(250);
    // The number of messages to be sent must be roughly equal to the time
    // since started multiplied by the rate.
    // The margin in this test is reasonably generous, allowing for a timing
    // error of around 10ms.
    uint64_t count = 0;
    ASSERT_NO_THROW(count = rc1.getOutboundMessageCount());
    EXPECT_TRUE((count >= 5240) && (count <= 5260)) <<
        "count is " << count << ", expected range 5240-5260";

    // Check that the aggressivity limits the count of messages.
    NakedRateControl rc2(1000, 3500);
    rc2.start_time_ =
        NakedRateControl::currentTime() - boost::posix_time::seconds(5) -
        boost::posix_time::milliseconds(250);
    ASSERT_NO_THROW(count = rc2.getOutboundMessageCount());
    EXPECT_EQ(3500, count);

    // Now, don't specify the rate. In this case the aggressivity dictates
    // how many messages to send.
    NakedRateControl rc3(0, 3);
    rc3.last_sent_ =
        NakedRateControl::currentTime() - boost::posix_time::seconds(5);
    ASSERT_NO_THROW(count = rc3.getOutboundMessageCount());
    EXPECT_EQ(3, count);

    // Specify the rate and set the sent counter so next message is due well
    // to the future: the number of messages to be sent must be 0.
    NakedRateControl rc4(10, 3);
    rc4.last_sent_ = NakedRateControl::currentTime() +
        boost::posix_time::seconds(5);
    rc4.sent_ = 6000;
    ASSERT_NO_THROW(count = rc4.getOutboundMessageCount());
    EXPECT_EQ(0, count);

}

// Test the aggressivity modifier for valid and invalid values.
TEST(RateControl, setAggressivity) {
    NakedRateControl rc;
    ASSERT_NO_THROW(rc.setAggressivity(1));
    EXPECT_THROW(rc.setAggressivity(0), isc::BadValue);
    EXPECT_THROW(rc.setAggressivity(-1), isc::BadValue);
}

// Test the rate modifier for valid and invalid rate values.
TEST(RateControl, setRate) {
    NakedRateControl rc;
    EXPECT_NO_THROW(rc.setRate(1));
    EXPECT_NO_THROW(rc.setRate(0));
    EXPECT_THROW(rc.setRate(-1), isc::BadValue);
}

// Test that the message send time is updated to the current time.
TEST(RateControl, updateSendTime) {
    NakedRateControl rc;
    // Set the timestamp to the future.
    rc.last_sent_ =
        NakedRateControl::currentTime() + boost::posix_time::seconds(5);
    rc.updateSendTime();
    // Updated timestamp should be set to now or to the past.
    EXPECT_TRUE(rc.last_sent_ <= NakedRateControl::currentTime());

}
