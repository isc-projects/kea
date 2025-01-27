// Copyright (C) 2016-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service_mgr.h>
#include <agent/ca_process.h>
#include <agent/ca_controller.h>
#include <agent/ca_response_creator_factory.h>
#include <agent/ca_log.h>
#include <asiolink/io_address.h>
#include <asiolink/io_error.h>
#include <cc/command_interpreter.h>
#include <config/timeouts.h>
#include <boost/pointer_cast.hpp>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::http;
using namespace isc::process;


namespace isc {
namespace agent {

CtrlAgentProcess::CtrlAgentProcess(const char* name,
                                   const asiolink::IOServicePtr& io_service)
    : DProcessBase(name, io_service, DCfgMgrBasePtr(new CtrlAgentCfgMgr())) {
}

CtrlAgentProcess::~CtrlAgentProcess() {
}

void
CtrlAgentProcess::init() {
}

void
CtrlAgentProcess::run() {
    LOG_INFO(agent_logger, CTRL_AGENT_STARTED).arg(VERSION);

    try {
        // Register commands.
        CtrlAgentControllerPtr controller =
            boost::dynamic_pointer_cast<CtrlAgentController>(
                CtrlAgentController::instance());
        controller->registerCommands();

        // Let's process incoming data or expiring timers in a loop until
        // shutdown condition is detected.
        while (!shouldShutdown()) {
            runIO();
        }
        // Done so removing all listeners.
        closeCommandSockets();
        stopIOService();
    } catch (const std::exception& ex) {
        LOG_FATAL(agent_logger, CTRL_AGENT_FAILED).arg(ex.what());
        try {
            stopIOService();
        } catch (...) {
            // Ignore double errors
        }
        isc_throw(DProcessBaseError,
                  "Process run method failed: " << ex.what());
    }

    try {
        // Deregister commands.
        CtrlAgentControllerPtr controller =
            boost::dynamic_pointer_cast<CtrlAgentController>(
                CtrlAgentController::instance());
        controller->deregisterCommands();
    } catch (const std::exception&) {
        // What to do? Simply ignore...
    }

    LOG_DEBUG(agent_logger, isc::log::DBGLVL_START_SHUT, CTRL_AGENT_RUN_EXIT);
}

size_t
CtrlAgentProcess::runIO() {
    // Handle events registered by hooks using external IOService objects.
    IOServiceMgr::instance().pollIOServices();
    size_t cnt = getIOService()->poll();
    if (!cnt) {
        cnt = getIOService()->runOne();
    }
    return (cnt);
}

isc::data::ConstElementPtr
CtrlAgentProcess::shutdown(isc::data::ConstElementPtr /*args*/) {
    setShutdownFlag(true);
    return (isc::config::createAnswer(CONTROL_RESULT_SUCCESS,
                                      "Control Agent is shutting down"));
}

isc::data::ConstElementPtr
CtrlAgentProcess::configure(isc::data::ConstElementPtr config_set,
                            bool check_only) {
    // System reconfiguration often poses an interesting issue whereby the
    // configuration parsing is successful, but an attempt to use a new
    // configuration is not. This will leave us in the inconsistent state
    // when the configuration is in fact only partially applied and the
    // system's ability to operate is impaired. The use of C++ lambda is
    // a way to resolve this problem by injecting the code to the
    // simpleParseConfig which performs an attempt to open new instance
    // of the listener (if required). The lambda code will throw an
    // exception if it fails and cause the simpleParseConfig to rollback
    // configuration changes and report an error.
    ConstElementPtr answer = getCfgMgr()->simpleParseConfig(config_set,
                                                            check_only,
                                                            [this]() {
        ConfigPtr base_ctx = getCfgMgr()->getContext();
        CtrlAgentCfgContextPtr
            ctx = boost::dynamic_pointer_cast<CtrlAgentCfgContext>(base_ctx);

        if (!ctx) {
            isc_throw(Unexpected, "Internal logic error: bad context type");
        }

        /// @todo: If the parameter is a hostname, we need to resolve it.
        IOAddress server_address("::");
        try {
            server_address = IOAddress(ctx->getHttpHost());

        } catch (const IOError& e) {
            isc_throw(BadValue, "Failed to convert " << ctx->getHttpHost()
                      << " to IP address:" << e.what());
        }

        uint16_t server_port = ctx->getHttpPort();

        // Search for the specific connection and reuse the existing one if found.
        auto it = sockets_.find(std::make_pair(server_address, server_port));
        if (it != sockets_.end()) {
            auto listener = getHttpListener();
            if (listener) {
                // Reconfig keeping the same address and port.
                if (listener->getTlsContext()) {
                    LOG_INFO(agent_logger, CTRL_AGENT_HTTPS_SERVICE_REUSED)
                        .arg(server_address.toText())
                        .arg(server_port);
                } else {
                    LOG_INFO(agent_logger, CTRL_AGENT_HTTP_SERVICE_REUSED)
                        .arg(server_address.toText())
                        .arg(server_port);
                }
            }
            // If the connection can be reused, mark it as usable.
            it->second->usable_ = true;
        } else {

            // Connection not found so it needs to be created.
            // When TLS is enabled configure it.
            bool use_https = false;
            TlsContextPtr tls_context;
            if (!ctx->getCertFile().empty()) {
                TlsContext::configure(tls_context,
                                      TlsRole::SERVER,
                                      ctx->getTrustAnchor(),
                                      ctx->getCertFile(),
                                      ctx->getKeyFile(),
                                      ctx->getCertRequired());
                use_https = true;
            }

            // Create response creator factory first. It will be used to
            // generate response creators. Each response creator will be
            // used to generate answer to specific request.
            HttpResponseCreatorFactoryPtr rcf(new CtrlAgentResponseCreatorFactory());

            // Create HTTP listener. It will open up a TCP socket and be
            // prepared to accept incoming connection.
            HttpListenerPtr http_listener
                (new HttpListener(getIOService(),
                                  server_address,
                                  server_port,
                                  tls_context,
                                  rcf,
                                  HttpListener::RequestTimeout(TIMEOUT_AGENT_RECEIVE_COMMAND),
                                  HttpListener::IdleTimeout(TIMEOUT_AGENT_IDLE_CONNECTION_TIMEOUT)));

            // Instruct the HTTP listener to actually open socket, install
            // callback and start listening.
            http_listener->start();

            HttpSocketInfoPtr socket_info(new HttpSocketInfo());
            socket_info->config_ = ctx;
            socket_info->listener_ = http_listener;

            sockets_[std::make_pair(server_address, server_port)] = socket_info;

            // Ok, seems we're good to go.
            if (use_https) {
              LOG_INFO(agent_logger, CTRL_AGENT_HTTPS_SERVICE_STARTED)
                  .arg(server_address.toText())
                  .arg(server_port);
            } else {
                LOG_INFO(agent_logger, CTRL_AGENT_HTTP_SERVICE_STARTED)
                    .arg(server_address.toText())
                    .arg(server_port);
            }
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
                data.second->listener_->stop();
                auto it = sockets_.find(std::make_pair(data.second->config_->getHttpHost(),
                                                       data.second->config_->getHttpPort()));
                if (it != sockets_.end()) {
                    sockets_.erase(it);
                }
            }
        }
    });

