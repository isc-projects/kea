// Copyright (C) 2017-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#include <config.h>

#include <lease_cmds.h>
#include <lease_cmds_log.h>
#include <cc/command_interpreter.h>
#include <hooks/hooks.h>

using namespace isc::config;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::lease_cmds;

extern "C" {

/// @brief This is a command callout for 'lease4-add' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int lease4_add(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return(lease_cmds.leaseAddHandler(handle));
}

/// @brief This is a command callout for 'lease6-add' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int lease6_add(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return(lease_cmds.leaseAddHandler(handle));
}

/// @brief This is a command callout for 'lease6-bulk-apply' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int lease6_bulk_apply(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return (lease_cmds.lease6BulkApplyHandler(handle));
}

/// @brief This is a command callout for 'lease4-get' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int lease4_get(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return(lease_cmds.leaseGetHandler(handle));
}

/// @brief This is a command callout for 'lease6-get' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int lease6_get(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return(lease_cmds.leaseGetHandler(handle));
}

/// @brief This is a command callout for 'lease4-get-all' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 if an error occurs, 3 if no leases are returned.
int lease4_get_all(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return (lease_cmds.leaseGetAllHandler(handle));
}

/// @brief This is a command callout for 'lease6-get-all' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 if an error occurs, 3 if no leases are returned.
int lease6_get_all(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return (lease_cmds.leaseGetAllHandler(handle));
}

/// @brief This is a command callout for 'lease4-get-page' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 if an error occurs, 3 if no leases are returned.
int lease4_get_page(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return (lease_cmds.leaseGetPageHandler(handle));
}

/// @brief This is a command callout for 'lease6-get-page' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 if an error occurs, 3 if no leases are returned.
int lease6_get_page(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return (lease_cmds.leaseGetPageHandler(handle));
}

/// @brief This is a command callout for 'lease4-get-by-hw-address' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 if an error occurs, 3 if no leases are returned.
int lease4_get_by_hw_address(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return (lease_cmds.leaseGetByHwAddressHandler(handle));
}

/// @brief This is a command callout for 'lease4-get-by-client-id' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 if an error occurs, 3 if no leases are returned.
int lease4_get_by_client_id(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return (lease_cmds.leaseGetByClientIdHandler(handle));
}

/// @brief This is a command callout for 'lease6-get-by-duid' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 if an error occurs, 3 if no leases are returned.
int lease6_get_by_duid(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return (lease_cmds.leaseGetByDuidHandler(handle));
}

/// @brief This is a command callout for 'lease4-get-by-hostname' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 if an error occurs, 3 if no leases are returned.
int lease4_get_by_hostname(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return (lease_cmds.leaseGetByHostnameHandler(handle));
}

/// @brief This is a command callout for 'lease6-get-by-hostname' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 if an error occurs, 3 if no leases are returned.
int lease6_get_by_hostname(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return (lease_cmds.leaseGetByHostnameHandler(handle));
}

/// @brief This is a command callout for 'lease4-del' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int lease4_del(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return(lease_cmds.lease4DelHandler(handle));
}

/// @brief This is a command callout for 'lease6-del' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int lease6_del(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return(lease_cmds.lease6DelHandler(handle));
}

/// @brief This is a command callout for 'lease4-update' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int lease4_update(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return(lease_cmds.lease4UpdateHandler(handle));
}

/// @brief This is a command callout for 'lease6-update' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int lease6_update(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return(lease_cmds.lease6UpdateHandler(handle));
}

/// @brief This is a command callout for 'lease4-wipe' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int lease4_wipe(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return(lease_cmds.lease4WipeHandler(handle));
}

/// @brief This is a command callout for 'lease6-wipe' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int lease6_wipe(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return(lease_cmds.lease6WipeHandler(handle));
}

/// @brief This is a command callout for 'lease4-resend-ddns' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int lease4_resend_ddns(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return(lease_cmds.lease4ResendDdnsHandler(handle));
}

/// @brief This is a command callout for 'lease6-resend-ddns' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int lease6_resend_ddns(CalloutHandle& handle) {
    LeaseCmds lease_cmds;
    return(lease_cmds.lease6ResendDdnsHandler(handle));
}

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle
/// @return 0 when initialization is successful, 1 otherwise
int load(LibraryHandle& handle) {
    handle.registerCommandCallout("lease4-add", lease4_add);
    handle.registerCommandCallout("lease6-add", lease6_add);
    handle.registerCommandCallout("lease6-bulk-apply", lease6_bulk_apply);
    handle.registerCommandCallout("lease4-get", lease4_get);
    handle.registerCommandCallout("lease6-get", lease6_get);
    handle.registerCommandCallout("lease4-get-all", lease4_get_all);
    handle.registerCommandCallout("lease6-get-all", lease6_get_all);
    handle.registerCommandCallout("lease4-get-page", lease4_get_page);
    handle.registerCommandCallout("lease6-get-page", lease6_get_page);
    handle.registerCommandCallout("lease4-get-by-hw-address",
                                  lease4_get_by_hw_address);
    handle.registerCommandCallout("lease4-get-by-client-id",
                                  lease4_get_by_client_id);
    handle.registerCommandCallout("lease6-get-by-duid", lease6_get_by_duid);
    handle.registerCommandCallout("lease4-get-by-hostname",
                                  lease4_get_by_hostname);
    handle.registerCommandCallout("lease6-get-by-hostname",
                                  lease6_get_by_hostname);
    handle.registerCommandCallout("lease4-del", lease4_del);
    handle.registerCommandCallout("lease6-del", lease6_del);
    handle.registerCommandCallout("lease4-update", lease4_update);
    handle.registerCommandCallout("lease6-update", lease6_update);
    handle.registerCommandCallout("lease4-wipe", lease4_wipe);
    handle.registerCommandCallout("lease6-wipe", lease6_wipe);
    handle.registerCommandCallout("lease4-resend-ddns", lease4_resend_ddns);
    handle.registerCommandCallout("lease6-resend-ddns", lease6_resend_ddns);

    LOG_INFO(lease_cmds_logger, LEASE_CMDS_INIT_OK);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return 0 if deregistration was successful, 1 otherwise
int unload() {
    LOG_INFO(lease_cmds_logger, LEASE_CMDS_DEINIT_OK);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
