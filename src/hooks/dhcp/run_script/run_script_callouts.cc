// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <hooks/hooks.h>
#include <run_script.h>
#include <run_script_log.h>
#include <dhcp/option6_ia.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet.h>

namespace isc {
namespace run_script {

RunScriptImplPtr impl;

} // end of namespace run_script
} // end of namespace isc

using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::run_script;
using namespace isc::util;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle
/// @return 0 when initialization is successful, 1 otherwise
int load(LibraryHandle& handle) {
    try {
        impl.reset(new RunScriptImpl());
        impl->configure(handle);
    } catch (const std::exception& ex) {
        LOG_ERROR(run_script_logger, RUN_SCRIPT_LOAD_ERROR)
            .arg(ex.what());
        return (1);
    }

    LOG_INFO(run_script_logger, RUN_SCRIPT_LOAD);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return always 0.
int unload() {
    impl.reset();
    LOG_INFO(run_script_logger, RUN_SCRIPT_UNLOAD);
    return (0);
}

/// @brief handle @ref lease4_renew hook and set environment parameters for the
/// script.
/// IN: query4 subnet4 clientid hwaddr lease4
/// OUT: next_step
int lease4_renew(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }
    ProcessEnvVars vars;
    Pkt4Ptr pkt4;
    handle.getArgument("query4", pkt4);
    RunScriptImpl::extractPkt4(vars, pkt4);
    Subnet4Ptr subnet4;
    handle.getArgument("subnet4", subnet4);
    RunScriptImpl::extractSubnet4(vars, subnet4);
    ClientIdPtr clientid;
    handle.getArgument("clientid", clientid);
    RunScriptImpl::extractClientID(vars, clientid);
    HWAddrPtr hwaddr;
    handle.getArgument("hwaddr", hwaddr);
    RunScriptImpl::extractHWAddr(vars, hwaddr);
    Lease4Ptr lease4;
    handle.getArgument("lease4", lease4);
    RunScriptImpl::extractLease4(vars, lease4);
    impl->runScript(vars);
    return (0);
}

/// @brief handle @ref lease4_expire hook and set environment parameters for the
/// script.
/// IN: lease4 remove_lease
/// OUT: next_step
int lease4_expire(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }
    ProcessEnvVars vars;
    Lease4Ptr lease4;
    handle.getArgument("lease4", lease4);
    RunScriptImpl::extractLease4(vars, lease4);
    bool remove_lease;
    handle.getArgument("remove_lease", remove_lease);
    RunScriptImpl::extractBoolean(vars, remove_lease);
    impl->runScript(vars);
    return (0);
}

/// @brief handle @ref lease4_recover hook and set environment parameters for
/// the script.
/// IN: lease4
/// OUT: next_step
int lease4_recover(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }
    ProcessEnvVars vars;
    Lease4Ptr lease4;
    handle.getArgument("lease4", lease4);
    RunScriptImpl::extractLease4(vars, lease4);
    impl->runScript(vars);
    return (0);
}

/// @brief handle @ref leases4_committed hook and set environment parameters for
/// the script.
/// IN: query4 leases4 deleted_leases4
/// OUT: next_step
int leases4_committed(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }
    ProcessEnvVars vars;
    Pkt4Ptr pkt4;
    handle.getArgument("query4", pkt4);
    RunScriptImpl::extractPkt4(vars, pkt4);
    Lease4CollectionPtr leases4;
    handle.getArgument("leases4", leases4);
    RunScriptImpl::extractLeases4(vars, leases4);
    Lease4CollectionPtr deleted_leases4;
    handle.getArgument("deleted_leases4", deleted_leases4);
    RunScriptImpl::extractLeases4(vars, deleted_leases4);
    impl->runScript(vars);
    return (0);
}

/// @brief handle @ref lease4_release hook and set environment parameters for
/// the script.
/// IN: query4 lease4
/// OUT: next_step
int lease4_release(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }
    ProcessEnvVars vars;
    Pkt4Ptr pkt4;
    handle.getArgument("query4", pkt4);
    RunScriptImpl::extractPkt4(vars, pkt4);
    Lease4Ptr lease4;
    handle.getArgument("lease4", lease4);
    RunScriptImpl::extractLease4(vars, lease4);
    impl->runScript(vars);
    return (0);
}

/// @brief handle @ref lease4_decline hook and set environment parameters for
/// the script.
/// IN: query4 lease4
/// OUT: next_step
int lease4_decline(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }
    ProcessEnvVars vars;
    Pkt4Ptr pkt4;
    handle.getArgument("query4", pkt4);
    RunScriptImpl::extractPkt4(vars, pkt4);
    Lease4Ptr lease4;
    handle.getArgument("lease4", lease4);
    RunScriptImpl::extractLease4(vars, lease4);
    impl->runScript(vars);
    return (0);
}

