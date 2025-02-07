// Copyright (C) 2024-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <config/command_mgr.h>
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
using namespace isc::data;
using namespace isc::dhcp;
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
          use_external_(true) {
    }

    /// @brief Open http control sockets using configuration.
    ///
    /// @param config Configuration information for the http control sockets.
    void openCommandSockets(const isc::data::ConstElementPtr config);

    /// @brief Open http control socket using configuration.
    ///
    /// Creates http/https listener, or reuses the existing one reapplying
    /// changes.
    ///
    /// @param config Configuration information for the http control socket.
    void openCommandSocket(const isc::data::ConstElementPtr config);

    /// @brief Close control socket.
    ///
    /// @param info Configuration information for the http control socket.
    /// @param remove When true remove the listeners immediately.
    void closeCommandSocket(HttpSocketInfoPtr info, bool remove);

    /// @brief Close control socket.
    ///
    /// @param remove When true remove the listeners immediately.
    void closeCommandSockets(bool remove = true);

    /// @brief Returns a const pointer to the HTTP listener.
    ///
    /// @param info Configuration information for the http control socket.
    ///
    /// @return Const pointer to the currently used listener or null pointer if
    /// there is no listener.
    ConstHttpListenerPtr getHttpListener(HttpSocketInfoPtr info) const;

    /// @brief Pointer to the IO service.
    IOServicePtr io_service_;

    /// @brief Connection timeout.
    long timeout_;

    /// @brief Idle connection timeout.
    long idle_timeout_;

    /// @brief The HTTP/HTTPS socket data (configuration, listener, etc.).
    std::map<std::pair<IOAddress, uint16_t>, HttpSocketInfoPtr> sockets_;

    /// @brief Use external sockets flag.
    bool use_external_;
};

void
HttpCommandMgrImpl::openCommandSockets(const isc::data::ConstElementPtr config) {
    if (!config) {
        isc_throw(BadSocketInfo, "Missing config parameters, can't create socket.");
    }

    if (config->getType() != Element::list) {
        isc_throw(DhcpConfigError, "expected list type ("
                  << config->getPosition() << ")");
    }

    for (auto const& socket : config->listValue()) {
        openCommandSocket(socket);
    }

    auto copy = sockets_;
    for (auto const& data : copy) {
        if (data.second->usable_) {
            // If the connection can be used (just created) or reused, keep it
            // in the list and clear the flag. It will be marked again on next
            // configuration event if needed.
            data.second->usable_ = false;
        } else {
            // If the connection can not be reused, stop it and remove it from the list.
            closeCommandSocket(data.second, true);
        }
    }
}

void
HttpCommandMgrImpl::openCommandSocket(const isc::data::ConstElementPtr config) {
    if (!config) {
        isc_throw(BadSocketInfo, "Missing config parameters, can't create socket.");
    }

    HttpCommandConfigPtr cmd_config(new HttpCommandConfig(config));

    IOAddress server_address = cmd_config->getSocketAddress();
    uint16_t server_port = cmd_config->getSocketPort();

    // Search for the specific connection and reuse the existing one if found.
    auto it = sockets_.find(std::make_pair(server_address, server_port));
    if (it != sockets_.end()) {
        auto listener = it->second->listener_;
        if (listener) {
            // Reconfig keeping the same address and port.
            if (listener->getTlsContext()) {
                if (cmd_config->getTrustAnchor().empty()) {
                    // Can not switch from HTTPS to HTTP
                    LOG_ERROR(command_logger, HTTP_COMMAND_MGR_HTTPS_SERVICE_REUSE_FAILED)
                        .arg(server_address.toText())
                        .arg(server_port);
                    isc_throw(BadValue,
                              "Can not switch from HTTPS to HTTP sockets using the same address and port.");
                } else {
                    // Apply TLS settings each time.
                    TlsContextPtr tls_context;
                    TlsContext::configure(tls_context,
                                          TlsRole::SERVER,
                                          cmd_config->getTrustAnchor(),
                                          cmd_config->getCertFile(),
                                          cmd_config->getKeyFile(),
                                          cmd_config->getCertRequired());
                    // Overwrite the authentication setup, the http headers and the emulation flag
                    // in the response creator config.
                    it->second->config_->setAuthConfig(cmd_config->getAuthConfig());
                    it->second->config_->setHttpHeaders(cmd_config->getHttpHeaders());
                    it->second->config_->setEmulateAgentResponse(cmd_config->getEmulateAgentResponse());
                    io_service_->post([listener, tls_context]() { listener->setTlsContext(tls_context); });
                    LOG_INFO(command_logger, HTTP_COMMAND_MGR_HTTPS_SERVICE_UPDATED)
                        .arg(server_address.toText())
                        .arg(server_port);
                }
            } else if (!cmd_config->getTrustAnchor().empty()) {
                // Can not switch from HTTP to HTTPS
                LOG_ERROR(command_logger, HTTP_COMMAND_MGR_HTTP_SERVICE_REUSE_FAILED)
                    .arg(server_address.toText())
                    .arg(server_port);
                isc_throw(BadValue,
                          "Can not switch from HTTP to HTTPS sockets using the same address and port.");
            }
        }
        // If the connection can be reused, mark it as usable.
        it->second->usable_ = true;
        return;
    }

    // Connection not found so it needs to be created.
    // When TLS is enabled configure it.
    bool use_https = false;
    TlsContextPtr tls_context;
    if (!cmd_config->getCertFile().empty()) {
        TlsContext::configure(tls_context,
                              TlsRole::SERVER,
                              cmd_config->getTrustAnchor(),
                              cmd_config->getCertFile(),
                              cmd_config->getKeyFile(),
                              cmd_config->getCertRequired());
        use_https = true;
    }

    // Create response creator factory first. It will be used to
    // generate response creators. Each response creator will be used
    // to generate answer to specific request.
    HttpResponseCreatorFactoryPtr rfc(new HttpCommandResponseCreatorFactory(cmd_config));

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

    HttpSocketInfoPtr socket_info(new HttpSocketInfo());
    socket_info->config_ = cmd_config;
    socket_info->listener_ = http_listener;

    sockets_[std::make_pair(server_address, server_port)] = socket_info;

    // Ok, seems we're good to go.
    LOG_INFO(command_logger, HTTP_COMMAND_MGR_SERVICE_STARTED)
        .arg(use_https ? "HTTPS" : "HTTP")
        .arg(server_address.toText())
        .arg(server_port);
}

