// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <config/hooked_command_mgr.h>
#include <config/config_log.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_manager.h>
#include <hooks/server_hooks.h>
#include <boost/pointer_cast.hpp>
#include <vector>

using namespace isc::data;
using namespace isc::hooks;

namespace isc {
namespace config {

HookedCommandMgr::HookedCommandMgr()
    : BaseCommandMgr() {
}

bool
HookedCommandMgr::delegateCommandToHookLibrary(const std::string& cmd_name,
                                               const ConstElementPtr& params,
                                               const ConstElementPtr& original_cmd,
                                               ElementPtr& answer) {

    ConstElementPtr hook_response;
    if (HooksManager::commandHandlersPresent(cmd_name)) {

        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

        // Set status to normal.
        callout_handle->setStatus(CalloutHandle::NEXT_STEP_CONTINUE);

        // Delete previously set arguments.
        callout_handle->deleteAllArguments();

        ConstElementPtr command = original_cmd ? original_cmd :
            createCommand(cmd_name, params);

        // And pass it to the hook library.
        callout_handle->setArgument("command", command);
        callout_handle->setArgument("response", hook_response);

        HooksManager::callCommandHandlers(cmd_name, *callout_handle);

        // The callouts should set the response.
        callout_handle->getArgument("response", hook_response);

        answer = boost::const_pointer_cast<Element>(hook_response);

        return (true);
    }

    return (false);
}

ConstElementPtr
HookedCommandMgr::handleCommand(const std::string& cmd_name,
                                const ConstElementPtr& params,
                                const ConstElementPtr& original_cmd) {

    // The 'list-commands' is a special case. Hook libraries do not implement
    // this command. We determine what commands are supported by the hook
    // libraries by checking what hook points are present that have callouts
    // registered.
    if ((cmd_name != "list-commands")) {
        ElementPtr hook_response;
        // Check if there are any hooks libraries to process this command.
        if (delegateCommandToHookLibrary(cmd_name, params, original_cmd,
                                         hook_response)) {
            // Hooks libraries processed this command so simply return a
            // result.
            return (hook_response);
        }

    }

    // If we're here it means that the callouts weren't called. We need
    // to handle the command using local Command Manager.
    ConstElementPtr response = BaseCommandMgr::handleCommand(cmd_name,
                                                             params,
                                                             original_cmd);

    // If we're processing 'list-commands' command we may need to include
    // commands supported by hooks libraries in the response.
    if (cmd_name == "list-commands") {
        // Hooks names can be used to decode what commands are supported.
        const std::vector<std::string>& hooks =
            ServerHooks::getServerHooksPtr()->getHookNames();

        // Only update the response if there are any hooks present.
        if (!hooks.empty()) {
            ElementPtr hooks_commands = Element::createList();
            for (auto h = hooks.cbegin(); h != hooks.end(); ++h) {
                // Try to convert hook name to command name. If non-empty
                // string is returned it means that the hook point may have
                // command handlers associated with it. Otherwise, it means that
                // existing hook points are not for command handlers but for
                // regular callouts.
                std::string command_name = ServerHooks::hookToCommandName(*h);
                if (!command_name.empty()) {
                    // Final check: are command handlers registered for this
                    // hook point? If there are no command handlers associated,
                    // it means that the hook library was already unloaded.
                    if (HooksManager::commandHandlersPresent(command_name)) {
                        hooks_commands->add(Element::create(command_name));
                    }
                }
            }

            // If there is at least one hook point with command handlers
            // registered
            // for it, combine the lists of commands.
            if (!hooks_commands->empty()) {
                response = combineCommandsLists(response, createAnswer(0, hooks_commands));
            }
        }
    }

    return (response);
}


} // end of namespace isc::config
} // end of namespace isc
