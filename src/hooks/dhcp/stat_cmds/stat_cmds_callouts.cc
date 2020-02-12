// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the End User License
// Agreement. See COPYING file in the premium/ directory.


// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#include <config.h>

#include <stat_cmds.h>
#include <stat_cmds_log.h>
#include <cc/command_interpreter.h>
#include <hooks/hooks.h>

using namespace isc::hooks;
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
