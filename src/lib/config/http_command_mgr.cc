// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <config/config_log.h>
#include <config/http_command_mgr.h>
#include <config/http_command_response_creator_factory.h>
#include <config/http_command_response_creator.h>
#include <config/timeouts.h>
#include <sstream>
#include <vector>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::http;
using namespace std;

namespace isc {
namespace config {

/// @brief Implementation of the @c HttpCommandMgr.
class HttpCommandMgrImpl {
public:

    /// @brief Constructor.
    HttpCommandMgrImpl()
        : io_service_(), timeout_(TIMEOUT_AGENT_RECEIVE_COMMAND),
          idle_timeout_(TIMEOUT_AGENT_IDLE_CONNECTION_TIMEOUT),
          current_config_(), http_listeners_(), active_(0),
          use_external_(true) {
    }

    /// @brief Configure control socket from configuration.
    void configure(HttpCommandConfigPtr config);

    /// @brief Close control socket.
    ///
    /// @param remove When true remove the listeners immediately.
    void close(bool remove);

    /// @brief Removes listeners which are no longer in use.
    void garbageCollectListeners();

    /// @brief Returns a const pointer to the HTTP listener.
    ConstHttpListenerPtr getHttpListener() const;

    /// @brief Pointer to the IO service.
    IOServicePtr io_service_;

    /// @brief Connection timeout.
    long timeout_;

    /// @brief Idle connection timeout.
    long idle_timeout_;

    /// @brief Current config.
    HttpCommandConfigPtr current_config_;

    /// @brief Active listeners.
    vector<HttpListenerPtr> http_listeners_;

    /// @brief Number of active listeners (0 or 1).
    size_t active_;

    /// @brief Use external sockets flag.
    bool use_external_;
};

void
HttpCommandMgrImpl::configure(HttpCommandConfigPtr config) {
    // First case: from no config to no config.
    if (!config && http_listeners_.empty()) {
        return;
    }

    // Second case: from config to no config.
    if (!config && !http_listeners_.empty()) {
        close(false);
        return;
   }

    // Third case: no address or port change.
    if (config && current_config_ &&
        (config->getSocketAddress() == current_config_->getSocketAddress()) &&
        (config->getSocketPort() == current_config_->getSocketPort())) {
        // Check if TLS setup changed.
        if ((config->getTrustAnchor() != current_config_->getTrustAnchor()) ||
            (config->getCertFile() != current_config_->getCertFile()) ||
            (config->getKeyFile() != current_config_->getKeyFile()) ||
            (config->getCertRequired() != current_config_->getCertRequired())) {
            LOG_WARN(command_logger, HTTP_COMMAND_MGR_IGNORED_TLS_SETUP_CHANGES);
            // Overwrite the authentication setup and the emulation flag
            // in the response creator config.
            current_config_->setAuthConfig(config->getAuthConfig());
            current_config_->setEmulateAgentResponse(config->getEmulateAgentResponse());
        } else {
            current_config_ = config;
        }
        return;
    }

    // Last case: from no config, or address or port change.
    current_config_ = config;
    IOAddress server_address = config->getSocketAddress();
    uint16_t server_port = config->getSocketPort();
    bool use_https = false;
    TlsContextPtr tls_context;
    if (!config->getCertFile().empty()) {
        TlsContext::configure(tls_context,
                              TlsRole::SERVER,
                              config->getTrustAnchor(),
                              config->getCertFile(),
                              config->getKeyFile(),
                              config->getCertRequired());
        use_https = true;
    }

    // Create response creator factory first. It will be used to
    // generate response creators. Each response creator will be used
    // to generate answer to specific request.
    HttpResponseCreatorFactoryPtr rfc(new HttpCommandResponseCreatorFactory(config));

    // Create HTTP listener. It will open up a TCP socket and be
    // prepared to accept incoming connection.
    HttpListenerPtr http_listener
        (new HttpListener(io_service_,
                          server_address,
                          server_port,
                          tls_context,
                          rfc,
                          HttpListener::RequestTimeout(timeout_),
                          HttpListener::IdleTimeout(idle_timeout_)));

    // Pass the use external socket flag.
    http_listener->addExternalSockets(use_external_);

    // Instruct the HTTP listener to actually open socket, install
    // callback and start listening.
    http_listener->start();

    // The new listener is running so add it to the collection of
    // active listeners. The next step will be to remove all other
    // active listeners, but we do it inside the main process loop.
    http_listeners_.push_back(http_listener);
    active_ = 1;

    // Ok, seems we're good to go.
    LOG_INFO(command_logger, HTTP_COMMAND_MGR_SERVICE_STARTED)
        .arg(use_https ? "HTTPS" : "HTTP")
        .arg(server_address.toText())
        .arg(server_port);
}

void
HttpCommandMgrImpl::close(bool remove) {
    bool use_https = false;
    ostringstream ep;
    if (current_config_) {
        use_https = !current_config_->getCertFile().empty();
        ep << " bound to address " << current_config_->getSocketAddress()
           << " port " << current_config_->getSocketPort();
    }
    LOG_INFO(command_logger, HTTP_COMMAND_MGR_SERVICE_STOPPING)
        .arg(use_https ? "HTTPS" : "HTTP")
        .arg(ep.str());
    current_config_.reset();
    active_ = 0;
    if (remove) {
        garbageCollectListeners();
    }
}

void
HttpCommandMgrImpl::garbageCollectListeners() {
    // We expect only one active listener. If there are more (most likely 2),
    // it means we have just reconfigured the server and need to shut down all
    // listeners except the most recently added.
    if (http_listeners_.size() > active_) {
        // Stop no longer used listeners.
        for (auto l = http_listeners_.begin();
             l != http_listeners_.end() - active_;
             ++l) {
            (*l)->stop();
        }
        // We have stopped listeners but there may be some pending handlers
        // related to these listeners. Need to invoke these handlers.
        try {
            io_service_->poll();
        } catch (...) {
        }
        // Finally, we're ready to remove no longer used listeners.
        http_listeners_.erase(http_listeners_.begin(),
                              http_listeners_.end() - active_);
    }
}

ConstHttpListenerPtr
HttpCommandMgrImpl::getHttpListener() const {
    // Return the most recent listener or null.
    return (http_listeners_.empty() ? ConstHttpListenerPtr() :
            http_listeners_.back());
}

HttpCommandMgr&
HttpCommandMgr::instance() {
    static HttpCommandMgr http_cmd_mgr;
    return (http_cmd_mgr);
}

HttpCommandMgr::HttpCommandMgr()
    : HookedCommandMgr(), impl_(new HttpCommandMgrImpl()) {
}

void
HttpCommandMgr::setIOService(const IOServicePtr& io_service) {
    impl_->io_service_ = io_service;
}

void
HttpCommandMgr::setConnectionTimeout(const long timeout) {
    impl_->timeout_ = timeout;
}

void
HttpCommandMgr::setIdleConnectionTimeout(const long timeout) {
    impl_->idle_timeout_ = timeout;
}

void
HttpCommandMgr::addExternalSockets(bool use_external) {
    impl_->use_external_ = use_external;
}

void
HttpCommandMgr::configure(HttpCommandConfigPtr config) {
    impl_->configure(config);
}

void
HttpCommandMgr::close(bool remove) {
    impl_->close(remove);
}

void
HttpCommandMgr::garbageCollectListeners() {
    impl_->garbageCollectListeners();
}

ConstHttpListenerPtr
HttpCommandMgr::getHttpListener() const {
    return (impl_->getHttpListener());
}

} // end of isc::config
} // end of isc
