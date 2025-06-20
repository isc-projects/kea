// Copyright (C) 2016-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOOKS_LIBINFO_H
#define HOOKS_LIBINFO_H

#include <cc/data.h>

#include <boost/shared_ptr.hpp>

#include <string>
#include <vector>
#include <utility>

namespace isc {
namespace hooks {

/// @brief Entity that holds information about hook libraries and their
/// parameters.
struct HookLibInfo {
    HookLibInfo(const std::string& libname,
                isc::data::ConstElementPtr parameters,
                const std::string& cfgname = "");

    /// @brief Full file path of the library.
    std::string libname_;

    /// @brief Set of configured parameters (if any)
    data::ConstElementPtr parameters_;

    /// @brief Configured library name (e.g. rom 'library')
    std::string cfgname_;

    /// @brief Compare two HookLibInfos for equality
    ///
    /// @param other HookLibInfo object with which to compare
    bool operator==(const HookLibInfo& other) const;

    /// @brief Compare two HookLibInfos for inequality
    ///
    /// @param other lease6 object with which to compare
    bool operator!=(const HookLibInfo& other) const {
        return (!operator==(other));
    }
};

/// @brief A storage for information about hook libraries.
typedef std::vector<HookLibInfo> HookLibsCollection;

/// @brief Shared pointer to collection of hooks libraries.
typedef boost::shared_ptr<HookLibsCollection> HookLibsCollectionPtr;

/// @brief Extracts library names from full library information structure
std::vector<std::string> extractNames(const HookLibsCollection& libinfo);

}  // namespace hooks
}  // namespace isc

#endif
