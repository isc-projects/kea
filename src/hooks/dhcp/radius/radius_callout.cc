// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Functions accessed by the hooks framework use C linkage to avoid the name
// mangling that accompanies use of the C++ compiler as well as to avoid
// issues related to namespaces.

#include <config.h>

#include <asiolink/io_service_mgr.h>
#include <cc/command_interpreter.h>
#include <cc/simple_parser.h>
#include <hooks/hooks.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet.h>
#include <radius.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host_mgr.h>
#include <process/daemon.h>
#include <stats/stats_mgr.h>
#include <radius_log.h>
#include <radius_parsers.h>
#include <radius_access.h>
#include <radius_accounting.h>
#include <util/multi_threading_mgr.h>

#include <string>
#include <sstream>
#include <vector>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::process;
using namespace isc::radius;
using namespace isc::stats;
using namespace isc::util;
using namespace std;

namespace {

/// @brief Brings parameters into a configuration.
///
/// @param handle the library handle
/// @return the config
ElementPtr getConfig(LibraryHandle& handle) {
    const vector<string> names = handle.getParameterNames();
    const set<string> keywords = RadiusConfigParser::RADIUS_KEYWORDS;
    ElementPtr config = Element::createMap();

    for (auto const& name : names) {
        if (keywords.count(name) == 0) {
            isc_throw(BadValue, "unknown parameter: " << name);
        }
        ConstElementPtr value = handle.getParameter(name);
        if (value) {
            config->set(name, value);
        }
    }
    return (config);
}

/// @brief  Body of subnet4_select.
///
/// @param handle callout handle passed to the callout.
/// @param subnet the subnet.
/// @param query the query.
/// @return the RADIUS auth handler.
RadiusAuthHandlerPtr subnet4Select(CalloutHandle& handle,
                                   ConstSubnet4Ptr subnet, Pkt4Ptr query) {
    RadiusImpl& impl = RadiusImpl::instance();
    MultiThreadingLock lock(impl.auth_->requests4_.mutex_);

    RadiusAuthHandlerPtr handler;
    uint32_t subnet_id = subnet->getID();
    uint32_t host_subnet_id =
        (subnet->getReservationsGlobal() ? SUBNET_ID_GLOBAL : subnet_id);
    vector<uint8_t> id;
    string text;
    if (!impl.auth_->getIdentifier(*query, id, text)) {
        // What to do?
        handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);
        return (handler);
    }

    // Ask host cache.
    ConstHostPtr host = HostMgr::instance().get4Any(host_subnet_id,
                                                    impl.id_type4_,
                                                    &id[0], id.size());
    // Check cached subnet reselect.
    if (host && host->getContext() &&
        (host->getContext()->getType() == Element::map) &&
        host->getContext()->contains("subnet-id")) {
        try {
            ConstElementPtr reselected = host->getContext()->get("subnet-id");
            subnet_id = static_cast<uint32_t>(reselected->intValue());
            LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                      RADIUS_ACCESS_SUBNET_RESELECT)
                .arg(subnet->getID())
                .arg(subnet_id);
            // Reselect to null.
            if (subnet_id == SUBNET_ID_UNUSED) {
                ConstSubnet4Ptr null_subnet;
                handle.setArgument("subnet4", null_subnet);
                return (handler);
            }
            // Reselect to an other subnet.
            uint32_t new_host_subnet_id = host_subnet_id;
            if (subnet_id != subnet->getID()) {
                ConstSubnet4Ptr new_subnet =
                    CfgMgr::instance().getCurrentCfg()->
                    getCfgSubnets4()->getSubnet(subnet_id);
                if (!new_subnet) {
                    isc_throw(BadValue,
                              "can't find subnet with id: " << subnet_id);
                }
                new_host_subnet_id =
                    (new_subnet->getReservationsGlobal() ?
                     SUBNET_ID_GLOBAL : subnet_id);
                handle.setArgument("subnet4", new_subnet);
            }
            // Get again host cache.
            if (new_host_subnet_id != host_subnet_id) {
                host = HostMgr::instance().get4Any(new_host_subnet_id,
                                                   impl.id_type4_,
                                                   &id[0], id.size());
            }
        } catch (const std::exception&) {
            // Delete bad entry from cache.
            HostPtr bad(new Host(*host));
            static_cast<void>(impl.cache_->remove(bad));
            handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);
            return (handler);
        }
    }

    // Check cached RADIUS response.
    if (host && host->getContext() &&
        (host->getContext()->getType() == Element::map)) {
        // Yeah! We don't need to ask the Radius server.
        Attributes attrs =
            Attributes::fromElement(host->getContext()->get("radius"));
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_ACCESS_CACHE_GET)
            .arg(host->toText())
            .arg(attrs.toText());
        // 3 cases:
        //  - ip address (is in the host).
        //  - framed pool (put in the query).
        //  - class (todo).
        if (!host->getIPv4Reservation().isV4Zero()) {
            // Done!
            return (handler);
        }
        ConstAttributePtr framed_pool = attrs.get(PW_FRAMED_POOL);
        if (framed_pool && (framed_pool->getValueType() == PW_TYPE_STRING)) {
            query->addClass(framed_pool->toString());
            // Done!
            return (handler);
        }
        // todo: class.
        ConstAttributePtr class_ = attrs.get(PW_CLASS);
        if (class_ && (class_->getValueType() == PW_TYPE_STRING)) {
            // todo
            return (handler);
        }
        return (handler);
    }

    // Get the pending request.
    RadiusAuthPendingRequestPtr<Pkt4Ptr> pending_request =
        impl.auth_->requests4_.get(id);

    // Conflict?
    if (pending_request) {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_ACCESS_CONFLICT)
          .arg(query->getLabel())
          .arg(text);
        StatsMgr::instance().addValue("pkt4-duplicate",
                                      static_cast<int64_t>(1));
        StatsMgr::instance().addValue("pkt4-receive-drop",
                                      static_cast<int64_t>(1));
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return (handler);
    }

    // Too many pending requests.
    size_t max_requests = impl.auth_->max_pending_requests_;
    if ((max_requests > 0) && (impl.auth_->requests4_.size() >= max_requests)) {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_ACCESS_MAX_PENDING_REQUESTS)
            .arg(query->getLabel())
            .arg(text);
        StatsMgr::instance().addValue("pkt4-queue-full",
                                      static_cast<int64_t>(1));
        StatsMgr::instance().addValue("pkt4-receive-drop",
                                      static_cast<int64_t>(1));
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return (handler);
    }

    // Ask the Radius server.
    handler = impl.auth_->buildAuth(*query, subnet_id, id, text);
    if (!handler) {
        // Error was logged.
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return (handler);
    }

    // Create a new pending access request.
    impl.auth_->requests4_.set(id, query);

    return (handler);
}

/// @brief Body of subnet6_select.
///
/// @param handle callout handle passed to the callout.
/// @param subnet the subnet.
/// @param query the query.
/// @return the RADIUS auth handler.
RadiusAuthHandlerPtr subnet6Select(CalloutHandle& handle,
                                   ConstSubnet6Ptr subnet, Pkt6Ptr query) {
    RadiusImpl& impl = RadiusImpl::instance();
    MultiThreadingLock lock(impl.auth_->requests6_.mutex_);

    RadiusAuthHandlerPtr handler;
    uint32_t subnet_id = subnet->getID();
    uint32_t host_subnet_id =
        (subnet->getReservationsGlobal() ? SUBNET_ID_GLOBAL : subnet_id);
    vector<uint8_t> id;
    string text;
    if (!impl.auth_->getIdentifier(*query, id, text)) {
        // What to do?
        handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);
        return (handler);
    }

    // Ask host cache.
    ConstHostPtr host = HostMgr::instance().get6Any(host_subnet_id,
                                                    impl.id_type6_,
                                                    &id[0], id.size());
    // Check cached subnet reselect.
    if (host && host->getContext() &&
        (host->getContext()->getType() == Element::map) &&
        host->getContext()->contains("subnet-id")) {
        try {
            ConstElementPtr reselected = host->getContext()->get("subnet-id");
            subnet_id = static_cast<uint32_t>(reselected->intValue());
            LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                      RADIUS_ACCESS_SUBNET_RESELECT)
                .arg(subnet->getID())
                .arg(subnet_id);
            // Reselect to null.
            if (subnet_id == SUBNET_ID_UNUSED) {
                ConstSubnet6Ptr null_subnet;
                handle.setArgument("subnet6", null_subnet);
                return (handler);
            }
            // Reselect to an other subnet.
            uint32_t new_host_subnet_id = host_subnet_id;
            if (subnet_id != subnet->getID()) {
                ConstSubnet6Ptr new_subnet =
                    CfgMgr::instance().getCurrentCfg()->
                    getCfgSubnets6()->getSubnet(subnet_id);
                if (!new_subnet) {
                    isc_throw(BadValue,
                              "can't find subnet with id: " << subnet_id);
                }
                new_host_subnet_id =
                    (new_subnet->getReservationsGlobal() ?
                     SUBNET_ID_GLOBAL : subnet_id);
                handle.setArgument("subnet6", new_subnet);
            }
            // Get again host cache.
            if (new_host_subnet_id != host_subnet_id) {
                host = HostMgr::instance().get6Any(new_host_subnet_id,
                                                   impl.id_type6_,
                                                   &id[0], id.size());
            }
        } catch (const std::exception&) {
            // Delete bad entry from cache.
            HostPtr bad(new Host(*host));
            static_cast<void>(impl.cache_->remove(bad));
            handle.setStatus(CalloutHandle::NEXT_STEP_SKIP);
            return (handler);
        }
    }

    // Check cached RADIUS response.
    if (host && host->getContext() &&
        (host->getContext()->getType() == Element::map)) {
        // Yeah! We don't need to ask the Radius server.
        Attributes attrs =
            Attributes::fromElement(host->getContext()->get("radius"));
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_ACCESS_CACHE_GET)
            .arg(host->toText())
            .arg(attrs.toText());
        // 4 cases:
        //  - ip address (is in the host).
        //  - delegated prefix (is in the host).
        //  - framed pool (put in the query).
        //  - class (todo).
        if (host->hasIPv6Reservation()) {
            // Done!
            return (handler);
        }
        ConstAttributePtr framed_pool = attrs.get(PW_FRAMED_POOL);
        if (framed_pool && (framed_pool->getValueType() == PW_TYPE_STRING)) {
            query->addClass(framed_pool->toString());
            // Done!
            return (handler);
        }
        // todo: class.
        ConstAttributePtr class_ = attrs.get(PW_CLASS);
        if (class_ && (class_->getValueType() == PW_TYPE_STRING)) {
            // todo
            return (handler);
        }
        return (handler);
    }

    // Get the pending request.
    RadiusAuthPendingRequestPtr<Pkt6Ptr> pending_request =
        impl.auth_->requests6_.get(id);

    // Conflict?
    if (pending_request) {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_ACCESS_CONFLICT)
          .arg(query->getLabel())
          .arg(text);
        StatsMgr::instance().addValue("pkt6-duplicate",
                                      static_cast<int64_t>(1));
        StatsMgr::instance().addValue("pkt6-receive-drop",
                                      static_cast<int64_t>(1));
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return (handler);
    }

    // Too many pending requests.
    size_t max_requests = impl.auth_->max_pending_requests_;
    if ((max_requests > 0) && (impl.auth_->requests6_.size() >= max_requests)) {
        LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                  RADIUS_ACCESS_MAX_PENDING_REQUESTS)
            .arg(query->getLabel())
            .arg(text);
        StatsMgr::instance().addValue("pkt6-queue-full",
                                      static_cast<int64_t>(1));
        StatsMgr::instance().addValue("pkt6-receive-drop",
                                      static_cast<int64_t>(1));
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return (handler);
    }

    // Ask the Radius server.
    handler = impl.auth_->buildAuth(*query, subnet_id, id, text);
    if (!handler) {
        // Error was logged.
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
        return (handler);
    }

    // Create a new pending access request.
    impl.auth_->requests6_.set(id, query);

    return (handler);
}

} // end of anonymous namespace

extern "C" {

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle
/// @return 0 when initialization is successful, 1 otherwise
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
        } else {
            if (proc_name != "kea-dhcp6") {
                isc_throw(isc::Unexpected, "Bad process name: " << proc_name
                          << ", expected kea-dhcp6");
            }
        }

        // Get and decode configuration.
        ElementPtr config = getConfig(handle);
        RadiusImpl& impl = RadiusImpl::instance();
        impl.init(config);
    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_CONFIGURATION_FAILED)
            .arg(ex.what());
        return (CONTROL_RESULT_ERROR);
    }

    LOG_INFO(radius_logger, RADIUS_INIT_OK);
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This function is called when the library is unloaded.
///
/// @return 0 if deregistration was successful, 1 otherwise
int unload() {
    IOServiceMgr::instance().unregisterIOService(RadiusImpl::instance().getIOService());
    RadiusImpl::instance().reset();
    LOG_INFO(radius_logger, RADIUS_DEINIT_OK);
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This function is called to retrieve the multi-threading compatibility.
///
/// @return 1 which means compatible with multi-threading,
int multi_threading_compatible() {
    return (1);
}

/// @brief This function is called by the DHCPv4 server when it is configured.
///
/// The only purpose of this callout is to retrieve io_service_ reference.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int dhcp4_srv_configured(CalloutHandle& /* handle */) {
    RadiusImpl::instance().startServices();
    IOServiceMgr::instance().registerIOService(RadiusImpl::instance().getIOService());
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This function is called by the DHCPv6 server when it is configured.
///
/// The only purpose of this callout is to retrieve io_service_ reference.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int dhcp6_srv_configured(CalloutHandle& /* handle */) {
    RadiusImpl::instance().startServices();
    IOServiceMgr::instance().registerIOService(RadiusImpl::instance().getIOService());
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This callout tries to retrieve host information from cache.
///
/// This function is called by the DHCPv4 server when a subnet
/// is being selected. It uses input packet to extract identifier
/// and then looks for host entry in the host cache.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int subnet4_select(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    InHook in_hook;
    RadiusImpl& impl = RadiusImpl::instance();
    if (!impl.auth_ || !impl.checkHostBackends()) {
        return (CONTROL_RESULT_SUCCESS);
    }
    Pkt4Ptr query;
    handle.getArgument("query4", query);
    ConstSubnet4Ptr subnet;
    handle.getArgument("subnet4", subnet);
    if (!query || !subnet || (subnet->getID() == 0)) {
        return (CONTROL_RESULT_SUCCESS);
    }
    ParkingLotHandlePtr parking_lot = handle.getParkingLotHandlePtr();
    parking_lot->reference(query);
    try {
        RadiusAuthHandlerPtr handler = subnet4Select(handle, subnet, query);
        if (!handler) {
            parking_lot->dereference(query);
            return (CONTROL_RESULT_SUCCESS);
        }
        handler->start();
        handle.setStatus(CalloutHandle::NEXT_STEP_PARK);
    } catch (...) {
        parking_lot->dereference(query);
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This callout tries to retrieve host information from cache.
///
/// This function is called by the DHCPv4 server when a subnet
/// is being selected. It uses input packet to extract identifier
/// and then looks for host entry in the host cache.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int subnet6_select(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (CONTROL_RESULT_SUCCESS);
    }

    InHook in_hook;
    RadiusImpl& impl = RadiusImpl::instance();
    if (!impl.auth_ || !impl.checkHostBackends()) {
        return (CONTROL_RESULT_SUCCESS);
    }
    Pkt6Ptr query;
    handle.getArgument("query6", query);
    ConstSubnet6Ptr subnet;
    handle.getArgument("subnet6", subnet);
    if (!query || !subnet || (subnet->getID() == 0)) {
        return (CONTROL_RESULT_SUCCESS);
    }
    ParkingLotHandlePtr parking_lot = handle.getParkingLotHandlePtr();
    parking_lot->reference(query);
    try {
        RadiusAuthHandlerPtr handler = subnet6Select(handle, subnet, query);
        if (!handler) {
            parking_lot->dereference(query);
            return (CONTROL_RESULT_SUCCESS);
        }
        handler->start();
        handle.setStatus(CalloutHandle::NEXT_STEP_PARK);
    } catch (...) {
        parking_lot->dereference(query);
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);
    }

    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This callout is called at the "lease4_select" hook.
