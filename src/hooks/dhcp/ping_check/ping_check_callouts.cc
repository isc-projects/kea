// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service_mgr.h>
#include <database/audit_entry.h>
#include <dhcpsrv/cfgmgr.h>
#include <ping_check_log.h>
#include <ping_check_mgr.h>
#include <hooks/hooks.h>
#include <process/daemon.h>
#include <string>

namespace isc {
namespace ping_check {

/// @brief PingCheckMgr singleton
PingCheckMgrPtr mgr;

} // end of namespace ping_check
} // end of namespace isc

using namespace isc;
using namespace isc::asiolink;
using namespace isc::log;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::ping_check;
using namespace isc::hooks;
using namespace isc::process;
using namespace std;

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.
extern "C" {

/// @brief dhcp4_srv_configured implementation.
///
/// @param handle callout handle.
int dhcp4_srv_configured(CalloutHandle& handle) {
    try {
        SrvConfigPtr server_config;
        handle.getArgument("server_config", server_config);
        mgr->updateSubnetConfig(server_config);

        NetworkStatePtr network_state;
        handle.getArgument("network_state", network_state);

        // Schedule a start of the services. This ensures we begin after
        // the dust has settled and Kea MT mode has been firmly established.
        mgr->startService(network_state);
        IOServiceMgr::instance().registerIOService(mgr->getIOService());
    } catch (const std::exception& ex) {
        LOG_ERROR(ping_check_logger, PING_CHECK_DHCP4_SRV_CONFIGURED_FAILED)
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

/// @brief cb4_updated callout implementation.
///
/// If it detects that any subnets were altered by the update it
/// replaces the subnet cache contents.  If any of the subnets
/// fail to parse, the error is logged and the function returns
/// a non-zero value.
///
/// @param handle CalloutHandle.
///
/// @return 0 upon success, 1 otherwise
int cb4_updated(CalloutHandle& handle) {
    AuditEntryCollectionPtr audit_entries;
    handle.getArgument("audit_entries", audit_entries);

    auto const& object_type_idx = audit_entries->get<AuditEntryObjectTypeTag>();
    auto range = object_type_idx.equal_range("dhcp4_subnet");
    if (std::distance(range.first, range.second)) {
        try {
            // Server config has been committed, so use the current configuration.
            mgr->updateSubnetConfig(CfgMgr::instance().getCurrentCfg());
        } catch (const std::exception& ex) {
            LOG_ERROR(ping_check_logger, PING_CHECK_CB4_UPDATE_FAILED)
                      .arg(ex.what());
            return (1);
        }
    }

    return (0);
}

/// @brief lease4_offer callout implementation.
///
/// @param handle callout handle.
int lease4_offer(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    Pkt4Ptr query4;
    Lease4Ptr lease4;
    ParkingLotHandlePtr parking_lot;
    try {
        // Get all arguments available for the leases4_committed hook point.
        // If any of these arguments is not available this is a programmatic
        // error. An exception will be thrown which will be caught by the
        // caller and logged.
        handle.getArgument("query4", query4);

        Lease4CollectionPtr leases4;
        handle.getArgument("leases4", leases4);

        uint32_t offer_lifetime;
        handle.getArgument("offer_lifetime", offer_lifetime);

        Lease4Ptr old_lease;
        handle.getArgument("old_lease", old_lease);

        ConstHostPtr host;
        handle.getArgument("host", host);

        if (query4->getType() != DHCPDISCOVER) {
            isc_throw(InvalidOperation, "query4 is not a DHCPDISCOVER");
        }

        if (!leases4) {
            isc_throw(InvalidOperation, "leases4 is null");
        }

        if (!leases4->empty()) {
            lease4 = (*leases4)[0];
        }

        if (!lease4) {
            // lease has been reused or there is no address available to check.
            LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_DETAIL,
                      PING_CHECK_CHANNEL_NO_LEASE_OR_LEASE_REUSED);
            return (0);
        }

        // Fetch the parking lot.  If it's empty the server is not employing
        // parking, which is fine.
        // Create a reference to the parked packet. This signals that we have a
        // stake in unparking it.
        parking_lot = handle.getParkingLotHandlePtr();
        if (parking_lot) {
            parking_lot->reference(query4);
        }

        // Get configuration based on the lease's subnet.
        auto const& config = mgr->getScopedConfig(lease4);

        // Call shouldPing() to determine if we should ping check or not.
        // - status == PARK - ping check it
        // - status == CONTINUE - check not needed, release DHCPOFFER to client
        // - status == DROP - duplicate check, drop the duplicate DHCPOFFER
        status =  mgr->shouldPing(lease4, query4, old_lease, host, config);
        handle.setStatus(status);
        if (status == CalloutHandle::NEXT_STEP_PARK) {
            mgr->startPing(lease4, query4, parking_lot, config);
        } else {
            // Dereference the parked packet.  This releases our stake in it.
            if (parking_lot) {
                parking_lot->dereference(query4);
            }
        }

    } catch (const std::exception& ex) {
        LOG_ERROR(ping_check_logger, PING_CHECK_LEASE4_OFFER_FAILED)
                  .arg(query4 ? query4->getLabel() : "<no query>")
                  .arg(lease4 ? lease4->addr_.toText() : "<no lease>")
                  .arg(ex.what());
        // Make sure we dereference.
        if (parking_lot) {
            parking_lot->dereference(query4);
        }

        return (1);
    }

    return (0);
}

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle
/// @return 0 when initialization is successful, 1 otherwise
int load(LibraryHandle& handle) {
    try {
        // Make the hook library only loadable by kea-dhcp4.
        const string& proc_name = Daemon::getProcName();
        if (proc_name != "kea-dhcp4") {
            isc_throw(isc::Unexpected, "Bad process name: " << proc_name
                      << ", expected kea-dhcp4");
        }

        // Instantiate the manager singleton.
        mgr.reset(new PingCheckMgr());

        // Configure the manager using the hook library's parameters.
        ConstElementPtr json = handle.getParameters();
        mgr->configure(json);
    } catch (const exception& ex) {
        LOG_ERROR(ping_check_logger, PING_CHECK_LOAD_ERROR)
                  .arg(ex.what());
        return (1);
    }

    LOG_INFO(ping_check_logger, PING_CHECK_LOAD_OK);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return always 0.
int unload() {
    if (mgr) {
        IOServiceMgr::instance().unregisterIOService(mgr->getIOService());
        mgr.reset();
    }
    LOG_INFO(ping_check_logger, PING_CHECK_UNLOAD);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
