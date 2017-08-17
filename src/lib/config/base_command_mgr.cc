// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cc/command_interpreter.h>
#include <config/base_command_mgr.h>
#include <config/config_log.h>
#include <boost/bind.hpp>

using namespace isc::data;

namespace isc {
namespace config {

BaseCommandMgr::BaseCommandMgr() {
    registerCommand("list-commands", boost::bind(&BaseCommandMgr::listCommandsHandler,
                                                 this, _1, _2));
}

void
BaseCommandMgr::registerCommand(const std::string& cmd, CommandHandler handler) {
    if (!handler) {
        isc_throw(InvalidCommandHandler, "Specified command handler is NULL");
    }

    HandlerContainer::const_iterator it = handlers_.find(cmd);
    if (it != handlers_.end()) {
        isc_throw(InvalidCommandName, "Handler for command '" << cmd
                  << "' is already installed.");
    }

    HandlersPair handlers;
    handlers.handler = handler;
    handlers_.insert(make_pair(cmd, handlers));

    LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_REGISTERED).arg(cmd);
}

void
BaseCommandMgr::registerExtendedCommand(const std::string& cmd,
                                        ExtendedCommandHandler handler) {
    if (!handler) {
        isc_throw(InvalidCommandHandler, "Specified command handler is NULL");
    }

    HandlerContainer::const_iterator it = handlers_.find(cmd);
    if (it != handlers_.end()) {
        isc_throw(InvalidCommandName, "Handler for command '" << cmd
                  << "' is already installed.");
    }

    HandlersPair handlers;
    handlers.extended_handler = handler;
    handlers_.insert(make_pair(cmd, handlers));

    LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_EXTENDED_REGISTERED).arg(cmd);
}

void
BaseCommandMgr::deregisterCommand(const std::string& cmd) {
    if (cmd == "list-commands") {
        isc_throw(InvalidCommandName,
                  "Can't uninstall internal command 'list-commands'");
    }

    HandlerContainer::iterator it = handlers_.find(cmd);
    if (it == handlers_.end()) {
        isc_throw(InvalidCommandName, "Handler for command '" << cmd
                  << "' not found.");
    }
    handlers_.erase(it);

    LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_DEREGISTERED).arg(cmd);
}

void
BaseCommandMgr::deregisterAll() {

    // No need to log anything here. deregisterAll is not used in production
    // code, just in tests.
    handlers_.clear();
    registerCommand("list-commands",
        boost::bind(&BaseCommandMgr::listCommandsHandler, this, _1, _2));
}

isc::data::ConstElementPtr
BaseCommandMgr::processCommand(const isc::data::ConstElementPtr& cmd) {
    if (!cmd) {
        return (createAnswer(CONTROL_RESULT_ERROR,
                             "Command processing failed: NULL command parameter"));
    }

    try {
        ConstElementPtr arg;
        std::string name = parseCommand(arg, cmd);

        LOG_INFO(command_logger, COMMAND_RECEIVED).arg(name);

        return (handleCommand(name, arg, cmd));

    } catch (const Exception& e) {
        LOG_WARN(command_logger, COMMAND_PROCESS_ERROR2).arg(e.what());
        return (createAnswer(CONTROL_RESULT_ERROR,
                             std::string("Error during command processing: ")
                             + e.what()));
    }
}

ConstElementPtr
BaseCommandMgr::handleCommand(const std::string& cmd_name,
                              const ConstElementPtr& params,
                              const ConstElementPtr& original_cmd) {
    auto it = handlers_.find(cmd_name);
    if (it == handlers_.end()) {
        // Ok, there's no such command.
        return (createAnswer(CONTROL_RESULT_COMMAND_UNSUPPORTED,
                             "'" + cmd_name + "' command not supported."));
    }

    // Call the actual handler and return whatever it returned
    if (it->second.handler) {
        return (it->second.handler(cmd_name, params));
    }
    return (it->second.extended_handler(cmd_name, params, original_cmd));
}

isc::data::ConstElementPtr
BaseCommandMgr::listCommandsHandler(const std::string& name,
                                    const isc::data::ConstElementPtr& ) {
    using namespace isc::data;
    ElementPtr commands = Element::createList();
    for (HandlerContainer::const_iterator it = handlers_.begin();
         it != handlers_.end(); ++it) {
        commands->add(Element::create(it->first));
    }
    return (createAnswer(CONTROL_RESULT_SUCCESS, commands));
}


} // namespace isc::config
} // namespace isc
