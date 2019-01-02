// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <agent/ca_cfg_mgr.h>
#include <agent/ca_command_mgr.h>
#include <agent/ca_controller.h>
#include <agent/ca_log.h>
#include <agent/ca_process.h>
#include <asiolink/asio_wrapper.h>
#include <asiolink/io_service.h>
#include <asiolink/unix_domain_socket.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <cc/json_feed.h>
#include <config/client_connection.h>
#include <config/timeouts.h>
#include <boost/pointer_cast.hpp>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::process;

namespace isc {
namespace agent {

CtrlAgentCommandMgr&
CtrlAgentCommandMgr::instance() {
    static CtrlAgentCommandMgr command_mgr;
    return (command_mgr);
}

CtrlAgentCommandMgr::CtrlAgentCommandMgr()
    : HookedCommandMgr() {
}

ConstElementPtr
CtrlAgentCommandMgr::handleCommand(const std::string& cmd_name,
                                   const isc::data::ConstElementPtr& params,
                                   const isc::data::ConstElementPtr& original_cmd) {
    ConstElementPtr answer = handleCommandInternal(cmd_name, params, original_cmd);

    if (answer->getType() == Element::list) {
        return (answer);
    }

    // In general, the handlers should return a list of answers rather than a
    // single answer, but in some cases we rely on the generic handlers,
    // e.g. 'list-commands', which may return a single answer not wrapped in
    // the list. Such answers need to be wrapped in the list here.
    ElementPtr answer_list = Element::createList();
    answer_list->add(boost::const_pointer_cast<Element>(answer));

    return (answer_list);
}


ConstElementPtr
CtrlAgentCommandMgr::handleCommandInternal(std::string cmd_name,
                                           isc::data::ConstElementPtr params,
                                           isc::data::ConstElementPtr original_cmd) {

    ConstElementPtr services = Element::createList();

    // Retrieve 'service' parameter to determine if we should forward the
    // command or handle it on our own.
    if (original_cmd && original_cmd->contains("service")) {
        services = original_cmd->get("service");
        // If 'service' value is not a list, this is a fatal error. We don't want
        // to try processing commands that don't adhere to the required format.
        if (services->getType() != Element::list) {
            return (createAnswer(CONTROL_RESULT_ERROR, "service value must be a list"));
        }
    }

    // 'service' parameter hasn't been specified which indicates that the command
    // is intended to be processed by the CA. The following command will try to
    // process the command with hooks libraries (if available) or by one of the
    // CA's native handlers.
    if (services->empty()) {

        // It is frequent user error to not include the 'service' parameter in
        // the commands that should be forwarded to Kea servers. If the command
        // lacks this parameter the CA will try to process it and often fail
        // because it is not supported by the CA. In the future we may want to
        // make this parameter mandatory. For now, we're going to improve the
        // situation by clearly explaining to the controlling client that the
        // command is not supported by the CA, but it is possible that he may
        // achieve what he wants by providing the 'service' parameter.

        // Our interface is very restrictive so we walk around this by const
        // casting the returned pointer. It is certainly easier to do than
        // changing the whole data interface.
        ElementPtr answer = boost::const_pointer_cast<Element>
            (HookedCommandMgr::handleCommand(cmd_name, params, original_cmd));

        try {
            // Check what error code was returned by the handler.
            int rcode = 0;
            ConstElementPtr text = parseAnswer(rcode, answer);

            // There is a dedicated error code for unsupported command case.
            if (rcode == CONTROL_RESULT_COMMAND_UNSUPPORTED) {

                // Append the explanatory text to the text reported by the handler.
                // Smart, eh?
                std::ostringstream s;
                s << text->stringValue();
                s << " You did not include \"service\" parameter in the command,"
                    " which indicates that Kea Control Agent should process this"
                    " command rather than forward it to one or more Kea servers. If you"
                    " aimed to send this command to one of the Kea servers you"
                    " should include the \"service\" parameter in your request, e.g."
                    " \"service\": [ \"dhcp4\" ] to forward the command to the DHCPv4"
                    " server, or \"service\": [ \"dhcp4\", \"dhcp6\", \"d2\" ] to forward it to"
                    " DHCPv4, DHCPv6 and D2 servers etc.";

                answer->set(CONTROL_TEXT, Element::create(s.str()));
            }

        } catch (...) {
            // Exceptions are not really possible assuming that the BaseCommandMgr
            // creates the response correctly.
        }

        return (answer);
    }

    ElementPtr answer_list = Element::createList();

    // Before the command is forwarded we check if there are any hooks libraries
    // which would process the command.
    if (HookedCommandMgr::delegateCommandToHookLibrary(cmd_name, params, original_cmd,
                                                       answer_list)) {
        // The command has been processed by hooks library. Return the result.
        return (answer_list);
    }

    // We don't know whether the hooks libraries modified the value of the
    //  answer list, so let's be safe and re-create the answer_list.
    answer_list = Element::createList();

    // For each value within 'service' we have to try forwarding the command.
    for (unsigned i = 0; i < services->size(); ++i) {
        if (original_cmd) {
            ConstElementPtr answer;
            try {
                LOG_DEBUG(agent_logger, isc::log::DBGLVL_COMMAND,
                          CTRL_AGENT_COMMAND_FORWARD_BEGIN)
                    .arg(cmd_name).arg(services->get(i)->stringValue());

                answer = forwardCommand(services->get(i)->stringValue(),
                                        cmd_name, original_cmd);

            } catch (const CommandForwardingError& ex) {
                LOG_DEBUG(agent_logger, isc::log::DBGLVL_COMMAND,
                          CTRL_AGENT_COMMAND_FORWARD_FAILED)
                    .arg(cmd_name).arg(ex.what());
                answer = createAnswer(CONTROL_RESULT_ERROR, ex.what());
            }

            answer_list->add(boost::const_pointer_cast<Element>(answer));
        }
    }

    return (answer_list);
}

ConstElementPtr
CtrlAgentCommandMgr::forwardCommand(const std::string& service,
                                    const std::string& cmd_name,
                                    const isc::data::ConstElementPtr& command) {
    // Context will hold the server configuration.
    CtrlAgentCfgContextPtr ctx;

    // There is a hierarchy of the objects through which we need to pass to get
    // the configuration context. We may simplify this at some point but since
    // we're in the singleton we want to make sure that we're using most current
    // configuration.
    boost::shared_ptr<CtrlAgentController> controller =
        boost::dynamic_pointer_cast<CtrlAgentController>(CtrlAgentController::instance());
    if (controller) {
        CtrlAgentProcessPtr process = controller->getCtrlAgentProcess();
        if (process) {
            CtrlAgentCfgMgrPtr cfgmgr = process->getCtrlAgentCfgMgr();
            if (cfgmgr) {
                ctx = cfgmgr->getCtrlAgentCfgContext();
            }
        }
    }

    // This is highly unlikely but keep the checks just in case someone messes up
    // in the code.
    if (!ctx) {
        isc_throw(CommandForwardingError, "internal server error: unable to retrieve"
                  " Control Agent configuration information");
    }

    // Now that we know what service it should be forwarded to, we should
    // find a matching forwarding socket. If this socket is not configured,
    // we have to communicate it to the client.
    ConstElementPtr socket_info = ctx->getControlSocketInfo(service);
    if (!socket_info) {
        isc_throw(CommandForwardingError, "forwarding socket is not configured"
                  " for the server type " << service);
    }

    // If the configuration does its job properly the socket-name must be
    // specified and must be a string value.
    std::string socket_name = socket_info->get("socket-name")->stringValue();

    // Forward command and receive reply.
    IOServicePtr io_service(new IOService());;
    ClientConnection conn(*io_service);
    boost::system::error_code received_ec;
    ConstJSONFeedPtr received_feed;
    conn.start(ClientConnection::SocketPath(socket_name),
               ClientConnection::ControlCommand(command->toWire()),
               [&io_service, &received_ec, &received_feed]
               (const boost::system::error_code& ec, ConstJSONFeedPtr feed) {
                   // Capture error code and parsed data.
                   received_ec = ec;
                   received_feed = feed;
                   // Got the IO service so stop IO service. This causes to
                   // stop IO service when all handlers have been invoked.
                   io_service->stopWork();
               }, ClientConnection::Timeout(TIMEOUT_AGENT_FORWARD_COMMAND));
    io_service->run();

    if (received_ec) {
        isc_throw(CommandForwardingError, "unable to forward command to the "
                  << service << " service: " << received_ec.message()
                  << ". The server is likely to be offline");
    }

    // This shouldn't happen because the fact that there was no time out indicates
    // that the whole response has been read and it should be stored within the
    // feed. But, let's check to prevent assertions.
    if (!received_feed) {
        isc_throw(CommandForwardingError, "internal server error: empty response"
                  " received from the unix domain socket");
    }

    ConstElementPtr answer;
    try {
        answer = received_feed->toElement();

        LOG_INFO(agent_logger, CTRL_AGENT_COMMAND_FORWARDED)
            .arg(cmd_name).arg(service);

    } catch (const std::exception& ex) {
        isc_throw(CommandForwardingError, "internal server error: unable to parse"
                  " server's answer to the forwarded message: " << ex.what());
    }

    return (answer);
}


} // end of namespace isc::agent
} // end of namespace isc
