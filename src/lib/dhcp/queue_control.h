// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QUEUE_CONTROL_H
#define QUEUE_CONTROL_H

#include <cc/cfg_to_element.h>
#include <cc/user_context.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Represents DHCP packet queue controls 
///
/// This class manages the configurable parameters used to tailor the
/// behavior of DHCP packet queueing.
class QueueControl : public isc::data::UserContext, public isc::data::CfgToElement {
public:

    /// @brief Constructor.
    QueueControl();

    /// @brief Destructor
    ~QueueControl(){};

    /// @return true if objects are equal, false otherwise.
    bool equals(const QueueControl& other) const;

    /// @brief Fetches the queue type 
    ///
    /// @return string containg the queue type
    std::string getQueueType() const {
        return (queue_type_);
    }

    /// @brief Sets the queue type
    ///
    /// @param queue_type new value for the queue type
    void setQueueType(const std::string& queue_type) {
        queue_type_ = queue_type;
    }

    /// @brief Fetches the maximum number of packets that the queue may hold.
    ///
    /// @return the current capacity of the packet queue.
    size_t getCapacity() const {
        return (capacity_);
    }

    /// @brief Set the capacity of the DHCPv4 packet queue buffer.
    ///
    /// Sets the maximum number of packets that the queue may hold.
    ///
    /// @param capacity new value for the queue capacity
    void setCapacity(const size_t capacity) {
        capacity_ = capacity;
    }

    /// @brief Equality operator.
    ///
    /// @param other Object to be compared with this object.
    ///
    /// @return true if objects are equal, false otherwise.
    bool operator==(const QueueControl& other) const {
        return (equals(other));
    }

    /// @brief Inequality operator.
    ///
    /// @param other Object to be compared with this object.
    ///
    /// @return true if objects are not equal, false otherwise.
    bool operator!=(const QueueControl& other) const {
        return (!equals(other));
    }

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

private:
    /// @brief Name of the queue type
    /// This is the value used to uniquely identify/register
    /// packet queue implementations 
    std::string  queue_type_;

    /// @brief A set of interface names specified by the user.
    size_t  capacity_;
};

/// @brief A pointer to the @c QueueControl .
typedef boost::shared_ptr<QueueControl> QueueControlPtr;

/// @brief A pointer to the const @c QueueControl.
typedef boost::shared_ptr<const QueueControl> ConstQueueControlPtr;

}
}

#endif // QUEUE_CONTROL_H
