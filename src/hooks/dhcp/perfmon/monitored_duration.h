// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _MONITORED_DURATION_H
#define _MONITORED_DURATION_H

#include <cc/data.h>
#include <cc/cfg_to_element.h>
#include <dhcp/pkt.h>
#include <dhcpsrv/subnet_id.h>

#include <boost/date_time/posix_time/posix_time.hpp>

namespace isc {
namespace perfmon {

typedef boost::posix_time::ptime Timestamp;
typedef boost::posix_time::time_duration Duration;

/// @brief Embodies a span of time (i.e. an interval) over which duration data
/// is accumulated.
class DurationDataInterval {
public:
    /// @brief Get a duration of zero.
    ///
    /// @return Duration of zero microseconds.
    static const Duration& ZERO_DURATION() {
        static Duration duration(boost::posix_time::microseconds(0));
        return (duration);
    }

    /// @brief Constructor
    explicit DurationDataInterval(const Timestamp& start_time = dhcp::PktEvent::now());

    /// @brief Destructor
    ~DurationDataInterval() = default;

    /// @brief Add a duration to the interval.
    ///
    /// Given a duration value:
    /// -# Increment the number of occurrences
    /// -# Add the duration to the total duration
    /// -# Update the minimum and/or maxium duration accordingly
    ///
    /// @param duration Duration to add.
    void addDuration(const Duration& duration);

    /// @brief Get the start time of the interval.
    ///
    /// @return Timestamp containing the start time.
    const Timestamp& getStartTime() const {
        return (start_time_);
    }

    /// @brief Set the interval start time.
    ///
    /// @param start_time new value for the interval start time.
    void setStartTime(const Timestamp& start_time) {
        start_time_ = start_time;
    }

    /// @brief Get the number of occurrences that have contributed to the
    /// interval.
    ///
    /// @return the number of occurrences.
    uint64_t getOccurrences() const {
        return (occurrences_);
    };

    /// @brief Get the minimum duration that has occurred in the interval.
    ///
    /// @return Duration containing the minimum duration.
    Duration getMinDuration() const {
        return (min_duration_);
    }

    /// @brief Get the maximum duration that has occurred in the interval.
    ///
    /// @return Duration containing the maximum duration.
    Duration getMaxDuration() const {
        return (max_duration_);
    }

    /// @brief Get the total duration in the interval.
    ///
    /// @return Duration containing the total duration.
    Duration getTotalDuration() const {
        return (total_duration_);
    }

    /// @brief Get the mean duration for the interval.
    ///
    /// @return Duration containing the mean.
    Duration getMeanDuration() const;

    /// @brief Equality operator.
    ///
    /// Primarily used for testing.
    ///
    /// equality operator to compare two DurationDataInterval objects.
    /// @param other DurationDataInterval to be compared against.
    /// @return True the keys are equal
    bool operator==(const DurationDataInterval& other) const;

private:
    /// @brief Timestamp at which this interval began.
    Timestamp start_time_;

    /// @brief Number of event-pairs that occurred during the interval.
    uint64_t occurrences_;

    /// @brief Minimum duration that occurred during this interval.
    Duration min_duration_;

    /// @brief Maximum duration that occurred during this interval.
    Duration max_duration_;

    /// @brief Total duration of all the occurrences included in this interval.
    Duration total_duration_;
};

/// @brief Defines a pointer to a DurationDataInterval instance.
typedef boost::shared_ptr<DurationDataInterval> DurationDataIntervalPtr;

/// @brief Houses the composite key that uniquely identifies a duration:
/// -# Query Packet Type
/// -# Response Packet Type
/// -# Start Event
/// -# Stop Event
/// -# Subnet ID can be GLOBAL_SUBNET_ID for aggregate durations
class DurationKey : public data::CfgToElement {
public:
    /// @brief Constructor
    ///
    /// @param family protocol family AF_INET or AF_INET6
    /// @param query_type message type of the query packet
    /// @param response_type message type of the response packet
    /// @param start_event_label label of the start event
    /// @param stop_event_label label of the end event
    /// @param subnet_id id of the selected subnet
    DurationKey(uint16_t family, uint8_t query_type, uint8_t response_type,
                const std::string& start_event_label, const std::string& stop_event_label,
                dhcp::SubnetID subnet_id);

