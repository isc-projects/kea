// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#include <config.h>

#include <cb_cmds/cb_cmds_dhcp4.h>
#include <cb_cmds/cb_cmds_dhcp6.h>
#include <cb_cmds/cb_cmds_log.h>
#include <cc/command_interpreter.h>
#include <dhcpsrv/cfgmgr.h>
#include <hooks/hooks.h>
#include <process/daemon.h>

#include <boost/make_shared.hpp>

using namespace isc::cb;
using namespace isc::config;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::process;

namespace isc {
namespace cb {

ConfigCmdsDhcp4ImplPtr impl4;
ConfigCmdsDhcp6ImplPtr impl6;

} // end of namespace isc::cb
} // end of namespace isc

extern "C" {

/// @brief Handler for remote-class4-set command.
///
/// @param handle Callout handle including the command.
int client_class4_set_command(CalloutHandle& handle) {
    try {
        impl4->setClientClass4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_CLASS4_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-class4-get command.
///
/// @param handle Callout handle including the command.
int client_class4_get_command(CalloutHandle& handle) {
    try {
        impl4->getClientClass4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_CLASS4_GET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-class4-get-all command.
///
/// @param handle Callout handle including the command.
int client_class4_get_all_command(CalloutHandle& handle) {
    try {
        impl4->getAllClientClasses4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_CLASS4_GET_ALL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-class4-del command.
///
/// @param handle Callout handle including the command.
int client_class4_del_command(CalloutHandle& handle) {
    try {
        impl4->delClientClass4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_CLASS4_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-global-parameter4-set command.
///
/// @param handle Callout handle including the command.
int global_parameter4_set_command(CalloutHandle& handle) {
    try {
        impl4->setGlobalParameter4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_GLOBAL_PARAMETER4_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-global-parameter4-get command.
///
/// @param handle Callout handle including the command.
int global_parameter4_get_command(CalloutHandle& handle) {
    try {
        impl4->getGlobalParameter4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_GLOBAL_PARAMETER4_GET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-global-parameter4-get-all command.
///
/// @param handle Callout handle including the command.
int global_parameter4_get_all_command(CalloutHandle& handle) {
    try {
        impl4->getAllGlobalParameters4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger,
                  CB_CMDS_GLOBAL_PARAMETER4_GET_ALL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-global-parameter4-del command.
///
/// @param handle Callout handle including the command.
int global_parameter4_del_command(CalloutHandle& handle) {
    try {
        impl4->delGlobalParameter4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_GLOBAL_PARAMETER4_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-subnet4-set command.
///
/// @param handle Callout handle including the command.
int subnet4_set_command(CalloutHandle& handle) {
    try {
        impl4->setSubnet4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SUBNET4_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-subnet4-get-by-id command.
///
/// @param handle Callout handle including the command.
int subnet4_get_by_id_command(CalloutHandle& handle) {
    try {
        impl4->getSubnet4Id(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SUBNET4_GET_BY_ID_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-subnet4-get-by-prefix command.
///
/// @param handle Callout handle including the command.
int subnet4_get_by_prefix_command(CalloutHandle& handle) {
    try {
        impl4->getSubnet4Prefix(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SUBNET4_GET_BY_PREFIX_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-subnet4-list command.
///
/// @param handle Callout handle including the command.
int subnet4_list_command(CalloutHandle& handle) {
    try {
        impl4->listSubnets4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SUBNET4_LIST_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-subnet4-del-by-id command.
///
/// @param handle Callout handle including the command.
int subnet4_del_by_id_command(CalloutHandle& handle) {
    try {
        impl4->delSubnet4Id(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SUBNET4_DEL_BY_ID_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-subnet4-del-by-prefix command.
///
/// @param handle Callout handle including the command.
int subnet4_del_by_prefix_command(CalloutHandle& handle) {
    try {
        impl4->delSubnet4Prefix(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SUBNET4_DEL_BY_PREFIX_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-network4-set command.
///
/// @param handle Callout handle including the command.
int network4_set_command(CalloutHandle& handle) {
    try {
        impl4->setSharedNetwork4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_NETWORK4_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-network4-get command.
///
/// @param handle Callout handle including the command.
int network4_get_command(CalloutHandle& handle) {
    try {
        impl4->getSharedNetwork4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_NETWORK4_GET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-network4-list command.
///
/// @param handle Callout handle including the command.
int network4_list_command(CalloutHandle& handle) {
    try {
        impl4->listSharedNetworks4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_NETWORK4_LIST_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-network4-del command.
///
/// @param handle Callout handle including the command.
int network4_del_command(CalloutHandle& handle) {
    try {
        impl4->delSharedNetwork4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_NETWORK4_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option-def4-set command.
///
/// @param handle Callout handle including the command.
int option_def4_set_command(CalloutHandle& handle) {
    try {
        impl4->setOptionDef4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION_DEF4_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option-def4-get command.
///
/// @param handle Callout handle including the command.
int option_def4_get_command(CalloutHandle& handle) {
    try {
        impl4->getOptionDef4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION_DEF4_GET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option-def4-get-all command.
///
/// @param handle Callout handle including the command.
int option_def4_get_all_command(CalloutHandle& handle) {
    try {
        impl4->getAllOptionDefs4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION_DEF4_GET_ALL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option-def4-del command.
///
/// @param handle Callout handle including the command.
int option_def4_del_command(CalloutHandle& handle) {
    try {
        impl4->delOptionDef4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION_DEF4_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option4-global-set command.
///
/// @param handle Callout handle including the command.
int option4_global_set_command(CalloutHandle& handle) {
    try {
        impl4->setGlobalOption4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION4_GLOBAL_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option4-global-get command.
///
/// @param handle Callout handle including the command.
int option4_global_get_command(CalloutHandle& handle) {
    try {
        impl4->getGlobalOption4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION4_GLOBAL_GET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option4-global-get-all command.
///
/// @param handle Callout handle including the command.
int option4_global_get_all_command(CalloutHandle& handle) {
    try {
        impl4->getAllGlobalOptions4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger,
                  CB_CMDS_OPTION4_GLOBAL_GET_ALL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option4-global-del command.
///
/// @param handle Callout handle including the command.
int option4_global_del_command(CalloutHandle& handle) {
    try {
        impl4->delGlobalOption4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION4_GLOBAL_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-server4-set command.
///
/// @param handle Callout handle including the command.
int server4_set_command(CalloutHandle& handle) {
    try {
        impl4->setServer4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SERVER4_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-server4-get command.
///
/// @param handle Callout handle including the command.
int server4_get_command(CalloutHandle& handle) {
    try {
        impl4->getServer4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SERVER4_GET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-server4-get-all command.
///
/// @param handle Callout handle including the command.
int server4_get_all_command(CalloutHandle& handle) {
    try {
        impl4->getAllServers4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger,
                  CB_CMDS_SERVER4_GET_ALL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-server4-del command.
///
/// @param handle Callout handle including the command.
int server4_del_command(CalloutHandle& handle) {
    try {
        impl4->delServer4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SERVER4_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option4-network-set command.
///
/// @param handle Callout handle including the command.
int option4_network_set_command(CalloutHandle& handle) {
    try {
        impl4->setSharedNetworkOption4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION4_NETWORK_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option4-network-del command.
///
/// @param handle Callout handle including the command.
int option4_network_del_command(CalloutHandle& handle) {
    try {
        impl4->delSharedNetworkOption4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION4_NETWORK_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option4-subnet-set command.
///
/// @param handle Callout handle including the command.
int option4_subnet_set_command(CalloutHandle& handle) {
    try {
        impl4->setSubnetOption4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION4_SUBNET_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option4-subnet-del command.
///
/// @param handle Callout handle including the command.
int option4_subnet_del_command(CalloutHandle& handle) {
    try {
        impl4->delSubnetOption4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION4_SUBNET_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option4-pool-set command.
///
/// @param handle Callout handle including the command.
int option4_pool_set_command(CalloutHandle& handle) {
    try {
        impl4->setPoolOption4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION4_POOL_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option4-pool-del command.
///
/// @param handle Callout handle including the command.
int option4_pool_del_command(CalloutHandle& handle) {
    try {
        impl4->delPoolOption4(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION4_POOL_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-class4-set command.
///
/// @param handle Callout handle including the command.
int client_class6_set_command(CalloutHandle& handle) {
    try {
        impl6->setClientClass6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_CLASS6_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-class4-get command.
///
/// @param handle Callout handle including the command.
int client_class6_get_command(CalloutHandle& handle) {
    try {
        impl6->getClientClass6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_CLASS6_GET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-class6-get-all command.
///
/// @param handle Callout handle including the command.
int client_class6_get_all_command(CalloutHandle& handle) {
    try {
        impl6->getAllClientClasses6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_CLASS6_GET_ALL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-class6-del command.
///
/// @param handle Callout handle including the command.
int client_class6_del_command(CalloutHandle& handle) {
    try {
        impl6->delClientClass6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_CLASS6_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-global-parameter6-set command.
///
/// @param handle Callout handle including the command.
int global_parameter6_set_command(CalloutHandle& handle) {
    try {
        impl6->setGlobalParameter6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_GLOBAL_PARAMETER6_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-global-parameter6-get command.
///
/// @param handle Callout handle including the command.
int global_parameter6_get_command(CalloutHandle& handle) {
    try {
        impl6->getGlobalParameter6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_GLOBAL_PARAMETER6_GET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-global-parameter6-get-all command.
///
/// @param handle Callout handle including the command.
int global_parameter6_get_all_command(CalloutHandle& handle) {
    try {
        impl6->getAllGlobalParameters6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger,
                  CB_CMDS_GLOBAL_PARAMETER6_GET_ALL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-global-parameter6-del command.
///
/// @param handle Callout handle including the command.
int global_parameter6_del_command(CalloutHandle& handle) {
    try {
        impl6->delGlobalParameter6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_GLOBAL_PARAMETER6_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-subnet6-set command.
///
/// @param handle Callout handle including the command.
int subnet6_set_command(CalloutHandle& handle) {
    try {
        impl6->setSubnet6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SUBNET6_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-subnet6-get-by-id command.
///
/// @param handle Callout handle including the command.
int subnet6_get_by_id_command(CalloutHandle& handle) {
    try {
        impl6->getSubnet6Id(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SUBNET6_GET_BY_ID_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-subnet6-get-by-prefix command.
///
/// @param handle Callout handle including the command.
int subnet6_get_by_prefix_command(CalloutHandle& handle) {
    try {
        impl6->getSubnet6Prefix(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SUBNET6_GET_BY_PREFIX_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-subnet6-list command.
///
/// @param handle Callout handle including the command.
int subnet6_list_command(CalloutHandle& handle) {
    try {
        impl6->listSubnets6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SUBNET6_LIST_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-subnet6-del-by-id command.
///
/// @param handle Callout handle including the command.
int subnet6_del_by_id_command(CalloutHandle& handle) {
    try {
        impl6->delSubnet6Id(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SUBNET6_DEL_BY_ID_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-subnet6-del-by-prefix command.
///
/// @param handle Callout handle including the command.
int subnet6_del_by_prefix_command(CalloutHandle& handle) {
    try {
        impl6->delSubnet6Prefix(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SUBNET6_DEL_BY_PREFIX_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-network6-set command.
///
/// @param handle Callout handle including the command.
int network6_set_command(CalloutHandle& handle) {
    try {
        impl6->setSharedNetwork6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_NETWORK6_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-network6-get command.
///
/// @param handle Callout handle including the command.
int network6_get_command(CalloutHandle& handle) {
    try {
        impl6->getSharedNetwork6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_NETWORK6_GET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-network6-list command.
///
/// @param handle Callout handle including the command.
int network6_list_command(CalloutHandle& handle) {
    try {
        impl6->listSharedNetworks6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_NETWORK6_LIST_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-network6-del command.
///
/// @param handle Callout handle including the command.
int network6_del_command(CalloutHandle& handle) {
    try {
        impl6->delSharedNetwork6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_NETWORK6_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option-def6-set command.
///
/// @param handle Callout handle including the command.
int option_def6_set_command(CalloutHandle& handle) {
    try {
        impl6->setOptionDef6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION_DEF6_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option-def6-get command.
///
/// @param handle Callout handle including the command.
int option_def6_get_command(CalloutHandle& handle) {
    try {
        impl6->getOptionDef6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION_DEF6_GET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option-def6-get-all command.
///
/// @param handle Callout handle including the command.
int option_def6_get_all_command(CalloutHandle& handle) {
    try {
        impl6->getAllOptionDefs6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION_DEF6_GET_ALL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option-def6-del command.
///
/// @param handle Callout handle including the command.
int option_def6_del_command(CalloutHandle& handle) {
    try {
        impl6->delOptionDef6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION_DEF6_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option6-global-set command.
///
/// @param handle Callout handle including the command.
int option6_global_set_command(CalloutHandle& handle) {
    try {
        impl6->setGlobalOption6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION6_GLOBAL_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option6-global-get command.
///
/// @param handle Callout handle including the command.
int option6_global_get_command(CalloutHandle& handle) {
    try {
        impl6->getGlobalOption6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION6_GLOBAL_GET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option6-global-get-all command.
///
/// @param handle Callout handle including the command.
int option6_global_get_all_command(CalloutHandle& handle) {
    try {
        impl6->getAllGlobalOptions6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger,
                  CB_CMDS_OPTION6_GLOBAL_GET_ALL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option6-global-del command.
///
/// @param handle Callout handle including the command.
int option6_global_del_command(CalloutHandle& handle) {
    try {
        impl6->delGlobalOption6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION6_GLOBAL_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-server6-set command.
///
/// @param handle Callout handle including the command.
int server6_set_command(CalloutHandle& handle) {
    try {
        impl6->setServer6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SERVER6_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-server6-get command.
///
/// @param handle Callout handle including the command.
int server6_get_command(CalloutHandle& handle) {
    try {
        impl6->getServer6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SERVER6_GET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-server6-get-all command.
///
/// @param handle Callout handle including the command.
int server6_get_all_command(CalloutHandle& handle) {
    try {
        impl6->getAllServers6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger,
                  CB_CMDS_SERVER6_GET_ALL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-server6-del command.
///
/// @param handle Callout handle including the command.
int server6_del_command(CalloutHandle& handle) {
    try {
        impl6->delServer6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_SERVER6_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option6-network-set command.
///
/// @param handle Callout handle including the command.
int option6_network_set_command(CalloutHandle& handle) {
    try {
        impl6->setSharedNetworkOption6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION6_NETWORK_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option6-network-del command.
///
/// @param handle Callout handle including the command.
int option6_network_del_command(CalloutHandle& handle) {
    try {
        impl6->delSharedNetworkOption6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION6_NETWORK_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option6-subnet-set command.
///
/// @param handle Callout handle including the command.
int option6_subnet_set_command(CalloutHandle& handle) {
    try {
        impl6->setSubnetOption6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION6_SUBNET_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option6-subnet-del command.
///
/// @param handle Callout handle including the command.
int option6_subnet_del_command(CalloutHandle& handle) {
    try {
        impl6->delSubnetOption6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION6_SUBNET_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option6-pool-set command.
///
/// @param handle Callout handle including the command.
int option6_pool_set_command(CalloutHandle& handle) {
    try {
        impl6->setPoolOption6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION6_POOL_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option6-pool-del command.
///
/// @param handle Callout handle including the command.
int option6_pool_del_command(CalloutHandle& handle) {
    try {
        impl6->delPoolOption6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION6_POOL_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option6-pd-pool-set command.
///
/// @param handle Callout handle including the command.
int option6_pd_pool_set_command(CalloutHandle& handle) {
    try {
        impl6->setPdPoolOption6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION6_PD_POOL_SET_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief Handler for remote-option6-pd-pool-del command.
///
/// @param handle Callout handle including the command.
int option6_pd_pool_del_command(CalloutHandle& handle) {
    try {
        impl6->delPdPoolOption6(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(cb_cmds_logger, CB_CMDS_OPTION6_PD_POOL_DEL_HANDLER_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle
/// @return 0 when initialization is successful, 1 otherwise
int load(LibraryHandle& handle) {
    try {
        // Make the hook library not loadable by d2.
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

        impl4 = boost::make_shared<ConfigCmdsDhcp4Impl>();

        handle.registerCommandCallout("remote-class4-del",
                                      client_class4_del_command);
        handle.registerCommandCallout("remote-class4-get",
                                      client_class4_get_command);
        handle.registerCommandCallout("remote-class4-get-all",
                                      client_class4_get_all_command);
        handle.registerCommandCallout("remote-class4-set",
                                      client_class4_set_command);
        handle.registerCommandCallout("remote-global-parameter4-del",
                                      global_parameter4_del_command);
        handle.registerCommandCallout("remote-global-parameter4-get",
                                      global_parameter4_get_command);
        handle.registerCommandCallout("remote-global-parameter4-get-all",
                                      global_parameter4_get_all_command);
        handle.registerCommandCallout("remote-global-parameter4-set",
                                      global_parameter4_set_command);
        handle.registerCommandCallout("remote-network4-del",
                                      network4_del_command);
        handle.registerCommandCallout("remote-network4-get",
                                      network4_get_command);
        handle.registerCommandCallout("remote-network4-list",
                                      network4_list_command);
        handle.registerCommandCallout("remote-network4-set",
                                      network4_set_command);
        handle.registerCommandCallout("remote-option-def4-del",
                                      option_def4_del_command);
        handle.registerCommandCallout("remote-option-def4-get",
                                      option_def4_get_command);
        handle.registerCommandCallout("remote-option-def4-get-all",
                                      option_def4_get_all_command);
        handle.registerCommandCallout("remote-option-def4-set",
                                      option_def4_set_command);
        handle.registerCommandCallout("remote-option4-global-del",
                                      option4_global_del_command);
        handle.registerCommandCallout("remote-option4-global-get",
                                      option4_global_get_command);
        handle.registerCommandCallout("remote-option4-global-get-all",
                                      option4_global_get_all_command);
        handle.registerCommandCallout("remote-option4-global-set",
                                      option4_global_set_command);
        handle.registerCommandCallout("remote-option4-network-del",
                                      option4_network_del_command);
        handle.registerCommandCallout("remote-option4-network-set",
                                      option4_network_set_command);
        handle.registerCommandCallout("remote-option4-pool-del",
                                      option4_pool_del_command);
        handle.registerCommandCallout("remote-option4-pool-set",
                                      option4_pool_set_command);
        handle.registerCommandCallout("remote-option4-subnet-del",
                                      option4_subnet_del_command);
        handle.registerCommandCallout("remote-option4-subnet-set",
                                      option4_subnet_set_command);
        handle.registerCommandCallout("remote-server4-del",
                                      server4_del_command);
        handle.registerCommandCallout("remote-server4-get",
                                      server4_get_command);
        handle.registerCommandCallout("remote-server4-get-all",
                                      server4_get_all_command);
        handle.registerCommandCallout("remote-server4-set",
                                      server4_set_command);
        handle.registerCommandCallout("remote-subnet4-del-by-id",
                                      subnet4_del_by_id_command);
        handle.registerCommandCallout("remote-subnet4-del-by-prefix",
                                      subnet4_del_by_prefix_command);
        handle.registerCommandCallout("remote-subnet4-get-by-id",
                                      subnet4_get_by_id_command);
        handle.registerCommandCallout("remote-subnet4-get-by-prefix",
                                      subnet4_get_by_prefix_command);
        handle.registerCommandCallout("remote-subnet4-list",
                                      subnet4_list_command);
        handle.registerCommandCallout("remote-subnet4-set",
                                      subnet4_set_command);

        impl6 = boost::make_shared<ConfigCmdsDhcp6Impl>();

        handle.registerCommandCallout("remote-class6-del",
                                      client_class6_del_command);
        handle.registerCommandCallout("remote-class6-get",
                                      client_class6_get_command);
        handle.registerCommandCallout("remote-class6-get-all",
                                      client_class6_get_all_command);
        handle.registerCommandCallout("remote-class6-set",
                                      client_class6_set_command);
        handle.registerCommandCallout("remote-global-parameter6-del",
                                      global_parameter6_del_command);
        handle.registerCommandCallout("remote-global-parameter6-get",
                                      global_parameter6_get_command);
        handle.registerCommandCallout("remote-global-parameter6-get-all",
                                      global_parameter6_get_all_command);
        handle.registerCommandCallout("remote-global-parameter6-set",
                                      global_parameter6_set_command);
        handle.registerCommandCallout("remote-network6-del",
                                      network6_del_command);
        handle.registerCommandCallout("remote-network6-get",
                                      network6_get_command);
        handle.registerCommandCallout("remote-network6-list",
                                      network6_list_command);
        handle.registerCommandCallout("remote-network6-set",
                                      network6_set_command);
        handle.registerCommandCallout("remote-option-def6-del",
                                      option_def6_del_command);
        handle.registerCommandCallout("remote-option-def6-get",
                                      option_def6_get_command);
        handle.registerCommandCallout("remote-option-def6-get-all",
                                      option_def6_get_all_command);
        handle.registerCommandCallout("remote-option-def6-set",
                                      option_def6_set_command);
        handle.registerCommandCallout("remote-option6-global-del",
                                      option6_global_del_command);
        handle.registerCommandCallout("remote-option6-global-get",
                                      option6_global_get_command);
        handle.registerCommandCallout("remote-option6-global-get-all",
                                      option6_global_get_all_command);
        handle.registerCommandCallout("remote-option6-global-set",
                                      option6_global_set_command);
        handle.registerCommandCallout("remote-option6-network-del",
                                      option6_network_del_command);
        handle.registerCommandCallout("remote-option6-network-set",
                                      option6_network_set_command);
        handle.registerCommandCallout("remote-option6-pd-pool-del",
                                      option6_pd_pool_del_command);
        handle.registerCommandCallout("remote-option6-pd-pool-set",
                                      option6_pd_pool_set_command);
        handle.registerCommandCallout("remote-option6-pool-del",
                                      option6_pool_del_command);
        handle.registerCommandCallout("remote-option6-pool-set",
                                      option6_pool_set_command);
        handle.registerCommandCallout("remote-option6-subnet-del",
                                      option6_subnet_del_command);
        handle.registerCommandCallout("remote-option6-subnet-set",
                                      option6_subnet_set_command);
        handle.registerCommandCallout("remote-server6-del",
                                      server6_del_command);
        handle.registerCommandCallout("remote-server6-get",
                                      server6_get_command);
        handle.registerCommandCallout("remote-server6-get-all",
                                      server6_get_all_command);
        handle.registerCommandCallout("remote-server6-set",
                                      server6_set_command);
        handle.registerCommandCallout("remote-subnet6-del-by-id",
                                      subnet6_del_by_id_command);
        handle.registerCommandCallout("remote-subnet6-del-by-prefix",
                                      subnet6_del_by_prefix_command);
        handle.registerCommandCallout("remote-subnet6-get-by-id",
                                      subnet6_get_by_id_command);
        handle.registerCommandCallout("remote-subnet6-get-by-prefix",
                                      subnet6_get_by_prefix_command);
        handle.registerCommandCallout("remote-subnet6-list",
                                      subnet6_list_command);
        handle.registerCommandCallout("remote-subnet6-set",
                                      subnet6_set_command);

    } catch (const std::exception& ex) {
        return (CONTROL_RESULT_ERROR);
    }

    LOG_INFO(cb_cmds_logger, CB_CMDS_INIT_OK);
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This function is called when the library is unloaded.
///
/// @return 0 if deregistration was successful, 1 otherwise
int unload() {
    LOG_INFO(cb_cmds_logger, CB_CMDS_DEINIT_OK);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

}
