// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
#include <boost/pointer_cast.hpp>
#include <string>
#include <vector>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
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
    // The base class automatically registers 'list-commands'. This
    // command should be forwarded if the 'service' is specified, so
    // we have to indicate it by adding it to the set of commands
    // for which forwarding takes precedence.
    forward_first_commands_.insert("list-commands");
}

void
CtrlAgentCommandMgr::forwardOrHandle(const std::string& cmd,
                                     const ForceForward& force_forward,
                                     CommandHandler handler) {
    BaseCommandMgr::registerCommand(cmd, handler);
    if (force_forward.forward_) {
        forward_first_commands_.insert(cmd);
    }
}

void
CtrlAgentCommandMgr::forwardOrHandleExtended(const std::string& cmd,
                                             const ForceForward& force_forward,
                                             ExtendedCommandHandler handler) {
    BaseCommandMgr::registerExtendedCommand(cmd, handler);
    if (force_forward.forward_) {
        forward_first_commands_.insert(cmd);
    }
}

void
CtrlAgentCommandMgr::deregisterCommand(const std::string& cmd) {
    BaseCommandMgr::deregisterCommand(cmd);
    forward_first_commands_.erase(cmd);
}

void
CtrlAgentCommandMgr::deregisterAll() {
    BaseCommandMgr::deregisterAll();
    forward_first_commands_.clear();
    // The base class automatically registers 'list-commands'. This
    // command should be forwarded if the 'service' is specified, so
    // we have to indicate it by adding it to the set of commands
    // for which forwarding takes precedence.
    forward_first_commands_.insert("list-commands");
}

ConstElementPtr
CtrlAgentCommandMgr::handleCommand(const std::string& cmd_name,
                                   const isc::data::ConstElementPtr& params,
                                   const isc::data::ConstElementPtr& original_cmd) {
    ConstElementPtr answer;

    try {
        // There are certain commands that have to be forwarded if the 'service'
        // parameter is specified.
        if (forward_first_commands_.count(cmd_name) > 0) {
            if (original_cmd && original_cmd->contains("service")) {
                ConstElementPtr services = original_cmd->get("service");
                if (services && !services->empty()) {
                    // The non-empty control command 'service' parameter exists which
                    // means we will forward this command to the Kea server. Let's
                    // cheat that Control Agent doesn't support this command to
                    // avoid it being handled by CA.
                    answer = createAnswer(CONTROL_RESULT_COMMAND_UNSUPPORTED,
                                          "forwarding command");
                }
            }
        }
    } catch (const std::exception& ex) {
        answer = createAnswer(CONTROL_RESULT_ERROR, "invalid service parameter value: "
                              + std::string(ex.what()));
    }

    if (!answer) {
        // Try handling this command on our own.
        answer = HookedCommandMgr::handleCommand(cmd_name, params, original_cmd);
    }

    int rcode = 0;
    static_cast<void>(parseAnswer(rcode, answer));

    // We have tried handling the command on our own but it seems that neither
    // the Control Agent nor a hook library can handle this command. We need
    // to try forwarding the command to one of the Kea servers.
    if (original_cmd && (rcode == CONTROL_RESULT_COMMAND_UNSUPPORTED)) {
        try {
            answer = tryForwardCommand(cmd_name, original_cmd);

        } catch (const CommandForwardingError& ex) {
            // This is apparently some configuration error or client's error.
            // We have notify the client.
            answer = createAnswer(CONTROL_RESULT_ERROR, ex.what());

        } catch (const CommandForwardingSkip& ex) {
            // Command is not intended to be forwarded so do nothing.
        }
    }

    // We have a response, so let's wrap it in the list.
    ElementPtr answer_list = Element::createList();
    answer_list->add(boost::const_pointer_cast<Element>(answer));

    return (answer_list);
}

ConstElementPtr
CtrlAgentCommandMgr::tryForwardCommand(const std::string& cmd_name,
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

    // If the service is not specified it means that the Control Agent is the
    // intended receiver of this message. This is not a fatal error, we simply
    // skip forwarding the command and rely on the internal logic of the
    // Control Agent to generate response.
    ConstElementPtr service_elements = command->get("service");
    if (!service_elements) {
        isc_throw(CommandForwardingSkip, "service parameter not specified");
    }

    // If the service exists it must be a list, even though we currently allow
    // only one service.
    std::vector<ElementPtr> service_vec;
    try {
        service_vec = service_elements->listValue();

    } catch (const std::exception& ex) {
        isc_throw(CommandForwardingError, "service parameter is not a list");
    }

    // service list may be empty in which case we treat it as it is not specified.
    if (service_vec.empty()) {
        isc_throw(CommandForwardingSkip, "service parameter is empty");
    }

    // Do not allow more than one service value. This will be allowed in the
    // future.
    if (service_vec.size() > 1) {
        isc_throw(CommandForwardingError, "service parameter must contain 0 or 1"
                  " service value");
    }

    // Convert the service to the server type values. Make sure the client
    // provided right value.
    CtrlAgentCfgContext::ServerType server_type;
    try {
        server_type = CtrlAgentCfgContext::toServerType(service_vec.at(0)->stringValue());

    } catch (const std::exception& ex) {
        // Invalid value in service list. Can't proceed.
        isc_throw(CommandForwardingError, ex.what());
    }

    // Now that we know what service it should be forwarded to, we should
    // find a matching forwarding socket. If this socket is not configured,
    // we have to communicate it to the client.
    ConstElementPtr socket_info = ctx->getControlSocketInfo(server_type);
    if (!socket_info) {
        isc_throw(CommandForwardingError, "forwarding socket is not configured"
                  " for the server type " << service_vec.at(0)->stringValue());
    }

    // If the configuration does its job properly the socket-name must be
    // specified and must be a string value.
    std::string socket_name = socket_info->get("socket-name")->stringValue();

    // Forward command and receive reply.
    IOService io_service;
    UnixDomainSocket unix_socket(io_service);
    size_t receive_len;
    try {
        unix_socket.connect(socket_name);
        std::string wire_command = command->toWire();
        unix_socket.write(&wire_command[0], wire_command.size());
        receive_len = unix_socket.receive(&receive_buf_[0], receive_buf_.size());

    } catch (...) {
        isc_throw(CommandForwardingError, "unable to forward command to the "
                  + service_vec.at(0)->stringValue() + " service. The server "
                  "is likely to be offline");
    }

    // This is really not possible right now, but when we migrate to the
    // solution using timeouts it is possible that the response is not
    // received.
    if (receive_len == 0) {
        isc_throw(CommandForwardingError, "internal server error: no answer"
                  " received from the server to the forwarded message");
    }

    std::string reply(&receive_buf_[0], receive_len);

    ConstElementPtr answer;
    try {
        answer = Element::fromJSON(reply);

        LOG_INFO(agent_logger, CTRL_AGENT_COMMAND_FORWARDED)
            .arg(cmd_name)
            .arg(service_vec.at(0)->stringValue());

    } catch (const std::exception& ex) {
        isc_throw(CommandForwardingError, "internal server error: unable to parse"
                  " server's answer to the forwarded message: " << ex.what());
    }

    return (answer);
}


} // end of namespace isc::agent
} // end of namespace isc
