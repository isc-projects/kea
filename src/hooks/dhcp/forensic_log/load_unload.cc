// Copyright (C) 2016-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file load_unload.cc Defines the load and unload hooks library functions.

#include <config.h>

#include <asiolink/io_service.h>
#include <asiolink/io_service_mgr.h>
#include <cc/data.h>
#include <hooks/hooks.h>
#include <database/database_connection.h>
#include <dhcpsrv/cfgmgr.h>
#include <process/daemon.h>
#include <legal_log_log.h>
#include <dhcpsrv/backend_store.h>
#include <rotating_file.h>

#include <boost/lexical_cast.hpp>

#include <sstream>
#include <string>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::process;
using namespace isc::legal_log;
using namespace std;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief Called by the Hooks library manager when the library is loaded.
///
/// Instantiates the BackendStore and then opens it. If there is no type
/// or type is logfile, use a RotatingFile else use a Database.
///
/// @return 0 upon success, non-zero if the legal file cannot be opened
int load(LibraryHandle& handle) {
    try {
        // Make the hook library not loadable by d2 or ca.
        uint16_t family = CfgMgr::instance().getFamily();
        const string& proc_name = Daemon::getProcName();
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

        BackendStoreFactory::registerBackendFactory("logfile", RotatingFile::factory);

        // Get and decode parameters.
        ConstElementPtr const& parameters(handle.getParameters());
        DatabaseConnection::ParameterMap map;

        try {
            BackendStore::parseConfig(parameters, map);
            BackendStoreFactory::addBackend(map, handle.getLibraryIndex());
        } catch (const isc::db::DbOpenErrorWithRetry& err) {
            string redacted;
            try {
                redacted = DatabaseConnection::redactedAccessString(map);
            } catch (...) {
            }
            LOG_INFO(legal_log_logger, LEGAL_LOG_DB_OPEN_CONNECTION_WITH_RETRY_FAILED)
                    .arg(redacted).arg(err.what());
        }

    } catch (const std::exception& ex) {
        // Log the error and return failure.
        LOG_ERROR(legal_log_logger, LEGAL_LOG_LOAD_ERROR)
            .arg(ex.what());
        return (1);
    }

    return (0);
}

/// @brief Called by the Hooks library manager when the library is unloaded.
///
/// Explicitly destroys the BackendStore instance. Any errors are logged but
/// swallowed.
///
/// @return Always 0.
int unload() {
    try {
        // Since it's "global" Let's explicitly destroy it now rather
        // than indeterminately. Note, BackendStore destructor will close
        // the store.
        BackendStoreFactory::delAllBackends();

        BackendStoreFactory::unregisterBackendFactory("logfile");
    } catch (const std::exception& ex) {
        // On the off chance something goes awry, catch it and log it.
        // @todo Not sure if we should return a non-zero result or not.
        LOG_ERROR(legal_log_logger, LEGAL_LOG_UNLOAD_ERROR)
            .arg(ex.what());
    }

    return (0);
}

/// @brief dhcp4_srv_configured callout implementation.
///
/// @param handle callout handle.
int dhcp4_srv_configured(CalloutHandle& /* handle */) {
    return (0);
}

/// @brief dhcp6_srv_configured callout implementation.
///
/// @param handle callout handle.
int dhcp6_srv_configured(CalloutHandle& /* handle */) {
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

}
