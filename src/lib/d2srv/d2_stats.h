// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D2_STATS_H
#define D2_STATS_H

#include <set>
#include <string>

namespace isc {
namespace d2 {

/// @brief Statistics Names.
class D2Stats {
public:
    /// @brief Global NCR statistics names.
    ///
    /// - ncr-received
    /// - ncr-invalid
    /// - ncr-error
    static std::set<std::string> ncr;

    /// @brief Global DNS update statistics names.
    ///
    /// - update-sent
    /// - update-signed
    /// - update-unsigned
    /// - update-success
    /// - update-timeout
    /// - update-error
    static std::set<std::string> update;

    /// @brief Key DNS update statistics names.
    ///
    /// - update-sent
    /// - update-success
    /// - update-timeout
    /// - update-error
    static std::set<std::string> key;
};

} // namespace d2
} // namespace isc

#endif // D2_STATS_H
