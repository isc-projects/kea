// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#include <config.h>

#include <stat_cmds.h>
#include <stat_cmds_log.h>
#include <cc/command_interpreter.h>
#include <dhcpsrv/cfgmgr.h>
#include <hooks/hooks.h>
#include <process/daemon.h>

using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::process;
using namespace isc::stat_cmds;

extern "C" {

/// @brief This is a command callout for 'stat-lease4-get' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int stat_lease4_get(CalloutHandle& handle) {
    StatCmds stat_cmds;
    return(stat_cmds.statLease4GetHandler(handle));
}

/// @brief This is a command callout for 'stat-lease6-get' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int stat_lease6_get(CalloutHandle& handle) {
    StatCmds stat_cmds;
    return(stat_cmds.statLease6GetHandler(handle));
}

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle
/// @return 0 when initialization is successful, 1 otherwise
int load(LibraryHandle& handle) {
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

    handle.registerCommandCallout("stat-lease4-get", stat_lease4_get);
    handle.registerCommandCallout("stat-lease6-get", stat_lease6_get);
    LOG_INFO(stat_cmds_logger, STAT_CMDS_INIT_OK);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return 0 if deregistration was successful, 1 otherwise
int unload() {
    LOG_INFO(stat_cmds_logger, STAT_CMDS_DEINIT_OK);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