///
/// It does transmit Accounting-Request with Acct-Status-Type
/// set to Start if a lease has been assigned.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int lease4_select(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    InHook in_hook;
    RadiusImpl& impl = RadiusImpl::instance();
    if (!impl.acct_ || !impl.getIOContext()) {
        return (CONTROL_RESULT_SUCCESS);
    }

    bool fake_allocation = false;
    handle.getArgument("fake_allocation", fake_allocation);
    if (fake_allocation) {
        // If this is a discover, there's nothing to do
        return (CONTROL_RESULT_SUCCESS);
    }

    Lease4Ptr lease;
    handle.getArgument("lease4", lease);
    try {
        // Start the Accounting-Request transmission.
        RadiusAcctHandlerPtr handler = impl.acct_->buildAcct(lease, EVENT_CREATE);
        impl.getIOContext()->post(std::bind(&RadiusAccounting::runAsync, handler));
    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_HOOK_FAILED)
            .arg("lease4_select")
            .arg(ex.what());
    }
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This callout is called at the "lease4_renew" hook.
///
/// It does transmit Accounting-Request with Acct-Status-Type
/// set to Interim-Update.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int lease4_renew(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    InHook in_hook;
    RadiusImpl& impl = RadiusImpl::instance();
    if (!impl.acct_ || !impl.getIOContext()) {
        return (CONTROL_RESULT_SUCCESS);
    }
    Lease4Ptr lease;
    handle.getArgument("lease4", lease);
    try {
        // Start the Accounting-Request transmission.
        RadiusAcctHandlerPtr handler = impl.acct_->buildAcct(lease, EVENT_RENEW);
        impl.getIOContext()->post(std::bind(&RadiusAccounting::runAsync, handler));
    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_HOOK_FAILED)
            .arg("lease4_renew")
            .arg(ex.what());
    }
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This callout is called at the "lease4_release" hook.
///
/// It does transmit Accounting-Request with Acct-Status-Type
/// set to Stop.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int lease4_release(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    InHook in_hook;
    RadiusImpl& impl = RadiusImpl::instance();
    if (!impl.acct_ || !impl.getIOContext()) {
        return (CONTROL_RESULT_SUCCESS);
    }
    Lease4Ptr lease;
    handle.getArgument("lease4", lease);
    try {
        // Start the Accounting-Request transmission.
        RadiusAcctHandlerPtr handler = impl.acct_->buildAcct(lease, EVENT_RELEASE);
        impl.getIOContext()->post(std::bind(&RadiusAccounting::runAsync, handler));
    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_HOOK_FAILED)
            .arg("lease4_release")
            .arg(ex.what());
    }
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This callout is called at the "lease4_decline" hook.
///
/// It does transmit Accounting-Request with Acct-Status-Type
/// set to Stop.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int lease4_decline(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    InHook in_hook;
    RadiusImpl& impl = RadiusImpl::instance();
    if (!impl.acct_ || !impl.getIOContext()) {
        return (CONTROL_RESULT_SUCCESS);
    }
    Lease4Ptr lease;
    handle.getArgument("lease4", lease);
    try {
        // Start the Accounting-Request transmission.
        RadiusAcctHandlerPtr handler = impl.acct_->buildAcct(lease, EVENT_DECLINE);
        impl.getIOContext()->post(std::bind(&RadiusAccounting::runAsync, handler));
    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_HOOK_FAILED)
            .arg("lease4_decline")
            .arg(ex.what());
    }
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This callout is called at the "lease4_expire" hook.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int lease4_expire(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    InHook in_hook;
    RadiusImpl& impl = RadiusImpl::instance();
    if (!impl.acct_ || !impl.getIOContext()) {
        return (CONTROL_RESULT_SUCCESS);
    }
    Lease4Ptr lease;
    handle.getArgument("lease4", lease);
    try {
        RadiusAcctHandlerPtr handler = impl.acct_->buildAcct(lease, EVENT_EXPIRE);
        impl.getIOContext()->post(std::bind(&RadiusAccounting::runAsync, handler));
    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_HOOK_FAILED)
            .arg("lease4_expire")
            .arg(ex.what());
    }
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This callout is called at the "lease6_select" hook.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int lease6_select(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    InHook in_hook;
    RadiusImpl& impl = RadiusImpl::instance();
    if (!impl.acct_ || !impl.getIOContext()) {
        return (CONTROL_RESULT_SUCCESS);
    }
    bool fake_allocation;
    handle.getArgument("fake_allocation", fake_allocation);
    if (fake_allocation) {
        return (CONTROL_RESULT_SUCCESS);
    }
    Lease6Ptr lease;
    handle.getArgument("lease6", lease);
    try {
        RadiusAcctHandlerPtr handler = impl.acct_->buildAcct(lease, EVENT_CREATE);
        impl.getIOContext()->post(std::bind(&RadiusAccounting::runAsync, handler));
    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_HOOK_FAILED)
            .arg("lease6_select")
            .arg(ex.what());
    }
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This callout is called at the "lease6_renew" hook.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int lease6_renew(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    InHook in_hook;
    RadiusImpl& impl = RadiusImpl::instance();
    if (!impl.acct_ || !impl.getIOContext()) {
        return (CONTROL_RESULT_SUCCESS);
    }
    Lease6Ptr lease;
    handle.getArgument("lease6", lease);
    try {
        RadiusAcctHandlerPtr handler = impl.acct_->buildAcct(lease, EVENT_RENEW);
        impl.getIOContext()->post(std::bind(&RadiusAccounting::runAsync, handler));
    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_HOOK_FAILED)
            .arg("lease6_renew")
            .arg(ex.what());
    }
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This callout is called at the "lease6_rebind" hook.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int lease6_rebind(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    InHook in_hook;
    RadiusImpl& impl = RadiusImpl::instance();
    if (!impl.acct_ || !impl.getIOContext()) {
        return (CONTROL_RESULT_SUCCESS);
    }
    Lease6Ptr lease;
    handle.getArgument("lease6", lease);
    try {
        RadiusAcctHandlerPtr handler = impl.acct_->buildAcct(lease, EVENT_REBIND);
        impl.getIOContext()->post(std::bind(&RadiusAccounting::runAsync, handler));
    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_HOOK_FAILED)
            .arg("lease6_rebind")
            .arg(ex.what());
    }
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This callout is called at the "lease6_release" hook.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int lease6_release(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    InHook in_hook;
    RadiusImpl& impl = RadiusImpl::instance();
    if (!impl.acct_ || !impl.getIOContext()) {
        return (CONTROL_RESULT_SUCCESS);
    }
    Lease6Ptr lease;
    handle.getArgument("lease6", lease);
    try {
        RadiusAcctHandlerPtr handler = impl.acct_->buildAcct(lease, EVENT_RELEASE);
        impl.getIOContext()->post(std::bind(&RadiusAccounting::runAsync, handler));
    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_HOOK_FAILED)
            .arg("lease6_release")
            .arg(ex.what());
    }
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This callout is called at the "lease6_decline" hook.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int lease6_decline(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    InHook in_hook;
    RadiusImpl& impl = RadiusImpl::instance();
    if (!impl.acct_ || !impl.getIOContext()) {
        return (CONTROL_RESULT_SUCCESS);
    }
    Lease6Ptr lease;
    handle.getArgument("lease6", lease);
    try {
        RadiusAcctHandlerPtr handler = impl.acct_->buildAcct(lease, EVENT_DECLINE);
        impl.getIOContext()->post(std::bind(&RadiusAccounting::runAsync, handler));
    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_HOOK_FAILED)
            .arg("lease6_decline")
            .arg(ex.what());
    }
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This callout is called at the "lease6_expire" hook.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int lease6_expire(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP ||
        status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    InHook in_hook;
    RadiusImpl& impl = RadiusImpl::instance();
    if (!impl.acct_ || !impl.getIOContext()) {
        return (CONTROL_RESULT_SUCCESS);
    }
    Lease6Ptr lease;
    handle.getArgument("lease6", lease);
    try {
        RadiusAcctHandlerPtr handler = impl.acct_->buildAcct(lease, EVENT_EXPIRE);
        impl.getIOContext()->post(std::bind(&RadiusAccounting::runAsync, handler));
    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_HOOK_FAILED)
            .arg("lease6_expire")
            .arg(ex.what());
    }
    return (CONTROL_RESULT_SUCCESS);
}

