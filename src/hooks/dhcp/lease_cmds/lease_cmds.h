// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_CMDS_H
#define LEASE_CMDS_H

#include <cc/data.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace lease_cmds {

/// @brief Forward declaration of implementation class.
class LeaseCmdsImpl;

/// @brief Implements the logic for processing commands pertaining to
/// lease manipulation.
///
/// This class is used by the callouts implementing command handlers for
/// lease manipulations.
class LeaseCmds {
public:
    /// @brief Constructor.
    ///
    /// It creates an instance of the @c LeaseCmdsImpl.
    LeaseCmds();

    /// @brief lease4-add, lease6-add command handler
    ///
    /// This command attempts to add a lease.
    ///
    /// An example full command looks as follows. Note that the args
    /// parameter is expected to contain the "arguments" portion of it.
    /// This function covers both v4 and v6 leases.
    ///
    /// Example command for v4:
    /// {
    ///     "command": "lease4-add",
    ///     "parameters": {
    ///         "address": "192.0.2.1",
    ///         "hwaddr": "00:01:02:03:04:05",
    ///         "client-id": "this-is-a-client",
    ///         "valid-lft": 3600,
    ///         "expire": 12345678,
    ///         "subnet-id": 1,
    ///         "fqdn-fwd": true,
    ///         "fqdn-rev": true,
    ///         "hostname": "myhost.example.org",
    ///         "state": 0
    ///     }
    /// }
    /// Example command for v6:
    /// {
    ///     "command": "lease6-add",
    ///     "arguments": {
    ///         "subnet-id": 66,
    ///         "ip-address": "2001:db8:abcd::",
    ///         "type": "IA_PD",
    ///         "prefix-len": 48,
    ///         "duid": "01:02:03:04:05:06:07:08",
    ///         "iaid": 1234,
    ///         "preferred-lft": 500,
    ///         "valid-lft": 1000,
    ///         "expire": 12345678,
    ///         "fqdn-fwd": true,
    ///         "fqdn-rev": true,
    ///         "hostname": "urania.example.org""
    ///     }
    /// }

    ///
    /// @param command should be 'lease4-add' or 'lease6-add'
    /// @param args must contain host reservation definition.
    /// @return result of the operation
    data::ConstElementPtr
    leaseAddHandler(const std::string& command, data::ConstElementPtr args);

    /// @brief lease4-get, lease6-get command handler
    ///
    /// This command attempts to retrieve a lease that match selected criteria.
    /// The following types of parameters are supported:
    /// - (subnet-id, address) for both v4 and v6
    /// - (subnet-id, identifier-type, identifier) for v4
    /// - (subnet-id, type, iana, identifier-type, identifier) for v6
    ///
    /// Example command for query by (subnet-id, address):
    /// {
    ///     "command": "lease4-get",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "ip-address": "192.0.2.202"
    ///     }
    /// }
    ///
    /// Example command for query by (subnet-id, identifier-type, identifier)
    /// {
    ///     "command": "lease4-get",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "identifier-type": "hw-address",
    ///         "identifier": "00:01:02:03:04:05"
    ///     }
    /// }
    ///
    /// Example command for query by (subnet-id, type, iana, identifier-type,
    ///                               identifier):
    /// {
    ///     "command": "lease6-get",
    ///     "arguments": {
    ///     "subnet-id": 66,
    ///     "iaid": 42,
    ///     "type": "IA_NA",
    ///     "identifier-type": "duid",
    ///     "identifier": "77:77:77:77:77:77:77:77"
    ///     }
    /// }
    /// @param command "lease4-get" or "lease6-get"
    /// @param args must contain host reservation definition.
    /// @return result of the operation (includes lease details, if found)
    data::ConstElementPtr
    leaseGetHandler(const std::string& command, data::ConstElementPtr args);

    /// @brief lease4-del command handler
    ///
    /// This command attempts to delete an IPv4 lease that match selected
    /// criteria. Two types of parameters are supported: (subnet-id, address) or
    /// (subnet-id, identifier-type, identifier).
    ///
    /// Example command for deletion by (subnet-id, address):
    /// {
    ///     "command": "lease4-del",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "ip-address": "192.0.2.202"
    ///     }
    /// }
    ///
    /// Example command for deletion by (subnet-id, identifier-type, identifier)
    /// {
    ///     "command": "lease4-del",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "identifier-type": "hw-address",
    ///         "identifier": "00:01:02:03:04:05"
    ///     }
    /// }";
    /// @param command should be 'lease4-del' (but it's ignored)
    /// @param args must contain host reservation definition.
    /// @return result of the operation (host will be included as parameters, if found)
    data::ConstElementPtr
    lease4DelHandler(const std::string& command, data::ConstElementPtr args);

