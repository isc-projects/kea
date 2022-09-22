// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
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
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <functional>
#include <map>
#include <mutex>
#include <set>
#include <string>
#include <utility>

namespace isc {
namespace ha {

/// @brief Holds communication state between the two HA peers.
///
/// The HA service constantly monitors the state of the connection between
/// the two peers. If the connection is lost it is an indicator that
/// the partner server may be down and failover actions should be triggered.
///
/// A heartbeat command successfully sent over the control channel is an
/// indicator that the connection is healthy. A reply to the heartbeat
/// command includes information about the recipient state, its notion of
/// time, and other information useful for determining its health and
/// current activity.
///
/// This class uses an interval timer to run heartbeat commands over the
/// control channel. The implementation of the heartbeat is external to
/// this class and is provided via @c CommunicationState::startHeartbeat
/// method. This implementation is required to run the @c poke method
/// in case of receiving a successful response to the heartbeat command.
///
/// The @c poke method sets the "last poke time" to current time, thus
/// indicating that the connection is healthy. The @c getDurationInMillisecs
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
    int getPartnerState() const;

    /// @brief Sets partner state.
    ///
    /// @param state new partner's state in a textual form. Supported values are
    /// those returned in response to a ha-heartbeat command.
    /// @throw BadValue if unsupported state value was provided.
    void setPartnerState(const std::string& state);

private:
    /// @brief Sets partner state.
    ///
    /// @param state new partner's state in a textual form. Supported values are
    /// those returned in response to a ha-heartbeat command.
    /// @throw BadValue if unsupported state value was provided.
    void setPartnerStateInternal(const std::string& state);

public:
    /// @brief Returns scopes served by the partner server.
    ///
    /// @return A set of scopes served by the partner.
    std::set<std::string> getPartnerScopes() const;

    /// @brief Sets partner scopes.
    ///
    /// @param new_scopes Partner scopes enclosed in a JSON list.
    void setPartnerScopes(data::ConstElementPtr new_scopes);

private:
    /// @brief Sets partner scopes.
    ///
    /// @param new_scopes Partner scopes enclosed in a JSON list.
    void setPartnerScopesInternal(data::ConstElementPtr new_scopes);

public:
    /// @brief Starts recurring heartbeat (public interface).
    ///
    /// @param interval heartbeat interval in milliseconds.
    /// @param heartbeat_impl pointer to the heartbeat implementation
    /// function.
    void startHeartbeat(const long interval,
                        const std::function<void()>& heartbeat_impl);

    /// @brief Stops recurring heartbeat.
    void stopHeartbeat();

private:
    /// @brief Starts recurring heartbeat.
    ///
    /// @param interval heartbeat interval in milliseconds.
    /// @param heartbeat_impl pointer to the heartbeat implementation
    /// function.
    void startHeartbeatInternal(const long interval = 0,
                                const std::function<void()>& heartbeat_impl = 0);

    /// @brief Stops recurring heartbeat.
    void stopHeartbeatInternal();

public:
    /// @brief Checks if recurring heartbeat is running.
    ///
    /// @return true if heartbeat is running, false otherwise.
    bool isHeartbeatRunning() const;

    /// @brief Pokes the communication state.
    ///
    /// Sets the last poke time to current time. If the heartbeat timer
    /// has been scheduled, it is reset (starts over measuring the time
    /// to the next heartbeat).
    void poke();

private:
    /// @brief Pokes the communication state.
    ///
    /// Sets the last poke time to current time. If the heartbeat timer
    /// has been scheduled, it is reset (starts over measuring the time
    /// to the next heartbeat).
    void pokeInternal();

public:
    /// @brief Returns duration between the poke time and current time.
    ///
    /// @return Duration between the poke time and current time.
    int64_t getDurationInMillisecs() const;

    /// @brief Checks if communication with the partner is interrupted.
    ///
    /// This method checks if the communication with the partner appears
    /// to be interrupted. This is the case when the time since last
    /// successful communication is longer than the configured
    /// max-response-delay value.
    ///
    /// @return true if communication is interrupted, false otherwise.
    bool isCommunicationInterrupted() const;

protected:

    /// @brief Convenience function attempting to retrieve client
    /// identifier from the DHCP message.
    ///
    /// @param message DHCPv4 or DHCPv6 message.
    /// @param option_type code of the option holding the client id.
    /// @return vector containing the client identifier or an empty
    /// vector if it does not exist.
    static std::vector<uint8_t> getClientId(const dhcp::PktPtr& message,
                                            const uint16_t option_type);
public:

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

    /// @brief Returns the number of analyzed messages while being in the
    /// communications interrupted state.
    ///
    /// @return Number of analyzed messages. It includes retransmissions by
    /// the same clients.
    size_t getAnalyzedMessagesCount() const;

    /// @brief Checks if the partner failure has been detected based
    /// on the DHCP traffic analysis.
    ///
    /// In the special case when max-unacked-clients is set to 0 this
    /// method always returns true. Note that max-unacked-clients
    /// set to 0 means that failure detection is not really performed.
    /// Returning true in that case simplifies the code of the
    /// @c HAService which doesn't need to check if the failure detection
    /// is enabled or not. It simply calls this method in the
    /// 'communications interrupted' situation to check if the
    /// server should be transitioned to the 'partner-down' state.
    ///
    /// @return true if the partner failure has been detected, false
    /// otherwise.
    virtual bool failureDetected() const = 0;

    /// @brief Returns the current number of clients which attempted
    /// to get a lease from the partner server.
    ///
    /// The returned number is reset to 0 when the server successfully
    /// establishes communication with the partner. The number is
    /// incremented only in the communications interrupted case.
    ///
    /// @return The number of clients including unacked clients.
    virtual size_t getConnectingClientsCount() const = 0;

    /// @brief Returns the current number of clients which haven't got
    /// the lease from the partner server.
    ///
    /// The returned number is reset to 0 when the server successfully
    /// establishes communication with the partner. The number is
    /// incremented only in the communications interrupted case.
    ///
    /// @return Number of unacked clients.
    virtual size_t getUnackedClientsCount() const = 0;

protected:

    /// @brief Removes information about the clients the partner server
    /// should respond to while communication with the partner was
    /// interrupted.
    ///
    /// This information is cleared by the @c CommunicationState::poke.
    /// The derivations of this class must provide DHCPv4 and DHCPv6 specific
    /// implementations of this method. The @c poke method is called to
    /// indicate that the connection has been successfully (re)established.
    /// Therefore the clients counters are reset and the failure detection
    /// procedure starts over.
    ///
    /// See @c CommunicationState::analyzeMessage for details.
    virtual void clearConnectingClients() = 0;

public:

    /// @brief Returns the number of lease updates rejected by the partner (MT safe).
    ///
    /// Each rejected lease update is counted only once if it failed
    /// multiple times. Before returning the counter, it discards expired
    /// rejected lease updates.
    ///
    /// @return Current rejected lease update number count.
    size_t getRejectedLeaseUpdatesCount();

protected:

    /// @brief Returns the number of lease updates rejected by the partner.
    ///
    /// Each rejected lease update is counted only once if it failed
    /// multiple times. Before returning the counter, it discards expired
    /// rejected lease updates.
    ///
    /// @return Current rejected lease update number count.
    virtual size_t getRejectedLeaseUpdatesCountInternal() = 0;

