// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SFLQ_CMDS_H
#define SFLQ_CMDS_H

#include <config.h>
#include <config/cmds_impl.h>
#include <cc/data.h>
#include <asiolink/io_address.h>
#include <database/db_exceptions.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/subnet_id.h>

#include <string>
#include <sstream>

namespace isc {
namespace lease_cmds {

/// @brief Implements the logic for processing commands pertaining to
/// SFLQ pools and data.
class SflqCmdsImpl : private config::CmdsImpl {
public:
    /// @brief Constructor.
    SflqCmdsImpl() {};

    /// @brief Destructor.
    virtual ~SflqCmdsImpl() {};

    /// @brief The 'sflq-pool4-create' command handler
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool4-create",
    ///     "arguments": {
    ///         "start-address": "192.0.2.0",
    ///         "end-address": "192.0.2.255",
    ///         "subnet-id": 77,
    ///         "recreate": true
    ///     }
    /// }
    ///
    /// The 'recreate' parameter is optional, it defaults false.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool4CreateHandler(hooks::CalloutHandle& handle);

    /// @brief The 'sflq-pool4-get-all' command handler
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool4-get-all",
    ///     "arguments": {
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool4GetAllHandler(hooks::CalloutHandle& handle);

    /// @brief The 'sflq-pool4-by-subnet' command handler
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool4-get-by-subnet",
    ///     "arguments": {
    ///         "subnet-id" : 100
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool4GetBySubnetHandler(hooks::CalloutHandle& handle);

    /// @brief Handles a 'sflq-pool4-by-range' command
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool4-get-by-range",
    ///     "arguments": {
    ///         "start-address": "192.0.2.0",
    ///         "end-address": "192.0.2.255"
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool4GetByRangeHandler(hooks::CalloutHandle& handle);

    /// @brief Delete the SFLQ V4 pool that matches a start and end address.
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool4-del",
    ///     "arguments": {
    ///         "start-address": "192.0.2.0",
    ///         "end-address": "192.0.2.255",
    ///         "force": false
    ///     }
    /// }
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool4DelHandler(hooks::CalloutHandle& handle);

    /// @brief The 'sflq-pool6-create' command handler
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool6-create",
    ///     "arguments": {
    ///         "start-address": "3001::",
    ///         "end-address": "3001::FF",
    ///         "subnet-id": 77,
    ///         "lease-type" : "IA_PD",
    ///         "delegated_len: 64
    ///         "recreate": true
    ///     }
    /// }
    ///
    /// The 'recreate' parameter is optional, it defaults false.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool6CreateHandler(hooks::CalloutHandle& handle);

    /// @brief The 'sflq-pool6-get-all' command handler
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool6-get-all",
    ///     "arguments": {
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool6GetAllHandler(hooks::CalloutHandle& handle);

    /// @brief The 'sflq-pool6-by-subnet' command handler
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool6-get-by-subnet",
    ///     "arguments": {
    ///         "subnet-id" : 100
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool6GetBySubnetHandler(hooks::CalloutHandle& handle);

    /// @brief Handles a 'sflq-pool6-by-range' command
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool6-get-by-range",
    ///     "arguments": {
    ///         "start-address": "3001::",
    ///         "end-address": "3001::FFFF"
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool6GetByRangeHandler(hooks::CalloutHandle& handle);

    /// @brief Delete the SFLQ V6 pool that matches a start and end address.
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool6-del",
    ///     "arguments": {
    ///         "start-address": "3001::",
    ///         "end-address": "3001::FFFF",
    ///         "force": false
    ///     }
    /// }
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool6DelHandler(hooks::CalloutHandle& handle);

private:
    /// @brief The 'sflq-poolX-get-all' command handler
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-poolX-get-all",
    ///     "arguments": {
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @param family Protocol family AF_NET or AF_INET6
    /// @return result of the operation
    int sflqPoolGetAll(hooks::CalloutHandle& handle, uint16_t family);

    /// @brief Handles a 'sflq-poolX-by-subnet' command
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-poolX-get-by-subnet",
    ///     "arguments": {
    ///         "subnet-id" : 100
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @param family Protocol family AF_NET or AF_INET6
    /// @return result of the operation
    int sflqPoolGetBySubnet(hooks::CalloutHandle& handle, uint16_t family);

    /// @brief Handles a 'sflq-poolX-by-range' command
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-poolX-get-by-range",
    ///     "arguments": {
    ///         "start-address": "192.0.2.0",
    ///         "end-address": "192.0.2.255"
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @param family Protocol family AF_NET or AF_INET6
    /// @return result of the operation
    int sflqPoolGetByRange(hooks::CalloutHandle& handle, uint16_t family);

    /// @brief Handles a 'sflq-poolX-del' command
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-poolX-del",
    ///     "arguments": {
    ///         "start-address": "192.0.2.0",
    ///         "end-address": "192.0.2.255",
    ///         "force": false
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @param family Protocol family AF_NET or AF_INET6
    /// @return result of the operation
    int sflqPoolDel(hooks::CalloutHandle& handle, uint16_t family);

public:
    /// @brief Creates a success response from a list of SqlPoolInfos.
    ///
    /// @param pools list of pools to include in the response. May be empty.
    ///
    /// @return API response structure with a result code of CONTROL_RESULT_SUCCESS
    /// if the list of pools is not empty, otherwise CONTROL_RESULT_EMPTY.
    static data::ConstElementPtr buildGetResponse(dhcp::SflqPoolInfoCollectionPtr pools);

    /// @brief Extracts an ip address range from given parameters map
    ///
    /// Expects the map to contain valid addresses of the the given
    /// family (AF_INET or AF_INET6), specified as 'start-address' and
    /// 'end-address' and where the former is less than or equal to the
    /// latter.
    ///
    /// @param params Element map containing the command arguments.
    /// @param family protocol family (AF_INET or AF_INET6).
    /// @param[out] start_address IOAddress reference which receives the
    /// extracted start-address value
    /// @param[out] end_address IOAddress reference which receives the
    /// extracted end-address value
    ///
    /// @throw BadValue is either parameter is missing, is not a valid
    /// ip address or they do not constitute a valid range.
    static void extractRange(data::ConstElementPtr& params, uint8_t family,
                             asiolink::IOAddress& start_address,
                             asiolink::IOAddress& end_address);

    /// @brief Extracts a boolean from given parameters map
    ///
    /// Extracts a boolean element from the given map and returns its
    /// value. If the parameter is not found in the map, the function will
    /// the function will return the default value.
    ///
    /// @param params Element map containing the command arguments.
    /// @param name name of the desired parameter.
    /// @param default_value value to return if the parameter is optional and
    /// not specified.
    ///
    /// @throw BadValue is either parameter is missing, is not a valid
    /// ip address or they do not constitute a valid range.
    static bool extractBool(data::ConstElementPtr& params, const std::string& name,
                            bool default_value = false);

    /// @brief Extracts 'delegated-len' from given parameters map
    ///
    /// Extracts an integer element, 'delegate-len' from the given map
    /// if it is present and is >= 1 and <= 128. If it is not present
    /// it returns a value of 128.
    ///
    /// @param params Element map containing the command arguments.
    /// @param lease_type Lease::Type supplied with the arguments (IA_NA
    /// or IA_PD)
    ///
    /// @throw BadValue if the parameter is specified as anything other
    /// than an integer value >= 1 and <= 128.
    static uint8_t extractDelegatedLen(data::ConstElementPtr& params,
                                       dhcp::Lease::Type lease_type);

    /// @brief Extracts 'delegated-len' from given parameters map
    ///
    /// Extracts a string element, 'lease-type' from the given map
    /// For v4 it can be either "V4" or "3", for V6 it can be "IA_NA"
    /// "0", "IA_PD", or "2".
    ///
    /// @param params Element map containing the command arguments.
    /// @param family protocol family (AF_INET or AF_INET6).
    ///
    /// @throw BadValue if the parameter is not valid for the protocol
    /// family.
    static dhcp::Lease::Type extractLeaseType(data::ConstElementPtr& params,
                                              uint16_t family);
};

/// @brief Wrapper class around SFLQ pool commands.
///
/// This provides the interface through which callouts
/// execute the commands.
class SflqCmds {
public:
    /// @brief Constructor.
    ///
    /// It creates an instance of the @c SflqCmds
    SflqCmds();

