// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#include <config.h>

#include <perfmon_log.h>
#include <perfmon_mgr.h>
#include <cc/command_interpreter.h>
#include <dhcpsrv/cfgmgr.h>
#include <hooks/hooks.h>
#include <process/daemon.h>

namespace isc {
namespace perfmon {

/// @brief PerfMonMgr singleton
PerfMonMgrPtr mgr;

} // end of namespace perfmon
}

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::log;
using namespace isc::process;
using namespace isc::perfmon;

extern "C" {

int dhcp4_srv_configured(CalloutHandle& /* handle */) {
    // We do this here rather than in load() to ensure we check after the
    // packet filter has been determined.
    LOG_DEBUG(perfmon_logger, DBGLVL_TRACE_BASIC,
              PERFMON_DHCP4_SOCKET_RECEIVED_TIME_SUPPORT)
              .arg(IfaceMgr::instance().isSocketReceivedTimeSupported() ? "Yes" : "No");
    return (0);
}

int dhcp6_srv_configured(CalloutHandle& /* handle */) {
    // We do this here rather than in load() to ensure we check after the
    // packet filter has been determined.
    LOG_DEBUG(perfmon_logger, DBGLVL_TRACE_BASIC,
              PERFMON_DHCP6_SOCKET_RECEIVED_TIME_SUPPORT)
              .arg(IfaceMgr::instance().isSocketReceivedTimeSupported() ? "Yes" : "No");
    return (0);
}

/// @brief This callout is called at the "pkt4_send" hook.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt4_send(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    Pkt4Ptr query;
    handle.getArgument("query4", query);
    LOG_DEBUG(perfmon_logger, DBGLVL_TRACE_DETAIL, PERFMON_DHCP4_PKT_EVENTS)
              .arg(query->getLabel())
              .arg(query->dumpPktEvents());

    return (0);
}

/// @brief This callout is called at the "pkt6_send" hook.
///
/// @param handle CalloutHandle which provides access to context.
///
/// @return 0 upon success, non-zero otherwise.
int pkt6_send(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    Pkt6Ptr query;
    handle.getArgument("query6", query);
    LOG_DEBUG(perfmon_logger, DBGLVL_TRACE_DETAIL, PERFMON_DHCP6_PKT_EVENTS)
              .arg(query->getLabel())
              .arg(query->dumpPktEvents());

    return (0);
}

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle
/// @return 0 when initialization is successful, 1 otherwise
int load(LibraryHandle& handle) {
    try {
        // Make the hook library only loadable for kea-dhcpX.
        uint16_t family = CfgMgr::instance().getFamily();
        const std::string& proc_name = Daemon::getProcName();
        if (family == AF_INET) {
            if (proc_name != "kea-dhcp4") {
                isc_throw(isc::Unexpected, "Bad process name: " << proc_name
                          << ", expected kea-dhcp4");
            }
        } else if (proc_name != "kea-dhcp6") {
            isc_throw(isc::Unexpected, "Bad process name: " << proc_name
                      << ", expected kea-dhcp6");
        }

        // Instantiate the manager singleton.
        mgr.reset(new PerfMonMgr(family));

        // Configure the manager using the hook library's parameters.
        ConstElementPtr json = handle.getParameters();
        mgr->configure(json);

        /// @todo register commands
        /// handle.registerCommandCallout("command-here", handler_here);
    } catch (const std::exception& ex) {
        LOG_ERROR(perfmon_logger, PERFMON_INIT_FAILED).arg(ex.what());
        return (1);
    }

    LOG_INFO(perfmon_logger, PERFMON_INIT_OK);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return 0 if deregistration was successful, 1 otherwise
int unload() {
    LOG_INFO(perfmon_logger, PERFMON_DEINIT_OK);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
