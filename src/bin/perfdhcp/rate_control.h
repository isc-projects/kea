// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RATE_CONTROL_H
#define RATE_CONTROL_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace isc {
namespace perfdhcp {

/// \brief A message sending rate control class for perfdhcp.
///
/// This class provides the means to control the rate at which messages
/// of the specific type are sent by perfdhcp. Each message type,
/// for which the desired rate can be specified, has a corresponding
/// \c RateControl object. So, the perfdhcp is using up to three objects
/// of this type at the same time, to control the rate of the following
/// messages being sent:
/// - Discover(DHCPv4) or Solicit (DHCPv6)
/// - Renew (DHCPv6) or Request (DHCPv4) to renew leases.
/// - Release
///
/// The purpose of the RateControl class is to track the due time for
/// sending next message (or bunch of messages) to keep outbound rate
/// of particular messages at the desired level. The due time is calculated
/// using the desired rate value and the timestamp when the last message of
/// the particular type has been sent. That puts the responsibility on the
/// \c TestControl class to invoke the \c RateControl::updateSendDue, every
/// time the message is sent.
///
/// The \c RateControl object returns the number of messages to be sent at
/// the time. The number returned is 0, if perfdhcp shouldn't send any messages
/// yet, or 1 (sometimes more) if the send due time has been reached.
class RateControl {
public:

    /// \brief Default constructor.
    RateControl();

    /// \brief Constructor which sets desired rate and aggressivity.
    ///
    /// \param rate A desired rate.
    /// \param aggressivity A desired aggressivity.
    RateControl(const int rate, const int aggressivity);

    /// \brief Returns the value of aggressivity.
    int getAggressivity() const {
        return (aggressivity_);
    }

    /// \brief Returns current due time to send next message.
    boost::posix_time::ptime getDue() const {
        return (send_due_);
    }

    /// \brief Returns number of messages to be sent "now".
    ///
    /// This function calculates how many messages of the given type should
    /// be sent immediately when the call to the function returns, to catch
    /// up with the desired message rate.
    ///
    /// The value returned depends on the due time calculated with the
    /// \c RateControl::updateSendDue function and the current time. If
    /// the due time has been hit, the non-zero number of messages is returned.
    /// If the due time hasn't been hit, the number returned is 0.
    ///
    /// If the rate is non-zero, the number of messages to be sent is calculated
    /// as follows:
    /// \code
    ///          num = duration * rate
    /// \endcode
    /// where <b>duration</b> is a time period between the due time to send
    /// next set of messages and current time. The duration is expressed in
    /// seconds with the fractional part having 6 or 9 digits (depending on
    /// the timer resolution). If the calculated value is equal to 0, it is
    /// rounded to 1, so as at least one message is sent.
    ///
    /// The value of aggressivity limits the maximal number of messages to
    /// be sent one after another. If the number of messages calculated with
    /// the equation above exceeds the aggressivity, this function will return
    /// the value equal to aggressivity.
    ///
    /// If the rate is not specified (equal to 0), the value calculated by
    /// this function is equal to aggressivity.
    ///
    /// \return A number of messages to be sent immediately.
    uint64_t getOutboundMessageCount();

    /// \brief Returns the rate.
    int getRate() const {
        return (rate_);
    }

    /// \brief Returns the value of the late send flag.
    ///
    /// The flag returned by this function indicates whether the new due time
    /// calculated by the \c RateControl::updateSendDue is in the past.
    /// This value is used by the \c TestControl object to increment the counter
    /// of the late sent messages in the \c StatsMgr.
    bool isLateSent() const {
        return (late_sent_);
    }

    /// \brief Sets the value of aggressivity.
    ///
    /// \param aggressivity A new value of aggressivity. This value must be
    /// a positive integer.
    /// \throw isc::BadValue if new value is not a positive integer.
    void setAggressivity(const int aggressivity);

    /// \brief Sets the new rate.
    ///
    /// \param rate A new value of rate. This value must not be negative.
    /// \throw isc::BadValue if new rate is negative.
    void setRate(const int rate);

    /// \brief Sets the value of the due time.
    ///
    /// This function is intended for unit testing. It manipulates the value of
    /// the due time. The parameter passed to this function specifies the
    /// (positive or negative) number of seconds relative to current time.
    ///
    /// \param offset A number of seconds relative to current time which
    /// constitutes the new due time.
    void setRelativeDue(const int offset);

    /// \brief Sets the timestamp of the last sent message to current time.
    void updateSendTime();

protected:

    /// \brief Convenience function returning current time.
    ///
    /// \return current time.
    static boost::posix_time::ptime currentTime();

    /// \brief Calculates the send due.
    ///
    /// This function calculates the send due timestamp using the current time
    /// and desired rate. The due timestamp is calculated as a sum of the
    /// timestamp when the last message was sent and the reciprocal of the rate
    /// in micro or nanoseconds (depending on the timer resolution). If the rate
    /// is not specified, the duration between two consecutive sends is one
    /// timer tick.
    void updateSendDue();

    /// \brief Holds a timestamp when the next message should be sent.
    boost::posix_time::ptime send_due_;

    /// \brief Holds a timestamp when the last message was sent.
    boost::posix_time::ptime last_sent_;

    /// \brief Holds an aggressivity value.
    int aggressivity_;

    /// \brief Holds a desired rate value.
    int rate_;

    /// \brief A flag which indicates that the calculated due time is in the
    /// past.
    bool late_sent_;

};

}
}

#endif
