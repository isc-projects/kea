// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#include <config.h>

#include <ha_impl.h>
#include <ha_log.h>
#include <asiolink/io_service.h>
#include <cc/command_interpreter.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/network_state.h>
#include <exceptions/exceptions.h>
#include <hooks/hooks.h>
#include <process/daemon.h>

#include <sstream>
#include <string>

namespace isc {
namespace ha {

HAImplPtr impl;

} // end of namespace isc::ha
} // end of namespace isc

using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::ha;
using namespace isc::hooks;
using namespace isc::process;
using namespace std;

extern "C" {

/// @brief dhcp4_srv_configured callout implementation.
///
/// @param handle callout handle.
int dhcp4_srv_configured(CalloutHandle& handle) {
    try {
        isc::asiolink::IOServicePtr io_service;
        handle.getArgument("io_context", io_service);
        if (!io_service) {
            // Should not happen!
            handle.setStatus(isc::hooks::CalloutHandle::NEXT_STEP_DROP);
            const string error("Error: io_context is null");
            handle.setArgument("error", error);
            return (1);
        }
        isc::dhcp::NetworkStatePtr network_state;
        handle.getArgument("network_state", network_state);
        impl->startService(io_service, network_state, HAServerType::DHCPv4);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_DHCP4_START_SERVICE_FAILED)
            .arg(ex.what());
        handle.setStatus(isc::hooks::CalloutHandle::NEXT_STEP_DROP);
        ostringstream os;
        os << "Error: " << ex.what();
        string error(os.str());
        handle.setArgument("error", error);
        return (1);
    }
    return (0);
}

/// @brief buffer4_receive callout implementation.
///
/// @param handle callout handle.
int buffer4_receive(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP) {
        return (0);
    }

    try {
        impl->buffer4Receive(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_BUFFER4_RECEIVE_FAILED)
            .arg(ex.what());
        return (1);
    }

    return (0);
}

/// @brief leases4_committed callout implementation.
///
/// @param handle callout handle.
int leases4_committed(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    try {
        impl->leases4Committed(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_LEASES4_COMMITTED_FAILED)
            .arg(ex.what());
        return (1);
    }

    return (0);
}

/// @brief dhcp6_srv_configured callout implementation.
///
/// @param handle callout handle.
int dhcp6_srv_configured(CalloutHandle& handle) {
    try {
        isc::asiolink::IOServicePtr io_service;
        handle.getArgument("io_context", io_service);
        if (!io_service) {
            // Should not happen!
            handle.setStatus(isc::hooks::CalloutHandle::NEXT_STEP_DROP);
            const string error("Error: io_context is null");
            handle.setArgument("error", error);
            return (1);
        }
        isc::dhcp::NetworkStatePtr network_state;
        handle.getArgument("network_state", network_state);
        impl->startService(io_service, network_state, HAServerType::DHCPv6);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_DHCP6_START_SERVICE_FAILED)
            .arg(ex.what());
        handle.setStatus(isc::hooks::CalloutHandle::NEXT_STEP_DROP);
        ostringstream os;
        os << "Error: " << ex.what();
        string error(os.str());
        handle.setArgument("error", error);
        return (1);
    }
    return (0);
}

/// @brief buffer6_receive callout implementation.
///
/// @param handle callout handle.
int buffer6_receive(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    try {
        impl->buffer6Receive(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_BUFFER6_RECEIVE_FAILED)
            .arg(ex.what());
        return (1);
    }

    return (0);
}

/// @brief leases6_committed callout implementation.
///
/// @param handle callout handle.
int leases6_committed(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    try {
        impl->leases6Committed(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_LEASES6_COMMITTED_FAILED)
            .arg(ex.what());
        return (1);
    }

    return (0);
}

/// @brief command_processed callout implementation.
///
/// @param handle callout handle.
int command_processed(CalloutHandle& handle) {
    try {
        impl->commandProcessed(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_COMMAND_PROCESSED_FAILED)
            .arg(ex.what());
        return (1);
    }

    return (0);
}

