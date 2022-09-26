// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_PARSER_H
#define LEASE_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/srv_config.h>

namespace isc {
namespace lease_cmds {

/// @brief Parser for Lease4 structure
///
/// It expects the data in the following format:
/// {
///     "ip-address": "192.0.2.1",
///     "hw-address": "00:01:02:03:04:05",
///     "client-id": "this-is-a-client",
///     "valid-lft": 3600,
///     "cltt": 12345678,
///     "expire": 1499282530,
///     "subnet-id": 1,
///     "fqdn-fwd": true,
///     "fqdn-rev": true,
///     "hostname": "myhost.example.org",
///     "state": 0,
///     "user-context": { \"version\": 1 }
/// }
class Lease4Parser : public isc::data::SimpleParser {
public:

    /// @brief Parses Element tree and tries to convert to Lease4
    ///
    /// See @ref Lease6Parser class description for expected format.
    ///
    /// @param cfg Currently running config (used for sanity checks and defaults)
    /// @param lease_info structure to be parsed
    /// @param [out] force_create indicates if the lease should be created when it
    /// doesn't exist.
    /// @return A pointer to Lease4
    /// @throw BadValue if any of the parameters is invalid
    /// @throw DhcpConfigError if mandatory parameter is missing
    /// @throw LeaseCmdsConflict when specified subnet-id does not match the lease
    /// or the lease address does not match the subnet range.
    virtual isc::dhcp::Lease4Ptr parse(isc::dhcp::ConstSrvConfigPtr& cfg,
                                       const isc::data::ConstElementPtr& lease_info,
                                       bool& force_create);

    /// @brief virtual dtor (does nothing)
    virtual ~Lease4Parser() {}
};

/// @brief Parser for Lease6 structure
///
/// {
///     "address": "2001:db8::1",
///     "duid": "00:01:02:03:04:05",
///     "type": "IA_NA",
///     "cltt": 12345678,
///     "preferred-lft": 3600,
///     "valid-lft": 3600,
///     "expire": 1499282530,
///     "subnet-id": 1,
///     "fqdn-fwd": true,
///     "fqdn-rev": true,
///     "hostname": "myhost.example.org",
///     "state": 0,
///     "user-context": { \"version\": 1 }
/// }

/// It expects the input data to use the following format:
class Lease6Parser : public isc::data::SimpleParser {
public:
    /// @brief Parses Element tree and tries to convert to Lease4
    ///
    /// See @ref Lease6Parser class description for expected format.
    ///
    /// @param cfg Currently running config (used for sanity checks and defaults)
    /// @param lease_info structure to be parsed
    /// @param [out] force_create indicates if the lease should be created when it
    /// doesn't exist.
    /// @return A pointer to Lease4
    /// @throw BadValue if any of the parameters is invalid
    /// @throw DhcpConfigError if mandatory parameter is missing
    /// @throw LeaseCmdsConflict when specified subnet-id does not match the lease
    /// or the lease address does not match the subnet range.
    virtual isc::dhcp::Lease6Ptr parse(isc::dhcp::ConstSrvConfigPtr& cfg,
                                       const isc::data::ConstElementPtr& lease_info,
                                       bool& force_create);

    /// @brief virtual dtor (does nothing)
    virtual ~Lease6Parser() {}
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif
