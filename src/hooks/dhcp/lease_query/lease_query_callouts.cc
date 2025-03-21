// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service.h>
#include <asiolink/io_service_mgr.h>
#include <database/audit_entry.h>
#include <hooks/hooks.h>
#include <dhcpsrv/cfgmgr.h>
#include <lease_query_log.h>
#include <lease_query_impl_factory.h>
#include <blq_service.h>
#include <process/daemon.h>
#include <stats/stats_mgr.h>

#include <string>
#include <vector>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::lease_query;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::log;
using namespace isc::process;
using namespace isc::stats;
using namespace std;

namespace {
/// @brief Extracts the library parameters into MapElement
///
/// @param handle the library handle
/// @return the config
///
ConstElementPtr getConfig(LibraryHandle& handle) {
    const std::vector<std::string> names = handle.getParameterNames();
    ElementPtr config = Element::createMap();

    for (auto const& name : names) {
        ConstElementPtr value = handle.getParameter(name);
        if (value) {
            config->set(name, value);
        }
    }

    // Note checkKeywords() will throw DhcpConfigError if there is a problem.
    SimpleParser::checkKeywords(LeaseQueryImpl::LEASE_QUERY_KEYWORDS, config);
    return (config);
}

/// @brief Upgrade v4 extended information.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int extended_info4_upgrade(CalloutHandle& handle) {
    return (LeaseQueryImpl4::upgradeHandler(handle));
}

/// @brief Upgrade v6 extended information.
///
/// @param handle Callout handle used to retrieve a command and
/// provide a response.
/// @return 0 if this callout has been invoked successfully,
/// 1 otherwise.
int extended_info6_upgrade(CalloutHandle& handle) {
    return (LeaseQueryImpl6::upgradeHandler(handle));
}
} // end of anonymous namespace

extern "C" {

/// @brief This callout is called at the "buffer4_receive" hook.
///
/// If the inbound packet hasn't been unpacked, it is unpacked.  If it
/// is anything other than DHCPLEASEQUERY we set the call status to
/// NEXT_STEP_SKIP and return 0 to indicate success (i.e. we ignore the
/// packet).
///
/// The query is passed into LeaseQueryImpl4::processQuery() which carries
/// out all aspects of responding to it:
///
/// - Validating the query
/// - Searching for matching leases
/// - Constructing the response
/// - Sending the response to the requester
///
/// @return 0 if the packet was handled appropriately, 1 if an error
/// occurred.
///
/// @param handle CalloutHandle.
///
/// @return 0 upon success, non-zero otherwise.
int buffer4_receive(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP) {
        return (0);
    }

    // Get the received message.
    Pkt4Ptr query;
    handle.getArgument("query4", query);
    try {
        // If it's not already unpacked, unpack it
        if (handle.getStatus() != CalloutHandle::NEXT_STEP_SKIP) {
            query->unpack();
        }
    } catch (const std::exception& ex) {
        LOG_DEBUG(lease_query_logger, DBGLVL_TRACE_BASIC,
                  DHCP4_LEASE_QUERY_PACKET_UNPACK_FAILED)
            .arg(query->getRemoteAddr().toText())
            .arg(query->getLocalAddr().toText())
            .arg(query->getIface())
            .arg(ex.what());
        // Increase the statistics of parse failures and dropped packets.
        StatsMgr::instance().addValue("pkt4-parse-failed",
                                      static_cast<int64_t>(1));
        StatsMgr::instance().addValue("pkt4-receive-drop",
                                      static_cast<int64_t>(1));
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return (0);
    }

    // Not a lease query, so return without handling it.
    // Make sure status is SKIP so it doesn't get unpacked again.
    if (query->getType() != DHCPLEASEQUERY) {
        handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);
        return (0);
    }

    LOG_DEBUG(lease_query_logger, DBGLVL_TRACE_BASIC, DHCP4_LEASE_QUERY_RECEIVED)
              .arg(LeaseQueryImpl4::leaseQueryLabel(query));
    StatsMgr::instance().addValue("pkt4-lease-query-received", static_cast<int64_t>(1));

    try {
        LeaseQueryImplFactory::getImpl().processQuery(query);
    } catch (const std::exception& ex) {
        // Failed to parse the packet.
        LOG_DEBUG(lease_query_logger, DBGLVL_TRACE_BASIC,
                  DHCP4_LEASE_QUERY_PROCESS_FAILED)
                  .arg(LeaseQueryImpl4::leaseQueryLabel(query))
                  .arg(ex.what());

        StatsMgr::instance().addValue("pkt4-receive-drop",
                                      static_cast<int64_t>(1));
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return (0);
    }

    // We always set status to DROP as the query has been handled.
    handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
    return (0);
}

