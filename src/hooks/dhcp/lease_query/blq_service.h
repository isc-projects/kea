// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BLQ_SERVICE_H
#define BLQ_SERVICE_H

#include <asiolink/asio_wrapper.h>
#include <cc/data.h>
#include <cc/simple_parser.h>
#include <exceptions/exceptions.h>
#include <lease_query_impl.h>
#include <mt_lease_query_mgr.h>
#include <boost/noncopyable.hpp>

namespace isc {
namespace lease_query {

/// @brief Forward declaration of @c BulkLeaseQueryService.
class BulkLeaseQueryService;

/// @brief Defines a shared pointer to BulkLeaseQueryService.
typedef boost::shared_ptr<BulkLeaseQueryService> BulkLeaseQueryServicePtr;

// @brief Multi-threaded Lease Query listener manager singleton class.
class BulkLeaseQueryService  : boost::noncopyable {
public:

    /// @brief Manages (advanced) configuration.
    class AdvancedConfig {
        public:
        /// @brief Constructor.
        ///
        /// Set the default values.
        ///
        /// @param family protocol family of the list (AF_INET or AF_INET6).
        AdvancedConfig(uint16_t family)
            : family_(family),
              bulk_query_enabled_(false),
              active_query_enabled_(false),
              extended_info_tables_enabled_(false),
              lease_query_ip_(asiolink::IOAddress(family == AF_INET ?
                                                  "127.0.0.1" : "::1")),
              lease_query_tcp_port_(family == AF_INET ? 67 : 547),
              max_bulk_query_threads_(0),
              max_requester_connections_(10),
              max_concurrent_queries_(0),
              max_requester_idle_time_(300),
              max_leases_per_fetch_(100),
              trust_anchor_(),
              cert_file_(),
              key_file_(),
              cert_required_(true) {
        }

        /// @brief Parse the advanced argument.
        ///
        /// @param advanced The advanced configuration.
        /// @throw BadValue on bad values.
        void parse(isc::data::ConstElementPtr advanced);

        /// @brief Keywords for advanced configuration.
        static const isc::data::SimpleKeywords CONFIG_KEYWORDS;

        /// @brief Protocol family of the list (AF_INET or AF_INET6).
        uint16_t family_;

        /// @brief Bulk query flag (default false).
        bool bulk_query_enabled_;

        /// @brief Active query flag (always false).
        bool active_query_enabled_;

        /// @brief Extended info tables flag (default same as Bulk query).
        bool extended_info_tables_enabled_;

        /// @brief Lease query IP (default 127.0.0.1 or ::1).
        isc::asiolink::IOAddress lease_query_ip_;

        /// @brief Lease query TCP port (default 67 or 547).
        uint16_t lease_query_tcp_port_;

        /// @brief Maximum number of bulk query processing threads (default 0).
        size_t max_bulk_query_threads_;

        /// @brief Maximum number of requester connections (default 10).
        size_t max_requester_connections_;

        /// @brief Maximum number of concurrent queries per connection.
        size_t max_concurrent_queries_;

        /// @brief Maximum requester idle time (default 300 seconds).
        long max_requester_idle_time_;

        /// @brief Maximum number of leases per fetch (default 100).
        size_t max_leases_per_fetch_;

        /// @brief TLS trust anchor (not yet used).
        std::string trust_anchor_;

        /// @brief TLS server certificate file name (not yet used).
        std::string cert_file_;

        /// @brief TLS server private key file name (not yet used).
        std::string key_file_;

        /// @brief TLS client certificate required flag (not yet used).
        bool cert_required_;
    };

    /// @brief Destructor.
    virtual ~BulkLeaseQueryService();

    /// @brief Reset the sole instance of @c BulkLeaseQueryService.
    static void reset();

    /// @brief Create a new instance of the @c BulkLeaseQueryService.
    ///
    /// @param impl The lease query implementation (should not be null).
    /// @param advanced The advanced configuration (should not be null).
    /// @throw BadValue on bad values.
    static void create(LeaseQueryImpl* impl,
                       isc::data::ConstElementPtr advanced);

    /// @brief Returns a pointer to the sole instance of
    /// the @c BulkLeaseQueryService, can return null.
    static BulkLeaseQueryServicePtr instance();

    /// @brief Start the listener.
    ///
    /// Posted from dhcp6_srv_configured callout.
    static void doStartListener();

    /// @brief Configuration set/get methods.
    /// @{

    /// @brief Returns the protocol family.
    uint16_t getFamily() const {
        return (config_.family_);
    }

    /// @brief Returns the bulk query enabled flag.
    bool getBulkQueryEnabled() const {
        return (config_.bulk_query_enabled_);
    }