/// @brief handle @ref lease6_renew hook and set environment parameters for the
/// script.
/// IN: query6 lease6 ia_na/ia_pd
/// OUT: next_step
int lease6_renew(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }
    ProcessEnvVars vars;
    Pkt6Ptr pkt6;
    handle.getArgument("query6", pkt6);
    RunScriptImpl::extractPkt6(vars, pkt6);
    Lease6Ptr lease6;
    handle.getArgument("lease6", lease6);
    RunScriptImpl::extractLease6(vars, lease6);
    Option6IAPtr option6IA;
    if (lease6->type_ == Lease::TYPE_NA) {
        handle.getArgument("ia_na", option6IA);
    } else {
        handle.getArgument("ia_pd", option6IA);
    }
    RunScriptImpl::extractOptionIA(vars, option6IA);
    impl->runScript(vars);
    return (0);
}

/// @brief handle @ref lease6_rebind hook and set environment parameters for the
/// script.
/// IN: query6 lease6 ia_na/ia_pd
/// OUT: next_step
int lease6_rebind(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }
    ProcessEnvVars vars;
    Pkt6Ptr pkt6;
    handle.getArgument("query6", pkt6);
    RunScriptImpl::extractPkt6(vars, pkt6);
    Lease6Ptr lease6;
    handle.getArgument("lease6", lease6);
    RunScriptImpl::extractLease6(vars, lease6);
    Option6IAPtr option6IA;
    if (lease6->type_ == Lease::TYPE_NA) {
        handle.getArgument("ia_na", option6IA);
    } else {
        handle.getArgument("ia_pd", option6IA);
    }
    RunScriptImpl::extractOptionIA(vars, option6IA);
    impl->runScript(vars);
    return (0);
}

/// @brief handle @ref lease6_expire hook and set environment parameters for the
/// script.
/// IN: lease6 remove_lease
/// OUT: next_step
int lease6_expire(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }
    ProcessEnvVars vars;
    Lease6Ptr lease6;
    handle.getArgument("lease6", lease6);
    RunScriptImpl::extractLease6(vars, lease6);
    bool remove_lease;
    handle.getArgument("remove_lease", remove_lease);
    RunScriptImpl::extractBoolean(vars, remove_lease);
    impl->runScript(vars);
    return (0);
}

/// @brief handle @ref lease6_recover hook and set environment parameters for
/// the script.
/// IN: lease6
/// OUT: next_step
int lease6_recover(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }
    ProcessEnvVars vars;
    Lease6Ptr lease6;
    handle.getArgument("lease6", lease6);
    RunScriptImpl::extractLease6(vars, lease6);
    impl->runScript(vars);
    return (0);
}

/// @brief handle @ref leases6_committed hook and set environment parameters for
/// the script.
/// IN: query6 leases6 deleted_leases6
/// OUT: next_step
int leases6_committed(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }
    ProcessEnvVars vars;
    Pkt6Ptr pkt6;
    handle.getArgument("query6", pkt6);
    RunScriptImpl::extractPkt6(vars, pkt6);
    Lease6CollectionPtr leases6;
    handle.getArgument("leases6", leases6);
    RunScriptImpl::extractLeases6(vars, leases6);
    Lease6CollectionPtr deleted_leases6;
    handle.getArgument("deleted_leases6", deleted_leases6);
    RunScriptImpl::extractLeases6(vars, deleted_leases6);
    impl->runScript(vars);
    return (0);
}

/// @brief handle @ref lease6_release hook and set environment parameters for
/// the script.
/// IN: query6 lease6
/// OUT: next_step
int lease6_release(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }
    ProcessEnvVars vars;
    Pkt6Ptr pkt6;
    handle.getArgument("query6", pkt6);
    RunScriptImpl::extractPkt6(vars, pkt6);
    Lease6Ptr lease6;
    handle.getArgument("lease6", lease6);
    RunScriptImpl::extractLease6(vars, lease6);
    impl->runScript(vars);
    return (0);
}

/// @brief handle @ref lease6_decline hook and set environment parameters for
/// the script.
/// IN: query6 lease6
/// OUT: next_step
int lease6_decline(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }
    ProcessEnvVars vars;
    Pkt6Ptr pkt6;
    handle.getArgument("query6", pkt6);
    RunScriptImpl::extractPkt6(vars, pkt6);
    Lease6Ptr lease6;
    handle.getArgument("lease6", lease6);
    RunScriptImpl::extractLease6(vars, lease6);
    impl->runScript(vars);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