/// @brief This callout is called at the "buffer6_receive" hook.
///
/// If the inbound packet hasn't been unpacked, it is unpacked.  If it
/// is anything other than DHCPV6_LEASEQUERY we set the call status to
/// NEXT_STEP_SKIP and return 0 to indicate success (i.e. we ignore the
/// packet).
///
/// The query is passed into LeaseQueryImpl6::processQuery() which carries
/// out all aspects of responding to it:
///
/// - Validating the query
/// - Searching for matching leases
/// - Constructing the response
/// - Sending the response to the requester
///
/// @return 0 if the packet was handled appropriately, 1 if an error
/// occurred.
///
/// @param handle CalloutHandle.
///
/// @return 0 upon success, non-zero otherwise.
int buffer6_receive(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP) {
        return (0);
    }

    // Get the received message.
    Pkt6Ptr query;
    handle.getArgument("query6", query);

    try {
        // If it's not already unpacked, unpack it.
        if (handle.getStatus() != CalloutHandle::NEXT_STEP_SKIP) {
            query->unpack();
        }
    } catch (const std::exception& ex) {
        LOG_DEBUG(lease_query_logger, DBGLVL_TRACE_BASIC,
                  DHCP6_LEASE_QUERY_PACKET_UNPACK_FAILED)
            .arg(query->getRemoteAddr().toText())
            .arg(query->getLocalAddr().toText())
            .arg(query->getIface())
            .arg(ex.what());
        // Increase the statistics of parse failures and dropped packets.
        StatsMgr::instance().addValue("pkt6-parse-failed",
                                      static_cast<int64_t>(1));
        StatsMgr::instance().addValue("pkt6-receive-drop",
                                      static_cast<int64_t>(1));
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return (0);
    }

    // Not a lease query, so return without handling it.
    // Make sure status is SKIP so it doesn't get unpacked again.
    if (query->getType() != DHCPV6_LEASEQUERY) {
        handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);
        return (0);
    }

    LOG_DEBUG(lease_query_logger, DBGLVL_TRACE_BASIC, DHCP6_LEASE_QUERY_RECEIVED)
              .arg(LeaseQueryImpl6::leaseQueryLabel(query));
    StatsMgr::instance().addValue("pkt6-lease-query-received", static_cast<int64_t>(1));

    try {
        LeaseQueryImplFactory::getImpl().processQuery(query);
    } catch (const std::exception& ex) {
        // Log that we failed to process the packet.
        LOG_DEBUG(lease_query_logger, DBGLVL_TRACE_BASIC,
                  DHCP6_LEASE_QUERY_PROCESS_FAILED)
                  .arg(LeaseQueryImpl6::leaseQueryLabel(query))
                  .arg(ex.what());
    }

    // We always set status to DROP as the query has been handled.
    handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
    return (0);
}

/// @brief This function is called when the library is loaded.
///
/// Reset lease-query related stats.
///
/// @return always 0.
int load(LibraryHandle& handle) {
    try {

        // Make the hook library not loadable by d2 or ca.
        uint16_t family = CfgMgr::instance().getFamily();
        const std::string& proc_name = Daemon::getProcName();
        if (family == AF_INET) {
            if (proc_name != "kea-dhcp4") {
                isc_throw(isc::Unexpected, "Bad process name: " << proc_name
                          << ", expected kea-dhcp4");
            }

            StatsMgr::instance().setValue("pkt4-lease-query-received",
                                          static_cast<int64_t>(0));
            StatsMgr::instance().setValue("pkt4-lease-query-response-unknown-sent",
                                          static_cast<int64_t>(0));
            StatsMgr::instance().setValue("pkt4-lease-query-response-unassigned-sent",
                                          static_cast<int64_t>(0));
            StatsMgr::instance().setValue("pkt4-lease-query-response-active-sent",
                                          static_cast<int64_t>(0));
            handle.registerCommandCallout("extended-info4-upgrade",
                                          extended_info4_upgrade);
        } else {
            if (proc_name != "kea-dhcp6") {
                isc_throw(isc::Unexpected, "Bad process name: " << proc_name
                          << ", expected kea-dhcp6");
            }

            StatsMgr::instance().setValue("pkt6-lease-query-received",
                                          static_cast<int64_t>(0));
            StatsMgr::instance().setValue("pkt6-lease-query-reply-sent",
                                          static_cast<int64_t>(0));
            handle.registerCommandCallout("extended-info6-upgrade",
                                          extended_info6_upgrade);
        }

        ConstElementPtr config = getConfig(handle);
        LeaseQueryImpl::terminated_ = false;
        LeaseQueryImplFactory::createImpl(family, config);
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_query_logger, LEASE_QUERY_LOAD_FAILED)
                  .arg(ex.what());
        LeaseQueryImpl::terminated_ = true;
        LeaseQueryImplFactory::destroyImpl();
        return (1);
    }

    LOG_INFO(lease_query_logger, LEASE_QUERY_LOAD_OK);
    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// Remove lease-query stats.
