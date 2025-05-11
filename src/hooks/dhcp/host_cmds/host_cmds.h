// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_CMDS_H
#define HOST_CMDS_H

#include <hooks/hooks.h>

#include <boost/shared_ptr.hpp>

namespace isc {
namespace host_cmds {

/// @brief Forward declaration of implementation class.
class HostCmdsImpl;

/// @brief A wrapper class that provides handlers for the commands supported
/// by this hooks library.
///
/// This class exposes handlers for each command supported by the host_cmds
/// hooks library. Currently supported operations are:
/// - add reservation(s) for a host
/// - get reservation(s) for a host
/// - delete reservation(s) for a host
/// - get all reservations in a subnet
/// - get all reservations optionally in a subnet by page
/// - get all reservations with a hostname
/// - get all reservations with an identifier
///
/// The reservations can only be stored in a database (via host database backend),
/// i.e. manipulating host reservations held in server's memory (those that
/// are fetched from the server configuration file) is not supported.
///
/// When non-global host reservation is added, the library will check if the
/// subnet for the specified subnet-id exists in the server's configuration.
/// It is not possible to add the host reservation for non-configured subnet.
/// Also, when the host reservations are added, each reserved IP address is
/// validated by checking if it belongs to the subnet prefix. This check is
/// not performed for the reservation of the delegated prefixes, because
/// delegated prefixes do not have to match the subnet prefix.
///
/// The library does not check if the subnet exists or if the specified
/// reservation matches the subnet prefix for the 'reservation-get' and
/// 'reservation-del' commands. This allows for fetching and deleting
/// reservations from the database, even if the corresponding subnet
/// no longer exists, e.g. might be especially useful for cleaning up
/// the database from the dangling reservations.
///
/// For an actual implementation, see @ref HostCmdsImpl class in host_cmds.cc file.
class HostCmds {
public:
    /// @brief Constructor.
    ///
    /// It creates an instance of the @c HostCmdsImpl.
    HostCmds();

    /// @brief reservation-add command handler
    ///
    /// This command attempts to add host reservation.
    ///
    /// An example full command looks as follows. Note that the args
    /// parameter is expected to contain the "arguments" portion of it.
    /// Also, the syntax differs from what is defined in the configuration
    /// file with one important detail. There is subnet-id defined. This
    /// information is mandatory when adding new reservations.
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then sets the handle's "response"
    /// argument accordingly.
    ///
    /// Example command
    ///{
    ///    "command": "reservation-add",
    ///    "arguments": {
    ///        "reservation": {
    ///            "subnet-id": 1,
    ///            "hw-address": "1a:1b:1c:1d:1e:1f",
    ///            "ip-address": "192.0.2.202"
    ///        }
    ///    }
    ///}
    ///
    /// @param handle Callout context - which is expected to contain the
    /// add command JSON text in the "command" argument
    /// @return result of the operation
    int
    reservationAddHandler(hooks::CalloutHandle& handle);

    /// @brief reservation-get command handler
    ///
    /// This command attempts to retrieve a host that match selected criteria.
    /// Two types of parameters are supported: (subnet-id, address) or
    /// (subnet-id, identifier-type, identifier).
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then sets the handle's "response"
    /// argument accordingly.
    ///
    /// Example command for query by (subnet-id, address):
    /// {
    ///     "command": "reservation-get",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "ip-address": "192.0.2.202"
    ///     }
    /// }
    ///
    /// Example command for query by (subnet-id, identifier-type, identifier)
    /// {
    ///     "command": "reservation-get",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "identifier-type": "hw-address",
    ///         "identifier": "00:01:02:03:04:05"
    ///     }
    /// }";
    ///
    /// @param handle Callout context - which is expected to contain the
    /// get command JSON text in the "command" argument
    /// @return result of the operation
    int
    reservationGetHandler(hooks::CalloutHandle& handle);

    /// @brief reservation-del command handler
    ///
    /// This command attempts to delete a host that match selected criteria.
    /// Two types of parameters are supported: (subnet-id, address,
    /// operation-target) or (subnet-id, identifier-type, identifier,
    /// operation-target).
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then sets the handle's "response"
    /// argument accordingly.
    ///
    /// Note: for this operation to work while the operation-target was set to
    /// ALTERNATE_SOURCES, hosts-database must be specified in your
    /// configuration file (or from code point of view, alternate_source_
    /// must be set in HostMgr).
    ///
    /// Example command for query by (subnet-id, address, and default
    /// operation-target):
    /// {
    ///     "command": "reservation-del",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "ip-address": "192.0.2.202"
    ///     }
    /// }
    ///
    /// Example command for query by (subnet-id, identifier-type, identifier,
    /// and operation-target):
    /// {
    ///     "command": "reservation-del",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "identifier-type": "hw-address",
    ///         "identifier": "00:01:02:03:04:05",
    ///         "operation-target": "all-sources"
    ///     }
    /// }";
    /// @param handle Callout context - which is expected to contain the
    /// del command JSON text in the "command" argument
    /// @return result of the operation
    int
    reservationDelHandler(hooks::CalloutHandle& handle);

