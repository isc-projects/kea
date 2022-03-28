// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#include <config.h>

#include <hooks/hooks.h>
#include <mysql_cb_impl.h>

#include <mysql_cb_dhcp4.h>
#include <mysql_cb_dhcp6.h>
#include <mysql_cb_log.h>

using namespace isc::cb;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::log;

extern "C" {

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle
/// @return 0 when initialization is successful, 1 otherwise

int load(LibraryHandle& /* handle */) {
    LOG_INFO(mysql_cb_logger, MYSQL_CB_INIT_OK);
    // Register MySQL CB factories with CB Managers
    isc::dhcp::MySqlConfigBackendDHCPv4::registerBackendType();
    isc::dhcp::MySqlConfigBackendDHCPv6::registerBackendType();

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
    isc::dhcp::MySqlConfigBackendImpl::setIOService(io_service);
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
    isc::dhcp::MySqlConfigBackendImpl::setIOService(io_service);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return 0 if deregistration was successful, 1 otherwise
int unload() {
    LOG_INFO(mysql_cb_logger, MYSQL_CB_DEINIT_OK);
    // Unregister the factories and remove MySQL backends
    isc::dhcp::MySqlConfigBackendDHCPv4::unregisterBackendType();
    isc::dhcp::MySqlConfigBackendDHCPv6::unregisterBackendType();
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
