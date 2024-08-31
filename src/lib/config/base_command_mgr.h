// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BASE_COMMAND_MGR_H
#define BASE_COMMAND_MGR_H

#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <functional>
#include <map>
#include <string>

namespace isc {
namespace config {

/// @brief Exception indicating that the handler specified is not valid
class InvalidCommandHandler : public Exception {
public:
    InvalidCommandHandler(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception indicating that the command name is not valid
class InvalidCommandName : public Exception {
public:
    InvalidCommandName(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Commands Manager, responsible for processing external commands.
///
/// Commands Manager is a generic interface for handling external commands.
/// Commands are received over control sockets. Derivations of this class
/// provide implementations of the control socket layers, e.g. unix domain
/// sockets, TCP sockets etc. This base class merely provides methods to manage
/// command handling functions, i.e. register commands, deregister commands.
/// It also includes a @ref BaseCommandMgr::processCommand method which
/// uses the command as an input and invokes appropriate handlers.
///
/// The commands and responses are formatted using JSON.
/// See https://gitlab.isc.org/isc-projects/kea/wikis/designs/Stats-design
/// for details.
///
/// Below is an example of the command using JSON format:
/// @code
/// {
///     "command": "statistic-get",
///     "arguments": {
///         "name": "received-packets"
///     }
/// }
/// @endcode
///
/// And the response is:
///
/// @code
/// {
///     "result": 0,
///     "arguments": {
///         "received-packets": [ [ 1234, "2015-04-15 12:34:45.123" ] ]
///     }
/// }
/// @endcode
///
/// BaseCommandsMgr does not implement the commands (except one,
/// "list-commands") itself, but rather provides an interface
/// (see @ref registerCommand, @ref deregisterCommand, @ref processCommand)
/// for other components to use it.
class BaseCommandMgr {
public:

    /// @brief Defines command handler type
    ///
    /// Command handlers are expected to use this format.
    ///
    /// @param name name of the commands
    /// @param params parameters specific to the command
    /// @return response (created with createAnswer())
    typedef std::function<isc::data::ConstElementPtr (const std::string& name,
        const isc::data::ConstElementPtr& params)> CommandHandler;

    /// @brief Defines extended command handler type.
    ///
    /// This command handler includes third parameter which holds the
    /// entire command control message. The handler can retrieve
    /// additional information from this parameter, e.g. 'service'.
    ///
    /// @param name name of the commands
    /// @param params parameters specific to the command
    /// @param original original control command.
    /// @return response (created with createAnswer())
    typedef std::function<isc::data::ConstElementPtr (const std::string& name,
        const isc::data::ConstElementPtr& params,
        const isc::data::ConstElementPtr& original)> ExtendedCommandHandler;

    /// @brief Constructor.
    ///
    /// Registers hookpoint "command-processed"
    /// Registers "list-commands" command.
    BaseCommandMgr();

    /// @brief Destructor.
    virtual ~BaseCommandMgr() { };

    /// @brief Triggers command processing.
    ///
    /// This method processes specified command. The command is specified using
    /// a single Element. See @ref BaseCommandMgr for description of its syntax.
    /// After the command has been handled, callouts for the hook point,
    /// "command-processed" will be invoked.
    ///
    /// This method is virtual so it can be overridden in derived classes to
    /// pre-process command and post-process response if necessary.
    ///
    /// This method is an entry point for dealing with a command. Internally
    /// it calls @c BaseCommandMgr::handleCommand.
    ///
    /// @param cmd Pointer to the data element representing command in JSON
    /// format.
    virtual isc::data::ConstElementPtr
    processCommand(const isc::data::ConstElementPtr& cmd);

    /// @brief Registers specified command handler for a given command
    ///
    /// @param cmd Name of the command to be handled.
    /// @param handler Pointer to the method that will handle the command.
    void registerCommand(const std::string& cmd, CommandHandler handler);

    /// @brief Registers specified command handler for a given command.
    ///
    /// This variant of the method uses extended command handler which, besides
    /// command name and arguments, also has a third parameter 'original_cmd'
    /// in its signature. Such handlers can retrieve additional parameters from
    /// the command, e.g. 'service' indicating where the command should be
    /// routed.
    ///
    /// @param cmd Name of the command to be handled.
    /// @param handler Pointer to the method that will handle the command.
    void registerExtendedCommand(const std::string& cmd,
                                 ExtendedCommandHandler handler);

    /// @brief Deregisters specified command handler.
    ///
    /// @param cmd Name of the command that's no longer handled.
    void deregisterCommand(const std::string& cmd);

    /// @brief Auxiliary method that removes all installed commands.
    ///
    /// The only unwipeable method is list-commands, which is internally
    /// handled at all times.
    void deregisterAll();

    /// @brief returns a hash of a given Element structure
    ///
    /// The hash is currently implemented as SHA256 on the string
    // representation of the structure.
    ///
    /// @param config typically full config, but hash can be calculated on any structure
    /// @return hash of string representation
    static std::string getHash(const isc::data::ConstElementPtr& config);

protected:

    /// @brief Handles the command having a given name and arguments.
    ///
    /// This method can be overridden in the derived classes to provide
    /// custom logic for processing commands. For example, the
    /// @ref HookedCommandMgr extends this method to delegate commands
    /// processing to a hook library.
    ///
    /// @param cmd_name Command name.
    /// @param params Command arguments.
    /// @param original_cmd Pointer to the entire command received. It may
    /// be sometimes useful to retrieve additional parameters from this
    /// command.
    ///
    /// @return Pointer to the const data element representing response
    /// to a command.
    virtual isc::data::ConstElementPtr
    handleCommand(const std::string& cmd_name,
                  const isc::data::ConstElementPtr& params,
                  const isc::data::ConstElementPtr& original_cmd);

    struct HandlersPair {
        CommandHandler handler;
        ExtendedCommandHandler extended_handler;
    };

    /// @brief Type of the container for command handlers.
    typedef std::map<std::string, HandlersPair> HandlerContainer;

    /// @brief Container for command handlers.
    HandlerContainer handlers_;

private:

    /// @brief 'list-commands' command handler.
    ///
    /// This method implements command 'list-commands'. It returns a list of all
    /// currently supported commands.
    ///
    /// @param name Name of the command (should always be 'list-commands').
    /// @param params Additional parameters (ignored).
    ///
    /// @return Pointer to the structure that includes all currently supported
    /// commands.
    isc::data::ConstElementPtr
    listCommandsHandler(const std::string& name,
                        const isc::data::ConstElementPtr& params);
};

} // end of namespace isc::config
} // end of namespace isc

#endif
