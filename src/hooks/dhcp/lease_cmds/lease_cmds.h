// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_CMDS_H
#define LEASE_CMDS_H

#include <cc/data.h>
#include <hooks/hooks.h>

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
    /// It extracts the command name and arguments from the given Callouthandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
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
    ///
    /// @param handle Callout context - which is expected to contain the
    /// add command JSON text in the "command" argument
    /// @return result of the operation
    int
    leaseAddHandler(hooks::CalloutHandle& handle);

    /// @brief lease6-bulk-apply command handler
    ///
    /// This command conveys information about multiple leases to be added,
    /// updated or deleted. This command should be used instead of lease6-add,
    /// lease6-update and lease6-del when it is desired to apply multiple
    /// lease changes within a single transaction. This is much faster and
    /// should be used in cases when the performance is critical. This
    /// command was added as a result of our experience with High Availability
    /// where multiple IPv6 addresses and/or prefixes can be allocated for
    /// a single DHCPv6 packet.
    ///
    /// Example structure of the command:
    ///
    /// {
    ///     "command": "lease6-bulk-apply",
    ///     "arguments": {
    ///         "deleted-leases": [
    ///             {
    ///                 "subnet-id": 66,
    ///                 "ip-address": "2001:db8:abcd::",
    ///                 "type": "IA_PD",
    ///                 ...
    ///             },
    ///             {
    ///                 "subnet-id": 66,
    ///                 "ip-address": "2001:db8:abcd::234",
    ///                 "type": "IA_NA",
    ///                 ...
    ///             }
    ///         ],
    ///         "leases": [
    ///             {
    ///                 "subnet-id": 66,
    ///                 "ip-address": "2001:db8:cafe::",
    ///                 "type": "IA_PD",
    ///                 ...
    ///             },
    ///             {
    ///                 "subnet-id": 66,
    ///                 "ip-address": "2001:db8:abcd::333",
    ///                 "type": "IA_NA",
    ///                 ...
    ///             }
    ///         ]
    ///     }
    /// }
    ///
    /// The response indicates which of the leases failed to be applied.
    /// For example:
    ///
    /// {
    ///     "result": 0,
    ///     "text": IPv6 leases bulk apply completed.
    ///     "arguments": {
    ///         "failed-deleted-leases": [
    ///             {
    ///                 "subnet-id": 66,
    ///                 "ip-address": "2001:db8:abcd::",
    ///                 "type": "IA_PD"
    ///             }
    ///         ],
    ///         "failed-leases": [
    ///             {
    ///                 "subnet-id": 66,
    ///                 "ip-address": "2001:db8:cafe::",
    ///                 "type": "IA_PD",
    ///                 ...
    ///             }
    ///         ]
    ///     }
    /// }
    ///
    /// The command handler first attempts to delete all leases listed in
    /// the "deleted-leases" list. Next, it adds the leases listed in the
    /// "leases" list. If any of these leases already exists, it is updated.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// add command JSON text in the "command" argument
    /// @return result of the operation
    int
    lease6BulkApplyHandler(hooks::CalloutHandle& handle);

    /// @brief lease4-get, lease6-get command handler
    ///
    /// This command attempts to retrieve a lease that match selected criteria.
    /// It extracts the command name and arguments from the given Callouthandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
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
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    /// @return result of the operation (includes lease details, if found),
    /// 1 if an error occurs, 3 if lease not found.
    int
    leaseGetHandler(hooks::CalloutHandle& handle);

    /// @brief lease4-get-all, lease6-get-all commands handler
    ///
    /// These commands attempt to retrieve all IPv4 or IPv6 leases,
    /// or all IPv4 or all IPv6 leases belonging to the particular
    /// subnets. If no subnet identifiers are provided, it returns all
    /// IPv4 or IPv6 leases from the database.
    ///
    /// Example command for IPv4 query by (subnet-ids):
    /// {
    ///     "command": "lease4-get-all",
    ///     "arguments": {
    ///         "subnets": [ 1, 2, 3, 4 ]
    ///     }
    /// }
    ///
    /// Example command for retrieving all IPv6 leases:
    /// {
    ///     "command": "lease6-get-all",
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    /// @return 0 if the handler has been invoked successfully, 1 if an
    /// error occurs, 3 if no leases are returned.
    int
    leaseGetAllHandler(hooks::CalloutHandle& handle);

    /// @brief lease4-get-page, lease6-get-page commands handler
    ///
    /// These commands attempt to retrieve 1 page of all IPv4 or IPv6
    /// leases. The size of the page is specified by the caller. The
    /// caller also specifies the last address returned in the previous
    /// page. The new page starts from the first address following the
    /// address specified by the caller. If the first page should be
    /// returned the IPv4 zero address, IPv6 zero address or the keyword
    /// "start" should be provided instead of the last address.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get commands JSON text in the "command" argument.
    /// @return 0 if the handler has been invoked successfully, 1 if an
    /// error occurs, 3 if no leases are returned.
    int
    leaseGetPageHandler(hooks::CalloutHandle& handle);

    /// @brief lease4-get-by-hw-address command handler
    ///
    /// This command attempts to retrieve all IPv4 leases with a particular
    /// hardware address.
    ///
    /// Example command:
    /// {
    ///     "command": "lease4-get-by-hw-address",
    ///     "arguments": {
    ///         "hwaddr": "00:01:02:03:04:05"
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    /// @return 0 if the handler has been invoked successfully, 1 if an
    /// error occurs, 3 if no leases are returned.
    int
    leaseGetByHwAddressHandler(hooks::CalloutHandle& handle);

    /// @brief lease4-get-by-client-id command handler
    ///
    /// This command attempts to retrieve all IPv4 leases with a particular
    /// Client Id.
    ///
    /// Example command:
    /// {
    ///     "command": "lease4-get-by-client-id",
    ///     "arguments": {
    ///         "client-id": "this-is-a-client"
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    /// @return 0 if the handler has been invoked successfully, 1 if an
    /// error occurs, 3 if no leases are returned.
    int
    leaseGetByClientIdHandler(hooks::CalloutHandle& handle);

    /// @brief lease6-get-by-duid command handler
    ///
    /// This command attempts to retrieve all IPv6 leases with a particular
    /// DUID.
    ///
    /// Example command:
    /// {
    ///     "command": "lease6-get-by-duid",
    ///     "arguments": {
    ///         "duid": "01:02:03:04:05:06:07:08"
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    /// @return 0 if the handler has been invoked successfully, 1 if an
    /// error occurs, 3 if no leases are returned.
    int
    leaseGetByDuidHandler(hooks::CalloutHandle& handle);

    /// @brief lease4-get-by-hostname and lease6-get-by-hostname commands
    /// handler
    ///
    /// These commands attempt to retrieve all IPv4 or Ipv6 leases with
    /// a particular hostname.
    ///
    /// Example command for v4:
    /// {
    ///     "command": "lease4-get-by-hostname",
    ///     "arguments": {
    ///         "hostname": "urania.example.org"
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    /// @return 0 if the handler has been invoked successfully, 1 if an
    /// error occurs, 3 if no leases are returned.
    int
    leaseGetByHostnameHandler(hooks::CalloutHandle& handle);

    /// @brief lease4-del command handler
    ///
    /// This command attempts to delete an IPv4 lease that match selected
    /// criteria.
    /// It extracts the command name and arguments from the given Callouthandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// Two types of parameters are supported: (subnet-id, address) or
    /// (subnet-id, identifier-type, identifier).
    ///
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
    ///
    /// @param handle Callout context - which is expected to contain the
    /// delete command JSON text in the "command" argument
    /// @return result of the operation
    int
    lease4DelHandler(hooks::CalloutHandle& handle);

    /// @brief lease6-del command handler
    ///
    /// This command attempts to delete a lease that match selected criteria.
    /// It extracts the command name and arguments from the given Callouthandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
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
    ///
    /// @param handle Callout context - which is expected to contain the
    /// delete command JSON text in the "command" argument
    /// @return result of the operation
    int
    lease6DelHandler(hooks::CalloutHandle& handle);

    /// @brief lease4-update handler
    ///
    /// This command attempts to update existing IPv4 lease. The parameters
    /// specified will replace existing lease. The only condition is that
    /// the IP address must not change. If you want to change the IP address,
    /// please use lease4-del and lease4-add instead.
    /// It extracts the command name and arguments from the given Callouthandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
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
    /// The optional 'force-create' boolean parameter may be specified to force
    /// the lease to be created if it doesn't exist. By default, this parameter
    /// is set to false, which means that the lease is not created.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// update command JSON text in the "command" argument
    /// @return result of the operation
    int
    lease4UpdateHandler(hooks::CalloutHandle& handle);

    /// @brief lease6-update handler
    ///
    /// This command attempts to update existing IPv6 lease. The parameters
    /// specified will replace existing lease. The only condition is that
    /// the IP address must not change. If you want to change the IP address,
    /// please use lease6-del and lease6-add instead.
    /// It extracts the command name and arguments from the given Callouthandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
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
    /// The optional 'force-create' boolean parameter may be specified to force
    /// the lease to be created if it doesn't exist. By default, this parameter
    /// is set to false, which means that the lease is not created.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// update command JSON text in the "command" argument
    /// @return result of the operation
    int
    lease6UpdateHandler(hooks::CalloutHandle& handle);

    /// @brief lease4-wipe handler
    ///
    /// This commands attempts to remove all IPv4 leases from a specific
    /// subnet. Currently the leases are removed from the database,
    /// without any processing (like calling hooks or doing DDNS
    /// cleanups).
    /// It extracts the command name and arguments from the given Callouthandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// Example command:
    /// {
    ///     "command": "lease4-wipe",
    ///     "arguments": {
    ///         "subnet-id": 44
    ///     }
    /// }";
    ///
    /// @param handle Callout context - which is expected to contain the
    /// wipe command JSON text in the "command" argument
    /// @return result of the operation
    int
    lease4WipeHandler(hooks::CalloutHandle& handle);

    /// @brief lease6-wipe handler
    ///
    /// This commands attempts to remove all IPv4 leases from a specific
    /// subnet. Currently the leases are removed from the database,
    /// without any processing (like calling hooks or doing DDNS
    /// cleanups).
    /// It extracts the command name and arguments from the given Callouthandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// Example command:
    /// {
    ///     "command": "lease4-wipe",
    ///     "arguments": {
    ///         "subnet-id": 44
    ///     }
    /// };
    ///
    /// @param handle Callout context - which is expected to contain the
    /// wipe command JSON text in the "command" argument
    /// @return result of the operation
    int
    lease6WipeHandler(hooks::CalloutHandle& handle);

private:
    /// Pointer to the actual implementation
    boost::shared_ptr<LeaseCmdsImpl> impl_;
};

};
};

#endif
