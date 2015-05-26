// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef COMMAND_MGR_H
#define COMMAND_MGR_H

#include <config/command_interpreter.h>
#include <cc/data.h>
#include <boost/noncopyable.hpp>
#include <boost/any.hpp>
#include <string>
#include <map>

namespace isc {
namespace config {

/// @brief CommandMgr exception indicating that the handler specified is not valid
class InvalidCommandHandler : public Exception {
public:
    InvalidCommandHandler(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief CommandMgr exception indicating that the command name is not valid
class InvalidCommandName : public Exception {
public:
    InvalidCommandName(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Commands Manager, responsible for processing external commands
///
/// Commands Manager is a generic interface for handling external commands.
/// Commands can be received over control sockets. Currently unix socket is
/// supported, but additional type (udp, tcp, https etc.) may be added later.
/// The commands and responses are sent in JSON format.
/// See http://kea.isc.org/wiki/StatsDesign for details.
///
/// In general, the command has the following format:
/// {
///     "command": "statistic-get",
///     "arguments": {
///         "name": "received-packets"
///     }
/// }
///
/// And the response is:
///
/// {
///     "result": 0,
///     "observations": {
///         "received-packets": [ [ 1234, "2015-04-15 12:34:45.123" ] ]
///     }
/// }
///
/// CommandsMgr does not implement the commands (except one, "commands-list")
/// itself, but rather provides an interface (see @ref registerCommand,
/// @ref deregisterCommand, @ref processCommand) for other components to use
/// it. The @ref CommandHandler type is specified in a way to easily use
/// existing command handlers in DHCPv4 and DHCPv6 components.
class CommandMgr : public boost::noncopyable {
public:

    /// @brief Defines command handler type
    ///
    /// Command handlers are expected to use this format.
    /// @param name name of the commands
    /// @param params parameters specific to the command
    /// @return response (created with createAnswer())
    typedef boost::function<isc::data::ConstElementPtr (const std::string& name,
        const isc::data::ConstElementPtr& params)> CommandHandler;

    /// @brief CommandMgr is a singleton class. This method returns reference
    /// to its sole instance.
    ///
    /// @return the only existing instance of the manager
    static CommandMgr& instance();

    /// @brief Opens control socket with paramters specified in socket_info
    ///
    /// Currently supported types are:
    /// - unix (required parameters: socket-type: unix, socket-name:/unix/path)
    ///
    /// @throw CommandSocketError if socket creation fails
    ///
    /// @param socket_info describes control socket parameters
    /// @return socket descriptor of the socket created
    int openCtrlSocket(const isc::data::ConstElementPtr& socket_info);

    /// @brief Shuts down any open control sockets
    void closeCtrlSocket();

    /// @brief Registers specified command handler for a given command
    ///
    /// @param cmd name of the command to be handled
    /// @param handler pointer to the method that will handle the command
    void registerCommand(const std::string& cmd, CommandHandler handler);

    /// @brief Deregisters specified command handler
    ///
    /// @param cmd name of the command that's no longer handled
    void deregisterCommand(const std::string& cmd);

    /// @brief Triggers command processing
    ///
    /// This method processes specified command. The command is specified using
    /// a single Element. See @ref CommandMgr for description of its syntax.
    /// Typically, this method is called internally, when there's a new data
    /// received over control socket. However, in some cases (e.g. signal received)
    /// it may be called by external code explicitly. Hence this method is public.
    isc::data::ConstElementPtr processCommand(const isc::data::ConstElementPtr& cmd);

    /// @brief Auxiliary method that removes all installed commands.
    ///
    /// The only unwipeable method is list-commands, which is internally
    /// handled at all times.
    void deregisterAll();

private:

    /// @brief Private constructor
    ///
    /// Registers internal 'list-commands' command.
    CommandMgr();

    /// @brief 'list-commands' command handler
    ///
    /// This method implements command 'list-commands'. It returns a list of all
    /// currently supported commands.
    /// @param name name of the command (should always be 'list-commands')
    /// @param params additional parameters (ignored)
    /// @return structure that includes all currently supported commands
    isc::data::ConstElementPtr
    listCommandsHandler(const std::string& name,
                        const isc::data::ConstElementPtr& params);

    typedef std::map<std::string, CommandHandler> HandlerContainer;

    /// @brief Container for command handlers
    HandlerContainer handlers_;

    /// @brief Socket file descriptor
    int socket_;

    /// @brief Parameters for control socket
    isc::data::ConstElementPtr socket_info_;
};

}; // end of isc::config namespace
}; // end of isc namespace

#endif
