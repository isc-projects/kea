// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_address.h>
#include <asiolink/io_error.h>
#include <asiolink/io_service.h>
#include <cmd_http_listener.h>
#include <cmd_response_creator_factory.h>
#include <config_log.h>
#include <config/timeouts.h>
#include <util/multi_threading_mgr.h>

#include <boost/pointer_cast.hpp>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::http;
using namespace isc::util;

namespace isc {
namespace config {

CmdHttpListener::CmdHttpListener(const IOAddress& address, const uint16_t port,
                                 const uint16_t thread_pool_size /* = 1 */)
    : address_(address), port_(port), io_service_(), http_listener_(),
      thread_pool_size_(thread_pool_size), threads_() {
}

CmdHttpListener::~CmdHttpListener() {
    stop();
}

void
CmdHttpListener::start() {
    // We must be in multi-threading mode.
    if (!MultiThreadingMgr::instance().getMode()) {
        isc_throw(InvalidOperation, "CmdHttpListener cannot be started"
                  " when multi-threading is disabled");
    }

    // Punt if we're already listening.
    if (isListening()) {
        isc_throw(InvalidOperation, "CmdHttpListener is already listening!");
    }

    try {
        // Create a new IOService.
        io_service_.reset(new IOService());

        // Create the response creator factory first. It will be used to
        // generate response creators. Each response creator will be
        // used to generate the answer to specific request.
        HttpResponseCreatorFactoryPtr rcf(new CmdResponseCreatorFactory());

        // Create the HTTP listener. It will open up a TCP socket and be
        // prepared to accept incoming connections.
        TlsContextPtr tls_context;
        http_listener_.reset(new HttpListener(*io_service_, address_, port_,
                                              tls_context, rcf,
                                              HttpListener::RequestTimeout(TIMEOUT_AGENT_RECEIVE_COMMAND),
                                              HttpListener::IdleTimeout(TIMEOUT_AGENT_IDLE_CONNECTION_TIMEOUT)));

        // Create the thread pool.
        threads_.reset(new HttpThreadPool(io_service_, thread_pool_size_, false));

        // Instruct the HTTP listener to actually open socket, install
        // callback and start listening.
        http_listener_->start();

        // OK, seems like we're good to go.
        LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_HTTP_LISTENER_STARTED)
                  .arg(thread_pool_size_)
                  .arg(address_)
                  .arg(port_);
    } catch (const std::exception& ex) {
        isc_throw(Unexpected, "CmdHttpListener::run failed:" << ex.what());
    }
}

void
CmdHttpListener::pause() {
    if (threads_) {
        threads_->pause();
    }
}

void
CmdHttpListener::resume() {
    if (threads_) {
        threads_->resume();
    }
}

void
CmdHttpListener::stop() {
    // Nothing to do.
    if (!io_service_) {
        return;
    }

    LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_HTTP_LISTENER_STOPPING)
              .arg(address_)
              .arg(port_);

    // Stop the thread pool.
    threads_->stop();

    // Get rid of the listener.
    http_listener_.reset();

    // Ditch the IOService.
    io_service_.reset();

    LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_HTTP_LISTENER_STOPPED)
              .arg(address_)
              .arg(port_);
}

HttpThreadPool::RunState 
CmdHttpListener::getRunState() const {
    if (!threads_) {
        isc_throw(InvalidOperation,
                  "CmdHttpListener::getRunState - no thread pool!");
    }

    return (threads_->getRunState());
}

bool
CmdHttpListener::isListening() const {
    // If we have a listener we're listening.
    return (http_listener_ != 0);
}

} // namespace isc::config
} // namespace isc
