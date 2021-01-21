// Copyright (C) 2019,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASE_STAMPED_ELEMENT_H
#define BASE_STAMPED_ELEMENT_H

#include <cc/data.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace isc {
namespace data {

/// @brief This class represents configuration element which is
/// associated with database identifier and the modification
/// timestamp.
///
/// The @c StampedElement class derives from this class to extend
/// it with the capability to associate the configuration elements
/// with server tags. The @c db::Server class derives from it to
/// store a single server tag identifying a server it describes.
///
/// @note This class is not derived from @c Element and should not
/// be confused with the classes being derived from @c Element class.
/// Those classes are used to represent JSON structures, whereas this
/// class represents data fetched from the database.
class BaseStampedElement {
public:

    /// @brief Constructor.
    ///
    /// Sets timestamp to the current time.
    BaseStampedElement();

    /// @brief Sets element's database identifier.
    ///
    /// @param id New id.
    void setId(const uint64_t id) {
        id_ = id;
    }

    /// @brief Returns element's database identifier.
    uint64_t getId() const {
        return (id_);
    }

    /// @brief Sets timestamp to the explicitly provided value.
    ///
    /// @param timestamp New timestamp value.
    void setModificationTime(const boost::posix_time::ptime& timestamp) {
        timestamp_ = timestamp;
    }

    /// @brief Sets timestamp to the current time.
    void updateModificationTime();

    /// @brief Returns timestamp.
    boost::posix_time::ptime getModificationTime() const {
        return (timestamp_);
    }

protected:

    /// @brief Database identifier of the configuration element.
    ///
    /// The default value of 0 indicates that the identifier is
    /// not set.
    uint64_t id_;

    /// @brief Holds timestamp value.
    boost::posix_time::ptime timestamp_;
};

} // end of namespace isc::data
} // end of namespace isc

#endif
