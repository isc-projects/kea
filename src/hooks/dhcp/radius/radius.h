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

/// @brief UDP client class.
///
/// Copied from TcpClient with UDP specific parts moved from RadiusImpl.
class UdpClient {
public:
    /// @brief Constructor.
    ///
    /// @param io_service IO service to be used by the UDP client.
    /// @param thread_pool_size maximum number of threads in the thread pool.
    /// The value 0 means that MT is disabled.
    /// deferred until a subsequent call to @ref start().
    UdpClient(const asiolink::IOServicePtr& io_service,
              unsigned thread_pool_size = 0);

    /// @brief Destructor.
    ~UdpClient();

    /// @brief Starts running the client's thread pool, if multi-threaded.
    void start();

    /// @brief Halts client-side IO activity.
    ///
    /// Shutdown all exchanges, In multi-threaded mode discards the
    /// thread-pool and the internal IOService.
    void stop();

    /// @brief Check if the current thread can perform thread pool state
    /// transition.
    ///
    /// @throw MultiThreadingInvalidOperation if the state transition is done on
    /// any of the worker threads.
    void checkPermissions();

    /// @brief Pauses the client's thread pool.
    ///
    /// @throw InvalidOperation if the thread pool does not exist.
    void pause();

    /// @brief Resumes running the client's thread pool.
    ///
    /// @throw InvalidOperation if the thread pool does not exist.
    void resume();

    /// @brief Fetches a pointer to the internal IOService used to
    /// drive the thread-pool in multi-threaded mode.
    ///
    /// @return pointer to the IOService instance, or an empty pointer
    /// in single-threaded mode.
    const asiolink::IOServicePtr getThreadIOService() const;

    /// @brief the maximum size of the thread pool.
    ///
    /// @return the maximum size of the thread pool.
    unsigned getThreadPoolSize() const;

    /// @brief Register Exchange.
    ///
    /// @param exchange The exchange to register.
    void registerExchange(ExchangePtr exchange);

    /// @brief Unregister Exchange.
    ///
    /// @param exchange The exchange to unregister.
    void unregisterExchange(ExchangePtr exchange);

private:
    /// @brief Pointer to IOService.
    isc::asiolink::IOServicePtr io_service_;

    /// @brief Thread pool size.
    unsigned thread_pool_size_;

    /// @brief Pointer to private IOService used in multi-threaded mode.
    isc::asiolink::IOServicePtr thread_io_service_;

    /// @brief Thread pool.
    asiolink::IoServiceThreadPoolPtr thread_pool_;

    /// @brief The list of Exchange objects.
    std::list<ExchangePtr> exchange_list_;

    /// @brief Mutex to protect the internal state.
    std::mutex mutex_;
};

/// @brief Pointer to UDP client.
typedef boost::shared_ptr<UdpClient> UdpClientPtr;

/// @brief Default key of remap table in the subnet ID space.
/// Moved from radius_request.h file for better visibility.
static const uint32_t SUBNET_ID_DEFAULT = 0;

/// @brief Forward declaration of RadiusTls.
class RadiusTls;

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

    /// @brief Check if access is served.
    ///
    /// @return true is access is served, false otherwise.
    bool serveAccess() const;

    /// @brief Check if accounting is served.
    ///
    /// @return true is accounting is served, false otherwise.
    bool serveAccounting() const;

    /// @brief Get servers for access.
    ///
    /// @return Servers to use with access servers.
    const Servers& getAccessServers() const;

    /// @brief Get servers for accounting.
    ///
    /// @return Servers to use with accounting servers.
    const Servers& getAccountingServers() const;

    /// @brief Set the access idle timer.
    void setAccessIdleTimer();

    /// @brief Set the accounting idle timer.
    void setAccountingIdleTimer();

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

    /// @brief Transport protocol.
    RadiusProtocol proto_;

    /// @brief UDP client.
    UdpClientPtr udp_client_;

    /// @brief Subnet ID to NAS port map.
    std::map<uint32_t, uint32_t> remap_;

    /// @brief Pointer to common tls (never null).
    boost::shared_ptr<RadiusTls> common_;

    /// @brief Pointer to access (never null).
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

private:

    /// @brief The IOService object, used for all ASIO operations.
    isc::asiolink::IOServicePtr io_context_;

    /// @brief The hook I/O service.
    isc::asiolink::IOServicePtr io_service_;
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