///
/// @return always 0.
int unload() {
    // Helps current running works to terminate.
    LeaseQueryImpl::terminated_ = true;

    IOServiceMgr::instance().unregisterIOService(LeaseQueryImplFactory::getMutableImpl().getIOService());

    // Stop and Destroy the BulkLeaseQueryService instance.
    BulkLeaseQueryService::reset();

    // Destroy the LeaseQueryImpl instance.
    LeaseQueryImplFactory::destroyImpl();

    // Remove lease-query stats.
    if (CfgMgr::instance().getFamily() == AF_INET) {
        StatsMgr::instance().del("pkt4-lease-query-received");
        StatsMgr::instance().del("pkt4-lease-query-response-unknown-sent");
        StatsMgr::instance().del("pkt4-lease-query-response-unassigned-sent");
        StatsMgr::instance().del("pkt4-lease-query-response-active-sent");
    } else {
        StatsMgr::instance().del("pkt6-lease-query-received");
        StatsMgr::instance().del("pkt6-lease-query-reply-sent");
    }

    LOG_INFO(lease_query_logger, LEASE_QUERY_UNLOAD_OK);
    return (0);
}

/// @brief dhcp4_srv_configured callout implementation.
///
/// Starts the listener.
///
/// @param handle callout handle.
/// @return 0 on success, non-zero otherwise.
int dhcp4_srv_configured(CalloutHandle& /* handle */) {
    IOServiceMgr::instance().registerIOService(LeaseQueryImplFactory::getMutableImpl().getIOService());
    LeaseQueryImplFactory::getMutableImpl().getIOService()->post(BulkLeaseQueryService::doStartListener);
    return (0);
}

/// @brief This callout is called at the "cb6_updated" hook.
///
/// If it detects that any subnets were altered by the update it
/// repopulates the prefix length list.
///
/// @param handle CalloutHandle.
///
/// @return 0 upon success, number of expressions that failed otherwise.
int cb6_updated(CalloutHandle& handle) {
    // Only repopulate the list if CB updated subnets.
    AuditEntryCollectionPtr audit_entries;
    handle.getArgument("audit_entries", audit_entries);

    auto const& object_type_idx = audit_entries->get<AuditEntryObjectTypeTag>();
    auto range = object_type_idx.equal_range("dhcp6_subnet");
    if (std::distance(range.first, range.second)) {
        try {
            const SrvConfigPtr& cfg = CfgMgr::instance().getCurrentCfg();
            const LeaseQueryImpl6& impl6 = dynamic_cast<const LeaseQueryImpl6&>
                                           (LeaseQueryImplFactory::getImpl());
            LeaseQueryImpl6& impl = const_cast<LeaseQueryImpl6&>(impl6);
            impl.populatePrefixLengthList(cfg);
        } catch (const std::exception& ex) {
            const string error("Error: populatePrefixLengthList() failed");
            handle.setArgument("error", ex.what());
            return (1);
        }
    }

    return (0);
}

/// @brief dhcp6_srv_configured callout implementation.
///
/// Starts the listener.
///
/// @param handle callout handle.
/// @return 0 on success, non-zero otherwise.
int dhcp6_srv_configured(CalloutHandle& handle) {
    try {
        SrvConfigPtr cfg;
        handle.getArgument("server_config", cfg);
        const LeaseQueryImpl6& impl6 = dynamic_cast<const LeaseQueryImpl6&>
                                       (LeaseQueryImplFactory::getImpl());
        LeaseQueryImpl6& impl = const_cast<LeaseQueryImpl6&>(impl6);
        impl.populatePrefixLengthList(cfg);
    } catch (const std::exception& ex) {
        handle.setStatus(isc::hooks::CalloutHandle::NEXT_STEP_DROP);
        const string error("Error: populatePrefixLengthList() failed");
        handle.setArgument("error", ex.what());
        return (1);
    }

    IOServiceMgr::instance().registerIOService(LeaseQueryImplFactory::getMutableImpl().getIOService());
    LeaseQueryImplFactory::getMutableImpl().getIOService()->post(BulkLeaseQueryService::doStartListener);
    return (0);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading.
int multi_threading_compatible() {
    return (1);
}

} // end extern "C"
