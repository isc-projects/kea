// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#include <config.h>

#include <asiolink/io_service_mgr.h>
#include <dhcpsrv/base_host_data_source.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <hooks/hooks.h>
#include <process/daemon.h>
#include <mysql_cb_impl.h>
#include <mysql_cb_dhcp4.h>
#include <mysql_cb_dhcp6.h>
#include <mysql_cb_log.h>
#include <mysql_hb_log.h>
#include <mysql_host_data_source.h>
#include <mysql_legal_log.h>
#include <mysql_lb_log.h>
#include <mysql_lease_mgr.h>

#include <sstream>
#include <string>

using namespace isc::asiolink;
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

    // Register MySQL CB factories with CB Managers
    MySqlConfigBackendDHCPv4::registerBackendType();
    MySqlConfigBackendDHCPv6::registerBackendType();

    // Register MySQL FB factories with Backend Store managers.
    LegalLogMgrFactory::registerBackendFactory("mysql",
                                                MySqlStore::factory,
                                                true,
                                                MySqlStore::getDBVersion);

    // Register MySQL HB factories with Host Managers
    HostDataSourceFactory::registerFactory("mysql",
                                           MySqlHostDataSource::factory,
                                           true,
                                           MySqlHostDataSource::getDBVersion);

    // Register MySQL LB factories with Lease Managers
    LeaseMgrFactory::registerFactory("mysql",
                                     MySqlLeaseMgr::factory,
                                     true,
                                     MySqlLeaseMgr::getDBVersion);
    LOG_INFO(mysql_lb_logger, MYSQL_INIT_OK);
    return (0);
}

/// @brief This function is called by the DHCPv4 server when it is configured.
///
/// The only purpose of this callout is to retrieve io_service_ reference.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int dhcp4_srv_configured(CalloutHandle& /* handle */) {
    MySqlConfigBackendImpl::setIOService(IOServicePtr(new IOService()));
    IOServiceMgr::instance().registerIOService(MySqlConfigBackendImpl::getIOService());
    return (0);
}

/// @brief This function is called by the DHCPv6 server when it is configured.
///
/// The only purpose of this callout is to retrieve io_service_ reference.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int dhcp6_srv_configured(CalloutHandle& /* handle */) {
    MySqlConfigBackendImpl::setIOService(IOServicePtr(new IOService()));
    IOServiceMgr::instance().registerIOService(MySqlConfigBackendImpl::getIOService());
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return 0 if deregistration was successful, 1 otherwise
int unload() {
    // Unregister the factories and remove MySQL backends
    MySqlConfigBackendDHCPv4::unregisterBackendType();
    MySqlConfigBackendDHCPv6::unregisterBackendType();
    IOServicePtr io_service = MySqlConfigBackendImpl::getIOService();
    if (io_service) {
        IOServiceMgr::instance().unregisterIOService(io_service);
        io_service->stopAndPoll();
        MySqlConfigBackendImpl::setIOService(IOServicePtr());
    }

    // Unregister the factories and remove MySQL backends
    LegalLogMgrFactory::unregisterBackendFactory("mysql", true);

    // Unregister the factories and remove MySQL backends
    HostDataSourceFactory::deregisterFactory("mysql", true);

    // Unregister the factories and remove MySQL backends
    LeaseMgrFactory::deregisterFactory("mysql", true);
    LOG_INFO(mysql_lb_logger, MYSQL_DEINIT_OK);
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