/// @brief This callout is called at the "command_processed" hook point.
///
/// If any lease{4,6}-add/update/del command is issued, this code sends
/// appropriate Radius packets to the accounting server.
///
/// @param handle callout handle passed to the callout.
/// @return 0 on success, 1 otherwise.
int command_processed(CalloutHandle& handle) {
    InHook in_hook;
    RadiusImpl& impl = RadiusImpl::instance();
    if (!impl.acct_ || !impl.getIOContext()) {
        return (CONTROL_RESULT_SUCCESS);
    }
    string name;
    ConstElementPtr arguments;
    ConstElementPtr response;
    try {
        handle.getArgument("name", name);
        handle.getArgument("arguments", arguments);
        handle.getArgument("response", response);
        if (!arguments || !response) {
            // "arguments" and "response" are required for all further actions.
            // Stop here if they are not set.
            return (CONTROL_RESULT_SUCCESS);
        }

        int result = SimpleParser::getInteger(response, "result");
        if (result != 0) {
            // Command has failed.
            return (CONTROL_RESULT_SUCCESS);
        }

        // Handle peer updates?
        const ConstElementPtr origin(arguments->get("origin"));
        if (origin) {
            // "origin" has a dynamic type. There are commands like ha-sync-complete-notify that set
            // it to an integer. For simplicity, treat those cases like it is not coming from an HA
            // partner for now and it will get filtered out by name further down below. We only care
            // about lease updates.
            const bool is_from_ha_partner(origin->getType() == Element::string &&
                                          origin->stringValue() == "ha-partner");
            if (!impl.acct_->peer_updates_ && is_from_ha_partner) {
                return (CONTROL_RESULT_SUCCESS);
            }
        }

        RadiusAcctHandlerPtr handler;
        if (name == "lease4-add") {
            handler = impl.acct_->buildAcct4(arguments, EVENT_ADD);
        } else if (name == "lease4-update") {
            handler = impl.acct_->buildAcct4(arguments, EVENT_UPDATE);
        } else if (name== "lease4-del") {
            handler = impl.acct_->buildAcct4(arguments, EVENT_DEL);
        } else if (name == "lease6-add") {
            handler = impl.acct_->buildAcct6(arguments, EVENT_ADD);
        } else if (name == "lease6-update") {
            handler = impl.acct_->buildAcct6(arguments, EVENT_UPDATE);
        } else if (name== "lease6-del") {
            handler = impl.acct_->buildAcct6(arguments, EVENT_DEL);
        }
        if (handler) {
            impl.getIOContext()->post(std::bind(&RadiusAccounting::runAsync,
                                                handler));
        }
    } catch (const std::exception& ex) {
        ostringstream ss;
        ss << "command_processed: " << name;
        LOG_ERROR(radius_logger, RADIUS_HOOK_FAILED)
            .arg(ss.str())
            .arg(ex.what());
    }
    return (CONTROL_RESULT_SUCCESS);
}

} // end extern "C"
