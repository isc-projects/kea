// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/cfg_globals.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/cfg_multi_threading.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <util/multi_threading_mgr.h>
#include <radius.h>
#include <radius_access.h>
#include <radius_accounting.h>
#include <radius_log.h>
#include <radius_parsers.h>

#include <exception>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::util;

namespace isc {
namespace radius {

std::atomic<bool> RadiusImpl::shutdown_(false);

RadiusImpl&
RadiusImpl::instance() {
    return (*instancePtr());
}

const RadiusImplPtr&
RadiusImpl::instancePtr() {
    static RadiusImplPtr impl(new RadiusImpl());
    return (impl);
}

RadiusImpl::RadiusImpl()
    : auth_(new RadiusAccess()), acct_(new RadiusAccounting()),
      bindaddr_("*"), canonical_mac_address_(false),
      clientid_pop0_(false), clientid_printable_(false),
      deadtime_(0), extract_duid_(true),
      reselect_subnet_pool_(false), reselect_subnet_address_(false),
      retries_(3), thread_pool_size_(0), timeout_(0),
      id_type4_(Host::IDENT_CLIENT_ID), id_type6_(Host::IDENT_DUID),
      io_context_(new IOService()), io_service_(io_context_) {
}

RadiusImpl::~RadiusImpl() {
    try {
        cleanup();
    } catch(exception const& exception) {
        LOG_WARN(radius_logger, RADIUS_CLEANUP_EXCEPTION)
            .arg(exception.what());
    }
}

void RadiusImpl::registerExchange(ExchangePtr exchange) {
    MultiThreadingLock lock(mutex_);
    exchange_list_.push_back(exchange);
}

void RadiusImpl::unregisterExchange(ExchangePtr exchange) {
    MultiThreadingLock lock(mutex_);
    exchange_list_.remove(exchange);
}

void RadiusImpl::cleanup() {
    session_history_filename_.clear();
    id_type6_ = Host::IDENT_DUID;
    id_type4_ = Host::IDENT_CLIENT_ID;
    timeout_ = 10;
    retries_ = 3;
    reselect_subnet_address_ = false;
    reselect_subnet_pool_ = false;
    extract_duid_ = true;
    clientid_printable_ = false;
    clientid_pop0_ = false;
    canonical_mac_address_ = false;
    cache_.reset();
    bindaddr_ = "*";
    thread_pool_size_ = 0;
    remap_.clear();

    if (backend_) {
        HostDataSourceFactory::deregisterFactory("radius");
        HostMgr::delBackend("radius");
        backend_.reset();
    }

    auth_.reset(new RadiusAccess());
    acct_.reset(new RadiusAccounting());

    if (thread_pool_) {
        MultiThreadingMgr::instance().removeCriticalSectionCallbacks("RADIUS");
        thread_pool_->stop();
        for (auto const& exchange : exchange_list_) {
            exchange->shutdown();
        }
        thread_pool_->getIOService()->stopAndPoll();
        thread_pool_.reset();
    } else {
        for (auto const& exchange : exchange_list_) {
            exchange->shutdown();
        }
    }
    io_context_.reset(new IOService());
    exchange_list_.clear();
    if (getIOService()) {
        getIOService()->stopAndPoll();
    }
    io_service_ = io_context_;
}

void RadiusImpl::reset() {
    RadiusImpl::shutdown_ = true;
    std::unique_ptr<void, void(*)(void*)> p(static_cast<void*>(this), [](void*) { RadiusImpl::shutdown_ = false; });
    cleanup();
}

void RadiusImpl::init(ElementPtr&config) {
    auth_.reset(new RadiusAccess());
    acct_.reset(new RadiusAccounting());
    RadiusConfigParser parser;
    parser.parse(config);
    checkEarlyGlobalResvLookup();
    checkSharedNetworks();
    if (auth_->enabled_) {
        if (!HostDataSourceFactory::registeredFactory("cache")) {
            LOG_ERROR(radius_logger, RADIUS_ACCESS_NO_HOST_CACHE);
            isc_throw(Unexpected, "Configuring access failed: host cache library not loaded.");
            return;
        }
        backend_.reset(new RadiusBackend());
        auto radius_factory = [this](const DatabaseConnection::ParameterMap&) {
            return (backend_);
        };
        HostDataSourceFactory::registerFactory("radius", radius_factory);
    }
    if (acct_->enabled_) {
        acct_->init(session_history_filename_);
    }
}

void
RadiusImpl::startServices() {
    // Check if Kea core is multi-threaded.
    ConstElementPtr const& dhcp_config(
        CfgMgr::instance().getStagingCfg()->getDHCPMultiThreading());
    bool multi_threaded(false);
    uint32_t dhcp_threads(0);
    uint32_t dummy_queue_size(0);
    CfgMultiThreading::extract(dhcp_config, multi_threaded, dhcp_threads,
                               dummy_queue_size);

    if (multi_threaded) {
        // When threads are configured as zero, use the same number as DHCP
        // threads. If that is also zero, auto-detect.
        unsigned thread_pool_size(thread_pool_size_);
        if (thread_pool_size_ == 0) {
            if (dhcp_threads == 0) {
                uint32_t const hardware_threads(
                    MultiThreadingMgr::detectThreadCount());
                if (hardware_threads == 0) {
                    // Keep it single-threaded.
                    return;
                } else {
                    thread_pool_size = hardware_threads;
                }
            } else {
                thread_pool_size = dhcp_threads;
            }
        }

        // Schedule a start of the services. This ensures we begin after
        // the dust has settled and Kea MT mode has been firmly established.
        io_service_->post([this, thread_pool_size]() {
            // Initialize thread pool.
            thread_pool_ =
                boost::make_shared<IoServiceThreadPool>(IOServicePtr(),
                                                        thread_pool_size);
            io_context_ = thread_pool_->getIOService();

            // Add critical section callbacks.
            MultiThreadingMgr::instance().addCriticalSectionCallbacks("RADIUS",
                    [this]() { checkPausePermissions(); },
                    [this]() { pauseThreadPool(); },
                    [this]() { resumeThreadPool(); });

            // Run the thread pool.
            thread_pool_->run();

            LOG_INFO(radius_logger, RADIUS_THREAD_POOL_STARTED)
                .arg(thread_pool_size);
        });
    }
}

void
RadiusImpl::checkPausePermissions() {
    // Since this function is used as CS callback all exceptions must be
    // suppressed, unlikely though they may be.
    try {
        if (thread_pool_) {
            thread_pool_->checkPausePermissions();
        }
    } catch (const isc::MultiThreadingInvalidOperation& ex) {
        LOG_ERROR(radius_logger, RADIUS_PAUSE_ILLEGAL)
            .arg(ex.what());
        // The exception needs to be propagated to the caller of the
        // MultiThreadingCriticalSection constructor.
        throw;
    } catch (const exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_PAUSE_PERMISSIONS_FAILED)
            .arg(ex.what());
    }
}

void
RadiusImpl::pauseThreadPool() {
    // Since this function is used as CS callback all exceptions must be
    // suppressed, unlikely though they may be.
    try {
        // Pause the thread pool.
        if (thread_pool_) {
            thread_pool_->pause();
        }
    } catch (const exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_PAUSE_FAILED)
            .arg(ex.what());
    }
}

