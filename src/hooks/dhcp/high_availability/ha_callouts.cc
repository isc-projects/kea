// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/network_state.h>
#include <hooks/hooks.h>

namespace isc {
namespace ha {

HAImplPtr impl;

} // end of namespace isc::ha
} // end of namespace isc

using namespace isc::config;
using namespace isc::data;
using namespace isc::ha;
using namespace isc::hooks;

extern "C" {

/// @brief dhcp4_srv_configured callout implementation.
///
/// @param handle callout handle.
int dhcp4_srv_configured(CalloutHandle& handle) {
    try {
        isc::asiolink::IOServicePtr io_service;
        handle.getArgument("io_context", io_service);
        isc::dhcp::NetworkStatePtr network_state;
        handle.getArgument("network_state", network_state);
        impl->startService(io_service, network_state, HAServerType::DHCPv4);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_DHCP4_START_SERVICE_FAILED)
            .arg(ex.what());
        return (1);
    }
    return (0);
}

/// @brief buffer4_receive callout implementation.
///
/// @param handle callout handle.
int buffer4_receive(CalloutHandle& handle) {
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
        isc::dhcp::NetworkStatePtr network_state;
        handle.getArgument("network_state", network_state);
        impl->startService(io_service, network_state, HAServerType::DHCPv6);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_DHCP6_START_SERVICE_FAILED)
            .arg(ex.what());
        return (1);
    }
    return (0);
}

/// @brief buffer6_receive callout implementation.
///
/// @param handle callout handle.
int buffer6_receive(CalloutHandle& handle) {
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
    try {
        impl->leases6Committed(handle);

    } catch (const std::exception& ex) {
        LOG_ERROR(ha_logger, HA_LEASES6_COMMITTED_FAILED)
            .arg(ex.what());
        return (1);
    }

    return (0);
}

/// @brief comand_processed callout implementation.
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
        impl = boost::make_shared<HAImpl>();
        impl->configure(config);

        handle.registerCommandCallout("ha-heartbeat", heartbeat_command);
        handle.registerCommandCallout("ha-sync", sync_command);
        handle.registerCommandCallout("ha-scopes", scopes_command);
        handle.registerCommandCallout("ha-continue", continue_command);

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
    LOG_INFO(ha_logger, HA_DEINIT_OK);
    return (0);
}

/// @brief This function is called to know the multi-threading compatibility.
///
/// @note: this should be revisited as the library is not essentially
/// uncompatible.
///
/// @return 0 which means not compatible with multi-threading.
int multi_threading_compatible() {
    return (0);
}

} // end extern "C"