    /// @brief Destructor
    virtual ~DurationKey() = default;

    /// @brief Get protocol family
    ///
    /// @return uint16_t containing the family (AF_INET or AF_INET6)
    uint16_t getFamily() {
        return (family_);
    }

    /// @brief Get the query packet type.
    ///
    /// @return the query packet type.
    uint8_t getQueryType() const {
        return (query_type_);
    }

    /// @brief Get the response packet type.
    ///
    /// @return the response packet type.
    uint8_t getResponseType() const {
        return (response_type_);
    };

    /// @brief Get the start event label.
    ///
    /// @return the start event label.
    std::string getStartEventLabel() const {
        return (start_event_label_);
    }

    /// @brief Get the end event label.
    ///
    /// @return the end event label.
    std::string getStopEventLabel() const {
        return (stop_event_label_);
    }

    /// @brief Get the subnet id.
    ///
    /// @return SubnetID of the selected subnet.
    dhcp::SubnetID getSubnetId() const {
        return (subnet_id_);
    }

    /// @brief Set the subnet id.
    ///
    /// @param subnet_id new value for subnet id.
    void setSubnetId(dhcp::SubnetID subnet_id) {
        subnet_id_ = subnet_id;
    }

    /// @brief Get a label for a family-specific message type (e.g.
    /// "DHCPDISCOVER", "SOLICIT")
    ///
    /// @param family Protocol family of the key (AF_INET or AF_INET6)
    /// @param msg_type numeric message type to translate
    ///
    /// @return Text label, for values of DHCP_NOTYPE or DHCPV6_NOTYPE: "*"
    static std::string getMessageTypeLabel(uint16_t family, uint16_t msg_type);

    /// @brief Get a composite label of the member values with text message types.
    ///
    /// The format of the string:
    ///
    /// @code
    ///     <query type>-<response type>.<start_event>-<stop_event>.<subnet id>
    ///
    /// Example:
    ///
    ///     "DHCPDISCOVER-DHCPOFFER.socket_received.buffer_read.12"
    ///
    ///     or
    ///
    ///     "SOLICIT-ADVERTISE.socket_received.buffer_read.12"
    ///
    /// @endcode
    ///
    /// @return the composite label.
    std::string getLabel() const;

    /// @brief Get the StatsMgr formatted compatible name.
    ///
    /// @param value_name name of the specific value (e.g. "mean-usecs", "min-duration-usecs").
    /// The format of the string:
    ///
    /// @code
    ///
    ///     {subnet-id[x]}.perfmon.<query type>-<response type>.<start event>-<end event>.<value-name>
    ///
    /// Examples:
    ///
    ///  perfmon.discover-offer.socket_received-buffer_read.mean-usecs
    ///
    ///  subnet[9].perfmon.discover-offer.socket_received-buffer_read.mean-usecs
    ///
    /// @endcode
    ///
    /// @return the statistic name.
    std::string getStatName(const std::string& value_name) const;

    /// @brief Renders the the duration key as an Element.
    ///
    /// The element will appear as follows:
    ///
    /// @code
    /// {
    ///     "query-type": "discover",
    ///     "response-type": "offer",
    ///     "start-event": "socket_received",
    ///     "stop-event": "buffer_read",
    ///     "subnet-id": 10
    /// }
    /// @endcode
    ///
    /// @return Element::map containing the duration key values.
    virtual data::ElementPtr toElement() const;