    /// @brief lease6-del command handler
    ///
    /// This command attempts to delete a lease that match selected criteria.
    /// Two types of parameters are supported: (subnet-id, address) or
    /// (subnet-id, type, iaid, identifier-type, identifier).
    ///
    /// Example command for deletion by (subnet-id, address):
    /// {
    ///     "command": "lease6-del",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "ip-address": "192.0.2.202"
    ///     }
    /// }
    ///
    /// Example command for deletion by (subnet-id, type, iaid, identifier-type,
    /// identifier):
    /// {
    ///     "command": "lease6-del",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "type": "IA_NA",
    ///         "iaid": 123456,
    ///         "identifier-type": "hw-address",
    ///         "identifier": "00:01:02:03:04:05"
    ///     }
    /// }";
    /// @param command should be 'lease6-del' (but it's ignored)
    /// @param args must contain host reservation definition.
    /// @return result of the operation (host will be included as parameters, if found)
    data::ConstElementPtr
    lease6DelHandler(const std::string& command, data::ConstElementPtr args);

    /// @brief lease4-update handler
    ///
    /// This command attempts to update existing IPv4 lease. The parameters
    /// specified will replace existing lease. The only condition is that
    /// the IP address must not change. If you want to change the IP address,
    /// please use lease4-del and lease4-add instead.
    ///
    /// Example command:
    /// {
    ///     "command": "lease4-update",
    ///     "arguments": {
    ///         "subnet-id": 44,
    ///         "ip-address": "192.0.2.1",
    ///         "hw-address": "1a:1b:1c:1d:1e:1f",
    ///         "hostname": "newhostname.example.org"
    ///     }
    /// };
    ///
    /// @param command - should be "lease4-update", but it is ignored
    /// @param args arguments that describe the lease being updated.
    data::ConstElementPtr
    lease4UpdateHandler(const std::string& command, data::ConstElementPtr args);

    /// @brief lease6-update handler
    ///
    /// This command attempts to update existing IPv6 lease. The parameters
    /// specified will replace existing lease. The only condition is that
    /// the IP address must not change. If you want to change the IP address,
    /// please use lease6-del and lease6-add instead.
    ///
    /// Example command:
    /// {
    ///     "command": "lease6-update",
    ///     "arguments": {
    ///         "subnet-id": 66,
    ///         "ip-address": "2001:db8::1",
    ///         "iaid": 7654321,
    ///         "duid": "88:88:88:88:88:88:88:88",
    ///         "hostname": "newhostname.example.org"
    ///     }
    /// }";
    ///
    /// @param command - should be "lease6-update" (but it is ignored)
    /// @param args arguments that describe the lease being updated.
    data::ConstElementPtr
    lease6UpdateHandler(const std::string& command, data::ConstElementPtr args);

    /// @brief lease4-wipe handler
    ///
    /// This commands attempts to remove all IPv4 leases from a specific
    /// subnet. Currently the leases are removed from the database,
    /// without any processing (like calling hooks or doing DDNS
    /// cleanups).
    ///
    /// Example command:
    /// {\n"
    ///     "command": "lease4-wipe",\n"
    ///     "arguments": {"
    ///         "subnet-id": 44
    ///     }\n"
    /// }";
    /// @param command - should be "lease4-wipe" (but is ignored)
    /// @param args arguments that describe the lease being updated.
    data::ConstElementPtr
    lease4WipeHandler(const std::string& command, data::ConstElementPtr args);

    /// @brief lease6-wipe handler
    ///
    /// This commands attempts to remove all IPv4 leases from a specific
    /// subnet. Currently the leases are removed from the database,
    /// without any processing (like calling hooks or doing DDNS
    /// cleanups).
    ///
    /// Example command:
    /// {\n"
    ///     "command": "lease4-wipe",\n"
    ///     "arguments": {"
    ///         "subnet-id": 44
    ///     }\n"
    /// }";
    /// @param command - should be "lease4-wipe" (but is ignored)
    /// @param args arguments that describe the lease being updated.
    data::ConstElementPtr
    lease6WipeHandler(const std::string& command, data::ConstElementPtr args);

private:
    /// Pointer to the actual implementation
    boost::shared_ptr<LeaseCmdsImpl> impl_;
};

};
};

#endif
