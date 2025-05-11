// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PING_CHECK_MGR_H
#define PING_CHECK_MGR_H

#include <asiolink/interval_timer.h>
#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <asiolink/io_service_thread_pool.h>
#include <cc/data.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/srv_config.h>
#include <hooks/callout_handle.h>
#include <dhcp/pkt4.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/network_state.h>
#include <ping_context_store.h>
#include <ping_channel.h>
#include <config_cache.h>

#include <boost/enable_shared_from_this.hpp>

#include <mutex>

namespace isc {
namespace ping_check {

/// @brief Defines a pointer to a PingContextStore.
typedef boost::shared_ptr<PingContextStore> PingContextStorePtr;

/// @brief Ping Check Manager.
///
/// PinCheckMgr carries out the higher order management of requests for ping
/// checks from the server.  It is a singleton, instantiated when the library
/// is loaded.  It is responsible for:
/// 1. Parsing and applying configuration.
/// 2. Maintaining in-memory store of current ping requests (PingContextStore).
/// 3. Creating and managing the PingChannel through which individual ICMP ECHO/REPLY
/// cycles are conducted.
/// 4. When in multi-threaded mode, it creates an IOServiceThread and synchronizes
/// its state with Kea core MT.
class PingCheckMgr : public boost::enable_shared_from_this<PingCheckMgr> {
public:
    /// @brief Constructor.
    explicit PingCheckMgr();

    /// @brief Constructor.
    ///
    /// This constructor is used in testing. It permits setting some basic behavior
    /// parameters directly, rather than requiring calls to @c configure().
    ///
    /// @param num_threads number of threads to use in the thread pool (0 means follow
    /// core thread pool size).
    /// @param min_echos minimum number of ECHO REQUESTs sent without replies
    /// received required to declare an address free to offer. Defaults to 1,
    /// must be greater than zero.
    /// @param reply_timeout maximum number of milliseconds to wait for an
    /// ECHO REPLY after an ECHO REQUEST has been sent.  Defaults to 100.
    PingCheckMgr(uint32_t num_threads,
                 uint32_t min_echos = 1,
                 uint32_t reply_timeout = 100);

    /// @brief Destructor.
    virtual ~PingCheckMgr();

    /// @brief Configure the PingCheckMgr.
    ///
    /// @param params map containing the hook library parameters.
    /// @throw BadValue and similar exceptions on error.
    void configure(data::ConstElementPtr params);

    /// @brief Update the cache of subnet ping check configurations.
    ///
    /// Iterates over the subnets in the given server configuration,
    /// and caches their ping-check configuration.
    ///
    /// @param server_config Server configuration containing the
    /// configured subnets to process.
    void updateSubnetConfig(dhcp::SrvConfigPtr server_config);

    /// @brief Creates a ping channel instance.
    ///
    /// @param io_service IOService that will drive the channel.
    ///
    /// @return pointer to the newly created channel.
    virtual PingChannelPtr createChannel(asiolink::IOServicePtr io_service);

    /// @brief Initiates a ping check for a given lease and its associated
    /// DHCPDISCOVER packet.
    ///
    /// Adds a context to the store and posts a call to @c PingChannel::startSend().
    ///
    /// @param lease lease whose address needs to be ping checked.
    /// @param query parked DHCPDISCOVER associated with the lease.
    /// @param parking_lot parking lot in which query is parked.  If empty,
    /// parking is assumed to not be employed.
    /// @param config configuration parameters to employ.
    void startPing(dhcp::Lease4Ptr& lease, dhcp::Pkt4Ptr& query,
                   hooks::ParkingLotHandlePtr& parking_lot,
                   const PingCheckConfigPtr& config);