    /// @brief Validates that a query and response message type pair is sane.
    ///
    /// @param family Protocol family of the key (AF_INET or AF_INET6)
    /// The format of the string:
    /// @param query_type message type of the query packet
    /// @param response_type message type of the response packet
    ///
    /// @throw BadValue is the pairing does not make sense.
    static void validateMessagePair(uint16_t family, uint8_t query_type, uint8_t response_type);

    /// @brief Equality operator.
    ///
    /// equality operator to compare two DurationKey objects.
    /// @param other DurationKey to be compared against.
    /// @return True the keys are equal
    bool operator==(const DurationKey& other) const;

    /// @brief Inequality operator.
    ///
    /// Inequality operator to compare two DurationKey objects.
    /// @param other DurationKey to be compared against.
    /// @return True the keys are not equal
    bool operator!=(const DurationKey& other) const;

    /// @brief Less than operator.
    ///
    /// less than operator to compare two DurationKey objects.
    /// @param other DurationKey to be compared against.
    /// @return True key is less than the other key
    bool operator<(const DurationKey& other) const;

protected:
    /// @brief Protocol family AF_INET or AF_INET6.
    uint16_t family_;

    /// @brief Query message type (e.g. DHCPDISCOVER, DHCP6_SOLICIT).
    uint8_t query_type_;

    /// @brief Response message type (e.g. DHCPOFFER, DHCP6_ADVERTISE).
    uint8_t response_type_;

    /// @brief Label of the start event which begins the duration.
    std::string start_event_label_;

    /// @brief Label of the end event which ends the duration.
    std::string stop_event_label_;

    /// @brief Subnet ID of the subnet selected during query fulfillment.
    isc::dhcp::SubnetID subnet_id_;
};

std::ostream&
operator<<(std::ostream& os, const DurationKey& key);

/// @brief Defines a pointer to a DurationKey instance.
typedef boost::shared_ptr<DurationKey> DurationKeyPtr;

class MonitoredDuration : public DurationKey {
public:
    /// @brief Constructor
    ///
    /// @param family protocol family AF_INET or AF_INET6
    /// @param query_type message type of the query packet
    /// @param response_type message type of the response packet
    /// @param start_event_label label of the start event
    /// @param stop_event_label label of the end event
    /// @param subnet_id id of the selected subnet
    /// @param interval_duration the interval duration
    MonitoredDuration(uint16_t family, uint8_t query_type, uint8_t response_type,
                      const std::string& start_event_label, const std::string& stop_event_label,
                      dhcp::SubnetID subnet_id, const Duration& interval_duration);

    /// @brief Constructor
    ///
    /// @param key composite key that identifies the alarm
    /// @param interval_duration the interval duration
    MonitoredDuration(const DurationKey& key, const Duration& interval_duration);

    /// @brief Copy Constructor
    ///
    /// @param rhs duration to copy
    MonitoredDuration(const MonitoredDuration& rhs);

    /// @brief Destructor
    virtual ~MonitoredDuration() = default;

    /// @brief Get the interval duration.
    ///
    /// @return Duration containing the interval duration.
    Duration getIntervalDuration() const {
        return (interval_duration_);
    }

    /// @brief Get the previous interval.
    ///
    /// @return Pointer to the previous interval if it exists or an empty pointer.
    DurationDataIntervalPtr getPreviousInterval() const {
        return (previous_interval_);
    }

    /// @brief Get the current interval.
    ///
    /// @return Pointer to the current interval if it exists or an empty pointer.
    DurationDataIntervalPtr getCurrentInterval() const {
        return (current_interval_);
    }

    /// @brief Get the current interval start time.
    ///
    /// @return Current interval's start time or MIN_TIME if there's no
    /// current interval.
    Timestamp getCurrentIntervalStart() const;

    /// @brief Add a sample to the duration's current interval.
    ///
    /// If there is no current interval start a new one otherwise if the current
    /// interval has expired move it to the previous interval, set the return flag
    /// to true, then start a new interval.
    /// Add the sample to the current interval.
    ///
    /// @param sample duration value to add
    ///
    /// @return True if there is a newly completed (i.e. previous) interval to report.
    bool addSample(const Duration& sample);