/// @brief Heartbeat command handler implementation.
int heartbeat_command(CalloutHandle& handle) {
    try {
        impl->heartbeatHandler(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_HEARTBEAT_HANDLER_FAILED)
            .arg(ex.what());
        return (1);
    }

    return (0);
}

/// @brief ha-sync command handler implementation.
int sync_command(CalloutHandle& handle) {
    try {
        impl->synchronizeHandler(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_SYNC_HANDLER_FAILED)
            .arg(ex.what());
    }

    return (0);
}

/// @brief ha-scopes command handler implementation.
int scopes_command(CalloutHandle& handle) {
    try {
        impl->scopesHandler(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_SCOPES_HANDLER_FAILED)
            .arg(ex.what());
    }

    return (0);
}

/// @brief ha-continue command handler implementation.
int continue_command(CalloutHandle& handle) {
    try {
        impl->continueHandler(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_CONTINUE_HANDLER_FAILED)
            .arg(ex.what());
    }

    return (0);
}

/// @brief ha-maintenance-notify command handler implementation.
int maintenance_notify_command(CalloutHandle& handle) {
    try {
        impl->maintenanceNotifyHandler(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_MAINTENANCE_NOTIFY_HANDLER_FAILED)
            .arg(ex.what());
    }

    return (0);
}

/// @brief ha-maintenance-start command handler implementation.
int maintenance_start_command(CalloutHandle& handle) {
    try {
        impl->maintenanceStartHandler(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_MAINTENANCE_START_HANDLER_FAILED)
            .arg(ex.what());
    }

    return (0);
}

/// @brief ha-maintenance-cancel command handler implementation.
int maintenance_cancel_command(CalloutHandle& handle) {
    try {
        impl->maintenanceCancelHandler(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_MAINTENANCE_CANCEL_HANDLER_FAILED)
            .arg(ex.what());
    }

    return (0);
}

/// @brief ha-reset command handler implementation.
int ha_reset_command(CalloutHandle& handle) {
    try {
        impl->haResetHandler(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_RESET_HANDLER_FAILED)
            .arg(ex.what());
    }

    return (0);
}

/// @brief ha-sync-complete-notify command handler implementation.
int sync_complete_notify_command(CalloutHandle& handle) {
    try {
        impl->syncCompleteNotifyHandler(handle);
    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_SYNC_COMPLETE_NOTIFY_HANDLER_FAILED)
            .arg(ex.what());
    }

    return (0);
}

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle
/// @return 0 when initialization is successful, 1 otherwise
int load(LibraryHandle& handle) {
    ConstElementPtr config = handle.getParameter("high-availability");
    if (!config) {
        LOG_ERROR(ha_logger, HA_MISSING_CONFIGURATION);
        return (1);
    }

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

        impl = boost::make_shared<HAImpl>();
        impl->configure(config);

        handle.registerCommandCallout("ha-heartbeat", heartbeat_command);
        handle.registerCommandCallout("ha-sync", sync_command);
        handle.registerCommandCallout("ha-scopes", scopes_command);
        handle.registerCommandCallout("ha-continue", continue_command);
        handle.registerCommandCallout("ha-maintenance-notify", maintenance_notify_command);
        handle.registerCommandCallout("ha-maintenance-start", maintenance_start_command);
        handle.registerCommandCallout("ha-maintenance-cancel", maintenance_cancel_command);
        handle.registerCommandCallout("ha-reset", ha_reset_command);
        handle.registerCommandCallout("ha-sync-complete-notify", sync_complete_notify_command);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_CONFIGURATION_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    LOG_INFO(ha_logger, HA_INIT_OK);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return 0 if deregistration was successful, 1 otherwise
int unload() {
    impl.reset();
    LOG_INFO(ha_logger, HA_DEINIT_OK);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
