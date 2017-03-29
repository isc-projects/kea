// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOOKED_COMMAND_MGR_H
#define HOOKED_COMMAND_MGR_H

#include <cc/data.h>
#include <config/base_command_mgr.h>
#include <hooks/callout_handle.h>

namespace isc {
namespace config {

/// @brief Command Manager which can delegate commands to a hook library.
///
/// This class extends @ref BaseCommandMgr with the logic to delegate the
/// commands to a hook library if the hook library is installed and provides
/// callouts for the control API.
class HookedCommandMgr : public BaseCommandMgr {
public:

    /// @brief Constructor.
    ///
    /// Initializes callout handle used by the Command Manager.
    HookedCommandMgr();

protected:

    /// @brief Returns callout handle to the derived class.
    ///
    /// @return const pointer to the callout handle.
    const isc::hooks::CalloutHandlePtr& getCalloutHandle() const {
        return (callout_handle_);
    }

    /// @brief Handles the command having a given name and arguments.
    ///
    /// This method checks if the hook library is installed which implements
    /// callouts for the 'control_command_receive' hook point, and calls them
    /// if they exist. If the hook library supports the given command it creates
    /// a response and returns it in the 'response' argument of the
    /// @ref isc::data::ConstElementPtr type. If the callout also sets the 'skip'
    /// status, the response created by the callout is returned. Otherwise, the
    /// @ref BaseCommandMgr::handleCommand is called.
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

    /// @brief Pointer to a callout handle used by this class.
    isc::hooks::CalloutHandlePtr callout_handle_;
};

} // end of namespace isc::config
} // end of namespace isc

#endif
