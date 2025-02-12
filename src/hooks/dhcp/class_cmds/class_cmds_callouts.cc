// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#include <config.h>

#include <class_cmds.h>
#include <class_cmds_log.h>
#include <cc/command_interpreter.h>
#include <hooks/hooks.h>
#include <dhcpsrv/cfgmgr.h>
#include <process/daemon.h>

using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::process;
using namespace isc::class_cmds;

extern "C" {

/// @brief This is a command callout for 'class-add' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int class_add(CalloutHandle& handle) {
    try {
        ClassCmds class_cmds;
        class_cmds.addClass(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(class_cmds_logger, CLASS_CMDS_CLASS_ADD_HANDLER_FAILED)
            .arg(ex.what());
        return (1);
    }

    return (0);
}

/// @brief This is a command callout for 'class-get' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int class_get(CalloutHandle& handle) {
    try {
        ClassCmds class_cmds;
        class_cmds.getClass(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(class_cmds_logger, CLASS_CMDS_CLASS_GET_HANDLER_FAILED)
            .arg(ex.what());
        return (1);
    }

    return (0);
}

/// @brief This is a command callout for 'class-list' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int class_list(CalloutHandle& handle) {
    try {
        ClassCmds class_cmds;
        class_cmds.getClassList(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(class_cmds_logger, CLASS_CMDS_CLASS_LIST_HANDLER_FAILED)
            .arg(ex.what());
        return (1);
    }

    return (0);
}

/// @brief This is a command callout for 'class-update' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int class_update(CalloutHandle& handle) {
    try {
        ClassCmds class_cmds;
        class_cmds.updateClass(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(class_cmds_logger, CLASS_CMDS_CLASS_UPDATE_HANDLER_FAILED)
            .arg(ex.what());
        return (1);
    }

    return (0);
}

/// @brief This is a command callout for 'class-del' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int class_del(CalloutHandle& handle) {
    try {
        ClassCmds class_cmds;
        class_cmds.delClass(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(class_cmds_logger, CLASS_CMDS_CLASS_DEL_HANDLER_FAILED)
          .arg(ex.what());
        return (1);
    }

    return (0);
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
        handle.registerCommandCallout("class-add", class_add);
        handle.registerCommandCallout("class-get", class_get);
        handle.registerCommandCallout("class-list", class_list);
        handle.registerCommandCallout("class-update", class_update);
        handle.registerCommandCallout("class-del", class_del);
    } catch (const std::exception& ex) {
        LOG_ERROR(class_cmds_logger, CLASS_CMDS_INIT_FAILED)
            .arg(ex.what());
        return (1);
    }

    LOG_INFO(class_cmds_logger, CLASS_CMDS_INIT_OK);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return 0
int unload() {
    LOG_INFO(class_cmds_logger, CLASS_CMDS_DEINIT_OK);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
