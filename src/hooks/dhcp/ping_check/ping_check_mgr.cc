// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <ping_check_mgr.h>
#include <ping_check_log.h>
#include <dhcpsrv/cfgmgr.h>
#include <hooks/hooks_manager.h>
#include <util/multi_threading_mgr.h>
#include <util/chrono_time_utils.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::util;
using namespace std;
using namespace std::chrono;

namespace ph = std::placeholders;

namespace isc {
namespace ping_check {

PingCheckMgr::PingCheckMgr()
    : io_service_(new IOService()), thread_pool_(),
      store_(new PingContextStore()),
      channel_(),
      config_cache_(new ConfigCache()),
      mutex_(new mutex()),
      suspended_(false) {
}

PingCheckMgr::PingCheckMgr(uint32_t num_threads,
                           uint32_t min_echos,
                           uint32_t reply_timeout)
    : io_service_(new IOService()), thread_pool_(),
      store_(new PingContextStore()),
      channel_(),
      config_cache_(new ConfigCache()),
      mutex_(new mutex()),
      suspended_(false) {
    PingCheckConfigPtr config(new PingCheckConfig());
    config->setMinPingRequests(min_echos);
    config->setReplyTimeout(reply_timeout);
    config->setPingChannelThreads(num_threads);
    config_cache_->setGlobalConfig(config);
}

PingCheckMgr::~PingCheckMgr() {
    stop();
}

void
PingCheckMgr::configure(ConstElementPtr params) {
    if (!params) {
        isc_throw(dhcp::DhcpConfigError, "params must not be null");
        return;
    }

    if (params->getType() != Element::map) {
        isc_throw(dhcp::DhcpConfigError, "params must be an Element::map");
        return;
    }

    PingCheckConfigPtr config(new PingCheckConfig());
    config->parse(params);
    config_cache_->setGlobalConfig(config);
}

void
PingCheckMgr::updateSubnetConfig(SrvConfigPtr server_config) {
    // Iterate over subnets and cache configurations for each.
    ConfigCachePtr local_cache(new ConfigCache());
    local_cache->setGlobalConfig(config_cache_->getGlobalConfig());
    auto const& subnets = server_config->getCfgSubnets4()->getAll();
    for (auto const& subnet : (*subnets)) {
        auto user_context = subnet->getContext();
        local_cache->parseAndCacheConfig(subnet->getID(), user_context);
    }

    // No errors above, replace the existing cache.
    config_cache_ = local_cache;
}

const PingCheckConfigPtr
PingCheckMgr::getGlobalConfig() const {
    return (config_cache_->getGlobalConfig());
}

const PingCheckConfigPtr
PingCheckMgr::getScopedConfig(Lease4Ptr& lease) {
    if (!lease) {
        // This really shouldn't happen.
        isc_throw(InvalidOperation, "PingCheckConfig::getScopedConfig() - lease cannot be empty");
    }

    auto subnet_id = lease->subnet_id_;

    // If the cache is stale, update it.  We do this to catch subnets that have been updated
    // via subnet_cmds.
    auto server_config = CfgMgr::instance().getCurrentCfg();
    auto const& subnet = server_config->getCfgSubnets4()->getBySubnetId(subnet_id);
    if (!subnet) {
        // This really shouldn't happen.
        isc_throw(InvalidOperation, "PingCheckMgr::getScopedConfig() - "
                  "no subnet for id: " << subnet_id
                  << ", for lease address: " << lease->addr_);
    }

    // If cache is stale flush it and we'll lazy init subnets as we see them.
    if (subnet->getModificationTime() > config_cache_->getLastFlushTime()) {
        config_cache_->flush();
    }

    // If we don't find an entry for this subnet then we haven't seen it
    // before so parse and cache it.  If the subnet doesn't specify ping-check
    // we cache an empty entry.
    PingCheckConfigPtr config;
    if (!config_cache_->findConfig(subnet_id, config)) {
        auto user_context = subnet->getContext();
        try {
            config = config_cache_->parseAndCacheConfig(subnet_id, user_context);
        } catch (const std::exception& ex) {
            // We emit and error and then cache an empty entry. This causes us
            // to log the error once and then default to global settings afterward.
            // This avoids us relentlessly logging and failing.  Remember this
            // is happening because a subnet was updated with an invalid context via
            // subnet-cmd.
            LOG_ERROR(ping_check_logger, PING_CHECK_MGR_SUBNET_CONFIG_FAILED)
                      .arg(subnet_id)
                      .arg(ex.what());
            config_cache_->cacheConfig(subnet_id, config);
        }
    }

    // Return subnet's ping-check config if it specified one, otherwise
    // return the global config.
    return (config ? config : config_cache_->getGlobalConfig());
}

void
PingCheckMgr::startPing(dhcp::Lease4Ptr& lease, dhcp::Pkt4Ptr& query, hooks::ParkingLotHandlePtr& parking_lot,
                        const PingCheckConfigPtr& config) {
    if (checkSuspended()) {
        // Server should not be submitting requests.
        isc_throw(InvalidOperation, "PingCheckMgr::startPing() - DHCP service is suspended!");
    }

    if (!channel_ || !channel_->isOpen()) {
        isc_throw(InvalidOperation, "PingCheckMgr::startPing() - channel isn't open");
    }

    LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_BASIC,
              PING_CHECK_MGR_START_PING_CHECK)
              .arg(lease->addr_)
              .arg(query->getLabel());

