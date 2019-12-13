// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HA_COMMUNICATION_STATE_H
#define HA_COMMUNICATION_STATE_H

#include <ha_config.h>
#include <ha_service_states.h>
#include <asiolink/interval_timer.h>
#include <asiolink/io_service.h>
#include <cc/data.h>
#include <dhcp/pkt.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <set>
#include <string>

namespace isc {
namespace ha {

/// @brief Holds communication state between the two HA peers.
///
/// The HA service constantly monitors the state of the connection between
/// the two peers. If the connection is lost it is an indicator that
/// the partner server may be down and failover actions should be triggered.
///
/// Any command successfully sent over the control channel is an indicator
/// that the connection is healthy. The most common command sent over the
/// control channel is a lease update. If the DHCP traffic is heavy, the
/// number of generated lease updates is sufficient to determine whether
/// the connection is healthy or not. There is no need to send heartbeat
/// commands in this case. However, if the DHCP traffic is low there is
/// a need to send heartbeat commands to the partner at the specified
/// rate to keep up-to-date information about the state of the connection.
///
/// This class uses an interval timer to run heartbeat commands over the
/// control channel. The implementation of the heartbeat is external to
/// this class and is provided via @c CommunicationState::startHeartbeat
/// method. This implementation is required to run the @c poke method
/// in case of receiving a successful response to the heartbeat command.
/// It must also run @c poke when the lease update is successful.
///
/// The @c poke method sets the "last poke time" to current time, thus
/// indicating that the connection is healty. The @c getDurationInMillisecs
/// method is used to check for how long the server hasn't been able
/// to communicate with the partner. This duration is simply a time
/// elapsed since last successful poke time. If this duration becomes
/// greater than the configured threshold, the server assumes that the
/// communication with the partner is interrupted.
///
/// The derivations of this class provide DHCPv4 and DHCPv6 specific
/// mechanisms for detecting server failures based on the analysis of
/// the received DHCP messages, i.e. how long the clients have been
/// trying to communicate with the partner and message types they sent.
/// In particular, the increased number of Rebind messages may indicate
/// issues with the DHCP server.
///
/// This class is also used to monitor the clock skew between the active
/// servers. Maintaining a reasonably low clock skew is essential for the
/// HA service to function properly. This class calculates the clock
/// skew by comparing local time of the server with the time returned by
/// the partner in response to a heartbeat command. If this value exceeds
/// the certain thresholds, the CommunicationState::clockSkewShouldWarn
/// and the @c CommuicationState::clockSkewShouldTerminate indicate
/// whether the HA service should continue to operate normally, should
/// start issuing a warning about high clock skew or simply enter the
/// "terminated" state refusing to further operate until the clocks
/// are synchronized. This requires administrative intervention and the
/// restart of the HA service.
class CommunicationState {
public:

    /// @brief Constructor.
    ///
    /// @param io_service pointer to the common IO service instance.
    /// @param config pointer to the HA configuration.
    CommunicationState(const asiolink::IOServicePtr& io_service,
                       const HAConfigPtr& config);

    /// @brief Destructor.
    ///
    /// Stops scheduled heartbeat.
    virtual ~CommunicationState();

    /// @brief Returns last known state of the partner.
    ///
    /// @return Partner's state if it is known, or a negative value otherwise.
    int getPartnerState() const {
        return (partner_state_);
    }

    /// @brief Sets partner state.
    ///
    /// @param state new partner's state in a textual form. Supported values are
    /// those returned in response to a ha-heartbeat command.
    /// @throw BadValue if unsupported state value was provided.
    void setPartnerState(const std::string& state);

    std::set<std::string> getPartnerScopes() const {
        return (partner_scopes_);
    }

    void setPartnerScopes(data::ConstElementPtr new_scopes);

    /// @brief Starts recurring heartbeat (public interface).
    ///
    /// @param interval heartbeat interval in milliseconds.
    /// @param heartbeat_impl pointer to the heartbeat implementation
    /// function.
    void startHeartbeat(const long interval,
                        const boost::function<void()>& heartbeat_impl);

protected:

    /// @brief Starts recurring heartbeat.
    ///
    /// @param interval heartbeat interval in milliseconds.
    /// @param heartbeat_impl pointer to the heartbeat implementation
    /// function.
    void startHeartbeatInternal(const long interval = 0,
                                const boost::function<void()>& heartbeat_impl = 0);

public:

    /// @brief Stops recurring heartbeat.
    void stopHeartbeat();

    /// @brief Checks if recurring heartbeat is running.
    ///
    /// @return true if heartbeat is running, false otherwise.
    bool isHeartbeatRunning() const {
        return (static_cast<bool>(timer_));
    }

    /// @brief Pokes the communication state.
    ///
    /// Sets the last poke time to current time. If the heartbeat timer
    /// has been scheduled, it is reset (starts over measuring the time
    /// to the next heartbeat).
    void poke();

    /// @brief Returns duration between the poke time and current time.
    ///
    /// @return Duration between the poke time and current time.
    int64_t getDurationInMillisecs() const;

    /// @brief Checks if communication with the partner is interrupted.
    ///
    /// This method checks if the communication with the partner appears
    /// to be interrupted. This is the case when the time since last
    /// successful communication is longer than the confgured
    /// max-response-delay value.
    ///
    /// @return true if communication is interrupted, false otherwise.
    bool isCommunicationInterrupted() const;

    /// @brief Checks if the DHCP message appears to be unanswered.
    ///
    /// This method is used to provide the communication state with a
    /// received DHCP message directed to the HA partner, to detect
    /// if the partner fails to answer DHCP messages directed to it.
    /// The DHCPv4 and DHCPv6 specific derivations implement this
    /// functionality.
    ///
    /// This check is orthogonal to the heartbeat mechanism and is
    /// usually triggered after several consecutive heartbeats fail
    /// to be responded.
    ///
    /// The general approach to server failure detection is based on the
    /// analysis of the "secs" field value (DHCPv4) and "elapsed time"
    /// option value (DHCPv6). They indicate for how long the client
    /// has been trying to complete the DHCP transaction. If these
    /// values exceed a configured threshold, the client is considered
    /// to fail to communicate with the server. This fact is recorded
    /// by this object. If the number of distinct clients failing to
    /// communicate with the partner exceeds a configured maximum
    /// value, this server considers the partner to be offline. In this
    /// case, this server will most likely start serving clients
    /// which would normally be served by the partner.
    ///
    /// All information gathered by this method is cleared when the
    /// @c poke method is invoked.
    ///
    /// @param message DHCP message to be analyzed. This must be the
    /// message which belongs to the partner, i.e. the caller must
    /// filter out messages belonging to the partner prior to calling
    /// this method.
    virtual void analyzeMessage(const boost::shared_ptr<dhcp::Pkt>& message) = 0;

    /// @brief Checks if the partner failure has been detected based
    /// on the DHCP traffic analysis.
    ///
    /// In the special case when max-unacked-clients is set to 0 this
    /// method always returns true. Note that max-unacked-clients
    /// set to 0 means that failure detection is not really performed.
    /// Returning true in that case simplifies the code of the
    /// @c HAService which doesn't need to check if the failure detection
    /// is enabled or not. It simply calls this method in the
    /// 'communications interrupted' situtation to check if the
    /// server should be transitioned to the 'partner-down' state.
    ///
    /// @return true if the partner failure has been detected, false
    /// otherwise.
    virtual bool failureDetected() const = 0;

protected:

    /// @brief Removes information about clients which the partner server
    /// failed to respond to.
    ///
    /// This information is cleared by the @c CommunicationState::poke.
    /// The derivations of this class must provide DHCPv4 and DHCPv6 specific
    /// implementations of this method. The @c poke method is called to
    /// indicate that the connection has been successfully (re)established.
    /// Therefore the clients counters are reset and the failure detection
    /// procedure starts over.
    ///
    /// See @c CommunicationState::analyzeMessage for details.
    virtual void clearUnackedClients() = 0;

public:

    /// @brief Indicates whether the HA service should issue a warning about
    /// high clock skew between the active servers.
    ///
    /// The HA service monitors the clock skew between the active servers. The
    /// clock skew is calculated from the local time and the time returned by
    /// the partner in response to a heartbeat. When clock skew exceeds a certain
    /// threshold the HA service starts issuing a warning message. This method
    /// returns true if the HA service should issue this message.
    ///
    /// Currently, the warning threshold for the clock skew is hardcoded to
    /// 30 seconds.  In the future it may become configurable.
    ///
    /// This method is called for each heartbeat. If we issue a warning for each
    /// heartbeat it may flood logs with those messages. This method provides
    /// a gating mechanism which prevents the HA service from logging the
    /// warning more often than every 60 seconds. If the last warning was issued
    /// less than 60 seconds ago this method will return false even if the clock
    /// skew exceeds the 30 seconds threshold. The correction of the clock skew
    /// will reset the gating counter.
    ///
    /// @return true if the warning message should be logged because of the clock
    /// skew exceeding a warning thresdhold.
    bool clockSkewShouldWarn();

    /// @brief Indicates whether the HA service should enter "terminated"
    /// state as a result of the clock skew exceeding maximum value.
    ///
    /// If the clocks on the active servers are not synchronized (perhaps as
    /// a result of a warning message caused by @c clockSkewShouldWarn) and the
    /// clocks further drift, the clock skew may exceed another threshold which
    /// should cause the HA service to enter "terminated" state. In this state
    /// the servers still respond to DHCP clients normally, but they will neither
    /// send lease updates nor heartbeats. In this case, the administrator must
    /// correct the problem (synchronize the clocks) and restart the service.
    /// This method indicates whether the service should terminate or not.
    ///
    /// Currently, the terminal threshold for the clock skew is hardcoded to
    /// 60 seconds.  In the future it may become configurable.
    ///
    /// @return true if the HA service should enter "terminated" state.
    bool clockSkewShouldTerminate() const;

protected:

    /// @brief Checks if the clock skew is greater than the specified number
    /// of seconds.
    ///
    /// @param seconds a positive value to compare the clock skew with.
    /// @return true if the absolute clock skew is greater than the specified
    /// number of seconds, false otherwise.
    bool isClockSkewGreater(const long seconds) const;

public:

    /// @brief Provide partner's notion of time so the new clock skew can be
    /// calculated.
    ///
    /// @param time_text Partner's time received in response to a heartbeat. The
    /// time must be provided in the RFC 1123 format.  It stores the current
    /// time, partner's time, and the difference (skew) between them.
    ///
    /// @throw isc::http::HttpTimeConversionError if the time format is invalid.
    ///
    /// @todo Consider some other time formats which include millisecond
    /// precision.
    void setPartnerTime(const std::string& time_text);

    /// @brief Returns current clock skew value in the logger friendly format.
    std::string logFormatClockSkew() const;

protected:

    /// @brief Pointer to the common IO service instance.
    asiolink::IOServicePtr io_service_;

    /// @brief High availability configuration.
    HAConfigPtr config_;

    /// @brief Interval timer triggering heartbeat commands.
    asiolink::IntervalTimerPtr timer_;

    /// @brief Interval specified for the heartbeat.
    long interval_;

    /// @brief Last poke time.
    boost::posix_time::ptime poke_time_;

    /// @brief Pointer to the function providing heartbeat implementation.
    boost::function<void()> heartbeat_impl_;

    /// @brief Last known state of the partner server.
    ///
    /// Negative value means that the partner's state is unknown.
    int partner_state_;

    /// @brief Last known set of scopes served by the partner server.
    std::set<std::string> partner_scopes_;

    /// @brief Clock skew between the active servers.
    boost::posix_time::time_duration clock_skew_;

    /// @brief Holds a time when last warning about too high clock skew
    /// was issued.
    boost::posix_time::ptime last_clock_skew_warn_;

    /// @brief My time when skew was calculated.
    boost::posix_time::ptime my_time_at_skew_;

