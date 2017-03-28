// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <agent/ca_process.h>
#include <agent/ca_controller.h>
#include <agent/ca_response_creator_factory.h>
#include <agent/ca_log.h>
#include <asiolink/io_address.h>
#include <asiolink/io_error.h>
#include <cc/command_interpreter.h>
#include <http/listener.h>
#include <boost/pointer_cast.hpp>

using namespace isc::asiolink;
using namespace isc::http;
using namespace isc::process;

// Temporarily hardcoded configuration.
/// @todo: remove once 5134 is merged.
namespace {

const long REQUEST_TIMEOUT = 10000;

}

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

        // Create response creator factory first. It will be used to generate
        // response creators. Each response creator will be used to generate
        // answer to specific request.
        HttpResponseCreatorFactoryPtr rcf(new CtrlAgentResponseCreatorFactory());

        DCfgContextBasePtr base_ctx = getCfgMgr()->getContext();
        CtrlAgentCfgContextPtr ctx =
            boost::dynamic_pointer_cast<CtrlAgentCfgContext>(base_ctx);
        if (!ctx) {
            isc_throw(Unexpected, "Interal logic error: bad context type");
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

        // Create http listener. It will open up a TCP socket and be prepared
        // to accept incoming connection.
        HttpListener http_listener(*getIoService(), server_address,
                                   server_port, rcf, REQUEST_TIMEOUT);

        // Instruct the http listener to actually open socket, install callback
        // and start listening.
        http_listener.start();

        // Ok, seems we're good to go.
        LOG_INFO(agent_logger, CTRL_AGENT_HTTP_SERVICE_STARTED)
            .arg(server_address.toText()).arg(server_port);

        // Let's process incoming data or expiring timers in a loop until
        // shutdown condition is detected.
        while (!shouldShutdown()) {
            getIoService()->run_one();
        }
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

isc::data::ConstElementPtr
CtrlAgentProcess::shutdown(isc::data::ConstElementPtr /*args*/) {
    setShutdownFlag(true);
    return (isc::config::createAnswer(0, "Control Agent is shutting down"));
}

isc::data::ConstElementPtr
CtrlAgentProcess::configure(isc::data::ConstElementPtr config_set,
                            bool check_only) {
    int rcode = 0;
    isc::data::ConstElementPtr answer = getCfgMgr()->simpleParseConfig(config_set,
                                                                       check_only);
    config::parseAnswer(rcode, answer);
    return (answer);
}


CtrlAgentCfgMgrPtr
CtrlAgentProcess::getCtrlAgentCfgMgr() {
    return(boost::dynamic_pointer_cast<CtrlAgentCfgMgr>(getCfgMgr()));
}

} // namespace isc::agent
} // namespace isc
