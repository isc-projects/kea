// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CTRL_AGENT_COMMAND_MGR_H
#define CTRL_AGENT_COMMAND_MGR_H

#include <config/hooked_command_mgr.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace agent {

/// @brief Command Manager for Control Agent.
///
/// This is an implementation of the Command Manager within Control Agent.
/// In addition to the standard capabilities of the @ref HookedCommandMgr
/// it is also intended to forward commands to the respective Kea servers
/// when the command is not supported directly by the Control Agent.
///
/// @todo This Command Manager doesn't yet support forwarding commands.
///
/// The @ref CtrlAgentCommandMgr is implemented as a singleton. The commands
/// are registered using @c CtrlAgentCommandMgr::instance().registerCommand().
/// The @ref CtrlAgentResponseCreator uses the sole instance of the Command
/// Manager to handle incoming commands.
class CtrlAgentCommandMgr : public config::HookedCommandMgr,
                            public boost::noncopyable {
public:

    /// @brief Returns sole instance of the Command Manager.
    static CtrlAgentCommandMgr& instance();

    /// @brief Handles the command having a given name and arguments.
    ///
    /// This method extends the base implementation with the ability to forward
    /// commands to Kea servers if the Control Agent failed to handle it itself.
    ///
    /// @todo Currently this method only wraps an answer within a list Element.
    /// This will be later used to include multiple answers within this list.
    /// For now it is just a single answer from the Control Agent.
    ///
    /// @param cmd_name Command name.
    /// @param params Command arguments.
    ///
    /// @return Pointer to the const data element representing response
    /// to a command.
    virtual isc::data::ConstElementPtr
    handleCommand(const std::string& cmd_name,
                  const isc::data::ConstElementPtr& params);

private:
    /// @brief Private constructor.
    ///
    /// The instance should be created using @ref CtrlAgentCommandMgr::instance,
    /// thus the constructor is private.
    CtrlAgentCommandMgr();

};

} // end of namespace isc::agent
} // end of namespace isc

#endif