    /// @brief Extracts the number of lease updates rejected by the partner
    /// from the specified container.
    ///
    /// @param rejected_clients container holding rejected clients (v4 or v6).
    /// @tparam RejectedClientsType type of the container holding rejected
    /// clients.
    /// @return Current rejected lease update number count.
    template<typename RejectedClientsType>
    static size_t getRejectedLeaseUpdatesCountFromContainer(RejectedClientsType& rejected_clients) {
        if (rejected_clients.empty()) {
            return (0);
        }
        auto& idx = rejected_clients.template get<1>();
        auto upper_limit = idx.upper_bound(time(NULL));
        if (upper_limit != idx.end()) {
            auto lower_limit = idx.cbegin();
            idx.erase(lower_limit, upper_limit);
        }
        return (rejected_clients.size());
    }

public:

    /// @brief Marks that the lease update failed due to a conflict for the
    /// specified DHCP message (MT safe).
    ///
    /// If the conflict has been already reported for the given client, the
    /// rejected lease count remains unchanged.
    ///
    /// @param message DHCP message for which a lease update failed due to
    ///  a conflict.
    /// @param lifetime a time in seconds after which the rejected lease
    /// update entry should be discarded.
    /// @return true if the update was rejected for the first time, false
    /// otherwise.
    bool reportRejectedLeaseUpdate(const dhcp::PktPtr& message,
                                   const uint32_t lifetime = 86400);

protected:

    /// @brief Marks that the lease update failed due to a conflict for the
    /// specified DHCP message.
    ///
    /// If the conflict has been already reported for the given client, the
    /// rejected lease count remains unchanged.
    ///
    /// @param message DHCP message for which a lease update failed due to
    ///  a conflict.
    /// @param lifetime a time in seconds after which the rejected lease
    /// update entry should be discarded.
    /// @return true if the update was rejected for the first time, false
    /// otherwise.
    virtual bool reportRejectedLeaseUpdateInternal(const dhcp::PktPtr& message,
                                                   const uint32_t lifetime) = 0;
public:

    /// @brief Marks the lease update successful (MT safe).
    ///
    /// If the lease update was previously marked "in conflict", it is
    /// now cleared, effectively lowering the number of conflicted leases.
    ///
    /// @param message DHCP message for which the lease update was
    /// successful.
    /// @return true when the lease was marked "in conflict" and it is
    /// now cleared.
    bool reportSuccessfulLeaseUpdate(const dhcp::PktPtr& message);

protected:

    /// @brief Marks the lease update successful.
    ///
    /// If the lease update was previously marked "in conflict", it is
    /// now cleared, effectively lowering the number of conflicted leases.
    ///
    /// @param message DHCP message for which the lease update was
    /// successful.
    /// @return true when the lease was marked "in conflict" and it is
    /// now cleared.
    virtual bool reportSuccessfulLeaseUpdateInternal(const dhcp::PktPtr& message) = 0;

public:

    /// @brief Clears rejected client leases (MT safe).
    void clearRejectedLeaseUpdates();

protected:

    /// @brief Clears rejected client leases.
    virtual void clearRejectedLeaseUpdatesInternal() = 0;

public:

    /// @brief Issues a warning about high clock skew between the active
    /// servers if one is warranted.
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
    /// skew exceeding a warning threshold.
    bool clockSkewShouldWarn();

private:
    /// @brief Issues a warning about high clock skew between the active
    /// servers if one is warranted.
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
    /// skew exceeding a warning threshold.
    bool clockSkewShouldWarnInternal();

public:
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
    bool clockSkewShouldTerminate();

private:
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
    bool clockSkewShouldTerminateInternal();

    /// @brief Checks if the clock skew is greater than the specified number
    /// of seconds.
    ///
    /// @param seconds a positive value to compare the clock skew with.
    /// @return true if the absolute clock skew is greater than the specified
    /// number of seconds, false otherwise.
    bool isClockSkewGreater(const long seconds) const;

public:

    /// @brief Indicates whether the HA service should enter "terminated"
    /// state due to excessive number of rejected lease updates.
    ///
    /// @return true if the number of rejected lease updates is equal or
    /// exceeds the value of max-rejected-lease-updates, false when the
    /// max-rejected-lease-updates is 0 or is greater than the current
    /// number of rejected lease updates.
    bool rejectedLeaseUpdatesShouldTerminate();

private:

    /// @brief Indicates whether the HA service should enter "terminated"
    /// state due to excessive number of rejected lease updates.
    ///
    /// @return true if the number of rejected lease updates is equal or
    /// exceeds the value of max-rejected-lease-updates, false when the
    /// max-rejected-lease-updates is 0 or is greater than the current
    /// number of rejected lease updates.
    bool rejectedLeaseUpdatesShouldTerminateInternal();

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

private:
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
    void setPartnerTimeInternal(const std::string& time_text);

public:
    /// @brief Returns current clock skew value in the logger friendly format.
    std::string logFormatClockSkew() const;

private:
    /// @brief Returns current clock skew value in the logger friendly format.
    std::string logFormatClockSkewInternal() const;

public:
    /// @brief Returns the report about current communication state.
    ///
    /// This function returns a JSON map describing the state of communication
    /// with a partner. This report is included in the response to the
    /// status-get command.
    ///
    /// @return JSON element holding the report.
    data::ElementPtr getReport() const;

    /// @brief Modifies poke time by adding seconds to it.
    ///
    /// Used in unittests only.
    ///
    /// @param secs number of seconds to be added to the poke time. If
    /// the value is negative it will set the poke time in the past
    /// comparing to current value.
    void modifyPokeTime(const long secs);

private:

    /// @brief Returns duration between the poke time and current time.
    ///
    /// Should be called in a thread safe context.
    ///
    /// @return Duration between the poke time and current time.
    int64_t getDurationInMillisecsInternal() const;

protected:
    /// @brief Update the poke time and compute the duration.
    ///
    /// @return The time elapsed.
    boost::posix_time::time_duration updatePokeTime();

private:
    /// @brief Update the poke time and compute the duration.
    ///
    /// Should be called in a thread safe context.
    ///
    /// @return The time elapsed.
    boost::posix_time::time_duration updatePokeTimeInternal();

public:

    /// @brief Returns a total number of unsent lease updates.
    uint64_t getUnsentUpdateCount() const;

    /// @brief Increases a total number of unsent lease updates by 1.
    ///
    /// This method should be called when the server has allocated a
    /// lease but decided to not send the lease update to its partner.
    /// If the server is in the partner-down state it allocates new
    /// leases but doesn't send lease updates because the partner is
    /// unavailable.
    ///
    /// This method protects against setting the value to 0 in an
    /// unlikely event of the overflow. The zero is reserved for the
    /// server startup case.
    void increaseUnsentUpdateCount();

private:

    /// @brief Thread unsafe implementation of the @c increaseUnsentUpdateCount.
    void increaseUnsentUpdateCountInternal();

public:

    /// @brief Checks if the partner allocated new leases for which it hasn't sent
    /// any lease updates.
    ///
    /// It compares a previous and current value of the @c partner_unsent_update_count_.
    /// If the current value is 0 and the previous value is non-zero it indicates
    /// that the partner was restarted.
    ///
    /// @return true if the partner has allocated new leases for which it didn't
    /// send lease updates, false otherwise.
    bool hasPartnerNewUnsentUpdates() const;

private:

    /// @brief Thread unsafe implementation of the @c hasPartnerNewUnsentUpdates.
    ///
    /// @return true if the partner has allocated new leases for which it didn't
    /// send lease updates, false otherwise.
    bool hasPartnerNewUnsentUpdatesInternal() const;

public:

    /// @brief Saves new total number of unsent lease updates from the partner.
    ///
    /// @param unsent_update_count new total number of unsent lease updates from
    /// the partner.
    void setPartnerUnsentUpdateCount(uint64_t unsent_update_count);

private:

    /// @brief Thread unsafe implementation of the @c setPartnerUnsentUpdateCount.
    ///
    /// @param unsent_update_count new total number of unsent lease updates from
    /// the partner.
    void setPartnerUnsentUpdateCountInternal(uint64_t unsent_update_count);

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
    std::function<void()> heartbeat_impl_;

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

