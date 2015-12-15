// Copyright (C) 2009,2015  Internet Systems Consortium, Inc. ("ISC")
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
/// is described here: http://kea.isc.org/wiki/StatsDesign, but also
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

/// @brief Status code indicating a successful operation
const int CONTROL_RESULT_SUCCESS = 0;

/// @brief Status code indicating a general failure
const int CONTROL_RESULT_ERROR = 1;

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
/// @param status textual represenation of the status (used mostly for errors)
/// @param arg The optional argument for the answer. This can be of
///        any Element type. May be NULL.
/// @return Standard command/config answer message
isc::data::ConstElementPtr createAnswer(const int status_code,
                                        const std::string& status,
                                        const isc::data::ConstElementPtr& arg);

/// @brief Parses a standard config/command level answer message.
///
/// @param status_code This value will be set to the return code contained in
///              the message
/// @param msg The message to parse
/// @return The optional argument in the message.
isc::data::ConstElementPtr parseAnswer(int &status_code,
                                       const isc::data::ConstElementPtr& msg);

/// @brief Creates a standard config/command command message with no
/// argument (of the form { "command": "my_command" })
///
/// @param command The command string
/// @return The created message
isc::data::ConstElementPtr createCommand(const std::string& command);

/// @brief Creates a standard config/command command message with the
/// given argument (of the form { "command": "my_command", "arguments": arg }
///
/// @param command The command string
/// @param arg The optional argument for the command. This can be of
///        any Element type. May be NULL.
/// @return The created message
isc::data::ConstElementPtr createCommand(const std::string& command,
                                         isc::data::ConstElementPtr arg);

/// @brief Parses the given command into a string containing the actual
///        command and an ElementPtr containing the optional argument.
///
/// @throw Raises a CtrlChannelError if this is not a well-formed command
///
/// @param arg This value will be set to the ElementPtr pointing to
///        the argument, or to an empty Map (ElementPtr) if there was none.
/// @param command The command message containing the command (as made
///        by createCommand()
/// @return The command name
std::string parseCommand(isc::data::ConstElementPtr& arg,
                         isc::data::ConstElementPtr command);

}; // end of namespace isc::config
}; // end of namespace isc

#endif // COMMAND_INTERPRETER_H