    /// @brief Initiates a ping check for a given lease and its associated
    /// DHCPDISCOVER packet.
    ///
    /// Convenience method used in unit tests which uses global
    /// configuration parameters only.
    ///
    /// @param lease lease whose address needs to be ping checked.
    /// @param query parked DHCPDISCOVER associated with the lease.
    /// @param parking_lot parking lot in which query is parked.  If empty,
    /// parking is assumed to not be employed.
    void startPing(dhcp::Lease4Ptr& lease, dhcp::Pkt4Ptr& query,
                   hooks::ParkingLotHandlePtr& parking_lot);

    /// @brief Callback passed to PingChannel to use to retrieve the next
    /// address to check.
    ///
    /// Fetches the context which has been in the WAITING_TO_SEND state the
    /// longest and returns its lease address.
    ///
    /// @param[out] next upon return it will contain the next target address.
    /// Contents are only meaningful if the function returns true.
    ///
    /// @return True another target address exists, false otherwise.
    virtual bool nextToSend(asiolink::IOAddress& next);

    /// @brief Callback passed to PingChannel to invoke when an ECHO REQUEST
    /// send has completed.
    ///
    /// If the send completed successfully we'll transition the context to
    /// WAITING_FOR_REPLY, update the context in the store, and the update
    /// next expiration.
    ///
    /// If the send failed, this implies that a recoverable error occurred, such
    /// as a interface being down and thus, there is currently no way to send
    /// the ping to the target network. We'll treat this the same as an ICMP
    /// TARGET_UNREACHABLE and release the OFFER by calling @c finishFree().
    ///
    /// @param echo ICMP echo message that as sent.
    /// @param send_failed True if the send completed with a non-fatal error,
    /// false otherwise.
    virtual void sendCompleted(const ICMPMsgPtr& echo, bool send_failed);

    /// @brief Callback passed to PingChannel to invoke when an ICMP
    /// reply has been received.
    ///
    /// If the reply type is an ECHO REQUEST, it is passed to
    /// handleEchoRequest(), if it is an UNREACHABLE message it
    /// is passed to handleTargetUnreachable(), any other message
    /// type is dropped on the floor and the function returns.
    /// Upon handler completion, it calls setNextExpiration() to
    /// update the expiration timer.
    ///
    /// @param reply ICMP message that was received.
    virtual void replyReceived(const ICMPMsgPtr& reply);

    /// @brief Process an ECHO REPLY message.
    ///
    /// @param  echo_reply ICMP ECHO REPLY message to process.
    void handleEchoReply(const ICMPMsgPtr& echo_reply);

    /// @brief Process an UNREACHABLE message.
    ///
    /// @param unreachable ICMP UNREACHABLE message to process.
    void handleTargetUnreachable(const ICMPMsgPtr& unreachable);

    /// @brief Processes a context whose address has been deemed free to use.
    ///
    /// -# Moves the context to TARGET_FREE state
    /// -# Updates the context in the store
    /// -# Unparks the query which will release the DHCPOFFER to the client
    /// -# Invokes the target free callback (do we still need this?)
    /// -# Deletes the store from the context
    ///
    /// @param context context to process.
    void finishFree(const PingContextPtr& context);

    /// @brief Position a context to do another ping test.
    ///
    /// -# Moves the context to WAITING_SEND_STATE
    /// -# Updates the context in the store
    ///
    /// @param context context to process.
    void doNextEcho(const PingContextPtr& context);

    /// @brief Callback passed to PingChannel to invoke when it shuts down.
    ///
    /// Logs the shutdown and then posts a call to @c stopService() to the
    /// main IOService.
    virtual void channelShutdown();

    /// @brief Performs expiration processing for contexts whose WAITING_FOR_REPLY
    /// states expired prior to a given point in time.
    ///
    /// expired_pings = store_->getExpiredSince(since)
    /// for context : expired_pings {
    ///    unpark context->getQuery()
    ///    store_->deleteContext(context)
    /// }
    ///
    /// @param since point in time to select against. Defaults to current time.
    /// @return number of contexts scheduled for another ping, zero if none.
    virtual size_t processExpiredSince(const TimeStamp& since = PingContext::now());

