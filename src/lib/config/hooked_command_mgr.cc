// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config/hooked_command_mgr.h>
#include <config/config_log.h>
#include <hooks/hooks_manager.h>

using namespace isc::data;
using namespace isc::hooks;

namespace {

/// @brief Structure that holds registered hook indexes.
struct CommandMgrHooks {
    /// @brief Index for "control_command_receive" hook point.
    int hook_index_control_command_receive_;

    /// @brief Constructor that registers hook points for HookedCommandMgr
    CommandMgrHooks() {
        hook_index_control_command_receive_ =
            HooksManager::registerHook("control_command_receive");
    }
};

// Declare a hooks object. As this is outside any function or method, it
// will be instantiated (and the constructor run) when the module is loaded.
// As a result, the hook indexes will be defined before any method in this
// module is called.
CommandMgrHooks Hooks;

} // end of anonymous namespace

namespace isc {
namespace config {

HookedCommandMgr::HookedCommandMgr()
    : BaseCommandMgr(), callout_handle_(HooksManager::createCalloutHandle()) {
}

ConstElementPtr
HookedCommandMgr::handleCommand(const std::string& cmd_name,
                                const ConstElementPtr& params) {
    if (!callout_handle_) {
        isc_throw(Unexpected, "callout handle not configured for the Command "
                  "Manager: this is a programming error");
    }

    ConstElementPtr hook_response;
    if (HooksManager::calloutsPresent(Hooks.hook_index_control_command_receive_)) {

        // Delete previously set arguments.
        callout_handle_->deleteAllArguments();

        // Being in this function we don't have access to the original data
        // object holding the whole command (name and arguments). Let's
        // recreate it.
        ElementPtr original_command = Element::createMap();
        original_command->set("command", Element::create(cmd_name));
        original_command->set("arguments", params);

        // And pass it to the hook library.
        callout_handle_->setArgument("command", boost::dynamic_pointer_cast<
                                     const Element>(original_command));
        callout_handle_->setArgument("response", hook_response);

        HooksManager::callCallouts(Hooks.hook_index_control_command_receive_,
                                   *callout_handle_);

        // The callouts should set the response.
        callout_handle_->getArgument("response", hook_response);

        // If the hook return 'skip' status, simply return the response.
        if (callout_handle_->getStatus() == CalloutHandle::NEXT_STEP_SKIP) {
            return (hook_response);

        } else {
            LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_HOOK_RECEIVE_SKIP)
                .arg(cmd_name);
        }
    }

    // If we're here it means that the callouts weren't called or the 'skip'
    // status wasn't returned. The latter is the case when the 'list-commands'
    // is being processed. Anyhow, we need to handle the command using local
    // Command Mananger.
    ConstElementPtr response = BaseCommandMgr::handleCommand(cmd_name, params);

    // For the 'list-commands' case we will have to combine commands supported
    // by the hook libraries with the commands that this Command Manager supports.
    if ((cmd_name == "list-commands") && hook_response && response) {
        response = combineCommandsLists(hook_response, response);
    }

    return (response);
}


} // end of namespace isc::config
} // end of namespace isc
