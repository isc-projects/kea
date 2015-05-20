// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef CCSESSION_H
#define CCSESSION_H 1

#include <config/config_data.h>
#include <config/module_spec.h>

#include <cc/data.h>

#include <string>
#include <list>
#include <boost/function.hpp>

namespace isc {
namespace config {

extern const char *CONTROL_COMMAND;

extern const char *CONTROL_RESULT;
extern const char *CONTROL_TEXT;
extern const char *CONTROL_ARGUMENTS;

const int CONTROL_RESULT_SUCCESS = 0;
const int CONTROL_RESULT_ERROR = 1;

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
/// @param status_text A string to put into the "text" argument
/// @return Standard command/config answer message
isc::data::ConstElementPtr createAnswer(const int status_code,
                                        const isc::data::ConstElementPtr& arg);

/// @brief Creates a standard config/command level answer message
///        (i.e. of the form { "result": X, "[ rcode, arg ] }
/// If rcode != 0, arg must be a StringElement
///
/// @param status_code The return code (0 for success)
/// @param arg For status_code == 0, this is an optional argument of any
///            Element type. For status_code == 1, this argument is mandatory,
///            and may be any type of ElementPtr.
/// @return Standard command/config answer message
isc::data::ConstElementPtr createAnswer(const int status_code,
                                        const std::string& status,
                                        const isc::data::ConstElementPtr& arg);

/// @brief Parses a standard config/command level answer message.
///
/// @param status_code This value will be set to the return code contained in
///              the message
/// @param msg The message to parse
/// @return The optional argument in the message, or an empty ElementPtr
///         if there was no argument. If rcode != 0, this contains a
///         StringElement with the error description.
isc::data::ConstElementPtr parseAnswer(int &status_code,
                                       const isc::data::ConstElementPtr& msg);

/// @brief Creates a standard config/command command message with no
/// argument (of the form { "command": "my_command" }
///
/// @param command The command string
/// @return The created message
isc::data::ConstElementPtr createCommand(const std::string& command);

/// @brief Creates a standard config/command command message with the
/// given argument (of the form { "command": "my_command", "arguments": arg }
///
/// @param command The command string
/// @param arg The optional argument for the command. This can be of
///        any Element type, but it should conform to the .spec file.
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
/// \return The command name
std::string parseCommand(isc::data::ConstElementPtr& arg,
                         isc::data::ConstElementPtr command);

/// @brief A standard control channel exception that is thrown if a function
/// is there is a problem with one of the messages
class CtrlChannelError : public isc::Exception {
public:
    CtrlChannelError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

    /**
     * Set a command handler; the function that is passed takes an
     * ElementPtr, pointing to a list element, containing
     * [ module_name, command_name, arg1, arg2, ... ]
     * The returned ElementPtr should look like
     * { "result": [ return_value, result_value ] }
     * result value here is optional and depends on the command
     *
     * This protocol is very likely to change.
     */
    void setCommandHandler(isc::data::ConstElementPtr(*command_handler)(
                               const std::string& command,
                               isc::data::ConstElementPtr args));

    /**
     * Gives access to the configuration values of a different module
     * Once this function has been called with the name of the specification
     * file or the module you want the configuration of, you can use
     * \c getRemoteConfigValue() to get a specific setting.
     * Changes are automatically updated, and you can specify handlers
     * for those changes. This function will subscribe to the relevant module
     * channel.
     *
     * This method must be called before calling the \c start() method on the
     * ModuleCCSession (it also implies the ModuleCCSession must have been
     * constructed with start_immediately being false).
     *
     * \param spec_name This specifies the module to add. It is either a
     *                  filename of the spec file to use or a name of module
     *                  (in case it's a module name, the spec data is
     *                  downloaded from the configuration manager, therefore
     *                  the configuration manager must know it). If
     *                  spec_is_filename is true (the default), then a
     *                  filename is assumed, otherwise a module name.
     * \param handler The handler functor called whenever there's a change.
     *                Called once initially from this function. May be NULL
     *                if you don't want any handler to be called and you're
     *                fine with requesting the data through
     *                getRemoteConfigValue() each time.
     *
     *                The handler should not throw, or it'll fall through and
     *                the exception will get into strange places, probably
     *                aborting the application.
     * \param spec_is_filename Says if spec_name is filename or module name.
     * \return The name of the module specified in the given specification
     *         file
     */
    typedef boost::function<void(const std::string&,
                                 isc::data::ConstElementPtr,
                                 const ConfigData&)> RemoteHandler;

    /// \brief Called when a notification comes
    ///
    /// The callback should be exception-free. If it raises an exception,
    /// it'll leak through the event loop up and probably terminate the
    /// application.
    ///
    /// \param event_name The identification of event type.
    /// \param params The parameters of the event. This may be NULL
    ///     pointer in case no parameters were sent with the event.
    typedef boost::function<void (const std::string& event_name,
                                  const data::ConstElementPtr& params)>
        NotificationCallback;

    /// \brief Multiple notification callbacks for the same notification
    typedef std::list<NotificationCallback> NotificationCallbacks;

    /// \brief Returns the loggers related to this module
    ///
    /// This function does two things;
    /// - it drops the configuration parts for loggers for other modules.
    /// - it replaces the '*' in the name of the loggers by the name of
    ///   this module, but *only* if the expanded name is not configured
    ///   explicitly.
    ///
    /// Examples: if this is the module b10-resolver,
    /// For the config names ['*', 'b10-auth']
    /// The '*' is replaced with 'b10-resolver', and this logger is used.
    /// 'b10-auth' is ignored (of course, it will not be in the b10-auth
    /// module).
    ///
    /// For ['*', 'b10-resolver']
    /// The '*' is ignored, and only 'b10-resolver' is used.
    ///
    /// For ['*.reslib', 'b10-resolver']
    /// Or ['b10-resolver.reslib', '*']
    /// Both are used, where the * will be expanded to b10-resolver
    ///
    /// \note This is a public function at this time, but mostly for
    /// the purposes of testing. Once we can directly test what loggers
    /// are running, this function may be moved to the unnamed namespace
    ///
    /// \param loggers the original 'loggers' config list
    /// \return ListElement containing only loggers relevant for this
    ///         module, where * is replaced by the root logger name
    isc::data::ConstElementPtr
    getRelatedLoggers(isc::data::ConstElementPtr loggers);

}; // end of namespace isc::config
}; // end of namespace isc

#endif // CCSESSION_H
