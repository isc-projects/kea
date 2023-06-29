// Copyright (C) 2009-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <cc/data.h>
#include <string>

/// @file command_interpreter.h
///
/// This file contains several functions and constants that are used for
/// handling commands and responses sent over control channel. The design
/// is described here: https://gitlab.isc.org/isc-projects/kea/wikis/Stats-design, but also
/// in @ref ctrlSocket section in the Developer's Guide.

namespace isc {
namespace config {

/// @brief String used for commands ("command")
extern const char *CONTROL_COMMAND;

/// @brief String used for result, i.e. integer status ("result")
extern const char *CONTROL_RESULT;

/// @brief String used for storing textual description ("text")
extern const char *CONTROL_TEXT;

/// @brief String used for arguments map ("arguments")
extern const char *CONTROL_ARGUMENTS;

/// @brief String used for service list ("service")
extern const char *CONTROL_SERVICE;

/// @brief String used for remote address ("remote-address")
extern const char *CONTROL_REMOTE_ADDRESS;

/// @brief Status code indicating a successful operation
const int CONTROL_RESULT_SUCCESS = 0;

/// @brief Status code indicating a general failure
const int CONTROL_RESULT_ERROR = 1;

/// @brief Status code indicating that the specified command is not supported.
const int CONTROL_RESULT_COMMAND_UNSUPPORTED = 2;

/// @brief Status code indicating that the specified command was completed
///        correctly, but failed to produce any results. For example, get
///        completed the search, but couldn't find the object it was looking for.
const int CONTROL_RESULT_EMPTY = 3;

/// @brief Status code indicating that the command was unsuccessful due to a
/// conflict between the command arguments and the server state. For example,
/// a lease4-add fails when the subnet identifier in the command does not
/// match the subnet identifier in the server configuration.
const int CONTROL_RESULT_CONFLICT = 4;

/// @brief A standard control channel exception that is thrown if a function
/// is there is a problem with one of the messages
class CtrlChannelError : public isc::Exception {
public:
    CtrlChannelError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Creates a standard config/command level success answer message
///        (i.e. of the form { "result": 0 }
/// @return Standard command/config success answer message
isc::data::ConstElementPtr createAnswer();

/// @brief Creates a standard config/command level answer message
/// (i.e. of the form { "result": 1, "text": "Invalid command received" }
///
/// @param status_code The return code (0 for success)
/// @param status_text A string to put into the "text" argument
/// @return Standard command/config answer message
isc::data::ConstElementPtr createAnswer(const int status_code,
                                        const std::string& status_text);

/// @brief Creates a standard config/command level answer message
/// (i.e. of the form { "result": status_code, "arguments": arg }
///
/// @param status_code The return code (0 for success)
/// @param arg The optional argument for the answer. This can be of
///        any Element type. May be NULL.
/// @return Standard command/config answer message
isc::data::ConstElementPtr createAnswer(const int status_code,
                                        const isc::data::ConstElementPtr& arg);

/// @brief Creates a standard config/command level answer message
///
/// @param status_code The return code (0 for success)
/// @param status textual representation of the status (used mostly for errors)
/// @param arg The optional argument for the answer. This can be of
///        any Element type. May be NULL.
/// @return Standard command/config answer message
isc::data::ConstElementPtr createAnswer(const int status_code,
                                        const std::string& status,
                                        const isc::data::ConstElementPtr& arg);

/// @brief Parses a standard config/command level answer and returns arguments
/// or text status code.
///
/// If you need to get the text status, please use @ref parseAnswerText.
///
/// @param status_code This value will be set to the return code contained in
///              the message
/// @param msg The message to parse
/// @return The optional argument in the message (or null)
isc::data::ConstElementPtr
parseAnswer(int &status_code, const isc::data::ConstElementPtr& msg);

/// @brief Parses a standard config/command level answer and returns text status.
///
/// This method returns the text status. If you need to get the arguments provided,
/// please use @ref parseAnswer.
///
/// @param status_code This value will be set to the return code contained in
///              the message
/// @param msg The message to parse
/// @return The optional argument in the message (or null)
isc::data::ConstElementPtr
parseAnswerText(int &rcode, const isc::data::ConstElementPtr& msg);

/// @brief Converts answer to printable text
///
/// @param msg answer to be parsed
/// @return printable string
std::string answerToText(const isc::data::ConstElementPtr& msg);

/// @brief Creates a standard command message with no
/// argument (of the form { "command": "my_command" })
///
/// @param command The command string
/// @return The created message
isc::data::ConstElementPtr createCommand(const std::string& command);

/// @brief Creates a standard command message with the
/// given argument (of the form { "command": "my_command", "arguments": arg }
///
/// @param command The command string
/// @param arg The optional argument for the command. This can be of
///        any Element type. May be NULL.
/// @return The created message
isc::data::ConstElementPtr createCommand(const std::string& command,
                                         isc::data::ConstElementPtr arg);

/// @brief Creates a standard config/command command message with no
/// argument and with the given service (of the form
/// { "command": "my_command", "service": [ service ] })
///
/// @param command The command string
/// @param service The target service. May be empty.
/// @return The created message
 isc::data::ConstElementPtr createCommand(const std::string& command,
                                          const std::string& service);

/// @brief Creates a standard config/command command message with the
/// given argument and given service (of the form
/// { "command": "my_command", "arguments": arg, "service": [ service ] }
///
/// @param command The command string
/// @param arg The optional argument for the command. This can be of
///        any Element type. May be NULL.
/// @param service The target service. May be empty.
/// @return The created message
isc::data::ConstElementPtr createCommand(const std::string& command,
                                         isc::data::ConstElementPtr arg,
                                         const std::string& service);

/// @brief Parses the given command into a string containing the actual
///        command and an ElementPtr containing the optional argument.
///
/// @throw CtrlChannelError if this is not a well-formed command
///
/// @param arg This value will be set to the ElementPtr pointing to
///        the argument, or to an empty Map (ElementPtr) if there was none.
/// @param command The command message containing the command (as made
///        by createCommand()
/// @return The command name.
std::string parseCommand(isc::data::ConstElementPtr& arg,
                         isc::data::ConstElementPtr command);


/// @brief Parses the given command into a string containing the command
///        name and an ElementPtr containing the mandatory argument.
///
/// This function expects that command arguments are specified and are
/// a map.
///
/// @throw CtrlChannelError if this is not a well-formed command,
///        arguments are not specified or are not a map.
///
/// @param arg Reference to the data element to which command arguments
///        will be assigned.
/// @param command The command message containing the command and
///        the arguments.
/// @return Command name.
std::string parseCommandWithArgs(isc::data::ConstElementPtr& arg,
                                 isc::data::ConstElementPtr command);

/// @brief Combines lists of commands carried in two responses.
///
/// This method is used to combine list of commands returned by the
/// two command managers.
///
/// If the same command appears in two responses only a single
/// instance is returned in the combined response.
///
/// @param response1 First command response.
/// @param response2 Second command response.
///
/// @return Pointer to the 'list-commands' response holding combined
/// list of commands.
isc::data::ConstElementPtr
combineCommandsLists(const isc::data::ConstElementPtr& response1,
                     const isc::data::ConstElementPtr& response2);

}; // end of namespace isc::config
}; // end of namespace isc

#endif // COMMAND_INTERPRETER_H
