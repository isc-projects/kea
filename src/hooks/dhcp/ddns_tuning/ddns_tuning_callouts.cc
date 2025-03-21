// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <database/audit_entry.h>
#include <ddns_tuning.h>
#include <ddns_tuning_log.h>
#include <cc/command_interpreter.h>
#include <dhcp/option_string.h>
#include <dhcp/option4_client_fqdn.h>
#include <dhcp/option6_client_fqdn.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/subnet.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <hooks/hooks.h>
#include <process/daemon.h>
#include <string>

namespace isc {
namespace ddns_tuning {

DdnsTuningImplPtr impl;

} // end of namespace ddns_tuning
} // end of namespace isc

using namespace isc;
using namespace isc::log;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::ddns_tuning;
using namespace isc::hooks;
using namespace isc::process;
using namespace std;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief This callout is called at the "cb4_updated" hook.
///
/// If it detects that any subnets were altered by the update it
/// replaces the subnet expression cache contents with new expressions
/// for the subnets contained in current server configuration.  If any
/// of the subnet expressions fail to parse this function will return
/// a non-zero value.
///
/// @param handle CalloutHandle.
///
/// @return 0 upon success, number of expressions that failed otherwise.
int cb4_updated(CalloutHandle& handle) {
    // Only repopulate the cache if CB updated subnets. Global expression is done
    // via hook parameter, so that can only happen on a reconfigure.
    // Audit entries track by StampedElement::id and there is no mapping currently
    // in Subnet4Collection between those and SubnetIDs.  There is no efficient way
    // to select added or updated subnets, nor to identify those that were deleted,
    // so we'll just repopulate the entire cache if there were any subnet changes.
    AuditEntryCollectionPtr audit_entries;
    handle.getArgument("audit_entries", audit_entries);

    auto const& object_type_idx = audit_entries->get<AuditEntryObjectTypeTag>();
    auto range = object_type_idx.equal_range("dhcp4_subnet");
    if (std::distance(range.first, range.second)) {
        return (impl->repopulateCache(CfgMgr::instance().getCurrentCfg()->getCfgSubnets4()));
    }

    return (0);
}

/// @brief This callout is called at the "dhcp4_srv_configured" hook.
///
/// It replaces the subnet expression cache contents with new expressions
/// for the subnets contained in the server configuration passed in via
/// the handle.  If any of the subnet expressions fail to parse this
/// function will return a non-zero value.
///
/// @param handle CalloutHandle.
///
/// @return 0 upon success, number of expressions that failed otherwise
int dhcp4_srv_configured(CalloutHandle& handle) {
    SrvConfigPtr cfg;
    handle.getArgument("server_config", cfg);
    int result = impl->repopulateCache(cfg->getCfgSubnets4());
    if (result) {
        handle.setStatus(isc::hooks::CalloutHandle::NEXT_STEP_DROP);
        const string error("Errors were detected in the ddns tuning hooks library configuration.");
        handle.setArgument("error", error);
    }
    return (result);
}

/// @brief This callout is called at the "ddns4_update" hook.
///
/// Attempts to calculate a host name for the given client query
/// for the given subnet based on configured host name expressions.  If
/// this results in a different, non-empty host name value then the original
/// host name:
/// -# The new name is qualified based on the given DDNS behavioral parameters
/// (i.e. ddns-qualifying-suffix)
///
/// The forward and reverse flag arguments are not currently used.
///
/// @param handle CalloutHandle.
///
/// @return 0 upon success, non-zero otherwise
int ddns4_update(CalloutHandle& handle) {
    // Catch insanity.
    if (!impl) {
        isc_throw(Unexpected, "ddns4_update called with no impl!");
    }

    // Punt if set to DROP.
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP) {
        return (0);
    }

    // Get the parameters we currently use.
    string hostname;
    Pkt4Ptr query;
    Pkt4Ptr response;
    ConstSubnet4Ptr subnet;
    DdnsParamsPtr ddns_params;

    handle.getArgument("hostname", hostname);
    handle.getArgument("query4", query);
    handle.getArgument("response4", response);
    handle.getArgument("subnet4", subnet);
    handle.getArgument("ddns-params", ddns_params);

    try {
        // Attempt to calculate the host name.  If the result is a not empty and
        // different from the original qualify, update the response, and then
        // the hostname argument.
        string calc_hostname = impl->calculateHostname(query, subnet);
        if (!calc_hostname.empty() && (calc_hostname != hostname)) {
            // Count the number of DNS labels in the name.
            auto label_count = OptionDataTypeUtil::getLabelCount(calc_hostname);

            // If there are two labels, it means that we have an unqualified name
            // and we need to add the qualifying suffix.
            if (label_count == 2) {
                D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
                calc_hostname = d2_mgr.qualifyName(calc_hostname, *ddns_params, false);
            }

            LOG_DEBUG(ddns_tuning_logger, DBGLVL_TRACE_BASIC, DDNS_TUNING4_CALCULATED_HOSTNAME)
                      .arg(hostname)
                      .arg(calc_hostname)
                      .arg(query->getLabel());

            // Send the new name back to the caller.
            handle.setArgument("hostname", calc_hostname);
        }
    } catch (const exception& ex) {
        LOG_ERROR(ddns_tuning_logger, DDNS_TUNING4_PROCESS_ERROR)
                  .arg(query->getLabel()).arg(ex.what());
        return (1);
    }

    // Set direction flags to false if the client belongs to "SKIP_DDNS"
    if (query->inClass("SKIP_DDNS")) {
        LOG_DEBUG(ddns_tuning_logger, DBGLVL_TRACE_BASIC, DDNS_TUNING4_SKIPPING_DDNS)
                  .arg(query->getLabel());
        handle.setArgument("fwd-update", false);
        handle.setArgument("rev-update", false);
    }

    return (0);
}

