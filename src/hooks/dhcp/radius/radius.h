// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_H
#define RADIUS_H

#include <cfg_attribute.h>
#include <client_exchange.h>
#include <radius_backend.h>
#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <asiolink/io_service_thread_pool.h>
#include <dhcpsrv/cache_host_data_source.h>
#include <dhcpsrv/host.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <atomic>
#include <list>
#include <map>
#include <mutex>
#include <thread>
#include <unordered_set>
#include <vector>

namespace isc {
namespace radius {

/// @brief Default key of remap table in the subnet ID space.
/// Moved from radius_request.h file for better visibility.
static const uint32_t SUBNET_ID_DEFAULT = 0;

/// @brief Forward declaration of RadiusAccess.
class RadiusAccess;

/// @brief forward declaration of RadiusAccounting.
class RadiusAccounting;

/// @brief Pointer to the Radius hooks library implementation.
class RadiusImpl;
typedef boost::shared_ptr<RadiusImpl> RadiusImplPtr;

/// @brief Radius hooks library implementation.
class RadiusImpl : public data::CfgToElement, public boost::noncopyable {
public:

    /// RadiusImpl is a singleton class. This method returns reference
    /// to its sole instance.
    ///
    /// @return the only existing instance of radius implementation.
    static RadiusImpl& instance();

    /// @brief Destructor.
    ~RadiusImpl();

    /// @brief Reset the state as it was just created.
    void reset();

    /// @brief Initialize.
    ///
    /// @param config Configuration specified for the hooks library.
    /// @throw ConfigError when configuration fails.
    void init(data::ElementPtr& config);

    /// @brief Check the early global host reservations lookup flag.
    ///
    /// @throw ConfigError when the server configuration is not compatible.
    void checkEarlyGlobalResvLookup();

    /// @brief Check shared network server configuration.
    ///
    /// This verifies the compatibility of the server configuration
    /// with the RADIUS hook, in particular with shared networks:
    ///  - set the disable single query flag
    ///  - verify that any shared network with more than one subnet uses
    ///   only global reservations.
    /// @throw ConfigError when the server configuration is not compatible.
    void checkSharedNetworks();

    /// @brief Check host backends (cache and radius).
    ///
    /// As a side effect when the host cache backend is found the cache_
    /// field is set.
    ///
    /// @todo: Calls to addBackend() (in particular the cache one) should
    /// be moved to Kea core (cf #5562).
    /// Note they must be after the load function so currently this method
    /// is called at first use.
    ///
    /// @return true when found, false when an error occurred.
    bool checkHostBackends();

    /// @brief Start the I/O mechanisms.
    ///
    /// Start the thread pool for MT or create the IO context for ST.
    void startServices();

    /// @brief Get the hook I/O service.
    ///
    /// @return the hook I/O service.
    isc::asiolink::IOServicePtr getIOContext() {
        return (io_context_);
    }

    /// @brief Set the hook I/O service.
    ///
    /// @param io_service the hook I/O service.
    void setIOContext(isc::asiolink::IOServicePtr io_service) {
        io_context_ = io_service;
    }

    /// @brief Get the hook I/O service.
    ///
    /// @return the hook I/O service.
    isc::asiolink::IOServicePtr getIOService() {
        return (io_service_);
    }

    /// @brief Set the hook I/O service.
    ///
    /// @param io_service the hook I/O service.
    void setIOService(isc::asiolink::IOServicePtr io_service) {
        io_service_ = io_service;
    }

    /// @brief Unparse implementation configuration.
    ///
    /// @return a pointer to unparsed configuration.
    data::ElementPtr toElement() const override;

    /// @brief Register Exchange.
    ///
    /// @param exchange The exchange to register.
    void registerExchange(ExchangePtr exchange);

    /// @brief Unregister Exchange.
    ///
    /// @param exchange The exchange to unregister.
    void unregisterExchange(ExchangePtr exchange);

    /// @brief Dictionary path.
    std::string dictionary_;

    /// @brief Subnet ID to NAS port map.
    std::map<uint32_t, uint32_t> remap_;

    // @brief Pointer to access (never null).
    boost::shared_ptr<RadiusAccess> auth_;

    /// @brief Pointer to accounting (never null).
    boost::shared_ptr<RadiusAccounting> acct_;

    /// @brief Host cache.
    dhcp::CacheHostDataSourcePtr cache_;

    /// @brief Radius backend.
    RadiusBackendPtr backend_;

    /// @brief bindaddr.
    std::string bindaddr_;

    /// @brief Canonical MAC address.
    bool canonical_mac_address_;

    /// @brief Client Id pop leading zero(s).
    bool clientid_pop0_;

    /// @brief Client Id try printable.
    bool clientid_printable_;

    /// @brief Deadtime.
    unsigned deadtime_;

    /// @brief Extract Duid from Client Id.
    bool extract_duid_;

    /// @brief Reselect subnet using pool.
    bool reselect_subnet_pool_;

    /// @brief Reselect subnet using address.
    bool reselect_subnet_address_;

    /// @brief Retries.
    unsigned retries_;

    /// @brief Session history filename.
    std::string session_history_filename_;

    /// @brief Thread pool size.
    unsigned thread_pool_size_;

    /// @brief Timeout.
    unsigned timeout_;

    /// @brief Identifier type for IPv4.
    dhcp::Host::IdentifierType id_type4_;

    /// @brief Identifier type for IPv6.
    dhcp::Host::IdentifierType id_type6_;

    /// @brief Thread pool.
    asiolink::IoServiceThreadPoolPtr thread_pool_;

    /// @brief Flag which indicates that the instance is shutting down.
    static std::atomic<bool> shutdown_;

protected:
    /// @brief Protected constructor.
    RadiusImpl();

    /// @brief Returns pointer to the sole instance of radius implementation.
    ///
    /// @return Shared pointer to the RadiusImpl instance.
    static const RadiusImplPtr& instancePtr();

    /// @brief Clean up members.
    void cleanup();

    /// @brief Check if the current thread can transition the thread pool to the paused state.
    ///
    /// Used as a CS callback.
    ///
    /// @throw MultiThreadingInvalidOperation if the state transition is done on
    /// any of the worker threads.
    void checkPausePermissions();

    /// @brief Pause the thread pool.
    ///
    /// Used as a CS callback.
    void pauseThreadPool();

    /// @brief Resume the thread pool.
    ///
    /// Used as a CS callback.
    void resumeThreadPool();

private:

    /// @brief The IOService object, used for all ASIO operations.
    isc::asiolink::IOServicePtr io_context_;

    /// @brief The hook I/O service.
    isc::asiolink::IOServicePtr io_service_;

    /// @brief The list of Exchange objects.
    std::list<ExchangePtr> exchange_list_;

    /// @brief Mutex to protect the internal state.
    std::mutex mutex_;
};

/// @brief InHook class (RAII style).
class InHook {
public:
    /// @brief Constructor.
    ///
    /// Add the current thread id to the set.
    InHook();

    /// @brief Destructor.
    ///
    /// Remove the current thread id from the set.
    ~InHook();

    /// @brief Check if the current thread is in hook code or not.
    static bool check();

private:
    /// @brief Set of thread ids in hook code.
    static std::unordered_set<std::thread::id> set_;

    /// @brief Mutex to protect the set.
    static std::mutex mutex_;
};

} // end of namespace isc::radius
} // end of namespace isc

#endif