    int rcode = 0;
    config::parseAnswer(rcode, answer);

    /// Let postponed hook initializations run.
    try {
        // Handle events registered by hooks using external IOService objects.
        IOServiceMgr::instance().pollIOServices();
    } catch (const std::exception& ex) {
        std::ostringstream err;
        err << "Error initializing hooks: "
            << ex.what();
        return (isc::config::createAnswer(CONTROL_RESULT_ERROR, err.str()));
    }

    return (answer);
}

void
CtrlAgentProcess::closeCommandSockets() {
    for (auto const& data : sockets_) {
        data.second->listener_->stop();
    }
    sockets_.clear();
    // We have stopped listeners but there may be some pending handlers
    // related to these listeners. Need to invoke these handlers.
    try {
        getIOService()->pollOne();
    } catch (...) {
    }
}

CtrlAgentCfgMgrPtr
CtrlAgentProcess::getCtrlAgentCfgMgr() {
    return (boost::dynamic_pointer_cast<CtrlAgentCfgMgr>(getCfgMgr()));
}

ConstHttpListenerPtr
CtrlAgentProcess::getHttpListener(HttpSocketInfoPtr info) const {
    // Return the most recent listener or null.
    if (info) {
        auto it = sockets_.find(std::make_pair(info->config_->getHttpHost(), info->config_->getHttpPort()));
        if (it != sockets_.end()) {
            return (it->second->listener_);
        }
    } else if (sockets_.size()) {
        return (sockets_.begin()->second->listener_);
    }
    return (ConstHttpListenerPtr());
}

bool
CtrlAgentProcess::isListening() const {
    // If there are is a listener, we're listening.
    return (static_cast<bool>(getHttpListener()));
}

} // namespace isc::agent
} // namespace isc
