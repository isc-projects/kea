// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_MULTI_THREADING_H
#define CFG_MULTI_THREADING_H

#include <cc/data.h>

namespace isc {
namespace dhcp {

/// @brief Utility class to apply multi threading configurations
class CfgMultiThreading {
public:

    /// @brief apply multi threading configuration
    ///
    /// @param value The multi-threading configuration
    static void apply(data::ConstElementPtr value);

    /// @brief Extract multi-threading parameters from a given configuration.
    ///
    /// If the configuration does not contain the enable parameter,
    /// multi-threading is disabled. This is very useful as a default value for
    /// unit tests, so that they are kept simple, and that they can enable
    /// multi-threading on their own if it is in their scope to test MT.
    ///
    /// @param[in] value The multi-threading configuration
    /// @param[out] enabled The enabled flag
    /// @param[out] thread_count The thread count
    /// @param[out] queue_size The queue size
    static void extract(data::ConstElementPtr value, bool& enabled,
                        uint32_t& thread_count, uint32_t& queue_size);
};

}  // namespace dhcp
}  // namespace isc

#endif // CFG_MULTI_THREADING_H
