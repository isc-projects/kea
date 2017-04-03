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
#include <iterator>
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
        return (HookedCommandMgr::handleCommand(cmd_name, params, original_cmd));
    }

    ElementPtr answer_list = Element::createList();

    // Before the command is forwarded it should be processed by the hooks libraries.
    if (HookedCommandMgr::delegateCommandToHookLibrary(cmd_name, params, original_cmd,
                                                       answer_list)) {
        // If the hooks libraries set the 'skip' flag, they indicate that the
        // commands have been processed. The answer_list should contain the list
        // of answers with each answer pertaining to one service.
        if (callout_handle_->getStatus() == CalloutHandle::NEXT_STEP_SKIP) {
                LOG_DEBUG(agent_logger, isc::log::DBGLVL_COMMAND,
                          CTRL_AGENT_COMMAND_PROCESS_SKIP)
                    .arg(cmd_name);
            return (answer_list);
        }
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

    // Convert the service to the server type values. Make sure the client
    // provided right value.
    CtrlAgentCfgContext::ServerType server_type;
    try {
        server_type = CtrlAgentCfgContext::toServerType(service);

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
                  " for the server type " << service);
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

    } catch (const std::exception& ex) {
        isc_throw(CommandForwardingError, "unable to forward command to the "
                  << service << " service: " << ex.what() << ". The server "
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
            .arg(cmd_name).arg(service);

    } catch (const std::exception& ex) {
        isc_throw(CommandForwardingError, "internal server error: unable to parse"
                  " server's answer to the forwarded message: " << ex.what());
    }

    return (answer);
}


} // end of namespace isc::agent
} // end of namespace isc
