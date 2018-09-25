// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef STAMPED_ELEMENT_H
#define STAMPED_ELEMENT_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace isc {
namespace data {

/// @brief This class represents configuration element which is
/// associated with the modification timestamp.
///
/// Classes storing Kea configuration should derive from this object
/// to track modification times of the configuration objects. This
/// is specifically required by the Kea Configuration Backend feature
/// which stores configuration in the database and must be able
/// to recognize recently modified objects to fetch incremental
/// changes.
class StampedElement {
public:

    /// @brief Constructor.
    ///
    /// Sets timestamp to the current time.
    StampedElement();

    /// @brief Sets timestamp to the explicitly provided value.
    ///
    /// @param timestamp New timestamp value.
    void setModificationTime(const boost::posix_time::ptime& timestamp) {
        timestamp_ = timestamp;
    }

    /// @brief Sets timestmp to the current time.
    void updateModificationTime();

    /// @brief Returns timestamp.
    boost::posix_time::ptime getModificationTime() const {
        return (timestamp_);
    }

private:

    /// @brief Holds timestamp value.
    boost::posix_time::ptime timestamp_;

};

} // end of namespace isc::data
} // end of namespace isc

#endif