    /// @brief Total number of analyzed messages to be responded by partner.
    size_t analyzed_messages_count_;

    /// @brief Total number of unsent lease updates.
    ///
    /// The lease updates are not sent when the server is in the partner
    /// down state. The server counts the number of lease updates which
    /// haven't been sent to the partner because the partner was unavailable.
    /// The partner receives this value in a response to a heartbeat message
    /// and can use it to determine if it should synchronize its lease
    /// database.
    uint64_t unsent_update_count_;

    /// @brief Previous and current total number of unsent lease updates
    /// from the partner.
    ///
    /// This value is returned in response to a heartbeat command and saved
    /// using the @c setPartnerUnsentUpdateCount. The previous value is
    /// preserved so the values can be compared in the state handlers.
    std::pair<uint64_t, uint64_t> partner_unsent_update_count_;

    /// @brief The mutex used to protect internal state.
    const boost::scoped_ptr<std::mutex> mutex_;
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

    /// @brief Returns the current number of clients which attempted
    /// to get a lease from the partner server.
    ///
    /// The returned number is reset to 0 when the server successfully
    /// establishes communication with the partner. The number is
    /// incremented only in the communications interrupted case.
    ///
    /// @return The number of clients including unacked clients.
    virtual size_t getConnectingClientsCount() const;

    /// @brief Returns the current number of clients which haven't gotten
    /// a lease from the partner server.
    ///
    /// The returned number is reset to 0 when the server successfully
    /// establishes communication with the partner. The number is
    /// incremented only in the communications interrupted case.
    ///
    /// @return Number of unacked clients.
    virtual size_t getUnackedClientsCount() const;

protected:

    /// @brief Returns the number of lease updates rejected by the partner.
    ///
    /// Each rejected lease update is counted only once if it failed
    /// multiple times. Before returning the counter, it discards expired
    /// rejected lease updates.
    ///
    /// @return Current rejected lease update number count.
    virtual size_t getRejectedLeaseUpdatesCountInternal();

    /// @brief Marks that the lease update failed due to a conflict for the
    /// specified DHCP message.
    ///
    /// If the conflict has been already reported for the given client, the
    /// rejected lease count remains unchanged.
    ///
    /// @param message DHCP message for which a lease update failed due to
    ///  a conflict.
    /// @param lifetime a time in seconds after which the rejected lease
    /// update entry should be discarded.
    /// @return true if the update was rejected for the first time, false
    /// otherwise.
    virtual bool reportRejectedLeaseUpdateInternal(const dhcp::PktPtr& message,
                                                   const uint32_t lifetime);

    /// @brief Marks the lease update successful.
    ///
    /// If the lease update was previously marked "in conflict", it is
    /// now cleared, effectively lowering the number of conflicted leases.
    ///
    /// @param message DHCP message for which the lease update was
    /// successful.
    /// @return true when the lease was marked "in conflict" and it is
    /// now cleared.
    virtual bool reportSuccessfulLeaseUpdateInternal(const dhcp::PktPtr& message);

    /// @brief Clears rejected client leases.
    virtual void clearRejectedLeaseUpdatesInternal();

    /// @brief Checks if the DHCPv4 message appears to be unanswered.
    ///
    /// Should be called in a thread safe context.
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
    virtual void analyzeMessageInternal(const boost::shared_ptr<dhcp::Pkt>& message);

    /// @brief Checks if the partner failure has been detected based
    /// on the DHCP traffic analysis.
    ///
    /// Should be called in a thread safe context.
    ///
    /// @return true if the partner failure has been detected, false
    /// otherwise.
    virtual bool failureDetectedInternal() const;

    /// @brief Removes information about the clients the partner server
    /// should respond to while communication with the partner was
    /// interrupted.
    ///
    /// See @c CommunicationState::analyzeMessage for details.
    virtual void clearConnectingClients();