    // Adds a context to the store
    store_->addContext(lease, query, config->getMinPingRequests(),
                       config->getReplyTimeout(), parking_lot);

    // Posts a call to channel's startSend() and startRead().  This will kick-start perpetual
    // write and read cycles if they are not already running.
    if (channel_) {
        channel_->startSend();
        channel_->startRead();
    }
}

void
PingCheckMgr::startPing(dhcp::Lease4Ptr& lease, dhcp::Pkt4Ptr& query, hooks::ParkingLotHandlePtr& parking_lot) {
    startPing(lease, query, parking_lot, getGlobalConfig());
}

bool
PingCheckMgr::nextToSend(IOAddress& next) {
    if (checkSuspended()) {
        return (false);
    }

    PingContextPtr context = store_->getNextToSend();
    if (!context) {
        return (false);
    }

    next = context->getTarget();
    // Transition to sending.
    context->setState(PingContext::SENDING);
    store_->updateContext(context);

    return (true);
}

void
PingCheckMgr::sendCompleted(const ICMPMsgPtr& echo, bool send_failed) {
    if (checkSuspended()) {
        return;
    }

    try {
        if (!echo) {
            isc_throw(BadValue, "PingCheckMgr::sendCompleted() - echo is empty");
        }

        if (echo->getType() != ICMPMsg::ECHO_REQUEST) {
            isc_throw(BadValue, "PingCheckMgr::sendCompleted() - message type: "
                      << echo->getType() << " is not an ECHO_REQUEST");
        }

        // Update the context associated with this ECHO_REQUEST.
        PingContextPtr context = store_->getContextByAddress(echo->getDestination());
        if (!context) {
            isc_throw(Unexpected, "PingCheckMgr::sendCompleted() "
                      " no context found for: " << echo->getDestination());
        }

        if (send_failed) {
            // Recoverable error occurred which means we can't get to the target's
            // network (interface down?).  Treat this the same as TARGET UNREACHABLE.
            finishFree(context);
        } else {
            // Transition the context to WAITING_FOR_REPLY.
            context->beginWaitingForReply();
            store_->updateContext(context);
        }

        // Update the expiration timer if necessary.
        setNextExpiration();
    } catch (const std::exception& ex) {
        LOG_ERROR(ping_check_logger, PING_CHECK_MGR_SEND_COMPLETED_ERROR)
            .arg(ex.what());
    }
}

void
PingCheckMgr::replyReceived(const ICMPMsgPtr& reply) {
    if (checkSuspended()) {
        return;
    }

    try {
        if (!reply) {
            isc_throw(BadValue, "PingCheckMgr::replyReceived() - echo is empty");
        }

        switch (reply->getType()) {
        case ICMPMsg::ECHO_REPLY:
            handleEchoReply(reply);
            break;
        case ICMPMsg::TARGET_UNREACHABLE:
            // Extract embedded ECHO REQUEST
            handleTargetUnreachable(reply);
            break;
        default:
            // Ignore anything else.
            return;
        }

        setNextExpiration();
    } catch (const std::exception& ex) {
        LOG_ERROR(ping_check_logger, PING_CHECK_MGR_REPLY_RECEIVED_ERROR)
            .arg(ex.what());
    }
}

void
PingCheckMgr::handleEchoReply(const ICMPMsgPtr& echo_reply) {
    // Update the context associated with this ECHO_REQUEST.
    PingContextPtr context = store_->getContextByAddress(echo_reply->getSource());
    if (!context) {
        LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_DETAIL,
                  PING_CHECK_MGR_RECEIVED_UNEXPECTED_ECHO_REPLY)
                  .arg(echo_reply->getSource())
                  .arg(echo_reply->getId())
                  .arg(echo_reply->getSequence());
        return;
    }

    LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_BASIC,
              PING_CHECK_MGR_RECEIVED_ECHO_REPLY)
        .arg(echo_reply->getSource())
        .arg(echo_reply->getId())
        .arg(echo_reply->getSequence());

    context->setState(PingContext::TARGET_IN_USE);
    store_->updateContext(context);

    // If parking is employed, unpark the query from the parking lot,
    // and set the offer_address_in_use argument in the callout handle
    // to true, indicating to the server that the lease should be declined
    // and the DHCPOFFER discarded.
    auto parking_lot = context->getParkingLot();
    if (parking_lot) {
        auto query = context->getQuery();
        auto callout_handle = query->getCalloutHandle();
        callout_handle->setArgument("offer_address_in_use", true);
        parking_lot->unpark(query);
    }

    // Remove the context from the store.
    store_->deleteContext(context);
}

void
PingCheckMgr::handleTargetUnreachable(const ICMPMsgPtr& unreachable) {
    // Unpack the embedded ECHO REQUEST.
    ICMPMsgPtr embedded_echo;
    auto payload = unreachable->getPayload();
    embedded_echo = ICMPMsg::unpack(payload.data(), payload.size());

    // Fetch the context associated with the ECHO_REQUEST.
    PingContextPtr context = store_->getContextByAddress(embedded_echo->getDestination());
    if (!context) {
        LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_DETAIL,
                  PING_CHECK_MGR_RECEIVED_UNEXPECTED_UNREACHABLE_MSG)
            .arg(embedded_echo->getDestination())
            .arg(embedded_echo->getId())
            .arg(embedded_echo->getSequence());
        return;
    }

    LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_DETAIL,
              PING_CHECK_MGR_RECEIVED_UNREACHABLE_MSG)
        .arg(embedded_echo->getDestination())
        .arg(embedded_echo->getId())
        .arg(embedded_echo->getSequence());

    // Render the address usable.
    finishFree(context);
}

void
PingCheckMgr::finishFree(const PingContextPtr& context) {
    context->setState(PingContext::TARGET_FREE);
    store_->updateContext(context);

    LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_BASIC,
              PING_CHECK_MGR_LEASE_FREE_TO_USE)
        .arg(context->getTarget())
        .arg(context->getQuery()->getLabel());

    // If parking is employed, unpark the query from the parking lot,
    // and set the offer_address_in_use argument in the callout handle
    // to false, indicating to the server that the lease is available
    // and the DHCPOFFER should be sent to the client.
    auto parking_lot = context->getParkingLot();
    if (parking_lot) {
        auto query = context->getQuery();
        auto callout_handle = query->getCalloutHandle();
        callout_handle->setArgument("offer_address_in_use", false);
        parking_lot->unpark(context->getQuery());
    }

    // Remove the context from the store.
    store_->deleteContext(context);
}

void
PingCheckMgr::channelShutdown() {
    LOG_ERROR(ping_check_logger, PING_CHECK_MGR_CHANNEL_DOWN);
    if (io_service_) {
        // As this is a callback that may be invoked by a channel
        // thread we post a call to stopService() rather than call
        // it directly.
        io_service_->post([&]() { stopService(true); });
    }
}