    /// @brief Partner reported time when skew was calculated.
    boost::posix_time::ptime partner_time_at_skew_;
};

/// @brief Type of the pointer to the @c CommunicationState object.
typedef boost::shared_ptr<CommunicationState> CommunicationStatePtr;


/// @brief Holds communication state between DHCPv4 servers.
///
/// This class implements DHCPv4 failure detection by monitoring the
/// value of the "secs" field in received DHCPv4 messages as described
/// in @c CommunicationState::analyzeMessage.
class CommunicationState4 : public CommunicationState {
public:

    /// @brief Constructor.
    ///
    /// @param io_service pointer to the common IO service instance.
    /// @param config pointer to the HA configuration.
    CommunicationState4(const asiolink::IOServicePtr& io_service,
                        const HAConfigPtr& config);

    /// @brief Checks if the DHCPv4 message appears to be unanswered.
    ///
    /// This method uses "secs" field value for detecting client
    /// communication failures as described in the
    /// @c CommunicationState::analyzeMessage. Some misbehaving Windows
    /// clients were reported to swap "secs" field bytes. In this case
    /// the first byte is set to non-zero byte and the second byte is
    /// set to 0. This method handles such cases and corrects bytes
    /// order before comparing against the threshold.
    ///
    /// @param message DHCPv4 message to be analyzed. This must be the
    /// message which belongs to the partner, i.e. the caller must
    /// filter out messages belonging to the partner prior to calling
    /// this method.
    virtual void analyzeMessage(const boost::shared_ptr<dhcp::Pkt>& message);

    /// @brief Checks if the partner failure has been detected based
    /// on the DHCP traffic analysis.
    ///
    /// @return true if the partner failure has been detected, false
    /// otherwise.
    virtual bool failureDetected() const;

protected:

    /// @brief Removes information about clients which the partner server
    /// failed to respond to.
    ///
    /// See @c CommunicationState::analyzeMessage for details.
    virtual void clearUnackedClients();

    /// @brief Holds information about the clients which the partner server
    /// failed to respond to.
    ///
    /// The key of the multimap holds hardware addresses of the clients.
    /// The value of the multimap holds client identifiers of the
    /// clients. The client identifiers may be empty.
    std::multimap<std::vector<uint8_t>, std::vector<uint8_t> > unacked_clients_;
};

/// @brief Pointer to the @c CommunicationState4 object.
typedef boost::shared_ptr<CommunicationState4> CommunicationState4Ptr;

/// @brief Holds communication state between DHCPv6 servers.
///
/// This class implements DHCPv6 failure detection by monitoring the
/// value of the "Elapsed Time" option in received DHCPv6 messages as described
/// in @c CommunicationState::analyzeMessage.
class CommunicationState6 : public CommunicationState {
public:

    /// @brief Constructor.
    ///
    /// @param io_service pointer to the common IO service instance.
    /// @param config pointer to the HA configuration.
    CommunicationState6(const asiolink::IOServicePtr& io_service,
                        const HAConfigPtr& config);

    /// @brief Checks if the DHCPv6 message appears to be unanswered.
    ///
    /// See @c CommunicationState::analyzeMessage for details.
    ///
    /// @param message DHCPv6 message to be analyzed. This must be the
    /// message which belongs to the partner, i.e. the caller must
    /// filter out messages belonging to the partner prior to calling
    /// this method.
    virtual void analyzeMessage(const boost::shared_ptr<dhcp::Pkt>& message);

    /// @brief Checks if the partner failure has been detected based
    /// on the DHCP traffic analysis.
    ///
    /// @return true if the partner failure has been detected, false
    /// otherwise.
    virtual bool failureDetected() const;

protected:

    /// @brief Removes information about clients which the partner server
    /// failed to respond to.
    ///
    /// See @c CommunicationState::analyzeMessage for details.
    virtual void clearUnackedClients();

    /// @brief Holds information about the clients which the partner server
    /// failed to respond to.
    ///
    /// The value of the set holds DUIDs of the clients.
    std::set<std::vector<uint8_t> > unacked_clients_;
};

/// @brief Pointer to the @c CommunicationState6 object.
typedef boost::shared_ptr<CommunicationState6> CommunicationState6Ptr;

} // end of namespace isc::ha
} // end of namespace isc

#endif
