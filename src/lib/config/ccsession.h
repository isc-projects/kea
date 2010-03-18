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

// $Id$

#ifndef __CCSESSION_H
#define __CCSESSION_H 1

#include <string>

#include <config/config_data.h>
#include <config/module_spec.h>
#include <cc/session.h>
#include <cc/data.h>

namespace boost {
namespace asio {
class io_service;
}
}

namespace isc {
namespace config {

///
/// \brief Creates a standard config/command level success answer message
///        (i.e. of the form { "result": [ 0 ] }
/// \return Standard command/config success answer message
ElementPtr createAnswer();

///
/// \brief Creates a standard config/command level answer message
///        (i.e. of the form { "result": [ rcode, arg ] }
/// If rcode != 0, arg must be a StringElement
///
/// \param rcode The return code (0 for success)
/// \param arg For rcode == 0, this is an optional argument of any
///            Element type. For rcode == 1, this argument is mandatory,
///            and must be a StringElement containing an error description
/// \return Standard command/config answer message
ElementPtr createAnswer(const int rcode, const ElementPtr arg);

///
/// \brief Creates a standard config/command level answer message
/// (i.e. of the form { "result": [ rcode, arg ] }
///
/// \param rcode The return code (0 for success)
/// \param arg A string to put into the StringElement argument
/// \return Standard command/config answer message
ElementPtr createAnswer(const int rcode, const std::string& arg);

///
/// Parses a standard config/command level answer message
/// 
/// \param rcode This value will be set to the return code contained in
///              the message
/// \param msg The message to parse
/// \return The optional argument in the message, or an empty ElementPtr
///         if there was no argument. If rcode != 0, this contains a
///         StringElement with the error description.
ElementPtr parseAnswer(int &rcode, const ElementPtr msg);


///
/// \brief Creates a standard config/command command message with no
/// argument (of the form { "command": [ "my_command" ] }
/// 
/// \param command The command string
/// \return The created message
ElementPtr createCommand(const std::string& command);

///
/// \brief Creates a standard config/command command message with the
/// given argument (of the form { "command": [ "my_command", arg ] }
/// 
/// \param command The command string
/// \param arg The optional argument for the command. This can be of 
///        any Element type, but it should conform to the .spec file.
/// \return The created message
ElementPtr createCommand(const std::string& command, ElementPtr arg);

///
/// \brief Parses the given command into a string containing the actual
///        command and an ElementPtr containing the optional argument.
///
/// \param arg This value will be set to the ElementPtr pointing to
///        the argument, or to an empty ElementPtr if there was none.
/// \param command The command message containing the command (as made
///        by createCommand()
/// \return The command string
const std::string parseCommand(ElementPtr& arg, const ElementPtr command);


///
/// \brief A standard cc session exception that is thrown if a function
/// is there is a problem with one of the messages
///
// todo: include types and called function in the exception
class CCSessionError : public isc::Exception {
public:
    CCSessionError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief This modules keeps a connection to the command channel,
/// holds configuration information, and handles messages from
/// the command channel
///
class ModuleCCSession : public ConfigData {
public:
    /**
     * Initialize a config/command session
     * @param module_name: The name of this module. This is not a
     *                     reference because we expect static strings
     *                     to be passed here.
     * @param spec_file_name: The name of the file containing the
     *                        module specification.
     */
    ModuleCCSession(std::string spec_file_name,
                    isc::data::ElementPtr(*config_handler)(isc::data::ElementPtr new_config) = NULL,
                    isc::data::ElementPtr(*command_handler)(const std::string& command, const isc::data::ElementPtr args) = NULL
                    ) throw (isc::cc::SessionError);
    ModuleCCSession(std::string spec_file_name,
                    boost::asio::io_service& io_service,
                    isc::data::ElementPtr(*config_handler)(isc::data::ElementPtr new_config) = NULL,
                    isc::data::ElementPtr(*command_handler)(const std::string& command, const isc::data::ElementPtr args) = NULL
                    ) throw (isc::cc::SessionError);

    /**
     * Returns the socket that is used to communicate with the msgq
     * command channel. This socket should *only* be used to run a
     * select() loop over it. And if not time-critical, it is strongly
     * recommended to only use checkCommand() to check for messages
     *
     * @return The socket used to communicate with the msgq command
     *         channel.
     */
    int getSocket();

    /**
     * Check if there is a command or config change on the command
     * session. If so, the appropriate handler is called if set.
     * If not set, a default answer is returned.
     * This is a non-blocking read; if there is nothing this function
     * will return 0.
     */
    int checkCommand();

    /**
     * The config handler function should expect an ElementPtr containing
     * the full configuration where non-default values have been set.
     * Later we might want to think about more granular control
     * (i.e. this does not scale to for instance lists containing
     * 100000 zones, where the whole list is passed every time a single
     * thing changes)
     */
    void setConfigHandler(isc::data::ElementPtr(*config_handler)(isc::data::ElementPtr new_config)) { config_handler_ = config_handler; };

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
    void setCommandHandler(isc::data::ElementPtr(*command_handler)(const std::string& command, const isc::data::ElementPtr args)) { command_handler_ = command_handler; };

    /**
     * Gives access to the configuration values of a different module
     * Once this function has been called with the name of the specification
     * file of the module you want the configuration of, you can use
     * \c getRemoteConfigValue() to get a specific setting.
     * Changes are automatically updated, but you cannot specify handlers
     * for those changes, must use \c getRemoteConfigValue() to get a value
     * This function will subscribe to the relevant module channel.
     *
     * \param spec_file_name The path to the specification file of
     *                       the module we want to have configuration
     *                       values from
     * \return The name of the module specified in the given specification
     *         file
     */
    std::string addRemoteConfig(const std::string& spec_file_name);

    /**
     * Removes the module with the given name from the remote config
     * settings. If the module was not added with \c addRemoteConfig(),
     * nothing happens.
     */
    void removeRemoteConfig(const std::string& module_name);

    /**
     * Returns the current configuration value for the given module
     * name at the given identifier. See \c ConfigData::getValue() for
     * more details.
     * Raises a ModuleCCSessionError if the module name is unknown
     * Raises a DataNotFoundError if the identifier does not exist
     * in the specification.
     *
     * \param module_name The name of the module to get a config value for
     * \param identifier The identifier of the config value
     * \return The configuration setting at the given identifier
     */
    ElementPtr getRemoteConfigValue(const std::string& module_name, const std::string& identifier);
    
private:
    void init(
        std::string spec_file_name,
        isc::data::ElementPtr(*config_handler)(
            isc::data::ElementPtr new_config),
        isc::data::ElementPtr(*command_handler)(
            const std::string& command, const isc::data::ElementPtr args)
        ) throw (isc::cc::SessionError);
    ModuleSpec readModuleSpecification(const std::string& filename);
    void startCheck();
    
    std::string module_name_;
    isc::cc::Session session_;
    ModuleSpec module_specification_;
    ElementPtr handleConfigUpdate(ElementPtr new_config);

    isc::data::ElementPtr(*config_handler_)(isc::data::ElementPtr new_config);
    isc::data::ElementPtr(*command_handler_)(const std::string& command, const isc::data::ElementPtr args);

    std::map<std::string, ConfigData> remote_module_configs_;
    void updateRemoteConfig(const std::string& module_name, ElementPtr new_config);
};

}
}
#endif // __CCSESSION_H

// Local Variables:
// mode: c++
// End:
