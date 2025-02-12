// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#include <config.h>

#include <host_cmds.h>
#include <host_cmds_log.h>
#include <cc/command_interpreter.h>
#include <hooks/hooks.h>
#include <dhcpsrv/cfgmgr.h>
#include <process/daemon.h>

using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::process;
using namespace isc::host_cmds;

extern "C" {

/// @brief This is a command callout for 'reservation-add' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int reservation_add(CalloutHandle& handle) {
    HostCmds host_cmds;
    return (host_cmds.reservationAddHandler(handle));
}

/// @brief This is a command callout for 'reservation-get' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int reservation_get(CalloutHandle& handle) {
    HostCmds host_cmds;
    return (host_cmds.reservationGetHandler(handle));
}

/// @brief This is a command callout for 'reservation-get-by-address' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int reservation_get_by_address(CalloutHandle& handle) {
    HostCmds host_cmds;
    return (host_cmds.reservationGetByAddressHandler(handle));
}

/// @brief This is a command callout for 'reservation-del' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int reservation_del(CalloutHandle& handle) {
    HostCmds host_cmds;
    return (host_cmds.reservationDelHandler(handle));
}

/// @brief This is a command callout for 'reservation-get-all' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int reservation_get_all(CalloutHandle& handle) {
    HostCmds host_cmds;
    return (host_cmds.reservationGetAllHandler(handle));
}

/// @brief This is a command callout for 'reservation-get-page' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int reservation_get_page(CalloutHandle& handle) {
    HostCmds host_cmds;
    return (host_cmds.reservationGetPageHandler(handle));
}

/// @brief This is a command callout for 'reservation-get-by-hostname' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int reservation_get_by_hostname(CalloutHandle& handle) {
    HostCmds host_cmds;
    return (host_cmds.reservationGetByHostnameHandler(handle));
}

/// @brief This is a command callout for 'reservation-get-by-id' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int reservation_get_by_id(CalloutHandle& handle) {
    HostCmds host_cmds;
    return (host_cmds.reservationGetByIdHandler(handle));
}

/// @brief This is a command callout for the reservation-update command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
///
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int reservation_update(CalloutHandle& handle) {
    HostCmds host_cmds;
    return (host_cmds.reservationUpdateHandler(handle));
}

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle
/// @return 0 when initialization is successful, 1 otherwise
int load(LibraryHandle& handle) {
    try {
        // Make the hook library not loadable by d2 or ca.
        uint16_t family = CfgMgr::instance().getFamily();
        const std::string& proc_name = Daemon::getProcName();
        if (family == AF_INET) {
            if (proc_name != "kea-dhcp4") {
                isc_throw(isc::Unexpected, "Bad process name: " << proc_name
                          << ", expected kea-dhcp4");
            }
        } else {
            if (proc_name != "kea-dhcp6") {
                isc_throw(isc::Unexpected, "Bad process name: " << proc_name
                          << ", expected kea-dhcp6");
            }
        }

        // Register commands.
        handle.registerCommandCallout("reservation-add", reservation_add);
        handle.registerCommandCallout("reservation-get", reservation_get);
        handle.registerCommandCallout("reservation-del", reservation_del);
        handle.registerCommandCallout("reservation-get-all",
                                      reservation_get_all);
        handle.registerCommandCallout("reservation-get-page",
                                      reservation_get_page);
        handle.registerCommandCallout("reservation-get-by-address",
                                      reservation_get_by_address);
        handle.registerCommandCallout("reservation-get-by-hostname",
                                      reservation_get_by_hostname);
        handle.registerCommandCallout("reservation-get-by-id",
                                      reservation_get_by_id);
        handle.registerCommandCallout("reservation-update", reservation_update);
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cmds_logger, HOST_CMDS_INIT_FAILED)
            .arg(ex.what());
        return (1);
    }

    LOG_INFO(host_cmds_logger, HOST_CMDS_INIT_OK);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return 0
int unload() {
    LOG_INFO(host_cmds_logger, HOST_CMDS_DEINIT_OK);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