/// @brief This callout is called at the "cb6_updated" hook.
///
/// If it detects that any subnets were altered by the update it
/// replaces the subnet expression cache contents with new expressions
/// for the subnets contained in current server configuration.  If any
/// of the subnet expressions fail to parse this function will return
/// a non-zero value.
///
/// @param handle CalloutHandle.
///
/// @return 0 upon success, number of expressions that failed otherwise.
int cb6_updated(CalloutHandle& handle) {
    // Only repopulate the cache if CB updated subnets. Global expression is done
    // via hook parameter, so that can only happen on a reconfigure.
    // Audit entries track by StampedElement::id and there is no mapping currently
    // in Subnet6Collection between those and SubnetIDs.  There is no efficient way
    // to select added or updated subnets, nor to identify those that were deleted,
    // so we'll just repopulate the entire cache if there were any subnet changes.
    AuditEntryCollectionPtr audit_entries;
    handle.getArgument("audit_entries", audit_entries);

    auto const& object_type_idx = audit_entries->get<AuditEntryObjectTypeTag>();
    auto range = object_type_idx.equal_range("dhcp6_subnet");
    if (std::distance(range.first, range.second)) {
        return (impl->repopulateCache(CfgMgr::instance().getCurrentCfg()->getCfgSubnets6()));
    }

    return (0);
}

/// @brief This callout is called at the "dhcp6_srv_configured" hook.
///
/// It replaces the subnet expression cache contents with new expressions
/// for the subnets contained in the server configuration passed in via
/// the handle.  If any of the subnet expressions fail to parse this
/// function will return a non-zero value.
///
/// @param handle CalloutHandle.
///
/// @return 0 upon success, number of expressions that failed otherwise
int dhcp6_srv_configured(CalloutHandle& handle) {
    SrvConfigPtr cfg;
    handle.getArgument("server_config", cfg);
    int result = impl->repopulateCache(cfg->getCfgSubnets6());
    if (result) {
        handle.setStatus(isc::hooks::CalloutHandle::NEXT_STEP_DROP);
        const string error("Errors were detected in the ddns tuning hooks library configuration.");
        handle.setArgument("error", error);
    }
    return (result);
}

/// @brief This callout is called at the "ddns6_update" hook.
///
/// Attempts to calculate a host name for the given client query
/// for the given subnet based on configured host name expressions.  If
/// this results in a different, non-empty host name value then the original
/// host name:
/// -# The new name is qualified based on the given DDNS behavioral parameters
/// (i.e. ddns-qualifying-suffix)
///
/// The forward and reverse flag arguments are not currently used.
///
/// @param handle CalloutHandle.
///
/// @return 0 upon success, non-zero otherwise
int ddns6_update(CalloutHandle& handle) {
    // Catch insanity.
    if (!impl) {
        isc_throw(Unexpected, "ddns6_update called with no impl!");
    }

    // Punt if set to DROP.
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP) {
        return (0);
    }

    // Get the parameters we currently use.
    string hostname;
    Pkt6Ptr query;
    Pkt6Ptr response;
    ConstSubnet6Ptr subnet;
    DdnsParamsPtr ddns_params;

    handle.getArgument("hostname", hostname);
    handle.getArgument("query6", query);
    handle.getArgument("response6", response);
    handle.getArgument("subnet6", subnet);
    handle.getArgument("ddns-params", ddns_params);

    try {
        // Attempt to calculate the host name.  If the result is a not empty and
        // different from the original qualify, update the response, and then
        // the hostname argument.
        string calc_hostname = impl->calculateHostname(query, subnet);
        if (!calc_hostname.empty() && (calc_hostname != hostname)) {
            // Count the number of DNS labels in the name.
            auto label_count = OptionDataTypeUtil::getLabelCount(calc_hostname);

            // If there are two labels, it means that we have an unqualified name
            // and we need to add the qualifying suffix.
            if (label_count == 2) {
                D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
                calc_hostname = d2_mgr.qualifyName(calc_hostname, *ddns_params, true);
            }

            LOG_DEBUG(ddns_tuning_logger, DBGLVL_TRACE_BASIC, DDNS_TUNING6_CALCULATED_HOSTNAME)
                      .arg(hostname)
                      .arg(calc_hostname)
                      .arg(query->getLabel());

            // Send the new name back to the caller.
            handle.setArgument("hostname", calc_hostname);
        }
    } catch (const exception& ex) {
        LOG_ERROR(ddns_tuning_logger, DDNS_TUNING6_PROCESS_ERROR)
                  .arg(query->getLabel()).arg(ex.what());
        return (1);
    }

    // Set direction flags to false if the client belongs to "SKIP_DDNS"
    if (query->inClass("SKIP_DDNS")) {
        LOG_DEBUG(ddns_tuning_logger, DBGLVL_TRACE_BASIC, DDNS_TUNING6_SKIPPING_DDNS)
                  .arg(query->getLabel());
        handle.setArgument("fwd-update", false);
        handle.setArgument("rev-update", false);
    }

    return (0);
}

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle
/// @return 0 when initialization is successful, 1 otherwise
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

        impl.reset(new DdnsTuningImpl(family));
        ConstElementPtr json = handle.getParameters();
        impl->configure(json);
    } catch (const exception& ex) {
        LOG_ERROR(ddns_tuning_logger, DDNS_TUNING_LOAD_ERROR)
                  .arg(ex.what());
        return (1);
    }

    LOG_INFO(ddns_tuning_logger, DDNS_TUNING_LOAD_OK);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return always 0.
int unload() {
    impl.reset();
    LOG_INFO(ddns_tuning_logger, DDNS_TUNING_UNLOAD);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
