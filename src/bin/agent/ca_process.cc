// Copyright (C) 2016-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
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
    : DProcessBase(name, io_service, DCfgMgrBasePtr(new CtrlAgentCfgMgr())),
      http_listeners_() {
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
            // Remove unused listeners within the main loop because new listeners
            // are created in within a callback method. This avoids removal the
            // listeners within a callback.
            garbageCollectListeners(1);
            runIO();
        }
        // Done so removing all listeners.
        garbageCollectListeners(0);
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
    size_t cnt = getIoService()->get_io_service().poll();
    if (!cnt) {
        cnt = getIoService()->get_io_service().run_one();
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
        bool use_https = false;

        // Only open a new listener if the configuration has changed.
        if (http_listeners_.empty() ||
            (http_listeners_.back()->getLocalAddress() != server_address) ||
            (http_listeners_.back()->getLocalPort() != server_port)) {
            // Create a TLS context.
            TlsContextPtr tls_context;
            // When TLS is enabled configure it.
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

            // Create http listener. It will open up a TCP socket and be
            // prepared to accept incoming connection.
            HttpListenerPtr http_listener
                (new HttpListener(*getIoService(), server_address,
                                  server_port, tls_context, rcf,
                                  HttpListener::RequestTimeout(TIMEOUT_AGENT_RECEIVE_COMMAND),
                                  HttpListener::IdleTimeout(TIMEOUT_AGENT_IDLE_CONNECTION_TIMEOUT)));

            // Instruct the http listener to actually open socket, install
            // callback and start listening.
            http_listener->start();

            // The new listener is running so add it to the collection of
            // active listeners. The next step will be to remove all other
            // active listeners, but we do it inside the main process loop.
            http_listeners_.push_back(http_listener);
        }

        // Ok, seems we're good to go.
        if (use_https) {
          LOG_INFO(agent_logger, CTRL_AGENT_HTTPS_SERVICE_STARTED)
              .arg(server_address.toText()).arg(server_port);
        } else {
            LOG_INFO(agent_logger, CTRL_AGENT_HTTP_SERVICE_STARTED)
                .arg(server_address.toText()).arg(server_port);
        }
    });

    int rcode = 0;
    config::parseAnswer(rcode, answer);
    return (answer);
}

void
CtrlAgentProcess::garbageCollectListeners(size_t leaving) {
    // We expect only one active listener. If there are more (most likely 2),
    // it means we have just reconfigured the server and need to shut down all
    // listeners except the most recently added.
    if (http_listeners_.size() > leaving) {
        // Stop no longer used listeners.
        for (auto l = http_listeners_.begin();
             l != http_listeners_.end() - leaving;
             ++l) {
            (*l)->stop();
        }
        // We have stopped listeners but there may be some pending handlers
        // related to these listeners. Need to invoke these handlers.
        getIoService()->get_io_service().poll();
        // Finally, we're ready to remove no longer used listeners.
        http_listeners_.erase(http_listeners_.begin(),
                              http_listeners_.end() - leaving);
    }
}


CtrlAgentCfgMgrPtr
CtrlAgentProcess::getCtrlAgentCfgMgr() {
    return (boost::dynamic_pointer_cast<CtrlAgentCfgMgr>(getCfgMgr()));
}

ConstHttpListenerPtr
CtrlAgentProcess::getHttpListener() const {
    // Return the most recent listener or null.
    return (http_listeners_.empty() ? ConstHttpListenerPtr() :
            http_listeners_.back());
}

bool
CtrlAgentProcess::isListening() const {
    // If there are is a listener, we're listening.
    return (static_cast<bool>(getHttpListener()));
}

} // namespace isc::agent
} // namespace isc
