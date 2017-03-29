// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CTRL_AGENT_COMMAND_MGR_H
#define CTRL_AGENT_COMMAND_MGR_H

#include <config/hooked_command_mgr.h>
#include <exceptions/exceptions.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <array>

namespace isc {
namespace agent {

/// @brief Exception thrown when an error occurred during control command
/// forwarding.
class CommandForwardingError : public Exception {
public:
    CommandForwardingError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown when command forwarding has been skipped.
class CommandForwardingSkip : public Exception {
public:
    CommandForwardingSkip(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

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
    /// @param original_cmd Original command being processed.
    ///
    /// @return Pointer to the const data element representing response
    /// to a command.
    virtual isc::data::ConstElementPtr
    handleCommand(const std::string& cmd_name,
                  const isc::data::ConstElementPtr& params,
                  const isc::data::ConstElementPtr& orginal_cmd);

private:

    /// @brief Tries to forward received control command to Kea servers.
    ///
    /// When the Control Agent was unable to process the control command
    /// because it doesn't recognize it, the command should be forwarded to
    /// the specific Kea services listed within a 'service' parameter.
    ///
    /// @todo Currently only one service per control command is supported.
    /// Forwarding to multiple services should be allowed in the future.
    ///
    /// This method makes an attempt to forward the control command. If
    /// the 'service' parameter is not specified or it is empty, the
    /// command is not forwarded and the @ref CommandForwardingSkip exception
    /// is thrown. The caller catching this exception should not treat
    /// this situation as an error but this is normal situation when the
    /// message is not intended to be forwarded.
    ///
    /// All other exceptions should be treated as an error.
    ///
    /// @param cmd_name Command name.
    /// @param command Pointer to the object representing the forwarded command.
    ///
    /// @return Response to forwarded command.
    /// @throw CommandForwardingError when an error occurred during forwarding.
    /// @throw CommandForwardingSkip when 'service' parameter hasn't been
    /// specified which means that the command should not be forwarded.
    isc::data::ConstElementPtr
    tryForwardCommand(const std::string& cmd_name,
                      const isc::data::ConstElementPtr& command);

    /// @brief Private constructor.
    ///
    /// The instance should be created using @ref CtrlAgentCommandMgr::instance,
    /// thus the constructor is private.
    CtrlAgentCommandMgr();

    /// @brief Buffer into which responses to forwarded commands are stored.
    std::array<char, 8192> receive_buf_;

};

} // end of namespace isc::agent
} // end of namespace isc

#endif
