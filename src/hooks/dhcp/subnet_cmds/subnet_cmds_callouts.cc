// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#include <config.h>

#include <subnet_cmds.h>
#include <subnet_cmds_log.h>
#include <cc/command_interpreter.h>
#include <hooks/hooks.h>
#include <dhcpsrv/cfgmgr.h>
#include <process/daemon.h>

using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::process;
using namespace isc::subnet_cmds;

extern "C" {

/// @brief This is a command handler for 'subnet4-list' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int subnet4_list(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        SubnetCmds subnet_cmds;
        response = subnet_cmds.getSubnet4List();

    } catch (const std::exception& ex) {
        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_SUBNET4_LIST_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'subnet6-list' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int subnet6_list(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        SubnetCmds subnet_cmds;
        response = subnet_cmds.getSubnet6List();

    } catch (const std::exception& ex) {
        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_SUBNET6_LIST_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'subnet4-get' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int subnet4_get(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.getSubnet4(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_SUBNET4_GET_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'subnet4-get' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int subnet6_get(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.getSubnet6(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_SUBNET6_GET_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'subnet4-add' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int subnet4_add(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.addSubnet4(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_SUBNET4_ADD_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'subnet6-add' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int subnet6_add(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.addSubnet6(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_SUBNET6_ADD_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'subnet4-update' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int subnet4_update(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.updateSubnet4(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_SUBNET4_UPDATE_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'subnet6-update' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int subnet6_update(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.updateSubnet6(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_SUBNET6_UPDATE_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'subnet4-del' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int subnet4_del(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.delSubnet4(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_SUBNET4_DEL_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'subnet6-del' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int subnet6_del(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.delSubnet6(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_SUBNET6_DEL_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'subnet4-delta-add' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int subnet4_delta_add(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.addSubnet4Delta(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_SUBNET4_DELTA_ADD_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'subnet6-delta-add' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int subnet6_delta_add(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.addSubnet6Delta(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_SUBNET6_DELTA_ADD_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'subnet4-delta-del' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int subnet4_delta_del(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.delSubnet4Delta(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_SUBNET4_DELTA_DEL_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'subnet6-delta-del' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int subnet6_delta_del(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.delSubnet6Delta(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_SUBNET6_DELTA_DEL_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

// -----------------------------------------------------------------------------
// --- SHARED NETWORKS ---------------------------------------------------------
// -----------------------------------------------------------------------------

/// @brief This is a command handler for 'network4-list' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int network4_list(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        SubnetCmds subnet_cmds;
        response = subnet_cmds.getNetwork4List();

    } catch (const std::exception& ex) {
        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_NETWORK4_LIST_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'network6-list' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int network6_list(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        SubnetCmds subnet_cmds;
        response = subnet_cmds.getNetwork6List();

    } catch (const std::exception& ex) {
        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_NETWORK6_LIST_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'network4-get' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int network4_get(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.getNetwork4(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_NETWORK4_GET_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'network4-get' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int network6_get(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.getNetwork6(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_NETWORK6_GET_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'network4-add' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int network4_add(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.addNetwork4(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_NETWORK4_ADD_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'network6-add' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int network6_add(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.addNetwork6(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_NETWORK6_ADD_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'network4-del' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int network4_del(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.delNetwork4(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_NETWORK4_DEL_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'network6-del' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int network6_del(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.delNetwork6(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_NETWORK6_DEL_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'network4-subnet-add' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int network4_subnet_add(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.addNetwork4Subnet(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_NETWORK4_SUBNET_ADD_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'network6-subnet-add' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int network6_subnet_add(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.addNetwork6Subnet(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_NETWORK6_SUBNET_ADD_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'network4-subnet-del' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int network4_subnet_del(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.delNetwork4Subnet(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_NETWORK4_SUBNET_DEL_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

    return (0);
}

/// @brief This is a command handler for 'network6-subnet-del' command.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int network6_subnet_del(CalloutHandle& handle) {
    ConstElementPtr response;

    try {
        ConstElementPtr command;
        handle.getArgument("command", command);
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        SubnetCmds subnet_cmds;
        response = subnet_cmds.delNetwork6Subnet(args);

    } catch (const std::exception& ex) {
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_NETWORK6_SUBNET_DEL_FAILED)
            .arg(ex.what());
    }

    handle.setArgument("response", response);

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

        // Register commands for handling subnets.
        handle.registerCommandCallout("subnet4-list", subnet4_list);
        handle.registerCommandCallout("subnet6-list", subnet6_list);
        handle.registerCommandCallout("subnet4-get", subnet4_get);
        handle.registerCommandCallout("subnet6-get", subnet6_get);
        handle.registerCommandCallout("subnet4-add", subnet4_add);
        handle.registerCommandCallout("subnet6-add", subnet6_add);
        handle.registerCommandCallout("subnet4-update", subnet4_update);
        handle.registerCommandCallout("subnet6-update", subnet6_update);
        handle.registerCommandCallout("subnet4-del", subnet4_del);
        handle.registerCommandCallout("subnet6-del", subnet6_del);
        handle.registerCommandCallout("subnet4-delta-add", subnet4_delta_add);
        handle.registerCommandCallout("subnet6-delta-add", subnet6_delta_add);
        handle.registerCommandCallout("subnet4-delta-del", subnet4_delta_del);
        handle.registerCommandCallout("subnet6-delta-del", subnet6_delta_del);

        // Register commands for handling shared networks
        handle.registerCommandCallout("network4-list", network4_list);
        handle.registerCommandCallout("network6-list", network6_list);
        handle.registerCommandCallout("network4-get", network4_get);
        handle.registerCommandCallout("network6-get", network6_get);
        handle.registerCommandCallout("network4-add", network4_add);
        handle.registerCommandCallout("network6-add", network6_add);
        handle.registerCommandCallout("network4-del", network4_del);
        handle.registerCommandCallout("network6-del", network6_del);
        handle.registerCommandCallout("network4-subnet-add",
                                      network4_subnet_add);
        handle.registerCommandCallout("network6-subnet-add",
                                      network6_subnet_add);
        handle.registerCommandCallout("network4-subnet-del",
                                      network4_subnet_del);
        handle.registerCommandCallout("network6-subnet-del",
                                      network6_subnet_del);
    } catch (const std::exception& ex) {
        LOG_ERROR(subnet_cmds_logger, SUBNET_CMDS_INIT_FAILED)
            .arg(ex.what());
        return (1);
    }


    LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_INIT_OK);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return 0 if deregistration was successful, 1 otherwise
int unload() {
    LOG_INFO(subnet_cmds_logger, SUBNET_CMDS_DEINIT_OK);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