size_t
PingCheckMgr::processExpiredSince(const TimeStamp& since /* = PingContext::now() */) {
    auto expired_pings = store_->getExpiredSince(since);
    size_t more_pings = 0;
    for (auto const& context : *(expired_pings)) {
        LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_DETAIL,
                  PING_CHECK_MGR_REPLY_TIMEOUT_EXPIRED)
                  .arg(context->getTarget())
                  .arg(context->getEchosSent())
                  .arg(context->getMinEchos())
                  .arg(context->getReplyTimeout());

        if (context->getEchosSent() < context->getMinEchos()) {
            doNextEcho(context);
            ++more_pings;
        } else {
            finishFree(context);
        }
    }

    return (more_pings);
}

void
PingCheckMgr::doNextEcho(const PingContextPtr& context) {
    // Position to do another ping by re-entering WAITING_TO_SEND
    LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_DETAIL,
              PING_CHECK_MGR_NEXT_ECHO_SCHEDULED)
              .arg(context->getTarget())
              .arg(context->getEchosSent() + 1)
              .arg(context->getMinEchos());

    context->beginWaitingToSend();
    store_->updateContext(context);
}

TimeStamp
PingCheckMgr::getNextExpiry() {
    MultiThreadingLock lock(*mutex_);
    return (next_expiry_);
}

void
PingCheckMgr::setNextExpiration() {
    MultiThreadingLock lock(*mutex_);
    if (checkSuspendedInternal()) {
        return;
    }

    setNextExpirationInternal();
}

void
PingCheckMgr::setNextExpirationInternal() {
    // Find the context that expires soonest.
    PingContextPtr context = store_->getExpiresNext();
    if (context) {
        // if the context's expiry is sooner than current expiry
        // reschedule expiration timer
        if ((next_expiry_ == PingContext::EMPTY_TIME()) ||
            (context->getNextExpiry() < next_expiry_)) {
            auto now = PingContext::now();
            auto timeout = duration_cast<milliseconds>(context->getNextExpiry() - now);
            /// @todo For now we'll impose a 2 ms minimum to avoid thrashing the timer.
            timeout = (timeout > milliseconds(2) ? timeout : milliseconds(2));
            next_expiry_ = now + timeout;
            expiration_timer_->setup(std::bind(&PingCheckMgr::expirationTimedOut,
                                     shared_from_this()),
                                     timeout.count(), IntervalTimer::ONE_SHOT);
        }
    } else {
        // Nothing waiting to expire. Cancel the timer.
        cancelExpirationTimerInternal();
    }
}

void
PingCheckMgr::cancelExpirationTimer() {
    MultiThreadingLock lock(*mutex_);
    cancelExpirationTimerInternal();
}

void
PingCheckMgr::cancelExpirationTimerInternal() {
    if (expiration_timer_) {
        expiration_timer_->cancel();
        next_expiry_ = PingContext::EMPTY_TIME();
    }
}

void
PingCheckMgr::expirationTimedOut() {
    MultiThreadingLock lock(*mutex_);
    if (checkSuspendedInternal()) {
        return;
    }

    // Process everything that has expired since current time.
    auto more_pings = processExpiredSince();

    // Update the expiration timer.
    next_expiry_ = PingContext::EMPTY_TIME();
    setNextExpirationInternal();

    // In the event there was nothing left to process when timed out,
    // poke the channel to make sure things are moving.
    if (more_pings && channel_) {
        channel_->startSend();
        channel_->startRead();
    }
}

CalloutHandle::CalloutNextStep
PingCheckMgr::shouldPing(Lease4Ptr& lease, Pkt4Ptr& query,
                         Lease4Ptr& old_lease,
                         const PingCheckConfigPtr& config) {

    // If ping-check is disabled or the channel isn't open,
    // drop the query from parking and release the offer to the client.
    if (!config->getEnablePingCheck() || !channel_ || !channel_->isOpen()) {
        return (CalloutHandle::CalloutNextStep::NEXT_STEP_CONTINUE);
    }

    // If we're already running check on this address then drop the
    // query from parking and discard the offer.
    if (store_->getContextByAddress(lease->addr_)) {
        LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_BASIC,
                  PING_CHECK_DUPLICATE_CHECK)
                  .arg(lease->addr_)
                  .arg(query->getLabel());
        return (CalloutHandle::CalloutNextStep::NEXT_STEP_DROP);
    }

    // If there's a previous lease that belongs to this client and
    // it was touched by the client less than ping-cltt-secs ago then
    // no check is needed.  Drop the query from parking and release the
    // offer to the client,
    if (old_lease && (old_lease->addr_ == lease->addr_)) {
        if (old_lease->belongsToClient(lease->hwaddr_, lease->client_id_)) {
            auto now = time(0);
            if ((now - old_lease->cltt_) < config->getPingClttSecs()) {
                return (CalloutHandle::CalloutNextStep::NEXT_STEP_CONTINUE);
            }
        }
    }

    // Leave it parked and do the ping check.
    return (CalloutHandle::CalloutNextStep::NEXT_STEP_PARK);
}

