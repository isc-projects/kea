// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_multi_threading.h>
#include <util/multi_threading_mgr.h>
#include <blq_service.h>
#include <tcp/tcp_listener.h>
#include <lease_query_log.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::tcp;
using namespace isc::util;
using namespace boost::asio;

namespace isc {
namespace lease_query {

const SimpleKeywords
BulkLeaseQueryService::AdvancedConfig::CONFIG_KEYWORDS =
{
    { "bulk-query-enabled",           Element::boolean },
    { "active-query-enabled",         Element::boolean },
    { "extended-info-tables-enabled", Element::boolean },
    { "lease-query-ip",               Element::string },
    { "lease-query-tcp-port",         Element::integer },
    { "max-bulk-query-threads",       Element::integer },
    { "max-requester-connections",    Element::integer },
    { "max-concurrent-queries",       Element::integer },
    { "max-requester-idle-time",      Element::integer },
    { "max-leases-per-fetch",         Element::integer },
    { "trust-anchor",                 Element::string },
    { "cert-file",                    Element::string },
    { "key-file",                     Element::string },
    { "cert-required",                Element::boolean },
    { "comment",                      Element::string }
};

void
BulkLeaseQueryService::AdvancedConfig::parse(ConstElementPtr advanced) {
    if (!advanced) {
        return;
    }

    // Note checkKeywords() will throw DhcpConfigError if there is a problem.
    SimpleParser::checkKeywords(CONFIG_KEYWORDS, advanced);

    ConstElementPtr value = advanced->get("bulk-query-enabled");
    if (value) {
        bulk_query_enabled_ = value->boolValue();
    }

    value = advanced->get("active-query-enabled");
    if (value) {
        active_query_enabled_ = value->boolValue();
    }
    if (active_query_enabled_) {
        isc_throw(BadValue, "Active query is not supported");
    }

    value = advanced->get("extended-info-tables-enabled");
    if (value) {
        extended_info_tables_enabled_ = value->boolValue();
    } else {
        extended_info_tables_enabled_ = bulk_query_enabled_;
    }

    value = advanced->get("lease-query-ip");
    if (value) {
        std::string addr = value->stringValue();
        try {
            lease_query_ip_ = IOAddress(addr);
        } catch (const std::exception& ex) {
            isc_throw(BadValue, "invalid lease-query-ip '"
                      << addr << "': " << ex.what());
        }
        if (lease_query_ip_.getFamily() != family_) {
            isc_throw(BadValue, "lease-query-ip not a "
                      << (family_ == AF_INET ? "IPv4" : "IPv6")
                      << " address");
        }
    }

    value = advanced->get("lease-query-tcp-port");
    if (value) {
        int64_t port = value->intValue();
        if ((port <= 0) || (port > std::numeric_limits<uint16_t>::max())) {
            isc_throw(BadValue, "invalid lease-query-tcp-port '"
                      << port << "'");
        }
        lease_query_tcp_port_ = static_cast<uint16_t>(port);
    }

    value = advanced->get("max-bulk-query-threads");
    if (value) {
        int64_t val = value->intValue();
        if (val < 0) {
            isc_throw(BadValue, "invalid max-bulk-query-threads '"
                      << val << "'");
        }
        max_bulk_query_threads_ = static_cast<size_t>(val);
    }

    value = advanced->get("max-requester-connections");
    if (value) {
        int64_t val = value->intValue();
        if (val <= 0) {
            isc_throw(BadValue, "invalid max-requester-connections '"
                      << val << "'");
        }
        max_requester_connections_ = static_cast<size_t>(val);
    }

    value = advanced->get("max-concurrent-queries");
    if (value) {
        int64_t val = value->intValue();
        if (val < 0) {
            isc_throw(BadValue, "invalid max-concurrent-queries '"
                      << val << "'");
        }
        max_concurrent_queries_ = static_cast<size_t>(val);
    }

    value = advanced->get("max-requester-idle-time");
    if (value) {
        int64_t val = value->intValue();
        if ((val <= 0) || (val * 1000 > std::numeric_limits<int32_t>::max())) {
            isc_throw(BadValue, "invalid max-requester-idle-time '"
                      << val << "'");
        }
        max_requester_idle_time_ = static_cast<long>(val);
    }

    value = advanced->get("max-leases-per-fetch");
    // Derive the command page size from this value almost in an
    // arbitrary way as the paging in command is only to not overflow
    // the used memory for handling fetch results...
    if (value) {
        int64_t val = value->intValue();
        if (val <= 0) {
            isc_throw(BadValue, "invalid max-leases-per-fetch '"
                      << val << "'");
        }
        max_leases_per_fetch_ = static_cast<size_t>(val);
        if (max_leases_per_fetch_ >= 10) {
            if (max_leases_per_fetch_ <= 100) {
                LeaseQueryImpl::PageSize = 10 * max_leases_per_fetch_;
            } else {
                LeaseQueryImpl::PageSize = 2 * max_leases_per_fetch_;
            }
        }
    }
}

BulkLeaseQueryService::BulkLeaseQueryService(LeaseQueryImpl* impl,
                                             const AdvancedConfig& config)
    : impl_(impl), config_(config) {

    if (getBulkQueryEnabled()) {
        // Verify Kea core is multi-threaded and determine number of threads
        // DHCP service uses.
        auto mcfg = CfgMgr::instance().getStagingCfg()->getDHCPMultiThreading();
        bool dhcp_mt_enabled = false;
        uint32_t dhcp_threads = 0;
        uint32_t dummy_queue_size = 0;
        CfgMultiThreading::extract(mcfg, dhcp_mt_enabled, dhcp_threads,
                                   dummy_queue_size);
        if (!dhcp_mt_enabled) {
            isc_throw(BadValue, "BulkLeaseQuery requires Kea multi-threading to be enabled");
        }

        // When DHCP threads is configured as zero, we should auto-detect.
        if (!dhcp_threads) {
            dhcp_threads = MultiThreadingMgr::detectThreadCount();
            // If machine says it cannot support threads.
            if (!dhcp_threads) {
                isc_throw(BadValue, "BulkLeaseQuery requires multi-threaded capable system");
            }
        }

        size_t thread_pool_size = getMaxBulkQueryThreads();
        if (!thread_pool_size) {
            // If max_bulk_query_threads is 0, then we use the same number
            // of threads as DHCP.
            thread_pool_size = dhcp_threads;
        }

        // Instantiate the listener.
        mt_listener_mgr_.reset(new MtLeaseQueryListenerMgr(getLeaseQueryIp(),
                                                           getLeaseQueryTcpPort(),
                                                           getFamily(),
                                                           // TcpListner idle timeout is milliseconds.
                                                           TcpListener::IdleTimeout(getMaxRequesterIdleTime() * 1000),
                                                           thread_pool_size,
                                                           asiolink::TlsContextPtr(),
                                                           BulkLeaseQueryService::acceptFilter,
                                                           getMaxConcurrentQueries()));
    }
}

BulkLeaseQueryService::~BulkLeaseQueryService() {
    stopListener();
}

BulkLeaseQueryServicePtr&
BulkLeaseQueryService::getBulkLeaseQueryServicePtr() {
    static BulkLeaseQueryServicePtr mgr_ptr;
    return (mgr_ptr);
}

void
BulkLeaseQueryService::reset() {
    getBulkLeaseQueryServicePtr().reset();
}

BulkLeaseQueryServicePtr
BulkLeaseQueryService::instance() {
    return (getBulkLeaseQueryServicePtr());
}

void
BulkLeaseQueryService::create(LeaseQueryImpl* impl, ConstElementPtr advanced) {
    if (!impl) {
        isc_throw(BadValue, "BulkLeaseQueryService::create: no lease query implementation");
    }
    BulkLeaseQueryServicePtr& mgr = getBulkLeaseQueryServicePtr();
    if (!advanced && mgr) {
        mgr.reset();
        return;
    }

    AdvancedConfig config(impl->getFamily());
    config.parse(advanced);
    mgr.reset(new BulkLeaseQueryService(impl, config));
}

void
BulkLeaseQueryService::setMaxRequesterConnections(size_t max_requester_connections) {
    if (!max_requester_connections) {
        isc_throw(BadValue, "new max requester connections is 0");
    }
    config_.max_requester_connections_ = max_requester_connections;
}

void
BulkLeaseQueryService::setMaxLeasePerFetch(size_t max_leases_per_fetch) {
    if (!max_leases_per_fetch) {
        isc_throw(BadValue, "new max leases per fetch is 0");
    }
    config_.max_leases_per_fetch_ = max_leases_per_fetch;
}

void
BulkLeaseQueryService::startListener() {
    if (mt_listener_mgr_) {
        // Add critical section callbacks.
        MultiThreadingMgr::instance().addCriticalSectionCallbacks("BLQ",
            std::bind(&BulkLeaseQueryService::checkListenerPausePermission, this),
            std::bind(&BulkLeaseQueryService::pauseListener, this),
            std::bind(&BulkLeaseQueryService::resumeListener, this));

        mt_listener_mgr_->start();
    }
}

void
BulkLeaseQueryService::checkListenerPausePermission() {
    // Since this function is used as CS callback all exceptions must be
    // suppressed (except the @ref MultiThreadingInvalidOperation), unlikely
    // though they may be.
    // The @ref MultiThreadingInvalidOperation is propagated to the scope
    // of the @ref MultiThreadingCriticalSection constructor.
    try {
        if (!mt_listener_mgr_) {
            // Shouldn't happen.
            isc_throw(Unexpected, "checkListenerPausePermission::mt_listener_mgr_ does not exist");
        }

        mt_listener_mgr_->checkPermissions();
    } catch (const isc::MultiThreadingInvalidOperation& ex) {
        LOG_ERROR(lease_query_logger, BULK_LEASE_QUERY_PAUSE_LISTENER_ILLEGAL)
            .arg(ex.what());
        // The exception needs to be propagated to the caller of the
        // @ref MultiThreadingCriticalSection constructor.
        throw;
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_query_logger,
                  BULK_LEASE_QUERY_PAUSE_CHECK_PERMISSIONS_FAILED)
            .arg(ex.what());
    }
}

void
BulkLeaseQueryService::pauseListener() {
    // Since this function is used as CS callback all exceptions must be
    // suppressed, unlikely though they may be.
    try {
        if (!mt_listener_mgr_) {
            // Shouldn't happen.
            isc_throw(Unexpected, "pauseListener::mt_listener_mgr_ does not exist");
        }

        mt_listener_mgr_->pause();
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_query_logger, BULK_LEASE_QUERY_PAUSE_LISTENER_FAILED)
            .arg(ex.what());
    }
}

