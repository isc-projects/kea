// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D2_STATS_H
#define D2_STATS_H

#include <list>
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
    static const std::list<std::string> ncr;

    /// @brief Global DNS update statistics names.
    ///
    /// - update-sent
    /// - update-signed
    /// - update-unsigned
    /// - update-success
    /// - update-timeout
    /// - update-error
    static const std::list<std::string> update;

    /// @brief Key DNS update statistics names.
    ///
    /// - update-sent
    /// - update-success
    /// - update-timeout
    /// - update-error
    static const std::list<std::string> key;

    /// @brief Initialize D2 statistics.
    ///
    /// @note: Add default samples if needed.
    static void init();
};

} // namespace d2
} // namespace isc

#endif // D2_STATS_H