void
PingCheckMgr::startService(NetworkStatePtr network_state) {
    network_state_ = network_state;
    io_service_->post([&]() { start(); });
}

bool
PingCheckMgr::checkSuspended() {
    MultiThreadingLock lock(*mutex_);
    return (checkSuspendedInternal());
}

bool
PingCheckMgr::checkSuspendedInternal() {
    if (!network_state_ || network_state_->isServiceEnabled()) {
        suspended_ = false;
    } else {
        if (!suspended_) {
            suspended_ = true;

            // Flush the context store, dropping parked queries.
            flush(false);
        }
    }

    return (suspended_);
}

void
PingCheckMgr::stopService(bool finish_free) {
    // Pause the thread pool while we flush the store.
    pause();

    // Flush the context store.  If finish_free is true
    // the flush will treat the remaining context lease
    // addresses as free to use and unpark them. This
    // will cause the server to send out the associated
    // OFFERs.  If it's false we just drop them from
    // the parking lot.
    flush(finish_free);

    // Stop the thread pool, destroy the channel and the like.
    stop();
}

void
PingCheckMgr::start() {
    if (MultiThreadingMgr::instance().isTestMode()) {
        return;
    }
    if (!MultiThreadingMgr::instance().getMode()) {
        startSingleThreaded();
        return;
    }

    // We must be in multi-threading mode.
    // Add critical section callbacks.
    MultiThreadingMgr::instance().addCriticalSectionCallbacks("PING_CHECK",
        std::bind(&PingCheckMgr::checkPermissions, this),
        std::bind(&PingCheckMgr::pause, this),
        std::bind(&PingCheckMgr::resume, this));

    // Punt if we're already started.
    if (thread_pool_ && thread_pool_->isStopped()) {
        isc_throw(InvalidOperation, "PingCheckMgr already started!");
    }

    try {
        auto config = config_cache_->getGlobalConfig();
        auto use_threads = (config->getPingChannelThreads() ? config->getPingChannelThreads()
                            : MultiThreadingMgr::instance().getThreadPoolSize());
        thread_pool_.reset(new IoServiceThreadPool(IOServicePtr(), use_threads, true));
        IOServicePtr pool_ios = thread_pool_->getIOService();
        channel_ = createChannel(pool_ios);
        channel_->open();
        expiration_timer_.reset(new IntervalTimer(pool_ios));
        thread_pool_->run();
        LOG_INFO(ping_check_logger, PING_CHECK_MGR_STARTED)
                .arg(use_threads);
    } catch (const std::exception& ex) {
        channel_.reset();
        thread_pool_.reset();
        isc_throw(Unexpected, "PingCheckMgr::start failed:" << ex.what());
    }
}

void
PingCheckMgr::startSingleThreaded() {
    try {
        auto config = config_cache_->getGlobalConfig();
        channel_ = createChannel(io_service_);
        channel_->open();
        expiration_timer_.reset(new IntervalTimer(io_service_));
        LOG_INFO(ping_check_logger, PING_CHECK_MGR_STARTED_SINGLE_THREADED);
    } catch (const std::exception& ex) {
        channel_.reset();
        isc_throw(Unexpected, "PingCheckMgr::startSingleThreaded() failed:" << ex.what());
    }
}

PingChannelPtr
PingCheckMgr::createChannel(IOServicePtr io_service) {
    return (PingChannelPtr(new PingChannel(io_service,
                                           std::bind(&PingCheckMgr::nextToSend,
                                                     this, ph::_1),
                                           std::bind(&PingCheckMgr::sendCompleted,
                                                     this, ph::_1, ph::_2),
                                           std::bind(&PingCheckMgr::replyReceived,
                                                     this, ph::_1),
                                           std::bind(&PingCheckMgr::channelShutdown,
                                                     this))));
}

