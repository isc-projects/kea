// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PING_CONTEXT_H
#define PING_CONTEXT_H

#include <dhcp/pkt4.h>
#include <dhcpsrv/lease.h>
#include <hooks/parking_lots.h>

#include <chrono>

namespace isc {
namespace ping_check {

/// @brief Specifies the type for time stamps.
using TimeStamp = std::chrono::time_point<std::chrono::system_clock>;

/// @brief Embodies the life cycle of a ping check test for a single address
/// for a single DHCPDISCOVER.
///
/// The class uses a state-model to direct the tasks needed to execute one
/// or more ECHO REQUEST SEND/WAIT FOR REPLY cycles until the address is
/// either deemed free to offer or in-use and should not be offered.  The
/// number of cycles conducted is dictated by the minimum number of echos
/// (@c min_echos_) and whether or not either an ECHO REPLY or DESTINATION
/// UNREACHABLE are received.
class PingContext {
public:

    /// @brief Defines PingContext life cycle states
    enum State {
        NEW,                  // Newly created
        WAITING_TO_SEND,      // Waiting to send next ECHO REQUEST
        SENDING,              // Next ECHO REQUEST is being sent
        WAITING_FOR_REPLY,    // ECHO REQUEST sent, Waiting for reply or timeout
        TARGET_FREE,          // Target has been deemed free to offer.
        TARGET_IN_USE         // Target has been deemed in-use, do not offer
    };

    /// @brief Converts a string to State
    ///
    /// @param state_str  Upper case string label to convert
    /// @return State value corresponding to the given string
    ///
    /// @throw BadValue if the string is not a valid state label
    static State stringToState(const std::string& state_str);

    /// @brief Converts a State to a string
    ///
    /// @param state  State to convert
    /// @return string label corresponding to the given state
    static std::string stateToString(const State& state);

    /// @brief Constructor
    ///
    /// @param lease pointer to the lease whose address needs to be checked
    /// @param query DHCPDISCOVER that instigated the check
    /// @param min_echos minimum number of ECHO REQUESTs sent without replies
    /// received required to declare an address free to offer. Defaults to 1,
    /// must be greater than zero.
    /// @param reply_timeout maximum number of milliseconds to wait for an
    /// ECHO REPLY after an ECHO REQUEST has been sent.  Defaults to 100,
    /// must be greater than 0.
    /// @param parking_lot parking lot in which the query is parked.  Defaults
    /// to an empty pointer.
    ///
    /// @throw BadValue if either lease or query are empty, or if the lease
    /// address is 0.0.0.0
    PingContext(isc::dhcp::Lease4Ptr& lease, isc::dhcp::Pkt4Ptr& query,
                uint32_t min_echos = 1, uint32_t reply_timeout = 100,
                isc::hooks::ParkingLotHandlePtr& parking_lot = EMPTY_LOT());

    /// @brief Destructor
    virtual ~PingContext() = default;

    /// @brief Fetches the current timestamp (UTC/milliseconds precision)
    ///
    /// @return current time as a TimeStamp
    static TimeStamp now();

    /// @brief Fetches an empty timestamp
    ///
    /// @return an empty TimeStamp
    static const TimeStamp& EMPTY_TIME() {
        static TimeStamp empty_time;
        return (empty_time);
    }

    /// @brief Fetches the minimum timestamp
    ///
    /// @return the minimum timestamp
    static const TimeStamp& MIN_TIME() {
        static TimeStamp min_time = std::chrono::system_clock::time_point::min();
        return (min_time);
    }

    /// @brief Fetches an empty parking lot handle
    ///
    /// @return an empty ParkingLotHandlePtr
    static hooks::ParkingLotHandlePtr& EMPTY_LOT() {
        static hooks::ParkingLotHandlePtr empty_lot(0);
        return (empty_lot);
    }

    /// @brief Fetches the IP address that is under test.
    ///
    /// @return IP address as an IOAddress
    const isc::asiolink::IOAddress& getTarget() const;

    /// @brief Fetches the minimum number of ECHO REQUESTs
    ///
    /// @return minimum number of echos as a uint32_t
    uint32_t getMinEchos() const;

    /// @brief Sets the minimum number of ECHO REQUESTs
    ///
    /// @param value new value, must be greater than 0
    ///
    /// @throw BadValue if the given value is 0
    void setMinEchos(uint32_t value);

    /// @brief Fetches the reply timeout (milliseconds)
    ///
    /// @return reply timeout as a unit32_t
    uint32_t getReplyTimeout() const;

    /// @brief Sets the reply timeout
    ///
    /// @param value new value in milliseconds, must be greater than 0
    ///
    /// @throw BadValue if the given value is 0.
    void setReplyTimeout(uint32_t value);