    /// @brief Returns the active query enabled flag.
    bool getActiveQueryEnabled() const {
        return (config_.active_query_enabled_);
    }

    /// @brief Returns the extended info tables enabled flag.
    bool getExtendedInfoTablesEnabled() const {
        return (config_.extended_info_tables_enabled_);
    }

    /// @brief Returns the lease query IP address.
    const isc::asiolink::IOAddress& getLeaseQueryIp() const {
        return (config_.lease_query_ip_);
    }

    /// @brief Returns the lease query TCP port.
    uint16_t getLeaseQueryTcpPort() const {
        return (config_.lease_query_tcp_port_);
    }

    /// @brief Returns the maximum number of bulk query processing threads.
    size_t getMaxBulkQueryThreads() const {
        return (config_.max_bulk_query_threads_);
    }

    /// @brief Sets the maximum number of bulk query processing threads.
    ///
    /// @param max_bulk_query_threads The new maximum.
    void setMaxBulkQueryThreads(size_t max_bulk_query_threads) {
        config_.max_bulk_query_threads_ = max_bulk_query_threads;
    }

    /// @brief Returns the maximum number of requester connections.
    size_t getMaxRequesterConnections() const {
        return (config_.max_requester_connections_);
    }

    /// @brief Sets the maximum number of requester connections.
    ///
    /// @param max_requester_connections New maximum.
    /// @throw BadValue when the new maximum is 0.
    void setMaxRequesterConnections(size_t max_requester_connections);

    /// @brief Returns the maximum number of concurrent queries per connection.
    size_t getMaxConcurrentQueries() const {
        return (config_.max_concurrent_queries_);
    }

    /// @brief Sets the maximum number of concurrent queries per connection.
    ///
    /// @param max_concurrent_queries The new maximum.
    void setMaxConcurrentQueries(size_t max_concurrent_queries) {
        config_.max_concurrent_queries_ = max_concurrent_queries;
    }

    /// @brief Returns the maximum requester idle time.
    long getMaxRequesterIdleTime() const {
        return (config_.max_requester_idle_time_);
    }

    /// @brief Returns the maximum number of leases per fetch.
    size_t getMaxLeasePerFetch() const {
        return (config_.max_leases_per_fetch_);
    }

    /// @brief Sets the maximum number of leases per fetch.
    ///
    /// @param max_leases_per_fetch The new maximum.
    /// @throw BadValue when the new maximum is 0.
    void setMaxLeasePerFetch(size_t max_leases_per_fetch);
    /// @}

    /// @brief Check listener current thread permissions to
    /// perform thread pool state transition.
    ///
    /// @throw MultiThreadingInvalidOperation if the state transition
    /// is done on any of the worker threads.
    void checkListenerPausePermission();

    /// @brief Start the listener instance.
    ///
    /// Starts the listener's thread pool and registers
    /// pauseListener() and resumeListener() as the MultiThreading
    /// critical section entry and exit callbacks, respectively.
    void startListener();

    /// @brief Pauses listener thread pool operations.
    ///
    /// Suspends the listener thread pool event processing.
    /// Serves as the MultiThreading critical section entry callback.
    void pauseListener();

    /// @brief Resumes listener thread pool operations.
    ///
    /// Resumes listener thread pool event processing.
    /// Serves as the MultiThreading critical section exit callback.
    void resumeListener();

    /// @brief Stop the listener instance.
    ///
    /// It unregisters the MultiThreading critical section callbacks,
    /// closes all connections and stops the listener's thread pool.
    void stopListener();

    /// @brief TCP connection accept filter.
    ///
    /// @param endpoint The endpoint of the remote end of the TCP connection.
    /// @return True if the connection should be accepted, False if it should
    /// be dropped i.e. immediately closed.
    static bool acceptFilter(const boost::asio::ip::tcp::endpoint& endpoint);

private:
    /// @brief Constructor.
    ///
    /// @param impl The lease query implementation.
    /// @param config Bulk config.
    BulkLeaseQueryService(LeaseQueryImpl* impl,
                          const AdvancedConfig& config);

    /// @brief Returns a reference to the pointer to the sole instance.
    static BulkLeaseQueryServicePtr& getBulkLeaseQueryServicePtr();

    /// @param Lease query implementation.
    LeaseQueryImpl* impl_;

    /// @param Configuration.
    AdvancedConfig config_;

    /// @param Listener manager instance.
    MtLeaseQueryListenerMgrPtr mt_listener_mgr_;
};

} // namespace isc::lease_query
} // namespace isc

#endif // BLQ_SERVICE_H