void
HttpCommandMgrImpl::closeCommandSocket(HttpSocketInfoPtr info, bool remove) {
    bool use_https = false;
    if (info) {
        ostringstream ep;
        use_https = !info->config_->getCertFile().empty();
        ep << "bound to address " << info->config_->getSocketAddress()
           << " port " << info->config_->getSocketPort();

        LOG_INFO(command_logger, HTTP_COMMAND_MGR_SERVICE_STOPPING)
            .arg(use_https ? "HTTPS" : "HTTP")
            .arg(ep.str());
        info->listener_->stop();
        if (remove) {
            auto it = sockets_.find(std::make_pair(info->config_->getSocketAddress(), info->config_->getSocketPort()));
            if (it != sockets_.end()) {
                sockets_.erase(it);
            }
        }
        // We have stopped listeners but there may be some pending handlers
        // related to these listeners. Need to invoke these handlers.
        try {
            io_service_->pollOne();
        } catch (...) {
        }
    } else {
        closeCommandSockets(remove);
    }
}

void
HttpCommandMgrImpl::closeCommandSockets(bool remove) {
    auto copy = sockets_;
    for (auto const& data : copy) {
        closeCommandSocket(data.second, remove);
    }
}

ConstHttpListenerPtr
HttpCommandMgrImpl::getHttpListener(HttpSocketInfoPtr info) const {
    // Return the most recent listener or null.
    if (info) {
        auto it = sockets_.find(std::make_pair(info->config_->getSocketAddress(), info->config_->getSocketPort()));
        if (it != sockets_.end()) {
            return (it->second->listener_);
        }
    } else if (sockets_.size()) {
        return (sockets_.begin()->second->listener_);
    }
    return (ConstHttpListenerPtr());
}

HttpCommandMgr&
HttpCommandMgr::instance() {
    static HttpCommandMgr http_cmd_mgr;
    return (http_cmd_mgr);
}

HttpCommandMgr::HttpCommandMgr() : impl_(new HttpCommandMgrImpl()) {
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
HttpCommandMgr::openCommandSocket(const isc::data::ConstElementPtr config) {
    impl_->openCommandSocket(config);
}

void
HttpCommandMgr::openCommandSockets(const isc::data::ConstElementPtr config) {
    impl_->openCommandSockets(config);
}

void
HttpCommandMgr::closeCommandSocket(HttpSocketInfoPtr info, bool remove) {
    impl_->closeCommandSocket(info, remove);
}

void
HttpCommandMgr::closeCommandSockets() {
    impl_->closeCommandSockets();
}

ConstHttpListenerPtr
HttpCommandMgr::getHttpListener(HttpSocketInfoPtr info) const {
    return (impl_->getHttpListener(info));
}

} // end of isc::config
} // end of isc
