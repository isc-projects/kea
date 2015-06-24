// Copyright (C) 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
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
    // rate.  The agressivity is set high enough so that it will not restrict
    // the calculated count.
    NakedRateControl rc1(1000, 1000000);
    // Set the timestamp of the last sent message well to the past. The
    // resulting due time will be in the past too.  A fractional number of
    // seconds is used to check the floating point arithmetic performed inside
    // the RateControl class.
    rc1.last_sent_ =
        NakedRateControl::currentTime() - boost::posix_time::seconds(5) -
        boost::posix_time::milliseconds(250);
    // The number of messages to be sent must be roughly equal to the time
    // between the last sent message and the current time multiplied by the
    // rate.  ("Roughly", as current time is advancing, so the actual interval
    // when the calcuation is made may be different from the interval set.)  The
    // margin in this test is reasonably generous, allowing for a timing error
    // of around 10ms.
    uint64_t count;
    ASSERT_NO_THROW(count = rc1.getOutboundMessageCount());
    EXPECT_TRUE((count >= 5240) && (count <= 5260)) <<
        "count is " << count << ", expected range 5240-5260";

    // Check that the agressivity limits the count of messages.
    NakedRateControl rc2(1000, 3500);
    rc2.last_sent_ =
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

    // Specify the rate and set the timestamp of the last sent message well
    // to the future. If the resulting due time is well in the future too,
    // the number of messages to be sent must be 0.
    NakedRateControl rc4(10, 3);
    rc4.last_sent_ = NakedRateControl::currentTime() +
        boost::posix_time::seconds(5);
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

// Test the function which calculates the due time to send next set of
// messages.
TEST(RateControl, updateSendDue) {
    NakedRateControl rc;
    // Set the send due timestamp to the value which is well in the future.
    // If we don't hit the due time, the function should not modify the
    // due time.
    rc.send_due_ =
        NakedRateControl::currentTime() + boost::posix_time::seconds(10);
    boost::posix_time::ptime last_send_due = rc.send_due_;
    ASSERT_NO_THROW(rc.updateSendDue());
    EXPECT_TRUE(rc.send_due_ == last_send_due);
    // Set the due time to the value which is already behind.
    rc.send_due_ =
        NakedRateControl::currentTime() - boost::posix_time::seconds(10);
    last_send_due = rc.send_due_;
    ASSERT_NO_THROW(rc.updateSendDue());
    // The value should be modified to the new value.
    EXPECT_TRUE(rc.send_due_ > last_send_due);

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
