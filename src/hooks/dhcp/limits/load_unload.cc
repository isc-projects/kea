// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/dhcp_config_error.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/srv_config.h>
#include <exceptions/exceptions.h>
#include <hooks/library_handle.h>
#include <limits/limit_manager.h>
#include <process/daemon.h>

namespace isc {
namespace limits {

using namespace isc::dhcp;
using namespace isc::process;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces
extern "C" {

/// @brief Called by the hooks library manager when the library is loaded.
///
/// @param handle LibraryHandle
///
/// @return 0 on success, non-zero otherwise.
int
load(isc::hooks::LibraryHandle& handle) {
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

    if (handle.getParameters()) {
        isc_throw(ConfigError, "expected no parameters for libdhcp_limits.so, found "
                                   << handle.getParameters()->str());
    }

    // Parse the configuration to get the limits of interest. Take them from the
    // staging configuration since we are still in the hook library load phase.
    LimitManager::instance().initialize(CfgMgr::instance().getStagingCfg());

    return (0);
}

/// @brief Called by the hooks library manager when the library is unloaded.
///
/// @return 0 on success, non-zero otherwise.
int
unload() {
    // Parse an empty config to clear configuration and packet counters.
    LimitManager::instance().initialize(SrvConfigPtr());

    // Clear the class lease counters.
    if (LeaseMgrFactory::haveInstance() &&
        LeaseMgrFactory::instance().getType() == "memfile") {
        LeaseMgrFactory::instance().clearClassLeaseCounts();
    }

    return (0);
}

/// @brief Return multi-threading compatibility.
///
/// @return 1 means compatible with multi-threading.
int
multi_threading_compatible() {
    return (1);
}

}  // extern "C"

}  // namespace limits
}  // namespace isc
