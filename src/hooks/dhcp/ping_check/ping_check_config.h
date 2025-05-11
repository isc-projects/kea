// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PING_CHECK_CONFIG_H
#define PING_CHECK_CONFIG_H

#include <cc/data.h>
#include <cc/simple_parser.h>

namespace isc {
namespace ping_check {

/// @brief Houses the Ping check configuration parameters for a single scope
/// (e.g. global, subnet...);
class PingCheckConfig {
public:
    /// @brief List of valid parameters and expected types.
    static const data::SimpleKeywords CONFIG_KEYWORDS;

    /// @brief Constructor
    PingCheckConfig();

    /// @brief Destructor
    ~PingCheckConfig() = default;

    /// @brief Extracts member values from an Element::map
    ///
    /// @param config map of configuration parameters
    ///
    /// @throw BadValue if invalid values are detected.
    void parse(data::ConstElementPtr config);

    /// @brief Fetches the value of enable-ping-check
    ///
    /// @return boolean value of enable-ping-check
    bool getEnablePingCheck() const {
        return (enable_ping_check_);
    };

    /// @brief Sets the value of enable-ping-check
    ///
    /// @param value new value for enable-ping-check
    void setEnablePingCheck(bool value) {
        enable_ping_check_ = value;
    }

    /// @brief Fetches the value of min-ping-requests
    ///
    /// @return integer value of min-ping-requests
    uint32_t getMinPingRequests() const {
        return (min_ping_requests_);
    };

    /// @brief Sets the value of min-ping-requests
    ///
    /// @param value new value for min-ping-requests
    void setMinPingRequests(uint32_t value) {
        min_ping_requests_ = value;
    }

    /// @brief Fetches the value of reply-timeout
    ///
    /// @return integer value of reply-timeout
    uint32_t getReplyTimeout() const {
        return (reply_timeout_);
    }

    /// @brief Sets the value of reply-timeout
    ///
    /// @param value new value for reply-timeout
    void setReplyTimeout(uint32_t value) {
        reply_timeout_ = value;
    }

    /// @brief Fetches the value of ping-cltt-secs
    ///
    /// @return integer value of ping-cltt-secs
    uint32_t getPingClttSecs() const {
        return (ping_cltt_secs_);
    }

    /// @brief Sets the value of ping-cltt-secs
    ///
    /// @param value new value for ping-cltt-secs
    void setPingClttSecs(uint32_t value) {
        ping_cltt_secs_ = value;
    }

    /// @brief Fetches the value of ping-channel-threads
    ///
    /// @return integer value of ping-channel-threads
    uint32_t getPingChannelThreads() const {
        return (ping_channel_threads_);
    }

    /// @brief Sets the value of ping-channel-threads
    ///
    /// @param value new value for ping-channel-threads
    void setPingChannelThreads(uint32_t value) {
        ping_channel_threads_ = value;
    }

private:
    // @brief True if checking is enabled.
    bool enable_ping_check_;

    /// @brief minimum number of ECHO REQUESTs sent, without replies received,
    /// required to declare an address free to offer.
    uint32_t min_ping_requests_;

    /// @brief maximum number of milliseconds to wait for an ECHO REPLY after
    /// an ECHO REQUEST has been sent.
    uint32_t reply_timeout_;

    /// @brief minimum number of seconds that must elapse after the lease's CLTT
    /// before a ping check will be conducted, when the client is the lease's
    /// previous owner.
    uint32_t ping_cltt_secs_;

    /// @brief Number of threads to use if Kea core is multi-threaded.
    /// Defaults to 0 (for now) which means follow core number of threads.
    size_t ping_channel_threads_;
};

/// @brief Defines a shared pointer to a PingCheckConfig.
typedef boost::shared_ptr<PingCheckConfig> PingCheckConfigPtr;

} // end of namespace ping_check
} // end of namespace isc

#endif