    /// @brief Concludes the current interval
    ///
    /// Rotates current interval to previous and resets curent interval to empty.
    ///
    /// @throw InvalidOperation if there is no current interval.
    void expireCurrentInterval();

    /// @brief Deletes the current and previous intervals.
    void clear();

    /// @brief Renders the the duration as an Element.
    ///
    /// The element includes the duration key and the previous interval
    /// content(if one) as follows:
    /// @code
    /// {
    ///     "duration-key": {
    ///         "query-type": "discover",
    ///         "response-type": "offer",
    ///         "start-event": "socket_received",
    ///         "stop-event": "buffer_read",
    ///         "subnet-id": 10
    ///      },
    ///      "start-time": "2024-01-18 10:11:19.498739",
    ///      "occurrences": 105,
    ///      "min-duration-usecs": 5300,
    ///      "max-duration-usecs": 9000,
    ///      "total-duration-usecs": 786500,
    ///      "mean-duration-usecs": 7490
    /// }
    /// @endcode
    ///
    /// If there is no previous interval, it will appears as follows:
    ///
    /// @code
    /// {
    ///     "duration-key": {
    ///         "query-type": "discover",
    ///         "response-type": "offer",
    ///         "start-event": "socket_received",
    ///         "stop-event": "buffer_read",
    ///         "subnet-id": 10
    ///      },
    ///      "start-time": "<none>",
    ///      "occurrences": 0,
    ///      "min-duration-usecs": 0,
    ///      "max-duration-usecs": 0,
    ///      "total-duration-usecs": 0,
    ///      "mean-duration-usecs": 0
    /// }
    /// @endcode
    ///
    /// @return Element::map containing the duration key values.
    virtual data::ElementPtr toElement() const;

    /// @brief Fetches a an Element::list of value row column names
    ///
    /// The list element includes the name of each column in a value row, in
    /// the order the values are stored in a value row.
    ///
    /// The values in the list in order are:
    ///
    /// -# "query-type"
    /// -# "response-type"
    /// -# "start-event"
    /// -# "stop-event"
    /// -# "subnet-id"
    /// -# "start-time"
    /// -# "occurrences"
    /// -# "min-duration-usecs"
    /// -# "max-duration-usecs"
    /// -# "total-duration-usecs"
    /// -# "mean-duration-usecs"
    ///
    /// @return Element::map containing the duration key values.
    static data::ConstElementPtr valueRowColumns();

    /// @brief Renders the the duration as an Element::list of values.
    ///
    /// The list element includes a value for each member of DurationKey
    /// and the previous interval. If there is no previous interval value of
    /// of "<none>" will be added for start-time and values of 0 for the
    /// remaining data values.
    ///
    /// The values in the list will be in the following order and type:
    ///
    /// -# query-type              Element::string
    /// -# response-type           Element::string
    /// -# start-event             Element::string
    /// -# stop-event              Element::string
    /// -# subnet-id               Element::int
    /// -# start-time              Element::string ex: "2024-01-18 10:11:19.498739" or "<none>",
    /// -# occurrences             Element::int
    /// -# min-duration-usecs      Element::int
    /// -# max-duration-usecs      Element::int
    /// -# total-duration-usecs    Element::int
    /// -# mean-duration-usecs     Element::int
    ///
    /// @return Element::map containing the duration key values.
    data::ElementPtr toValueRow() const;

private:
    /// @brief Length of the time of a single data interval.
    Duration interval_duration_;

    /// @brief Data interval into which samples are currently accumulating.
    DurationDataIntervalPtr current_interval_;

    /// @brief Closed data interval immediately prior to the current interval.
    DurationDataIntervalPtr previous_interval_;
};

typedef boost::shared_ptr<MonitoredDuration> MonitoredDurationPtr;

} // end of namespace isc::perfmon
} // end of namespace isc

#endif