void
RadiusImpl::resumeThreadPool() {
    // Since this function is used as CS callback all exceptions must be
    // suppressed, unlikely though they may be.
    try {
        if (thread_pool_) {
            thread_pool_->run();
        }
    } catch (const exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_RESUME_FAILED)
            .arg(ex.what());
    }
}

namespace {

/// @brief Checks if reservations-global is true and
/// reservations-in-subnet is false at the same level
/// using the staging config (vs the current config) to fetch the
/// values of reservations flags at the global scope.
///
/// @param subnet The subnet (member of a shared network).
/// @param network The parent of the subnet.
/// @return True if the the host reservation mode is global, false otherwise.
bool isHostReservationModeGlobal(SubnetPtr subnet, NetworkPtr network) {
    auto subnet_hr_global = subnet->getReservationsGlobal(Network::Inheritance::NONE);
    auto subnet_hr_subnet = subnet->getReservationsInSubnet(Network::Inheritance::NONE);
    if (!subnet_hr_global.unspecified() && !subnet_hr_subnet.unspecified()) {
        return (subnet_hr_global && !subnet_hr_subnet);
    }
    if (!subnet_hr_global.unspecified() || !subnet_hr_subnet.unspecified()) {
        return (false);
    }
    auto network_hr_global = network->getReservationsGlobal(Network::Inheritance::NONE);
    auto network_hr_subnet = network->getReservationsInSubnet(Network::Inheritance::NONE);
    if (!network_hr_global.unspecified() && !network_hr_subnet.unspecified()) {
        return (network_hr_global && !network_hr_subnet);
    }
    if (!network_hr_global.unspecified() || !network_hr_subnet.unspecified()) {
        return (false);
    }
    // Inherit from staging (vs current) config for globals.
    auto global_hr_mode_elem = CfgMgr::instance().getStagingCfg()->
        getConfiguredGlobal("reservations-global");
    // Default reservations-global is false.
    if (!global_hr_mode_elem) {
        return (false);
    }
    auto subnet_hr_mode_elem = CfgMgr::instance().getStagingCfg()->
        getConfiguredGlobal("reservations-in-subnet");
    // Default reservations-in-subnet is true.
    if (!subnet_hr_mode_elem) {
        return (false);
    }
    if (global_hr_mode_elem->getType() != Element::boolean) {
        isc_throw(Unexpected, "'reservations-global' global value must be a boolean");
    }
    if (!global_hr_mode_elem->boolValue()) {
        return (false);
    }
    if (subnet_hr_mode_elem->getType() != Element::boolean) {
        isc_throw(Unexpected, "'reservations-in-subnet' global value must be a boolean");
    }
    if (subnet_hr_mode_elem->boolValue()) {
        return (false);
    }
    return (true);
}

} // end of anonymous namespace

