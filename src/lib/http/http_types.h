// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_TYPES_H
#define HTTP_TYPES_H

namespace isc {
namespace http {

/// @brief HTTP protocol version.
struct HttpVersion {
    unsigned major_; ///< Major HTTP version.
    unsigned minor_; ///< Minor HTTP version.

    /// @brief Constructor.
    ///
    /// @param major Major HTTP version.
    /// @param minor Minor HTTP version.
    explicit HttpVersion(const unsigned major, const unsigned minor)
        : major_(major), minor_(minor) {
    }

    /// @brief Operator less.
    ///
    /// @param rhs Version to compare to.
    bool operator<(const HttpVersion& rhs) const {
        return ((major_ < rhs.major_) ||
                ((major_ == rhs.major_) && (minor_ < rhs.minor_)));
    }

    /// @brief Operator equal.
    ///
    /// @param rhs Version to compare to.
    bool operator==(const HttpVersion& rhs) const {
        return ((major_ == rhs.major_) && (minor_ == rhs.minor_));
    }

    /// @brief Operator not equal.
    ///
    /// @param rhs Version to compare to.
    bool operator!=(const HttpVersion& rhs) const {
        return (!operator==(rhs));
    }

    /// @name Methods returning @c HttpVersion object encapsulating typical
    /// HTTP version numbers.
    //@{

    /// @brief HTTP version 1.0.
    static const HttpVersion& HTTP_10() {
        static HttpVersion ver(1, 0);
        return (ver);
    };

    /// @brief HTTP version 1.1.
    static const HttpVersion& HTTP_11() {
        static HttpVersion ver(1, 1);
        return (ver);
    }

    /// @brief HTTP version 2.0.
    static const HttpVersion& HTTP_20() {
        static HttpVersion ver(2, 0);
        return (ver);
    }

    //@}
};

} // end of namespace isc::http
} // end of namespace isc

#endif