void
PingCheckMgr::checkPermissions() {
    // Since this function is used as CS callback all exceptions must be
    // suppressed, unlikely though they may be.
    try {
        if (thread_pool_) {
            thread_pool_->checkPausePermissions();
        }
    } catch (const isc::MultiThreadingInvalidOperation& ex) {
        LOG_ERROR(ping_check_logger, PING_CHECK_PAUSE_ILLEGAL)
                  .arg(ex.what());
        // The exception needs to be propagated to the caller of the
        // @ref MultiThreadingCriticalSection constructor.
        throw;
    } catch (const std::exception& ex) {
        LOG_ERROR(ping_check_logger, PING_CHECK_PAUSE_PERMISSIONS_FAILED)
                  .arg(ex.what());
    }
}

void
PingCheckMgr::pause() {
    if (!MultiThreadingMgr::instance().getMode()) {
        return;
    }

    // Since this function is used as CS callback all exceptions must be
    // suppressed, unlikely though they may be.
    try {
        // Cancel the expiration timer.
        cancelExpirationTimer();

        // Pause the thread pool.
        if (thread_pool_) {
            thread_pool_->pause();
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(ping_check_logger, PING_CHECK_PAUSE_FAILED)
                  .arg(ex.what());
    }
}

void
PingCheckMgr::resume() {
    if (!MultiThreadingMgr::instance().getMode()) {
        return;
    }

    // Since this function is used as CS callback all exceptions must be
    // suppressed, unlikely though they may be.
    try {
        if (thread_pool_) {
            thread_pool_->run();
        }

        // Restore the expiration timer.
        setNextExpiration();
    } catch (const std::exception& ex) {
        LOG_ERROR(ping_check_logger, PING_CHECK_RESUME_FAILED)
                  .arg(ex.what());
    }
}

void
PingCheckMgr::stop() {
    LOG_DEBUG(ping_check_logger, isc::log::DBGLVL_TRACE_BASIC, PING_CHECK_MGR_STOPPING);

    // Cancel the expiration timer.
    cancelExpirationTimer();

    if (channel_) {
        channel_->close();
    }

    if (thread_pool_) {
        // Remove critical section callbacks.
        MultiThreadingMgr::instance().removeCriticalSectionCallbacks("PING_CHECK");

        // Stop the thread pool.
        thread_pool_->stop();

        thread_pool_->getIOService()->stopAndPoll();

        // Ditch the thread_pool
        thread_pool_.reset();
    }
    // Ditch the timer. It must be destroyed before the thread pool because in
    // MT it holds a reference to the pool's IOService.
    expiration_timer_.reset();

    // Get rid of the channel.
    channel_.reset();

    if (io_service_) {
        io_service_->stopAndPoll();
    }

    LOG_INFO(ping_check_logger, PING_CHECK_MGR_STOPPED);
}

bool
PingCheckMgr::isRunning() {
    // In ST mode, running is an open channel.
    if (!MultiThreadingMgr::instance().getMode()) {
        return (channel_ && channel_->isOpen());
    }

    if (thread_pool_) {
        return (thread_pool_->isRunning());
    }

    return (false);
}

bool
PingCheckMgr::isStopped() {
    // In ST mode, stopped equates to no channel.
    if (!MultiThreadingMgr::instance().getMode()) {
        return (!channel_);
    }

    if (thread_pool_) {
        return (thread_pool_->isStopped());
    }

    return (true);
}

bool
PingCheckMgr::isPaused() {
    if (thread_pool_) {
        return (thread_pool_->isPaused());
    }

    return (false);
}

void
PingCheckMgr::flush(bool finish_free /* = false */) {
    if (!store_) {
        return;
    }

    // Fetch them all.
    auto contexts = store_->getAll();
    for (auto const& context : *contexts) {
        if (finish_free) {
            finishFree(context);
        } else {
            auto parking_lot = context->getParkingLot();
            if (parking_lot) {
                parking_lot->drop(context->getQuery());
            }
        }
    }

    store_->clear();
}

} // end of namespace ping_check
} // end of namespace isc