    /// @brief sflq-pool4-create handler.
    ///
    /// Invokes LeaseMgr::sflqCreateFlqPool4() after parsing the arguments.
    /// @brief lease6-resend-ddns command handler
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool4-create",
    ///     "arguments": {
    ///         "start-address": "192.0.2.0",
    ///         "end-address": "192.0.2.255",
    ///         "subnet-id": 77,
    ///         "recreate": true
    ///     }
    /// }
    ///
    /// The 'recreate' parameter is optional, it defaults false.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool4CreateHandler(hooks::CalloutHandle& handle);

    /// @brief The 'sflq-pool4-get-all' command handler
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool4-get-all",
    ///     "arguments": {
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool4GetAllHandler(hooks::CalloutHandle& handle);

    /// @brief The 'sflq-pool4-get-by-subnet' command handler
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool4-get-by-subnet",
    ///     "arguments": {
    ///         "subnet-id" : 100
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool4GetBySubnetHandler(hooks::CalloutHandle& handle);

    /// @brief Handles a 'sflq-pool4-by-range' command
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool4-get-by-range",
    ///     "arguments": {
    ///         "start-address": "192.0.2.0",
    ///         "end-address": "192.0.2.255"
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool4GetByRangeHandler(hooks::CalloutHandle& handle);

    /// @brief Delete the SFLQ V4 pool that matches a start and end address.
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool4-del",
    ///     "arguments": {
    ///         "start-address": "192.0.2.0",
    ///         "end-address": "192.0.2.255",
    ///         "force": false
    ///     }
    /// }
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool4DelHandler(hooks::CalloutHandle& handle);

    /// @brief The 'sflq-pool6-create' command handler
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool6-create",
    ///     "arguments": {
    ///         "start-address": "3001::",
    ///         "end-address": "3001::FF",
    ///         "subnet-id": 77,
    ///         "lease-type" : "IA_PD",
    ///         "delegated_len: 64
    ///         "recreate": true
    ///     }
    /// }
    ///
    /// The 'delegated-len' is optional, it defaults to 128.
    /// The 'recreate' parameter is optional, it defaults false.
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool6CreateHandler(hooks::CalloutHandle& handle);

    /// @brief The 'sflq-pool6-get-all' command handler
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool6-get-all",
    ///     "arguments": {
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool6GetAllHandler(hooks::CalloutHandle& handle);

    /// @brief The 'sflq-pool6-get-by-subnet' command handler
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool6-get-by-subnet",
    ///     "arguments": {
    ///         "subnet-id" : 100
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool6GetBySubnetHandler(hooks::CalloutHandle& handle);

    /// @brief Handles a 'sflq-pool6-by-range' command
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool6-get-by-range",
    ///     "arguments": {
    ///         "start-address": "3001::",
    ///         "end-address": "3001::FFFF"
    ///     }
    /// }
    ///
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool6GetByRangeHandler(hooks::CalloutHandle& handle);

    /// @brief Delete the SFLQ V6 pool that matches a start and end address.
    ///
    /// It extracts the command name and arguments from the given CalloutHandle,
    /// attempts to process them, and then set's the handle's "response"
    /// argument accordingly.
    ///
    /// An example command with all supported arguments is shown below:
    /// {
    ///     "command": "sflq-pool6-del",
    ///     "arguments": {
    ///         "start-address": "3001::",
    ///         "end-address": "3001::FFFF",
    ///         "force": false
    ///     }
    /// }
    /// @param handle Callout context - which is expected to contain the
    /// the command JSON text in the "command" argument
    /// @return result of the operation
    int sflqPool6DelHandler(hooks::CalloutHandle& handle);

private:
    /// Pointer to the SFLQ commands implementation
    boost::shared_ptr<SflqCmdsImpl> sflq_impl_;
};

};
};
#endif