    /// @brief Fetches the time at which expiration timer will next expire.
    ///
    /// @return TimeStamp containing the next expiration time.
    TimeStamp getNextExpiry();

    /// @brief Updates the expiration timer (thread safe).
    ///
    ///  PingContextPtr next = pings->getExpiresNext()
    ///  if next
    ///      reschedule expiration timer for next->getNextExpiry();
    ///  else
    ///      cancel expiration timer
    virtual void setNextExpiration();

    /// @brief Updates the expiration timer.
    ///
    ///  PingContextPtr next = pings->getExpiresNext()
    ///  if next
    ///      reschedule expiration timer for next->getNextExpiry();
    ///  else
    ///      cancel expiration timer
    virtual void setNextExpirationInternal();

    /// @brief Cancels the expiration timer (thread safe).
    void cancelExpirationTimer();

    /// @brief Cancels the expiration timer.
    void cancelExpirationTimerInternal();

    /// @brief Callback passed to expiration timer to invoke on timeout.
    virtual void expirationTimedOut();

    /// @brief Determines whether or not a lease should be ping checked.
    ///
    /// Employs the following logic to determine if a ping-check should
    /// be conducted:
    ///
    /// If there's a previous lease that belongs to this client and
    /// it was touched by the client less than ping-cltt-secs ago,
    /// then send the offer to the client without ping checking.
    ///
    /// Otherwise a ping-check is called for, leave the query parked.
    ///
    /// @param lease prospective lease to check.
    /// @param query DHCPDISCOVER associated with the lease.
    /// @param old_lease pre-existing lease for this client (if one).
    /// @param config configuration parameters to employ.
    ///
    /// @return CalloutNextStep indicating what should happen next:
    /// - status == PARK - ping check it
    /// - status == CONTINUE - check not needed, release DHCPOFFER to client
    /// - status == DROP - duplicate check, drop the duplicate DHCPOFFER
    virtual hooks::CalloutHandle::CalloutNextStep shouldPing(dhcp::Lease4Ptr& lease,
                                                             dhcp::Pkt4Ptr& query,
                                                             dhcp::Lease4Ptr& old_lease,
                                                             const PingCheckConfigPtr& config);

    /// @brief Check if the current thread can perform thread pool state
    /// transition.
    ///
    /// @throw MultiThreadingInvalidOperation if the state transition is done on
    /// any of the worker threads.
    void checkPermissions();

    /// @brief Performs a deferred start by posting an invocation of @c start()
    /// to the given IOService.
    ///
    /// @param network_state pointer to server's networks state object.
    void startService(dhcp::NetworkStatePtr network_state);

    /// @brief Shuts down the manager's channel, flushes the store.
    ///
    /// This function gracefully winds down operation:
    ///
    /// 1. Pauses the thread pool.
    /// 2. Flushes the context store, either finishing all contexts as free
    /// or just dropping them from parking, depending on finish_free parameter.
    /// 3. Stop the thread pool, shutdown the channel.
    ///
    /// @param finish_free if true finishFree() will be invoke on all remaining
    /// contexts in the store, otherwise their queries are simply dropped from
    /// the parking lot.
    void stopService(bool finish_free = false);

    /// @brief Start PingChannel operations.
    ///
    /// Will start multi-threaded if core MT is enabled, or calls
    /// @c startSingleThreaded() if core MT is disabled.  Creates
    /// a thread pool with its own IOService, uses that IOService
    /// when creating the channel.
    void start();

    /// @brief Start single-threaded PingChannel operations.
    ///
    /// Does not create a thread pool.  Uses main thread's IOService
    /// when creating the channel.
    void startSingleThreaded();

    /// @brief Pause PingChannel operations.
    ///
    /// In multi-threaded mode this pauses the thread pool threads, in
    /// single-threaded mode it does nothing.
    void pause();