void RadiusImpl::checkEarlyGlobalResvLookup() {
    auto flag = CfgMgr::instance().getStagingCfg()->
        getConfiguredGlobal(CfgGlobals::EARLY_GLOBAL_RESERVATIONS_LOOKUP);
    if (flag && (flag->boolValue())) {
        isc_throw(ConfigError, "early-global-reservations-lookup is not "
                  "compatible with RADIUS");
    }
}

void RadiusImpl::checkSharedNetworks() {
    bool need_disable_single_query = false;
    if (CfgMgr::instance().getFamily() == AF_INET) {
        auto networks = CfgMgr::instance().getStagingCfg()->
            getCfgSharedNetworks4()->getAll();
        if (networks->empty()) {
            return;
        }
        need_disable_single_query = true;
        for (auto const& network : *networks) {
            auto subnets = network->getAllSubnets();
            if (subnets->size() <= 1) {
                continue;
            }
            for (auto const& subnet : *subnets) {
                if (!isHostReservationModeGlobal(subnet, network)) {
                    isc_throw(ConfigError, "subnet " << subnet->getID()
                              << " '" << subnet->toText() << "' of shared "
                              << "network " << network->getName()
                              << " does not use only global host reservations "
                              << "which are required for subnets in "
                              << "shared networks by RADIUS");
                }
            }
        }
    } else {
        auto networks = CfgMgr::instance().getStagingCfg()->
            getCfgSharedNetworks6()->getAll();
        if (networks->empty()) {
            return;
        }
        need_disable_single_query = true;
        for (auto const& network : *networks) {
            auto subnets = network->getAllSubnets();
            if (subnets->size() <= 1) {
                continue;
            }
            for (auto const& subnet : *subnets) {
                if (!isHostReservationModeGlobal(subnet, network)) {
                    isc_throw(ConfigError, "subnet " << subnet->getID()
                              << " '" << subnet->toText() << "' of shared "
                              << "network " << network->getName()
                              << " does not use only global host reservations "
                              << "which are required for subnets in "
                              << "shared networks by RADIUS");
                }
            }
        }
    }
    if (need_disable_single_query) {
        HostMgr::instance().setDisableSingleQuery(true);
    }
}

