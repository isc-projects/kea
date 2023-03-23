// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_address.h>
#include <asiolink/io_error.h>
#include <asiolink/io_service.h>
#include <mt_tcp_listener_mgr.h>
#include <tcp_log.h>
#include <util/multi_threading_mgr.h>

#include <boost/pointer_cast.hpp>

using namespace isc::asiolink;
using namespace isc::tcp;
using namespace isc::util;

namespace isc {
namespace tcp {

MtTcpListenerMgr::MtTcpListenerMgr(TcpListenerFactory listener_factory,
                                   const IOAddress& address,
                                   const uint16_t port,
                                   const uint16_t thread_pool_size /* = 1 */,
                                   TlsContextPtr context /* = () */,
                                   TcpConnectionFilterCallback connection_filter /* = 0 */)
    : listener_factory_(listener_factory),
      address_(address), port_(port), thread_io_service_(), tcp_listener_(),
      thread_pool_size_(thread_pool_size), thread_pool_(),
      tls_context_(context), connection_filter_(connection_filter),
      idle_timeout_(TCP_IDLE_CONNECTION_TIMEOUT) {
}

MtTcpListenerMgr::~MtTcpListenerMgr() {
    stop();
}

void
MtTcpListenerMgr::start() {
    // We must be in multi-threading mode.
    if (!MultiThreadingMgr::instance().getMode()) {
        isc_throw(InvalidOperation, "MtTcpListenerMgr cannot be started"
                  " when multi-threading is disabled");
    }

    // Punt if we're already started.
    if (!isStopped()) {
        isc_throw(InvalidOperation, "MtTcpListenerMgr already started!");
    }

    try {
        // Create a new IOService.
        thread_io_service_.reset(new IOService());

        // Create a new TCPListener derivation using the factory.
        tcp_listener_ = listener_factory_(*thread_io_service_,
                                          address_,
                                          port_,
                                          tls_context_,
                                          idle_timeout_,
                                          connection_filter_);

        // Instruct the HTTP listener to actually open socket, install
        // callback and start listening.
        tcp_listener_->start();

        // Create the thread pool with immediate start.
        thread_pool_.reset(new IoServiceThreadPool(thread_io_service_, thread_pool_size_));

        // OK, seems like we're good to go.
        LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC, MT_TCP_LISTENER_MGR_STARTED)
            .arg(thread_pool_size_)
            .arg(address_)
            .arg(port_)
            .arg(tls_context_ ? "true" : "false");
    } catch (const std::exception& ex) {
        thread_io_service_.reset();
        tcp_listener_.reset();
        thread_pool_.reset();
        isc_throw(Unexpected, "MtTcpListenerMgr::start failed:" << ex.what());
    }
}

void
MtTcpListenerMgr::checkPermissions() {
    if (thread_pool_) {
        thread_pool_->checkPausePermissions();
    }
}

void
MtTcpListenerMgr::pause() {
    if (thread_pool_) {
        thread_pool_->pause();
    }
}

void
MtTcpListenerMgr::resume() {
    if (thread_pool_) {
        thread_pool_->run();
    }
}

void
MtTcpListenerMgr::stop() {
    // Nothing to do.
    if (!thread_io_service_) {
        return;
    }

    LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC, MT_TCP_LISTENER_MGR_STOPPING)
              .arg(address_)
              .arg(port_);

    // Stop the thread pool.
    thread_pool_->stop();

    // Get rid of the listener.
    tcp_listener_.reset();

    // Ditch the IOService.
    thread_io_service_.reset();

    LOG_DEBUG(tcp_logger, isc::log::DBGLVL_TRACE_BASIC, MT_TCP_LISTENER_MGR_STOPPED)
              .arg(address_)
              .arg(port_);
}

bool
MtTcpListenerMgr::isRunning() {
    if (thread_pool_) {
        return (thread_pool_->isRunning());
    }

    return (false);
}

bool
MtTcpListenerMgr::isStopped() {
    if (thread_pool_) {
        return (thread_pool_->isStopped());
    }

    return (true);
}

bool
MtTcpListenerMgr::isPaused() {
    if (thread_pool_) {
        return (thread_pool_->isPaused());
    }

    return (false);
}

} // namespace isc::config
} // namespace isc
