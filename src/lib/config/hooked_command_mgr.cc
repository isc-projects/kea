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

    if (HooksManager::calloutsPresent(Hooks.hook_index_control_command_receive_)) {

        // Delete previously set arguments.
        callout_handle_->deleteAllArguments();

        callout_handle_->setArgument("command", cmd_name);
        callout_handle_->setArgument("arguments", params);

        HooksManager::callCallouts(Hooks.hook_index_control_command_receive_,
                                   *callout_handle_);

        if (callout_handle_->getStatus() == CalloutHandle::NEXT_STEP_SKIP) {
            ConstElementPtr response;
            callout_handle_->getArgument("response", response);
            return (response);

        } else {
            LOG_DEBUG(command_logger, DBG_COMMAND, COMMAND_HOOK_RECEIVE_SKIP)
                .arg(cmd_name);
        }
    }

    return (BaseCommandMgr::handleCommand(cmd_name, params));
}


} // end of namespace isc::config
} // end of namespace isc
