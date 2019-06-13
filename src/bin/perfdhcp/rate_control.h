// Copyright (C) 2013-2019 Internet Systems Consortium, Inc. ("ISC")
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

    /// \brief Constructor which sets desired rate.
    ///
    /// \param rate A desired rate.
    RateControl(const unsigned int rate);

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
    /// \return A number of messages to be sent immediately.
    uint64_t getOutboundMessageCount(bool const waiting_to_exit = false);

    /// \brief Returns the rate.
    unsigned int getRate() const {
        return (rate_);
    }

    /// \brief Sets the new rate.
    ///
    /// \param rate A new value of rate. This value must not be negative.
    /// \throw isc::BadValue if new rate is negative.
    void setRate(const int rate);

protected:

    /// \brief Convenience function returning current time.
    ///
    /// \return current time.
    boost::posix_time::ptime currentTime();

    /// \brief Holds a desired rate value.
    unsigned int rate_;

    /// \brief Holds number of packets send from the beginning.

    /// It is used to calculate current request rate. Then this is used
    /// to estimate number of packets to send in current cycle.
    uint64_t total_pkts_sent_count_;

    /// \brief Holds time of start of testing.

    /// It is used to calculate current request rate. Then this is used
    /// to estimate number of packets to send in current cycle.
    boost::posix_time::ptime start_time_;
};

}
}

#endif
