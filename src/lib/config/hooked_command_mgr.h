// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOOKED_COMMAND_MGR_H
#define HOOKED_COMMAND_MGR_H

#include <cc/data.h>
#include <config/base_command_mgr.h>

namespace isc {
namespace config {

/// @brief Command Manager which can delegate commands to a hook library.
///
/// This class extends @ref BaseCommandMgr with the logic to delegate the
/// commands to a hook library if the hook library is installed and provides
/// command handlers for the control API.
///
/// The command handlers are registered by a hook library by calling
/// @ref isc::hooks::LibraryHandle::registerCommandCallout. This call
/// creates a hook point for this command (if one doesn't exist) and then
/// registers the specified handler(s). When the @ref HookedCommandMgr
/// receives a command for processing it calls the
/// @ref isc::hooks::HooksManager::commandHandlersPresent to check if there
/// are handlers present for this command. If so, the @ref HookedCommandMgr
/// calls @ref isc::hooks::HooksManager::callCommandHandlers to process
/// the command in the hooks libraries. If command handlers are not installed
/// for this command, the @ref HookedCommandMgr will try to process the
/// command on its own.
///
/// The @ref isc::hooks::CalloutHandle::CalloutNextStep flag setting by the
/// command handlers does NOT have any influence on the operation of the
/// @ref HookedCommandMgr, i.e. it will always skip processing command on
/// its own if the command handlers are present for the given command, even
/// if the handlers return an error code.
class HookedCommandMgr : public BaseCommandMgr {
public:

    /// @brief Constructor.
    ///
    /// Initializes callout handle used by the Command Manager.
    HookedCommandMgr();

protected:

    /// @brief Handles the command within the hooks libraries.
    ///
    /// This method checks if the hooks libraries are installed which implement
    /// command handlers for the specified command to be processed. If the
    /// command handlers are present, this method calls them to create a response
    /// and then passes the response back within the @c answer argument.
    ///
    /// Values of all arguments can be modified by the hook library.
    ///
    /// @param cmd_name Command name.
    /// @param params Command arguments.
    /// @param original_cmd Original command received.
    /// @param [out] answer Command processing result returned by the hook.
    ///
    /// @return Boolean value indicating if any callouts have been executed.
    bool
    delegateCommandToHookLibrary(const std::string& cmd_name,
                                 const isc::data::ConstElementPtr& params,
                                 const isc::data::ConstElementPtr& original_cmd,
                                 isc::data::ElementPtr& answer);

    /// @brief Handles the command having a given name and arguments.
    ///
    /// This method calls @ref HookedCommandMgr::delegateCommandToHookLibrary to
    /// try to process the command with the hook libraries, if they are installed.
    ///
    /// @param cmd_name Command name.
    /// @param params Command arguments.
    /// @param original_cmd Original command received.
    ///
    /// @return Pointer to the const data element representing response
    /// to a command.
    virtual isc::data::ConstElementPtr
    handleCommand(const std::string& cmd_name,
                  const isc::data::ConstElementPtr& params,
                  const isc::data::ConstElementPtr& original_cmd);

};

} // end of namespace isc::config
} // end of namespace isc

#endif