void
BulkLeaseQueryService::resumeListener() {
    // Since this function is used as CS callback all exceptions must be
    // suppressed, unlikely though they may be.
    try {
        if (!mt_listener_mgr_) {
            // Shouldn't happen.
            isc_throw(Unexpected, "resumeListener::mt_listener_mgr_ does not exist");
        }

        mt_listener_mgr_->resume();
    } catch (std::exception& ex) {
        LOG_ERROR(lease_query_logger, BULK_LEASE_QUERY_RESUME_LISTENER_FAILED)
            .arg(ex.what());
    }
}

void
BulkLeaseQueryService::stopListener() {
    if (mt_listener_mgr_) {
        // Remove critical section callbacks.
        MultiThreadingMgr::instance().removeCriticalSectionCallbacks("BLQ");
        mt_listener_mgr_->stop();
    }
}

bool
BulkLeaseQueryService::acceptFilter(const ip::tcp::endpoint& endpoint) {
    if (LeaseQueryImpl::terminated_) {
        // Terminated!
        return (false);
    }

    BulkLeaseQueryServicePtr blq_srv = BulkLeaseQueryService::instance();
    if (!blq_srv || !blq_srv->mt_listener_mgr_ ||
        (endpoint == TcpConnection::NO_ENDPOINT())) {
        // Should not happen.
        return (false);
    }

    std::string reason = "no reason";
    IOAddress peer = IOAddress(endpoint.address());
    if (!blq_srv->impl_ || !blq_srv->impl_->isRequester(peer)) {
        reason = "not a valid requester";
    } else {
        // Note that max_conn is always >= 1.
        size_t max_conn = blq_srv->getMaxRequesterConnections();
        TcpListenerPtr listener = blq_srv->mt_listener_mgr_->getTcpListener();
        if (!listener) {
            // Should not happen.
            return (false);
        }

        size_t total_cnt = 0;
        size_t used_cnt = listener->usedByRemoteIp(peer, total_cnt);
        // The total count is the number of active connections plus
        // the connection in the accept() and the current connection.
        if (total_cnt >= max_conn + 2) {
            // Limiting.
            reason = "too many connections";
        } else if ((max_conn + 1 - total_cnt) > 0) {
            // More than one free slot.
            return (true);
        } else if ((max_conn <= 1) ||
                   (blq_srv->impl_->getNumRequesters() <= 1)) {
            // No last slot reservation.
            return (true);
        } else if (used_cnt + 1 < total_cnt) {
            // Another requester.
            return (true);
        } else {
            reason = "last free slot reserved for another requester";
        }
    }

    LOG_ERROR(lease_query_logger, BULK_LEASE_QUERY_REJECTED_CONNECTION)
        .arg(peer.toText())
        .arg(reason);
    return (false);
}

void
BulkLeaseQueryService::doStartListener() {
    try {
        if (BulkLeaseQueryService::instance()) {
            BulkLeaseQueryService::instance()->startListener();
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(lease_query_logger,
                  BULK_LEASE_QUERY_LISTENER_START_FAILED)
            .arg(ex.what());
    }
}

} // end of isc::lease_query namespace
} // end of isc namespace
