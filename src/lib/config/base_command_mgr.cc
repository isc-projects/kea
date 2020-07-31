// Copyright (C) 2017-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <config/base_command_mgr.h>
#include <config/config_log.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_manager.h>
#include <functional>

using namespace isc::data;
using namespace isc::hooks;
namespace ph = std::placeholders;

namespace {

/// Structure that holds registered hook indexes
struct BaseCommandMgrHooks {
    int hook_index_command_processed_; ///< index for "command_processe" hook point

    /// Constructor that registers hook points for AllocationEngine
    BaseCommandMgrHooks() {
        hook_index_command_processed_ = HooksManager::registerHook("command_processed");
    }
};

// Declare a Hooks object. As this is outside any function or method, it
// will be instantiated (and the constructor run) when the module is loaded.
// As a result, the hook indexes will be defined before any method in this
// module is called.
BaseCommandMgrHooks Hooks;

}; // anonymous namespace

namespace isc {
namespace config {

BaseCommandMgr::BaseCommandMgr() {
    registerCommand("list-commands", std::bind(&BaseCommandMgr::listCommandsHandler,
                                               this, ph::_1, ph::_2));
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
        std::bind(&BaseCommandMgr::listCommandsHandler, this, ph::_1, ph::_2));
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

        ConstElementPtr response = handleCommand(name, arg, cmd);

        // If there any callouts for command-processed hook point call them
        if (HooksManager::calloutsPresent(Hooks.hook_index_command_processed_)) {
            // Commands are not associated with anything so there's no pre-existing
            // callout.
            CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

            // Add the command name, arguments, and response to the callout context
            callout_handle->setArgument("name", name);
            callout_handle->setArgument("arguments", arg);
            callout_handle->setArgument("response", response);

            // Call callouts
            HooksManager::callCallouts(Hooks.hook_index_command_processed_,
                                        *callout_handle);

            // Refresh the response from the callout context in case it was modified.
            // @todo Should we allow this?
            callout_handle->getArgument("response", response);
        }

        return (response);

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
BaseCommandMgr::listCommandsHandler(const std::string& /* name */,
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