    /// @brief Fetches the number of ECHO REQUESTs sent.
    ///
    /// @return number of echos sent as a unit32_t
    uint32_t getEchosSent() const;

    /// @brief Sets the number of ECHO REQUESTs sent.
    ///
    /// @param value new value
    void setEchosSent(uint32_t value);

    /// @brief Fetches the timestamp of when the most recent ECHO REQUEST
    /// was sent
    ///
    /// @return time the last echo was sent as a TimeStamp
    const TimeStamp& getLastEchoSentTime() const;

    /// @brief Sets the timestamp the most recent ECHO REQUEST was sent
    ///
    /// @param value new value
    void setLastEchoSentTime(const TimeStamp& value);

    /// @brief Fetches the time the context went into WAITING_TO_SEND state
    ///
    /// The value returned is only meaningful when the context state is WAITING_TO_SEND.
    ///
    /// @return send waits start time as a TimeStamp
    const TimeStamp& getSendWaitStart() const;

    /// @brief Sets the send wait start timestamp
    ///
    /// @param value new value
    void setSendWaitStart(const TimeStamp& value);

    /// @brief Returns true if state is WAITING_TO_SEND
    ///
    /// @return True if the context is in WAITING_TO_SEND state
    bool isWaitingToSend() const;

    /// @brief Fetches the time at which the WAITING_FOR_REPLY state expires(ed)
    ///
    /// The value returned is only meaningful when the context state is WAITING_FOR_REPLY.
    ///
    /// @return expiration
    const TimeStamp& getNextExpiry() const;

    /// @brief Sets the timestamp which specifies the time at which the WAITING_FOR_REPLY state expires
    /// @param value new value
    void setNextExpiry(const TimeStamp& value);

    /// @brief Returns true if state is WAITING_FOR_REPLY
    ///
    /// @return True if the context is in WAITING_TO_REPLY state
    bool isWaitingForReply() const;

    /// @brief Fetches the time at which the context was created
    ///
    /// @return creation time as a TimeStamp
    const TimeStamp& getCreatedTime() const;

    /// @brief Fetches the current state.
    ///
    /// @return current state as PingContext::State
    State getState() const;

    /// @brief Sets the state.
    ///
    /// @param value new state value
    void setState(const State& value);

    /// @brief Returns the query that instigated this check
    ///
    /// @return query as a Pkt4Ptr
    isc::dhcp::Pkt4Ptr getQuery() const;

    /// @brief Returns the candidate lease whose address is the target to check
    ///
    /// @return lease under test as a Lease4Ptr
    isc::dhcp::Lease4Ptr getLease() const;

    /// @brief Enters WAITING_TO_SEND state
    ///
    /// @param begin_time timestamp of when the state began.  Defaults to
    /// time now.  Provided for testing purposes.
    void beginWaitingToSend(const TimeStamp& begin_time = PingContext::now());

    /// @brief Enters WAITING_TO_REPLY state
    ///
    /// @param begin_time timestamp of when the state began.  Defaults to
    /// time now.  Provided for testing purposes.
    void beginWaitingForReply(const TimeStamp& begin_time = PingContext::now());

    /// @brief Fetches the parking lot used for this context.
    ///
    /// @return Pointer to the parking lot handle or empty if parking is not
    /// employed.
    isc::hooks::ParkingLotHandlePtr getParkingLot() {
        return (parking_lot_);
    };

private:
    /// @brief Minimum number of echos to send without receiving a reply
    /// before giving up
    uint32_t min_echos_ = 0;

    /// @brief Amount of time (likely in ms) to wait for an echo reply
    uint32_t reply_timeout_ = 0;

    /// @brief Number of echos sent since instantiation
    uint32_t echos_sent_ = 0;

    /// @brief Timestamp the most recent echo send completed
    TimeStamp last_echo_sent_time_;

    /// @brief Timestamp of entry into waiting_to_send
    TimeStamp send_wait_start_;

    /// @brief Timestamp the most recent echo times out
    TimeStamp next_expiry_;

    /// @brief Time context was created
    TimeStamp created_time_;

    /// @brief Candidate lease to check
    isc::dhcp::Lease4Ptr lease_;

    /// @brief DHCPDISCOVER packet that instigated this check.
    isc::dhcp::Pkt4Ptr query_;

    /// @brief Current state of this context
    State state_;

    /// @brief Parking lot where the associated query is parked.
    /// If empty parking is not being employed.
    isc::hooks::ParkingLotHandlePtr parking_lot_;
};

/// @brief Defines a shared pointer to a PingContext.
typedef boost::shared_ptr<PingContext> PingContextPtr;

} // end of namespace ping_check
} // end of namespace isc

#endif