    /// @brief Hashed index used in the multi index containers to find
    /// clients by HW address and client identifier.
    ///
    /// @tparam ClientData Type of a structure holding client information.
    template<typename ClientData>
    using ClientIdent4 = boost::multi_index::hashed_unique<
        boost::multi_index::composite_key<
            ClientData,
            boost::multi_index::member<ClientData, std::vector<uint8_t>,
                                       &ClientData::hwaddr_>,
            boost::multi_index::member<ClientData, std::vector<uint8_t>,
                                       &ClientData::clientid_>
            >
        >;

    /// @brief Structure holding information about the client which has
    /// sent the packet being analyzed.
    struct ConnectingClient4 {
        std::vector<uint8_t> hwaddr_;
        std::vector<uint8_t> clientid_;
        bool unacked_;
    };

    /// @brief Multi index container holding information about the clients
    /// attempting to get leases from the partner server.
    typedef boost::multi_index_container<
        ConnectingClient4,
        boost::multi_index::indexed_by<
            // First index is a composite index which allows to find a client
            // by the HW address/client identifier tuple.
            ClientIdent4<ConnectingClient4>,
            // Second index allows for counting all clients which are
            // considered unacked.
            boost::multi_index::ordered_non_unique<
                boost::multi_index::member<ConnectingClient4, bool, &ConnectingClient4::unacked_>
            >
        >
    > ConnectingClients4;

    /// @brief Holds information about the clients attempting to contact
    /// the partner server while the servers are in communications
    /// interrupted state.
    ConnectingClients4 connecting_clients_;

    /// @brief Structure holding information about the client who has a
    /// rejected lease update.
    struct RejectedClient4 {
        std::vector<uint8_t> hwaddr_;
        std::vector<uint8_t> clientid_;
        int64_t expire_;
    };

    /// @brief Multi index container holding information about the clients
    /// who have rejected leases.
    typedef boost::multi_index_container<
        RejectedClient4,
        boost::multi_index::indexed_by<
            ClientIdent4<RejectedClient4>,
            boost::multi_index::ordered_non_unique<
                boost::multi_index::member<RejectedClient4, int64_t,
                                           &RejectedClient4::expire_>
            >
        >
    > RejectedClients4;

    /// @brief Holds information about the clients for whom lease updates
    /// have been rejected by the partner.
    RejectedClients4 rejected_clients_;
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

    /// @brief Returns the current number of clients which attempted
    /// to get a lease from the partner server.
    ///
    /// The returned number is reset to 0 when the server successfully
    /// establishes communication with the partner. The number is
    /// incremented only in the communications interrupted case.
    ///
    /// @return The number of clients including unacked clients.
    virtual size_t getConnectingClientsCount() const;

    /// @brief Returns the current number of clients which haven't gotten
    /// a lease from the partner server.
    ///
    /// The returned number is reset to 0 when the server successfully
    /// establishes communication with the partner. The number is
    /// incremented only in the communications interrupted case.
    ///
    /// @return Number of unacked clients.
    virtual size_t getUnackedClientsCount() const;

protected:

    /// @brief Returns the number of lease updates rejected by the partner.
    ///
    /// Each rejected lease update is counted only once if it failed
    /// multiple times. Before returning the counter, it discards expired
    /// rejected lease updates.
    ///
    /// @return Current rejected lease update number count.
    virtual size_t getRejectedLeaseUpdatesCountInternal();

    /// @brief Marks that the lease update failed due to a conflict for the
    /// specified DHCP message.
    ///
    /// If the conflict has been already reported for the given client, the
    /// rejected lease count remains unchanged.
    ///
    /// @param message DHCP message for which a lease update failed due to
    ///  a conflict.
    /// @param lifetime a time in seconds after which the rejected lease
    /// update entry should be discarded.
    /// @return true if the update was rejected for the first time, false
    /// otherwise.
    virtual bool reportRejectedLeaseUpdateInternal(const dhcp::PktPtr& message,
                                                   const uint32_t lifetime = 86400);

