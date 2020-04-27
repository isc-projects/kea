// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef STAT_CMDS_H
#define STAT_CMDS_H

#include <hooks/hooks.h>

#include <boost/shared_ptr.hpp>

namespace isc {
namespace stat_cmds {

/// @brief Forward declaration of implementation class.
class StatCmdsImpl;

/// @brief Implements the logic for processing commands pertaining to
/// stat manipulation.
///
/// This class is used by the callouts implementing command handlers for
/// stat manipulations.
class StatCmds {
public:
    /// @brief Default Constructor.
    StatCmds() {};

    /// @brief stat-lease4-get command handler
    ///
    /// This command attempts to fetch lease4 statistics for one or
    /// more subnets based upon subnet selection criteria (or lack thereof).
    /// It extracts the command name and arguments from the given Callouthandle,
    /// attempts to process them, and then set's the handle's "response"
    /// arguments accordingly.
    /// {
    ///     "command": "stat-lease4-get",
    ///     "arguments": {
    ///         "subnet-id": 10         // optional
    ///         "subnet-range": {       // optional
    ///             "first-subnet-id": 10,  // id >= 10
    ///             "last-subnet-id": 50    // id <= 50
    ///         }
    ///      }
    /// }
    ///
    /// It produces a response as described below:
    ///
    /// {
    ///     "result": 0,
    ///     "text": "<message>",
    ///     "arguments": {
    ///         "result-set": {
    ///             "timestamp": "2018-03-22 09:43:30.815371",
    ///             "columns": ["subnet_id", "total-addresses",
    ///                         "cumulative-assigned-addresses",
    ///                         "assigned-addresses", "declined-addresses"],
    ///             "rows": [
    ///                 [1, 600, 1000, 450, 3],
    ///                 :
    ///             ]
    ///         }
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    ///
    /// add command JSON text in the "command" argument
    /// @return result of the operation
    int
    statLease4GetHandler(hooks::CalloutHandle& handle);

    /// @brief stat-lease6-get command handler
    ///
    /// This command attempts to fetch lease6 statistics for one or
    /// more subnets based upon subnet selection criteria (or lack thereof).
    /// It extracts the command name and arguments from the given Callouthandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    /// {
    ///     "command": "stat-lease6-get",
    ///     "arguments": {
    ///         "subnet-id": 10         // optional
    ///         "subnet-range": {       // optional
    ///                 "first-subnet-id": 10,  // id >= 10
    ///                 "last-subnet-id":  50   // id <= 50
    ///         }
    ///      }
    /// }
    ///
    /// It produces a response as described below:
    ///
    /// {
    ///     "result": 0,
    ///     "text": "<message>",
    ///     "arguments": {
    ///         "result-set": {
    ///             "timestamp": "2018-03-22 09:43:30.815371",
    ///             "columns": ["subnet_id", "total-nas",
    ///                         "cumulative-assigned-nas",
    ///                         "assigned-nas", "declined-nas",
    ///                         "total-pds", "cumulative-assigned-pds",
    ///                         "assigned-pds"],
    ///             "rows": [
    ///                 [1, 600, 1000, 450, 3, 64, 20, 10],
    ///                 :
    ///             ]
    ///         }
    ///     }
    /// }
    ///
    ///
    /// @param handle Callout context - which is expected to contain the
    /// add command JSON text in the "command" argument
    /// @return result of the operation
    int
    statLease6GetHandler(hooks::CalloutHandle& handle);
};

};
};

#endif