bool RadiusImpl::checkHostBackends() {
    if (cache_) {
        return (true);
    }
    // Try only once.
    static bool already_tried = false;
    if (already_tried) {
        return (false);
    }
    already_tried = true;
    // Add backends
    try {
        // createManagers can reset the host manager so re-add host cache.
        // Note that init already checked the factory was registered.
        if (!HostMgr::instance().getHostDataSource()) {
            HostMgr::instance().addBackend("type=cache");
        }
        HostMgr::instance().addBackend("type=radius");
    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_ACCESS_HOST_BACKEND_ERROR)
            .arg("radius")
            .arg(ex.what());
        return (false);
    }
    // Get a pointer to host cache backend
    HostDataSourcePtr cache = HostMgr::instance().getHostDataSource();
    cache_ = boost::dynamic_pointer_cast<CacheHostDataSource>(cache);
    if (!cache_) {
        LOG_ERROR(radius_logger, RADIUS_ACCESS_NO_HOST_CACHE);
        return (false);
    }
    return (true);
}

ElementPtr RadiusImpl::toElement() const {
    ElementPtr result = Element::createMap();

    // dictionary.
    result->set("dictionary", Element::create(dictionary_));

    // bindaddr.
    result->set("bindaddr", Element::create(bindaddr_));

    // canonical-mac-address.
    result->set("canonical-mac-address",
                Element::create(canonical_mac_address_));

    // client-id-pop0.
    result->set("client-id-pop0", Element::create(clientid_pop0_));

    // client-id-printable.
    result->set("client-id-printable", Element::create(clientid_printable_));

    // deadtime.
    result->set("deadtime", Element::create(deadtime_));

    // extract-duid.
    result->set("extract-duid", Element::create(extract_duid_));

    // identifier-type4.
    result->set("identifier-type4",
                Element::create(Host::getIdentifierName(id_type4_)));

    // identifier-type6.
    result->set("identifier-type6",
                Element::create(Host::getIdentifierName(id_type6_)));

    // realm.

    // reselect-subnet-address.
    result->set("reselect-subnet-address",
                Element::create(reselect_subnet_address_));

    // reselect-subnet-pool.
    result->set("reselect-subnet-pool",
                Element::create(reselect_subnet_pool_));

    // retries.
    result->set("retries", Element::create(retries_));

    // session-history.
    result->set("session-history", Element::create(session_history_filename_));

    // thread-pool-size.
    result->set("thread-pool-size", Element::create(thread_pool_size_));

    // timeout.
    result->set("timeout", Element::create(timeout_));

    // services.
    result->set("access", auth_->toElement());
    result->set("accounting", acct_->toElement());

    // NAS ports.
    if (!remap_.empty()) {
        ElementPtr ports = Element::createList();
        for (auto const& item : remap_) {
            ElementPtr entry = Element::createMap();
            if (item.first != 0) {
                entry->set("subnet-id",
                           Element::create(static_cast<int64_t>(item.first)));
            }
            entry->set("port",
                       Element::create(static_cast<int64_t>(item.second)));
            ports->add(entry);
        }
        result->set("nas-ports", ports);
    }

    return (result);
}

unordered_set<thread::id> InHook::set_;

mutex InHook::mutex_;

InHook::InHook() {
    const auto& id = this_thread::get_id();
    MultiThreadingLock lock(mutex_);
    auto ret = set_.insert(id);
    if (!ret.second) {
        std::cerr << "InHook insert error on " << id << "\n";
    }
}

InHook::~InHook() {
    const auto& id = this_thread::get_id();
    MultiThreadingLock lock(mutex_);
    size_t ret = set_.erase(id);
    if (ret != 1) {
        std::cerr << "InHook erase error on " << id << "\n";
    }
}

bool InHook::check() {
    const auto& id = this_thread::get_id();
    MultiThreadingLock lock(mutex_);
    size_t ret = set_.count(id);
    return (ret == 1);
}

} // end of namespace isc::radius
} // end of namespace isc