    /// @brief Marks the lease update successful.
    ///
    /// If the lease update was previously marked "in conflict", it is
    /// now cleared, effectively lowering the number of conflicted leases.
    ///
    /// @param message DHCP message for which the lease update was
    /// successful.
    /// @return true when the lease was marked "in conflict" and it is
    /// now cleared.
    virtual bool reportSuccessfulLeaseUpdateInternal(const dhcp::PktPtr& message);

    /// @brief Clears rejected client leases.
    virtual void clearRejectedLeaseUpdatesInternal();

protected:

    /// @brief Checks if the DHCPv6 message appears to be unanswered.
    ///
    /// Should be called in a thread safe context.
    ///
    /// See @c CommunicationState::analyzeMessage for details.
    ///
    /// @param message DHCPv6 message to be analyzed. This must be the
    /// message which belongs to the partner, i.e. the caller must
    /// filter out messages belonging to the partner prior to calling
    /// this method.
    virtual void analyzeMessageInternal(const boost::shared_ptr<dhcp::Pkt>& message);

    /// @brief Checks if the partner failure has been detected based
    /// on the DHCP traffic analysis.
    ///
    /// Should be called in a thread safe context.
    ///
    /// @return true if the partner failure has been detected, false
    /// otherwise.
    virtual bool failureDetectedInternal() const;

    /// @brief Removes information about the clients the partner server
    /// should respond to while communication with the partner was
    /// interrupted.
    ///
    /// See @c CommunicationState::analyzeMessage for details.
    virtual void clearConnectingClients();

    /// @brief Hashed index used in the multi index containers to find
    /// clients by DUID.
    ///
    /// @tparam ClientData Type of a structure holding client information.
    template<typename ClientData>
    using ClientIdent6 = boost::multi_index::hashed_unique<
        boost::multi_index::member<ClientData, std::vector<uint8_t>,
                                   &ClientData::duid_>
        >;

    /// @brief Structure holding information about a client which
    /// sent a packet being analyzed.
    struct ConnectingClient6 {
        std::vector<uint8_t> duid_;
        bool unacked_;
    };

    /// @brief Multi index container holding information about the clients
    /// attempting to get leases from the partner server.
    typedef boost::multi_index_container<
        ConnectingClient6,
        boost::multi_index::indexed_by<
            // First index is for accessing connecting clients by DUID.
            ClientIdent6<ConnectingClient6>,
            // Second index allows for counting all clients which are
            // considered unacked.
            boost::multi_index::ordered_non_unique<
                boost::multi_index::member<ConnectingClient6, bool, &ConnectingClient6::unacked_>
            >
        >
    > ConnectingClients6;

    /// @brief Holds information about the clients attempting to contact
    /// the partner server while the servers are in communications
    /// interrupted state.
    ConnectingClients6 connecting_clients_;

    /// @brief Structure holding information about the client who has a
    /// rejected lease update.
    struct RejectedClient6 {
        std::vector<uint8_t> duid_;
        int64_t expire_;
    };

    /// @brief Multi index container holding information about the clients
    /// who have rejected leases.
    typedef boost::multi_index_container<
        RejectedClient6,
        boost::multi_index::indexed_by<
            ClientIdent6<RejectedClient6>,
            boost::multi_index::ordered_non_unique<
                boost::multi_index::member<RejectedClient6, int64_t,
                                           &RejectedClient6::expire_>
            >
        >
    > RejectedClients6;

    /// @brief Holds information about the clients for whom lease updates
    /// have been rejected by the partner.
    RejectedClients6 rejected_clients_;
};

/// @brief Pointer to the @c CommunicationState6 object.
typedef boost::shared_ptr<CommunicationState6> CommunicationState6Ptr;

} // end of namespace isc::ha
} // end of namespace isc

#endif