    /// @brief Resume PingChannel operations.
    ///
    /// In multi-threaded mode this resumes the thread pool threads, in
    /// single-threaded mode it does nothing.
    void resume();

    /// @brief Flushes the ping context store.
    ///
    /// This function iterates over the contexts in the store and then
    /// either invokes finishFree() or drops their queries from parking
    /// depending upon finish_free parameter.  It assumes the operations
    /// have ceased (i.e. thread pool is not running).
    ///
    /// @param finish_free if true finishFree() will be invoke on all remaining
    /// contexts in the store, otherwise their queries are simply dropped from
    /// the parking lot.
    void flush(bool finish_free = false);

    /// @brief Stop PingChannel operations.
    void stop();

    /// @brief Indicates if the thread pool is running.
    ///
    /// @return True if the thread pool exists and it is in the RUNNING state in
    /// multi-threaded mode, true if the channel exists and is open in single-threaded
    /// mode, false otherwise.
    bool isRunning();

    /// @brief Indicates if the thread pool is stopped.
    ///
    /// @return True if the thread pool does not exist or it is in the STOPPED
    /// state in multi-threaded mode, true if the channel does not exist in
    /// single-threaded mode, false otherwise.
    bool isStopped();

    /// @brief Indicates if the thread pool is paused.
    ///
    /// @return True if the thread pool exists and it is in the PAUSED state,
    /// false otherwise.  Always returns false in single-threaded mode.
    bool isPaused();

    /// @brief Checks if operations are currently suspended due to NetworkState.
    ///
    /// Thread-safe wrapper around checkSuspendedInternal().
    ///
    /// @return True if operations are suspended, false otherwise.
    bool checkSuspended();

    /// @brief Checks if operations are currently suspended due to NetworkState.
    ///
    /// If DHCP service is enabled, operations are not suspended and the function
    /// returns false.  Otherwise operations, if not already suspended, are suspended
    /// by flushing the PingContext store and the function returns true.  The queries
    /// for flushed contexts are dropped from parking and thus their offers discarded.
    ///
    /// @return True if operations are suspended, false otherwise.
    bool checkSuspendedInternal();

    /// @brief Fetches the current, global configuration parameters.
    ///
    /// @return PingCheckConfig reference containing the current configuration.
    const PingCheckConfigPtr getGlobalConfig() const;

    /// @brief Fetches the current, scoped configuration parameters.
    ///
    /// @param lease lease for which the parameters are desired.
    ///
    /// @return PingCheckConfig reference containing the current configuration.
    const PingCheckConfigPtr getScopedConfig(dhcp::Lease4Ptr& lease);

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

protected:

    /// @brief The hook I/O service.
    isc::asiolink::IOServicePtr io_service_;

    /// @brief Thread pool used when running multi-threaded.
    asiolink::IoServiceThreadPoolPtr thread_pool_;

    /// @brief In-memory store of PingContexts.
    PingContextStorePtr store_;

    /// @brief Channel that conducts ICMP messaging.
    PingChannelPtr channel_;

    /// @brief Warehouses parsed global and subnet configuration.
    ConfigCachePtr config_cache_;

    /// @brief Tracks whether or not the server is processing DHCP packets.
    dhcp::NetworkStatePtr network_state_;

    /// @brief TimeStamp of the next expiration event.
    TimeStamp next_expiry_;

    /// @brief Timer which tracks the next expiration event.
    asiolink::IntervalTimerPtr expiration_timer_;

    /// @brief The mutex used to protect internal state.
    const boost::scoped_ptr<std::mutex> mutex_;

    /// @brief Indicates whether or not operations have been suspended.
    bool suspended_;
};

/// @brief Defines a shared pointer to a PingCheckMgr.
typedef boost::shared_ptr<PingCheckMgr> PingCheckMgrPtr;

} // end of namespace ping_check
} // end of namespace isc

#endif
