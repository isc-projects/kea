// Copyright (C) 2021-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#include <config.h>

#include <dhcpsrv/cfgmgr.h>
#include <hooks/hooks.h>
#include <process/daemon.h>
#include <pgsql_cb_impl.h>

#include <pgsql_cb_dhcp4.h>
#include <pgsql_cb_dhcp6.h>
#include <pgsql_cb_log.h>

#include <sstream>
#include <string>

using namespace isc::cb;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::log;
using namespace isc::process;
using namespace std;

extern "C" {

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle
/// @return 0 when initialization is successful, 1 otherwise

int load(LibraryHandle& /* handle */) {
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

    LOG_INFO(pgsql_cb_logger, PGSQL_CB_INIT_OK);
    // Register PostgreSQL CB factories with CB Managers
    isc::dhcp::PgSqlConfigBackendDHCPv4::registerBackendType();
    isc::dhcp::PgSqlConfigBackendDHCPv6::registerBackendType();

    return (0);
}

/// @brief This function is called by the DHCPv4 server when it is configured.
///
/// The only purpose of this callout is to retrieve io_service_ reference.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int dhcp4_srv_configured(CalloutHandle& handle) {
    isc::asiolink::IOServicePtr io_service;
    handle.getArgument("io_context", io_service);
    if (!io_service) {
        const string error("Error: io_context is null");
        handle.setArgument("error", error);
        handle.setStatus(isc::hooks::CalloutHandle::NEXT_STEP_DROP);
        return (1);
    }
    isc::dhcp::PgSqlConfigBackendImpl::setIOService(io_service);
    return (0);
}

/// @brief This function is called by the DHCPv6 server when it is configured.
///
/// The only purpose of this callout is to retrieve io_service_ reference.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int dhcp6_srv_configured(CalloutHandle& handle) {
    isc::asiolink::IOServicePtr io_service;
    handle.getArgument("io_context", io_service);
    if (!io_service) {
        const string error("Error: io_context is null");
        handle.setArgument("error", error);
        handle.setStatus(isc::hooks::CalloutHandle::NEXT_STEP_DROP);
        return (1);
    }
    isc::dhcp::PgSqlConfigBackendImpl::setIOService(io_service);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return 0 if deregistration was successful, 1 otherwise
int unload() {
    LOG_INFO(pgsql_cb_logger, PGSQL_CB_DEINIT_OK);
    // Unregister the factories and remove PostgreSQL backends
    isc::dhcp::PgSqlConfigBackendDHCPv4::unregisterBackendType();
    isc::dhcp::PgSqlConfigBackendDHCPv6::unregisterBackendType();
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @note: the compatibility is based on the assumption this hook library
/// is always called from the main thread.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