    /// @brief reservation-get-all command handler
    ///
    /// This command attempts to retrieve all hosts in a subnet.
    /// Supported parameters are: (subnet-id).
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then sets the handle's "response"
    /// argument accordingly.
    ///
    /// Example command for query:
    /// {
    ///     "command": "reservation-get-all",
    ///     "arguments": {
    ///         "subnet-id": 1
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// reservation-get-all command JSON text in the "command" argument.
    /// @return result of the operation
    int
    reservationGetAllHandler(hooks::CalloutHandle& handle);

    /// @brief reservation-get-page command handler
    ///
    /// This command attempts to retrieve a page of hosts in a subnet.
    /// Supported parameters are: (subnet-id, limit, source-index, from).
    /// At the exception of limit all parameters are optional,
    /// source-index and from host-id default to 0.
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then sets the handle's "response"
    /// argument accordingly.
    ///
    /// Example command for query:
    /// {
    ///     "command": "reservation-get-page",
    ///     "arguments": {
    ///         "subnet-id": 1,
    ///         "limit": 100,
    ///         "source-index": 1,
    ///         "from": 12345
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// reservation-get-page command JSON text in the "command" argument.
    /// @return result of the operation
    int
    reservationGetPageHandler(hooks::CalloutHandle& handle);

    /// @brief reservation-get-by-hostname command handler
    ///
    /// This command attempts to retrieve all hosts with a hostname
    /// and optionally in a subnet.
    /// Supported parameters are: (hostname, subnet-id).
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then sets the handle's "response"
    /// argument accordingly.
    ///
    /// Example command for query:
    /// {
    ///     "command": "reservation-get-by-hostname",
    ///     "arguments": {
    ///         "hostname": "foobar"
    ///     }
    /// }
    ///
    /// Example command for query with a subnet:
    /// {
    ///     "command": "reservation-get-by-hostname",
    ///     "arguments": {
    ///         "hostname": "foobar",
    ///         "subnet-id": 1
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// reservation-get-by-hostname command JSON text in the "command" argument.
    /// @return result of the operation
    int
    reservationGetByHostnameHandler(hooks::CalloutHandle& handle);

    /// @brief reservation-get-by-id command handler
    ///
    /// This command attempts to retrieve all hosts with an identifier.
    /// Supported parameters are: (identifier-type, identifier).
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then sets the handle's "response"
    /// argument accordingly.
    ///
    /// Example command for query:
    /// {
    ///     "command": "reservation-get-by-id",
    ///     "arguments": {
    ///         "identifier-type": "hw-address",
    ///         "identifier": "00:01:02:03:04:05"
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// reservation-get-by-id command JSON text in the "command" argument.
    /// @return result of the operation
    int
    reservationGetByIdHandler(hooks::CalloutHandle& handle);

    /// @brief reservation-get-by-address command handler
    ///
    /// This command attempts to retrieve all hosts with a given IP address
    /// and optionally in a subnet.
    /// Supported parameters are: (ip-address, subnet-id, operation-target).
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then sets the handle's "response"
    /// argument accordingly.
    ///
    /// Example command for query:
    /// {
    ///     "command": "reservation-get-by-address",
    ///     "arguments": {
    ///         "ip-address": "192.168.0.1"
    ///     }
    /// }
    ///
    /// Example command for query with a subnet:
    /// {
    ///     "command": "reservation-get-by-address",
    ///     "arguments": {
    ///         "ip-address": "192.168.0.1",
    ///         "subnet-id": 1
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// reservation-get-by-address command JSON text in the "command" argument.
    /// @return result of the operation
    int
    reservationGetByAddressHandler(hooks::CalloutHandle& handle);

    /// @brief reservation-update command handler
    ///
    /// This command attempts to update an existing host reservation.
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then sets the handle's response
    /// argument accordingly.
    ///
    /// The structure differs from a reservation defined in the configuration
    /// file with one important detail: subnet-id is defined. This information
    /// is mandatory.
    ///
    /// Example command:
    /// {
    ///     "command": "reservation-update",
    ///     "arguments": {
    ///         "reservation": {
    ///             "subnet-id": 1,
    ///             "hw-address": "1a:1b:1c:1d:1e:1f",
    ///             "ip-address": "192.0.2.202"
    ///         }
    ///     }
    /// }
    ///
    /// @param handle callout context
    ///
    /// @return 0 for success, non-zero in case of failure
    int
    reservationUpdateHandler(hooks::CalloutHandle& handle);

private:

    /// Pointer to the actual implementation
    boost::shared_ptr<HostCmdsImpl> impl_;
};

}  // namespace host_cmds
}  // namespace isc

#endif
